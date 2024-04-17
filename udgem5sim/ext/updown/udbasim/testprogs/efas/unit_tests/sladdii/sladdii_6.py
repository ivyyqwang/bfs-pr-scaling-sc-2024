from EFA_v2 import *
def sladdii_6():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-4383237750954030341, 7, 1968]
    tran0.writeAction("movir X16 49963")
    tran0.writeAction("slorii X16 X16 12 2503")
    tran0.writeAction("slorii X16 X16 12 3368")
    tran0.writeAction("slorii X16 X16 12 1240")
    tran0.writeAction("slorii X16 X16 12 2811")
    tran0.writeAction("sladdii X16 X17 7 1968")
    tran0.writeAction("yieldt")
    return efa
