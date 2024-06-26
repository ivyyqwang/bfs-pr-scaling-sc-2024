from EFA_v2 import *
def refill_noaction_TX_9():
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
    tran0.writeAction("movir X16 56415")
    tran0.writeAction("slorii X16 X16 12 3425")
    tran0.writeAction("slorii X16 X16 12 3282")
    tran0.writeAction("slorii X16 X16 12 3494")
    tran0.writeAction("slorii X16 X16 12 3833")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 22247")
    tran0.writeAction("slorii X16 X16 12 1562")
    tran0.writeAction("slorii X16 X16 12 2790")
    tran0.writeAction("slorii X16 X16 12 3908")
    tran0.writeAction("slorii X16 X16 12 2682")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 13126")
    tran0.writeAction("slorii X16 X16 12 3388")
    tran0.writeAction("slorii X16 X16 12 1034")
    tran0.writeAction("slorii X16 X16 12 2140")
    tran0.writeAction("slorii X16 X16 12 40")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 18097")
    tran0.writeAction("slorii X16 X16 12 1814")
    tran0.writeAction("slorii X16 X16 12 364")
    tran0.writeAction("slorii X16 X16 12 984")
    tran0.writeAction("slorii X16 X16 12 638")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 56235")
    tran0.writeAction("slorii X16 X16 12 2442")
    tran0.writeAction("slorii X16 X16 12 1705")
    tran0.writeAction("slorii X16 X16 12 3705")
    tran0.writeAction("slorii X16 X16 12 2541")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 54809")
    tran0.writeAction("slorii X16 X16 12 2089")
    tran0.writeAction("slorii X16 X16 12 2161")
    tran0.writeAction("slorii X16 X16 12 2429")
    tran0.writeAction("slorii X16 X16 12 3194")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 34634")
    tran0.writeAction("slorii X16 X16 12 2040")
    tran0.writeAction("slorii X16 X16 12 702")
    tran0.writeAction("slorii X16 X16 12 572")
    tran0.writeAction("slorii X16 X16 12 476")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 63865")
    tran0.writeAction("slorii X16 X16 12 1517")
    tran0.writeAction("slorii X16 X16 12 3552")
    tran0.writeAction("slorii X16 X16 12 275")
    tran0.writeAction("slorii X16 X16 12 734")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 56415")
    tran0.writeAction("slorii X16 X16 12 3425")
    tran0.writeAction("slorii X16 X16 12 3282")
    tran0.writeAction("slorii X16 X16 12 3494")
    tran0.writeAction("slorii X16 X16 12 3833")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 8")
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
    tran1 = state1.writeTransition("refill", state1, state2, 249, 0)
    tran3 = state1.writeTransition("refill_with_action", state1, state2, 255, 0)
    tran3.writeAction("movir X30 2")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("refill_with_action", state2, state2, 110, 4)
    tran2.writeAction("movir X31 1")
    tran2.writeAction("addi X5 X18 0")
    tran2.writeAction("yieldt")
    tran4 = state2.writeTransition("refill_with_action", state2, state1, 255, 4)
    tran4.writeAction("movir X31 2")
    tran4.writeAction("addi X5 X18 0")
    tran4.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa
