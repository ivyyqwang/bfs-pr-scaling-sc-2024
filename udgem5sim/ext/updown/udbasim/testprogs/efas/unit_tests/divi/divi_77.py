from EFA_v2 import *
def divi_77():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-6150851065663575673, -8403]
    tran0.writeAction("movir X16 43683")
    tran0.writeAction("slorii X16 X16 12 3224")
    tran0.writeAction("slorii X16 X16 12 2908")
    tran0.writeAction("slorii X16 X16 12 3234")
    tran0.writeAction("slorii X16 X16 12 2439")
    tran0.writeAction("divi X16 X17 -8403")
    tran0.writeAction("yieldt")
    return efa
