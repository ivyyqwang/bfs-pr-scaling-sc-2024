from EFA_v2 import *
def slsubii_66():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-729493378615670571, 11, 179]
    tran0.writeAction("movir X16 62944")
    tran0.writeAction("slorii X16 X16 12 1306")
    tran0.writeAction("slorii X16 X16 12 797")
    tran0.writeAction("slorii X16 X16 12 2512")
    tran0.writeAction("slorii X16 X16 12 2261")
    tran0.writeAction("slsubii X16 X17 11 179")
    tran0.writeAction("yieldt")
    return efa
