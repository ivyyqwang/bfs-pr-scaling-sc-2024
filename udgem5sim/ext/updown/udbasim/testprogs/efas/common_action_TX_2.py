from EFA_v2 import *
def common_action_TX_2():
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
    tran0.writeAction("movir X16 834")
    tran0.writeAction("slorii X16 X16 12 228")
    tran0.writeAction("slorii X16 X16 12 1668")
    tran0.writeAction("slorii X16 X16 12 816")
    tran0.writeAction("slorii X16 X16 12 3101")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 24459")
    tran0.writeAction("slorii X16 X16 12 3469")
    tran0.writeAction("slorii X16 X16 12 2283")
    tran0.writeAction("slorii X16 X16 12 242")
    tran0.writeAction("slorii X16 X16 12 3858")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 27726")
    tran0.writeAction("slorii X16 X16 12 3009")
    tran0.writeAction("slorii X16 X16 12 320")
    tran0.writeAction("slorii X16 X16 12 602")
    tran0.writeAction("slorii X16 X16 12 2626")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 13255")
    tran0.writeAction("slorii X16 X16 12 3729")
    tran0.writeAction("slorii X16 X16 12 3440")
    tran0.writeAction("slorii X16 X16 12 1224")
    tran0.writeAction("slorii X16 X16 12 1242")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 6134")
    tran0.writeAction("slorii X16 X16 12 3399")
    tran0.writeAction("slorii X16 X16 12 282")
    tran0.writeAction("slorii X16 X16 12 1942")
    tran0.writeAction("slorii X16 X16 12 3000")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 61256")
    tran0.writeAction("slorii X16 X16 12 646")
    tran0.writeAction("slorii X16 X16 12 973")
    tran0.writeAction("slorii X16 X16 12 2134")
    tran0.writeAction("slorii X16 X16 12 2906")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 4592")
    tran0.writeAction("slorii X16 X16 12 442")
    tran0.writeAction("slorii X16 X16 12 202")
    tran0.writeAction("slorii X16 X16 12 2957")
    tran0.writeAction("slorii X16 X16 12 799")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 53902")
    tran0.writeAction("slorii X16 X16 12 1587")
    tran0.writeAction("slorii X16 X16 12 770")
    tran0.writeAction("slorii X16 X16 12 3238")
    tran0.writeAction("slorii X16 X16 12 3251")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 834")
    tran0.writeAction("slorii X16 X16 12 228")
    tran0.writeAction("slorii X16 X16 12 1668")
    tran0.writeAction("slorii X16 X16 12 816")
    tran0.writeAction("slorii X16 X16 12 3101")
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