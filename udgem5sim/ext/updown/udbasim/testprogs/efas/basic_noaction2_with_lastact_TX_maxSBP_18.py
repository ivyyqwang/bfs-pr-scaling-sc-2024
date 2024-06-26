from EFA_v2 import *
def basic_noaction2_with_lastact_TX_maxSBP_18():
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
    tran0.writeAction("movir X16 56088")
    tran0.writeAction("slorii X16 X16 12 3922")
    tran0.writeAction("slorii X16 X16 12 3374")
    tran0.writeAction("slorii X16 X16 12 848")
    tran0.writeAction("slorii X16 X16 12 1281")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 8644")
    tran0.writeAction("slorii X16 X16 12 580")
    tran0.writeAction("slorii X16 X16 12 2574")
    tran0.writeAction("slorii X16 X16 12 2675")
    tran0.writeAction("slorii X16 X16 12 3035")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 851")
    tran0.writeAction("slorii X16 X16 12 341")
    tran0.writeAction("slorii X16 X16 12 1306")
    tran0.writeAction("slorii X16 X16 12 3380")
    tran0.writeAction("slorii X16 X16 12 2259")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 52409")
    tran0.writeAction("slorii X16 X16 12 3900")
    tran0.writeAction("slorii X16 X16 12 3854")
    tran0.writeAction("slorii X16 X16 12 1231")
    tran0.writeAction("slorii X16 X16 12 2397")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 61671")
    tran0.writeAction("slorii X16 X16 12 2257")
    tran0.writeAction("slorii X16 X16 12 436")
    tran0.writeAction("slorii X16 X16 12 1244")
    tran0.writeAction("slorii X16 X16 12 3599")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 38937")
    tran0.writeAction("slorii X16 X16 12 2270")
    tran0.writeAction("slorii X16 X16 12 1088")
    tran0.writeAction("slorii X16 X16 12 2448")
    tran0.writeAction("slorii X16 X16 12 3476")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 18734")
    tran0.writeAction("slorii X16 X16 12 2733")
    tran0.writeAction("slorii X16 X16 12 1056")
    tran0.writeAction("slorii X16 X16 12 2192")
    tran0.writeAction("slorii X16 X16 12 1182")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 27579")
    tran0.writeAction("slorii X16 X16 12 360")
    tran0.writeAction("slorii X16 X16 12 2770")
    tran0.writeAction("slorii X16 X16 12 2571")
    tran0.writeAction("slorii X16 X16 12 1381")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 56088")
    tran0.writeAction("slorii X16 X16 12 3922")
    tran0.writeAction("slorii X16 X16 12 3374")
    tran0.writeAction("slorii X16 X16 12 848")
    tran0.writeAction("slorii X16 X16 12 1281")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 7")
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
    tran0.writeAction("addi X20 X17 8")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("basic", state1, state2, 1)
    tran3 = state1.writeTransition("basic_with_action", state1, state2, 255)
    tran3.writeAction("addi X5 X16 0")
    tran3.writeAction("movir X30 8")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("basic", state2, state2, 5)
    tran4 = state2.writeTransition("basic_with_action", state2, state1, 255)
    tran4.writeAction("addi X5 X17 0")
    tran4.writeAction("movir X31 8")
    tran4.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa
