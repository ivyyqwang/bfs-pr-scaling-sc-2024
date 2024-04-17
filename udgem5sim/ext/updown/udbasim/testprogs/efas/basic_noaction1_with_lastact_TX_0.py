from EFA_v2 import *
def basic_noaction1_with_lastact_TX_0():
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
    tran0.writeAction("movir X16 0")
    tran0.writeAction("slorii X16 X16 12 13")
    tran0.writeAction("slorii X16 X16 12 2304")
    tran0.writeAction("slorii X16 X16 12 0")
    tran0.writeAction("slorii X16 X16 12 229")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 4886")
    tran0.writeAction("slorii X16 X16 12 1856")
    tran0.writeAction("slorii X16 X16 12 2061")
    tran0.writeAction("slorii X16 X16 12 3650")
    tran0.writeAction("slorii X16 X16 12 1921")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 28854")
    tran0.writeAction("slorii X16 X16 12 1580")
    tran0.writeAction("slorii X16 X16 12 1173")
    tran0.writeAction("slorii X16 X16 12 1375")
    tran0.writeAction("slorii X16 X16 12 1882")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 26177")
    tran0.writeAction("slorii X16 X16 12 1536")
    tran0.writeAction("slorii X16 X16 12 1248")
    tran0.writeAction("slorii X16 X16 12 3120")
    tran0.writeAction("slorii X16 X16 12 368")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 40967")
    tran0.writeAction("slorii X16 X16 12 3597")
    tran0.writeAction("slorii X16 X16 12 4086")
    tran0.writeAction("slorii X16 X16 12 2126")
    tran0.writeAction("slorii X16 X16 12 23")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 4808")
    tran0.writeAction("slorii X16 X16 12 3192")
    tran0.writeAction("slorii X16 X16 12 2634")
    tran0.writeAction("slorii X16 X16 12 670")
    tran0.writeAction("slorii X16 X16 12 237")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 52271")
    tran0.writeAction("slorii X16 X16 12 3175")
    tran0.writeAction("slorii X16 X16 12 2409")
    tran0.writeAction("slorii X16 X16 12 1916")
    tran0.writeAction("slorii X16 X16 12 3411")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 36844")
    tran0.writeAction("slorii X16 X16 12 2025")
    tran0.writeAction("slorii X16 X16 12 2979")
    tran0.writeAction("slorii X16 X16 12 164")
    tran0.writeAction("slorii X16 X16 12 363")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 0")
    tran0.writeAction("slorii X16 X16 12 13")
    tran0.writeAction("slorii X16 X16 12 2304")
    tran0.writeAction("slorii X16 X16 12 0")
    tran0.writeAction("slorii X16 X16 12 229")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 4")
    tran0.writeAction("sli X17 X17 36")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 4")
    tran0.writeAction("sli X17 X17 32")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X20 0")
    tran0.writeAction("add X20 X7 X5")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("addi X20 X17 12")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("basic", state1, state2, 229)
    tran3 = state1.writeTransition("basic_with_action", state1, state2, 255)
    tran3.writeAction("movir X30 8")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("basic_with_action", state2, state2, 217)
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
