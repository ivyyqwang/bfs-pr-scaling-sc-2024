from EFA_v2 import *
def basic_action1_without_lastact_TX_15():
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
    tran0.writeAction("movir X16 46545")
    tran0.writeAction("slorii X16 X16 12 2153")
    tran0.writeAction("slorii X16 X16 12 3232")
    tran0.writeAction("slorii X16 X16 12 2680")
    tran0.writeAction("slorii X16 X16 12 1224")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 23367")
    tran0.writeAction("slorii X16 X16 12 1920")
    tran0.writeAction("slorii X16 X16 12 4082")
    tran0.writeAction("slorii X16 X16 12 1227")
    tran0.writeAction("slorii X16 X16 12 2267")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 35150")
    tran0.writeAction("slorii X16 X16 12 2559")
    tran0.writeAction("slorii X16 X16 12 859")
    tran0.writeAction("slorii X16 X16 12 3893")
    tran0.writeAction("slorii X16 X16 12 2326")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 2164")
    tran0.writeAction("slorii X16 X16 12 3585")
    tran0.writeAction("slorii X16 X16 12 3471")
    tran0.writeAction("slorii X16 X16 12 1985")
    tran0.writeAction("slorii X16 X16 12 1760")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 13762")
    tran0.writeAction("slorii X16 X16 12 2016")
    tran0.writeAction("slorii X16 X16 12 3131")
    tran0.writeAction("slorii X16 X16 12 1248")
    tran0.writeAction("slorii X16 X16 12 2484")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 41224")
    tran0.writeAction("slorii X16 X16 12 3018")
    tran0.writeAction("slorii X16 X16 12 67")
    tran0.writeAction("slorii X16 X16 12 2240")
    tran0.writeAction("slorii X16 X16 12 635")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 60102")
    tran0.writeAction("slorii X16 X16 12 1355")
    tran0.writeAction("slorii X16 X16 12 1418")
    tran0.writeAction("slorii X16 X16 12 2963")
    tran0.writeAction("slorii X16 X16 12 502")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 62022")
    tran0.writeAction("slorii X16 X16 12 1220")
    tran0.writeAction("slorii X16 X16 12 1461")
    tran0.writeAction("slorii X16 X16 12 3115")
    tran0.writeAction("slorii X16 X16 12 1452")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 46545")
    tran0.writeAction("slorii X16 X16 12 2153")
    tran0.writeAction("slorii X16 X16 12 3232")
    tran0.writeAction("slorii X16 X16 12 2680")
    tran0.writeAction("slorii X16 X16 12 1224")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 7")
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
    tran0.writeAction("addi X20 X17 21")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("basic_with_action", state1, state2, 72)
    tran1.writeAction("movir X30 7")
    tran3 = state1.writeTransition("basic_with_action", state1, state2, 255)
    tran3.writeAction("movir X30 8")
    tran2 = state2.writeTransition("basic_with_action", state2, state2, 9)
    tran2.writeAction("addi X5 X17 0")
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
