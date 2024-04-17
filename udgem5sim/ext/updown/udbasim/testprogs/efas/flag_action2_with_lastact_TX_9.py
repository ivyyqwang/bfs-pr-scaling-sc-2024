from EFA_v2 import *
def flag_action2_with_lastact_TX_9():
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
    tran0 = state.writeTransition("flagCarry_with_action", state, state1, 1)
    tran0.writeAction("movir X17 0")
    tran0.writeAction("add X7 X17 X17")
    tran0.writeAction("movir X16 11958")
    tran0.writeAction("slorii X16 X16 12 3990")
    tran0.writeAction("slorii X16 X16 12 2674")
    tran0.writeAction("slorii X16 X16 12 2224")
    tran0.writeAction("slorii X16 X16 12 2391")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 7013")
    tran0.writeAction("slorii X16 X16 12 2686")
    tran0.writeAction("slorii X16 X16 12 469")
    tran0.writeAction("slorii X16 X16 12 3475")
    tran0.writeAction("slorii X16 X16 12 2201")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 59238")
    tran0.writeAction("slorii X16 X16 12 1078")
    tran0.writeAction("slorii X16 X16 12 1013")
    tran0.writeAction("slorii X16 X16 12 3552")
    tran0.writeAction("slorii X16 X16 12 1863")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 62430")
    tran0.writeAction("slorii X16 X16 12 1946")
    tran0.writeAction("slorii X16 X16 12 500")
    tran0.writeAction("slorii X16 X16 12 1983")
    tran0.writeAction("slorii X16 X16 12 2359")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 9273")
    tran0.writeAction("slorii X16 X16 12 2782")
    tran0.writeAction("slorii X16 X16 12 2982")
    tran0.writeAction("slorii X16 X16 12 1921")
    tran0.writeAction("slorii X16 X16 12 585")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 32252")
    tran0.writeAction("slorii X16 X16 12 3635")
    tran0.writeAction("slorii X16 X16 12 940")
    tran0.writeAction("slorii X16 X16 12 2797")
    tran0.writeAction("slorii X16 X16 12 2148")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 40515")
    tran0.writeAction("slorii X16 X16 12 24")
    tran0.writeAction("slorii X16 X16 12 3337")
    tran0.writeAction("slorii X16 X16 12 1268")
    tran0.writeAction("slorii X16 X16 12 3947")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 46080")
    tran0.writeAction("slorii X16 X16 12 1409")
    tran0.writeAction("slorii X16 X16 12 1483")
    tran0.writeAction("slorii X16 X16 12 2167")
    tran0.writeAction("slorii X16 X16 12 1457")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 11958")
    tran0.writeAction("slorii X16 X16 12 3990")
    tran0.writeAction("slorii X16 X16 12 2674")
    tran0.writeAction("slorii X16 X16 12 2224")
    tran0.writeAction("slorii X16 X16 12 2391")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 2")
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
    tran0.writeAction("movir X16 219")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("flagCarry_with_action", state1, state2, 219)
    tran1.writeAction("movir X16 221")
    tran1.writeAction("movir X30 7")
    tran1.writeAction("lastact")
    tran3 = state1.writeTransition("flagCarry_with_action", state1, state2, 255)
    tran3.writeAction("movir X16 255")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("flagCarry_with_action", state2, state2, 221)
    tran2.writeAction("addi X5 X17 0")
    tran2.writeAction("movir X31 7")
    tran2.writeAction("yieldt")
    tran4 = state2.writeTransition("flagCarry_with_action", state2, state1, 255)
    tran4.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa