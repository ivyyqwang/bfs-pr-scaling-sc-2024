from EFA_v2 import *
def basic_noaction2_with_lastact_TX_maxSBP_15():
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
    tran0.writeAction("movir X16 2097")
    tran0.writeAction("slorii X16 X16 12 421")
    tran0.writeAction("slorii X16 X16 12 263")
    tran0.writeAction("slorii X16 X16 12 1936")
    tran0.writeAction("slorii X16 X16 12 38")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 25434")
    tran0.writeAction("slorii X16 X16 12 3056")
    tran0.writeAction("slorii X16 X16 12 2882")
    tran0.writeAction("slorii X16 X16 12 1002")
    tran0.writeAction("slorii X16 X16 12 2816")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 37590")
    tran0.writeAction("slorii X16 X16 12 2151")
    tran0.writeAction("slorii X16 X16 12 3122")
    tran0.writeAction("slorii X16 X16 12 1815")
    tran0.writeAction("slorii X16 X16 12 1073")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 6261")
    tran0.writeAction("slorii X16 X16 12 491")
    tran0.writeAction("slorii X16 X16 12 820")
    tran0.writeAction("slorii X16 X16 12 2544")
    tran0.writeAction("slorii X16 X16 12 2116")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 26926")
    tran0.writeAction("slorii X16 X16 12 931")
    tran0.writeAction("slorii X16 X16 12 1721")
    tran0.writeAction("slorii X16 X16 12 1787")
    tran0.writeAction("slorii X16 X16 12 1034")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 8039")
    tran0.writeAction("slorii X16 X16 12 1663")
    tran0.writeAction("slorii X16 X16 12 850")
    tran0.writeAction("slorii X16 X16 12 3509")
    tran0.writeAction("slorii X16 X16 12 1258")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 25090")
    tran0.writeAction("slorii X16 X16 12 998")
    tran0.writeAction("slorii X16 X16 12 629")
    tran0.writeAction("slorii X16 X16 12 3258")
    tran0.writeAction("slorii X16 X16 12 1132")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 40125")
    tran0.writeAction("slorii X16 X16 12 1078")
    tran0.writeAction("slorii X16 X16 12 3295")
    tran0.writeAction("slorii X16 X16 12 2188")
    tran0.writeAction("slorii X16 X16 12 704")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 2097")
    tran0.writeAction("slorii X16 X16 12 421")
    tran0.writeAction("slorii X16 X16 12 263")
    tran0.writeAction("slorii X16 X16 12 1936")
    tran0.writeAction("slorii X16 X16 12 38")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 2")
    tran0.writeAction("sli X17 X17 36")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 7")
    tran0.writeAction("sli X17 X17 32")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X20 0")
    tran0.writeAction("add X20 X7 X5")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("addi X20 X17 7")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("basic", state1, state2, 38)
    tran3 = state1.writeTransition("basic_with_action", state1, state2, 255)
    tran3.writeAction("addi X5 X16 0")
    tran3.writeAction("movir X30 8")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("basic", state2, state2, 8)
    tran4 = state2.writeTransition("basic_with_action", state2, state1, 255)
    tran4.writeAction("addi X5 X17 0")
    tran4.writeAction("movir X31 8")
    tran4.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa
