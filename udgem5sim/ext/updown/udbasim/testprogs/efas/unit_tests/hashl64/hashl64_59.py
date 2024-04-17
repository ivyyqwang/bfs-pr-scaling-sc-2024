from EFA_v2 import *
def hashl64_59():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-2899273608178523247, 3427096577209884192, -622004836380541729, -5513672038957230508, -8828744309743968016, -5041140487295269267, -3823890195679441142, 6306504585205697223, 20, 2732313576886385411]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 55235")
    tran0.writeAction("slorii X17 X17 12 2912")
    tran0.writeAction("slorii X17 X17 12 941")
    tran0.writeAction("slorii X17 X17 12 3498")
    tran0.writeAction("slorii X17 X17 12 913")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 12175")
    tran0.writeAction("slorii X17 X17 12 2018")
    tran0.writeAction("slorii X17 X17 12 3567")
    tran0.writeAction("slorii X17 X17 12 2261")
    tran0.writeAction("slorii X17 X17 12 3616")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 63326")
    tran0.writeAction("slorii X17 X17 12 798")
    tran0.writeAction("slorii X17 X17 12 1430")
    tran0.writeAction("slorii X17 X17 12 3943")
    tran0.writeAction("slorii X17 X17 12 3295")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 45947")
    tran0.writeAction("slorii X17 X17 12 2055")
    tran0.writeAction("slorii X17 X17 12 3653")
    tran0.writeAction("slorii X17 X17 12 3893")
    tran0.writeAction("slorii X17 X17 12 1620")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 34169")
    tran0.writeAction("slorii X17 X17 12 4093")
    tran0.writeAction("slorii X17 X17 12 948")
    tran0.writeAction("slorii X17 X17 12 3930")
    tran0.writeAction("slorii X17 X17 12 240")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 47626")
    tran0.writeAction("slorii X17 X17 12 1110")
    tran0.writeAction("slorii X17 X17 12 3991")
    tran0.writeAction("slorii X17 X17 12 3792")
    tran0.writeAction("slorii X17 X17 12 1645")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 51950")
    tran0.writeAction("slorii X17 X17 12 3330")
    tran0.writeAction("slorii X17 X17 12 122")
    tran0.writeAction("slorii X17 X17 12 1752")
    tran0.writeAction("slorii X17 X17 12 3850")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 22405")
    tran0.writeAction("slorii X17 X17 12 840")
    tran0.writeAction("slorii X17 X17 12 455")
    tran0.writeAction("slorii X17 X17 12 2284")
    tran0.writeAction("slorii X17 X17 12 2759")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X18 20")
    tran0.writeAction("add X7 X18 X5")
    tran0.writeAction("movir X16 9707")
    tran0.writeAction("slorii X16 X16 12 523")
    tran0.writeAction("slorii X16 X16 12 2245")
    tran0.writeAction("slorii X16 X16 12 1187")
    tran0.writeAction("slorii X16 X16 12 2819")
    tran0.writeAction("hashl64 X16 X17")
    tran0.writeAction("yieldt")
    return efa