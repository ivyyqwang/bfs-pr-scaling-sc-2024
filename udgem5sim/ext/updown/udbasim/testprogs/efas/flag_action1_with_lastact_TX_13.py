from EFA_v2 import *
def flag_action1_with_lastact_TX_13():
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
    tran0.writeAction("movir X16 27201")
    tran0.writeAction("slorii X16 X16 12 2143")
    tran0.writeAction("slorii X16 X16 12 1722")
    tran0.writeAction("slorii X16 X16 12 1190")
    tran0.writeAction("slorii X16 X16 12 1969")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 16830")
    tran0.writeAction("slorii X16 X16 12 1605")
    tran0.writeAction("slorii X16 X16 12 3675")
    tran0.writeAction("slorii X16 X16 12 2813")
    tran0.writeAction("slorii X16 X16 12 3978")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 58574")
    tran0.writeAction("slorii X16 X16 12 3353")
    tran0.writeAction("slorii X16 X16 12 3434")
    tran0.writeAction("slorii X16 X16 12 4046")
    tran0.writeAction("slorii X16 X16 12 3062")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 7513")
    tran0.writeAction("slorii X16 X16 12 3786")
    tran0.writeAction("slorii X16 X16 12 3581")
    tran0.writeAction("slorii X16 X16 12 899")
    tran0.writeAction("slorii X16 X16 12 2799")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 16577")
    tran0.writeAction("slorii X16 X16 12 2302")
    tran0.writeAction("slorii X16 X16 12 2174")
    tran0.writeAction("slorii X16 X16 12 1809")
    tran0.writeAction("slorii X16 X16 12 1703")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 50646")
    tran0.writeAction("slorii X16 X16 12 1233")
    tran0.writeAction("slorii X16 X16 12 4020")
    tran0.writeAction("slorii X16 X16 12 1826")
    tran0.writeAction("slorii X16 X16 12 737")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 50144")
    tran0.writeAction("slorii X16 X16 12 3070")
    tran0.writeAction("slorii X16 X16 12 4001")
    tran0.writeAction("slorii X16 X16 12 1491")
    tran0.writeAction("slorii X16 X16 12 982")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 55228")
    tran0.writeAction("slorii X16 X16 12 36")
    tran0.writeAction("slorii X16 X16 12 1974")
    tran0.writeAction("slorii X16 X16 12 1975")
    tran0.writeAction("slorii X16 X16 12 1452")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 27201")
    tran0.writeAction("slorii X16 X16 12 2143")
    tran0.writeAction("slorii X16 X16 12 1722")
    tran0.writeAction("slorii X16 X16 12 1190")
    tran0.writeAction("slorii X16 X16 12 1969")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 5")
    tran0.writeAction("sli X17 X17 36")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 5")
    tran0.writeAction("sli X17 X17 32")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("add X7 X31 X31")
    tran0.writeAction("movir X20 0")
    tran0.writeAction("sli X31 X21 3")
    tran0.writeAction("add X21 X20 X5")
    tran0.writeAction("movlsb X31")
    tran0.writeAction("addi X20 X17 15")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("movir X16 92")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("flagCarry_with_action", state1, state2, 92)
    tran1.writeAction("movir X16 174")
    tran1.writeAction("lastact")
    tran3 = state1.writeTransition("flagCarry_with_action", state1, state2, 255)
    tran3.writeAction("movir X16 255")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("flagCarry_with_action", state2, state2, 174)
    tran2.writeAction("movir X31 7")
    tran2.writeAction("yieldt")
    tran4 = state2.writeTransition("flagCarry_with_action", state2, state1, 255)
    tran4.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa
