from EFA_v2 import *
def flag_action1_with_lastact_TX_5():
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
    tran0.writeAction("movir X16 34066")
    tran0.writeAction("slorii X16 X16 12 2136")
    tran0.writeAction("slorii X16 X16 12 51")
    tran0.writeAction("slorii X16 X16 12 1989")
    tran0.writeAction("slorii X16 X16 12 127")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 53359")
    tran0.writeAction("slorii X16 X16 12 4041")
    tran0.writeAction("slorii X16 X16 12 3537")
    tran0.writeAction("slorii X16 X16 12 3044")
    tran0.writeAction("slorii X16 X16 12 2934")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 60991")
    tran0.writeAction("slorii X16 X16 12 421")
    tran0.writeAction("slorii X16 X16 12 3374")
    tran0.writeAction("slorii X16 X16 12 3652")
    tran0.writeAction("slorii X16 X16 12 3018")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 64612")
    tran0.writeAction("slorii X16 X16 12 396")
    tran0.writeAction("slorii X16 X16 12 52")
    tran0.writeAction("slorii X16 X16 12 3111")
    tran0.writeAction("slorii X16 X16 12 748")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 48750")
    tran0.writeAction("slorii X16 X16 12 3736")
    tran0.writeAction("slorii X16 X16 12 2369")
    tran0.writeAction("slorii X16 X16 12 1233")
    tran0.writeAction("slorii X16 X16 12 3689")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 58424")
    tran0.writeAction("slorii X16 X16 12 3566")
    tran0.writeAction("slorii X16 X16 12 3116")
    tran0.writeAction("slorii X16 X16 12 739")
    tran0.writeAction("slorii X16 X16 12 656")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 2395")
    tran0.writeAction("slorii X16 X16 12 2711")
    tran0.writeAction("slorii X16 X16 12 1084")
    tran0.writeAction("slorii X16 X16 12 117")
    tran0.writeAction("slorii X16 X16 12 2168")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 53585")
    tran0.writeAction("slorii X16 X16 12 2316")
    tran0.writeAction("slorii X16 X16 12 3771")
    tran0.writeAction("slorii X16 X16 12 3657")
    tran0.writeAction("slorii X16 X16 12 526")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 34066")
    tran0.writeAction("slorii X16 X16 12 2136")
    tran0.writeAction("slorii X16 X16 12 51")
    tran0.writeAction("slorii X16 X16 12 1989")
    tran0.writeAction("slorii X16 X16 12 127")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 36")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 7")
    tran0.writeAction("sli X17 X17 32")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("add X7 X31 X31")
    tran0.writeAction("movir X20 0")
    tran0.writeAction("sli X31 X21 3")
    tran0.writeAction("add X21 X20 X5")
    tran0.writeAction("movlsb X31")
    tran0.writeAction("addi X20 X17 21")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("movir X16 81")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("flagCarry_with_action", state1, state2, 81)
    tran1.writeAction("movir X16 197")
    tran1.writeAction("lastact")
    tran3 = state1.writeTransition("flagCarry_with_action", state1, state2, 255)
    tran3.writeAction("movir X16 255")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("flagCarry_with_action", state2, state2, 197)
    tran2.writeAction("movir X31 7")
    tran2.writeAction("yieldt")
    tran4 = state2.writeTransition("flagCarry_with_action", state2, state1, 255)
    tran4.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa