#include "simupdown.h"

#include "out/split_vertex_exe.hpp"
#include "updown_config.h"
#include <bits/types/FILE.h>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <sys/types.h>
#ifdef BASIM
#include <basimupdown.h>
#endif

#ifdef GEM5_MODE
#include <gem5/m5ops.h>
#endif

// #define DEBUG
#define DUMP_OUTPUT
// #define DEBUG_OUTPUT

#define USAGE                                                                                                                                                  \
  "USAGE: ./updown_vertex_split <graph_file> <num_uds> <max_split_degree> (<sht_start_ud> <num_bucket_per_lane> <num_entry_per_bucket>)\n\
  graph_file: \t\tgraph file name.\n\
  num_uds: \t\tnumber of UDs per node.\n\
  max_split_degree: \tmaximum degree after split.\n\
  sht_start_ud: \tSHT start updown id.\n\
  num_bucket_per_lane: \tnumber of SHT buckets per lane.\n\
  num_entry_per_bucket:\tnumber of entries per SHT bucket.\n"

#define NUM_LANE_PER_UD 64
#define NUM_UD_PER_CLUSTER 4
#define NUM_CLUSTER_PER_NODE 8
#define NUM_NODES 1

#define TOP_FLAG_OFFSET 0
#define SEND_BUFFER_OFFSET 8
#define SPLIT_V_SHT_OFFSET 1152
#define HIGH_DEG_SHT_OFFSET 1216
#define HEAP_OFFSET 1600
#define NUM_BUCKETS_PER_LANE 64
#define NUM_ENTRIES_PER_BUCKET 16
#define SPLIT_V_SHT_VALUE_SIZE 2

struct Vertex {
  uint64_t degree;
  uint64_t orig_vid;
  uint64_t vid;
  uint64_t *neighbors;
  uint64_t distance;
  uint64_t parent;
  uint64_t split_range;
  uint64_t padding;
};

struct Edge {
  uint64_t src;
  uint64_t dst;
};

typedef uint64_t Count;

struct SHTExtAlloc {
  UpDown::word_t desc_lm_offset;
  UpDown::word_t lane_desc_lm_offset;
  UpDown::word_t start_nwid;
  UpDown::word_t num_lanes;
  UpDown::word_t num_buckets_per_lane;
  UpDown::word_t num_entries_per_bucket;
  UpDown::word_t val_num_words;
  UpDown::word_t *dram_alloc_addr;
  constexpr UpDown::word_t desc_size() { return 4 * sizeof(UpDown::word_t); }
  constexpr UpDown::word_t lane_desc_size() { return (3 + (3 + 8) * num_buckets_per_lane + 3) * sizeof(UpDown::word_t); }
};

struct Iterator {
  uint64_t itr_0;
  uint64_t itr_1;
};

int main(int argc, char *argv[]) {

  if (argc < 4) {
    printf("Insufficient Input Params\n");
    printf("%s\n", USAGE);
    exit(1);
  }

  uint64_t num_nodes = NUM_NODES;
  uint64_t num_uds = NUM_UD_PER_CLUSTER * NUM_CLUSTER_PER_NODE;
  uint64_t num_lanes_per_ud = NUM_LANE_PER_UD;

  char *graph_file = argv[1];
  num_uds = atoi(argv[2]);
  int max_split_degree = atoi(argv[3]);
  uint64_t sht_start_nwid = (num_uds / 2) * num_lanes_per_ud;
  uint64_t num_entry_per_bucket = NUM_ENTRIES_PER_BUCKET;
  uint64_t num_buckets_per_lane = NUM_BUCKETS_PER_LANE;
  if (argc > 4) {
    sht_start_nwid = atoi(argv[4]) * num_lanes_per_ud;
  }
  if (argc > 5) {
    num_buckets_per_lane = atoi(argv[5]);
  }
  if (argc > 6) {
    num_entry_per_bucket = atoi(argv[6]);
  }

  uint64_t num_lanes = num_nodes * num_uds * num_lanes_per_ud;
  uint64_t num_sht_lanes = num_lanes - sht_start_nwid;
  uint64_t num_kvmsr_lanes = num_lanes - num_sht_lanes;

  printf("Vertex split program configurations: \n\tnum_nodes = %ld, "
         "\n\tnum_uds_per_node = %ld, \n\tnum_lanes_per_ud = %ld, \n",
         num_nodes, num_uds, num_lanes_per_ud);
  printf("\tnum_lanes = %ld\n", num_lanes);

  printf("SHT configurations: \n\tnum_buckets_per_lane = %ld, "
         "\n\tnum_entry_per_bucket = %ld"
         "\n\tstart_nwid = %ld"
         "\n\tnum_sht_lanes = %ld\n",
         num_buckets_per_lane, num_entry_per_bucket, sht_start_nwid, num_sht_lanes);

  printf("Max split degree = %d\n", max_split_degree);

  // Set up machine parameters
  UpDown::ud_machine_t machine;
  machine.NumLanes = num_lanes_per_ud;
  machine.NumUDs = std::min((int)num_uds, NUM_UD_PER_CLUSTER);
  machine.NumStacks = std::ceil((double)num_uds / NUM_UD_PER_CLUSTER);
  machine.NumNodes = num_nodes;
  machine.LocalMemAddrMode = 1;

#ifdef GEM5_MODE
  UpDown::UDRuntime_t *split_v_rt = new UpDown::UDRuntime_t(machine);
#elif BASIM
  UpDown::BASimUDRuntime_t *split_v_rt = new UpDown::BASimUDRuntime_t(machine, "split_vertex_exe.bin", 0, 1);
#else
  // Init runtime
  UpDown::SimUDRuntime_t *split_v_rt = new UpDown::SimUDRuntime_t(machine, "split_vertex_exe", "split_vertex_exe", "./", UpDown::EmulatorLogLevel::FULL_TRACE);
#endif

#ifdef DEBUG
  printf("=== Base Addresses ===\n");
  split_v_rt->dumpBaseAddrs();
  printf("\n=== Machine Config ===\n");
  split_v_rt->dumpMachineConfig();
#endif
  // Read graph file
  FILE *edge_list_file = fopen(graph_file, "rb");
  if (edge_list_file == NULL) {
    printf("Error: cannot open graph file %s\n", graph_file);
    exit(1);
  }
  uint64_t scale;
  uint64_t num_edges;
  uint64_t num_vertices;
  std::size_t n;

  fseek(edge_list_file, 0, SEEK_SET);
  n = fread(&scale, sizeof(scale), 1, edge_list_file);
  n = fread(&num_edges, sizeof(num_edges), 1, edge_list_file);
  num_vertices = std::pow(2, scale);
  printf("Graph configurations:\n\tnum_vertices=%ld\n\tscale=%ld\n\tnum_edges=%ld\n", num_vertices, scale, num_edges);

  printf("Allocating memmory for edge list...\n");

  Edge *edge_list = reinterpret_cast<Edge *>(split_v_rt->mm_malloc(num_edges * sizeof(Edge)));
  n = fread(edge_list, sizeof(Edge), num_edges,
            edge_list_file); // read in all vertices
  fclose(edge_list_file);

#ifdef DEBUG_INPUT
  printf("------------------- Input Edge list = %lu(%p) -------------------\n", (uint64_t)edge_list, edge_list);
  for (int i = 0; i < num_edges; i++) {
    printf("(%ld, %ld)\t", edge_list[i].src, edge_list[i].dst);
    if ((i + 1) % 16 == 0) {
      printf("\n");
    }
  }
#endif

  int num_partitions = num_lanes * num_buckets_per_lane;
  Iterator *partitions = reinterpret_cast<Iterator *>(split_v_rt->mm_malloc((num_partitions) * sizeof(Iterator)));

#ifdef DEBUG
  printf("-------------------\nparitions = %lu(%p)\n", (uint64_t)partitions, partitions);
#endif

  // Allocate the neighbor lists bin.
  uint64_t num_nlist_bins = (num_kvmsr_lanes / num_lanes_per_ud);
  uint64_t nlist_bin_size = num_edges * sizeof(uint64_t);
  printf("-------------------\nNeighbor lists store, size = %ld, bin size per updown = %ld.\n", num_nlist_bins * nlist_bin_size, nlist_bin_size);
  uint64_t *nlists_bin = reinterpret_cast<uint64_t *>(split_v_rt->mm_malloc(nlist_bin_size * num_nlist_bins));
  printf("-------------------\nNeighbor lists store = %lu(%p), size = %ld, bin size per updown = %ld.\n", (uint64_t)nlists_bin, nlists_bin,
         num_nlist_bins * nlist_bin_size, nlist_bin_size);

  fflush(stdout);

  // Initialize split vertex SHT
  SHTExtAlloc sht_ext_alloc;
  sht_ext_alloc.start_nwid = sht_start_nwid;
  sht_ext_alloc.num_lanes = num_sht_lanes;
  sht_ext_alloc.val_num_words = SPLIT_V_SHT_VALUE_SIZE;
  sht_ext_alloc.num_buckets_per_lane = num_buckets_per_lane;
  sht_ext_alloc.num_entries_per_bucket = num_entry_per_bucket;
  sht_ext_alloc.lane_desc_lm_offset = HEAP_OFFSET;
  sht_ext_alloc.dram_alloc_addr = reinterpret_cast<UpDown::word_t *>(split_v_rt->mm_malloc(
      num_sht_lanes * sht_ext_alloc.num_buckets_per_lane * sht_ext_alloc.num_entries_per_bucket * (sht_ext_alloc.val_num_words + 1) * sizeof(UpDown::word_t)));

  // Initialize high degree SHT
  UpDown::word_t high_deg_sht_offset = HIGH_DEG_SHT_OFFSET;
  UpDown::word_t bucket_desc_lm_start_off = HEAP_OFFSET + (sht_ext_alloc.lane_desc_size() * 2);
  UpDown::word_t entry_size = 16;
  UpDown::word_t alloc_entries_per_bucket = num_entry_per_bucket;
  UpDown::word_t send_buffer_offset = SEND_BUFFER_OFFSET;
  uint64_t high_deg_sht_dram_size = num_sht_lanes * num_buckets_per_lane * entry_size * alloc_entries_per_bucket;
  void *high_deg_sht_dram_alloc = split_v_rt->mm_malloc(high_deg_sht_dram_size);

#ifdef DEBUG
  printf("-------------------\nHigh degree SHT store = %lu(%p), size = %ld.\n", (uint64_t)high_deg_sht_dram_alloc, high_deg_sht_dram_alloc,
         high_deg_sht_dram_size);
#endif

  Count *sample_deg_count = reinterpret_cast<Count *>(split_v_rt->mm_malloc(num_vertices * sizeof(Count)));
  memset(sample_deg_count, 0, num_vertices * sizeof(Count));

  fflush(stdout);
#ifdef GEM5_MODE
  m5_switch_cpu();
#endif

  printf("Prepare SHT initialization operands done.\n");
  UpDown::networkid_t nwid(0, false, 0);
  UpDown::word_t flag = 0;
  UpDown::operands_t *single_word_sht_init_ops;

  single_word_sht_init_ops = new UpDown::operands_t(9);
  single_word_sht_init_ops->set_operand(0, high_deg_sht_offset); // SHT_DESC_LM_OFFSET
  single_word_sht_init_ops->set_operand(1, send_buffer_offset);  // LM buf offset (8 words buffer)
  single_word_sht_init_ops->set_operand(2, sht_start_nwid);      // X10 - START_NWID
  single_word_sht_init_ops->set_operand(3,
                                        num_sht_lanes);                              // X11 - NUM_ALLOC_LANES
  single_word_sht_init_ops->set_operand(4, bucket_desc_lm_start_off);                // X12 - BUCKET_DESC_LM_OFFSET
  single_word_sht_init_ops->set_operand(5, (UpDown::word_t)high_deg_sht_dram_alloc); // X13 - DRAM_ALLOC_ADDR
  single_word_sht_init_ops->set_operand(6, num_buckets_per_lane);                    // X14 - BUCKETS_PER_LANE
  single_word_sht_init_ops->set_operand(7, alloc_entries_per_bucket);                // X15 - ENTRIES_PER_BUCKET
  single_word_sht_init_ops->set_operand(8, num_kvmsr_lanes);                         // X15 - NUM_KVMSR_LANES

  flag = 0;
  split_v_rt->t2ud_memcpy(&flag, 8, nwid, 0);                                    // set signal flag to 0
  split_v_rt->send_event(UpDown::event_t(split_vertex_exe::single_word_SHT_init, /*Event Label*/
                                         nwid,                                   /*Network ID*/
                                         UpDown::CREATE_THREAD,                  /*Thread ID*/
                                         single_word_sht_init_ops                /*Operands*/
                                         ));

#ifdef GEM5_MODE
  m5_reset_stats(0, 0);
#endif

  split_v_rt->start_exec(nwid);

  split_v_rt->test_wait_addr(nwid, 0, 1);

#ifdef GEM5_MODE
  m5_dump_reset_stats(0,0);
#endif

  printf("High degree SHT initialization terminates.\n");
  fflush(stdout);

  UpDown::operands_t sampling_ops(8);
  /* operands
    OB_0: Pointer to the partition array (64-bit DRAM address)
    OB_1: Number of partitions per lane
    OB_2: Number of lanes
    OB_3: Pointer to edge list (64-bit DRAM address)
    OB_4: Number of edges
    OB_5: Pointer to edge list (64-bit DRAM address)
    OB_6: Number of vertices
  */
  sampling_ops.set_operand(0, (uint64_t)partitions);
  sampling_ops.set_operand(1, (uint64_t)1);
  sampling_ops.set_operand(2, (uint64_t)num_kvmsr_lanes);
  sampling_ops.set_operand(3, (uint64_t)edge_list);
  sampling_ops.set_operand(4, (uint64_t)num_edges);
  sampling_ops.set_operand(5, (uint64_t)sample_deg_count);
  sampling_ops.set_operand(6, (uint64_t)num_vertices);
  sampling_ops.set_operand(7, (uint64_t)max_split_degree);

  printf("Prepare sampling program operands done.\n");

  UpDown::event_t sampling(split_vertex_exe::sampling__entry_event /*Event Label*/, nwid, UpDown::CREATE_THREAD /*Thread ID*/, &sampling_ops /*Operands*/);

  // Init top flag to 0
  flag = 0;
  split_v_rt->t2ud_memcpy(&flag, sizeof(uint64_t), nwid, TOP_FLAG_OFFSET /*Offset*/);

  printf("Clear top flag.\n");
  split_v_rt->send_event(sampling);

#ifdef GEM5_MODE
  m5_reset_stats(0, 0);
#endif

  split_v_rt->start_exec(nwid);

  split_v_rt->test_wait_addr(nwid, TOP_FLAG_OFFSET, 1);

#ifdef GEM5_MODE
  m5_dump_reset_stats(0,0);
#endif

  printf("Sampling program terminates.\n");
  fflush(stdout);

  UpDown::operands_t sht_init_ops(6);
  // X8  - PGA_DESC_LM_OFFSET [0:31] | TMP_BUF_LM_OFFSET [32:63]
  sht_init_ops.set_operand(0, (send_buffer_offset << 32) | SPLIT_V_SHT_OFFSET);
  // X9  - NUM_ALLOC_LANES(0:31) | START_NWID(32:63);
  sht_init_ops.set_operand(1, (sht_start_nwid << 32) | num_sht_lanes);
  // X10 - LANE_DESC_LM_OFFSET(0:31) | BUCKETS_PER_LANE(32:63);
  sht_init_ops.set_operand(2, (sht_ext_alloc.num_buckets_per_lane << 32) | sht_ext_alloc.lane_desc_lm_offset);
  // X11 - ENTRIES_PER_BUCKET(0:31) | VAL_NUM_WORDS(32:63);
  sht_init_ops.set_operand(3, (sht_ext_alloc.val_num_words << 32) | sht_ext_alloc.num_entries_per_bucket);
  // X12 - DRAM_ALLOC_ADDR;
  sht_init_ops.set_operand(4, reinterpret_cast<UpDown::word_t>(sht_ext_alloc.dram_alloc_addr));
  // X13 - NUM_KVMSR_LANES;
  sht_init_ops.set_operand(5, num_kvmsr_lanes);

  UpDown::event_t sht_init_evnt_ops(split_vertex_exe::SHT_init /*Event Label*/, nwid, UpDown::CREATE_THREAD /*Thread ID*/, &sht_init_ops /*Operands*/);

  // Init top flag to 0
  flag = 0;
  split_v_rt->t2ud_memcpy(&flag, sizeof(uint64_t), nwid, TOP_FLAG_OFFSET /*Offset*/);

  split_v_rt->send_event(sht_init_evnt_ops);

#ifdef GEM5_MODE
  m5_reset_stats(0, 0);
#endif

  split_v_rt->start_exec(nwid);

  split_v_rt->test_wait_addr(nwid, TOP_FLAG_OFFSET, 1);
  
#ifdef GEM5_MODE
  m5_dump_reset_stats(0,0);
#endif

  printf("Split vertices SHT initialisation terminates.\n");
  fflush(stdout);

  UpDown::word_t kvmsr_read_sht_ops_data[7];
  UpDown::operands_t split_vertex_ops(7, kvmsr_read_sht_ops_data);

  /* operands
    OB_0: Pointer to the partition array (64-bit DRAM address)
    OB_1: Number of partitions per lane
    OB_2: Number of lanes
    OB_3: Max original vertex id
    OB_4: Max split degree
  */
  split_vertex_ops.set_operand(0, (uint64_t)partitions);
  split_vertex_ops.set_operand(1, (uint64_t)num_buckets_per_lane);
  split_vertex_ops.set_operand(2, (uint64_t)num_kvmsr_lanes);
  split_vertex_ops.set_operand(3, (uint64_t)num_vertices + 1);
  split_vertex_ops.set_operand(4, (uint64_t)max_split_degree);

  printf("Prepare split vertex program operands done.\n");

  UpDown::event_t kvmsr_init_read_sht_evnt_ops(split_vertex_exe::split_vertex__entry_event /*Event Label*/, nwid, UpDown::CREATE_THREAD /*Thread ID*/,
                                               &split_vertex_ops /*Operands*/);

  // Init top flag to 0
  flag = 0;
  split_v_rt->t2ud_memcpy(&flag, sizeof(uint64_t), nwid, TOP_FLAG_OFFSET /*Offset*/);

  printf("Clear top flag.\n");
  split_v_rt->send_event(kvmsr_init_read_sht_evnt_ops);

#ifdef GEM5_MODE
  m5_reset_stats(0, 0);
#endif

  split_v_rt->start_exec(nwid);

  split_v_rt->test_wait_addr(nwid, TOP_FLAG_OFFSET, 1);

#ifdef GEM5_MODE
  m5_dump_reset_stats(0,0);
#endif

  uint64_t num_split_vertices = 0;
  split_v_rt->ud2t_memcpy(&num_split_vertices, sizeof(uint64_t), nwid, SEND_BUFFER_OFFSET);

  printf("Split vertices program terminates, total number of original vertices "
         "= %ld, total number of split vertices = %ld.\n",
         num_vertices, num_split_vertices);
  fflush(stdout);

  // Allocate the vertex array.
  Vertex *vertex_array = reinterpret_cast<Vertex *>(split_v_rt->mm_malloc(num_split_vertices * sizeof(Vertex)));
  printf("-------------------\nSplit vertex store = %lu(%p), size = %ld.\n", (uint64_t)vertex_array, vertex_array, num_split_vertices);
  for (uint64_t i = 0; i < num_split_vertices; i++) {
    vertex_array[i].degree = 0;
  }

  fflush(stdout);

  UpDown::operands_t split_edge_ops(7);
  /* operands
    OB_0: Pointer to the partition array (64-bit DRAM address)
    OB_1: Number of partitions per lane
    OB_2: Number of lanes
    OB_3: Pointer to edge list (64-bit DRAM address)
    OB_4: Number of edges
    OB_5: split vertex list base address
    OB_6: split vertex list array size
  */
  split_edge_ops.set_operand(0, (uint64_t)partitions);
  split_edge_ops.set_operand(1, (uint64_t)2);
  split_edge_ops.set_operand(2, (uint64_t)num_kvmsr_lanes);
  split_edge_ops.set_operand(3, (uint64_t)edge_list);
  split_edge_ops.set_operand(4, (uint64_t)num_edges);
  split_edge_ops.set_operand(5, (uint64_t)vertex_array);
  split_edge_ops.set_operand(6, (uint64_t)num_split_vertices);

  printf("Prepare split edge program operands done.\n");

  UpDown::event_t split_edge(split_vertex_exe::edge_split__edge_split_entry_event /*Event Label*/, nwid, UpDown::CREATE_THREAD /*Thread ID*/,
                             &split_edge_ops /*Operands*/);

  // Init top flag to 0
  flag = 0;
  split_v_rt->t2ud_memcpy(&flag, sizeof(uint64_t), nwid, TOP_FLAG_OFFSET /*Offset*/);

  printf("Clear top flag.\n");
  split_v_rt->send_event(split_edge);

#ifdef GEM5_MODE
  m5_reset_stats(0, 0);
#endif

  split_v_rt->start_exec(nwid);

  split_v_rt->test_wait_addr(nwid, TOP_FLAG_OFFSET, 1);

#ifdef GEM5_MODE
  m5_dump_reset_stats(0,0);
#endif

  uint64_t num_split_edges = 0;
  split_v_rt->ud2t_memcpy(&num_split_edges, sizeof(uint64_t), nwid, SEND_BUFFER_OFFSET);

  printf("Split edge program terminates, split %ld edges.\n", num_split_edges);
  fflush(stdout);

#ifdef DEBUG
  printf("------------------- Finish splitting edge list -------------------\n");
  for (int i = 0; i < num_edges; i++) {
    printf("(%ld, %ld)\t", edge_list[i].src, edge_list[i].dst);
    if ((i + 1) % 16 == 0) {
      printf("\n");
    }
  }
#endif

#ifdef DEBUG_INTERMEDIATE_RESULT
  for (uint64_t i = 0; i < num_split_vertices; i++) {
    printf("Vertex %ld \tdegree = %ld \taddr=%lu(%p)\n", i, vertex_array[i].degree, (uint64_t)(vertex_array + i), (vertex_array + i));
  }
#endif

  // Allocate the neighbor lists.
  UpDown::operands_t alloc_neighbors_ops(7);
  /* operands
    OB_0: Pointer to the partition array (64-bit DRAM address)
    OB_1: Number of partitions per lane
    OB_2: Number of lanes
    OB_3: Pointer to edge list (64-bit DRAM address)
    OB_4: Number of edges
    OB_5: split vertex list base address
    OB_6: split vertex list array size
  */
  alloc_neighbors_ops.set_operand(0, (uint64_t)partitions);
  alloc_neighbors_ops.set_operand(1, (uint64_t)2);
  alloc_neighbors_ops.set_operand(2, (uint64_t)num_kvmsr_lanes);
  alloc_neighbors_ops.set_operand(3, (uint64_t)vertex_array);
  alloc_neighbors_ops.set_operand(4, (uint64_t)num_split_vertices);
  alloc_neighbors_ops.set_operand(5, (uint64_t)nlists_bin);
  alloc_neighbors_ops.set_operand(6, (uint64_t)nlist_bin_size);

  printf("Prepare allocate neighbor list program operands done.\n");

  UpDown::event_t alloc_neighbors(split_vertex_exe::alloc_neighbors__entry_event /*Event Label*/, nwid, UpDown::CREATE_THREAD /*Thread ID*/,
                                  &alloc_neighbors_ops /*Operands*/);

  // Init top flag to 0
  flag = 0;
  split_v_rt->t2ud_memcpy(&flag, sizeof(uint64_t), nwid, TOP_FLAG_OFFSET /*Offset*/);

  printf("Clear top flag.\n");
  split_v_rt->send_event(alloc_neighbors);

#ifdef GEM5_MODE
  m5_reset_stats(0, 0);
#endif

  split_v_rt->start_exec(nwid);

  split_v_rt->test_wait_addr(nwid, TOP_FLAG_OFFSET, 1);

#ifdef GEM5_MODE
  m5_dump_reset_stats(0,0);
#endif

  printf("Allocate neighbors program terminates.\n");
#ifdef DEBUG_OUTPUT
  printf("------------------- Finish building Vertex Array -------------------\n");
  uint64_t split_vids_base = 0;
  uint64_t split_vids_bound = 0;
  for (uint64_t i = 0; i < num_split_vertices; i++) {
    if (vertex_array[i].degree == 0)
      continue;
    split_vids_bound = vertex_array[i].split_range & (((uint64_t)1 << 32) - 1);
    printf("Vertex %ld \tdegree=%ld \tori_vid=%ld \tnlist=%lu(%p) \tsplit_vid_range=[%ld, %ld) \taddr=%lu(%p)\n", i, vertex_array[i].degree,
           vertex_array[i].orig_vid, (uint64_t)vertex_array[i].neighbors, vertex_array[i].neighbors, vertex_array[i].split_range >> 32, split_vids_bound,
           (uint64_t)(vertex_array + i), (vertex_array + i));
  }
#endif

  fflush(stdout);

  Count *nlist_offsets = reinterpret_cast<Count *>(split_v_rt->mm_malloc(num_split_vertices * sizeof(Count)));
  memset(nlist_offsets, 0, num_split_vertices * sizeof(Count));

  // Allocate the neighbor lists.
  UpDown::operands_t build_nlists_ops(8);
  /* operands
    OB_0: Pointer to the partition array (64-bit DRAM address)
    OB_1: Number of partitions per lane
    OB_2: Number of lanes
    OB_3: Pointer to edge list (64-bit DRAM address)
    OB_4: Number of edges
    OB_5: split vertex list base address
    OB_6: split vertex list array size
  */
  build_nlists_ops.set_operand(0, (uint64_t)partitions);
  build_nlists_ops.set_operand(1, (uint64_t)num_kvmsr_lanes);
  build_nlists_ops.set_operand(2, (uint64_t)edge_list);
  build_nlists_ops.set_operand(3, (uint64_t)num_edges);
  build_nlists_ops.set_operand(4, (uint64_t)nlist_offsets);
  build_nlists_ops.set_operand(5, (uint64_t)vertex_array);
  build_nlists_ops.set_operand(6, (uint64_t)num_split_vertices);
  build_nlists_ops.set_operand(7, (uint64_t)sht_start_nwid << 32 | num_sht_lanes);

  printf("Prepare build neighbor list operands done.\n");

  UpDown::event_t build_nlists(split_vertex_exe::build_neighbor_list__build_nlist_entry_event /*Event Label*/, nwid, UpDown::CREATE_THREAD /*Thread ID*/,
                               &build_nlists_ops /*Operands*/);

  // Init top flag to 0
  flag = 0;
  split_v_rt->t2ud_memcpy(&flag, sizeof(uint64_t), nwid, TOP_FLAG_OFFSET /*Offset*/);

  printf("Clear top flag.\n");
  split_v_rt->send_event(build_nlists);

#ifdef GEM5_MODE
  m5_reset_stats(0, 0);
#endif

  split_v_rt->start_exec(nwid);

  split_v_rt->test_wait_addr(nwid, TOP_FLAG_OFFSET, 1);

#ifdef GEM5_MODE
  m5_dump_reset_stats(0,0);
#endif

  printf("Allocate neighbors program terminates.\n");
#ifdef DEBUG_OUTPUT
  printf("------------------- Vertex Array -------------------\n");
  for (uint64_t i = 0; i < num_split_vertices; i++) {
    if (vertex_array[i].degree == 0)
      continue;
    printf("Vertex %ld \tdegree = %ld \tnlist=%lu(%p) \taddr=%lu(%p)\n", i, vertex_array[i].degree, (uint64_t)vertex_array[i].neighbors,
           vertex_array[i].neighbors, (uint64_t)(vertex_array + i), (vertex_array + i));
  }
#endif

#ifdef DUMP_OUTPUT
  std::string output_file = "./graph/split_scale_" + std::to_string(scale) + "_max_split_degree_" + std::to_string(max_split_degree) + ".bin";
  FILE *output = fopen(output_file.c_str(), "wb");
  if (!output) {
    printf("Error when openning file, exiting.\n");
    exit(EXIT_FAILURE);
  }
  fseek(output, 0, SEEK_SET);
  fwrite(&num_vertices, sizeof(uint64_t), 1, output);
  fwrite(&num_split_vertices, sizeof(uint64_t), 1, output);
  fwrite(&num_edges, sizeof(uint64_t), 1, output);
  Vertex temp_vertex;
  uint64_t max_degree = 0;
  uint64_t avg_degree = 0;
  for (int i = 0; i < num_split_vertices; i++) {
    temp_vertex = vertex_array[i];
    temp_vertex.vid = i;

    fwrite(&temp_vertex, sizeof(Vertex), 1, output);
#ifdef DEBUG
    printf("Vertex %d \tdegree = %ld \t ori_vid = %ld \tnlist=%lu(%p) \taddr=%lu(%p)\n", i, vertex_array[i].degree, vertex_array[i].orig_vid,
           (uint64_t)vertex_array[i].neighbors, vertex_array[i].neighbors, (uint64_t)(vertex_array + i), (vertex_array + i));
#endif

    if (temp_vertex.degree == 0) {
      continue;
    }

    uint64_t *neighbors = (temp_vertex.neighbors);
    fwrite(neighbors, sizeof(uint64_t), temp_vertex.degree, output);
#ifdef DEBUG
    printf("\tEdges: [");
    for (int j = 0; j < temp_vertex.degree; j++) {
      printf("(%ld, %ld)\t", temp_vertex.vid, neighbors[j]);
    }
    printf("]\n");
    
    printf("\tEdges in ori_vid: [");
    for (int j = 0; j < temp_vertex.degree; j++) {
      printf("(%ld, %ld)\t", temp_vertex.orig_vid, vertex_array[neighbors[j]].orig_vid);
    }
    printf("]\n");

#endif

    max_degree = std::max(max_degree, temp_vertex.degree);
    avg_degree += temp_vertex.degree;
  }

  printf("Graph after split:\n\tMax degree = %ld\n\ttotal_degree =%ld\n\tavg degree = %f\n", max_degree, avg_degree, avg_degree / (num_split_vertices + 1.0));
#endif

  fflush(stdout);
  delete split_v_rt;
  printf("Vertex splitting program finishes.\n");

  return 0;
}
