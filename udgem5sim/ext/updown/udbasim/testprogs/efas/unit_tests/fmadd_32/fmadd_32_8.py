from EFA_v2 import *
def fmadd_32_8():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [722376120, 3352510445, 483949081]
    tran0.writeAction("movir X16 0")
    tran0.writeAction("slorii X16 X16 12 0")
    tran0.writeAction("slorii X16 X16 12 43")
    tran0.writeAction("slorii X16 X16 12 233")
    tran0.writeAction("slorii X16 X16 12 1464")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("slorii X17 X17 12 0")
    tran0.writeAction("slorii X17 X17 12 199")
    tran0.writeAction("slorii X17 X17 12 3379")
    tran0.writeAction("slorii X17 X17 12 4077")
    tran0.writeAction("movir X18 0")
    tran0.writeAction("slorii X18 X18 12 0")
    tran0.writeAction("slorii X18 X18 12 28")
    tran0.writeAction("slorii X18 X18 12 3463")
    tran0.writeAction("slorii X18 X18 12 2585")
    tran0.writeAction("fmadd.32 X16 X17 X18")
    tran0.writeAction("yieldt")
    return efa
