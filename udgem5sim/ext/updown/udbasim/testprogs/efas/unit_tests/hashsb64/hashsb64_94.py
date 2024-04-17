from EFA_v2 import *
def hashsb64_94():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-2427940160119112339, -3733478422913555714, 6948194539978260932, 8227641622490779277, -1543896628188657279, -32334374083035977, 3265448703788741853, 4009129656532863726, 264, 7063]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 56910")
    tran0.writeAction("slorii X17 X17 12 916")
    tran0.writeAction("slorii X17 X17 12 2500")
    tran0.writeAction("slorii X17 X17 12 799")
    tran0.writeAction("slorii X17 X17 12 3437")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 52272")
    tran0.writeAction("slorii X17 X17 12 82")
    tran0.writeAction("slorii X17 X17 12 1977")
    tran0.writeAction("slorii X17 X17 12 2670")
    tran0.writeAction("slorii X17 X17 12 766")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 24684")
    tran0.writeAction("slorii X17 X17 12 3873")
    tran0.writeAction("slorii X17 X17 12 3833")
    tran0.writeAction("slorii X17 X17 12 2920")
    tran0.writeAction("slorii X17 X17 12 452")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 29230")
    tran0.writeAction("slorii X17 X17 12 1863")
    tran0.writeAction("slorii X17 X17 12 1719")
    tran0.writeAction("slorii X17 X17 12 3200")
    tran0.writeAction("slorii X17 X17 12 3725")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 60050")
    tran0.writeAction("slorii X17 X17 12 4003")
    tran0.writeAction("slorii X17 X17 12 594")
    tran0.writeAction("slorii X17 X17 12 3652")
    tran0.writeAction("slorii X17 X17 12 2433")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 65421")
    tran0.writeAction("slorii X17 X17 12 512")
    tran0.writeAction("slorii X17 X17 12 3806")
    tran0.writeAction("slorii X17 X17 12 3055")
    tran0.writeAction("slorii X17 X17 12 3255")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 11601")
    tran0.writeAction("slorii X17 X17 12 836")
    tran0.writeAction("slorii X17 X17 12 2949")
    tran0.writeAction("slorii X17 X17 12 2407")
    tran0.writeAction("slorii X17 X17 12 1245")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 14243")
    tran0.writeAction("slorii X17 X17 12 1186")
    tran0.writeAction("slorii X17 X17 12 3692")
    tran0.writeAction("slorii X17 X17 12 512")
    tran0.writeAction("slorii X17 X17 12 2798")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movlsb X16")
    tran0.writeAction("movir X16 264")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("add X16 X17 X5")
    tran0.writeAction("movir X16 7063")
    tran0.writeAction("hashsb64 X16 X17")
    tran0.writeAction("yieldt")
    return efa
