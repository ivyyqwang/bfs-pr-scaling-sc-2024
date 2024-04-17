from EFA_v2 import *
def basic_action2_without_lastact_TX_6():
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
    tran0.writeAction("movir X16 27195")
    tran0.writeAction("slorii X16 X16 12 3996")
    tran0.writeAction("slorii X16 X16 12 3744")
    tran0.writeAction("slorii X16 X16 12 933")
    tran0.writeAction("slorii X16 X16 12 3756")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 60799")
    tran0.writeAction("slorii X16 X16 12 2420")
    tran0.writeAction("slorii X16 X16 12 3444")
    tran0.writeAction("slorii X16 X16 12 1558")
    tran0.writeAction("slorii X16 X16 12 3")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 37333")
    tran0.writeAction("slorii X16 X16 12 2394")
    tran0.writeAction("slorii X16 X16 12 1628")
    tran0.writeAction("slorii X16 X16 12 997")
    tran0.writeAction("slorii X16 X16 12 209")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 9196")
    tran0.writeAction("slorii X16 X16 12 2068")
    tran0.writeAction("slorii X16 X16 12 1017")
    tran0.writeAction("slorii X16 X16 12 1114")
    tran0.writeAction("slorii X16 X16 12 4049")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 33827")
    tran0.writeAction("slorii X16 X16 12 928")
    tran0.writeAction("slorii X16 X16 12 306")
    tran0.writeAction("slorii X16 X16 12 1377")
    tran0.writeAction("slorii X16 X16 12 479")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 57564")
    tran0.writeAction("slorii X16 X16 12 2245")
    tran0.writeAction("slorii X16 X16 12 2761")
    tran0.writeAction("slorii X16 X16 12 3513")
    tran0.writeAction("slorii X16 X16 12 1539")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 47788")
    tran0.writeAction("slorii X16 X16 12 1983")
    tran0.writeAction("slorii X16 X16 12 3048")
    tran0.writeAction("slorii X16 X16 12 2099")
    tran0.writeAction("slorii X16 X16 12 2393")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 56649")
    tran0.writeAction("slorii X16 X16 12 470")
    tran0.writeAction("slorii X16 X16 12 850")
    tran0.writeAction("slorii X16 X16 12 1800")
    tran0.writeAction("slorii X16 X16 12 1676")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 27195")
    tran0.writeAction("slorii X16 X16 12 3996")
    tran0.writeAction("slorii X16 X16 12 3744")
    tran0.writeAction("slorii X16 X16 12 933")
    tran0.writeAction("slorii X16 X16 12 3756")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 36")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 5")
    tran0.writeAction("sli X17 X17 32")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("add X7 X31 X31")
    tran0.writeAction("movir X20 0")
    tran0.writeAction("sli X31 X21 3")
    tran0.writeAction("add X21 X20 X5")
    tran0.writeAction("movlsb X31")
    tran0.writeAction("addi X20 X17 15")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("basic_with_action", state1, state2, 0)
    tran1.writeAction("addi X5 X16 0")
    tran1.writeAction("movir X30 5")
    tran3 = state1.writeTransition("basic_with_action", state1, state2, 255)
    tran3.writeAction("addi X5 X16 0")
    tran3.writeAction("movir X30 6")
    tran2 = state2.writeTransition("basic_with_action", state2, state2, 1)
    tran2.writeAction("addi X5 X17 0")
    tran2.writeAction("movir X31 5")
    tran2.writeAction("yieldt")
    tran4 = state2.writeTransition("basic_with_action", state2, state1, 255)
    tran4.writeAction("addi X5 X17 0")
    tran4.writeAction("movir X31 6")
    tran4.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa
