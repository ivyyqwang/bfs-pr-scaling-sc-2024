from EFA_v2 import *
def hashl_76():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-8162603757903945993, -254447259098872926, -1465757872746682016, -3039962963630622452, 4906345962665027555]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 36536")
    tran0.writeAction("slorii X17 X17 12 2482")
    tran0.writeAction("slorii X17 X17 12 295")
    tran0.writeAction("slorii X17 X17 12 3549")
    tran0.writeAction("slorii X17 X17 12 3831")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 64632")
    tran0.writeAction("slorii X17 X17 12 89")
    tran0.writeAction("slorii X17 X17 12 227")
    tran0.writeAction("slorii X17 X17 12 1392")
    tran0.writeAction("slorii X17 X17 12 930")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 60328")
    tran0.writeAction("slorii X17 X17 12 2383")
    tran0.writeAction("slorii X17 X17 12 2828")
    tran0.writeAction("slorii X17 X17 12 826")
    tran0.writeAction("slorii X17 X17 12 2400")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 54735")
    tran0.writeAction("slorii X17 X17 12 3612")
    tran0.writeAction("slorii X17 X17 12 2686")
    tran0.writeAction("slorii X17 X17 12 1855")
    tran0.writeAction("slorii X17 X17 12 2316")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 17430")
    tran0.writeAction("slorii X17 X17 12 3450")
    tran0.writeAction("slorii X17 X17 12 2169")
    tran0.writeAction("slorii X17 X17 12 3362")
    tran0.writeAction("slorii X17 X17 12 2019")
    tran0.writeAction("hashl X16 X17 4")
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movrl X17 0(X16) 0 8")
    tran0.writeAction("yieldt")
    return efa