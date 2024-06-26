from EFA_v2 import *
def movsbr_cycle_1_common_TX():
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
    tran0.writeAction("movir X16 25966")
    tran0.writeAction("slorii X16 X16 12 3907")
    tran0.writeAction("slorii X16 X16 12 4081")
    tran0.writeAction("slorii X16 X16 12 2082")
    tran0.writeAction("slorii X16 X16 12 2909")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 63399")
    tran0.writeAction("slorii X16 X16 12 344")
    tran0.writeAction("slorii X16 X16 12 2507")
    tran0.writeAction("slorii X16 X16 12 3657")
    tran0.writeAction("slorii X16 X16 12 3695")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 31164")
    tran0.writeAction("slorii X16 X16 12 745")
    tran0.writeAction("slorii X16 X16 12 4083")
    tran0.writeAction("slorii X16 X16 12 764")
    tran0.writeAction("slorii X16 X16 12 1503")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 42117")
    tran0.writeAction("slorii X16 X16 12 1339")
    tran0.writeAction("slorii X16 X16 12 1523")
    tran0.writeAction("slorii X16 X16 12 1933")
    tran0.writeAction("slorii X16 X16 12 2286")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 55805")
    tran0.writeAction("slorii X16 X16 12 2417")
    tran0.writeAction("slorii X16 X16 12 1508")
    tran0.writeAction("slorii X16 X16 12 2395")
    tran0.writeAction("slorii X16 X16 12 1721")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 42927")
    tran0.writeAction("slorii X16 X16 12 2157")
    tran0.writeAction("slorii X16 X16 12 1876")
    tran0.writeAction("slorii X16 X16 12 2441")
    tran0.writeAction("slorii X16 X16 12 1250")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 10103")
    tran0.writeAction("slorii X16 X16 12 1313")
    tran0.writeAction("slorii X16 X16 12 1128")
    tran0.writeAction("slorii X16 X16 12 239")
    tran0.writeAction("slorii X16 X16 12 2271")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 58764")
    tran0.writeAction("slorii X16 X16 12 3123")
    tran0.writeAction("slorii X16 X16 12 808")
    tran0.writeAction("slorii X16 X16 12 2707")
    tran0.writeAction("slorii X16 X16 12 710")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 18383")
    tran0.writeAction("slorii X16 X16 12 2234")
    tran0.writeAction("slorii X16 X16 12 1843")
    tran0.writeAction("slorii X16 X16 12 2381")
    tran0.writeAction("slorii X16 X16 12 3807")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 34476")
    tran0.writeAction("slorii X16 X16 12 1467")
    tran0.writeAction("slorii X16 X16 12 972")
    tran0.writeAction("slorii X16 X16 12 3150")
    tran0.writeAction("slorii X16 X16 12 2068")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 55750")
    tran0.writeAction("slorii X16 X16 12 4092")
    tran0.writeAction("slorii X16 X16 12 3847")
    tran0.writeAction("slorii X16 X16 12 2523")
    tran0.writeAction("slorii X16 X16 12 2956")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 37384")
    tran0.writeAction("slorii X16 X16 12 1410")
    tran0.writeAction("slorii X16 X16 12 3761")
    tran0.writeAction("slorii X16 X16 12 1311")
    tran0.writeAction("slorii X16 X16 12 3254")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 25611")
    tran0.writeAction("slorii X16 X16 12 3354")
    tran0.writeAction("slorii X16 X16 12 1757")
    tran0.writeAction("slorii X16 X16 12 2651")
    tran0.writeAction("slorii X16 X16 12 1650")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 6416")
    tran0.writeAction("slorii X16 X16 12 2150")
    tran0.writeAction("slorii X16 X16 12 3414")
    tran0.writeAction("slorii X16 X16 12 3847")
    tran0.writeAction("slorii X16 X16 12 585")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 48423")
    tran0.writeAction("slorii X16 X16 12 701")
    tran0.writeAction("slorii X16 X16 12 3650")
    tran0.writeAction("slorii X16 X16 12 3676")
    tran0.writeAction("slorii X16 X16 12 2323")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 43819")
    tran0.writeAction("slorii X16 X16 12 772")
    tran0.writeAction("slorii X16 X16 12 840")
    tran0.writeAction("slorii X16 X16 12 2786")
    tran0.writeAction("slorii X16 X16 12 3625")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 25966")
    tran0.writeAction("slorii X16 X16 12 3907")
    tran0.writeAction("slorii X16 X16 12 4081")
    tran0.writeAction("slorii X16 X16 12 2082")
    tran0.writeAction("slorii X16 X16 12 2909")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 2")
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
