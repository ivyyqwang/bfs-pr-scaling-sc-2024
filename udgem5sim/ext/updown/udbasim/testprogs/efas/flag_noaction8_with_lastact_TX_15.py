from EFA_v2 import *
def flag_noaction8_with_lastact_TX_15():
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
    tran0.writeAction("movir X16 30633")
    tran0.writeAction("slorii X16 X16 12 2873")
    tran0.writeAction("slorii X16 X16 12 838")
    tran0.writeAction("slorii X16 X16 12 2247")
    tran0.writeAction("slorii X16 X16 12 1827")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 52088")
    tran0.writeAction("slorii X16 X16 12 861")
    tran0.writeAction("slorii X16 X16 12 3891")
    tran0.writeAction("slorii X16 X16 12 847")
    tran0.writeAction("slorii X16 X16 12 1468")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 22310")
    tran0.writeAction("slorii X16 X16 12 1130")
    tran0.writeAction("slorii X16 X16 12 501")
    tran0.writeAction("slorii X16 X16 12 826")
    tran0.writeAction("slorii X16 X16 12 3073")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 12907")
    tran0.writeAction("slorii X16 X16 12 2003")
    tran0.writeAction("slorii X16 X16 12 44")
    tran0.writeAction("slorii X16 X16 12 1309")
    tran0.writeAction("slorii X16 X16 12 38")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 5788")
    tran0.writeAction("slorii X16 X16 12 2832")
    tran0.writeAction("slorii X16 X16 12 3911")
    tran0.writeAction("slorii X16 X16 12 3905")
    tran0.writeAction("slorii X16 X16 12 1701")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 44405")
    tran0.writeAction("slorii X16 X16 12 1314")
    tran0.writeAction("slorii X16 X16 12 2477")
    tran0.writeAction("slorii X16 X16 12 1135")
    tran0.writeAction("slorii X16 X16 12 969")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 9714")
    tran0.writeAction("slorii X16 X16 12 3198")
    tran0.writeAction("slorii X16 X16 12 1927")
    tran0.writeAction("slorii X16 X16 12 2129")
    tran0.writeAction("slorii X16 X16 12 1606")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 19075")
    tran0.writeAction("slorii X16 X16 12 1732")
    tran0.writeAction("slorii X16 X16 12 3854")
    tran0.writeAction("slorii X16 X16 12 2942")
    tran0.writeAction("slorii X16 X16 12 3978")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 30633")
    tran0.writeAction("slorii X16 X16 12 2873")
    tran0.writeAction("slorii X16 X16 12 838")
    tran0.writeAction("slorii X16 X16 12 2247")
    tran0.writeAction("slorii X16 X16 12 1827")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 6")
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
    tran0.writeAction("movir X16 55")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("flagCarry", state1, state2, 55)
    tran3 = state1.writeTransition("flagCarry_with_action", state1, state2, 255)
    tran3.writeAction("movir X16 255")
    tran3.writeAction("movir X30 8")
    tran3.writeAction("movir X30 9")
    tran3.writeAction("movir X30 10")
    tran3.writeAction("movir X30 11")
    tran3.writeAction("movir X30 12")
    tran3.writeAction("movir X30 13")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("flagCarry_with_action", state2, state2, 55)
    tran2.writeAction("addi X5 X17 0")
    tran2.writeAction("movir X31 7")
    tran2.writeAction("movir X31 8")
    tran2.writeAction("movir X31 9")
    tran2.writeAction("movir X31 10")
    tran2.writeAction("movir X31 11")
    tran2.writeAction("movir X31 12")
    tran2.writeAction("movir X31 13")
    tran2.writeAction("yieldt")
    tran4 = state2.writeTransition("flagCarry_with_action", state2, state1, 255)
    tran4.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa
