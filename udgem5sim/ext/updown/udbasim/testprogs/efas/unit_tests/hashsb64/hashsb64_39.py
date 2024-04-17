from EFA_v2 import *
def hashsb64_39():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [8654397775830260225, -7295838569593243395, -5066253133956448132, 6695824482768926276, 6725663444443527789, 5746882841938918623, -4280270846829991352, 8196747482859135872, 368, 13059]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 30746")
    tran0.writeAction("slorii X17 X17 12 2446")
    tran0.writeAction("slorii X17 X17 12 3221")
    tran0.writeAction("slorii X17 X17 12 1201")
    tran0.writeAction("slorii X17 X17 12 2561")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 39615")
    tran0.writeAction("slorii X17 X17 12 3991")
    tran0.writeAction("slorii X17 X17 12 2520")
    tran0.writeAction("slorii X17 X17 12 3279")
    tran0.writeAction("slorii X17 X17 12 2301")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 47537")
    tran0.writeAction("slorii X17 X17 12 217")
    tran0.writeAction("slorii X17 X17 12 3560")
    tran0.writeAction("slorii X17 X17 12 1296")
    tran0.writeAction("slorii X17 X17 12 124")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 23788")
    tran0.writeAction("slorii X17 X17 12 1422")
    tran0.writeAction("slorii X17 X17 12 1053")
    tran0.writeAction("slorii X17 X17 12 3299")
    tran0.writeAction("slorii X17 X17 12 1604")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 23894")
    tran0.writeAction("slorii X17 X17 12 1460")
    tran0.writeAction("slorii X17 X17 12 1220")
    tran0.writeAction("slorii X17 X17 12 3631")
    tran0.writeAction("slorii X17 X17 12 2669")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 20417")
    tran0.writeAction("slorii X17 X17 12 119")
    tran0.writeAction("slorii X17 X17 12 3863")
    tran0.writeAction("slorii X17 X17 12 2279")
    tran0.writeAction("slorii X17 X17 12 3295")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 50329")
    tran0.writeAction("slorii X17 X17 12 1733")
    tran0.writeAction("slorii X17 X17 12 1976")
    tran0.writeAction("slorii X17 X17 12 974")
    tran0.writeAction("slorii X17 X17 12 2632")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 29120")
    tran0.writeAction("slorii X17 X17 12 2854")
    tran0.writeAction("slorii X17 X17 12 2125")
    tran0.writeAction("slorii X17 X17 12 1622")
    tran0.writeAction("slorii X17 X17 12 896")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movlsb X16")
    tran0.writeAction("movir X16 368")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("add X16 X17 X5")
    tran0.writeAction("movir X16 13059")
    tran0.writeAction("hashsb64 X16 X17")
    tran0.writeAction("yieldt")
    return efa