from EFA_v2 import *
def sraddii_46():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [467775345238718639, 9, 1476]
    tran0.writeAction("movir X16 1661")
    tran0.writeAction("slorii X16 X16 12 3571")
    tran0.writeAction("slorii X16 X16 12 695")
    tran0.writeAction("slorii X16 X16 12 2619")
    tran0.writeAction("slorii X16 X16 12 2223")
    tran0.writeAction("sraddii X16 X17 9 1476")
    tran0.writeAction("yieldt")
    return efa
