from EFA_v2 import *
def basic_action8_with_lastact_TX_7():
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
    tran0.writeAction("slorii X16 X16 12 2376")
    tran0.writeAction("slorii X16 X16 12 3328")
    tran0.writeAction("slorii X16 X16 12 0")
    tran0.writeAction("slorii X16 X16 12 127")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 60354")
    tran0.writeAction("slorii X16 X16 12 557")
    tran0.writeAction("slorii X16 X16 12 3038")
    tran0.writeAction("slorii X16 X16 12 1664")
    tran0.writeAction("slorii X16 X16 12 1536")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 13332")
    tran0.writeAction("slorii X16 X16 12 222")
    tran0.writeAction("slorii X16 X16 12 686")
    tran0.writeAction("slorii X16 X16 12 3099")
    tran0.writeAction("slorii X16 X16 12 1762")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 63280")
    tran0.writeAction("slorii X16 X16 12 1465")
    tran0.writeAction("slorii X16 X16 12 2131")
    tran0.writeAction("slorii X16 X16 12 2807")
    tran0.writeAction("slorii X16 X16 12 2929")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 49156")
    tran0.writeAction("slorii X16 X16 12 2751")
    tran0.writeAction("slorii X16 X16 12 1830")
    tran0.writeAction("slorii X16 X16 12 119")
    tran0.writeAction("slorii X16 X16 12 2177")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 42929")
    tran0.writeAction("slorii X16 X16 12 3571")
    tran0.writeAction("slorii X16 X16 12 2623")
    tran0.writeAction("slorii X16 X16 12 2951")
    tran0.writeAction("slorii X16 X16 12 3823")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 28070")
    tran0.writeAction("slorii X16 X16 12 386")
    tran0.writeAction("slorii X16 X16 12 1407")
    tran0.writeAction("slorii X16 X16 12 3541")
    tran0.writeAction("slorii X16 X16 12 2988")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 14559")
    tran0.writeAction("slorii X16 X16 12 2950")
    tran0.writeAction("slorii X16 X16 12 1719")
    tran0.writeAction("slorii X16 X16 12 598")
    tran0.writeAction("slorii X16 X16 12 2029")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 0")
    tran0.writeAction("slorii X16 X16 12 2376")
    tran0.writeAction("slorii X16 X16 12 3328")
    tran0.writeAction("slorii X16 X16 12 0")
    tran0.writeAction("slorii X16 X16 12 127")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 4")
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
    tran1 = state1.writeTransition("basic_with_action", state1, state2, 127)
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
    tran2 = state2.writeTransition("basic_with_action", state2, state2, 148)
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
