from EFA_v2 import *
def hashl_95():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [6777415868242291737, 1640088492884912883, 7987425086783895292, -6261938529916373150, -547211700591728952, -8763427368773605342, -5540570322202709728]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 24078")
    tran0.writeAction("slorii X17 X17 12 893")
    tran0.writeAction("slorii X17 X17 12 745")
    tran0.writeAction("slorii X17 X17 12 2774")
    tran0.writeAction("slorii X17 X17 12 3097")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 5826")
    tran0.writeAction("slorii X17 X17 12 3132")
    tran0.writeAction("slorii X17 X17 12 2930")
    tran0.writeAction("slorii X17 X17 12 2502")
    tran0.writeAction("slorii X17 X17 12 2803")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 28377")
    tran0.writeAction("slorii X17 X17 12 140")
    tran0.writeAction("slorii X17 X17 12 3095")
    tran0.writeAction("slorii X17 X17 12 3267")
    tran0.writeAction("slorii X17 X17 12 1788")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 43289")
    tran0.writeAction("slorii X17 X17 12 513")
    tran0.writeAction("slorii X17 X17 12 1423")
    tran0.writeAction("slorii X17 X17 12 11")
    tran0.writeAction("slorii X17 X17 12 1890")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 63591")
    tran0.writeAction("slorii X17 X17 12 3741")
    tran0.writeAction("slorii X17 X17 12 2953")
    tran0.writeAction("slorii X17 X17 12 1198")
    tran0.writeAction("slorii X17 X17 12 1736")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 34402")
    tran0.writeAction("slorii X17 X17 12 211")
    tran0.writeAction("slorii X17 X17 12 3357")
    tran0.writeAction("slorii X17 X17 12 1282")
    tran0.writeAction("slorii X17 X17 12 2082")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 45851")
    tran0.writeAction("slorii X17 X17 12 3850")
    tran0.writeAction("slorii X17 X17 12 1452")
    tran0.writeAction("slorii X17 X17 12 147")
    tran0.writeAction("slorii X17 X17 12 288")
    tran0.writeAction("hashl X16 X17 6")
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movrl X17 0(X16) 0 8")
    tran0.writeAction("yieldt")
    return efa