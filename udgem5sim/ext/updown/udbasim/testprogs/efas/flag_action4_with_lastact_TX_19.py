from EFA_v2 import *
def flag_action4_with_lastact_TX_19():
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
    tran0.writeAction("movir X16 51019")
    tran0.writeAction("slorii X16 X16 12 2070")
    tran0.writeAction("slorii X16 X16 12 3884")
    tran0.writeAction("slorii X16 X16 12 338")
    tran0.writeAction("slorii X16 X16 12 2058")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 17621")
    tran0.writeAction("slorii X16 X16 12 187")
    tran0.writeAction("slorii X16 X16 12 2369")
    tran0.writeAction("slorii X16 X16 12 1393")
    tran0.writeAction("slorii X16 X16 12 390")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 38852")
    tran0.writeAction("slorii X16 X16 12 294")
    tran0.writeAction("slorii X16 X16 12 880")
    tran0.writeAction("slorii X16 X16 12 1379")
    tran0.writeAction("slorii X16 X16 12 638")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 12893")
    tran0.writeAction("slorii X16 X16 12 2374")
    tran0.writeAction("slorii X16 X16 12 2066")
    tran0.writeAction("slorii X16 X16 12 1245")
    tran0.writeAction("slorii X16 X16 12 2650")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 4798")
    tran0.writeAction("slorii X16 X16 12 2042")
    tran0.writeAction("slorii X16 X16 12 1385")
    tran0.writeAction("slorii X16 X16 12 586")
    tran0.writeAction("slorii X16 X16 12 2547")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 5998")
    tran0.writeAction("slorii X16 X16 12 18")
    tran0.writeAction("slorii X16 X16 12 4070")
    tran0.writeAction("slorii X16 X16 12 385")
    tran0.writeAction("slorii X16 X16 12 3437")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 13439")
    tran0.writeAction("slorii X16 X16 12 2305")
    tran0.writeAction("slorii X16 X16 12 3699")
    tran0.writeAction("slorii X16 X16 12 3205")
    tran0.writeAction("slorii X16 X16 12 3731")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 42318")
    tran0.writeAction("slorii X16 X16 12 3954")
    tran0.writeAction("slorii X16 X16 12 1056")
    tran0.writeAction("slorii X16 X16 12 2822")
    tran0.writeAction("slorii X16 X16 12 429")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 51019")
    tran0.writeAction("slorii X16 X16 12 2070")
    tran0.writeAction("slorii X16 X16 12 3884")
    tran0.writeAction("slorii X16 X16 12 338")
    tran0.writeAction("slorii X16 X16 12 2058")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 6")
    tran0.writeAction("sli X17 X17 36")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 7")
    tran0.writeAction("sli X17 X17 32")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("add X7 X31 X31")
    tran0.writeAction("movir X20 0")
    tran0.writeAction("sli X31 X21 3")
    tran0.writeAction("add X21 X20 X5")
    tran0.writeAction("movlsb X31")
    tran0.writeAction("addi X20 X17 21")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("movir X16 222")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("flagCarry_with_action", state1, state2, 222)
    tran1.writeAction("movir X16 100")
    tran1.writeAction("movir X30 7")
    tran1.writeAction("movir X29 7")
    tran1.writeAction("movir X28 7")
    tran1.writeAction("lastact")
    tran3 = state1.writeTransition("flagCarry_with_action", state1, state2, 255)
    tran3.writeAction("movir X16 255")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("flagCarry_with_action", state2, state2, 100)
    tran2.writeAction("addi X5 X17 0")
    tran2.writeAction("movir X31 7")
    tran2.writeAction("movir X31 8")
    tran2.writeAction("movir X31 9")
    tran2.writeAction("yieldt")
    tran4 = state2.writeTransition("flagCarry_with_action", state2, state1, 255)
    tran4.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa
