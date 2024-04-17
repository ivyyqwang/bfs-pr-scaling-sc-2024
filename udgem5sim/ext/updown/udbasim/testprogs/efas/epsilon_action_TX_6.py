from EFA_v2 import *
def epsilon_action_TX_6():
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
    tran0 = state.writeTransition("epsilonCarry_with_action", state, state1, 1)
    tran0.writeAction("movir X17 0")
    tran0.writeAction("add X7 X17 X17")
    tran0.writeAction("movir X16 23765")
    tran0.writeAction("slorii X16 X16 12 1741")
    tran0.writeAction("slorii X16 X16 12 3886")
    tran0.writeAction("slorii X16 X16 12 2096")
    tran0.writeAction("slorii X16 X16 12 3727")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 811")
    tran0.writeAction("slorii X16 X16 12 1310")
    tran0.writeAction("slorii X16 X16 12 953")
    tran0.writeAction("slorii X16 X16 12 1713")
    tran0.writeAction("slorii X16 X16 12 2474")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 58156")
    tran0.writeAction("slorii X16 X16 12 1302")
    tran0.writeAction("slorii X16 X16 12 2426")
    tran0.writeAction("slorii X16 X16 12 2650")
    tran0.writeAction("slorii X16 X16 12 560")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 179")
    tran0.writeAction("slorii X16 X16 12 3630")
    tran0.writeAction("slorii X16 X16 12 638")
    tran0.writeAction("slorii X16 X16 12 1645")
    tran0.writeAction("slorii X16 X16 12 3020")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 16917")
    tran0.writeAction("slorii X16 X16 12 1406")
    tran0.writeAction("slorii X16 X16 12 811")
    tran0.writeAction("slorii X16 X16 12 3737")
    tran0.writeAction("slorii X16 X16 12 1999")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 45815")
    tran0.writeAction("slorii X16 X16 12 2839")
    tran0.writeAction("slorii X16 X16 12 1134")
    tran0.writeAction("slorii X16 X16 12 1165")
    tran0.writeAction("slorii X16 X16 12 2376")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 22148")
    tran0.writeAction("slorii X16 X16 12 2249")
    tran0.writeAction("slorii X16 X16 12 3119")
    tran0.writeAction("slorii X16 X16 12 3170")
    tran0.writeAction("slorii X16 X16 12 93")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 6739")
    tran0.writeAction("slorii X16 X16 12 3499")
    tran0.writeAction("slorii X16 X16 12 1592")
    tran0.writeAction("slorii X16 X16 12 867")
    tran0.writeAction("slorii X16 X16 12 632")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 23765")
    tran0.writeAction("slorii X16 X16 12 1741")
    tran0.writeAction("slorii X16 X16 12 3886")
    tran0.writeAction("slorii X16 X16 12 2096")
    tran0.writeAction("slorii X16 X16 12 3727")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 2")
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
    tran0.writeAction("addi X20 X17 24")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("epsilonCarry_with_action", state1, state2, 0)
    tran1.writeAction("addi X5 X16 0")
    tran1.writeAction("movir X30 3")
    tran1.writeAction("lastact")
    tran2 = state2.writeTransition("epsilonCarry_with_action", state2, state2, 0)
    tran2.writeAction("addi X5 X17 0")
    tran2.writeAction("movir X31 4")
    tran2.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa
