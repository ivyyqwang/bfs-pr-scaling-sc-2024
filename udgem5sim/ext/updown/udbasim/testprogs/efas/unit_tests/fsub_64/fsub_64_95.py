from EFA_v2 import *
def fsub_64_95():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [1001945981833071114, 1053594711325759659]
    tran0.writeAction("movir X16 3559")
    tran0.writeAction("slorii X16 X16 12 2568")
    tran0.writeAction("slorii X16 X16 12 4059")
    tran0.writeAction("slorii X16 X16 12 1188")
    tran0.writeAction("slorii X16 X16 12 2570")
    tran0.writeAction("movir X17 3743")
    tran0.writeAction("slorii X17 X17 12 492")
    tran0.writeAction("slorii X17 X17 12 3785")
    tran0.writeAction("slorii X17 X17 12 3285")
    tran0.writeAction("slorii X17 X17 12 2219")
    tran0.writeAction("fsub.64 X16 X17 X18")
    tran0.writeAction("yieldt")
    return efa
