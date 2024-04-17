from EFA_v2 import *
def flag_noaction8_with_lastact_TX_16():
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
    tran0.writeAction("movir X16 139")
    tran0.writeAction("slorii X16 X16 12 2141")
    tran0.writeAction("slorii X16 X16 12 488")
    tran0.writeAction("slorii X16 X16 12 2489")
    tran0.writeAction("slorii X16 X16 12 1165")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 14188")
    tran0.writeAction("slorii X16 X16 12 1778")
    tran0.writeAction("slorii X16 X16 12 404")
    tran0.writeAction("slorii X16 X16 12 398")
    tran0.writeAction("slorii X16 X16 12 1677")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 5205")
    tran0.writeAction("slorii X16 X16 12 280")
    tran0.writeAction("slorii X16 X16 12 987")
    tran0.writeAction("slorii X16 X16 12 896")
    tran0.writeAction("slorii X16 X16 12 3024")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 60772")
    tran0.writeAction("slorii X16 X16 12 3246")
    tran0.writeAction("slorii X16 X16 12 1731")
    tran0.writeAction("slorii X16 X16 12 1230")
    tran0.writeAction("slorii X16 X16 12 2383")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 3852")
    tran0.writeAction("slorii X16 X16 12 1044")
    tran0.writeAction("slorii X16 X16 12 3038")
    tran0.writeAction("slorii X16 X16 12 1453")
    tran0.writeAction("slorii X16 X16 12 350")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 44701")
    tran0.writeAction("slorii X16 X16 12 1466")
    tran0.writeAction("slorii X16 X16 12 1071")
    tran0.writeAction("slorii X16 X16 12 768")
    tran0.writeAction("slorii X16 X16 12 1107")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 39984")
    tran0.writeAction("slorii X16 X16 12 2014")
    tran0.writeAction("slorii X16 X16 12 2624")
    tran0.writeAction("slorii X16 X16 12 2414")
    tran0.writeAction("slorii X16 X16 12 250")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 8121")
    tran0.writeAction("slorii X16 X16 12 3765")
    tran0.writeAction("slorii X16 X16 12 3290")
    tran0.writeAction("slorii X16 X16 12 2534")
    tran0.writeAction("slorii X16 X16 12 3515")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 139")
    tran0.writeAction("slorii X16 X16 12 2141")
    tran0.writeAction("slorii X16 X16 12 488")
    tran0.writeAction("slorii X16 X16 12 2489")
    tran0.writeAction("slorii X16 X16 12 1165")
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
    tran0.writeAction("movir X16 10")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("flagCarry", state1, state2, 10)
    tran3 = state1.writeTransition("flagCarry_with_action", state1, state2, 255)
    tran3.writeAction("movir X16 255")
    tran3.writeAction("movir X30 8")
    tran3.writeAction("movir X30 9")
    tran3.writeAction("movir X30 10")
    tran3.writeAction("movir X30 11")
    tran3.writeAction("movir X30 12")
    tran3.writeAction("movir X30 13")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("flagCarry_with_action", state2, state2, 10)
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
