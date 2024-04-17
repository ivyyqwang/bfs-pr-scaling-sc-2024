from linker.EFAProgram import efaProgram

@efaProgram
def GenerateBogus(efa):
    # state0 = efa.State()
    state1 = efa.State("Test")
    efa.add_initId(state1.state_id)
    efa.add_state(state1)
    
    tran0 = state1.writeTransition("eventCarry", state1, state1, 'example')
    tran0.writeAction("print 'Hello World!'")
    tran0.writeAction("yield_terminate")
    efa.appendBlockAction('block_100', "print 'BA: Hello World!'")
    efa.appendBlockAction('block_100', "yield")
    