from EFA_v2 import *
def epsilon_noaction_TX_17():
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
    tran0.writeAction("movir X16 19506")
    tran0.writeAction("slorii X16 X16 12 82")
    tran0.writeAction("slorii X16 X16 12 1931")
    tran0.writeAction("slorii X16 X16 12 625")
    tran0.writeAction("slorii X16 X16 12 2705")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 40418")
    tran0.writeAction("slorii X16 X16 12 3907")
    tran0.writeAction("slorii X16 X16 12 3037")
    tran0.writeAction("slorii X16 X16 12 3132")
    tran0.writeAction("slorii X16 X16 12 4075")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 53149")
    tran0.writeAction("slorii X16 X16 12 1883")
    tran0.writeAction("slorii X16 X16 12 498")
    tran0.writeAction("slorii X16 X16 12 969")
    tran0.writeAction("slorii X16 X16 12 746")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 18087")
    tran0.writeAction("slorii X16 X16 12 3495")
    tran0.writeAction("slorii X16 X16 12 3384")
    tran0.writeAction("slorii X16 X16 12 2353")
    tran0.writeAction("slorii X16 X16 12 2452")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 15123")
    tran0.writeAction("slorii X16 X16 12 1679")
    tran0.writeAction("slorii X16 X16 12 2386")
    tran0.writeAction("slorii X16 X16 12 1042")
    tran0.writeAction("slorii X16 X16 12 3541")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 36386")
    tran0.writeAction("slorii X16 X16 12 250")
    tran0.writeAction("slorii X16 X16 12 3898")
    tran0.writeAction("slorii X16 X16 12 3878")
    tran0.writeAction("slorii X16 X16 12 3461")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 21225")
    tran0.writeAction("slorii X16 X16 12 2053")
    tran0.writeAction("slorii X16 X16 12 1234")
    tran0.writeAction("slorii X16 X16 12 3776")
    tran0.writeAction("slorii X16 X16 12 3962")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 32641")
    tran0.writeAction("slorii X16 X16 12 2127")
    tran0.writeAction("slorii X16 X16 12 1252")
    tran0.writeAction("slorii X16 X16 12 364")
    tran0.writeAction("slorii X16 X16 12 799")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 19506")
    tran0.writeAction("slorii X16 X16 12 82")
    tran0.writeAction("slorii X16 X16 12 1931")
    tran0.writeAction("slorii X16 X16 12 625")
    tran0.writeAction("slorii X16 X16 12 2705")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 2")
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