from EFA_v2 import *
def hashl64_95():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [5590962976648882256, 8796452865870218929, 499049076887805580, 236970967057513186, -5034447886844529022, 9163985208551520919, 32891543215380934, -1060032309537891381, 26, 654853727827385676]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 19863")
    tran0.writeAction("slorii X17 X17 12 371")
    tran0.writeAction("slorii X17 X17 12 1151")
    tran0.writeAction("slorii X17 X17 12 2118")
    tran0.writeAction("slorii X17 X17 12 2128")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 31251")
    tran0.writeAction("slorii X17 X17 12 1140")
    tran0.writeAction("slorii X17 X17 12 1697")
    tran0.writeAction("slorii X17 X17 12 2708")
    tran0.writeAction("slorii X17 X17 12 1713")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 1772")
    tran0.writeAction("slorii X17 X17 12 4007")
    tran0.writeAction("slorii X17 X17 12 3529")
    tran0.writeAction("slorii X17 X17 12 1573")
    tran0.writeAction("slorii X17 X17 12 3724")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 841")
    tran0.writeAction("slorii X17 X17 12 3645")
    tran0.writeAction("slorii X17 X17 12 1737")
    tran0.writeAction("slorii X17 X17 12 2227")
    tran0.writeAction("slorii X17 X17 12 2786")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 47650")
    tran0.writeAction("slorii X17 X17 12 197")
    tran0.writeAction("slorii X17 X17 12 528")
    tran0.writeAction("slorii X17 X17 12 1703")
    tran0.writeAction("slorii X17 X17 12 1666")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 32557")
    tran0.writeAction("slorii X17 X17 12 63")
    tran0.writeAction("slorii X17 X17 12 3722")
    tran0.writeAction("slorii X17 X17 12 2651")
    tran0.writeAction("slorii X17 X17 12 2711")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 116")
    tran0.writeAction("slorii X17 X17 12 3498")
    tran0.writeAction("slorii X17 X17 12 3885")
    tran0.writeAction("slorii X17 X17 12 1913")
    tran0.writeAction("slorii X17 X17 12 2502")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 61770")
    tran0.writeAction("slorii X17 X17 12 35")
    tran0.writeAction("slorii X17 X17 12 2835")
    tran0.writeAction("slorii X17 X17 12 2281")
    tran0.writeAction("slorii X17 X17 12 3019")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X18 26")
    tran0.writeAction("add X7 X18 X5")
    tran0.writeAction("movir X16 2326")
    tran0.writeAction("slorii X16 X16 12 2079")
    tran0.writeAction("slorii X16 X16 12 3826")
    tran0.writeAction("slorii X16 X16 12 4061")
    tran0.writeAction("slorii X16 X16 12 3404")
    tran0.writeAction("hashl64 X16 X17")
    tran0.writeAction("yieldt")
    return efa