from EFA_v2 import *
def common_noaction_TX_maxSBP_11():
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
    tran0 = state.writeTransition("commonCarry_with_action", state, state1, 1)
    tran0.writeAction("movir X17 0")
    tran0.writeAction("add X7 X17 X17")
    tran0.writeAction("movir X16 10443")
    tran0.writeAction("slorii X16 X16 12 3216")
    tran0.writeAction("slorii X16 X16 12 2792")
    tran0.writeAction("slorii X16 X16 12 4017")
    tran0.writeAction("slorii X16 X16 12 1535")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 45869")
    tran0.writeAction("slorii X16 X16 12 444")
    tran0.writeAction("slorii X16 X16 12 925")
    tran0.writeAction("slorii X16 X16 12 3360")
    tran0.writeAction("slorii X16 X16 12 3112")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 59808")
    tran0.writeAction("slorii X16 X16 12 939")
    tran0.writeAction("slorii X16 X16 12 2163")
    tran0.writeAction("slorii X16 X16 12 718")
    tran0.writeAction("slorii X16 X16 12 1783")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 11318")
    tran0.writeAction("slorii X16 X16 12 2455")
    tran0.writeAction("slorii X16 X16 12 2841")
    tran0.writeAction("slorii X16 X16 12 2036")
    tran0.writeAction("slorii X16 X16 12 2927")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 17654")
    tran0.writeAction("slorii X16 X16 12 2327")
    tran0.writeAction("slorii X16 X16 12 489")
    tran0.writeAction("slorii X16 X16 12 4002")
    tran0.writeAction("slorii X16 X16 12 3267")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 9723")
    tran0.writeAction("slorii X16 X16 12 2647")
    tran0.writeAction("slorii X16 X16 12 3096")
    tran0.writeAction("slorii X16 X16 12 896")
    tran0.writeAction("slorii X16 X16 12 3283")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 3019")
    tran0.writeAction("slorii X16 X16 12 1713")
    tran0.writeAction("slorii X16 X16 12 254")
    tran0.writeAction("slorii X16 X16 12 1507")
    tran0.writeAction("slorii X16 X16 12 3315")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 57217")
    tran0.writeAction("slorii X16 X16 12 120")
    tran0.writeAction("slorii X16 X16 12 564")
    tran0.writeAction("slorii X16 X16 12 568")
    tran0.writeAction("slorii X16 X16 12 3883")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 10443")
    tran0.writeAction("slorii X16 X16 12 3216")
    tran0.writeAction("slorii X16 X16 12 2792")
    tran0.writeAction("slorii X16 X16 12 4017")
    tran0.writeAction("slorii X16 X16 12 1535")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 2")
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
    tran0.writeAction("addi X20 X17 5")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("commonCarry", state1, state2, 0)
    tran2 = state2.writeTransition("commonCarry", state2, state2, 0)
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa
