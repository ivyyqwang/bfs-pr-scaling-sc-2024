from EFA_v2 import *
def muli_56():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-4766558149548520202, 23192]
    tran0.writeAction("movir X16 48601")
    tran0.writeAction("slorii X16 X16 12 3209")
    tran0.writeAction("slorii X16 X16 12 3590")
    tran0.writeAction("slorii X16 X16 12 3756")
    tran0.writeAction("slorii X16 X16 12 3318")
    tran0.writeAction("muli X16 X17 23192")
    tran0.writeAction("yieldt")
    return efa
