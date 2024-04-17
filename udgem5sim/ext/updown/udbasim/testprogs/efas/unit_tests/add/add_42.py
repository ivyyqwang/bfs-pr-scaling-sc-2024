from EFA_v2 import *
def add_42():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-5707560790080674464, -7235666487796346251]
    tran0.writeAction("movir X16 45258")
    tran0.writeAction("slorii X16 X16 12 2747")
    tran0.writeAction("slorii X16 X16 12 909")
    tran0.writeAction("slorii X16 X16 12 1202")
    tran0.writeAction("slorii X16 X16 12 1376")
    tran0.writeAction("movir X17 39829")
    tran0.writeAction("slorii X17 X17 12 3066")
    tran0.writeAction("slorii X17 X17 12 2657")
    tran0.writeAction("slorii X17 X17 12 2869")
    tran0.writeAction("slorii X17 X17 12 629")
    tran0.writeAction("add X16 X17 X17 ")
    tran0.writeAction("yieldt")
    return efa
