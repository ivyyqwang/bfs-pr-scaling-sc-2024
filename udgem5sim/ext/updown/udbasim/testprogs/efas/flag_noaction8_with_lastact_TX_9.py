from EFA_v2 import *
def flag_noaction8_with_lastact_TX_9():
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
    tran0.writeAction("movir X16 29203")
    tran0.writeAction("slorii X16 X16 12 4090")
    tran0.writeAction("slorii X16 X16 12 1867")
    tran0.writeAction("slorii X16 X16 12 2856")
    tran0.writeAction("slorii X16 X16 12 1488")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 29342")
    tran0.writeAction("slorii X16 X16 12 3439")
    tran0.writeAction("slorii X16 X16 12 1696")
    tran0.writeAction("slorii X16 X16 12 3101")
    tran0.writeAction("slorii X16 X16 12 3196")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 35529")
    tran0.writeAction("slorii X16 X16 12 1704")
    tran0.writeAction("slorii X16 X16 12 1034")
    tran0.writeAction("slorii X16 X16 12 2874")
    tran0.writeAction("slorii X16 X16 12 1715")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 34535")
    tran0.writeAction("slorii X16 X16 12 38")
    tran0.writeAction("slorii X16 X16 12 4038")
    tran0.writeAction("slorii X16 X16 12 2100")
    tran0.writeAction("slorii X16 X16 12 701")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 44100")
    tran0.writeAction("slorii X16 X16 12 3698")
    tran0.writeAction("slorii X16 X16 12 2873")
    tran0.writeAction("slorii X16 X16 12 3740")
    tran0.writeAction("slorii X16 X16 12 614")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 49714")
    tran0.writeAction("slorii X16 X16 12 803")
    tran0.writeAction("slorii X16 X16 12 3233")
    tran0.writeAction("slorii X16 X16 12 1979")
    tran0.writeAction("slorii X16 X16 12 2812")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 7805")
    tran0.writeAction("slorii X16 X16 12 1056")
    tran0.writeAction("slorii X16 X16 12 3661")
    tran0.writeAction("slorii X16 X16 12 1402")
    tran0.writeAction("slorii X16 X16 12 3771")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 3280")
    tran0.writeAction("slorii X16 X16 12 3214")
    tran0.writeAction("slorii X16 X16 12 2476")
    tran0.writeAction("slorii X16 X16 12 3122")
    tran0.writeAction("slorii X16 X16 12 550")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 29203")
    tran0.writeAction("slorii X16 X16 12 4090")
    tran0.writeAction("slorii X16 X16 12 1867")
    tran0.writeAction("slorii X16 X16 12 2856")
    tran0.writeAction("slorii X16 X16 12 1488")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 4")
    tran0.writeAction("sli X17 X17 36")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 5")
    tran0.writeAction("sli X17 X17 32")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("add X7 X31 X31")
    tran0.writeAction("movir X20 0")
    tran0.writeAction("sli X31 X21 3")
    tran0.writeAction("add X21 X20 X5")
    tran0.writeAction("movlsb X31")
    tran0.writeAction("addi X20 X17 15")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("movir X16 231")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("flagCarry", state1, state2, 231)
    tran3 = state1.writeTransition("flagCarry_with_action", state1, state2, 255)
    tran3.writeAction("movir X16 255")
    tran3.writeAction("movir X30 8")
    tran3.writeAction("movir X30 9")
    tran3.writeAction("movir X30 10")
    tran3.writeAction("movir X30 11")
    tran3.writeAction("movir X30 12")
    tran3.writeAction("movir X30 13")
    tran3.writeAction("lastact")
    tran2 = state2.writeTransition("flagCarry_with_action", state2, state2, 231)
    tran2.writeAction("addi X5 X17 0")
    tran2.writeAction("movir X31 7")
    tran2.writeAction("movir X31 8")
    tran2.writeAction("movir X31 9")
    tran2.writeAction("movir X31 10")
    tran2.writeAction("movir X31 11")
    tran2.writeAction("movir X31 12")
    tran2.writeAction("movir X31 13")
    tran2.writeAction("yieldt")
    tran4 = state2.writeTransition("flagCarry_with_action", state2, state1, 255)
    tran4.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa
