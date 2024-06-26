from EFA_v2 import *
def basic_action4_with_lastact_TX_maxSBP_7():
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
    tran0.writeAction("movir X16 33820")
    tran0.writeAction("slorii X16 X16 12 3789")
    tran0.writeAction("slorii X16 X16 12 1887")
    tran0.writeAction("slorii X16 X16 12 2972")
    tran0.writeAction("slorii X16 X16 12 2865")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 26696")
    tran0.writeAction("slorii X16 X16 12 2017")
    tran0.writeAction("slorii X16 X16 12 1008")
    tran0.writeAction("slorii X16 X16 12 3722")
    tran0.writeAction("slorii X16 X16 12 147")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 15935")
    tran0.writeAction("slorii X16 X16 12 763")
    tran0.writeAction("slorii X16 X16 12 1968")
    tran0.writeAction("slorii X16 X16 12 3168")
    tran0.writeAction("slorii X16 X16 12 3602")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 45928")
    tran0.writeAction("slorii X16 X16 12 3549")
    tran0.writeAction("slorii X16 X16 12 3378")
    tran0.writeAction("slorii X16 X16 12 943")
    tran0.writeAction("slorii X16 X16 12 1664")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 39659")
    tran0.writeAction("slorii X16 X16 12 269")
    tran0.writeAction("slorii X16 X16 12 250")
    tran0.writeAction("slorii X16 X16 12 941")
    tran0.writeAction("slorii X16 X16 12 65")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 4883")
    tran0.writeAction("slorii X16 X16 12 1643")
    tran0.writeAction("slorii X16 X16 12 781")
    tran0.writeAction("slorii X16 X16 12 2724")
    tran0.writeAction("slorii X16 X16 12 1829")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 10996")
    tran0.writeAction("slorii X16 X16 12 1100")
    tran0.writeAction("slorii X16 X16 12 1020")
    tran0.writeAction("slorii X16 X16 12 3738")
    tran0.writeAction("slorii X16 X16 12 2569")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 16129")
    tran0.writeAction("slorii X16 X16 12 1064")
    tran0.writeAction("slorii X16 X16 12 1686")
    tran0.writeAction("slorii X16 X16 12 3683")
    tran0.writeAction("slorii X16 X16 12 3576")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 33820")
    tran0.writeAction("slorii X16 X16 12 3789")
    tran0.writeAction("slorii X16 X16 12 1887")
    tran0.writeAction("slorii X16 X16 12 2972")
    tran0.writeAction("slorii X16 X16 12 2865")
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
    tran0.writeAction("addi X20 X17 7")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("basic_with_action", state1, state2, 49)
    tran1.writeAction("movir X30 7")
    tran1.writeAction("lastact")
    tran3 = state1.writeTransition("basic_with_action", state1, state2, 255)
    tran3.writeAction("addi X5 X16 8")
    tran3.writeAction("movir X30 8")
    tran3.writeAction("movir X29 8")
    tran3.writeAction("movir X28 8")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("basic_with_action", state2, state2, 22)
    tran2.writeAction("movir X30 7")
    tran4 = state2.writeTransition("basic_with_action", state2, state1, 255)
    tran4.writeAction("addi X5 X17 0")
    tran4.writeAction("movir X30 8")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa
