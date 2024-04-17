from EFA_v2 import *
def hashl64_77():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [6418345491203852063, 8761253077607265078, 55635254873701879, 8005679834262229942, 8396571478490002107, 5146847031901944800, 8381965249553591021, -509086498523506131, 51, 5057603441771713593]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 22802")
    tran0.writeAction("slorii X17 X17 12 2227")
    tran0.writeAction("slorii X17 X17 12 2024")
    tran0.writeAction("slorii X17 X17 12 3832")
    tran0.writeAction("slorii X17 X17 12 1823")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 31126")
    tran0.writeAction("slorii X17 X17 12 916")
    tran0.writeAction("slorii X17 X17 12 326")
    tran0.writeAction("slorii X17 X17 12 323")
    tran0.writeAction("slorii X17 X17 12 822")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 197")
    tran0.writeAction("slorii X17 X17 12 2687")
    tran0.writeAction("slorii X17 X17 12 2099")
    tran0.writeAction("slorii X17 X17 12 3011")
    tran0.writeAction("slorii X17 X17 12 3575")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 28441")
    tran0.writeAction("slorii X17 X17 12 3638")
    tran0.writeAction("slorii X17 X17 12 1202")
    tran0.writeAction("slorii X17 X17 12 2901")
    tran0.writeAction("slorii X17 X17 12 950")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 29830")
    tran0.writeAction("slorii X17 X17 12 2516")
    tran0.writeAction("slorii X17 X17 12 1490")
    tran0.writeAction("slorii X17 X17 12 2347")
    tran0.writeAction("slorii X17 X17 12 699")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 18285")
    tran0.writeAction("slorii X17 X17 12 1121")
    tran0.writeAction("slorii X17 X17 12 2873")
    tran0.writeAction("slorii X17 X17 12 3231")
    tran0.writeAction("slorii X17 X17 12 3040")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 29778")
    tran0.writeAction("slorii X17 X17 12 2959")
    tran0.writeAction("slorii X17 X17 12 3107")
    tran0.writeAction("slorii X17 X17 12 1270")
    tran0.writeAction("slorii X17 X17 12 2797")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 63727")
    tran0.writeAction("slorii X17 X17 12 1480")
    tran0.writeAction("slorii X17 X17 12 1759")
    tran0.writeAction("slorii X17 X17 12 2289")
    tran0.writeAction("slorii X17 X17 12 2605")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X18 51")
    tran0.writeAction("add X7 X18 X5")
    tran0.writeAction("movir X16 17968")
    tran0.writeAction("slorii X16 X16 12 888")
    tran0.writeAction("slorii X16 X16 12 2225")
    tran0.writeAction("slorii X16 X16 12 2441")
    tran0.writeAction("slorii X16 X16 12 1081")
    tran0.writeAction("hashl64 X16 X17")
    tran0.writeAction("yieldt")
    return efa