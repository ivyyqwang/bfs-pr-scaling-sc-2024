from EFA_v2 import *
def basic_noaction4_with_lastact_TX_6():
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
    tran0.writeAction("movir X16 12390")
    tran0.writeAction("slorii X16 X16 12 666")
    tran0.writeAction("slorii X16 X16 12 3757")
    tran0.writeAction("slorii X16 X16 12 1224")
    tran0.writeAction("slorii X16 X16 12 2387")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 31670")
    tran0.writeAction("slorii X16 X16 12 1009")
    tran0.writeAction("slorii X16 X16 12 179")
    tran0.writeAction("slorii X16 X16 12 2370")
    tran0.writeAction("slorii X16 X16 12 1813")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 48792")
    tran0.writeAction("slorii X16 X16 12 3711")
    tran0.writeAction("slorii X16 X16 12 3832")
    tran0.writeAction("slorii X16 X16 12 218")
    tran0.writeAction("slorii X16 X16 12 332")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 12485")
    tran0.writeAction("slorii X16 X16 12 2945")
    tran0.writeAction("slorii X16 X16 12 1204")
    tran0.writeAction("slorii X16 X16 12 688")
    tran0.writeAction("slorii X16 X16 12 745")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 61852")
    tran0.writeAction("slorii X16 X16 12 1052")
    tran0.writeAction("slorii X16 X16 12 437")
    tran0.writeAction("slorii X16 X16 12 2653")
    tran0.writeAction("slorii X16 X16 12 398")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 18147")
    tran0.writeAction("slorii X16 X16 12 213")
    tran0.writeAction("slorii X16 X16 12 1348")
    tran0.writeAction("slorii X16 X16 12 2491")
    tran0.writeAction("slorii X16 X16 12 2413")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 6639")
    tran0.writeAction("slorii X16 X16 12 3424")
    tran0.writeAction("slorii X16 X16 12 104")
    tran0.writeAction("slorii X16 X16 12 2997")
    tran0.writeAction("slorii X16 X16 12 2310")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 46219")
    tran0.writeAction("slorii X16 X16 12 174")
    tran0.writeAction("slorii X16 X16 12 3680")
    tran0.writeAction("slorii X16 X16 12 3868")
    tran0.writeAction("slorii X16 X16 12 1286")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 12390")
    tran0.writeAction("slorii X16 X16 12 666")
    tran0.writeAction("slorii X16 X16 12 3757")
    tran0.writeAction("slorii X16 X16 12 1224")
    tran0.writeAction("slorii X16 X16 12 2387")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 5")
    tran0.writeAction("sli X17 X17 36")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 6")
    tran0.writeAction("sli X17 X17 32")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("add X7 X31 X31")
    tran0.writeAction("movir X20 0")
    tran0.writeAction("sli X31 X21 3")
    tran0.writeAction("add X21 X20 X5")
    tran0.writeAction("movlsb X31")
    tran0.writeAction("addi X20 X17 18")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("basic", state1, state2, 19)
    tran3 = state1.writeTransition("basic_with_action", state1, state2, 255)
    tran3.writeAction("addi X5 X16 8")
    tran3.writeAction("movir X30 8")
    tran3.writeAction("movir X29 8")
    tran3.writeAction("movir X28 8")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("basic_with_action", state2, state2, 5)
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
