from EFA_v2 import *
def basic_action2_without_lastact_TX_7():
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
    tran0.writeAction("movir X16 39660")
    tran0.writeAction("slorii X16 X16 12 1689")
    tran0.writeAction("slorii X16 X16 12 2349")
    tran0.writeAction("slorii X16 X16 12 1341")
    tran0.writeAction("slorii X16 X16 12 3694")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 3617")
    tran0.writeAction("slorii X16 X16 12 3103")
    tran0.writeAction("slorii X16 X16 12 251")
    tran0.writeAction("slorii X16 X16 12 1005")
    tran0.writeAction("slorii X16 X16 12 1142")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 22320")
    tran0.writeAction("slorii X16 X16 12 1235")
    tran0.writeAction("slorii X16 X16 12 467")
    tran0.writeAction("slorii X16 X16 12 3903")
    tran0.writeAction("slorii X16 X16 12 1488")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 35771")
    tran0.writeAction("slorii X16 X16 12 3764")
    tran0.writeAction("slorii X16 X16 12 2351")
    tran0.writeAction("slorii X16 X16 12 1434")
    tran0.writeAction("slorii X16 X16 12 3081")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 13429")
    tran0.writeAction("slorii X16 X16 12 3529")
    tran0.writeAction("slorii X16 X16 12 455")
    tran0.writeAction("slorii X16 X16 12 3996")
    tran0.writeAction("slorii X16 X16 12 1325")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 1941")
    tran0.writeAction("slorii X16 X16 12 2880")
    tran0.writeAction("slorii X16 X16 12 2203")
    tran0.writeAction("slorii X16 X16 12 2476")
    tran0.writeAction("slorii X16 X16 12 692")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 30051")
    tran0.writeAction("slorii X16 X16 12 4017")
    tran0.writeAction("slorii X16 X16 12 2007")
    tran0.writeAction("slorii X16 X16 12 1817")
    tran0.writeAction("slorii X16 X16 12 1603")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 37082")
    tran0.writeAction("slorii X16 X16 12 3259")
    tran0.writeAction("slorii X16 X16 12 619")
    tran0.writeAction("slorii X16 X16 12 1058")
    tran0.writeAction("slorii X16 X16 12 250")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 39660")
    tran0.writeAction("slorii X16 X16 12 1689")
    tran0.writeAction("slorii X16 X16 12 2349")
    tran0.writeAction("slorii X16 X16 12 1341")
    tran0.writeAction("slorii X16 X16 12 3694")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 7")
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
    tran0.writeAction("addi X20 X17 24")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("basic_with_action", state1, state2, 110)
    tran1.writeAction("addi X5 X16 0")
    tran1.writeAction("movir X30 5")
    tran3 = state1.writeTransition("basic_with_action", state1, state2, 255)
    tran3.writeAction("addi X5 X16 0")
    tran3.writeAction("movir X30 6")
    tran2 = state2.writeTransition("basic_with_action", state2, state2, 94)
    tran2.writeAction("addi X5 X17 0")
    tran2.writeAction("movir X31 5")
    tran2.writeAction("yieldt")
    tran4 = state2.writeTransition("basic_with_action", state2, state1, 255)
    tran4.writeAction("addi X5 X17 0")
    tran4.writeAction("movir X31 6")
    tran4.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa
