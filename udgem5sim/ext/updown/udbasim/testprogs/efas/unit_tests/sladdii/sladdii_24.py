from EFA_v2 import *
def sladdii_24():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [6358275054237633786, 13, 1617]
    tran0.writeAction("movir X16 22589")
    tran0.writeAction("slorii X16 X16 12 535")
    tran0.writeAction("slorii X16 X16 12 2408")
    tran0.writeAction("slorii X16 X16 12 252")
    tran0.writeAction("slorii X16 X16 12 3322")
    tran0.writeAction("sladdii X16 X17 13 1617")
    tran0.writeAction("yieldt")
    return efa
