from EFA_v2 import *
def srsubii_17():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [2182248712446298034, 0, 1493]
    tran0.writeAction("movir X16 7752")
    tran0.writeAction("slorii X16 X16 12 3706")
    tran0.writeAction("slorii X16 X16 12 1108")
    tran0.writeAction("slorii X16 X16 12 3748")
    tran0.writeAction("slorii X16 X16 12 1970")
    tran0.writeAction("srsubii X16 X17 0 1493")
    tran0.writeAction("yieldt")
    return efa
