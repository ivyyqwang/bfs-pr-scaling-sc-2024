from EFA_v2 import *
def flag_noaction1_with_lastact_TX_8():
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
    tran0.writeAction("movir X16 45784")
    tran0.writeAction("slorii X16 X16 12 1603")
    tran0.writeAction("slorii X16 X16 12 1913")
    tran0.writeAction("slorii X16 X16 12 1903")
    tran0.writeAction("slorii X16 X16 12 1824")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 49337")
    tran0.writeAction("slorii X16 X16 12 2565")
    tran0.writeAction("slorii X16 X16 12 2312")
    tran0.writeAction("slorii X16 X16 12 1891")
    tran0.writeAction("slorii X16 X16 12 143")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 43218")
    tran0.writeAction("slorii X16 X16 12 1178")
    tran0.writeAction("slorii X16 X16 12 4091")
    tran0.writeAction("slorii X16 X16 12 2418")
    tran0.writeAction("slorii X16 X16 12 1772")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 26607")
    tran0.writeAction("slorii X16 X16 12 79")
    tran0.writeAction("slorii X16 X16 12 2850")
    tran0.writeAction("slorii X16 X16 12 864")
    tran0.writeAction("slorii X16 X16 12 3761")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 41196")
    tran0.writeAction("slorii X16 X16 12 1415")
    tran0.writeAction("slorii X16 X16 12 2064")
    tran0.writeAction("slorii X16 X16 12 1334")
    tran0.writeAction("slorii X16 X16 12 1859")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 36355")
    tran0.writeAction("slorii X16 X16 12 1578")
    tran0.writeAction("slorii X16 X16 12 1488")
    tran0.writeAction("slorii X16 X16 12 2932")
    tran0.writeAction("slorii X16 X16 12 3082")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 51527")
    tran0.writeAction("slorii X16 X16 12 542")
    tran0.writeAction("slorii X16 X16 12 1899")
    tran0.writeAction("slorii X16 X16 12 3119")
    tran0.writeAction("slorii X16 X16 12 1643")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 58899")
    tran0.writeAction("slorii X16 X16 12 536")
    tran0.writeAction("slorii X16 X16 12 2635")
    tran0.writeAction("slorii X16 X16 12 2407")
    tran0.writeAction("slorii X16 X16 12 1313")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 45784")
    tran0.writeAction("slorii X16 X16 12 1603")
    tran0.writeAction("slorii X16 X16 12 1913")
    tran0.writeAction("slorii X16 X16 12 1903")
    tran0.writeAction("slorii X16 X16 12 1824")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 4")
    tran0.writeAction("sli X17 X17 36")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 5")
    tran0.writeAction("sli X17 X17 32")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X20 0")
    tran0.writeAction("add X20 X7 X5")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("addi X20 X17 15")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("movir X16 105")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("flagCarry", state1, state2, 105)
    tran3 = state1.writeTransition("flagCarry_with_action", state1, state2, 255)
    tran3.writeAction("movir X16 255")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("flagCarry_with_action", state2, state2, 105)
    tran2.writeAction("movir X31 7")
    tran2.writeAction("yieldt")
    tran4 = state2.writeTransition("flagCarry_with_action", state2, state1, 255)
    tran4.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa
