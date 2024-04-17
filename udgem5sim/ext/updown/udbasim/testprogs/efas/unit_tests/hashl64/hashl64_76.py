from EFA_v2 import *
def hashl64_76():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [5878810189373116037, -1103928931743343680, 4508679186008407228, 6263429958966678769, -612749878202813664, -7980867643529166351, -3038496457723160828, -2799239240002203403, 46, 2192800367286231910]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 20885")
    tran0.writeAction("slorii X17 X17 12 2987")
    tran0.writeAction("slorii X17 X17 12 2127")
    tran0.writeAction("slorii X17 X17 12 2176")
    tran0.writeAction("slorii X17 X17 12 3717")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 61614")
    tran0.writeAction("slorii X17 X17 12 231")
    tran0.writeAction("slorii X17 X17 12 3142")
    tran0.writeAction("slorii X17 X17 12 661")
    tran0.writeAction("slorii X17 X17 12 3008")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 16018")
    tran0.writeAction("slorii X17 X17 12 189")
    tran0.writeAction("slorii X17 X17 12 1256")
    tran0.writeAction("slorii X17 X17 12 935")
    tran0.writeAction("slorii X17 X17 12 3260")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 22252")
    tran0.writeAction("slorii X17 X17 12 709")
    tran0.writeAction("slorii X17 X17 12 3283")
    tran0.writeAction("slorii X17 X17 12 3065")
    tran0.writeAction("slorii X17 X17 12 1265")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 63359")
    tran0.writeAction("slorii X17 X17 12 307")
    tran0.writeAction("slorii X17 X17 12 2933")
    tran0.writeAction("slorii X17 X17 12 2283")
    tran0.writeAction("slorii X17 X17 12 800")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 37182")
    tran0.writeAction("slorii X17 X17 12 1074")
    tran0.writeAction("slorii X17 X17 12 2468")
    tran0.writeAction("slorii X17 X17 12 144")
    tran0.writeAction("slorii X17 X17 12 497")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 54741")
    tran0.writeAction("slorii X17 X17 12 377")
    tran0.writeAction("slorii X17 X17 12 514")
    tran0.writeAction("slorii X17 X17 12 525")
    tran0.writeAction("slorii X17 X17 12 1796")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 55591")
    tran0.writeAction("slorii X17 X17 12 427")
    tran0.writeAction("slorii X17 X17 12 3586")
    tran0.writeAction("slorii X17 X17 12 1369")
    tran0.writeAction("slorii X17 X17 12 245")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X18 46")
    tran0.writeAction("add X7 X18 X5")
    tran0.writeAction("movir X16 7790")
    tran0.writeAction("slorii X16 X16 12 1605")
    tran0.writeAction("slorii X16 X16 12 235")
    tran0.writeAction("slorii X16 X16 12 1810")
    tran0.writeAction("slorii X16 X16 12 870")
    tran0.writeAction("hashl64 X16 X17")
    tran0.writeAction("yieldt")
    return efa
