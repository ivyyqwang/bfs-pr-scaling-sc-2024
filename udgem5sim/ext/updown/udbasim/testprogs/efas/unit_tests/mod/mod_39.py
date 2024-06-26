from EFA_v2 import *
def mod_39():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-822119031696182054, 8770108840239357376]
    tran0.writeAction("movir X16 62615")
    tran0.writeAction("slorii X16 X16 12 1009")
    tran0.writeAction("slorii X16 X16 12 2224")
    tran0.writeAction("slorii X16 X16 12 2707")
    tran0.writeAction("slorii X16 X16 12 1242")
    tran0.writeAction("movir X17 31157")
    tran0.writeAction("slorii X17 X17 12 2808")
    tran0.writeAction("slorii X17 X17 12 1583")
    tran0.writeAction("slorii X17 X17 12 4013")
    tran0.writeAction("slorii X17 X17 12 3520")
    tran0.writeAction("mod X16 X17 X17 ")
    tran0.writeAction("yieldt")
    return efa
