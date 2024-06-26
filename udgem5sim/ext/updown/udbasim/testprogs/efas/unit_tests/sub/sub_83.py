from EFA_v2 import *
def sub_83():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [6918167253739375600, -7662336517332290992]
    tran0.writeAction("movir X16 24578")
    tran0.writeAction("slorii X16 X16 12 1095")
    tran0.writeAction("slorii X16 X16 12 1687")
    tran0.writeAction("slorii X16 X16 12 3584")
    tran0.writeAction("slorii X16 X16 12 3056")
    tran0.writeAction("movir X17 38313")
    tran0.writeAction("slorii X17 X17 12 3736")
    tran0.writeAction("slorii X17 X17 12 2246")
    tran0.writeAction("slorii X17 X17 12 3707")
    tran0.writeAction("slorii X17 X17 12 592")
    tran0.writeAction("sub X16 X17 X17 ")
    tran0.writeAction("yieldt")
    return efa
