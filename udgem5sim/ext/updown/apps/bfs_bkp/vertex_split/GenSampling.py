from linker.EFAProgram import EFAProgram, efaProgram
from KVMSRMachineConfig import *
from Macro import *
from libraries.ScalableHashTable.linkable.sht_call_macros import SHT
from libraries.UDMapShuffleReduce.linkable.LinkableKVMapShuffleReduceTPL import UDKeyValueMapShuffleReduceTemplate
from libraries.UDMapShuffleReduce.utils.OneDimArrayKeyValueSet import OneDimKeyValueSet
from libraries.UDMapShuffleReduce.utils.IntermediateKeyValueSet import IntermediateKeyValueSet
from Config import *

class Sampling:
    
    def __init__(self, efa: EFAProgram):
        
        self.task   = 'sampling'
        self.efa    = efa
        self.efa.code_level = 'machine'
        self.state  = efa.State()
        efa.add_initId(self.state.state_id)

        self.sampling_sht_desc_offset   = HIGH_DEG_SHT_OFFSET
        
        self.debug_flag = DEBUG_FLAG
                
        self.__gen_ev_labels()
        self.__gen_udkvmsr()
        self.__gen_init()
        self.__gen_sampling_degree()
        self.__gen_find_high_deg_vertex()
        
    def __gen_udkvmsr(self):
            
        self.udkvmsr = UDKeyValueMapShuffleReduceTemplate(efa=self.efa, task_name=self.task, meta_data_offset=UDKVMSR_LM_OFFSET, debug_flag=self.debug_flag)
        
        self.udkvmsr.set_input_kvset(OneDimKeyValueSet(f"{self.task}_input_kvset", element_size=EDGE_STRUCT_SIZE))
        self.udkvmsr.set_intermediate_kvset(IntermediateKeyValueSet(f"{self.task}_intermediate_kvset", key_size=1, value_size=1))
        self.udkvmsr.set_output_kvset(OneDimKeyValueSet(f"{self.task}_output_kvset", element_size=VERTEX_COUNT_STRUCT_SIZE))
        
        self.udkvmsr.set_max_thread_per_lane(max_map_th_per_lane=MAX_SAMPLING_MAP_THREADS, max_reduce_th_per_lane=MAX_SAMPLING_REDUCE_THREADS)
        self.udkvmsr.setup_cache(cache_offset=KVMSR_CACHE_OFFSET, entry_size=KVMSR_CAHCE_ENTRY_SIZE, num_entries=KVMSR_CACHE_NUM_ENTRIES)
        
        self.udkvmsr.generate_udkvmsr_task()
        
    def __gen_ev_labels(self):
        
        self.sampling_entry_ev_label    = get_event_label(self.task, 'entry_event')
        self.broadcast_init_ev_label    = get_event_label(self.task, 'broadcast_initialization')
        self.bcst_sht_ret_ev_label      = get_event_label(self.task, 'broadcast_sht_return')
        self.sampling_term_ev_label     = get_event_label(self.task, 'terminate_event')
                
        self.kv_map_ev_label        = get_event_label(self.task, 'kv_map')
        
        self.lane_init_ev_label     = get_event_label(self.task, 'lane_init')
        self.fetch_loop_ev_label    = get_event_label(self.task, 'fetch_loop')
        self.put_split_vid_ev_label = get_event_label(self.task, 'put_split_vid_ack')
        
        # UDKVMSR interface events
        self.udkvmsr_entry_ev_label = get_event_label(self.task, 'map_shuffle_reduce')
        self.kv_map_emit_ev_label   = get_event_label(self.task, 'kv_map_emit')
        self.kv_map_return_ev_label = get_event_label(self.task, 'kv_map_return')
        self.kv_reduce_ev_label     = get_event_label(self.task, 'kv_reduce')
        self.kv_combine_ev_label    = get_event_label(self.task, 'kv_combine')
        self.kv_red_return_ev_label = get_event_label(self.task, 'kv_reduce_return')
    
    def __gen_init(self):
        
        send_buffer = 'X16'
        lm_addr     = 'X17'
        temp_evw    = 'X18'
        temp_reg    = 'X19'
        vertex_array_addr = 'X20'
        vertex_array_size = 'X21'
        stride      = 'X22'
        num_lanes   = 'X23'
        sampled_deg = 'X24'
        split_threshold = 'X25'
        
        '''
        Vertex split entry event.
        X8:     partition array address
        X9:     number of partitions per lane
        X10:    number of lanes
        X11:    edge list base address
        X12:    edge list array size
        X13:    vertex list base address
        X14:    vertex list array size
        X15:    max split degree
        '''
        entry_tran = self.state.writeTransition("eventCarry", self.state, self.state, self.sampling_entry_ev_label)
        if self.debug_flag:
            entry_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.sampling_entry_ev_label}] Event <sampling_entry> ev_word=%lu " + 
                                                f"partition=%lu(0x%lx) num_partitions_per_lane=%ld num_lanes=%ld' {'X0'} {'EQT'} {'X8'} {'X8'} {'X9'} {'X10'}")
            entry_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.sampling_entry_ev_label}] edge_list=%lu(0x%lx) edge_list_size=%ld" + 
                                                f" vertex_list=%lu(0x%lx) vertex_list_size=%ld max_split_degree=%ld' {'X0'} {'X11'} {'X11'} {'X12'} {'X13'} {'X13'} {'X14'} {'X15'}")
        # Initialize the UDKVMSR program.
        entry_tran.writeAction(f"addi {'X7'} {send_buffer} {KVMSR_SEND_BUFFER_OFFSET}")
        entry_tran.writeAction(f"movrl {'X8'} 0({send_buffer}) 0 8")
        entry_tran.writeAction(f"movrl {'X9'} 8({send_buffer}) 0 8")
        entry_tran.writeAction(f"movrl {'X10'} 16({send_buffer}) 0 8")
        entry_tran.writeAction(f"addi {'X7'} {lm_addr} {KVMSR_INPUT_OFFSET}")
        entry_tran.writeAction(f"movrl {lm_addr} 24({send_buffer}) 0 8")
        if self.debug_flag:
            entry_tran.writeAction(f"print '[DEBUG][NWID %d][{self.sampling_entry_ev_label}] Save input edge list base pointer %lu(0x%lx) and " + 
                                          f"size %ld to scratchpad addr %ld(0x%lx)' {'X0'} {'X11'} {'X11'} {'X12'} {lm_addr} {lm_addr}")
        entry_tran.writeAction(f"movrl {'X11'} 0({lm_addr}) 1 8")
        entry_tran.writeAction(f"divi {'X12'} {temp_reg} {SAMPLING_RATE}")
        entry_tran.writeAction(f"movrl {temp_reg} 0({lm_addr}) 1 8")
        entry_tran.writeAction(f"addi {'X7'} {lm_addr} {KVMSR_OUTPUT_OFFSET}")
        entry_tran.writeAction(f"movrl {lm_addr} 32({send_buffer}) 0 8")
        if self.debug_flag:
            entry_tran.writeAction(f"print '[DEBUG][NWID %d][{self.sampling_entry_ev_label}] Save output vertex count base pointer %lu(0x%lx) and " + 
                                          f"size %ld to scratchpad addr %ld(0x%lx)' {'X0'} {'X13'} {'X13'} {'X14'} {lm_addr} {lm_addr}")
        entry_tran.writeAction(f"movrl {'X13'} 0({lm_addr}) 1 8")
        entry_tran.writeAction(f"movrl {'X14'} 0({lm_addr}) 1 8")
        set_ev_label(entry_tran, temp_evw, self.udkvmsr_entry_ev_label, new_thread=True)
        entry_tran.writeAction(f"send_wret {temp_evw} {self.broadcast_init_ev_label} {send_buffer} {UDKVMSR_INIT_NUM_OPS} {temp_reg}")
        
        entry_tran.writeAction(f"addi {'X10'} {num_lanes} 0")
        entry_tran.writeAction(f"addi {'X13'} {vertex_array_addr} 0")
        entry_tran.writeAction(f"addi {'X14'} {vertex_array_size} 0")
        entry_tran.writeAction(f"addi {'X15'} {split_threshold} {0}")
        entry_tran.writeAction(f"yield")
        
        '''
        UDKVMSR program finishes, start the broadcast program.
        X8:     number of reduce tasks processed
        '''
        zero_reminder_label = "zero_reminder"
        init_bcst_tran = self.state.writeTransition("eventCarry", self.state, self.state, self.broadcast_init_ev_label)
        if self.debug_flag:
            init_bcst_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.broadcast_init_ev_label}] Event <broadcast_init> ev_word=%lu " + 
                                        f"num_reduce_tasks=%ld' {'X0'} {'EQT'} {'X8'}")
        init_bcst_tran.writeAction(f"addi {'X7'} {send_buffer} {SEND_BUFFER_OFFSET}")
        init_bcst_tran.writeAction(f"movrl {num_lanes} 0({send_buffer}) 0 8")
        init_bcst_tran.writeAction(f"addi {'X2'} {temp_evw} 0")
        init_bcst_tran.writeAction(f"evlb {temp_evw} {self.lane_init_ev_label}")
        init_bcst_tran.writeAction(f"movrl {temp_evw} {WORD_SIZE}({send_buffer}) 0 8")
        init_bcst_tran.writeAction(f"movrl {vertex_array_addr} {WORD_SIZE * 2}({send_buffer}) 0 8")
        init_bcst_tran.writeAction(f"movrl {vertex_array_size} {WORD_SIZE * 3}({send_buffer}) 0 8")
        init_bcst_tran.writeAction(f"div {vertex_array_size} {num_lanes} {stride}")
        init_bcst_tran.writeAction(f"mul {stride} {num_lanes} {temp_reg}")
        init_bcst_tran.writeAction(f"beq {temp_reg} {vertex_array_size} {zero_reminder_label}")
        init_bcst_tran.writeAction(f"addi {stride} {stride} 1")
        init_bcst_tran.writeAction(f"{zero_reminder_label}: movrl {stride} {WORD_SIZE * 4}({send_buffer}) 0 8")
        init_bcst_tran.writeAction(f"movrl {split_threshold} {WORD_SIZE * 5}({send_buffer}) 0 8")
        if self.debug_flag:
            init_bcst_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.broadcast_init_ev_label}] Operands: vertex_array_addr=%lu(0x%lx) " +
                                        f"vertex_array_size=%ld stride=%ld split_threshold=%ld' {'X0'} {vertex_array_addr} {vertex_array_addr} {vertex_array_size} {stride} {split_threshold}")
        set_ev_label(init_bcst_tran, temp_evw, BCST_EV_LABEL, new_thread=True)
        init_bcst_tran.writeAction(f"send_wret {temp_evw} {self.sampling_term_ev_label} {send_buffer} {8} {temp_reg}")
        init_bcst_tran.writeAction(f"addi {'X8'} {sampled_deg} 0")
        init_bcst_tran.writeAction(f"yield")
        
        '''
        UDKVMSR program finishes, signal the top.
        X8:     number of reduce tasks processed
        '''
        term_tran = self.state.writeTransition("eventCarry", self.state, self.state, self.sampling_term_ev_label)
        # UpDown program finishes, Signal the top 
        term_tran.writeAction(f"addi {'X7'} {lm_addr} {TOP_FLAG_OFFSET}")
        term_tran.writeAction(f"movir {temp_reg} 1")
        term_tran.writeAction(f"movrl {temp_reg} {0}({lm_addr}) 1 8")
        term_tran.writeAction(f"movrl {sampled_deg} 0({send_buffer}) 0 8")
        if self.debug_flag:
            term_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.sampling_term_ev_label}] Finish sampling the vertex degrees " + 
                                        f"sampled degree = %ld' {'X0'} {'EQT'} {sampled_deg}")
        term_tran.writeAction("yieldt")
    
    def __gen_sampling_degree(self):
        
        temp_reg    = 'X16'
        temp_evw    = 'X17'
        
        '''
        kv_map on an edge
        X8:     src vertex id
        X9:     dst vertex id
        '''
        kv_map_tran = self.state.writeTransition("eventCarry", self.state, self.state, self.kv_map_ev_label)
        if self.debug_flag and False:
            kv_map_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.kv_map_ev_label}] Event <kv_map> ev_word=%lu src=%ld dst=%ld' {'X0'} {'EQT'} {'X8'} {'X9'}")
        set_ev_label(kv_map_tran, temp_evw, self.kv_map_emit_ev_label, new_thread=True)
        kv_map_tran.writeAction(f"movir {temp_reg} {1}")
        kv_map_tran.writeAction(f"sendr_wcont {temp_evw} {'X1'} {'X8'} {temp_reg}")
        # kv_map_tran.writeAction(f"sendr_wcont {temp_evw} {'X1'} {'X9'} {temp_reg}")
        set_ev_label(kv_map_tran, temp_evw, self.kv_map_return_ev_label)
        kv_map_tran.writeAction(f"sendr_wcont {temp_evw} {'X1'} {'X8'} {'X9'}")
        kv_map_tran.writeAction(f"yield")
        
        '''
        reduce on a vertex
        X8:     vertex id
        X9:     count 1
        '''
        kv_reduce_tran = self.state.writeTransition("eventCarry", self.state, self.state, self.kv_reduce_ev_label)
        if self.debug_flag and False:
            kv_reduce_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.kv_reduce_ev_label}] Event <kv_reduce> ev_word=%lu vertex=%ld count=%ld' {'X0'} {'EQT'} {'X8'} {'X9'}")
        set_ev_label(kv_reduce_tran, temp_evw, self.kv_combine_ev_label)
        kv_reduce_tran.writeAction(f"sendr_wret {temp_evw} {self.kv_red_return_ev_label} {'X8'} {'X9'} {temp_reg}")
        kv_reduce_tran.writeAction(f"yield")
    
    def __gen_find_high_deg_vertex(self):
        
        FETCH_BATCH_SIZE    = 32
        vertex_array_ptr    = 'X16'
        vertex_array_bnd    = 'X17'
        counter             = 'X18'
        fetch_loop_evw      = 'X19'
        num_fetch_batch     = 'X20'
        num_vertices        = 'X21'
        temp_addr           = 'X22'
        vertex_array_base   = 'X23'
        temp_vid            = 'X24'
        sht_ack_evw         = 'X25'
        temp_reg            = 'X26'
        send_buffer         = 'X27'
        pending_ret         = 'X28'
        split_threshold     = 'X29'
        saved_cont          = 'X31'
        
        in_bound_label  = "array_in_bound"
        break_label     = "loop_break"
        continue_label  = "loop_continue"
        success_label   = "success_insert"
        fetch_loop_label    = "fetch_loop"
        skip_fetch_label    = "skip_fetch"
        fin_fetch_label     = "finish_fetch"
        empty_label         = "empty"
        
        '''
        Broadcast a segment of the vertex list to a lane.
        X8:     vertex list base address
        X9:     vertex list array size
        X10:    stide (number of vertices assigned to each lane)
        X11:    max split degree
        '''
        lane_init_tran = self.state.writeTransition("eventCarry", self.state, self.state, self.lane_init_ev_label)
        if self.debug_flag:
            lane_init_tran.writeAction(f"print ''")
            lane_init_tran.writeAction(f"sri {'X2'} {temp_reg} {32}")
            lane_init_tran.writeAction(f"andi {temp_reg} {temp_reg} {0xFF}")
            lane_init_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.lane_init_ev_label}] Event <lane_init> ev_word=%lu tid=%ld " + 
                                        f"vertex_list_size=%ld stride=%ld split_threshold=%ld' {'X0'} {'EQT'} {temp_reg} {'X9'} {'X10'} {'X11'}")
        lane_init_tran.writeAction(f"addi {'X1'} {saved_cont} 0")
        lane_init_tran.writeAction(f"mul {'X0'} {'X10'} {num_vertices}")
        lane_init_tran.writeAction(f"bge {num_vertices} {'X9'} {empty_label}")
        lane_init_tran.writeAction(f"sli {num_vertices} {vertex_array_ptr} {int(log2(VERTEX_COUNT_STRUCT_SIZE)) + LOG2_WORD_SIZE}")
        lane_init_tran.writeAction(f"add {'X8'} {vertex_array_ptr} {vertex_array_ptr}")
        lane_init_tran.writeAction(f"add {'X10'} {num_vertices} {temp_reg}")
        lane_init_tran.writeAction(f"addi {'X11'} {split_threshold} 0")
        lane_init_tran.writeAction(f"ble {temp_reg} {'X9'} {in_bound_label}")
        lane_init_tran.writeAction(f"addi {'X9'} {temp_reg} 0")
        lane_init_tran.writeAction(f"{in_bound_label}: sub {temp_reg} {num_vertices} {num_vertices}")
        lane_init_tran.writeAction(f"sli {num_vertices} {vertex_array_bnd} {int(log2(VERTEX_COUNT_STRUCT_SIZE)) + LOG2_WORD_SIZE}")
        lane_init_tran.writeAction(f"add {vertex_array_ptr} {vertex_array_bnd} {vertex_array_bnd}")
        if self.debug_flag:
            lane_init_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.lane_init_ev_label}] num_vertices = %ld vertex_array_ptr=%lu(0x%lx) " + 
                                        f"vertex_array_bnd=%lu(0x%lx)' {'X0'} {num_vertices} {vertex_array_ptr} {vertex_array_ptr} {vertex_array_bnd} {vertex_array_bnd}")
        set_ev_label(lane_init_tran, fetch_loop_evw, self.fetch_loop_ev_label)
        lane_init_tran.writeAction(f"movir {counter} 0")
        lane_init_tran.writeAction(f"movir {num_fetch_batch} {FETCH_BATCH_SIZE}")
        lane_init_tran.writeAction(f"{fetch_loop_label}: bge {vertex_array_ptr} {vertex_array_bnd} {break_label}")
        lane_init_tran.writeAction(f"send_dmlm_ld {vertex_array_ptr} {fetch_loop_evw} {DRAM_MSG_SIZE}")
        if self.debug_flag:
            lane_init_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.lane_init_ev_label}] Fetch vertex list addr=%lu(0x%lx) ' {'X0'} {vertex_array_ptr} {vertex_array_ptr}")
        lane_init_tran.writeAction(f"addi {vertex_array_ptr} {vertex_array_ptr} {DRAM_MSG_SIZE << LOG2_WORD_SIZE}")
        lane_init_tran.writeAction(f"addi {counter} {counter} 1")
        lane_init_tran.writeAction(f"blt {counter} {num_fetch_batch} {fetch_loop_label}")
        lane_init_tran.writeAction(f"{break_label}: movir {counter} 0")
        lane_init_tran.writeAction(f"addi {'X8'} {vertex_array_base} 0")
        set_ev_label(lane_init_tran, sht_ack_evw, self.put_split_vid_ev_label)
        lane_init_tran.writeAction(f"movir {temp_reg} {self.sampling_sht_desc_offset}")
        lane_init_tran.writeAction(f"addi {'X7'} {send_buffer} {KVMSR_SEND_BUFFER_OFFSET}")
        lane_init_tran.writeAction(f"movrl {temp_reg} {0}({send_buffer}) 0 8")
        lane_init_tran.writeAction(f"movir {temp_reg} {SEND_BUFFER_OFFSET}")
        lane_init_tran.writeAction(f"movrl {temp_reg} {WORD_SIZE}({send_buffer}) 0 8")
        lane_init_tran.writeAction(f"movir {pending_ret} 0")
        lane_init_tran.writeAction(f"yield")
        
        set_ignore_cont(lane_init_tran, temp_reg, empty_label)
        lane_init_tran.writeAction(f"sendr_wcont {saved_cont} {temp_reg} {'X8'} {num_vertices}")
        if self.debug_flag:
            lane_init_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.lane_init_ev_label}] Zero vertex is given base_addr=%lu(0x%lx), " + 
                                        f"return to %lu' {'X0'} {'X8'} {'X8'} {saved_cont}")
        lane_init_tran.writeAction(f"yieldt")
        
        fetch_loop_tran = self.state.writeTransition("eventCarry", self.state, self.state, self.fetch_loop_ev_label)
        if self.debug_flag:
            fetch_loop_tran.writeAction(f"sri {'X2'} {temp_addr} {32}")
            fetch_loop_tran.writeAction(f"andi {temp_addr} {temp_addr} {0xFF}")
            fetch_loop_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.fetch_loop_ev_label}] Event <fetch_loop> tid=%ld dram_return_addr=%lu(0x%lx) " + 
                                        f"counter=%ld num_vertices=%ld num_pending_return=%ld' {'X0'} {temp_addr} {'X3'} {'X3'} {counter} {num_vertices} {pending_ret}")
            fetch_loop_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.fetch_loop_ev_label}] Operands: curr_fetch_ptr=%lu(0x%lx) fetch_bound=%lu(0x%lx)' " + 
                                        f"{'X0'} {vertex_array_ptr} {vertex_array_ptr} {vertex_array_bnd} {vertex_array_bnd}")
        fetch_loop_tran.writeAction(f"bge {vertex_array_ptr} {vertex_array_bnd} {skip_fetch_label}")
        fetch_loop_tran.writeAction(f"send_dmlm_ld {vertex_array_ptr} {fetch_loop_evw} {DRAM_MSG_SIZE}")
        if self.debug_flag:
            fetch_loop_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.lane_init_ev_label}] Fetch vertex list addr=%lu(0x%lx) ' {'X0'} {vertex_array_ptr} {vertex_array_ptr}")
        fetch_loop_tran.writeAction(f"addi {vertex_array_ptr} {vertex_array_ptr} {DRAM_MSG_SIZE << LOG2_WORD_SIZE}")
        fetch_loop_tran.writeAction(f"{skip_fetch_label}: addi {'X3'} {temp_addr} 0")
        fetch_loop_tran.writeAction(f"sub {temp_addr} {vertex_array_base} {temp_vid}")
        fetch_loop_tran.writeAction(f"sri {temp_vid} {temp_vid} {int(log2(VERTEX_COUNT_STRUCT_SIZE)) + LOG2_WORD_SIZE}")
        # fetch_loop_tran.writeAction(f"movir {split_threshold} {SPLIT_THRESHOLD}")
        for k in range(0, DRAM_MSG_SIZE, VERTEX_COUNT_STRUCT_SIZE):
            op = f'X{OB_REG_BASE + k}'
            skip_split_label    = f"skip_split_{k}"
            fetch_loop_tran.writeAction(f"bge {temp_addr} {vertex_array_bnd} {break_label}")
            fetch_loop_tran.writeAction(f"blt {op} {split_threshold} {skip_split_label}")
            fetch_loop_tran.writeAction(f"movrl {temp_vid} {WORD_SIZE * 2}({send_buffer}) 0 8")
            fetch_loop_tran.writeAction(f"muli {op} {temp_reg} {SAMPLING_RATE}")
            fetch_loop_tran.writeAction(f"movrl {temp_reg} {WORD_SIZE * 3}({send_buffer}) 0 8")
            if self.debug_flag:
                fetch_loop_tran.writeAction(f"print '[{self.fetch_loop_ev_label}] Add vid=%ld to split SHT count=%ld est_degree=%ld' {temp_vid} {op} {temp_reg}")
            SHT.update_wcont(tran=fetch_loop_tran, ret=sht_ack_evw, tmp_reg0=temp_reg, arg_lm_addr_reg=send_buffer)
            fetch_loop_tran.writeAction(f"addi {pending_ret} {pending_ret} 1")
            fetch_loop_tran.writeAction(f"{skip_split_label}: addi {temp_vid} {temp_vid} 1")
            fetch_loop_tran.writeAction(f"addi {temp_addr} {temp_addr} {VERTEX_COUNT_STRUCT_SIZE * WORD_SIZE}")
            fetch_loop_tran.writeAction(f"addi {counter} {counter} 1")
        fetch_loop_tran.writeAction(f"{break_label}: beq {counter} {num_vertices} {fin_fetch_label}")
        fetch_loop_tran.writeAction(f"{continue_label}: yield")
        fetch_loop_tran.writeAction(f"{fin_fetch_label}: bnei {pending_ret} {0} {continue_label}")
        if self.debug_flag:
            fetch_loop_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.fetch_loop_ev_label}] All vertices are processed base_addr=%lu(0x%lx), " + 
                                        f"return to continuation %lu' {'X0'} {vertex_array_base} {vertex_array_base} {saved_cont}")
        set_ignore_cont(fetch_loop_tran, temp_reg)
        fetch_loop_tran.writeAction(f"sendr_wcont {saved_cont} {temp_reg} {vertex_array_base} {num_vertices}")
        fetch_loop_tran.writeAction(f"yieldt")
        
        '''
        Store the high degree vertex ID to the SHT return.
        '''
        put_split_vid_tran = self.state.writeTransition("eventCarry", self.state, self.state, self.put_split_vid_ev_label)
        if self.debug_flag:
            put_split_vid_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.put_split_vid_ev_label}] Event <put_split_vid> ev_word=%lu status= %ld return_val=%lu(0x%lx) " + 
                                           f"' {'X0'} {'X2'} {'X8'} {'X9'} {'X9'}")
            # put_split_vid_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.put_split_vid_ev_label}] counter=%ld num_vertices=%ld num_pending_return=%ld' {counter} {num_vertices} {pending_ret}")
        put_split_vid_tran.writeAction(f"beqi {'X8'} {1} {success_label}")
        put_split_vid_tran.writeAction(f"print '[ERROR][NWID %ld][{self.put_split_vid_ev_label}] Error: bucket full, fail to insert. status= %ld num_entry=%ld' {'X0'} {'X8'} {'X9'}")
        put_split_vid_tran.writeAction(f"{success_label}: subi {pending_ret} {pending_ret} 1")
        put_split_vid_tran.writeAction(f"bne {counter} {num_vertices} {continue_label}")
        put_split_vid_tran.writeAction(f"bnei {pending_ret} {0} {continue_label}")
        if self.debug_flag:
            put_split_vid_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.fetch_loop_ev_label}] All vertices are processed base_addr=%lu(0x%lx), " + 
                                        f"return to continuation %lu' {'X0'} {vertex_array_base} {vertex_array_base} {saved_cont}")
        set_ignore_cont(put_split_vid_tran, temp_reg)
        put_split_vid_tran.writeAction(f"sendr_wcont {saved_cont} {temp_reg} {vertex_array_base} {num_vertices}")
        put_split_vid_tran.writeAction(f"yieldt")
        put_split_vid_tran.writeAction(f"{continue_label}: yield")
        
        

@efaProgram
def GenSamplingEFA(efa: EFAProgram):
    Sampling(efa=efa)
    return efa