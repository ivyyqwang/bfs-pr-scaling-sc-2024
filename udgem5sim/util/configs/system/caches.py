# -*- coding: utf-8 -*-
# Copyright (c) 2016 Jason Lowe-Power
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are
# met: redistributions of source code must retain the above copyright
# notice, this list of conditions and the following disclaimer;
# redistributions in binary form must reproduce the above copyright
# notice, this list of conditions and the following disclaimer in the
# documentation and/or other materials provided with the distribution;
# neither the name of the copyright holders nor the names of its
# contributors may be used to endorse or promote products derived from
# this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# Authors: Jason Lowe-Power

""" Caches with options for a simple gem5 configuration script

This file contains L1 I/D and L2 caches to be used in the simple
gem5 configuration script.  It uses the SimpleOpts wrapper to set up command
line options from each individual class.
"""
from m5.defines import buildEnv

import m5

from m5.objects import Cache, L2XBar, StridePrefetcher, WriteAllocator, SubSystem, TreePLRURP, PIFPrefetcher
from m5.params import AddrRange, AllMemory, MemorySize
from m5.util.convert import toMemorySize

# Some specific options for caches
# For all options see src/mem/cache/BaseCache.py

class PrefetchCache(Cache):

    #def __init__(self):
    #    super(PrefetchCache, self).__init__()
        #self.prefetcher = PIFPrefetcher()
        #self.replacement_policy = TreePLRURP()
        #self.prefetch_on_access = True
    prefetcher = PIFPrefetcher()
    replacement_policy = TreePLRURP()
    prefetch_on_access = True

class L1Cache(PrefetchCache):
    """Simple L1 Cache with default values"""

    assoc = 16

    tag_latency = 1
    data_latency = 1
    response_latency = 1

    mshrs = 128
    tgts_per_mshr = 16
    write_buffers = 56
    demand_mshr_reserve = 96

    # writeback_clean = True

    #def __init__(self):
    #    super(L1Cache, self).__init__()

    def connectBus(self, bus):
        """Connect this cache to a memory-side bus"""
        self.mem_side = bus.cpu_side_ports

    def connectCPU(self, cpu):
        """Connect this cache's port to a CPU-side port
           This must be defined in a subclass"""
        raise NotImplementedError

class L1ICache(L1Cache):
    """Simple L1 instruction cache with default values"""

    # Set the default size
    size = '32kB'

    #def __init__(self):
    #    super(L1ICache, self).__init__()

    def connectCPU(self, cpu):
        """Connect this cache's port to a CPU icache port"""
        self.cpu_side = cpu.icache_port

class L1DCache(L1Cache):
    """Simple L1 data cache with default values"""

    # Set the default size
    size = '64kB'
    assoc = 16

    tag_latency = 1
    data_latency = 1
    response_latency = 1

    write_buffers = 128

    write_allocator = WriteAllocator()
    write_allocator.coalesce_limit = 2
    write_allocator.no_allocate_limit = 8
    write_allocator.delay_threshold = 8

    #def __init__(self):
    #    super(L1DCache, self).__init__()

    def connectCPU(self, cpu):
        """Connect this cache's port to a CPU dcache port"""
        self.cpu_side = cpu.dcache_port

class MMUCache(PrefetchCache):
    # Default parameters
    size = '8kB'
    assoc = 8
    tag_latency = 1
    data_latency = 1
    response_latency = 1
    mshrs = 32
    tgts_per_mshr = 8

    def __init__(self):
        super(MMUCache, self).__init__()

    def connectCPU(self, cpu):
        """Connect the CPU itb and dtb to the cache
           Note: This creates a new crossbar
        """
        self.mmubus = L2XBar()
        self.cpu_side = self.mmubus.mem_side_ports
        for tlb in [cpu.itb, cpu.dtb]:
            self.mmubus.cpu_side_ports = tlb.walker.port

    def connectBus(self, bus):
        """Connect this cache to a memory-side bus"""
        self.mem_side = bus.cpu_side_ports

class L2Cache(PrefetchCache):
    """Simple L2 Cache with default values"""

    size = '256kB'
    assoc = 16
    tag_latency = 14
    data_latency = 14
    response_latency = 1
    mshrs = 256
    tgts_per_mshr = 16
    write_buffers = 256

    #def __init__(self):
    #    super(L2Cache, self).__init__()

    def connectCPUSideBus(self, bus):
        self.cpu_side = bus.mem_side_ports

    def connectMemSideBus(self, bus):
        self.mem_side = bus.cpu_side_ports

class L3Cache(PrefetchCache):
    """Simple L3 Cache bank with default values
       This assumes that the L3 is made up of multiple banks. This cannot
       be used as a standalone L3 cache.
    """

    # Default parameters
    #size = '8MB'
    size = '8MB'
    assoc = 16
    tag_latency = 44
    data_latency = 44
    response_latency = 1
    mshrs = 256
    tgts_per_mshr = 16
    write_buffers = 256

    clusivity = 'mostly_excl'

    #def __init__(self):
    #    super(L3Cache, self).__init__()

    def connectCPUSideBus(self, bus):
        self.cpu_side = bus.mem_side_ports

    def connectMemSideBus(self, bus):
        self.mem_side = bus.cpu_side_ports

class IOCache(Cache):
    assoc = 8
    tag_latency = 50
    data_latency = 50
    response_latency = 50
    mshrs = 20
    size = '1kB'
    tgts_per_mshr = 12

class PageTableWalkerCache(Cache):
    assoc = 2
    tag_latency = 2
    data_latency = 2
    response_latency = 2
    mshrs = 10
    size = '1kB'
    tgts_per_mshr = 12

    # the x86 table walker actually writes to the table-walker cache
    if buildEnv['TARGET_ISA'] in ['x86', 'riscv']:
        is_read_only = False
    else:
        is_read_only = True
        # Writeback clean lines as well
        writeback_clean = True

