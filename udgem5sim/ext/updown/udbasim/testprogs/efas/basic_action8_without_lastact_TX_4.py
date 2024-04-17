from EFA_v2 import *
def basic_action8_without_lastact_TX_4():
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
    tran0.writeAction("movir X16 37481")
    tran0.writeAction("slorii X16 X16 12 1808")
    tran0.writeAction("slorii X16 X16 12 1344")
    tran0.writeAction("slorii X16 X16 12 1456")
    tran0.writeAction("slorii X16 X16 12 2031")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 13375")
    tran0.writeAction("slorii X16 X16 12 2628")
    tran0.writeAction("slorii X16 X16 12 4045")
    tran0.writeAction("slorii X16 X16 12 1667")
    tran0.writeAction("slorii X16 X16 12 585")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 24644")
    tran0.writeAction("slorii X16 X16 12 1283")
    tran0.writeAction("slorii X16 X16 12 841")
    tran0.writeAction("slorii X16 X16 12 2535")
    tran0.writeAction("slorii X16 X16 12 1242")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 30389")
    tran0.writeAction("slorii X16 X16 12 12")
    tran0.writeAction("slorii X16 X16 12 1937")
    tran0.writeAction("slorii X16 X16 12 1420")
    tran0.writeAction("slorii X16 X16 12 3168")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 16058")
    tran0.writeAction("slorii X16 X16 12 2078")
    tran0.writeAction("slorii X16 X16 12 732")
    tran0.writeAction("slorii X16 X16 12 1776")
    tran0.writeAction("slorii X16 X16 12 590")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 25230")
    tran0.writeAction("slorii X16 X16 12 934")
    tran0.writeAction("slorii X16 X16 12 647")
    tran0.writeAction("slorii X16 X16 12 3837")
    tran0.writeAction("slorii X16 X16 12 529")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 65105")
    tran0.writeAction("slorii X16 X16 12 3442")
    tran0.writeAction("slorii X16 X16 12 1932")
    tran0.writeAction("slorii X16 X16 12 670")
    tran0.writeAction("slorii X16 X16 12 239")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 28358")
    tran0.writeAction("slorii X16 X16 12 2535")
    tran0.writeAction("slorii X16 X16 12 2331")
    tran0.writeAction("slorii X16 X16 12 2040")
    tran0.writeAction("slorii X16 X16 12 3677")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 37481")
    tran0.writeAction("slorii X16 X16 12 1808")
    tran0.writeAction("slorii X16 X16 12 1344")
    tran0.writeAction("slorii X16 X16 12 1456")
    tran0.writeAction("slorii X16 X16 12 2031")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 3")
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
    tran1 = state1.writeTransition("basic_with_action", state1, state2, 7)
    tran1.writeAction("addi X5 X16 0")
    tran1.writeAction("movir X30 7")
    tran1.writeAction("movir X29 7")
    tran1.writeAction("movir X28 7")
    tran1.writeAction("movir X27 7")
    tran1.writeAction("movir X26 7")
    tran1.writeAction("movir X25 7")
    tran1.writeAction("movir X24 7")
    tran3 = state1.writeTransition("basic_with_action", state1, state2, 255)
    tran3.writeAction("addi X5 X16 8")
    tran3.writeAction("movir X30 8")
    tran3.writeAction("movir X29 8")
    tran3.writeAction("movir X28 8")
    tran3.writeAction("movir X27 8")
    tran3.writeAction("movir X26 8")
    tran3.writeAction("movir X25 8")
    tran3.writeAction("movir X24 8")
    tran2 = state2.writeTransition("basic_with_action", state2, state2, 7)
    tran2.writeAction("addi X5 X17 0")
    tran2.writeAction("movir X31 7")
    tran2.writeAction("yieldt")
    tran4 = state2.writeTransition("basic_with_action", state2, state1, 255)
    tran4.writeAction("addi X5 X17 0")
    tran4.writeAction("movir X31 8")
    tran4.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa
