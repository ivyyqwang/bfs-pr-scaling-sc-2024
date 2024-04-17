from EFA_v2 import *
def common_noaction_TX_10():
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
    tran0 = state.writeTransition("commonCarry_with_action", state, state1, 1)
    tran0.writeAction("movir X17 0")
    tran0.writeAction("add X7 X17 X17")
    tran0.writeAction("movir X16 36361")
    tran0.writeAction("slorii X16 X16 12 2690")
    tran0.writeAction("slorii X16 X16 12 3523")
    tran0.writeAction("slorii X16 X16 12 3166")
    tran0.writeAction("slorii X16 X16 12 1279")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 4446")
    tran0.writeAction("slorii X16 X16 12 1122")
    tran0.writeAction("slorii X16 X16 12 904")
    tran0.writeAction("slorii X16 X16 12 3301")
    tran0.writeAction("slorii X16 X16 12 3015")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 61289")
    tran0.writeAction("slorii X16 X16 12 4039")
    tran0.writeAction("slorii X16 X16 12 548")
    tran0.writeAction("slorii X16 X16 12 955")
    tran0.writeAction("slorii X16 X16 12 1286")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 20767")
    tran0.writeAction("slorii X16 X16 12 2126")
    tran0.writeAction("slorii X16 X16 12 2391")
    tran0.writeAction("slorii X16 X16 12 3342")
    tran0.writeAction("slorii X16 X16 12 1734")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 12169")
    tran0.writeAction("slorii X16 X16 12 1711")
    tran0.writeAction("slorii X16 X16 12 3672")
    tran0.writeAction("slorii X16 X16 12 557")
    tran0.writeAction("slorii X16 X16 12 3766")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 57929")
    tran0.writeAction("slorii X16 X16 12 1018")
    tran0.writeAction("slorii X16 X16 12 2081")
    tran0.writeAction("slorii X16 X16 12 114")
    tran0.writeAction("slorii X16 X16 12 2158")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 2043")
    tran0.writeAction("slorii X16 X16 12 3210")
    tran0.writeAction("slorii X16 X16 12 3561")
    tran0.writeAction("slorii X16 X16 12 3821")
    tran0.writeAction("slorii X16 X16 12 397")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 2541")
    tran0.writeAction("slorii X16 X16 12 1907")
    tran0.writeAction("slorii X16 X16 12 2963")
    tran0.writeAction("slorii X16 X16 12 1061")
    tran0.writeAction("slorii X16 X16 12 2977")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 36361")
    tran0.writeAction("slorii X16 X16 12 2690")
    tran0.writeAction("slorii X16 X16 12 3523")
    tran0.writeAction("slorii X16 X16 12 3166")
    tran0.writeAction("slorii X16 X16 12 1279")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 8")
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
    tran1 = state1.writeTransition("commonCarry", state1, state2, 0)
    tran2 = state2.writeTransition("commonCarry_with_action", state2, state2, 0)
    tran2.writeAction("addi X5 X17 0")
    tran2.writeAction("movir X31 2")
    tran2.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa