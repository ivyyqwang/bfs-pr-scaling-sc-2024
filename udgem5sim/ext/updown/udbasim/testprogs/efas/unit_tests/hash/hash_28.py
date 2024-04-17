from EFA_v2 import *
def hash_28():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [4996340954016374181, -7529838952868923845]
    tran0.writeAction("movir X16 17750")
    tran0.writeAction("slorii X16 X16 12 2330")
    tran0.writeAction("slorii X16 X16 12 60")
    tran0.writeAction("slorii X16 X16 12 3613")
    tran0.writeAction("slorii X16 X16 12 3493")
    tran0.writeAction("movir X17 38784")
    tran0.writeAction("slorii X17 X17 12 2613")
    tran0.writeAction("slorii X17 X17 12 3582")
    tran0.writeAction("slorii X17 X17 12 1427")
    tran0.writeAction("slorii X17 X17 12 1595")
    tran0.writeAction("hash X16 X17")
    tran0.writeAction("yieldt")
    return efa
