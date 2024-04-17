from EFA_v2 import *
def flag_action2_with_lastact_TX_14():
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
    tran0.writeAction("movir X16 22432")
    tran0.writeAction("slorii X16 X16 12 3399")
    tran0.writeAction("slorii X16 X16 12 1868")
    tran0.writeAction("slorii X16 X16 12 3990")
    tran0.writeAction("slorii X16 X16 12 3703")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 19157")
    tran0.writeAction("slorii X16 X16 12 641")
    tran0.writeAction("slorii X16 X16 12 1105")
    tran0.writeAction("slorii X16 X16 12 379")
    tran0.writeAction("slorii X16 X16 12 3371")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 56602")
    tran0.writeAction("slorii X16 X16 12 2893")
    tran0.writeAction("slorii X16 X16 12 755")
    tran0.writeAction("slorii X16 X16 12 3287")
    tran0.writeAction("slorii X16 X16 12 980")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 14210")
    tran0.writeAction("slorii X16 X16 12 1815")
    tran0.writeAction("slorii X16 X16 12 384")
    tran0.writeAction("slorii X16 X16 12 2885")
    tran0.writeAction("slorii X16 X16 12 3573")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 4965")
    tran0.writeAction("slorii X16 X16 12 3656")
    tran0.writeAction("slorii X16 X16 12 1864")
    tran0.writeAction("slorii X16 X16 12 1735")
    tran0.writeAction("slorii X16 X16 12 14")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 7991")
    tran0.writeAction("slorii X16 X16 12 694")
    tran0.writeAction("slorii X16 X16 12 2284")
    tran0.writeAction("slorii X16 X16 12 1736")
    tran0.writeAction("slorii X16 X16 12 2419")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 56096")
    tran0.writeAction("slorii X16 X16 12 3985")
    tran0.writeAction("slorii X16 X16 12 72")
    tran0.writeAction("slorii X16 X16 12 4015")
    tran0.writeAction("slorii X16 X16 12 973")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 14720")
    tran0.writeAction("slorii X16 X16 12 2233")
    tran0.writeAction("slorii X16 X16 12 2643")
    tran0.writeAction("slorii X16 X16 12 2042")
    tran0.writeAction("slorii X16 X16 12 48")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 22432")
    tran0.writeAction("slorii X16 X16 12 3399")
    tran0.writeAction("slorii X16 X16 12 1868")
    tran0.writeAction("slorii X16 X16 12 3990")
    tran0.writeAction("slorii X16 X16 12 3703")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 2")
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
    tran0.writeAction("movir X16 206")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("flagCarry_with_action", state1, state2, 206)
    tran1.writeAction("movir X16 12")
    tran1.writeAction("movir X30 7")
    tran1.writeAction("lastact")
    tran3 = state1.writeTransition("flagCarry_with_action", state1, state2, 255)
    tran3.writeAction("movir X16 255")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("flagCarry_with_action", state2, state2, 12)
    tran2.writeAction("addi X5 X17 0")
    tran2.writeAction("movir X31 7")
    tran2.writeAction("yieldt")
    tran4 = state2.writeTransition("flagCarry_with_action", state2, state1, 255)
    tran4.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa