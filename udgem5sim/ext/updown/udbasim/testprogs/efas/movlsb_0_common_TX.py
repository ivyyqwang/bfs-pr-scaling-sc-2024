from EFA_v2 import *
def movlsb_0_common_TX():
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
    tran0.writeAction("movir X16 31799")
    tran0.writeAction("slorii X16 X16 12 850")
    tran0.writeAction("slorii X16 X16 12 1201")
    tran0.writeAction("slorii X16 X16 12 3688")
    tran0.writeAction("slorii X16 X16 12 2586")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 21089")
    tran0.writeAction("slorii X16 X16 12 112")
    tran0.writeAction("slorii X16 X16 12 3849")
    tran0.writeAction("slorii X16 X16 12 3860")
    tran0.writeAction("slorii X16 X16 12 2704")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 37000")
    tran0.writeAction("slorii X16 X16 12 1523")
    tran0.writeAction("slorii X16 X16 12 16")
    tran0.writeAction("slorii X16 X16 12 211")
    tran0.writeAction("slorii X16 X16 12 538")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 31797")
    tran0.writeAction("slorii X16 X16 12 736")
    tran0.writeAction("slorii X16 X16 12 1148")
    tran0.writeAction("slorii X16 X16 12 1825")
    tran0.writeAction("slorii X16 X16 12 3234")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 45433")
    tran0.writeAction("slorii X16 X16 12 3727")
    tran0.writeAction("slorii X16 X16 12 272")
    tran0.writeAction("slorii X16 X16 12 334")
    tran0.writeAction("slorii X16 X16 12 3378")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 41796")
    tran0.writeAction("slorii X16 X16 12 2583")
    tran0.writeAction("slorii X16 X16 12 1258")
    tran0.writeAction("slorii X16 X16 12 3403")
    tran0.writeAction("slorii X16 X16 12 2221")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 33944")
    tran0.writeAction("slorii X16 X16 12 837")
    tran0.writeAction("slorii X16 X16 12 2623")
    tran0.writeAction("slorii X16 X16 12 2893")
    tran0.writeAction("slorii X16 X16 12 178")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 17163")
    tran0.writeAction("slorii X16 X16 12 3917")
    tran0.writeAction("slorii X16 X16 12 879")
    tran0.writeAction("slorii X16 X16 12 3996")
    tran0.writeAction("slorii X16 X16 12 3644")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 55128")
    tran0.writeAction("slorii X16 X16 12 2463")
    tran0.writeAction("slorii X16 X16 12 3840")
    tran0.writeAction("slorii X16 X16 12 1870")
    tran0.writeAction("slorii X16 X16 12 3800")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 42470")
    tran0.writeAction("slorii X16 X16 12 1314")
    tran0.writeAction("slorii X16 X16 12 2")
    tran0.writeAction("slorii X16 X16 12 3014")
    tran0.writeAction("slorii X16 X16 12 595")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 65084")
    tran0.writeAction("slorii X16 X16 12 2140")
    tran0.writeAction("slorii X16 X16 12 1098")
    tran0.writeAction("slorii X16 X16 12 395")
    tran0.writeAction("slorii X16 X16 12 3648")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 27181")
    tran0.writeAction("slorii X16 X16 12 2107")
    tran0.writeAction("slorii X16 X16 12 194")
    tran0.writeAction("slorii X16 X16 12 3145")
    tran0.writeAction("slorii X16 X16 12 45")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 6672")
    tran0.writeAction("slorii X16 X16 12 289")
    tran0.writeAction("slorii X16 X16 12 337")
    tran0.writeAction("slorii X16 X16 12 2521")
    tran0.writeAction("slorii X16 X16 12 254")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 24597")
    tran0.writeAction("slorii X16 X16 12 48")
    tran0.writeAction("slorii X16 X16 12 1035")
    tran0.writeAction("slorii X16 X16 12 1074")
    tran0.writeAction("slorii X16 X16 12 2995")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 53792")
    tran0.writeAction("slorii X16 X16 12 684")
    tran0.writeAction("slorii X16 X16 12 340")
    tran0.writeAction("slorii X16 X16 12 4016")
    tran0.writeAction("slorii X16 X16 12 1791")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 8676")
    tran0.writeAction("slorii X16 X16 12 3186")
    tran0.writeAction("slorii X16 X16 12 1471")
    tran0.writeAction("slorii X16 X16 12 2675")
    tran0.writeAction("slorii X16 X16 12 2087")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 31799")
    tran0.writeAction("slorii X16 X16 12 850")
    tran0.writeAction("slorii X16 X16 12 1201")
    tran0.writeAction("slorii X16 X16 12 3688")
    tran0.writeAction("slorii X16 X16 12 2586")
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
    tran0.writeAction("addi X7 X20 19")
    tran0.writeAction("movir X21 0")
    tran0.writeAction("sli X20 X20 3")
    tran0.writeAction("addi X21 X17 664")
    tran0.writeAction("add X20 X21 X5")
    tran0.writeAction("or X17 X16 X4")
    tran0.writeAction("addi X4 X18 0")
    tran0.writeAction("lastact")
    tran1 = state0.writeTransition("commonCarry_with_action", state0, state0, 0)
    tran1.writeAction("addi X7 X17 19")
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
