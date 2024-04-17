from EFA_v2 import *
def addi_2():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-5667468110614058673, 1717]
    tran0.writeAction("movir X16 45401")
    tran0.writeAction("slorii X16 X16 12 444")
    tran0.writeAction("slorii X16 X16 12 2026")
    tran0.writeAction("slorii X16 X16 12 4074")
    tran0.writeAction("slorii X16 X16 12 2383")
    tran0.writeAction("addi X16 X17 1717")
    tran0.writeAction("yieldt")
    return efa