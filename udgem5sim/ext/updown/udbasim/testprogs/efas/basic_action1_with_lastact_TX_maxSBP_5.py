from EFA_v2 import *
def basic_action1_with_lastact_TX_maxSBP_5():
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
    tran0.writeAction("movir X16 44118")
    tran0.writeAction("slorii X16 X16 12 1208")
    tran0.writeAction("slorii X16 X16 12 3444")
    tran0.writeAction("slorii X16 X16 12 2931")
    tran0.writeAction("slorii X16 X16 12 1180")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 29850")
    tran0.writeAction("slorii X16 X16 12 961")
    tran0.writeAction("slorii X16 X16 12 4052")
    tran0.writeAction("slorii X16 X16 12 3885")
    tran0.writeAction("slorii X16 X16 12 1051")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 14764")
    tran0.writeAction("slorii X16 X16 12 3383")
    tran0.writeAction("slorii X16 X16 12 1202")
    tran0.writeAction("slorii X16 X16 12 3574")
    tran0.writeAction("slorii X16 X16 12 1144")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 409")
    tran0.writeAction("slorii X16 X16 12 1462")
    tran0.writeAction("slorii X16 X16 12 2513")
    tran0.writeAction("slorii X16 X16 12 2443")
    tran0.writeAction("slorii X16 X16 12 3757")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 39303")
    tran0.writeAction("slorii X16 X16 12 1011")
    tran0.writeAction("slorii X16 X16 12 3542")
    tran0.writeAction("slorii X16 X16 12 645")
    tran0.writeAction("slorii X16 X16 12 985")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 48794")
    tran0.writeAction("slorii X16 X16 12 2371")
    tran0.writeAction("slorii X16 X16 12 1843")
    tran0.writeAction("slorii X16 X16 12 603")
    tran0.writeAction("slorii X16 X16 12 1149")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 62288")
    tran0.writeAction("slorii X16 X16 12 593")
    tran0.writeAction("slorii X16 X16 12 3240")
    tran0.writeAction("slorii X16 X16 12 1457")
    tran0.writeAction("slorii X16 X16 12 2464")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 58561")
    tran0.writeAction("slorii X16 X16 12 2679")
    tran0.writeAction("slorii X16 X16 12 3629")
    tran0.writeAction("slorii X16 X16 12 1382")
    tran0.writeAction("slorii X16 X16 12 3942")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 44118")
    tran0.writeAction("slorii X16 X16 12 1208")
    tran0.writeAction("slorii X16 X16 12 3444")
    tran0.writeAction("slorii X16 X16 12 2931")
    tran0.writeAction("slorii X16 X16 12 1180")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 36")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 6")
    tran0.writeAction("sli X17 X17 32")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X20 0")
    tran0.writeAction("add X20 X7 X5")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("addi X20 X17 6")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("basic_with_action", state1, state2, 156)
    tran1.writeAction("movir X30 7")
    tran1.writeAction("lastact")
    tran3 = state1.writeTransition("basic_with_action", state1, state2, 255)
    tran3.writeAction("movir X30 8")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("basic_with_action", state2, state2, 86)
    tran2.writeAction("movir X30 7")
    tran4 = state2.writeTransition("basic_with_action", state2, state1, 255)
    tran4.writeAction("addi X5 X17 0")
    tran4.writeAction("movir X30 8")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa