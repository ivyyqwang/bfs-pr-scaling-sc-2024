from EFA_v2 import *
def fcnvt_i64_64_64():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-904621180041636359]
    tran0.writeAction("movir X16 62322")
    tran0.writeAction("slorii X16 X16 12 573")
    tran0.writeAction("slorii X16 X16 12 1123")
    tran0.writeAction("slorii X16 X16 12 1325")
    tran0.writeAction("slorii X16 X16 12 1529")
    tran0.writeAction("fcnvt.i64.64 X16 X16")
    tran0.writeAction("yieldt")
    return efa
