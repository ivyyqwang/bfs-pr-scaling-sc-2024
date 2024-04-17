from EFA_v2 import *
def basic_action1_with_lastact_TX_maxSBP_2():
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
    tran0.writeAction("movir X16 17767")
    tran0.writeAction("slorii X16 X16 12 2128")
    tran0.writeAction("slorii X16 X16 12 2131")
    tran0.writeAction("slorii X16 X16 12 116")
    tran0.writeAction("slorii X16 X16 12 2296")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 46549")
    tran0.writeAction("slorii X16 X16 12 2293")
    tran0.writeAction("slorii X16 X16 12 1217")
    tran0.writeAction("slorii X16 X16 12 1601")
    tran0.writeAction("slorii X16 X16 12 872")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 61092")
    tran0.writeAction("slorii X16 X16 12 200")
    tran0.writeAction("slorii X16 X16 12 3887")
    tran0.writeAction("slorii X16 X16 12 1733")
    tran0.writeAction("slorii X16 X16 12 3514")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 14205")
    tran0.writeAction("slorii X16 X16 12 757")
    tran0.writeAction("slorii X16 X16 12 204")
    tran0.writeAction("slorii X16 X16 12 1835")
    tran0.writeAction("slorii X16 X16 12 2732")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 41329")
    tran0.writeAction("slorii X16 X16 12 1511")
    tran0.writeAction("slorii X16 X16 12 3014")
    tran0.writeAction("slorii X16 X16 12 766")
    tran0.writeAction("slorii X16 X16 12 1351")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 58231")
    tran0.writeAction("slorii X16 X16 12 2437")
    tran0.writeAction("slorii X16 X16 12 914")
    tran0.writeAction("slorii X16 X16 12 3948")
    tran0.writeAction("slorii X16 X16 12 297")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 35146")
    tran0.writeAction("slorii X16 X16 12 3320")
    tran0.writeAction("slorii X16 X16 12 420")
    tran0.writeAction("slorii X16 X16 12 1148")
    tran0.writeAction("slorii X16 X16 12 3507")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 34989")
    tran0.writeAction("slorii X16 X16 12 3126")
    tran0.writeAction("slorii X16 X16 12 1872")
    tran0.writeAction("slorii X16 X16 12 2245")
    tran0.writeAction("slorii X16 X16 12 395")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 17767")
    tran0.writeAction("slorii X16 X16 12 2128")
    tran0.writeAction("slorii X16 X16 12 2131")
    tran0.writeAction("slorii X16 X16 12 116")
    tran0.writeAction("slorii X16 X16 12 2296")
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
    tran1 = state1.writeTransition("basic_with_action", state1, state2, 24)
    tran1.writeAction("movir X30 7")
    tran1.writeAction("lastact")
    tran3 = state1.writeTransition("basic_with_action", state1, state2, 255)
    tran3.writeAction("movir X30 8")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("basic_with_action", state2, state2, 7)
    tran2.writeAction("movir X30 7")
    tran4 = state2.writeTransition("basic_with_action", state2, state1, 255)
    tran4.writeAction("addi X5 X17 0")
    tran4.writeAction("movir X30 8")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa