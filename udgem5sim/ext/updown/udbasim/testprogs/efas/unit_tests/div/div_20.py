from EFA_v2 import *
def div_20():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-5098963940185317368, 7109067986276214381]
    tran0.writeAction("movir X16 47420")
    tran0.writeAction("slorii X16 X16 12 3444")
    tran0.writeAction("slorii X16 X16 12 4054")
    tran0.writeAction("slorii X16 X16 12 2982")
    tran0.writeAction("slorii X16 X16 12 8")
    tran0.writeAction("movir X17 25256")
    tran0.writeAction("slorii X17 X17 12 1978")
    tran0.writeAction("slorii X17 X17 12 2822")
    tran0.writeAction("slorii X17 X17 12 390")
    tran0.writeAction("slorii X17 X17 12 1645")
    tran0.writeAction("div X16 X17 X17 ")
    tran0.writeAction("yieldt")
    return efa
