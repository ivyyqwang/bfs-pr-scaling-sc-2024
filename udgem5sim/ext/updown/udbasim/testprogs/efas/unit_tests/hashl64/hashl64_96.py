from EFA_v2 import *
def hashl64_96():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [6153478556458852535, 974275965048417038, 2401694544408493087, 2923993364381022898, -4937780740538231525, -2540486714824758720, 4456385316560049453, -7514108782541585332, 30, 5805158427584729292]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 21861")
    tran0.writeAction("slorii X17 X17 12 2242")
    tran0.writeAction("slorii X17 X17 12 1282")
    tran0.writeAction("slorii X17 X17 12 2922")
    tran0.writeAction("slorii X17 X17 12 183")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 3461")
    tran0.writeAction("slorii X17 X17 12 1325")
    tran0.writeAction("slorii X17 X17 12 1033")
    tran0.writeAction("slorii X17 X17 12 3734")
    tran0.writeAction("slorii X17 X17 12 2830")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 8532")
    tran0.writeAction("slorii X17 X17 12 2183")
    tran0.writeAction("slorii X17 X17 12 1698")
    tran0.writeAction("slorii X17 X17 12 1891")
    tran0.writeAction("slorii X17 X17 12 3103")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 10388")
    tran0.writeAction("slorii X17 X17 12 455")
    tran0.writeAction("slorii X17 X17 12 2321")
    tran0.writeAction("slorii X17 X17 12 2171")
    tran0.writeAction("slorii X17 X17 12 2738")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 47993")
    tran0.writeAction("slorii X17 X17 12 1961")
    tran0.writeAction("slorii X17 X17 12 1013")
    tran0.writeAction("slorii X17 X17 12 1857")
    tran0.writeAction("slorii X17 X17 12 1307")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 56510")
    tran0.writeAction("slorii X17 X17 12 1548")
    tran0.writeAction("slorii X17 X17 12 2814")
    tran0.writeAction("slorii X17 X17 12 1110")
    tran0.writeAction("slorii X17 X17 12 2624")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 15832")
    tran0.writeAction("slorii X17 X17 12 1069")
    tran0.writeAction("slorii X17 X17 12 1439")
    tran0.writeAction("slorii X17 X17 12 3393")
    tran0.writeAction("slorii X17 X17 12 1325")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 38840")
    tran0.writeAction("slorii X17 X17 12 2141")
    tran0.writeAction("slorii X17 X17 12 4012")
    tran0.writeAction("slorii X17 X17 12 3956")
    tran0.writeAction("slorii X17 X17 12 1100")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X18 30")
    tran0.writeAction("add X7 X18 X5")
    tran0.writeAction("movir X16 20624")
    tran0.writeAction("slorii X16 X16 12 269")
    tran0.writeAction("slorii X16 X16 12 1333")
    tran0.writeAction("slorii X16 X16 12 217")
    tran0.writeAction("slorii X16 X16 12 204")
    tran0.writeAction("hashl64 X16 X17")
    tran0.writeAction("yieldt")
    return efa
