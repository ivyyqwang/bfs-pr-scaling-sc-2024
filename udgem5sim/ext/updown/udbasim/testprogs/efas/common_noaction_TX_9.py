from EFA_v2 import *
def common_noaction_TX_9():
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
    tran0 = state.writeTransition("commonCarry_with_action", state, state1, 1)
    tran0.writeAction("movir X17 0")
    tran0.writeAction("add X7 X17 X17")
    tran0.writeAction("movir X16 53722")
    tran0.writeAction("slorii X16 X16 12 3506")
    tran0.writeAction("slorii X16 X16 12 265")
    tran0.writeAction("slorii X16 X16 12 3406")
    tran0.writeAction("slorii X16 X16 12 284")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 22231")
    tran0.writeAction("slorii X16 X16 12 1437")
    tran0.writeAction("slorii X16 X16 12 367")
    tran0.writeAction("slorii X16 X16 12 746")
    tran0.writeAction("slorii X16 X16 12 1631")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 42743")
    tran0.writeAction("slorii X16 X16 12 2068")
    tran0.writeAction("slorii X16 X16 12 3485")
    tran0.writeAction("slorii X16 X16 12 3811")
    tran0.writeAction("slorii X16 X16 12 761")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 16560")
    tran0.writeAction("slorii X16 X16 12 2140")
    tran0.writeAction("slorii X16 X16 12 1215")
    tran0.writeAction("slorii X16 X16 12 2573")
    tran0.writeAction("slorii X16 X16 12 20")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 61120")
    tran0.writeAction("slorii X16 X16 12 2263")
    tran0.writeAction("slorii X16 X16 12 2551")
    tran0.writeAction("slorii X16 X16 12 1865")
    tran0.writeAction("slorii X16 X16 12 3344")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 29639")
    tran0.writeAction("slorii X16 X16 12 848")
    tran0.writeAction("slorii X16 X16 12 1676")
    tran0.writeAction("slorii X16 X16 12 3491")
    tran0.writeAction("slorii X16 X16 12 1870")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 6056")
    tran0.writeAction("slorii X16 X16 12 742")
    tran0.writeAction("slorii X16 X16 12 278")
    tran0.writeAction("slorii X16 X16 12 1292")
    tran0.writeAction("slorii X16 X16 12 163")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 47124")
    tran0.writeAction("slorii X16 X16 12 2995")
    tran0.writeAction("slorii X16 X16 12 1774")
    tran0.writeAction("slorii X16 X16 12 3012")
    tran0.writeAction("slorii X16 X16 12 2263")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 53722")
    tran0.writeAction("slorii X16 X16 12 3506")
    tran0.writeAction("slorii X16 X16 12 265")
    tran0.writeAction("slorii X16 X16 12 3406")
    tran0.writeAction("slorii X16 X16 12 284")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 4")
    tran0.writeAction("sli X17 X17 36")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 7")
    tran0.writeAction("sli X17 X17 32")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("add X7 X31 X31")
    tran0.writeAction("movir X20 0")
    tran0.writeAction("sli X31 X21 3")
    tran0.writeAction("add X21 X20 X5")
    tran0.writeAction("movlsb X31")
    tran0.writeAction("addi X20 X17 21")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("movir X30 0")
    tran0.writeAction("movir X31 0")
    tran0.writeAction("lastact")
    tran1 = state1.writeTransition("commonCarry", state1, state2, 0)
    tran2 = state2.writeTransition("commonCarry_with_action", state2, state2, 0)
    tran2.writeAction("addi X5 X17 0")
    tran2.writeAction("movir X31 2")
    tran2.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa
