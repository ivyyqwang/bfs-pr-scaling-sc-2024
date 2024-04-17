from EFA_v2 import *
def hashl64_31():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-1170470076499375943, -4970594710360941382, 6244969040910214853, -861647749795618679, 2686622157926253882, 7541444990014024241, 6098484911038498891, -7247548602404874889, 35, 5129833644886485854]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 61377")
    tran0.writeAction("slorii X17 X17 12 2682")
    tran0.writeAction("slorii X17 X17 12 2742")
    tran0.writeAction("slorii X17 X17 12 124")
    tran0.writeAction("slorii X17 X17 12 2233")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 47876")
    tran0.writeAction("slorii X17 X17 12 3687")
    tran0.writeAction("slorii X17 X17 12 574")
    tran0.writeAction("slorii X17 X17 12 2049")
    tran0.writeAction("slorii X17 X17 12 3258")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 22186")
    tran0.writeAction("slorii X17 X17 12 2404")
    tran0.writeAction("slorii X17 X17 12 356")
    tran0.writeAction("slorii X17 X17 12 3134")
    tran0.writeAction("slorii X17 X17 12 1733")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 62474")
    tran0.writeAction("slorii X17 X17 12 3326")
    tran0.writeAction("slorii X17 X17 12 4047")
    tran0.writeAction("slorii X17 X17 12 3758")
    tran0.writeAction("slorii X17 X17 12 137")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 9544")
    tran0.writeAction("slorii X17 X17 12 3273")
    tran0.writeAction("slorii X17 X17 12 3656")
    tran0.writeAction("slorii X17 X17 12 3636")
    tran0.writeAction("slorii X17 X17 12 1338")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 26792")
    tran0.writeAction("slorii X17 X17 12 2436")
    tran0.writeAction("slorii X17 X17 12 794")
    tran0.writeAction("slorii X17 X17 12 3830")
    tran0.writeAction("slorii X17 X17 12 2609")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 21666")
    tran0.writeAction("slorii X17 X17 12 699")
    tran0.writeAction("slorii X17 X17 12 1830")
    tran0.writeAction("slorii X17 X17 12 2168")
    tran0.writeAction("slorii X17 X17 12 2123")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 39787")
    tran0.writeAction("slorii X17 X17 12 2191")
    tran0.writeAction("slorii X17 X17 12 509")
    tran0.writeAction("slorii X17 X17 12 1141")
    tran0.writeAction("slorii X17 X17 12 1399")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X18 35")
    tran0.writeAction("add X7 X18 X5")
    tran0.writeAction("movir X16 18224")
    tran0.writeAction("slorii X16 X16 12 3400")
    tran0.writeAction("slorii X16 X16 12 1376")
    tran0.writeAction("slorii X16 X16 12 1254")
    tran0.writeAction("slorii X16 X16 12 2910")
    tran0.writeAction("hashl64 X16 X17")
    tran0.writeAction("yieldt")
    return efa
