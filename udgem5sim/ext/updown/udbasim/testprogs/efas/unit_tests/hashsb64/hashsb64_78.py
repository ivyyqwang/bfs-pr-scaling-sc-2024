from EFA_v2 import *
def hashsb64_78():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [6907836040241472263, 2362882334632344951, -3996066820627669838, -9180697863014694813, 8983839210776246424, 4151511029351035972, 6724089174760406236, 4769817094173567894, 344, 25106]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 24541")
    tran0.writeAction("slorii X17 X17 12 2308")
    tran0.writeAction("slorii X17 X17 12 1921")
    tran0.writeAction("slorii X17 X17 12 958")
    tran0.writeAction("slorii X17 X17 12 775")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 8394")
    tran0.writeAction("slorii X17 X17 12 2639")
    tran0.writeAction("slorii X17 X17 12 1753")
    tran0.writeAction("slorii X17 X17 12 3303")
    tran0.writeAction("slorii X17 X17 12 3447")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 51339")
    tran0.writeAction("slorii X17 X17 12 486")
    tran0.writeAction("slorii X17 X17 12 1553")
    tran0.writeAction("slorii X17 X17 12 3125")
    tran0.writeAction("slorii X17 X17 12 3250")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 32919")
    tran0.writeAction("slorii X17 X17 12 2494")
    tran0.writeAction("slorii X17 X17 12 3932")
    tran0.writeAction("slorii X17 X17 12 3364")
    tran0.writeAction("slorii X17 X17 12 99")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 31917")
    tran0.writeAction("slorii X17 X17 12 34")
    tran0.writeAction("slorii X17 X17 12 2541")
    tran0.writeAction("slorii X17 X17 12 2227")
    tran0.writeAction("slorii X17 X17 12 2200")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 14749")
    tran0.writeAction("slorii X17 X17 12 532")
    tran0.writeAction("slorii X17 X17 12 2329")
    tran0.writeAction("slorii X17 X17 12 2395")
    tran0.writeAction("slorii X17 X17 12 1092")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 23888")
    tran0.writeAction("slorii X17 X17 12 3127")
    tran0.writeAction("slorii X17 X17 12 2699")
    tran0.writeAction("slorii X17 X17 12 2635")
    tran0.writeAction("slorii X17 X17 12 3292")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 16945")
    tran0.writeAction("slorii X17 X17 12 3254")
    tran0.writeAction("slorii X17 X17 12 37")
    tran0.writeAction("slorii X17 X17 12 3282")
    tran0.writeAction("slorii X17 X17 12 2966")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movlsb X16")
    tran0.writeAction("movir X16 344")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("add X16 X17 X5")
    tran0.writeAction("movir X16 25106")
    tran0.writeAction("hashsb64 X16 X17")
    tran0.writeAction("yieldt")
    return efa
