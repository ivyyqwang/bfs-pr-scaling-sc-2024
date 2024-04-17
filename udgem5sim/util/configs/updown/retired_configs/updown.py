""" Simple config/run script for the UpDownObj

This file tests the integration with Spike through

"""

import argparse
import sys
import os
import m5
from m5.defines import buildEnv
from m5.objects import *
from m5.params import NULL
from m5.util import addToPath, fatal, warn

addToPath('../')

from ruby import Ruby
from system.core import TunedCPU
from system.core import UnconstrainedCPU
import shutil

from common import Options
import Simulation
import CacheConfig
from common import CpuConfig
from common import ObjectList
from common import MemConfig
from common.FileSystemConfig import config_filesystem
from common.Caches import *
from common.cpu2000 import *

def get_processes(args):
    """Interprets provided args and returns a list of processes"""

    multiprocesses = []
    inputs = []
    outputs = []
    errouts = []
    pargs = []

    workloads = args.cmd.split(';')
    if args.input != "":
        inputs = args.input.split(';')
    if args.output != "":
        outputs = args.output.split(';')
    if args.errout != "":
        errouts = args.errout.split(';')
    if args.options != "":
        pargs = args.options.split(';')

    idx = 0
    for wrkld in workloads:
        process = Process(pid = 100 + idx)
        process.executable = wrkld
        process.cwd = os.getcwd()

        if args.env:
            with open(args.env, 'r') as f:
                process.env = [line.rstrip() for line in f]

        if len(pargs) > idx:
            process.cmd = [wrkld] + pargs[idx].split()
        else:
            process.cmd = [wrkld]

        if len(inputs) > idx:
            process.input = inputs[idx]
        if len(outputs) > idx:
            process.output = outputs[idx]
        if len(errouts) > idx:
            process.errout = errouts[idx]

        multiprocesses.append(process)
        idx += 1

    if args.smt:
        assert(args.cpu_type == "DerivO3CPU")
        return multiprocesses, idx
    else:
        return multiprocesses, 1

def parse_config(cfg_file):
    
    """
    As defined by Jose in updown/runtime/include/updown.h of runtime repo 
    
    Scratchpad memory address space
           MEMORY                     SIZE
      |--------------|  <-- Scratchpad Base Address
      |              |
      |   SPMEM UD0  |
      |              |
      |--------------|  <-- CapacityPerLane * CapacityNumLanes
      |              |
      |   SPMEM UD1  |
      |              |
      |--------------|  <-- 2 * CapacityPerLane * CapacityNumLanes
      |      ...     |
      |--------------|
      |              |
      |   SPMEM UDN  |
      |              |
      |--------------|  <-- NumUDs * CapacityPerLane * CapacityNumLanes
   
    Scratchpad memory for 1 UD
           MEMORY                     SIZE
      |--------------|  <-- Scratchpad Base Address
      |              |
      |    Lane 0    |
      |              |
      |* * * * * * * |  <-- SPmem BankSize
      | * * * * * * *|    |
      |* * * * * * * |    | For expansion purposes
      | * * * * * * *|    |
      |--------------|  <-- CapacityPerLane
      |              |
      |    Lane 1    |
      |              |
      |* * * * * * * |  <-- CapacityPerLane + SPmem BankSize
      | * * * * * * *|    |
      |* * * * * * * |    | For expansion purposes
      | * * * * * * *|    |
      |--------------|  <-- 2 * CapacityPerLane
      |      ...     |
      |--------------|  <-- (NumLanes-1)*CapacityPerLane
      |              |
      |    Lane N    |
      |              |
      |* * * * * * * |  <-- (NumLanes-1)*CapacityPerLane + SPmem BankSize
      | * * * * * * *|    |
      |* * * * * * * |    | For expansion purposes
      | * * * * * * *|    |
      |--------------|  <-- (NumLanes) * CapacityPerLane
      | * * * * * * *|
      |* * * * * * * |   -|
      | * * * * * * *|    | For expansion purposes
      |* * * * * * * |   -|
      | * * * * * * *|
      |--------------|  <-- CapacityPerLane * CapacityNumLanes
   
    Control signals memory address space
           MEMORY                     SIZE
      |--------------|  <-- Control Base Address
      |              |
      |  CONTROL UD0 |
      |              |
      |--------------|  <-- CapacityControlPerLane * CapacityNumLanes
      |              |
      |  CONTROL UD1 |
      |              |
      |--------------|  <-- 2 * CapacityControlPerLane * CapacityNumLanes
      |      ...     |
      |--------------|
      |              |
      |  CONTROL UD2 |
      |              |
      |--------------|  <-- NumUDs * CapacityControlPerLane * CapacityNumLanes
   
    Control signals memory address space for 1 UD
           MEMORY                     SIZE
      |--------------|  <-- Control Base Address
      |    Lane 0    |
      |  Event Queue |
      | Oprnds Queue |
      |     Lock     |
      |* * * * * * * |   -|
      | * * * * * * *|    |
      |* * * * * * * |    | For expansion purposes
      | * * * * * * *|    |
      |--------------|  <-- CapacityControlPerLane
      |    Lane 1    |
      |  Event Queue |
      | Oprnds Queue |
      |     Lock     |
      |* * * * * * * |   -|
      | * * * * * * *|    |
      |* * * * * * * |    | For expansion purposes
      | * * * * * * *|    |
      |--------------|  <-- 2 * CapacityControlPerLane
      |      ...     |
      |--------------|  <-- (NumLanes-1) * CapacityControlPerLane
      |    Lane N    |
      |  Event Queue |
      | Oprnds Queue |
      |     Lock     |
      |* * * * * * * |   -|
      | * * * * * * *|    |
      |* * * * * * * |    | For expansion purposes
      | * * * * * * *|    |
      |--------------|  <-- NumLanes * CapacityControlPerLane
      | * * * * * * *|
      |* * * * * * * |   -|
      | * * * * * * *|    | For expansion purposes
      |* * * * * * * |   -|
      | * * * * * * *|
      |--------------|  <-- CapacityControlPerLane * CapacityNumLanes
    """
    """
    #define DEF_NUM_LANES 64         // Number of lanes per CU
    #define DEF_NUM_UDS 1           // Number of CUs
    #define DEF_NUM_STACKS 1           // Number of Stacks per Node
    #define DEF_NUM_NODES 0x1           // Number of Nodes in System
    #define DEF_SPMEM_BANK_SIZE 65536 // Scratchpad Memory size per lane
    #define DEF_WORD_SIZE 8           // Wordsize
    #define DEF_MAPPED_SIZE 1UL << 32
    
    // Base address for scratchpad memories
    #define BASE_SPMEM_ADDR 0x400000000
    // Base address for memory mapped control registers
    #define BASE_CTRL_ADDR 0x600000000
    // Scratchpad address space maximum capacity
    //#define SPMEM_CAPACITY_PER_LANE 1UL << 17
    #define SPMEM_CAPACITY_PER_LANE 65536
    // Control signals address space capacity. Number of control registers may
    #define CONTROL_CAPACITY_PER_LANE 32
    // Number of lanes capacity
    //#define NUM_LANES_CAPACITY 1UL << 7
    #define NUM_LANES_CAPACITY 64
    // Number of lanes capacity
    //#define NUM_UDS_CAPACITY 1UL << 7
    #define NUM_UDS_CAPACITY 4
    // Number of lanes capacity
    //#define NUM_NODES_CAPACITY 1UL << 7
    #define NUM_NODES_CAPACITY 1
    // Number of lanes capacity
    //#define NUM_STACKS_CAPACITY 1UL << 7
    #define NUM_STACKS_CAPACITY 8
    
    // Base address mapped memory - This is due to simulation
    #define BASE_MAPPED_ADDR 0x80000000
    
    // CONTROL SIGNALES OFFSET IN WORDS
    #define EVENT_QUEUE_OFFSET 0x0
    #define OPERAND_QUEUE_OFFSET 0x1
    #define START_EXEC_OFFSET 0x2
    #define LOCK_OFFSET 0x3
    """
    config = {
            "DEF_NUM_LANES" : 64,
            "DEF_NUM_UDS" : 1,
            "DEF_NUM_NODES" : 1,
            "DEF_NUM_STACKS" : 1,
            "DEF_SPMEM_BANK_SIZE" : 65536,
            "BASE_SPMEM_ADDR" : 0x400000000,
            "BASE_CTRL_ADDR" : 0x600000000,
            "SPMEM_CAPACITY_PER_LANE": 65536,
            "CONTROL_CAPACITY_PER_LANE" : 32,
            "NUM_LANES_CAPACITY" : 64,
            "NUM_UDS_CAPACITY" : 4,
            "NUM_NODES_CAPACITY" : 1,
            "NUM_STACKS_CAPACITY" : 1
            }
    fd = open(cfg_file, "r")
    file_lines = fd.readlines()
    for line in file_lines:
        lineitems = line.split()
        if(len(lineitems) > 0):
            if(lineitems[0] == "#define"):
                keyval = lineitems[1]
                if keyval in config.keys():
                    if(lineitems[2][0:2] == "0x"):
                        config[keyval] = int(lineitems[2], 16)
                    else:
                        config[keyval] = int(lineitems[2])
    return config


### Parsing configs and setting up simulation

## some path variables to be set.

print(os.environ.get('UPDOWN_INSTALL_DIR'))
updown_install_path = os.environ.get('UPDOWN_INSTALL_DIR')
sys.path.append(updown_install_path + "/updown/apps")


## Parsing all the command line arguments 
parser = argparse.ArgumentParser()
Options.addCommonOptions(parser)
Options.addSEOptions(parser)

parser.add_argument("--updown-kernel", action="store",
                        type=str, dest="updown",
                        help="updown kernel to execute")
parser.add_argument("--efa", type=str,
                    help="EFA to load in updown")
parser.add_argument("--progfile", type=str,
                    help="Progfile containing EFA")
parser.add_argument("--num-lanes", type=int, default=1)
parser.add_argument("--upmem-channels", type=int, default=8)
parser.add_argument("--lmbanksize", type=int, default=65536)
parser.add_argument("--lm_mode", type=int, default=0)
parser.add_argument("--suffix", type=str, default="simdata")
parser.add_argument("--logfile", type=str, default=None)
parser.add_argument("--udconfig-file", type=str, default="ext/updown/runtime/include/updown_config.h")
parser.add_argument("--updown-perf-log", action="store_true")
parser.add_argument("--updown-perf-log-internal", action="store_true")
parser.add_argument("--print-level", type=int, default=5)
parser.add_argument("--recode", action="store_true")
parser.add_argument("--num-uds", type=int, default=1)
parser.add_argument("--num-iud-channels", type=int, default=8)


                        #default="/opt/riscv/riscv64-unknown-elf/bin/pk b.o")
parser.add_argument("--l3cache", action="store_true",
                        dest="l3cache",
                        help="Include L3Cache")
if '--ruby' in sys.argv:
    Ruby.define_options(parser)

args = parser.parse_args()
print("checkpoint_dir ", args.checkpoint_dir)
if args.logfile:
    sys.stdout = open(args.logfile, 'w')
    sys.stderr = sys.stdout

multiprocesses = []
numThreads = 1

if args.bench:
    apps = args.bench.split("-")
    if len(apps) != args.num_cpus:
        print("number of benchmarks not equal to set num_cpus!")
        sys.exit(1)

    for app in apps:
        try:
            if buildEnv['TARGET_ISA'] == 'arm':
                exec("workload = %s('arm_%s', 'linux', '%s')" % (
                        app, args.arm_iset, args.spec_input))
            else:
                exec("workload = %s(buildEnv['TARGET_ISA', 'linux', '%s')" % (
                        app, args.spec_input))
            multiprocesses.append(workload.makeProcess())
        except:
            print("Unable to find workload for %s: %s" %
                  (buildEnv['TARGET_ISA'], app),
                  file=sys.stderr)
            sys.exit(1)
elif args.cmd:
    multiprocesses, numThreads = get_processes(args)
else:
    print("No workload specified. Exiting!\n", file=sys.stderr)
    sys.exit(1)


(CPUClass, test_mem_mode, FutureClass) = Simulation.setCPUClass(args)
CPUClass.numThreads = numThreads

# Check -- do not allow SMT with multiple CPUs
if args.smt and args.num_cpus > 1:
    fatal("You cannot use SMT with multiple CPUs!")

np = args.num_cpus
nc = args.upmem_channels
nud_channels = args.num_iud_channels
mp0_path = multiprocesses[0].executable



#system = System(cpu = [CPUClass(cpu_id=i) for i in range(np)],
"""
 Using the Skylake Config from 
"""
if not args.fast_forward:
    #system = System(cpu = [TunedCPU(cpu_id=i) for i in range(np)],
    #system = System(cpu = [UnconstrainedCPU(cpu_id=i) for i in range(np)],
    system = System(cpu = [TunedCPU(cpu_id=i) for i in range(np)],
                mem_mode = 'timing',
                #mem_mode = 'atomic',
                mem_ranges = [AddrRange(args.mem_size)],
                cache_line_size = args.cacheline_size)
else:
    system = System(cpu = [AtomicSimpleCPU(cpu_id=i) for i in range(np)],
                mem_mode = 'atomic',
                mem_ranges = [AddrRange(args.mem_size)],
                cache_line_size = args.cacheline_size)


if numThreads > 1:
    system.multi_thread = True

# Create a top-level voltage domain
system.voltage_domain = VoltageDomain(voltage = args.sys_voltage)
# Andronicus: Hardcoding sys_clock and cpu_clock here
print("Setting Sys Clock: 2Ghz")
args.sys_clock = '2GHz'
#if not args.cpu_clock:
print("Setting CPU Clock: 2Ghz")
args.cpu_clock = '2GHz'


# Create a source clock for the system and set the clock period
system.clk_domain = SrcClockDomain(clock =  args.sys_clock,
                                   voltage_domain = system.voltage_domain)

# Create a CPU voltage domain
system.cpu_voltage_domain = VoltageDomain()

# Create a separate clock domain for the CPUs
system.cpu_clk_domain = SrcClockDomain(clock = args.cpu_clock,
                                       voltage_domain =
                                       system.cpu_voltage_domain)

# If elastic tracing is enabled, then configure the cpu and attach the elastic
# trace probe
if args.elastic_trace_en:
    CpuConfig.config_etrace(CPUClass, system.cpu, args)

# All cpus belong to a common cpu_clk_domain, therefore running at a common
# frequency.
for cpu in system.cpu:
    cpu.clk_domain = system.cpu_clk_domain

if ObjectList.is_kvm_cpu(CPUClass) or ObjectList.is_kvm_cpu(FutureClass):
    if buildEnv['TARGET_ISA'] == 'x86':
        system.kvm_vm = KvmVM()
        for process in multiprocesses:
            process.useArchPT = True
            process.kvmInSE = True
    else:
        fatal("KvmCPU can only be used in SE mode with x86")

# Sanity check
if args.simpoint_profile:
    if not ObjectList.is_noncaching_cpu(CPUClass):
        fatal("SimPoint/BPProbe should be done with an atomic cpu")
    if np > 1:
        fatal("SimPoint generation not supported with more than one CPUs")
for i in range(np):
    if args.smt:
        system.cpu[i].workload = multiprocesses
    elif len(multiprocesses) == 1:
        system.cpu[i].workload = multiprocesses[0]
    else:
        system.cpu[i].workload = multiprocesses[i]

    if args.simpoint_profile:
        system.cpu[i].addSimPointProbe(args.simpoint_interval)

    if args.checker:
        system.cpu[i].addCheckerCpu()

    if args.bp_type:
        bpClass = ObjectList.bp_list.get(args.bp_type)
        system.cpu[i].branchPred = bpClass()

    if args.indirect_bp_type:
        indirectBPClass = \
            ObjectList.indirect_bp_list.get(args.indirect_bp_type)
        system.cpu[i].branchPred.indirectBranchPred = indirectBPClass()

    system.cpu[i].createThreads()

cfg = parse_config(args.udconfig_file)
# Create an instantiation of the simobject
nlanes = cfg["DEF_NUM_LANES"]
print("NumLanes:%d" % nlanes)
lmbanksize = cfg["DEF_SPMEM_BANK_SIZE"]
#UpMemorySize = lmbanksize*nlanes+1024
updowncnt = cfg["DEF_NUM_UDS"]
np = updowncnt
print("Number of UpDowns:%d" % updowncnt)
single_ud_memsize = lmbanksize*nlanes # [*2 to allow for in_stream addressing]
single_ctrlsize = nlanes*32 # [*2 to allow for in_stream addressing]
#UpMemorySize = updowncnt*(lmbanksize*nlanes*2)
UpMemorySize = updowncnt*(lmbanksize*nlanes)
UpCtrlSize = updowncnt*(nlanes*32)
udspbase = cfg["BASE_SPMEM_ADDR"]
udctrlbase = cfg["BASE_CTRL_ADDR"]
ud_addr_range=[]
ud_ctrladdr_range=[]
for i in range(updowncnt):
    ud_addr_range.append(AddrRange(start=Addr(udspbase + i*single_ud_memsize),
                    end=Addr(udspbase + (i+1)*single_ud_memsize)))
    ud_ctrladdr_range.append(AddrRange(start=Addr(udctrlbase + i*single_ctrlsize),
                    end=Addr(udctrlbase + (i+1)*single_ctrlsize)))
print("Address Ranges of Updowns")
print(ud_addr_range)
# Create the memory mapping file and move it to the correct locations! 
print("Progfile:%s, EFA:%s" %(args.progfile, args.efa))
simdir="simdata"
simdirpath=""
if args.suffix:
    simdir = "simdata_" + args.suffix
    print("Using suffix %s for simdata" % simdir)
    path = os.getcwd()
    simdirpath = os.path.join(path,simdir)
    if(not os.path.isdir(simdirpath)):
        print("%s created for simdata" % simdir)
        os.mkdir(simdirpath)

updowns=[]
udcnt = 0
for ud in range(updowncnt):
    upobj=UpDownObj(latency=1,
            addrRange=ud_addr_range[ud],
            ctrladdrRange=ud_ctrladdr_range[ud],
            numlanes=nlanes,
            efa=args.efa,
            simdir=simdir,
            lm_mode=args.lm_mode,
            recode=args.recode,
            upmem_channels=args.upmem_channels,
            iud_channels=args.num_iud_channels,
            lmsize=lmbanksize,
            progfile=args.progfile,
            print_level=args.print_level,
            perf_log_enable=args.updown_perf_log,
            perf_log_internal_enable=args.updown_perf_log_internal,
            udidx=ud,
            nwid=ud)
    updowns.append(upobj)
    udcnt += 1
system.updown=updowns
#   system.updown = UpDownObj(latency=1,
#                              simdir=simdir,
#                              lm_mode=args.lm_mode,
#                              upmem_channels=args.upmem_channels,
#                              print_level=args.print_level,
#                              perf_log_file=args.updown_perf_log,
#                              perf_log_internal=args.updown_perf_log_internal,
#                              addrRange=upAddrRange)
#                              #upArgs= args.updown)
#system.mem_ranges.append(dsAddrRange)


if args.ruby:
    Ruby.create_system(args, False, system)
    assert(args.num_cpus == len(system.ruby._cpu_ports))

    system.ruby.clk_domain = SrcClockDomain(clock = args.ruby_clock,
                                        voltage_domain = system.voltage_domain)
    for i in range(np):
        ruby_port = system.ruby._cpu_ports[i]

        # Create the interrupt controller and connect its ports to Ruby
        # Note that the interrupt controller is always present but only
        # in x86 does it have message ports that need to be connected
        system.cpu[i].createInterruptController()

        # Connect the cpu's cache ports to Ruby
        ruby_port.connectCpuPorts(system.cpu[i])
else:
    MemClass = Simulation.setMemClass(args)
    print(MemClass)
    system.membus = SystemXBar()
    system.udbus = UDXBar()
    #system.membus2 = IOXBar()
    system.system_port = system.membus.slave
    CacheConfig.config_cache(args, system)
    MemConfig.config_mem(args, system, nc, 1)
    config_filesystem(system, args)

#system.updown.mem_side = system.membus.slave
for j in range(updowncnt):
    for i in range(np):
        system.updown[j].cpu_side[i] = system.cpu[i].l1xbar.mem_side_ports
    for i in range(nc):
        system.updown[j].mem_side[i] = system.membus.slave
    for i in range(nud_channels):
        system.updown[j].udin_side[i] = system.udbus.mem_side_ports
        system.updown[j].udout_side[i] = system.udbus.cpu_side_ports

system.workload = SEWorkload.init_compatible(mp0_path)

if args.wait_gdb:
    system.workload.wait_for_remote_gdb = True

root = Root(full_system = False, system = system)
checkpoint_dir = None
cpt_starttick = 0
if(args.checkpoint_restore):
    cpt_starttick, checkpoint_dir = Simulation.initialize(args, root, system, FutureClass)
else:
    Simulation.initialize(args, root, system, FutureClass)

#Simulation.initialize(args, root, system, FutureClass)
## Mapping UpStream memory to the process
print(Addr(args.mem_size))
print(args.mem_size)
print(system.mem_ranges)
print(int(0xFFFFFFF))
if not(args.checkpoint_restore):
    for process in multiprocesses:
        if(args.progfile=='GenPagerankEFA' or args.progfile=='GenPagerankMultiUDEFA'):
            process.map(0x80000000,
                        0x80000000,
                        0x7FFFFFFF,
                        False)
        else:
            process.map(0x80000000,
                        0x80000000,
                        0x7FFFFFFF,
                        False)
        process.map(0x100000000,
                    0x100000000,
                    0x100000,
                    False)
        process.map(Addr(udspbase),
                    Addr(udspbase),
                    UpMemorySize,
                    False)
        process.map(Addr(udctrlbase),
                    Addr(udctrlbase),
                    UpCtrlSize,
                    False)
    
exit_event = Simulation.run(args, root, system, FutureClass, checkpoint_dir, cpt_starttick)


# cleanup post run
if(os.path.isdir(simdirpath)):
    shutil.rmtree(simdirpath,ignore_errors=True)
    print("Deleting %s simdata" % simdirpath)
