from m5.params import *
from m5.proxy import *
from m5.objects.ClockedObject import ClockedObject

#A wrapper for a single UpDown Accelerator

class UpDownBASim(ClockedObject):
    type = 'UpDownBASim'
    cxx_header = "updown_basim/updown_basim.hh"

    cpu_side = VectorResponsePort("CPU side port, receives requests")
    mem_side = VectorRequestPort("Memory side port, sends requests")
    udout_side = VectorRequestPort("UD Out side port, sends UD requests")

    latency = Param.Cycles(1, "Cycles to access memory")
    numlanes = Param.Int(64, "Number of Lanes in updown")
    dblksize = Param.Int(64, "Number of bytes in cacheline")
    progfile = Param.String("GenTriCountEFA", "File Containing the EFA Program")
    simdir = Param.String("simdata", "Directory for temporary sim files")
    efa = Param.String("GenerateTriEFA_singlestream_loopopt", "Name of EFA to use for each lane")
    lm_mode = Param.Int(0, "LM Addressing Mode, 0:Global, 1:Restricted")
    lmsize = Param.Int(65536, "LM Size per lane")
    addrRange = Param.AddrRange(AddrRange(0,1), "Memory Address range")
    ctrladdrRange = Param.AddrRange(AddrRange(0x600000000,0x600000800), "Ctrl Memory Address range")
    ctrlAddrBase = Param.Addr(Addr(0x600000000), "Ctrl Memory Address range")
    upmem_channels= Param.Int(8, "Number of memory channels")
    iud_channels= Param.Int(8, "Number of inter-ud channels")
    system = Param.System(Parent.any, "The system")
    recode = Param.Bool(0, "Recode Style Endianness")
    print_level = Param.Int(5, 'UpDown emulator debug print level')
    print_threshold = Param.Addr(0, 'UpDown emulator debug print threshold timestamp')
    perf_log_enable = Param.Bool(False, 'Enable UpDown performance logging')
    perf_log_internal_enable = Param.Bool(False, 'Enable UpDown internal performance logging')
    period = Param.Int(500, "No of Ticks per Cycle")
    nwid = Param.Int(0, "UpDown ID")
    pa_base = Param.Addr(0, "Local Segment Offset")
    lseg_start = Param.Addr(0x80000000, "Local Segment Start")
    lseg_size = Param.Addr(0x80000000, "Total Segment size")
    lseg_block_size = Param.Addr(0x4000000, "Per Stack block size")
    gseg_start = Param.Addr(0x200000000, "Local Segment Start")
    gseg_size = Param.Addr(0x80000000, "Total Segment size")
    gseg_block_size = Param.Addr(0x4000000, "Per Stack block size")
    num_stacks = Param.Int(8, "Per Stack block size")
    num_nodes = Param.Int(2, "Per Stack block size")
    num_uds = Param.Int(4, "Per Stack block size")
    stack_size = Param.Addr(0x400000000, "Per Stack block size")
