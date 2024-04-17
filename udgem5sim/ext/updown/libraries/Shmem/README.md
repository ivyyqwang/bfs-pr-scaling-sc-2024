# UDShmem Library
## Description
- Core
    - `CAUDShmem.py`: The core file that include all the SHMEM's implementations
        - `efa`: required, efa object.
        - `state`: optional, state object.
        - `event_map_start`: optional, default 2. Will name its events after eventid=2, when `linker=True`, this is ignored.
        - `debug_level`: optional, default 2.
        - `perflog_level`: optional, default 5.
        - `term_flag_offset`: optional, default 0. starting scratchpad offset to put bookkeeping values for UDSHMEM.
        - `linker`: optional, default `False`. Enable it when using linker.
        - `impl`: optional, default `implLocAwareInterleaving`. Using interleaving implementation. This choice is based on the performance characterizations.
        - `throttle`: optional, default 128. The number of read requests before yield.
        - `enable3rdPartyMovers`: optional, default `False`. Only used in 3rd-party movers study, when enabled, UDSHMEM requires one extra arguments `nodeid` besides `dst`, `src` and `nelems`. **Note this is different from OpenSHMEM's `pe`.**
        - `includeConfigs`: optional, default `False`. When enabled, it requires 3 extra arguments `log2numnodes`, `log2blocksize` and `log2privblocksize`.
        - `enableFastSim`: optional, default `False`. When enabled, default config for FastSim would be used.
        - `printActions`: optional, default `False`. Debug option, to print parsed assembly when assembling or linking.
        - `work_estimator_exp_scalr`: optional, default 1. **Not recommended to change**, this is an empirically optimal value from the grid search of the performance characterizations.
        - `work_estimator_scalr`: optional, default 1. **Not recommended to change**, this is an empirically optimal value from the grid search of the performance characterizations.
        - `override_config`: optional, default `False`. Set `True` when you want to use the following default configurations
        - `numnodes`: optional, default 2. Valid when `override_config` set `True`. The total number of nodes in the system, has to be the power of 2.
        - `blocksize`: optional, default 65536. Valid when `override_config` set `True`. This is an empirically optimal value from the grid search of the performance characterizations.
        - `privblocksize`: optional, default 65536. Valid when `override_config` set `True`. This is an empirically optimal value from the grid search of the performance characterizations.
        - `log2gmapbase`: optional, default 33. Valid when `override_config` set `True`. This is aligned with the default updown configuration.
        - `log2mapbase`: optional, default 31. Valid when `override_config` set `True`. This is aligned with the default updown configuration.
    - `Utils.py`: utility tools.
- Linkable
    - `LibCAUDShmem.py`: The default linkable module.
        - Default using `Interleaving` implementation,
        - Throttle set to `128`. Mover yields after a continuous 128 chunks (64Bytes) read, would be wakeup once there is read-returns.
        - The user/system has to write the configuration to the lanes where SHMEM will be called and prior to the call, during runtime. (to `addr = term_flag_offset + 8`) 
    - `LibCAUDShmemHPE.py`: The linkable module with default/user-defined configurations during program build.
        - Default using `Interleaving` implementation.
        - Throttle set to `128`.
        - The user has to specify the configurations in the library file prior to build the program
        - The default settings are
            - `override_config=True`
            - `numnodes=2`
            - `blocksize=65536`, blocksize = 64KB
            - `privblocksize=65536`, private segment blocksize is 64KB
            - `log2gmapbase=33`, starting from `1<<33`
            - `log2mapbase=31`, starting from `1<<31`
    - `LibCAUDShmemHPEGEM5.py`: The linkable module with default/user-defined configuration during program build, specific to GEM5 simulation.
        - Same configurations as `LibCAUDShmemHPE.py`
        - `enableFastSim=True`

    - `LibCAUDShmemW3rdPartyMovers.py`
        - `enable3rdPartyMovers=True`, so it takes in 4th operands as the designated nodeid to start to put movers on.

## Implementations
### Unrealistic Baseline
Set `impl=CAUDShmem.implLocAwareUnrealBaseline`, this will implement unrealistic baseline version, which sends all the read first then write.
It is required to accompany this with larger queues in GEM5 simulation, e.g. use `configs/updown/HBM2e_8Gb_x128_UP_x1024.ini` when run GEM5 simulatins.
### [Recommended, Default] Interleaving
Set `impl=CAUDShmem.implLocAwareInterleaving`
This is default implementation that only takes up limited amount of resources.
### EvLoop
Set `impl=CAUDShmem.implLocAwareEvLoop`, this implements the read event loop version, which keeps sending read if there's any, and check whether to process write after each batch of send.