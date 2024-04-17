from EFA_v2 import *
def sri_3():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
    tran0.writeAction("movir X16 -5730")
    tran0.writeAction("slorii X16 X16 12 1812")
    tran0.writeAction("slorii X16 X16 12 1151")
    tran0.writeAction("slorii X16 X16 12 1936")
    tran0.writeAction("slorii X16 X16 12 3792")
    tran0.writeAction("movir X17 17370")
    tran0.writeAction("slorii X17 X17 12 533")
    tran0.writeAction("slorii X17 X17 12 1891")
    tran0.writeAction("slorii X17 X17 12 2583")
    tran0.writeAction("slorii X17 X17 12 3273")
    tran0.writeAction("sri X16 X17 39")
    tran0.writeAction(f"print '%d,%d' X16 X17")
    tran0.writeAction("yieldt")
    return efa