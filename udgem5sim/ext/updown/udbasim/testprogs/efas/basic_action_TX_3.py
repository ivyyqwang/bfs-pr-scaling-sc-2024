from EFA_v2 import *
def basic_action_TX_3():
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
    tran0.writeAction("movir X16 29696")
    tran0.writeAction("slorii X16 X16 12 2894")
    tran0.writeAction("slorii X16 X16 12 520")
    tran0.writeAction("slorii X16 X16 12 41")
    tran0.writeAction("slorii X16 X16 12 3184")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 31810")
    tran0.writeAction("slorii X16 X16 12 3409")
    tran0.writeAction("slorii X16 X16 12 1769")
    tran0.writeAction("slorii X16 X16 12 1723")
    tran0.writeAction("slorii X16 X16 12 263")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 15233")
    tran0.writeAction("slorii X16 X16 12 1367")
    tran0.writeAction("slorii X16 X16 12 3793")
    tran0.writeAction("slorii X16 X16 12 3056")
    tran0.writeAction("slorii X16 X16 12 1244")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 57967")
    tran0.writeAction("slorii X16 X16 12 1341")
    tran0.writeAction("slorii X16 X16 12 1545")
    tran0.writeAction("slorii X16 X16 12 3844")
    tran0.writeAction("slorii X16 X16 12 2580")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 21061")
    tran0.writeAction("slorii X16 X16 12 38")
    tran0.writeAction("slorii X16 X16 12 3536")
    tran0.writeAction("slorii X16 X16 12 2658")
    tran0.writeAction("slorii X16 X16 12 4020")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 22702")
    tran0.writeAction("slorii X16 X16 12 1192")
    tran0.writeAction("slorii X16 X16 12 1951")
    tran0.writeAction("slorii X16 X16 12 1948")
    tran0.writeAction("slorii X16 X16 12 939")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 32087")
    tran0.writeAction("slorii X16 X16 12 2874")
    tran0.writeAction("slorii X16 X16 12 422")
    tran0.writeAction("slorii X16 X16 12 2980")
    tran0.writeAction("slorii X16 X16 12 3276")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 51504")
    tran0.writeAction("slorii X16 X16 12 1753")
    tran0.writeAction("slorii X16 X16 12 3839")
    tran0.writeAction("slorii X16 X16 12 3034")
    tran0.writeAction("slorii X16 X16 12 1315")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 29696")
    tran0.writeAction("slorii X16 X16 12 2894")
    tran0.writeAction("slorii X16 X16 12 520")
    tran0.writeAction("slorii X16 X16 12 41")
    tran0.writeAction("slorii X16 X16 12 3184")
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
    tran1 = state1.writeTransition("basic_with_action", state1, state2, 112)
    tran1.writeAction("addi X5 X16 0")
    tran1.writeAction("movir X30 5")
    tran1.writeAction("movir X29 5")
    tran1.writeAction("lastact")
    tran3 = state1.writeTransition("basic_with_action", state1, state2, 255)
    tran3.writeAction("addi X5 X16 0")
    tran3.writeAction("movir X30 6")
    tran3.writeAction("movir X29 6")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("basic_with_action", state2, state2, 156)
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