from EFA_v2 import *
def basic_noaction8_with_lastact_TX_11():
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
    tran0.writeAction("movir X16 26730")
    tran0.writeAction("slorii X16 X16 12 3352")
    tran0.writeAction("slorii X16 X16 12 2153")
    tran0.writeAction("slorii X16 X16 12 675")
    tran0.writeAction("slorii X16 X16 12 2219")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 42383")
    tran0.writeAction("slorii X16 X16 12 551")
    tran0.writeAction("slorii X16 X16 12 2471")
    tran0.writeAction("slorii X16 X16 12 1959")
    tran0.writeAction("slorii X16 X16 12 371")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 46004")
    tran0.writeAction("slorii X16 X16 12 1205")
    tran0.writeAction("slorii X16 X16 12 2311")
    tran0.writeAction("slorii X16 X16 12 2391")
    tran0.writeAction("slorii X16 X16 12 1293")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 22384")
    tran0.writeAction("slorii X16 X16 12 863")
    tran0.writeAction("slorii X16 X16 12 1052")
    tran0.writeAction("slorii X16 X16 12 2485")
    tran0.writeAction("slorii X16 X16 12 3531")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 41389")
    tran0.writeAction("slorii X16 X16 12 2931")
    tran0.writeAction("slorii X16 X16 12 897")
    tran0.writeAction("slorii X16 X16 12 3732")
    tran0.writeAction("slorii X16 X16 12 2404")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 53276")
    tran0.writeAction("slorii X16 X16 12 2615")
    tran0.writeAction("slorii X16 X16 12 1667")
    tran0.writeAction("slorii X16 X16 12 1470")
    tran0.writeAction("slorii X16 X16 12 520")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 54409")
    tran0.writeAction("slorii X16 X16 12 1247")
    tran0.writeAction("slorii X16 X16 12 3718")
    tran0.writeAction("slorii X16 X16 12 255")
    tran0.writeAction("slorii X16 X16 12 264")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 50937")
    tran0.writeAction("slorii X16 X16 12 3932")
    tran0.writeAction("slorii X16 X16 12 1349")
    tran0.writeAction("slorii X16 X16 12 1957")
    tran0.writeAction("slorii X16 X16 12 1705")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 26730")
    tran0.writeAction("slorii X16 X16 12 3352")
    tran0.writeAction("slorii X16 X16 12 2153")
    tran0.writeAction("slorii X16 X16 12 675")
    tran0.writeAction("slorii X16 X16 12 2219")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 4")
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
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("basic", state1, state2, 11)
    tran3 = state1.writeTransition("basic_with_action", state1, state2, 255)
    tran3.writeAction("movir X30 8")
    tran3.writeAction("movir X29 8")
    tran3.writeAction("movir X28 8")
    tran3.writeAction("movir X27 8")
    tran3.writeAction("movir X26 8")
    tran3.writeAction("movir X25 8")
    tran3.writeAction("movir X24 8")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("basic_with_action", state2, state2, 1)
    tran2.writeAction("movir X31 7")
    tran2.writeAction("yieldt")
    tran4 = state2.writeTransition("basic_with_action", state2, state1, 255)
    tran4.writeAction("addi X5 X17 0")
    tran4.writeAction("movir X31 8")
    tran4.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa
