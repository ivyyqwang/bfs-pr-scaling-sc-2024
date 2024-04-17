from EFA_v2 import *
def basic_action1_with_lastact_TX_2():
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
    tran0.writeAction("movir X16 36950")
    tran0.writeAction("slorii X16 X16 12 885")
    tran0.writeAction("slorii X16 X16 12 1086")
    tran0.writeAction("slorii X16 X16 12 955")
    tran0.writeAction("slorii X16 X16 12 1080")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 59627")
    tran0.writeAction("slorii X16 X16 12 3675")
    tran0.writeAction("slorii X16 X16 12 841")
    tran0.writeAction("slorii X16 X16 12 1882")
    tran0.writeAction("slorii X16 X16 12 1372")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 37399")
    tran0.writeAction("slorii X16 X16 12 1700")
    tran0.writeAction("slorii X16 X16 12 2688")
    tran0.writeAction("slorii X16 X16 12 2282")
    tran0.writeAction("slorii X16 X16 12 1091")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 20510")
    tran0.writeAction("slorii X16 X16 12 1867")
    tran0.writeAction("slorii X16 X16 12 262")
    tran0.writeAction("slorii X16 X16 12 2685")
    tran0.writeAction("slorii X16 X16 12 149")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 11661")
    tran0.writeAction("slorii X16 X16 12 3355")
    tran0.writeAction("slorii X16 X16 12 2549")
    tran0.writeAction("slorii X16 X16 12 1605")
    tran0.writeAction("slorii X16 X16 12 3645")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 27605")
    tran0.writeAction("slorii X16 X16 12 527")
    tran0.writeAction("slorii X16 X16 12 2773")
    tran0.writeAction("slorii X16 X16 12 1704")
    tran0.writeAction("slorii X16 X16 12 3235")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 15596")
    tran0.writeAction("slorii X16 X16 12 1534")
    tran0.writeAction("slorii X16 X16 12 1403")
    tran0.writeAction("slorii X16 X16 12 1547")
    tran0.writeAction("slorii X16 X16 12 102")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 56378")
    tran0.writeAction("slorii X16 X16 12 4051")
    tran0.writeAction("slorii X16 X16 12 1907")
    tran0.writeAction("slorii X16 X16 12 568")
    tran0.writeAction("slorii X16 X16 12 3462")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 36950")
    tran0.writeAction("slorii X16 X16 12 885")
    tran0.writeAction("slorii X16 X16 12 1086")
    tran0.writeAction("slorii X16 X16 12 955")
    tran0.writeAction("slorii X16 X16 12 1080")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 8")
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
    tran0.writeAction("addi X20 X17 24")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("basic_with_action", state1, state2, 56)
    tran1.writeAction("movir X30 7")
    tran1.writeAction("lastact")
    tran3 = state1.writeTransition("basic_with_action", state1, state2, 255)
    tran3.writeAction("movir X30 8")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("basic_with_action", state2, state2, 180)
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
