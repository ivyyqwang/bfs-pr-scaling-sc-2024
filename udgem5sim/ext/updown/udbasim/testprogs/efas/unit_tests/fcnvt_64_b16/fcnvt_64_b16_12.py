from EFA_v2 import *
def fcnvt_64_b16_12():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [2709004484711229202]
    tran0.writeAction("movir X16 9624")
    tran0.writeAction("slorii X16 X16 12 1299")
    tran0.writeAction("slorii X16 X16 12 2518")
    tran0.writeAction("slorii X16 X16 12 626")
    tran0.writeAction("slorii X16 X16 12 1810")
    tran0.writeAction("fcnvt.64.b16 X16 X16")
    tran0.writeAction("yieldt")
    return efa
