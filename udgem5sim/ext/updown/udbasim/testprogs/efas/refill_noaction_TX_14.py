from EFA_v2 import *
def refill_noaction_TX_14():
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
    tran0 = state.writeTransition("refill_with_action", state, state1, 1)
    tran0.writeAction("movir X17 0")
    tran0.writeAction("add X7 X17 X17")
    tran0.writeAction("movir X16 32849")
    tran0.writeAction("slorii X16 X16 12 8")
    tran0.writeAction("slorii X16 X16 12 3716")
    tran0.writeAction("slorii X16 X16 12 3760")
    tran0.writeAction("slorii X16 X16 12 74")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 27138")
    tran0.writeAction("slorii X16 X16 12 453")
    tran0.writeAction("slorii X16 X16 12 534")
    tran0.writeAction("slorii X16 X16 12 2155")
    tran0.writeAction("slorii X16 X16 12 734")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 46053")
    tran0.writeAction("slorii X16 X16 12 3731")
    tran0.writeAction("slorii X16 X16 12 1370")
    tran0.writeAction("slorii X16 X16 12 3887")
    tran0.writeAction("slorii X16 X16 12 1243")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 27894")
    tran0.writeAction("slorii X16 X16 12 3533")
    tran0.writeAction("slorii X16 X16 12 3872")
    tran0.writeAction("slorii X16 X16 12 2178")
    tran0.writeAction("slorii X16 X16 12 1512")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 41153")
    tran0.writeAction("slorii X16 X16 12 725")
    tran0.writeAction("slorii X16 X16 12 2408")
    tran0.writeAction("slorii X16 X16 12 4035")
    tran0.writeAction("slorii X16 X16 12 822")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 58924")
    tran0.writeAction("slorii X16 X16 12 2464")
    tran0.writeAction("slorii X16 X16 12 2314")
    tran0.writeAction("slorii X16 X16 12 2496")
    tran0.writeAction("slorii X16 X16 12 3157")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 50374")
    tran0.writeAction("slorii X16 X16 12 2524")
    tran0.writeAction("slorii X16 X16 12 3936")
    tran0.writeAction("slorii X16 X16 12 81")
    tran0.writeAction("slorii X16 X16 12 1753")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 41791")
    tran0.writeAction("slorii X16 X16 12 463")
    tran0.writeAction("slorii X16 X16 12 457")
    tran0.writeAction("slorii X16 X16 12 863")
    tran0.writeAction("slorii X16 X16 12 4011")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 32849")
    tran0.writeAction("slorii X16 X16 12 8")
    tran0.writeAction("slorii X16 X16 12 3716")
    tran0.writeAction("slorii X16 X16 12 3760")
    tran0.writeAction("slorii X16 X16 12 74")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 2")
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
    tran1 = state1.writeTransition("refill", state1, state2, 74, 4)
    tran3 = state1.writeTransition("refill_with_action", state1, state2, 255, 4)
    tran3.writeAction("movir X30 2")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("refill_with_action", state2, state2, 142, 1)
    tran2.writeAction("movir X31 1")
    tran2.writeAction("addi X5 X18 0")
    tran2.writeAction("yieldt")
    tran4 = state2.writeTransition("refill_with_action", state2, state1, 255, 1)
    tran4.writeAction("movir X31 2")
    tran4.writeAction("addi X5 X18 0")
    tran4.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa