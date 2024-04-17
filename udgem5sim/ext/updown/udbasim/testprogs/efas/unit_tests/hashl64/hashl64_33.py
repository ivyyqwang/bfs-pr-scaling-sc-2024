from EFA_v2 import *
def hashl64_33():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-7464812065792203893, 1260853252294635038, 4882658753535285787, 5161319451149701230, -733173878143951965, 4504936356248782675, 1427217385720192494, 3437046744869788201, 49, 6310745753788633440]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 39015")
    tran0.writeAction("slorii X17 X17 12 2703")
    tran0.writeAction("slorii X17 X17 12 2551")
    tran0.writeAction("slorii X17 X17 12 1662")
    tran0.writeAction("slorii X17 X17 12 907")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 4479")
    tran0.writeAction("slorii X17 X17 12 1845")
    tran0.writeAction("slorii X17 X17 12 2632")
    tran0.writeAction("slorii X17 X17 12 3758")
    tran0.writeAction("slorii X17 X17 12 3614")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 17346")
    tran0.writeAction("slorii X17 X17 12 2820")
    tran0.writeAction("slorii X17 X17 12 1107")
    tran0.writeAction("slorii X17 X17 12 3777")
    tran0.writeAction("slorii X17 X17 12 2587")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 18336")
    tran0.writeAction("slorii X17 X17 12 2827")
    tran0.writeAction("slorii X17 X17 12 490")
    tran0.writeAction("slorii X17 X17 12 377")
    tran0.writeAction("slorii X17 X17 12 110")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 62931")
    tran0.writeAction("slorii X17 X17 12 995")
    tran0.writeAction("slorii X17 X17 12 3594")
    tran0.writeAction("slorii X17 X17 12 2597")
    tran0.writeAction("slorii X17 X17 12 2979")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 16004")
    tran0.writeAction("slorii X17 X17 12 3067")
    tran0.writeAction("slorii X17 X17 12 3953")
    tran0.writeAction("slorii X17 X17 12 3896")
    tran0.writeAction("slorii X17 X17 12 1875")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 5070")
    tran0.writeAction("slorii X17 X17 12 2026")
    tran0.writeAction("slorii X17 X17 12 1677")
    tran0.writeAction("slorii X17 X17 12 465")
    tran0.writeAction("slorii X17 X17 12 3566")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 12210")
    tran0.writeAction("slorii X17 X17 12 3452")
    tran0.writeAction("slorii X17 X17 12 3552")
    tran0.writeAction("slorii X17 X17 12 1541")
    tran0.writeAction("slorii X17 X17 12 2601")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X18 49")
    tran0.writeAction("add X7 X18 X5")
    tran0.writeAction("movir X16 22420")
    tran0.writeAction("slorii X16 X16 12 1117")
    tran0.writeAction("slorii X16 X16 12 970")
    tran0.writeAction("slorii X16 X16 12 1541")
    tran0.writeAction("slorii X16 X16 12 352")
    tran0.writeAction("hashl64 X16 X17")
    tran0.writeAction("yieldt")
    return efa