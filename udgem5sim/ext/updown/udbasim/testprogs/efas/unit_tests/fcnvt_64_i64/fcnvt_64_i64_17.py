from EFA_v2 import *
def fcnvt_64_i64_17():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [1461289310308997878]
    tran0.writeAction("movir X16 5191")
    tran0.writeAction("slorii X16 X16 12 2222")
    tran0.writeAction("slorii X16 X16 12 687")
    tran0.writeAction("slorii X16 X16 12 177")
    tran0.writeAction("slorii X16 X16 12 2806")
    tran0.writeAction("fcnvt.64.i64 X16 X16")
    tran0.writeAction("yieldt")
    return efa
