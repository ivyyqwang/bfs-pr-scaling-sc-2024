from EFA_v2 import *
def bcpylli_4():
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
    tran0.writeAction("slorii X16 X16 12 9")
    tran0.writeAction("slorii X16 X16 12 1830")
    tran0.writeAction("addi X16 X21 0")
    tran0.writeAction("add X16 X7 X16")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("slorii X17 X17 12 0")
    tran0.writeAction("slorii X17 X17 12 0")
    tran0.writeAction("slorii X17 X17 12 12")
    tran0.writeAction("slorii X17 X17 12 200")
    tran0.writeAction("addi X17 X22 0")
    tran0.writeAction("add X17 X7 X17")
    tran0.writeAction("addi X16 X19 0")
    tran0.writeAction("movir X20 7")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("movir X20 0")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("movir X20 9")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("movir X20 120")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("movir X20 109")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("movir X20 150")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("movir X20 138")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("movir X20 100")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("movir X20 46")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("movir X20 50")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("movir X20 156")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("movir X20 18")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("movir X20 242")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("movir X20 56")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("movir X20 49")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("movir X20 71")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("movir X20 96")
    tran0.writeAction("movrl X20 0(X19) 0 8")
    tran0.writeAction("addi X19 X19 1")
    tran0.writeAction("bcpylli X16 X17 17")
    tran0.writeAction("sub X16 X7 X16")
    tran0.writeAction("sub X17 X7 X17")
    tran0.writeAction("yieldt")
    return efa