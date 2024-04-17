from EFA_v2 import *
def fdiv_64_89():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [17524097827473279800, 10112482484236387575]
    tran0.writeAction("movir X16 62258")
    tran0.writeAction("slorii X16 X16 12 418")
    tran0.writeAction("slorii X16 X16 12 159")
    tran0.writeAction("slorii X16 X16 12 3028")
    tran0.writeAction("slorii X16 X16 12 2872")
    tran0.writeAction("movir X17 35926")
    tran0.writeAction("slorii X17 X17 12 3091")
    tran0.writeAction("slorii X17 X17 12 3518")
    tran0.writeAction("slorii X17 X17 12 1104")
    tran0.writeAction("slorii X17 X17 12 1271")
    tran0.writeAction("fdiv.64 X16 X17 X18")
    tran0.writeAction("yieldt")
    return efa
