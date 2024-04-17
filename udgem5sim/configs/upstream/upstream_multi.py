""" Simple config/run script for the DownstreamObj

This file tests the integration with Spike through

"""

import argparse
import sys
import os
from email_status import *
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
from create_mem_mapping import *
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
    print("Num Workloads:%d" % len(workloads))
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


parser = argparse.ArgumentParser()
Options.addCommonOptions(parser)
Options.addSEOptions(parser)

parser.add_argument("--upstream-kernel", action="store",
                        type=str, dest="upstream",
                        help="upstream kernel to execute")
parser.add_argument("--efa", type=str,
                    help="EFA to load in upstream")
parser.add_argument("--progfile", type=str,
                    help="Progfile containing EFA")
parser.add_argument("--num-lanes", type=int, default=1)
parser.add_argument("--upmem-channels", type=int, default=8)
parser.add_argument("--lmbanksize", type=int, default=65536)
parser.add_argument("--lm_mode", type=int, default=0)
parser.add_argument("--suffix", type=str, default="simdata")
parser.add_argument("--statusmail", dest="statusmail",action='store_true')
parser.set_defaults(statusmail=False)
parser.add_argument("--logfile", type=str, default=None)
parser.add_argument("--updown-perf-log", action="store_true")
parser.add_argument("--updown-perf-log-internal", action="store_true")
parser.add_argument("--print-level", type=int, default=5)
parser.add_argument("--recode", action="store_true")


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
mp0_path = multiprocesses[0].executable
#system = System(cpu = [CPUClass(cpu_id=i) for i in range(np)],
"""
 Using the Skylake Config from 
"""
print(args.mem_size)
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
print(int(system.mem_ranges[0].end))
print(args.mem_size)


if numThreads > 1:
    system.multi_thread = True

# Create a top-level voltage domain
system.voltage_domain = VoltageDomain(voltage = args.sys_voltage)
# Andronicus: Hardcoding sys_clock and cpu_clock here
#if not args.sys_clock:
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
        print("Setting up CPU %d" % i)
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

# Create an instantiation of the simobject
# you created EndOfDRAM - EndOfDRAM + DSMemorySize
#UpMemorySize = 0xFF
#UpMemorySize = 0x10000F
nlanes = int(args.num_lanes)
print("NumLanes:%d" % nlanes)
lmbanksize = int(args.lmbanksize)
#UpMemorySize = lmbanksize*nlanes+1024
UpMemorySize = lmbanksize*nlanes*2+1024 # [*2 to allow for in_stream addressing]
print("Mapping Created\n")
# Create the memory mapping file and move it to the correct locations! 
#create_mapping(file_name, num_lanes, mapbase, upbase):
create_mapping("configs/upstream/upstream.h",nlanes, 0x80000000, int(system.mem_ranges[0].end), UpMemorySize)
#shutil.copy("./upstream.h", "src/upstream/upstream.h")
#shutil.copy("configs/upstream/upstream.h", "tests/test-progs/upstream-snap/src/tests/")
#UpMemorySize = 0x400500
#tot_mem_size = 0x100000000 + UpMemorySize
print("Progfile:%s, EFA:%s" %(args.progfile, args.efa))
tot_mem_size = int(system.mem_ranges[0].end) + UpMemorySize
print(tot_mem_size)
upAddrRange = AddrRange(start=Addr(system.mem_ranges[0].end),
                        end=Addr(system.mem_ranges[0].end) + UpMemorySize)
print("UpStreamRange:",upAddrRange)
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



if args.efa:
    system.upstream = UpstreamObj(latency=1,
                                  addrRange=upAddrRange,
                                  numlanes=args.num_lanes,
                                  efa=args.efa,
                                  simdir=simdir,
                                  lm_mode=args.lm_mode,
                                  recode=args.recode,
                                  upmem_channels=args.upmem_channels,
                                  lmsize=args.lmbanksize,
                                  progfile=args.progfile,
								  print_level=args.print_level,
								  perf_log_enable=args.updown_perf_log,
								  perf_log_internal_enable=args.updown_perf_log_internal,
                                  )
else:
    system.upstream = UpstreamObj(latency=1,
                                  simdir=simdir,
                                  lm_mode=args.lm_mode,
                                  upmem_channels=args.upmem_channels,
                                  print_level=args.print_level,
                                  perf_log_enable=args.updown_perf_log,
                                  perf_log_internal_enable=args.updown_perf_log_internal,
                                  addrRange=upAddrRange)
                                  #upArgs= args.upstream)
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
    #system.membus2 = IOXBar()
    system.system_port = system.membus.slave
    CacheConfig.config_cache(args, system)
    MemConfig.config_mem(args, system, nc)
    config_filesystem(system, args)

#system.upstream.mem_side = system.membus.slave
for i in range(np):
    system.upstream.cpu_side[i] = system.cpu[i].l1xbar.mem_side_ports
for i in range(nc):
    system.upstream.mem_side[i] = system.membus.slave

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
print(upAddrRange.start)
print(system.mem_ranges)
print(int(0xFFFFFFF))
if not(args.checkpoint_restore):
    for process in multiprocesses:
        #process.map(0,
        #            0,
        #            0x7FFFFFFF,
        #            True
        if(args.progfile=='GenPagerankEFA' or args.progfile=='GenMapreduceEFA'):
            process.map(0x80000000,
                        0x80000000,
                        0x7FFFFFFF,
                        False)
        else:
            process.map(0x80000000,
                        0x80000000,
                        0x7FFFFFFF,
                        True)
        process.map(0x100000000,
                    0x100000000,
                    0x7FFFFFFF,
                    False)
        process.map(0x180000000,
                    0x180000000,
                    0x7FFFFFFF,
                    False)
        process.map(Addr(args.mem_size),
                    Addr(args.mem_size),
                    UpMemorySize,
                    False)
        #process.map(0,
        #            0,
        #            tot_mem_size,
        #            False)
    
exit_event = Simulation.run(args, root, system, FutureClass, checkpoint_dir, cpt_starttick)

if args.statusmail:
    send_status_mail(args.suffix, exit_event.getCode())

# cleanup post run
if(os.path.isdir(simdirpath)):
    shutil.rmtree(simdirpath, ignore_errors=True)
    print("Deleted simdata folder at '%s'." % simdirpath)
