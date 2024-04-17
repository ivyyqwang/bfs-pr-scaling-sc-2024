from EFA_v2 import *
def mod_56():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [3304319376807332939, -8709489979296653967]
    tran0.writeAction("movir X16 11739")
    tran0.writeAction("slorii X16 X16 12 1231")
    tran0.writeAction("slorii X16 X16 12 1879")
    tran0.writeAction("slorii X16 X16 12 168")
    tran0.writeAction("slorii X16 X16 12 3147")
    tran0.writeAction("movir X17 34593")
    tran0.writeAction("slorii X17 X17 12 2768")
    tran0.writeAction("slorii X17 X17 12 569")
    tran0.writeAction("slorii X17 X17 12 813")
    tran0.writeAction("slorii X17 X17 12 3441")
    tran0.writeAction("mod X16 X17 X17 ")
    tran0.writeAction("yieldt")
    return efa
