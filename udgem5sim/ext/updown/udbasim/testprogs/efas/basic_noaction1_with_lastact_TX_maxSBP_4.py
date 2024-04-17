from EFA_v2 import *
def basic_noaction1_with_lastact_TX_maxSBP_4():
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
    tran0.writeAction("movir X16 37659")
    tran0.writeAction("slorii X16 X16 12 2448")
    tran0.writeAction("slorii X16 X16 12 2535")
    tran0.writeAction("slorii X16 X16 12 2264")
    tran0.writeAction("slorii X16 X16 12 1904")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 37293")
    tran0.writeAction("slorii X16 X16 12 1401")
    tran0.writeAction("slorii X16 X16 12 832")
    tran0.writeAction("slorii X16 X16 12 1797")
    tran0.writeAction("slorii X16 X16 12 755")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 24411")
    tran0.writeAction("slorii X16 X16 12 53")
    tran0.writeAction("slorii X16 X16 12 2405")
    tran0.writeAction("slorii X16 X16 12 2944")
    tran0.writeAction("slorii X16 X16 12 733")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 27751")
    tran0.writeAction("slorii X16 X16 12 6")
    tran0.writeAction("slorii X16 X16 12 3902")
    tran0.writeAction("slorii X16 X16 12 2438")
    tran0.writeAction("slorii X16 X16 12 1861")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 59989")
    tran0.writeAction("slorii X16 X16 12 4013")
    tran0.writeAction("slorii X16 X16 12 1508")
    tran0.writeAction("slorii X16 X16 12 91")
    tran0.writeAction("slorii X16 X16 12 3103")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 16787")
    tran0.writeAction("slorii X16 X16 12 725")
    tran0.writeAction("slorii X16 X16 12 3291")
    tran0.writeAction("slorii X16 X16 12 1557")
    tran0.writeAction("slorii X16 X16 12 418")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 42660")
    tran0.writeAction("slorii X16 X16 12 2768")
    tran0.writeAction("slorii X16 X16 12 471")
    tran0.writeAction("slorii X16 X16 12 2529")
    tran0.writeAction("slorii X16 X16 12 3114")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 10005")
    tran0.writeAction("slorii X16 X16 12 1945")
    tran0.writeAction("slorii X16 X16 12 2053")
    tran0.writeAction("slorii X16 X16 12 25")
    tran0.writeAction("slorii X16 X16 12 3718")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 37659")
    tran0.writeAction("slorii X16 X16 12 2448")
    tran0.writeAction("slorii X16 X16 12 2535")
    tran0.writeAction("slorii X16 X16 12 2264")
    tran0.writeAction("slorii X16 X16 12 1904")
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
    tran1 = state1.writeTransition("basic", state1, state2, 112)
    tran3 = state1.writeTransition("basic_with_action", state1, state2, 255)
    tran3.writeAction("movir X30 8")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("basic", state2, state2, 7)
    tran4 = state2.writeTransition("basic_with_action", state2, state1, 255)
    tran4.writeAction("addi X5 X17 0")
    tran4.writeAction("movir X31 8")
    tran4.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa
