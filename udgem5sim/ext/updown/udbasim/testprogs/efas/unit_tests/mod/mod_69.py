from EFA_v2 import *
def mod_69():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-4868760517485859032, 2479617017950011368]
    tran0.writeAction("movir X16 48238")
    tran0.writeAction("slorii X16 X16 12 2817")
    tran0.writeAction("slorii X16 X16 12 2794")
    tran0.writeAction("slorii X16 X16 12 3310")
    tran0.writeAction("slorii X16 X16 12 3880")
    tran0.writeAction("movir X17 8809")
    tran0.writeAction("slorii X17 X17 12 1512")
    tran0.writeAction("slorii X17 X17 12 2637")
    tran0.writeAction("slorii X17 X17 12 3783")
    tran0.writeAction("slorii X17 X17 12 4072")
    tran0.writeAction("mod X16 X17 X17 ")
    tran0.writeAction("yieldt")
    return efa
