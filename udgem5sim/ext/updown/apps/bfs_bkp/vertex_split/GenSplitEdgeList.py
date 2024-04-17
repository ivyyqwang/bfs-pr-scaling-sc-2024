from linker.EFAProgram import EFAProgram, efaProgram
from KVMSRMachineConfig import *
from Macro import *
from libraries.ScalableHashTable.linkable.sht_ext_call_macros import SHTExt as SHT
from libraries.UDMapShuffleReduce.linkable.LinkableKVMapShuffleReduceTPL import UDKeyValueMapShuffleReduceTemplate
from libraries.UDMapShuffleReduce.utils.OneDimArrayKeyValueSet import OneDimKeyValueSet, MaskedOneDimKeyValueSet
from libraries.UDMapShuffleReduce.utils.IntermediateKeyValueSet import IntermediateKeyValueSet
from Config import *

class EdgeListSplit:
    
    def __init__(self, efa: EFAProgram):
        
        self.task   = 'edge_split'
        self.efa    = efa
        self.efa.code_level = 'machine'
        self.state  = efa.State()
        efa.add_initId(self.state.state_id)
        
        self.send_buffer_offset     = SEND_BUFFER_OFFSET
        
        self.split_v_sht_offset     = SPLIT_V_SHT_OFFSET
        
        self.debug_flag             = DEBUG_FLAG
                
        self.__gen_ev_labels()
        self.__gen_udkvmsr()
        self.__gen_init()
        self.__gen_edge_split()
        self.__gen_count_degree()
        
    def __gen_udkvmsr(self):
            
        self.udkvmsr = UDKeyValueMapShuffleReduceTemplate(efa=self.efa, task_name=self.task, meta_data_offset=UDKVMSR_LM_OFFSET, debug_flag=self.debug_flag)
        
        self.udkvmsr.set_input_kvset(OneDimKeyValueSet(f"{self.task}_input_kvset", element_size=EDGE_STRUCT_SIZE))
        self.udkvmsr.set_intermediate_kvset(IntermediateKeyValueSet(f"{self.task}_intermediate_kvset", key_size=1, value_size=1))
        self.udkvmsr.set_output_kvset(MaskedOneDimKeyValueSet(f"{self.task}_output_kvset", element_size=VERTEX_STRUCT_SIZE, mask='10000000'))
        
        self.udkvmsr.set_max_thread_per_lane(max_map_th_per_lane=MAX_EDGE_SPLIT_MAP_THREADS, max_reduce_th_per_lane=MAX_EDGE_SPLIT_REDUCE_THREADS)
        self.udkvmsr.setup_cache(cache_offset=KVMSR_CACHE_OFFSET, entry_size=KVMSR_CAHCE_ENTRY_SIZE, num_entries=KVMSR_CACHE_NUM_ENTRIES)
        
        self.udkvmsr.generate_udkvmsr_task()

        
    def __gen_ev_labels(self):
        
        self.edge_split_entry_ev_label  = get_event_label(self.task, 'edge_split_entry_event')
        self.edge_split_term_ev_label   = get_event_label(self.task, 'edge_split_terminate_event')
        
                
        self.kv_map_ev_label        = get_event_label(self.task, 'kv_map')
        self.get_split_vid_ev_label = get_event_label(self.task, 'get_split_vid')
        self.put_split_vid_ev_label = get_event_label(self.task, 'put_split_vid')
        self.wr_edge_ack_ev_label   = get_event_label(self.task, 'write_edge_ack_from_dram')
        
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
        
        '''
        Vertex split entry event.
        X8:     partition array address
        X9:     number of partitions per lane
        X10:    number of lanes
        X11:    edge list base address
        X12:    edge list array size
        X13:    vertex list base address
        X14:    vertex list array size
        '''
        entry_tran = self.state.writeTransition("eventCarry", self.state, self.state, self.edge_split_entry_ev_label)
        if self.debug_flag:
            entry_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.edge_split_entry_ev_label}] Event <edge_split_entry> ev_word=%lu " + 
                                                f"partition=%lu(0x%lx) num_partitions_per_lane=%ld num_lanes=%ld' {'X0'} {'EQT'} {'X8'} {'X8'} {'X9'} {'X10'}")
            entry_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.edge_split_entry_ev_label}] edge_list=%lu(0x%lx) edge_list_size=%ld" + 
                                                f" vertex_list=%lu(0x%lx) vertex_list_size=%ld' {'X0'} {'X11'} {'X11'} {'X12'} {'X13'} {'X13'} {'X14'}")
        entry_tran.writeAction(f"addi {'X7'} {send_buffer} {KVMSR_SEND_BUFFER_OFFSET}")
        entry_tran.writeAction(f"movrl {'X8'} 0({send_buffer}) 0 8")
        entry_tran.writeAction(f"movrl {'X9'} 8({send_buffer}) 0 8")
        entry_tran.writeAction(f"movrl {'X10'} 16({send_buffer}) 0 8")
        entry_tran.writeAction(f"addi {'X7'} {lm_addr} {KVMSR_INPUT_OFFSET}")
        entry_tran.writeAction(f"movrl {lm_addr} 24({send_buffer}) 0 8")
        if self.debug_flag:
            entry_tran.writeAction(f"print '[DEBUG][NWID %d] Save input key value set base pointer %lu(0x%lx) and " + 
                                          f"size %ld to scratchpad addr %ld(0x%lx)' {'X0'} {'X11'} {'X11'} {'X12'} {lm_addr} {lm_addr}")
        entry_tran.writeAction(f"movrl {'X11'} 0({lm_addr}) 1 8")
        entry_tran.writeAction(f"movrl {'X12'} 0({lm_addr}) 1 8")
        entry_tran.writeAction(f"addi {'X7'} {lm_addr} {KVMSR_OUTPUT_OFFSET}")
        entry_tran.writeAction(f"movrl {lm_addr} 32({send_buffer}) 0 8")
        if self.debug_flag:
            entry_tran.writeAction(f"print '[DEBUG][NWID %d] Save output key value set base pointer %lu(0x%lx) and " + 
                                          f"size %ld to scratchpad addr %ld(0x%lx)' {'X0'} {'X13'} {'X13'} {'X14'} {lm_addr} {lm_addr}")
        entry_tran.writeAction(f"movrl {'X13'} 0({lm_addr}) 1 8")
        entry_tran.writeAction(f"movrl {'X14'} 0({lm_addr}) 1 8")
        set_ev_label(entry_tran, temp_evw, self.udkvmsr_entry_ev_label, new_thread=True)
        entry_tran.writeAction(f"send_wret {temp_evw} {self.edge_split_term_ev_label} {send_buffer} {UDKVMSR_INIT_NUM_OPS} {temp_reg}")
        entry_tran.writeAction(f"mov_imm2reg {temp_reg} 0")
        entry_tran.writeAction(f"addi {'X7'} {lm_addr} {TOP_FLAG_OFFSET}")
        entry_tran.writeAction(f"move {temp_reg} {0}({lm_addr}) 0 8")
        entry_tran.writeAction(f"yield")
        
        '''
        UDKVMSR program finishes, signal the top.
        X8:     number of reduce tasks processed (totoal number of edges)
        '''
        term_tran = self.state.writeTransition("eventCarry", self.state, self.state, self.edge_split_term_ev_label)
        # UpDown program finishes, Signal the top 
        term_tran.writeAction(f"movir {temp_reg} 1")
        term_tran.writeAction(f"movrl {temp_reg} {0}({lm_addr}) 1 8")
        term_tran.writeAction(f"addi {'X7'} {send_buffer} {SEND_BUFFER_OFFSET}")
        term_tran.writeAction(f"movrl {'X8'} 0({send_buffer}) 0 8")
        term_tran.writeAction("yield_terminate")
        
    def __gen_edge_split(self):
        
        src_vid         = 'X16'
        dst_vid         = 'X17'
        ori_src_vid     = 'X18'
        pending_ret     = 'X19'
        hash_seed       = 'X20'
        split_vid       = 'X21'
        buffer_addr     = 'X22'
        edge_addr       = 'X23'
        split_flag      = 'X24'
        temp_reg        = 'X25'
        map_evw         = 'X26'
        
        scratch         = ["X29", "X30", "X31"]
        
        '''
        Read the edge.
        X8:     src vertex ID
        X9:     dst vertex ID
        X10:    edge address
        '''
        kv_map_tran = self.state.writeTransition("eventCarry", self.state, self.state, self.kv_map_ev_label)
        if self.debug_flag:
            kv_map_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.kv_map_ev_label}] Event <kv_map> Split edge (%ld, %ld) " + 
                                          f"at addr = %lu(0x%lx)' {'X0'} {'X8'} {'X9'} {'X10'} {'X10'}")
        kv_map_tran.writeAction(f"movir {temp_reg} {self.split_v_sht_offset}")
        kv_map_tran.writeAction(f"addi {'X2'} {map_evw} 0")
        kv_map_tran.writeAction(f"evlb {map_evw} {self.get_split_vid_ev_label}")
        kv_map_tran.writeAction(f"addi {'X8'} {src_vid} 0")
        kv_map_tran.writeAction(f"addi {'X9'} {dst_vid} 0")
        SHT.get_wcont(tran=kv_map_tran, ret=map_evw, tmp_reg=scratch[0], desc_lm_offset_reg=temp_reg, key_reg=src_vid)
        SHT.get_wcont(tran=kv_map_tran, ret=map_evw, tmp_reg=scratch[0], desc_lm_offset_reg=temp_reg, key_reg=dst_vid)
        kv_map_tran.writeAction(f"movir {pending_ret} {2}")
        kv_map_tran.writeAction(f"addi {'X10'} {edge_addr} 0")
        kv_map_tran.writeAction(f"hash {edge_addr} {hash_seed}")
        kv_map_tran.writeAction(f"movir {split_flag} {0}")
        kv_map_tran.writeAction(f"addi {'X8'} {ori_src_vid} 0")
        kv_map_tran.writeAction(f"yield")

        '''
        Get vertex ID from SHT, check if the vertex needs to be split.
        X8:     key = vertex ID
        X9:     Status of get.
        X10:    split base vertex ID (if key is presented)
        X11:    number of split vertices (if key is presented)
        '''
        get_ret_key = 'X8'
        get_status  = 'X9'
        base_vid    = 'X10'
        num_splits  = 'X11'
        
        no_split_label      = "not_split"
        src_ret_label       = "src_vertex_return"
        finish_split_label  = "finish_split_the_edge"
        save_edge_label     = "save_split_edge_to_dram"
        split_vertex_tran = self.state.writeTransition("eventCarry", self.state, self.state, self.get_split_vid_ev_label)
        if self.debug_flag:
            split_vertex_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.get_split_vid_ev_label}] Event <get_split_vid> " + 
                                          f"key=%ld status=%ld' {'X0'} {get_ret_key} {get_status}")
        split_vertex_tran.writeAction(f"beqi {get_status} 0 {no_split_label}")
        if self.debug_flag:
            split_vertex_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.get_split_vid_ev_label}] Vertex %ld is a high degree vertex, " + 
                                          f"base_split_vid=%ld num_split=%ld' {'X0'} {get_ret_key} {base_vid} {num_splits}")
        # Vertex is identified as a high degree vertex, split it.
        split_vertex_tran.writeAction(f"movir {split_flag} {FLAG}")
        split_vertex_tran.writeAction(f"hash {get_ret_key} {hash_seed}")
        split_vertex_tran.writeAction(f"sri {hash_seed} {hash_seed} {1}") # Get a positive pseudo-random value.
        split_vertex_tran.writeAction(f"mod {hash_seed} {num_splits} {split_vid}")
        split_vertex_tran.writeAction(f"add {split_vid} {base_vid} {split_vid}")
        # Check if the vertex is the source vertex or the destination vertex.
        split_vertex_tran.writeAction(f"beq {get_ret_key} {src_vid} {src_ret_label}")
        # Update the vid of the destination vertex.
        if self.debug_flag:
            split_vertex_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.get_split_vid_ev_label}] Split destination vertex %ld, " + 
                                          f"new vid = %ld, edge_addr=%lu(0x%lx)' {'X0'} {get_ret_key} {split_vid} {edge_addr} {edge_addr}")
        split_vertex_tran.writeAction(f"addi {split_vid} {dst_vid} 0")
        split_vertex_tran.writeAction(f"subi {pending_ret} {pending_ret} 1")
        split_vertex_tran.writeAction(f"beqi {pending_ret} 0 {finish_split_label}")
        split_vertex_tran.writeAction(f"yield")
        # Update the vid of the source vertex.
        split_vertex_tran.writeAction(f"{src_ret_label}: addi {split_vid} {src_vid} 0")
        if self.debug_flag:
            split_vertex_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.get_split_vid_ev_label}] Split source vertex %ld, " + 
                                          f"new vid = %ld, edge_addr=%lu(0x%lx)' {'X0'} {get_ret_key} {split_vid} {edge_addr} {edge_addr}")
        split_vertex_tran.writeAction(f"subi {pending_ret} {pending_ret} 1")
        split_vertex_tran.writeAction(f"beqi {pending_ret} 0 {finish_split_label}")
        split_vertex_tran.writeAction(f"yield")
        # Vertex not found in SHT, return the original vertex ID.
        split_vertex_tran.writeAction(f"{no_split_label}: subi {pending_ret} {pending_ret} 1")
        split_vertex_tran.writeAction(f"beqi {pending_ret} 0 {finish_split_label}")
        # if self.debug_flag or True:
        if self.debug_flag:
            split_vertex_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.get_split_vid_ev_label}] Vid = %ld is not high degree vertex, " + 
                                          f"skip spliting edge (%ld, %ld) at addr=%lu(0x%lx)' {'X0'} {get_ret_key} {src_vid} {dst_vid} {edge_addr} {edge_addr}")
        split_vertex_tran.writeAction(f"yield")
        
        # Finish splitting the edge, emit degree count 1 for the source vertex to the reduce.
        set_ev_label(split_vertex_tran, scratch[0], self.kv_map_emit_ev_label, new_thread=True, label=finish_split_label)
        split_vertex_tran.writeAction(f"movir {temp_reg} {1}")
        split_vertex_tran.writeAction(f"sendr_wcont {scratch[0]} {'X2'} {src_vid} {temp_reg}")
        # split_vertex_tran.writeAction(f"sendr_wcont {scratch[0]} {'X2'} {ori_src_vid} {temp_reg}")
        if self.debug_flag:
            split_vertex_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.get_split_vid_ev_label}] Emit degree count 1 for " + 
                                          f"vertex %ld (original id = %ld)' {'X0'} {src_vid} {ori_src_vid}")
        split_vertex_tran.writeAction(f"beqi {split_flag} {FLAG} {save_edge_label}")
        split_vertex_tran.writeAction(f"evlb {map_evw} {self.kv_map_return_ev_label}")
        split_vertex_tran.writeAction(f"sendr_wcont {map_evw} {'X2'} {src_vid} {dst_vid}")
        split_vertex_tran.writeAction(f"yield")
        # Vertex is split, update the edge.
        split_vertex_tran.writeAction(f"{save_edge_label}: evlb {map_evw} {self.wr_edge_ack_ev_label}")
        split_vertex_tran.writeAction(f"sendr2_dmlm {edge_addr} {map_evw} {src_vid} {dst_vid}")
        # if self.debug_flag or True:
        if self.debug_flag:
            split_vertex_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.get_split_vid_ev_label}] Save split edge (%ld, %ld) at " + 
                                          f"addr=%lu(0x%lx)' {'X0'} {src_vid} {dst_vid} {edge_addr} {edge_addr}")
        split_vertex_tran.writeAction(f"yield")
        
        fin_split_edge_tran = self.state.writeTransition("eventCarry", self.state, self.state, self.wr_edge_ack_ev_label)
        if self.debug_flag:
            fin_split_edge_tran.writeAction(f"print '[DEBUG][NWID %ld][{self.wr_edge_ack_ev_label}] Event <write_edge_ack_from_dram> write back " + 
                                            f"edge (%ld, %ld) at addr %lu(0x%lx)' {'X0'} {src_vid} {dst_vid} {'X8'} {'X8'}")
        fin_split_edge_tran.writeAction(f"evlb {map_evw} {self.kv_map_return_ev_label}")
        fin_split_edge_tran.writeAction(f"sendr_wcont {map_evw} {'X1'} {src_vid} {dst_vid}")
        fin_split_edge_tran.writeAction(f"yield")

    def __gen_count_degree(self):

        reduce_tran = self.state.writeTransition("eventCarry", self.state, self.state, self.kv_reduce_ev_label)
        
        '''
        Event:      Reduce task. Combine the incoming intermediate key-value pair with the one in SHT using the kv_combine provided by UDKVMSR.
        Operands:   Intermediate key-value pair
        '''
        temp_evw    = "X16"
        return_evw  = "X17"
        if self.debug_flag:
            reduce_tran.writeAction(f"print '[DEBUG][NWID %d][{self.kv_reduce_ev_label}] Event <{self.task}::kv_reduce> Add count %ld to vid = %ld ' {'X0'} {'X9'} {'X8'}")
        '''
        Call kv_combine to combine the intermediate key-value pair with the output key-value pair, using the customized combine function (defined in kv_combine_op).
        kv_combine is a functionality provided by UDKVMSR to do atomic update of the output key-value pair.
        '''
        set_ev_label(reduce_tran, temp_evw, self.kv_combine_ev_label)
        set_ev_label(reduce_tran, return_evw, self.kv_red_return_ev_label)
        reduce_tran.writeAction(f"sendops_wcont {temp_evw} {return_evw} {'X8'} 2")
        reduce_tran.writeAction("yield")
        
        return 

@efaProgram
def GenSplitEdgeListEFA(efa: EFAProgram):
    EdgeListSplit(efa=efa)
    return efa