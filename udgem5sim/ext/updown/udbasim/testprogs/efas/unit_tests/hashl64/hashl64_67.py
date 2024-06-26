from EFA_v2 import *
def hashl64_67():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-1780496234594185904, -7513096883269298244, 7578666184929969606, 7489073197977243929, 7987235553820775608, 6639108658035420026, 2033583239271197672, 4401965136563687975, 22, 4076763052922539668]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 59210")
    tran0.writeAction("slorii X17 X17 12 1665")
    tran0.writeAction("slorii X17 X17 12 2989")
    tran0.writeAction("slorii X17 X17 12 380")
    tran0.writeAction("slorii X17 X17 12 3408")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 38844")
    tran0.writeAction("slorii X17 X17 12 483")
    tran0.writeAction("slorii X17 X17 12 213")
    tran0.writeAction("slorii X17 X17 12 2617")
    tran0.writeAction("slorii X17 X17 12 1980")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 26924")
    tran0.writeAction("slorii X17 X17 12 3403")
    tran0.writeAction("slorii X17 X17 12 3552")
    tran0.writeAction("slorii X17 X17 12 64")
    tran0.writeAction("slorii X17 X17 12 1478")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 26606")
    tran0.writeAction("slorii X17 X17 12 2182")
    tran0.writeAction("slorii X17 X17 12 1294")
    tran0.writeAction("slorii X17 X17 12 1361")
    tran0.writeAction("slorii X17 X17 12 281")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 28376")
    tran0.writeAction("slorii X17 X17 12 1478")
    tran0.writeAction("slorii X17 X17 12 2818")
    tran0.writeAction("slorii X17 X17 12 3513")
    tran0.writeAction("slorii X17 X17 12 1208")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 23586")
    tran0.writeAction("slorii X17 X17 12 3490")
    tran0.writeAction("slorii X17 X17 12 1571")
    tran0.writeAction("slorii X17 X17 12 1726")
    tran0.writeAction("slorii X17 X17 12 2938")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 7224")
    tran0.writeAction("slorii X17 X17 12 3026")
    tran0.writeAction("slorii X17 X17 12 3717")
    tran0.writeAction("slorii X17 X17 12 3882")
    tran0.writeAction("slorii X17 X17 12 3048")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 15638")
    tran0.writeAction("slorii X17 X17 12 3775")
    tran0.writeAction("slorii X17 X17 12 2070")
    tran0.writeAction("slorii X17 X17 12 2181")
    tran0.writeAction("slorii X17 X17 12 551")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X18 22")
    tran0.writeAction("add X7 X18 X5")
    tran0.writeAction("movir X16 14483")
    tran0.writeAction("slorii X16 X16 12 2342")
    tran0.writeAction("slorii X16 X16 12 1442")
    tran0.writeAction("slorii X16 X16 12 3624")
    tran0.writeAction("slorii X16 X16 12 3732")
    tran0.writeAction("hashl64 X16 X17")
    tran0.writeAction("yieldt")
    return efa
