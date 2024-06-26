from EFA_v2 import *
def flag_action1_with_lastact_TX_4():
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
    tran0.writeAction("movir X16 13445")
    tran0.writeAction("slorii X16 X16 12 3544")
    tran0.writeAction("slorii X16 X16 12 1840")
    tran0.writeAction("slorii X16 X16 12 3101")
    tran0.writeAction("slorii X16 X16 12 320")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 33275")
    tran0.writeAction("slorii X16 X16 12 2551")
    tran0.writeAction("slorii X16 X16 12 249")
    tran0.writeAction("slorii X16 X16 12 3695")
    tran0.writeAction("slorii X16 X16 12 1968")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 23988")
    tran0.writeAction("slorii X16 X16 12 44")
    tran0.writeAction("slorii X16 X16 12 3708")
    tran0.writeAction("slorii X16 X16 12 3513")
    tran0.writeAction("slorii X16 X16 12 4080")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 32800")
    tran0.writeAction("slorii X16 X16 12 762")
    tran0.writeAction("slorii X16 X16 12 1304")
    tran0.writeAction("slorii X16 X16 12 168")
    tran0.writeAction("slorii X16 X16 12 2543")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 58061")
    tran0.writeAction("slorii X16 X16 12 2578")
    tran0.writeAction("slorii X16 X16 12 2520")
    tran0.writeAction("slorii X16 X16 12 3151")
    tran0.writeAction("slorii X16 X16 12 2616")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 11024")
    tran0.writeAction("slorii X16 X16 12 3471")
    tran0.writeAction("slorii X16 X16 12 3542")
    tran0.writeAction("slorii X16 X16 12 1498")
    tran0.writeAction("slorii X16 X16 12 3080")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 43001")
    tran0.writeAction("slorii X16 X16 12 629")
    tran0.writeAction("slorii X16 X16 12 3034")
    tran0.writeAction("slorii X16 X16 12 594")
    tran0.writeAction("slorii X16 X16 12 1131")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 24751")
    tran0.writeAction("slorii X16 X16 12 2330")
    tran0.writeAction("slorii X16 X16 12 2124")
    tran0.writeAction("slorii X16 X16 12 2131")
    tran0.writeAction("slorii X16 X16 12 3734")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 13445")
    tran0.writeAction("slorii X16 X16 12 3544")
    tran0.writeAction("slorii X16 X16 12 1840")
    tran0.writeAction("slorii X16 X16 12 3101")
    tran0.writeAction("slorii X16 X16 12 320")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 4")
    tran0.writeAction("sli X17 X17 36")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 5")
    tran0.writeAction("sli X17 X17 32")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X20 0")
    tran0.writeAction("add X20 X7 X5")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("addi X20 X17 15")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("movir X16 139")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("flagCarry_with_action", state1, state2, 139)
    tran1.writeAction("movir X16 3")
    tran1.writeAction("lastact")
    tran3 = state1.writeTransition("flagCarry_with_action", state1, state2, 255)
    tran3.writeAction("movir X16 255")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("flagCarry_with_action", state2, state2, 3)
    tran2.writeAction("movir X31 7")
    tran2.writeAction("yieldt")
    tran4 = state2.writeTransition("flagCarry_with_action", state2, state1, 255)
    tran4.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa
