from EFA_v2 import *
def hashl64_61():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-1389374997279530703, 2084385672965210164, 6600629683572885025, 5192790904108664824, -4084197876009921341, 471984319748191415, 8479315934536550540, -4908905935932416652, 16, 3650740883078543731]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 60599")
    tran0.writeAction("slorii X17 X17 12 3884")
    tran0.writeAction("slorii X17 X17 12 3355")
    tran0.writeAction("slorii X17 X17 12 1410")
    tran0.writeAction("slorii X17 X17 12 305")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 7405")
    tran0.writeAction("slorii X17 X17 12 923")
    tran0.writeAction("slorii X17 X17 12 2524")
    tran0.writeAction("slorii X17 X17 12 20")
    tran0.writeAction("slorii X17 X17 12 52")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 23450")
    tran0.writeAction("slorii X17 X17 12 603")
    tran0.writeAction("slorii X17 X17 12 2495")
    tran0.writeAction("slorii X17 X17 12 1068")
    tran0.writeAction("slorii X17 X17 12 1569")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 18448")
    tran0.writeAction("slorii X17 X17 12 2045")
    tran0.writeAction("slorii X17 X17 12 144")
    tran0.writeAction("slorii X17 X17 12 1132")
    tran0.writeAction("slorii X17 X17 12 2040")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 51026")
    tran0.writeAction("slorii X17 X17 12 58")
    tran0.writeAction("slorii X17 X17 12 3000")
    tran0.writeAction("slorii X17 X17 12 97")
    tran0.writeAction("slorii X17 X17 12 1219")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 1676")
    tran0.writeAction("slorii X17 X17 12 3379")
    tran0.writeAction("slorii X17 X17 12 3318")
    tran0.writeAction("slorii X17 X17 12 595")
    tran0.writeAction("slorii X17 X17 12 1207")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 30124")
    tran0.writeAction("slorii X17 X17 12 2382")
    tran0.writeAction("slorii X17 X17 12 2760")
    tran0.writeAction("slorii X17 X17 12 1476")
    tran0.writeAction("slorii X17 X17 12 2188")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 48096")
    tran0.writeAction("slorii X17 X17 12 256")
    tran0.writeAction("slorii X17 X17 12 3916")
    tran0.writeAction("slorii X17 X17 12 3857")
    tran0.writeAction("slorii X17 X17 12 3444")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X18 16")
    tran0.writeAction("add X7 X18 X5")
    tran0.writeAction("movir X16 12970")
    tran0.writeAction("slorii X16 X16 12 151")
    tran0.writeAction("slorii X16 X16 12 3486")
    tran0.writeAction("slorii X16 X16 12 3655")
    tran0.writeAction("slorii X16 X16 12 2419")
    tran0.writeAction("hashl64 X16 X17")
    tran0.writeAction("yieldt")
    return efa
