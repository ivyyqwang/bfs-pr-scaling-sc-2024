from EFA_v2 import *
def flag_noaction2_with_lastact_TX_4():
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
    tran0.writeAction("movir X16 39305")
    tran0.writeAction("slorii X16 X16 12 2356")
    tran0.writeAction("slorii X16 X16 12 1799")
    tran0.writeAction("slorii X16 X16 12 2263")
    tran0.writeAction("slorii X16 X16 12 1228")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 46262")
    tran0.writeAction("slorii X16 X16 12 12")
    tran0.writeAction("slorii X16 X16 12 941")
    tran0.writeAction("slorii X16 X16 12 3678")
    tran0.writeAction("slorii X16 X16 12 3762")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 2412")
    tran0.writeAction("slorii X16 X16 12 1721")
    tran0.writeAction("slorii X16 X16 12 843")
    tran0.writeAction("slorii X16 X16 12 2041")
    tran0.writeAction("slorii X16 X16 12 1369")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 52930")
    tran0.writeAction("slorii X16 X16 12 2182")
    tran0.writeAction("slorii X16 X16 12 878")
    tran0.writeAction("slorii X16 X16 12 847")
    tran0.writeAction("slorii X16 X16 12 2803")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 27529")
    tran0.writeAction("slorii X16 X16 12 1365")
    tran0.writeAction("slorii X16 X16 12 24")
    tran0.writeAction("slorii X16 X16 12 3616")
    tran0.writeAction("slorii X16 X16 12 507")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 7882")
    tran0.writeAction("slorii X16 X16 12 617")
    tran0.writeAction("slorii X16 X16 12 20")
    tran0.writeAction("slorii X16 X16 12 1514")
    tran0.writeAction("slorii X16 X16 12 2571")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 10988")
    tran0.writeAction("slorii X16 X16 12 3169")
    tran0.writeAction("slorii X16 X16 12 234")
    tran0.writeAction("slorii X16 X16 12 1021")
    tran0.writeAction("slorii X16 X16 12 1315")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 3563")
    tran0.writeAction("slorii X16 X16 12 789")
    tran0.writeAction("slorii X16 X16 12 993")
    tran0.writeAction("slorii X16 X16 12 1430")
    tran0.writeAction("slorii X16 X16 12 1291")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 39305")
    tran0.writeAction("slorii X16 X16 12 2356")
    tran0.writeAction("slorii X16 X16 12 1799")
    tran0.writeAction("slorii X16 X16 12 2263")
    tran0.writeAction("slorii X16 X16 12 1228")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 36")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 32")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X20 0")
    tran0.writeAction("add X20 X7 X5")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("addi X20 X17 3")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("movir X16 221")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("flagCarry", state1, state2, 221)
    tran3 = state1.writeTransition("flagCarry_with_action", state1, state2, 255)
    tran3.writeAction("movir X16 255")
    tran3.writeAction("movir X30 8")
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