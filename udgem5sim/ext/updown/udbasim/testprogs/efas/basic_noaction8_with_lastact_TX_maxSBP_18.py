from EFA_v2 import *
def basic_noaction8_with_lastact_TX_maxSBP_18():
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
    tran0.writeAction("movir X16 55059")
    tran0.writeAction("slorii X16 X16 12 2790")
    tran0.writeAction("slorii X16 X16 12 3823")
    tran0.writeAction("slorii X16 X16 12 1750")
    tran0.writeAction("slorii X16 X16 12 2702")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 26828")
    tran0.writeAction("slorii X16 X16 12 2239")
    tran0.writeAction("slorii X16 X16 12 4091")
    tran0.writeAction("slorii X16 X16 12 1470")
    tran0.writeAction("slorii X16 X16 12 4034")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 26721")
    tran0.writeAction("slorii X16 X16 12 314")
    tran0.writeAction("slorii X16 X16 12 2184")
    tran0.writeAction("slorii X16 X16 12 2561")
    tran0.writeAction("slorii X16 X16 12 1627")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 51829")
    tran0.writeAction("slorii X16 X16 12 3488")
    tran0.writeAction("slorii X16 X16 12 3319")
    tran0.writeAction("slorii X16 X16 12 1843")
    tran0.writeAction("slorii X16 X16 12 3138")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 31348")
    tran0.writeAction("slorii X16 X16 12 714")
    tran0.writeAction("slorii X16 X16 12 2977")
    tran0.writeAction("slorii X16 X16 12 2829")
    tran0.writeAction("slorii X16 X16 12 2435")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 9380")
    tran0.writeAction("slorii X16 X16 12 19")
    tran0.writeAction("slorii X16 X16 12 2174")
    tran0.writeAction("slorii X16 X16 12 1992")
    tran0.writeAction("slorii X16 X16 12 2684")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 37961")
    tran0.writeAction("slorii X16 X16 12 805")
    tran0.writeAction("slorii X16 X16 12 2146")
    tran0.writeAction("slorii X16 X16 12 1612")
    tran0.writeAction("slorii X16 X16 12 4014")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 34531")
    tran0.writeAction("slorii X16 X16 12 209")
    tran0.writeAction("slorii X16 X16 12 1783")
    tran0.writeAction("slorii X16 X16 12 784")
    tran0.writeAction("slorii X16 X16 12 1686")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 55059")
    tran0.writeAction("slorii X16 X16 12 2790")
    tran0.writeAction("slorii X16 X16 12 3823")
    tran0.writeAction("slorii X16 X16 12 1750")
    tran0.writeAction("slorii X16 X16 12 2702")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 7")
    tran0.writeAction("sli X17 X17 36")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 8")
    tran0.writeAction("sli X17 X17 32")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("add X7 X31 X31")
    tran0.writeAction("movir X20 0")
    tran0.writeAction("sli X31 X21 3")
    tran0.writeAction("add X21 X20 X5")
    tran0.writeAction("movlsb X31")
    tran0.writeAction("addi X20 X17 8")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("basic", state1, state2, 14)
    tran3 = state1.writeTransition("basic_with_action", state1, state2, 255)
    tran3.writeAction("movir X30 8")
    tran3.writeAction("movir X29 8")
    tran3.writeAction("movir X28 8")
    tran3.writeAction("movir X27 8")
    tran3.writeAction("movir X26 8")
    tran3.writeAction("movir X25 8")
    tran3.writeAction("movir X24 8")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("basic", state2, state2, 106)
    tran4 = state2.writeTransition("basic_with_action", state2, state1, 255)
    tran4.writeAction("addi X5 X17 0")
    tran4.writeAction("movir X31 8")
    tran4.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa
