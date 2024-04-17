from EFA_v2 import *
def movsbr_3_common_TX():
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
    tran0.writeAction("movir X16 37103")
    tran0.writeAction("slorii X16 X16 12 1773")
    tran0.writeAction("slorii X16 X16 12 3992")
    tran0.writeAction("slorii X16 X16 12 3925")
    tran0.writeAction("slorii X16 X16 12 1765")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 60419")
    tran0.writeAction("slorii X16 X16 12 8")
    tran0.writeAction("slorii X16 X16 12 1671")
    tran0.writeAction("slorii X16 X16 12 844")
    tran0.writeAction("slorii X16 X16 12 2420")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 14864")
    tran0.writeAction("slorii X16 X16 12 1113")
    tran0.writeAction("slorii X16 X16 12 1711")
    tran0.writeAction("slorii X16 X16 12 1752")
    tran0.writeAction("slorii X16 X16 12 3887")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 51957")
    tran0.writeAction("slorii X16 X16 12 1317")
    tran0.writeAction("slorii X16 X16 12 2531")
    tran0.writeAction("slorii X16 X16 12 3409")
    tran0.writeAction("slorii X16 X16 12 2880")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 34080")
    tran0.writeAction("slorii X16 X16 12 2658")
    tran0.writeAction("slorii X16 X16 12 1742")
    tran0.writeAction("slorii X16 X16 12 3088")
    tran0.writeAction("slorii X16 X16 12 3020")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 29729")
    tran0.writeAction("slorii X16 X16 12 142")
    tran0.writeAction("slorii X16 X16 12 1932")
    tran0.writeAction("slorii X16 X16 12 15")
    tran0.writeAction("slorii X16 X16 12 2470")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 54478")
    tran0.writeAction("slorii X16 X16 12 1738")
    tran0.writeAction("slorii X16 X16 12 99")
    tran0.writeAction("slorii X16 X16 12 2678")
    tran0.writeAction("slorii X16 X16 12 2018")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 7418")
    tran0.writeAction("slorii X16 X16 12 2747")
    tran0.writeAction("slorii X16 X16 12 3862")
    tran0.writeAction("slorii X16 X16 12 2100")
    tran0.writeAction("slorii X16 X16 12 4056")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 46765")
    tran0.writeAction("slorii X16 X16 12 541")
    tran0.writeAction("slorii X16 X16 12 2953")
    tran0.writeAction("slorii X16 X16 12 3403")
    tran0.writeAction("slorii X16 X16 12 427")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 28196")
    tran0.writeAction("slorii X16 X16 12 2204")
    tran0.writeAction("slorii X16 X16 12 907")
    tran0.writeAction("slorii X16 X16 12 2180")
    tran0.writeAction("slorii X16 X16 12 791")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 62487")
    tran0.writeAction("slorii X16 X16 12 3404")
    tran0.writeAction("slorii X16 X16 12 3550")
    tran0.writeAction("slorii X16 X16 12 1647")
    tran0.writeAction("slorii X16 X16 12 3922")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 60625")
    tran0.writeAction("slorii X16 X16 12 1282")
    tran0.writeAction("slorii X16 X16 12 1517")
    tran0.writeAction("slorii X16 X16 12 1343")
    tran0.writeAction("slorii X16 X16 12 3438")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 36472")
    tran0.writeAction("slorii X16 X16 12 3755")
    tran0.writeAction("slorii X16 X16 12 620")
    tran0.writeAction("slorii X16 X16 12 1361")
    tran0.writeAction("slorii X16 X16 12 429")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 57347")
    tran0.writeAction("slorii X16 X16 12 1434")
    tran0.writeAction("slorii X16 X16 12 3743")
    tran0.writeAction("slorii X16 X16 12 2470")
    tran0.writeAction("slorii X16 X16 12 690")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 15902")
    tran0.writeAction("slorii X16 X16 12 1828")
    tran0.writeAction("slorii X16 X16 12 3395")
    tran0.writeAction("slorii X16 X16 12 175")
    tran0.writeAction("slorii X16 X16 12 2864")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X16 12568")
    tran0.writeAction("slorii X16 X16 12 3112")
    tran0.writeAction("slorii X16 X16 12 1516")
    tran0.writeAction("slorii X16 X16 12 2021")
    tran0.writeAction("slorii X16 X16 12 1712")
    tran0.writeAction("movrl X16 0(X17) 1 8")
    tran0.writeAction("movir X18 1")
    tran0.writeAction("sli X18 X18 23")
    tran0.writeAction("or X18 X2 X2")
    tran0.writeAction("movir X16 37103")
    tran0.writeAction("slorii X16 X16 12 1773")
    tran0.writeAction("slorii X16 X16 12 3992")
    tran0.writeAction("slorii X16 X16 12 3925")
    tran0.writeAction("slorii X16 X16 12 1765")
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
    tran1.writeAction("addi X7 X20 68")
    tran1.writeAction("movir X21 0")
    tran1.writeAction("add X20 X21 X5")
    tran1.writeAction("movsbr X16")
    tran1.writeAction("yieldt")
    efa.appendBlockAction("end_of_input_terminate_efa1","sub X31 X10 X31")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")
    efa.linkBlocktoState("end_of_input_terminate_efa1", state0)
    return efa