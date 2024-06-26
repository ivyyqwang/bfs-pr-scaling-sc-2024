from EFA_v2 import *
def fadd_64_42():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [16205398956704169017, 4971965778707783617]
    tran0.writeAction("movir X16 57573")
    tran0.writeAction("slorii X16 X16 12 583")
    tran0.writeAction("slorii X16 X16 12 3521")
    tran0.writeAction("slorii X16 X16 12 3431")
    tran0.writeAction("slorii X16 X16 12 3129")
    tran0.writeAction("movir X17 17663")
    tran0.writeAction("slorii X17 X17 12 3976")
    tran0.writeAction("slorii X17 X17 12 2171")
    tran0.writeAction("slorii X17 X17 12 1129")
    tran0.writeAction("slorii X17 X17 12 4033")
    tran0.writeAction("fadd.64 X16 X17 X18")
    tran0.writeAction("yieldt")
    return efa
