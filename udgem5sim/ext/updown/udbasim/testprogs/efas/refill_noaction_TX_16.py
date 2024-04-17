from EFA_v2 import *
def refill_noaction_TX_16():
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
    tran0.writeAction("movir X16 31433")
    tran0.writeAction("slorii X16 X16 12 3654")
    tran0.writeAction("slorii X16 X16 12 1792")
    tran0.writeAction("slorii X16 X16 12 240")
    tran0.writeAction("slorii X16 X16 12 97")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 55648")
    tran0.writeAction("slorii X16 X16 12 868")
    tran0.writeAction("slorii X16 X16 12 1028")
    tran0.writeAction("slorii X16 X16 12 89")
    tran0.writeAction("slorii X16 X16 12 222")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 34456")
    tran0.writeAction("slorii X16 X16 12 3532")
    tran0.writeAction("slorii X16 X16 12 3537")
    tran0.writeAction("slorii X16 X16 12 2485")
    tran0.writeAction("slorii X16 X16 12 2885")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 8372")
    tran0.writeAction("slorii X16 X16 12 1261")
    tran0.writeAction("slorii X16 X16 12 2559")
    tran0.writeAction("slorii X16 X16 12 4038")
    tran0.writeAction("slorii X16 X16 12 2610")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 24290")
    tran0.writeAction("slorii X16 X16 12 3987")
    tran0.writeAction("slorii X16 X16 12 3148")
    tran0.writeAction("slorii X16 X16 12 3841")
    tran0.writeAction("slorii X16 X16 12 1420")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 42623")
    tran0.writeAction("slorii X16 X16 12 795")
    tran0.writeAction("slorii X16 X16 12 1052")
    tran0.writeAction("slorii X16 X16 12 3710")
    tran0.writeAction("slorii X16 X16 12 954")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 41851")
    tran0.writeAction("slorii X16 X16 12 677")
    tran0.writeAction("slorii X16 X16 12 2437")
    tran0.writeAction("slorii X16 X16 12 1002")
    tran0.writeAction("slorii X16 X16 12 85")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 54771")
    tran0.writeAction("slorii X16 X16 12 3230")
    tran0.writeAction("slorii X16 X16 12 1933")
    tran0.writeAction("slorii X16 X16 12 2931")
    tran0.writeAction("slorii X16 X16 12 1662")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 31433")
    tran0.writeAction("slorii X16 X16 12 3654")
    tran0.writeAction("slorii X16 X16 12 1792")
    tran0.writeAction("slorii X16 X16 12 240")
    tran0.writeAction("slorii X16 X16 12 97")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 2")
    tran0.writeAction("sli X17 X17 36")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 3")
    tran0.writeAction("sli X17 X17 32")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X20 0")
    tran0.writeAction("add X20 X7 X5")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("addi X20 X17 9")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("refill", state1, state2, 97, 1)
    tran3 = state1.writeTransition("refill_with_action", state1, state2, 255, 1)
    tran3.writeAction("movir X30 2")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("refill_with_action", state2, state2, 15, 2)
    tran2.writeAction("movir X31 1")
    tran2.writeAction("addi X5 X18 0")
    tran2.writeAction("yieldt")
    tran4 = state2.writeTransition("refill_with_action", state2, state1, 255, 2)
    tran4.writeAction("movir X31 2")
    tran4.writeAction("addi X5 X18 0")
    tran4.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa