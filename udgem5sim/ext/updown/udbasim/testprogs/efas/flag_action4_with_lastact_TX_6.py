from EFA_v2 import *
def flag_action4_with_lastact_TX_6():
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
    tran0.writeAction("movir X16 26768")
    tran0.writeAction("slorii X16 X16 12 3782")
    tran0.writeAction("slorii X16 X16 12 2698")
    tran0.writeAction("slorii X16 X16 12 1624")
    tran0.writeAction("slorii X16 X16 12 315")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 13180")
    tran0.writeAction("slorii X16 X16 12 3440")
    tran0.writeAction("slorii X16 X16 12 2718")
    tran0.writeAction("slorii X16 X16 12 1888")
    tran0.writeAction("slorii X16 X16 12 1532")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 33379")
    tran0.writeAction("slorii X16 X16 12 3481")
    tran0.writeAction("slorii X16 X16 12 3416")
    tran0.writeAction("slorii X16 X16 12 1115")
    tran0.writeAction("slorii X16 X16 12 2")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 2800")
    tran0.writeAction("slorii X16 X16 12 3750")
    tran0.writeAction("slorii X16 X16 12 3603")
    tran0.writeAction("slorii X16 X16 12 2780")
    tran0.writeAction("slorii X16 X16 12 1107")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 54924")
    tran0.writeAction("slorii X16 X16 12 1623")
    tran0.writeAction("slorii X16 X16 12 866")
    tran0.writeAction("slorii X16 X16 12 42")
    tran0.writeAction("slorii X16 X16 12 2303")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 49181")
    tran0.writeAction("slorii X16 X16 12 137")
    tran0.writeAction("slorii X16 X16 12 3151")
    tran0.writeAction("slorii X16 X16 12 2818")
    tran0.writeAction("slorii X16 X16 12 3031")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 38904")
    tran0.writeAction("slorii X16 X16 12 891")
    tran0.writeAction("slorii X16 X16 12 1036")
    tran0.writeAction("slorii X16 X16 12 1879")
    tran0.writeAction("slorii X16 X16 12 1882")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 64083")
    tran0.writeAction("slorii X16 X16 12 3208")
    tran0.writeAction("slorii X16 X16 12 3463")
    tran0.writeAction("slorii X16 X16 12 3250")
    tran0.writeAction("slorii X16 X16 12 1409")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 26768")
    tran0.writeAction("slorii X16 X16 12 3782")
    tran0.writeAction("slorii X16 X16 12 2698")
    tran0.writeAction("slorii X16 X16 12 1624")
    tran0.writeAction("slorii X16 X16 12 315")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 36")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 4")
    tran0.writeAction("sli X17 X17 32")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X20 0")
    tran0.writeAction("add X20 X7 X5")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("addi X20 X17 12")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("movir X16 132")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("flagCarry_with_action", state1, state2, 132)
    tran1.writeAction("movir X16 136")
    tran1.writeAction("movir X30 7")
    tran1.writeAction("movir X29 7")
    tran1.writeAction("movir X28 7")
    tran1.writeAction("lastact")
    tran3 = state1.writeTransition("flagCarry_with_action", state1, state2, 255)
    tran3.writeAction("movir X16 255")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("flagCarry_with_action", state2, state2, 136)
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