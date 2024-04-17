
#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <list>
#include <ostream>
#include <vector>

// #define DEBUG
// #define DEBUG_INPUT
#define VALIDATE_RESULT

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

struct Edge {
  uint64_t src;
  uint64_t dst;
};

void bfs_ref(Vertex *g_v, uint64_t num_vertices, uint64_t root_id) {
  bool *visited = new bool[num_vertices];
  for (int i = 0; i < num_vertices; i++)
    visited[i] = false;

  std::list<uint64_t> frontier;
  frontier.push_back(root_id);
  visited[root_id] = true;
  // #ifdef DEBUG
  printf("Push root %ld (degree=%ld) to the frontier\n", root_id, g_v[root_id].degree);
  // #endif
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
               temp, g_v[temp].distance, distance, curr_vertex);
#endif

        // Update the distance and parent pointer
        g_v[temp].distance = distance;
        g_v[temp].parent = curr_vertex;
        visited[temp] = true;
        frontier.push_back(temp);
      }
    }
  }
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
  
  bool validate_result = false;
#ifdef VALIDATE_RESULT
  if (argc == 4) {
    output_file = argv[3];
    validate_result = true;
  }
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
  printf("Graph configurations:\n\tnum_vertices=%ld\n\tnum_edges=%ld\n", num_vertices, num_edges);

  printf("Allocating memmory for edge list...\n");

  Edge *edge_list = reinterpret_cast<Edge *>(malloc(num_edges * sizeof(Edge)));
  n = fread(edge_list, sizeof(Edge), num_edges,
            edge_list_file); // read in all vertices
  fclose(edge_list_file);

#ifdef DEBUG
  printf("------------------- Input Edge list = %lu(%p) -------------------\n", (uint64_t)edge_list, edge_list);
  for (int i = 0; i < num_edges; i++) {
    printf("(%ld, %ld)\t", edge_list[i].src, edge_list[i].dst);
    if ((i + 1) % 16 == 0) {
      printf("\n");
    }
  }
#endif

  printf("Allocating memmory for vertex list...\n");
  Vertex *g_v_bin = reinterpret_cast<Vertex *>(malloc(num_vertices * sizeof(Vertex)));
  memset(g_v_bin, 0, num_vertices * sizeof(Vertex));
  printf("Allocated %ld * %ld = %ld bytes for vertex list\n", num_vertices, sizeof(Vertex), num_vertices * sizeof(Vertex));

  // Allocate memory for neighbour list
  printf("Allocating memmory for neighbour list...\n");
  std::vector<std::vector<uint64_t>> nlist_bins(num_vertices);
  printf("Allocated %ld * %ld = %ld bytes for neighbour list\n", num_vertices, sizeof(std::vector<uint64_t>), num_vertices * sizeof(std::vector<uint64_t>));
  // uint64_t *nlist_bins = reinterpret_cast<uint64_t *>(malloc(num_edges * sizeof(uint64_t)));

  // calculate size of neighbour list and assign values to each member value
  printf("Build the graph now\n");

  uint64_t src_vid, dst_vid;
  for (int i = 0; i < num_edges; i++) {
    src_vid = edge_list[i].src;
    nlist_bins[src_vid].push_back(edge_list[i].dst);
  }

  Vertex* temp_vertex;

  for (int i = 0; i < num_vertices; i++) {
    temp_vertex = g_v_bin + i;
    temp_vertex->vid = i;
    temp_vertex->neighbors = nlist_bins[i].data();
    temp_vertex->degree = nlist_bins[i].size();
    temp_vertex->distance = 0xffffffffffffffff;
    // std::sort(nlist_bins[i].begin(), nlist_bins[i].end());
#ifdef DEBUG_INPUT
    printf("Vertex %d (addr %p) - deg %ld, dist %ld, neighbors %p\n", 
           i, (g_v_bin + i), temp_vertex->degree, g_v_bin[i].distance, temp_vertex->neighbors);

    printf("\tEdges: [");
    for (int j = 0; j < temp_vertex->degree; j++) {
      printf("(%ld, %ld), ", temp_vertex->vid, temp_vertex->neighbors[j]);
    }
    printf("]\n");
#endif
  }

  printf("Vertices build done.\n");

  printf("Graph Built. Will do Async BFS now\n");
  printf("Graph: NumEdges:%ld\n", num_edges);
  printf("Graph: NumVertices:%ld\n", num_vertices);

  // Dumps a set of statistics per iteration of BFS
  printf("Run BFS.\n");
  bfs_ref(g_v_bin, num_vertices, root_vertex_id);

  uint64_t max_deg = 0;
#ifdef VALIDATE_RESULT
  if (validate_result) {
    printf("Validate result.\n");
    std::ofstream output(output_file);
    for (int i = 0; i < num_vertices; i++) {
      temp_vertex = g_v_bin + i;
      if (temp_vertex->distance >= 0 && (temp_vertex->distance != 0xffffffffffffffff)) {
  #ifdef DEBUG
        printf("Vertex %ld - deg %ld, dist %ld\n", temp_vertex->vid, temp_vertex->degree, temp_vertex->distance);
  #endif
        output << "Vertex " << temp_vertex->vid << " - dist " << temp_vertex->distance << std::endl;
        
        max_deg = std::max(max_deg, temp_vertex->degree);
      }
    }
  } 
#endif

  printf("BFS done.\n");
}
