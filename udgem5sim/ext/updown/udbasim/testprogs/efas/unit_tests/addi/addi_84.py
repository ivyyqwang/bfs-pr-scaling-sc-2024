from EFA_v2 import *
def addi_84():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-6940250917457913367, 26210]
    tran0.writeAction("movir X16 40879")
    tran0.writeAction("slorii X16 X16 12 1128")
    tran0.writeAction("slorii X16 X16 12 4036")
    tran0.writeAction("slorii X16 X16 12 3449")
    tran0.writeAction("slorii X16 X16 12 2537")
    tran0.writeAction("addi X16 X17 26210")
    tran0.writeAction("yieldt")
    return efa
