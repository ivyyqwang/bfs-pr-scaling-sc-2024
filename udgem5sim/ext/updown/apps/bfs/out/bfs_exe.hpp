#ifndef __bfs_exe_H__
#define __bfs_exe_H__

namespace bfs_exe {

    typedef unsigned int EventSymbol;

    constexpr EventSymbol BFS__init_node = 0;
    constexpr EventSymbol BFS__init_updown = 1;
    constexpr EventSymbol BFS__init_frontier_scratchpad = 2;
    constexpr EventSymbol BFS__init_lane = 3;
    constexpr EventSymbol BFS__init_updown_return = 4;
    constexpr EventSymbol BFS__fin_init_node = 5;
    constexpr EventSymbol BFS__init_global_sync = 6;
    constexpr EventSymbol BFS__global_sync = 7;
    constexpr EventSymbol BFS__init_node_sync = 8;
    constexpr EventSymbol BFS__node_sync = 9;
    constexpr EventSymbol sync_bfs__ud_entry = 10;
    constexpr EventSymbol BFS__ud_accumulate = 11;
    constexpr EventSymbol sync_bfs__ud_delay = 12;
    constexpr EventSymbol BFS__init_frontier = 13;
    constexpr EventSymbol BFS__insert_to_frontier = 14;
    constexpr EventSymbol BFS__finish_read_frontier = 15;
    constexpr EventSymbol BFS__insert_ack = 16;
    constexpr EventSymbol BFS__init_updown_master = 17;
    constexpr EventSymbol BFS__updown_master_sync = 18;
    constexpr EventSymbol BFS__terminate_updown_master = 19;
    constexpr EventSymbol BFS__init_lane_master = 20;
    constexpr EventSymbol BFS__frontier_fetch_loop = 21;
    constexpr EventSymbol BFS__broadcast_frontier = 22;
    constexpr EventSymbol BFS__broadcast_frontier_fetch = 23;
    constexpr EventSymbol BFS__finish_fetch_return = 24;
    constexpr EventSymbol BFS__terminate_frontier = 25;
    constexpr EventSymbol BFS__terminate_sync = 26;
    constexpr EventSymbol BFS__update_distance = 27;
    constexpr EventSymbol BFS__read_vertex = 28;
    constexpr EventSymbol BFS__store_ack = 29;
    constexpr EventSymbol BFS__receive_update = 30;
    constexpr EventSymbol BFS__fetch_vertex = 31;
    constexpr EventSymbol BFS__fetch_neighbors = 32;

} // namespace

#endif