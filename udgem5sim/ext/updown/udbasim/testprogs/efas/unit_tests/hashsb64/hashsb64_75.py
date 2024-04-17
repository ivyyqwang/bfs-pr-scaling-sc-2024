from EFA_v2 import *
def hashsb64_75():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-2616114283318900027, 8782957868484113251, -2404198166769120668, -8648528930434291324, -561971257248132723, -5751309283750802894, -5391133749289294239, 3274352722106576775, 416, 7104]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 56241")
    tran0.writeAction("slorii X17 X17 12 2846")
    tran0.writeAction("slorii X17 X17 12 2954")
    tran0.writeAction("slorii X17 X17 12 3896")
    tran0.writeAction("slorii X17 X17 12 2757")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 31203")
    tran0.writeAction("slorii X17 X17 12 1370")
    tran0.writeAction("slorii X17 X17 12 1460")
    tran0.writeAction("slorii X17 X17 12 891")
    tran0.writeAction("slorii X17 X17 12 867")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 56994")
    tran0.writeAction("slorii X17 X17 12 2344")
    tran0.writeAction("slorii X17 X17 12 348")
    tran0.writeAction("slorii X17 X17 12 332")
    tran0.writeAction("slorii X17 X17 12 2660")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 34810")
    tran0.writeAction("slorii X17 X17 12 1036")
    tran0.writeAction("slorii X17 X17 12 631")
    tran0.writeAction("slorii X17 X17 12 3174")
    tran0.writeAction("slorii X17 X17 12 2436")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 63539")
    tran0.writeAction("slorii X17 X17 12 1953")
    tran0.writeAction("slorii X17 X17 12 3701")
    tran0.writeAction("slorii X17 X17 12 3053")
    tran0.writeAction("slorii X17 X17 12 397")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 45103")
    tran0.writeAction("slorii X17 X17 12 1002")
    tran0.writeAction("slorii X17 X17 12 3484")
    tran0.writeAction("slorii X17 X17 12 2568")
    tran0.writeAction("slorii X17 X17 12 2610")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 46382")
    tran0.writeAction("slorii X17 X17 12 3462")
    tran0.writeAction("slorii X17 X17 12 2848")
    tran0.writeAction("slorii X17 X17 12 4062")
    tran0.writeAction("slorii X17 X17 12 1633")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 11632")
    tran0.writeAction("slorii X17 X17 12 3431")
    tran0.writeAction("slorii X17 X17 12 982")
    tran0.writeAction("slorii X17 X17 12 2030")
    tran0.writeAction("slorii X17 X17 12 3975")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movlsb X16")
    tran0.writeAction("movir X16 416")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("add X16 X17 X5")
    tran0.writeAction("movir X16 7104")
    tran0.writeAction("hashsb64 X16 X17")
    tran0.writeAction("yieldt")
    return efa