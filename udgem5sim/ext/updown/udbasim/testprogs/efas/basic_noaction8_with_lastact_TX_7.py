from EFA_v2 import *
def basic_noaction8_with_lastact_TX_7():
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
    tran0.writeAction("movir X16 0")
    tran0.writeAction("slorii X16 X16 12 11")
    tran0.writeAction("slorii X16 X16 12 2048")
    tran0.writeAction("slorii X16 X16 12 0")
    tran0.writeAction("slorii X16 X16 12 45")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 13711")
    tran0.writeAction("slorii X16 X16 12 3127")
    tran0.writeAction("slorii X16 X16 12 40")
    tran0.writeAction("slorii X16 X16 12 3950")
    tran0.writeAction("slorii X16 X16 12 1432")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 49520")
    tran0.writeAction("slorii X16 X16 12 4056")
    tran0.writeAction("slorii X16 X16 12 1324")
    tran0.writeAction("slorii X16 X16 12 2689")
    tran0.writeAction("slorii X16 X16 12 2305")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 5228")
    tran0.writeAction("slorii X16 X16 12 2589")
    tran0.writeAction("slorii X16 X16 12 2056")
    tran0.writeAction("slorii X16 X16 12 1714")
    tran0.writeAction("slorii X16 X16 12 3911")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 58639")
    tran0.writeAction("slorii X16 X16 12 2377")
    tran0.writeAction("slorii X16 X16 12 1760")
    tran0.writeAction("slorii X16 X16 12 2639")
    tran0.writeAction("slorii X16 X16 12 779")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 23680")
    tran0.writeAction("slorii X16 X16 12 2576")
    tran0.writeAction("slorii X16 X16 12 2480")
    tran0.writeAction("slorii X16 X16 12 3401")
    tran0.writeAction("slorii X16 X16 12 1811")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 429")
    tran0.writeAction("slorii X16 X16 12 2945")
    tran0.writeAction("slorii X16 X16 12 585")
    tran0.writeAction("slorii X16 X16 12 276")
    tran0.writeAction("slorii X16 X16 12 1326")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 10552")
    tran0.writeAction("slorii X16 X16 12 3627")
    tran0.writeAction("slorii X16 X16 12 1490")
    tran0.writeAction("slorii X16 X16 12 2221")
    tran0.writeAction("slorii X16 X16 12 1612")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 0")
    tran0.writeAction("slorii X16 X16 12 11")
    tran0.writeAction("slorii X16 X16 12 2048")
    tran0.writeAction("slorii X16 X16 12 0")
    tran0.writeAction("slorii X16 X16 12 45")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 4")
    tran0.writeAction("sli X17 X17 36")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 4")
    tran0.writeAction("sli X17 X17 32")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X20 0")
    tran0.writeAction("add X20 X7 X5")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("addi X20 X17 12")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("basic", state1, state2, 45)
    tran3 = state1.writeTransition("basic_with_action", state1, state2, 255)
    tran3.writeAction("movir X30 8")
    tran3.writeAction("movir X29 8")
    tran3.writeAction("movir X28 8")
    tran3.writeAction("movir X27 8")
    tran3.writeAction("movir X26 8")
    tran3.writeAction("movir X25 8")
    tran3.writeAction("movir X24 8")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("basic_with_action", state2, state2, 184)
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
