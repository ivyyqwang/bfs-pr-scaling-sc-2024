from EFA_v2 import *
def fcnvt_i64_64_88():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-1701742335873905180]
    tran0.writeAction("movir X16 59490")
    tran0.writeAction("slorii X16 X16 12 805")
    tran0.writeAction("slorii X16 X16 12 3226")
    tran0.writeAction("slorii X16 X16 12 4064")
    tran0.writeAction("slorii X16 X16 12 3556")
    tran0.writeAction("fcnvt.i64.64 X16 X16")
    tran0.writeAction("yieldt")
    return efa