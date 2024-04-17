from EFA_v2 import *
def refill_TX_6():
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
    tran0.writeAction("movir X16 63432")
    tran0.writeAction("slorii X16 X16 12 2189")
    tran0.writeAction("slorii X16 X16 12 1563")
    tran0.writeAction("slorii X16 X16 12 2665")
    tran0.writeAction("slorii X16 X16 12 1371")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 45363")
    tran0.writeAction("slorii X16 X16 12 131")
    tran0.writeAction("slorii X16 X16 12 2896")
    tran0.writeAction("slorii X16 X16 12 878")
    tran0.writeAction("slorii X16 X16 12 1377")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 8762")
    tran0.writeAction("slorii X16 X16 12 254")
    tran0.writeAction("slorii X16 X16 12 3245")
    tran0.writeAction("slorii X16 X16 12 2838")
    tran0.writeAction("slorii X16 X16 12 2855")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 54575")
    tran0.writeAction("slorii X16 X16 12 519")
    tran0.writeAction("slorii X16 X16 12 1507")
    tran0.writeAction("slorii X16 X16 12 3635")
    tran0.writeAction("slorii X16 X16 12 606")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 46050")
    tran0.writeAction("slorii X16 X16 12 2744")
    tran0.writeAction("slorii X16 X16 12 554")
    tran0.writeAction("slorii X16 X16 12 3897")
    tran0.writeAction("slorii X16 X16 12 2229")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 58544")
    tran0.writeAction("slorii X16 X16 12 1535")
    tran0.writeAction("slorii X16 X16 12 4023")
    tran0.writeAction("slorii X16 X16 12 2435")
    tran0.writeAction("slorii X16 X16 12 1988")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 50393")
    tran0.writeAction("slorii X16 X16 12 3922")
    tran0.writeAction("slorii X16 X16 12 679")
    tran0.writeAction("slorii X16 X16 12 2302")
    tran0.writeAction("slorii X16 X16 12 686")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 24196")
    tran0.writeAction("slorii X16 X16 12 1599")
    tran0.writeAction("slorii X16 X16 12 590")
    tran0.writeAction("slorii X16 X16 12 709")
    tran0.writeAction("slorii X16 X16 12 394")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 63432")
    tran0.writeAction("slorii X16 X16 12 2189")
    tran0.writeAction("slorii X16 X16 12 1563")
    tran0.writeAction("slorii X16 X16 12 2665")
    tran0.writeAction("slorii X16 X16 12 1371")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 6")
    tran0.writeAction("sli X17 X17 36")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 8")
    tran0.writeAction("sli X17 X17 32")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("add X7 X31 X31")
    tran0.writeAction("movir X20 0")
    tran0.writeAction("sli X31 X21 3")
    tran0.writeAction("add X21 X20 X5")
    tran0.writeAction("movlsb X31")
    tran0.writeAction("addi X20 X17 24")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("refill_with_action", state1, state2, 27, 2)
    tran1.writeAction("movir X30 1")
    tran1.writeAction("addi X5 X17 0")
    tran1.writeAction("lastact")
    tran3 = state1.writeTransition("refill_with_action", state1, state2, 255, 2)
    tran3.writeAction("movir X30 2")
    tran3.writeAction("addi X5 X17 0")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("refill_with_action", state2, state2, 21, 1)
    tran2.writeAction("movir X31 1")
    tran2.writeAction("addi X5 X18 0")
    tran2.writeAction("yieldt")
    tran4 = state2.writeTransition("refill_with_action", state2, state1, 255, 1)
    tran4.writeAction("movir X31 2")
    tran4.writeAction("addi X5 X18 0")
    tran4.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa
