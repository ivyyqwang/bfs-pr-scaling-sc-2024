from EFA_v2 import *
def flag_noaction1_with_lastact_TX_17():
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
    tran0.writeAction("movir X16 54714")
    tran0.writeAction("slorii X16 X16 12 2765")
    tran0.writeAction("slorii X16 X16 12 39")
    tran0.writeAction("slorii X16 X16 12 791")
    tran0.writeAction("slorii X16 X16 12 2514")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 40103")
    tran0.writeAction("slorii X16 X16 12 3226")
    tran0.writeAction("slorii X16 X16 12 3915")
    tran0.writeAction("slorii X16 X16 12 3925")
    tran0.writeAction("slorii X16 X16 12 441")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 32454")
    tran0.writeAction("slorii X16 X16 12 1685")
    tran0.writeAction("slorii X16 X16 12 3393")
    tran0.writeAction("slorii X16 X16 12 2864")
    tran0.writeAction("slorii X16 X16 12 3936")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 632")
    tran0.writeAction("slorii X16 X16 12 605")
    tran0.writeAction("slorii X16 X16 12 3720")
    tran0.writeAction("slorii X16 X16 12 2081")
    tran0.writeAction("slorii X16 X16 12 3711")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 22279")
    tran0.writeAction("slorii X16 X16 12 348")
    tran0.writeAction("slorii X16 X16 12 3446")
    tran0.writeAction("slorii X16 X16 12 1569")
    tran0.writeAction("slorii X16 X16 12 1691")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 63100")
    tran0.writeAction("slorii X16 X16 12 2751")
    tran0.writeAction("slorii X16 X16 12 2506")
    tran0.writeAction("slorii X16 X16 12 3209")
    tran0.writeAction("slorii X16 X16 12 1554")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 10682")
    tran0.writeAction("slorii X16 X16 12 1811")
    tran0.writeAction("slorii X16 X16 12 134")
    tran0.writeAction("slorii X16 X16 12 1669")
    tran0.writeAction("slorii X16 X16 12 3509")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 59153")
    tran0.writeAction("slorii X16 X16 12 2640")
    tran0.writeAction("slorii X16 X16 12 1714")
    tran0.writeAction("slorii X16 X16 12 3794")
    tran0.writeAction("slorii X16 X16 12 2578")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 54714")
    tran0.writeAction("slorii X16 X16 12 2765")
    tran0.writeAction("slorii X16 X16 12 39")
    tran0.writeAction("slorii X16 X16 12 791")
    tran0.writeAction("slorii X16 X16 12 2514")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 36")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 5")
    tran0.writeAction("sli X17 X17 32")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("add X7 X31 X31")
    tran0.writeAction("movir X20 0")
    tran0.writeAction("sli X31 X21 3")
    tran0.writeAction("add X21 X20 X5")
    tran0.writeAction("movlsb X31")
    tran0.writeAction("addi X20 X17 15")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("movir X16 208")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("flagCarry", state1, state2, 208)
    tran3 = state1.writeTransition("flagCarry_with_action", state1, state2, 255)
    tran3.writeAction("movir X16 255")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("flagCarry_with_action", state2, state2, 208)
    tran2.writeAction("movir X31 7")
    tran2.writeAction("yieldt")
    tran4 = state2.writeTransition("flagCarry_with_action", state2, state1, 255)
    tran4.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa
