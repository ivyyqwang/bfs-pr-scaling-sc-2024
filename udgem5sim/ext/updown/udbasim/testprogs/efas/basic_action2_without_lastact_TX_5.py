from EFA_v2 import *
def basic_action2_without_lastact_TX_5():
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
    tran0 = state.writeTransition("basic_with_action", state, state1, 1)
    tran0.writeAction("movir X17 0")
    tran0.writeAction("add X7 X17 X17")
    tran0.writeAction("movir X16 50106")
    tran0.writeAction("slorii X16 X16 12 133")
    tran0.writeAction("slorii X16 X16 12 730")
    tran0.writeAction("slorii X16 X16 12 3615")
    tran0.writeAction("slorii X16 X16 12 2913")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 62705")
    tran0.writeAction("slorii X16 X16 12 3264")
    tran0.writeAction("slorii X16 X16 12 464")
    tran0.writeAction("slorii X16 X16 12 2762")
    tran0.writeAction("slorii X16 X16 12 441")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 25899")
    tran0.writeAction("slorii X16 X16 12 3635")
    tran0.writeAction("slorii X16 X16 12 3257")
    tran0.writeAction("slorii X16 X16 12 3829")
    tran0.writeAction("slorii X16 X16 12 188")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 14630")
    tran0.writeAction("slorii X16 X16 12 1092")
    tran0.writeAction("slorii X16 X16 12 305")
    tran0.writeAction("slorii X16 X16 12 1347")
    tran0.writeAction("slorii X16 X16 12 3428")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 56349")
    tran0.writeAction("slorii X16 X16 12 2503")
    tran0.writeAction("slorii X16 X16 12 207")
    tran0.writeAction("slorii X16 X16 12 2546")
    tran0.writeAction("slorii X16 X16 12 2231")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 45159")
    tran0.writeAction("slorii X16 X16 12 57")
    tran0.writeAction("slorii X16 X16 12 1045")
    tran0.writeAction("slorii X16 X16 12 3400")
    tran0.writeAction("slorii X16 X16 12 1435")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 28890")
    tran0.writeAction("slorii X16 X16 12 1974")
    tran0.writeAction("slorii X16 X16 12 2443")
    tran0.writeAction("slorii X16 X16 12 2155")
    tran0.writeAction("slorii X16 X16 12 189")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 32671")
    tran0.writeAction("slorii X16 X16 12 3049")
    tran0.writeAction("slorii X16 X16 12 4083")
    tran0.writeAction("slorii X16 X16 12 557")
    tran0.writeAction("slorii X16 X16 12 888")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 50106")
    tran0.writeAction("slorii X16 X16 12 133")
    tran0.writeAction("slorii X16 X16 12 730")
    tran0.writeAction("slorii X16 X16 12 3615")
    tran0.writeAction("slorii X16 X16 12 2913")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 1")
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
    tran1 = state1.writeTransition("basic_with_action", state1, state2, 97)
    tran1.writeAction("addi X5 X16 0")
    tran1.writeAction("movir X30 5")
    tran3 = state1.writeTransition("basic_with_action", state1, state2, 255)
    tran3.writeAction("addi X5 X16 0")
    tran3.writeAction("movir X30 6")
    tran2 = state2.writeTransition("basic_with_action", state2, state2, 185)
    tran2.writeAction("addi X5 X17 0")
    tran2.writeAction("movir X31 5")
    tran2.writeAction("yieldt")
    tran4 = state2.writeTransition("basic_with_action", state2, state1, 255)
    tran4.writeAction("addi X5 X17 0")
    tran4.writeAction("movir X31 6")
    tran4.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa