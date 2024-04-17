from EFA_v2 import *
def hash_73():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-2626614107060788084, -1150605354777397151]
    tran0.writeAction("movir X16 56204")
    tran0.writeAction("slorii X16 X16 12 1606")
    tran0.writeAction("slorii X16 X16 12 722")
    tran0.writeAction("slorii X16 X16 12 2506")
    tran0.writeAction("slorii X16 X16 12 1164")
    tran0.writeAction("movir X17 61448")
    tran0.writeAction("slorii X17 X17 12 936")
    tran0.writeAction("slorii X17 X17 12 1703")
    tran0.writeAction("slorii X17 X17 12 3403")
    tran0.writeAction("slorii X17 X17 12 2145")
    tran0.writeAction("hash X16 X17")
    tran0.writeAction("yieldt")
    return efa
