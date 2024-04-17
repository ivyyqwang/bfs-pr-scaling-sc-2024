from EFA_v2 import *
def hash_37():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-3779852816191073527, 9169547212969625369]
    tran0.writeAction("movir X16 52107")
    tran0.writeAction("slorii X16 X16 12 1086")
    tran0.writeAction("slorii X16 X16 12 995")
    tran0.writeAction("slorii X16 X16 12 2749")
    tran0.writeAction("slorii X16 X16 12 777")
    tran0.writeAction("movir X17 32576")
    tran0.writeAction("slorii X17 X17 12 3177")
    tran0.writeAction("slorii X17 X17 12 2972")
    tran0.writeAction("slorii X17 X17 12 932")
    tran0.writeAction("slorii X17 X17 12 1817")
    tran0.writeAction("hash X16 X17")
    tran0.writeAction("yieldt")
    return efa
