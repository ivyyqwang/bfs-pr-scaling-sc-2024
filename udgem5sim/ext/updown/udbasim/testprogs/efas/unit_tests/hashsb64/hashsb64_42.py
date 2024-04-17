from EFA_v2 import *
def hashsb64_42():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [7625538773792658660, -7314985888442163997, -695416711591692389, -5670207257001564531, -1415822033079640077, 1509624497323761717, -1986801654740833219, 4199029827677614377, 200, 6286]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 27091")
    tran0.writeAction("slorii X17 X17 12 1457")
    tran0.writeAction("slorii X17 X17 12 3304")
    tran0.writeAction("slorii X17 X17 12 3601")
    tran0.writeAction("slorii X17 X17 12 1252")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 39547")
    tran0.writeAction("slorii X17 X17 12 3889")
    tran0.writeAction("slorii X17 X17 12 1862")
    tran0.writeAction("slorii X17 X17 12 1677")
    tran0.writeAction("slorii X17 X17 12 3299")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 63065")
    tran0.writeAction("slorii X17 X17 12 1570")
    tran0.writeAction("slorii X17 X17 12 3950")
    tran0.writeAction("slorii X17 X17 12 2895")
    tran0.writeAction("slorii X17 X17 12 1947")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 45391")
    tran0.writeAction("slorii X17 X17 12 1544")
    tran0.writeAction("slorii X17 X17 12 2739")
    tran0.writeAction("slorii X17 X17 12 2374")
    tran0.writeAction("slorii X17 X17 12 1677")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 60505")
    tran0.writeAction("slorii X17 X17 12 4053")
    tran0.writeAction("slorii X17 X17 12 3261")
    tran0.writeAction("slorii X17 X17 12 477")
    tran0.writeAction("slorii X17 X17 12 4083")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 5363")
    tran0.writeAction("slorii X17 X17 12 1079")
    tran0.writeAction("slorii X17 X17 12 2915")
    tran0.writeAction("slorii X17 X17 12 862")
    tran0.writeAction("slorii X17 X17 12 53")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 58477")
    tran0.writeAction("slorii X17 X17 12 1894")
    tran0.writeAction("slorii X17 X17 12 3050")
    tran0.writeAction("slorii X17 X17 12 58")
    tran0.writeAction("slorii X17 X17 12 3133")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 14917")
    tran0.writeAction("slorii X17 X17 12 3894")
    tran0.writeAction("slorii X17 X17 12 383")
    tran0.writeAction("slorii X17 X17 12 4071")
    tran0.writeAction("slorii X17 X17 12 297")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movlsb X16")
    tran0.writeAction("movir X16 200")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("add X16 X17 X5")
    tran0.writeAction("movir X16 6286")
    tran0.writeAction("hashsb64 X16 X17")
    tran0.writeAction("yieldt")
    return efa
