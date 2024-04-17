from linker.EFAProgram import efaProgram, EFAProgram

from Config import *
from libraries.ScalableHashTable.linkable.sht_ext_call_macros import SHTExt
from libraries.ScalableHashTable.linkable.sht_call_macros import SHT
from libraries.UDMapShuffleReduce.linkable.LinkableGlobalSync import Broadcast
from Macro import *

@efaProgram
def GenSHTInit(efa: EFAProgram):
    
    efa = efa
    efa.code_level = 'machine'

    state = efa.State("S0")
    efa.add_initId(state.state_id)
    efa.add_state(state)
    
    
    send_buffer = "X16"
    lm_addr     = "X17"
    temp_regs   = ["X18", "X19", "X20"]
    sht_desc_offset = "X21"
    num_lanes   = "X22"
    temp_evw    = "X23"
    temp_reg    = "X24"
    desc_size   = "X25"
    
    broadcast = Broadcast(state=state, identifier=BROADCAST_ID)

    '''
    Initialize SHT.
        X8-X13:     sht descriptor 
        X14:        number of lanes broadcast SHT descriptor
    '''
    init_tran = state.writeTransition("eventCarry", state, state, SHT_INIT_EV_LABEL)
    if DEBUG_FLAG:
        init_tran.writeAction(f"print '[DEBUG][{SHT_INIT_EV_LABEL}] Event {SHT_INIT_EV_LABEL} Operands: sht init ops=[{' '.join(['%lu,' for _ in range(SHT_INIT_NUM_OPS)])}]'" + 
                              f" {' '.join([f'X{(OB_REG_BASE+k)}, ' for k in range(SHT_INIT_NUM_OPS)])}")
    init_tran.writeAction(f"addi {'X7'} {send_buffer} {SEND_BUFFER_OFFSET}")
    init_tran.writeAction(f"bcpyoli {'X8'} {send_buffer} {SHT_INIT_NUM_OPS}")
    SHTExt.initialize(init_tran, BCST_SHT_EV_LABEL, temp_regs[0], temp_regs[1], send_buffer)
    init_tran.writeAction(f"movir {sht_desc_offset} {SPLIT_V_SHT_OFFSET}")
    init_tran.writeAction(f"movir {desc_size} {SHT_DESC_SIZE}")
    init_tran.writeAction(f"addi {f'X{OB_REG_BASE+SHT_INIT_NUM_OPS}'} {num_lanes} 0")
    init_tran.writeAction(f"yield")    
    
    '''
    Initialize single word SHT.
        X8-X15:     sht descriptor 
        X3:         number of lanes broadcast SHT descriptor
    '''
    init_single_tran = state.writeTransition("eventCarry", state, state, SINGLE_WORD_SHT_INIT_EV_LABEL)
    if DEBUG_FLAG:
        init_single_tran.writeAction(f"print '[DEBUG][NWID %d][{SINGLE_WORD_SHT_INIT_EV_LABEL}] Event {SINGLE_WORD_SHT_INIT_EV_LABEL} number of lanes to broadcast =%ld' {'X0'} {num_lanes}")
        init_single_tran.writeAction(f"print '[DEBUG][{SINGLE_WORD_SHT_INIT_EV_LABEL}] Operands: [{' '.join(['%ld, ' for _ in range(SINGLE_WORD_SHT_INIT_NUM_OPS-1)])}]' \
            {' '.join([f'X{(OB_REG_BASE+k)} ' for k in range(SINGLE_WORD_SHT_INIT_NUM_OPS)])}")
    init_single_tran.writeAction(f"addi {'X7'} {send_buffer} {SEND_BUFFER_OFFSET}")
    init_single_tran.writeAction(f"bcpyoli {'X8'} {send_buffer} {SINGLE_WORD_SHT_INIT_NUM_OPS}")
    SHT.initialize(init_single_tran, BCST_SHT_EV_LABEL, temp_regs[0], temp_regs[1], send_buffer)
    init_single_tran.writeAction(f"movir {sht_desc_offset} {HIGH_DEG_SHT_OFFSET}")
    init_single_tran.writeAction(f"movir {desc_size} {SINGLE_WORD_SHT_DESC_SIZE}")
    init_single_tran.writeAction(f"addi {f'X{3}'} {num_lanes} 0")
    init_single_tran.writeAction("yield")
    
    '''
    Finish broadcast the SHT descriptor. 
    '''
    bcst_sht_tran = state.writeTransition("eventCarry", state, state, BCST_SHT_EV_LABEL)
    if DEBUG_FLAG:
        bcst_sht_tran.writeAction(f"print '[DEBUG][{BCST_SHT_EV_LABEL}] Finish init SHT, broadcast the descriptor to %ld lanes' {num_lanes} ")
    # Broadcast the SHT descriptor to all lanes.
    bcst_sht_tran.writeAction(f"movrl {num_lanes} 0({send_buffer}) 0 8")
    bcst_sht_tran.writeAction(f"addi {'X2'} {temp_evw} 0")
    bcst_sht_tran.writeAction(f"evlb {temp_evw} {broadcast.get_broadcast_value_sp_ev_label()}")
    bcst_sht_tran.writeAction(f"movrl {temp_evw} {WORD_SIZE}({send_buffer}) 0 8")
    bcst_sht_tran.writeAction(f"sli {sht_desc_offset} {temp_reg} {32}")
    bcst_sht_tran.writeAction(f"add {temp_reg} {desc_size} {temp_reg}")
    bcst_sht_tran.writeAction(f"movrl {temp_reg} {WORD_SIZE * 2}({send_buffer}) 0 8")
    bcst_sht_tran.writeAction(f"addi {send_buffer} {lm_addr} {3 * WORD_SIZE}")
    bcst_sht_tran.writeAction(f"sli {desc_size} {desc_size} {LOG2_WORD_SIZE}")
    bcst_sht_tran.writeAction(f"add {'X7'} {sht_desc_offset} {sht_desc_offset}")
    bcst_sht_tran.writeAction(f"bcpyll {sht_desc_offset} {lm_addr} {desc_size}")
    if DEBUG_FLAG:
        for i in range(SINGLE_WORD_SHT_DESC_SIZE):
            bcst_sht_tran.writeAction(f"movlr {WORD_SIZE * (i+3)}({send_buffer}) {temp_reg} 0 8")
            bcst_sht_tran.writeAction(f"print '[DEBUG][NWID %ld][{BCST_SHT_EV_LABEL}] SHT descriptor[{i}]: %lu' {'X0'} {temp_reg}")
    set_ev_label(bcst_sht_tran, temp_evw, broadcast.get_broadcast_ev_label(), new_thread=True)
    bcst_sht_tran.writeAction(f"send_wret {temp_evw} {SHT_INIT_RET_EV_LABEL} {send_buffer} {8} {temp_reg}")
    bcst_sht_tran.writeAction(f"yield")
    
    '''
    Finish intialize SHT, return to the top.
    '''
    term_tran = state.writeTransition("eventCarry", state, state, SHT_INIT_RET_EV_LABEL)
    # Finish init SHT, Signal the top 
    term_tran.writeAction(f"addi {'X7'} {lm_addr} 0")
    term_tran.writeAction(f"movir {temp_regs[2]} {FLAG}")
    term_tran.writeAction(f"move {temp_regs[2]} {TOP_FLAG_OFFSET}({lm_addr}) 0 8")
    term_tran.writeAction("yieldt")
    