from EFA_v2 import *
def bneu_27():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
    tran0.writeAction('movir X16 2089454')
    tran0.writeAction('movir X17 136556')
    tran0.writeAction('movir X18 2089454')
    tran0.writeAction('movir X19 0')
    tran0.writeAction('movir X20 0')
    tran0.writeAction('bneu X16 X17 expect_true')
    tran0.writeAction('jmp false_test')
    tran0.writeAction('expect_true: movir X19 1')
    tran0.writeAction('false_test: bneu X16 X18 save')
    tran0.writeAction('movir X20 1')
    tran0.writeAction('save: addi X7 X21 0')
    tran0.writeAction('movrl X19 0(X21) 0 8')
    tran0.writeAction('movrl X20 8(X21) 0 8')
    tran0.writeAction('print: print \'%d,%d\' X19 X20')
    tran0.writeAction("yieldt")
    return efa
