from EFA_v2 import *
def hashsb64_37():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [3148606208569528102, 8777108700431542276, -8069143765631860817, 8185307422569990425, -2931116861123317933, -1738628715919768633, -2705437746825809640, 7107857162113438740, 104, 14326]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 11186")
    tran0.writeAction("slorii X17 X17 12 394")
    tran0.writeAction("slorii X17 X17 12 2599")
    tran0.writeAction("slorii X17 X17 12 1540")
    tran0.writeAction("slorii X17 X17 12 3878")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 31182")
    tran0.writeAction("slorii X17 X17 12 2269")
    tran0.writeAction("slorii X17 X17 12 3108")
    tran0.writeAction("slorii X17 X17 12 870")
    tran0.writeAction("slorii X17 X17 12 2052")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 36868")
    tran0.writeAction("slorii X17 X17 12 2631")
    tran0.writeAction("slorii X17 X17 12 3919")
    tran0.writeAction("slorii X17 X17 12 3911")
    tran0.writeAction("slorii X17 X17 12 4015")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 29080")
    tran0.writeAction("slorii X17 X17 12 219")
    tran0.writeAction("slorii X17 X17 12 2995")
    tran0.writeAction("slorii X17 X17 12 2672")
    tran0.writeAction("slorii X17 X17 12 2329")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 55122")
    tran0.writeAction("slorii X17 X17 12 2379")
    tran0.writeAction("slorii X17 X17 12 3737")
    tran0.writeAction("slorii X17 X17 12 2402")
    tran0.writeAction("slorii X17 X17 12 3923")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 59359")
    tran0.writeAction("slorii X17 X17 12 614")
    tran0.writeAction("slorii X17 X17 12 1279")
    tran0.writeAction("slorii X17 X17 12 1264")
    tran0.writeAction("slorii X17 X17 12 967")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 55924")
    tran0.writeAction("slorii X17 X17 12 1451")
    tran0.writeAction("slorii X17 X17 12 1034")
    tran0.writeAction("slorii X17 X17 12 2107")
    tran0.writeAction("slorii X17 X17 12 280")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 25252")
    tran0.writeAction("slorii X17 X17 12 742")
    tran0.writeAction("slorii X17 X17 12 3597")
    tran0.writeAction("slorii X17 X17 12 4045")
    tran0.writeAction("slorii X17 X17 12 1044")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movlsb X16")
    tran0.writeAction("movir X16 104")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("add X16 X17 X5")
    tran0.writeAction("movir X16 14326")
    tran0.writeAction("hashsb64 X16 X17")
    tran0.writeAction("yieldt")
    return efa