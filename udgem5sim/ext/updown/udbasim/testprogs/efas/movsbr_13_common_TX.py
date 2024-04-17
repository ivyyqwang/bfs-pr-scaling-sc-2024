from EFA_v2 import *
def movsbr_13_common_TX():
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
    tran0.writeAction("movir X16 41204")
    tran0.writeAction("slorii X16 X16 12 3513")
    tran0.writeAction("slorii X16 X16 12 2708")
    tran0.writeAction("slorii X16 X16 12 597")
    tran0.writeAction("slorii X16 X16 12 992")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 9799")
    tran0.writeAction("slorii X16 X16 12 730")
    tran0.writeAction("slorii X16 X16 12 1993")
    tran0.writeAction("slorii X16 X16 12 3762")
    tran0.writeAction("slorii X16 X16 12 2533")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 44128")
    tran0.writeAction("slorii X16 X16 12 3765")
    tran0.writeAction("slorii X16 X16 12 1898")
    tran0.writeAction("slorii X16 X16 12 3671")
    tran0.writeAction("slorii X16 X16 12 853")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 41128")
    tran0.writeAction("slorii X16 X16 12 2987")
    tran0.writeAction("slorii X16 X16 12 1097")
    tran0.writeAction("slorii X16 X16 12 460")
    tran0.writeAction("slorii X16 X16 12 3633")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 502")
    tran0.writeAction("slorii X16 X16 12 1545")
    tran0.writeAction("slorii X16 X16 12 2905")
    tran0.writeAction("slorii X16 X16 12 4025")
    tran0.writeAction("slorii X16 X16 12 1730")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 59058")
    tran0.writeAction("slorii X16 X16 12 1781")
    tran0.writeAction("slorii X16 X16 12 3294")
    tran0.writeAction("slorii X16 X16 12 3232")
    tran0.writeAction("slorii X16 X16 12 2651")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 62130")
    tran0.writeAction("slorii X16 X16 12 2234")
    tran0.writeAction("slorii X16 X16 12 3235")
    tran0.writeAction("slorii X16 X16 12 3172")
    tran0.writeAction("slorii X16 X16 12 1451")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 54352")
    tran0.writeAction("slorii X16 X16 12 3363")
    tran0.writeAction("slorii X16 X16 12 3617")
    tran0.writeAction("slorii X16 X16 12 3383")
    tran0.writeAction("slorii X16 X16 12 662")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 37711")
    tran0.writeAction("slorii X16 X16 12 986")
    tran0.writeAction("slorii X16 X16 12 517")
    tran0.writeAction("slorii X16 X16 12 1830")
    tran0.writeAction("slorii X16 X16 12 2731")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 55783")
    tran0.writeAction("slorii X16 X16 12 3126")
    tran0.writeAction("slorii X16 X16 12 3344")
    tran0.writeAction("slorii X16 X16 12 2184")
    tran0.writeAction("slorii X16 X16 12 1713")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 47591")
    tran0.writeAction("slorii X16 X16 12 2453")
    tran0.writeAction("slorii X16 X16 12 2435")
    tran0.writeAction("slorii X16 X16 12 1457")
    tran0.writeAction("slorii X16 X16 12 3142")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 63780")
    tran0.writeAction("slorii X16 X16 12 438")
    tran0.writeAction("slorii X16 X16 12 4")
    tran0.writeAction("slorii X16 X16 12 937")
    tran0.writeAction("slorii X16 X16 12 3738")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 41724")
    tran0.writeAction("slorii X16 X16 12 958")
    tran0.writeAction("slorii X16 X16 12 284")
    tran0.writeAction("slorii X16 X16 12 3439")
    tran0.writeAction("slorii X16 X16 12 256")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 57262")
    tran0.writeAction("slorii X16 X16 12 1570")
    tran0.writeAction("slorii X16 X16 12 2547")
    tran0.writeAction("slorii X16 X16 12 241")
    tran0.writeAction("slorii X16 X16 12 4028")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 39711")
    tran0.writeAction("slorii X16 X16 12 2165")
    tran0.writeAction("slorii X16 X16 12 4064")
    tran0.writeAction("slorii X16 X16 12 1557")
    tran0.writeAction("slorii X16 X16 12 1769")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 13906")
    tran0.writeAction("slorii X16 X16 12 2086")
    tran0.writeAction("slorii X16 X16 12 3041")
    tran0.writeAction("slorii X16 X16 12 2078")
    tran0.writeAction("slorii X16 X16 12 2185")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 41204")
    tran0.writeAction("slorii X16 X16 12 3513")
    tran0.writeAction("slorii X16 X16 12 2708")
    tran0.writeAction("slorii X16 X16 12 597")
    tran0.writeAction("slorii X16 X16 12 992")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 7")
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
    tran1.writeAction("addi X7 X20 293")
    tran1.writeAction("movir X21 0")
    tran1.writeAction("add X20 X21 X5")
    tran1.writeAction("movsbr X16")
    tran1.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","sub X31 X10 X31")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state0)
    return efa
