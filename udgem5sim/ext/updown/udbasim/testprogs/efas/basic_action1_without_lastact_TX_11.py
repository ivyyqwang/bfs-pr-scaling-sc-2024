from EFA_v2 import *
def basic_action1_without_lastact_TX_11():
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
    tran0.writeAction("movir X16 25066")
    tran0.writeAction("slorii X16 X16 12 1361")
    tran0.writeAction("slorii X16 X16 12 2896")
    tran0.writeAction("slorii X16 X16 12 3959")
    tran0.writeAction("slorii X16 X16 12 639")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 39283")
    tran0.writeAction("slorii X16 X16 12 469")
    tran0.writeAction("slorii X16 X16 12 1315")
    tran0.writeAction("slorii X16 X16 12 537")
    tran0.writeAction("slorii X16 X16 12 3885")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 5856")
    tran0.writeAction("slorii X16 X16 12 537")
    tran0.writeAction("slorii X16 X16 12 366")
    tran0.writeAction("slorii X16 X16 12 3695")
    tran0.writeAction("slorii X16 X16 12 2116")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 44160")
    tran0.writeAction("slorii X16 X16 12 3450")
    tran0.writeAction("slorii X16 X16 12 1745")
    tran0.writeAction("slorii X16 X16 12 1346")
    tran0.writeAction("slorii X16 X16 12 3499")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 4973")
    tran0.writeAction("slorii X16 X16 12 2562")
    tran0.writeAction("slorii X16 X16 12 4010")
    tran0.writeAction("slorii X16 X16 12 1471")
    tran0.writeAction("slorii X16 X16 12 2283")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 11182")
    tran0.writeAction("slorii X16 X16 12 3996")
    tran0.writeAction("slorii X16 X16 12 3358")
    tran0.writeAction("slorii X16 X16 12 3199")
    tran0.writeAction("slorii X16 X16 12 3416")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 43559")
    tran0.writeAction("slorii X16 X16 12 3261")
    tran0.writeAction("slorii X16 X16 12 1149")
    tran0.writeAction("slorii X16 X16 12 1221")
    tran0.writeAction("slorii X16 X16 12 971")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 28979")
    tran0.writeAction("slorii X16 X16 12 3829")
    tran0.writeAction("slorii X16 X16 12 1415")
    tran0.writeAction("slorii X16 X16 12 2051")
    tran0.writeAction("slorii X16 X16 12 387")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 25066")
    tran0.writeAction("slorii X16 X16 12 1361")
    tran0.writeAction("slorii X16 X16 12 2896")
    tran0.writeAction("slorii X16 X16 12 3959")
    tran0.writeAction("slorii X16 X16 12 639")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 3")
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
    tran1 = state1.writeTransition("basic_with_action", state1, state2, 7)
    tran1.writeAction("movir X30 7")
    tran3 = state1.writeTransition("basic_with_action", state1, state2, 255)
    tran3.writeAction("movir X30 8")
    tran2 = state2.writeTransition("basic_with_action", state2, state2, 2)
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