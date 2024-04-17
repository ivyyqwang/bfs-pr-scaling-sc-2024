from EFA_v2 import *
def common_event_common_TX_10():
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
    tran0.writeAction("movir X16 10866")
    tran0.writeAction("slorii X16 X16 12 1443")
    tran0.writeAction("slorii X16 X16 12 4050")
    tran0.writeAction("slorii X16 X16 12 1754")
    tran0.writeAction("slorii X16 X16 12 3352")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 43112")
    tran0.writeAction("slorii X16 X16 12 2605")
    tran0.writeAction("slorii X16 X16 12 3258")
    tran0.writeAction("slorii X16 X16 12 1110")
    tran0.writeAction("slorii X16 X16 12 2740")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 45710")
    tran0.writeAction("slorii X16 X16 12 1889")
    tran0.writeAction("slorii X16 X16 12 353")
    tran0.writeAction("slorii X16 X16 12 1865")
    tran0.writeAction("slorii X16 X16 12 2772")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 41315")
    tran0.writeAction("slorii X16 X16 12 1007")
    tran0.writeAction("slorii X16 X16 12 3936")
    tran0.writeAction("slorii X16 X16 12 1648")
    tran0.writeAction("slorii X16 X16 12 1833")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 44059")
    tran0.writeAction("slorii X16 X16 12 779")
    tran0.writeAction("slorii X16 X16 12 1505")
    tran0.writeAction("slorii X16 X16 12 764")
    tran0.writeAction("slorii X16 X16 12 3331")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 18138")
    tran0.writeAction("slorii X16 X16 12 2108")
    tran0.writeAction("slorii X16 X16 12 3005")
    tran0.writeAction("slorii X16 X16 12 258")
    tran0.writeAction("slorii X16 X16 12 3629")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 42547")
    tran0.writeAction("slorii X16 X16 12 3581")
    tran0.writeAction("slorii X16 X16 12 944")
    tran0.writeAction("slorii X16 X16 12 2013")
    tran0.writeAction("slorii X16 X16 12 3884")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 6957")
    tran0.writeAction("slorii X16 X16 12 2916")
    tran0.writeAction("slorii X16 X16 12 2297")
    tran0.writeAction("slorii X16 X16 12 2457")
    tran0.writeAction("slorii X16 X16 12 2527")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 10866")
    tran0.writeAction("slorii X16 X16 12 1443")
    tran0.writeAction("slorii X16 X16 12 4050")
    tran0.writeAction("slorii X16 X16 12 1754")
    tran0.writeAction("slorii X16 X16 12 3352")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 6")
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
    tran1 = state1.writeTransition("commonCarry_with_action", state1, state2, 0)
    tran1.writeAction("addi X30 X30 1")
    tran1.writeAction("addi X5 X17 0")
    tran1.writeAction("yield")
    tran2 = state2.writeTransition("commonCarry_with_action", state2, state2, 0)
    tran2.writeAction("addi X31 X31 1")
    tran2.writeAction("addi X5 X19 0")
    tran2.writeAction("yieldt")
    tran4 = state.writeTransition("event", state, state2, 0)
    tran4.writeAction("addi X30 X30 1")
    tran4.writeAction("addi X5 X18 0")
    tran4.writeAction("lastact")
    efa.appendBlockAction("end_of_input_terminate_efa1","movir X29 10")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state2)
    return efa
