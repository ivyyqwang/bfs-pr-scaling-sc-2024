#include "types.hh"
#include "udaccelerator.hh"
#include "udlane.hh"
#include <gtest/gtest.h>

using namespace basim;

#define MAX_VERTICES 128

uint32_t min_distance(uint8_t dist[MAX_VERTICES], bool *spt_set, uint32_t vertices) {
  uint8_t min = UINT8_MAX;
  uint32_t min_index;

  for (auto v = 0; v < vertices; v++) {
    if (spt_set[v] == false) {
      if (dist[v] <= min) {
        min = dist[v];
        min_index = v;
      }
    }
  }

  return min_index;
}

uint8_t *dijkstra(uint8_t graph[MAX_VERTICES * MAX_VERTICES], uint8_t src, uint32_t vertices) {
  static uint8_t dist[MAX_VERTICES];
  bool spt_set[MAX_VERTICES];
  for (auto i = 0; i < vertices; i++) {
    dist[i] = UINT8_MAX;
    spt_set[i] = false;
  }

  dist[src] = 0;
  for (auto count = 0; count < vertices - 1; count++) {
    uint32_t u = min_distance(dist, spt_set, vertices);
    spt_set[u] = true;

    for (auto v = 0; v < vertices; v++) {
      if (spt_set[v] == false) {
        if (graph[(u * vertices) + v] > 0) {
          if (dist[u] != UINT8_MAX) {
            if ((dist[u] + graph[(u * vertices) + v]) < dist[v]) {
              dist[v] = dist[u] + graph[(u * vertices) + v];
            }
          }
        }
      }
    }
  }

  return dist;
}

void random_edge_graph(uint8_t graph[MAX_VERTICES * MAX_VERTICES], int vertices) {
  srand((unsigned)time(NULL));
  std::cout << "----graph----" << std::endl;
  for (auto i = 0; i < vertices; i++) {
    graph[(i * vertices) + i] = 0;
    for (auto j = i + 1; j < vertices; j++) {
      uint8_t edge = (rand() % 30) + 1;
      if (edge > 20) {
        edge = -1;
      }

      std::cout << i << "<->" << j << ": " << (uint64_t)edge << std::endl;
      graph[(i * vertices) + j] = edge;
      graph[(j * vertices) + i] = edge;
    }
  }
}

class DIJKSTRA : public ::testing::Test {
protected:
  UDAccelerator acc0 = UDAccelerator(1, 0, 1);
  uint8_t graph[MAX_VERTICES * MAX_VERTICES];
  uint8_t soln[MAX_VERTICES];
  int graph_size = sizeof(uint8_t) * MAX_VERTICES * MAX_VERTICES;
  int soln_size = sizeof(uint8_t) * MAX_VERTICES;
};
TEST_F(DIJKSTRA, random_32) {
  int vertices = 32;
  random_edge_graph(graph, vertices);
  uint8_t *soln_ptr = dijkstra(graph, 0, vertices);
  std::cout << "----soln----" << std::endl;
  for (int i = 0; i < vertices; i++) {
    soln[i] = *soln_ptr++;
    std::cout << i << ": " << (uint64_t)soln[i] << std::endl;
  }

  acc0.initSetup(0, "testprogs/binaries/dijkstra.bin", 0);
  uint8_t numop = 4;
  eventword_t ev0(0);
  ev0.setNumOperands(numop);
  operands_t op0(numop);
  word_t op_data[] = {vertices, 0, UINT8_MAX, MAX_VERTICES};
  op0.setData(op_data);
  eventoperands_t eops(&ev0, &op0);
  acc0.pushEventOperands(eops, 0);

  for (int i = 0; i < graph_size; i++) {
    acc0.writeScratchPad(sizeof(uint8_t), (sizeof(uint8_t) * 8) + i, &graph[i]);
  }
  for (int i = 0; i < soln_size; i++) {
    acc0.writeScratchPad(sizeof(uint8_t), (sizeof(uint8_t) * 8) + graph_size + i, &soln[i]);
  }

  while (!acc0.isIdle())
    acc0.simulate(2);

  EXPECT_TRUE(acc0.testMem(0, 1));
}
TEST_F(DIJKSTRA, random_64) {
  int vertices = 32;
  random_edge_graph(graph, vertices);
  uint8_t *soln_ptr = dijkstra(graph, 0, vertices);
  std::cout << "----soln----" << std::endl;
  for (int i = 0; i < vertices; i++) {
    soln[i] = *soln_ptr++;
    std::cout << i << ": " << (uint64_t)soln[i] << std::endl;
  }

  acc0.initSetup(0, "testprogs/binaries/dijkstra.bin", 0);
  uint8_t numop = 4;
  eventword_t ev0(0);
  ev0.setNumOperands(numop);
  operands_t op0(numop);
  word_t op_data[] = {vertices, 0, UINT8_MAX, MAX_VERTICES};
  op0.setData(op_data);
  eventoperands_t eops(&ev0, &op0);
  acc0.pushEventOperands(eops, 0);

  for (int i = 0; i < graph_size; i++) {
    acc0.writeScratchPad(sizeof(uint8_t), (sizeof(uint8_t) * 8) + i, &graph[i]);
  }
  for (int i = 0; i < soln_size; i++) {
    acc0.writeScratchPad(sizeof(uint8_t), (sizeof(uint8_t) * 8) + graph_size + i, &soln[i]);
  }

  while (!acc0.isIdle())
    acc0.simulate(2);

  EXPECT_TRUE(acc0.testMem(0, 1));
}
TEST_F(DIJKSTRA, random_128) {
  int vertices = 128;
  random_edge_graph(graph, vertices);
  uint8_t *soln_ptr = dijkstra(graph, 0, vertices);
  std::cout << "----soln----" << std::endl;
  for (int i = 0; i < vertices; i++) {
    soln[i] = *soln_ptr++;
    std::cout << i << ": " << (uint64_t)soln[i] << std::endl;
  }

  acc0.initSetup(0, "testprogs/binaries/dijkstra.bin", 0);
  uint8_t numop = 4;
  eventword_t ev0(0);
  ev0.setNumOperands(numop);
  operands_t op0(numop);
  word_t op_data[] = {vertices, 0, UINT8_MAX, MAX_VERTICES};
  op0.setData(op_data);
  eventoperands_t eops(&ev0, &op0);
  acc0.pushEventOperands(eops, 0);

  for (int i = 0; i < graph_size; i++) {
    acc0.writeScratchPad(sizeof(uint8_t), (sizeof(uint8_t) * 8) + i, &graph[i]);
  }
  for (int i = 0; i < soln_size; i++) {
    acc0.writeScratchPad(sizeof(uint8_t), (sizeof(uint8_t) * 8) + graph_size + i, &soln[i]);
  }

  while (!acc0.isIdle())
    acc0.simulate(2);

  EXPECT_TRUE(acc0.testMem(0, 1));
}
