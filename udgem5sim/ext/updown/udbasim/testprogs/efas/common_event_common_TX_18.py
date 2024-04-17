from EFA_v2 import *
def common_event_common_TX_18():
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
    tran0.writeAction("movir X16 35347")
    tran0.writeAction("slorii X16 X16 12 2425")
    tran0.writeAction("slorii X16 X16 12 2922")
    tran0.writeAction("slorii X16 X16 12 3068")
    tran0.writeAction("slorii X16 X16 12 372")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 54375")
    tran0.writeAction("slorii X16 X16 12 487")
    tran0.writeAction("slorii X16 X16 12 958")
    tran0.writeAction("slorii X16 X16 12 3035")
    tran0.writeAction("slorii X16 X16 12 1633")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 24946")
    tran0.writeAction("slorii X16 X16 12 3906")
    tran0.writeAction("slorii X16 X16 12 623")
    tran0.writeAction("slorii X16 X16 12 451")
    tran0.writeAction("slorii X16 X16 12 2408")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 8549")
    tran0.writeAction("slorii X16 X16 12 2849")
    tran0.writeAction("slorii X16 X16 12 320")
    tran0.writeAction("slorii X16 X16 12 2859")
    tran0.writeAction("slorii X16 X16 12 2270")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 26660")
    tran0.writeAction("slorii X16 X16 12 2087")
    tran0.writeAction("slorii X16 X16 12 3000")
    tran0.writeAction("slorii X16 X16 12 1525")
    tran0.writeAction("slorii X16 X16 12 471")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 3570")
    tran0.writeAction("slorii X16 X16 12 19")
    tran0.writeAction("slorii X16 X16 12 1368")
    tran0.writeAction("slorii X16 X16 12 917")
    tran0.writeAction("slorii X16 X16 12 3859")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 59298")
    tran0.writeAction("slorii X16 X16 12 1281")
    tran0.writeAction("slorii X16 X16 12 1662")
    tran0.writeAction("slorii X16 X16 12 3748")
    tran0.writeAction("slorii X16 X16 12 459")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 53082")
    tran0.writeAction("slorii X16 X16 12 3454")
    tran0.writeAction("slorii X16 X16 12 1990")
    tran0.writeAction("slorii X16 X16 12 1754")
    tran0.writeAction("slorii X16 X16 12 1318")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 35347")
    tran0.writeAction("slorii X16 X16 12 2425")
    tran0.writeAction("slorii X16 X16 12 2922")
    tran0.writeAction("slorii X16 X16 12 3068")
    tran0.writeAction("slorii X16 X16 12 372")
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
    tran0.writeAction("addi X20 X17 15")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("commonCarry_with_action", state1, state2, 0)
    tran1.writeAction("addi X30 X30 1")
    tran1.writeAction("addi X5 X17 0")
    tran1.writeAction("yield")
    tran2 = state2.writeTransition("commonCarry_with_action", state2, state2, 0)
    tran2.writeAction("addi X31 X31 1")
    tran2.writeAction("addi X5 X19 0")
    tran2.writeAction("yieldt")
    tran4 = state.writeTransition("event", state, state2, 0)
    tran4.writeAction("addi X30 X30 1")
    tran4.writeAction("addi X5 X18 0")
    tran4.writeAction("lastact")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa
