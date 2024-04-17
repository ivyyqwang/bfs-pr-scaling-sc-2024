from EFA_v2 import *
def flag_noaction4_with_lastact_TX_17():
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
    tran0.writeAction("movir X16 65257")
    tran0.writeAction("slorii X16 X16 12 2786")
    tran0.writeAction("slorii X16 X16 12 3414")
    tran0.writeAction("slorii X16 X16 12 206")
    tran0.writeAction("slorii X16 X16 12 1175")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 42943")
    tran0.writeAction("slorii X16 X16 12 2604")
    tran0.writeAction("slorii X16 X16 12 1623")
    tran0.writeAction("slorii X16 X16 12 2015")
    tran0.writeAction("slorii X16 X16 12 459")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 51954")
    tran0.writeAction("slorii X16 X16 12 3013")
    tran0.writeAction("slorii X16 X16 12 1429")
    tran0.writeAction("slorii X16 X16 12 1075")
    tran0.writeAction("slorii X16 X16 12 990")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 17096")
    tran0.writeAction("slorii X16 X16 12 3901")
    tran0.writeAction("slorii X16 X16 12 75")
    tran0.writeAction("slorii X16 X16 12 640")
    tran0.writeAction("slorii X16 X16 12 3500")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 41154")
    tran0.writeAction("slorii X16 X16 12 3230")
    tran0.writeAction("slorii X16 X16 12 278")
    tran0.writeAction("slorii X16 X16 12 219")
    tran0.writeAction("slorii X16 X16 12 3921")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 50092")
    tran0.writeAction("slorii X16 X16 12 3300")
    tran0.writeAction("slorii X16 X16 12 4028")
    tran0.writeAction("slorii X16 X16 12 1114")
    tran0.writeAction("slorii X16 X16 12 800")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 45761")
    tran0.writeAction("slorii X16 X16 12 2301")
    tran0.writeAction("slorii X16 X16 12 2714")
    tran0.writeAction("slorii X16 X16 12 3296")
    tran0.writeAction("slorii X16 X16 12 564")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 23776")
    tran0.writeAction("slorii X16 X16 12 3774")
    tran0.writeAction("slorii X16 X16 12 2948")
    tran0.writeAction("slorii X16 X16 12 2913")
    tran0.writeAction("slorii X16 X16 12 1985")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 65257")
    tran0.writeAction("slorii X16 X16 12 2786")
    tran0.writeAction("slorii X16 X16 12 3414")
    tran0.writeAction("slorii X16 X16 12 206")
    tran0.writeAction("slorii X16 X16 12 1175")
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
    tran0.writeAction("movir X16 76")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("flagCarry", state1, state2, 76)
    tran3 = state1.writeTransition("flagCarry_with_action", state1, state2, 255)
    tran3.writeAction("movir X16 255")
    tran3.writeAction("movir X30 8")
    tran3.writeAction("movir X30 9")
    tran3.writeAction("movir X30 10")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("flagCarry_with_action", state2, state2, 76)
    tran2.writeAction("addi X5 X17 0")
    tran2.writeAction("movir X31 7")
    tran2.writeAction("movir X31 8")
    tran2.writeAction("movir X31 9")
    tran2.writeAction("yieldt")
    tran4 = state2.writeTransition("flagCarry_with_action", state2, state1, 255)
    tran4.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa