from EFA_v2 import *
def hashsb64_46():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [2524089415664706379, 6352807600665622637, -7062662711171013700, -6011245380114838059, 1579175281343732723, 416486371416497264, 1426296524475408848, -2078323448999144737, 296, 12990]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 8967")
    tran0.writeAction("slorii X17 X17 12 1503")
    tran0.writeAction("slorii X17 X17 12 842")
    tran0.writeAction("slorii X17 X17 12 74")
    tran0.writeAction("slorii X17 X17 12 843")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 22569")
    tran0.writeAction("slorii X17 X17 12 2893")
    tran0.writeAction("slorii X17 X17 12 2732")
    tran0.writeAction("slorii X17 X17 12 311")
    tran0.writeAction("slorii X17 X17 12 2157")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 40444")
    tran0.writeAction("slorii X17 X17 12 1562")
    tran0.writeAction("slorii X17 X17 12 3852")
    tran0.writeAction("slorii X17 X17 12 1042")
    tran0.writeAction("slorii X17 X17 12 956")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 44179")
    tran0.writeAction("slorii X17 X17 12 3138")
    tran0.writeAction("slorii X17 X17 12 3324")
    tran0.writeAction("slorii X17 X17 12 2240")
    tran0.writeAction("slorii X17 X17 12 3541")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 5610")
    tran0.writeAction("slorii X17 X17 12 1464")
    tran0.writeAction("slorii X17 X17 12 3378")
    tran0.writeAction("slorii X17 X17 12 2337")
    tran0.writeAction("slorii X17 X17 12 3059")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 1479")
    tran0.writeAction("slorii X17 X17 12 2690")
    tran0.writeAction("slorii X17 X17 12 1518")
    tran0.writeAction("slorii X17 X17 12 293")
    tran0.writeAction("slorii X17 X17 12 3184")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 5067")
    tran0.writeAction("slorii X17 X17 12 914")
    tran0.writeAction("slorii X17 X17 12 469")
    tran0.writeAction("slorii X17 X17 12 2994")
    tran0.writeAction("slorii X17 X17 12 464")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 58152")
    tran0.writeAction("slorii X17 X17 12 1277")
    tran0.writeAction("slorii X17 X17 12 1446")
    tran0.writeAction("slorii X17 X17 12 169")
    tran0.writeAction("slorii X17 X17 12 735")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movlsb X16")
    tran0.writeAction("movir X16 296")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("add X16 X17 X5")
    tran0.writeAction("movir X16 12990")
    tran0.writeAction("hashsb64 X16 X17")
    tran0.writeAction("yieldt")
    return efa