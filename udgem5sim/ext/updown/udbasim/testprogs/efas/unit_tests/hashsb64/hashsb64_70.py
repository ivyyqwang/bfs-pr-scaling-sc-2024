from EFA_v2 import *
def hashsb64_70():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-6460428921070095979, 4104027732090110584, -2676790275693705336, -8412363044560970078, 9095042836021086699, -5452198357831640899, 7992965776998268620, -8250409058169365788, 64, 26451]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 42583")
    tran0.writeAction("slorii X17 X17 12 3874")
    tran0.writeAction("slorii X17 X17 12 6")
    tran0.writeAction("slorii X17 X17 12 3919")
    tran0.writeAction("slorii X17 X17 12 405")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 14580")
    tran0.writeAction("slorii X17 X17 12 1783")
    tran0.writeAction("slorii X17 X17 12 2671")
    tran0.writeAction("slorii X17 X17 12 2388")
    tran0.writeAction("slorii X17 X17 12 632")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 56026")
    tran0.writeAction("slorii X17 X17 12 534")
    tran0.writeAction("slorii X17 X17 12 3375")
    tran0.writeAction("slorii X17 X17 12 232")
    tran0.writeAction("slorii X17 X17 12 1928")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 35649")
    tran0.writeAction("slorii X17 X17 12 1158")
    tran0.writeAction("slorii X17 X17 12 431")
    tran0.writeAction("slorii X17 X17 12 1309")
    tran0.writeAction("slorii X17 X17 12 3746")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 32312")
    tran0.writeAction("slorii X17 X17 12 340")
    tran0.writeAction("slorii X17 X17 12 1425")
    tran0.writeAction("slorii X17 X17 12 4088")
    tran0.writeAction("slorii X17 X17 12 2539")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 46165")
    tran0.writeAction("slorii X17 X17 12 3687")
    tran0.writeAction("slorii X17 X17 12 2820")
    tran0.writeAction("slorii X17 X17 12 1953")
    tran0.writeAction("slorii X17 X17 12 2237")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 28396")
    tran0.writeAction("slorii X17 X17 12 2944")
    tran0.writeAction("slorii X17 X17 12 1679")
    tran0.writeAction("slorii X17 X17 12 3423")
    tran0.writeAction("slorii X17 X17 12 3788")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 36224")
    tran0.writeAction("slorii X17 X17 12 2698")
    tran0.writeAction("slorii X17 X17 12 3220")
    tran0.writeAction("slorii X17 X17 12 613")
    tran0.writeAction("slorii X17 X17 12 2788")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movlsb X16")
    tran0.writeAction("movir X16 64")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("add X16 X17 X5")
    tran0.writeAction("movir X16 26451")
    tran0.writeAction("hashsb64 X16 X17")
    tran0.writeAction("yieldt")
    return efa
