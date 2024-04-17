from EFA_v2 import *
def fcnvt_i64_64_41():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-8667071570711958225]
    tran0.writeAction("movir X16 34744")
    tran0.writeAction("slorii X16 X16 12 1541")
    tran0.writeAction("slorii X16 X16 12 920")
    tran0.writeAction("slorii X16 X16 12 3386")
    tran0.writeAction("slorii X16 X16 12 3375")
    tran0.writeAction("fcnvt.i64.64 X16 X16")
    tran0.writeAction("yieldt")
    return efa
