from typing import Callable
from linker.EFAProgram import efaProgram, EFAProgram

from libraries.UDMapShuffleReduce.linkable.LinkableKVMapShuffleReduceTPL import UDKeyValueMapShuffleReduceTemplate
from libraries.UDMapShuffleReduce.utils.SHTKeyValueSet import SHTKeyValueSet
from libraries.LMStaticMaps.LMStaticMap import *

class pga_do_all():
  # sht_desc_lm_offset = 0

  PGA_DESC_OFF_VERTEX = 0
  PGA_DESC_OFF_EDGE   = 32

  def __init__(self, 
               efa,
               task_name: str,
               do_all_desc_lm_offset: int,
              #  graph_desc_lm_offset: int,
               udkvmsr_meta_data_offset: int,
               send_buffer_offset: int,
               max_map_th_per_lane: int = 24,
               key_size: int = 1, value_size: int = 7,
               debug_flag: bool = True):
    '''
      Generate init_tran_vertex with f'{task_name}::pga_do_all_init_tran_vertex'
      Redirect the f'{task}::kv_map' to user_do_all_label
      User need to return to f'{task}::kv_map_return' by themselves
    '''
    self.efa = efa
    self.task_name = task_name

    self.do_all_desc_lm_offset    = do_all_desc_lm_offset
    # self.graph_desc_lm_offset     = graph_desc_lm_offset
    self.udkvmsr_meta_data_offset = udkvmsr_meta_data_offset
    self.send_buffer_offset       = send_buffer_offset
    # self.pga_desc_lm_offset       = self.graph_desc_lm_offset+self.sht_desc_lm_offset

    self.key_size   = key_size
    self.value_size = min(7, value_size)
    self.max_map_th_per_lane = max_map_th_per_lane

    self.debug_flag = debug_flag


    self.MSRSHT = UDKeyValueMapShuffleReduceTemplate(efa=self.efa,
                                                     task_name=self.task_name,
                                                     meta_data_offset=self.udkvmsr_meta_data_offset,
                                                     debug_flag=self.debug_flag)
    self.MSRSHT.set_input_kvset(SHTKeyValueSet(name=self.task_name+"_input_kvset",
                                               key_size=self.key_size,
                                               value_size=self.value_size, 
                                               argument_size=1) )
    # self.MSRSHT.in_kvset_meta_size = SHTKeyValueSet.SHT_DESC_SIZE + 1

    self.MSRSHT.set_max_thread_per_lane(max_map_th_per_lane=max_map_th_per_lane)

    self.MSRSHT.generate_udkvmsr_task()


    '''
    Entry event transition to be triggered by the top program. Updown program starts from here.
      operands
      X8:  Pointer to the partition array (64-bit DRAM address)
      X9:  PGA descriptor offset
      X10: Number of SHT buckets per lane
      X11: Number of lanes
      X12: Label of user defined do_all transation
    '''    
    continue_reg                    = "X1"
    event_reg                       = "X2"
    lm_base_reg                     = "X7"
    pointer_to_partition_array_reg  = "X8"
    pga_desc_lm_offset_reg          = "X9"
    num_sht_buckets_per_lane_reg    = "X10"
    num_lanes_reg                   = "X11"
    user_do_all_label_reg           = "X12"

    temp_reg                        = "X16"
    # lm_base_reg                     = "X17"
    send_buffer                     = "X18"
    lm_addr_reg                     = "X19"
    sht_addr_reg                    = "X20"
    ev_word_reg                     = "X21"


    init_tran_vertex = self.MSRSHT.state.writeTransition("eventCarry", self.MSRSHT.state, self.MSRSHT.state, f'{self.task_name}::do_all_vertex_init')
    if self.debug_flag:
      init_tran_vertex.writeAction(f"print '[DEBUG][NWID %d] Event <{f'{self.task_name}::do_all_vertex_init'}> ' {'X0'} ")
    # Move the pga desc to a reserverd scratchpad address and append the user defined do_all label to the end of the desc
    init_tran_vertex.writeAction(f"movir {lm_addr_reg}  {self.do_all_desc_lm_offset}")
    init_tran_vertex.writeAction(f"add   {lm_base_reg} {lm_addr_reg} {lm_addr_reg}")
    init_tran_vertex.writeAction(f"addi  {pga_desc_lm_offset_reg} {sht_addr_reg} {self.PGA_DESC_OFF_VERTEX}")
    init_tran_vertex.writeAction(f"add   {lm_base_reg} {sht_addr_reg} {sht_addr_reg}")
    for _ in range(SHTKeyValueSet.SHT_DESC_SIZE):
      init_tran_vertex.writeAction(f"movlr 0({sht_addr_reg}) {temp_reg} 1 8")
      init_tran_vertex.writeAction(f"movrl {temp_reg} 0({lm_addr_reg}) 1 8")
    init_tran_vertex.writeAction(f"movrl  {user_do_all_label_reg} 0({lm_addr_reg}) 0 8")

    # Move the UDKVMSR call parameters to a send buffer in scratchpad.
    init_tran_vertex.writeAction(f"movir {send_buffer} {self.send_buffer_offset}")
    init_tran_vertex.writeAction(f"add   {lm_base_reg} {send_buffer} {send_buffer}")
    init_tran_vertex.writeAction(f"movrl {pointer_to_partition_array_reg} 0({send_buffer}) 0 8")
    init_tran_vertex.writeAction(f"movrl {num_sht_buckets_per_lane_reg} 8({send_buffer}) 0 8")
    init_tran_vertex.writeAction(f"movrl {num_lanes_reg} 16({send_buffer}) 0 8")
    init_tran_vertex.writeAction(f"movir {lm_addr_reg} {self.do_all_desc_lm_offset}")
    init_tran_vertex.writeAction(f"add   {lm_base_reg} {lm_addr_reg} {lm_addr_reg}")
    init_tran_vertex.writeAction(f"movrl {lm_addr_reg} 24({send_buffer}) 0 8")
    '''
    Send the parameters to UDKVMSR library to start the UDKVMSR program. 
        Operands:
        OB_0: Pointer to the partition array (64-bit DRAM address)
        OB_1: Number of partitions per lane
        OB_2: Number of lanes
        OB_3: Scratchapd addr storing the input kvset metadata (sht descriptor) 
    '''
    init_tran_vertex.writeAction(f"evi  {event_reg} {ev_word_reg} 255 {0b0100}")
    init_tran_vertex.writeAction(f"evlb {ev_word_reg} {f'{task_name}::map_shuffle_reduce'}")
    init_tran_vertex.writeAction(f"addi {continue_reg} {temp_reg} 0")
    init_tran_vertex.writeAction(f"send_wcont {ev_word_reg} {temp_reg} {send_buffer} 4")
    # Save the number of lanes
    init_tran_vertex.writeAction("yield")


    init_tran_vertex_terminate = self.MSRSHT.state.writeTransition("eventCarry", self.MSRSHT.state, self.MSRSHT.state, f'{self.task_name}::do_all_vertex_init_terminate')
    if self.debug_flag:
      init_tran_vertex_terminate.writeAction(f"print '[DEBUG][NWID %d] Event <{f'{self.task_name}::do_all_vertex_init_terminate'}> ' {'X0'} ")
    # Move the pga desc to a reserverd scratchpad address and append the user defined do_all label to the end of the desc
    init_tran_vertex_terminate.writeAction(f"movir {lm_addr_reg}  {self.do_all_desc_lm_offset}")
    init_tran_vertex_terminate.writeAction(f"add   {lm_base_reg} {lm_addr_reg} {lm_addr_reg}")
    init_tran_vertex_terminate.writeAction(f"addi  {pga_desc_lm_offset_reg} {sht_addr_reg} {self.PGA_DESC_OFF_VERTEX}")
    init_tran_vertex_terminate.writeAction(f"add   {lm_base_reg} {sht_addr_reg} {sht_addr_reg}")
    for _ in range(SHTKeyValueSet.SHT_DESC_SIZE):
      init_tran_vertex_terminate.writeAction(f"movlr 0({sht_addr_reg}) {temp_reg} 1 8")
      init_tran_vertex_terminate.writeAction(f"movrl {temp_reg} 0({lm_addr_reg}) 1 8")
    init_tran_vertex_terminate.writeAction(f"movrl  {user_do_all_label_reg} 0({lm_addr_reg}) 0 8")

    # Move the UDKVMSR call parameters to a send buffer in scratchpad.
    init_tran_vertex_terminate.writeAction(f"movir {send_buffer} {self.send_buffer_offset}")
    init_tran_vertex_terminate.writeAction(f"add   {lm_base_reg} {send_buffer} {send_buffer}")
    init_tran_vertex_terminate.writeAction(f"movrl {pointer_to_partition_array_reg} 0({send_buffer}) 0 8")
    init_tran_vertex_terminate.writeAction(f"movrl {num_sht_buckets_per_lane_reg} 8({send_buffer}) 0 8")
    init_tran_vertex_terminate.writeAction(f"movrl {num_lanes_reg} 16({send_buffer}) 0 8")
    init_tran_vertex_terminate.writeAction(f"movir {lm_addr_reg} {self.do_all_desc_lm_offset}")
    init_tran_vertex_terminate.writeAction(f"add   {lm_base_reg} {lm_addr_reg} {lm_addr_reg}")
    init_tran_vertex_terminate.writeAction(f"movrl {lm_addr_reg} 24({send_buffer}) 0 8")
    '''
    Send the parameters to UDKVMSR library to start the UDKVMSR program. 
        Operands:
        OB_0: Pointer to the partition array (64-bit DRAM address)
        OB_1: Number of partitions per lane
        OB_2: Number of lanes
        OB_3: Scratchapd addr storing the input kvset metadata (sht descriptor) 
    '''
    init_tran_vertex_terminate.writeAction(f"evi  {event_reg} {ev_word_reg} 255 {0b0100}")
    init_tran_vertex_terminate.writeAction(f"evlb {ev_word_reg} {f'{task_name}::map_shuffle_reduce'}")
    init_tran_vertex_terminate.writeAction(f"addi {continue_reg} {temp_reg} 0")
    init_tran_vertex_terminate.writeAction(f"send_wcont {ev_word_reg} {temp_reg} {send_buffer} 4")
    # Save the number of lanes
    init_tran_vertex_terminate.writeAction("yieldt")


    init_tran_edge = self.MSRSHT.state.writeTransition("eventCarry", self.MSRSHT.state, self.MSRSHT.state, f'{self.task_name}::do_all_edge_init')
    if self.debug_flag:
      init_tran_edge.writeAction(f"print '[DEBUG][NWID %d] Event <{f'{self.task_name}::do_all_edge_init'}> ' {'X0'} ")
    # Move the pga desc to a reserverd scratchpad address and append the user defined do_all label to the end of the desc
    init_tran_edge.writeAction(f"movir {lm_addr_reg}  {self.do_all_desc_lm_offset}")
    init_tran_edge.writeAction(f"add   {lm_base_reg} {lm_addr_reg} {lm_addr_reg}")
    init_tran_edge.writeAction(f"addi  {pga_desc_lm_offset_reg} {sht_addr_reg} {self.PGA_DESC_OFF_EDGE}")
    init_tran_edge.writeAction(f"add   {lm_base_reg} {sht_addr_reg} {sht_addr_reg}")
    for _ in range(SHTKeyValueSet.SHT_DESC_SIZE):
      init_tran_edge.writeAction(f"movlr 0({sht_addr_reg}) {temp_reg} 1 8")
      init_tran_edge.writeAction(f"movrl {temp_reg} 0({lm_addr_reg}) 1 8")
    init_tran_edge.writeAction(f"movrl  {user_do_all_label_reg} 0({lm_addr_reg}) 0 8")

    # Move the UDKVMSR call parameters to a send buffer in scratchpad.
    init_tran_edge.writeAction(f"movir {send_buffer} {self.send_buffer_offset}")
    init_tran_edge.writeAction(f"add   {lm_base_reg} {send_buffer} {send_buffer}")
    init_tran_edge.writeAction(f"movrl {pointer_to_partition_array_reg} 0({send_buffer}) 0 8")
    init_tran_edge.writeAction(f"movrl {num_sht_buckets_per_lane_reg} 8({send_buffer}) 0 8")
    init_tran_edge.writeAction(f"movrl {num_lanes_reg} 16({send_buffer}) 0 8")
    init_tran_edge.writeAction(f"movir {lm_addr_reg} {self.do_all_desc_lm_offset}")
    init_tran_edge.writeAction(f"add   {lm_base_reg} {lm_addr_reg} {lm_addr_reg}")
    init_tran_edge.writeAction(f"movrl {lm_addr_reg} 24({send_buffer}) 0 8")
    '''
    Send the parameters to UDKVMSR library to start the UDKVMSR program. 
        Operands:
        OB_0: Pointer to the partition array (64-bit DRAM address)
        OB_1: Number of partitions per lane
        OB_2: Number of lanes
        OB_3: Scratchapd addr storing the input kvset metadata (sht descriptor) 
    '''
    init_tran_edge.writeAction(f"evi  {event_reg} {ev_word_reg} 255 {0b0100}")
    init_tran_edge.writeAction(f"evlb {ev_word_reg} {f'{task_name}::map_shuffle_reduce'}")
    init_tran_edge.writeAction(f"addi {continue_reg} {temp_reg} 0")
    init_tran_edge.writeAction(f"send_wcont {ev_word_reg} {temp_reg} {send_buffer} 4")
    # Save the number of lanes
    init_tran_edge.writeAction("yield")


    init_tran_edge_terminate = self.MSRSHT.state.writeTransition("eventCarry", self.MSRSHT.state, self.MSRSHT.state, f'{self.task_name}::do_all_edge_init_terminate')
    if self.debug_flag:
      init_tran_edge_terminate.writeAction(f"print '[DEBUG][NWID %d] Event <{f'{self.task_name}::do_all_edge_init_terminate'}> ' {'X0'} ")
    # Move the pga desc to a reserverd scratchpad address and append the user defined do_all label to the end of the desc
    init_tran_edge_terminate.writeAction(f"movir {lm_addr_reg}  {self.do_all_desc_lm_offset}")
    init_tran_edge_terminate.writeAction(f"add   {lm_base_reg} {lm_addr_reg} {lm_addr_reg}")
    init_tran_edge_terminate.writeAction(f"addi  {pga_desc_lm_offset_reg} {sht_addr_reg} {self.PGA_DESC_OFF_EDGE}")
    init_tran_edge_terminate.writeAction(f"add   {lm_base_reg} {sht_addr_reg} {sht_addr_reg}")
    for _ in range(SHTKeyValueSet.SHT_DESC_SIZE):
      init_tran_edge_terminate.writeAction(f"movlr 0({sht_addr_reg}) {temp_reg} 1 8")
      init_tran_edge_terminate.writeAction(f"movrl {temp_reg} 0({lm_addr_reg}) 1 8")
    init_tran_edge_terminate.writeAction(f"movrl  {user_do_all_label_reg} 0({lm_addr_reg}) 0 8")

    # Move the UDKVMSR call parameters to a send buffer in scratchpad.
    init_tran_edge_terminate.writeAction(f"movir {send_buffer} {self.send_buffer_offset}")
    init_tran_edge_terminate.writeAction(f"add   {lm_base_reg} {send_buffer} {send_buffer}")
    init_tran_edge_terminate.writeAction(f"movrl {pointer_to_partition_array_reg} 0({send_buffer}) 0 8")
    init_tran_edge_terminate.writeAction(f"movrl {num_sht_buckets_per_lane_reg} 8({send_buffer}) 0 8")
    init_tran_edge_terminate.writeAction(f"movrl {num_lanes_reg} 16({send_buffer}) 0 8")
    init_tran_edge_terminate.writeAction(f"movir {lm_addr_reg} {self.do_all_desc_lm_offset}")
    init_tran_edge_terminate.writeAction(f"add   {lm_base_reg} {lm_addr_reg} {lm_addr_reg}")
    init_tran_edge_terminate.writeAction(f"movrl {lm_addr_reg} 24({send_buffer}) 0 8")
    '''
    Send the parameters to UDKVMSR library to start the UDKVMSR program. 
        Operands:
        OB_0: Pointer to the partition array (64-bit DRAM address)
        OB_1: Number of partitions per lane
        OB_2: Number of lanes
        OB_3: Scratchapd addr storing the input kvset metadata (sht descriptor) 
    '''
    init_tran_edge_terminate.writeAction(f"evi  {event_reg} {ev_word_reg} 255 {0b0100}")
    init_tran_edge_terminate.writeAction(f"evlb {ev_word_reg} {f'{task_name}::map_shuffle_reduce'}")
    init_tran_edge_terminate.writeAction(f"addi {continue_reg} {temp_reg} 0")
    init_tran_edge_terminate.writeAction(f"send_wcont {ev_word_reg} {temp_reg} {send_buffer} 4")
    # Save the number of lanes
    init_tran_edge_terminate.writeAction("yieldt")



    '''
    Event:      Map task. Bin the input key-value pair to a lane (i.e., intermediate key) and emit the count.
    Operands:   X16: Input key
                X8: Input value
    '''
    continue_reg      = "X1"
    event_reg         = "X2"
    lm_base_reg       = "X7"
    value_reg         = "X9"
    key_reg           = "X8"
    temp_reg0         = "X17"
    temp_reg1         = "X18"
    send_buffer       = "X19"
    user_kv_map_label = "X20"
    
    map_tran = self.MSRSHT.state.writeTransition("eventCarry", self.MSRSHT.state, self.MSRSHT.state, f'{self.task_name}::kv_map')
    if self.debug_flag:
      map_tran.writeAction(f"print '[DEBUG][NWID %d] Event <{f'{self.task_name}::kv_map'}> key = %d' {'X0'} {'X8'}")

    map_tran.writeAction(f"movir {send_buffer} {self.udkvmsr_meta_data_offset + 8 * SHTKeyValueSet.SHT_DESC_SIZE + 8 * 16}")
    map_tran.writeAction(f"add   {lm_base_reg} {send_buffer} {send_buffer}")
    map_tran.writeAction(f"movlr 0({send_buffer}) {user_kv_map_label} 0 8")
    map_tran.writeAction(f"ev {event_reg} {temp_reg0} {user_kv_map_label} {event_reg} 3")
    map_tran.writeAction(f"addi {continue_reg} {temp_reg1} 0")
    map_tran.writeAction(f"evlb {temp_reg1} {f'{self.task_name}::kv_map_return'}" )
    map_tran.writeAction(f"sendops_wcont {temp_reg0} {temp_reg1} {key_reg} {self.value_size+1}")
    map_tran.writeAction(f"yield")

    # return efa
