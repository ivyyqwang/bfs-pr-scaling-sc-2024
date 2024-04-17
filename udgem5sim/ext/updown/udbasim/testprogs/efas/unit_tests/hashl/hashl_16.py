from EFA_v2 import *
def hashl_16():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-6331377732053059521, 8719460693613394882, -4334324544010153339, 6378228058593290067, -3837416582317601205, 2689652602536473379, -3648404255031893126, -8985595297018103046, -3561864635560408420]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 43042")
    tran0.writeAction("slorii X17 X17 12 1751")
    tran0.writeAction("slorii X17 X17 12 3950")
    tran0.writeAction("slorii X17 X17 12 651")
    tran0.writeAction("slorii X17 X17 12 2111")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 30977")
    tran0.writeAction("slorii X17 X17 12 3060")
    tran0.writeAction("slorii X17 X17 12 3483")
    tran0.writeAction("slorii X17 X17 12 3307")
    tran0.writeAction("slorii X17 X17 12 3010")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 50137")
    tran0.writeAction("slorii X17 X17 12 1580")
    tran0.writeAction("slorii X17 X17 12 2717")
    tran0.writeAction("slorii X17 X17 12 73")
    tran0.writeAction("slorii X17 X17 12 645")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 22660")
    tran0.writeAction("slorii X17 X17 12 74")
    tran0.writeAction("slorii X17 X17 12 64")
    tran0.writeAction("slorii X17 X17 12 3614")
    tran0.writeAction("slorii X17 X17 12 1875")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 51902")
    tran0.writeAction("slorii X17 X17 12 3103")
    tran0.writeAction("slorii X17 X17 12 811")
    tran0.writeAction("slorii X17 X17 12 3136")
    tran0.writeAction("slorii X17 X17 12 3659")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 9555")
    tran0.writeAction("slorii X17 X17 12 2316")
    tran0.writeAction("slorii X17 X17 12 2727")
    tran0.writeAction("slorii X17 X17 12 1603")
    tran0.writeAction("slorii X17 X17 12 803")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 52574")
    tran0.writeAction("slorii X17 X17 12 1082")
    tran0.writeAction("slorii X17 X17 12 2301")
    tran0.writeAction("slorii X17 X17 12 3278")
    tran0.writeAction("slorii X17 X17 12 890")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 33612")
    tran0.writeAction("slorii X17 X17 12 3082")
    tran0.writeAction("slorii X17 X17 12 3937")
    tran0.writeAction("slorii X17 X17 12 3339")
    tran0.writeAction("slorii X17 X17 12 2810")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 52881")
    tran0.writeAction("slorii X17 X17 12 2927")
    tran0.writeAction("slorii X17 X17 12 3147")
    tran0.writeAction("slorii X17 X17 12 1620")
    tran0.writeAction("slorii X17 X17 12 2716")
    tran0.writeAction("hashl X16 X17 8")
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movrl X17 0(X16) 0 8")
    tran0.writeAction("yieldt")
    return efa