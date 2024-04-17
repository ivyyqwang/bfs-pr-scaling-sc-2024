#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <list>

// #define DEBUG
#define VALIDATE_RESULT

#ifdef GEM5_MODE
 #include <gem5/m5ops.h>
#endif

#ifdef VALIDATE_RESULT
#include <fstream>
#include <iostream>
#include <ostream>
#endif

#define USAGE "USAGE: ./sync_bfs_ref <graph_file> <root_vid> (<output_file>)"

#define NUM_LANE_PER_UD 64
#define NUM_UD_PER_CLUSTER 4
#define NUM_CLUSTER_PER_NODE 8
#define LOG2_WORD_SIZE 3

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

void bfs_ref(Vertex *g_v, uint64_t num_vertices, uint64_t root_id) {
#ifdef GEM5_MODE
    m5_switch_cpu();
    m5_reset_stats(0,0);
#endif
  bool *visited = new bool[num_vertices];
  for (int i = 0; i < num_vertices; i++)
    visited[i] = false;

  std::list<uint64_t> frontier;
  frontier.push_back(root_id);
  visited[root_id] = true;
#ifdef DEBUG
  printf("Push root %ld to the frontier\n", root_id);
#endif

  g_v[root_id].distance = 0;

  while (!frontier.empty()) {
    uint64_t curr_vertex = frontier.front();
    frontier.pop_front();
#ifdef DEBUG
    // printf("Pop vertex %ld from the frontier\n", curr_vertex);
#endif

    uint64_t *neighbors = g_v[curr_vertex].neighbors;
    uint64_t degree = g_v[curr_vertex].degree;
    uint64_t distance = g_v[curr_vertex].distance + 1;

    for (int i = 0; i < degree; i++) {
      uint64_t temp = neighbors[i];
      if (!visited[temp]) {

#ifdef DEBUG
        printf("Neighbor %ld set to visited\n\tOld distance=%ld \tnew "
               "distance=%ld \tparent=%ld\n",
               temp, g_v[temp].dist, distance, curr_vertex);
#endif

        // Update the distance and parent pointer
        g_v[temp].distance = distance;
        g_v[temp].parent = curr_vertex;
        visited[temp] = true;
        frontier.push_back(temp);
      }
    }
  }
#ifdef GEM5_MODE
    m5_dump_reset_stats(0,0);
#endif
}

int main(int argc, char *argv[]) {

  char *graph_file;
  char *output_file;
  uint64_t root_vertex_id;
  if (argc < 3) {
    printf("Insufficient Input Params\n");
    printf("%s\n", USAGE);
    exit(1);
  }
  graph_file = argv[1];
  root_vertex_id = atoi(argv[2]);
#ifdef VALIDATE_RESULT
  if (argc < 4) {
    printf("Insufficient Input Params\n");
    printf("%s\n", USAGE);
    exit(1);
  }
  output_file = argv[3];
#endif

  FILE *in_file = fopen(graph_file, "rb");
  if (!in_file) {
    printf("Error when openning file, exiting.\n");
    exit(EXIT_FAILURE);
  }
  std::size_t n;
  uint64_t num_vertices, num_edges = 0;
  fseek(in_file, 0, SEEK_SET);
  n = fread(&num_vertices, sizeof(num_vertices), 1, in_file);
  n = fread(&num_edges, sizeof(num_edges), 1, in_file);
  num_edges *= 2;
  printf("Graph of Size :\n\tnum_vertices=%ld\n\tnum_edges=%ld\n", num_vertices,
         num_edges);

  Vertex *g_v_bin =
      reinterpret_cast<Vertex *>(malloc(num_vertices * sizeof(Vertex)));

  uint64_t *nlist_bin =
      reinterpret_cast<uint64_t *>(malloc(num_edges * sizeof(uint64_t)));

  printf("Build the graph now\n");

  uint64_t curr_base = 0;
  uint64_t deg, srcid, udid, offset, dstid;
  Vertex *temp_vertex;
  uint64_t *neighbors;

  for (int i = 0; i < num_vertices; i++) {
    neighbors = nlist_bin + curr_base;
    temp_vertex = g_v_bin + i;

    n = fread(temp_vertex, sizeof(Vertex), 1, in_file);
    n = fread(neighbors, sizeof(uint64_t), temp_vertex->degree, in_file);
    temp_vertex->vid = i;
    temp_vertex->neighbors = neighbors;

    // fread(&deg, sizeof(deg), 1, in_file);
    // fread(&srcid, sizeof(srcid), 1, in_file);
    // neighbors = nlist_bin + curr_base;
    // fread(neighbors, sizeof(uint64_t), deg, in_file);

    // g_v_bin[srcid].id = srcid;
    // g_v_bin[srcid].deg = deg;
    // g_v_bin[srcid].neighbors = neighbors;
    // g_v_bin[srcid].dist = 0xffffffffffffffff;
    // g_v_bin[srcid].parent = 0xffffffffffffffff;

#ifdef DEBUG
    printf("Vertex %ld (addr %p) on bin %ld - deg %ld, dist %ld, neighbor_list "
           "%p\nNeighbors: [",
           srcid, (g_v_bin + offset), udid, deg, g_v_bin[offset].dist,
           neighbors);
    printf("]\n");
#endif

    curr_base += temp_vertex->degree;
    // curr_base += deg;
  }

  printf("Vertices build done.\n");

  printf("Graph Built. Will do Async BFS now\n");
  printf("Graph: NumEdges:%ld\n", num_edges);
  printf("Graph: NumVertices:%ld\n", num_vertices);

  // Dumps a set of statistics per iteration of BFS
  printf("Run BFS.\n");
  bfs_ref(g_v_bin, num_vertices, root_vertex_id);

#ifdef VALIDATE_RESULT
  std::ofstream output(output_file);
  for (int i = 0; i < num_vertices; i++) {
    temp_vertex = g_v_bin + i;
    if (temp_vertex->distance >= 0 && (temp_vertex->distance != 0xffffffffffffffff)) {
#ifdef DEBUG
      printf("Vertex %ld - \tdeg %ld, \tdist %ld, \tparent %ld\n",
             temp_vertex.id, temp_vertex.deg, temp_vertex.dist,
             temp_vertex.parent);
#else
      output << "Vertex " << temp_vertex->vid << " - dist " << temp_vertex->distance
             << std::endl;
#endif
    }
  }

#endif

  printf("BFS done.\n");
}
