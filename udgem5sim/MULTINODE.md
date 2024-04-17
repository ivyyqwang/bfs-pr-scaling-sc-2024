# Running MultiNode Simulations

# THIS README IS DEPRECATED

Please refer to [UPDOWN-README](UPDOWN-README.md)

## Setup Instructions
Note: The multinode setup is currently available in the multinode branch. The master branch updates are available in this branch. It will be merged to master by 5/10. 

### Running simulations on gem5 for multinode configurations

1. Follow the same steps to setup runtime and gem5 as before given here [UPDOWN-README](UPDOWN-README.md) (Steps 1 - 6)

2. Make sure the runtime [repo](ext/updown) is updated to the master branch 

3. Use the following updated command to run node/multinode simulations

```
build/X86/gem5.opt|fast --outdir=<output_folder> configs/updown/updown_multinode.py --cpu-type=DerivO3CPU --caches --l2cache --l3cache --num-cpus=1 --num-uds=4 --num-stacks=8 --num-nodes=2 --stack-mem-size=16GB --fast-forward=1000000000000000000 --mem-type=DRAMsim3 --dramsim3-ini=configs/updown/HBM2e_8Gb_x128_UP.ini --lm_mode=0 --lseg-block-size=64MB --gseg-block-size=64MB --cmd=ext/updown/install/updown/apps/lane_ping_pong_mnode '--options=64 4 8 2 0 4095' --progfile=isav2EFAs --efa=LanePingPongTest --suffix=test --updown-perf-log
```

4. As mentioned in [UPDOWN-README](UPDOWN-README.md), ``--cmd`` and the corresponding ``--options`` should be repeated for as many cpus as there are in the system.

5. To simplify this. a convenience script is provided to run the simulations.

```
runsim.py --cfg configs/updown/cfg_inis/system_cfg.ini
```
6. ``configs/updown/cfg_inis/*`` files can be used as templates to create one for the app you are running. This is not mandatory and the original gem5 run command will also work well. 


7. In order to allow for running sweeps on the machine configuration (without recompiling runtime or gem5), configure the ``UDRuntime_t`` with the correct configuration of ``udmachine_t``, the same parameters can be passed into gem5 
```
    --num-uds = Number of UDs per stack
    --num-stacks = Number of stacks/clusters per node
    --num-nodes = Number of nodes in system (Tested upto 2 currently)
    --num-cpus = Number of threads/processes per Node
```

Important Note: Due to the limitation of SysCall Emulation mode simulation of gem5, multiple cpus are used to mimic multithreaded simulation. Instantiating many cpus will definitely slow down simulations considerably as the CPU in gem5 generates detailed simulation events. It is recommended that the CPU thread be kept to 1 per node.


## Memory Allocation
Until DRAMMalloc is available, we have provided 2 separate memory regions for local and global memory segments. 

1. To allocate node local memory segments use the ``UDRuntime`` api ``mm_malloc`` as before. The local segments will be allocated across stacks. 

2. To allocate global memory segments use ``UDRuntime`` api ``mm_alloc_global``. This new api will allocate the global segment across nodes. 

3. The local and global segment block sizes are configurable through the following runtime parameters 
    ```
    --lseg-block-size=64MB --gseg-block-size=64MB
    ```

The start addresses for these regions and their total allocation are configured in ``updown_config.h`` [here](ext/updown/runtime/include/updown_config.h)


## Debugging
Debugging the larger simulations can be challenging. The best practise to do this would be,
1. Run the app on fastsim with the configuration you intend to simulate on gem5. 
2. Scale up simualtios on gem5 from 1 cluster - 2 upto 1 node and beyond. 
3. If 2 cluster configuration works, 'ideally' it should work upto 1 node 
4. gem5 provides some debug flags that can be used to trace transactions. Additionally the UpDown emulator also provides some tracing tools to debug. In order to dump UpDown gem5 logs You can use the following switches. These switches should precede ``configs`` in the run command
```
    --debug-flags=UpDown --> Dumps UpDown debug messages (additional flags can be found running --debug-help)
    --debug-start=<> --> Timestamp from when you want to dump messages (simulation Tick)
```
The UpDown Emulator trace can be enabled using the following two switches
```
    --print-level=<> --> Dumps different levels of traces 1 being lowest, 5 being highest (1 is mostly sufficient)
    --print-threshold=<> --> Timestamp from when you want to dump messages (simulation Tick - you can match the value above)
```

## Latency Simulations
In order to sweep memory latencies to mimic off-cluster/off-node transactions, you can dial in latency (in cycles of 0.5ns period) using the following switch 
```
    --mem-lat=<>
```
This latency will be added on top of the existing DRAM latency (~50-75ns)


## Performance Model 

The performance of the system is based on the released model available here [System Model](https://docs.google.com/spreadsheets/d/1cGTkvzw3csEjzs4teaecmLm9XJpErG95/edit?usp=share_link&ouid=102997537627254077376&rtpof=true&sd=true). 


Please contact (andronicus@uchicago.edu) for all issues related to multinode simulations
