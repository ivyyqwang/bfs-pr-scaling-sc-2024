from EFA_v2 import *
def basic_noaction8_with_lastact_TX_14():
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
    tran0 = state.writeTransition("basic_with_action", state, state1, 1)
    tran0.writeAction("movir X17 0")
    tran0.writeAction("add X7 X17 X17")
    tran0.writeAction("movir X16 40846")
    tran0.writeAction("slorii X16 X16 12 2955")
    tran0.writeAction("slorii X16 X16 12 3253")
    tran0.writeAction("slorii X16 X16 12 1852")
    tran0.writeAction("slorii X16 X16 12 635")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 52520")
    tran0.writeAction("slorii X16 X16 12 2106")
    tran0.writeAction("slorii X16 X16 12 2368")
    tran0.writeAction("slorii X16 X16 12 2356")
    tran0.writeAction("slorii X16 X16 12 1384")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 49688")
    tran0.writeAction("slorii X16 X16 12 2329")
    tran0.writeAction("slorii X16 X16 12 2269")
    tran0.writeAction("slorii X16 X16 12 3628")
    tran0.writeAction("slorii X16 X16 12 3121")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 38802")
    tran0.writeAction("slorii X16 X16 12 848")
    tran0.writeAction("slorii X16 X16 12 3451")
    tran0.writeAction("slorii X16 X16 12 373")
    tran0.writeAction("slorii X16 X16 12 1564")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 55655")
    tran0.writeAction("slorii X16 X16 12 662")
    tran0.writeAction("slorii X16 X16 12 3867")
    tran0.writeAction("slorii X16 X16 12 230")
    tran0.writeAction("slorii X16 X16 12 2540")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 56171")
    tran0.writeAction("slorii X16 X16 12 3304")
    tran0.writeAction("slorii X16 X16 12 825")
    tran0.writeAction("slorii X16 X16 12 3389")
    tran0.writeAction("slorii X16 X16 12 1121")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 5582")
    tran0.writeAction("slorii X16 X16 12 235")
    tran0.writeAction("slorii X16 X16 12 2585")
    tran0.writeAction("slorii X16 X16 12 136")
    tran0.writeAction("slorii X16 X16 12 246")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 23511")
    tran0.writeAction("slorii X16 X16 12 90")
    tran0.writeAction("slorii X16 X16 12 487")
    tran0.writeAction("slorii X16 X16 12 1853")
    tran0.writeAction("slorii X16 X16 12 3780")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 40846")
    tran0.writeAction("slorii X16 X16 12 2955")
    tran0.writeAction("slorii X16 X16 12 3253")
    tran0.writeAction("slorii X16 X16 12 1852")
    tran0.writeAction("slorii X16 X16 12 635")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 2")
    tran0.writeAction("sli X17 X17 36")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 6")
    tran0.writeAction("sli X17 X17 32")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("add X7 X31 X31")
    tran0.writeAction("movir X20 0")
    tran0.writeAction("sli X31 X21 3")
    tran0.writeAction("add X21 X20 X5")
    tran0.writeAction("movlsb X31")
    tran0.writeAction("addi X20 X17 18")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("basic", state1, state2, 3)
    tran3 = state1.writeTransition("basic_with_action", state1, state2, 255)
    tran3.writeAction("movir X30 8")
    tran3.writeAction("movir X29 8")
    tran3.writeAction("movir X28 8")
    tran3.writeAction("movir X27 8")
    tran3.writeAction("movir X26 8")
    tran3.writeAction("movir X25 8")
    tran3.writeAction("movir X24 8")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("basic_with_action", state2, state2, 1)
    tran2.writeAction("movir X31 7")
    tran2.writeAction("yieldt")
    tran4 = state2.writeTransition("basic_with_action", state2, state1, 255)
    tran4.writeAction("addi X5 X17 0")
    tran4.writeAction("movir X31 8")
    tran4.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa