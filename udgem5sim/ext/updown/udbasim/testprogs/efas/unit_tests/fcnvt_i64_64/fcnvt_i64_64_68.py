from EFA_v2 import *
def fcnvt_i64_64_68():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [2749793275710056433]
    tran0.writeAction("movir X16 9769")
    tran0.writeAction("slorii X16 X16 12 934")
    tran0.writeAction("slorii X16 X16 12 2636")
    tran0.writeAction("slorii X16 X16 12 1866")
    tran0.writeAction("slorii X16 X16 12 2033")
    tran0.writeAction("fcnvt.i64.64 X16 X16")
    tran0.writeAction("yieldt")
    return efa