from EFA_v2 import *
def refill_noaction_TX_5():
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
    tran0 = state.writeTransition("refill_with_action", state, state1, 1)
    tran0.writeAction("movir X17 0")
    tran0.writeAction("add X7 X17 X17")
    tran0.writeAction("movir X16 41904")
    tran0.writeAction("slorii X16 X16 12 1713")
    tran0.writeAction("slorii X16 X16 12 3769")
    tran0.writeAction("slorii X16 X16 12 3778")
    tran0.writeAction("slorii X16 X16 12 1365")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 49661")
    tran0.writeAction("slorii X16 X16 12 2771")
    tran0.writeAction("slorii X16 X16 12 135")
    tran0.writeAction("slorii X16 X16 12 1763")
    tran0.writeAction("slorii X16 X16 12 2725")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 58153")
    tran0.writeAction("slorii X16 X16 12 699")
    tran0.writeAction("slorii X16 X16 12 2306")
    tran0.writeAction("slorii X16 X16 12 109")
    tran0.writeAction("slorii X16 X16 12 95")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 10036")
    tran0.writeAction("slorii X16 X16 12 937")
    tran0.writeAction("slorii X16 X16 12 1739")
    tran0.writeAction("slorii X16 X16 12 446")
    tran0.writeAction("slorii X16 X16 12 2016")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 50027")
    tran0.writeAction("slorii X16 X16 12 1417")
    tran0.writeAction("slorii X16 X16 12 1588")
    tran0.writeAction("slorii X16 X16 12 3187")
    tran0.writeAction("slorii X16 X16 12 4034")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 37050")
    tran0.writeAction("slorii X16 X16 12 714")
    tran0.writeAction("slorii X16 X16 12 2704")
    tran0.writeAction("slorii X16 X16 12 2840")
    tran0.writeAction("slorii X16 X16 12 88")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 40635")
    tran0.writeAction("slorii X16 X16 12 1165")
    tran0.writeAction("slorii X16 X16 12 3850")
    tran0.writeAction("slorii X16 X16 12 3593")
    tran0.writeAction("slorii X16 X16 12 1814")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 16818")
    tran0.writeAction("slorii X16 X16 12 3834")
    tran0.writeAction("slorii X16 X16 12 3280")
    tran0.writeAction("slorii X16 X16 12 1932")
    tran0.writeAction("slorii X16 X16 12 1711")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 41904")
    tran0.writeAction("slorii X16 X16 12 1713")
    tran0.writeAction("slorii X16 X16 12 3769")
    tran0.writeAction("slorii X16 X16 12 3778")
    tran0.writeAction("slorii X16 X16 12 1365")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 1")
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
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("refill", state1, state2, 85, 1)
    tran3 = state1.writeTransition("refill_with_action", state1, state2, 255, 1)
    tran3.writeAction("movir X30 2")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("refill_with_action", state2, state2, 185, 2)
    tran2.writeAction("movir X31 1")
    tran2.writeAction("addi X5 X18 0")
    tran2.writeAction("yieldt")
    tran4 = state2.writeTransition("refill_with_action", state2, state1, 255, 2)
    tran4.writeAction("movir X31 2")
    tran4.writeAction("addi X5 X18 0")
    tran4.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa