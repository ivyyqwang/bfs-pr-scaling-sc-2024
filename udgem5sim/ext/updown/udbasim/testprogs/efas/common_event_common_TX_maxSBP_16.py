from EFA_v2 import *
def common_event_common_TX_maxSBP_16():
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
    tran0.writeAction("movir X16 27092")
    tran0.writeAction("slorii X16 X16 12 3736")
    tran0.writeAction("slorii X16 X16 12 3951")
    tran0.writeAction("slorii X16 X16 12 511")
    tran0.writeAction("slorii X16 X16 12 2397")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 2914")
    tran0.writeAction("slorii X16 X16 12 1829")
    tran0.writeAction("slorii X16 X16 12 1803")
    tran0.writeAction("slorii X16 X16 12 2260")
    tran0.writeAction("slorii X16 X16 12 4049")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 7785")
    tran0.writeAction("slorii X16 X16 12 393")
    tran0.writeAction("slorii X16 X16 12 2534")
    tran0.writeAction("slorii X16 X16 12 3705")
    tran0.writeAction("slorii X16 X16 12 2947")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 30753")
    tran0.writeAction("slorii X16 X16 12 4036")
    tran0.writeAction("slorii X16 X16 12 4045")
    tran0.writeAction("slorii X16 X16 12 1381")
    tran0.writeAction("slorii X16 X16 12 2419")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 43813")
    tran0.writeAction("slorii X16 X16 12 2107")
    tran0.writeAction("slorii X16 X16 12 3536")
    tran0.writeAction("slorii X16 X16 12 239")
    tran0.writeAction("slorii X16 X16 12 1406")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 18432")
    tran0.writeAction("slorii X16 X16 12 757")
    tran0.writeAction("slorii X16 X16 12 3850")
    tran0.writeAction("slorii X16 X16 12 1436")
    tran0.writeAction("slorii X16 X16 12 1325")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 56356")
    tran0.writeAction("slorii X16 X16 12 3707")
    tran0.writeAction("slorii X16 X16 12 1683")
    tran0.writeAction("slorii X16 X16 12 2917")
    tran0.writeAction("slorii X16 X16 12 3909")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 21652")
    tran0.writeAction("slorii X16 X16 12 618")
    tran0.writeAction("slorii X16 X16 12 2052")
    tran0.writeAction("slorii X16 X16 12 1125")
    tran0.writeAction("slorii X16 X16 12 1795")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 27092")
    tran0.writeAction("slorii X16 X16 12 3736")
    tran0.writeAction("slorii X16 X16 12 3951")
    tran0.writeAction("slorii X16 X16 12 511")
    tran0.writeAction("slorii X16 X16 12 2397")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 7")
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
    tran0.writeAction("addi X20 X17 8")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("commonCarry_with_action", state1, state2, 0)
    tran1.writeAction("addi X30 X30 1")
    tran1.writeAction("addi X5 X20 0")
    tran1.writeAction("lastact")
    tran2 = state2.writeTransition("commonCarry_with_action", state2, state2, 0)
    tran2.writeAction("addi X31 X31 1")
    tran2.writeAction("addi X5 X19 0")
    tran2.writeAction("yieldt")
    tran4 = state.writeTransition("event", state, state2, 0)
    tran4.writeAction("movir X16 0")
    tran4.writeAction("add X4 X16 X17")
    tran4.writeAction("sri X17 X17 32")
    tran4.writeAction("sli X17 X17 32")
    tran4.writeAction("addi X17 X17 24")
    tran4.writeAction("add X17 X16 X4")
    tran4.writeAction("addi X30 X30 1")
    tran4.writeAction("addi X5 X18 0")
    tran4.writeAction("lastact")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yield")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa
