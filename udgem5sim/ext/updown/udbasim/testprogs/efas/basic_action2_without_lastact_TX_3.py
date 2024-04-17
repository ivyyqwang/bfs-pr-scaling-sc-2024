from EFA_v2 import *
def basic_action2_without_lastact_TX_3():
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
    tran0.writeAction("movir X16 56685")
    tran0.writeAction("slorii X16 X16 12 3583")
    tran0.writeAction("slorii X16 X16 12 1792")
    tran0.writeAction("slorii X16 X16 12 0")
    tran0.writeAction("slorii X16 X16 12 21")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 48306")
    tran0.writeAction("slorii X16 X16 12 1645")
    tran0.writeAction("slorii X16 X16 12 2816")
    tran0.writeAction("slorii X16 X16 12 0")
    tran0.writeAction("slorii X16 X16 12 131")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 4287")
    tran0.writeAction("slorii X16 X16 12 3066")
    tran0.writeAction("slorii X16 X16 12 1216")
    tran0.writeAction("slorii X16 X16 12 3888")
    tran0.writeAction("slorii X16 X16 12 2331")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 32545")
    tran0.writeAction("slorii X16 X16 12 3184")
    tran0.writeAction("slorii X16 X16 12 2013")
    tran0.writeAction("slorii X16 X16 12 2934")
    tran0.writeAction("slorii X16 X16 12 2979")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 6009")
    tran0.writeAction("slorii X16 X16 12 2048")
    tran0.writeAction("slorii X16 X16 12 1092")
    tran0.writeAction("slorii X16 X16 12 3240")
    tran0.writeAction("slorii X16 X16 12 2235")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 50711")
    tran0.writeAction("slorii X16 X16 12 2635")
    tran0.writeAction("slorii X16 X16 12 3382")
    tran0.writeAction("slorii X16 X16 12 2159")
    tran0.writeAction("slorii X16 X16 12 2505")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 44176")
    tran0.writeAction("slorii X16 X16 12 2481")
    tran0.writeAction("slorii X16 X16 12 3294")
    tran0.writeAction("slorii X16 X16 12 2611")
    tran0.writeAction("slorii X16 X16 12 3361")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 30942")
    tran0.writeAction("slorii X16 X16 12 304")
    tran0.writeAction("slorii X16 X16 12 837")
    tran0.writeAction("slorii X16 X16 12 3718")
    tran0.writeAction("slorii X16 X16 12 1236")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 56685")
    tran0.writeAction("slorii X16 X16 12 3583")
    tran0.writeAction("slorii X16 X16 12 1792")
    tran0.writeAction("slorii X16 X16 12 0")
    tran0.writeAction("slorii X16 X16 12 21")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 4")
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
    tran1 = state1.writeTransition("basic_with_action", state1, state2, 21)
    tran1.writeAction("addi X5 X16 0")
    tran1.writeAction("movir X30 5")
    tran3 = state1.writeTransition("basic_with_action", state1, state2, 255)
    tran3.writeAction("addi X5 X16 0")
    tran3.writeAction("movir X30 6")
    tran2 = state2.writeTransition("basic_with_action", state2, state2, 131)
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
