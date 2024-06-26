from EFA_v2 import *
def fcnvt_64_i64_5():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [14275933911693766771]
    tran0.writeAction("movir X16 50718")
    tran0.writeAction("slorii X16 X16 12 1252")
    tran0.writeAction("slorii X16 X16 12 363")
    tran0.writeAction("slorii X16 X16 12 1883")
    tran0.writeAction("slorii X16 X16 12 115")
    tran0.writeAction("fcnvt.64.i64 X16 X16")
    tran0.writeAction("yieldt")
    return efa
