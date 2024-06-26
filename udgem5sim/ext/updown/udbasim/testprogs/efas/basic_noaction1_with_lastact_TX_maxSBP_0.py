from EFA_v2 import *
def basic_noaction1_with_lastact_TX_maxSBP_0():
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
    tran0.writeAction("movir X16 15284")
    tran0.writeAction("slorii X16 X16 12 2883")
    tran0.writeAction("slorii X16 X16 12 742")
    tran0.writeAction("slorii X16 X16 12 2828")
    tran0.writeAction("slorii X16 X16 12 1298")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 4844")
    tran0.writeAction("slorii X16 X16 12 591")
    tran0.writeAction("slorii X16 X16 12 2050")
    tran0.writeAction("slorii X16 X16 12 1315")
    tran0.writeAction("slorii X16 X16 12 1490")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 44972")
    tran0.writeAction("slorii X16 X16 12 4041")
    tran0.writeAction("slorii X16 X16 12 3190")
    tran0.writeAction("slorii X16 X16 12 3064")
    tran0.writeAction("slorii X16 X16 12 3363")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 54159")
    tran0.writeAction("slorii X16 X16 12 1824")
    tran0.writeAction("slorii X16 X16 12 1818")
    tran0.writeAction("slorii X16 X16 12 281")
    tran0.writeAction("slorii X16 X16 12 3314")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 26089")
    tran0.writeAction("slorii X16 X16 12 3856")
    tran0.writeAction("slorii X16 X16 12 1329")
    tran0.writeAction("slorii X16 X16 12 3887")
    tran0.writeAction("slorii X16 X16 12 2088")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 63457")
    tran0.writeAction("slorii X16 X16 12 3544")
    tran0.writeAction("slorii X16 X16 12 3984")
    tran0.writeAction("slorii X16 X16 12 1928")
    tran0.writeAction("slorii X16 X16 12 1310")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 746")
    tran0.writeAction("slorii X16 X16 12 1177")
    tran0.writeAction("slorii X16 X16 12 2781")
    tran0.writeAction("slorii X16 X16 12 1787")
    tran0.writeAction("slorii X16 X16 12 1813")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 18042")
    tran0.writeAction("slorii X16 X16 12 99")
    tran0.writeAction("slorii X16 X16 12 329")
    tran0.writeAction("slorii X16 X16 12 3942")
    tran0.writeAction("slorii X16 X16 12 298")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 15284")
    tran0.writeAction("slorii X16 X16 12 2883")
    tran0.writeAction("slorii X16 X16 12 742")
    tran0.writeAction("slorii X16 X16 12 2828")
    tran0.writeAction("slorii X16 X16 12 1298")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 8")
    tran0.writeAction("sli X17 X17 36")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 8")
    tran0.writeAction("sli X17 X17 32")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("add X7 X31 X31")
    tran0.writeAction("movir X20 0")
    tran0.writeAction("sli X31 X21 3")
    tran0.writeAction("add X21 X20 X5")
    tran0.writeAction("movlsb X31")
    tran0.writeAction("addi X20 X17 8")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("basic", state1, state2, 18)
    tran3 = state1.writeTransition("basic_with_action", state1, state2, 255)
    tran3.writeAction("movir X30 8")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("basic", state2, state2, 197)
    tran4 = state2.writeTransition("basic_with_action", state2, state1, 255)
    tran4.writeAction("addi X5 X17 0")
    tran4.writeAction("movir X31 8")
    tran4.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa
