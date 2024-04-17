from EFA_v2 import *
def hashsb64_64():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [1127387578007529535, 3819506930643256522, -9217996158092515119, 3954217980842918338, 6035388362177344580, 7662401991710811947, 3625384722917220527, 8620827351895808851, 128, 23440]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 4005")
    tran0.writeAction("slorii X17 X17 12 1168")
    tran0.writeAction("slorii X17 X17 12 1903")
    tran0.writeAction("slorii X17 X17 12 1338")
    tran0.writeAction("slorii X17 X17 12 2111")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 13569")
    tran0.writeAction("slorii X17 X17 12 2517")
    tran0.writeAction("slorii X17 X17 12 282")
    tran0.writeAction("slorii X17 X17 12 548")
    tran0.writeAction("slorii X17 X17 12 1226")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 32787")
    tran0.writeAction("slorii X17 X17 12 405")
    tran0.writeAction("slorii X17 X17 12 1359")
    tran0.writeAction("slorii X17 X17 12 4014")
    tran0.writeAction("slorii X17 X17 12 2257")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 14048")
    tran0.writeAction("slorii X17 X17 12 836")
    tran0.writeAction("slorii X17 X17 12 3488")
    tran0.writeAction("slorii X17 X17 12 2476")
    tran0.writeAction("slorii X17 X17 12 450")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 21442")
    tran0.writeAction("slorii X17 X17 12 27")
    tran0.writeAction("slorii X17 X17 12 3345")
    tran0.writeAction("slorii X17 X17 12 439")
    tran0.writeAction("slorii X17 X17 12 1092")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 27222")
    tran0.writeAction("slorii X17 X17 12 1312")
    tran0.writeAction("slorii X17 X17 12 938")
    tran0.writeAction("slorii X17 X17 12 690")
    tran0.writeAction("slorii X17 X17 12 1835")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 12879")
    tran0.writeAction("slorii X17 X17 12 3907")
    tran0.writeAction("slorii X17 X17 12 647")
    tran0.writeAction("slorii X17 X17 12 2494")
    tran0.writeAction("slorii X17 X17 12 175")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 30627")
    tran0.writeAction("slorii X17 X17 12 1356")
    tran0.writeAction("slorii X17 X17 12 3371")
    tran0.writeAction("slorii X17 X17 12 2953")
    tran0.writeAction("slorii X17 X17 12 2899")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movlsb X16")
    tran0.writeAction("movir X16 128")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("add X16 X17 X5")
    tran0.writeAction("movir X16 23440")
    tran0.writeAction("hashsb64 X16 X17")
    tran0.writeAction("yieldt")
    return efa