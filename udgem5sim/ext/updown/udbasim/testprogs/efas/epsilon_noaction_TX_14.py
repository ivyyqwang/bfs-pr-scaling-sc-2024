from EFA_v2 import *
def epsilon_noaction_TX_14():
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
    tran0.writeAction("movir X16 19444")
    tran0.writeAction("slorii X16 X16 12 628")
    tran0.writeAction("slorii X16 X16 12 4091")
    tran0.writeAction("slorii X16 X16 12 4085")
    tran0.writeAction("slorii X16 X16 12 3742")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 29567")
    tran0.writeAction("slorii X16 X16 12 2119")
    tran0.writeAction("slorii X16 X16 12 2635")
    tran0.writeAction("slorii X16 X16 12 605")
    tran0.writeAction("slorii X16 X16 12 1230")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 59232")
    tran0.writeAction("slorii X16 X16 12 1635")
    tran0.writeAction("slorii X16 X16 12 1376")
    tran0.writeAction("slorii X16 X16 12 2702")
    tran0.writeAction("slorii X16 X16 12 479")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 34790")
    tran0.writeAction("slorii X16 X16 12 579")
    tran0.writeAction("slorii X16 X16 12 3965")
    tran0.writeAction("slorii X16 X16 12 3009")
    tran0.writeAction("slorii X16 X16 12 2297")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 49910")
    tran0.writeAction("slorii X16 X16 12 383")
    tran0.writeAction("slorii X16 X16 12 1330")
    tran0.writeAction("slorii X16 X16 12 0")
    tran0.writeAction("slorii X16 X16 12 127")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 36290")
    tran0.writeAction("slorii X16 X16 12 1394")
    tran0.writeAction("slorii X16 X16 12 2859")
    tran0.writeAction("slorii X16 X16 12 4")
    tran0.writeAction("slorii X16 X16 12 3374")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 25877")
    tran0.writeAction("slorii X16 X16 12 126")
    tran0.writeAction("slorii X16 X16 12 744")
    tran0.writeAction("slorii X16 X16 12 1690")
    tran0.writeAction("slorii X16 X16 12 266")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 27211")
    tran0.writeAction("slorii X16 X16 12 3015")
    tran0.writeAction("slorii X16 X16 12 3257")
    tran0.writeAction("slorii X16 X16 12 2639")
    tran0.writeAction("slorii X16 X16 12 3138")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 19444")
    tran0.writeAction("slorii X16 X16 12 628")
    tran0.writeAction("slorii X16 X16 12 4091")
    tran0.writeAction("slorii X16 X16 12 4085")
    tran0.writeAction("slorii X16 X16 12 3742")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 1")
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
