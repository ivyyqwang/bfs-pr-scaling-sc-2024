from EFA_v2 import *
def divi_16():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-1357426425330831190, 9620]
    tran0.writeAction("movir X16 60713")
    tran0.writeAction("slorii X16 X16 12 1853")
    tran0.writeAction("slorii X16 X16 12 2989")
    tran0.writeAction("slorii X16 X16 12 1751")
    tran0.writeAction("slorii X16 X16 12 170")
    tran0.writeAction("divi X16 X17 9620")
    tran0.writeAction("yieldt")
    return efa
