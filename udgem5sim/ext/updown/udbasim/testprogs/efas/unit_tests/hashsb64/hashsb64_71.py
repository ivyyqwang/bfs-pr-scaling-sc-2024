from EFA_v2 import *
def hashsb64_71():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-5407351404491017850, 1538756484282620651, 1261913174131221039, -624563547037239415, -52670041825326176, -9167944784220951553, 7457313062837463181, -5149188303876678887, 368, 19110]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 46325")
    tran0.writeAction("slorii X17 X17 12 936")
    tran0.writeAction("slorii X17 X17 12 3079")
    tran0.writeAction("slorii X17 X17 12 2471")
    tran0.writeAction("slorii X17 X17 12 390")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 5466")
    tran0.writeAction("slorii X17 X17 12 3117")
    tran0.writeAction("slorii X17 X17 12 3753")
    tran0.writeAction("slorii X17 X17 12 2025")
    tran0.writeAction("slorii X17 X17 12 2795")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 4483")
    tran0.writeAction("slorii X17 X17 12 885")
    tran0.writeAction("slorii X17 X17 12 2193")
    tran0.writeAction("slorii X17 X17 12 1954")
    tran0.writeAction("slorii X17 X17 12 559")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 63317")
    tran0.writeAction("slorii X17 X17 12 428")
    tran0.writeAction("slorii X17 X17 12 855")
    tran0.writeAction("slorii X17 X17 12 767")
    tran0.writeAction("slorii X17 X17 12 1929")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 65348")
    tran0.writeAction("slorii X17 X17 12 3598")
    tran0.writeAction("slorii X17 X17 12 66")
    tran0.writeAction("slorii X17 X17 12 2852")
    tran0.writeAction("slorii X17 X17 12 2976")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 32964")
    tran0.writeAction("slorii X17 X17 12 3756")
    tran0.writeAction("slorii X17 X17 12 2792")
    tran0.writeAction("slorii X17 X17 12 470")
    tran0.writeAction("slorii X17 X17 12 3071")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 26493")
    tran0.writeAction("slorii X17 X17 12 2859")
    tran0.writeAction("slorii X17 X17 12 2137")
    tran0.writeAction("slorii X17 X17 12 1258")
    tran0.writeAction("slorii X17 X17 12 2189")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 47242")
    tran0.writeAction("slorii X17 X17 12 1672")
    tran0.writeAction("slorii X17 X17 12 1257")
    tran0.writeAction("slorii X17 X17 12 3417")
    tran0.writeAction("slorii X17 X17 12 2841")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movlsb X16")
    tran0.writeAction("movir X16 368")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("add X16 X17 X5")
    tran0.writeAction("movir X16 19110")
    tran0.writeAction("hashsb64 X16 X17")
    tran0.writeAction("yieldt")
    return efa
