from EFA_v2 import *
def bcpylli_8():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
    tran0.writeAction("movir X16 0")
    tran0.writeAction("slorii X16 X16 12 0")
    tran0.writeAction("slorii X16 X16 12 0")
    tran0.writeAction("slorii X16 X16 12 10")
    tran0.writeAction("slorii X16 X16 12 2277")
    tran0.writeAction("addi X16 X21 0")
    tran0.writeAction("add X16 X7 X16")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("slorii X17 X17 12 0")
    tran0.writeAction("slorii X17 X17 12 0")
    tran0.writeAction("slorii X17 X17 12 11")
    tran0.writeAction("slorii X17 X17 12 1262")
    tran0.writeAction("addi X17 X22 0")
    tran0.writeAction("add X17 X7 X17")
    tran0.writeAction("addi X16 X19 0")
    tran0.writeAction("movir X20 180")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("movir X20 82")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("movir X20 28")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("movir X20 254")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("movir X20 53")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("movir X20 179")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("bcpylli X16 X17 6")
    tran0.writeAction("sub X16 X7 X16")
    tran0.writeAction("sub X17 X7 X17")
    tran0.writeAction("yieldt")
    return efa