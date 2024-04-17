from EFA_v2 import *
def hashl64_9():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-3643581455261254249, 3832364648957975856, -6317560545088026405, -3308792186283813308, 388822183140828547, 9054476856790693484, 450384419504265076, 4557355493138184431, 22, 7372267265731978523]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 52591")
    tran0.writeAction("slorii X17 X17 12 1631")
    tran0.writeAction("slorii X17 X17 12 2192")
    tran0.writeAction("slorii X17 X17 12 3899")
    tran0.writeAction("slorii X17 X17 12 3479")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 13615")
    tran0.writeAction("slorii X17 X17 12 1205")
    tran0.writeAction("slorii X17 X17 12 2030")
    tran0.writeAction("slorii X17 X17 12 3705")
    tran0.writeAction("slorii X17 X17 12 3376")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 43091")
    tran0.writeAction("slorii X17 X17 12 2114")
    tran0.writeAction("slorii X17 X17 12 2039")
    tran0.writeAction("slorii X17 X17 12 20")
    tran0.writeAction("slorii X17 X17 12 2267")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 53780")
    tran0.writeAction("slorii X17 X17 12 3312")
    tran0.writeAction("slorii X17 X17 12 2444")
    tran0.writeAction("slorii X17 X17 12 3953")
    tran0.writeAction("slorii X17 X17 12 1604")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 1381")
    tran0.writeAction("slorii X17 X17 12 1531")
    tran0.writeAction("slorii X17 X17 12 1834")
    tran0.writeAction("slorii X17 X17 12 3690")
    tran0.writeAction("slorii X17 X17 12 1411")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 32167")
    tran0.writeAction("slorii X17 X17 12 3947")
    tran0.writeAction("slorii X17 X17 12 2692")
    tran0.writeAction("slorii X17 X17 12 19")
    tran0.writeAction("slorii X17 X17 12 1644")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 1600")
    tran0.writeAction("slorii X17 X17 12 355")
    tran0.writeAction("slorii X17 X17 12 3656")
    tran0.writeAction("slorii X17 X17 12 3777")
    tran0.writeAction("slorii X17 X17 12 1908")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 16190")
    tran0.writeAction("slorii X17 X17 12 4010")
    tran0.writeAction("slorii X17 X17 12 3283")
    tran0.writeAction("slorii X17 X17 12 2771")
    tran0.writeAction("slorii X17 X17 12 2287")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X18 22")
    tran0.writeAction("add X7 X18 X5")
    tran0.writeAction("movir X16 26191")
    tran0.writeAction("slorii X16 X16 12 2272")
    tran0.writeAction("slorii X16 X16 12 1195")
    tran0.writeAction("slorii X16 X16 12 798")
    tran0.writeAction("slorii X16 X16 12 1307")
    tran0.writeAction("hashl64 X16 X17")
    tran0.writeAction("yieldt")
    return efa
