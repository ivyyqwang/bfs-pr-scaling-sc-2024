from EFA_v2 import *
import sys, os
env_updown_install_dir = os.environ['UPDOWN_INSTALL_DIR']
sys.path.insert(1, os.path.join(env_updown_install_dir, "updown/libraries"))
from UDShmem import UDShmem
def LibShmemEFA():
# def main():
    efa = EFA([])
    efa.code_level = 'machine'
    
    state0 = State() #Initial State
    efa.add_initId(state0.state_id)
    efa.add_state(state0)
    

    shmem = UDShmem(efa, state0, event_map_start=2, debug=False, largest_chunk=16, impl='basim') # init generate EFAs, efa and states are required for now, since we have block actions
    # X8 = src
    # X9 = dst
    # X10 = nelem
    tran = state0.writeTransition("eventCarry", state0, state0, 0)
    shmem.call_udshmem_get(tran, cont_label=1, reg_src="X8", reg_dst="X9", reg_nelem="X10", reg0="X16", reg1="X17", reg2="X18", reg3="X19", reg4="X20")
    tran.writeAction("yield")

    tran2 = state0.writeTransition("eventCarry", state0, state0, 1)
    # tran2.writeAction("print 'tran2 finished'")
    # tran2.writeAction("addi X16 X16 0")
    tran2.writeAction("yieldt")
    return efa