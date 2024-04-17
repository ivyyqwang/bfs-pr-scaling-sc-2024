from EFA_v2 import *
def hashl_49():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-321268448096862035, -4413436533817454587, -3470969315789237288, 1219086394967744413, 575597111861194500, 8549513214478450370]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 64394")
    tran0.writeAction("slorii X17 X17 12 2560")
    tran0.writeAction("slorii X17 X17 12 3185")
    tran0.writeAction("slorii X17 X17 12 2644")
    tran0.writeAction("slorii X17 X17 12 173")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 49856")
    tran0.writeAction("slorii X17 X17 12 1325")
    tran0.writeAction("slorii X17 X17 12 2843")
    tran0.writeAction("slorii X17 X17 12 325")
    tran0.writeAction("slorii X17 X17 12 5")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 53204")
    tran0.writeAction("slorii X17 X17 12 2620")
    tran0.writeAction("slorii X17 X17 12 3098")
    tran0.writeAction("slorii X17 X17 12 417")
    tran0.writeAction("slorii X17 X17 12 984")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 4331")
    tran0.writeAction("slorii X17 X17 12 265")
    tran0.writeAction("slorii X17 X17 12 3586")
    tran0.writeAction("slorii X17 X17 12 2309")
    tran0.writeAction("slorii X17 X17 12 3997")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 2044")
    tran0.writeAction("slorii X17 X17 12 3816")
    tran0.writeAction("slorii X17 X17 12 1546")
    tran0.writeAction("slorii X17 X17 12 930")
    tran0.writeAction("slorii X17 X17 12 3844")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 30373")
    tran0.writeAction("slorii X17 X17 12 3983")
    tran0.writeAction("slorii X17 X17 12 2215")
    tran0.writeAction("slorii X17 X17 12 2031")
    tran0.writeAction("slorii X17 X17 12 3778")
    tran0.writeAction("hashl X16 X17 5")
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movrl X17 0(X16) 0 8")
    tran0.writeAction("yieldt")
    return efa
