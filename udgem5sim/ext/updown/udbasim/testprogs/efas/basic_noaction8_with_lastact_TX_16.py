from EFA_v2 import *
def basic_noaction8_with_lastact_TX_16():
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
    tran0.writeAction("movir X16 21")
    tran0.writeAction("slorii X16 X16 12 1935")
    tran0.writeAction("slorii X16 X16 12 2583")
    tran0.writeAction("slorii X16 X16 12 1562")
    tran0.writeAction("slorii X16 X16 12 207")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 7250")
    tran0.writeAction("slorii X16 X16 12 432")
    tran0.writeAction("slorii X16 X16 12 3914")
    tran0.writeAction("slorii X16 X16 12 4015")
    tran0.writeAction("slorii X16 X16 12 1196")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 32696")
    tran0.writeAction("slorii X16 X16 12 3847")
    tran0.writeAction("slorii X16 X16 12 1319")
    tran0.writeAction("slorii X16 X16 12 3048")
    tran0.writeAction("slorii X16 X16 12 3895")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 41359")
    tran0.writeAction("slorii X16 X16 12 3302")
    tran0.writeAction("slorii X16 X16 12 3935")
    tran0.writeAction("slorii X16 X16 12 521")
    tran0.writeAction("slorii X16 X16 12 2980")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 42518")
    tran0.writeAction("slorii X16 X16 12 1257")
    tran0.writeAction("slorii X16 X16 12 3439")
    tran0.writeAction("slorii X16 X16 12 526")
    tran0.writeAction("slorii X16 X16 12 3891")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 17145")
    tran0.writeAction("slorii X16 X16 12 473")
    tran0.writeAction("slorii X16 X16 12 4")
    tran0.writeAction("slorii X16 X16 12 1061")
    tran0.writeAction("slorii X16 X16 12 789")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 31749")
    tran0.writeAction("slorii X16 X16 12 1445")
    tran0.writeAction("slorii X16 X16 12 4020")
    tran0.writeAction("slorii X16 X16 12 581")
    tran0.writeAction("slorii X16 X16 12 1246")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 27649")
    tran0.writeAction("slorii X16 X16 12 1796")
    tran0.writeAction("slorii X16 X16 12 372")
    tran0.writeAction("slorii X16 X16 12 1855")
    tran0.writeAction("slorii X16 X16 12 2540")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 21")
    tran0.writeAction("slorii X16 X16 12 1935")
    tran0.writeAction("slorii X16 X16 12 2583")
    tran0.writeAction("slorii X16 X16 12 1562")
    tran0.writeAction("slorii X16 X16 12 207")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 7")
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
    tran1 = state1.writeTransition("basic", state1, state2, 79)
    tran3 = state1.writeTransition("basic_with_action", state1, state2, 255)
    tran3.writeAction("movir X30 8")
    tran3.writeAction("movir X29 8")
    tran3.writeAction("movir X28 8")
    tran3.writeAction("movir X27 8")
    tran3.writeAction("movir X26 8")
    tran3.writeAction("movir X25 8")
    tran3.writeAction("movir X24 8")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("basic_with_action", state2, state2, 32)
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