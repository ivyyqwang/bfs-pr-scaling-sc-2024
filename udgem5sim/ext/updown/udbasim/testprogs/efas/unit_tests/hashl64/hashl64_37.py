from EFA_v2 import *
def hashl64_37():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-4638671790928011992, -377395016019734188, -673438166863988073, 2043227176301235720, -8312347590486002015, 6309927758748768992, -6692854623831823898, 7232853574647776483, 0, 7655796349008508545]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 49056")
    tran0.writeAction("slorii X17 X17 12 521")
    tran0.writeAction("slorii X17 X17 12 1336")
    tran0.writeAction("slorii X17 X17 12 453")
    tran0.writeAction("slorii X17 X17 12 3368")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 64195")
    tran0.writeAction("slorii X17 X17 12 915")
    tran0.writeAction("slorii X17 X17 12 2946")
    tran0.writeAction("slorii X17 X17 12 577")
    tran0.writeAction("slorii X17 X17 12 340")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 63143")
    tran0.writeAction("slorii X17 X17 12 1912")
    tran0.writeAction("slorii X17 X17 12 3621")
    tran0.writeAction("slorii X17 X17 12 3611")
    tran0.writeAction("slorii X17 X17 12 2711")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 7259")
    tran0.writeAction("slorii X17 X17 12 4")
    tran0.writeAction("slorii X17 X17 12 2710")
    tran0.writeAction("slorii X17 X17 12 3520")
    tran0.writeAction("slorii X17 X17 12 3592")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 36004")
    tran0.writeAction("slorii X17 X17 12 2494")
    tran0.writeAction("slorii X17 X17 12 2107")
    tran0.writeAction("slorii X17 X17 12 2079")
    tran0.writeAction("slorii X17 X17 12 1697")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 22417")
    tran0.writeAction("slorii X17 X17 12 1501")
    tran0.writeAction("slorii X17 X17 12 3450")
    tran0.writeAction("slorii X17 X17 12 2445")
    tran0.writeAction("slorii X17 X17 12 2784")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 41758")
    tran0.writeAction("slorii X17 X17 12 834")
    tran0.writeAction("slorii X17 X17 12 3597")
    tran0.writeAction("slorii X17 X17 12 710")
    tran0.writeAction("slorii X17 X17 12 2534")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 25696")
    tran0.writeAction("slorii X17 X17 12 1056")
    tran0.writeAction("slorii X17 X17 12 317")
    tran0.writeAction("slorii X17 X17 12 1208")
    tran0.writeAction("slorii X17 X17 12 1251")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X18 0")
    tran0.writeAction("add X7 X18 X5")
    tran0.writeAction("movir X16 27198")
    tran0.writeAction("slorii X16 X16 12 3491")
    tran0.writeAction("slorii X16 X16 12 1951")
    tran0.writeAction("slorii X16 X16 12 1575")
    tran0.writeAction("slorii X16 X16 12 1665")
    tran0.writeAction("hashl64 X16 X17")
    tran0.writeAction("yieldt")
    return efa