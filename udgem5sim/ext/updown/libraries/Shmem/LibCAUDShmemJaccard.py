from CAUDShmem import CAUDShmem
from linker.EFAProgram import efaProgram, EFAProgram


@efaProgram
def LibCAUDShmemJaccard(efa: EFAProgram):
    """
    Only work in FASTSIM mode. The mapbase and gmapbase are set to default. numnodes is set to 2.
    Customized implementation of CAUDSHMEM for HPE, configurations will be passed as part of the library
    
    When using the library, user MUST pass the following configurations when initialize the library object:
    0: overrid_config: True, must be True to let the library takes in the given configurations
    1. term_flag_offset: offset of the termination flag in the LM memory, please specify in case it conflicts with other programs
    2. numnodes: machine.NumNodes, user defined, must be a power of 2, default is 1
    3. [optional] blocksize: blocksize in bytes, user defined, must be a power of 2, default is 64KB
    4. [optional] privblocksize: privblocksize in bytes, user defined, must be a power of 2, default is 64KB
    5. [optional] log2gmapbase: log2(gmapbase), user defined, default is 33
    6. [optional] log2mapbase: log2(mapbase), user defined, default is 31
    """
    state0 = efa.State("UDShmemState0")
    efa.add_initId(state0.state_id)
    efa.add_state(state0)
    shmem = CAUDShmem(efa, state0, event_map_start=0, debug_level=2, perflog_level=5, term_flag_offset=0, impl=CAUDShmem.implLocAwareEvLoop, linker=True,
                      enableFastSim=False, # have to turn on fastsim to make it default
                      override_config=True,
                      numnodes=2, # number of nodes, 2 is default
                      blocksize=134217728, # default blocksize in bytes, e.g. this is 128MB for jaccard broadcast
                      privblocksize=65536, # default private blocksize in bytes, e.g. this is 64KB
                      log2gmapbase=CAUDShmem.GMAP_BASE_LSHIFT, # default starting addr for global memory, e.g. this yields to 1 << 33
                      log2mapbase=CAUDShmem.MAP_BASE_LSHIFT, # default starting addr for local memory, e.g. this yields 1 << 31
                      )# init generate EFAs, efa and states are required for now, since we have block actions
    return efa