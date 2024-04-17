from EFA_v2 import *
def basic_noaction4_with_lastact_TX_maxSBP_11():
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
    tran0.writeAction("movir X16 32205")
    tran0.writeAction("slorii X16 X16 12 3777")
    tran0.writeAction("slorii X16 X16 12 899")
    tran0.writeAction("slorii X16 X16 12 2250")
    tran0.writeAction("slorii X16 X16 12 1529")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 19514")
    tran0.writeAction("slorii X16 X16 12 1247")
    tran0.writeAction("slorii X16 X16 12 1254")
    tran0.writeAction("slorii X16 X16 12 1789")
    tran0.writeAction("slorii X16 X16 12 2562")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 20042")
    tran0.writeAction("slorii X16 X16 12 30")
    tran0.writeAction("slorii X16 X16 12 880")
    tran0.writeAction("slorii X16 X16 12 362")
    tran0.writeAction("slorii X16 X16 12 2237")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 58247")
    tran0.writeAction("slorii X16 X16 12 3551")
    tran0.writeAction("slorii X16 X16 12 1772")
    tran0.writeAction("slorii X16 X16 12 1574")
    tran0.writeAction("slorii X16 X16 12 1410")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 49571")
    tran0.writeAction("slorii X16 X16 12 1747")
    tran0.writeAction("slorii X16 X16 12 3816")
    tran0.writeAction("slorii X16 X16 12 2552")
    tran0.writeAction("slorii X16 X16 12 1871")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 45754")
    tran0.writeAction("slorii X16 X16 12 3296")
    tran0.writeAction("slorii X16 X16 12 1608")
    tran0.writeAction("slorii X16 X16 12 1964")
    tran0.writeAction("slorii X16 X16 12 3156")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 50963")
    tran0.writeAction("slorii X16 X16 12 2722")
    tran0.writeAction("slorii X16 X16 12 414")
    tran0.writeAction("slorii X16 X16 12 4007")
    tran0.writeAction("slorii X16 X16 12 917")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 27664")
    tran0.writeAction("slorii X16 X16 12 3648")
    tran0.writeAction("slorii X16 X16 12 1108")
    tran0.writeAction("slorii X16 X16 12 307")
    tran0.writeAction("slorii X16 X16 12 825")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 32205")
    tran0.writeAction("slorii X16 X16 12 3777")
    tran0.writeAction("slorii X16 X16 12 899")
    tran0.writeAction("slorii X16 X16 12 2250")
    tran0.writeAction("slorii X16 X16 12 1529")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 1")
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
    tran0.writeAction("addi X20 X17 4")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("basic", state1, state2, 1)
    tran3 = state1.writeTransition("basic_with_action", state1, state2, 255)
    tran3.writeAction("addi X5 X16 8")
    tran3.writeAction("movir X30 8")
    tran3.writeAction("movir X29 8")
    tran3.writeAction("movir X28 8")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("basic", state2, state2, 1)
    tran4 = state2.writeTransition("basic_with_action", state2, state1, 255)
    tran4.writeAction("addi X5 X17 0")
    tran4.writeAction("movir X31 8")
    tran4.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa
