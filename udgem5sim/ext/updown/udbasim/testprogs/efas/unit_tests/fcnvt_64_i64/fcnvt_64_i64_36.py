from EFA_v2 import *
def fcnvt_64_i64_36():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [14564911295762631406]
    tran0.writeAction("movir X16 51744")
    tran0.writeAction("slorii X16 X16 12 3930")
    tran0.writeAction("slorii X16 X16 12 1985")
    tran0.writeAction("slorii X16 X16 12 24")
    tran0.writeAction("slorii X16 X16 12 2798")
    tran0.writeAction("fcnvt.64.i64 X16 X16")
    tran0.writeAction("yieldt")
    return efa
