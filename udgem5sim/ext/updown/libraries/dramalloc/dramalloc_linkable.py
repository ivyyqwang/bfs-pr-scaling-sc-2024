from Macro import *

NUM_UD_PER_NODE = 32

class TranslationEntryInstaller:
    def __init__(self, enable_debug=False):
        self.enable_debug = enable_debug
        
        # self.num_lanes_reg = "UDPR_0"
        self.nwid   = "UDPR_1"
        self.count  = "UDPR_2"
        self.event_word = "UDPR_14"
        
        self.glb_bcst_ev_label = "DRAMalloc::global_broadcast"
        self.node_bcst_ev_label = "DRAMalloc::node_broadcast"
        self.ud_install_ev_label = "DRAMalloc::updown_translation_install"
        self.node_bcst_ret_ev_label = "DRAMalloc::node_broadcast_return"
        self.glb_bcst_ret_ev_label = "DRAMalloc::global_broadcast_return"
        
    def __gen_bcst(self):
        
        glb_bcst_tran   = self.state.writeTransition("eventCarry", self.state, self.state, self.glb_bcst_ev_label)

        node_bcst_tran  = self.state.writeTransition("eventCarry", self.state, self.state, self.node_bcst_ev_label)

        ud_install_tran = self.state.writeTransition("eventCarry", self.state, self.state, self.ud_install_ev_label)

        node_bcst_ret_tran  = self.state.writeTransition("eventCarry", self.state, self.state, self.node_bcst_ret_ev_label)

        glb_bcst_ret_tran   = self.state.writeTransition("eventCarry", self.state, self.state, self.glb_bcst_ret_ev_label)
        
        num_child   = "UDPR_9"
        num_return  = "UDPR_10"
        
        '''
        Event:      UDKVMSR exit point, clean up scratchpad
        Operands:   
        '''
        if self.debug_flag:
            glb_bcst_tran.writeAction(f"print ' '")
            glb_bcst_tran.writeAction(f"print '[DEBUG][NWID %d] Event <dramalloc_global_broadcast> ev_word=%d' {'X0'} {'EQT'}")
        glb_bcst_tran.writeAction(f"addi X12 {num_child} 0")
        glb_bcst_tran = set_ev_label(glb_bcst_tran, self.ev_word, self.node_bcst_ev_label, new_thread = True, label=self.multiple_label)
        if self.debug_flag:
            glb_bcst_tran.writeAction(f"print '[DEBUG][NWID %d] Broadcast to %d nodes' {'X0'} {num_child}")
        glb_bcst_tran = broadcast(glb_bcst_tran, self.ev_word, num_child, self.glb_bcst_ret_ev_label, \
            (LOG2_LANE_PER_UD + LOG2_UD_PER_NODE), f"{'X8'} 4", self.scratch, 'ops', self.send_temp_reg_flag)
        glb_bcst_tran.writeAction(f"mov_imm2reg {num_return} 0")
        glb_bcst_tran.writeAction("yield")

        '''
        Event:      clean up node
        Operands:   X8: number of lanes
                    X9: input key-value set pointer
                    X10: output key-value set pointer
                    X11 ~ Xn: input and output key-value set metadata
        '''
        if self.debug_flag:
            node_bcst_tran.writeAction(f"print ' '")
            node_bcst_tran.writeAction(f"print '[DEBUG][NWID %d] Event <dramalloc_node_broadcast> ev_word=%d' {'X0'} {'EQT'}")
        node_bcst_tran.writeAction(f"addi X1 {self.saved_cont} 0")
        node_bcst_tran.writeAction(f"movir {num_child} {NUM_UD_PER_NODE}")
        node_bcst_tran = set_ev_label(node_bcst_tran, self.ev_word, self.ud_bcst_ev_label, new_thread = True, label=self.multiple_label)
        if self.debug_flag:
            node_bcst_tran.writeAction(f"print '[DEBUG][NWID %d] Broadcast to %d updowns' {'X0'} {num_child}")
        node_bcst_tran = broadcast(node_bcst_tran, self.ev_word, num_child, self.node_bcst_ret_ev_label, \
            (LOG2_LANE_PER_UD), f"X8 2", self.scratch, 'ops', self.send_temp_reg_flag)
        node_bcst_tran.writeAction(f"mov_imm2reg {num_return} 0")
        node_bcst_tran.writeAction("yield")

        '''
        Event:      Initialize updown scratchpad
        Operands:   X8: number of lanes
                    X9: input key-value set pointer
                    X10: output key-value set pointer
                    X11 ~ Xn: input and output key-value set metadata
        '''
        if self.debug_flag:
            ud_install_tran.writeAction(f"print ' '")
            ud_install_tran.writeAction(f"print '[DEBUG][NWID %d] Event <dramalloc_updown_translation_install> ev_word=%d' {'X0'} {'EQT'}")
            ud_install_tran.writeAction(f"print '[DEBUG][NWID %d] Install translation entry va_base = %d(0x%x) pa_base = %d(0x%x) size = %d swizzle_mask = %d' \
                {'X0'} {'X8'} {'X8'} {'X9'} {'X9'} {'X10'} {'X11'}")
        ud_install_tran.writeAction(f"instrans X8 X9 X10 X11 1 {0b11}")
        ud_install_tran.writeAction(format_pseudo(f"sendr_reply X0 X16", self.scratch[0], self.send_temp_reg_flag))
        ud_install_tran.writeAction("yield_terminate")

        continue_label  = "continue"
        cleanup_ret_label = "global_bcst_return"

        '''
        Event:      Node updown scratchpad initialized return event
        Operands:   X8 ~ X9: sender event word
        '''
        if self.debug_flag:
            node_bcst_ret_tran.writeAction(f"print ' '")
            node_bcst_ret_tran.writeAction(f"print '[DEBUG][NWID %d] Event <dramalloc_node_broadcast_return> ev_word=%d num_return=%d' {'X0'} {'EQT'} {num_return}")
        node_bcst_ret_tran.writeAction(f"addi {num_return} {num_return} 1")
        node_bcst_ret_tran.writeAction(f"blt {num_return} {num_child} {continue_label}")
        node_bcst_ret_tran.writeAction(format_pseudo("sendr_reply X0 X16", self.scratch[0], self.send_temp_reg_flag))
        node_bcst_ret_tran.writeAction("yield_terminate")
        node_bcst_ret_tran.writeAction(f"{continue_label}: yield")

        '''
        Event:      Node scratchpad initialized return event
        Operands:   X8 ~ X9: sender event word
        '''
        if self.debug_flag:
            glb_bcst_ret_tran.writeAction(f"print ' '")
            glb_bcst_ret_tran.writeAction(f"print '[DEBUG][NWID %d] Event <dramalloc_glb_broadcast_return> ev_word=%d num_return=%d' {'X0'} {'EQT'} {num_return}")
        glb_bcst_ret_tran.writeAction(f"addi {num_return} {num_return} 1")
        glb_bcst_ret_tran.writeAction(f"beq {num_return} {num_child} {cleanup_ret_label}")
        glb_bcst_ret_tran.writeAction(f"yield")
        glb_bcst_ret_tran.writeAction(f"{cleanup_ret_label}: move {self.user_cont_offset}(X7) {self.saved_cont} 0 8")
        glb_bcst_ret_tran.writeAction(f"sendr_wcont {self.saved_cont} EQT {self.num_lane_reg} {self.num_lane_reg}")
        if self.debug_flag:
            glb_bcst_ret_tran.writeAction(f"print '[DEBUG][NWID %d] Finish broadcast and install translation, return to top.' {'X0'} ")
        glb_bcst_ret_tran.writeAction(f"yieldt")
        
        return