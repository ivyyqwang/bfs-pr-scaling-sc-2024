from EFA_v2 import *
def slsubii_16():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [1134161108000243447, 7, 1902]
    tran0.writeAction("movir X16 4029")
    tran0.writeAction("slorii X16 X16 12 1432")
    tran0.writeAction("slorii X16 X16 12 1224")
    tran0.writeAction("slorii X16 X16 12 1711")
    tran0.writeAction("slorii X16 X16 12 3831")
    tran0.writeAction("slsubii X16 X17 7 1902")
    tran0.writeAction("yieldt")
    return efa
