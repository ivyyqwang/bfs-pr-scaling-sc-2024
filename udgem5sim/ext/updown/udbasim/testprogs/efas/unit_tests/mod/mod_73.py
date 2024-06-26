from EFA_v2 import *
def mod_73():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [6516749554341137873, -2355523177449730482]
    tran0.writeAction("movir X16 23152")
    tran0.writeAction("slorii X16 X16 12 595")
    tran0.writeAction("slorii X16 X16 12 324")
    tran0.writeAction("slorii X16 X16 12 2820")
    tran0.writeAction("slorii X16 X16 12 3537")
    tran0.writeAction("movir X17 57167")
    tran0.writeAction("slorii X17 X17 12 2050")
    tran0.writeAction("slorii X17 X17 12 1651")
    tran0.writeAction("slorii X17 X17 12 3724")
    tran0.writeAction("slorii X17 X17 12 3662")
    tran0.writeAction("mod X16 X17 X17 ")
    tran0.writeAction("yieldt")
    return efa
