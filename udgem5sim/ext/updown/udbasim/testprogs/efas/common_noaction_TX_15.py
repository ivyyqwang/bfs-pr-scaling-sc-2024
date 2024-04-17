from EFA_v2 import *
def common_noaction_TX_15():
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
    tran0.writeAction("movir X16 63472")
    tran0.writeAction("slorii X16 X16 12 1551")
    tran0.writeAction("slorii X16 X16 12 2178")
    tran0.writeAction("slorii X16 X16 12 1202")
    tran0.writeAction("slorii X16 X16 12 3838")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 6300")
    tran0.writeAction("slorii X16 X16 12 3979")
    tran0.writeAction("slorii X16 X16 12 860")
    tran0.writeAction("slorii X16 X16 12 1221")
    tran0.writeAction("slorii X16 X16 12 2154")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 28267")
    tran0.writeAction("slorii X16 X16 12 3396")
    tran0.writeAction("slorii X16 X16 12 809")
    tran0.writeAction("slorii X16 X16 12 3147")
    tran0.writeAction("slorii X16 X16 12 3678")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 12572")
    tran0.writeAction("slorii X16 X16 12 915")
    tran0.writeAction("slorii X16 X16 12 2942")
    tran0.writeAction("slorii X16 X16 12 2154")
    tran0.writeAction("slorii X16 X16 12 762")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 55")
    tran0.writeAction("slorii X16 X16 12 3970")
    tran0.writeAction("slorii X16 X16 12 961")
    tran0.writeAction("slorii X16 X16 12 3941")
    tran0.writeAction("slorii X16 X16 12 778")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 103")
    tran0.writeAction("slorii X16 X16 12 339")
    tran0.writeAction("slorii X16 X16 12 3272")
    tran0.writeAction("slorii X16 X16 12 1902")
    tran0.writeAction("slorii X16 X16 12 3586")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 3970")
    tran0.writeAction("slorii X16 X16 12 378")
    tran0.writeAction("slorii X16 X16 12 2966")
    tran0.writeAction("slorii X16 X16 12 29")
    tran0.writeAction("slorii X16 X16 12 2370")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 56067")
    tran0.writeAction("slorii X16 X16 12 2872")
    tran0.writeAction("slorii X16 X16 12 3194")
    tran0.writeAction("slorii X16 X16 12 803")
    tran0.writeAction("slorii X16 X16 12 2117")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 63472")
    tran0.writeAction("slorii X16 X16 12 1551")
    tran0.writeAction("slorii X16 X16 12 2178")
    tran0.writeAction("slorii X16 X16 12 1202")
    tran0.writeAction("slorii X16 X16 12 3838")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 36")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 7")
    tran0.writeAction("sli X17 X17 32")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X20 0")
    tran0.writeAction("add X20 X7 X5")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("addi X20 X17 21")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("commonCarry", state1, state2, 0)
    tran2 = state2.writeTransition("commonCarry_with_action", state2, state2, 0)
    tran2.writeAction("addi X5 X17 0")
    tran2.writeAction("movir X31 2")
    tran2.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa
