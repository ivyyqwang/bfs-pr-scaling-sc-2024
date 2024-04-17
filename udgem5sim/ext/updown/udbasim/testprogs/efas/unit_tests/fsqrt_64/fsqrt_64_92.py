from EFA_v2 import *
def fsqrt_64_92():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [4760474801049735378]
    tran0.writeAction("movir X16 16912")
    tran0.writeAction("slorii X16 X16 12 2473")
    tran0.writeAction("slorii X16 X16 12 3078")
    tran0.writeAction("slorii X16 X16 12 3145")
    tran0.writeAction("slorii X16 X16 12 210")
    tran0.writeAction("fsqrt.64 X16 X17")
    tran0.writeAction("yieldt")
    return efa
