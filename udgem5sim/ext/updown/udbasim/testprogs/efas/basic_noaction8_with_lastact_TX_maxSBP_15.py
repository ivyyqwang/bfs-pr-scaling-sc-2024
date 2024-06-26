from EFA_v2 import *
def basic_noaction8_with_lastact_TX_maxSBP_15():
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
    tran0.writeAction("movir X16 17231")
    tran0.writeAction("slorii X16 X16 12 3678")
    tran0.writeAction("slorii X16 X16 12 3981")
    tran0.writeAction("slorii X16 X16 12 3936")
    tran0.writeAction("slorii X16 X16 12 354")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 57701")
    tran0.writeAction("slorii X16 X16 12 379")
    tran0.writeAction("slorii X16 X16 12 2367")
    tran0.writeAction("slorii X16 X16 12 1442")
    tran0.writeAction("slorii X16 X16 12 485")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 50625")
    tran0.writeAction("slorii X16 X16 12 3563")
    tran0.writeAction("slorii X16 X16 12 1525")
    tran0.writeAction("slorii X16 X16 12 1559")
    tran0.writeAction("slorii X16 X16 12 3221")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 61690")
    tran0.writeAction("slorii X16 X16 12 3996")
    tran0.writeAction("slorii X16 X16 12 1597")
    tran0.writeAction("slorii X16 X16 12 654")
    tran0.writeAction("slorii X16 X16 12 1511")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 49496")
    tran0.writeAction("slorii X16 X16 12 3488")
    tran0.writeAction("slorii X16 X16 12 1583")
    tran0.writeAction("slorii X16 X16 12 2184")
    tran0.writeAction("slorii X16 X16 12 525")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 53795")
    tran0.writeAction("slorii X16 X16 12 331")
    tran0.writeAction("slorii X16 X16 12 363")
    tran0.writeAction("slorii X16 X16 12 1922")
    tran0.writeAction("slorii X16 X16 12 1673")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 44508")
    tran0.writeAction("slorii X16 X16 12 423")
    tran0.writeAction("slorii X16 X16 12 3616")
    tran0.writeAction("slorii X16 X16 12 2453")
    tran0.writeAction("slorii X16 X16 12 1894")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 63317")
    tran0.writeAction("slorii X16 X16 12 269")
    tran0.writeAction("slorii X16 X16 12 180")
    tran0.writeAction("slorii X16 X16 12 693")
    tran0.writeAction("slorii X16 X16 12 158")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 17231")
    tran0.writeAction("slorii X16 X16 12 3678")
    tran0.writeAction("slorii X16 X16 12 3981")
    tran0.writeAction("slorii X16 X16 12 3936")
    tran0.writeAction("slorii X16 X16 12 354")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 36")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 5")
    tran0.writeAction("sli X17 X17 32")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X20 0")
    tran0.writeAction("add X20 X7 X5")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("addi X20 X17 5")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("basic", state1, state2, 98)
    tran3 = state1.writeTransition("basic_with_action", state1, state2, 255)
    tran3.writeAction("movir X30 8")
    tran3.writeAction("movir X29 8")
    tran3.writeAction("movir X28 8")
    tran3.writeAction("movir X27 8")
    tran3.writeAction("movir X26 8")
    tran3.writeAction("movir X25 8")
    tran3.writeAction("movir X24 8")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("basic", state2, state2, 229)
    tran4 = state2.writeTransition("basic_with_action", state2, state1, 255)
    tran4.writeAction("addi X5 X17 0")
    tran4.writeAction("movir X31 8")
    tran4.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa
