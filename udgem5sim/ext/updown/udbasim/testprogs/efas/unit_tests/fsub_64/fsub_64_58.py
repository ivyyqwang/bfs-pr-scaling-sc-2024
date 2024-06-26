from EFA_v2 import *
def fsub_64_58():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [9906505268821749912, 2483867827805034193]
    tran0.writeAction("movir X16 35194")
    tran0.writeAction("slorii X16 X16 12 4000")
    tran0.writeAction("slorii X16 X16 12 3609")
    tran0.writeAction("slorii X16 X16 12 2687")
    tran0.writeAction("slorii X16 X16 12 152")
    tran0.writeAction("movir X17 8824")
    tran0.writeAction("slorii X17 X17 12 1930")
    tran0.writeAction("slorii X17 X17 12 281")
    tran0.writeAction("slorii X17 X17 12 1393")
    tran0.writeAction("slorii X17 X17 12 1745")
    tran0.writeAction("fsub.64 X16 X17 X18")
    tran0.writeAction("yieldt")
    return efa
