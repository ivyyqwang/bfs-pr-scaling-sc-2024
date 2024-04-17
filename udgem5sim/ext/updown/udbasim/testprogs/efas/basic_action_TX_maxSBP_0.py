from EFA_v2 import *
def basic_action_TX_maxSBP_0():
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
    tran0.writeAction("movir X16 45965")
    tran0.writeAction("slorii X16 X16 12 3728")
    tran0.writeAction("slorii X16 X16 12 1439")
    tran0.writeAction("slorii X16 X16 12 3619")
    tran0.writeAction("slorii X16 X16 12 867")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 53668")
    tran0.writeAction("slorii X16 X16 12 3941")
    tran0.writeAction("slorii X16 X16 12 1066")
    tran0.writeAction("slorii X16 X16 12 587")
    tran0.writeAction("slorii X16 X16 12 3879")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 12008")
    tran0.writeAction("slorii X16 X16 12 3100")
    tran0.writeAction("slorii X16 X16 12 740")
    tran0.writeAction("slorii X16 X16 12 354")
    tran0.writeAction("slorii X16 X16 12 1521")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 24322")
    tran0.writeAction("slorii X16 X16 12 1651")
    tran0.writeAction("slorii X16 X16 12 2361")
    tran0.writeAction("slorii X16 X16 12 1187")
    tran0.writeAction("slorii X16 X16 12 1705")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 21632")
    tran0.writeAction("slorii X16 X16 12 1867")
    tran0.writeAction("slorii X16 X16 12 1017")
    tran0.writeAction("slorii X16 X16 12 1687")
    tran0.writeAction("slorii X16 X16 12 4088")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 64137")
    tran0.writeAction("slorii X16 X16 12 592")
    tran0.writeAction("slorii X16 X16 12 1187")
    tran0.writeAction("slorii X16 X16 12 4095")
    tran0.writeAction("slorii X16 X16 12 21")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 2371")
    tran0.writeAction("slorii X16 X16 12 3512")
    tran0.writeAction("slorii X16 X16 12 1304")
    tran0.writeAction("slorii X16 X16 12 2920")
    tran0.writeAction("slorii X16 X16 12 2742")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 30393")
    tran0.writeAction("slorii X16 X16 12 3966")
    tran0.writeAction("slorii X16 X16 12 2857")
    tran0.writeAction("slorii X16 X16 12 3803")
    tran0.writeAction("slorii X16 X16 12 1543")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 45965")
    tran0.writeAction("slorii X16 X16 12 3728")
    tran0.writeAction("slorii X16 X16 12 1439")
    tran0.writeAction("slorii X16 X16 12 3619")
    tran0.writeAction("slorii X16 X16 12 867")
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
    tran1 = state1.writeTransition("basic_with_action", state1, state2, 99)
    tran1.writeAction("addi X5 X16 0")
    tran1.writeAction("movir X30 5")
    tran1.writeAction("movir X29 5")
    tran1.writeAction("lastact")
    tran3 = state1.writeTransition("basic_with_action", state1, state2, 255)
    tran3.writeAction("addi X5 X16 0")
    tran3.writeAction("movir X30 6")
    tran3.writeAction("movir X29 6")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("basic_with_action", state2, state2, 141)
    tran2.writeAction("addi X5 X17 0")
    tran2.writeAction("movir X31 5")
    tran4 = state2.writeTransition("basic_with_action", state2, state1, 255)
    tran4.writeAction("addi X5 X17 0")
    tran4.writeAction("movir X31 6")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa
