
from EFA_v2 import EFA, State, Transition

def sht_empty_test_out():

    ## init_null_state with ID 0
    efa = EFA([])
    efa.code_level = 'machine'

    init_null_state_0 = State()
    efa.add_state(init_null_state_0)
    efa.add_initId(init_null_state_0.state_id)

    ## entry_init with ID 0
    entry_init_0 = init_null_state_0.writeTransition("eventCarry", init_null_state_0, init_null_state_0, 0)
    entry_init_0.writeAction(f"movir X17 1")
    entry_init_0.writeAction(f"addi X8 X18 0")
    entry_init_0.writeAction(f"movrl X17 0(X18) 0 8")  # write 1 as termination flag
    entry_init_0.writeAction(f"yieldt")

    return efa