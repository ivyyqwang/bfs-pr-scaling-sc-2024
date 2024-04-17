from EFA_v2 import *
def movsbr_8_common_TX():
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
    tran0.writeAction("movir X16 11292")
    tran0.writeAction("slorii X16 X16 12 1729")
    tran0.writeAction("slorii X16 X16 12 24")
    tran0.writeAction("slorii X16 X16 12 2760")
    tran0.writeAction("slorii X16 X16 12 3590")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 38052")
    tran0.writeAction("slorii X16 X16 12 1077")
    tran0.writeAction("slorii X16 X16 12 2249")
    tran0.writeAction("slorii X16 X16 12 1384")
    tran0.writeAction("slorii X16 X16 12 336")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 31980")
    tran0.writeAction("slorii X16 X16 12 3674")
    tran0.writeAction("slorii X16 X16 12 241")
    tran0.writeAction("slorii X16 X16 12 4024")
    tran0.writeAction("slorii X16 X16 12 3378")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 25933")
    tran0.writeAction("slorii X16 X16 12 2497")
    tran0.writeAction("slorii X16 X16 12 3871")
    tran0.writeAction("slorii X16 X16 12 2425")
    tran0.writeAction("slorii X16 X16 12 3851")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 47818")
    tran0.writeAction("slorii X16 X16 12 196")
    tran0.writeAction("slorii X16 X16 12 1649")
    tran0.writeAction("slorii X16 X16 12 1380")
    tran0.writeAction("slorii X16 X16 12 1457")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 21079")
    tran0.writeAction("slorii X16 X16 12 1392")
    tran0.writeAction("slorii X16 X16 12 1926")
    tran0.writeAction("slorii X16 X16 12 2909")
    tran0.writeAction("slorii X16 X16 12 3277")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 36184")
    tran0.writeAction("slorii X16 X16 12 3970")
    tran0.writeAction("slorii X16 X16 12 1318")
    tran0.writeAction("slorii X16 X16 12 399")
    tran0.writeAction("slorii X16 X16 12 3864")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 51641")
    tran0.writeAction("slorii X16 X16 12 1854")
    tran0.writeAction("slorii X16 X16 12 1876")
    tran0.writeAction("slorii X16 X16 12 18")
    tran0.writeAction("slorii X16 X16 12 2284")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 53299")
    tran0.writeAction("slorii X16 X16 12 1788")
    tran0.writeAction("slorii X16 X16 12 2159")
    tran0.writeAction("slorii X16 X16 12 917")
    tran0.writeAction("slorii X16 X16 12 2914")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 5210")
    tran0.writeAction("slorii X16 X16 12 3512")
    tran0.writeAction("slorii X16 X16 12 1695")
    tran0.writeAction("slorii X16 X16 12 822")
    tran0.writeAction("slorii X16 X16 12 1024")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 19338")
    tran0.writeAction("slorii X16 X16 12 2265")
    tran0.writeAction("slorii X16 X16 12 57")
    tran0.writeAction("slorii X16 X16 12 3234")
    tran0.writeAction("slorii X16 X16 12 3931")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 9527")
    tran0.writeAction("slorii X16 X16 12 140")
    tran0.writeAction("slorii X16 X16 12 2546")
    tran0.writeAction("slorii X16 X16 12 3224")
    tran0.writeAction("slorii X16 X16 12 1845")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 50760")
    tran0.writeAction("slorii X16 X16 12 1713")
    tran0.writeAction("slorii X16 X16 12 2248")
    tran0.writeAction("slorii X16 X16 12 4049")
    tran0.writeAction("slorii X16 X16 12 3403")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 41444")
    tran0.writeAction("slorii X16 X16 12 271")
    tran0.writeAction("slorii X16 X16 12 2850")
    tran0.writeAction("slorii X16 X16 12 1056")
    tran0.writeAction("slorii X16 X16 12 1215")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 10486")
    tran0.writeAction("slorii X16 X16 12 1437")
    tran0.writeAction("slorii X16 X16 12 2037")
    tran0.writeAction("slorii X16 X16 12 2911")
    tran0.writeAction("slorii X16 X16 12 2482")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 36718")
    tran0.writeAction("slorii X16 X16 12 3342")
    tran0.writeAction("slorii X16 X16 12 224")
    tran0.writeAction("slorii X16 X16 12 3077")
    tran0.writeAction("slorii X16 X16 12 989")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 11292")
    tran0.writeAction("slorii X16 X16 12 1729")
    tran0.writeAction("slorii X16 X16 12 24")
    tran0.writeAction("slorii X16 X16 12 2760")
    tran0.writeAction("slorii X16 X16 12 3590")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 8")
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
    tran1.writeAction("addi X7 X20 33")
    tran1.writeAction("movir X21 0")
    tran1.writeAction("add X20 X21 X5")
    tran1.writeAction("movsbr X16")
    tran1.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","sub X31 X10 X31")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state0)
    return efa