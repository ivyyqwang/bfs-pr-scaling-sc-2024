from EFA_v2 import *
def epsilon_action_TX_9():
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
    tran0.writeAction("movir X16 12310")
    tran0.writeAction("slorii X16 X16 12 3252")
    tran0.writeAction("slorii X16 X16 12 1629")
    tran0.writeAction("slorii X16 X16 12 2211")
    tran0.writeAction("slorii X16 X16 12 4058")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 26970")
    tran0.writeAction("slorii X16 X16 12 2431")
    tran0.writeAction("slorii X16 X16 12 2890")
    tran0.writeAction("slorii X16 X16 12 3688")
    tran0.writeAction("slorii X16 X16 12 1537")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 20611")
    tran0.writeAction("slorii X16 X16 12 2930")
    tran0.writeAction("slorii X16 X16 12 1908")
    tran0.writeAction("slorii X16 X16 12 1378")
    tran0.writeAction("slorii X16 X16 12 639")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 52674")
    tran0.writeAction("slorii X16 X16 12 99")
    tran0.writeAction("slorii X16 X16 12 129")
    tran0.writeAction("slorii X16 X16 12 3917")
    tran0.writeAction("slorii X16 X16 12 397")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 9680")
    tran0.writeAction("slorii X16 X16 12 3242")
    tran0.writeAction("slorii X16 X16 12 2733")
    tran0.writeAction("slorii X16 X16 12 3516")
    tran0.writeAction("slorii X16 X16 12 572")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 13951")
    tran0.writeAction("slorii X16 X16 12 2581")
    tran0.writeAction("slorii X16 X16 12 3293")
    tran0.writeAction("slorii X16 X16 12 408")
    tran0.writeAction("slorii X16 X16 12 2670")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 41984")
    tran0.writeAction("slorii X16 X16 12 733")
    tran0.writeAction("slorii X16 X16 12 2974")
    tran0.writeAction("slorii X16 X16 12 3218")
    tran0.writeAction("slorii X16 X16 12 1375")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 61586")
    tran0.writeAction("slorii X16 X16 12 1044")
    tran0.writeAction("slorii X16 X16 12 2603")
    tran0.writeAction("slorii X16 X16 12 802")
    tran0.writeAction("slorii X16 X16 12 1805")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 12310")
    tran0.writeAction("slorii X16 X16 12 3252")
    tran0.writeAction("slorii X16 X16 12 1629")
    tran0.writeAction("slorii X16 X16 12 2211")
    tran0.writeAction("slorii X16 X16 12 4058")
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