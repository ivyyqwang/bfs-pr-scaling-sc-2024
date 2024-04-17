from EFA_v2 import *
def mul_66():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-1146259327023558845, 5270449378450588079]
    tran0.writeAction("movir X16 61463")
    tran0.writeAction("slorii X16 X16 12 2739")
    tran0.writeAction("slorii X16 X16 12 1816")
    tran0.writeAction("slorii X16 X16 12 1156")
    tran0.writeAction("slorii X16 X16 12 3907")
    tran0.writeAction("movir X17 18724")
    tran0.writeAction("slorii X17 X17 12 1628")
    tran0.writeAction("slorii X17 X17 12 2337")
    tran0.writeAction("slorii X17 X17 12 924")
    tran0.writeAction("slorii X17 X17 12 431")
    tran0.writeAction("mul X16 X17 X17 ")
    tran0.writeAction("yieldt")
    return efa
