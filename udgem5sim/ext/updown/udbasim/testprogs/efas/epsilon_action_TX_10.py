from EFA_v2 import *
def epsilon_action_TX_10():
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
    tran0 = state.writeTransition("epsilonCarry_with_action", state, state1, 1)
    tran0.writeAction("movir X17 0")
    tran0.writeAction("add X7 X17 X17")
    tran0.writeAction("movir X16 41022")
    tran0.writeAction("slorii X16 X16 12 1878")
    tran0.writeAction("slorii X16 X16 12 2401")
    tran0.writeAction("slorii X16 X16 12 362")
    tran0.writeAction("slorii X16 X16 12 2383")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 41965")
    tran0.writeAction("slorii X16 X16 12 1442")
    tran0.writeAction("slorii X16 X16 12 3323")
    tran0.writeAction("slorii X16 X16 12 1416")
    tran0.writeAction("slorii X16 X16 12 4084")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 41048")
    tran0.writeAction("slorii X16 X16 12 3049")
    tran0.writeAction("slorii X16 X16 12 1517")
    tran0.writeAction("slorii X16 X16 12 2528")
    tran0.writeAction("slorii X16 X16 12 1160")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 44883")
    tran0.writeAction("slorii X16 X16 12 1525")
    tran0.writeAction("slorii X16 X16 12 1934")
    tran0.writeAction("slorii X16 X16 12 1471")
    tran0.writeAction("slorii X16 X16 12 549")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 52207")
    tran0.writeAction("slorii X16 X16 12 1674")
    tran0.writeAction("slorii X16 X16 12 1501")
    tran0.writeAction("slorii X16 X16 12 2825")
    tran0.writeAction("slorii X16 X16 12 4090")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 22949")
    tran0.writeAction("slorii X16 X16 12 1970")
    tran0.writeAction("slorii X16 X16 12 2278")
    tran0.writeAction("slorii X16 X16 12 1526")
    tran0.writeAction("slorii X16 X16 12 1936")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 5648")
    tran0.writeAction("slorii X16 X16 12 298")
    tran0.writeAction("slorii X16 X16 12 3368")
    tran0.writeAction("slorii X16 X16 12 2576")
    tran0.writeAction("slorii X16 X16 12 2892")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 34783")
    tran0.writeAction("slorii X16 X16 12 1827")
    tran0.writeAction("slorii X16 X16 12 2859")
    tran0.writeAction("slorii X16 X16 12 1840")
    tran0.writeAction("slorii X16 X16 12 3963")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 41022")
    tran0.writeAction("slorii X16 X16 12 1878")
    tran0.writeAction("slorii X16 X16 12 2401")
    tran0.writeAction("slorii X16 X16 12 362")
    tran0.writeAction("slorii X16 X16 12 2383")
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
    tran0.writeAction("addi X20 X17 21")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("epsilonCarry_with_action", state1, state2, 0)
    tran1.writeAction("addi X5 X16 0")
    tran1.writeAction("movir X30 3")
    tran1.writeAction("lastact")
    tran2 = state2.writeTransition("epsilonCarry_with_action", state2, state2, 0)
    tran2.writeAction("addi X5 X17 0")
    tran2.writeAction("movir X31 4")
    tran2.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa
