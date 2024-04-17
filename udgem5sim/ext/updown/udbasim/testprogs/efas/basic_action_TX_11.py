from EFA_v2 import *
def basic_action_TX_11():
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
    tran0.writeAction("movir X16 8013")
    tran0.writeAction("slorii X16 X16 12 376")
    tran0.writeAction("slorii X16 X16 12 2694")
    tran0.writeAction("slorii X16 X16 12 3594")
    tran0.writeAction("slorii X16 X16 12 684")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 27692")
    tran0.writeAction("slorii X16 X16 12 4070")
    tran0.writeAction("slorii X16 X16 12 1902")
    tran0.writeAction("slorii X16 X16 12 1307")
    tran0.writeAction("slorii X16 X16 12 3613")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 24702")
    tran0.writeAction("slorii X16 X16 12 3680")
    tran0.writeAction("slorii X16 X16 12 120")
    tran0.writeAction("slorii X16 X16 12 211")
    tran0.writeAction("slorii X16 X16 12 2625")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 22783")
    tran0.writeAction("slorii X16 X16 12 3822")
    tran0.writeAction("slorii X16 X16 12 1962")
    tran0.writeAction("slorii X16 X16 12 2889")
    tran0.writeAction("slorii X16 X16 12 1952")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 58313")
    tran0.writeAction("slorii X16 X16 12 458")
    tran0.writeAction("slorii X16 X16 12 1885")
    tran0.writeAction("slorii X16 X16 12 260")
    tran0.writeAction("slorii X16 X16 12 2834")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 36779")
    tran0.writeAction("slorii X16 X16 12 2779")
    tran0.writeAction("slorii X16 X16 12 227")
    tran0.writeAction("slorii X16 X16 12 1037")
    tran0.writeAction("slorii X16 X16 12 3067")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 37867")
    tran0.writeAction("slorii X16 X16 12 2426")
    tran0.writeAction("slorii X16 X16 12 1258")
    tran0.writeAction("slorii X16 X16 12 2736")
    tran0.writeAction("slorii X16 X16 12 2613")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 21361")
    tran0.writeAction("slorii X16 X16 12 426")
    tran0.writeAction("slorii X16 X16 12 2465")
    tran0.writeAction("slorii X16 X16 12 3967")
    tran0.writeAction("slorii X16 X16 12 2047")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 8013")
    tran0.writeAction("slorii X16 X16 12 376")
    tran0.writeAction("slorii X16 X16 12 2694")
    tran0.writeAction("slorii X16 X16 12 3594")
    tran0.writeAction("slorii X16 X16 12 684")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 5")
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
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("basic_with_action", state1, state2, 12)
    tran1.writeAction("addi X5 X16 0")
    tran1.writeAction("movir X30 5")
    tran1.writeAction("movir X29 5")
    tran1.writeAction("lastact")
    tran3 = state1.writeTransition("basic_with_action", state1, state2, 255)
    tran3.writeAction("addi X5 X16 0")
    tran3.writeAction("movir X30 6")
    tran3.writeAction("movir X29 6")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("basic_with_action", state2, state2, 5)
    tran2.writeAction("addi X5 X17 0")
    tran2.writeAction("movir X31 5")
    tran2.writeAction("yieldt")
    tran4 = state2.writeTransition("basic_with_action", state2, state1, 255)
    tran4.writeAction("addi X5 X17 0")
    tran4.writeAction("movir X31 6")
    tran4.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa
