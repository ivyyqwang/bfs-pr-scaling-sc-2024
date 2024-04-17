from EFA_v2 import *
def sari_1():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
    tran0.writeAction("movir X16 6537")
    tran0.writeAction("slorii X16 X16 12 1886")
    tran0.writeAction("slorii X16 X16 12 2884")
    tran0.writeAction("slorii X16 X16 12 2388")
    tran0.writeAction("slorii X16 X16 12 150")
    tran0.writeAction("movir X17 -3663")
    tran0.writeAction("slorii X17 X17 12 3740")
    tran0.writeAction("slorii X17 X17 12 1822")
    tran0.writeAction("slorii X17 X17 12 2912")
    tran0.writeAction("slorii X17 X17 12 1596")
    tran0.writeAction("sari X16 X17 27")
    tran0.writeAction(f"print '%d,%d' X16 X17")
    tran0.writeAction("yieldt")
    return efa
