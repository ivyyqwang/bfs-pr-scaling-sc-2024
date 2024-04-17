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
sys.path.append('../../../ext/updown/udbasim/assembler')

from ruby import Ruby
from system.core import TunedCPU
from system.core import UnconstrainedCPU
import shutil
import re
import math
import pdb
from common import Options
import Simulation_multi as Simulation
import CacheConfig_node
import MemConfig_node
from common import CpuConfig
from common import ObjectList
from common.FileSystemConfig import config_filesystem
from common.Caches import *
from common.cpu2000 import *
from efa2bin import *
from efa2binall import *
import copy

def get_processes_gen(args, nnodes, ncpus):
    """Interprets provided args for UD and returns a list of processes"""

    multiprocesses = []
    inputs = []
    outputs = []
    errouts = []
    pargs = []
    tprocs = nnodes * ncpus

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
            if args.replicate_cli:
                process.cmd = [wrkld] + parg[0].split() + [i] 
            else:
                process.cmd = [wrkld] + parg[idx].split() + [i]
        else:
            process.cmd = [wrkld]

        if len(inputs) > idx:
            process.input = inputs[idx]
        if len(outputs) > idx:
            process.output = outputs[idx]
        if len(errouts) > idx:
            process.errout = errouts[idx]

        print(process.cmd)
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
    segments = []
    start_addr = seg_start
    i = 0
    while start_addr + block_size <= seg_start + seg_size: 
        segments.append((start_addr, start_addr + block_size))
        start_addr += block_size
        #i = (i + 1) % nparts
    #print('Segment Addresses')
    #print(segments)
    return segments

def calc_size(size, size_str):
    if size_str == "MB":
        return int((2**(20+math.log(int(size),2))))
    elif size_str == "GB":
        return int((2**(30+math.log(int(size),2))))
    elif size_str == "KB":
        return int((2**(10+math.log(int(size),2))))


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
            "NUM_STACKS_CAPACITY" : 1,
            "BASE_MAPPED_GLOBAL_ADDR" : 0x200000000,
            "BASE_MAPPED_ADDR" : 0x80000000,
            "BASE_SYNC_SPACE" : 0x7FFF0000,
            "DEF_MAPPED_SIZE" : 0x200000000,
            "DEF_GMAPPED_SIZE" : 0x80000000
            }
    fd = open(cfg_file, "r")
    file_lines = fd.readlines()
    g5def = 1
    for line in file_lines:
        lineitems = line.split()
        if(len(lineitems) > 0):
            if(g5def == 1 and lineitems[0] == "#else"):
                g5def = 0
            if(g5def == 0 and lineitems[0] == "#else"):
                g5def = 1
            if(lineitems[0] == "#ifndef"):
                if(lineitems[1] == "GEM5_MODE"):
                    g5def = 0
            if(lineitems[0] == "#ifdef"):
                if(lineitems[1] == "GEM5_MODE"):
                    g5def = 1
            if(lineitems[0] == "#define" and g5def == 1):
                keyval = lineitems[1]
                if keyval in config.keys():
                    if keyval == "DEF_MAPPED_SIZE" or keyval == "DEF_GMAPPED_SIZE":
                        oper = ""
                        for i in range(2, len(lineitems)):
                            if lineitems[i] == "1UL":
                                lineitems[i] = 1
                            oper += str(lineitems[i])
                        print(f"Eval:{oper}")
                        config[keyval] = eval(oper)
                    elif(lineitems[2][0:2] == "0x"):
                        config[keyval] = int(lineitems[2], 16)
                    else:
                        config[keyval] = int(lineitems[2])
    return config

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
parser.add_argument("--upmem-channels", type=int, default=8)
parser.add_argument("--lm_mode", type=int, default=1)
parser.add_argument("--suffix", type=str, default="simdata")
parser.add_argument("--logfile", type=str, default=None)
parser.add_argument("--udconfig-file", type=str, default="ext/updown/runtime/include/updown_config.h")
parser.add_argument("--updown-perf-log", action="store_true")
parser.add_argument("--updown-perf-log-internal", action="store_true")
parser.add_argument("--print-level", type=int, default=5)
parser.add_argument("--print-threshold", type=int, default=0)
parser.add_argument("--recode", action="store_true")
parser.add_argument("--num-iud-channels", type=int, default=8)
parser.add_argument("--num-istack-channels", type=int, default=8)
parser.add_argument("--num-inode-channels", type=int, default=8)
parser.add_argument("--stack-mem-size", type=str, default="16GB")
parser.add_argument("--gseg-block-size", type=str, default="64MB")
parser.add_argument("--lseg-block-size", type=str, default="16MB")
parser.add_argument("--num-lanes", type=int)
parser.add_argument("--use-pyemul", action="store_true")
parser.add_argument("--num-uds", type=int)
parser.add_argument("--num-stacks", type=int)
parser.add_argument("--num-nodes", type=int)
parser.add_argument("--replicate-cli", action="store_true")
parser.add_argument("--lmbanksize", type=int)
parser.add_argument("--mem-lat", type=int, default=10, help='Latency in cycles')
parser.add_argument("--ud-ud-lat", type=str, default='5ns', help='UD-UD (cluster) Latency')
parser.add_argument("--cl-cl-lat", type=str, default='', help='UD-UD (node) Latency')
parser.add_argument("--node-node-lat", type=str, default='', help='UD-UD (global) Latency')


                        #default="/opt/riscv/riscv64-unknown-elf/bin/pk b.o")
parser.add_argument("--l3cache", action="store_true",
                        dest="l3cache",
                        help="Include L3Cache")
if '--ruby' in sys.argv:
    Ruby.define_options(parser)

args = parser.parse_args()
if args.logfile:
    sys.stdout = open(args.logfile, 'w')
    sys.stderr = sys.stdout

cfg = parse_config(args.udconfig_file)

# Setup system configs
nlanes = args.num_lanes if args.num_lanes else cfg["DEF_NUM_LANES"]
nuds = args.num_uds if args.num_uds else cfg["DEF_NUM_UDS"]
nstacks = args.num_stacks if args.num_stacks else cfg["DEF_NUM_STACKS"]
nnodes = args.num_nodes if args.num_nodes else cfg["DEF_NUM_NODES"]
lmbanksize = args.lmbanksize if args.lmbanksize else cfg["DEF_SPMEM_BANK_SIZE"]
gseg_start = cfg["BASE_MAPPED_GLOBAL_ADDR"]
lseg_start = cfg["BASE_MAPPED_ADDR"]
lock_start = cfg["BASE_SYNC_SPACE"]
lock_size = lseg_start-lock_start
gsize = cfg["DEF_GMAPPED_SIZE"]
lsize = cfg["DEF_MAPPED_SIZE"]
np = args.num_cpus
nc = args.upmem_channels
#nud_channels = args.num_iud_channels
nud_channels = 8
node_ports = 4
mem_lat_half = int(args.mem_lat/2)

# Print system parsed and to be setup
print("NODES:%d, STACKS:%d, UDS:%d, LMSIZE:%d, CPUS:%d " % (nnodes, nstacks, nuds, lmbanksize, np))
print(f"lseg_block:{args.lseg_block_size}, gseg_block:{args.gseg_block_size}")
print(f"Memory Latency set to {args.mem_lat}")
# Setup memory
msize = re.findall(r'\d+', args.stack_mem_size)
gbsize = re.findall(r'\d+', args.gseg_block_size)
lbsize = re.findall(r'\d+', args.lseg_block_size)
gbsize_str = re.findall(r'\D+', args.gseg_block_size)
lbsize_str = re.findall(r'\D+', args.lseg_block_size)
numGBbits = math.log2(int(msize[0])) 
stack_size = int(2**(30 + numGBbits))
node_size = int(stack_size * nstacks)
numbits = int(math.log2(int(node_size)) )
print(f'Stack Size:{stack_size}, Node Size:{node_size}')
node_addr = [(int(i*node_size), int((i+1)*node_size)) for i in range(nnodes)]

block_size = calc_size(lbsize[0],lbsize_str[0]) # Interleave stacks at huge page size for now?
gblock_size = calc_size(gbsize[0], gbsize_str[0])

#gsize = int(2**(30 + math.log2(int(gsize[0]))))
print(f'Global Segment Start:{gseg_start}, Global Segment Size:{gsize}, Global Segment Block size"{gblock_size}')
print(f'Local Segment Start:{lseg_start}, Local Segment Size:{lsize} Local segment block size:{block_size}')
print("Calculating Global Segment Addresses for each node")
node_segs = segment_manager(nstacks, lseg_start, lsize, block_size)
node_global_segs = segment_manager(nnodes*nstacks, gseg_start, gsize, gblock_size)
print(f'No of local segment blocks in Node 0 - {len(node_segs)}')
print(f'No of global segment blocks in Node 0 - {len(node_global_segs)}')
node_addr = []
ud_sp_addr = []
ud_ctrl_addr = []
node_ud_sp_addr = []
node_ud_ctrl_addr = []
node_gseg_addr = []
ud_sp_size = lmbanksize*nlanes # [*2 to allow for in_stream addressing]
ud_ctrl_size = nlanes*32 # [*2 to allow for in_stream addressing]
total_ud_memory_size = nnodes * nstacks * nuds * ud_sp_size # Total scratchpad segment size
total_ud_ctrl_size = nnodes * nstacks * nuds * ud_ctrl_size # Total scratchpad segment size
if total_ud_ctrl_size < 4096:
    total_ud_ctrl_size = 4096
print(f"Total CTRLSIze{total_ud_ctrl_size}")
ud_sp_base_addr = cfg["BASE_SPMEM_ADDR"]
ud_ctrl_base_addr = cfg["BASE_CTRL_ADDR"]
intlv_bits = int(math.log(nc, 2))
#intlv_bits = 3

cluster_latency = 10 #* 16
node_latency =20 #* 16
inter_node_latency = 1000

# Set up the system
mainsys = SuperSystem()
systems = [None for x in range(nnodes)]

multiprocesses = []
numThreads = 1

if args.cmd:
    #multiprocesses, numThreads = get_processes(args)
    multiprocesses, numThreads = get_processes_gen(args, nnodes, np)
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

if args.cmd:
    #multiprocesses, numThreads = get_processes(args)
    multiprocesses, numThreads = get_processes_gen(args, nnodes, np)
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


switch_clk_domain = SrcClockDomain(clock =  '16GHz',
                                       voltage_domain = VoltageDomain(voltage = args.sys_voltage))

# Decoupling Memory controller from switch / cpu / UD clk domains
# when moving to HBM3 this can be moved back to 2GHz to get 1.1GB/sec
mem_clk_domain = SrcClockDomain(clock =  '900MHz',
                                       voltage_domain = VoltageDomain(voltage = args.sys_voltage))



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
                    mem_ranges = (node_addr[i]),
                    cache_line_size = args.cacheline_size,
                    m5ops_base = node_addr[i].start + Addr(0x1ffff0000),
                    mmap_using_noreserve = True)
    else:
        systems[i] = System(cpu = [AtomicSimpleCPU(cpu_id=i) for i in range(np)],
                    mem_mode = 'atomic',
                    mem_ranges = (node_addr[i]),
                    m5ops_base = node_addr[i].start + Addr(0x1ffff0000),
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
    # Suffix is not required anymore
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
        nwid = (0xffffffff) & (((i << 11) & 0x7fff800) |
                    ((int(ud / nuds) <<8) & 0x700) |
                    ((int(ud % nuds) << 6) & 0xC0))
        if args.use_pyemul:
            upobj=UpDownObj(latency=1,
                addrRange=ud_sp_addr[i*nuds_pnode + ud],
                ctrladdrRange=ud_ctrl_addr[i*nuds_pnode + ud],
                ctrlAddrBase=ud_ctrl_base_addr,
                numlanes=nlanes,
                efa=args.efa,
                simdir=simdir,
                lm_mode=args.lm_mode,
                recode=args.recode,
                upmem_channels=args.upmem_channels,
                iud_channels=nud_channels,
                lmsize=lmbanksize,
                progfile=args.progfile,
                print_level=args.print_level,
                print_threshold=args.print_threshold,
                perf_log_enable=args.updown_perf_log,
                perf_log_internal_enable=args.updown_perf_log_internal,
                pa_base=node_addr[i].start,
                udidx=ud,
                nwid=nwid,
                lseg_block_size=block_size,
                lseg_start=lseg_start,
                lseg_size=lsize,
                gseg_block_size=gblock_size,
                gseg_start=gseg_start,
                gseg_size=gsize,
                num_stacks=nstacks,
                num_uds=nuds,
                num_nodes=nnodes, 
                stack_size=stack_size,
            )   
        else:
            upobj=UpDownBASim(latency=1,
                addrRange=ud_sp_addr[i*nuds_pnode + ud],
                ctrladdrRange=ud_ctrl_addr[i*nuds_pnode + ud],
                ctrlAddrBase=ud_ctrl_base_addr,
                numlanes=nlanes,
                efa=args.efa,
                simdir=simdir,
                lm_mode=args.lm_mode,
                recode=args.recode,
                upmem_channels=args.upmem_channels,
                iud_channels=nud_channels,
                lmsize=lmbanksize,
                progfile=args.progfile,
                print_level=args.print_level,
                print_threshold=args.print_threshold,
                perf_log_enable=args.updown_perf_log,
                perf_log_internal_enable=args.updown_perf_log_internal,
                pa_base=node_addr[i].start,
                nwid=nwid,
                lseg_block_size=block_size,
                lseg_start=lseg_start,
                lseg_size=lsize,
                gseg_block_size=gblock_size,
                gseg_start=gseg_start,
                gseg_size=gsize,
                num_stacks=nstacks,
                num_uds=nuds,
                num_nodes=nnodes, 
                stack_size=stack_size,
            )
        updowns.append(upobj)
    systems[i].updown=updowns
    #systems[i].membus = [CoherentStackXBar(frontend_latency=mem_lat_half, forward_latency=mem_lat_half, response_latency=2, snoop_response_latency=2, width=4096) for x in range(nstacks)]
    systems[i].membus = [CoherentStackXBar(intlv_bits=intlv_bits, intlv_low_bit=7, frontend_latency=mem_lat_half, forward_latency=mem_lat_half,response_latency=2, snoop_response_latency=2, width=4096) for x in range(nstacks)]
    systems[i].clxbar = [CLXBar(ctrl_base_addr = node_ud_ctrl_addr[i].start + ud_ctrl_size*x*nuds,
                                  ctrl_addr_size = ud_ctrl_size,
                                  sp_base_addr = node_ud_sp_addr[i].start + ud_sp_size*x*nuds,
                                  sp_addr_size = ud_sp_size*nuds,
                                  stack_base_addr = node_addr[i].start + stack_size*x,
                                  stack_addr_size = stack_size,
                                  node_ctrl_base = node_ud_ctrl_addr[0].start,
                                  node_mem_base = node_addr[0].start,
                                  node_sp_base = node_ud_sp_addr[0].start,
                                  nodes = nnodes,
                                  node_id = i,
                                  nuds = nuds,
                                  clusters = nstacks,
                                  cluster_id = x,
                                  num_channels = 1,
                                  clk_domain=switch_clk_domain) 
                         for x in range(nstacks)]
    systems[i].interxbar = [CPUXBar(ctrl_base_addr = node_ud_ctrl_addr[i].start + ud_ctrl_size*x*nuds,
                                  ctrl_addr_size = ud_ctrl_size*nuds,
                                  sp_base_addr = node_ud_sp_addr[i].start + ud_sp_size*x*nuds,
                                  sp_addr_size = ud_sp_size*nuds,
                                  stack_base_addr = node_addr[i].start + stack_size*x,
                                  stack_addr_size = stack_size,
                                  node_ctrl_base = node_ud_ctrl_addr[0].start,
                                  node_mem_base = node_addr[0].start,
                                  node_sp_base = node_ud_sp_addr[0].start,
                                  nodes = nnodes,
                                  node_id = i,
                                  clusters = nstacks,
                                  cluster_id = x,
                                  num_channels = 1,
                                  clk_domain=switch_clk_domain) 
                          for x in range(nstacks)]

    MemClass = Simulation.setMemClass(args)
    print(MemClass)
    MemConfig_node.config_mem(args, systems[i], nc, nstacks)
    print(f"No of mem_ctrls{len(systems[i].mem_ctrls)}")
    CacheConfig_node.config_cache(args, systems[i], np, nuds, nstacks, AddrRange(0, nnodes*node_size), 1)
    #bridge between CPUs and the memory subsystem crossbars
    cpubridges =[]
    node_base_sp = ud_sp_base_addr + i*ud_sp_size*nuds*nstacks
    node_base_ctrl = ud_ctrl_base_addr + i*ud_ctrl_size*nuds*nstacks
    node_base_stack = node_addr[0].start + i*stack_size*nstacks
    for j in range(nstacks):
        for k in range(np):
            lranges=[]
            lranges.append(AddrRange(node_base_sp + j* ud_sp_size*nuds, node_base_sp + (j+1)*ud_sp_size*nuds))
            lranges.append(AddrRange(node_base_ctrl + j* ud_ctrl_size*nuds, node_base_ctrl + (j+1)*ud_ctrl_size*nuds))
            cpubridges.append(Bridge(req_size=65536, resp_size=65536, ranges=(lranges), clk_domain=switch_clk_domain))
    systems[i].cpubridge=cpubridges
    # Adding bridges between clxbar and membus as well 
    clx2membridges = [] 
    for j in range(len(systems[i].mem_ctrls)):
        clx2membridges.append(Bridge(req_size=16384, resp_size=16384, ranges=systems[i].mem_ctrls[j].range, clk_domain=mem_clk_domain,delay='1ns'))
    systems[i].clx2membridges = clx2membridges         
   
    #bridge between clusters and bridge between clx and inter xbars
    clx2ibridges = [] 
    i2clxbridges = [] 
    outofnoderange = []
    if nnodes > 1:
        for l in range(nnodes):
            if l != i:
                outofnoderange.append(AddrRange(ud_sp_base_addr + l * ud_sp_size * nuds * nstacks,
                                                ud_sp_base_addr + (l + 1) * ud_sp_size * nuds * nstacks))
                outofnoderange.append(AddrRange(ud_ctrl_base_addr + l * ud_ctrl_size * nuds * nstacks,
                                                ud_ctrl_base_addr + (l + 1) * ud_ctrl_size * nuds * nstacks))
                outofnoderange.append(AddrRange(node_addr[0].start + l * stack_size * nstacks, 
                                                node_addr[0].start + (l + 1) * stack_size * nstacks))
    
    for j in range(nstacks):
        clx2irange=copy.deepcopy(outofnoderange)
        i2clxrange=[]
        for k in range(nstacks):
            if j == k:
                i2clxrange.append(AddrRange(node_base_sp + k*ud_sp_size*nuds, node_base_sp + (k+1)*ud_sp_size*nuds))
                i2clxrange.append(AddrRange(node_base_ctrl + k*ud_ctrl_size*nuds, node_base_ctrl + (k+1)*ud_ctrl_size*nuds))
                i2clxrange.append(AddrRange(node_base_stack + k*stack_size, node_base_stack + (k+1)*stack_size))
            else:
                clx2irange.append(AddrRange(node_base_sp + k*ud_sp_size*nuds, node_base_sp + (k+1)*ud_sp_size*nuds))
                clx2irange.append(AddrRange(node_base_ctrl + k*ud_ctrl_size*nuds, node_base_ctrl + (k+1)*ud_ctrl_size*nuds))
                clx2irange.append(AddrRange(node_base_stack + k*stack_size, node_base_stack + (k+1)*stack_size))
        
        clx2ibridges.append(Bridge(req_size=16384, resp_size=16384, ranges=clx2irange, clk_domain=switch_clk_domain,delay='5ns'))
        i2clxbridges.append(Bridge(req_size=16384, resp_size=16384, ranges=i2clxrange, clk_domain=switch_clk_domain,delay='5ns'))
    systems[i].clx2ibridges=clx2ibridges
    systems[i].i2clxbridges=i2clxbridges
    if nstacks > 1:
        i2ibridges =[]
        for j in range(nstacks):
            for k in range(nstacks-1):
            # cluster out bridge 
                lranges=[]
                lranges.append(AddrRange(node_base_sp + j*ud_sp_size*nuds, node_base_sp + (j+1)*ud_sp_size*nuds))
                lranges.append(AddrRange(node_base_ctrl + j*ud_ctrl_size*nuds, node_base_ctrl + (j+1)*ud_ctrl_size*nuds))
                lranges.append(AddrRange(node_base_stack + j*stack_size, node_base_stack + (j+1)*stack_size))
                i2ibridges.append(Bridge(req_size=16384, resp_size=16384, ranges=lranges, clk_domain=switch_clk_domain,delay='0.2ns'))
        systems[i].i2ibridge=i2ibridges
        
        # cluster in bridge 

    l = [0 for x in range(nstacks)]
    for j in range(nuds_pnode):
        systems[i].updown[j].cpu_side = systems[i].clxbar[int(j/nuds)].mem_side_ports
        for k in range(nc):
            systems[i].updown[j].mem_side[k] = systems[i].clxbar[int(j/nuds)].ud_in_ports
        for k in range(nud_channels):
            systems[i].updown[j].udout_side[k] = systems[i].clxbar[int(j/nuds)].ud_in_ports
    for j in range(nstacks):
        for k in range(nc):
            systems[i].clxbar[j].mem_side_ports = systems[i].clx2membridges[j*nc + k].cpu_side_port
            systems[i].clx2membridges[j*nc + k].mem_side_port = systems[i].membus[j].cpu_side_ports[k]
        for k in range(np):
            systems[i].cpubridge[j*np+k].cpu_side_port = systems[i].cpu[k].l1xbar.mem_side_ports
            systems[i].interxbar[j].cpu_in_ports = systems[i].cpubridge[j*np+k].mem_side_port
        systems[i].clxbar[j].cpu_in_ports = systems[i].i2clxbridges[j].mem_side_port
        systems[i].i2clxbridges[j].cpu_side_port = systems[i].interxbar[j].mem_side_ports
        systems[i].clxbar[j].mem_side_ports = systems[i].clx2ibridges[j].cpu_side_port
        systems[i].clx2ibridges[j].mem_side_port = systems[i].interxbar[j].clx_in_ports
        for k in range(nstacks):
            if j != k:
                systems[i].interxbar[j].mem_side_ports = systems[i].i2ibridge[k*(nstacks-1) + l[k]].cpu_side_port
                systems[i].i2ibridge[k*(nstacks-1) + l[k]].mem_side_port = systems[i].interxbar[k].cpu_side_ports
                l[k] += 1
    
    config_filesystem(systems[i], args)
    systems[i].workload = SEWorkload.init_compatible(mp0_path)
    systems[i].system_port = systems[i].membus[0].cpu_side_ports[nc]

    if args.wait_gdb:
        systems[i].workload.wait_for_remote_gdb = True

outranges=[]
inranges=[]
if nnodes > 1:
    for i in range(nnodes):
        lranges=[]
        rranges=[]
        for k in range(nnodes):
            if i != k:
                lranges.append(AddrRange(ud_sp_base_addr + k*ud_sp_size*nuds*nstacks, ud_sp_base_addr + (k+1)*ud_sp_size*nuds*nstacks))
                lranges.append(AddrRange(ud_ctrl_base_addr + k*ud_ctrl_size*nuds*nstacks, ud_ctrl_base_addr + (k+1)*ud_ctrl_size*nuds*nstacks))
                lranges.append(AddrRange(node_addr[0].start + k*stack_size*nstacks, node_addr[0].start + (k+1)*stack_size*nstacks))
            else: 
                rranges.append(AddrRange(ud_sp_base_addr + k*ud_sp_size*nuds*nstacks, ud_sp_base_addr + (k+1)*ud_sp_size*nuds*nstacks))
                rranges.append(AddrRange(ud_ctrl_base_addr + k*ud_ctrl_size*nuds*nstacks, ud_ctrl_base_addr + (k+1)*ud_ctrl_size*nuds*nstacks))
                rranges.append(AddrRange(node_addr[0].start + k*stack_size*nstacks, node_addr[0].start + (k+1)*stack_size*nstacks))
        outranges.append(lranges)
        inranges.append(rranges)
    print(outranges)
    for i in range(nnodes):
        systems[i].nodexbar = NodeXBar(ctrl_base_addr = node_ud_ctrl_addr[0].start,
                                  ctrl_addr_size = ud_ctrl_size*nuds*nstacks,
                                  stack_base_addr = node_addr[0].start,
                                  stack_addr_size = node_size,
                                  sp_base_addr = node_ud_sp_addr[0].start,
                                  sp_addr_size = ud_sp_size*nuds*nstacks,
                                  nodes = nnodes,
                                  node_id = i,
                                  clk_domain=SrcClockDomain(clock =  '16GHz',
                                       voltage_domain = systems[i].voltage_domain)) 
        
        nodeinbridges =[]
        nodeoutbridges =[]
        node_base_sp = ud_sp_base_addr + i*ud_sp_size*nuds*nstacks
        node_base_ctrl = ud_ctrl_base_addr + i*ud_ctrl_size*nuds*nstacks
        node_base_stack = node_addr[0].start + i*stack_size*nstacks
        for j in range(nstacks):
            # CPU-NodeXBar Bridges 
            lranges=[]
            lranges.append(AddrRange(node_base_sp + j*ud_sp_size*nuds, node_base_sp + (j+1)*ud_sp_size*nuds))
            lranges.append(AddrRange(node_base_ctrl + j*ud_ctrl_size*nuds, node_base_ctrl + (j+1)*ud_ctrl_size*nuds))
            lranges.append(AddrRange(node_base_stack + j*stack_size, node_base_stack + (j+1)*stack_size))
            nodeinbridges.append(Bridge(req_size=16384, resp_size=16384, ranges=lranges, clk_domain=switch_clk_domain,delay='10ns'))
        for j in range(nstacks):
            nodeoutbridges.append(Bridge(req_size=16384, resp_size=16384, ranges=outranges[i], clk_domain=switch_clk_domain,delay='10ns'))
        systems[i].nodeinbridge=nodeinbridges 
        systems[i].nodeoutbridge=nodeoutbridges 
        
        for k in range(nstacks):
            systems[i].nodexbar.cpu_in_ports[k] = systems[i].nodeoutbridge[k].mem_side_port
            systems[i].nodeoutbridge[k].cpu_side_port = systems[i].interxbar[k].mem_side_ports
            systems[i].nodexbar.mem_side_ports = systems[i].nodeinbridge[k].cpu_side_port
            systems[i].nodeinbridge[k].mem_side_port = systems[i].interxbar[k].cpu_side_ports
        
    mainsys.sysbar = SysXBar(ctrl_base_addr = node_ud_ctrl_addr[0].start,
                                  ctrl_addr_size = ud_ctrl_size*nuds*nstacks,
                                  stack_base_addr = node_addr[0].start,
                                  stack_addr_size = node_size,
                                  sp_base_addr = node_ud_sp_addr[0].start,
                                  sp_addr_size = ud_sp_size*nuds*nstacks,
                                  nodes = nnodes,
                                  node_id = i,
                                  numPorts = 4, 
                                  clk_domain=SrcClockDomain(clock =  '16GHz',
                                       voltage_domain = systems[i].voltage_domain)) 
    sysinbridges = []
    sysoutbridges = []
    bits_to_use = math.log(node_ports, 2)
    low_bit = 7
    for i in range(nnodes):
        for j in range(node_ports):
            local_inranges=[]
            local_outranges=[]
            for r in inranges[i]:
                start = int(r.start)
                size = int(r.end - r.start)
                arange = m5.objects.AddrRange(m5.objects.Addr(start), size = size,
                                                        intlvHighBit = \
                                                        low_bit + bits_to_use - 1,
                                                        xorHighBit = 0,
                                                        intlvBits = bits_to_use,
                                                        intlvMatch = j)
                local_inranges.append(arange)
            for r in outranges[i]:
                start = int(r.start)
                size = int(r.end - r.start)
                arange = m5.objects.AddrRange(m5.objects.Addr(start), size = size,
                                                        intlvHighBit = \
                                                        low_bit + bits_to_use - 1,
                                                        xorHighBit = 0,
                                                        intlvBits = bits_to_use,
                                                        intlvMatch = j)
                local_outranges.append(arange)
            
            sysinbridges.append(Bridge(req_size=65536, resp_size=65536, ranges=local_inranges, clk_domain=switch_clk_domain,delay='256ns'))
            sysoutbridges.append(Bridge(req_size=65536, resp_size=65536, ranges=local_outranges, clk_domain=switch_clk_domain,delay='256ns'))
    mainsys.sysinbridges = sysinbridges
    mainsys.sysoutbridges = sysoutbridges
    
    for i in range(nnodes):
        for j in range(node_ports):
            systems[i].nodexbar.node_in_ports = mainsys.sysinbridges[i*node_ports+j].mem_side_port
            mainsys.sysinbridges[i*node_ports+j].cpu_side_port = mainsys.sysbar.mem_side_ports
            systems[i].nodexbar.mem_side_ports = mainsys.sysoutbridges[i*node_ports+j].cpu_side_port
            mainsys.sysoutbridges[i*node_ports+j].mem_side_port = mainsys.sysbar.node_in_ports

##mainsys.workload = SEWorkload.init_compatible(mp0_path)
mainsys.voltage_domain = VoltageDomain(voltage = args.sys_voltage)
mainsys.clk_domain = SrcClockDomain(clock =  args.sys_clock,
                                   voltage_domain = mainsys.voltage_domain)

mainsys.systems = systems
root = (Root(full_system = False, system = mainsys))
checkpoint_dir = None
cpt_starttick = 0

Simulation.initialize(args, root, mainsys, FutureClass, np ,nstacks, nuds)
print("Finished Initialization")
## Mapping UpStream memory to the process
print("Map Processes", flush=True)    
if not(args.checkpoint_restore):
    gseg_pa_start = lseg_start + int(lsize/nstacks)
    for i, process in enumerate(multiprocesses):
        base_phys = int(i / np) << numbits
        print(f'Process:{i} Node:{int(i / np)}, base_phys:{base_phys:#x}')
        for j, addr in enumerate(node_segs):
            va_start = addr[0]
            size = block_size
            pa_start = lseg_start + base_phys + (int(j/nstacks)*block_size) + ((j%nstacks) * stack_size)
            print(f'VA:{va_start:x} PA:{pa_start:x}, size:{size}')
            process.map(va_start,
                        pa_start,
                        size,
                        False)
        for j, addr in enumerate(node_global_segs):
            va_start = addr[0]
            size = gblock_size
            pa_start = gseg_pa_start + int(j / (nstacks*nnodes))*gblock_size + (j%(nstacks*nnodes))*stack_size 
            print(f'VA:{va_start:x} PA:{pa_start:x}, size:{size}')
            process.map(va_start,
                        pa_start,
                        size,
                        False)
        print(f'Process:{i} Segments mapped')
        process.map(Addr(lock_start),
                    Addr(lock_start),
                    lock_size,
                    False)
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
