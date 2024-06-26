from EFA_v2 import *
def common_event_common_TX_maxSBP_14():
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
    tran0.writeAction("movir X16 22839")
    tran0.writeAction("slorii X16 X16 12 3307")
    tran0.writeAction("slorii X16 X16 12 1166")
    tran0.writeAction("slorii X16 X16 12 1471")
    tran0.writeAction("slorii X16 X16 12 124")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 34300")
    tran0.writeAction("slorii X16 X16 12 3284")
    tran0.writeAction("slorii X16 X16 12 2725")
    tran0.writeAction("slorii X16 X16 12 498")
    tran0.writeAction("slorii X16 X16 12 1289")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 7690")
    tran0.writeAction("slorii X16 X16 12 2458")
    tran0.writeAction("slorii X16 X16 12 3350")
    tran0.writeAction("slorii X16 X16 12 265")
    tran0.writeAction("slorii X16 X16 12 1891")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 13365")
    tran0.writeAction("slorii X16 X16 12 2244")
    tran0.writeAction("slorii X16 X16 12 3349")
    tran0.writeAction("slorii X16 X16 12 3760")
    tran0.writeAction("slorii X16 X16 12 1135")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 9870")
    tran0.writeAction("slorii X16 X16 12 310")
    tran0.writeAction("slorii X16 X16 12 2871")
    tran0.writeAction("slorii X16 X16 12 1512")
    tran0.writeAction("slorii X16 X16 12 3432")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 42250")
    tran0.writeAction("slorii X16 X16 12 2429")
    tran0.writeAction("slorii X16 X16 12 2453")
    tran0.writeAction("slorii X16 X16 12 1657")
    tran0.writeAction("slorii X16 X16 12 1722")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 12929")
    tran0.writeAction("slorii X16 X16 12 3873")
    tran0.writeAction("slorii X16 X16 12 1057")
    tran0.writeAction("slorii X16 X16 12 1740")
    tran0.writeAction("slorii X16 X16 12 1300")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 44742")
    tran0.writeAction("slorii X16 X16 12 1705")
    tran0.writeAction("slorii X16 X16 12 2973")
    tran0.writeAction("slorii X16 X16 12 718")
    tran0.writeAction("slorii X16 X16 12 1196")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 22839")
    tran0.writeAction("slorii X16 X16 12 3307")
    tran0.writeAction("slorii X16 X16 12 1166")
    tran0.writeAction("slorii X16 X16 12 1471")
    tran0.writeAction("slorii X16 X16 12 124")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 7")
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
    tran0.writeAction("addi X20 X17 7")
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
    tran4.writeAction("addi X17 X17 21")
    tran4.writeAction("add X17 X16 X4")
    tran4.writeAction("addi X30 X30 1")
    tran4.writeAction("addi X5 X18 0")
    tran4.writeAction("lastact")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yield")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa
