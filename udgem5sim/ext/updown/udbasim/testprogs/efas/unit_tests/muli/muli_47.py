from EFA_v2 import *
def muli_47():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-8139890164774549974, 26542]
    tran0.writeAction("movir X16 36617")
    tran0.writeAction("slorii X16 X16 12 1232")
    tran0.writeAction("slorii X16 X16 12 1449")
    tran0.writeAction("slorii X16 X16 12 3756")
    tran0.writeAction("slorii X16 X16 12 1578")
    tran0.writeAction("muli X16 X17 26542")
    tran0.writeAction("yieldt")
    return efa
