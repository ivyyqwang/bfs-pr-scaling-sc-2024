from EFA_v2 import *
def basic_noaction2_with_lastact_TX_maxSBP_7():
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
    tran0.writeAction("movir X16 11574")
    tran0.writeAction("slorii X16 X16 12 2430")
    tran0.writeAction("slorii X16 X16 12 17")
    tran0.writeAction("slorii X16 X16 12 2501")
    tran0.writeAction("slorii X16 X16 12 1823")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 29730")
    tran0.writeAction("slorii X16 X16 12 1049")
    tran0.writeAction("slorii X16 X16 12 86")
    tran0.writeAction("slorii X16 X16 12 885")
    tran0.writeAction("slorii X16 X16 12 3103")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 34732")
    tran0.writeAction("slorii X16 X16 12 2481")
    tran0.writeAction("slorii X16 X16 12 123")
    tran0.writeAction("slorii X16 X16 12 2553")
    tran0.writeAction("slorii X16 X16 12 2126")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 32357")
    tran0.writeAction("slorii X16 X16 12 729")
    tran0.writeAction("slorii X16 X16 12 1283")
    tran0.writeAction("slorii X16 X16 12 3561")
    tran0.writeAction("slorii X16 X16 12 2102")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 52779")
    tran0.writeAction("slorii X16 X16 12 1501")
    tran0.writeAction("slorii X16 X16 12 1321")
    tran0.writeAction("slorii X16 X16 12 3751")
    tran0.writeAction("slorii X16 X16 12 3219")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 17290")
    tran0.writeAction("slorii X16 X16 12 1354")
    tran0.writeAction("slorii X16 X16 12 2893")
    tran0.writeAction("slorii X16 X16 12 2865")
    tran0.writeAction("slorii X16 X16 12 2774")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 39986")
    tran0.writeAction("slorii X16 X16 12 1239")
    tran0.writeAction("slorii X16 X16 12 370")
    tran0.writeAction("slorii X16 X16 12 2909")
    tran0.writeAction("slorii X16 X16 12 177")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 50762")
    tran0.writeAction("slorii X16 X16 12 307")
    tran0.writeAction("slorii X16 X16 12 1086")
    tran0.writeAction("slorii X16 X16 12 2439")
    tran0.writeAction("slorii X16 X16 12 1708")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 11574")
    tran0.writeAction("slorii X16 X16 12 2430")
    tran0.writeAction("slorii X16 X16 12 17")
    tran0.writeAction("slorii X16 X16 12 2501")
    tran0.writeAction("slorii X16 X16 12 1823")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 5")
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
    tran1 = state1.writeTransition("basic", state1, state2, 31)
    tran3 = state1.writeTransition("basic_with_action", state1, state2, 255)
    tran3.writeAction("addi X5 X16 0")
    tran3.writeAction("movir X30 8")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("basic", state2, state2, 24)
    tran4 = state2.writeTransition("basic_with_action", state2, state1, 255)
    tran4.writeAction("addi X5 X17 0")
    tran4.writeAction("movir X31 8")
    tran4.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa