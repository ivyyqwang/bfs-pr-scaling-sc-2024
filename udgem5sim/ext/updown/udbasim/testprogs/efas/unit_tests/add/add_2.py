from EFA_v2 import *
def add_2():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [6637921473675629578, -2685448188043597966]
    tran0.writeAction("movir X16 23582")
    tran0.writeAction("slorii X16 X16 12 2598")
    tran0.writeAction("slorii X16 X16 12 2365")
    tran0.writeAction("slorii X16 X16 12 1529")
    tran0.writeAction("slorii X16 X16 12 1034")
    tran0.writeAction("movir X17 55995")
    tran0.writeAction("slorii X17 X17 12 1521")
    tran0.writeAction("slorii X17 X17 12 2528")
    tran0.writeAction("slorii X17 X17 12 3870")
    tran0.writeAction("slorii X17 X17 12 1906")
    tran0.writeAction("add X16 X17 X17 ")
    tran0.writeAction("yieldt")
    return efa
