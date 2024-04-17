from EFA_v2 import *
def fcnvt_64_32_75():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [8577590354983532579]
    tran0.writeAction("movir X16 30473")
    tran0.writeAction("slorii X16 X16 12 2959")
    tran0.writeAction("slorii X16 X16 12 2905")
    tran0.writeAction("slorii X16 X16 12 2499")
    tran0.writeAction("slorii X16 X16 12 2083")
    tran0.writeAction("fcnvt.64.32 X16 X16")
    tran0.writeAction("yieldt")
    return efa