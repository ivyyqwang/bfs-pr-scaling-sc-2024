from EFA_v2 import *
def epsilon_noaction_TX_13():
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
    tran0 = state.writeTransition("epsilonCarry_with_action", state, state1, 1)
    tran0.writeAction("movir X17 0")
    tran0.writeAction("add X7 X17 X17")
    tran0.writeAction("movir X16 14293")
    tran0.writeAction("slorii X16 X16 12 1714")
    tran0.writeAction("slorii X16 X16 12 3937")
    tran0.writeAction("slorii X16 X16 12 3062")
    tran0.writeAction("slorii X16 X16 12 246")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 48667")
    tran0.writeAction("slorii X16 X16 12 960")
    tran0.writeAction("slorii X16 X16 12 1974")
    tran0.writeAction("slorii X16 X16 12 332")
    tran0.writeAction("slorii X16 X16 12 3383")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 14365")
    tran0.writeAction("slorii X16 X16 12 419")
    tran0.writeAction("slorii X16 X16 12 3947")
    tran0.writeAction("slorii X16 X16 12 2272")
    tran0.writeAction("slorii X16 X16 12 3386")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 64744")
    tran0.writeAction("slorii X16 X16 12 626")
    tran0.writeAction("slorii X16 X16 12 2629")
    tran0.writeAction("slorii X16 X16 12 1346")
    tran0.writeAction("slorii X16 X16 12 3641")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 8037")
    tran0.writeAction("slorii X16 X16 12 1202")
    tran0.writeAction("slorii X16 X16 12 3176")
    tran0.writeAction("slorii X16 X16 12 3553")
    tran0.writeAction("slorii X16 X16 12 742")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 51310")
    tran0.writeAction("slorii X16 X16 12 3678")
    tran0.writeAction("slorii X16 X16 12 1581")
    tran0.writeAction("slorii X16 X16 12 776")
    tran0.writeAction("slorii X16 X16 12 506")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 25730")
    tran0.writeAction("slorii X16 X16 12 3570")
    tran0.writeAction("slorii X16 X16 12 919")
    tran0.writeAction("slorii X16 X16 12 3159")
    tran0.writeAction("slorii X16 X16 12 390")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 13057")
    tran0.writeAction("slorii X16 X16 12 764")
    tran0.writeAction("slorii X16 X16 12 134")
    tran0.writeAction("slorii X16 X16 12 310")
    tran0.writeAction("slorii X16 X16 12 1059")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 14293")
    tran0.writeAction("slorii X16 X16 12 1714")
    tran0.writeAction("slorii X16 X16 12 3937")
    tran0.writeAction("slorii X16 X16 12 3062")
    tran0.writeAction("slorii X16 X16 12 246")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 2")
    tran0.writeAction("sli X17 X17 36")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 6")
    tran0.writeAction("sli X17 X17 32")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X20 0")
    tran0.writeAction("add X20 X7 X5")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("addi X20 X17 18")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("epsilonCarry", state1, state2, 0)
    tran2 = state2.writeTransition("epsilonCarry_with_action", state2, state2, 0)
    tran2.writeAction("addi X5 X17 0")
    tran2.writeAction("movir X31 4")
    tran2.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa
