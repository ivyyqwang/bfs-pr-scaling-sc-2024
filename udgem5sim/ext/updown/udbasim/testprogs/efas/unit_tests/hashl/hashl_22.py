from EFA_v2 import *
def hashl_22():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [9211675494678574569, -3234925934681355037, 4496230475169886123, 6211210535293556558, -3662228820937565065, -7540055460702726205, -1223460649222398218, 1727389179198931978]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 32726")
    tran0.writeAction("slorii X17 X17 12 1824")
    tran0.writeAction("slorii X17 X17 12 3726")
    tran0.writeAction("slorii X17 X17 12 1995")
    tran0.writeAction("slorii X17 X17 12 1513")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 54043")
    tran0.writeAction("slorii X17 X17 12 960")
    tran0.writeAction("slorii X17 X17 12 116")
    tran0.writeAction("slorii X17 X17 12 2536")
    tran0.writeAction("slorii X17 X17 12 3299")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 15973")
    tran0.writeAction("slorii X17 X17 12 3356")
    tran0.writeAction("slorii X17 X17 12 2956")
    tran0.writeAction("slorii X17 X17 12 3222")
    tran0.writeAction("slorii X17 X17 12 4011")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 22066")
    tran0.writeAction("slorii X17 X17 12 2673")
    tran0.writeAction("slorii X17 X17 12 717")
    tran0.writeAction("slorii X17 X17 12 1377")
    tran0.writeAction("slorii X17 X17 12 1870")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 52525")
    tran0.writeAction("slorii X17 X17 12 612")
    tran0.writeAction("slorii X17 X17 12 2665")
    tran0.writeAction("slorii X17 X17 12 3353")
    tran0.writeAction("slorii X17 X17 12 3191")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 38748")
    tran0.writeAction("slorii X17 X17 12 1400")
    tran0.writeAction("slorii X17 X17 12 486")
    tran0.writeAction("slorii X17 X17 12 285")
    tran0.writeAction("slorii X17 X17 12 1987")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 61189")
    tran0.writeAction("slorii X17 X17 12 1616")
    tran0.writeAction("slorii X17 X17 12 1422")
    tran0.writeAction("slorii X17 X17 12 1761")
    tran0.writeAction("slorii X17 X17 12 3830")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 6136")
    tran0.writeAction("slorii X17 X17 12 3764")
    tran0.writeAction("slorii X17 X17 12 3695")
    tran0.writeAction("slorii X17 X17 12 24")
    tran0.writeAction("slorii X17 X17 12 1034")
    tran0.writeAction("hashl X16 X17 7")
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movrl X17 0(X16) 0 8")
    tran0.writeAction("yieldt")
    return efa
