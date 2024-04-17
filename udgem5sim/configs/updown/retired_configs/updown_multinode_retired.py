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
import re
import math
from common import Options
import Simulation_multi as Simulation
import CacheConfig_node
import MemConfig_node
from common import CpuConfig
from common import ObjectList
from common.FileSystemConfig import config_filesystem
from common.Caches import *
from common.cpu2000 import *

def get_processes_gen(args, nstacks, nnodes, nuds):
    """Interprets provided args for UD and returns a list of processes"""

    multiprocesses = []
    inputs = []
    outputs = []
    errouts = []
    pargs = []
    tprocs = nstacks * nuds * nnodes

    workload = args.cmd.split(';')
    workloads = [workload[0] for x in range(tprocs)]
    if args.input != "":
        inputs = args.input.split(';')
    if args.output != "":
        outputs = args.output.split(';')
    if args.errout != "":
        errouts = args.errout.split(';')
    if args.options != "":
        parg = args.options.split(';')
        pargs = [parg for x in range(tprocs)]
        

    idx = 0
    for i, wrkld in enumerate(workloads):
        process = Process(pid = 100 + idx)
        process.executable = wrkld
        process.cwd = os.getcwd()

        if args.env:
            with open(args.env, 'r') as f:
                process.env = [line.rstrip() for line in f]

        if len(pargs) > idx:
            #process.cmd = [wrkld] + parg[0].split() + [i % (nuds*nstacks)] 
            process.cmd = [wrkld] + parg[0].split() + [i] 
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

# Use this for nodes and stacks
def segment_manager(nparts, seg_start, seg_size, block_size):
    segments = [[] for i in range(nparts)]
    start_addr = seg_start
    i = 0
    while start_addr + block_size <= seg_start + seg_size: 
        segments[i].append((start_addr, start_addr + block_size - 1))
        start_addr += block_size
        i = (i + 1) % nparts
    print('Segment Addresses')
    return segments

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

import pdb
#pdb.set_trace()

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
parser.add_argument("--updown-perf-log", type=str, default=None)
parser.add_argument("--updown-perf-log-internal", action="store_true")
parser.add_argument("--print-level", type=int, default=5)
parser.add_argument("--recode", action="store_true")
parser.add_argument("--num-uds", type=int, default=1)
parser.add_argument("--num-iud-channels", type=int, default=8)
parser.add_argument("--num-istack-channels", type=int, default=8)
parser.add_argument("--num-inode-channels", type=int, default=8)
parser.add_argument("--stack-mem-size", type=str, default="32GB")
parser.add_argument("--gseg-size", type=str, default="2GB")
parser.add_argument("--gseg-start-addr", type=int, default=0x80000000)


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

cfg = parse_config(args.udconfig_file)

args.num_cpus = cfg["DEF_NUM_UDS"] * cfg["DEF_NUM_STACKS"] #* cfg["DEF_NUM_NODES"]
np = args.num_cpus #* cfg["DEF_NUM_NODES"]
nc = args.upmem_channels
nud_channels = args.num_iud_channels
nlanes = cfg["DEF_NUM_LANES"]
lmbanksize = cfg["DEF_SPMEM_BANK_SIZE"]
nuds = cfg["DEF_NUM_UDS"]
nstacks = cfg["DEF_NUM_STACKS"]
nnodes = cfg["DEF_NUM_NODES"]
print("NODES:%d, STACKS:%d, UDS:%d, CPUS:%d" % (nnodes, nstacks, nuds, np))
mainsys = SubSystem()
systems = [None for x in range(nnodes)]

multiprocesses = []
numThreads = 1

if args.cmd:
    #multiprocesses, numThreads = get_processes(args)
    multiprocesses, numThreads = get_processes_gen(args, nstacks, nnodes, nuds)
else:
    print("No workload specified. Exiting!\n", file=sys.stderr)
    sys.exit(1)

(CPUClass, test_mem_mode, FutureClass) = Simulation.setCPUClass(args)
CPUClass.numThreads = numThreads

# Check -- do not allow SMT with multiple CPUs
if args.smt and args.num_cpus > 1:
    fatal("You cannot use SMT with multiple CPUs!")

"""
 Using the Skylake Config from 
"""
msize = re.findall(r'\d+', args.stack_mem_size)
gsize = re.findall(r'\d+', args.gseg_size)
numGBbits = math.log2(int(msize[0])) 
stack_size = int(2**(30 + numGBbits))
node_size = int(stack_size * nstacks)
numbits = int(math.log2(int(node_size)) )
print(f'Stack Size:{stack_size}, Node Size:{node_size}')
#node_stack_addr = [(int(i*stack_size), int((i+1)*stack_size)) for i in range(nstacks)]
node_addr = [(int(i*node_size), int((i+1)*node_size)) for i in range(nnodes)]
block_size = 2**26 # Interleave stacks at huge page size  to be changed if not correct later maybe input param? 64MB per node? --> 64/8 = 8MB or 4 huge pages per stack? 
gseg_start = int(args.gseg_start_addr)
gsize = int(2**(30 + math.log2(int(gsize[0]))))
print(f'Global Segment Start:{gseg_start}, Global Segment Size:{gsize}')
print("Calculating Global Segment Addresses for each node")
node_segs = segment_manager(nnodes, gseg_start, gsize, block_size)
print(f'No of global segment blocks in Node 0 - {len(node_segs[0])}')
node_addr = []
ud_sp_addr = []
ud_ctrl_addr = []
node_ud_sp_addr = []
node_ud_ctrl_addr = []
node_gseg_addr = []

# Create an instantiation of the simobject
ud_sp_size = lmbanksize*nlanes # [*2 to allow for in_stream addressing]
ud_ctrl_size = nlanes*32 # [*2 to allow for in_stream addressing]

total_ud_memory_size = nnodes * nstacks * nuds * ud_sp_size # Total scratchpad segment size
total_ud_ctrl_size = nnodes * nstacks * nuds * ud_ctrl_size # Total scratchpad segment size

ud_sp_base_addr = cfg["BASE_SPMEM_ADDR"]
ud_ctrl_base_addr = cfg["BASE_CTRL_ADDR"]




for i in range(nnodes):
    start_addr = (i << (numbits)) | 0x0
    end_addr = (i << numbits) | ((node_size & 0xffffffffffffffff) - 1)
    #start_addr = 0x0
    #end_addr = (node_size & 0xffffffffffffffff) - 1
    print(f'i:{i}, i<<{numbits}:{i<<numbits}, Start:{start_addr}, End:{end_addr}')
    node_addr.append(AddrRange(start_addr, end_addr))
    start_addr = ud_sp_base_addr + i*nuds*nstacks*ud_sp_size
    end_addr = ud_sp_base_addr + (i+1 )*nuds*nstacks*ud_sp_size
    node_ud_sp_addr.append(AddrRange(start_addr, end_addr))
    start_addr = ud_ctrl_base_addr + i*nuds*nstacks*ud_ctrl_size
    end_addr = ud_ctrl_base_addr + (i+1 )*nuds*nstacks*ud_ctrl_size
    node_ud_ctrl_addr.append(AddrRange(start_addr, end_addr))
    
    for j in range(nuds * nstacks * nnodes):
        ud_sp_addr.append(AddrRange(start = Addr(ud_sp_base_addr + j * ud_sp_size),
                    end=Addr(ud_sp_base_addr + (j + 1) * ud_sp_size)))
        ud_ctrl_addr.append(AddrRange(start = Addr(ud_ctrl_base_addr + j* ud_ctrl_size),
                    end=Addr(ud_ctrl_base_addr + (j+1)* ud_ctrl_size)))
    
for i in range(nnodes):
    gseg_start_addr = (i << numbits) | 0x0
    gseg_end_addr = (i << numbits) + 0x7fffffff
    node_gseg_addr.append(AddrRange(gseg_start_addr, gseg_end_addr))

mp0_path = multiprocesses[0].executable
#roots=[]
for i in range(nnodes):
    if not args.fast_forward:
        systems[i] = System(cpu = [TunedCPU(cpu_id=i) for i in range(np)],
                    mem_mode = 'timing',
                    #mem_ranges = (node_addr[i],node_gseg_addr[i]),
                    mem_ranges = (node_addr[i]),
                    cache_line_size = args.cacheline_size,
                    m5ops_base = node_addr[i].start + Addr(0x1ffff0000),
                    mmap_using_noreserve = True)
    else:
        systems[i] = System(cpu = [AtomicSimpleCPU(cpu_id=i) for i in range(np)],
                    mem_mode = 'atomic',
                    #mem_ranges = (node_addr[i],node_gseg_addr[i]),
                    mem_ranges = (node_addr[i]),
                    m5ops_base = node_addr[i].start + Addr(0x1ffff0000),
                    #mem_ranges = [AddrRange(0, node_segs[0][0][0]),AddrRange(x) for x in node_segs[0]],
                    cache_line_size = args.cacheline_size,
                    mmap_using_noreserve=True)


    if numThreads > 1:
        systems[i].multi_thread = True

    # Create a top-level voltage domain
    systems[i].voltage_domain = VoltageDomain(voltage = args.sys_voltage)
    # Andronicus: Hardcoding sys_clock and cpu_clock here
    args.sys_clock = '2GHz'
    args.cpu_clock = '2GHz'
    # Create a source clock for the system and set the clock period
    systems[i].clk_domain = SrcClockDomain(clock =  args.sys_clock,
                                       voltage_domain = systems[i].voltage_domain)

    # Create a CPU voltage domain
    systems[i].cpu_voltage_domain = VoltageDomain()

    # Create a separate clock domain for the CPUs
    systems[i].cpu_clk_domain = SrcClockDomain(clock = args.cpu_clock,
                                           voltage_domain =
                                           systems[i].cpu_voltage_domain)

    # All cpus belong to a common cpu_clk_domain, therefore running at a common
    # frequency.
    for cpu in systems[i].cpu:
        cpu.clk_domain = systems[i].cpu_clk_domain

    if ObjectList.is_kvm_cpu(CPUClass) or ObjectList.is_kvm_cpu(FutureClass):
        if buildEnv['TARGET_ISA'] == 'x86':
            systems[i].kvm_vm = KvmVM()
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
    for j in range(np):
        if args.smt:
            systems[i].cpu[j].workload = multiprocesses
        elif len(multiprocesses) == 1:
            systems[i].cpu[j].workload = multiprocesses[0]
        else:
            systems[i].cpu[j].workload = multiprocesses[np*i + j]
        
        if args.simpoint_profile:
            systems[i].cpu[j].addSimPointProbe(args.simpoint_interval)
        systems[i].cpu[j].createThreads()

        if args.bp_type:
            bpClass = ObjectList.bp_list.get(args.bp_type)
            systems[i].cpu[j].branchPred = bpClass()

        if args.indirect_bp_type:
            indirectBPClass = \
                ObjectList.indirect_bp_list.get(args.indirect_bp_type)
            systems[i].cpu[j].branchPred.indirectBranchPred = indirectBPClass()

        systems[i].cpu[j].createThreads()

    # Create the memory mapping file and move it to the correct locations! 
    print("Progfile:%s, EFA:%s" %(args.progfile, args.efa))
    simdir="simdata"
    simdirpath=""
    if args.suffix:
        simdir = "simdata_" + args.suffix
        print("Using suffix %s for simdata" % simdir, flush=True)
        path = os.getcwd()
        simdirpath = os.path.join(path,simdir)
        if(not os.path.isdir(simdirpath)):
            print("%s created for simdata" % simdir)
            os.mkdir(simdirpath)

    nuds_pnode = nuds*nstacks
    updowns=[]
    for ud in range(nuds_pnode):
        nwid = (0xffffffff) & (((i << 11) & 0x7fff800)| ((int(ud/nuds) <<8) & 0x700) | ((int(ud%nuds) << 6) & 0xC0))
        upobj=UpDownObj(latency=1,
                addrRange=ud_sp_addr[i*nuds_pnode + ud],
                ctrladdrRange=ud_ctrl_addr[i*nuds_pnode + ud],
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
                perf_log_enable=0,
                perf_log_internal_enable=0,
                pa_base=node_addr[i].start,
                udidx=ud,
                nwid=nwid)
        updowns.append(upobj)
    systems[i].updown=updowns
    #systems[i].membus = [SystemXBar() for x in range(nstacks)]
    systems[i].membus = [StackXBar() for x in range(nstacks)]
    #systems[i].nodexbar = [StackXBar() for x in range(nstacks)]
    systems[i].clxbar = [NoncoherentXBar() for x in range(nstacks)]
    #systems[i].udxbar = [NoncoherentXBar() for x in range(nstacks)]
    systems[i].cpuxbar = [CPUXBar(ctrl_base_addr = node_ud_ctrl_addr[i].start + ud_ctrl_size*x*nuds,
                                  ctrl_addr_size = ud_ctrl_size*nuds,
                                  sp_base_addr = node_ud_sp_addr[i].start + ud_sp_size*x*nuds,
                                  sp_addr_size = ud_sp_size*nuds,
                                  stack_base_addr = node_addr[i].start + stack_size*x,
                                  stack_addr_size = stack_size,
                                  nodes = nnodes,
                                  node_id = i,
                                  clusters = nstacks,
                                  cluster_id = x
                                  ) 
                          for x in range(nstacks)]
    #for k in range(nstacks):
    #    systems[i].membus[k] = SystemXBar()
    #    systems[i].clxbar[k] = UDXBar()

    MemClass = Simulation.setMemClass(args)
    print(MemClass)
    systems[i].system_port = systems[i].membus[0].cpu_side_ports
    CacheConfig_node.config_cache(args, systems[i], np, nuds, nstacks, False)
    MemConfig_node.config_mem(args, systems[i], nc, nstacks)

    #system.updown.mem_side = system.membus.cpu_side_ports
    for j in range(nuds_pnode):
        systems[i].updown[j].cpu_side = systems[i].clxbar[int(j/nuds)].mem_side_ports
        for k in range(nc):
            systems[i].updown[j].mem_side[k] = systems[i].clxbar[int(j/nuds)].cpu_side_ports
        for k in range(nud_channels):
            #systems[i].updown[j].cpu_side = systems[i].clxbar[int(j/nuds)].mem_side_ports
            systems[i].updown[j].udout_side[k] = systems[i].clxbar[int(j/nuds)].cpu_side_ports
            #systems[i].updown[j].mem_side[k] = systems[i].membus[k].cpu_side_ports
        #for k in range(nud_channels):
        #    systems[i].updown[j].udin_side[k] = systems[i].clxbar[int(j/nuds)].mem_side_ports
        #    systems[i].updown[j].udout_side[k] = systems[i].clxbar[int(j/nuds)].cpu_side_ports
    for j in range(nstacks):
        for k in range(nuds_pnode):
            systems[i].cpuxbar[j].cpu_in_ports = systems[i].cpu[k].l1xbar.mem_side_ports
        #3for k in range(nstacks):
        #3    if j != k:
        #3        systems[i].cpuxbar[j].mem_side_ports = systems[i].cpuxbar[k].cpu_side_ports
        systems[i].clxbar[j].mem_side_ports = systems[i].membus[j].cpu_side_ports
        systems[i].clxbar[j].cpu_side_ports = systems[i].cpuxbar[j].mem_side_ports
        for k in range(nstacks):
            if j != k:
                systems[i].clxbar[j].mem_side_ports = systems[i].cpuxbar[k].cpu_side_ports
        #systems[i].clxbar[j].mem_side_ports = systems[i].cpuxbar[j].cpu_side_ports
            #    systems[i].clxbar[k].mem_side_ports = systems[i].nodexbar[j].cpu_side_ports
            #    systems[i].clxbar[k].cpu_side_ports = systems[i].nodexbar[j].mem_side_ports
    
    config_filesystem(systems[i], args)
    systems[i].workload = SEWorkload.init_compatible(mp0_path)

    if args.wait_gdb:
        systems[i].workload.wait_for_remote_gdb = True


#mainsys.sysbar = NoncoherentXBar()
#for i in range(nnodes):
#    for k in range(nstacks):
#        systems[i].cpuxbar[k].cpu_side_ports = mainsys.sysbar.mem_side_ports
#        systems[i].cpuxbar[k].mem_side_ports = mainsys.sysbar.cpu_side_ports
#
#
##mainsys.workload = SEWorkload.init_compatible(mp0_path)
#mainsys.voltage_domain = VoltageDomain(voltage = args.sys_voltage)
#mainsys.clk_domain = SrcClockDomain(clock =  args.sys_clock,
#                                   voltage_domain = mainsys.voltage_domain)

## Create a CPU voltage domain
#mainsys.cpu_voltage_domain = VoltageDomain()
#
## Create a separate clock domain for the CPUs
#mainsys.cpu_clk_domain = SrcClockDomain(clock = args.cpu_clock,
#                                       voltage_domain =
#                                       mainsys.cpu_voltage_domain)
mainsys.systems = systems
root = (Root(full_system = False, system = mainsys))
checkpoint_dir = None
cpt_starttick = 0

#for i in range(nnodes):
#    if(args.checkpoint_restore):
#        cpt_starttick, checkpoint_dir = Simulation.initialize(args, root, systems[i], FutureClass, np, nstacks, nuds)
#    else:
#        Simulation.initialize(args, root, systems[i], FutureClass, np ,nstacks, nuds)
Simulation.initialize(args, root, mainsys, FutureClass, np ,nstacks, nuds)
print("Finished Initialization")
## Mapping UpStream memory to the process
print("Map Processes", flush=True)    
if not(args.checkpoint_restore):
    for i, process in enumerate(multiprocesses):
        base_phys = int(i / nuds_pnode) << numbits
        print(f'Process:{i} Node:{int(i / nuds_pnode)}, base_phys:{base_phys:#x}')
        #base_phys = 0
        if(args.progfile=='GenPagerankEFA' or args.progfile=='GenPagerankMultiUDEFA'):
            process.map(0x80000000,
                        base_phys+0x80000000,
                        0x7FFFFFFF,
                        False)
        else:
            process.map(0x80000000,
                        base_phys+0x80000000,
                        0x7FFFFFFF,
                        False)
        #process.map(0x100000000,
        #            base_phys+0x100000000,
        #            0x100000,
        #            False)
        process.map(Addr(ud_sp_base_addr),
                    Addr(ud_sp_base_addr),
                    total_ud_memory_size,
                    False)
        process.map(Addr(ud_ctrl_base_addr),
                    Addr(ud_ctrl_base_addr),
                    total_ud_ctrl_size,
                    False)
#for i in range(nnodes):
exit_event = Simulation.run(args, root, mainsys, FutureClass, checkpoint_dir, cpt_starttick)


# cleanup post run
if(os.path.isdir(simdirpath)):
    shutil.rmtree(simdirpath,ignore_errors=True)
    print("Deleting %s simdata" % simdirpath)
