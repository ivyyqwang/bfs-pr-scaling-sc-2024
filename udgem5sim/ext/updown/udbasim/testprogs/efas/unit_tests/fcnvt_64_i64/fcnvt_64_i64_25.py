from EFA_v2 import *
def fcnvt_64_i64_25():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [2615549805666922951]
    tran0.writeAction("movir X16 9292")
    tran0.writeAction("slorii X16 X16 12 1227")
    tran0.writeAction("slorii X16 X16 12 195")
    tran0.writeAction("slorii X16 X16 12 487")
    tran0.writeAction("slorii X16 X16 12 455")
    tran0.writeAction("fcnvt.64.i64 X16 X16")
    tran0.writeAction("yieldt")
    return efa
