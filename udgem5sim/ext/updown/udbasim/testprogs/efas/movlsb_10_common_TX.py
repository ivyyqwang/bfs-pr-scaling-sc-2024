from EFA_v2 import *
def movlsb_10_common_TX():
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
    tran0.writeAction("movir X16 38774")
    tran0.writeAction("slorii X16 X16 12 861")
    tran0.writeAction("slorii X16 X16 12 3282")
    tran0.writeAction("slorii X16 X16 12 786")
    tran0.writeAction("slorii X16 X16 12 1224")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 25283")
    tran0.writeAction("slorii X16 X16 12 3892")
    tran0.writeAction("slorii X16 X16 12 3441")
    tran0.writeAction("slorii X16 X16 12 3813")
    tran0.writeAction("slorii X16 X16 12 1457")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 9833")
    tran0.writeAction("slorii X16 X16 12 2568")
    tran0.writeAction("slorii X16 X16 12 1409")
    tran0.writeAction("slorii X16 X16 12 2717")
    tran0.writeAction("slorii X16 X16 12 57")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 44122")
    tran0.writeAction("slorii X16 X16 12 1225")
    tran0.writeAction("slorii X16 X16 12 3812")
    tran0.writeAction("slorii X16 X16 12 799")
    tran0.writeAction("slorii X16 X16 12 1199")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 22086")
    tran0.writeAction("slorii X16 X16 12 2801")
    tran0.writeAction("slorii X16 X16 12 2821")
    tran0.writeAction("slorii X16 X16 12 2586")
    tran0.writeAction("slorii X16 X16 12 2542")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 11344")
    tran0.writeAction("slorii X16 X16 12 166")
    tran0.writeAction("slorii X16 X16 12 3360")
    tran0.writeAction("slorii X16 X16 12 3764")
    tran0.writeAction("slorii X16 X16 12 2244")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 31318")
    tran0.writeAction("slorii X16 X16 12 1531")
    tran0.writeAction("slorii X16 X16 12 1621")
    tran0.writeAction("slorii X16 X16 12 3715")
    tran0.writeAction("slorii X16 X16 12 3958")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 290")
    tran0.writeAction("slorii X16 X16 12 172")
    tran0.writeAction("slorii X16 X16 12 1834")
    tran0.writeAction("slorii X16 X16 12 2690")
    tran0.writeAction("slorii X16 X16 12 3280")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 6120")
    tran0.writeAction("slorii X16 X16 12 3769")
    tran0.writeAction("slorii X16 X16 12 1121")
    tran0.writeAction("slorii X16 X16 12 1594")
    tran0.writeAction("slorii X16 X16 12 2276")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 9873")
    tran0.writeAction("slorii X16 X16 12 682")
    tran0.writeAction("slorii X16 X16 12 542")
    tran0.writeAction("slorii X16 X16 12 523")
    tran0.writeAction("slorii X16 X16 12 994")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 14954")
    tran0.writeAction("slorii X16 X16 12 3072")
    tran0.writeAction("slorii X16 X16 12 3371")
    tran0.writeAction("slorii X16 X16 12 3565")
    tran0.writeAction("slorii X16 X16 12 640")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 13560")
    tran0.writeAction("slorii X16 X16 12 2859")
    tran0.writeAction("slorii X16 X16 12 3542")
    tran0.writeAction("slorii X16 X16 12 3116")
    tran0.writeAction("slorii X16 X16 12 903")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 59056")
    tran0.writeAction("slorii X16 X16 12 3203")
    tran0.writeAction("slorii X16 X16 12 3742")
    tran0.writeAction("slorii X16 X16 12 1268")
    tran0.writeAction("slorii X16 X16 12 2046")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 46515")
    tran0.writeAction("slorii X16 X16 12 731")
    tran0.writeAction("slorii X16 X16 12 3719")
    tran0.writeAction("slorii X16 X16 12 3911")
    tran0.writeAction("slorii X16 X16 12 1271")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 19774")
    tran0.writeAction("slorii X16 X16 12 2180")
    tran0.writeAction("slorii X16 X16 12 1125")
    tran0.writeAction("slorii X16 X16 12 1623")
    tran0.writeAction("slorii X16 X16 12 1803")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 57912")
    tran0.writeAction("slorii X16 X16 12 683")
    tran0.writeAction("slorii X16 X16 12 3259")
    tran0.writeAction("slorii X16 X16 12 2271")
    tran0.writeAction("slorii X16 X16 12 1414")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 38774")
    tran0.writeAction("slorii X16 X16 12 861")
    tran0.writeAction("slorii X16 X16 12 3282")
    tran0.writeAction("slorii X16 X16 12 786")
    tran0.writeAction("slorii X16 X16 12 1224")
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
    tran0.writeAction("addi X7 X20 31")
    tran0.writeAction("movir X21 0")
    tran0.writeAction("sli X20 X20 3")
    tran0.writeAction("addi X21 X17 760")
    tran0.writeAction("add X20 X21 X5")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("lastact")
    tran1 = state0.writeTransition("commonCarry_with_action", state0, state0, 0)
    tran1.writeAction("addi X7 X17 31")
    tran1.writeAction("addi X17 X16 0")
    tran1.writeAction("movlsb X17")
    tran1.writeAction("addi X7 X18 128 ")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("movsbr X20")
    tran1.writeAction("movir X21 8")
    tran1.writeAction("add X5 X21 X5")
    tran1.writeAction("movrl X20 0(X18) 1 1")
    tran1.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","sub X31 X10 X31")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state0)
    return efa