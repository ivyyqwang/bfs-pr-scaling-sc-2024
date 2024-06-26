from EFA_v2 import *
def hashsb64_16():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [5923939810058238529, 6757154437388085413, -8309827084549135236, -6280498374080923948, 2278330301940738521, -3029570555674778162, 4050626807146359638, 4905556450252248868, 128, 12067]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 21046")
    tran0.writeAction("slorii X17 X17 12 253")
    tran0.writeAction("slorii X17 X17 12 3825")
    tran0.writeAction("slorii X17 X17 12 1295")
    tran0.writeAction("slorii X17 X17 12 2625")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 24006")
    tran0.writeAction("slorii X17 X17 12 962")
    tran0.writeAction("slorii X17 X17 12 2284")
    tran0.writeAction("slorii X17 X17 12 3978")
    tran0.writeAction("slorii X17 X17 12 2213")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 36013")
    tran0.writeAction("slorii X17 X17 12 2308")
    tran0.writeAction("slorii X17 X17 12 2880")
    tran0.writeAction("slorii X17 X17 12 2166")
    tran0.writeAction("slorii X17 X17 12 1148")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 43223")
    tran0.writeAction("slorii X17 X17 12 768")
    tran0.writeAction("slorii X17 X17 12 280")
    tran0.writeAction("slorii X17 X17 12 1999")
    tran0.writeAction("slorii X17 X17 12 1748")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 8094")
    tran0.writeAction("slorii X17 X17 12 1045")
    tran0.writeAction("slorii X17 X17 12 1704")
    tran0.writeAction("slorii X17 X17 12 762")
    tran0.writeAction("slorii X17 X17 12 2521")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 54772")
    tran0.writeAction("slorii X17 X17 12 3290")
    tran0.writeAction("slorii X17 X17 12 391")
    tran0.writeAction("slorii X17 X17 12 90")
    tran0.writeAction("slorii X17 X17 12 1486")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 14390")
    tran0.writeAction("slorii X17 X17 12 2937")
    tran0.writeAction("slorii X17 X17 12 3765")
    tran0.writeAction("slorii X17 X17 12 2594")
    tran0.writeAction("slorii X17 X17 12 2902")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 17428")
    tran0.writeAction("slorii X17 X17 12 153")
    tran0.writeAction("slorii X17 X17 12 2506")
    tran0.writeAction("slorii X17 X17 12 3733")
    tran0.writeAction("slorii X17 X17 12 1828")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movlsb X16")
    tran0.writeAction("movir X16 128")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("add X16 X17 X5")
    tran0.writeAction("movir X16 12067")
    tran0.writeAction("hashsb64 X16 X17")
    tran0.writeAction("yieldt")
    return efa
