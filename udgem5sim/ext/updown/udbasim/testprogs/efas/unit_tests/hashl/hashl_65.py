from EFA_v2 import *
def hashl_65():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-304249318788744688, -2716913071307149306, 2236649260163971699, 5550680239187316726, 5677218049093166556, 2467721371978184542]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 64455")
    tran0.writeAction("slorii X17 X17 12 365")
    tran0.writeAction("slorii X17 X17 12 2886")
    tran0.writeAction("slorii X17 X17 12 1811")
    tran0.writeAction("slorii X17 X17 12 2576")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 55883")
    tran0.writeAction("slorii X17 X17 12 2399")
    tran0.writeAction("slorii X17 X17 12 1243")
    tran0.writeAction("slorii X17 X17 12 499")
    tran0.writeAction("slorii X17 X17 12 6")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 7946")
    tran0.writeAction("slorii X17 X17 12 714")
    tran0.writeAction("slorii X17 X17 12 1759")
    tran0.writeAction("slorii X17 X17 12 875")
    tran0.writeAction("slorii X17 X17 12 2675")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 19719")
    tran0.writeAction("slorii X17 X17 12 4004")
    tran0.writeAction("slorii X17 X17 12 1230")
    tran0.writeAction("slorii X17 X17 12 2212")
    tran0.writeAction("slorii X17 X17 12 4086")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 20169")
    tran0.writeAction("slorii X17 X17 12 2171")
    tran0.writeAction("slorii X17 X17 12 3208")
    tran0.writeAction("slorii X17 X17 12 2598")
    tran0.writeAction("slorii X17 X17 12 1500")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 8767")
    tran0.writeAction("slorii X17 X17 12 440")
    tran0.writeAction("slorii X17 X17 12 869")
    tran0.writeAction("slorii X17 X17 12 1635")
    tran0.writeAction("slorii X17 X17 12 1886")
    tran0.writeAction("hashl X16 X17 5")
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movrl X17 0(X16) 0 8")
    tran0.writeAction("yieldt")
    return efa