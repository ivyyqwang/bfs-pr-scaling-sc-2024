from EFA_v2 import *
def addi_82():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [8602418519449511318, 8038]
    tran0.writeAction("movir X16 30561")
    tran0.writeAction("slorii X16 X16 12 3809")
    tran0.writeAction("slorii X16 X16 12 221")
    tran0.writeAction("slorii X16 X16 12 122")
    tran0.writeAction("slorii X16 X16 12 1430")
    tran0.writeAction("addi X16 X17 8038")
    tran0.writeAction("yieldt")
    return efa
