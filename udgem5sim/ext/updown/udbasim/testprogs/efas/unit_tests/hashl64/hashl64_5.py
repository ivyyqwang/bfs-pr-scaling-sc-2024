from EFA_v2 import *
def hashl64_5():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-1532038417905367112, 5954343238934899817, 6237029365223274457, -5667485895756925215, 186957303806752869, -5391536754703840889, -3465605618213220627, 5276876401388665511, 3, 3741877626814653020]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 60093")
    tran0.writeAction("slorii X17 X17 12 434")
    tran0.writeAction("slorii X17 X17 12 3342")
    tran0.writeAction("slorii X17 X17 12 2044")
    tran0.writeAction("slorii X17 X17 12 1976")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 21154")
    tran0.writeAction("slorii X17 X17 12 314")
    tran0.writeAction("slorii X17 X17 12 219")
    tran0.writeAction("slorii X17 X17 12 1898")
    tran0.writeAction("slorii X17 X17 12 3177")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 22158")
    tran0.writeAction("slorii X17 X17 12 1554")
    tran0.writeAction("slorii X17 X17 12 2455")
    tran0.writeAction("slorii X17 X17 12 3331")
    tran0.writeAction("slorii X17 X17 12 2009")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 45401")
    tran0.writeAction("slorii X17 X17 12 185")
    tran0.writeAction("slorii X17 X17 12 2813")
    tran0.writeAction("slorii X17 X17 12 3571")
    tran0.writeAction("slorii X17 X17 12 1761")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 664")
    tran0.writeAction("slorii X17 X17 12 842")
    tran0.writeAction("slorii X17 X17 12 3425")
    tran0.writeAction("slorii X17 X17 12 2319")
    tran0.writeAction("slorii X17 X17 12 2149")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 46381")
    tran0.writeAction("slorii X17 X17 12 1694")
    tran0.writeAction("slorii X17 X17 12 798")
    tran0.writeAction("slorii X17 X17 12 1700")
    tran0.writeAction("slorii X17 X17 12 2439")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 53223")
    tran0.writeAction("slorii X17 X17 12 2848")
    tran0.writeAction("slorii X17 X17 12 3394")
    tran0.writeAction("slorii X17 X17 12 3288")
    tran0.writeAction("slorii X17 X17 12 3821")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 18747")
    tran0.writeAction("slorii X17 X17 12 946")
    tran0.writeAction("slorii X17 X17 12 260")
    tran0.writeAction("slorii X17 X17 12 1691")
    tran0.writeAction("slorii X17 X17 12 2727")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X18 3")
    tran0.writeAction("add X7 X18 X5")
    tran0.writeAction("movir X16 13293")
    tran0.writeAction("slorii X16 X16 12 3358")
    tran0.writeAction("slorii X16 X16 12 83")
    tran0.writeAction("slorii X16 X16 12 1102")
    tran0.writeAction("slorii X16 X16 12 604")
    tran0.writeAction("hashl64 X16 X17")
    tran0.writeAction("yieldt")
    return efa
