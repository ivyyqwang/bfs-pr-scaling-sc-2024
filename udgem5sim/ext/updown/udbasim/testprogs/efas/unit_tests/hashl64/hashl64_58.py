from EFA_v2 import *
def hashl64_58():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [8635054607006134502, -5780596936880725509, 8604897451416598030, 6652159717524304192, -2762935727003428702, -6206837951946131904, -2918795830609114154, 7944823003841109553, 14, 6179173337376131857]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 30677")
    tran0.writeAction("slorii X17 X17 12 3590")
    tran0.writeAction("slorii X17 X17 12 2594")
    tran0.writeAction("slorii X17 X17 12 2871")
    tran0.writeAction("slorii X17 X17 12 230")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 44999")
    tran0.writeAction("slorii X17 X17 12 795")
    tran0.writeAction("slorii X17 X17 12 1659")
    tran0.writeAction("slorii X17 X17 12 2102")
    tran0.writeAction("slorii X17 X17 12 507")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 30570")
    tran0.writeAction("slorii X17 X17 12 3018")
    tran0.writeAction("slorii X17 X17 12 1072")
    tran0.writeAction("slorii X17 X17 12 1435")
    tran0.writeAction("slorii X17 X17 12 1550")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 23633")
    tran0.writeAction("slorii X17 X17 12 896")
    tran0.writeAction("slorii X17 X17 12 1208")
    tran0.writeAction("slorii X17 X17 12 815")
    tran0.writeAction("slorii X17 X17 12 320")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 55720")
    tran0.writeAction("slorii X17 X17 12 329")
    tran0.writeAction("slorii X17 X17 12 2126")
    tran0.writeAction("slorii X17 X17 12 2969")
    tran0.writeAction("slorii X17 X17 12 2210")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 43484")
    tran0.writeAction("slorii X17 X17 12 3612")
    tran0.writeAction("slorii X17 X17 12 1175")
    tran0.writeAction("slorii X17 X17 12 3431")
    tran0.writeAction("slorii X17 X17 12 1600")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 55166")
    tran0.writeAction("slorii X17 X17 12 1450")
    tran0.writeAction("slorii X17 X17 12 2064")
    tran0.writeAction("slorii X17 X17 12 2672")
    tran0.writeAction("slorii X17 X17 12 3030")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 28225")
    tran0.writeAction("slorii X17 X17 12 2790")
    tran0.writeAction("slorii X17 X17 12 3507")
    tran0.writeAction("slorii X17 X17 12 1233")
    tran0.writeAction("slorii X17 X17 12 3633")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X18 14")
    tran0.writeAction("add X7 X18 X5")
    tran0.writeAction("movir X16 21952")
    tran0.writeAction("slorii X16 X16 12 3414")
    tran0.writeAction("slorii X16 X16 12 2403")
    tran0.writeAction("slorii X16 X16 12 3560")
    tran0.writeAction("slorii X16 X16 12 2833")
    tran0.writeAction("hashl64 X16 X17")
    tran0.writeAction("yieldt")
    return efa
