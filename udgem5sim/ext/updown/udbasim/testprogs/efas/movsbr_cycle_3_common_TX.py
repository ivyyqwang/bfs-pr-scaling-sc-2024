from EFA_v2 import *
def movsbr_cycle_3_common_TX():
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
    tran0.writeAction("movir X16 42147")
    tran0.writeAction("slorii X16 X16 12 1105")
    tran0.writeAction("slorii X16 X16 12 3168")
    tran0.writeAction("slorii X16 X16 12 1641")
    tran0.writeAction("slorii X16 X16 12 3201")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 3082")
    tran0.writeAction("slorii X16 X16 12 934")
    tran0.writeAction("slorii X16 X16 12 426")
    tran0.writeAction("slorii X16 X16 12 3450")
    tran0.writeAction("slorii X16 X16 12 576")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 6702")
    tran0.writeAction("slorii X16 X16 12 377")
    tran0.writeAction("slorii X16 X16 12 1373")
    tran0.writeAction("slorii X16 X16 12 2839")
    tran0.writeAction("slorii X16 X16 12 1633")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 6988")
    tran0.writeAction("slorii X16 X16 12 3251")
    tran0.writeAction("slorii X16 X16 12 2161")
    tran0.writeAction("slorii X16 X16 12 1261")
    tran0.writeAction("slorii X16 X16 12 3635")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 30785")
    tran0.writeAction("slorii X16 X16 12 1350")
    tran0.writeAction("slorii X16 X16 12 873")
    tran0.writeAction("slorii X16 X16 12 3957")
    tran0.writeAction("slorii X16 X16 12 3330")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 37533")
    tran0.writeAction("slorii X16 X16 12 3443")
    tran0.writeAction("slorii X16 X16 12 697")
    tran0.writeAction("slorii X16 X16 12 3395")
    tran0.writeAction("slorii X16 X16 12 3492")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 61535")
    tran0.writeAction("slorii X16 X16 12 3685")
    tran0.writeAction("slorii X16 X16 12 3338")
    tran0.writeAction("slorii X16 X16 12 3318")
    tran0.writeAction("slorii X16 X16 12 4059")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 5638")
    tran0.writeAction("slorii X16 X16 12 2589")
    tran0.writeAction("slorii X16 X16 12 1713")
    tran0.writeAction("slorii X16 X16 12 3953")
    tran0.writeAction("slorii X16 X16 12 1071")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 41428")
    tran0.writeAction("slorii X16 X16 12 2615")
    tran0.writeAction("slorii X16 X16 12 104")
    tran0.writeAction("slorii X16 X16 12 3534")
    tran0.writeAction("slorii X16 X16 12 200")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 48552")
    tran0.writeAction("slorii X16 X16 12 3583")
    tran0.writeAction("slorii X16 X16 12 484")
    tran0.writeAction("slorii X16 X16 12 3475")
    tran0.writeAction("slorii X16 X16 12 1994")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 64708")
    tran0.writeAction("slorii X16 X16 12 3938")
    tran0.writeAction("slorii X16 X16 12 3299")
    tran0.writeAction("slorii X16 X16 12 60")
    tran0.writeAction("slorii X16 X16 12 1956")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 7641")
    tran0.writeAction("slorii X16 X16 12 2466")
    tran0.writeAction("slorii X16 X16 12 1725")
    tran0.writeAction("slorii X16 X16 12 1943")
    tran0.writeAction("slorii X16 X16 12 1901")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 11089")
    tran0.writeAction("slorii X16 X16 12 1838")
    tran0.writeAction("slorii X16 X16 12 3558")
    tran0.writeAction("slorii X16 X16 12 3164")
    tran0.writeAction("slorii X16 X16 12 3863")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 55158")
    tran0.writeAction("slorii X16 X16 12 39")
    tran0.writeAction("slorii X16 X16 12 4095")
    tran0.writeAction("slorii X16 X16 12 3041")
    tran0.writeAction("slorii X16 X16 12 2999")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 23467")
    tran0.writeAction("slorii X16 X16 12 1375")
    tran0.writeAction("slorii X16 X16 12 896")
    tran0.writeAction("slorii X16 X16 12 874")
    tran0.writeAction("slorii X16 X16 12 706")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 36525")
    tran0.writeAction("slorii X16 X16 12 4029")
    tran0.writeAction("slorii X16 X16 12 2559")
    tran0.writeAction("slorii X16 X16 12 668")
    tran0.writeAction("slorii X16 X16 12 1716")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 42147")
    tran0.writeAction("slorii X16 X16 12 1105")
    tran0.writeAction("slorii X16 X16 12 3168")
    tran0.writeAction("slorii X16 X16 12 1641")
    tran0.writeAction("slorii X16 X16 12 3201")
    tran0.writeAction("sri X16 X16 41")
    tran0.writeAction("sli X16 X16 41")
    tran0.writeAction("movir X17 1")
    tran0.writeAction("sli X17 X17 40")
    tran0.writeAction("or X17 X16 X16")
    tran0.writeAction("movir X17 1")
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