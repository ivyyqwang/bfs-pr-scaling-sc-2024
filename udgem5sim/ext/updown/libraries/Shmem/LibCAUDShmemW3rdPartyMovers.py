from CAUDShmem import CAUDShmem
from linker.EFAProgram import efaProgram, EFAProgram


@efaProgram
def LibCAUDShmemW3rdPartyMovers(efa: EFAProgram):
    """
    Default implementation of CAUDShmem
    User MUST first write the following configurations into the LM memory, starting from addr at term_flag_offset + 8:
    1. log2numnodes: log2(machine.NumNodes), user defined
    2. log2numstacks: log2(machine.NumStacks), must be 3 due to infra limitation
    3. log2nuds: log2(machine.NumUDs), must be 2 due to infra limitation
    4. log2numlanes: log2(machine.NumLanes), must be 6 due to infra limitation
    5: mapbase: 1 << 31 by default
    6: gmapbase: 1 << 33 by default
    7: log2blocksize: log2(blocksize), user defined, blocksize must be a power of 2
    8: log2privblocksize: log2(privblocksize), user defined, privblocksize must be a power of 2
    """
    state0 = efa.State("UDShmemState0")
    efa.add_initId(state0.state_id)
    efa.add_state(state0)
    shmem = CAUDShmem(efa, state0, event_map_start=0, debug_level=2, perflog_level=5, term_flag_offset=0, impl=CAUDShmem.implLocAwareInterleaving, linker=True, enable3rdPartyMovers=True)# init generate EFAs, efa and states are required for now, since we have block actions
    return efa