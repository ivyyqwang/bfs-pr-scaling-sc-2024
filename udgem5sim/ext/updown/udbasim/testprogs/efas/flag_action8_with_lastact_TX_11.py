from EFA_v2 import *
def flag_action8_with_lastact_TX_11():
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
    tran0.writeAction("movir X16 11466")
    tran0.writeAction("slorii X16 X16 12 4062")
    tran0.writeAction("slorii X16 X16 12 2897")
    tran0.writeAction("slorii X16 X16 12 700")
    tran0.writeAction("slorii X16 X16 12 311")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 64275")
    tran0.writeAction("slorii X16 X16 12 1289")
    tran0.writeAction("slorii X16 X16 12 1657")
    tran0.writeAction("slorii X16 X16 12 2740")
    tran0.writeAction("slorii X16 X16 12 3623")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 6056")
    tran0.writeAction("slorii X16 X16 12 3266")
    tran0.writeAction("slorii X16 X16 12 861")
    tran0.writeAction("slorii X16 X16 12 267")
    tran0.writeAction("slorii X16 X16 12 2884")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 33108")
    tran0.writeAction("slorii X16 X16 12 2836")
    tran0.writeAction("slorii X16 X16 12 1721")
    tran0.writeAction("slorii X16 X16 12 2050")
    tran0.writeAction("slorii X16 X16 12 3188")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 39496")
    tran0.writeAction("slorii X16 X16 12 1590")
    tran0.writeAction("slorii X16 X16 12 3908")
    tran0.writeAction("slorii X16 X16 12 1552")
    tran0.writeAction("slorii X16 X16 12 4030")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 24172")
    tran0.writeAction("slorii X16 X16 12 518")
    tran0.writeAction("slorii X16 X16 12 2217")
    tran0.writeAction("slorii X16 X16 12 2018")
    tran0.writeAction("slorii X16 X16 12 211")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 30078")
    tran0.writeAction("slorii X16 X16 12 1062")
    tran0.writeAction("slorii X16 X16 12 192")
    tran0.writeAction("slorii X16 X16 12 1730")
    tran0.writeAction("slorii X16 X16 12 94")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 24443")
    tran0.writeAction("slorii X16 X16 12 2450")
    tran0.writeAction("slorii X16 X16 12 962")
    tran0.writeAction("slorii X16 X16 12 3014")
    tran0.writeAction("slorii X16 X16 12 700")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 11466")
    tran0.writeAction("slorii X16 X16 12 4062")
    tran0.writeAction("slorii X16 X16 12 2897")
    tran0.writeAction("slorii X16 X16 12 700")
    tran0.writeAction("slorii X16 X16 12 311")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 4")
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
    tran0.writeAction("addi X20 X17 18")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("movir X16 196")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("flagCarry_with_action", state1, state2, 196)
    tran1.writeAction("movir X16 47")
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
    tran2 = state2.writeTransition("flagCarry_with_action", state2, state2, 47)
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
