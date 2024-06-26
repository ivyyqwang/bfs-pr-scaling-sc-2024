from EFA_v2 import *
def fdiv_64_72():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [7264284094724650389, 398388930528966829]
    tran0.writeAction("movir X16 25807")
    tran0.writeAction("slorii X16 X16 12 3774")
    tran0.writeAction("slorii X16 X16 12 1397")
    tran0.writeAction("slorii X16 X16 12 2387")
    tran0.writeAction("slorii X16 X16 12 1429")
    tran0.writeAction("movir X17 1415")
    tran0.writeAction("slorii X17 X17 12 1481")
    tran0.writeAction("slorii X17 X17 12 3870")
    tran0.writeAction("slorii X17 X17 12 2567")
    tran0.writeAction("slorii X17 X17 12 2221")
    tran0.writeAction("fdiv.64 X16 X17 X18")
    tran0.writeAction("yieldt")
    return efa
