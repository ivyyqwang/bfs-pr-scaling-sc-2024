from EFA_v2 import *
def hashl64_89():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-5906713628453776626, -2831515506940380952, -5185642865398252303, 2759270443127882777, 1204604078646953362, 5820483476869055610, -3003806833524364700, 7702284989178367573, 35, 3598900703259098040]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 44551")
    tran0.writeAction("slorii X17 X17 12 564")
    tran0.writeAction("slorii X17 X17 12 2")
    tran0.writeAction("slorii X17 X17 12 221")
    tran0.writeAction("slorii X17 X17 12 782")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 55476")
    tran0.writeAction("slorii X17 X17 12 1786")
    tran0.writeAction("slorii X17 X17 12 1536")
    tran0.writeAction("slorii X17 X17 12 3311")
    tran0.writeAction("slorii X17 X17 12 2280")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 47112")
    tran0.writeAction("slorii X17 X17 12 3668")
    tran0.writeAction("slorii X17 X17 12 2531")
    tran0.writeAction("slorii X17 X17 12 3679")
    tran0.writeAction("slorii X17 X17 12 3313")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 9802")
    tran0.writeAction("slorii X17 X17 12 3677")
    tran0.writeAction("slorii X17 X17 12 2377")
    tran0.writeAction("slorii X17 X17 12 3572")
    tran0.writeAction("slorii X17 X17 12 1049")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 4279")
    tran0.writeAction("slorii X17 X17 12 2512")
    tran0.writeAction("slorii X17 X17 12 1786")
    tran0.writeAction("slorii X17 X17 12 3024")
    tran0.writeAction("slorii X17 X17 12 1426")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 20678")
    tran0.writeAction("slorii X17 X17 12 2094")
    tran0.writeAction("slorii X17 X17 12 587")
    tran0.writeAction("slorii X17 X17 12 3320")
    tran0.writeAction("slorii X17 X17 12 1146")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 54864")
    tran0.writeAction("slorii X17 X17 12 1369")
    tran0.writeAction("slorii X17 X17 12 2441")
    tran0.writeAction("slorii X17 X17 12 3642")
    tran0.writeAction("slorii X17 X17 12 2660")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 27364")
    tran0.writeAction("slorii X17 X17 12 54")
    tran0.writeAction("slorii X17 X17 12 930")
    tran0.writeAction("slorii X17 X17 12 3276")
    tran0.writeAction("slorii X17 X17 12 3669")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X18 35")
    tran0.writeAction("add X7 X18 X5")
    tran0.writeAction("movir X16 12785")
    tran0.writeAction("slorii X16 X16 12 3537")
    tran0.writeAction("slorii X16 X16 12 3887")
    tran0.writeAction("slorii X16 X16 12 2711")
    tran0.writeAction("slorii X16 X16 12 3000")
    tran0.writeAction("hashl64 X16 X17")
    tran0.writeAction("yieldt")
    return efa
