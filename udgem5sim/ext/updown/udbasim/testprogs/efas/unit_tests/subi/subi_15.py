from EFA_v2 import *
def subi_15():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [661162348519890701, 10498]
    tran0.writeAction("movir X16 2348")
    tran0.writeAction("slorii X16 X16 12 3770")
    tran0.writeAction("slorii X16 X16 12 1834")
    tran0.writeAction("slorii X16 X16 12 1601")
    tran0.writeAction("slorii X16 X16 12 3853")
    tran0.writeAction("subi X16 X17 10498")
    tran0.writeAction("yieldt")
    return efa