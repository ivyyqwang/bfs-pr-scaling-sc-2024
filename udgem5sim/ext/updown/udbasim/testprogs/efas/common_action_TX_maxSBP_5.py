from EFA_v2 import *
def common_action_TX_maxSBP_5():
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
    tran0 = state.writeTransition("commonCarry_with_action", state, state1, 1)
    tran0.writeAction("movir X17 0")
    tran0.writeAction("add X7 X17 X17")
    tran0.writeAction("movir X16 47560")
    tran0.writeAction("slorii X16 X16 12 1319")
    tran0.writeAction("slorii X16 X16 12 3186")
    tran0.writeAction("slorii X16 X16 12 343")
    tran0.writeAction("slorii X16 X16 12 1960")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 55694")
    tran0.writeAction("slorii X16 X16 12 1429")
    tran0.writeAction("slorii X16 X16 12 780")
    tran0.writeAction("slorii X16 X16 12 3411")
    tran0.writeAction("slorii X16 X16 12 117")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 28337")
    tran0.writeAction("slorii X16 X16 12 810")
    tran0.writeAction("slorii X16 X16 12 1974")
    tran0.writeAction("slorii X16 X16 12 2580")
    tran0.writeAction("slorii X16 X16 12 2439")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 42556")
    tran0.writeAction("slorii X16 X16 12 2691")
    tran0.writeAction("slorii X16 X16 12 1589")
    tran0.writeAction("slorii X16 X16 12 1251")
    tran0.writeAction("slorii X16 X16 12 1519")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 1408")
    tran0.writeAction("slorii X16 X16 12 1010")
    tran0.writeAction("slorii X16 X16 12 3575")
    tran0.writeAction("slorii X16 X16 12 2852")
    tran0.writeAction("slorii X16 X16 12 1876")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 28742")
    tran0.writeAction("slorii X16 X16 12 3840")
    tran0.writeAction("slorii X16 X16 12 277")
    tran0.writeAction("slorii X16 X16 12 4041")
    tran0.writeAction("slorii X16 X16 12 2498")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 9043")
    tran0.writeAction("slorii X16 X16 12 946")
    tran0.writeAction("slorii X16 X16 12 3733")
    tran0.writeAction("slorii X16 X16 12 1445")
    tran0.writeAction("slorii X16 X16 12 1787")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 60461")
    tran0.writeAction("slorii X16 X16 12 3636")
    tran0.writeAction("slorii X16 X16 12 1050")
    tran0.writeAction("slorii X16 X16 12 1900")
    tran0.writeAction("slorii X16 X16 12 1541")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 47560")
    tran0.writeAction("slorii X16 X16 12 1319")
    tran0.writeAction("slorii X16 X16 12 3186")
    tran0.writeAction("slorii X16 X16 12 343")
    tran0.writeAction("slorii X16 X16 12 1960")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 3")
    tran0.writeAction("sli X17 X17 36")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 6")
    tran0.writeAction("sli X17 X17 32")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("add X7 X31 X31")
    tran0.writeAction("movir X20 0")
    tran0.writeAction("sli X31 X21 3")
    tran0.writeAction("add X21 X20 X5")
    tran0.writeAction("movlsb X31")
    tran0.writeAction("addi X20 X17 6")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("commonCarry_with_action", state1, state2, 0)
    tran1.writeAction("addi X5 X16 0")
    tran1.writeAction("movir X30 1")
    tran1.writeAction("lastact")
    tran2 = state2.writeTransition("commonCarry_with_action", state2, state2, 0)
    tran2.writeAction("addi X5 X17 0")
    tran2.writeAction("movir X31 2")
    tran2.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa
