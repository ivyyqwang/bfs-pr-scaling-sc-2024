from EFA_v2 import *
def subi_40():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-8075330451678882554, -6685]
    tran0.writeAction("movir X16 36846")
    tran0.writeAction("slorii X16 X16 12 2715")
    tran0.writeAction("slorii X16 X16 12 3383")
    tran0.writeAction("slorii X16 X16 12 3217")
    tran0.writeAction("slorii X16 X16 12 1286")
    tran0.writeAction("subi X16 X17 -6685")
    tran0.writeAction("yieldt")
    return efa
