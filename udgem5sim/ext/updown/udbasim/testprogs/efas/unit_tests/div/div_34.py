from EFA_v2 import *
def div_34():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [5964767367233493482, 4009324679571990194]
    tran0.writeAction("movir X16 21191")
    tran0.writeAction("slorii X16 X16 12 453")
    tran0.writeAction("slorii X16 X16 12 347")
    tran0.writeAction("slorii X16 X16 12 3253")
    tran0.writeAction("slorii X16 X16 12 2538")
    tran0.writeAction("movir X17 14243")
    tran0.writeAction("slorii X17 X17 12 4024")
    tran0.writeAction("slorii X17 X17 12 3523")
    tran0.writeAction("slorii X17 X17 12 390")
    tran0.writeAction("slorii X17 X17 12 1714")
    tran0.writeAction("div X16 X17 X17 ")
    tran0.writeAction("yieldt")
    return efa
