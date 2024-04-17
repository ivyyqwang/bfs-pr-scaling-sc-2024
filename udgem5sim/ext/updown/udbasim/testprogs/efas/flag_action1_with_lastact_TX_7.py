from EFA_v2 import *
def flag_action1_with_lastact_TX_7():
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
    tran0.writeAction("movir X16 3284")
    tran0.writeAction("slorii X16 X16 12 1588")
    tran0.writeAction("slorii X16 X16 12 2026")
    tran0.writeAction("slorii X16 X16 12 2665")
    tran0.writeAction("slorii X16 X16 12 1591")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 56288")
    tran0.writeAction("slorii X16 X16 12 743")
    tran0.writeAction("slorii X16 X16 12 1986")
    tran0.writeAction("slorii X16 X16 12 1820")
    tran0.writeAction("slorii X16 X16 12 624")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 30397")
    tran0.writeAction("slorii X16 X16 12 2708")
    tran0.writeAction("slorii X16 X16 12 1799")
    tran0.writeAction("slorii X16 X16 12 1705")
    tran0.writeAction("slorii X16 X16 12 3253")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 56642")
    tran0.writeAction("slorii X16 X16 12 3052")
    tran0.writeAction("slorii X16 X16 12 4009")
    tran0.writeAction("slorii X16 X16 12 2543")
    tran0.writeAction("slorii X16 X16 12 3196")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 3859")
    tran0.writeAction("slorii X16 X16 12 2329")
    tran0.writeAction("slorii X16 X16 12 1745")
    tran0.writeAction("slorii X16 X16 12 1528")
    tran0.writeAction("slorii X16 X16 12 1200")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 30611")
    tran0.writeAction("slorii X16 X16 12 2367")
    tran0.writeAction("slorii X16 X16 12 1515")
    tran0.writeAction("slorii X16 X16 12 929")
    tran0.writeAction("slorii X16 X16 12 3016")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 19586")
    tran0.writeAction("slorii X16 X16 12 643")
    tran0.writeAction("slorii X16 X16 12 2541")
    tran0.writeAction("slorii X16 X16 12 3195")
    tran0.writeAction("slorii X16 X16 12 2967")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 18804")
    tran0.writeAction("slorii X16 X16 12 3036")
    tran0.writeAction("slorii X16 X16 12 3614")
    tran0.writeAction("slorii X16 X16 12 2522")
    tran0.writeAction("slorii X16 X16 12 1685")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 3284")
    tran0.writeAction("slorii X16 X16 12 1588")
    tran0.writeAction("slorii X16 X16 12 2026")
    tran0.writeAction("slorii X16 X16 12 2665")
    tran0.writeAction("slorii X16 X16 12 1591")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 4")
    tran0.writeAction("sli X17 X17 36")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 6")
    tran0.writeAction("sli X17 X17 32")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X20 0")
    tran0.writeAction("add X20 X7 X5")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("addi X20 X17 18")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("movir X16 219")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("flagCarry_with_action", state1, state2, 219)
    tran1.writeAction("movir X16 178")
    tran1.writeAction("lastact")
    tran3 = state1.writeTransition("flagCarry_with_action", state1, state2, 255)
    tran3.writeAction("movir X16 255")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("flagCarry_with_action", state2, state2, 178)
    tran2.writeAction("movir X31 7")
    tran2.writeAction("yieldt")
    tran4 = state2.writeTransition("flagCarry_with_action", state2, state1, 255)
    tran4.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa