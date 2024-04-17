from EFA_v2 import *
def flag_action8_with_lastact_TX_0():
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
    tran0 = state.writeTransition("flagCarry_with_action", state, state1, 1)
    tran0.writeAction("movir X17 0")
    tran0.writeAction("add X7 X17 X17")
    tran0.writeAction("movir X16 64514")
    tran0.writeAction("slorii X16 X16 12 2088")
    tran0.writeAction("slorii X16 X16 12 2029")
    tran0.writeAction("slorii X16 X16 12 2846")
    tran0.writeAction("slorii X16 X16 12 1479")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 64414")
    tran0.writeAction("slorii X16 X16 12 2963")
    tran0.writeAction("slorii X16 X16 12 2880")
    tran0.writeAction("slorii X16 X16 12 811")
    tran0.writeAction("slorii X16 X16 12 262")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 33043")
    tran0.writeAction("slorii X16 X16 12 3918")
    tran0.writeAction("slorii X16 X16 12 1458")
    tran0.writeAction("slorii X16 X16 12 2160")
    tran0.writeAction("slorii X16 X16 12 1675")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 54037")
    tran0.writeAction("slorii X16 X16 12 3151")
    tran0.writeAction("slorii X16 X16 12 4044")
    tran0.writeAction("slorii X16 X16 12 3497")
    tran0.writeAction("slorii X16 X16 12 1559")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 57624")
    tran0.writeAction("slorii X16 X16 12 642")
    tran0.writeAction("slorii X16 X16 12 1324")
    tran0.writeAction("slorii X16 X16 12 3283")
    tran0.writeAction("slorii X16 X16 12 3979")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 36091")
    tran0.writeAction("slorii X16 X16 12 678")
    tran0.writeAction("slorii X16 X16 12 460")
    tran0.writeAction("slorii X16 X16 12 2051")
    tran0.writeAction("slorii X16 X16 12 830")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 20800")
    tran0.writeAction("slorii X16 X16 12 3901")
    tran0.writeAction("slorii X16 X16 12 2841")
    tran0.writeAction("slorii X16 X16 12 1787")
    tran0.writeAction("slorii X16 X16 12 1722")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 62272")
    tran0.writeAction("slorii X16 X16 12 3080")
    tran0.writeAction("slorii X16 X16 12 1610")
    tran0.writeAction("slorii X16 X16 12 3602")
    tran0.writeAction("slorii X16 X16 12 2741")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 64514")
    tran0.writeAction("slorii X16 X16 12 2088")
    tran0.writeAction("slorii X16 X16 12 2029")
    tran0.writeAction("slorii X16 X16 12 2846")
    tran0.writeAction("slorii X16 X16 12 1479")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 8")
    tran0.writeAction("sli X17 X17 36")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 8")
    tran0.writeAction("sli X17 X17 32")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X20 0")
    tran0.writeAction("add X20 X7 X5")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("addi X20 X17 24")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("movir X16 112")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("flagCarry_with_action", state1, state2, 112)
    tran1.writeAction("movir X16 54")
    tran1.writeAction("movir X30 7")
    tran1.writeAction("movir X29 7")
    tran1.writeAction("movir X28 7")
    tran1.writeAction("movir X27 7")
    tran1.writeAction("movir X26 7")
    tran1.writeAction("movir X25 7")
    tran1.writeAction("movir X24 7")
    tran1.writeAction("lastact")
    tran3 = state1.writeTransition("flagCarry_with_action", state1, state2, 255)
    tran3.writeAction("movir X16 255")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("flagCarry_with_action", state2, state2, 54)
    tran2.writeAction("addi X5 X17 0")
    tran2.writeAction("movir X31 7")
    tran2.writeAction("movir X31 8")
    tran2.writeAction("movir X31 9")
    tran2.writeAction("movir X31 10")
    tran2.writeAction("movir X31 11")
    tran2.writeAction("movir X31 12")
    tran2.writeAction("movir X31 13")
    tran2.writeAction("yieldt")
    tran4 = state2.writeTransition("flagCarry_with_action", state2, state1, 255)
    tran4.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa
