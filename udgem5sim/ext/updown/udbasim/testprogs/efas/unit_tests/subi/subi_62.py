from EFA_v2 import *
def subi_62():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [8229293111041084104, -17699]
    tran0.writeAction("movir X16 29236")
    tran0.writeAction("slorii X16 X16 12 1319")
    tran0.writeAction("slorii X16 X16 12 3036")
    tran0.writeAction("slorii X16 X16 12 708")
    tran0.writeAction("slorii X16 X16 12 2760")
    tran0.writeAction("subi X16 X17 -17699")
    tran0.writeAction("yieldt")
    return efa
