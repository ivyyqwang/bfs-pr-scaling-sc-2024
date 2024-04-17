from EFA_v2 import *
def hashsb64_62():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [7025721359410274616, 3813165542040488650, -7382525181526639198, -8051716128022175794, -6419408527543009769, 1110240018242734423, 1180382966790074372, -8995737462089241432, 184, 604]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 24960")
    tran0.writeAction("slorii X17 X17 12 1541")
    tran0.writeAction("slorii X17 X17 12 2622")
    tran0.writeAction("slorii X17 X17 12 2146")
    tran0.writeAction("slorii X17 X17 12 312")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 13547")
    tran0.writeAction("slorii X17 X17 12 349")
    tran0.writeAction("slorii X17 X17 12 2947")
    tran0.writeAction("slorii X17 X17 12 340")
    tran0.writeAction("slorii X17 X17 12 2762")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 39308")
    tran0.writeAction("slorii X17 X17 12 7")
    tran0.writeAction("slorii X17 X17 12 1585")
    tran0.writeAction("slorii X17 X17 12 2983")
    tran0.writeAction("slorii X17 X17 12 3490")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 36930")
    tran0.writeAction("slorii X17 X17 12 2285")
    tran0.writeAction("slorii X17 X17 12 1892")
    tran0.writeAction("slorii X17 X17 12 3909")
    tran0.writeAction("slorii X17 X17 12 4046")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 42729")
    tran0.writeAction("slorii X17 X17 12 2783")
    tran0.writeAction("slorii X17 X17 12 1191")
    tran0.writeAction("slorii X17 X17 12 2807")
    tran0.writeAction("slorii X17 X17 12 3607")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 3944")
    tran0.writeAction("slorii X17 X17 12 1494")
    tran0.writeAction("slorii X17 X17 12 2574")
    tran0.writeAction("slorii X17 X17 12 3200")
    tran0.writeAction("slorii X17 X17 12 2391")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 4193")
    tran0.writeAction("slorii X17 X17 12 2304")
    tran0.writeAction("slorii X17 X17 12 3562")
    tran0.writeAction("slorii X17 X17 12 1819")
    tran0.writeAction("slorii X17 X17 12 4")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 33576")
    tran0.writeAction("slorii X17 X17 12 2951")
    tran0.writeAction("slorii X17 X17 12 143")
    tran0.writeAction("slorii X17 X17 12 2034")
    tran0.writeAction("slorii X17 X17 12 3240")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movlsb X16")
    tran0.writeAction("movir X16 184")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("add X16 X17 X5")
    tran0.writeAction("movir X16 604")
    tran0.writeAction("hashsb64 X16 X17")
    tran0.writeAction("yieldt")
    return efa