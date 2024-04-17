#ifndef __dram_forward_bfs_exe_H__
#define __dram_forward_bfs_exe_H__

namespace dram_forward_bfs_exe {

    typedef unsigned int EventSymbol;

    constexpr EventSymbol BFS__init_node = 0;
    constexpr EventSymbol BFS__init_updown = 1;
    constexpr EventSymbol BFS__init_frontier = 2;
    constexpr EventSymbol BFS__fin_init_ud = 3;
    constexpr EventSymbol BFS__init_global_sync = 4;
    constexpr EventSymbol BFS__global_sync = 5;
    constexpr EventSymbol BFS__init_node_sync = 6;
    constexpr EventSymbol BFS__node_sync = 7;
    constexpr EventSymbol sync_bfs__ud_entry = 8;
    constexpr EventSymbol BFS__ud_accumulate = 9;
    constexpr EventSymbol sync_bfs__ud_delay = 10;
    constexpr EventSymbol BFS__insert_to_frontier = 11;
    constexpr EventSymbol BFS__fetch_frontier = 12;
    constexpr EventSymbol BFS__frontier_fetch_return = 13;
    constexpr EventSymbol BFS__frontier_update_sync = 14;
    constexpr EventSymbol BFS__broadcast_frontier_fetch = 15;
    constexpr EventSymbol BFS__finish_fetch_return = 16;
    constexpr EventSymbol BFS__update_sibling = 17;
    constexpr EventSymbol BFS__update_original_vertex = 18;
    constexpr EventSymbol BFS__update_distance = 19;
    constexpr EventSymbol BFS__read_vertex = 20;
    constexpr EventSymbol BFS__store_ack = 21;
    constexpr EventSymbol BFS__receive_update = 22;
    constexpr EventSymbol BFS__fetch_vertex = 23;
    constexpr EventSymbol BFS__fetch_neighbors = 24;

} // namespace

#endif