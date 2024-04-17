from EFA_v2 import *
def flag_action4_with_lastact_TX_5():
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
    tran0.writeAction("movir X16 2985")
    tran0.writeAction("slorii X16 X16 12 3344")
    tran0.writeAction("slorii X16 X16 12 3130")
    tran0.writeAction("slorii X16 X16 12 2976")
    tran0.writeAction("slorii X16 X16 12 3002")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 8660")
    tran0.writeAction("slorii X16 X16 12 1378")
    tran0.writeAction("slorii X16 X16 12 176")
    tran0.writeAction("slorii X16 X16 12 250")
    tran0.writeAction("slorii X16 X16 12 1044")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 2710")
    tran0.writeAction("slorii X16 X16 12 282")
    tran0.writeAction("slorii X16 X16 12 1940")
    tran0.writeAction("slorii X16 X16 12 3865")
    tran0.writeAction("slorii X16 X16 12 1063")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 8166")
    tran0.writeAction("slorii X16 X16 12 196")
    tran0.writeAction("slorii X16 X16 12 2595")
    tran0.writeAction("slorii X16 X16 12 3783")
    tran0.writeAction("slorii X16 X16 12 2279")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 19258")
    tran0.writeAction("slorii X16 X16 12 1831")
    tran0.writeAction("slorii X16 X16 12 2683")
    tran0.writeAction("slorii X16 X16 12 2629")
    tran0.writeAction("slorii X16 X16 12 19")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 60408")
    tran0.writeAction("slorii X16 X16 12 3960")
    tran0.writeAction("slorii X16 X16 12 2929")
    tran0.writeAction("slorii X16 X16 12 297")
    tran0.writeAction("slorii X16 X16 12 1239")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 9734")
    tran0.writeAction("slorii X16 X16 12 2785")
    tran0.writeAction("slorii X16 X16 12 3656")
    tran0.writeAction("slorii X16 X16 12 114")
    tran0.writeAction("slorii X16 X16 12 3502")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 5837")
    tran0.writeAction("slorii X16 X16 12 136")
    tran0.writeAction("slorii X16 X16 12 3171")
    tran0.writeAction("slorii X16 X16 12 410")
    tran0.writeAction("slorii X16 X16 12 478")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 2985")
    tran0.writeAction("slorii X16 X16 12 3344")
    tran0.writeAction("slorii X16 X16 12 3130")
    tran0.writeAction("slorii X16 X16 12 2976")
    tran0.writeAction("slorii X16 X16 12 3002")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 3")
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
    tran0.writeAction("movir X16 54")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("flagCarry_with_action", state1, state2, 54)
    tran1.writeAction("movir X16 190")
    tran1.writeAction("movir X30 7")
    tran1.writeAction("movir X29 7")
    tran1.writeAction("movir X28 7")
    tran1.writeAction("lastact")
    tran3 = state1.writeTransition("flagCarry_with_action", state1, state2, 255)
    tran3.writeAction("movir X16 255")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("flagCarry_with_action", state2, state2, 190)
    tran2.writeAction("addi X5 X17 0")
    tran2.writeAction("movir X31 7")
    tran2.writeAction("movir X31 8")
    tran2.writeAction("movir X31 9")
    tran2.writeAction("yieldt")
    tran4 = state2.writeTransition("flagCarry_with_action", state2, state1, 255)
    tran4.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa