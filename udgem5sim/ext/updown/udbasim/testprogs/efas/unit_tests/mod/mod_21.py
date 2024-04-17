from EFA_v2 import *
def mod_21():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-5984137534694779183, 7687451250898633915]
    tran0.writeAction("movir X16 44276")
    tran0.writeAction("slorii X16 X16 12 297")
    tran0.writeAction("slorii X16 X16 12 3605")
    tran0.writeAction("slorii X16 X16 12 1785")
    tran0.writeAction("slorii X16 X16 12 1745")
    tran0.writeAction("movir X17 27311")
    tran0.writeAction("slorii X17 X17 12 1282")
    tran0.writeAction("slorii X17 X17 12 3789")
    tran0.writeAction("slorii X17 X17 12 3872")
    tran0.writeAction("slorii X17 X17 12 1211")
    tran0.writeAction("mod X16 X17 X17 ")
    tran0.writeAction("yieldt")
    return efa
