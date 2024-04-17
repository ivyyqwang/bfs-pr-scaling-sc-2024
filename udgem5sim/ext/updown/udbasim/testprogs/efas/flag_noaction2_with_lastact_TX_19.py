from EFA_v2 import *
def flag_noaction2_with_lastact_TX_19():
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
    tran0.writeAction("movir X16 5181")
    tran0.writeAction("slorii X16 X16 12 3877")
    tran0.writeAction("slorii X16 X16 12 3078")
    tran0.writeAction("slorii X16 X16 12 2568")
    tran0.writeAction("slorii X16 X16 12 2277")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 29669")
    tran0.writeAction("slorii X16 X16 12 438")
    tran0.writeAction("slorii X16 X16 12 2009")
    tran0.writeAction("slorii X16 X16 12 1771")
    tran0.writeAction("slorii X16 X16 12 604")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 26065")
    tran0.writeAction("slorii X16 X16 12 3807")
    tran0.writeAction("slorii X16 X16 12 3080")
    tran0.writeAction("slorii X16 X16 12 2800")
    tran0.writeAction("slorii X16 X16 12 1870")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 33562")
    tran0.writeAction("slorii X16 X16 12 714")
    tran0.writeAction("slorii X16 X16 12 3204")
    tran0.writeAction("slorii X16 X16 12 3316")
    tran0.writeAction("slorii X16 X16 12 95")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 57747")
    tran0.writeAction("slorii X16 X16 12 4089")
    tran0.writeAction("slorii X16 X16 12 274")
    tran0.writeAction("slorii X16 X16 12 3202")
    tran0.writeAction("slorii X16 X16 12 3873")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 32333")
    tran0.writeAction("slorii X16 X16 12 959")
    tran0.writeAction("slorii X16 X16 12 288")
    tran0.writeAction("slorii X16 X16 12 1770")
    tran0.writeAction("slorii X16 X16 12 2979")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 43579")
    tran0.writeAction("slorii X16 X16 12 1761")
    tran0.writeAction("slorii X16 X16 12 117")
    tran0.writeAction("slorii X16 X16 12 3433")
    tran0.writeAction("slorii X16 X16 12 1163")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 54016")
    tran0.writeAction("slorii X16 X16 12 2396")
    tran0.writeAction("slorii X16 X16 12 845")
    tran0.writeAction("slorii X16 X16 12 176")
    tran0.writeAction("slorii X16 X16 12 2396")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 5181")
    tran0.writeAction("slorii X16 X16 12 3877")
    tran0.writeAction("slorii X16 X16 12 3078")
    tran0.writeAction("slorii X16 X16 12 2568")
    tran0.writeAction("slorii X16 X16 12 2277")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 8")
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
    tran0.writeAction("movir X16 58")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("flagCarry", state1, state2, 58)
    tran3 = state1.writeTransition("flagCarry_with_action", state1, state2, 255)
    tran3.writeAction("movir X16 255")
    tran3.writeAction("movir X30 8")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("flagCarry_with_action", state2, state2, 58)
    tran2.writeAction("addi X5 X17 0")
    tran2.writeAction("movir X31 7")
    tran2.writeAction("yieldt")
    tran4 = state2.writeTransition("flagCarry_with_action", state2, state1, 255)
    tran4.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa