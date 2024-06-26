from EFA_v2 import *
def hashl64_27():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [8387575459961872170, -6599650196907109052, -6367213525306795219, 4116699269274750524, 540748919444325400, -6630458660847110654, -162922351642986394, 6882062453034002128, 23, 4771008778889256895]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 29798")
    tran0.writeAction("slorii X17 X17 12 2679")
    tran0.writeAction("slorii X17 X17 12 265")
    tran0.writeAction("slorii X17 X17 12 3321")
    tran0.writeAction("slorii X17 X17 12 3882")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 42089")
    tran0.writeAction("slorii X17 X17 12 1361")
    tran0.writeAction("slorii X17 X17 12 3267")
    tran0.writeAction("slorii X17 X17 12 2109")
    tran0.writeAction("slorii X17 X17 12 1348")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 42915")
    tran0.writeAction("slorii X17 X17 12 464")
    tran0.writeAction("slorii X17 X17 12 2207")
    tran0.writeAction("slorii X17 X17 12 105")
    tran0.writeAction("slorii X17 X17 12 2861")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 14625")
    tran0.writeAction("slorii X17 X17 12 1858")
    tran0.writeAction("slorii X17 X17 12 3224")
    tran0.writeAction("slorii X17 X17 12 948")
    tran0.writeAction("slorii X17 X17 12 3644")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 1921")
    tran0.writeAction("slorii X17 X17 12 516")
    tran0.writeAction("slorii X17 X17 12 1784")
    tran0.writeAction("slorii X17 X17 12 636")
    tran0.writeAction("slorii X17 X17 12 1048")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 41979")
    tran0.writeAction("slorii X17 X17 12 3599")
    tran0.writeAction("slorii X17 X17 12 2630")
    tran0.writeAction("slorii X17 X17 12 1211")
    tran0.writeAction("slorii X17 X17 12 1538")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 64957")
    tran0.writeAction("slorii X17 X17 12 751")
    tran0.writeAction("slorii X17 X17 12 3072")
    tran0.writeAction("slorii X17 X17 12 1427")
    tran0.writeAction("slorii X17 X17 12 2150")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 24449")
    tran0.writeAction("slorii X17 X17 12 4085")
    tran0.writeAction("slorii X17 X17 12 1691")
    tran0.writeAction("slorii X17 X17 12 594")
    tran0.writeAction("slorii X17 X17 12 1744")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X18 23")
    tran0.writeAction("add X7 X18 X5")
    tran0.writeAction("movir X16 16950")
    tran0.writeAction("slorii X16 X16 12 115")
    tran0.writeAction("slorii X16 X16 12 1245")
    tran0.writeAction("slorii X16 X16 12 3949")
    tran0.writeAction("slorii X16 X16 12 4031")
    tran0.writeAction("hashl64 X16 X17")
    tran0.writeAction("yieldt")
    return efa
