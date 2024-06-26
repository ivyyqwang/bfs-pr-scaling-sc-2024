from EFA_v2 import *
def hashl64_63():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [1734753052290620096, 5926078651086478702, -1384127466034140603, 148266180613876017, -4838620338580782268, -9092541085205906278, 5758387528798992929, 6155468477562929121, 7, 8247934673183992031]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 6163")
    tran0.writeAction("slorii X17 X17 12 331")
    tran0.writeAction("slorii X17 X17 12 1470")
    tran0.writeAction("slorii X17 X17 12 3305")
    tran0.writeAction("slorii X17 X17 12 2752")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 21053")
    tran0.writeAction("slorii X17 X17 12 2706")
    tran0.writeAction("slorii X17 X17 12 685")
    tran0.writeAction("slorii X17 X17 12 145")
    tran0.writeAction("slorii X17 X17 12 3438")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 60618")
    tran0.writeAction("slorii X17 X17 12 2422")
    tran0.writeAction("slorii X17 X17 12 1839")
    tran0.writeAction("slorii X17 X17 12 710")
    tran0.writeAction("slorii X17 X17 12 2629")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 526")
    tran0.writeAction("slorii X17 X17 12 3060")
    tran0.writeAction("slorii X17 X17 12 3651")
    tran0.writeAction("slorii X17 X17 12 2842")
    tran0.writeAction("slorii X17 X17 12 2353")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 48345")
    tran0.writeAction("slorii X17 X17 12 3143")
    tran0.writeAction("slorii X17 X17 12 43")
    tran0.writeAction("slorii X17 X17 12 3736")
    tran0.writeAction("slorii X17 X17 12 836")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 33232")
    tran0.writeAction("slorii X17 X17 12 3296")
    tran0.writeAction("slorii X17 X17 12 3758")
    tran0.writeAction("slorii X17 X17 12 2691")
    tran0.writeAction("slorii X17 X17 12 3226")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 20457")
    tran0.writeAction("slorii X17 X17 12 3695")
    tran0.writeAction("slorii X17 X17 12 701")
    tran0.writeAction("slorii X17 X17 12 423")
    tran0.writeAction("slorii X17 X17 12 2593")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 21868")
    tran0.writeAction("slorii X17 X17 12 2527")
    tran0.writeAction("slorii X17 X17 12 1951")
    tran0.writeAction("slorii X17 X17 12 1035")
    tran0.writeAction("slorii X17 X17 12 4065")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X18 7")
    tran0.writeAction("add X7 X18 X5")
    tran0.writeAction("movir X16 29302")
    tran0.writeAction("slorii X16 X16 12 2254")
    tran0.writeAction("slorii X16 X16 12 709")
    tran0.writeAction("slorii X16 X16 12 3110")
    tran0.writeAction("slorii X16 X16 12 2271")
    tran0.writeAction("hashl64 X16 X17")
    tran0.writeAction("yieldt")
    return efa
