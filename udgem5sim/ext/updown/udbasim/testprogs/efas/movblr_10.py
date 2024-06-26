from EFA_v2 import *
def movblr_10():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
    tran0.writeAction("movir X16 0")
    tran0.writeAction("slorii X16 X16 12 0")
    tran0.writeAction("slorii X16 X16 12 0")
    tran0.writeAction("slorii X16 X16 12 24")
    tran0.writeAction("slorii X16 X16 12 1484")
    tran0.writeAction("addi X16 X21 0")
    tran0.writeAction("sli X7 X19 3")
    tran0.writeAction("add X16 X19 X16")
    tran0.writeAction("movbil X16 7 222")
    tran0.writeAction("movblr X16 X17 7")
    tran0.writeAction("yieldt")
    return efa
