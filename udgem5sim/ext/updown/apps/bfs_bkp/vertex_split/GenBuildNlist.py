from linker.EFAProgram import EFAProgram, efaProgram
from KVMSRMachineConfig import *
from Macro import *
from libraries.UDMapShuffleReduce.linkable.LinkableKVMapShuffleReduceTPL import UDKeyValueMapShuffleReduceTemplate
from libraries.UDMapShuffleReduce.utils.OneDimArrayKeyValueSet import OneDimKeyValueSet
from libraries.UDMapShuffleReduce.linkable.LinkableLMCache import LMCache
from Config import *

class BuildNlist:
    
    def __init__(self, efa: EFAProgram):
        
        self.task   = 'build_neighbor_list'
        self.efa    = efa
        self.efa.code_level = 'machine'
        self.state  = efa.State()
        efa.add_initId(self.state.state_id)
        
        self.send_buffer_offset = SEND_BUFFER_OFFSET
        
        self.cache_nwid_offset  = BUILD_N_DATA_OFFSET
        self.vertex_list_offset = BUILD_N_DATA_OFFSET + (1 * WORD_SIZE)
        
        self.debug_flag         = DEBUG_FLAG
        
        self.num_partitions_per_lane = 2
        
        cache_data_store = OneDimKeyValueSet(f"{self.task}_cache_data_store", element_size=VERTEX_COUNT_STRUCT_SIZE)
        self.cache = LMCache(state=self.state, identifier=self.task, cache_offset = LM_CACHE_OFFSET, num_entries = LM_CACHE_NUM_ENTRIES, policy=LMCache.Policy.WRITE_THROUGH, 
            entry_size = LM_CACHE_ENTRY_SIZE, data_store = cache_data_store, metadata_offset = LM_CACHE_META_OFFSET, debug_flag = self.debug_flag, combine_func=self.cache_combine_func)

        self.__gen_ev_labels()
        self.__gen_udkvmsr()
        self.__gen_init()
        self.__gen_edge_split()
        
    def __gen_udkvmsr(self):
            
        self.udkvmsr = UDKeyValueMapShuffleReduceTemplate(efa=self.efa, task_name=self.task, meta_data_offset=UDKVMSR_LM_OFFSET, debug_flag=self.debug_flag)
        
        self.udkvmsr.set_input_kvset(OneDimKeyValueSet(f"{self.task}_input_kvset", element_size=EDGE_STRUCT_SIZE, metadata_size=5))
        
        self.udkvmsr.set_max_thread_per_lane(max_map_th_per_lane=MAX_BUILD_NLSIT_MAP_THREADS)

        self.udkvmsr.generate_udkvmsr_task()
        
    def __gen_ev_labels(self):
        
        self.build_nlist_entry_ev_label = get_event_label(self.task, 'build_nlist_entry_event')
        self.init_udkvmsr_ev_label      = get_event_label(self.task, 'init_udkvmsr_program')
        self.build_nlist_term_ev_label  = get_event_label(self.task, 'build_nlist_terminate_event')
        
                
        self.kv_map_ev_label        = get_event_label(self.task, 'kv_map')
        self.cache_return_ev_label  = get_event_label(self.task, 'get_nlist_offset')
        self.get_vertex_ev_label    = get_event_label(self.task, 'get_vertex_struct')
        self.wr_nlist_ev_label      = get_event_label(self.task, 'write_dst_to_dram')
        self.wr_nlist_ack_ev_label  = get_event_label(self.task, 'write_nlist_ack_from_dram')
        
        # UDKVMSR interface events
        self.udkvmsr_entry_ev_label = get_event_label(self.task, 'map_shuffle_reduce')
        self.kv_map_emit_ev_label   = get_event_label(self.task, 'kv_map_emit')
        self.kv_map_return_ev_label = get_event_label(self.task, 'kv_map_return')
        
        # Cache interface events
        self.cache_init_ev_label    = get_event_label(self.task, "cache_init")
        self.combine_val_ev_label   = get_event_label(self.task, "cache_combine_value")
    
    def __gen_init(self):
        
        send_buffer = 'X16'
        lm_addr     = 'X17'
        temp_evw    = 'X18'
        temp_reg    = 'X19'
        num_lanes   = 'X23'
        base_lane   = 'X24'
        
        '''
        Vertex split entry event.
        X8:     partition array address
        X9:     number of lanes
        X10:    edge list base address
        X11:    edge list array size
        X12:    nlist offset list base address
        X13:    vertex list array base address
        X14:    vertex list size
        X15:    cache base lane nwid [63:32] | cache number of lanes [31:0]
        '''
        entry_tran = self.state.writeTransition("eventCarry", self.state, self.state, self.build_nlist_entry_ev_label)
        if self.debug_flag:
            entry_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.build_nlist_entry_ev_label}] Event <edge_split_entry> ev_word=%lu partition=%lu(0x%lx) " + 
                                                f"num_partitions_per_lane={self.num_partitions_per_lane} num_lanes=%ld cache_metadata=%lu' {'X0'} {'EQT'} {'X8'} {'X8'} {'X9'} {'X15'}")
            entry_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.build_nlist_entry_ev_label}] edge_list=%lu(0x%lx) edge_list_size=%ld nlist_offset_array=%lu(0x%lx)" + 
                                                f"vertex_list=%lu(0x%lx) vertex_list_size=%ld' {'X0'} {'X10'} {'X10'} {'X11'} {'X12'} {'X12'} {'X13'} {'X13'} {'X14'}")
        
        set_ev_label(entry_tran, temp_evw, self.cache_init_ev_label, new_thread=True)
        entry_tran.writeAction(f"sri {'X15'} {base_lane} 32")
        set_nwid(entry_tran, temp_evw, base_lane, src_ev=temp_evw)
        entry_tran.writeAction(f"sli {'X15'} {num_lanes} 32")
        entry_tran.writeAction(f"sri {num_lanes} {num_lanes} 32")
        if self.debug_flag:
            entry_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.build_nlist_entry_ev_label}] Init cache base_lane=%ld num_lanes=%ld' {base_lane} {num_lanes}")
        entry_tran.writeAction(f"sendr3_wret {temp_evw} {self.init_udkvmsr_ev_label} {num_lanes} {'X12'} {'X14'} {temp_reg}")
        entry_tran.writeAction(f"addi {'X7'} {send_buffer} {self.send_buffer_offset}")
        entry_tran.writeAction(f"movrl {'X8'} 0({send_buffer}) 0 8")
        entry_tran.writeAction(f"movir {temp_reg} {self.num_partitions_per_lane}")
        entry_tran.writeAction(f"movrl {temp_reg} 8({send_buffer}) 0 8")
        entry_tran.writeAction(f"movrl {'X9'} 16({send_buffer}) 0 8")
        entry_tran.writeAction(f"addi {'X7'} {lm_addr} {KVMSR_INPUT_OFFSET}")
        entry_tran.writeAction(f"movrl {lm_addr} 24({send_buffer}) 0 8")
        if self.debug_flag:
            entry_tran.writeAction(f"print '[DEBUG][NWID %d] Save input key value set base pointer %lu(0x%lx) and " + 
                                          f"size %ld to scratchpad addr %ld(0x%lx)' {'X0'} {'X11'} {'X11'} {'X12'} {lm_addr} {lm_addr}")
        entry_tran.writeAction(f"movrl {'X10'} 0({lm_addr}) 1 8")
        entry_tran.writeAction(f"movrl {'X11'} 0({lm_addr}) 1 8")
        entry_tran.writeAction(f"movrl {base_lane} 0({lm_addr}) 1 8")
        entry_tran.writeAction(f"movrl {'X13'} 0({lm_addr}) 1 8")
        entry_tran.writeAction(f"movrl {'X14'} 0({lm_addr}) 1 8")
        entry_tran.writeAction(f"yield")
        
        '''
        Finish initialization, send the event to start the UDKVMSR program.
        '''
        init_udkvmsr_tran = self.state.writeTransition("eventCarry", self.state, self.state, self.init_udkvmsr_ev_label)
        set_ev_label(init_udkvmsr_tran, temp_evw, self.udkvmsr_entry_ev_label, new_thread=True)
        init_udkvmsr_tran.writeAction(f"send_wret {temp_evw} {self.build_nlist_term_ev_label} {send_buffer} {UDKVMSR_INIT_NUM_OPS} {temp_reg}")
        init_udkvmsr_tran.writeAction(f"mov_imm2reg {temp_reg} 0")
        init_udkvmsr_tran.writeAction(f"addi {'X7'} {lm_addr} {TOP_FLAG_OFFSET}")
        init_udkvmsr_tran.writeAction(f"move {temp_reg} {0}({lm_addr}) 0 8")
        init_udkvmsr_tran.writeAction(f"yield")
        
        '''
        UDKVMSR program finishes, signal the top.
        X8:     number of reduce tasks processed
        '''
        term_tran = self.state.writeTransition("eventCarry", self.state, self.state, self.build_nlist_term_ev_label)
        # UpDown program finishes, Signal the top 
        term_tran.writeAction(f"movir {temp_reg} 1")
        term_tran.writeAction(f"movrl {temp_reg} {0}({lm_addr}) 1 8")
        term_tran.writeAction(f"movrl {'X8'} 0({send_buffer}) 0 8")
        term_tran.writeAction("yield_terminate")
        
    def __gen_edge_split(self):
        
        src_vid         = 'X16'
        dst_vid         = 'X17'
        map_evw         = 'X18'
        pending_ret     = 'X19'
        vertex_addr     = 'X20'
        nlist_offset    = 'X21'
        nlist_addr      = 'X23'
        temp_reg        = 'X25'
        temp_evw        = 'X26'
        
        
        scratch         = ["X29", "X30", "X31"]
        
        continue_label  = "continue"
        '''
        Read the edge.
        X8:     src vertex ID
        X9:     dst vertex ID
        '''
        kv_map_tran = self.state.writeTransition("eventCarry", self.state, self.state, self.kv_map_ev_label)
        if self.debug_flag:
            kv_map_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.kv_map_ev_label}] Event <kv_map> read edge (%ld, %ld) " + 
                                          f"at edge_addr=%lu(0x%lx)' {'X0'} {'EQT'} {'X8'} {'X9'} {'X10'} {'X10'}")
        kv_map_tran.writeAction(f"addi {'X8'} {src_vid} 0")
        kv_map_tran.writeAction(f"addi {'X9'} {dst_vid} 0")
        # Get the neighbor list offset of the source vertex.
        kv_map_tran.writeAction(f"movlr {self.cache_nwid_offset}({'X7'}) {temp_reg} 0 8")
        kv_map_tran.writeAction(f"add {'X0'} {temp_reg} {temp_reg}")
        set_ev_label(kv_map_tran, temp_evw, self.combine_val_ev_label, new_thread=True)
        set_nwid(kv_map_tran, temp_evw, temp_reg, src_ev=temp_evw)
        set_ev_label(kv_map_tran, map_evw, self.cache_return_ev_label)
        kv_map_tran.writeAction(f"movir {temp_reg} {1}")
        kv_map_tran.writeAction(f"sendr_wcont {temp_evw} {map_evw} {src_vid} {temp_reg}")
        # if self.debug_flag:
        #     kv_map_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.kv_map_ev_label}] Get src_vid=%ld neighbor list offset from cache ' {'X0'} {'X8'}")
        # Read vertex structure from DRAM.
        kv_map_tran.writeAction(f"evlb {map_evw} {self.get_vertex_ev_label}")
        kv_map_tran.writeAction(f"movlr {self.vertex_list_offset}({'X7'}) {vertex_addr} 0 8")
        kv_map_tran.writeAction(f"sli {src_vid} {temp_reg} {int(log2(VERTEX_STRUCT_SIZE * WORD_SIZE))}")
        kv_map_tran.writeAction(f"add {vertex_addr} {temp_reg} {vertex_addr}")
        kv_map_tran.writeAction(f"send_dmlm_ld {vertex_addr} {map_evw} {VERTEX_STRUCT_SIZE}")
        if self.debug_flag:
            kv_map_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.kv_map_ev_label}] Read vid=%ld struct from DRAM addr=%lu(0x%lx) ' {'X0'} {src_vid} {vertex_addr} {vertex_addr}")
        kv_map_tran.writeAction(f"movir {pending_ret} {2}")
        kv_map_tran.writeAction(f"evlb {map_evw} {self.wr_nlist_ev_label}")
        kv_map_tran.writeAction(f"yield")

        '''
        Get neighbor list offset of the source vertex.
        X8:     src vertex id.
        X9:     offset.
        '''
        cache_ret_tran = self.state.writeTransition("eventCarry", self.state, self.state, self.cache_return_ev_label)
        if self.debug_flag:
            cache_ret_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.cache_return_ev_label}] Event <get_nlist_offset>" + 
                                       f" Cache returns src_id=%ld offset=%ld. edge (%ld, %ld) pending_return=%ld ' {'X0'} {'X8'} {'X9'} {src_vid} {dst_vid} {pending_ret}")
        cache_ret_tran.writeAction(f"subi {'X9'} {nlist_offset} {1}")
        cache_ret_tran.writeAction(f"sli {nlist_offset} {nlist_offset} {LOG2_WORD_SIZE}")
        cache_ret_tran.writeAction(f"subi {pending_ret} {pending_ret} 1")
        cache_ret_tran.writeAction(f"bnei {pending_ret} 0 {continue_label}")
        cache_ret_tran.writeAction(f"sendr_wcont {map_evw} {'X1'} {src_vid} {nlist_offset}")
        cache_ret_tran.writeAction(f"{continue_label}: yield")
        
        '''
        Read source vertex structure from DRAM.
        X8:     degree
        X9:     orig_vid
        X10:    vid
        X11:    neighbors
        X12:    distance
        X13:    parent
        X14:    offset
        X15:    padding1
        '''
        read_v_ret_tran = self.state.writeTransition("eventCarry", self.state, self.state, self.get_vertex_ev_label)
        if self.debug_flag:
            read_v_ret_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.get_vertex_ev_label}] Event <get_vertex_struct> vid=%ld struct return from addr=%lu(0x%lx): " + 
                                        f"vid=%ld nlist_addr=%li(0x%lx). pending_return=%ld ' {'X0'} {src_vid} {'X3'} {'X3'} {'X10'} {'X11'} {'X11'} {pending_ret}")
        read_v_ret_tran.writeAction(f"addi {'X11'} {nlist_addr} 0")
        read_v_ret_tran.writeAction(f"subi {pending_ret} {pending_ret} 1")
        read_v_ret_tran.writeAction(f"bnei {pending_ret} 0 {continue_label}")
        read_v_ret_tran.writeAction(f"sendr_wcont {map_evw} {'X1'} {src_vid} {nlist_addr}")
        read_v_ret_tran.writeAction(f"{continue_label}: yield")
        
        '''
        Finish read the vertex and get the neighbor list offset.
        '''
        wr_nlist_tran = self.state.writeTransition("eventCarry", self.state, self.state, self.wr_nlist_ev_label)
        wr_nlist_tran.writeAction(f"add {nlist_addr} {nlist_offset} {nlist_addr}")
        if self.debug_flag:
            wr_nlist_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.wr_nlist_ev_label}] Event <write_dst_to_dram> edge (%ld, %ld) src_vid=%ld nlist_addr=%lu(0x%lx) " + 
                                      f"nlist_offset=%ld dst_vid=%ld' {'X0'} {src_vid}  {dst_vid}  {src_vid} {nlist_addr} {nlist_addr} {nlist_offset} {dst_vid}")
        wr_nlist_tran.writeAction(f"evlb {map_evw} {self.wr_nlist_ack_ev_label}")
        wr_nlist_tran.writeAction(f"sendr_dmlm {nlist_addr} {map_evw} {dst_vid}")
        wr_nlist_tran.writeAction(f"yield")
        
        '''
        Write the destination vertex ID to source vertex's neighbor list.
        '''       
        wr_ack_tran = self.state.writeTransition("eventCarry", self.state, self.state, self.wr_nlist_ack_ev_label)
        if self.debug_flag:
            wr_ack_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.wr_nlist_ack_ev_label}] Event <write_edge_ack_from_dram> write back " + 
                                            f"edge (%ld, %ld) to DRAM addr=%lu(0x%lx) ' {'X0'} {src_vid} {dst_vid} {'X8'} {'X8'}")
        wr_ack_tran.writeAction(f"evlb {map_evw} {self.kv_map_return_ev_label}")
        wr_ack_tran.writeAction(f"sendr_wcont {map_evw} {'X2'} {src_vid} {dst_vid}")
        wr_ack_tran.writeAction(f"yield")
        
        
    def cache_combine_func(self, tran: EFAProgram.Transition, key: str, values: list, cached_values: list, result_regs: list, scratch: list, combine_fail_label: str, label_prefix: str):
        '''
        Default combine function.
        Parameters:
            tran:               EFAProgram.Transition
            key:                Register name of the key to be updated
            values:             list of Register names of the values to be updated. List length equals to value_size.
            cached_values:      list of Register names of the cached values. List length equals to value_size.
            result_regs:        list of Register names for storing the combined results. List length equals to value_size.
            combine_fail_label: Branch label for failure.
            label_prefix:       Prefix for the branch labels. 
        '''
        
        for i in range(len(values)):
            tran.writeAction(f"add {values[i]} {cached_values[i]} {result_regs[i]}")
            if self.debug_flag:
                tran.writeAction(f"print '[DEBUG][NWID %ld][combing_func] key %ld combine result value %ld' {'X0'} {key} {result_regs[i]}")

@efaProgram
def GenAddNeighborsEFA(efa: EFAProgram):
    BuildNlist(efa=efa)
    return efa