from EFA_v2 import *
def basic_action8_with_lastact_TX_10():
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
    tran0.writeAction("movir X16 13296")
    tran0.writeAction("slorii X16 X16 12 2357")
    tran0.writeAction("slorii X16 X16 12 512")
    tran0.writeAction("slorii X16 X16 12 0")
    tran0.writeAction("slorii X16 X16 12 194")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 47062")
    tran0.writeAction("slorii X16 X16 12 2114")
    tran0.writeAction("slorii X16 X16 12 2304")
    tran0.writeAction("slorii X16 X16 12 0")
    tran0.writeAction("slorii X16 X16 12 93")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 59609")
    tran0.writeAction("slorii X16 X16 12 369")
    tran0.writeAction("slorii X16 X16 12 968")
    tran0.writeAction("slorii X16 X16 12 229")
    tran0.writeAction("slorii X16 X16 12 1903")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 50364")
    tran0.writeAction("slorii X16 X16 12 449")
    tran0.writeAction("slorii X16 X16 12 2013")
    tran0.writeAction("slorii X16 X16 12 647")
    tran0.writeAction("slorii X16 X16 12 3538")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 48795")
    tran0.writeAction("slorii X16 X16 12 905")
    tran0.writeAction("slorii X16 X16 12 1832")
    tran0.writeAction("slorii X16 X16 12 1193")
    tran0.writeAction("slorii X16 X16 12 2564")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 53186")
    tran0.writeAction("slorii X16 X16 12 3438")
    tran0.writeAction("slorii X16 X16 12 74")
    tran0.writeAction("slorii X16 X16 12 3694")
    tran0.writeAction("slorii X16 X16 12 3516")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 10938")
    tran0.writeAction("slorii X16 X16 12 236")
    tran0.writeAction("slorii X16 X16 12 3468")
    tran0.writeAction("slorii X16 X16 12 1796")
    tran0.writeAction("slorii X16 X16 12 784")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 36649")
    tran0.writeAction("slorii X16 X16 12 1064")
    tran0.writeAction("slorii X16 X16 12 2494")
    tran0.writeAction("slorii X16 X16 12 2568")
    tran0.writeAction("slorii X16 X16 12 754")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 13296")
    tran0.writeAction("slorii X16 X16 12 2357")
    tran0.writeAction("slorii X16 X16 12 512")
    tran0.writeAction("slorii X16 X16 12 0")
    tran0.writeAction("slorii X16 X16 12 194")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 4")
    tran0.writeAction("sli X17 X17 36")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 8")
    tran0.writeAction("sli X17 X17 32")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X20 0")
    tran0.writeAction("add X20 X7 X5")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("addi X20 X17 24")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("basic_with_action", state1, state2, 194)
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
    tran2 = state2.writeTransition("basic_with_action", state2, state2, 93)
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