from EFA_v2 import *
def common_noaction_TX_maxSBP_9():
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
    tran0.writeAction("movir X16 38769")
    tran0.writeAction("slorii X16 X16 12 1133")
    tran0.writeAction("slorii X16 X16 12 3222")
    tran0.writeAction("slorii X16 X16 12 257")
    tran0.writeAction("slorii X16 X16 12 1887")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 5285")
    tran0.writeAction("slorii X16 X16 12 1323")
    tran0.writeAction("slorii X16 X16 12 3673")
    tran0.writeAction("slorii X16 X16 12 2997")
    tran0.writeAction("slorii X16 X16 12 3154")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 323")
    tran0.writeAction("slorii X16 X16 12 1124")
    tran0.writeAction("slorii X16 X16 12 2235")
    tran0.writeAction("slorii X16 X16 12 2984")
    tran0.writeAction("slorii X16 X16 12 2679")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 3445")
    tran0.writeAction("slorii X16 X16 12 3569")
    tran0.writeAction("slorii X16 X16 12 506")
    tran0.writeAction("slorii X16 X16 12 1640")
    tran0.writeAction("slorii X16 X16 12 4065")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 56781")
    tran0.writeAction("slorii X16 X16 12 1207")
    tran0.writeAction("slorii X16 X16 12 187")
    tran0.writeAction("slorii X16 X16 12 1794")
    tran0.writeAction("slorii X16 X16 12 68")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 30073")
    tran0.writeAction("slorii X16 X16 12 110")
    tran0.writeAction("slorii X16 X16 12 799")
    tran0.writeAction("slorii X16 X16 12 73")
    tran0.writeAction("slorii X16 X16 12 2338")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 25365")
    tran0.writeAction("slorii X16 X16 12 346")
    tran0.writeAction("slorii X16 X16 12 3382")
    tran0.writeAction("slorii X16 X16 12 1066")
    tran0.writeAction("slorii X16 X16 12 571")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 21451")
    tran0.writeAction("slorii X16 X16 12 450")
    tran0.writeAction("slorii X16 X16 12 2829")
    tran0.writeAction("slorii X16 X16 12 2694")
    tran0.writeAction("slorii X16 X16 12 4047")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 38769")
    tran0.writeAction("slorii X16 X16 12 1133")
    tran0.writeAction("slorii X16 X16 12 3222")
    tran0.writeAction("slorii X16 X16 12 257")
    tran0.writeAction("slorii X16 X16 12 1887")
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
    tran0.writeAction("addi X20 X17 7")
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
