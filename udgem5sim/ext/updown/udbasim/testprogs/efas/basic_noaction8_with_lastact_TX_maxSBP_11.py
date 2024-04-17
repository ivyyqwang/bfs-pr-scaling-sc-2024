from EFA_v2 import *
def basic_noaction8_with_lastact_TX_maxSBP_11():
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
    tran0.writeAction("movir X16 32382")
    tran0.writeAction("slorii X16 X16 12 210")
    tran0.writeAction("slorii X16 X16 12 3177")
    tran0.writeAction("slorii X16 X16 12 3909")
    tran0.writeAction("slorii X16 X16 12 885")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 7482")
    tran0.writeAction("slorii X16 X16 12 1539")
    tran0.writeAction("slorii X16 X16 12 3090")
    tran0.writeAction("slorii X16 X16 12 489")
    tran0.writeAction("slorii X16 X16 12 89")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 32552")
    tran0.writeAction("slorii X16 X16 12 3210")
    tran0.writeAction("slorii X16 X16 12 3201")
    tran0.writeAction("slorii X16 X16 12 1390")
    tran0.writeAction("slorii X16 X16 12 264")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 56178")
    tran0.writeAction("slorii X16 X16 12 449")
    tran0.writeAction("slorii X16 X16 12 3402")
    tran0.writeAction("slorii X16 X16 12 3885")
    tran0.writeAction("slorii X16 X16 12 1040")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 37314")
    tran0.writeAction("slorii X16 X16 12 2644")
    tran0.writeAction("slorii X16 X16 12 925")
    tran0.writeAction("slorii X16 X16 12 2674")
    tran0.writeAction("slorii X16 X16 12 399")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 60115")
    tran0.writeAction("slorii X16 X16 12 2574")
    tran0.writeAction("slorii X16 X16 12 3078")
    tran0.writeAction("slorii X16 X16 12 1490")
    tran0.writeAction("slorii X16 X16 12 1785")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 6005")
    tran0.writeAction("slorii X16 X16 12 1467")
    tran0.writeAction("slorii X16 X16 12 3047")
    tran0.writeAction("slorii X16 X16 12 2562")
    tran0.writeAction("slorii X16 X16 12 1094")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 54994")
    tran0.writeAction("slorii X16 X16 12 1697")
    tran0.writeAction("slorii X16 X16 12 3148")
    tran0.writeAction("slorii X16 X16 12 1466")
    tran0.writeAction("slorii X16 X16 12 1121")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 32382")
    tran0.writeAction("slorii X16 X16 12 210")
    tran0.writeAction("slorii X16 X16 12 3177")
    tran0.writeAction("slorii X16 X16 12 3909")
    tran0.writeAction("slorii X16 X16 12 885")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 6")
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
    tran1 = state1.writeTransition("basic", state1, state2, 53)
    tran3 = state1.writeTransition("basic_with_action", state1, state2, 255)
    tran3.writeAction("movir X30 8")
    tran3.writeAction("movir X29 8")
    tran3.writeAction("movir X28 8")
    tran3.writeAction("movir X27 8")
    tran3.writeAction("movir X26 8")
    tran3.writeAction("movir X25 8")
    tran3.writeAction("movir X24 8")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("basic", state2, state2, 38)
    tran4 = state2.writeTransition("basic_with_action", state2, state1, 255)
    tran4.writeAction("addi X5 X17 0")
    tran4.writeAction("movir X31 8")
    tran4.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa