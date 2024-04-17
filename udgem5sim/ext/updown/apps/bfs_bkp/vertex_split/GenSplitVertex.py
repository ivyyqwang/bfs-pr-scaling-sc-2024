from linker.EFAProgram import EFAProgram, efaProgram
from KVMSRMachineConfig import *
from Macro import *
from libraries.ScalableHashTable.linkable.sht_ext_call_macros import SHTExt
from libraries.UDMapShuffleReduce.linkable.LinkableGlobalSync import Broadcast
from libraries.UDMapShuffleReduce.linkable.LinkableKVMapShuffleReduceTPL import UDKeyValueMapShuffleReduceTemplate
from libraries.UDMapShuffleReduce.utils.SHTKeyValueSet import SingleWordSHTKeyValueSet
from libraries.UDMapShuffleReduce.utils.OneDimArrayKeyValueSet import OneDimKeyValueSet
from Config import *
from libraries.LMStaticMaps.LMStaticMap import *

class VertexSplit:
    
    def __init__(self, efa: EFAProgram):
        
        self.task   = 'split_vertex'
        self.efa    = efa
        self.efa.code_level = 'machine'
        self.state  = efa.State()
        efa.add_initId(self.state.state_id)
        
        self.send_buffer_offset     = SEND_BUFFER_OFFSET
        self.vid_alloc_evw_offset   = KVMSR_OUTPUT_OFFSET
        self.max_split_deg_offset   = self.vid_alloc_evw_offset + WORD_SIZE
        
        self.split_v_sht_offset     = SPLIT_V_SHT_OFFSET
        self.high_deg_sht_offset    = HIGH_DEG_SHT_OFFSET
        
        self.debug_flag = DEBUG_FLAG
                
        self.broadcast  = Broadcast(state=self.state, identifier=self.task, debug_flag=self.debug_flag)
        
        self.__gen_ev_labels()
        self.__gen_udkvmsr()
        self.__gen_init()
        self.__gen_vid_allocator()
        self.__gen_vertex_split()
        
    def __gen_udkvmsr(self):
            
        self.udkvmsr = UDKeyValueMapShuffleReduceTemplate(efa=self.efa, task_name=self.task, meta_data_offset=UDKVMSR_LM_OFFSET, debug_flag=self.debug_flag)
        
        self.udkvmsr.set_input_kvset(SingleWordSHTKeyValueSet(f"{self.task}_input_kvset"))
        
        self.udkvmsr.set_output_kvset(OneDimKeyValueSet(f"{self.task}_argument", element_size=1, metadata_size=2))
        
        self.udkvmsr.set_max_thread_per_lane(max_map_th_per_lane=MAX_VERTEX_SPLIT_MAP_THREADS)
        
        self.udkvmsr.generate_udkvmsr_task()
        
    def __gen_ev_labels(self):
        
        self.vertex_split_entry_ev_label    = get_event_label(self.task, 'entry_event')
        self.init_udkvmsr_ev_label          = get_event_label(self.task, 'init_udkvmsr_program')
        self.udkvmsr_return_ev_label        = get_event_label(self.task, 'udkvmsr_return_event')
        self.vertex_split_term_ev_label     = get_event_label(self.task, 'terminate_event')
        
        self.udkvmsr_entry_ev_label         = get_event_label(self.task, 'map_shuffle_reduce')
        
        self.init_vid_allocator_ev_label    = get_event_label(self.task, 'init_vid_allocator')
        self.alloc_vid_ev_label             = get_event_label(self.task, 'alloc_vid')
        self.term_allocator_ev_label        = get_event_label(self.task, 'terminate_allocator')
        
        self.kv_map_ev_label        = get_event_label(self.task, 'kv_map')
        self.split_vertex_ev_label  = get_event_label(self.task, 'split_vertex')
        self.add_split_ret_ev_label = get_event_label(self.task, 'add_split_return')
        self.kv_map_return_ev_label = get_event_label(self.task, 'kv_map_return')
    
    def __gen_init(self):
        
        send_buffer = 'X16'
        lm_addr     = 'X17'
        temp_evw    = 'X18'
        temp_reg    = 'X19'
        front_evw   = 'X21'
        num_lanes   = 'X23'
        max_split_deg = 'X26'
        
        '''
        Vertex split entry event.
        X8:     partition array address
        X9:     number of partitions per lane
        X10:    number of lanes
        X11:    max vertex id
        X12:    max split degree
        '''
        split_entry_tran = self.state.writeTransition("eventCarry", self.state, self.state, self.vertex_split_entry_ev_label)
        if self.debug_flag:
            split_entry_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.vertex_split_entry_ev_label}] Event <vertex_split_entry> ev_word=%lu partition=%lu(0x%lx) " + 
                                                f"num_partitions_per_lane=%ld num_lanes=%ld' {'X0'} {'EQT'} {'X8'} {'X8'} {'X9'} {'X10'}")
            split_entry_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.vertex_split_entry_ev_label}] max_vid = %ld max_split_degree = %ld' {'X0'} {'X11'} {'X12'}")
        set_ev_label(split_entry_tran, temp_evw, self.init_vid_allocator_ev_label, new_thread=True)
        split_entry_tran.writeAction(f"subi {'X10'} {temp_reg} 1")
        set_nwid(split_entry_tran, temp_evw, temp_reg, src_ev=temp_evw)
        split_entry_tran.writeAction(f"sendr_wret {temp_evw} {self.init_udkvmsr_ev_label} {'X11'} {'X11'} {temp_reg}")
        split_entry_tran.writeAction(f"addi {'X10'} {num_lanes} 0")
        split_entry_tran.writeAction(f"addi {'X12'} {max_split_deg} 0")
        split_entry_tran.writeAction(f"addi {'X7'} {send_buffer} {KVMSR_SEND_BUFFER_OFFSET}")
        split_entry_tran.writeAction(f"movrl {'X8'} 0({send_buffer}) 0 8")
        split_entry_tran.writeAction(f"movrl {'X9'} 8({send_buffer}) 0 8")
        split_entry_tran.writeAction(f"movrl {'X10'} 16({send_buffer}) 0 8")
        split_entry_tran.writeAction(f"addi {'X7'} {lm_addr} {self.high_deg_sht_offset}")
        split_entry_tran.writeAction(f"movrl {lm_addr} 24({send_buffer}) 0 8")
        if self.debug_flag:
            split_entry_tran.writeAction(f"print '[DEBUG][NWID %d] Save input high degree SHT descriptor " + 
                                          f"to scratchpad addr %lu(0x%lx)' {'X0'} {lm_addr} {lm_addr}")
        split_entry_tran.writeAction(f"addi {'X7'} {lm_addr} {self.vid_alloc_evw_offset}")
        split_entry_tran.writeAction(f"movrl {lm_addr} 32({send_buffer}) 0 8")
        split_entry_tran.writeAction(f"movrl {max_split_deg} 8({lm_addr}) 0 8")
        split_entry_tran.writeAction(f"yield")
        
        '''
        Finish initialization, send the event to start the UDKVMSR program.
        X8:     vertex id allocator event word
        '''
        init_udkvmsr_tran = self.state.writeTransition("eventCarry", self.state, self.state, self.init_udkvmsr_ev_label)
        init_udkvmsr_tran.writeAction(f"addi {'X8'} {front_evw} 0")
        init_udkvmsr_tran.writeAction(f"movrl {front_evw} 0({lm_addr}) 0 8")
        # init_udkvmsr_tran.writeAction(f"addi {'X7'} {send_buffer} {KVMSR_SEND_BUFFER_OFFSET}")
        set_ev_label(init_udkvmsr_tran, temp_evw, self.udkvmsr_entry_ev_label, new_thread=True)
        init_udkvmsr_tran.writeAction(f"send_wret {temp_evw} {self.udkvmsr_return_ev_label} {send_buffer} 5 {temp_reg}")
        init_udkvmsr_tran.writeAction(f"mov_imm2reg {temp_reg} 0")
        init_udkvmsr_tran.writeAction(f"addi {'X7'} {lm_addr} {TOP_FLAG_OFFSET}")
        init_udkvmsr_tran.writeAction(f"move {temp_reg} {0}({lm_addr}) 0 8")
        init_udkvmsr_tran.writeAction(f"yield")
        
        '''
        UDKVMSR returns, send the event to terminate the vertex id allocator.
        '''
        udkvmsr_return_tran = self.state.writeTransition("eventCarry", self.state, self.state, self.udkvmsr_return_ev_label)
        udkvmsr_return_tran.writeAction(f"evlb {front_evw} {self.term_allocator_ev_label}")
        udkvmsr_return_tran.writeAction(f"sendr_wret {front_evw} {self.vertex_split_term_ev_label} {front_evw} {'X2'} {temp_reg}")
        udkvmsr_return_tran.writeAction(f"yield")
        
        '''
        Vertex id allocator terminates, return to top with the highest vertex id.
        X8:     vertex id allocator latest vid
        '''
        term_tran = self.state.writeTransition("eventCarry", self.state, self.state, self.vertex_split_term_ev_label)
        # UpDown program finishes, Signal the top 
        term_tran.writeAction(f"addi {'X7'} {lm_addr} {TOP_FLAG_OFFSET}")
        term_tran.writeAction(f"mov_imm2reg {temp_reg} 1")
        term_tran.writeAction(f"movrl {temp_reg} {0}({lm_addr}) 1 8")
        term_tran.writeAction(f"movrl {'X8'} 0({lm_addr}) 0 8")
        if self.debug_flag:
            term_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.vertex_split_term_ev_label}] Finish splitting vertices, new max vertex id = %ld' {'X0'} {'X8'}")
        term_tran.writeAction("yield_terminate")
        
    def __gen_vid_allocator(self):
        
        curr_vid    = 'X16'
        alloc_evw   = 'X17'
        
        '''
        Initialize the vertex ID allocator.
        X8:     base vertex ID, start the allocation from this ID
        '''
        init_allocator_tran = self.state.writeTransition("eventCarry", self.state, self.state, self.init_vid_allocator_ev_label)
        if self.debug_flag:
            init_allocator_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.init_vid_allocator_ev_label}] Event <init_vid_allocator> base_vid=%ld' {'X0'} {'EQT'} {'X8'}")
        init_allocator_tran.writeAction(f"addi {'X8'} {curr_vid} 0")
        set_ev_label(init_allocator_tran, alloc_evw, self.alloc_vid_ev_label)
        init_allocator_tran.writeAction(f"sendr_wcont {'X1'} {alloc_evw} {alloc_evw} {'X2'}")
        init_allocator_tran.writeAction(f"yield")
        
        '''
        Request new vertex IDs.
        X8:      number of vertex IDs to allocate
        '''
        alloc_vid_tran = self.state.writeTransition("eventCarry", self.state, self.state, self.alloc_vid_ev_label)
        if self.debug_flag:
            alloc_vid_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.alloc_vid_ev_label}] Event <allocate_vid> ev_word=%lu " + 
                                       f"num_vids=%ld curr_vid=%ld' {'X0'} {'EQT'} {'X8'} {curr_vid}")
        alloc_vid_tran.writeAction(f"sendr_wcont {'X1'} {alloc_evw} {curr_vid} {'X8'}")
        alloc_vid_tran.writeAction(f"add {'X8'} {curr_vid} {curr_vid}")
        alloc_vid_tran.writeAction(f"yield")
        
        term_alloc_tran = self.state.writeTransition("eventCarry", self.state, self.state, self.term_allocator_ev_label)
        if self.debug_flag:
            term_alloc_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.term_allocator_ev_label}] Event <terminate_allocator>' {'X0'} {'EQT'}")
        term_alloc_tran.writeAction(f"sendr_wcont {'X1'} {alloc_evw} {curr_vid} {'X8'}")
        term_alloc_tran.writeAction(f"yieldt")
        
    
    def __gen_vertex_split(self):
        
        vid         = 'X16'
        split_vid   = 'X17'
        max_deg     = 'X18'
        num_splits  = 'X19'
        temp_evw    = 'X20'
        temp_val    = 'X21'
        buffer_addr     = 'X22'
        max_split_vid   = 'X23'
        pending_return  = 'X24'
        
        scratch         = ["X29", "X30", "X31"]
        
        '''
        Read the vertex ID and the estimated degree of the vertex to be split.
        X8:     vertex ID
        X9:     estimated degree
        '''
        kv_map_tran = self.state.writeTransition("eventCarry", self.state, self.state, self.kv_map_ev_label)
        kv_map_tran.writeAction(f"movlr {self.max_split_deg_offset}({'X7'}) {max_deg} 8 8")
        kv_map_tran.writeAction(f"div {'X9'} {max_deg} {num_splits}")
        kv_map_tran.writeAction(f"addi {num_splits} {num_splits} 1")
        kv_map_tran.writeAction(f"movlr {self.vid_alloc_evw_offset}({'X7'}) {temp_evw} 0 8")
        if self.debug_flag:
            kv_map_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.kv_map_ev_label}] Event <kv_map> ev_word=%lu vid=%ld est_deg=%ld num_splits=%ld' {'X0'} {'EQT'} {'X8'} {'X9'} {num_splits}")
        # Get split vertex IDs from the allocator.
        kv_map_tran.writeAction(f"sendr_wret {temp_evw} {self.split_vertex_ev_label} {num_splits} {num_splits} {scratch[0]}")
        kv_map_tran.writeAction(f"addi {'X8'} {vid} 0")
        kv_map_tran.writeAction(f"yield")
        
        '''
        Vertex id allocator returns with split vertex ids.
        X8:     base split vertex ID
        X9:     number of split vertices
        '''
        split_loop_label = "split_loop"
        break_loop_label = "break_loop"
        split_vertex_tran = self.state.writeTransition("eventCarry", self.state, self.state, self.split_vertex_ev_label)
        # if self.debug_flag or True:
        if self.debug_flag:
            split_vertex_tran.writeAction(f"print '[{self.split_vertex_ev_label}] Split ori_vid=%ld into %ld vertices starts from vid %ld' {vid} {'X9'} {'X8'}")
        split_vertex_tran.writeAction(f"addi {'X8'} {split_vid} 0")
        set_ev_label(split_vertex_tran, temp_evw, self.add_split_ret_ev_label)
        # Prepare the SHTExt call.
        split_vertex_tran.writeAction(f"movir {temp_val} {self.send_buffer_offset}")
        split_vertex_tran.writeAction(f"add {temp_val} {'X7'} {buffer_addr}")
        split_vertex_tran.writeAction(f"sli {temp_val} {temp_val} {32}")
        split_vertex_tran.writeAction(f"ori {temp_val} {temp_val} {self.split_v_sht_offset}")
        split_vertex_tran.writeAction(f"movrl {temp_val} 0({buffer_addr}) 0 8")
        # Add the original vertex (split base vid and number of split vertices) to the hash table.
        split_vertex_tran.writeAction(f"movrl {vid} {WORD_SIZE}({buffer_addr}) 0 8")
        split_vertex_tran.writeAction(f"movrl {split_vid} {WORD_SIZE*2}({buffer_addr}) 0 8")
        split_vertex_tran.writeAction(f"movrl {num_splits} {WORD_SIZE*3}({buffer_addr}) 0 8")
        SHTExt.update_wcont(tran=split_vertex_tran, ret=temp_evw, tmp_reg0=scratch[0], arg_lm_addr_reg=buffer_addr, num_val_words=SPLIT_V_SHT_VALUE_SIZE)
        # if self.debug_flag or True:
        if self.debug_flag:
            split_vertex_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.split_vertex_ev_label}] Add original vertex to the SHT vid=%ld " + 
                                          f"split_vid=%ld number of splits=%ld' {'X0'} {vid} {split_vid} {num_splits}")
        
        # Add the split vertices to the hash table.
        split_vertex_tran.writeAction(f"add {split_vid} {num_splits} {max_split_vid}")
        split_vertex_tran.writeAction(f"movrl {vid} {WORD_SIZE*2}({buffer_addr}) 0 8")
        split_vertex_tran.writeAction(f"sli {split_vid} {temp_val} {32}")
        split_vertex_tran.writeAction(f"add {temp_val} {max_split_vid} {temp_val}")
        split_vertex_tran.writeAction(f"movrl {temp_val} {WORD_SIZE*3}({buffer_addr}) 0 8")
        # if self.debug_flag or True:
        if self.debug_flag:
            split_vertex_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.split_vertex_ev_label}] Prepare split vertices SHT entry original_vid(val[0]) = %ld " + 
                                          f"val[1] = %lu' {'X0'} {vid} {temp_val}")
        split_vertex_tran.writeAction(f"{split_loop_label}: bge {split_vid} {max_split_vid} {break_loop_label}")
        split_vertex_tran.writeAction(f"movrl {split_vid} {WORD_SIZE}({buffer_addr}) 0 8")
        SHTExt.update_wcont(tran=split_vertex_tran, ret=temp_evw, tmp_reg0=scratch[0], arg_lm_addr_reg=buffer_addr, num_val_words=SPLIT_V_SHT_VALUE_SIZE)
        if self.debug_flag:
            split_vertex_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.split_vertex_ev_label}] Add split vertex = %ld to SHT val[0]=%ld val[1]=%ld' {'X0'} {split_vid} {vid} {temp_val}")
        split_vertex_tran.writeAction(f"addi {split_vid} {split_vid} 1")
        split_vertex_tran.writeAction(f"jmp {split_loop_label}")
        split_vertex_tran.writeAction(f"{break_loop_label}: addi {num_splits} {pending_return} 1")
        split_vertex_tran.writeAction(f"yield")
        
        '''
        SHTExt add vertex return.
        '''
        continue_label = "continue"
        add_split_ret_tran = self.state.writeTransition("eventCarry", self.state, self.state, self.add_split_ret_ev_label)
        if self.debug_flag:
            add_split_ret_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.add_split_ret_ev_label}] Event <add_split_return> ev_word=%lu " + 
                                           f"number of pending returns=%ld' {'X0'} {'EQT'} {pending_return}")
        add_split_ret_tran.writeAction(f"subi {pending_return} {pending_return} 1")
        add_split_ret_tran.writeAction(f"bnei {pending_return} 0 {continue_label}")
        if self.debug_flag:
            add_split_ret_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.add_split_ret_ev_label}] Finish adding all the vertices to the SHTExt vid=%ld" + 
                                           f"number of split vertices=%ld' {'X0'} {vid} {num_splits}")
        set_ev_label(add_split_ret_tran, temp_evw, self.kv_map_return_ev_label)
        add_split_ret_tran.writeAction(f"sendr_wcont {temp_evw} {'X2'} {vid} {num_splits}")
        add_split_ret_tran.writeAction(f"{continue_label}: yield")
        

@efaProgram
def GenVertexSplitEFA(efa: EFAProgram):
    VertexSplit(efa=efa)
    return efa