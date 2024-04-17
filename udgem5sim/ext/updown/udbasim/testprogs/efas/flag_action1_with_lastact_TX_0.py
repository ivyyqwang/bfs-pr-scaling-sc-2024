from EFA_v2 import *
def flag_action1_with_lastact_TX_0():
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
    tran0.writeAction("movir X16 35953")
    tran0.writeAction("slorii X16 X16 12 219")
    tran0.writeAction("slorii X16 X16 12 2702")
    tran0.writeAction("slorii X16 X16 12 209")
    tran0.writeAction("slorii X16 X16 12 1268")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 48464")
    tran0.writeAction("slorii X16 X16 12 1267")
    tran0.writeAction("slorii X16 X16 12 3707")
    tran0.writeAction("slorii X16 X16 12 1493")
    tran0.writeAction("slorii X16 X16 12 4074")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 32187")
    tran0.writeAction("slorii X16 X16 12 2773")
    tran0.writeAction("slorii X16 X16 12 3683")
    tran0.writeAction("slorii X16 X16 12 1357")
    tran0.writeAction("slorii X16 X16 12 1239")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 49353")
    tran0.writeAction("slorii X16 X16 12 3412")
    tran0.writeAction("slorii X16 X16 12 618")
    tran0.writeAction("slorii X16 X16 12 1322")
    tran0.writeAction("slorii X16 X16 12 1467")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 44622")
    tran0.writeAction("slorii X16 X16 12 1424")
    tran0.writeAction("slorii X16 X16 12 933")
    tran0.writeAction("slorii X16 X16 12 2838")
    tran0.writeAction("slorii X16 X16 12 2125")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 34748")
    tran0.writeAction("slorii X16 X16 12 2391")
    tran0.writeAction("slorii X16 X16 12 313")
    tran0.writeAction("slorii X16 X16 12 2829")
    tran0.writeAction("slorii X16 X16 12 3613")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 65199")
    tran0.writeAction("slorii X16 X16 12 3116")
    tran0.writeAction("slorii X16 X16 12 3922")
    tran0.writeAction("slorii X16 X16 12 2638")
    tran0.writeAction("slorii X16 X16 12 144")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 35896")
    tran0.writeAction("slorii X16 X16 12 2560")
    tran0.writeAction("slorii X16 X16 12 1906")
    tran0.writeAction("slorii X16 X16 12 3721")
    tran0.writeAction("slorii X16 X16 12 1342")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 35953")
    tran0.writeAction("slorii X16 X16 12 219")
    tran0.writeAction("slorii X16 X16 12 2702")
    tran0.writeAction("slorii X16 X16 12 209")
    tran0.writeAction("slorii X16 X16 12 1268")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 8")
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
    tran0.writeAction("movir X16 31")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("flagCarry_with_action", state1, state2, 31)
    tran1.writeAction("movir X16 71")
    tran1.writeAction("lastact")
    tran3 = state1.writeTransition("flagCarry_with_action", state1, state2, 255)
    tran3.writeAction("movir X16 255")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("flagCarry_with_action", state2, state2, 71)
    tran2.writeAction("movir X31 7")
    tran2.writeAction("yieldt")
    tran4 = state2.writeTransition("flagCarry_with_action", state2, state1, 255)
    tran4.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa