from EFA_v2 import *
def basic_noaction4_with_lastact_TX_maxSBP_12():
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
    tran0.writeAction("movir X16 26368")
    tran0.writeAction("slorii X16 X16 12 2227")
    tran0.writeAction("slorii X16 X16 12 3638")
    tran0.writeAction("slorii X16 X16 12 2928")
    tran0.writeAction("slorii X16 X16 12 157")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 11687")
    tran0.writeAction("slorii X16 X16 12 1586")
    tran0.writeAction("slorii X16 X16 12 4051")
    tran0.writeAction("slorii X16 X16 12 1303")
    tran0.writeAction("slorii X16 X16 12 3479")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 39401")
    tran0.writeAction("slorii X16 X16 12 1039")
    tran0.writeAction("slorii X16 X16 12 1480")
    tran0.writeAction("slorii X16 X16 12 2643")
    tran0.writeAction("slorii X16 X16 12 3612")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 52714")
    tran0.writeAction("slorii X16 X16 12 3956")
    tran0.writeAction("slorii X16 X16 12 3904")
    tran0.writeAction("slorii X16 X16 12 2114")
    tran0.writeAction("slorii X16 X16 12 1699")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 12518")
    tran0.writeAction("slorii X16 X16 12 2427")
    tran0.writeAction("slorii X16 X16 12 1330")
    tran0.writeAction("slorii X16 X16 12 1787")
    tran0.writeAction("slorii X16 X16 12 2647")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 24862")
    tran0.writeAction("slorii X16 X16 12 1193")
    tran0.writeAction("slorii X16 X16 12 2283")
    tran0.writeAction("slorii X16 X16 12 3418")
    tran0.writeAction("slorii X16 X16 12 3823")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 22897")
    tran0.writeAction("slorii X16 X16 12 213")
    tran0.writeAction("slorii X16 X16 12 1993")
    tran0.writeAction("slorii X16 X16 12 1747")
    tran0.writeAction("slorii X16 X16 12 3109")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 16235")
    tran0.writeAction("slorii X16 X16 12 1729")
    tran0.writeAction("slorii X16 X16 12 1833")
    tran0.writeAction("slorii X16 X16 12 2103")
    tran0.writeAction("slorii X16 X16 12 2509")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 26368")
    tran0.writeAction("slorii X16 X16 12 2227")
    tran0.writeAction("slorii X16 X16 12 3638")
    tran0.writeAction("slorii X16 X16 12 2928")
    tran0.writeAction("slorii X16 X16 12 157")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 2")
    tran0.writeAction("sli X17 X17 36")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 5")
    tran0.writeAction("sli X17 X17 32")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X20 0")
    tran0.writeAction("add X20 X7 X5")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("addi X20 X17 5")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("basic", state1, state2, 157)
    tran3 = state1.writeTransition("basic_with_action", state1, state2, 255)
    tran3.writeAction("addi X5 X16 8")
    tran3.writeAction("movir X30 8")
    tran3.writeAction("movir X29 8")
    tran3.writeAction("movir X28 8")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("basic", state2, state2, 139)
    tran4 = state2.writeTransition("basic_with_action", state2, state1, 255)
    tran4.writeAction("addi X5 X17 0")
    tran4.writeAction("movir X31 8")
    tran4.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa
