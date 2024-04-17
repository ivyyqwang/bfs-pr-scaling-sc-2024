from EFA_v2 import *
def hashsb64_93():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [3956137576804183783, -8259401649217136405, -6711704622245361588, 8637346337482008808, 8482809149688373037, 8797807439279140579, -3683839255945344791, -4649705800896533207, 448, 5653]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 14055")
    tran0.writeAction("slorii X17 X17 12 98")
    tran0.writeAction("slorii X17 X17 12 2659")
    tran0.writeAction("slorii X17 X17 12 4046")
    tran0.writeAction("slorii X17 X17 12 3815")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 36192")
    tran0.writeAction("slorii X17 X17 12 2911")
    tran0.writeAction("slorii X17 X17 12 1489")
    tran0.writeAction("slorii X17 X17 12 561")
    tran0.writeAction("slorii X17 X17 12 2283")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 41691")
    tran0.writeAction("slorii X17 X17 12 963")
    tran0.writeAction("slorii X17 X17 12 1225")
    tran0.writeAction("slorii X17 X17 12 2940")
    tran0.writeAction("slorii X17 X17 12 2124")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 30686")
    tran0.writeAction("slorii X17 X17 12 75")
    tran0.writeAction("slorii X17 X17 12 2871")
    tran0.writeAction("slorii X17 X17 12 2606")
    tran0.writeAction("slorii X17 X17 12 2280")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 30136")
    tran0.writeAction("slorii X17 X17 12 4063")
    tran0.writeAction("slorii X17 X17 12 2640")
    tran0.writeAction("slorii X17 X17 12 2493")
    tran0.writeAction("slorii X17 X17 12 3885")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 31256")
    tran0.writeAction("slorii X17 X17 12 372")
    tran0.writeAction("slorii X17 X17 12 212")
    tran0.writeAction("slorii X17 X17 12 2138")
    tran0.writeAction("slorii X17 X17 12 3811")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 52448")
    tran0.writeAction("slorii X17 X17 12 1531")
    tran0.writeAction("slorii X17 X17 12 1771")
    tran0.writeAction("slorii X17 X17 12 3024")
    tran0.writeAction("slorii X17 X17 12 2281")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 49016")
    tran0.writeAction("slorii X17 X17 12 3795")
    tran0.writeAction("slorii X17 X17 12 1427")
    tran0.writeAction("slorii X17 X17 12 2002")
    tran0.writeAction("slorii X17 X17 12 3369")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movlsb X16")
    tran0.writeAction("movir X16 448")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("add X16 X17 X5")
    tran0.writeAction("movir X16 5653")
    tran0.writeAction("hashsb64 X16 X17")
    tran0.writeAction("yieldt")
    return efa
