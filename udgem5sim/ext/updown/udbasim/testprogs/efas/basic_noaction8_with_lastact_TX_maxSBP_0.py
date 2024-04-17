from EFA_v2 import *
def basic_noaction8_with_lastact_TX_maxSBP_0():
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
    tran0.writeAction("movir X16 32045")
    tran0.writeAction("slorii X16 X16 12 169")
    tran0.writeAction("slorii X16 X16 12 1489")
    tran0.writeAction("slorii X16 X16 12 1543")
    tran0.writeAction("slorii X16 X16 12 4031")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 44767")
    tran0.writeAction("slorii X16 X16 12 3760")
    tran0.writeAction("slorii X16 X16 12 3347")
    tran0.writeAction("slorii X16 X16 12 1134")
    tran0.writeAction("slorii X16 X16 12 2582")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 29101")
    tran0.writeAction("slorii X16 X16 12 1455")
    tran0.writeAction("slorii X16 X16 12 1799")
    tran0.writeAction("slorii X16 X16 12 1547")
    tran0.writeAction("slorii X16 X16 12 2946")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 2376")
    tran0.writeAction("slorii X16 X16 12 1318")
    tran0.writeAction("slorii X16 X16 12 2885")
    tran0.writeAction("slorii X16 X16 12 1756")
    tran0.writeAction("slorii X16 X16 12 329")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 14641")
    tran0.writeAction("slorii X16 X16 12 2175")
    tran0.writeAction("slorii X16 X16 12 2699")
    tran0.writeAction("slorii X16 X16 12 1969")
    tran0.writeAction("slorii X16 X16 12 2141")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 45689")
    tran0.writeAction("slorii X16 X16 12 2570")
    tran0.writeAction("slorii X16 X16 12 2073")
    tran0.writeAction("slorii X16 X16 12 2673")
    tran0.writeAction("slorii X16 X16 12 2456")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 29829")
    tran0.writeAction("slorii X16 X16 12 2855")
    tran0.writeAction("slorii X16 X16 12 3068")
    tran0.writeAction("slorii X16 X16 12 2651")
    tran0.writeAction("slorii X16 X16 12 1591")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 44672")
    tran0.writeAction("slorii X16 X16 12 280")
    tran0.writeAction("slorii X16 X16 12 2645")
    tran0.writeAction("slorii X16 X16 12 264")
    tran0.writeAction("slorii X16 X16 12 489")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 32045")
    tran0.writeAction("slorii X16 X16 12 169")
    tran0.writeAction("slorii X16 X16 12 1489")
    tran0.writeAction("slorii X16 X16 12 1543")
    tran0.writeAction("slorii X16 X16 12 4031")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 1")
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
    tran1 = state1.writeTransition("basic", state1, state2, 191)
    tran3 = state1.writeTransition("basic_with_action", state1, state2, 255)
    tran3.writeAction("movir X30 8")
    tran3.writeAction("movir X29 8")
    tran3.writeAction("movir X28 8")
    tran3.writeAction("movir X27 8")
    tran3.writeAction("movir X26 8")
    tran3.writeAction("movir X25 8")
    tran3.writeAction("movir X24 8")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("basic", state2, state2, 125)
    tran4 = state2.writeTransition("basic_with_action", state2, state1, 255)
    tran4.writeAction("addi X5 X17 0")
    tran4.writeAction("movir X31 8")
    tran4.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa