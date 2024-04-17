from EFA_v2 import *
def fcnvt_64_b16_49():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [449904511717881287]
    tran0.writeAction("movir X16 1598")
    tran0.writeAction("slorii X16 X16 12 1564")
    tran0.writeAction("slorii X16 X16 12 1291")
    tran0.writeAction("slorii X16 X16 12 3235")
    tran0.writeAction("slorii X16 X16 12 1479")
    tran0.writeAction("fcnvt.64.b16 X16 X16")
    tran0.writeAction("yieldt")
    return efa
