from EFA_v2 import *
def slsubii_68():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-7453793667622761535, 12, 1178]
    tran0.writeAction("movir X16 39054")
    tran0.writeAction("slorii X16 X16 12 3298")
    tran0.writeAction("slorii X16 X16 12 1716")
    tran0.writeAction("slorii X16 X16 12 1184")
    tran0.writeAction("slorii X16 X16 12 3009")
    tran0.writeAction("slsubii X16 X17 12 1178")
    tran0.writeAction("yieldt")
    return efa
