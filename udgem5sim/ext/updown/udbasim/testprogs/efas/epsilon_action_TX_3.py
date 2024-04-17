from EFA_v2 import *
def epsilon_action_TX_3():
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
    tran0.writeAction("movir X16 27308")
    tran0.writeAction("slorii X16 X16 12 1286")
    tran0.writeAction("slorii X16 X16 12 3186")
    tran0.writeAction("slorii X16 X16 12 1425")
    tran0.writeAction("slorii X16 X16 12 1445")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 24931")
    tran0.writeAction("slorii X16 X16 12 1501")
    tran0.writeAction("slorii X16 X16 12 912")
    tran0.writeAction("slorii X16 X16 12 1536")
    tran0.writeAction("slorii X16 X16 12 2129")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 32356")
    tran0.writeAction("slorii X16 X16 12 4050")
    tran0.writeAction("slorii X16 X16 12 4033")
    tran0.writeAction("slorii X16 X16 12 77")
    tran0.writeAction("slorii X16 X16 12 2909")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 48973")
    tran0.writeAction("slorii X16 X16 12 753")
    tran0.writeAction("slorii X16 X16 12 1447")
    tran0.writeAction("slorii X16 X16 12 2132")
    tran0.writeAction("slorii X16 X16 12 1051")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 54827")
    tran0.writeAction("slorii X16 X16 12 696")
    tran0.writeAction("slorii X16 X16 12 1157")
    tran0.writeAction("slorii X16 X16 12 3130")
    tran0.writeAction("slorii X16 X16 12 2847")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 65339")
    tran0.writeAction("slorii X16 X16 12 174")
    tran0.writeAction("slorii X16 X16 12 2010")
    tran0.writeAction("slorii X16 X16 12 3032")
    tran0.writeAction("slorii X16 X16 12 3017")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 49814")
    tran0.writeAction("slorii X16 X16 12 816")
    tran0.writeAction("slorii X16 X16 12 548")
    tran0.writeAction("slorii X16 X16 12 3840")
    tran0.writeAction("slorii X16 X16 12 2080")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 63818")
    tran0.writeAction("slorii X16 X16 12 1442")
    tran0.writeAction("slorii X16 X16 12 2863")
    tran0.writeAction("slorii X16 X16 12 3628")
    tran0.writeAction("slorii X16 X16 12 848")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 27308")
    tran0.writeAction("slorii X16 X16 12 1286")
    tran0.writeAction("slorii X16 X16 12 3186")
    tran0.writeAction("slorii X16 X16 12 1425")
    tran0.writeAction("slorii X16 X16 12 1445")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 4")
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