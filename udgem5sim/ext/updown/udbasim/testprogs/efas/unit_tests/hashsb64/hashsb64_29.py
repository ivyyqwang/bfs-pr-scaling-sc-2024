from EFA_v2 import *
def hashsb64_29():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-4025720650729678109, 488422732818193090, 6025309505283173039, -559564583945371914, -6188185772452800950, -6542177059334134837, -7262214469344460155, -866612402185972487, 48, 19886]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 51233")
    tran0.writeAction("slorii X17 X17 12 3142")
    tran0.writeAction("slorii X17 X17 12 1464")
    tran0.writeAction("slorii X17 X17 12 1241")
    tran0.writeAction("slorii X17 X17 12 2787")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 1735")
    tran0.writeAction("slorii X17 X17 12 926")
    tran0.writeAction("slorii X17 X17 12 833")
    tran0.writeAction("slorii X17 X17 12 3497")
    tran0.writeAction("slorii X17 X17 12 2754")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 21406")
    tran0.writeAction("slorii X17 X17 12 817")
    tran0.writeAction("slorii X17 X17 12 596")
    tran0.writeAction("slorii X17 X17 12 770")
    tran0.writeAction("slorii X17 X17 12 2735")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 63548")
    tran0.writeAction("slorii X17 X17 12 111")
    tran0.writeAction("slorii X17 X17 12 2497")
    tran0.writeAction("slorii X17 X17 12 191")
    tran0.writeAction("slorii X17 X17 12 3830")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 43551")
    tran0.writeAction("slorii X17 X17 12 605")
    tran0.writeAction("slorii X17 X17 12 908")
    tran0.writeAction("slorii X17 X17 12 3377")
    tran0.writeAction("slorii X17 X17 12 1610")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 42293")
    tran0.writeAction("slorii X17 X17 12 2122")
    tran0.writeAction("slorii X17 X17 12 96")
    tran0.writeAction("slorii X17 X17 12 2782")
    tran0.writeAction("slorii X17 X17 12 971")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 39735")
    tran0.writeAction("slorii X17 X17 12 1766")
    tran0.writeAction("slorii X17 X17 12 2752")
    tran0.writeAction("slorii X17 X17 12 88")
    tran0.writeAction("slorii X17 X17 12 645")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 62457")
    tran0.writeAction("slorii X17 X17 12 713")
    tran0.writeAction("slorii X17 X17 12 3225")
    tran0.writeAction("slorii X17 X17 12 3101")
    tran0.writeAction("slorii X17 X17 12 1273")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movlsb X16")
    tran0.writeAction("movir X16 48")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("add X16 X17 X5")
    tran0.writeAction("movir X16 19886")
    tran0.writeAction("hashsb64 X16 X17")
    tran0.writeAction("yieldt")
    return efa
