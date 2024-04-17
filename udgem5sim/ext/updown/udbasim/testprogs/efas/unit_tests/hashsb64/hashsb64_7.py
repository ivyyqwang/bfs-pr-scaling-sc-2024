from EFA_v2 import *
def hashsb64_7():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-2146328568966526207, 32697609055918841, -4853123206951086109, -5626631761002005815, -7127613341929355052, -8335577238328884059, -4518745080014517615, -2241366900272255822, 304, 4449]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 57910")
    tran0.writeAction("slorii X17 X17 12 2904")
    tran0.writeAction("slorii X17 X17 12 2507")
    tran0.writeAction("slorii X17 X17 12 1956")
    tran0.writeAction("slorii X17 X17 12 2817")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 116")
    tran0.writeAction("slorii X17 X17 12 676")
    tran0.writeAction("slorii X17 X17 12 3420")
    tran0.writeAction("slorii X17 X17 12 3205")
    tran0.writeAction("slorii X17 X17 12 2809")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 48294")
    tran0.writeAction("slorii X17 X17 12 994")
    tran0.writeAction("slorii X17 X17 12 2046")
    tran0.writeAction("slorii X17 X17 12 1949")
    tran0.writeAction("slorii X17 X17 12 2019")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 45546")
    tran0.writeAction("slorii X17 X17 12 771")
    tran0.writeAction("slorii X17 X17 12 2427")
    tran0.writeAction("slorii X17 X17 12 2231")
    tran0.writeAction("slorii X17 X17 12 2761")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 40213")
    tran0.writeAction("slorii X17 X17 12 2582")
    tran0.writeAction("slorii X17 X17 12 3553")
    tran0.writeAction("slorii X17 X17 12 3956")
    tran0.writeAction("slorii X17 X17 12 2260")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 35922")
    tran0.writeAction("slorii X17 X17 12 330")
    tran0.writeAction("slorii X17 X17 12 2655")
    tran0.writeAction("slorii X17 X17 12 2356")
    tran0.writeAction("slorii X17 X17 12 1189")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 49482")
    tran0.writeAction("slorii X17 X17 12 788")
    tran0.writeAction("slorii X17 X17 12 2691")
    tran0.writeAction("slorii X17 X17 12 780")
    tran0.writeAction("slorii X17 X17 12 2705")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 57573")
    tran0.writeAction("slorii X17 X17 12 266")
    tran0.writeAction("slorii X17 X17 12 3569")
    tran0.writeAction("slorii X17 X17 12 3906")
    tran0.writeAction("slorii X17 X17 12 3250")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movlsb X16")
    tran0.writeAction("movir X16 304")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("add X16 X17 X5")
    tran0.writeAction("movir X16 4449")
    tran0.writeAction("hashsb64 X16 X17")
    tran0.writeAction("yieldt")
    return efa