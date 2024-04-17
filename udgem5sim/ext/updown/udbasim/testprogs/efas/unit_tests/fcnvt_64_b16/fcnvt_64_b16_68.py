from EFA_v2 import *
def fcnvt_64_b16_68():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [13363136146920331425]
    tran0.writeAction("movir X16 47475")
    tran0.writeAction("slorii X16 X16 12 1624")
    tran0.writeAction("slorii X16 X16 12 1618")
    tran0.writeAction("slorii X16 X16 12 1509")
    tran0.writeAction("slorii X16 X16 12 2209")
    tran0.writeAction("fcnvt.64.b16 X16 X16")
    tran0.writeAction("yieldt")
    return efa
