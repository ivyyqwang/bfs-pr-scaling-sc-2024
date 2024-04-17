from EFA_v2 import *
def basic_noaction4_with_lastact_TX_maxSBP_16():
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
    tran0.writeAction("movir X16 17865")
    tran0.writeAction("slorii X16 X16 12 3944")
    tran0.writeAction("slorii X16 X16 12 3541")
    tran0.writeAction("slorii X16 X16 12 3608")
    tran0.writeAction("slorii X16 X16 12 2523")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 56148")
    tran0.writeAction("slorii X16 X16 12 1341")
    tran0.writeAction("slorii X16 X16 12 3842")
    tran0.writeAction("slorii X16 X16 12 4028")
    tran0.writeAction("slorii X16 X16 12 701")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 4615")
    tran0.writeAction("slorii X16 X16 12 847")
    tran0.writeAction("slorii X16 X16 12 2292")
    tran0.writeAction("slorii X16 X16 12 2518")
    tran0.writeAction("slorii X16 X16 12 3643")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 26758")
    tran0.writeAction("slorii X16 X16 12 2519")
    tran0.writeAction("slorii X16 X16 12 1616")
    tran0.writeAction("slorii X16 X16 12 983")
    tran0.writeAction("slorii X16 X16 12 3476")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 4036")
    tran0.writeAction("slorii X16 X16 12 350")
    tran0.writeAction("slorii X16 X16 12 2459")
    tran0.writeAction("slorii X16 X16 12 3401")
    tran0.writeAction("slorii X16 X16 12 2987")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 64951")
    tran0.writeAction("slorii X16 X16 12 2313")
    tran0.writeAction("slorii X16 X16 12 354")
    tran0.writeAction("slorii X16 X16 12 538")
    tran0.writeAction("slorii X16 X16 12 1449")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 24911")
    tran0.writeAction("slorii X16 X16 12 1180")
    tran0.writeAction("slorii X16 X16 12 3156")
    tran0.writeAction("slorii X16 X16 12 1417")
    tran0.writeAction("slorii X16 X16 12 2808")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 59228")
    tran0.writeAction("slorii X16 X16 12 1780")
    tran0.writeAction("slorii X16 X16 12 1591")
    tran0.writeAction("slorii X16 X16 12 3885")
    tran0.writeAction("slorii X16 X16 12 3653")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 17865")
    tran0.writeAction("slorii X16 X16 12 3944")
    tran0.writeAction("slorii X16 X16 12 3541")
    tran0.writeAction("slorii X16 X16 12 3608")
    tran0.writeAction("slorii X16 X16 12 2523")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 36")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 4")
    tran0.writeAction("sli X17 X17 32")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("add X7 X31 X31")
    tran0.writeAction("movir X20 0")
    tran0.writeAction("sli X31 X21 3")
    tran0.writeAction("add X21 X20 X5")
    tran0.writeAction("movlsb X31")
    tran0.writeAction("addi X20 X17 4")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("basic", state1, state2, 1)
    tran3 = state1.writeTransition("basic_with_action", state1, state2, 255)
    tran3.writeAction("addi X5 X16 8")
    tran3.writeAction("movir X30 8")
    tran3.writeAction("movir X29 8")
    tran3.writeAction("movir X28 8")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("basic", state2, state2, 1)
    tran4 = state2.writeTransition("basic_with_action", state2, state1, 255)
    tran4.writeAction("addi X5 X17 0")
    tran4.writeAction("movir X31 8")
    tran4.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa
