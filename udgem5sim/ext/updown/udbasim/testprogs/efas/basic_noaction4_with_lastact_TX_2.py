from EFA_v2 import *
def basic_noaction4_with_lastact_TX_2():
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
    tran0.writeAction("movir X16 37491")
    tran0.writeAction("slorii X16 X16 12 3521")
    tran0.writeAction("slorii X16 X16 12 3788")
    tran0.writeAction("slorii X16 X16 12 315")
    tran0.writeAction("slorii X16 X16 12 3071")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 60336")
    tran0.writeAction("slorii X16 X16 12 477")
    tran0.writeAction("slorii X16 X16 12 540")
    tran0.writeAction("slorii X16 X16 12 1162")
    tran0.writeAction("slorii X16 X16 12 2571")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 24948")
    tran0.writeAction("slorii X16 X16 12 1232")
    tran0.writeAction("slorii X16 X16 12 2823")
    tran0.writeAction("slorii X16 X16 12 2309")
    tran0.writeAction("slorii X16 X16 12 2551")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 4697")
    tran0.writeAction("slorii X16 X16 12 103")
    tran0.writeAction("slorii X16 X16 12 2826")
    tran0.writeAction("slorii X16 X16 12 18")
    tran0.writeAction("slorii X16 X16 12 4072")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 38594")
    tran0.writeAction("slorii X16 X16 12 2801")
    tran0.writeAction("slorii X16 X16 12 1086")
    tran0.writeAction("slorii X16 X16 12 2705")
    tran0.writeAction("slorii X16 X16 12 2119")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 61953")
    tran0.writeAction("slorii X16 X16 12 3221")
    tran0.writeAction("slorii X16 X16 12 3639")
    tran0.writeAction("slorii X16 X16 12 2526")
    tran0.writeAction("slorii X16 X16 12 3475")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 37847")
    tran0.writeAction("slorii X16 X16 12 2934")
    tran0.writeAction("slorii X16 X16 12 3487")
    tran0.writeAction("slorii X16 X16 12 3141")
    tran0.writeAction("slorii X16 X16 12 2218")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 7663")
    tran0.writeAction("slorii X16 X16 12 1411")
    tran0.writeAction("slorii X16 X16 12 755")
    tran0.writeAction("slorii X16 X16 12 6")
    tran0.writeAction("slorii X16 X16 12 3276")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 37491")
    tran0.writeAction("slorii X16 X16 12 3521")
    tran0.writeAction("slorii X16 X16 12 3788")
    tran0.writeAction("slorii X16 X16 12 315")
    tran0.writeAction("slorii X16 X16 12 3071")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 2")
    tran0.writeAction("sli X17 X17 36")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 4")
    tran0.writeAction("sli X17 X17 32")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("add X7 X31 X31")
    tran0.writeAction("movir X20 0")
    tran0.writeAction("sli X31 X21 3")
    tran0.writeAction("add X21 X20 X5")
    tran0.writeAction("movlsb X31")
    tran0.writeAction("addi X20 X17 12")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("basic", state1, state2, 3)
    tran3 = state1.writeTransition("basic_with_action", state1, state2, 255)
    tran3.writeAction("addi X5 X16 8")
    tran3.writeAction("movir X30 8")
    tran3.writeAction("movir X29 8")
    tran3.writeAction("movir X28 8")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("basic_with_action", state2, state2, 3)
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
