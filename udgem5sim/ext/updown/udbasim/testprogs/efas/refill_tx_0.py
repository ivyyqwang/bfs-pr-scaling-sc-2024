from EFA_v2 import *

def refill_tx_0():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)

    state0 = State()
    state0.alphabet = [0-255]
    efa.add_state(state0)

    state1 = State()
    state1.alphabet = [0-255]
    efa.add_state(state1)

    tran = state.writeTransition("basic_with_action", state, state0, 1)     #refill tx will be the outgoing tx from a state with "basic" state property 
    #X8 is the LM local address
    #set SBP
    tran.writeAction("add X8 X7 X5")   #set SBP X5 = X8 + X7
    tran.writeAction("add X9 X8 X30")   #X30 (MaxSBP)= X9(InputSize) + X8(SBP Init)
    #clear rdMode, CR_Issue, CR_Advance, MaxSBP in SBCR
    tran.writeAction("sri X4 X29 41") #(rshift) X29 clear SBCR(X4) left hand side
    tran.writeAction("sli X29 X29 41")   #(lshift) shift cleared SBCR back
    #Set rdMode if working in SB mode
    tran.writeAction("movir X28 1")      #(mov_imm2reg) 
    tran.writeAction("sli X28 X27 40")   #(lshift) X27: rdMode
    tran.writeAction("or X29 X27 X29")   #(orr) Update rdMode
    #this code is LM mode
    #Set CR_Issue
    #tran.writeAction("movir X28 1")     #(mov_imm2reg) 
    tran.writeAction("sli X28 X27 36")   #(lshift) X27: CR_Issue=1
    tran.writeAction("or X29 X27 X29")   #(orr) Update CR_Issue
    #Set CR_Advance
    tran.writeAction("sli X28 X27 35")   #(lshift) X27: CR_Advance=8 (32+3) bits shift
    tran.writeAction("or X29 X27 X29")   #(orr) Update CR_Advance
   # #Set MaxSBP (this was in LMMode)
   # tran.writeAction("or X29 X30 X4")     #(orr) Update MaxSBP(in X30) write to SBCR
    #Fill into SB for the first time
    tran.writeAction("movlsb X5")
    #make the SBP bits address in LM to work in SB mode
    tran.writeAction("movir X28 3")      #3: the shift value (we need to use register since X5 can only be written by R type instructions
    tran.writeAction("sl X5 X28 X5")
    #Set MaxSBP
    tran.writeAction("sl X30 X28 X30")    #X30 (MaxSBP)= bit address
    tran.writeAction("or X29 X30 X4")     #(orr) Update MaxSBP(in X30) write to SBCR

    tran.writeAction("lastact")

    tran = state0.writeTransition("refill_with_action", state0, state0, 0, 7)
    tran.writeAction("movir X17 0")
    #tran.writeAction("yieldt")
    tran.writeAction("lastact")
    tran = state0.writeTransition("refill_with_action", state0, state1, 1, 7)
    tran.writeAction("movir X17 1")
    #tran.writeAction("yieldt")
    tran.writeAction("lastact")
    tran = state1.writeTransition("refill_with_action", state1, state0, 0, 7)
    tran.writeAction("movir X17 0")
    #tran.writeAction("yieldt")
    tran.writeAction("lastact")
    tran = state1.writeTransition("refill_with_action", state1, state1, 1, 7)
    tran.writeAction("movir X17 2")
    tran.writeAction("yieldt")
    #tran.writeAction("beq X16 X30 test")

    #efa.appendBlockAction("test","sub X31 X10 X31")
    #efa.appendBlockAction("test","yieldt")

    efa.appendBlockAction("end_of_input_terminate_efa1","sub X31 X10 X31")
    efa.appendBlockAction("end_of_input_terminate_efa1","yieldt")

    efa.appendBlockAction("sb_refill","sri X5 X28 3")   #get the current SBP's LM byte address 
    efa.appendBlockAction("sb_refill","movlsb X28")
    efa.appendBlockAction("sb_refill","yieldt")

    efa.linkBlocktoState("end_of_input_terminate_efa1", state0)
    efa.linkBlocktoState("sb_refill", state0)
    return efa
