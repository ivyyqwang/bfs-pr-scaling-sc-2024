from EFA_v2 import *
def modi_72():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [3117268332160711741, -25134]
    tran0.writeAction("movir X16 11074")
    tran0.writeAction("slorii X16 X16 12 3120")
    tran0.writeAction("slorii X16 X16 12 2104")
    tran0.writeAction("slorii X16 X16 12 55")
    tran0.writeAction("slorii X16 X16 12 3133")
    tran0.writeAction("modi X16 X17 -25134")
    tran0.writeAction("yieldt")
    return efa
