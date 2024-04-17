from EFA_v2 import *
def movsbr_10_common_TX():
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
    tran0.writeAction("movir X16 57203")
    tran0.writeAction("slorii X16 X16 12 371")
    tran0.writeAction("slorii X16 X16 12 3872")
    tran0.writeAction("slorii X16 X16 12 75")
    tran0.writeAction("slorii X16 X16 12 4029")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 28888")
    tran0.writeAction("slorii X16 X16 12 2941")
    tran0.writeAction("slorii X16 X16 12 2156")
    tran0.writeAction("slorii X16 X16 12 846")
    tran0.writeAction("slorii X16 X16 12 2204")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 49915")
    tran0.writeAction("slorii X16 X16 12 2307")
    tran0.writeAction("slorii X16 X16 12 3646")
    tran0.writeAction("slorii X16 X16 12 958")
    tran0.writeAction("slorii X16 X16 12 3261")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 62102")
    tran0.writeAction("slorii X16 X16 12 232")
    tran0.writeAction("slorii X16 X16 12 1757")
    tran0.writeAction("slorii X16 X16 12 528")
    tran0.writeAction("slorii X16 X16 12 1560")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 15953")
    tran0.writeAction("slorii X16 X16 12 2960")
    tran0.writeAction("slorii X16 X16 12 1803")
    tran0.writeAction("slorii X16 X16 12 3546")
    tran0.writeAction("slorii X16 X16 12 2150")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 5752")
    tran0.writeAction("slorii X16 X16 12 4078")
    tran0.writeAction("slorii X16 X16 12 3741")
    tran0.writeAction("slorii X16 X16 12 619")
    tran0.writeAction("slorii X16 X16 12 72")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 48288")
    tran0.writeAction("slorii X16 X16 12 3073")
    tran0.writeAction("slorii X16 X16 12 2531")
    tran0.writeAction("slorii X16 X16 12 1730")
    tran0.writeAction("slorii X16 X16 12 3532")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 62260")
    tran0.writeAction("slorii X16 X16 12 1100")
    tran0.writeAction("slorii X16 X16 12 1042")
    tran0.writeAction("slorii X16 X16 12 2433")
    tran0.writeAction("slorii X16 X16 12 242")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 10589")
    tran0.writeAction("slorii X16 X16 12 402")
    tran0.writeAction("slorii X16 X16 12 3942")
    tran0.writeAction("slorii X16 X16 12 3394")
    tran0.writeAction("slorii X16 X16 12 1479")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 30123")
    tran0.writeAction("slorii X16 X16 12 964")
    tran0.writeAction("slorii X16 X16 12 3209")
    tran0.writeAction("slorii X16 X16 12 3211")
    tran0.writeAction("slorii X16 X16 12 1773")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 39854")
    tran0.writeAction("slorii X16 X16 12 619")
    tran0.writeAction("slorii X16 X16 12 2461")
    tran0.writeAction("slorii X16 X16 12 1535")
    tran0.writeAction("slorii X16 X16 12 3474")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 61854")
    tran0.writeAction("slorii X16 X16 12 3355")
    tran0.writeAction("slorii X16 X16 12 2118")
    tran0.writeAction("slorii X16 X16 12 3849")
    tran0.writeAction("slorii X16 X16 12 623")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 33753")
    tran0.writeAction("slorii X16 X16 12 351")
    tran0.writeAction("slorii X16 X16 12 3051")
    tran0.writeAction("slorii X16 X16 12 3882")
    tran0.writeAction("slorii X16 X16 12 3822")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 55521")
    tran0.writeAction("slorii X16 X16 12 3566")
    tran0.writeAction("slorii X16 X16 12 3240")
    tran0.writeAction("slorii X16 X16 12 2365")
    tran0.writeAction("slorii X16 X16 12 2502")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 19602")
    tran0.writeAction("slorii X16 X16 12 3338")
    tran0.writeAction("slorii X16 X16 12 2561")
    tran0.writeAction("slorii X16 X16 12 3545")
    tran0.writeAction("slorii X16 X16 12 2870")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 2405")
    tran0.writeAction("slorii X16 X16 12 840")
    tran0.writeAction("slorii X16 X16 12 1554")
    tran0.writeAction("slorii X16 X16 12 742")
    tran0.writeAction("slorii X16 X16 12 756")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 57203")
    tran0.writeAction("slorii X16 X16 12 371")
    tran0.writeAction("slorii X16 X16 12 3872")
    tran0.writeAction("slorii X16 X16 12 75")
    tran0.writeAction("slorii X16 X16 12 4029")
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
    tran0.writeAction("addi X7 X20 0")
    tran0.writeAction("movir X21 0")
    tran0.writeAction("sli X20 X20 3")
    tran0.writeAction("addi X21 X17 512")
    tran0.writeAction("add X20 X21 X5")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("lastact")
    tran1 = state0.writeTransition("commonCarry_with_action", state0, state0, 0)
    tran1.writeAction("addi X7 X17 0")
    tran1.writeAction("movlsb X17")
    tran1.writeAction("addi X7 X20 360")
    tran1.writeAction("movir X21 0")
    tran1.writeAction("add X20 X21 X5")
    tran1.writeAction("movsbr X16")
    tran1.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","sub X31 X10 X31")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state0)
    return efa
