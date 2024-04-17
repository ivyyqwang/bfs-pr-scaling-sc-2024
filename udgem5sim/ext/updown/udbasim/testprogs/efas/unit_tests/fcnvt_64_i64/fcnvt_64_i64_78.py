from EFA_v2 import *
def fcnvt_64_i64_78():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [8902304238207045029]
    tran0.writeAction("movir X16 31627")
    tran0.writeAction("slorii X16 X16 12 1384")
    tran0.writeAction("slorii X16 X16 12 2504")
    tran0.writeAction("slorii X16 X16 12 3216")
    tran0.writeAction("slorii X16 X16 12 3493")
    tran0.writeAction("fcnvt.64.i64 X16 X16")
    tran0.writeAction("yieldt")
    return efa
