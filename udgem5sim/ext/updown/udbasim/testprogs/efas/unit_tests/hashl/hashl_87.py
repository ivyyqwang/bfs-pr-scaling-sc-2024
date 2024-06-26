from EFA_v2 import *
def hashl_87():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-8922527047767845891, -6131673181389747157, 8499806293696003895, -2681191757135154744, 7091560384386886370, -2022947809391611433]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 33836")
    tran0.writeAction("slorii X17 X17 12 3342")
    tran0.writeAction("slorii X17 X17 12 3186")
    tran0.writeAction("slorii X17 X17 12 4025")
    tran0.writeAction("slorii X17 X17 12 1021")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 43751")
    tran0.writeAction("slorii X17 X17 12 3771")
    tran0.writeAction("slorii X17 X17 12 2688")
    tran0.writeAction("slorii X17 X17 12 1944")
    tran0.writeAction("slorii X17 X17 12 3115")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 30197")
    tran0.writeAction("slorii X17 X17 12 1548")
    tran0.writeAction("slorii X17 X17 12 2635")
    tran0.writeAction("slorii X17 X17 12 1555")
    tran0.writeAction("slorii X17 X17 12 3895")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 56010")
    tran0.writeAction("slorii X17 X17 12 2020")
    tran0.writeAction("slorii X17 X17 12 3437")
    tran0.writeAction("slorii X17 X17 12 1039")
    tran0.writeAction("slorii X17 X17 12 456")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 25194")
    tran0.writeAction("slorii X17 X17 12 1161")
    tran0.writeAction("slorii X17 X17 12 2254")
    tran0.writeAction("slorii X17 X17 12 2510")
    tran0.writeAction("slorii X17 X17 12 2786")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 58349")
    tran0.writeAction("slorii X17 X17 12 186")
    tran0.writeAction("slorii X17 X17 12 3958")
    tran0.writeAction("slorii X17 X17 12 239")
    tran0.writeAction("slorii X17 X17 12 471")
    tran0.writeAction("hashl X16 X17 5")
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movrl X17 0(X16) 0 8")
    tran0.writeAction("yieldt")
    return efa
