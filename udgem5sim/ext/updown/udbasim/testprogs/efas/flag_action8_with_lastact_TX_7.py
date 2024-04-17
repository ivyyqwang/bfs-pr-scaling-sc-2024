from EFA_v2 import *
def flag_action8_with_lastact_TX_7():
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
    tran0.writeAction("movir X16 23073")
    tran0.writeAction("slorii X16 X16 12 2022")
    tran0.writeAction("slorii X16 X16 12 607")
    tran0.writeAction("slorii X16 X16 12 3955")
    tran0.writeAction("slorii X16 X16 12 2399")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 21759")
    tran0.writeAction("slorii X16 X16 12 3610")
    tran0.writeAction("slorii X16 X16 12 1287")
    tran0.writeAction("slorii X16 X16 12 1045")
    tran0.writeAction("slorii X16 X16 12 1355")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 30144")
    tran0.writeAction("slorii X16 X16 12 1802")
    tran0.writeAction("slorii X16 X16 12 1748")
    tran0.writeAction("slorii X16 X16 12 1146")
    tran0.writeAction("slorii X16 X16 12 1093")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 62314")
    tran0.writeAction("slorii X16 X16 12 3016")
    tran0.writeAction("slorii X16 X16 12 259")
    tran0.writeAction("slorii X16 X16 12 1965")
    tran0.writeAction("slorii X16 X16 12 2659")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 23464")
    tran0.writeAction("slorii X16 X16 12 1703")
    tran0.writeAction("slorii X16 X16 12 2657")
    tran0.writeAction("slorii X16 X16 12 4032")
    tran0.writeAction("slorii X16 X16 12 1946")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 7457")
    tran0.writeAction("slorii X16 X16 12 2468")
    tran0.writeAction("slorii X16 X16 12 32")
    tran0.writeAction("slorii X16 X16 12 4055")
    tran0.writeAction("slorii X16 X16 12 335")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 31383")
    tran0.writeAction("slorii X16 X16 12 3921")
    tran0.writeAction("slorii X16 X16 12 1418")
    tran0.writeAction("slorii X16 X16 12 218")
    tran0.writeAction("slorii X16 X16 12 3509")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 25704")
    tran0.writeAction("slorii X16 X16 12 2913")
    tran0.writeAction("slorii X16 X16 12 818")
    tran0.writeAction("slorii X16 X16 12 167")
    tran0.writeAction("slorii X16 X16 12 1363")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 23073")
    tran0.writeAction("slorii X16 X16 12 2022")
    tran0.writeAction("slorii X16 X16 12 607")
    tran0.writeAction("slorii X16 X16 12 3955")
    tran0.writeAction("slorii X16 X16 12 2399")
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
    tran0.writeAction("movir X16 212")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("flagCarry_with_action", state1, state2, 212)
    tran1.writeAction("movir X16 100")
    tran1.writeAction("movir X30 7")
    tran1.writeAction("movir X29 7")
    tran1.writeAction("movir X28 7")
    tran1.writeAction("movir X27 7")
    tran1.writeAction("movir X26 7")
    tran1.writeAction("movir X25 7")
    tran1.writeAction("movir X24 7")
    tran1.writeAction("lastact")
    tran3 = state1.writeTransition("flagCarry_with_action", state1, state2, 255)
    tran3.writeAction("movir X16 255")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("flagCarry_with_action", state2, state2, 100)
    tran2.writeAction("addi X5 X17 0")
    tran2.writeAction("movir X31 7")
    tran2.writeAction("movir X31 8")
    tran2.writeAction("movir X31 9")
    tran2.writeAction("movir X31 10")
    tran2.writeAction("movir X31 11")
    tran2.writeAction("movir X31 12")
    tran2.writeAction("movir X31 13")
    tran2.writeAction("yieldt")
    tran4 = state2.writeTransition("flagCarry_with_action", state2, state1, 255)
    tran4.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa