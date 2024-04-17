from EFA_v2 import *
def hashsb64_59():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [4674976088686291153, 2169816403760100351, -1960524422946152718, -2900759504670823220, -4559189631871846106, 3004674037947671937, -5426262532312951641, -8723792187112918423, 168, 27069]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 16608")
    tran0.writeAction("slorii X17 X17 12 3487")
    tran0.writeAction("slorii X17 X17 12 3019")
    tran0.writeAction("slorii X17 X17 12 2422")
    tran0.writeAction("slorii X17 X17 12 2257")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 7708")
    tran0.writeAction("slorii X17 X17 12 3016")
    tran0.writeAction("slorii X17 X17 12 1509")
    tran0.writeAction("slorii X17 X17 12 3835")
    tran0.writeAction("slorii X17 X17 12 1023")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 58570")
    tran0.writeAction("slorii X17 X17 12 3350")
    tran0.writeAction("slorii X17 X17 12 3252")
    tran0.writeAction("slorii X17 X17 12 3345")
    tran0.writeAction("slorii X17 X17 12 3826")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 55230")
    tran0.writeAction("slorii X17 X17 12 1769")
    tran0.writeAction("slorii X17 X17 12 2417")
    tran0.writeAction("slorii X17 X17 12 1054")
    tran0.writeAction("slorii X17 X17 12 3276")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 49338")
    tran0.writeAction("slorii X17 X17 12 2066")
    tran0.writeAction("slorii X17 X17 12 3960")
    tran0.writeAction("slorii X17 X17 12 2599")
    tran0.writeAction("slorii X17 X17 12 2342")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 10674")
    tran0.writeAction("slorii X17 X17 12 3057")
    tran0.writeAction("slorii X17 X17 12 3641")
    tran0.writeAction("slorii X17 X17 12 2906")
    tran0.writeAction("slorii X17 X17 12 1409")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 46258")
    tran0.writeAction("slorii X17 X17 12 175")
    tran0.writeAction("slorii X17 X17 12 2551")
    tran0.writeAction("slorii X17 X17 12 1945")
    tran0.writeAction("slorii X17 X17 12 1191")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 34542")
    tran0.writeAction("slorii X17 X17 12 3539")
    tran0.writeAction("slorii X17 X17 12 2552")
    tran0.writeAction("slorii X17 X17 12 3303")
    tran0.writeAction("slorii X17 X17 12 617")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movlsb X16")
    tran0.writeAction("movir X16 168")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("add X16 X17 X5")
    tran0.writeAction("movir X16 27069")
    tran0.writeAction("hashsb64 X16 X17")
    tran0.writeAction("yieldt")
    return efa
