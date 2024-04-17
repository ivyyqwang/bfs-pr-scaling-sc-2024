from EFA_v2 import *
def epsilon_noaction_TX_9():
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
    tran0.writeAction("movir X16 21656")
    tran0.writeAction("slorii X16 X16 12 1286")
    tran0.writeAction("slorii X16 X16 12 2844")
    tran0.writeAction("slorii X16 X16 12 2938")
    tran0.writeAction("slorii X16 X16 12 2514")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 3117")
    tran0.writeAction("slorii X16 X16 12 3392")
    tran0.writeAction("slorii X16 X16 12 1452")
    tran0.writeAction("slorii X16 X16 12 1307")
    tran0.writeAction("slorii X16 X16 12 3511")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 18193")
    tran0.writeAction("slorii X16 X16 12 3630")
    tran0.writeAction("slorii X16 X16 12 4042")
    tran0.writeAction("slorii X16 X16 12 3011")
    tran0.writeAction("slorii X16 X16 12 2390")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 52801")
    tran0.writeAction("slorii X16 X16 12 4016")
    tran0.writeAction("slorii X16 X16 12 1412")
    tran0.writeAction("slorii X16 X16 12 321")
    tran0.writeAction("slorii X16 X16 12 906")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 34489")
    tran0.writeAction("slorii X16 X16 12 2052")
    tran0.writeAction("slorii X16 X16 12 1194")
    tran0.writeAction("slorii X16 X16 12 1853")
    tran0.writeAction("slorii X16 X16 12 2723")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 310")
    tran0.writeAction("slorii X16 X16 12 3300")
    tran0.writeAction("slorii X16 X16 12 2088")
    tran0.writeAction("slorii X16 X16 12 3126")
    tran0.writeAction("slorii X16 X16 12 490")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 14962")
    tran0.writeAction("slorii X16 X16 12 3602")
    tran0.writeAction("slorii X16 X16 12 161")
    tran0.writeAction("slorii X16 X16 12 415")
    tran0.writeAction("slorii X16 X16 12 1406")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 36832")
    tran0.writeAction("slorii X16 X16 12 511")
    tran0.writeAction("slorii X16 X16 12 4073")
    tran0.writeAction("slorii X16 X16 12 3189")
    tran0.writeAction("slorii X16 X16 12 249")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 21656")
    tran0.writeAction("slorii X16 X16 12 1286")
    tran0.writeAction("slorii X16 X16 12 2844")
    tran0.writeAction("slorii X16 X16 12 2938")
    tran0.writeAction("slorii X16 X16 12 2514")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 1")
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
    tran1 = state1.writeTransition("epsilonCarry", state1, state2, 0)
    tran2 = state2.writeTransition("epsilonCarry_with_action", state2, state2, 0)
    tran2.writeAction("addi X5 X17 0")
    tran2.writeAction("movir X31 4")
    tran2.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa
