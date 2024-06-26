from EFA_v2 import *
def hashsb64_10():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-4470124893228606524, -7249698216236062677, -3014108758423826415, -1972794681504319815, 3193629608119434042, -2321730607680902941, 3839389444645003347, 8362458928092569805, 184, 21330]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 49654")
    tran0.writeAction("slorii X17 X17 12 3793")
    tran0.writeAction("slorii X17 X17 12 2021")
    tran0.writeAction("slorii X17 X17 12 1957")
    tran0.writeAction("slorii X17 X17 12 3012")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 39779")
    tran0.writeAction("slorii X17 X17 12 3678")
    tran0.writeAction("slorii X17 X17 12 516")
    tran0.writeAction("slorii X17 X17 12 1910")
    tran0.writeAction("slorii X17 X17 12 2091")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 54827")
    tran0.writeAction("slorii X17 X17 12 3008")
    tran0.writeAction("slorii X17 X17 12 3515")
    tran0.writeAction("slorii X17 X17 12 3089")
    tran0.writeAction("slorii X17 X17 12 17")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 58527")
    tran0.writeAction("slorii X17 X17 12 923")
    tran0.writeAction("slorii X17 X17 12 130")
    tran0.writeAction("slorii X17 X17 12 635")
    tran0.writeAction("slorii X17 X17 12 1721")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 11346")
    tran0.writeAction("slorii X17 X17 12 211")
    tran0.writeAction("slorii X17 X17 12 1344")
    tran0.writeAction("slorii X17 X17 12 527")
    tran0.writeAction("slorii X17 X17 12 2874")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 57287")
    tran0.writeAction("slorii X17 X17 12 2277")
    tran0.writeAction("slorii X17 X17 12 57")
    tran0.writeAction("slorii X17 X17 12 114")
    tran0.writeAction("slorii X17 X17 12 2275")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 13640")
    tran0.writeAction("slorii X17 X17 12 1029")
    tran0.writeAction("slorii X17 X17 12 2978")
    tran0.writeAction("slorii X17 X17 12 1842")
    tran0.writeAction("slorii X17 X17 12 83")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 29709")
    tran0.writeAction("slorii X17 X17 12 1729")
    tran0.writeAction("slorii X17 X17 12 1729")
    tran0.writeAction("slorii X17 X17 12 3078")
    tran0.writeAction("slorii X17 X17 12 205")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movlsb X16")
    tran0.writeAction("movir X16 184")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("add X16 X17 X5")
    tran0.writeAction("movir X16 21330")
    tran0.writeAction("hashsb64 X16 X17")
    tran0.writeAction("yieldt")
    return efa
