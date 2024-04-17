from EFA_v2 import *
def basic_noaction4_with_lastact_TX_13():
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
    tran0.writeAction("movir X16 0")
    tran0.writeAction("slorii X16 X16 12 0")
    tran0.writeAction("slorii X16 X16 12 0")
    tran0.writeAction("slorii X16 X16 12 0")
    tran0.writeAction("slorii X16 X16 12 104")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 0")
    tran0.writeAction("slorii X16 X16 12 0")
    tran0.writeAction("slorii X16 X16 12 0")
    tran0.writeAction("slorii X16 X16 12 0")
    tran0.writeAction("slorii X16 X16 12 221")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 8054")
    tran0.writeAction("slorii X16 X16 12 2728")
    tran0.writeAction("slorii X16 X16 12 1235")
    tran0.writeAction("slorii X16 X16 12 589")
    tran0.writeAction("slorii X16 X16 12 2068")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 53880")
    tran0.writeAction("slorii X16 X16 12 1188")
    tran0.writeAction("slorii X16 X16 12 2643")
    tran0.writeAction("slorii X16 X16 12 2372")
    tran0.writeAction("slorii X16 X16 12 1577")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 24292")
    tran0.writeAction("slorii X16 X16 12 2539")
    tran0.writeAction("slorii X16 X16 12 2748")
    tran0.writeAction("slorii X16 X16 12 1456")
    tran0.writeAction("slorii X16 X16 12 3190")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 8506")
    tran0.writeAction("slorii X16 X16 12 2386")
    tran0.writeAction("slorii X16 X16 12 1425")
    tran0.writeAction("slorii X16 X16 12 1512")
    tran0.writeAction("slorii X16 X16 12 2412")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 15409")
    tran0.writeAction("slorii X16 X16 12 2692")
    tran0.writeAction("slorii X16 X16 12 1876")
    tran0.writeAction("slorii X16 X16 12 126")
    tran0.writeAction("slorii X16 X16 12 2455")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 61920")
    tran0.writeAction("slorii X16 X16 12 225")
    tran0.writeAction("slorii X16 X16 12 3762")
    tran0.writeAction("slorii X16 X16 12 1908")
    tran0.writeAction("slorii X16 X16 12 1505")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 0")
    tran0.writeAction("slorii X16 X16 12 0")
    tran0.writeAction("slorii X16 X16 12 0")
    tran0.writeAction("slorii X16 X16 12 0")
    tran0.writeAction("slorii X16 X16 12 104")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 8")
    tran0.writeAction("sli X17 X17 36")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 8")
    tran0.writeAction("sli X17 X17 32")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X20 0")
    tran0.writeAction("add X20 X7 X5")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("addi X20 X17 24")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("basic", state1, state2, 104)
    tran3 = state1.writeTransition("basic_with_action", state1, state2, 255)
    tran3.writeAction("addi X5 X16 8")
    tran3.writeAction("movir X30 8")
    tran3.writeAction("movir X29 8")
    tran3.writeAction("movir X28 8")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("basic_with_action", state2, state2, 221)
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
