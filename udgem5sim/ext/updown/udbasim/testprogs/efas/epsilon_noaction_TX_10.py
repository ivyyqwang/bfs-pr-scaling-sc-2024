from EFA_v2 import *
def epsilon_noaction_TX_10():
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
    tran0.writeAction("movir X16 40576")
    tran0.writeAction("slorii X16 X16 12 3414")
    tran0.writeAction("slorii X16 X16 12 145")
    tran0.writeAction("slorii X16 X16 12 3246")
    tran0.writeAction("slorii X16 X16 12 2596")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 44638")
    tran0.writeAction("slorii X16 X16 12 2197")
    tran0.writeAction("slorii X16 X16 12 2000")
    tran0.writeAction("slorii X16 X16 12 4061")
    tran0.writeAction("slorii X16 X16 12 1593")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 12559")
    tran0.writeAction("slorii X16 X16 12 3356")
    tran0.writeAction("slorii X16 X16 12 580")
    tran0.writeAction("slorii X16 X16 12 3776")
    tran0.writeAction("slorii X16 X16 12 3592")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 57799")
    tran0.writeAction("slorii X16 X16 12 4002")
    tran0.writeAction("slorii X16 X16 12 2909")
    tran0.writeAction("slorii X16 X16 12 1907")
    tran0.writeAction("slorii X16 X16 12 3339")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 35190")
    tran0.writeAction("slorii X16 X16 12 3570")
    tran0.writeAction("slorii X16 X16 12 1048")
    tran0.writeAction("slorii X16 X16 12 2816")
    tran0.writeAction("slorii X16 X16 12 2269")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 61311")
    tran0.writeAction("slorii X16 X16 12 3788")
    tran0.writeAction("slorii X16 X16 12 3286")
    tran0.writeAction("slorii X16 X16 12 150")
    tran0.writeAction("slorii X16 X16 12 2333")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 24805")
    tran0.writeAction("slorii X16 X16 12 3051")
    tran0.writeAction("slorii X16 X16 12 3587")
    tran0.writeAction("slorii X16 X16 12 843")
    tran0.writeAction("slorii X16 X16 12 867")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 29121")
    tran0.writeAction("slorii X16 X16 12 2190")
    tran0.writeAction("slorii X16 X16 12 3685")
    tran0.writeAction("slorii X16 X16 12 2949")
    tran0.writeAction("slorii X16 X16 12 3485")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 40576")
    tran0.writeAction("slorii X16 X16 12 3414")
    tran0.writeAction("slorii X16 X16 12 145")
    tran0.writeAction("slorii X16 X16 12 3246")
    tran0.writeAction("slorii X16 X16 12 2596")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 6")
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
    tran1 = state1.writeTransition("epsilonCarry", state1, state2, 0)
    tran2 = state2.writeTransition("epsilonCarry_with_action", state2, state2, 0)
    tran2.writeAction("addi X5 X17 0")
    tran2.writeAction("movir X31 4")
    tran2.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa
