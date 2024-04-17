from EFA_v2 import *
def refill_TX_8():
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
    tran0.writeAction("movir X16 31399")
    tran0.writeAction("slorii X16 X16 12 3961")
    tran0.writeAction("slorii X16 X16 12 2539")
    tran0.writeAction("slorii X16 X16 12 874")
    tran0.writeAction("slorii X16 X16 12 1814")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 10168")
    tran0.writeAction("slorii X16 X16 12 2958")
    tran0.writeAction("slorii X16 X16 12 950")
    tran0.writeAction("slorii X16 X16 12 2991")
    tran0.writeAction("slorii X16 X16 12 820")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 18100")
    tran0.writeAction("slorii X16 X16 12 3332")
    tran0.writeAction("slorii X16 X16 12 637")
    tran0.writeAction("slorii X16 X16 12 2375")
    tran0.writeAction("slorii X16 X16 12 3395")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 43868")
    tran0.writeAction("slorii X16 X16 12 246")
    tran0.writeAction("slorii X16 X16 12 2027")
    tran0.writeAction("slorii X16 X16 12 608")
    tran0.writeAction("slorii X16 X16 12 892")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 10142")
    tran0.writeAction("slorii X16 X16 12 3671")
    tran0.writeAction("slorii X16 X16 12 394")
    tran0.writeAction("slorii X16 X16 12 3207")
    tran0.writeAction("slorii X16 X16 12 3421")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 6133")
    tran0.writeAction("slorii X16 X16 12 3521")
    tran0.writeAction("slorii X16 X16 12 1741")
    tran0.writeAction("slorii X16 X16 12 382")
    tran0.writeAction("slorii X16 X16 12 1868")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 7311")
    tran0.writeAction("slorii X16 X16 12 2900")
    tran0.writeAction("slorii X16 X16 12 215")
    tran0.writeAction("slorii X16 X16 12 4036")
    tran0.writeAction("slorii X16 X16 12 3966")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 11079")
    tran0.writeAction("slorii X16 X16 12 2024")
    tran0.writeAction("slorii X16 X16 12 2053")
    tran0.writeAction("slorii X16 X16 12 2189")
    tran0.writeAction("slorii X16 X16 12 3497")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 31399")
    tran0.writeAction("slorii X16 X16 12 3961")
    tran0.writeAction("slorii X16 X16 12 2539")
    tran0.writeAction("slorii X16 X16 12 874")
    tran0.writeAction("slorii X16 X16 12 1814")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 4")
    tran0.writeAction("sli X17 X17 36")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 6")
    tran0.writeAction("sli X17 X17 32")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("add X7 X31 X31")
    tran0.writeAction("movir X20 0")
    tran0.writeAction("sli X31 X21 3")
    tran0.writeAction("add X21 X20 X5")
    tran0.writeAction("movlsb X31")
    tran0.writeAction("addi X20 X17 18")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("refill_with_action", state1, state2, 6, 2)
    tran1.writeAction("movir X30 1")
    tran1.writeAction("addi X5 X17 0")
    tran1.writeAction("lastact")
    tran3 = state1.writeTransition("refill_with_action", state1, state2, 255, 2)
    tran3.writeAction("movir X30 2")
    tran3.writeAction("addi X5 X17 0")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("refill_with_action", state2, state2, 1, 6)
    tran2.writeAction("movir X31 1")
    tran2.writeAction("addi X5 X18 0")
    tran2.writeAction("yieldt")
    tran4 = state2.writeTransition("refill_with_action", state2, state1, 255, 6)
    tran4.writeAction("movir X31 2")
    tran4.writeAction("addi X5 X18 0")
    tran4.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa