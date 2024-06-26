from EFA_v2 import *
def fcnvt_64_b16_65():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [4619401797161430537]
    tran0.writeAction("movir X16 16411")
    tran0.writeAction("slorii X16 X16 12 1687")
    tran0.writeAction("slorii X16 X16 12 1466")
    tran0.writeAction("slorii X16 X16 12 2490")
    tran0.writeAction("slorii X16 X16 12 3593")
    tran0.writeAction("fcnvt.64.b16 X16 X16")
    tran0.writeAction("yieldt")
    return efa
