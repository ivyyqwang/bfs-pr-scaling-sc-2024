#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <cstdint>


// #define DEBUG
#define USAGE "USAGE: ./preprocess_bfs_edges <graph_file> <scale>"

/**
 * Simple graph edge structure
*/
struct Edge{
  uint64_t src;
  uint64_t dst;
};

int main(int argc, char* argv[]) {

  char* filename;
  uint64_t scale = 0;
  if(argc < 3){
        printf("Insufficient Input Params\n");
        printf("%s\n", USAGE);
        exit(1);
  }else{
        filename = argv[1];
        scale = atoi(argv[2]);
  }

  printf("Reading the graph %s\n", filename);
  std::ifstream input( filename );

  std::vector<Edge> edge_list;
  Edge element;
  uint64_t max_vid = std::pow(2, scale);
  std::string tok;
  char* token;
  std::size_t n;

  for (std::string line; std::getline(input, line);)
  {
    token = std::strtok(const_cast<char*>(line.c_str()), " ");
    element.src = std::stoul(token);
    token = std::strtok(NULL, " ");
    element.dst = std::stoul(token);
    edge_list.push_back(element);
    // max_vid = std::max(max_vid, std::max(element.src, element.dst));
  }

  uint64_t num_edges = edge_list.size();

  printf("Graph:\n\tmax_vertex_id = %ld\n\tnum_edges = %ld\n", max_vid, num_edges);

  printf("Writing to binary.\n");
  
  std::string binfile = std::string(filename) + "_edges.bin";
  char* binfilename = const_cast<char*>(binfile.c_str()); 
  
  printf("Binfile:%s\n", binfilename);
  FILE* out_file = fopen(binfilename, "wb");
  if (!out_file) {
        exit(EXIT_FAILURE);
  }
    
  fseek(out_file, 0, SEEK_SET);
  fwrite(&scale, sizeof(uint64_t), 1, out_file);
  printf("Writing scale = %ld of size uint64_t (%ld)\n", scale, sizeof(uint64_t));
  fwrite(&num_edges, sizeof(uint64_t), 1, out_file);
  printf("Writing num_edges = %ld of size Edge (%ld)\n", num_edges, sizeof(uint64_t));
  for(int i = 0; i < num_edges; i++){
    fwrite(&edge_list[i], sizeof(Edge), 1, out_file);
#ifdef DEBUG
    if (i%5 == 0) printf("\nLine: ");
    printf("(%ld, \t%ld)\t", edge_list[i].src, edge_list[i].dst);
#endif
  }
  fclose(out_file);

  // Try to read file back
  #ifdef DEBUG
  printf("\n-------------------\n");
  binfilename = const_cast<char*>(binfilename); 
  printf("Binfile:%s\n", binfilename);
  out_file = fopen(binfilename, "rb");

  uint64_t num_rd_edges, vid;
  fseek(out_file, 0, SEEK_SET);
  n = fread(&num_rd_edges, sizeof(num_rd_edges), 1, out_file);
  Edge* edges_rd = reinterpret_cast<Edge *>(malloc(num_rd_edges * sizeof(Edge)));
  n = fread(edges_rd, sizeof(Edge), num_edges, out_file); // read in all vertices
  fclose(out_file);

  printf("Number of edges write = %ld\nNumber of edges read back = %ld\n", num_edges, num_rd_edges);
  
  for(int i=0; i< num_rd_edges;i++){
    if (i%5 == 0) printf("\nLine: ");
    printf("(%ld, \t%ld)\t", edges_rd[i].src, edges_rd[i].dst);
  }
  printf("\n");
  #endif

}


