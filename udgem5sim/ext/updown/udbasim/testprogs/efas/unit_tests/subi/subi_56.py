from EFA_v2 import *
def subi_56():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [3152634141204017832, 6317]
    tran0.writeAction("movir X16 11200")
    tran0.writeAction("slorii X16 X16 12 1664")
    tran0.writeAction("slorii X16 X16 12 3149")
    tran0.writeAction("slorii X16 X16 12 959")
    tran0.writeAction("slorii X16 X16 12 680")
    tran0.writeAction("subi X16 X17 6317")
    tran0.writeAction("yieldt")
    return efa
