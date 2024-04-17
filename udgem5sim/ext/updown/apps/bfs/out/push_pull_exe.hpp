#ifndef __push_pull_exe_H__
#define __push_pull_exe_H__

namespace push_pull_exe {

    typedef unsigned int EventSymbol;

    constexpr EventSymbol Broadcast__broadcast_global = 0;
    constexpr EventSymbol Broadcast__broadcast_node = 1;
    constexpr EventSymbol Broadcast__broadcast_ud = 2;
    constexpr EventSymbol Broadcast__broadcast_ud_fin = 3;
    constexpr EventSymbol Broadcast__broadcast_node_fin = 4;
    constexpr EventSymbol Broadcast__broadcast_global_fin = 5;
    constexpr EventSymbol Broadcast__broadcast_value_to_scratchpad = 6;
    constexpr EventSymbol BFS_pull__map_shuffle_reduce = 7;
    constexpr EventSymbol BFS_pull__finish_init_udkvmsr = 8;
    constexpr EventSymbol BFS_input_kvset__generate_partition_array = 9;
    constexpr EventSymbol BFS_input_kvset__write_partition_array_return = 10;
    constexpr EventSymbol BFS_pull__broadcast_global = 11;
    constexpr EventSymbol BFS_pull__broadcast_node = 12;
    constexpr EventSymbol BFS_pull__broadcast_ud = 13;
    constexpr EventSymbol BFS_pull__broadcast_ud_fin = 14;
    constexpr EventSymbol BFS_pull__broadcast_node_fin = 15;
    constexpr EventSymbol BFS_pull__broadcast_global_fin = 16;
    constexpr EventSymbol BFS_pull__broadcast_value_to_scratchpad = 17;
    constexpr EventSymbol BFS_pull__init_input_kvset_on_lane = 18;
    constexpr EventSymbol BFS_pull__init_sp_lane = 19;
    constexpr EventSymbol BFS_pull__init_global_master = 20;
    constexpr EventSymbol BFS_pull__global_master = 21;
    constexpr EventSymbol BFS_pull__init_master_node = 22;
    constexpr EventSymbol BFS_pull__node_master = 23;
    constexpr EventSymbol BFS_pull__termiante_node_master = 24;
    constexpr EventSymbol BFS_pull__init_updown_master = 25;
    constexpr EventSymbol BFS_pull__updown_master = 26;
    constexpr EventSymbol BFS_pull__terminate_updown_master = 27;
    constexpr EventSymbol BFS_pull__lane_master_init = 28;
    constexpr EventSymbol BFS_pull__lane_master_loop = 29;
    constexpr EventSymbol BFS_pull__lane_master_read_partition = 30;
    constexpr EventSymbol BFS_pull__lane_master_get_next_return = 31;
    constexpr EventSymbol BFS_pull__lane_master_terminate = 32;
    constexpr EventSymbol BFS_pull__init_global_snyc = 33;
    constexpr EventSymbol BFS_pull__init_node_sync = 34;
    constexpr EventSymbol BFS_pull__ud_accumulate = 35;
    constexpr EventSymbol BFS_pull__global_sync_return = 36;
    constexpr EventSymbol BFS_pull__node_sync_return = 37;
    constexpr EventSymbol BFS_pull__kv_map_return = 38;
    constexpr EventSymbol BFS__init_node = 39;
    constexpr EventSymbol BFS__init_updown = 40;
    constexpr EventSymbol BFS__init_frontier_scratchpad = 41;
    constexpr EventSymbol BFS__init_lane = 42;
    constexpr EventSymbol BFS__init_updown_return = 43;
    constexpr EventSymbol BFS__fin_init_node = 44;
    constexpr EventSymbol BFS__init_global_sync = 45;
    constexpr EventSymbol BFS__global_sync = 46;
    constexpr EventSymbol BFS__init_node_sync = 47;
    constexpr EventSymbol BFS__node_sync = 48;
    constexpr EventSymbol push_pull_bfs__ud_entry = 49;
    constexpr EventSymbol BFS__ud_accumulate = 50;
    constexpr EventSymbol push_pull_bfs__ud_delay = 51;
    constexpr EventSymbol BFS__init_frontier = 52;
    constexpr EventSymbol BFS__allocate_frontier = 53;
    constexpr EventSymbol BFS__switch_ud_frontier = 54;
    constexpr EventSymbol BFS__init_updown_master = 55;
    constexpr EventSymbol BFS__updown_master_sync = 56;
    constexpr EventSymbol BFS__terminate_updown_master = 57;
    constexpr EventSymbol BFS__init_lane_master = 58;
    constexpr EventSymbol BFS__frontier_fetch_loop = 59;
    constexpr EventSymbol BFS__initialize_iteration = 60;
    constexpr EventSymbol BFS__broadcast_frontier_fetch = 61;
    constexpr EventSymbol BFS__finish_fetch_return = 62;
    constexpr EventSymbol BFS__switch_frontiers = 63;
    constexpr EventSymbol BFS__terminate_sync = 64;
    constexpr EventSymbol BFS__update_distance = 65;
    constexpr EventSymbol BFS__read_vertex = 66;
    constexpr EventSymbol BFS__store_ack = 67;
    constexpr EventSymbol BFS__insert_frontier = 68;
    constexpr EventSymbol BFS__receive_update = 69;
    constexpr EventSymbol BFS__fetch_vertex = 70;
    constexpr EventSymbol BFS__fetch_neighbors = 71;
    constexpr EventSymbol BFS_pull__kv_map = 72;
    constexpr EventSymbol BFS_pull__rd_nlist_return = 73;
    constexpr EventSymbol BFS_pull__read_vertex = 74;
    constexpr EventSymbol BFS_pull__read_orig_vertex = 75;
    constexpr EventSymbol BFS_pull__update_siblings = 76;
    constexpr EventSymbol BFS_pull__write_dram_return = 77;

} // namespace

#endif