from EFA_v2 import *
def common_event_common_TX_11():
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
    tran0.writeAction("movir X16 64931")
    tran0.writeAction("slorii X16 X16 12 1128")
    tran0.writeAction("slorii X16 X16 12 403")
    tran0.writeAction("slorii X16 X16 12 3249")
    tran0.writeAction("slorii X16 X16 12 9")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 1771")
    tran0.writeAction("slorii X16 X16 12 2047")
    tran0.writeAction("slorii X16 X16 12 684")
    tran0.writeAction("slorii X16 X16 12 3258")
    tran0.writeAction("slorii X16 X16 12 2828")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 39127")
    tran0.writeAction("slorii X16 X16 12 2097")
    tran0.writeAction("slorii X16 X16 12 1506")
    tran0.writeAction("slorii X16 X16 12 2729")
    tran0.writeAction("slorii X16 X16 12 1123")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 5952")
    tran0.writeAction("slorii X16 X16 12 3815")
    tran0.writeAction("slorii X16 X16 12 1081")
    tran0.writeAction("slorii X16 X16 12 4069")
    tran0.writeAction("slorii X16 X16 12 1006")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 28828")
    tran0.writeAction("slorii X16 X16 12 565")
    tran0.writeAction("slorii X16 X16 12 3651")
    tran0.writeAction("slorii X16 X16 12 4058")
    tran0.writeAction("slorii X16 X16 12 1537")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 33066")
    tran0.writeAction("slorii X16 X16 12 1698")
    tran0.writeAction("slorii X16 X16 12 1112")
    tran0.writeAction("slorii X16 X16 12 1722")
    tran0.writeAction("slorii X16 X16 12 2391")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 53539")
    tran0.writeAction("slorii X16 X16 12 2010")
    tran0.writeAction("slorii X16 X16 12 3098")
    tran0.writeAction("slorii X16 X16 12 2229")
    tran0.writeAction("slorii X16 X16 12 3671")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 18528")
    tran0.writeAction("slorii X16 X16 12 2130")
    tran0.writeAction("slorii X16 X16 12 913")
    tran0.writeAction("slorii X16 X16 12 2174")
    tran0.writeAction("slorii X16 X16 12 1900")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 64931")
    tran0.writeAction("slorii X16 X16 12 1128")
    tran0.writeAction("slorii X16 X16 12 403")
    tran0.writeAction("slorii X16 X16 12 3249")
    tran0.writeAction("slorii X16 X16 12 9")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 8")
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
    tran1 = state1.writeTransition("commonCarry_with_action", state1, state2, 0)
    tran1.writeAction("addi X30 X30 1")
    tran1.writeAction("addi X5 X17 0")
    tran1.writeAction("yield")
    tran2 = state2.writeTransition("commonCarry_with_action", state2, state2, 0)
    tran2.writeAction("addi X31 X31 1")
    tran2.writeAction("addi X5 X19 0")
    tran2.writeAction("yieldt")
    tran4 = state.writeTransition("event", state, state2, 0)
    tran4.writeAction("addi X30 X30 1")
    tran4.writeAction("addi X5 X18 0")
    tran4.writeAction("lastact")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa
