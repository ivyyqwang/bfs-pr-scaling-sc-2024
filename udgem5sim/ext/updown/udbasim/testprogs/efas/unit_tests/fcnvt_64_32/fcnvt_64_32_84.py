from EFA_v2 import *
def fcnvt_64_32_84():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [4892458070223683498]
    tran0.writeAction("movir X16 17381")
    tran0.writeAction("slorii X16 X16 12 2059")
    tran0.writeAction("slorii X16 X16 12 394")
    tran0.writeAction("slorii X16 X16 12 719")
    tran0.writeAction("slorii X16 X16 12 4010")
    tran0.writeAction("fcnvt.64.32 X16 X16")
    tran0.writeAction("yieldt")
    return efa
