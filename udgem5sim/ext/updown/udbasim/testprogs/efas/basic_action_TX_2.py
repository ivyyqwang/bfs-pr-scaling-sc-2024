from EFA_v2 import *
def basic_action_TX_2():
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
    tran0.writeAction("movir X16 44450")
    tran0.writeAction("slorii X16 X16 12 1770")
    tran0.writeAction("slorii X16 X16 12 3844")
    tran0.writeAction("slorii X16 X16 12 3660")
    tran0.writeAction("slorii X16 X16 12 3981")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 17495")
    tran0.writeAction("slorii X16 X16 12 1921")
    tran0.writeAction("slorii X16 X16 12 2539")
    tran0.writeAction("slorii X16 X16 12 493")
    tran0.writeAction("slorii X16 X16 12 1397")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 29923")
    tran0.writeAction("slorii X16 X16 12 518")
    tran0.writeAction("slorii X16 X16 12 600")
    tran0.writeAction("slorii X16 X16 12 731")
    tran0.writeAction("slorii X16 X16 12 3306")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 14620")
    tran0.writeAction("slorii X16 X16 12 2762")
    tran0.writeAction("slorii X16 X16 12 3915")
    tran0.writeAction("slorii X16 X16 12 3268")
    tran0.writeAction("slorii X16 X16 12 2269")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 19842")
    tran0.writeAction("slorii X16 X16 12 2168")
    tran0.writeAction("slorii X16 X16 12 2991")
    tran0.writeAction("slorii X16 X16 12 599")
    tran0.writeAction("slorii X16 X16 12 2917")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 28186")
    tran0.writeAction("slorii X16 X16 12 1604")
    tran0.writeAction("slorii X16 X16 12 3635")
    tran0.writeAction("slorii X16 X16 12 2790")
    tran0.writeAction("slorii X16 X16 12 2339")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 16665")
    tran0.writeAction("slorii X16 X16 12 1167")
    tran0.writeAction("slorii X16 X16 12 1224")
    tran0.writeAction("slorii X16 X16 12 3842")
    tran0.writeAction("slorii X16 X16 12 1520")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 61010")
    tran0.writeAction("slorii X16 X16 12 3692")
    tran0.writeAction("slorii X16 X16 12 189")
    tran0.writeAction("slorii X16 X16 12 3233")
    tran0.writeAction("slorii X16 X16 12 405")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 44450")
    tran0.writeAction("slorii X16 X16 12 1770")
    tran0.writeAction("slorii X16 X16 12 3844")
    tran0.writeAction("slorii X16 X16 12 3660")
    tran0.writeAction("slorii X16 X16 12 3981")
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
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("basic_with_action", state1, state2, 1)
    tran1.writeAction("addi X5 X16 0")
    tran1.writeAction("movir X30 5")
    tran1.writeAction("movir X29 5")
    tran1.writeAction("lastact")
    tran3 = state1.writeTransition("basic_with_action", state1, state2, 255)
    tran3.writeAction("addi X5 X16 0")
    tran3.writeAction("movir X30 6")
    tran3.writeAction("movir X29 6")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("basic_with_action", state2, state2, 1)
    tran2.writeAction("addi X5 X17 0")
    tran2.writeAction("movir X31 5")
    tran2.writeAction("yieldt")
    tran4 = state2.writeTransition("basic_with_action", state2, state1, 255)
    tran4.writeAction("addi X5 X17 0")
    tran4.writeAction("movir X31 6")
    tran4.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa
