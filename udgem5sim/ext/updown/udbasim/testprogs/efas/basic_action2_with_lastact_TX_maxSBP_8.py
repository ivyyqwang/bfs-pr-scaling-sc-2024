from EFA_v2 import *
def basic_action2_with_lastact_TX_maxSBP_8():
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
    tran0.writeAction("movir X16 0")
    tran0.writeAction("slorii X16 X16 12 3457")
    tran0.writeAction("slorii X16 X16 12 3072")
    tran0.writeAction("slorii X16 X16 12 0")
    tran0.writeAction("slorii X16 X16 12 134")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 17696")
    tran0.writeAction("slorii X16 X16 12 3026")
    tran0.writeAction("slorii X16 X16 12 1183")
    tran0.writeAction("slorii X16 X16 12 1646")
    tran0.writeAction("slorii X16 X16 12 256")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 60414")
    tran0.writeAction("slorii X16 X16 12 280")
    tran0.writeAction("slorii X16 X16 12 2128")
    tran0.writeAction("slorii X16 X16 12 858")
    tran0.writeAction("slorii X16 X16 12 433")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 61840")
    tran0.writeAction("slorii X16 X16 12 1521")
    tran0.writeAction("slorii X16 X16 12 3452")
    tran0.writeAction("slorii X16 X16 12 554")
    tran0.writeAction("slorii X16 X16 12 1112")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 13340")
    tran0.writeAction("slorii X16 X16 12 2556")
    tran0.writeAction("slorii X16 X16 12 2175")
    tran0.writeAction("slorii X16 X16 12 568")
    tran0.writeAction("slorii X16 X16 12 1801")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 21167")
    tran0.writeAction("slorii X16 X16 12 1443")
    tran0.writeAction("slorii X16 X16 12 2267")
    tran0.writeAction("slorii X16 X16 12 313")
    tran0.writeAction("slorii X16 X16 12 2735")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 39958")
    tran0.writeAction("slorii X16 X16 12 2151")
    tran0.writeAction("slorii X16 X16 12 3142")
    tran0.writeAction("slorii X16 X16 12 3933")
    tran0.writeAction("slorii X16 X16 12 2164")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 2575")
    tran0.writeAction("slorii X16 X16 12 944")
    tran0.writeAction("slorii X16 X16 12 2563")
    tran0.writeAction("slorii X16 X16 12 686")
    tran0.writeAction("slorii X16 X16 12 2730")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 0")
    tran0.writeAction("slorii X16 X16 12 3457")
    tran0.writeAction("slorii X16 X16 12 3072")
    tran0.writeAction("slorii X16 X16 12 0")
    tran0.writeAction("slorii X16 X16 12 134")
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
    tran0.writeAction("addi X20 X17 5")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("basic_with_action", state1, state2, 134)
    tran1.writeAction("movir X30 7")
    tran1.writeAction("lastact")
    tran3 = state1.writeTransition("basic_with_action", state1, state2, 255)
    tran3.writeAction("addi X5 X16 0")
    tran3.writeAction("movir X30 8")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("basic_with_action", state2, state2, 216)
    tran2.writeAction("movir X30 7")
    tran4 = state2.writeTransition("basic_with_action", state2, state1, 255)
    tran4.writeAction("addi X5 X17 0")
    tran4.writeAction("movir X30 8")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa
