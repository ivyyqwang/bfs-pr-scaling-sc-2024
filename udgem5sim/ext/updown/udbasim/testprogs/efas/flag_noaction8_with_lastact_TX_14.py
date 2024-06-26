from EFA_v2 import *
def flag_noaction8_with_lastact_TX_14():
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
    tran0.writeAction("movir X16 30253")
    tran0.writeAction("slorii X16 X16 12 1175")
    tran0.writeAction("slorii X16 X16 12 3699")
    tran0.writeAction("slorii X16 X16 12 3994")
    tran0.writeAction("slorii X16 X16 12 2421")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 55276")
    tran0.writeAction("slorii X16 X16 12 1426")
    tran0.writeAction("slorii X16 X16 12 3991")
    tran0.writeAction("slorii X16 X16 12 153")
    tran0.writeAction("slorii X16 X16 12 3525")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 31264")
    tran0.writeAction("slorii X16 X16 12 741")
    tran0.writeAction("slorii X16 X16 12 3591")
    tran0.writeAction("slorii X16 X16 12 591")
    tran0.writeAction("slorii X16 X16 12 808")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 54532")
    tran0.writeAction("slorii X16 X16 12 73")
    tran0.writeAction("slorii X16 X16 12 1730")
    tran0.writeAction("slorii X16 X16 12 584")
    tran0.writeAction("slorii X16 X16 12 2128")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 35986")
    tran0.writeAction("slorii X16 X16 12 3595")
    tran0.writeAction("slorii X16 X16 12 673")
    tran0.writeAction("slorii X16 X16 12 3791")
    tran0.writeAction("slorii X16 X16 12 3314")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 47725")
    tran0.writeAction("slorii X16 X16 12 3543")
    tran0.writeAction("slorii X16 X16 12 802")
    tran0.writeAction("slorii X16 X16 12 2939")
    tran0.writeAction("slorii X16 X16 12 2568")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 46429")
    tran0.writeAction("slorii X16 X16 12 4074")
    tran0.writeAction("slorii X16 X16 12 3365")
    tran0.writeAction("slorii X16 X16 12 3704")
    tran0.writeAction("slorii X16 X16 12 3717")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 57822")
    tran0.writeAction("slorii X16 X16 12 3394")
    tran0.writeAction("slorii X16 X16 12 284")
    tran0.writeAction("slorii X16 X16 12 1551")
    tran0.writeAction("slorii X16 X16 12 3205")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 30253")
    tran0.writeAction("slorii X16 X16 12 1175")
    tran0.writeAction("slorii X16 X16 12 3699")
    tran0.writeAction("slorii X16 X16 12 3994")
    tran0.writeAction("slorii X16 X16 12 2421")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 4")
    tran0.writeAction("sli X17 X17 36")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 4")
    tran0.writeAction("sli X17 X17 32")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X20 0")
    tran0.writeAction("add X20 X7 X5")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("addi X20 X17 12")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("movir X16 112")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("flagCarry", state1, state2, 112)
    tran3 = state1.writeTransition("flagCarry_with_action", state1, state2, 255)
    tran3.writeAction("movir X16 255")
    tran3.writeAction("movir X30 8")
    tran3.writeAction("movir X30 9")
    tran3.writeAction("movir X30 10")
    tran3.writeAction("movir X30 11")
    tran3.writeAction("movir X30 12")
    tran3.writeAction("movir X30 13")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("flagCarry_with_action", state2, state2, 112)
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
