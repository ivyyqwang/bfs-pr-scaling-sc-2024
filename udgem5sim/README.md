# UpDown Readme

## Setup Instructions
### Steps to run applications on gem5 using UD runtime

1. `git clone git@bitbucket.org:achien7242/udgem5sim.git`

2. `cd udgem5sim; source setup_env.sh`

3. Update submodules
    1. `git submodule init; git submodule update`

4. Compile DRAMSim3
    1. `cd $PROJ/ext/dramsim3/DRAMsim3`
    2. `mkdir build && cd build && cmake .. && make`

5. Compile UpDown Runtime, Apps and Libraries
    1. ``cd $PROJ/ext/updown``
    2. ``mkdir build; cd build``
    3. ``cmake $UPDOWN_SOURCE_CODE -DUPDOWNRT_ENABLE_TESTS=ON -DUPDOWNRT_ENABLE_UBENCH=ON -DUPDOWNRT_ENABLE_LIBRARIES=ON -DCMAKE_INSTALL_PREFIX=$UPDOWN_INSTALL_DIR -DUPDOWNRT_ENABLE_APPS=ON -DCMAKE_GEM5_BASE=$PROJ -DUPDOWN_ENABLE_FASTIM=OFF -DUPDOWN_ENABLE_BASIM=ON -DUPOWN_NODES=<1 | 8 | 32 | 64>``
    4. ``make -j; make install``

6. Compile GEM5 with UpDown+DRAMSim3
    1. `cd $PROJ`
    2. `scons build/X86/gem5.<opt|debug|fast> -j<numcpus>`


### Steps to run an example

7. `cd $PROJ`
    1. ``build/X86/gem5.fast --outdir=readbw  configs/updown/updown_agile.py --cpu-type=DerivO3CPU --caches --l2cache --l3cache --num-cpus=<> --num-uds=<> --num-stacks=<> --num-nodes=<> --stack-mem-size=16GB --fast-forward=1000000000000000000 --mem-type=DRAMsim3 --dramsim3-ini=configs/updown/HBM2e_8Gb_x128_UP.ini --lm_mode=1 --lseg-block-size=16MB --gseg-block-size=16MB --cmd='ext/updown/install/updown/ubenchmarks/updownDRAMReadBW' '--options=65536 0' --progfile=ext/updown/install/updown/ubenchmarks/updownDRAMReadBWEFA.bin --efa=updownDRAMReadBWEFA  --replicate-cli``
   Description of important parameters :
   1. `outdir` - Directory where stats will get dumped
   2. `configs/updown/updown_agile.py` - Do not change this (config builds the system)
   3. `num-uds` - Number of UDs per stack (4)
   4. `num-stacks` - Number of stacks/clusters per node (8)
   5. `num-nodes`  - Number of nodes in system (max=64 in simulation)
   6. `num-cpus` - Number of threads/processes per Node
   7. `cmd` - Top App 
   8. `options` - Runtime command line parameters to top app
   9. `progfile` - UpDown Binary
   10. `efa` - Program Entry point in binary file (currently not supported)
   11. `replicate-cli` - when running on multiple threads this can be used to avoid repeating `cmd` and `options` for each thread

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

## Performance Model 

The performance of the system is based on the released model available here [System Model](https://docs.google.com/spreadsheets/d/1bMsyeTtab9iiMDUnOQxK-HOtuDUeNnfqplydskAqbnE/edit#gid=110367088). 

### Adapting apps to run on gem5 for performance evaluation 
To use applications that have been tested already on FastSim on gem5, the following minor modifications need to be made. (example is based on Triangle Counting App)
1. `UpDown::UDRuntime_t` is to be used instead of `UpDown::SimUDRuntime_t` For example the following code snippet 

    ```
    auto test_rt = new UpDown::SimUDRuntime_t(machine,
    "GenTriCountEFAVertex", 
    "GenerateTriEFA", 
    "./", 
    UpDown::EmulatorLogLevel::STAGE_TRACE);
    ```

    can be replaced by 

    ```
    auto test_rt = new UpDown::UDRuntime_t();
    ```

2. Add gem5 pseudo instructions for stats and region of interest marking 
    `` #include <gem5/m5ops.h>

3. Reset stats and mark region of interest as shown below for triangle-counting 

    ```
    m5_switch_cpu();
    m5_dump_reset_stats(0,0);
        function_of_interest();
    m5_dump_reset_stats(0,0);
    ```
[a MultiNode Simulations](MULTINODE.md)
## Folder Structure 
The folder structure in inherited from the gem5 simulator. Below is a description of the important folders for UpDown

```
├── aws_scripts                                 # example scripts to launch simulations on aws
├── build_opts                                  # pre-made default configurations for gem5
├── components_library                          # gem5 components-library
├── configs                                     # gem5 simulation configuration files
│   └── updown                                  # updown system configuration files
├── docker_scripts                              # example scripts to launch simulations using docker images
├── ext                                         # less-common external packages needed to build gem5
│   ├── dramsim3                                # dramsim3 Submodule for HBM2e
│   ├── updown                                  # UpDown Submodule for UpDown Runtime, Apps, libraries
├── include                                     # include files for use in other programs (gem5)
├── scripts                                     # example scripts for local runs 
├── site_scons                                  # modular components of the build system
├── slurm_scripts                               # example scripts to launch simulations on slurm
├── src                                         # gem5 simulator src files 
│   ├── updown                                  # updown simobject wrapper
├── system                                      # source for some optional system software for simulated systems
├── tests                                       # tests to run on gem5 simulation infra
│   └── test-progs/upstream-snap/src/tests      # TOP programs 
│   |   ├── triangle-count                      # baseline, top programs for triangle count 
│   |   ├── pagerank                            # baseline, top programs for pagerank
│   |   ├── csr                                 # baseline, top programs for spmv
│   |   ├── jaccard                             # baseline, top programs for jaccard similarity coefficients
│   |   ├── utils                               # graph preprocessing programs
│   |   ├── microbench                          # microbenchmarks for updown
└── util                                        # useful utility programs and files (gem5)

```

## Common Errors in Simulations (updated as and when we see issues)

1. Simulation hang - Logs show no memory transactions 

    - Likely because the cpu is running in ``Atomic Mode`` and Memory is configured to ``Timing Mode``. In our simulations, we usually load the datasets using the ``AtomicCPU`` since we do not need detailed stats and do a switch cpu to ``TunedCPU`` for detailed timing. Typically the simulation script expects all the instantiated CPUs to be switched before moving to ``Timing Mode``.

2. Invalid Instructio encountered 
    build/X86/arch/x86/faults.cc:135: panic: Unrecognized/invalid instruction executed:
 
    {
	    leg = 0,
	    rex = 0,
	    vex/xop = 0,
	    op = {
	    	type = one byte,
	    	op = 0x6,
	    	},
	    modRM = 0,
	    sib = 0,
	    immediate = 0,
	    displacement = 0
	    dispSize = 0}
        Memory Usage: 41439284 KBytes
    }
    
    
    - This is likely due to an issue either on the 'top program' or the 'runtime'. Common mistakes might be - 
        1. MAPPED SIZE is not sufficient (check DEF_MAPPED_SIZE in ext/updown/runtime/include/updown_config.h)
        2. Compilation done with incorrect flags - delete ext/updown/build and recompile and try 

3. fatal: Syscall 318 out of range 
    
    - This syscall is not implemented in gem5 SE mode. One of hte scenarios in which this has shown up is if SimUDRuntime is being 'initialized' instead of UDRuntime in the gem5 env. 

4. SegFault at the end of simulation 
    - This is a known bug that doesn't affect the simulation. There is an issue with some file pointer at cleanup phase in the `ext/updown/<master>` branch. once this is fixed we'll remove this. Stats are reported correctly in this case