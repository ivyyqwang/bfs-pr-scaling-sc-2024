from EFA_v2 import *
def fsub_32_92():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [907149216, 278275822]
    tran0.writeAction("movir X16 0")
    tran0.writeAction("slorii X16 X16 12 0")
    tran0.writeAction("slorii X16 X16 12 54")
    tran0.writeAction("slorii X16 X16 12 287")
    tran0.writeAction("slorii X16 X16 12 4000")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("slorii X17 X17 12 0")
    tran0.writeAction("slorii X17 X17 12 16")
    tran0.writeAction("slorii X17 X17 12 2402")
    tran0.writeAction("slorii X17 X17 12 1774")
    tran0.writeAction("fsub.32 X16 X17 X18")
    tran0.writeAction("yieldt")
    return efa
