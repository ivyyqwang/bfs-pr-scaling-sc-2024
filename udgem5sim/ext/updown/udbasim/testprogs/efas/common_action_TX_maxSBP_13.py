from EFA_v2 import *
def common_action_TX_maxSBP_13():
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
    tran0.writeAction("movir X16 12499")
    tran0.writeAction("slorii X16 X16 12 3216")
    tran0.writeAction("slorii X16 X16 12 2380")
    tran0.writeAction("slorii X16 X16 12 2445")
    tran0.writeAction("slorii X16 X16 12 500")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 16630")
    tran0.writeAction("slorii X16 X16 12 3072")
    tran0.writeAction("slorii X16 X16 12 1372")
    tran0.writeAction("slorii X16 X16 12 2841")
    tran0.writeAction("slorii X16 X16 12 2231")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 63397")
    tran0.writeAction("slorii X16 X16 12 632")
    tran0.writeAction("slorii X16 X16 12 594")
    tran0.writeAction("slorii X16 X16 12 3044")
    tran0.writeAction("slorii X16 X16 12 419")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 4782")
    tran0.writeAction("slorii X16 X16 12 470")
    tran0.writeAction("slorii X16 X16 12 2912")
    tran0.writeAction("slorii X16 X16 12 2533")
    tran0.writeAction("slorii X16 X16 12 2292")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 7811")
    tran0.writeAction("slorii X16 X16 12 2821")
    tran0.writeAction("slorii X16 X16 12 2688")
    tran0.writeAction("slorii X16 X16 12 1383")
    tran0.writeAction("slorii X16 X16 12 1464")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 37175")
    tran0.writeAction("slorii X16 X16 12 2166")
    tran0.writeAction("slorii X16 X16 12 1164")
    tran0.writeAction("slorii X16 X16 12 2888")
    tran0.writeAction("slorii X16 X16 12 1672")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 28120")
    tran0.writeAction("slorii X16 X16 12 1243")
    tran0.writeAction("slorii X16 X16 12 2430")
    tran0.writeAction("slorii X16 X16 12 718")
    tran0.writeAction("slorii X16 X16 12 3380")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 49069")
    tran0.writeAction("slorii X16 X16 12 1163")
    tran0.writeAction("slorii X16 X16 12 3164")
    tran0.writeAction("slorii X16 X16 12 2593")
    tran0.writeAction("slorii X16 X16 12 1808")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 12499")
    tran0.writeAction("slorii X16 X16 12 3216")
    tran0.writeAction("slorii X16 X16 12 2380")
    tran0.writeAction("slorii X16 X16 12 2445")
    tran0.writeAction("slorii X16 X16 12 500")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 8")
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
    tran0.writeAction("addi X20 X17 8")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("commonCarry_with_action", state1, state2, 0)
    tran1.writeAction("addi X5 X16 0")
    tran1.writeAction("movir X30 1")
    tran1.writeAction("lastact")
    tran2 = state2.writeTransition("commonCarry_with_action", state2, state2, 0)
    tran2.writeAction("addi X5 X17 0")
    tran2.writeAction("movir X31 2")
    tran2.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa
