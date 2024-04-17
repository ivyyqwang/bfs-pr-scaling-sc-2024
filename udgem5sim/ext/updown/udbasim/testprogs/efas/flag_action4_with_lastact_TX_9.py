from EFA_v2 import *
def flag_action4_with_lastact_TX_9():
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
    tran0.writeAction("movir X16 47652")
    tran0.writeAction("slorii X16 X16 12 3360")
    tran0.writeAction("slorii X16 X16 12 3326")
    tran0.writeAction("slorii X16 X16 12 1728")
    tran0.writeAction("slorii X16 X16 12 1115")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 49668")
    tran0.writeAction("slorii X16 X16 12 3217")
    tran0.writeAction("slorii X16 X16 12 3283")
    tran0.writeAction("slorii X16 X16 12 3333")
    tran0.writeAction("slorii X16 X16 12 1879")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 39140")
    tran0.writeAction("slorii X16 X16 12 1521")
    tran0.writeAction("slorii X16 X16 12 2345")
    tran0.writeAction("slorii X16 X16 12 3907")
    tran0.writeAction("slorii X16 X16 12 2170")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 49765")
    tran0.writeAction("slorii X16 X16 12 3562")
    tran0.writeAction("slorii X16 X16 12 1134")
    tran0.writeAction("slorii X16 X16 12 386")
    tran0.writeAction("slorii X16 X16 12 2070")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 3310")
    tran0.writeAction("slorii X16 X16 12 745")
    tran0.writeAction("slorii X16 X16 12 3088")
    tran0.writeAction("slorii X16 X16 12 2025")
    tran0.writeAction("slorii X16 X16 12 1524")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 31488")
    tran0.writeAction("slorii X16 X16 12 283")
    tran0.writeAction("slorii X16 X16 12 3730")
    tran0.writeAction("slorii X16 X16 12 1342")
    tran0.writeAction("slorii X16 X16 12 1455")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 59032")
    tran0.writeAction("slorii X16 X16 12 3531")
    tran0.writeAction("slorii X16 X16 12 469")
    tran0.writeAction("slorii X16 X16 12 3449")
    tran0.writeAction("slorii X16 X16 12 92")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 50221")
    tran0.writeAction("slorii X16 X16 12 1210")
    tran0.writeAction("slorii X16 X16 12 3877")
    tran0.writeAction("slorii X16 X16 12 2023")
    tran0.writeAction("slorii X16 X16 12 987")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 47652")
    tran0.writeAction("slorii X16 X16 12 3360")
    tran0.writeAction("slorii X16 X16 12 3326")
    tran0.writeAction("slorii X16 X16 12 1728")
    tran0.writeAction("slorii X16 X16 12 1115")
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
    tran0.writeAction("movir X16 160")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("flagCarry_with_action", state1, state2, 160)
    tran1.writeAction("movir X16 188")
    tran1.writeAction("movir X30 7")
    tran1.writeAction("movir X29 7")
    tran1.writeAction("movir X28 7")
    tran1.writeAction("lastact")
    tran3 = state1.writeTransition("flagCarry_with_action", state1, state2, 255)
    tran3.writeAction("movir X16 255")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("flagCarry_with_action", state2, state2, 188)
    tran2.writeAction("addi X5 X17 0")
    tran2.writeAction("movir X31 7")
    tran2.writeAction("movir X31 8")
    tran2.writeAction("movir X31 9")
    tran2.writeAction("yieldt")
    tran4 = state2.writeTransition("flagCarry_with_action", state2, state1, 255)
    tran4.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa
