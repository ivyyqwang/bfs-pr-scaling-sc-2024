from EFA_v2 import *
def hashl64_93():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [4715672177514116222, 6083232060279845282, -4038784320063731547, 8565056098435523385, -2404908383764180527, -6055631846745898486, -7025562753814969306, 4978978866537282635, 31, 8723266627451326553]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 16753")
    tran0.writeAction("slorii X17 X17 12 1773")
    tran0.writeAction("slorii X17 X17 12 3161")
    tran0.writeAction("slorii X17 X17 12 3775")
    tran0.writeAction("slorii X17 X17 12 1150")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 21611")
    tran0.writeAction("slorii X17 X17 12 4021")
    tran0.writeAction("slorii X17 X17 12 1047")
    tran0.writeAction("slorii X17 X17 12 1015")
    tran0.writeAction("slorii X17 X17 12 418")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 51187")
    tran0.writeAction("slorii X17 X17 12 1456")
    tran0.writeAction("slorii X17 X17 12 3886")
    tran0.writeAction("slorii X17 X17 12 752")
    tran0.writeAction("slorii X17 X17 12 2213")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 30429")
    tran0.writeAction("slorii X17 X17 12 786")
    tran0.writeAction("slorii X17 X17 12 1108")
    tran0.writeAction("slorii X17 X17 12 2222")
    tran0.writeAction("slorii X17 X17 12 825")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 56992")
    tran0.writeAction("slorii X17 X17 12 201")
    tran0.writeAction("slorii X17 X17 12 276")
    tran0.writeAction("slorii X17 X17 12 1545")
    tran0.writeAction("slorii X17 X17 12 465")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 44022")
    tran0.writeAction("slorii X17 X17 12 302")
    tran0.writeAction("slorii X17 X17 12 2916")
    tran0.writeAction("slorii X17 X17 12 688")
    tran0.writeAction("slorii X17 X17 12 522")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 40576")
    tran0.writeAction("slorii X17 X17 12 766")
    tran0.writeAction("slorii X17 X17 12 1535")
    tran0.writeAction("slorii X17 X17 12 2636")
    tran0.writeAction("slorii X17 X17 12 1062")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 17688")
    tran0.writeAction("slorii X17 X17 12 3630")
    tran0.writeAction("slorii X17 X17 12 1596")
    tran0.writeAction("slorii X17 X17 12 539")
    tran0.writeAction("slorii X17 X17 12 3147")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X18 31")
    tran0.writeAction("add X7 X18 X5")
    tran0.writeAction("movir X16 30991")
    tran0.writeAction("slorii X16 X16 12 1100")
    tran0.writeAction("slorii X16 X16 12 1954")
    tran0.writeAction("slorii X16 X16 12 1049")
    tran0.writeAction("slorii X16 X16 12 89")
    tran0.writeAction("hashl64 X16 X17")
    tran0.writeAction("yieldt")
    return efa