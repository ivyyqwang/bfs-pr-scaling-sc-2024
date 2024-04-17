from EFA_v2 import *
def common_noaction_TX_maxSBP_14():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    state1 = State()
    state1.alphabet = [0-255]
    efa.add_state(state1)
    state2 = State()
    state2.alphabet = [0-255]
    efa.add_state(state2)
    tran0 = state.writeTransition("commonCarry_with_action", state, state1, 1)
    tran0.writeAction("movir X17 0")
    tran0.writeAction("add X7 X17 X17")
    tran0.writeAction("movir X16 30812")
    tran0.writeAction("slorii X16 X16 12 1867")
    tran0.writeAction("slorii X16 X16 12 3726")
    tran0.writeAction("slorii X16 X16 12 1345")
    tran0.writeAction("slorii X16 X16 12 3291")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 55270")
    tran0.writeAction("slorii X16 X16 12 491")
    tran0.writeAction("slorii X16 X16 12 686")
    tran0.writeAction("slorii X16 X16 12 999")
    tran0.writeAction("slorii X16 X16 12 1747")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 33183")
    tran0.writeAction("slorii X16 X16 12 3805")
    tran0.writeAction("slorii X16 X16 12 1629")
    tran0.writeAction("slorii X16 X16 12 1278")
    tran0.writeAction("slorii X16 X16 12 65")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 21020")
    tran0.writeAction("slorii X16 X16 12 3319")
    tran0.writeAction("slorii X16 X16 12 1952")
    tran0.writeAction("slorii X16 X16 12 991")
    tran0.writeAction("slorii X16 X16 12 2765")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 44810")
    tran0.writeAction("slorii X16 X16 12 2")
    tran0.writeAction("slorii X16 X16 12 189")
    tran0.writeAction("slorii X16 X16 12 563")
    tran0.writeAction("slorii X16 X16 12 1614")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 9717")
    tran0.writeAction("slorii X16 X16 12 3564")
    tran0.writeAction("slorii X16 X16 12 3259")
    tran0.writeAction("slorii X16 X16 12 958")
    tran0.writeAction("slorii X16 X16 12 1681")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 63811")
    tran0.writeAction("slorii X16 X16 12 1625")
    tran0.writeAction("slorii X16 X16 12 3652")
    tran0.writeAction("slorii X16 X16 12 944")
    tran0.writeAction("slorii X16 X16 12 2896")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 27014")
    tran0.writeAction("slorii X16 X16 12 476")
    tran0.writeAction("slorii X16 X16 12 1899")
    tran0.writeAction("slorii X16 X16 12 2961")
    tran0.writeAction("slorii X16 X16 12 1752")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 30812")
    tran0.writeAction("slorii X16 X16 12 1867")
    tran0.writeAction("slorii X16 X16 12 3726")
    tran0.writeAction("slorii X16 X16 12 1345")
    tran0.writeAction("slorii X16 X16 12 3291")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 2")
    tran0.writeAction("sli X17 X17 36")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 7")
    tran0.writeAction("sli X17 X17 32")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("add X7 X31 X31")
    tran0.writeAction("movir X20 0")
    tran0.writeAction("sli X31 X21 3")
    tran0.writeAction("add X21 X20 X5")
    tran0.writeAction("movlsb X31")
    tran0.writeAction("addi X20 X17 7")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("commonCarry", state1, state2, 0)
    tran2 = state2.writeTransition("commonCarry", state2, state2, 0)
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa
