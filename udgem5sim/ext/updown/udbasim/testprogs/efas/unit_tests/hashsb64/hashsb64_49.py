from EFA_v2 import *
def hashsb64_49():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-7799660170517929464, -7661554964052875331, 1324440742766845876, -629301231340322105, -5941049105161130836, 1222712822596445694, -1806344552168301502, -6435342310088119550, 224, 13450]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 37826")
    tran0.writeAction("slorii X17 X17 12 166")
    tran0.writeAction("slorii X17 X17 12 1591")
    tran0.writeAction("slorii X17 X17 12 2114")
    tran0.writeAction("slorii X17 X17 12 520")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 38316")
    tran0.writeAction("slorii X17 X17 12 2821")
    tran0.writeAction("slorii X17 X17 12 2644")
    tran0.writeAction("slorii X17 X17 12 2038")
    tran0.writeAction("slorii X17 X17 12 1981")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 4705")
    tran0.writeAction("slorii X17 X17 12 1469")
    tran0.writeAction("slorii X17 X17 12 1694")
    tran0.writeAction("slorii X17 X17 12 2753")
    tran0.writeAction("slorii X17 X17 12 4020")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 63300")
    tran0.writeAction("slorii X17 X17 12 1117")
    tran0.writeAction("slorii X17 X17 12 3393")
    tran0.writeAction("slorii X17 X17 12 1000")
    tran0.writeAction("slorii X17 X17 12 711")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 44429")
    tran0.writeAction("slorii X17 X17 12 629")
    tran0.writeAction("slorii X17 X17 12 221")
    tran0.writeAction("slorii X17 X17 12 2942")
    tran0.writeAction("slorii X17 X17 12 3244")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 4343")
    tran0.writeAction("slorii X17 X17 12 3885")
    tran0.writeAction("slorii X17 X17 12 1405")
    tran0.writeAction("slorii X17 X17 12 722")
    tran0.writeAction("slorii X17 X17 12 1534")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 59118")
    tran0.writeAction("slorii X17 X17 12 2355")
    tran0.writeAction("slorii X17 X17 12 834")
    tran0.writeAction("slorii X17 X17 12 189")
    tran0.writeAction("slorii X17 X17 12 3138")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 42673")
    tran0.writeAction("slorii X17 X17 12 292")
    tran0.writeAction("slorii X17 X17 12 975")
    tran0.writeAction("slorii X17 X17 12 638")
    tran0.writeAction("slorii X17 X17 12 2818")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movlsb X16")
    tran0.writeAction("movir X16 224")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("add X16 X17 X5")
    tran0.writeAction("movir X16 13450")
    tran0.writeAction("hashsb64 X16 X17")
    tran0.writeAction("yieldt")
    return efa
