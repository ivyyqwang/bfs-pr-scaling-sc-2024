from EFA_v2 import *
def basic_noaction2_with_lastact_TX_14():
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
    tran0.writeAction("movir X16 42238")
    tran0.writeAction("slorii X16 X16 12 3758")
    tran0.writeAction("slorii X16 X16 12 3650")
    tran0.writeAction("slorii X16 X16 12 222")
    tran0.writeAction("slorii X16 X16 12 319")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 39759")
    tran0.writeAction("slorii X16 X16 12 1116")
    tran0.writeAction("slorii X16 X16 12 1457")
    tran0.writeAction("slorii X16 X16 12 2906")
    tran0.writeAction("slorii X16 X16 12 2329")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 45780")
    tran0.writeAction("slorii X16 X16 12 595")
    tran0.writeAction("slorii X16 X16 12 4012")
    tran0.writeAction("slorii X16 X16 12 2740")
    tran0.writeAction("slorii X16 X16 12 3256")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 28839")
    tran0.writeAction("slorii X16 X16 12 283")
    tran0.writeAction("slorii X16 X16 12 3693")
    tran0.writeAction("slorii X16 X16 12 1399")
    tran0.writeAction("slorii X16 X16 12 3196")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 44876")
    tran0.writeAction("slorii X16 X16 12 2050")
    tran0.writeAction("slorii X16 X16 12 696")
    tran0.writeAction("slorii X16 X16 12 2021")
    tran0.writeAction("slorii X16 X16 12 2840")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 13702")
    tran0.writeAction("slorii X16 X16 12 3201")
    tran0.writeAction("slorii X16 X16 12 1727")
    tran0.writeAction("slorii X16 X16 12 91")
    tran0.writeAction("slorii X16 X16 12 1022")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 48461")
    tran0.writeAction("slorii X16 X16 12 2687")
    tran0.writeAction("slorii X16 X16 12 2979")
    tran0.writeAction("slorii X16 X16 12 4053")
    tran0.writeAction("slorii X16 X16 12 1310")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 42044")
    tran0.writeAction("slorii X16 X16 12 2370")
    tran0.writeAction("slorii X16 X16 12 3916")
    tran0.writeAction("slorii X16 X16 12 2204")
    tran0.writeAction("slorii X16 X16 12 2466")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 42238")
    tran0.writeAction("slorii X16 X16 12 3758")
    tran0.writeAction("slorii X16 X16 12 3650")
    tran0.writeAction("slorii X16 X16 12 222")
    tran0.writeAction("slorii X16 X16 12 319")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 6")
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
    tran0.writeAction("addi X20 X17 24")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("basic", state1, state2, 63)
    tran3 = state1.writeTransition("basic_with_action", state1, state2, 255)
    tran3.writeAction("addi X5 X16 0")
    tran3.writeAction("movir X30 8")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("basic_with_action", state2, state2, 33)
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