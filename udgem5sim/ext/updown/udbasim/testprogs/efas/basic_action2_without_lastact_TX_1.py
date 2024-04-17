from EFA_v2 import *
def basic_action2_without_lastact_TX_1():
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
    tran0.writeAction("movir X16 48281")
    tran0.writeAction("slorii X16 X16 12 237")
    tran0.writeAction("slorii X16 X16 12 1952")
    tran0.writeAction("slorii X16 X16 12 462")
    tran0.writeAction("slorii X16 X16 12 2853")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 48028")
    tran0.writeAction("slorii X16 X16 12 2569")
    tran0.writeAction("slorii X16 X16 12 2670")
    tran0.writeAction("slorii X16 X16 12 2275")
    tran0.writeAction("slorii X16 X16 12 2091")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 15977")
    tran0.writeAction("slorii X16 X16 12 1724")
    tran0.writeAction("slorii X16 X16 12 3817")
    tran0.writeAction("slorii X16 X16 12 3372")
    tran0.writeAction("slorii X16 X16 12 941")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 15053")
    tran0.writeAction("slorii X16 X16 12 3365")
    tran0.writeAction("slorii X16 X16 12 788")
    tran0.writeAction("slorii X16 X16 12 122")
    tran0.writeAction("slorii X16 X16 12 3818")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 45261")
    tran0.writeAction("slorii X16 X16 12 3821")
    tran0.writeAction("slorii X16 X16 12 3619")
    tran0.writeAction("slorii X16 X16 12 892")
    tran0.writeAction("slorii X16 X16 12 1109")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 22436")
    tran0.writeAction("slorii X16 X16 12 4070")
    tran0.writeAction("slorii X16 X16 12 2284")
    tran0.writeAction("slorii X16 X16 12 3301")
    tran0.writeAction("slorii X16 X16 12 3729")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 169")
    tran0.writeAction("slorii X16 X16 12 889")
    tran0.writeAction("slorii X16 X16 12 2653")
    tran0.writeAction("slorii X16 X16 12 3429")
    tran0.writeAction("slorii X16 X16 12 3677")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 44822")
    tran0.writeAction("slorii X16 X16 12 3932")
    tran0.writeAction("slorii X16 X16 12 2819")
    tran0.writeAction("slorii X16 X16 12 1911")
    tran0.writeAction("slorii X16 X16 12 1011")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 48281")
    tran0.writeAction("slorii X16 X16 12 237")
    tran0.writeAction("slorii X16 X16 12 1952")
    tran0.writeAction("slorii X16 X16 12 462")
    tran0.writeAction("slorii X16 X16 12 2853")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 3")
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
    tran1 = state1.writeTransition("basic_with_action", state1, state2, 5)
    tran1.writeAction("addi X5 X16 0")
    tran1.writeAction("movir X30 5")
    tran3 = state1.writeTransition("basic_with_action", state1, state2, 255)
    tran3.writeAction("addi X5 X16 0")
    tran3.writeAction("movir X30 6")
    tran2 = state2.writeTransition("basic_with_action", state2, state2, 2)
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