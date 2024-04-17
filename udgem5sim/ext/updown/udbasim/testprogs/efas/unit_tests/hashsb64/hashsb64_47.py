from EFA_v2 import *
def hashsb64_47():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [688870583102125978, -2170615927070055925, 5620073874652651385, -1582115436140647578, 1823802890103531964, 6619479278682780211, 8977876827421281700, 5218910776652544612, 272, 21610]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 2447")
    tran0.writeAction("slorii X17 X17 12 1474")
    tran0.writeAction("slorii X17 X17 12 1346")
    tran0.writeAction("slorii X17 X17 12 75")
    tran0.writeAction("slorii X17 X17 12 1946")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 57824")
    tran0.writeAction("slorii X17 X17 12 1733")
    tran0.writeAction("slorii X17 X17 12 147")
    tran0.writeAction("slorii X17 X17 12 754")
    tran0.writeAction("slorii X17 X17 12 523")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 19966")
    tran0.writeAction("slorii X17 X17 12 2102")
    tran0.writeAction("slorii X17 X17 12 2462")
    tran0.writeAction("slorii X17 X17 12 509")
    tran0.writeAction("slorii X17 X17 12 3961")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 59915")
    tran0.writeAction("slorii X17 X17 12 806")
    tran0.writeAction("slorii X17 X17 12 1195")
    tran0.writeAction("slorii X17 X17 12 714")
    tran0.writeAction("slorii X17 X17 12 2918")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 6479")
    tran0.writeAction("slorii X17 X17 12 1841")
    tran0.writeAction("slorii X17 X17 12 204")
    tran0.writeAction("slorii X17 X17 12 3898")
    tran0.writeAction("slorii X17 X17 12 2492")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 23517")
    tran0.writeAction("slorii X17 X17 12 469")
    tran0.writeAction("slorii X17 X17 12 1307")
    tran0.writeAction("slorii X17 X17 12 3875")
    tran0.writeAction("slorii X17 X17 12 563")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 31895")
    tran0.writeAction("slorii X17 X17 12 3382")
    tran0.writeAction("slorii X17 X17 12 2143")
    tran0.writeAction("slorii X17 X17 12 2688")
    tran0.writeAction("slorii X17 X17 12 3492")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 18541")
    tran0.writeAction("slorii X17 X17 12 1211")
    tran0.writeAction("slorii X17 X17 12 844")
    tran0.writeAction("slorii X17 X17 12 3411")
    tran0.writeAction("slorii X17 X17 12 2660")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movlsb X16")
    tran0.writeAction("movir X16 272")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("add X16 X17 X5")
    tran0.writeAction("movir X16 21610")
    tran0.writeAction("hashsb64 X16 X17")
    tran0.writeAction("yieldt")
    return efa
