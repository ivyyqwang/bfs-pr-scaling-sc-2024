from EFA_v2 import *
def hashsb64_63():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-6129529253757780391, 3326303951471975932, -953947009733873752, -3736602220621521326, -7996175588546252186, 4813107912839268513, 3143602100391957747, 5222437864068142887, 416, 23338]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 43759")
    tran0.writeAction("slorii X17 X17 12 2201")
    tran0.writeAction("slorii X17 X17 12 3725")
    tran0.writeAction("slorii X17 X17 12 1647")
    tran0.writeAction("slorii X17 X17 12 3673")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 11817")
    tran0.writeAction("slorii X17 X17 12 1661")
    tran0.writeAction("slorii X17 X17 12 514")
    tran0.writeAction("slorii X17 X17 12 1905")
    tran0.writeAction("slorii X17 X17 12 3580")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 62146")
    tran0.writeAction("slorii X17 X17 12 3683")
    tran0.writeAction("slorii X17 X17 12 4022")
    tran0.writeAction("slorii X17 X17 12 1090")
    tran0.writeAction("slorii X17 X17 12 4008")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 52260")
    tran0.writeAction("slorii X17 X17 12 3777")
    tran0.writeAction("slorii X17 X17 12 996")
    tran0.writeAction("slorii X17 X17 12 3761")
    tran0.writeAction("slorii X17 X17 12 3666")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 37127")
    tran0.writeAction("slorii X17 X17 12 3594")
    tran0.writeAction("slorii X17 X17 12 2803")
    tran0.writeAction("slorii X17 X17 12 207")
    tran0.writeAction("slorii X17 X17 12 614")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 17099")
    tran0.writeAction("slorii X17 X17 12 2434")
    tran0.writeAction("slorii X17 X17 12 1362")
    tran0.writeAction("slorii X17 X17 12 1664")
    tran0.writeAction("slorii X17 X17 12 2209")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 11168")
    tran0.writeAction("slorii X17 X17 12 1303")
    tran0.writeAction("slorii X17 X17 12 1133")
    tran0.writeAction("slorii X17 X17 12 141")
    tran0.writeAction("slorii X17 X17 12 1267")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 18553")
    tran0.writeAction("slorii X17 X17 12 3385")
    tran0.writeAction("slorii X17 X17 12 341")
    tran0.writeAction("slorii X17 X17 12 1357")
    tran0.writeAction("slorii X17 X17 12 1831")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movlsb X16")
    tran0.writeAction("movir X16 416")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("add X16 X17 X5")
    tran0.writeAction("movir X16 23338")
    tran0.writeAction("hashsb64 X16 X17")
    tran0.writeAction("yieldt")
    return efa
