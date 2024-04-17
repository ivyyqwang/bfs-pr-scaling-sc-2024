from EFA_v2 import *
def muli_98():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-8959802750567522963, -1686]
    tran0.writeAction("movir X16 33704")
    tran0.writeAction("slorii X16 X16 12 1581")
    tran0.writeAction("slorii X16 X16 12 3730")
    tran0.writeAction("slorii X16 X16 12 3501")
    tran0.writeAction("slorii X16 X16 12 3437")
    tran0.writeAction("muli X16 X17 -1686")
    tran0.writeAction("yieldt")
    return efa
