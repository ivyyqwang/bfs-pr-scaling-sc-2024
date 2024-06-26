from EFA_v2 import *
def refill_noaction_TX_1():
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
    tran0 = state.writeTransition("refill_with_action", state, state1, 1)
    tran0.writeAction("movir X17 0")
    tran0.writeAction("add X7 X17 X17")
    tran0.writeAction("movir X16 43967")
    tran0.writeAction("slorii X16 X16 12 2434")
    tran0.writeAction("slorii X16 X16 12 1112")
    tran0.writeAction("slorii X16 X16 12 657")
    tran0.writeAction("slorii X16 X16 12 1236")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 64539")
    tran0.writeAction("slorii X16 X16 12 2207")
    tran0.writeAction("slorii X16 X16 12 3196")
    tran0.writeAction("slorii X16 X16 12 3671")
    tran0.writeAction("slorii X16 X16 12 3630")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 33569")
    tran0.writeAction("slorii X16 X16 12 2029")
    tran0.writeAction("slorii X16 X16 12 3071")
    tran0.writeAction("slorii X16 X16 12 857")
    tran0.writeAction("slorii X16 X16 12 1782")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 31516")
    tran0.writeAction("slorii X16 X16 12 3273")
    tran0.writeAction("slorii X16 X16 12 4024")
    tran0.writeAction("slorii X16 X16 12 2867")
    tran0.writeAction("slorii X16 X16 12 2621")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 2516")
    tran0.writeAction("slorii X16 X16 12 1751")
    tran0.writeAction("slorii X16 X16 12 4078")
    tran0.writeAction("slorii X16 X16 12 3034")
    tran0.writeAction("slorii X16 X16 12 313")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 24241")
    tran0.writeAction("slorii X16 X16 12 3036")
    tran0.writeAction("slorii X16 X16 12 936")
    tran0.writeAction("slorii X16 X16 12 2344")
    tran0.writeAction("slorii X16 X16 12 3928")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 32424")
    tran0.writeAction("slorii X16 X16 12 2604")
    tran0.writeAction("slorii X16 X16 12 2378")
    tran0.writeAction("slorii X16 X16 12 656")
    tran0.writeAction("slorii X16 X16 12 28")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 201")
    tran0.writeAction("slorii X16 X16 12 969")
    tran0.writeAction("slorii X16 X16 12 23")
    tran0.writeAction("slorii X16 X16 12 1114")
    tran0.writeAction("slorii X16 X16 12 746")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 43967")
    tran0.writeAction("slorii X16 X16 12 2434")
    tran0.writeAction("slorii X16 X16 12 1112")
    tran0.writeAction("slorii X16 X16 12 657")
    tran0.writeAction("slorii X16 X16 12 1236")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 6")
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
    tran0.writeAction("addi X20 X17 18")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("refill", state1, state2, 20, 0)
    tran3 = state1.writeTransition("refill_with_action", state1, state2, 255, 0)
    tran3.writeAction("movir X30 2")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("refill_with_action", state2, state2, 19, 3)
    tran2.writeAction("movir X31 1")
    tran2.writeAction("addi X5 X18 0")
    tran2.writeAction("yieldt")
    tran4 = state2.writeTransition("refill_with_action", state2, state1, 255, 3)
    tran4.writeAction("movir X31 2")
    tran4.writeAction("addi X5 X18 0")
    tran4.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa
