from EFA_v2 import *
def bcpyll_13():
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
    tran0.writeAction("slorii X16 X16 12 14")
    tran0.writeAction("slorii X16 X16 12 2771")
    tran0.writeAction("addi X16 X21 0")
    tran0.writeAction("add X16 X7 X16")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("slorii X17 X17 12 0")
    tran0.writeAction("slorii X17 X17 12 0")
    tran0.writeAction("slorii X17 X17 12 6")
    tran0.writeAction("slorii X17 X17 12 1093")
    tran0.writeAction("addi X17 X22 0")
    tran0.writeAction("add X17 X7 X17")
    tran0.writeAction("movir X18 0")
    tran0.writeAction("slorii X18 X18 12 0")
    tran0.writeAction("slorii X18 X18 12 0")
    tran0.writeAction("slorii X18 X18 12 0")
    tran0.writeAction("slorii X18 X18 12 28")
    tran0.writeAction("addi X18 X23 0")
    tran0.writeAction("addi X16 X19 0")
    tran0.writeAction("movir X20 238")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("movir X20 240")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("movir X20 255")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("movir X20 94")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("movir X20 124")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("movir X20 158")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("movir X20 165")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("movir X20 15")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("movir X20 158")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("movir X20 142")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("movir X20 139")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("movir X20 224")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("movir X20 172")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("movir X20 2")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("movir X20 160")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("movir X20 83")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("movir X20 1")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("movir X20 219")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("movir X20 176")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("movir X20 232")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("movir X20 221")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("movir X20 11")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("movir X20 118")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("movir X20 219")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("movir X20 252")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("movir X20 135")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("movir X20 153")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("movir X20 178")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("bcpyll X16 X17 X18")
    tran0.writeAction("sub X16 X7 X16")
    tran0.writeAction("sub X17 X7 X17")
    tran0.writeAction("yieldt")
    return efa
