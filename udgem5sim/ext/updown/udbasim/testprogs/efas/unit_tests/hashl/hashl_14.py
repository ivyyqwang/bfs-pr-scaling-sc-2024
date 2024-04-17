from EFA_v2 import *
def hashl_14():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [3423903608351472196, 2271728457046630758, -8921549338970093909, 7572504243101348949, -5413003025981211009, -6401230834693447974]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 12164")
    tran0.writeAction("slorii X17 X17 12 611")
    tran0.writeAction("slorii X17 X17 12 240")
    tran0.writeAction("slorii X17 X17 12 3963")
    tran0.writeAction("slorii X17 X17 12 2628")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 8070")
    tran0.writeAction("slorii X17 X17 12 3279")
    tran0.writeAction("slorii X17 X17 12 3804")
    tran0.writeAction("slorii X17 X17 12 1682")
    tran0.writeAction("slorii X17 X17 12 358")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 33840")
    tran0.writeAction("slorii X17 X17 12 1186")
    tran0.writeAction("slorii X17 X17 12 1284")
    tran0.writeAction("slorii X17 X17 12 2320")
    tran0.writeAction("slorii X17 X17 12 1707")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 26902")
    tran0.writeAction("slorii X17 X17 12 3847")
    tran0.writeAction("slorii X17 X17 12 3326")
    tran0.writeAction("slorii X17 X17 12 795")
    tran0.writeAction("slorii X17 X17 12 1109")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 46305")
    tran0.writeAction("slorii X17 X17 12 614")
    tran0.writeAction("slorii X17 X17 12 3420")
    tran0.writeAction("slorii X17 X17 12 1127")
    tran0.writeAction("slorii X17 X17 12 3711")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 42794")
    tran0.writeAction("slorii X17 X17 12 1063")
    tran0.writeAction("slorii X17 X17 12 2196")
    tran0.writeAction("slorii X17 X17 12 3357")
    tran0.writeAction("slorii X17 X17 12 3802")
    tran0.writeAction("hashl X16 X17 5")
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movrl X17 0(X16) 0 8")
    tran0.writeAction("yieldt")
    return efa
