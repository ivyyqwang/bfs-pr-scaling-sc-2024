from EFA_v2 import *
def srsubii_26():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [2250880987894543192, 0, 1323]
    tran0.writeAction("movir X16 7996")
    tran0.writeAction("slorii X16 X16 12 3013")
    tran0.writeAction("slorii X16 X16 12 1331")
    tran0.writeAction("slorii X16 X16 12 551")
    tran0.writeAction("slorii X16 X16 12 856")
    tran0.writeAction("srsubii X16 X17 0 1323")
    tran0.writeAction("yieldt")
    return efa
