from EFA_v2 import *
def hashl64_41():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [4899324524796892109, -2828117504206512073, -2288501654068926677, 8287062956554627282, 112753790656358161, 850236747988711567, -902274875274197886, 2662947169988122945, 55, 8206848562962850333]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 17405")
    tran0.writeAction("slorii X17 X17 12 3675")
    tran0.writeAction("slorii X17 X17 12 659")
    tran0.writeAction("slorii X17 X17 12 3597")
    tran0.writeAction("slorii X17 X17 12 973")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 55488")
    tran0.writeAction("slorii X17 X17 12 2081")
    tran0.writeAction("slorii X17 X17 12 3370")
    tran0.writeAction("slorii X17 X17 12 2894")
    tran0.writeAction("slorii X17 X17 12 55")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 57405")
    tran0.writeAction("slorii X17 X17 12 2493")
    tran0.writeAction("slorii X17 X17 12 3809")
    tran0.writeAction("slorii X17 X17 12 1342")
    tran0.writeAction("slorii X17 X17 12 1835")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 29441")
    tran0.writeAction("slorii X17 X17 12 2301")
    tran0.writeAction("slorii X17 X17 12 2604")
    tran0.writeAction("slorii X17 X17 12 3018")
    tran0.writeAction("slorii X17 X17 12 2258")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 400")
    tran0.writeAction("slorii X17 X17 12 2383")
    tran0.writeAction("slorii X17 X17 12 2471")
    tran0.writeAction("slorii X17 X17 12 618")
    tran0.writeAction("slorii X17 X17 12 1809")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 3020")
    tran0.writeAction("slorii X17 X17 12 2653")
    tran0.writeAction("slorii X17 X17 12 330")
    tran0.writeAction("slorii X17 X17 12 3483")
    tran0.writeAction("slorii X17 X17 12 2191")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 62330")
    tran0.writeAction("slorii X17 X17 12 1948")
    tran0.writeAction("slorii X17 X17 12 2057")
    tran0.writeAction("slorii X17 X17 12 2136")
    tran0.writeAction("slorii X17 X17 12 1154")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 9460")
    tran0.writeAction("slorii X17 X17 12 2821")
    tran0.writeAction("slorii X17 X17 12 1946")
    tran0.writeAction("slorii X17 X17 12 3169")
    tran0.writeAction("slorii X17 X17 12 2369")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X18 55")
    tran0.writeAction("add X7 X18 X5")
    tran0.writeAction("movir X16 29156")
    tran0.writeAction("slorii X16 X16 12 2388")
    tran0.writeAction("slorii X16 X16 12 2376")
    tran0.writeAction("slorii X16 X16 12 3382")
    tran0.writeAction("slorii X16 X16 12 541")
    tran0.writeAction("hashl64 X16 X17")
    tran0.writeAction("yieldt")
    return efa