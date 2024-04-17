from EFA_v2 import *
def hashl64_25():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-7957036231646154186, -7750499238788435216, 1006952882242572073, -2678840537780320402, 3388602085479117591, 7151426353441248567, -4418211873766646644, 6708718091656421956, 13, 6114692556960797938]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 37266")
    tran0.writeAction("slorii X17 X17 12 3803")
    tran0.writeAction("slorii X17 X17 12 1179")
    tran0.writeAction("slorii X17 X17 12 3351")
    tran0.writeAction("slorii X17 X17 12 566")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 38000")
    tran0.writeAction("slorii X17 X17 12 2848")
    tran0.writeAction("slorii X17 X17 12 408")
    tran0.writeAction("slorii X17 X17 12 327")
    tran0.writeAction("slorii X17 X17 12 752")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 3577")
    tran0.writeAction("slorii X17 X17 12 1700")
    tran0.writeAction("slorii X17 X17 12 4019")
    tran0.writeAction("slorii X17 X17 12 2556")
    tran0.writeAction("slorii X17 X17 12 3881")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 56018")
    tran0.writeAction("slorii X17 X17 12 3467")
    tran0.writeAction("slorii X17 X17 12 2391")
    tran0.writeAction("slorii X17 X17 12 2816")
    tran0.writeAction("slorii X17 X17 12 1902")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 12038")
    tran0.writeAction("slorii X17 X17 12 3002")
    tran0.writeAction("slorii X17 X17 12 1190")
    tran0.writeAction("slorii X17 X17 12 535")
    tran0.writeAction("slorii X17 X17 12 791")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 25406")
    tran0.writeAction("slorii X17 X17 12 3974")
    tran0.writeAction("slorii X17 X17 12 234")
    tran0.writeAction("slorii X17 X17 12 953")
    tran0.writeAction("slorii X17 X17 12 1335")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 49839")
    tran0.writeAction("slorii X17 X17 12 1467")
    tran0.writeAction("slorii X17 X17 12 1441")
    tran0.writeAction("slorii X17 X17 12 2973")
    tran0.writeAction("slorii X17 X17 12 3212")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 23834")
    tran0.writeAction("slorii X17 X17 12 632")
    tran0.writeAction("slorii X17 X17 12 3935")
    tran0.writeAction("slorii X17 X17 12 1710")
    tran0.writeAction("slorii X17 X17 12 580")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X18 13")
    tran0.writeAction("add X7 X18 X5")
    tran0.writeAction("movir X16 21723")
    tran0.writeAction("slorii X16 X16 12 3079")
    tran0.writeAction("slorii X16 X16 12 3016")
    tran0.writeAction("slorii X16 X16 12 1529")
    tran0.writeAction("slorii X16 X16 12 1266")
    tran0.writeAction("hashl64 X16 X17")
    tran0.writeAction("yieldt")
    return efa