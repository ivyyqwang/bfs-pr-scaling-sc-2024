from EFA_v2 import *
def movsbr_17_common_TX():
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
    tran0.writeAction("movir X16 29332")
    tran0.writeAction("slorii X16 X16 12 1485")
    tran0.writeAction("slorii X16 X16 12 1287")
    tran0.writeAction("slorii X16 X16 12 1987")
    tran0.writeAction("slorii X16 X16 12 1099")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 61090")
    tran0.writeAction("slorii X16 X16 12 855")
    tran0.writeAction("slorii X16 X16 12 2089")
    tran0.writeAction("slorii X16 X16 12 2696")
    tran0.writeAction("slorii X16 X16 12 2035")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 63144")
    tran0.writeAction("slorii X16 X16 12 144")
    tran0.writeAction("slorii X16 X16 12 3256")
    tran0.writeAction("slorii X16 X16 12 1335")
    tran0.writeAction("slorii X16 X16 12 1035")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 38692")
    tran0.writeAction("slorii X16 X16 12 403")
    tran0.writeAction("slorii X16 X16 12 1996")
    tran0.writeAction("slorii X16 X16 12 2982")
    tran0.writeAction("slorii X16 X16 12 2476")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 57312")
    tran0.writeAction("slorii X16 X16 12 671")
    tran0.writeAction("slorii X16 X16 12 1150")
    tran0.writeAction("slorii X16 X16 12 3316")
    tran0.writeAction("slorii X16 X16 12 67")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 24302")
    tran0.writeAction("slorii X16 X16 12 2345")
    tran0.writeAction("slorii X16 X16 12 639")
    tran0.writeAction("slorii X16 X16 12 2881")
    tran0.writeAction("slorii X16 X16 12 816")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 1318")
    tran0.writeAction("slorii X16 X16 12 3931")
    tran0.writeAction("slorii X16 X16 12 3175")
    tran0.writeAction("slorii X16 X16 12 3441")
    tran0.writeAction("slorii X16 X16 12 1738")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 43344")
    tran0.writeAction("slorii X16 X16 12 3860")
    tran0.writeAction("slorii X16 X16 12 2652")
    tran0.writeAction("slorii X16 X16 12 3766")
    tran0.writeAction("slorii X16 X16 12 3883")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 23132")
    tran0.writeAction("slorii X16 X16 12 2058")
    tran0.writeAction("slorii X16 X16 12 62")
    tran0.writeAction("slorii X16 X16 12 2997")
    tran0.writeAction("slorii X16 X16 12 2232")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 21393")
    tran0.writeAction("slorii X16 X16 12 3000")
    tran0.writeAction("slorii X16 X16 12 1566")
    tran0.writeAction("slorii X16 X16 12 2164")
    tran0.writeAction("slorii X16 X16 12 3123")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 58265")
    tran0.writeAction("slorii X16 X16 12 2423")
    tran0.writeAction("slorii X16 X16 12 1128")
    tran0.writeAction("slorii X16 X16 12 3664")
    tran0.writeAction("slorii X16 X16 12 4043")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 6998")
    tran0.writeAction("slorii X16 X16 12 1596")
    tran0.writeAction("slorii X16 X16 12 1376")
    tran0.writeAction("slorii X16 X16 12 1911")
    tran0.writeAction("slorii X16 X16 12 3921")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 46905")
    tran0.writeAction("slorii X16 X16 12 412")
    tran0.writeAction("slorii X16 X16 12 1410")
    tran0.writeAction("slorii X16 X16 12 3430")
    tran0.writeAction("slorii X16 X16 12 2074")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 44735")
    tran0.writeAction("slorii X16 X16 12 3053")
    tran0.writeAction("slorii X16 X16 12 1753")
    tran0.writeAction("slorii X16 X16 12 4093")
    tran0.writeAction("slorii X16 X16 12 2840")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 53259")
    tran0.writeAction("slorii X16 X16 12 1700")
    tran0.writeAction("slorii X16 X16 12 655")
    tran0.writeAction("slorii X16 X16 12 3934")
    tran0.writeAction("slorii X16 X16 12 2739")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 44059")
    tran0.writeAction("slorii X16 X16 12 1416")
    tran0.writeAction("slorii X16 X16 12 255")
    tran0.writeAction("slorii X16 X16 12 3882")
    tran0.writeAction("slorii X16 X16 12 1923")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 29332")
    tran0.writeAction("slorii X16 X16 12 1485")
    tran0.writeAction("slorii X16 X16 12 1287")
    tran0.writeAction("slorii X16 X16 12 1987")
    tran0.writeAction("slorii X16 X16 12 1099")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 4")
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
    tran1.writeAction("addi X7 X20 492")
    tran1.writeAction("movir X21 0")
    tran1.writeAction("add X20 X21 X5")
    tran1.writeAction("movsbr X16")
    tran1.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","sub X31 X10 X31")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state0)
    return efa
