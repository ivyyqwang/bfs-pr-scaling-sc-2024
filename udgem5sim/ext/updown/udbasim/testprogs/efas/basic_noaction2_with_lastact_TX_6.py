from EFA_v2 import *
def basic_noaction2_with_lastact_TX_6():
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
    tran0.writeAction("movir X16 50530")
    tran0.writeAction("slorii X16 X16 12 3875")
    tran0.writeAction("slorii X16 X16 12 2528")
    tran0.writeAction("slorii X16 X16 12 2356")
    tran0.writeAction("slorii X16 X16 12 1208")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 20456")
    tran0.writeAction("slorii X16 X16 12 1344")
    tran0.writeAction("slorii X16 X16 12 155")
    tran0.writeAction("slorii X16 X16 12 3857")
    tran0.writeAction("slorii X16 X16 12 126")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 36125")
    tran0.writeAction("slorii X16 X16 12 2102")
    tran0.writeAction("slorii X16 X16 12 3385")
    tran0.writeAction("slorii X16 X16 12 296")
    tran0.writeAction("slorii X16 X16 12 2420")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 33695")
    tran0.writeAction("slorii X16 X16 12 2973")
    tran0.writeAction("slorii X16 X16 12 3980")
    tran0.writeAction("slorii X16 X16 12 1198")
    tran0.writeAction("slorii X16 X16 12 4003")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 20242")
    tran0.writeAction("slorii X16 X16 12 1166")
    tran0.writeAction("slorii X16 X16 12 2403")
    tran0.writeAction("slorii X16 X16 12 2736")
    tran0.writeAction("slorii X16 X16 12 2433")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 3662")
    tran0.writeAction("slorii X16 X16 12 2014")
    tran0.writeAction("slorii X16 X16 12 280")
    tran0.writeAction("slorii X16 X16 12 3250")
    tran0.writeAction("slorii X16 X16 12 2664")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 31480")
    tran0.writeAction("slorii X16 X16 12 1865")
    tran0.writeAction("slorii X16 X16 12 787")
    tran0.writeAction("slorii X16 X16 12 1011")
    tran0.writeAction("slorii X16 X16 12 1770")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 29770")
    tran0.writeAction("slorii X16 X16 12 3930")
    tran0.writeAction("slorii X16 X16 12 1507")
    tran0.writeAction("slorii X16 X16 12 3160")
    tran0.writeAction("slorii X16 X16 12 263")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 50530")
    tran0.writeAction("slorii X16 X16 12 3875")
    tran0.writeAction("slorii X16 X16 12 2528")
    tran0.writeAction("slorii X16 X16 12 2356")
    tran0.writeAction("slorii X16 X16 12 1208")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 2")
    tran0.writeAction("sli X17 X17 36")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 3")
    tran0.writeAction("sli X17 X17 32")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("add X7 X31 X31")
    tran0.writeAction("movir X20 0")
    tran0.writeAction("sli X31 X21 3")
    tran0.writeAction("add X21 X20 X5")
    tran0.writeAction("movlsb X31")
    tran0.writeAction("addi X20 X17 9")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("basic", state1, state2, 0)
    tran3 = state1.writeTransition("basic_with_action", state1, state2, 255)
    tran3.writeAction("addi X5 X16 0")
    tran3.writeAction("movir X30 8")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("basic_with_action", state2, state2, 3)
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
