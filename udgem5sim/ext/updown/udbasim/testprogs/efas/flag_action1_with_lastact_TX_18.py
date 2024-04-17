from EFA_v2 import *
def flag_action1_with_lastact_TX_18():
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
    tran0 = state.writeTransition("flagCarry_with_action", state, state1, 1)
    tran0.writeAction("movir X17 0")
    tran0.writeAction("add X7 X17 X17")
    tran0.writeAction("movir X16 33854")
    tran0.writeAction("slorii X16 X16 12 2234")
    tran0.writeAction("slorii X16 X16 12 866")
    tran0.writeAction("slorii X16 X16 12 971")
    tran0.writeAction("slorii X16 X16 12 3301")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 24584")
    tran0.writeAction("slorii X16 X16 12 3640")
    tran0.writeAction("slorii X16 X16 12 1971")
    tran0.writeAction("slorii X16 X16 12 3051")
    tran0.writeAction("slorii X16 X16 12 1276")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 42208")
    tran0.writeAction("slorii X16 X16 12 717")
    tran0.writeAction("slorii X16 X16 12 3424")
    tran0.writeAction("slorii X16 X16 12 3610")
    tran0.writeAction("slorii X16 X16 12 2569")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 30402")
    tran0.writeAction("slorii X16 X16 12 884")
    tran0.writeAction("slorii X16 X16 12 3264")
    tran0.writeAction("slorii X16 X16 12 2791")
    tran0.writeAction("slorii X16 X16 12 1616")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 52435")
    tran0.writeAction("slorii X16 X16 12 532")
    tran0.writeAction("slorii X16 X16 12 323")
    tran0.writeAction("slorii X16 X16 12 2661")
    tran0.writeAction("slorii X16 X16 12 803")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 43793")
    tran0.writeAction("slorii X16 X16 12 3935")
    tran0.writeAction("slorii X16 X16 12 2593")
    tran0.writeAction("slorii X16 X16 12 1968")
    tran0.writeAction("slorii X16 X16 12 1059")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 51334")
    tran0.writeAction("slorii X16 X16 12 368")
    tran0.writeAction("slorii X16 X16 12 1593")
    tran0.writeAction("slorii X16 X16 12 1132")
    tran0.writeAction("slorii X16 X16 12 1751")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 62307")
    tran0.writeAction("slorii X16 X16 12 241")
    tran0.writeAction("slorii X16 X16 12 655")
    tran0.writeAction("slorii X16 X16 12 997")
    tran0.writeAction("slorii X16 X16 12 700")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 33854")
    tran0.writeAction("slorii X16 X16 12 2234")
    tran0.writeAction("slorii X16 X16 12 866")
    tran0.writeAction("slorii X16 X16 12 971")
    tran0.writeAction("slorii X16 X16 12 3301")
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
    tran0.writeAction("movir X16 127")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("flagCarry_with_action", state1, state2, 127)
    tran1.writeAction("movir X16 72")
    tran1.writeAction("lastact")
    tran3 = state1.writeTransition("flagCarry_with_action", state1, state2, 255)
    tran3.writeAction("movir X16 255")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("flagCarry_with_action", state2, state2, 72)
    tran2.writeAction("movir X31 7")
    tran2.writeAction("yieldt")
    tran4 = state2.writeTransition("flagCarry_with_action", state2, state1, 255)
    tran4.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa