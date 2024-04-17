from EFA_v2 import *
def basic_action8_with_lastact_TX_11():
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
    tran0.writeAction("movir X16 10463")
    tran0.writeAction("slorii X16 X16 12 584")
    tran0.writeAction("slorii X16 X16 12 2102")
    tran0.writeAction("slorii X16 X16 12 2750")
    tran0.writeAction("slorii X16 X16 12 2085")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 21858")
    tran0.writeAction("slorii X16 X16 12 3442")
    tran0.writeAction("slorii X16 X16 12 4078")
    tran0.writeAction("slorii X16 X16 12 1576")
    tran0.writeAction("slorii X16 X16 12 3290")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 6072")
    tran0.writeAction("slorii X16 X16 12 3225")
    tran0.writeAction("slorii X16 X16 12 4068")
    tran0.writeAction("slorii X16 X16 12 1338")
    tran0.writeAction("slorii X16 X16 12 2390")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 28615")
    tran0.writeAction("slorii X16 X16 12 4026")
    tran0.writeAction("slorii X16 X16 12 2476")
    tran0.writeAction("slorii X16 X16 12 2542")
    tran0.writeAction("slorii X16 X16 12 1269")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 11317")
    tran0.writeAction("slorii X16 X16 12 1971")
    tran0.writeAction("slorii X16 X16 12 4087")
    tran0.writeAction("slorii X16 X16 12 1206")
    tran0.writeAction("slorii X16 X16 12 48")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 12851")
    tran0.writeAction("slorii X16 X16 12 1038")
    tran0.writeAction("slorii X16 X16 12 1400")
    tran0.writeAction("slorii X16 X16 12 543")
    tran0.writeAction("slorii X16 X16 12 2480")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 41640")
    tran0.writeAction("slorii X16 X16 12 1530")
    tran0.writeAction("slorii X16 X16 12 1300")
    tran0.writeAction("slorii X16 X16 12 2882")
    tran0.writeAction("slorii X16 X16 12 1740")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 13527")
    tran0.writeAction("slorii X16 X16 12 3039")
    tran0.writeAction("slorii X16 X16 12 459")
    tran0.writeAction("slorii X16 X16 12 195")
    tran0.writeAction("slorii X16 X16 12 2645")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 10463")
    tran0.writeAction("slorii X16 X16 12 584")
    tran0.writeAction("slorii X16 X16 12 2102")
    tran0.writeAction("slorii X16 X16 12 2750")
    tran0.writeAction("slorii X16 X16 12 2085")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 1")
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
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("basic_with_action", state1, state2, 37)
    tran1.writeAction("addi X5 X16 0")
    tran1.writeAction("movir X30 7")
    tran1.writeAction("movir X29 7")
    tran1.writeAction("movir X28 7")
    tran1.writeAction("movir X27 7")
    tran1.writeAction("movir X26 7")
    tran1.writeAction("movir X25 7")
    tran1.writeAction("movir X24 7")
    tran1.writeAction("lastact")
    tran3 = state1.writeTransition("basic_with_action", state1, state2, 255)
    tran3.writeAction("movir X30 8")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("basic_with_action", state2, state2, 36)
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