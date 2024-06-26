from EFA_v2 import *
def hashsb64_68():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-8484622288025317581, 3468005077258737036, 1285434646906659026, 731115814419943449, 8015741876090430756, -7020596189689204528, 3063074161587002310, -1618494776799585654, 376, 8166]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 35392")
    tran0.writeAction("slorii X17 X17 12 2319")
    tran0.writeAction("slorii X17 X17 12 2948")
    tran0.writeAction("slorii X17 X17 12 3640")
    tran0.writeAction("slorii X17 X17 12 3891")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 12320")
    tran0.writeAction("slorii X17 X17 12 3395")
    tran0.writeAction("slorii X17 X17 12 3669")
    tran0.writeAction("slorii X17 X17 12 1057")
    tran0.writeAction("slorii X17 X17 12 1420")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 4566")
    tran0.writeAction("slorii X17 X17 12 3200")
    tran0.writeAction("slorii X17 X17 12 54")
    tran0.writeAction("slorii X17 X17 12 3486")
    tran0.writeAction("slorii X17 X17 12 210")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 2597")
    tran0.writeAction("slorii X17 X17 12 1823")
    tran0.writeAction("slorii X17 X17 12 1448")
    tran0.writeAction("slorii X17 X17 12 701")
    tran0.writeAction("slorii X17 X17 12 25")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 28477")
    tran0.writeAction("slorii X17 X17 12 2604")
    tran0.writeAction("slorii X17 X17 12 1119")
    tran0.writeAction("slorii X17 X17 12 2430")
    tran0.writeAction("slorii X17 X17 12 1316")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 40593")
    tran0.writeAction("slorii X17 X17 12 3407")
    tran0.writeAction("slorii X17 X17 12 1618")
    tran0.writeAction("slorii X17 X17 12 467")
    tran0.writeAction("slorii X17 X17 12 208")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 10882")
    tran0.writeAction("slorii X17 X17 12 923")
    tran0.writeAction("slorii X17 X17 12 2202")
    tran0.writeAction("slorii X17 X17 12 289")
    tran0.writeAction("slorii X17 X17 12 3014")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 59785")
    tran0.writeAction("slorii X17 X17 12 3897")
    tran0.writeAction("slorii X17 X17 12 862")
    tran0.writeAction("slorii X17 X17 12 145")
    tran0.writeAction("slorii X17 X17 12 2698")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movlsb X16")
    tran0.writeAction("movir X16 376")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("add X16 X17 X5")
    tran0.writeAction("movir X16 8166")
    tran0.writeAction("hashsb64 X16 X17")
    tran0.writeAction("yieldt")
    return efa
