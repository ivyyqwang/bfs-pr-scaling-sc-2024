from EFA_v2 import *
def basic_action2_with_lastact_TX_maxSBP_3():
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
    tran0.writeAction("movir X16 27641")
    tran0.writeAction("slorii X16 X16 12 2422")
    tran0.writeAction("slorii X16 X16 12 1575")
    tran0.writeAction("slorii X16 X16 12 710")
    tran0.writeAction("slorii X16 X16 12 930")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 63901")
    tran0.writeAction("slorii X16 X16 12 1420")
    tran0.writeAction("slorii X16 X16 12 858")
    tran0.writeAction("slorii X16 X16 12 1747")
    tran0.writeAction("slorii X16 X16 12 918")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 60979")
    tran0.writeAction("slorii X16 X16 12 1121")
    tran0.writeAction("slorii X16 X16 12 3872")
    tran0.writeAction("slorii X16 X16 12 2013")
    tran0.writeAction("slorii X16 X16 12 1033")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 30647")
    tran0.writeAction("slorii X16 X16 12 1744")
    tran0.writeAction("slorii X16 X16 12 1928")
    tran0.writeAction("slorii X16 X16 12 1670")
    tran0.writeAction("slorii X16 X16 12 3832")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 50689")
    tran0.writeAction("slorii X16 X16 12 565")
    tran0.writeAction("slorii X16 X16 12 3157")
    tran0.writeAction("slorii X16 X16 12 2306")
    tran0.writeAction("slorii X16 X16 12 3124")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 3130")
    tran0.writeAction("slorii X16 X16 12 3709")
    tran0.writeAction("slorii X16 X16 12 3338")
    tran0.writeAction("slorii X16 X16 12 646")
    tran0.writeAction("slorii X16 X16 12 3577")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 18902")
    tran0.writeAction("slorii X16 X16 12 3882")
    tran0.writeAction("slorii X16 X16 12 3756")
    tran0.writeAction("slorii X16 X16 12 248")
    tran0.writeAction("slorii X16 X16 12 1611")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 55338")
    tran0.writeAction("slorii X16 X16 12 1031")
    tran0.writeAction("slorii X16 X16 12 280")
    tran0.writeAction("slorii X16 X16 12 761")
    tran0.writeAction("slorii X16 X16 12 4024")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 27641")
    tran0.writeAction("slorii X16 X16 12 2422")
    tran0.writeAction("slorii X16 X16 12 1575")
    tran0.writeAction("slorii X16 X16 12 710")
    tran0.writeAction("slorii X16 X16 12 930")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 8")
    tran0.writeAction("sli X17 X17 36")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 8")
    tran0.writeAction("sli X17 X17 32")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("add X7 X31 X31")
    tran0.writeAction("movir X20 0")
    tran0.writeAction("sli X31 X21 3")
    tran0.writeAction("add X21 X20 X5")
    tran0.writeAction("movlsb X31")
    tran0.writeAction("addi X20 X17 8")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("basic_with_action", state1, state2, 162)
    tran1.writeAction("movir X30 7")
    tran1.writeAction("lastact")
    tran3 = state1.writeTransition("basic_with_action", state1, state2, 255)
    tran3.writeAction("addi X5 X16 0")
    tran3.writeAction("movir X30 8")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("basic_with_action", state2, state2, 99)
    tran2.writeAction("movir X30 7")
    tran4 = state2.writeTransition("basic_with_action", state2, state1, 255)
    tran4.writeAction("addi X5 X17 0")
    tran4.writeAction("movir X30 8")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa
