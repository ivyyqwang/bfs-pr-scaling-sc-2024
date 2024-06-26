from EFA_v2 import *
def flag_noaction1_with_lastact_TX_4():
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
    tran0.writeAction("movir X16 58902")
    tran0.writeAction("slorii X16 X16 12 548")
    tran0.writeAction("slorii X16 X16 12 3346")
    tran0.writeAction("slorii X16 X16 12 3717")
    tran0.writeAction("slorii X16 X16 12 242")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 23412")
    tran0.writeAction("slorii X16 X16 12 2125")
    tran0.writeAction("slorii X16 X16 12 1639")
    tran0.writeAction("slorii X16 X16 12 3529")
    tran0.writeAction("slorii X16 X16 12 125")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 25016")
    tran0.writeAction("slorii X16 X16 12 2700")
    tran0.writeAction("slorii X16 X16 12 1607")
    tran0.writeAction("slorii X16 X16 12 2518")
    tran0.writeAction("slorii X16 X16 12 2384")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 59157")
    tran0.writeAction("slorii X16 X16 12 74")
    tran0.writeAction("slorii X16 X16 12 2241")
    tran0.writeAction("slorii X16 X16 12 3164")
    tran0.writeAction("slorii X16 X16 12 2697")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 11131")
    tran0.writeAction("slorii X16 X16 12 2507")
    tran0.writeAction("slorii X16 X16 12 2986")
    tran0.writeAction("slorii X16 X16 12 3380")
    tran0.writeAction("slorii X16 X16 12 3648")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 24566")
    tran0.writeAction("slorii X16 X16 12 3255")
    tran0.writeAction("slorii X16 X16 12 1295")
    tran0.writeAction("slorii X16 X16 12 3820")
    tran0.writeAction("slorii X16 X16 12 200")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 34347")
    tran0.writeAction("slorii X16 X16 12 2199")
    tran0.writeAction("slorii X16 X16 12 3462")
    tran0.writeAction("slorii X16 X16 12 2354")
    tran0.writeAction("slorii X16 X16 12 1702")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 8734")
    tran0.writeAction("slorii X16 X16 12 3049")
    tran0.writeAction("slorii X16 X16 12 2760")
    tran0.writeAction("slorii X16 X16 12 367")
    tran0.writeAction("slorii X16 X16 12 3793")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 58902")
    tran0.writeAction("slorii X16 X16 12 548")
    tran0.writeAction("slorii X16 X16 12 3346")
    tran0.writeAction("slorii X16 X16 12 3717")
    tran0.writeAction("slorii X16 X16 12 242")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 4")
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
    tran0.writeAction("movir X16 51")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("flagCarry", state1, state2, 51)
    tran3 = state1.writeTransition("flagCarry_with_action", state1, state2, 255)
    tran3.writeAction("movir X16 255")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("flagCarry_with_action", state2, state2, 51)
    tran2.writeAction("movir X31 7")
    tran2.writeAction("yieldt")
    tran4 = state2.writeTransition("flagCarry_with_action", state2, state1, 255)
    tran4.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa
