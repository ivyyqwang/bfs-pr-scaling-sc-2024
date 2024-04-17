from EFA_v2 import *
def movsbr_cycle_7_common_TX():
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
    tran0.writeAction("movir X16 7986")
    tran0.writeAction("slorii X16 X16 12 2843")
    tran0.writeAction("slorii X16 X16 12 2632")
    tran0.writeAction("slorii X16 X16 12 2442")
    tran0.writeAction("slorii X16 X16 12 302")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 36878")
    tran0.writeAction("slorii X16 X16 12 3947")
    tran0.writeAction("slorii X16 X16 12 1616")
    tran0.writeAction("slorii X16 X16 12 1224")
    tran0.writeAction("slorii X16 X16 12 2040")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 16447")
    tran0.writeAction("slorii X16 X16 12 2998")
    tran0.writeAction("slorii X16 X16 12 3634")
    tran0.writeAction("slorii X16 X16 12 3401")
    tran0.writeAction("slorii X16 X16 12 384")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 62440")
    tran0.writeAction("slorii X16 X16 12 2880")
    tran0.writeAction("slorii X16 X16 12 737")
    tran0.writeAction("slorii X16 X16 12 1934")
    tran0.writeAction("slorii X16 X16 12 1201")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 52115")
    tran0.writeAction("slorii X16 X16 12 3962")
    tran0.writeAction("slorii X16 X16 12 3153")
    tran0.writeAction("slorii X16 X16 12 870")
    tran0.writeAction("slorii X16 X16 12 3282")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 58385")
    tran0.writeAction("slorii X16 X16 12 2233")
    tran0.writeAction("slorii X16 X16 12 2469")
    tran0.writeAction("slorii X16 X16 12 937")
    tran0.writeAction("slorii X16 X16 12 702")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 59660")
    tran0.writeAction("slorii X16 X16 12 4093")
    tran0.writeAction("slorii X16 X16 12 1489")
    tran0.writeAction("slorii X16 X16 12 1231")
    tran0.writeAction("slorii X16 X16 12 1623")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 18385")
    tran0.writeAction("slorii X16 X16 12 1416")
    tran0.writeAction("slorii X16 X16 12 102")
    tran0.writeAction("slorii X16 X16 12 2043")
    tran0.writeAction("slorii X16 X16 12 1011")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 5484")
    tran0.writeAction("slorii X16 X16 12 1159")
    tran0.writeAction("slorii X16 X16 12 729")
    tran0.writeAction("slorii X16 X16 12 1236")
    tran0.writeAction("slorii X16 X16 12 164")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 32220")
    tran0.writeAction("slorii X16 X16 12 759")
    tran0.writeAction("slorii X16 X16 12 1507")
    tran0.writeAction("slorii X16 X16 12 1146")
    tran0.writeAction("slorii X16 X16 12 3624")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 60751")
    tran0.writeAction("slorii X16 X16 12 517")
    tran0.writeAction("slorii X16 X16 12 2654")
    tran0.writeAction("slorii X16 X16 12 1149")
    tran0.writeAction("slorii X16 X16 12 953")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 5122")
    tran0.writeAction("slorii X16 X16 12 2579")
    tran0.writeAction("slorii X16 X16 12 721")
    tran0.writeAction("slorii X16 X16 12 1515")
    tran0.writeAction("slorii X16 X16 12 3764")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 27763")
    tran0.writeAction("slorii X16 X16 12 2038")
    tran0.writeAction("slorii X16 X16 12 1059")
    tran0.writeAction("slorii X16 X16 12 2178")
    tran0.writeAction("slorii X16 X16 12 364")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 23302")
    tran0.writeAction("slorii X16 X16 12 1116")
    tran0.writeAction("slorii X16 X16 12 677")
    tran0.writeAction("slorii X16 X16 12 13")
    tran0.writeAction("slorii X16 X16 12 3955")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 35899")
    tran0.writeAction("slorii X16 X16 12 1640")
    tran0.writeAction("slorii X16 X16 12 1222")
    tran0.writeAction("slorii X16 X16 12 1573")
    tran0.writeAction("slorii X16 X16 12 2221")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 19904")
    tran0.writeAction("slorii X16 X16 12 852")
    tran0.writeAction("slorii X16 X16 12 3438")
    tran0.writeAction("slorii X16 X16 12 1043")
    tran0.writeAction("slorii X16 X16 12 2486")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 7986")
    tran0.writeAction("slorii X16 X16 12 2843")
    tran0.writeAction("slorii X16 X16 12 2632")
    tran0.writeAction("slorii X16 X16 12 2442")
    tran0.writeAction("slorii X16 X16 12 302")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 3")
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