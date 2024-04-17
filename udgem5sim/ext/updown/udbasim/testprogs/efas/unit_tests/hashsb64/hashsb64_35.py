from EFA_v2 import *
def hashsb64_35():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [3550463951875153705, 8476438499487720154, -3070100175063559748, 4489434490271458774, -296191855120003202, 1035381550227325959, 7622131955950221892, -2014187096951593109, 272, 4588]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 12613")
    tran0.writeAction("slorii X17 X17 12 3202")
    tran0.writeAction("slorii X17 X17 12 1839")
    tran0.writeAction("slorii X17 X17 12 1425")
    tran0.writeAction("slorii X17 X17 12 3881")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 30114")
    tran0.writeAction("slorii X17 X17 12 1470")
    tran0.writeAction("slorii X17 X17 12 1978")
    tran0.writeAction("slorii X17 X17 12 1682")
    tran0.writeAction("slorii X17 X17 12 730")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 54628")
    tran0.writeAction("slorii X17 X17 12 3330")
    tran0.writeAction("slorii X17 X17 12 2088")
    tran0.writeAction("slorii X17 X17 12 1933")
    tran0.writeAction("slorii X17 X17 12 444")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 15949")
    tran0.writeAction("slorii X17 X17 12 2766")
    tran0.writeAction("slorii X17 X17 12 515")
    tran0.writeAction("slorii X17 X17 12 70")
    tran0.writeAction("slorii X17 X17 12 1494")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 64483")
    tran0.writeAction("slorii X17 X17 12 2929")
    tran0.writeAction("slorii X17 X17 12 954")
    tran0.writeAction("slorii X17 X17 12 852")
    tran0.writeAction("slorii X17 X17 12 3966")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 3678")
    tran0.writeAction("slorii X17 X17 12 1696")
    tran0.writeAction("slorii X17 X17 12 2244")
    tran0.writeAction("slorii X17 X17 12 1200")
    tran0.writeAction("slorii X17 X17 12 1031")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 27079")
    tran0.writeAction("slorii X17 X17 12 1034")
    tran0.writeAction("slorii X17 X17 12 337")
    tran0.writeAction("slorii X17 X17 12 2319")
    tran0.writeAction("slorii X17 X17 12 2628")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 58380")
    tran0.writeAction("slorii X17 X17 12 696")
    tran0.writeAction("slorii X17 X17 12 455")
    tran0.writeAction("slorii X17 X17 12 102")
    tran0.writeAction("slorii X17 X17 12 1899")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movlsb X16")
    tran0.writeAction("movir X16 272")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("add X16 X17 X5")
    tran0.writeAction("movir X16 4588")
    tran0.writeAction("hashsb64 X16 X17")
    tran0.writeAction("yieldt")
    return efa