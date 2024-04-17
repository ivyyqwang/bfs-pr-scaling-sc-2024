from linker.EFAProgram import EFAProgram, efaProgram
from KVMSRMachineConfig import *
from Macro import *
from libraries.ScalableHashTable.linkable.sht_ext_call_macros import SHTExt as SHT
from libraries.UDMapShuffleReduce.linkable.LinkableGlobalSync import Broadcast
from libraries.UDMapShuffleReduce.linkable.LinkableKVMapShuffleReduceTPL import UDKeyValueMapShuffleReduceTemplate
from libraries.UDMapShuffleReduce.utils.OneDimArrayKeyValueSet import OneDimKeyValueSet
from Config import *

class AllocNeighbors:
    
    def __init__(self, efa: EFAProgram):
        
        self.task   = 'alloc_neighbors'
        self.efa    = efa
        self.efa.code_level = 'machine'
        self.state  = efa.State()
        efa.add_initId(self.state.state_id)
        
        self.send_buffer_offset = SEND_BUFFER_OFFSET
        self.alloc_mem_offset   = ALLOC_E_DATA_OFFSET
        
        self.udkvmsr_lm_offset  = UDKVMSR_LM_OFFSET
        self.split_v_sht_offset = SPLIT_V_SHT_OFFSET
        
        self.debug_flag = DEBUG_FLAG
                
        self.broadcast  = Broadcast(state=self.state, identifier=self.task, debug_flag=self.debug_flag)
        
        self.__gen_ev_labels()
        self.__gen_udkvmsr()
        self.__gen_init()
        self.__gen_init_updown()
        self.__gen_alloc_neighbors()
        
    def __gen_udkvmsr(self):
            
        self.udkvmsr = UDKeyValueMapShuffleReduceTemplate(efa=self.efa, task_name=self.task, meta_data_offset=UDKVMSR_LM_OFFSET, debug_flag=self.debug_flag)
        
        self.udkvmsr.set_input_kvset(OneDimKeyValueSet(f"{self.task}_input_kvset", element_size=VERTEX_STRUCT_SIZE))
        
        self.udkvmsr.set_max_thread_per_lane(max_map_th_per_lane=MAX_ALLOC_NLIST_MAP_THREADS)
        
        self.udkvmsr.generate_udkvmsr_task()
        
    def __gen_ev_labels(self):
        
        self.entry_ev_label         = get_event_label(self.task, 'entry_event')
        self.bcst_sync_ev_label     = get_event_label(self.task, 'broadcast_synchronization')
        self.init_udkvmsr_ev_label  = get_event_label(self.task, 'init_udkvmsr_program')
        self.udkvmsr_ret_ev_label   = get_event_label(self.task, 'udkvmsr_return_event')
        self.terminate_ev_label     = get_event_label(self.task, 'terminate_event')
        
        self.init_ud_alloc_ev_label    = get_event_label(self.task, 'init_updown_nlist_allocator')
        self.alloc_nlist_ev_label      = get_event_label(self.task, 'allocate_nlist')
        self.term_ud_allocator_ev_label= get_event_label(self.task, 'terminate_updown_allocator')
        self.term_allocator_ev_label   = get_event_label(self.task, 'terminate_allocator')
        
        self.alloc_ret_ev_label     = get_event_label(self.task, 'allocate_nlist_return')
        self.get_split_v_ev_label   = get_event_label(self.task, 'get_split_vertex')
        self.sync_ev_label          = get_event_label(self.task, 'sync')
        self.store_v_ret_ev_label   = get_event_label(self.task, 'store_vertex_return')
        
        self.udkvmsr_entry_ev_label = get_event_label(self.task, 'map_shuffle_reduce')
        self.kv_map_ev_label        = get_event_label(self.task, 'kv_map')
        self.kv_map_return_ev_label = get_event_label(self.task, 'kv_map_return')
    
    def __gen_init(self):
        
        send_buffer = 'X16'
        lm_addr     = 'X17'
        temp_evw    = 'X18'
        temp_reg    = 'X19'
        num_lanes   = 'X23'
        num_uds     = 'X24'
        
        scratch         = ["X29", "X30", "X31"]
        '''
        Vertex split entry event.
        X8:     partition array address
        X9:     number of partitions per lane
        X10:    number of lanes
        X11:    vertex array base address
        X12:    vertex array size
        X13:    neighbor list base address
        X14:    neighbor list size per updown 
        '''
        multiple_label = "multiple"
        entry_tran = self.state.writeTransition("eventCarry", self.state, self.state, self.entry_ev_label)
        if self.debug_flag:
            entry_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.entry_ev_label}] Event <alloc_neighbors_entry> ev_word=%lu partition=%lu(0x%lx) " + 
                                                f"num_partitions_per_lane=%ld num_lanes=%ld' {'X0'} {'EQT'} {'X8'} {'X8'} {'X9'} {'X10'}")
            entry_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.entry_ev_label}] vertex_list=%lu(0x%lx) vertex_list_size=%ld" + 
                                                f" neighbors=%lu(0x%lx) neighbors_per_ud=%ld' {'X0'} {'X11'} {'X11'} {'X12'} {'X13'} {'X13'} {'X14'}")
        entry_tran.writeAction(f"addi {'X10'} {num_lanes} 0")
        get_num_ud_per_node(tran=entry_tran, total_num_lanes=num_lanes, result=num_uds, label=multiple_label, reg=temp_reg)
        set_ev_label(entry_tran, temp_evw, self.init_ud_alloc_ev_label, new_thread = True, label=multiple_label)
        if self.debug_flag:
            entry_tran.writeAction(f"print '[DEBUG][NWID %d][{self.entry_ev_label}] Broadcast to %ld updowns' {'X0'} {num_uds}")
        broadcast(entry_tran, temp_evw, num_uds, self.bcst_sync_ev_label, LOG2_LANE_PER_UD, f"{'X13'} {'X14'} {scratch[1]}", scratch, 'r3')
        entry_tran.writeAction(f"addi {'X7'} {send_buffer} {KVMSR_SEND_BUFFER_OFFSET}")
        entry_tran.writeAction(f"movrl {'X8'} 0({send_buffer}) 0 8")
        entry_tran.writeAction(f"movrl {'X9'} 8({send_buffer}) 0 8")
        entry_tran.writeAction(f"movrl {'X10'} 16({send_buffer}) 0 8")
        entry_tran.writeAction(f"addi {'X7'} {lm_addr} {KVMSR_INPUT_OFFSET}")
        entry_tran.writeAction(f"movrl {lm_addr} 24({send_buffer}) 0 8")
        if self.debug_flag:
            entry_tran.writeAction(f"print '[DEBUG][NWID %d] Save input vertex array base pointer %lu(0x%lx) and " + 
                                          f"size %ld to scratchpad addr %lu(0x%lx)' {'X0'} {'X11'} {'X11'} {'X12'} {lm_addr} {lm_addr}")
        entry_tran.writeAction(f"movrl {'X11'} 0({lm_addr}) 1 8")
        entry_tran.writeAction(f"movrl {'X12'} 0({lm_addr}) 1 8")
        entry_tran.writeAction(f"movir {temp_reg} 0")
        entry_tran.writeAction(f"addi {'X7'} {lm_addr} {TOP_FLAG_OFFSET}")
        entry_tran.writeAction(f"move {temp_reg} {0}({lm_addr}) 0 8")
        entry_tran.writeAction(f"yield")
        
        '''
        Finish init the verted id allocator. Start broadcast parameters to all lanes.
        X8:     updown id
        '''
        finish_sync_label = "finish_sync"
        bcst_sync_tran = self.state.writeTransition("eventCarry", self.state, self.state, self.bcst_sync_ev_label)
        if self.debug_flag:
            bcst_sync_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.bcst_sync_ev_label}] Event <broadcast_synchronization> ev_word=%lu return updown_id=%ld' {'X0'} {'EQT'} {'X8'}")
        bcst_sync_tran.writeAction(f"subi {num_uds} {num_uds} 1")
        bcst_sync_tran.writeAction(f"beqi {num_uds} {0} {finish_sync_label}")
        bcst_sync_tran.writeAction(f"yield")
        bcst_sync_tran.writeAction(f"{finish_sync_label}: addi {'X7'} {send_buffer} {KVMSR_SEND_BUFFER_OFFSET}")
        set_ev_label(bcst_sync_tran, temp_evw, self.udkvmsr_entry_ev_label, new_thread=True)
        bcst_sync_tran.writeAction(f"send_wret {temp_evw} {self.terminate_ev_label} {send_buffer} 5 {temp_reg}")
        if self.debug_flag:
            bcst_sync_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.bcst_sync_ev_label}] Finish broadcast the " + 
                                       f"neighbor list bins to %ld updown. Start the {self.task} UDKVMSR program' {'X0'} {num_uds} {'X8'}")
        bcst_sync_tran.writeAction(f"yield")
        
        
        '''
        UDKVMSR returns, return to top with the highest vertex id.
        '''
        term_tran = self.state.writeTransition("eventCarry", self.state, self.state, self.terminate_ev_label)
        # UpDown program finishes, Signal the top 
        term_tran.writeAction(f"movir {temp_reg} 1")
        term_tran.writeAction(f"movrl {temp_reg} {0}({lm_addr}) 1 8")
        set_ev_label(term_tran, temp_evw, self.term_ud_allocator_ev_label, new_thread = True)
        if self.debug_flag:
            term_tran.writeAction(f"print '[DEBUG][NWID %d][{self.entry_ev_label}] Terminate nlist allocator on %ld updowns' {'X0'} {num_uds}")
        broadcast(term_tran, temp_evw, num_uds, self.terminate_ev_label, LOG2_LANE_PER_UD, f"{scratch[1]} {'X2'}", scratch, 'r')
        term_tran.writeAction("yield_terminate")
    
    def __gen_init_updown(self):
        
        '''
        Broadcast argument to all the updown.
        X8:     neighbor list base address
        X9:     neighbor list size per updown
        X10:    updown id
        '''
        lm_addr      = 'X16'
        nlist_offset = 'X17'
        temp_val     = 'X18'
        alloc_evw    = 'X19'
        init_ud_alloc_tran = self.state.writeTransition("eventCarry", self.state, self.state, self.init_ud_alloc_ev_label)
        if self.debug_flag:
            init_ud_alloc_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.init_ud_alloc_ev_label}] Event <init_nlist_allocator> ev_word=%lu " + 
                                         f"nlist_addr=%lu(0x%lx) nlist_size=%ld updown_id=%ld' {'X0'} {'EQT'} {'X8'} {'X8'} {'X9'} {'X10'}")
        init_ud_alloc_tran.writeAction(f"mul {'X9'} {'X10'} {nlist_offset}")
        init_ud_alloc_tran.writeAction(f"add {'X8'} {nlist_offset} {nlist_offset}")
        # init_ud_sp_tran.writeAction(f"addi {'X7'} {lm_addr} {self.alloc_mem_offset}")
        # init_ud_sp_tran.writeAction(f"movrl {nlist_offset} 0({lm_addr}) 0 8")
        init_ud_alloc_tran.writeAction(f"addi {'X7'} {temp_val} {self.alloc_mem_offset}")
        set_ev_label(init_ud_alloc_tran, alloc_evw, self.alloc_nlist_ev_label)
        for n in range(LANE_PER_UD):
            # print(f"Initialize lane {n}'s cache in scratchpad memory")
            init_ud_alloc_tran.writeAction(f"movir {lm_addr} {n}")
            init_ud_alloc_tran.writeAction(f"sli {lm_addr} {lm_addr} 16")
            init_ud_alloc_tran.writeAction(f"add {lm_addr} {temp_val} {lm_addr}")
            init_ud_alloc_tran.writeAction(f"movrl {alloc_evw} 0({lm_addr}) 0 8")
            if self.debug_flag:
                init_ud_alloc_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.init_ud_alloc_ev_label}] Store nlist allocator ev_word=%lu " + 
                                            f"at lm addr %lu(0x%lx) start allocating from addr=%lu(0x%lx)' {'X0'} {alloc_evw} {lm_addr} {lm_addr} {nlist_offset} {nlist_offset}")
        init_ud_alloc_tran.writeAction(f"sendr_reply {'X10'} {alloc_evw} {temp_val}")
        init_ud_alloc_tran.writeAction(f"yield")
        
        '''
        Request new neighbor list allocation.
        X8:      size of neighbor list to allocate
        '''
        alloc_nlist_tran = self.state.writeTransition("eventCarry", self.state, self.state, self.alloc_nlist_ev_label)
        if self.debug_flag:
            alloc_nlist_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.alloc_nlist_ev_label}] Event <allocate_nlist> ev_word=%lu " + 
                                       f"nlist_size=%ld curr_addr=%ld' {'X0'} {'EQT'} {'X8'} {nlist_offset}")
        alloc_nlist_tran.writeAction(f"sendr_wcont {'X1'} {alloc_evw} {nlist_offset} {'X8'}")
        alloc_nlist_tran.writeAction(f"add {'X8'} {nlist_offset} {nlist_offset}")
        alloc_nlist_tran.writeAction(f"yield")
        
        term_ud_alloc_tran = self.state.writeTransition("eventCarry", self.state, self.state, self.term_ud_allocator_ev_label)
        if self.debug_flag:
            term_ud_alloc_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.term_ud_allocator_ev_label}] terminate nlist allocator on ud %ld' {'X0'} {'X8'}")
        term_ud_alloc_tran.writeAction(f"movlr {self.alloc_mem_offset}({'X7'}) {alloc_evw} 0 8")
        set_ev_label(term_ud_alloc_tran, alloc_evw, self.term_allocator_ev_label, src_ev=alloc_evw)
        term_ud_alloc_tran.writeAction(f"sendr_wcont {alloc_evw} {'X2'} {'X0'} {'X8'}")
        term_ud_alloc_tran.writeAction(f"yieldt")
        
        term_alloc_tran = self.state.writeTransition("eventCarry", self.state, self.state, self.term_allocator_ev_label)
        if self.debug_flag:
            term_alloc_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.term_allocator_ev_label}] Terminate allocator ev_word=%lu on ud %ld' {'X0'} {alloc_evw} {'X8'}")
        term_alloc_tran.writeAction(f"yieldt")
        
    
    def __gen_alloc_neighbors(self):
        
        vid         = 'X16'
        lm_addr     = 'X17'
        nlist_bsize = 'X18'
        nlist_addr  = 'X19'
        temp_evw    = 'X20'
        temp_val    = 'X21'
        buffer_addr = 'X22'
        v_offset    = 'X23'
        degree      = 'X24'
        ori_vid     = 'X25'
        split_vids  = 'X26'
        v_addr      = 'X27'
        pending_ack = 'X28'
                
        scratch     = ["X29", "X30", "X31"]
        continue_label = "continue"
        
        '''
        Read the vertex ID and the estimated degree of the vertex to be split.
        X8:     degree
        X9:     original vertex ID
        X10:    vertex ID
        X11:    neighbor list
        X12:    distance
        X13:    parent
        X14:    split vids (optional)
        '''
        zero_degree_label = "zero_degree"
        kv_map_tran = self.state.writeTransition("eventCarry", self.state, self.state, self.kv_map_ev_label)
        # kv_map_tran.writeAction(f"beqi {'X8'} {0} {zero_degree_label}")
        kv_map_tran.writeAction(f"addi {'X8'} {degree} 0")
        kv_map_tran.writeAction(f"addi {'X3'} {v_addr} 0")
        kv_map_tran.writeAction(f"movlr {self.udkvmsr.in_kvset.meta_data_offset}({'X7'}) {v_offset} 0 8")
        kv_map_tran.writeAction(f"sub {v_addr} {v_offset} {v_offset}")
        kv_map_tran.writeAction(f"sri {v_offset} {vid} {int(log2(VERTEX_STRUCT_SIZE)) + LOG2_WORD_SIZE}")
        if self.debug_flag:
            kv_map_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.kv_map_ev_label}] Event <kv_map> vid=%ld degree=%ld " + 
                                    f"addr=%lu(0x%lx)' {'X0'} {vid} {degree} {v_addr} {v_addr}")
        kv_map_tran.writeAction(f"sli {degree} {nlist_bsize} {LOG2_WORD_SIZE}")
        kv_map_tran.writeAction(f"sri {'X7'} {lm_addr} {22}")
        kv_map_tran.writeAction(f"sli {lm_addr} {lm_addr} {22}")
        if self.debug_flag:
            kv_map_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.kv_map_ev_label}] Allocate %ld bytes for vertex %ld neighbor list degree = %ld' {'X0'} {nlist_bsize} {vid} {degree}")
        kv_map_tran.writeAction(f"addi {lm_addr} {lm_addr} {self.alloc_mem_offset}")
        # spin_lock(tran=kv_map_tran, lm_addr=lm_addr, value=nlist_bsize, op="add", result=nlist_addr, scratch_regs=scratch)
        kv_map_tran.writeAction(f"movlr {self.alloc_mem_offset}({'X7'}) {temp_evw} 0 8")
        kv_map_tran.writeAction(f"sendr_wret {temp_evw} {self.alloc_ret_ev_label} {nlist_bsize} {'X8'} {scratch[0]}")
        # get the split vertex mapping from SHT
        set_ev_label(kv_map_tran, temp_evw, self.get_split_v_ev_label)
        kv_map_tran.writeAction(f"movir {lm_addr} {self.split_v_sht_offset}")
        SHT.get_wcont(tran=kv_map_tran, ret=temp_evw, tmp_reg=temp_val, desc_lm_offset_reg=lm_addr, key_reg=vid)
        kv_map_tran.writeAction(f"movir {pending_ack} 2")
        set_ev_label(kv_map_tran, temp_evw, self.sync_ev_label)
        kv_map_tran.writeAction(f"yield")
        # zero degree vertex, skip updating the vertex structure
        set_ev_label(kv_map_tran, temp_evw, self.kv_map_return_ev_label, label=zero_degree_label)
        kv_map_tran.writeAction(f"sendr_wcont {temp_evw} {'X2'} {vid} {'X8'}")
        kv_map_tran.writeAction(f"yield")
        
        
        '''
        Allocate neighbor list return.
        X8:     neighbor list address
        '''
        alloc_ret_tran = self.state.writeTransition("eventCarry", self.state, self.state, self.alloc_ret_ev_label)
        alloc_ret_tran.writeAction(f"addi {'X8'} {nlist_addr} {0}")
        if self.debug_flag:
            alloc_ret_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.kv_map_ev_label}] Allocate neighbor list for vertex %ld at addr %lu(0x%lx)' {'X0'} {vid} {nlist_addr} {nlist_addr}")
        alloc_ret_tran.writeAction(f"subi {pending_ack} {pending_ack} 1")
        alloc_ret_tran.writeAction(f"bnei {pending_ack} {0} {continue_label}")
        alloc_ret_tran.writeAction(f"sendr_wcont {temp_evw} {'X2'} {nlist_addr} {'X8'}")
        alloc_ret_tran.writeAction(f"{continue_label}: yield")
        '''
        Get split mapping from SHT.
        X8:     vertex id
        X9:     status bit
        X10:    value[0]
        X11:    value[1]
        
        Original vertex ID  -> (split base vertex ID, number of split vertices)
        Split vertex ID     -> (original vertex ID, [split base vertex ID | number of split vertices])
        '''
        error_label = "get_original_vertex_error"
        ori_v_label = "original_vertex"
        store_v_label = "store_vertex"
        split_v_label = "split_vertex"
        hige_deg_label = "high_degree"
        get_split_v_tran = self.state.writeTransition("eventCarry", self.state, self.state, self.get_split_v_ev_label)
        if self.debug_flag:
            get_split_v_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.get_split_v_ev_label}] Event <get_split_vertex> vid=%ld status=%lu' {'X0'} {'X8'} {'X9'}")
        get_split_v_tran.writeAction(f"beqi {'X9'} {0} {ori_v_label}")
        get_split_v_tran.writeAction(f"bgt {'X10'} {'X8'} {hige_deg_label}")
        
        # Is a split vertex, store the original vertex ID, and get split vertex ID range
        get_split_v_tran.writeAction(f"{split_v_label}: addi {'X10'} {ori_vid} 0")
        get_split_v_tran.writeAction(f"addi {'X11'} {split_vids} 0")
        if self.debug_flag:
            get_split_v_tran.writeAction(f"sri {split_vids} {temp_val} {32}")
            get_split_v_tran.writeAction(f"sli {split_vids} {v_offset} {32}")
            get_split_v_tran.writeAction(f"sri {v_offset} {v_offset} {32}")
            get_split_v_tran.writeAction(f"add {temp_val} {v_offset} {v_offset}")
            get_split_v_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.get_split_v_ev_label}] Get original vertex ID %ld for split vertex %ld, " + 
                                         f"split_range=[%ld, %ld)' {'X0'} {ori_vid} {vid} {temp_val} {v_offset}")
        get_split_v_tran.writeAction(f"jmp {store_v_label}")
        
        # Not a split vertex, set original vid to the current vertex ID
        get_split_v_tran.writeAction(f"{ori_v_label}: addi {vid} {ori_vid} 0")
        get_split_v_tran.writeAction(f"movir {split_vids} 0")
        if self.debug_flag:
            get_split_v_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.get_split_v_ev_label}] Vertex %ld is not a split vertex, set original vertex ID to %ld' {'X0'} {vid} {ori_vid}")
        get_split_v_tran.writeAction(f"jmp {store_v_label}")
        get_split_v_tran.writeAction(f"{hige_deg_label}: addi {vid} {ori_vid} 0")
        get_split_v_tran.writeAction(f"sli {'X10'} {split_vids} 32")
        get_split_v_tran.writeAction(f"add {'X10'} {'X11'} {temp_val}")
        if self.debug_flag or True:
            get_split_v_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.get_split_v_ev_label}] Vertex %ld is a high degree vertex, " + 
                                         f"set split range to [%ld, %ld] num_split = %ld' {'X0'} {ori_vid} {'X10'}  {temp_val} {'X11'}")
        get_split_v_tran.writeAction(f"or {split_vids} {temp_val} {split_vids}")
            
        get_split_v_tran.writeAction(f"{store_v_label}: subi {pending_ack} {pending_ack} 1")
        get_split_v_tran.writeAction(f"bnei {pending_ack} {0} {continue_label}")
        get_split_v_tran.writeAction(f"sendr_wcont {temp_evw} {'X2'} {vid} {'X8'}")
        get_split_v_tran.writeAction(f"{continue_label}: yield")
        
        get_split_v_tran.writeAction(f"{error_label}: movir {temp_val} {-1}")
        get_split_v_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.get_split_v_ev_label}] Error: vertex id %ld is in split v SHT but not a split vertex: val[0]=%ld val[1]=%ld' {'X0'} {vid} {'X10'} {'X11'}")
        get_split_v_tran.writeAction(f"jmp {split_v_label}")
        set_ev_label(get_split_v_tran, temp_evw, self.kv_map_return_ev_label)
        get_split_v_tran.writeAction(f"sendr_wcont {temp_evw} {'X2'} {vid} {'X8'}")
        get_split_v_tran.writeAction(f"yield")
        
        '''
        Finish getting the split vertex mapping and neighbor list allocation. Save the vertex structure to DRAM.
        '''
        sync_tran = self.state.writeTransition("eventCarry", self.state, self.state, self.sync_ev_label)
        # Save the vertex structure to DRAM
        sync_tran.writeAction(f"addi {'X7'} {buffer_addr} {self.send_buffer_offset}")
        sync_tran.writeAction(f"movrl {degree} {WORD_SIZE*0}({buffer_addr}) 0 8")
        sync_tran.writeAction(f"movrl {ori_vid} {WORD_SIZE*1}({buffer_addr}) 0 8")
        sync_tran.writeAction(f"movrl {vid} {WORD_SIZE*2}({buffer_addr}) 0 8")
        sync_tran.writeAction(f"movrl {nlist_addr} {WORD_SIZE*3}({buffer_addr}) 0 8")
        sync_tran.writeAction(f"movir {temp_val} {-1}")
        sync_tran.writeAction(f"movrl {temp_val} {WORD_SIZE*4}({buffer_addr}) 0 8")
        sync_tran.writeAction(f"movrl {temp_val} {WORD_SIZE*5}({buffer_addr}) 0 8")
        sync_tran.writeAction(f"movrl {split_vids} {WORD_SIZE*6}({buffer_addr}) 0 8")
        sync_tran.writeAction(f"send_dmlm_wret {v_addr} {self.store_v_ret_ev_label} {buffer_addr} {VERTEX_STRUCT_SIZE} {temp_evw}")
        if self.debug_flag:
            sync_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.sync_ev_label}] Send vertex %ld ori_vid=%ld, degree=%ld, nlist_addr=%lu(0x%lx) " + 
                                  f"structure to DRAM addr=%lu(0x%lx)' {'X0'} {vid} {ori_vid} {degree} {nlist_addr} {nlist_addr} {v_addr} {v_addr}")
        sync_tran.writeAction(f"yield")
        
        '''
        Update vertex structure return.
        '''
        store_v_ret_tran = self.state.writeTransition("eventCarry", self.state, self.state, self.store_v_ret_ev_label)
        if self.debug_flag:
            store_v_ret_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.store_v_ret_ev_label}] Event <store_vertex_return> ev_word=%lu " + 
                                         f"vid=%ld addr=%lu(0x%lx)' {'X0'} {'EQT'} {vid} {'X8'} {'X8'}")
        set_ev_label(store_v_ret_tran, temp_evw, self.kv_map_return_ev_label)
        store_v_ret_tran.writeAction(f"sendr_wcont {temp_evw} {'X2'} {vid} {'X8'}")
        store_v_ret_tran.writeAction(f"{continue_label}: yield")
        

@efaProgram
def GenAllocNeighborsEFA(efa: EFAProgram):
    AllocNeighbors(efa=efa)
    return efa