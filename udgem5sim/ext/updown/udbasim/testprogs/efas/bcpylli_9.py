from EFA_v2 import *
def bcpylli_9():
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
    tran0.writeAction("slorii X16 X16 12 13")
    tran0.writeAction("slorii X16 X16 12 3206")
    tran0.writeAction("addi X16 X21 0")
    tran0.writeAction("add X16 X7 X16")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("slorii X17 X17 12 0")
    tran0.writeAction("slorii X17 X17 12 0")
    tran0.writeAction("slorii X17 X17 12 14")
    tran0.writeAction("slorii X17 X17 12 3009")
    tran0.writeAction("addi X17 X22 0")
    tran0.writeAction("add X17 X7 X17")
    tran0.writeAction("addi X16 X19 0")
    tran0.writeAction("movir X20 44")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("movir X20 172")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("movir X20 81")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("movir X20 164")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("bcpylli X16 X17 4")
    tran0.writeAction("sub X16 X7 X16")
    tran0.writeAction("sub X17 X7 X17")
    tran0.writeAction("yieldt")
    return efa