from EFA_v2 import *
def modi_29():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-3764151080879876815, -6946]
    tran0.writeAction("movir X16 52163")
    tran0.writeAction("slorii X16 X16 12 200")
    tran0.writeAction("slorii X16 X16 12 2311")
    tran0.writeAction("slorii X16 X16 12 1033")
    tran0.writeAction("slorii X16 X16 12 1329")
    tran0.writeAction("modi X16 X17 -6946")
    tran0.writeAction("yieldt")
    return efa
