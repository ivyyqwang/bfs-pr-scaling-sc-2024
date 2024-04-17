from EFA_v2 import *
def fmul_64_84():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [851134700649845280, 13225321590380296783]
    tran0.writeAction("movir X16 3023")
    tran0.writeAction("slorii X16 X16 12 3432")
    tran0.writeAction("slorii X16 X16 12 48")
    tran0.writeAction("slorii X16 X16 12 993")
    tran0.writeAction("slorii X16 X16 12 544")
    tran0.writeAction("movir X17 46985")
    tran0.writeAction("slorii X17 X17 12 3198")
    tran0.writeAction("slorii X17 X17 12 2666")
    tran0.writeAction("slorii X17 X17 12 3775")
    tran0.writeAction("slorii X17 X17 12 2639")
    tran0.writeAction("fmul.64 X16 X17 X18")
    tran0.writeAction("yieldt")
    return efa
