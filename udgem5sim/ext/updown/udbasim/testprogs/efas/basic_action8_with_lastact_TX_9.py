from EFA_v2 import *
def basic_action8_with_lastact_TX_9():
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
    tran0.writeAction("movir X16 0")
    tran0.writeAction("slorii X16 X16 12 0")
    tran0.writeAction("slorii X16 X16 12 0")
    tran0.writeAction("slorii X16 X16 12 0")
    tran0.writeAction("slorii X16 X16 12 105")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 0")
    tran0.writeAction("slorii X16 X16 12 0")
    tran0.writeAction("slorii X16 X16 12 0")
    tran0.writeAction("slorii X16 X16 12 0")
    tran0.writeAction("slorii X16 X16 12 27")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 19525")
    tran0.writeAction("slorii X16 X16 12 76")
    tran0.writeAction("slorii X16 X16 12 1256")
    tran0.writeAction("slorii X16 X16 12 1193")
    tran0.writeAction("slorii X16 X16 12 2732")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 1536")
    tran0.writeAction("slorii X16 X16 12 352")
    tran0.writeAction("slorii X16 X16 12 3812")
    tran0.writeAction("slorii X16 X16 12 2589")
    tran0.writeAction("slorii X16 X16 12 2725")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 19716")
    tran0.writeAction("slorii X16 X16 12 3942")
    tran0.writeAction("slorii X16 X16 12 1237")
    tran0.writeAction("slorii X16 X16 12 3312")
    tran0.writeAction("slorii X16 X16 12 1226")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 27261")
    tran0.writeAction("slorii X16 X16 12 2358")
    tran0.writeAction("slorii X16 X16 12 217")
    tran0.writeAction("slorii X16 X16 12 3045")
    tran0.writeAction("slorii X16 X16 12 2805")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 1833")
    tran0.writeAction("slorii X16 X16 12 3646")
    tran0.writeAction("slorii X16 X16 12 3672")
    tran0.writeAction("slorii X16 X16 12 1085")
    tran0.writeAction("slorii X16 X16 12 744")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 13276")
    tran0.writeAction("slorii X16 X16 12 2946")
    tran0.writeAction("slorii X16 X16 12 1867")
    tran0.writeAction("slorii X16 X16 12 968")
    tran0.writeAction("slorii X16 X16 12 1801")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 0")
    tran0.writeAction("slorii X16 X16 12 0")
    tran0.writeAction("slorii X16 X16 12 0")
    tran0.writeAction("slorii X16 X16 12 0")
    tran0.writeAction("slorii X16 X16 12 105")
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
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("basic_with_action", state1, state2, 105)
    tran1.writeAction("addi X5 X16 0")
    tran1.writeAction("movir X30 7")
    tran1.writeAction("movir X29 7")
    tran1.writeAction("movir X28 7")
    tran1.writeAction("movir X27 7")
    tran1.writeAction("movir X26 7")
    tran1.writeAction("movir X25 7")
    tran1.writeAction("movir X24 7")
    tran1.writeAction("lastact")
    tran3 = state1.writeTransition("basic_with_action", state1, state2, 255)
    tran3.writeAction("movir X30 8")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("basic_with_action", state2, state2, 27)
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
