from EFA_v2 import *
def fsub_64_10():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [13474119615670950805, 17737977067519021350]
    tran0.writeAction("movir X16 47869")
    tran0.writeAction("slorii X16 X16 12 2822")
    tran0.writeAction("slorii X16 X16 12 1737")
    tran0.writeAction("slorii X16 X16 12 777")
    tran0.writeAction("slorii X16 X16 12 2965")
    tran0.writeAction("movir X17 63017")
    tran0.writeAction("slorii X17 X17 12 3906")
    tran0.writeAction("slorii X17 X17 12 2495")
    tran0.writeAction("slorii X17 X17 12 2033")
    tran0.writeAction("slorii X17 X17 12 294")
    tran0.writeAction("fsub.64 X16 X17 X18")
    tran0.writeAction("yieldt")
    return efa
