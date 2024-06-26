from EFA_v2 import *
def hashl64_91():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-5855355687887398530, -9042930618631360511, -563112045219131504, -5803398541086997042, -1403408443355698911, 5859249517170048624, -2780627869412273523, -9100746503210564973, 42, 3001643396230200868]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 44733")
    tran0.writeAction("slorii X17 X17 12 2448")
    tran0.writeAction("slorii X17 X17 12 1629")
    tran0.writeAction("slorii X17 X17 12 3721")
    tran0.writeAction("slorii X17 X17 12 2430")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 33409")
    tran0.writeAction("slorii X17 X17 12 232")
    tran0.writeAction("slorii X17 X17 12 907")
    tran0.writeAction("slorii X17 X17 12 3991")
    tran0.writeAction("slorii X17 X17 12 1")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 63535")
    tran0.writeAction("slorii X17 X17 12 1737")
    tran0.writeAction("slorii X17 X17 12 1039")
    tran0.writeAction("slorii X17 X17 12 3972")
    tran0.writeAction("slorii X17 X17 12 3984")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 44918")
    tran0.writeAction("slorii X17 X17 12 764")
    tran0.writeAction("slorii X17 X17 12 1612")
    tran0.writeAction("slorii X17 X17 12 2004")
    tran0.writeAction("slorii X17 X17 12 1486")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 60550")
    tran0.writeAction("slorii X17 X17 12 375")
    tran0.writeAction("slorii X17 X17 12 1234")
    tran0.writeAction("slorii X17 X17 12 4094")
    tran0.writeAction("slorii X17 X17 12 2337")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 20816")
    tran0.writeAction("slorii X17 X17 12 966")
    tran0.writeAction("slorii X17 X17 12 1129")
    tran0.writeAction("slorii X17 X17 12 1227")
    tran0.writeAction("slorii X17 X17 12 3696")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 55657")
    tran0.writeAction("slorii X17 X17 12 922")
    tran0.writeAction("slorii X17 X17 12 3943")
    tran0.writeAction("slorii X17 X17 12 533")
    tran0.writeAction("slorii X17 X17 12 653")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 33203")
    tran0.writeAction("slorii X17 X17 12 2676")
    tran0.writeAction("slorii X17 X17 12 1517")
    tran0.writeAction("slorii X17 X17 12 1048")
    tran0.writeAction("slorii X17 X17 12 659")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X18 42")
    tran0.writeAction("add X7 X18 X5")
    tran0.writeAction("movir X16 10663")
    tran0.writeAction("slorii X16 X16 12 4012")
    tran0.writeAction("slorii X16 X16 12 1014")
    tran0.writeAction("slorii X16 X16 12 2859")
    tran0.writeAction("slorii X16 X16 12 3620")
    tran0.writeAction("hashl64 X16 X17")
    tran0.writeAction("yieldt")
    return efa
