from EFA_v2 import *
def fcnvt_64_32_18():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [9421132023838148156]
    tran0.writeAction("movir X16 33470")
    tran0.writeAction("slorii X16 X16 12 2394")
    tran0.writeAction("slorii X16 X16 12 2318")
    tran0.writeAction("slorii X16 X16 12 3808")
    tran0.writeAction("slorii X16 X16 12 1596")
    tran0.writeAction("fcnvt.64.32 X16 X16")
    tran0.writeAction("yieldt")
    return efa
