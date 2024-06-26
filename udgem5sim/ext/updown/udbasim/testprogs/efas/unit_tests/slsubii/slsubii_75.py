from EFA_v2 import *
def slsubii_75():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-2523496595783537414, 15, 1128]
    tran0.writeAction("movir X16 56570")
    tran0.writeAction("slorii X16 X16 12 3027")
    tran0.writeAction("slorii X16 X16 12 1880")
    tran0.writeAction("slorii X16 X16 12 1698")
    tran0.writeAction("slorii X16 X16 12 3322")
    tran0.writeAction("slsubii X16 X17 15 1128")
    tran0.writeAction("yieldt")
    return efa
