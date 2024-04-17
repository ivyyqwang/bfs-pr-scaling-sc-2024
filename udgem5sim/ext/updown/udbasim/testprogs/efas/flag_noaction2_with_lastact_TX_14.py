from EFA_v2 import *
def flag_noaction2_with_lastact_TX_14():
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
    tran0.writeAction("movir X16 55327")
    tran0.writeAction("slorii X16 X16 12 2588")
    tran0.writeAction("slorii X16 X16 12 1203")
    tran0.writeAction("slorii X16 X16 12 950")
    tran0.writeAction("slorii X16 X16 12 1072")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 59846")
    tran0.writeAction("slorii X16 X16 12 3357")
    tran0.writeAction("slorii X16 X16 12 92")
    tran0.writeAction("slorii X16 X16 12 2201")
    tran0.writeAction("slorii X16 X16 12 3230")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 32760")
    tran0.writeAction("slorii X16 X16 12 3115")
    tran0.writeAction("slorii X16 X16 12 1365")
    tran0.writeAction("slorii X16 X16 12 2390")
    tran0.writeAction("slorii X16 X16 12 897")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 45022")
    tran0.writeAction("slorii X16 X16 12 1959")
    tran0.writeAction("slorii X16 X16 12 1138")
    tran0.writeAction("slorii X16 X16 12 3750")
    tran0.writeAction("slorii X16 X16 12 446")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 23053")
    tran0.writeAction("slorii X16 X16 12 2043")
    tran0.writeAction("slorii X16 X16 12 2551")
    tran0.writeAction("slorii X16 X16 12 318")
    tran0.writeAction("slorii X16 X16 12 1567")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 30763")
    tran0.writeAction("slorii X16 X16 12 3472")
    tran0.writeAction("slorii X16 X16 12 1722")
    tran0.writeAction("slorii X16 X16 12 1933")
    tran0.writeAction("slorii X16 X16 12 315")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 19750")
    tran0.writeAction("slorii X16 X16 12 474")
    tran0.writeAction("slorii X16 X16 12 1230")
    tran0.writeAction("slorii X16 X16 12 2911")
    tran0.writeAction("slorii X16 X16 12 2946")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 17889")
    tran0.writeAction("slorii X16 X16 12 2821")
    tran0.writeAction("slorii X16 X16 12 2243")
    tran0.writeAction("slorii X16 X16 12 2402")
    tran0.writeAction("slorii X16 X16 12 1753")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 55327")
    tran0.writeAction("slorii X16 X16 12 2588")
    tran0.writeAction("slorii X16 X16 12 1203")
    tran0.writeAction("slorii X16 X16 12 950")
    tran0.writeAction("slorii X16 X16 12 1072")
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
    tran0.writeAction("movir X16 66")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("flagCarry", state1, state2, 66)
    tran3 = state1.writeTransition("flagCarry_with_action", state1, state2, 255)
    tran3.writeAction("movir X16 255")
    tran3.writeAction("movir X30 8")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("flagCarry_with_action", state2, state2, 66)
    tran2.writeAction("addi X5 X17 0")
    tran2.writeAction("movir X31 7")
    tran2.writeAction("yieldt")
    tran4 = state2.writeTransition("flagCarry_with_action", state2, state1, 255)
    tran4.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa