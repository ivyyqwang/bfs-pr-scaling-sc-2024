from EFA_v2 import *
def flag_action4_with_lastact_TX_16():
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
    tran0.writeAction("movir X16 33595")
    tran0.writeAction("slorii X16 X16 12 1390")
    tran0.writeAction("slorii X16 X16 12 2288")
    tran0.writeAction("slorii X16 X16 12 1878")
    tran0.writeAction("slorii X16 X16 12 3039")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 10313")
    tran0.writeAction("slorii X16 X16 12 3138")
    tran0.writeAction("slorii X16 X16 12 1789")
    tran0.writeAction("slorii X16 X16 12 2222")
    tran0.writeAction("slorii X16 X16 12 3261")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 17063")
    tran0.writeAction("slorii X16 X16 12 723")
    tran0.writeAction("slorii X16 X16 12 2108")
    tran0.writeAction("slorii X16 X16 12 1273")
    tran0.writeAction("slorii X16 X16 12 1071")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 53064")
    tran0.writeAction("slorii X16 X16 12 2431")
    tran0.writeAction("slorii X16 X16 12 3713")
    tran0.writeAction("slorii X16 X16 12 755")
    tran0.writeAction("slorii X16 X16 12 2872")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 25597")
    tran0.writeAction("slorii X16 X16 12 2342")
    tran0.writeAction("slorii X16 X16 12 2797")
    tran0.writeAction("slorii X16 X16 12 3867")
    tran0.writeAction("slorii X16 X16 12 2213")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 45129")
    tran0.writeAction("slorii X16 X16 12 3422")
    tran0.writeAction("slorii X16 X16 12 2949")
    tran0.writeAction("slorii X16 X16 12 507")
    tran0.writeAction("slorii X16 X16 12 1187")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 58971")
    tran0.writeAction("slorii X16 X16 12 3170")
    tran0.writeAction("slorii X16 X16 12 41")
    tran0.writeAction("slorii X16 X16 12 3365")
    tran0.writeAction("slorii X16 X16 12 1482")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 53900")
    tran0.writeAction("slorii X16 X16 12 3903")
    tran0.writeAction("slorii X16 X16 12 4017")
    tran0.writeAction("slorii X16 X16 12 2742")
    tran0.writeAction("slorii X16 X16 12 3612")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 33595")
    tran0.writeAction("slorii X16 X16 12 1390")
    tran0.writeAction("slorii X16 X16 12 2288")
    tran0.writeAction("slorii X16 X16 12 1878")
    tran0.writeAction("slorii X16 X16 12 3039")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 4")
    tran0.writeAction("sli X17 X17 36")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 5")
    tran0.writeAction("sli X17 X17 32")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X20 0")
    tran0.writeAction("add X20 X7 X5")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("addi X20 X17 15")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("movir X16 208")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("flagCarry_with_action", state1, state2, 208)
    tran1.writeAction("movir X16 164")
    tran1.writeAction("movir X30 7")
    tran1.writeAction("movir X29 7")
    tran1.writeAction("movir X28 7")
    tran1.writeAction("lastact")
    tran3 = state1.writeTransition("flagCarry_with_action", state1, state2, 255)
    tran3.writeAction("movir X16 255")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("flagCarry_with_action", state2, state2, 164)
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