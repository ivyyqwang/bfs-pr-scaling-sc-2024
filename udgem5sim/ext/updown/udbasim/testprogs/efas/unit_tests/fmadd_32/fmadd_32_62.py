from EFA_v2 import *
def fmadd_32_62():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [566550774, 3469349163, 734952293]
    tran0.writeAction("movir X16 0")
    tran0.writeAction("slorii X16 X16 12 0")
    tran0.writeAction("slorii X16 X16 12 33")
    tran0.writeAction("slorii X16 X16 12 3150")
    tran0.writeAction("slorii X16 X16 12 246")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("slorii X17 X17 12 0")
    tran0.writeAction("slorii X17 X17 12 206")
    tran0.writeAction("slorii X17 X17 12 3233")
    tran0.writeAction("slorii X17 X17 12 299")
    tran0.writeAction("movir X18 0")
    tran0.writeAction("slorii X18 X18 12 0")
    tran0.writeAction("slorii X18 X18 12 43")
    tran0.writeAction("slorii X18 X18 12 3303")
    tran0.writeAction("slorii X18 X18 12 2917")
    tran0.writeAction("fmadd.32 X16 X17 X18")
    tran0.writeAction("yieldt")
    return efa
