from EFA_v2 import *
def fdiv_64_78():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [17189853682245594517, 4392592775875767823]
    tran0.writeAction("movir X16 61070")
    tran0.writeAction("slorii X16 X16 12 2573")
    tran0.writeAction("slorii X16 X16 12 2343")
    tran0.writeAction("slorii X16 X16 12 774")
    tran0.writeAction("slorii X16 X16 12 3477")
    tran0.writeAction("movir X17 15605")
    tran0.writeAction("slorii X17 X17 12 2557")
    tran0.writeAction("slorii X17 X17 12 2897")
    tran0.writeAction("slorii X17 X17 12 90")
    tran0.writeAction("slorii X17 X17 12 3599")
    tran0.writeAction("fdiv.64 X16 X17 X18")
    tran0.writeAction("yieldt")
    return efa
