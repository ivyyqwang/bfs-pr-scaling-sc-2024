from EFA_v2 import *
def hashsb64_51():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-1660496360912871964, 4277228817937087256, 5973055131859285331, -8759438912212213022, 4053609005401089083, -6115765189083281699, -6913383998969640535, -5432460689017926281, 32, 12769]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 59636")
    tran0.writeAction("slorii X17 X17 12 2997")
    tran0.writeAction("slorii X17 X17 12 2944")
    tran0.writeAction("slorii X17 X17 12 3929")
    tran0.writeAction("slorii X17 X17 12 3556")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 15195")
    tran0.writeAction("slorii X17 X17 12 3151")
    tran0.writeAction("slorii X17 X17 12 700")
    tran0.writeAction("slorii X17 X17 12 835")
    tran0.writeAction("slorii X17 X17 12 2840")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 21220")
    tran0.writeAction("slorii X17 X17 12 2271")
    tran0.writeAction("slorii X17 X17 12 3822")
    tran0.writeAction("slorii X17 X17 12 1215")
    tran0.writeAction("slorii X17 X17 12 1363")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 34416")
    tran0.writeAction("slorii X17 X17 12 907")
    tran0.writeAction("slorii X17 X17 12 2053")
    tran0.writeAction("slorii X17 X17 12 3510")
    tran0.writeAction("slorii X17 X17 12 738")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 14401")
    tran0.writeAction("slorii X17 X17 12 1278")
    tran0.writeAction("slorii X17 X17 12 2521")
    tran0.writeAction("slorii X17 X17 12 1050")
    tran0.writeAction("slorii X17 X17 12 1083")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 43808")
    tran0.writeAction("slorii X17 X17 12 1791")
    tran0.writeAction("slorii X17 X17 12 1686")
    tran0.writeAction("slorii X17 X17 12 4060")
    tran0.writeAction("slorii X17 X17 12 1757")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 40974")
    tran0.writeAction("slorii X17 X17 12 2974")
    tran0.writeAction("slorii X17 X17 12 433")
    tran0.writeAction("slorii X17 X17 12 2232")
    tran0.writeAction("slorii X17 X17 12 2473")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 46236")
    tran0.writeAction("slorii X17 X17 12 92")
    tran0.writeAction("slorii X17 X17 12 2342")
    tran0.writeAction("slorii X17 X17 12 3328")
    tran0.writeAction("slorii X17 X17 12 3447")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movlsb X16")
    tran0.writeAction("movir X16 32")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("add X16 X17 X5")
    tran0.writeAction("movir X16 12769")
    tran0.writeAction("hashsb64 X16 X17")
    tran0.writeAction("yieldt")
    return efa