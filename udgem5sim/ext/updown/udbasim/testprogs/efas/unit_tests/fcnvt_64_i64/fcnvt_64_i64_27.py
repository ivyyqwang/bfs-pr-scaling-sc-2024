from EFA_v2 import *
def fcnvt_64_i64_27():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [3460518274132325604]
    tran0.writeAction("movir X16 12294")
    tran0.writeAction("slorii X16 X16 12 944")
    tran0.writeAction("slorii X16 X16 12 2340")
    tran0.writeAction("slorii X16 X16 12 1659")
    tran0.writeAction("slorii X16 X16 12 1252")
    tran0.writeAction("fcnvt.64.i64 X16 X16")
    tran0.writeAction("yieldt")
    return efa
