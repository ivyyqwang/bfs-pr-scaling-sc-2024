from EFA_v2 import *
def epsilon_action_TX_17():
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
    tran0.writeAction("movir X16 10494")
    tran0.writeAction("slorii X16 X16 12 2105")
    tran0.writeAction("slorii X16 X16 12 1874")
    tran0.writeAction("slorii X16 X16 12 1543")
    tran0.writeAction("slorii X16 X16 12 1466")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 41819")
    tran0.writeAction("slorii X16 X16 12 1813")
    tran0.writeAction("slorii X16 X16 12 270")
    tran0.writeAction("slorii X16 X16 12 3817")
    tran0.writeAction("slorii X16 X16 12 1195")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 26004")
    tran0.writeAction("slorii X16 X16 12 2200")
    tran0.writeAction("slorii X16 X16 12 2356")
    tran0.writeAction("slorii X16 X16 12 3645")
    tran0.writeAction("slorii X16 X16 12 3342")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 38490")
    tran0.writeAction("slorii X16 X16 12 3731")
    tran0.writeAction("slorii X16 X16 12 46")
    tran0.writeAction("slorii X16 X16 12 3860")
    tran0.writeAction("slorii X16 X16 12 2012")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 41169")
    tran0.writeAction("slorii X16 X16 12 821")
    tran0.writeAction("slorii X16 X16 12 1848")
    tran0.writeAction("slorii X16 X16 12 2673")
    tran0.writeAction("slorii X16 X16 12 2458")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 50460")
    tran0.writeAction("slorii X16 X16 12 3665")
    tran0.writeAction("slorii X16 X16 12 3165")
    tran0.writeAction("slorii X16 X16 12 2447")
    tran0.writeAction("slorii X16 X16 12 1577")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 24531")
    tran0.writeAction("slorii X16 X16 12 2542")
    tran0.writeAction("slorii X16 X16 12 1830")
    tran0.writeAction("slorii X16 X16 12 390")
    tran0.writeAction("slorii X16 X16 12 1978")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 5899")
    tran0.writeAction("slorii X16 X16 12 127")
    tran0.writeAction("slorii X16 X16 12 322")
    tran0.writeAction("slorii X16 X16 12 48")
    tran0.writeAction("slorii X16 X16 12 1548")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 10494")
    tran0.writeAction("slorii X16 X16 12 2105")
    tran0.writeAction("slorii X16 X16 12 1874")
    tran0.writeAction("slorii X16 X16 12 1543")
    tran0.writeAction("slorii X16 X16 12 1466")
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
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("epsilonCarry_with_action", state1, state2, 0)
    tran1.writeAction("addi X5 X16 0")
    tran1.writeAction("movir X30 3")
    tran1.writeAction("lastact")
    tran2 = state2.writeTransition("epsilonCarry_with_action", state2, state2, 0)
    tran2.writeAction("addi X5 X17 0")
    tran2.writeAction("movir X31 4")
    tran2.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa