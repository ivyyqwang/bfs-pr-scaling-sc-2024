from EFA_v2 import *
def movsbr_cycle_13_common_TX():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    state0 = State()
    state0.alphabet = [0-255]
    efa.add_state(state0)
    tran0 = state.writeTransition("commonCarry_with_action", state, state0, 1)
    tran0.writeAction("movir X17 0")
    tran0.writeAction("add X7 X17 X17")
    tran0.writeAction("movir X16 33229")
    tran0.writeAction("slorii X16 X16 12 126")
    tran0.writeAction("slorii X16 X16 12 456")
    tran0.writeAction("slorii X16 X16 12 1523")
    tran0.writeAction("slorii X16 X16 12 3496")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 14161")
    tran0.writeAction("slorii X16 X16 12 2982")
    tran0.writeAction("slorii X16 X16 12 1196")
    tran0.writeAction("slorii X16 X16 12 1373")
    tran0.writeAction("slorii X16 X16 12 3976")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 17161")
    tran0.writeAction("slorii X16 X16 12 556")
    tran0.writeAction("slorii X16 X16 12 1910")
    tran0.writeAction("slorii X16 X16 12 1304")
    tran0.writeAction("slorii X16 X16 12 345")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 54573")
    tran0.writeAction("slorii X16 X16 12 3617")
    tran0.writeAction("slorii X16 X16 12 3162")
    tran0.writeAction("slorii X16 X16 12 3950")
    tran0.writeAction("slorii X16 X16 12 3904")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 60098")
    tran0.writeAction("slorii X16 X16 12 3613")
    tran0.writeAction("slorii X16 X16 12 665")
    tran0.writeAction("slorii X16 X16 12 356")
    tran0.writeAction("slorii X16 X16 12 1858")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 24741")
    tran0.writeAction("slorii X16 X16 12 3667")
    tran0.writeAction("slorii X16 X16 12 1913")
    tran0.writeAction("slorii X16 X16 12 1604")
    tran0.writeAction("slorii X16 X16 12 2827")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 37075")
    tran0.writeAction("slorii X16 X16 12 3585")
    tran0.writeAction("slorii X16 X16 12 1515")
    tran0.writeAction("slorii X16 X16 12 2146")
    tran0.writeAction("slorii X16 X16 12 2950")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 51013")
    tran0.writeAction("slorii X16 X16 12 715")
    tran0.writeAction("slorii X16 X16 12 360")
    tran0.writeAction("slorii X16 X16 12 2735")
    tran0.writeAction("slorii X16 X16 12 558")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 64856")
    tran0.writeAction("slorii X16 X16 12 3349")
    tran0.writeAction("slorii X16 X16 12 1993")
    tran0.writeAction("slorii X16 X16 12 3721")
    tran0.writeAction("slorii X16 X16 12 2920")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 61242")
    tran0.writeAction("slorii X16 X16 12 3326")
    tran0.writeAction("slorii X16 X16 12 96")
    tran0.writeAction("slorii X16 X16 12 3178")
    tran0.writeAction("slorii X16 X16 12 3497")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 13227")
    tran0.writeAction("slorii X16 X16 12 3237")
    tran0.writeAction("slorii X16 X16 12 54")
    tran0.writeAction("slorii X16 X16 12 3293")
    tran0.writeAction("slorii X16 X16 12 3814")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 48416")
    tran0.writeAction("slorii X16 X16 12 813")
    tran0.writeAction("slorii X16 X16 12 1268")
    tran0.writeAction("slorii X16 X16 12 953")
    tran0.writeAction("slorii X16 X16 12 3451")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 14324")
    tran0.writeAction("slorii X16 X16 12 1150")
    tran0.writeAction("slorii X16 X16 12 3085")
    tran0.writeAction("slorii X16 X16 12 2373")
    tran0.writeAction("slorii X16 X16 12 2956")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 39951")
    tran0.writeAction("slorii X16 X16 12 439")
    tran0.writeAction("slorii X16 X16 12 3302")
    tran0.writeAction("slorii X16 X16 12 3695")
    tran0.writeAction("slorii X16 X16 12 2651")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 9743")
    tran0.writeAction("slorii X16 X16 12 978")
    tran0.writeAction("slorii X16 X16 12 3652")
    tran0.writeAction("slorii X16 X16 12 264")
    tran0.writeAction("slorii X16 X16 12 2183")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 18286")
    tran0.writeAction("slorii X16 X16 12 1445")
    tran0.writeAction("slorii X16 X16 12 480")
    tran0.writeAction("slorii X16 X16 12 3784")
    tran0.writeAction("slorii X16 X16 12 1217")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 33229")
    tran0.writeAction("slorii X16 X16 12 126")
    tran0.writeAction("slorii X16 X16 12 456")
    tran0.writeAction("slorii X16 X16 12 1523")
    tran0.writeAction("slorii X16 X16 12 3496")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 6")
    tran0.writeAction("sli X17 X17 36")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 8")
    tran0.writeAction("sli X17 X17 32")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("addi X7 X20 63")
    tran0.writeAction("movir X21 0")
    tran0.writeAction("sli X20 X20 3")
    tran0.writeAction("addi X21 X17 1016")
    tran0.writeAction("add X20 X21 X5")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("lastact")
    tran1 = state0.writeTransition("commonCarry_with_action", state0, state0, 0)
    tran1.writeAction("addi X7 X17 63")
    tran1.writeAction("movlsb X17")
    tran1.writeAction("addi X7 X20 511")
    tran1.writeAction("movir X21 0")
    tran1.writeAction("add X20 X21 X5")
    tran1.writeAction("movsbr X16")
    tran1.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","sub X31 X10 X31")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state0)
    return efa