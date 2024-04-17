from EFA_v2 import *
def addi_30():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-8805129296492960903, 30538]
    tran0.writeAction("movir X16 34253")
    tran0.writeAction("slorii X16 X16 12 3672")
    tran0.writeAction("slorii X16 X16 12 3697")
    tran0.writeAction("slorii X16 X16 12 622")
    tran0.writeAction("slorii X16 X16 12 889")
    tran0.writeAction("addi X16 X17 30538")
    tran0.writeAction("yieldt")
    return efa
