from EFA_v2 import *
def fcnvt_64_i64_37():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [15967454401650595880]
    tran0.writeAction("movir X16 56727")
    tran0.writeAction("slorii X16 X16 12 3250")
    tran0.writeAction("slorii X16 X16 12 3545")
    tran0.writeAction("slorii X16 X16 12 2585")
    tran0.writeAction("slorii X16 X16 12 2088")
    tran0.writeAction("fcnvt.64.i64 X16 X16")
    tran0.writeAction("yieldt")
    return efa
