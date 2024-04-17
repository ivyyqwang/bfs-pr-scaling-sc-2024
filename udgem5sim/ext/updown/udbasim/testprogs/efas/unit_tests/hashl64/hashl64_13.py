from EFA_v2 import *
def hashl64_13():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [4988493372201252972, -7490618847948160902, 5398297768495385222, 9029047057897849566, -6858353845491863406, 4653254248142921318, 4837454686894850762, 5252873127586203048, 18, 275124088292352617]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 17722")
    tran0.writeAction("slorii X17 X17 12 2820")
    tran0.writeAction("slorii X17 X17 12 2742")
    tran0.writeAction("slorii X17 X17 12 1827")
    tran0.writeAction("slorii X17 X17 12 2156")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 38923")
    tran0.writeAction("slorii X17 X17 12 3997")
    tran0.writeAction("slorii X17 X17 12 2116")
    tran0.writeAction("slorii X17 X17 12 836")
    tran0.writeAction("slorii X17 X17 12 122")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 19178")
    tran0.writeAction("slorii X17 X17 12 2483")
    tran0.writeAction("slorii X17 X17 12 2066")
    tran0.writeAction("slorii X17 X17 12 3896")
    tran0.writeAction("slorii X17 X17 12 2694")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 32077")
    tran0.writeAction("slorii X17 X17 12 2535")
    tran0.writeAction("slorii X17 X17 12 1554")
    tran0.writeAction("slorii X17 X17 12 1176")
    tran0.writeAction("slorii X17 X17 12 734")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 41170")
    tran0.writeAction("slorii X17 X17 12 952")
    tran0.writeAction("slorii X17 X17 12 959")
    tran0.writeAction("slorii X17 X17 12 2143")
    tran0.writeAction("slorii X17 X17 12 146")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 16531")
    tran0.writeAction("slorii X17 X17 12 2785")
    tran0.writeAction("slorii X17 X17 12 1454")
    tran0.writeAction("slorii X17 X17 12 557")
    tran0.writeAction("slorii X17 X17 12 3686")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 17186")
    tran0.writeAction("slorii X17 X17 12 374")
    tran0.writeAction("slorii X17 X17 12 2149")
    tran0.writeAction("slorii X17 X17 12 1704")
    tran0.writeAction("slorii X17 X17 12 714")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 18661")
    tran0.writeAction("slorii X17 X17 12 3908")
    tran0.writeAction("slorii X17 X17 12 1875")
    tran0.writeAction("slorii X17 X17 12 3976")
    tran0.writeAction("slorii X17 X17 12 1448")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X18 18")
    tran0.writeAction("add X7 X18 X5")
    tran0.writeAction("movir X16 977")
    tran0.writeAction("slorii X16 X16 12 1790")
    tran0.writeAction("slorii X16 X16 12 1679")
    tran0.writeAction("slorii X16 X16 12 3354")
    tran0.writeAction("slorii X16 X16 12 617")
    tran0.writeAction("hashl64 X16 X17")
    tran0.writeAction("yieldt")
    return efa