from EFA_v2 import *
def modi_33():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-6912513249475928894, -11795]
    tran0.writeAction("movir X16 40977")
    tran0.writeAction("slorii X16 X16 12 3357")
    tran0.writeAction("slorii X16 X16 12 731")
    tran0.writeAction("slorii X16 X16 12 3301")
    tran0.writeAction("slorii X16 X16 12 3266")
    tran0.writeAction("modi X16 X17 -11795")
    tran0.writeAction("yieldt")
    return efa
