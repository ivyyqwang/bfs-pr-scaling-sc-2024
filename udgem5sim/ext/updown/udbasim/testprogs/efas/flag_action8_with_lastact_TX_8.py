from EFA_v2 import *
def flag_action8_with_lastact_TX_8():
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
    tran0.writeAction("movir X16 27620")
    tran0.writeAction("slorii X16 X16 12 2535")
    tran0.writeAction("slorii X16 X16 12 3483")
    tran0.writeAction("slorii X16 X16 12 3023")
    tran0.writeAction("slorii X16 X16 12 3196")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 23928")
    tran0.writeAction("slorii X16 X16 12 2058")
    tran0.writeAction("slorii X16 X16 12 1380")
    tran0.writeAction("slorii X16 X16 12 2903")
    tran0.writeAction("slorii X16 X16 12 3506")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 19721")
    tran0.writeAction("slorii X16 X16 12 2514")
    tran0.writeAction("slorii X16 X16 12 4052")
    tran0.writeAction("slorii X16 X16 12 2198")
    tran0.writeAction("slorii X16 X16 12 596")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 44606")
    tran0.writeAction("slorii X16 X16 12 1989")
    tran0.writeAction("slorii X16 X16 12 987")
    tran0.writeAction("slorii X16 X16 12 3291")
    tran0.writeAction("slorii X16 X16 12 2937")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 168")
    tran0.writeAction("slorii X16 X16 12 2108")
    tran0.writeAction("slorii X16 X16 12 929")
    tran0.writeAction("slorii X16 X16 12 213")
    tran0.writeAction("slorii X16 X16 12 634")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 22041")
    tran0.writeAction("slorii X16 X16 12 1509")
    tran0.writeAction("slorii X16 X16 12 1773")
    tran0.writeAction("slorii X16 X16 12 420")
    tran0.writeAction("slorii X16 X16 12 3140")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 3653")
    tran0.writeAction("slorii X16 X16 12 472")
    tran0.writeAction("slorii X16 X16 12 2217")
    tran0.writeAction("slorii X16 X16 12 3037")
    tran0.writeAction("slorii X16 X16 12 2383")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 55244")
    tran0.writeAction("slorii X16 X16 12 3235")
    tran0.writeAction("slorii X16 X16 12 1595")
    tran0.writeAction("slorii X16 X16 12 2253")
    tran0.writeAction("slorii X16 X16 12 1316")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 27620")
    tran0.writeAction("slorii X16 X16 12 2535")
    tran0.writeAction("slorii X16 X16 12 3483")
    tran0.writeAction("slorii X16 X16 12 3023")
    tran0.writeAction("slorii X16 X16 12 3196")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 8")
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
    tran0.writeAction("addi X20 X17 24")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("movir X16 0")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("flagCarry_with_action", state1, state2, 0)
    tran1.writeAction("movir X16 50")
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
    tran2 = state2.writeTransition("flagCarry_with_action", state2, state2, 50)
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
