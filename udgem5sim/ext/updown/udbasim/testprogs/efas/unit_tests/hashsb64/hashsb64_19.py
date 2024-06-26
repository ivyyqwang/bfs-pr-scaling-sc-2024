from EFA_v2 import *
def hashsb64_19():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [8150174739922552391, -8684684349698925258, -5106825157295286085, -8040119001403483982, 2035192151625643397, -9212485935718917301, -261105558820989866, 4918082487499701326, 144, 12460]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 28955")
    tran0.writeAction("slorii X17 X17 12 971")
    tran0.writeAction("slorii X17 X17 12 3734")
    tran0.writeAction("slorii X17 X17 12 1824")
    tran0.writeAction("slorii X17 X17 12 1607")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 34681")
    tran0.writeAction("slorii X17 X17 12 3289")
    tran0.writeAction("slorii X17 X17 12 2285")
    tran0.writeAction("slorii X17 X17 12 3281")
    tran0.writeAction("slorii X17 X17 12 3382")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 47392")
    tran0.writeAction("slorii X17 X17 12 3737")
    tran0.writeAction("slorii X17 X17 12 921")
    tran0.writeAction("slorii X17 X17 12 1581")
    tran0.writeAction("slorii X17 X17 12 2235")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 36971")
    tran0.writeAction("slorii X17 X17 12 3109")
    tran0.writeAction("slorii X17 X17 12 3545")
    tran0.writeAction("slorii X17 X17 12 1953")
    tran0.writeAction("slorii X17 X17 12 2226")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 7230")
    tran0.writeAction("slorii X17 X17 12 1863")
    tran0.writeAction("slorii X17 X17 12 2719")
    tran0.writeAction("slorii X17 X17 12 1267")
    tran0.writeAction("slorii X17 X17 12 1413")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 32806")
    tran0.writeAction("slorii X17 X17 12 2765")
    tran0.writeAction("slorii X17 X17 12 2543")
    tran0.writeAction("slorii X17 X17 12 785")
    tran0.writeAction("slorii X17 X17 12 2891")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 64608")
    tran0.writeAction("slorii X17 X17 12 1502")
    tran0.writeAction("slorii X17 X17 12 173")
    tran0.writeAction("slorii X17 X17 12 2437")
    tran0.writeAction("slorii X17 X17 12 1110")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 17472")
    tran0.writeAction("slorii X17 X17 12 2207")
    tran0.writeAction("slorii X17 X17 12 1819")
    tran0.writeAction("slorii X17 X17 12 2003")
    tran0.writeAction("slorii X17 X17 12 3150")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movlsb X16")
    tran0.writeAction("movir X16 144")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("add X16 X17 X5")
    tran0.writeAction("movir X16 12460")
    tran0.writeAction("hashsb64 X16 X17")
    tran0.writeAction("yieldt")
    return efa
