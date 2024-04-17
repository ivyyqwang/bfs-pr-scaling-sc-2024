from EFA_v2 import *
def common_noaction_TX_maxSBP_3():
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
    tran0.writeAction("movir X16 13741")
    tran0.writeAction("slorii X16 X16 12 863")
    tran0.writeAction("slorii X16 X16 12 1438")
    tran0.writeAction("slorii X16 X16 12 1433")
    tran0.writeAction("slorii X16 X16 12 3204")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 30047")
    tran0.writeAction("slorii X16 X16 12 3429")
    tran0.writeAction("slorii X16 X16 12 3252")
    tran0.writeAction("slorii X16 X16 12 682")
    tran0.writeAction("slorii X16 X16 12 795")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 31390")
    tran0.writeAction("slorii X16 X16 12 1778")
    tran0.writeAction("slorii X16 X16 12 2270")
    tran0.writeAction("slorii X16 X16 12 3774")
    tran0.writeAction("slorii X16 X16 12 3808")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 7346")
    tran0.writeAction("slorii X16 X16 12 2007")
    tran0.writeAction("slorii X16 X16 12 484")
    tran0.writeAction("slorii X16 X16 12 124")
    tran0.writeAction("slorii X16 X16 12 3667")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 55106")
    tran0.writeAction("slorii X16 X16 12 2376")
    tran0.writeAction("slorii X16 X16 12 1010")
    tran0.writeAction("slorii X16 X16 12 1450")
    tran0.writeAction("slorii X16 X16 12 2223")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 15200")
    tran0.writeAction("slorii X16 X16 12 2218")
    tran0.writeAction("slorii X16 X16 12 3111")
    tran0.writeAction("slorii X16 X16 12 1454")
    tran0.writeAction("slorii X16 X16 12 920")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 38239")
    tran0.writeAction("slorii X16 X16 12 2719")
    tran0.writeAction("slorii X16 X16 12 1167")
    tran0.writeAction("slorii X16 X16 12 880")
    tran0.writeAction("slorii X16 X16 12 1704")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 50873")
    tran0.writeAction("slorii X16 X16 12 448")
    tran0.writeAction("slorii X16 X16 12 2158")
    tran0.writeAction("slorii X16 X16 12 4009")
    tran0.writeAction("slorii X16 X16 12 1419")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 13741")
    tran0.writeAction("slorii X16 X16 12 863")
    tran0.writeAction("slorii X16 X16 12 1438")
    tran0.writeAction("slorii X16 X16 12 1433")
    tran0.writeAction("slorii X16 X16 12 3204")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 3")
    tran0.writeAction("sli X17 X17 36")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 3")
    tran0.writeAction("sli X17 X17 32")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("add X7 X31 X31")
    tran0.writeAction("movir X20 0")
    tran0.writeAction("sli X31 X21 3")
    tran0.writeAction("add X21 X20 X5")
    tran0.writeAction("movlsb X31")
    tran0.writeAction("addi X20 X17 3")
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
