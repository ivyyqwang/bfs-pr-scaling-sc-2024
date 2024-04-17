from EFA_v2 import *
def hash_58():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-4157477918162130204, 110609228316577653]
    tran0.writeAction("movir X16 50765")
    tran0.writeAction("slorii X16 X16 12 2749")
    tran0.writeAction("slorii X16 X16 12 3158")
    tran0.writeAction("slorii X16 X16 12 1702")
    tran0.writeAction("slorii X16 X16 12 2788")
    tran0.writeAction("movir X17 392")
    tran0.writeAction("slorii X17 X17 12 3944")
    tran0.writeAction("slorii X17 X17 12 466")
    tran0.writeAction("slorii X17 X17 12 2824")
    tran0.writeAction("slorii X17 X17 12 3957")
    tran0.writeAction("hash X16 X17")
    tran0.writeAction("yieldt")
    return efa