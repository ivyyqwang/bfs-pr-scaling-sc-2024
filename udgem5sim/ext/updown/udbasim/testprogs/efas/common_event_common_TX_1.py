from EFA_v2 import *
def common_event_common_TX_1():
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
    tran0.writeAction("movir X16 41611")
    tran0.writeAction("slorii X16 X16 12 254")
    tran0.writeAction("slorii X16 X16 12 3114")
    tran0.writeAction("slorii X16 X16 12 607")
    tran0.writeAction("slorii X16 X16 12 987")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 43353")
    tran0.writeAction("slorii X16 X16 12 3050")
    tran0.writeAction("slorii X16 X16 12 425")
    tran0.writeAction("slorii X16 X16 12 3202")
    tran0.writeAction("slorii X16 X16 12 484")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 47123")
    tran0.writeAction("slorii X16 X16 12 3012")
    tran0.writeAction("slorii X16 X16 12 4052")
    tran0.writeAction("slorii X16 X16 12 338")
    tran0.writeAction("slorii X16 X16 12 3994")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 46354")
    tran0.writeAction("slorii X16 X16 12 1922")
    tran0.writeAction("slorii X16 X16 12 1567")
    tran0.writeAction("slorii X16 X16 12 1345")
    tran0.writeAction("slorii X16 X16 12 3586")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 17030")
    tran0.writeAction("slorii X16 X16 12 1134")
    tran0.writeAction("slorii X16 X16 12 4047")
    tran0.writeAction("slorii X16 X16 12 1689")
    tran0.writeAction("slorii X16 X16 12 1106")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 6100")
    tran0.writeAction("slorii X16 X16 12 3264")
    tran0.writeAction("slorii X16 X16 12 1134")
    tran0.writeAction("slorii X16 X16 12 4082")
    tran0.writeAction("slorii X16 X16 12 2876")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 62418")
    tran0.writeAction("slorii X16 X16 12 3920")
    tran0.writeAction("slorii X16 X16 12 3748")
    tran0.writeAction("slorii X16 X16 12 3914")
    tran0.writeAction("slorii X16 X16 12 16")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 65228")
    tran0.writeAction("slorii X16 X16 12 2542")
    tran0.writeAction("slorii X16 X16 12 1626")
    tran0.writeAction("slorii X16 X16 12 1861")
    tran0.writeAction("slorii X16 X16 12 1423")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 41611")
    tran0.writeAction("slorii X16 X16 12 254")
    tran0.writeAction("slorii X16 X16 12 3114")
    tran0.writeAction("slorii X16 X16 12 607")
    tran0.writeAction("slorii X16 X16 12 987")
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
    tran0.writeAction("addi X20 X17 24")
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