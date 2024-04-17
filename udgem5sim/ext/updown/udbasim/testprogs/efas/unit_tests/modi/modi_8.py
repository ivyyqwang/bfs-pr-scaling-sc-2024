from EFA_v2 import *
def modi_8():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [6771367937023644516, -18550]
    tran0.writeAction("movir X16 24056")
    tran0.writeAction("slorii X16 X16 12 2996")
    tran0.writeAction("slorii X16 X16 12 817")
    tran0.writeAction("slorii X16 X16 12 3129")
    tran0.writeAction("slorii X16 X16 12 868")
    tran0.writeAction("modi X16 X17 -18550")
    tran0.writeAction("yieldt")
    return efa