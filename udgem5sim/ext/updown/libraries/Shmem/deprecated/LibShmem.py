from UDShmem import UDShmem
from linker.EFAProgram import efaProgram

@efaProgram
def GenerateShmemEFA(efa):
    # state0 = efa.State()
    state0 = efa.State("ShmemState1")
    efa.add_initId(state0.state_id)
    efa.add_state(state0)
    shmem = UDShmem(efa, state0, event_map_start=0, debug=True, largest_chunk=16, impl='basim', linker=True) # init generate EFAs, efa and states are required for now, since we have block actions
    return efa