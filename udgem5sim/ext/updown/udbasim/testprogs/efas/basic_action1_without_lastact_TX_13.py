from EFA_v2 import *
def basic_action1_without_lastact_TX_13():
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
    tran0.writeAction("movir X16 10397")
    tran0.writeAction("slorii X16 X16 12 763")
    tran0.writeAction("slorii X16 X16 12 2045")
    tran0.writeAction("slorii X16 X16 12 1204")
    tran0.writeAction("slorii X16 X16 12 1215")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 29292")
    tran0.writeAction("slorii X16 X16 12 719")
    tran0.writeAction("slorii X16 X16 12 2354")
    tran0.writeAction("slorii X16 X16 12 3062")
    tran0.writeAction("slorii X16 X16 12 857")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 7841")
    tran0.writeAction("slorii X16 X16 12 671")
    tran0.writeAction("slorii X16 X16 12 1382")
    tran0.writeAction("slorii X16 X16 12 3918")
    tran0.writeAction("slorii X16 X16 12 3978")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 10331")
    tran0.writeAction("slorii X16 X16 12 2484")
    tran0.writeAction("slorii X16 X16 12 2831")
    tran0.writeAction("slorii X16 X16 12 3516")
    tran0.writeAction("slorii X16 X16 12 2590")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 17398")
    tran0.writeAction("slorii X16 X16 12 296")
    tran0.writeAction("slorii X16 X16 12 2082")
    tran0.writeAction("slorii X16 X16 12 2890")
    tran0.writeAction("slorii X16 X16 12 2769")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 6781")
    tran0.writeAction("slorii X16 X16 12 2871")
    tran0.writeAction("slorii X16 X16 12 3203")
    tran0.writeAction("slorii X16 X16 12 548")
    tran0.writeAction("slorii X16 X16 12 762")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 16450")
    tran0.writeAction("slorii X16 X16 12 659")
    tran0.writeAction("slorii X16 X16 12 2361")
    tran0.writeAction("slorii X16 X16 12 2823")
    tran0.writeAction("slorii X16 X16 12 399")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 52569")
    tran0.writeAction("slorii X16 X16 12 2741")
    tran0.writeAction("slorii X16 X16 12 3346")
    tran0.writeAction("slorii X16 X16 12 1118")
    tran0.writeAction("slorii X16 X16 12 2358")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 10397")
    tran0.writeAction("slorii X16 X16 12 763")
    tran0.writeAction("slorii X16 X16 12 2045")
    tran0.writeAction("slorii X16 X16 12 1204")
    tran0.writeAction("slorii X16 X16 12 1215")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 3")
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
    tran1 = state1.writeTransition("basic_with_action", state1, state2, 7)
    tran1.writeAction("movir X30 7")
    tran3 = state1.writeTransition("basic_with_action", state1, state2, 255)
    tran3.writeAction("movir X30 8")
    tran2 = state2.writeTransition("basic_with_action", state2, state2, 5)
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
