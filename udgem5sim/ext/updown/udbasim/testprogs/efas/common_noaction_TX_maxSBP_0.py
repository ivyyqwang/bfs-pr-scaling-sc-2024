from EFA_v2 import *
def common_noaction_TX_maxSBP_0():
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
    tran0.writeAction("movir X16 47614")
    tran0.writeAction("slorii X16 X16 12 728")
    tran0.writeAction("slorii X16 X16 12 3439")
    tran0.writeAction("slorii X16 X16 12 3319")
    tran0.writeAction("slorii X16 X16 12 3590")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 30971")
    tran0.writeAction("slorii X16 X16 12 1094")
    tran0.writeAction("slorii X16 X16 12 209")
    tran0.writeAction("slorii X16 X16 12 4039")
    tran0.writeAction("slorii X16 X16 12 428")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 6643")
    tran0.writeAction("slorii X16 X16 12 853")
    tran0.writeAction("slorii X16 X16 12 884")
    tran0.writeAction("slorii X16 X16 12 3372")
    tran0.writeAction("slorii X16 X16 12 3257")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 21041")
    tran0.writeAction("slorii X16 X16 12 1581")
    tran0.writeAction("slorii X16 X16 12 3834")
    tran0.writeAction("slorii X16 X16 12 800")
    tran0.writeAction("slorii X16 X16 12 349")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 11352")
    tran0.writeAction("slorii X16 X16 12 1943")
    tran0.writeAction("slorii X16 X16 12 2720")
    tran0.writeAction("slorii X16 X16 12 215")
    tran0.writeAction("slorii X16 X16 12 1914")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 13927")
    tran0.writeAction("slorii X16 X16 12 1240")
    tran0.writeAction("slorii X16 X16 12 1277")
    tran0.writeAction("slorii X16 X16 12 3579")
    tran0.writeAction("slorii X16 X16 12 398")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 26027")
    tran0.writeAction("slorii X16 X16 12 2454")
    tran0.writeAction("slorii X16 X16 12 2477")
    tran0.writeAction("slorii X16 X16 12 987")
    tran0.writeAction("slorii X16 X16 12 3727")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 59170")
    tran0.writeAction("slorii X16 X16 12 1971")
    tran0.writeAction("slorii X16 X16 12 2993")
    tran0.writeAction("slorii X16 X16 12 2668")
    tran0.writeAction("slorii X16 X16 12 2515")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 47614")
    tran0.writeAction("slorii X16 X16 12 728")
    tran0.writeAction("slorii X16 X16 12 3439")
    tran0.writeAction("slorii X16 X16 12 3319")
    tran0.writeAction("slorii X16 X16 12 3590")
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
    tran1 = state1.writeTransition("commonCarry", state1, state2, 0)
    tran2 = state2.writeTransition("commonCarry", state2, state2, 0)
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa