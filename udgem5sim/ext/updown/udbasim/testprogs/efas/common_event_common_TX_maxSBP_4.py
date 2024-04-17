from EFA_v2 import *
def common_event_common_TX_maxSBP_4():
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
    tran0.writeAction("movir X16 48491")
    tran0.writeAction("slorii X16 X16 12 3628")
    tran0.writeAction("slorii X16 X16 12 3985")
    tran0.writeAction("slorii X16 X16 12 257")
    tran0.writeAction("slorii X16 X16 12 3713")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 32557")
    tran0.writeAction("slorii X16 X16 12 909")
    tran0.writeAction("slorii X16 X16 12 2695")
    tran0.writeAction("slorii X16 X16 12 2448")
    tran0.writeAction("slorii X16 X16 12 3880")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 5905")
    tran0.writeAction("slorii X16 X16 12 336")
    tran0.writeAction("slorii X16 X16 12 694")
    tran0.writeAction("slorii X16 X16 12 50")
    tran0.writeAction("slorii X16 X16 12 1780")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 30019")
    tran0.writeAction("slorii X16 X16 12 3322")
    tran0.writeAction("slorii X16 X16 12 3388")
    tran0.writeAction("slorii X16 X16 12 3377")
    tran0.writeAction("slorii X16 X16 12 2697")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 43371")
    tran0.writeAction("slorii X16 X16 12 4039")
    tran0.writeAction("slorii X16 X16 12 385")
    tran0.writeAction("slorii X16 X16 12 2496")
    tran0.writeAction("slorii X16 X16 12 1248")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 8984")
    tran0.writeAction("slorii X16 X16 12 3001")
    tran0.writeAction("slorii X16 X16 12 1470")
    tran0.writeAction("slorii X16 X16 12 2769")
    tran0.writeAction("slorii X16 X16 12 2680")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 7031")
    tran0.writeAction("slorii X16 X16 12 3898")
    tran0.writeAction("slorii X16 X16 12 600")
    tran0.writeAction("slorii X16 X16 12 3110")
    tran0.writeAction("slorii X16 X16 12 1966")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 60734")
    tran0.writeAction("slorii X16 X16 12 3680")
    tran0.writeAction("slorii X16 X16 12 1442")
    tran0.writeAction("slorii X16 X16 12 934")
    tran0.writeAction("slorii X16 X16 12 4083")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 48491")
    tran0.writeAction("slorii X16 X16 12 3628")
    tran0.writeAction("slorii X16 X16 12 3985")
    tran0.writeAction("slorii X16 X16 12 257")
    tran0.writeAction("slorii X16 X16 12 3713")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 36")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 32")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("add X7 X31 X31")
    tran0.writeAction("movir X20 0")
    tran0.writeAction("sli X31 X21 3")
    tran0.writeAction("add X21 X20 X5")
    tran0.writeAction("movlsb X31")
    tran0.writeAction("addi X20 X17 1")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("commonCarry_with_action", state1, state2, 0)
    tran1.writeAction("addi X30 X30 1")
    tran1.writeAction("addi X5 X20 0")
    tran1.writeAction("lastact")
    tran2 = state2.writeTransition("commonCarry_with_action", state2, state2, 0)
    tran2.writeAction("addi X31 X31 1")
    tran2.writeAction("addi X5 X19 0")
    tran2.writeAction("yieldt")
    tran4 = state.writeTransition("event", state, state2, 0)
    tran4.writeAction("movir X16 0")
    tran4.writeAction("add X4 X16 X17")
    tran4.writeAction("sri X17 X17 32")
    tran4.writeAction("sli X17 X17 32")
    tran4.writeAction("addi X17 X17 3")
    tran4.writeAction("add X17 X16 X4")
    tran4.writeAction("addi X30 X30 1")
    tran4.writeAction("addi X5 X18 0")
    tran4.writeAction("lastact")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yield")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa
