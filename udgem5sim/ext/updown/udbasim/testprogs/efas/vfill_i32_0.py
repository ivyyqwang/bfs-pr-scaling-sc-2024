from EFA_v2 import *
def vfill_i32_0():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [583954991, 765755019, 91]
    tran0.writeAction("movir X18 0")
    tran0.writeAction("slorii X18 X18 12 730")
    tran0.writeAction("slorii X18 X18 12 1150")
    tran0.writeAction("slorii X18 X18 8 139")
    tran0.writeAction("slorii X18 X18 12 556")
    tran0.writeAction("slorii X18 X18 12 3698")
    tran0.writeAction("slorii X18 X18 8 47")
    tran0.writeAction("vfill.i32 X18 91 ")
    tran0.writeAction("yieldt")
    return efa
