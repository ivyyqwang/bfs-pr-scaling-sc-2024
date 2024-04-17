from EFA_v2 import *
def fsqrt_64_63():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [11008424425280415283]
    tran0.writeAction("movir X16 39109")
    tran0.writeAction("slorii X16 X16 12 3195")
    tran0.writeAction("slorii X16 X16 12 141")
    tran0.writeAction("slorii X16 X16 12 2346")
    tran0.writeAction("slorii X16 X16 12 1587")
    tran0.writeAction("fsqrt.64 X16 X17")
    tran0.writeAction("yieldt")
    return efa