from EFA_v2 import *
def srsubii_75():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [4639580404036975984, 9, 1951]
    tran0.writeAction("movir X16 16483")
    tran0.writeAction("slorii X16 X16 12 412")
    tran0.writeAction("slorii X16 X16 12 3009")
    tran0.writeAction("slorii X16 X16 12 1995")
    tran0.writeAction("slorii X16 X16 12 3440")
    tran0.writeAction("srsubii X16 X17 9 1951")
    tran0.writeAction("yieldt")
    return efa
