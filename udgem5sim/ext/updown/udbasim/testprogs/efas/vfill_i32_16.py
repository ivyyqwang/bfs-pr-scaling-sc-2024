from EFA_v2 import *
def vfill_i32_16():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [752116720, -1545330286, 1120]
    tran0.writeAction("movir X18 0")
    tran0.writeAction("slorii X18 X18 12 2622")
    tran0.writeAction("slorii X18 X18 12 1057")
    tran0.writeAction("slorii X18 X18 8 146")
    tran0.writeAction("slorii X18 X18 12 717")
    tran0.writeAction("slorii X18 X18 12 1123")
    tran0.writeAction("slorii X18 X18 8 240")
    tran0.writeAction("vfill.i32 X18 1120 ")
    tran0.writeAction("yieldt")
    return efa
