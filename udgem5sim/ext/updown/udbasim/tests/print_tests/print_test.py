
from EFA_v2 import EFA, State, Transition

def print_test():

    ## init_null_state with ID 0
    efa = EFA([])
    efa.code_level = 'machine'

    init_null_state_0 = State()
    efa.add_state(init_null_state_0)
    efa.add_initId(init_null_state_0.state_id)

    ## entry_init with ID 0
    entry_init_0 = init_null_state_0.writeTransition("eventCarry", init_null_state_0, init_null_state_0, 0)
    entry_init_0.writeAction(f"addi X9 X20 0")
    entry_init_0.writeAction(f"subi X20 X20 1")
    entry_init_0.writeAction(f"print ''")
    entry_init_0.writeAction(f"print 'H'")
    entry_init_0.writeAction(f"print 'He'")
    entry_init_0.writeAction(f"print 'Hel'")
    entry_init_0.writeAction(f"print 'Hell'")
    entry_init_0.writeAction(f"print 'Hello'")
    entry_init_0.writeAction(f"print 'Hello %d %u % %%u %b %x %X' {'X20'} {'X20'} {'X20'} {'X20'} {'X20'} {'X20'}")
    entry_init_0.writeAction(f"addi X8 X18 0")
    entry_init_0.writeAction(f"addi X8 X18 0")
    entry_init_0.writeAction(f"print 'Hello World1'")
    entry_init_0.writeAction(f"movir X17 1")
    entry_init_0.writeAction(f"addi X7 X18 0")
    entry_init_0.writeAction(f"movrl X17 0(X18) 0 8")  # write 1 as termination flag
    entry_init_0.writeAction(f"yieldt")
    entry_init_0.writeAction(f"yieldt")

    entry_init_1 = init_null_state_0.writeTransition("eventCarry", init_null_state_0, init_null_state_0, 1)
    entry_init_1.writeAction(f"print '%d: Hello World2' {'X8'}")
    entry_init_1.writeAction(f"movir X17 1")
    entry_init_1.writeAction(f"addi X7 X18 0")
    entry_init_1.writeAction(f"movrl X17 0(X18) 0 8")  # write 1 as termination flag
    entry_init_1.writeAction(f"yieldt")
    entry_init_1.writeAction(f"yieldt")

    return efa