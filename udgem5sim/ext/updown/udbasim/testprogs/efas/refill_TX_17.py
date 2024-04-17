from EFA_v2 import *
def refill_TX_17():
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
    tran0.writeAction("movir X16 62074")
    tran0.writeAction("slorii X16 X16 12 32")
    tran0.writeAction("slorii X16 X16 12 3174")
    tran0.writeAction("slorii X16 X16 12 453")
    tran0.writeAction("slorii X16 X16 12 1454")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 58226")
    tran0.writeAction("slorii X16 X16 12 2912")
    tran0.writeAction("slorii X16 X16 12 704")
    tran0.writeAction("slorii X16 X16 12 574")
    tran0.writeAction("slorii X16 X16 12 2587")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 9346")
    tran0.writeAction("slorii X16 X16 12 3246")
    tran0.writeAction("slorii X16 X16 12 2578")
    tran0.writeAction("slorii X16 X16 12 897")
    tran0.writeAction("slorii X16 X16 12 3557")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 29744")
    tran0.writeAction("slorii X16 X16 12 1984")
    tran0.writeAction("slorii X16 X16 12 1337")
    tran0.writeAction("slorii X16 X16 12 1032")
    tran0.writeAction("slorii X16 X16 12 2")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 47407")
    tran0.writeAction("slorii X16 X16 12 733")
    tran0.writeAction("slorii X16 X16 12 933")
    tran0.writeAction("slorii X16 X16 12 3197")
    tran0.writeAction("slorii X16 X16 12 2560")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 11668")
    tran0.writeAction("slorii X16 X16 12 3390")
    tran0.writeAction("slorii X16 X16 12 654")
    tran0.writeAction("slorii X16 X16 12 2030")
    tran0.writeAction("slorii X16 X16 12 2389")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 44519")
    tran0.writeAction("slorii X16 X16 12 3380")
    tran0.writeAction("slorii X16 X16 12 1988")
    tran0.writeAction("slorii X16 X16 12 3088")
    tran0.writeAction("slorii X16 X16 12 519")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 11455")
    tran0.writeAction("slorii X16 X16 12 60")
    tran0.writeAction("slorii X16 X16 12 1177")
    tran0.writeAction("slorii X16 X16 12 1241")
    tran0.writeAction("slorii X16 X16 12 3677")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 62074")
    tran0.writeAction("slorii X16 X16 12 32")
    tran0.writeAction("slorii X16 X16 12 3174")
    tran0.writeAction("slorii X16 X16 12 453")
    tran0.writeAction("slorii X16 X16 12 1454")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 7")
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
    tran1 = state1.writeTransition("refill_with_action", state1, state2, 46, 1)
    tran1.writeAction("movir X30 1")
    tran1.writeAction("addi X5 X17 0")
    tran1.writeAction("lastact")
    tran3 = state1.writeTransition("refill_with_action", state1, state2, 255, 1)
    tran3.writeAction("movir X30 2")
    tran3.writeAction("addi X5 X17 0")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("refill_with_action", state2, state2, 43, 4)
    tran2.writeAction("movir X31 1")
    tran2.writeAction("addi X5 X18 0")
    tran2.writeAction("yieldt")
    tran4 = state2.writeTransition("refill_with_action", state2, state1, 255, 4)
    tran4.writeAction("movir X31 2")
    tran4.writeAction("addi X5 X18 0")
    tran4.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa
