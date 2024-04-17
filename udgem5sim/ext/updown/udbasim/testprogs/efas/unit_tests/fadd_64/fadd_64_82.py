from EFA_v2 import *
def fadd_64_82():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [15327017640307564578, 10939758560838916199]
    tran0.writeAction("movir X16 54452")
    tran0.writeAction("slorii X16 X16 12 2069")
    tran0.writeAction("slorii X16 X16 12 1660")
    tran0.writeAction("slorii X16 X16 12 2778")
    tran0.writeAction("slorii X16 X16 12 34")
    tran0.writeAction("movir X17 38865")
    tran0.writeAction("slorii X17 X17 12 3399")
    tran0.writeAction("slorii X17 X17 12 803")
    tran0.writeAction("slorii X17 X17 12 1401")
    tran0.writeAction("slorii X17 X17 12 2151")
    tran0.writeAction("fadd.64 X16 X17 X18")
    tran0.writeAction("yieldt")
    return efa