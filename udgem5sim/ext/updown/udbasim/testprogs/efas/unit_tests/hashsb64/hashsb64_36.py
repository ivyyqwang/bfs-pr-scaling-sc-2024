from EFA_v2 import *
def hashsb64_36():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-8729710434108342351, -1392446467887452864, -4594827708885787011, -5478024812427496183, -733007222399459412, -331070440919233515, -1185197932202179295, -3587914436304292408, 360, 21654]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 34521")
    tran0.writeAction("slorii X17 X17 12 3433")
    tran0.writeAction("slorii X17 X17 12 3254")
    tran0.writeAction("slorii X17 X17 12 3895")
    tran0.writeAction("slorii X17 X17 12 4017")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 60589")
    tran0.writeAction("slorii X17 X17 12 149")
    tran0.writeAction("slorii X17 X17 12 160")
    tran0.writeAction("slorii X17 X17 12 3362")
    tran0.writeAction("slorii X17 X17 12 3392")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 49211")
    tran0.writeAction("slorii X17 X17 12 3656")
    tran0.writeAction("slorii X17 X17 12 2831")
    tran0.writeAction("slorii X17 X17 12 3033")
    tran0.writeAction("slorii X17 X17 12 3709")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 46074")
    tran0.writeAction("slorii X17 X17 12 599")
    tran0.writeAction("slorii X17 X17 12 1272")
    tran0.writeAction("slorii X17 X17 12 1979")
    tran0.writeAction("slorii X17 X17 12 1289")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 62931")
    tran0.writeAction("slorii X17 X17 12 3421")
    tran0.writeAction("slorii X17 X17 12 155")
    tran0.writeAction("slorii X17 X17 12 345")
    tran0.writeAction("slorii X17 X17 12 4012")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 64359")
    tran0.writeAction("slorii X17 X17 12 3283")
    tran0.writeAction("slorii X17 X17 12 37")
    tran0.writeAction("slorii X17 X17 12 1544")
    tran0.writeAction("slorii X17 X17 12 3093")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 61325")
    tran0.writeAction("slorii X17 X17 12 1356")
    tran0.writeAction("slorii X17 X17 12 662")
    tran0.writeAction("slorii X17 X17 12 2300")
    tran0.writeAction("slorii X17 X17 12 1313")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 52789")
    tran0.writeAction("slorii X17 X17 12 685")
    tran0.writeAction("slorii X17 X17 12 1131")
    tran0.writeAction("slorii X17 X17 12 2403")
    tran0.writeAction("slorii X17 X17 12 1480")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movlsb X16")
    tran0.writeAction("movir X16 360")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("add X16 X17 X5")
    tran0.writeAction("movir X16 21654")
    tran0.writeAction("hashsb64 X16 X17")
    tran0.writeAction("yieldt")
    return efa
