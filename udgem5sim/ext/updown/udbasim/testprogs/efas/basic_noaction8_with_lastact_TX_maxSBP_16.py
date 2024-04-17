from EFA_v2 import *
def basic_noaction8_with_lastact_TX_maxSBP_16():
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
    tran0.writeAction("movir X16 49359")
    tran0.writeAction("slorii X16 X16 12 1301")
    tran0.writeAction("slorii X16 X16 12 1626")
    tran0.writeAction("slorii X16 X16 12 3051")
    tran0.writeAction("slorii X16 X16 12 128")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 59811")
    tran0.writeAction("slorii X16 X16 12 289")
    tran0.writeAction("slorii X16 X16 12 3438")
    tran0.writeAction("slorii X16 X16 12 1063")
    tran0.writeAction("slorii X16 X16 12 601")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 696")
    tran0.writeAction("slorii X16 X16 12 3891")
    tran0.writeAction("slorii X16 X16 12 1998")
    tran0.writeAction("slorii X16 X16 12 2487")
    tran0.writeAction("slorii X16 X16 12 3593")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 26780")
    tran0.writeAction("slorii X16 X16 12 3764")
    tran0.writeAction("slorii X16 X16 12 640")
    tran0.writeAction("slorii X16 X16 12 296")
    tran0.writeAction("slorii X16 X16 12 2790")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 29026")
    tran0.writeAction("slorii X16 X16 12 3685")
    tran0.writeAction("slorii X16 X16 12 2935")
    tran0.writeAction("slorii X16 X16 12 1670")
    tran0.writeAction("slorii X16 X16 12 1287")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 41792")
    tran0.writeAction("slorii X16 X16 12 1341")
    tran0.writeAction("slorii X16 X16 12 3076")
    tran0.writeAction("slorii X16 X16 12 1448")
    tran0.writeAction("slorii X16 X16 12 3420")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 48687")
    tran0.writeAction("slorii X16 X16 12 2112")
    tran0.writeAction("slorii X16 X16 12 2249")
    tran0.writeAction("slorii X16 X16 12 2737")
    tran0.writeAction("slorii X16 X16 12 3224")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 46956")
    tran0.writeAction("slorii X16 X16 12 2888")
    tran0.writeAction("slorii X16 X16 12 3787")
    tran0.writeAction("slorii X16 X16 12 1489")
    tran0.writeAction("slorii X16 X16 12 2018")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 49359")
    tran0.writeAction("slorii X16 X16 12 1301")
    tran0.writeAction("slorii X16 X16 12 1626")
    tran0.writeAction("slorii X16 X16 12 3051")
    tran0.writeAction("slorii X16 X16 12 128")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 36")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 4")
    tran0.writeAction("sli X17 X17 32")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("add X7 X31 X31")
    tran0.writeAction("movir X20 0")
    tran0.writeAction("sli X31 X21 3")
    tran0.writeAction("add X21 X20 X5")
    tran0.writeAction("movlsb X31")
    tran0.writeAction("addi X20 X17 4")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("basic", state1, state2, 0)
    tran3 = state1.writeTransition("basic_with_action", state1, state2, 255)
    tran3.writeAction("movir X30 8")
    tran3.writeAction("movir X29 8")
    tran3.writeAction("movir X28 8")
    tran3.writeAction("movir X27 8")
    tran3.writeAction("movir X26 8")
    tran3.writeAction("movir X25 8")
    tran3.writeAction("movir X24 8")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("basic", state2, state2, 0)
    tran4 = state2.writeTransition("basic_with_action", state2, state1, 255)
    tran4.writeAction("addi X5 X17 0")
    tran4.writeAction("movir X31 8")
    tran4.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa
