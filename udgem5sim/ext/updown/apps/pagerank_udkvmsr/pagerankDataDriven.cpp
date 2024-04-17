#include "PagerankMsrEFA.hpp"
#include "updown.h"
// #include "simupdown.h"

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <string>
#include <sys/types.h>

#ifdef BASIM
#include <basimupdown.h>
#endif

#ifdef GEM5_MODE
 #include <gem5/m5ops.h>
#endif

// #define VALIDATE_RESULT
// #define DEBUG
// #define DEBUG_GRAPH
// #define DEBUG_PROC

#define USAGE "USAGE: ./pagerankFastLoadMapShuffleReduce <graph_file_path> <num_nodes> <num_uds> <partition_per_lane> <num_iterations> (<output_file_path>)\n\
  graph_file_path: \tpath to the graph file.\n\
  num_nodes: \tnumber of nodes, minimum is 1.\n\
  num_uds: \tnumber of UDs per node, default = 32 if greater than 1 node is used.\n\
  partition_per_lane: \tnumber of partitions per lane.\n\
  num_iterations: \tnumber of iterations.\n"

#define NUM_LANE_PER_UD 64
#define NUM_UD_PER_CLUSTER 4
#define NUM_CLUSTER_PER_NODE 8
#define TOP_FLAG_OFFSET 0

#define ALPHA 0.85

// #define PART_PARM 1

struct Vertex{
  uint64_t id;
  uint64_t deg;
  uint64_t* neigh;
  double val;
  uint64_t is_active;
  uint64_t padding[3];
};

struct Value{
  // uint64_t id;
  double val;
};

struct Iterator {
  Vertex* begin;
  Vertex* end;
};

void pagerank_updown_iteration(UpDown::UDRuntime_t *pagerank_rt, Iterator *partitions, int PART_PARM, int num_lanes, Vertex *old_g_v_bin, Vertex *new_g_v_bin, int num_vertices, int iteration) {
  
#ifdef GEM5_MODE
  m5_switch_cpu();
  /* operands
    X8: Pointer to partitions (64-bit DRAM address)
    X9: Number of lanes
    X10: Number of partitions per lane
    X11: Pointer to inKVSet (64-bit DRAM address)
    X12: Input KVSet length
    X13: Pointer to outKVSet (64-bit DRAM address)
    X14: Output KVSet length
    X15: Top flag offset in the scratchpad (in Bytes)
  */
  UpDown::operands_t ops(7);
  ops.set_operand(0, (uint64_t) partitions);
  ops.set_operand(1, (uint64_t) PART_PARM);
  ops.set_operand(2, (uint64_t) num_lanes);
  ops.set_operand(3, (uint64_t) old_g_v_bin);
  ops.set_operand(4, (uint64_t) num_vertices);
  ops.set_operand(5, (uint64_t) new_g_v_bin);
  ops.set_operand(6, (uint64_t) num_vertices);

  UpDown::networkid_t nwid(0, false, 0);

  UpDown::event_t evnt_ops( PagerankMsrEFA::updown_init/*Event Label*/,
                            nwid,
                            UpDown::CREATE_THREAD /*Thread ID*/,
                            &ops /*Operands*/);

  // Init top flag to 0
  uint64_t val = 0;
  pagerank_rt->t2ud_memcpy(&val,
                  sizeof(uint64_t),
                  nwid,
                  TOP_FLAG_OFFSET /*Offset*/);

  pagerank_rt->send_event(evnt_ops);

#ifdef DEBUG
  printf("Event sent to updown lane %d.\n", 0);
#endif

  m5_reset_stats(0,0);
  pagerank_rt->start_exec(nwid);
  printf("Top init the UpDown program, waiting for itertaion %d terminate\n", iteration);
  fflush(stdout);

  pagerank_rt->test_wait_addr(nwid, TOP_FLAG_OFFSET, 1);

  m5_dump_reset_stats(0,0);

  printf("UpDown PageRank iteration %d terminates.\n", iteration);

#else

  /* operands
    X8: Pointer to partitions (64-bit DRAM address)
    X9: Number of lanes
    X10: Number of partitions per lane
    X11: Pointer to inKVSet (64-bit DRAM address)
    X12: Input KVSet length
    X13: Pointer to outKVSet (64-bit DRAM address)
    X14: Output KVSet length
    X15: Top flag offset in the scratchpad (in Bytes)
  */
  UpDown::operands_t ops(7);
  ops.set_operand(0, (uint64_t) partitions);
  ops.set_operand(1, (uint64_t) PART_PARM);
  ops.set_operand(2, (uint64_t) num_lanes);
  ops.set_operand(3, (uint64_t) g_v_bin);
  ops.set_operand(4, (uint64_t) num_vertices);
  ops.set_operand(5, (uint64_t) g_v_val);
  ops.set_operand(6, (uint64_t) num_vertices);

  UpDown::networkid_t nwid(0, false, 0);

  UpDown::event_t evnt_ops( PagerankMsrEFA::updown_init/*Event Label*/,
                            nwid,
                            UpDown::CREATE_THREAD /*Thread ID*/,
                            &ops /*Operands*/);

  // Init top flag to 0
  uint64_t val = 0;
  pagerank_rt->ud2t_memcpy(&val,
                  sizeof(uint64_t),
                  nwid,
                  TOP_FLAG_OFFSET /*Offset*/);

  pagerank_rt->send_event(evnt_ops);

  pagerank_rt->start_exec(nwid);
  printf("Waiting for itertaion %d terminate\n", iteration);
  fflush(stdout);

  pagerank_rt->test_wait_addr(nwid, TOP_FLAG_OFFSET, 1);

  printf("UpDown PageRank iteration %d terminates.\n", iteration);

#endif
}

int main(int argc, char* argv[]) {

  if (argc < 6) {
    printf("Insufficient Input Params\n");
    printf("%s\n", USAGE);
    exit(1);
  }
  
  std::string filename (argv[1]);
  uint64_t num_nodes = atoi(argv[2]);
  uint64_t num_uds_per_node = NUM_UD_PER_CLUSTER * NUM_CLUSTER_PER_NODE;
  uint64_t num_lanes_per_ud = NUM_LANE_PER_UD;
  int PART_PARM = atoi(argv[4]);
  int num_iterations = atoi(argv[5]);

  if (num_nodes < 2) {
    num_nodes = 1;
    num_uds_per_node = atoi(argv[3]);
  } 

  printf("Test configurations: \n\tnum_nodes = %ld, \n\tnum_uds_per_node = %ld, \n\tnum_lanes_per_ud = %ld, ", num_nodes, num_uds_per_node, num_lanes_per_ud);

  uint64_t num_lanes = num_nodes * num_uds_per_node * num_lanes_per_ud;

  printf("\n\ttotal_num_lanes = %ld\n", num_lanes);

  // Set up machine parameters
  UpDown::ud_machine_t machine;
  machine.NumLanes = num_lanes_per_ud;
  machine.NumUDs = std::min((int)num_uds_per_node, NUM_UD_PER_CLUSTER);
  machine.NumStacks = std::ceil((double)num_uds_per_node / NUM_UD_PER_CLUSTER);
  machine.NumNodes = num_nodes;
  machine.LocalMemAddrMode = 1;

#ifdef GEM5_MODE
  UpDown::UDRuntime_t *pagerank_rt = new UpDown::UDRuntime_t(machine);
#elif BASIM
  UpDown::BASimUDRuntime_t* pagerank_rt = new UpDown::BASimUDRuntime_t(machine, "PagerankMsrEFA.bin", 0, 1);
#else
  // Init runtime
  UpDown::SimUDRuntime_t *pagerank_rt = new UpDown::SimUDRuntime_t(machine,
  "GenMSRPagerankEFA", 
  "GeneratePageRankMapShuffleReduceEFA", 
  "./", 
  UpDown::EmulatorLogLevel::NONE);
#endif

#ifdef DEBUG
  printf("=== Base Addresses ===\n");
  pagerank_rt->dumpBaseAddrs();
  printf("\n=== Machine Config ===\n");
  pagerank_rt->dumpMachineConfig();
#endif

  
  FILE* in_file_gv = fopen((filename + "_gv.bin").c_str(), "rb");
  if (!in_file_gv) {
    printf("Error when openning file %s, exiting.\n", (filename + "_gv.bin").c_str());
    exit(EXIT_FAILURE);
  }

  FILE* in_file_nl = fopen((filename + "_nl.bin").c_str(), "rb");
  if (!in_file_nl) {
    printf("Error when openning file %s, exiting.\n", (filename + "_nl.bin").c_str());
    exit(EXIT_FAILURE);
  }

  uint64_t num_vertices, num_edges;
  std::size_t n;

  fseek(in_file_gv, 0, SEEK_SET);
  n = fread(&num_vertices, sizeof(num_vertices), 1, in_file_gv);
  n = fread(&num_edges, sizeof(num_edges), 1, in_file_nl);
  printf("Input graph: Number of Vertices = %ld\t Number of edges = %ld\n", num_vertices, num_edges);
  fflush(stdout);

  // Allocate the array where the top and updown can see it:
  Vertex* old_g_v_bin = reinterpret_cast<Vertex *>(pagerank_rt->mm_malloc(num_vertices * sizeof(Vertex)));
  Vertex* new_g_v_bin  = reinterpret_cast<Vertex *>(pagerank_rt->mm_malloc(num_vertices * sizeof(Vertex)));

  uint64_t* nlist_bin = reinterpret_cast<uint64_t *>(pagerank_rt->mm_malloc(num_edges * sizeof(uint64_t)));

  n = fread(old_g_v_bin, sizeof(Vertex), num_vertices, in_file_gv); // read in all vertices 
  n = fread(nlist_bin, sizeof(uint64_t), num_edges, in_file_nl); // read in all vertices
  
  // UpDown::word_t INPUT_KVMAP_SIZE = 1 << 14;
  uint64_t num_partitions = num_lanes * PART_PARM;
  uint64_t num_pairs_per_part = ceil((num_vertices + 0.0) / num_partitions);
  printf("Number of partitions per lane = %d\t Number of partitions = %ld\t Number of vertices per partition = %ld\n", PART_PARM, num_partitions, num_pairs_per_part);

  Iterator *partitions = reinterpret_cast<Iterator *>(
        pagerank_rt->mm_malloc_global((num_partitions) * sizeof(Iterator)));


#ifdef DEBUG
  printf("Vertax array = %p\n", g_v_bin);
  printf("Value array = %p\n", g_v_val);
  printf("Edge array = %p\n", nlist_bin);
#endif

  // calculate size of neighbour list and assign values to each member value
  printf("Build the graph now\n");
  fflush(stdout);

  uint64_t curr_base = 0;
  double init_pr_value = (1.0 - ALPHA) / num_vertices;
  for(int i = 0; i < num_vertices; i++) {
    old_g_v_bin[i].val = init_pr_value;
    old_g_v_bin[i].is_active = 1;
    old_g_v_bin[i].neigh = (uint64_t *) ((uint64_t) nlist_bin + curr_base * sizeof(uint64_t));

    new_g_v_bin[i].id = i;
    new_g_v_bin[i].deg = old_g_v_bin[i].deg;
    new_g_v_bin[i].val = 0.0;
    new_g_v_bin[i].is_active = 1;
    new_g_v_bin[i].neigh = (uint64_t *) ((uint64_t) nlist_bin + curr_base * sizeof(uint64_t));

#ifdef DEBUG_GRAPH
    printf("Vertex %d (addr %p) - deg %ld, neigh_list %p\n", i, (g_v_bin + i), g_v_bin[i].deg, (nlist_bin + curr_base));
#endif
    curr_base += old_g_v_bin[i].deg;
  }

#ifdef DEBUG_GRAPH
  printf("-------------------\nparitions = %p\n", partitions);
#endif
  
  // Initialize partitions
  int offset = 0;
  for (int i = 0; i < num_partitions; i++) {
    partitions[i].begin = old_g_v_bin + offset;
    offset = std::min((i+1) * num_pairs_per_part, num_vertices);
    partitions[i].end = new_g_v_bin + offset;
#ifdef DEBUG_GRAPH
    printf("Partition %d: pair_id=%d, key=%ld neighbors=%p "
            "base_pair_addr=%p, part_entry_addr=%p\n",
            i, offset, partitions[i].begin->id, partitions[i].begin->neigh, partitions[i],
            partitions + i);
#endif
  }


#ifdef DEBUG_GRAPH
  printf("Partition %ld: pair_id=%ld base_pair_addr=%p, part_entry_addr=%p\n",
      num_partitions, std::min(num_partitions * num_pairs_per_part, num_vertices), partitions[num_partitions], partitions + num_partitions);
#endif
  printf("Finish building the graph, start running PageRank.\n");
  fflush(stdout);

  for (int i = 0; i < num_iterations; i++) {
    printf("Start iteration %d\n", i);
    pagerank_updown_iteration(pagerank_rt, partitions, PART_PARM, num_lanes, old_g_v_bin, new_g_v_bin, num_vertices, i);
  }


#ifdef VALIDATE_RESULT
  const char* output_file;
  if (argc >= 7) {
    output_file = argv[6];
    std::ofstream output(output_file);
#ifdef DEBUG
    printf("-------------------\nUpDown program termiantes. Verify the result output kv set.\n");
#endif
    for (int i = 0; i < num_vertices; i++) {
#ifdef DEBUG
      printf("Output pagerank value array %d: key=%ld value=%f DRAM_addr=%p\n", i, g_v_val[i].id, g_v_val[i].val, g_v_val + i);
#endif
      output << i << " " << g_v_val[i].val << std::endl;
    }
  }
#endif


#ifdef FASTSIM
  for(int i = 0; i < num_uds_per_node; i = i + 1){
    for(int j = 0; j < num_lanes_per_ud; j = j + 1){
      pagerank_rt->print_stats(i, j);
    
#ifdef DETAIL_STATS
      bfs_rt->print_histograms(i, j);
#endif

    }
  }
#endif

  delete pagerank_rt;
  printf("UDKVMSR PageRank program finishes.\n");

  return 0;
}
