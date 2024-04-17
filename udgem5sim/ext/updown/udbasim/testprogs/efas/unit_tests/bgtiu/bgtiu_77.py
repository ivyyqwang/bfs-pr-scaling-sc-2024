from EFA_v2 import *
def bgtiu_77():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
    tran0.writeAction('movir X16 21')
    tran0.writeAction('movir X19 0')
    tran0.writeAction('movir X20 0')
    tran0.writeAction('bgtiu X16 13 expect_true')
    tran0.writeAction('jmp false_test')
    tran0.writeAction('expect_true: movir X19 1')
    tran0.writeAction('false_test: bgtiu X16 30 save')
    tran0.writeAction('movir X20 1')
    tran0.writeAction('save: addi X7 X21 0')
    tran0.writeAction('movrl X19 0(X21) 0 8')
    tran0.writeAction('movrl X20 8(X21) 0 8')
    tran0.writeAction('print: print \'%d,%d\' X19 X20')
    tran0.writeAction("yieldt")
    return efa
