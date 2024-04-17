from EFA_v2 import *
def hashsb64_53():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [466471703424158236, 969057579330714624, 1414006504055088018, 2130952836625841586, 4978469612944326907, 4552264631074818858, 658570364507188076, -5520586400834869594, 16, 21013]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 1657")
    tran0.writeAction("slorii X17 X17 12 984")
    tran0.writeAction("slorii X17 X17 12 2804")
    tran0.writeAction("slorii X17 X17 12 1508")
    tran0.writeAction("slorii X17 X17 12 2588")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 3442")
    tran0.writeAction("slorii X17 X17 12 3211")
    tran0.writeAction("slorii X17 X17 12 3054")
    tran0.writeAction("slorii X17 X17 12 3715")
    tran0.writeAction("slorii X17 X17 12 3072")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 5023")
    tran0.writeAction("slorii X17 X17 12 2294")
    tran0.writeAction("slorii X17 X17 12 3192")
    tran0.writeAction("slorii X17 X17 12 1210")
    tran0.writeAction("slorii X17 X17 12 914")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 7570")
    tran0.writeAction("slorii X17 X17 12 2725")
    tran0.writeAction("slorii X17 X17 12 140")
    tran0.writeAction("slorii X17 X17 12 795")
    tran0.writeAction("slorii X17 X17 12 3506")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 17687")
    tran0.writeAction("slorii X17 X17 12 315")
    tran0.writeAction("slorii X17 X17 12 3172")
    tran0.writeAction("slorii X17 X17 12 2552")
    tran0.writeAction("slorii X17 X17 12 251")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 16172")
    tran0.writeAction("slorii X17 X17 12 3657")
    tran0.writeAction("slorii X17 X17 12 34")
    tran0.writeAction("slorii X17 X17 12 3232")
    tran0.writeAction("slorii X17 X17 12 2858")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 2339")
    tran0.writeAction("slorii X17 X17 12 2916")
    tran0.writeAction("slorii X17 X17 12 476")
    tran0.writeAction("slorii X17 X17 12 206")
    tran0.writeAction("slorii X17 X17 12 2924")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 45922")
    tran0.writeAction("slorii X17 X17 12 3838")
    tran0.writeAction("slorii X17 X17 12 2802")
    tran0.writeAction("slorii X17 X17 12 1578")
    tran0.writeAction("slorii X17 X17 12 1702")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movlsb X16")
    tran0.writeAction("movir X16 16")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("add X16 X17 X5")
    tran0.writeAction("movir X16 21013")
    tran0.writeAction("hashsb64 X16 X17")
    tran0.writeAction("yieldt")
    return efa
