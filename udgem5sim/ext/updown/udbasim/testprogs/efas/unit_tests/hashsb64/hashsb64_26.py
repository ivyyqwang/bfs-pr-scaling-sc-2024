from EFA_v2 import *
def hashsb64_26():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [7444715390443931806, -2711306398138108439, 3544901334736023851, -1622321323305937043, -308825181567364320, 6726078602260012962, -7481041932418917714, -7630585577117231913, 0, 27491]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 26448")
    tran0.writeAction("slorii X17 X17 12 3859")
    tran0.writeAction("slorii X17 X17 12 1069")
    tran0.writeAction("slorii X17 X17 12 1204")
    tran0.writeAction("slorii X17 X17 12 2206")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 55903")
    tran0.writeAction("slorii X17 X17 12 2067")
    tran0.writeAction("slorii X17 X17 12 557")
    tran0.writeAction("slorii X17 X17 12 3007")
    tran0.writeAction("slorii X17 X17 12 1513")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 12594")
    tran0.writeAction("slorii X17 X17 12 79")
    tran0.writeAction("slorii X17 X17 12 2932")
    tran0.writeAction("slorii X17 X17 12 3067")
    tran0.writeAction("slorii X17 X17 12 299")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 59772")
    tran0.writeAction("slorii X17 X17 12 1461")
    tran0.writeAction("slorii X17 X17 12 2580")
    tran0.writeAction("slorii X17 X17 12 3309")
    tran0.writeAction("slorii X17 X17 12 1901")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 64438")
    tran0.writeAction("slorii X17 X17 12 3410")
    tran0.writeAction("slorii X17 X17 12 562")
    tran0.writeAction("slorii X17 X17 12 4021")
    tran0.writeAction("slorii X17 X17 12 800")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 23895")
    tran0.writeAction("slorii X17 X17 12 3405")
    tran0.writeAction("slorii X17 X17 12 2619")
    tran0.writeAction("slorii X17 X17 12 261")
    tran0.writeAction("slorii X17 X17 12 4002")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 38957")
    tran0.writeAction("slorii X17 X17 12 4095")
    tran0.writeAction("slorii X17 X17 12 4012")
    tran0.writeAction("slorii X17 X17 12 1509")
    tran0.writeAction("slorii X17 X17 12 2734")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 38426")
    tran0.writeAction("slorii X17 X17 12 2925")
    tran0.writeAction("slorii X17 X17 12 2207")
    tran0.writeAction("slorii X17 X17 12 2901")
    tran0.writeAction("slorii X17 X17 12 1239")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movlsb X16")
    tran0.writeAction("movir X16 0")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("add X16 X17 X5")
    tran0.writeAction("movir X16 27491")
    tran0.writeAction("hashsb64 X16 X17")
    tran0.writeAction("yieldt")
    return efa
