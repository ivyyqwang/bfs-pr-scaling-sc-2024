from EFA_v2 import *
def div_91():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [6439865379133324901, -1293823520445960231]
    tran0.writeAction("movir X16 22878")
    tran0.writeAction("slorii X16 X16 12 4087")
    tran0.writeAction("slorii X16 X16 12 324")
    tran0.writeAction("slorii X16 X16 12 2367")
    tran0.writeAction("slorii X16 X16 12 3685")
    tran0.writeAction("movir X17 60939")
    tran0.writeAction("slorii X17 X17 12 1701")
    tran0.writeAction("slorii X17 X17 12 3317")
    tran0.writeAction("slorii X17 X17 12 3166")
    tran0.writeAction("slorii X17 X17 12 4057")
    tran0.writeAction("div X16 X17 X17 ")
    tran0.writeAction("yieldt")
    return efa
