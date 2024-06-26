from EFA_v2 import *
def fadd_64_7():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [14150652795084096530, 12104250417731294770]
    tran0.writeAction("movir X16 50273")
    tran0.writeAction("slorii X16 X16 12 891")
    tran0.writeAction("slorii X16 X16 12 3686")
    tran0.writeAction("slorii X16 X16 12 3588")
    tran0.writeAction("slorii X16 X16 12 1042")
    tran0.writeAction("movir X17 43002")
    tran0.writeAction("slorii X17 X17 12 3833")
    tran0.writeAction("slorii X17 X17 12 4021")
    tran0.writeAction("slorii X17 X17 12 1013")
    tran0.writeAction("slorii X17 X17 12 1586")
    tran0.writeAction("fadd.64 X16 X17 X18")
    tran0.writeAction("yieldt")
    return efa
