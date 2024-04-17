from LAUDShmem import LAUDShmem
from linker.EFAProgram import efaProgram, EFAProgram

@efaProgram
def LibLAUDShmem(efa: EFAProgram):
    state0 = efa.State("UDShmemState0")
    efa.add_initId(state0.state_id)
    efa.add_state(state0)
    shmem = LAUDShmem(efa, state0, event_map_start=0, debug_level=2, perflog_level=5, term_flag_offset=0, impl=LAUDShmem.implLocAwareInterleaving, is3rdPartyMover=False, linker=True, includeConfigs=True)# init generate EFAs, efa and states are required for now, since we have block actions
    return efa