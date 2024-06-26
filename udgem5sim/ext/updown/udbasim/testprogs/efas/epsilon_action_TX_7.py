from EFA_v2 import *
def epsilon_action_TX_7():
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
    tran0 = state.writeTransition("epsilonCarry_with_action", state, state1, 1)
    tran0.writeAction("movir X17 0")
    tran0.writeAction("add X7 X17 X17")
    tran0.writeAction("movir X16 20943")
    tran0.writeAction("slorii X16 X16 12 2548")
    tran0.writeAction("slorii X16 X16 12 2710")
    tran0.writeAction("slorii X16 X16 12 2551")
    tran0.writeAction("slorii X16 X16 12 3863")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 49133")
    tran0.writeAction("slorii X16 X16 12 46")
    tran0.writeAction("slorii X16 X16 12 2888")
    tran0.writeAction("slorii X16 X16 12 2803")
    tran0.writeAction("slorii X16 X16 12 1784")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 27622")
    tran0.writeAction("slorii X16 X16 12 999")
    tran0.writeAction("slorii X16 X16 12 3037")
    tran0.writeAction("slorii X16 X16 12 1185")
    tran0.writeAction("slorii X16 X16 12 2651")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 29875")
    tran0.writeAction("slorii X16 X16 12 6")
    tran0.writeAction("slorii X16 X16 12 743")
    tran0.writeAction("slorii X16 X16 12 3016")
    tran0.writeAction("slorii X16 X16 12 1721")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 51461")
    tran0.writeAction("slorii X16 X16 12 2830")
    tran0.writeAction("slorii X16 X16 12 1115")
    tran0.writeAction("slorii X16 X16 12 1981")
    tran0.writeAction("slorii X16 X16 12 2833")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 12611")
    tran0.writeAction("slorii X16 X16 12 3036")
    tran0.writeAction("slorii X16 X16 12 3063")
    tran0.writeAction("slorii X16 X16 12 2803")
    tran0.writeAction("slorii X16 X16 12 2215")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 46847")
    tran0.writeAction("slorii X16 X16 12 1642")
    tran0.writeAction("slorii X16 X16 12 3602")
    tran0.writeAction("slorii X16 X16 12 134")
    tran0.writeAction("slorii X16 X16 12 1145")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 39301")
    tran0.writeAction("slorii X16 X16 12 3072")
    tran0.writeAction("slorii X16 X16 12 648")
    tran0.writeAction("slorii X16 X16 12 4039")
    tran0.writeAction("slorii X16 X16 12 2480")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 20943")
    tran0.writeAction("slorii X16 X16 12 2548")
    tran0.writeAction("slorii X16 X16 12 2710")
    tran0.writeAction("slorii X16 X16 12 2551")
    tran0.writeAction("slorii X16 X16 12 3863")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 4")
    tran0.writeAction("sli X17 X17 36")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 7")
    tran0.writeAction("sli X17 X17 32")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X20 0")
    tran0.writeAction("add X20 X7 X5")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("addi X20 X17 21")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("epsilonCarry_with_action", state1, state2, 0)
    tran1.writeAction("addi X5 X16 0")
    tran1.writeAction("movir X30 3")
    tran1.writeAction("lastact")
    tran2 = state2.writeTransition("epsilonCarry_with_action", state2, state2, 0)
    tran2.writeAction("addi X5 X17 0")
    tran2.writeAction("movir X31 4")
    tran2.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa
