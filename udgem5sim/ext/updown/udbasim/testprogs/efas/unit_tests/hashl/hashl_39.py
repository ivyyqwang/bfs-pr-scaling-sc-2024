from EFA_v2 import *
def hashl_39():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-8045741203279537440, -4713348845434528996, -6098399579869567205, -6426163932401208423, 4103272332066051294, -712997889346523472]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 36951")
    tran0.writeAction("slorii X17 X17 12 3216")
    tran0.writeAction("slorii X17 X17 12 247")
    tran0.writeAction("slorii X17 X17 12 3273")
    tran0.writeAction("slorii X17 X17 12 2784")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 48790")
    tran0.writeAction("slorii X17 X17 12 3363")
    tran0.writeAction("slorii X17 X17 12 653")
    tran0.writeAction("slorii X17 X17 12 1545")
    tran0.writeAction("slorii X17 X17 12 2844")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 43870")
    tran0.writeAction("slorii X17 X17 12 542")
    tran0.writeAction("slorii X17 X17 12 1167")
    tran0.writeAction("slorii X17 X17 12 1978")
    tran0.writeAction("slorii X17 X17 12 1819")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 42705")
    tran0.writeAction("slorii X17 X17 12 2783")
    tran0.writeAction("slorii X17 X17 12 868")
    tran0.writeAction("slorii X17 X17 12 3271")
    tran0.writeAction("slorii X17 X17 12 921")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 14577")
    tran0.writeAction("slorii X17 X17 12 3079")
    tran0.writeAction("slorii X17 X17 12 553")
    tran0.writeAction("slorii X17 X17 12 1989")
    tran0.writeAction("slorii X17 X17 12 1246")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 63002")
    tran0.writeAction("slorii X17 X17 12 3779")
    tran0.writeAction("slorii X17 X17 12 639")
    tran0.writeAction("slorii X17 X17 12 3674")
    tran0.writeAction("slorii X17 X17 12 3760")
    tran0.writeAction("hashl X16 X17 5")
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movrl X17 0(X16) 0 8")
    tran0.writeAction("yieldt")
    return efa