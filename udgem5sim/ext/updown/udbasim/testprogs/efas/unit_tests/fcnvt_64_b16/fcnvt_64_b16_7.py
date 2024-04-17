from EFA_v2 import *
def fcnvt_64_b16_7():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [9422224182559619947]
    tran0.writeAction("movir X16 33474")
    tran0.writeAction("slorii X16 X16 12 1903")
    tran0.writeAction("slorii X16 X16 12 2323")
    tran0.writeAction("slorii X16 X16 12 2299")
    tran0.writeAction("slorii X16 X16 12 2923")
    tran0.writeAction("fcnvt.64.b16 X16 X16")
    tran0.writeAction("yieldt")
    return efa