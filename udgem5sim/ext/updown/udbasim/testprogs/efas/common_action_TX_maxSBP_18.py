from EFA_v2 import *
def common_action_TX_maxSBP_18():
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
    tran0.writeAction("movir X16 31292")
    tran0.writeAction("slorii X16 X16 12 2652")
    tran0.writeAction("slorii X16 X16 12 214")
    tran0.writeAction("slorii X16 X16 12 3189")
    tran0.writeAction("slorii X16 X16 12 3391")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 28075")
    tran0.writeAction("slorii X16 X16 12 27")
    tran0.writeAction("slorii X16 X16 12 3995")
    tran0.writeAction("slorii X16 X16 12 2532")
    tran0.writeAction("slorii X16 X16 12 174")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 56669")
    tran0.writeAction("slorii X16 X16 12 565")
    tran0.writeAction("slorii X16 X16 12 2469")
    tran0.writeAction("slorii X16 X16 12 1444")
    tran0.writeAction("slorii X16 X16 12 229")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 23584")
    tran0.writeAction("slorii X16 X16 12 2576")
    tran0.writeAction("slorii X16 X16 12 1171")
    tran0.writeAction("slorii X16 X16 12 1813")
    tran0.writeAction("slorii X16 X16 12 2338")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 21503")
    tran0.writeAction("slorii X16 X16 12 1471")
    tran0.writeAction("slorii X16 X16 12 178")
    tran0.writeAction("slorii X16 X16 12 740")
    tran0.writeAction("slorii X16 X16 12 1693")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 49933")
    tran0.writeAction("slorii X16 X16 12 3125")
    tran0.writeAction("slorii X16 X16 12 1782")
    tran0.writeAction("slorii X16 X16 12 700")
    tran0.writeAction("slorii X16 X16 12 228")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 58459")
    tran0.writeAction("slorii X16 X16 12 2785")
    tran0.writeAction("slorii X16 X16 12 2066")
    tran0.writeAction("slorii X16 X16 12 3425")
    tran0.writeAction("slorii X16 X16 12 918")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 35147")
    tran0.writeAction("slorii X16 X16 12 2756")
    tran0.writeAction("slorii X16 X16 12 2403")
    tran0.writeAction("slorii X16 X16 12 219")
    tran0.writeAction("slorii X16 X16 12 1574")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 31292")
    tran0.writeAction("slorii X16 X16 12 2652")
    tran0.writeAction("slorii X16 X16 12 214")
    tran0.writeAction("slorii X16 X16 12 3189")
    tran0.writeAction("slorii X16 X16 12 3391")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 2")
    tran0.writeAction("sli X17 X17 36")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 6")
    tran0.writeAction("sli X17 X17 32")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("add X7 X31 X31")
    tran0.writeAction("movir X20 0")
    tran0.writeAction("sli X31 X21 3")
    tran0.writeAction("add X21 X20 X5")
    tran0.writeAction("movlsb X31")
    tran0.writeAction("addi X20 X17 6")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("commonCarry_with_action", state1, state2, 0)
    tran1.writeAction("addi X5 X16 0")
    tran1.writeAction("movir X30 1")
    tran1.writeAction("lastact")
    tran2 = state2.writeTransition("commonCarry_with_action", state2, state2, 0)
    tran2.writeAction("addi X5 X17 0")
    tran2.writeAction("movir X31 2")
    tran2.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa
