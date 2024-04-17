/**
 * @file updown_obj.cc
 * @author Andronicus
 * @brief Definition of a simple updown object
 * @version 0.1
 * @date 2021-06-28
 *
 * @copyright Copyright (c) 2021
 * Adapted from downstream_obj.cc by Jose Monsalve Diaz
 * This file is based on the simple_cache.cc
 * example in the learning_gem5 folder.
 * The following Copyright applies:
 * Copyright (c) 2017 Jason Lowe-Power
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met: redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer;
 * redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution;
 * neither the name of the copyright holders nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 */

#include "updown_basim/updown_basim.hh"

#include <inttypes.h>

#include <chrono>
#include <cstring>
#include <fstream>
#include <future>
#include <iostream>
#include <string>
#include <thread>

#include "base/callback.hh"
#include "base/output.hh"
#include "base/random.hh"
#include "base/types.hh"
#include "debug/AddrRanges.hh"
#include "debug/UpDown.hh"
#include "debug/UpDownBASim.hh"
#include "mem/packet.hh"
#include "mem/request.hh"
#include "params/UpDownBASim.hh"
#include "sim/system.hh"
#include "string.h"
#include "udaccelerator.hh"
#include "logging.hh"
#include "updown_obj/updown_obj.hh"
#include "perf_log/logger.hh"

//#define SENDPOLICY
#define NUMLANES 64
#define NUMTICKS 1
#define LANE_LANE_ACC_LATENCY 4
#define LANE_LANE_CLUSTER_LATENCY 8
#define BANKSIZE 65536
#define BANKSIZEWORDS 8192

using namespace std::chrono_literals;
using namespace gem5;
//struct emulator_stats;

UpDownBASim::UpDownBASim(const gem5::UpDownBASimParams &params) :
    ClockedObject(params),
    blocked_cpu(false),
    blocked_mem(false),
    blocked_ud(false),
    waitingPortId(-1),
    upstats(*this),
    latency(params.latency),
    nwid(params.nwid),
    wordSize(8),
    numlanes(params.numlanes),
    numuds(params.num_uds),
    numstacks(params.num_stacks),
    numnodes(params.num_nodes),
    period(params.period),
    capacity(params.addrRange.size()),
    scratchsize(params.addrRange.end() - params.addrRange.start()),
    upCtrlAddrBase(params.ctrlAddrBase),
    dblksize(params.dblksize)
{
    // Calculate all the addresses
    upAddrRange.push_back(params.addrRange);
    upCtrlAddrRange.push_back(params.ctrladdrRange);
    uint64_t upCtrlAddrBase_local = params.ctrladdrRange.start();

    nwid = params.nwid;
    num_outstanding_cpu = 0;
    uint32_t node_id = (uint32_t)(nwid &0x07fff800) >> 11;

    DPRINTF(UpDownBASim, "NWID: %d Setting addresses\n", nwid);
    sRange = params.addrRange;

    // Setup addresses for all the structures
    for (int i=0; i < UD_NUM_LANES; i++){
        gem5::AddrRange eRange = gem5::AddrRange(upCtrlAddrBase_local+i*32, upCtrlAddrBase_local+i*32+7);
        gem5::AddrRange oRange = gem5::AddrRange(upCtrlAddrBase_local+i*32+8, upCtrlAddrBase_local+i*32+15);
        gem5::AddrRange exRange = gem5::AddrRange(upCtrlAddrBase_local+i*32+16, upCtrlAddrBase_local+i*32+23);
        gem5::AddrRange stRange = gem5::AddrRange(upCtrlAddrBase_local+i*32+24, upCtrlAddrBase_local+i*32+31);
        DPRINTF(AddrRanges, "NWID:%d Lane:%d, EventAddrRange: %lx-%lx\n",nwid, i, eRange.start(), eRange.end());
        DPRINTF(AddrRanges, "NWID:%d Lane:%d, OpRange: %lx-%lx\n", nwid, i, oRange.start(), oRange.end());
        DPRINTF(AddrRanges, "NWID:%d Lane:%d, statRange: %lx-%lx\n",nwid, i, stRange.start(), stRange.end());
        DPRINTF(AddrRanges, "NWID:%d Lane:%d, ExecRange: %lx-%lx\n", nwid, i, exRange.start(), exRange.end());
        evRange.push_back(eRange);
        obRange.push_back(oRange);
        execRange.push_back(exRange);
        statRange.push_back(stRange);
        cur_opnum[i] = 0;
        statStore[i] = 0;
    }

    DPRINTF(AddrRanges, "NWID:%d sRange: %lx-%lx\n", nwid, sRange.start(), sRange.end());
    updown_system_id = params.system->getRequestorId(this, "data");
    // Since the CPU side ports are a vector of ports, create an instance of
    // the CPUSidePort for each connection. This member of params is
    // automatically created depending on the name of the vector port and
    // holds the number of connections to this port name
    for (int i = 0; i < params.port_cpu_side_connection_count; ++i) {
        cpuPorts.emplace_back(name() +
            gem5::csprintf(".cpu_side[%d]", i), i, this);
    }
    num_mc=params.upmem_channels;
    for (int i = 0; i < params.upmem_channels; ++i) {
        memPorts.emplace_back(name() +
            gem5::csprintf(".mem_side[%d]", i), i, this);
    }
    num_ud_channels = params.iud_channels;
    for (int i = 0; i < params.iud_channels; ++i) {
        udOutPorts.emplace_back(name() +
            gem5::csprintf(".udout_side[%d]", i), i, this);
    }

    progfile = params.progfile;

    // Add symbols to a map
    std::ifstream instream(progfile.c_str(), std::ifstream::binary);
    uint64_t startofEventSymbols;
    uint32_t numEventSymbols, label, labelAddr;
    if(instream){
        instream.seekg(0, instream.end); 
        int length = instream.tellg();
        instream.seekg(0, instream.beg);
        instream.read(reinterpret_cast<char *>(&startofEventSymbols), sizeof(startofEventSymbols));
        instream.seekg(startofEventSymbols, instream.beg);
        instream.read(reinterpret_cast<char *>(&numEventSymbols), sizeof(numEventSymbols));
        for(auto i = 0; i < numEventSymbols; i++){
          instream.read(reinterpret_cast<char *>(&label), sizeof(label));
          instream.read(reinterpret_cast<char *>(&labelAddr), sizeof(labelAddr));
          this->symbolMap[label] = labelAddr; 
        }
        instream.seekg(0, instream.beg);
    }else{
      printf("Could not load the binary: %s\n", progfile.c_str());
      exit(1);
    }


    //simdir = params.simdir;
    lm_mode = params.lm_mode;
    uint64_t lmbase = sRange.start();
    int total_uds = params.num_nodes * params.num_stacks * params.num_uds;

    udaccel = new basim::UDAccelerator(numlanes, nwid, lm_mode);
    basim::globalLogs.perflog.registerPerflogCallback(PerfLog::writeUpdownBasimPerflog);
    udaccel->initSetup(0, progfile, lmbase, total_uds);

    for (int i=0; i < numlanes; i++){
        least_poss_exec_cycle[i]=0;
        exec_stat[i] = false;
    }
    // One entry for now
    // This whole thing needs to go?

    udtrans_table = UDTranslations(node_id, this->nwid);
    int num_entries = params.lseg_size/ params.lseg_block_size;
    for (int i = 0;i < num_entries; i++){
        udtrans_entry ud_entry;
        uint64_t va_start;
        ud_entry.ttype = TransType::Local;
        ud_entry.base = params.lseg_start + params.lseg_block_size * i;
        ud_entry.pa_base = params.pa_base + params.lseg_start + (i / (params.num_stacks))* params.lseg_block_size + (i%(params.num_stacks)) * params.stack_size;
        //ud_entry.offset = params.pa_base + (i/params.num_stacks)*params.lseg_block_size + (i%params.num_stacks)*(1UL <<34);
        //ud_entry.offset = -params.lseg_block_size*i + (i%params.num_stacks)*(1UL <<34);
        ud_entry.limit = params.lseg_start + params.lseg_block_size * (i+1); //0x7FFFFFFF; //0x2000000000;
        udtrans_table.addTranslation(ud_entry);
    }
    // udaccel->insertLocalTrans(params.lseg_start, params.pa_base, params.lseg_size, 0b11);
    // printf("Add private segment translation: virtual base = %ld(0x%lx), physical base = %ld(0x%lx), size = %ld\n", params.lseg_start, params.lseg_start, params.pa_base, params.pa_base, params.lseg_size);
    num_entries = params.gseg_size/ params.gseg_block_size;
    uint64_t pa_start_addr = params.lseg_start + params.lseg_size/params.num_stacks;
    //pa_start = gseg_start + int(j / (nstacks*nnodes))*gblock_size + (j%(nstacks*nnodes))*stack_size
    for (int i = 0;i < num_entries; i++){
        udtrans_entry ud_entry;
        uint64_t va_start;
        ud_entry.ttype = TransType::Global;
        ud_entry.base = params.gseg_start + params.gseg_block_size * i;
        ud_entry.pa_base = pa_start_addr + (i/(params.num_stacks * params.num_nodes))*params.gseg_block_size + (i% (params.num_stacks*params.num_nodes))*(params.stack_size);
        //ud_entry.offset = -params.gseg_block_size*i + (i% (params.num_stacks*params.num_nodes))*(1UL <<34);
        ud_entry.limit = params.gseg_start + params.gseg_block_size * (i+1); //0x7FFFFFFF; //0x2000000000;
        udtrans_table.addTranslation(ud_entry);
    }
}

void
UpDownBASim::init(){
    //for (auto& port : udInPorts) {
    //    if (port.isConnected())
    //        port.sendRangeChange();
    //}
    for (auto& port : cpuPorts) {
        if (port.isConnected())
            port.sendRangeChange();
    }
}


void
UpDownBASim::UpDownStats::regStats()
{
    using namespace statistics;

    statistics::Group::regStats();

    const auto num_lanes = upobj.numlanes;

    cyclesPerEvent.init(20);
    //cyclesPerThread.init(20);

    inst_count.init(num_lanes);
    tran_count.init(num_lanes);
    inst_count_atomic.init(num_lanes);
    inst_count_bitwise.init(num_lanes);
    inst_count_ctrlflow.init(num_lanes);
    inst_count_datmov.init(num_lanes);
    inst_count_ev.init(num_lanes);
    inst_count_fparith.init(num_lanes);
    inst_count_hash.init(num_lanes);
    inst_count_intarith.init(num_lanes);
    inst_count_intcmp.init(num_lanes);
    inst_count_msg.init(num_lanes);
    inst_count_threadctrl.init(num_lanes);
    inst_count_tranctrl.init(num_lanes);
    inst_count_vec.init(num_lanes);
    tran_count_basic.init(num_lanes);
    tran_count_majority.init(num_lanes);
    tran_count_default.init(num_lanes);
    tran_count_epsilon.init(num_lanes);
    tran_count_common.init(num_lanes);
    tran_count_flagged.init(num_lanes);
    tran_count_refill.init(num_lanes);
    tran_count_event.init(num_lanes);
    lm_load_bytes.init(num_lanes);
    lm_store_bytes.init(num_lanes);
    dram_load_bytes.init(num_lanes);
    dram_store_bytes.init(num_lanes);
    dram_load_count.init(num_lanes);
    dram_store_count.init(num_lanes);

    numEvents.init(num_lanes);
    lane_busy_cycles.init(num_lanes);
    lane_idle_cycles.init(num_lanes);
    lane_exec_cycles.init(num_lanes);
    lane_stall_cycles.init(num_lanes);
    eventq_len_max.init(num_lanes);
    opbuff_len_max.init(num_lanes);
    updownPerLaneUserCtr0.init(num_lanes);
    updownPerLaneUserCtr1.init(num_lanes);
    updownPerLaneUserCtr2.init(num_lanes);
    updownPerLaneUserCtr3.init(num_lanes);
    updownPerLaneUserCtr4.init(num_lanes);
    updownPerLaneUserCtr5.init(num_lanes);
    updownPerLaneUserCtr6.init(num_lanes);
    updownPerLaneUserCtr7.init(num_lanes);
    updownPerLaneUserCtr8.init(num_lanes);
    updownPerLaneUserCtr9.init(num_lanes);
    updownPerLaneUserCtr10.init(num_lanes);
    updownPerLaneUserCtr11.init(num_lanes);
    updownPerLaneUserCtr12.init(num_lanes);
    updownPerLaneUserCtr13.init(num_lanes);
    updownPerLaneUserCtr14.init(num_lanes);
    updownPerLaneUserCtr15.init(num_lanes);

    //avgThreadExecCycles.flags(nonan).precision(2);
    //upLaneEventQMean.flags(nonan).precision(2);
    //upLaneOperandQMean.flags(nonan).precision(2);

    for (int i = 0; i < num_lanes; i++) {
        const std::string  lane = std::string("Lane[") + std::to_string(i) + std::string("]");
        inst_count.subname(i, lane);
        tran_count.subname(i, lane);
        inst_count_atomic.subname(i, lane);
        inst_count_bitwise.subname(i, lane);
        inst_count_ctrlflow.subname(i, lane);
        inst_count_datmov.subname(i, lane);
        inst_count_ev.subname(i, lane);
        inst_count_fparith.subname(i, lane);
        inst_count_hash.subname(i, lane);
        inst_count_intarith.subname(i, lane);
        inst_count_intcmp.subname(i, lane);
        inst_count_msg.subname(i, lane);
        inst_count_threadctrl.subname(i, lane);
        inst_count_tranctrl.subname(i, lane);
        inst_count_vec.subname(i, lane);
        tran_count_basic.subname(i, lane);
        tran_count_majority.subname(i, lane);
        tran_count_default.subname(i, lane);
        tran_count_epsilon.subname(i, lane);
        tran_count_common.subname(i, lane);
        tran_count_flagged.subname(i, lane);
        tran_count_refill.subname(i, lane);
        tran_count_event.subname(i, lane);
        lm_load_bytes.subname(i, lane);
        lm_store_bytes.subname(i, lane);
        dram_load_bytes.subname(i, lane);
        dram_store_bytes.subname(i, lane);
        dram_load_count.subname(i, lane);
        dram_store_count.subname(i, lane);
        numEvents.subname(i, lane);
        lane_busy_cycles.subname(i, lane);
        lane_idle_cycles.subname(i, lane);
        lane_exec_cycles.subname(i, lane);
        lane_stall_cycles.subname(i, lane);
        eventq_len_max.subname(i, lane);
        opbuff_len_max.subname(i, lane);
        //avgThreadExecCycles.subname(i, lane);
        updownPerLaneUserCtr0.subname(i, lane);
        updownPerLaneUserCtr1.subname(i, lane);
        updownPerLaneUserCtr2.subname(i, lane);
        updownPerLaneUserCtr3.subname(i, lane);
        updownPerLaneUserCtr4.subname(i, lane);
        updownPerLaneUserCtr5.subname(i, lane);
        updownPerLaneUserCtr6.subname(i, lane);
        updownPerLaneUserCtr7.subname(i, lane);
        updownPerLaneUserCtr8.subname(i, lane);
        updownPerLaneUserCtr9.subname(i, lane);
        updownPerLaneUserCtr10.subname(i, lane);
        updownPerLaneUserCtr11.subname(i, lane);
        updownPerLaneUserCtr12.subname(i, lane);
        updownPerLaneUserCtr13.subname(i, lane);
        updownPerLaneUserCtr14.subname(i, lane);
        updownPerLaneUserCtr15.subname(i, lane);
    }
    //avgThreadExecCycles = upLaneBusyCycles/numThreads;
    //avgDmLmSendLatency = TotalLat_SendsDmLm/numSends_DmLm;
    //avgInterLaneSendLatency = TotalLat_SendsInterLane/numSends_InterLane;

    // More calculations on the stats here

}

void
UpDownBASim::UpDownStats::preDumpStats()
{
    // Update all the sats before a dump is a done
    for(int i = 0; i < upobj.numlanes; i++){
        lnstats = (upobj.udaccel)->getLaneStats(i);
        inst_count[i] = lnstats->inst_count;
        tran_count[i] = lnstats->tran_count;
        inst_count_atomic[i] = lnstats->inst_count_atomic;
        inst_count_bitwise[i] = lnstats->inst_count_bitwise;
        inst_count_ctrlflow[i] = lnstats->inst_count_ctrlflow;
        inst_count_datmov[i] = lnstats->inst_count_datmov;
        inst_count_ev[i] = lnstats->inst_count_ev;
        inst_count_fparith[i] = lnstats->inst_count_fparith;
        inst_count_hash[i] = lnstats->inst_count_hash;
        inst_count_intarith[i] = lnstats->inst_count_intarith;
        inst_count_intcmp[i] = lnstats->inst_count_intcmp;
        inst_count_msg[i] = lnstats->inst_count_msg;
        inst_count_threadctrl[i] = lnstats->inst_count_threadctrl;
        inst_count_tranctrl[i] = lnstats->inst_count_tranctrl;
        inst_count_vec[i] = lnstats->inst_count_vec;
        tran_count_basic[i] = lnstats->tran_count_basic;
        tran_count_majority[i] = lnstats->tran_count_majority;
        tran_count_default[i] = lnstats->tran_count_default;
        tran_count_epsilon[i] = lnstats->tran_count_epsilon;
        tran_count_common[i] = lnstats->tran_count_common;
        tran_count_flagged[i] = lnstats->tran_count_flagged;
        tran_count_refill[i] = lnstats->tran_count_refill;
        tran_count_event[i] = lnstats->tran_count_event;
        lm_load_bytes[i] = lnstats->lm_load_bytes;
        lm_store_bytes[i] = lnstats->lm_store_bytes;
        dram_load_bytes[i] = lnstats->dram_load_bytes;
        dram_store_bytes[i] = lnstats->dram_store_bytes;
        dram_load_count[i] = lnstats->dram_load_count;
        dram_store_count[i] = lnstats->dram_store_count;
        eventq_len_max[i] = lnstats->eventq_len_max;
        opbuff_len_max[i] = lnstats->opbuff_len_max; 
        lane_exec_cycles[i] = uint64_t(lnstats->cycle_count);
        //lane_idle_cycles[i] = lane_busy_cycles[i] - lane_exec_cycles[i];
    }
}


gem5::Port &
UpDownBASim::getPort(const std::string &if_name, gem5::PortID idx)
{
    // This is the name from the Python UpDownBASim
    // declaration in UpDownBASim.py
    if (if_name == "mem_side" && idx < memPorts.size()) {
        return memPorts[idx];
    } else if (if_name == "cpu_side" && idx < cpuPorts.size()) {
        return cpuPorts[idx];
    //} else if (if_name == "udin_side" && idx < udInPorts.size()) {
    //    return udInPorts[idx];
    } else if (if_name == "udout_side" && idx < udOutPorts.size()) {
        return udOutPorts[idx];
    }else{
        // pass it along to our super class
        return ClockedObject::getPort(if_name, idx);
    }
}


void
UpDownBASim::CPUSidePort::sendPacket(gem5::PacketPtr pkt, int ins_new)
{

    if (blockedPacket_vec.size()>0 && ins_new){
        blockedPacket_vec.push_back(pkt);
        DPRINTF(UpDownBASim, "NWID:%d CPUSidePort: Outstanding packets adding to blocked queue %s, Size:%d \n", 
                            owner->nwid, pkt->print(), blockedPacket_vec.size());
        return;
    }

    // If we can't send the packet across the port, store it for later.
    //DPRINTF(UpDownBASim, "Sending %s to CPU\n", pkt->print());
    if (!sendTimingResp(pkt)) {
        DPRINTF(UpDownBASim, "NWID:%d failed pushing to blocked queue!\n", 
                                owner->nwid);
        if (ins_new)
            blockedPacket_vec.push_back(pkt);
    }else{
        DPRINTF(UpDownBASim, "NWID:%d Successfully sent to CPU\n", 
                                owner->nwid);
        if (!ins_new)
            blockedPacket_vec.erase(blockedPacket_vec.begin());
    }
}


gem5::AddrRangeList
UpDownBASim::CPUSidePort::getAddrRanges() const
{
    return owner->getAddrRanges();
}


void
UpDownBASim::CPUSidePort::trySendRetry()
{
    if (needRetry && blockedPacket_vec.size() == 0) {
        // Only send a retry if the port is now completely free
        needRetry = false;
        DPRINTF(UpDownBASim, "NWID:%d Sending retry req, %d\n", owner->nwid, owner->num_outstanding_cpu);
        sendRetryReq();
    }
}

gem5::Tick
UpDownBASim::CPUSidePort::recvAtomic(gem5::PacketPtr pkt)
{
    pkt->setCPUport(this->id);
    owner->handleCPUFunctional(pkt);
    return gem5::curTick();
}


void
UpDownBASim::CPUSidePort::recvFunctional(gem5::PacketPtr pkt)
{
    // Just forward to the downstream.
    if (pkt->mtype == MessageType::NW){
        return owner->handleUDFunctional(pkt);
    }else{
        pkt->setCPUport(this->id);
        return owner->handleCPUFunctional(pkt);
    }
}


bool
UpDownBASim::CPUSidePort::recvTimingReq(gem5::PacketPtr pkt)
{
    pkt->setCPUport(this->id);
    if (pkt->mtype == MessageType::NW){
        DPRINTF(UpDownBASim, "NWID:%d, Got timing request %s from UD:%d on port:%d \n", 
                            owner->nwid, pkt->print(), pkt->getsrcnwid(), this->id);
        // update stats
        if (needRetry) {
            // The downstream may not be able to send a reply if this is blocked
            DPRINTF(UpDownBASim, "NWID:%d, UD Request blocked\n", 
                            owner->nwid);
            return false;
        }
        (owner->upstats).InterUDMessageLatency += (gem5::curTick() - pkt->getSendtick());
        (owner->upstats).num_InterUDMessages++;
        (owner->upstats).bytesReceived_InterUDMessages += ((pkt->numOb+2)*8);  

        // Just forward to the cache. ??
        if (!owner->handleUDRequest(pkt, this->id)) {
            DPRINTF(UpDownBASim, "NWID:%d, UD Request failed\n", owner->nwid);
            // stalling
            needRetry = true;
            return false;
        } else {
            DPRINTF(UpDownBASim, "NWID:%d, UD Request succeeded\n", owner->nwid);
            return true;
        }

    }else{
        DPRINTF(UpDownBASim, "NWID:%d, Got timing request %s from CPU port ID:%d\n", 
                        owner->nwid, pkt->print(), this->id);
        owner->num_outstanding_cpu++;
        DPRINTF(UpDownBASim, "NWID:%d, Set port ID:%d in packet, outstanding:%d \n", 
                        owner->nwid, pkt->getCPUport(), owner->num_outstanding_cpu);

        if (needRetry) {
            // The downstream may not be able to send a reply if this is blocked
            DPRINTF(UpDownBASim, "NWID:%d, CPU Request blocked, outstanding:%d\n", owner->nwid,
                            owner->num_outstanding_cpu);
            return false;
        }

        // Just forward to the cache. ??
        if (!owner->handleCPURequest(pkt, id)) {
            DPRINTF(UpDownBASim, "NWID:%d, CPU Request failed, outstanding:%d\n", 
                            owner->nwid, owner->num_outstanding_cpu);
            // stalling
            needRetry = true;
            return false;
        } else {
            owner->num_outstanding_cpu--;
            DPRINTF(UpDownBASim, "NWID:%d CPU Request succeeded, outstanding:%d\n", 
                            owner->nwid, owner->num_outstanding_cpu);
            return true;
        }
    }
}


void
UpDownBASim::CPUSidePort::recvRespRetry()
{
    // We should have a blocked packet if this function is called.
    if (blockedPacket_vec.size() == 0){
        panic("Retry called when nothing blocked\n");
    }
    gem5::PacketPtr pkt = blockedPacket_vec.front();
    gem5::Tick latency_t = 1;

    // Grab the blocked packet.

    DPRINTF(UpDownBASim, "NWID:%d Retrying response pkt %s, blocked_size %d to port %d\n", 
                            owner->nwid, pkt->print(), blockedPacket_vec.size(), pkt->getCPUport());
    // Try to resend it. It's possible that it fails again.
    sendPacket(pkt, 0);

    if (blockedPacket_vec.size()>0){
        gem5::PacketPtr pkt_2_send = blockedPacket_vec.front();
        owner->schedule(new gem5::EventFunctionWrapper([this, pkt_2_send]
                {(owner->cpuPorts[pkt_2_send->getCPUport()]).sendPacket(pkt_2_send, 0);},
                    name() + ".sendPacket", true), gem5::curTick()+latency_t);
    }

    // We may now be able to accept new packets
    trySendRetry();
    DPRINTF(UpDownBASim, "NWID:%d After all the Retrying blocked_size %d\n", 
                            owner->nwid, blockedPacket_vec.size());
}

/*  UD Out Port Functions */


void
UpDownBASim::UDSideOutPort::sendPacket(gem5::PacketPtr pkt, int ins_new)
{
    // Note: This flow control is very simple since the cache is blocking.
    int portid = id;
    gem5::Tick latency_t = 1;
    if (blockedPacket_vec.size() > 0 && ins_new){
        blockedPacket_vec.push_back(pkt);
    }else if (blockedPacket_vec.size() == 0 && ins_new){
        pkt->setSendtick(gem5::curTick());
        if (!sendTimingReq(pkt)){
            blockedPacket_vec.push_back(pkt);
        }
    }else{
        pkt->setSendtick(gem5::curTick());
        if (sendTimingReq(pkt)){
            blockedPacket_vec.erase(blockedPacket_vec.begin());
            if (blockedPacket_vec.size()>0){
                gem5::PacketPtr pkt_2_send = blockedPacket_vec.front();
                owner->schedule(new gem5::EventFunctionWrapper([this, pkt_2_send, portid]{(owner->udOutPorts[portid]).sendPacket(pkt_2_send, 0); },
                                              name() + ".sendPacket", true),
                     gem5::curTick()+owner->period);
            }

        }
    }
}


bool
UpDownBASim::UDSideOutPort::recvTimingResp(gem5::PacketPtr pkt)
{

    std::map<uint64_t, sendmsg_tptr>::iterator it;
    it = owner->ud_reqs.find((pkt->req)->getTransID());
    if (it != owner->ud_reqs.end()){
        owner->ud_reqs.erase(it);
        return true;
    }else{
        return true;
    }
}

void
UpDownBASim::UDSideOutPort::recvReqRetry()
{
    // We should have a blocked packet if this function is called.
    assert(blockedPacket_vec.size() > 0);

    // Grab the blocked packet.
    gem5::PacketPtr pkt = blockedPacket_vec.front();

    sendPacket(pkt, 0);
}

/* Memory Side Port Functions */

void
UpDownBASim::MemSidePort::sendPacket(gem5::PacketPtr pkt, int ins_new)
{
    // Note: This flow control is very simple since the cache is blocking.
    int portid = id;
    gem5::Tick latency_t = 1;
    if (blockedPacket_vec.size() > 0 && ins_new){
        blockedPacket_vec.push_back(pkt);
        DPRINTF(UpDownBASim, "NWID:%d, TransID:%d Packet :%lx pushed into blockedPacket-0 \n",
                                owner->nwid, (pkt->req)->getTransID(), pkt->getAddr());
    }else if (blockedPacket_vec.size() == 0 && ins_new){
        if (!sendTimingReq(pkt)){
            DPRINTF(UpDownBASim, "NWID:%d, TransID:%d Packet :%lx pushed into blockedPacket-1 \n", 
                                owner->nwid, (pkt->req)->getTransID(), pkt->getAddr());
            blockedPacket_vec.push_back(pkt);
        }else{
            DPRINTF(UpDownBASim, "NWID:%d, TransID:%d Packet :%lx sent to memory (sendPacket-1) \n",
                                owner->nwid, (pkt->req)->getTransID(), pkt->getAddr());
        }
    }else{
        if (sendTimingReq(pkt)){
            DPRINTF(UpDownBASim, "NWID:%d, TransID:%d Packet :%lx sent to memory (sendPacket-2) \n",
                                owner->nwid, (pkt->req)->getTransID(), pkt->getAddr());
            blockedPacket_vec.erase(blockedPacket_vec.begin());
            if (blockedPacket_vec.size()>0){
                gem5::PacketPtr pkt_2_send = blockedPacket_vec.front();
                owner->schedule(new gem5::EventFunctionWrapper([this, pkt_2_send, portid]{
                             (owner->memPorts[portid]).sendPacket(pkt_2_send, 0); }, 
                              name() + ".sendPacket", true),
                     gem5::curTick()+ latency_t);
            }

        }
    }
}


bool
UpDownBASim::MemSidePort::recvTimingResp(gem5::PacketPtr pkt)
{
    // For Message from Memory - get the continuation from the stored struct and use that.
    std::map<uint64_t, sendmsg_tptr>::iterator it;

    // Get the MMessage
    sendmsg_tptr sm_intf;
    it = owner->mem_reqs.find((pkt->req)->getTransID());

    DPRINTF(UpDownBASim, "NWID:%d, MemSidePort Trans:%d Response for addr : %#x %s\n", 
                        owner->nwid, (pkt->req)->getTransID(), pkt->getAddr(), pkt->print());

    if (it != owner->mem_reqs.end()){
        sm_intf = it->second;
        basim::MMessagePtr m = sm_intf->msg;
        DPRINTF(UpDownBASim, "NWID:%d, PTID:%d, STID:%d\n", 
                        owner->nwid, (pkt->req)->getTransID(), sm_intf->sm_trans_id);
        assert(sm_intf->sm_trans_id == (pkt->req)->getTransID());

        basim::eventword_t cont = m->getXc();
        basim::networkid_t cont_nwid = cont.getNWID();
        int lane_num = cont_nwid.getLaneID();
        if (owner->statStore[lane_num]==1){
        //if (owner->statStore[pkt->getAddr()+lane_num*8]==1){
            DPRINTF(UpDownBASim, "NWID:%d, Top requests in flight, pushing into Pending Queue:%d\n",
                            owner->nwid, owner->pending_response[lane_num].size());
            owner->pending_response[lane_num].push(pkt);
            //delete sm_intf;
            return true; // Return true to Memory sendtimingResponse function
        }else if (owner->pending_response[lane_num].size()>0){
            DPRINTF(UpDownBASim, "NWID:%d, %lu responses still in queue\n",
                            owner->nwid, owner->pending_response[lane_num].size());
            owner->pending_response[lane_num].push(pkt);
            DPRINTF(UpDownBASim, "NWID:%d, %lu Updated responses still in queue\n", 
                            owner->nwid, owner->pending_response[lane_num].size());
            int num_remaining=owner->pending_response[lane_num].size();
            for (int i=0; i< num_remaining;i++){
                //gem5::PacketPtr pkt_rem = owner->pending_response[lane_num][i];
                gem5::PacketPtr pkt_rem = owner->pending_response[lane_num].front();
                if (owner->handleDRAMResponse(pkt_rem)){
                    DPRINTF(UpDownBASim, "NWID:%d, Lane:%d Handled: %d\n",
                                owner->nwid, lane_num, owner->pending_response[lane_num].size());
                    owner->pending_response[lane_num].pop(); //erase(owner->pending_response[lane_num].begin()+i);
                    DPRINTF(UpDownBASim, "NWID:%d, Lane_num:%d Remdaining pending responses: %d\n",
                                owner->nwid, lane_num, owner->pending_response[lane_num].size());
                }else{
                    printf("Error handling Response from pending queue \n");
                    exit(1);
                }
            }
            return true;

        }else{
            if (owner->handleDRAMResponse(pkt)){
                delete pkt;
                return true;
            }

        }
    }else{
        printf("Size of Map:%d, What's left ?\n", owner->mem_reqs.size());
        for (it=owner->mem_reqs.begin(); it != owner->mem_reqs.end(); ++it){
            printf("%d, ", (it->second)->sm_trans_id );
        }
        printf("\nThis should never happen: No entry in Mem_Req\n");
        exit(1);
    }
}

void
UpDownBASim::MemSidePort::recvReqRetry()
{
    // We should have a blocked packet if this function is called.
    assert(blockedPacket_vec.size() > 0);

    // Grab the blocked packet.
    gem5::PacketPtr pkt = blockedPacket_vec.front();

    sendPacket(pkt, 0);
}


bool
UpDownBASim::handleCPURequest(gem5::PacketPtr pkt, int port_id)
{
    if (blocked_cpu) {
        // There is currently an outstanding request so we can't respond. Stall
        return false;
    }

    DPRINTF(UpDownBASim, "NWID:%d, Got request for addr %#x\n", 
                nwid, pkt->getAddr());

    // This upstream is now blocked waiting for the response to this packet.
    blocked_cpu = true;

    // Store the port for when we get the response
    assert(waitingPortId == -1);
    waitingPortId = port_id;

    accessCPUTiming(pkt);

    return true;
}

bool
UpDownBASim::handleUDRequest(gem5::PacketPtr pkt, int port_id)
{

    DPRINTF(UpDownBASim, "NWID:%d Got UD request for addr %#x\n", nwid, pkt->getAddr());

    accessUDTiming(pkt);

    return true;
}

// DRAM Messages (Load or Store)

bool
UpDownBASim::handleDRAMResponse(gem5::PacketPtr pkt)
{
    std::map<uint64_t, sendmsg_tptr>::iterator it;
    DPRINTF(UpDownBASim, "NWID:%d, Got response for addr %#x, Trans:%d\n", 
            nwid, pkt->getAddr(), (pkt->req)->getTransID());
    DDUMP(UpDown, pkt->getConstPtr<uint8_t>(), pkt->getSize());
    sendmsg_tptr sm_intf; // = new struct sendmsg_intf();
    it = mem_reqs.find((pkt->req)->getTransID());
    if (it != mem_reqs.end()){
        sm_intf = it->second;
        if (sm_intf->partial){
            int index = (this->udtrans_table.getVA(pkt->getAddr()) - sm_intf->sdest_VA);
            DPRINTF(UpDownBASim, "NWID:%d Partial Addr %#x, Trans:%d is at Index:%d\n", 
                    nwid, pkt->getAddr(), (pkt->req)->getTransID(), index);
            if (sm_intf->bytes_recvd == 0)
                sm_intf->partial_data = new uint8_t[sm_intf->ssize];
            // figure out index and write to the right index!
            pkt->writeData(&sm_intf->partial_data[index]);
            sm_intf->bytes_recvd += pkt->getSize();
            sm_intf->num_recvd++;
            if (sm_intf->bytes_recvd!=sm_intf->ssize)
                return true;
        }else{
            DPRINTF(UpDownBASim, "NWID:%d, NonPartial Addr %#x, Trans:%d\n", 
                    nwid, pkt->getAddr(), (pkt->req)->getTransID());
            sm_intf->partial_data = new uint8_t[sm_intf->ssize];
            pkt->writeData(sm_intf->partial_data);
            sm_intf->bytes_recvd+=pkt->getSize();
            sm_intf->num_recvd++;
        }

        basim::MMessagePtr m = sm_intf->msg;
        basim::eventword_t cont = m->getXc();
        basim::networkid_t nwid_t = cont.getNWID();
        uint32_t nwid = nwid_t.networkid;
        int lane_num = static_cast<int>(nwid_t.getLaneID());
        if (!m->isStore()){
            //Loads
            DPRINTF(UpDownBASim, "NWID:%d Load return Size:%d, getlen():%d\n", nwid, sm_intf->ssize, m->getLen());
            DDUMP(UpDown, pkt->getConstPtr<uint8_t>(), pkt->getSize());
            basim::word_t* ldata = new basim::word_t[m->getLen()];
            memcpy(ldata, sm_intf->partial_data, m->getLen()*wordSize);
            DDUMP(UpDown, ldata, sm_intf->ssize);
            uint64_t noupdate_cont = 0x7fffffffffffffff;
            basim::operands_t op0(m->getLen()+1, basim::EventWord(noupdate_cont));  
            //basim::operands_t* op0 = new basim::operands_t(m->getLen()+1, basim::EventWord(noupdate_cont)); 
            for(int i = 0; i < m->getLen(); i++){
                op0.setDataWord(i, ldata[i]);
            }
            op0.setDataWord(m->getLen(), sm_intf->sdest_VA);
            basim::eventoperands_t eops(&cont, &op0);
            udaccel->pushEventOperands(eops, (cont.getNWID()).getLaneID());
            upstats.numEvents[lane_num]++;
            delete ldata;
        }else{
            //stores
            DPRINTF(UpDownBASim, "NWID:%d Store Ack Size:%d\n", nwid, sm_intf->ssize);
            DDUMP(UpDown, pkt->getConstPtr<uint8_t>(), pkt->getSize());
            int num_oper = 2;
            uint64_t noupdate_cont = 0x7fffffffffffffff;
            //basim::operands_t* op0 = new basim::operands_t(2, basim::EventWord(noupdate_cont)); 
            basim::operands_t op0(2, basim::EventWord(noupdate_cont));  // num opernads + cont
            op0.setDataWord(0, m->getdestaddr());
            op0.setDataWord(1, m->getdestaddr());
            basim::eventoperands_t eops(&cont, &op0);
            udaccel->pushEventOperands(eops, (cont.getNWID()).getLaneID());
            upstats.numEvents[lane_num]++;
        }

    }else{
        printf("Pkt not in map\n");
        exit(1);
    }

    DPRINTF(UpDownBASim, "NWID:%d Erasing Trans:%ld from Map\n",nwid, sm_intf->sm_trans_id);
    if (sm_intf->partial_data) delete sm_intf->partial_data;
    if (sm_intf->msg) delete sm_intf->msg;
    mem_reqs.erase(sm_intf->sm_trans_id);
    delete sm_intf;
    return true;
}


void UpDownBASim::sendCPUResponse(gem5::PacketPtr pkt)
{
    int port = pkt->getCPUport();
    DPRINTF(UpDownBASim, "NWID:%d, Sending resp for addr %#x to port%d\n", 
                        nwid, pkt->getAddr(), port);
    if (pkt->mtype != MessageType::NW){
        DPRINTF(UpDownBASim, "NWID:%d Sending resp for addr %#x to CPU %d\n", 
                        nwid, pkt->getAddr(), port, num_outstanding_cpu);
        //num_outstanding_cpu--;
    }
    // The packet is now done. We're about to put it in the port, no need for
    // this object to continue to stall.
    // We need to free the resource before sending the packet in case the CPU
    // tries to send another request immediately (e.g., in the same callchain).
    blocked_cpu = false;
    waitingPortId = -1;

    // Simply forward to the memory port
    cpuPorts[port].sendPacket(pkt, 1);

    // For each of the cpu ports, if it needs to send a retry, it should do it
    // now since this memory object may be unblocked now.
    for (auto& port : cpuPorts) {
        port.trySendRetry();
    }
}


void
UpDownBASim::handleCPUFunctional(gem5::PacketPtr pkt)
{
    accessCPUFunctional(pkt);
    pkt->makeResponse();
}

void
UpDownBASim::accessCPUTiming(gem5::PacketPtr pkt)
{
    accessCPUFunctional(pkt);
    pkt->makeResponse();
    schedule(new gem5::EventFunctionWrapper([this, pkt]{ sendCPUResponse(pkt); },
                                  name() + ".sendCPUResponse", true),
         clockEdge(latency));
}

bool
UpDownBASim::accessCPUFunctional(gem5::PacketPtr pkt)
{
    DPRINTF(UpDownBASim, "NWID:%d, Accessfunction Before read:%s\n", nwid, pkt->print());
    if (pkt->isWrite()) {
        // The packet should be aligned.
        write(pkt);
    } else if (pkt->isRead()) {
        // The packet should be aligned.
        read(pkt);
    }
    return true;
}

void
UpDownBASim::handleUDFunctional(gem5::PacketPtr pkt)
{
    accessUDFunctional(pkt);
}

void
UpDownBASim::accessUDTiming(gem5::PacketPtr pkt)
{
    accessUDFunctional(pkt);
}

bool
UpDownBASim::accessUDFunctional(gem5::PacketPtr pkt)
{
    DPRINTF(UpDownBASim, "NWID:%d, Accessfunction Before read:%s\n", 
                nwid, pkt->print());
    if (pkt->isWrite()) {
        writeUD(pkt);
    } else if (pkt->isRead()) {
        printf("cannot read from Remote LM as yet!\n");
        exit(1);
    }
    return true;
}

void
UpDownBASim::writeUD(gem5::PacketPtr pkt)
{
    bool found = false;
    uint32_t lane_num;
    int i = 0;
    for (gem5::AddrRangeList::iterator it = evRange.begin(); it != evRange.end() && !false; ++it, i++){
        if (pkt->getAddr() >= it->start() && pkt->getAddr() <= it->end()){
            found=true;
            lane_num=i;
        }
    }
    if (!found)
        fatal("NWID:%d, Unknown EvQ addr received %lx", nwid, pkt->getAddr());

    if (statStore[lane_num] == 0){
        DPRINTF(UpDownBASim, "NWID:%d InterUD Message for Lane %d: %s\n", 
                    nwid, lane_num, pkt->print());
        basim::MMessagePtr m = pkt->udmsg;
        basim::eventword_t ev = m->getXe();
        //basim::operands_t* op0 = new basim::operands_t(m->getLen(), m->getXc()); 
        basim::operands_t op0(m->getLen(), m->getXc());  // num opernads + cont
        op0.setData((m->getpayload()));
        basim::eventoperands_t eops(&ev, &op0);
        uint32_t dest_nwid = ev.getNWID().networkid;
    #ifdef SENDPOLICY
        int policy = (ev.getNWID()).getSendPolicy();
        lane_num = udaccel->getLanebyPolicy(lane_num, policy); 
    #endif
        DPRINTF(UpDownBASim, "NWID:%d, Inserting Event Lane:%d\n", dest_nwid, lane_num);
        udaccel->pushEventOperands(eops, lane_num);
        if(!exec_stat[lane_num])
            schedule(new gem5::EventFunctionWrapper([this, lane_num]{ execute(&lane_num); },
                                      name() + ".execute", true),
            gem5::curTick() + period);
        upstats.numEvents[lane_num]++;
    }else{
        schedule(new gem5::EventFunctionWrapper([this, pkt]{ writeUD(pkt); },
                                      name() + ".writeUD", true),
             clockEdge(gem5::Cycles(latency)));
    }
}
void
UpDownBASim::write(gem5::PacketPtr pkt)
{
    int lane_num;
    DPRINTF(UpDownBASim, "Writing %s\n", pkt->print());
    DDUMP(UpDown, pkt->getConstPtr<uint8_t>(), wordSize);
    // determine up front what is to be done
    addr_region_t ar = INV;
    if (pkt->getAddr() >= sRange.start() && pkt->getAddr() <= sRange.end()){
        ar=SPD;
    }
    else{
        gem5::AddrRangeList::iterator it;
        int i=0;
        for (it = evRange.begin(); it != evRange.end() && !false; ++it, i++){
            if (pkt->getAddr() >= it->start() && pkt->getAddr() <= it->end()){
                ar=EVQ;
                lane_num=i;
            }
        }
        for (it = obRange.begin(), i=0; it != obRange.end() && !false; ++it, i++){
            if (pkt->getAddr() >= it->start() && pkt->getAddr() <= it->end()){
                ar=OPB;
                lane_num=i;
            }
        }
        for (it = execRange.begin(), i=0; it != execRange.end() && !false; ++it, i++){
            if (pkt->getAddr() >= it->start() && pkt->getAddr() <= it->end()){
                ar=EXEC;
                lane_num=i;
            }
        }
        for (it = statRange.begin(), i=0; it != statRange.end() && !false; ++it, i++){
            if (pkt->getAddr() >= it->start() && pkt->getAddr() <= it->end()){
                ar=STAT;
                lane_num=i;
            }
        }
    }

    if (ar==EXEC){
        DPRINTF(UpDownBASim, "NWID:%d, Exec: Inferred Lane Num:%ld\n",
                            nwid, lane_num);
        if (gem5::curTick() < least_poss_exec_cycle[lane_num]){
            schedule(new gem5::EventFunctionWrapper([this, lane_num]{ execute(&lane_num); },
                                              name() + ".execute", true),
                    least_poss_exec_cycle[lane_num]);
        }else{
            schedule(new gem5::EventFunctionWrapper([this, lane_num]{ execute(&lane_num); },
                                              name() + ".execute", true),
                        gem5::curTick()+period);
        }
    }
    else if (ar==EVQ){
        //Write event into lane
        uint8_t *ledata = new uint8_t[wordSize];
        pkt->writeData(ledata);
        DDUMP(UpDown, ledata, wordSize);
        uint64_t edata = basim::bytestoword(ledata);
        int numOb = ((edata >> 20) & 0x7)+ 2;
        DPRINTF(UpDownBASim, "NWID:%d, Lane_num: %d Writing event data: Num Operands:%d, num recieved%d\n", 
                            nwid, lane_num, numOb, cur_opnum[lane_num]);
        DPRINTF(UpDownBASim, "NWID:%d, Lane_num: %d Writing event data 1: %lu\n", lane_num, edata);
        // Need to collect data in a buffer before pushing into basim
        assert(numOb == (cur_opnum[lane_num] -1) && "Number of Operands received do not match event_word encoding");
        cpu_ops[lane_num]->setNumOperands(numOb);
        cpu_ops[lane_num]->setData(&cpu_ops_temp[lane_num][1]);

        // Update the top event label based on symbol map
        basim::eventword_t temp_ev = basim::EventWord(edata);
        temp_ev.setEventLabel(symbolMap[temp_ev.getEventLabel()]);
        cpu_ev[lane_num]->eventword = temp_ev.eventword;
        
        cur_opnum[lane_num] = 0;
        cpu_evops[lane_num].eventword = cpu_ev[lane_num];
        cpu_evops[lane_num].operands = cpu_ops[lane_num];
        udaccel->pushEventOperands(cpu_evops[lane_num], lane_num);
        upstats.numEvents[lane_num]++;
        delete ledata;
        delete cpu_ev[lane_num];
        delete cpu_ops[lane_num];
    } else if (ar==OPB){
        //Write operands into lane
        uint8_t *ledata = new uint8_t[wordSize];
        pkt->writeData(ledata);
        DDUMP(UpDown, ledata, wordSize);
        uint64_t edata =  basim::bytestoword(ledata);
        if (cur_opnum[lane_num] == 0){
            cpu_ev[lane_num] = new basim::EventWord();
            cpu_ops[lane_num] = new basim::Operands();
        } else{
            cpu_ops_temp[lane_num][cur_opnum[lane_num]] = edata;
        }
        cur_opnum[lane_num]++;
        DPRINTF(UpDownBASim, "NWID:%d, Lane_num:%d Writing operand data: %ld\n", nwid, lane_num, edata);
        delete ledata;
    } else if (ar==SPD){
        uint8_t *ledata = new uint8_t[wordSize];
        pkt->writeData(ledata);
        DDUMP(UpDown, ledata, wordSize);
        gem5::Addr saddr = pkt->getAddr(); // - sRange.start();
        udaccel->writeScratchPad(wordSize, saddr, ledata);
        upstats.lm_store_bytes_top += pkt->getSize();
        delete ledata;
    } else if (ar==STAT){
        statStore[lane_num] = 0;
    }else{
        fatal("Invalid Address\n");
    }
}


void
UpDownBASim::execute(const int *ln){
    int lane_num = *ln;
    exec_stat[lane_num] = true;
    DPRINTF(UpDownBASim, "NWID:%d Lane:%d Execute EFA, EvQSize:%d\n", 
                        nwid, lane_num, udaccel->getEventQSize(lane_num));
    udaccel->simulate(lane_num, NUMTICKS, gem5::curTick());
    upstats.lane_busy_cycles[lane_num]++;
    least_poss_exec_cycle[lane_num] = gem5::curTick()+ period*1; // This needs to be changed to be parametric
    if (udaccel->sendReady(lane_num)){
        postTick(&lane_num);
    }

    if (!udaccel->isIdle(lane_num)){
        schedule(new gem5::EventFunctionWrapper([this, lane_num]{ execute(&lane_num); },
                                      name() + ".execute", true),
             gem5::curTick() + period);
    } else
        exec_stat[lane_num] = false;
}

basim::networkid_t
UpDownBASim::getDestForAddr(basim::networkid_t netid, gem5::Addr pol_addr){
    // To be implemented in translation memory
    return netid; 
}

void
UpDownBASim::postTick(int* ln){
    // Get the Message from the sendbuffer
    int lane_num = *ln;
    sendmsg_t* sm_intf = new sendmsg_t;
    //std::unique_ptr<basim::MMessage> m(std::move(udaccel->getSendMessage(lane_num)));
    basim::MMessagePtr m = (udaccel->getSendMessage(lane_num)).release();
    sm_intf->ssize = m->getLen() * WORDSIZE;
    sm_intf->sm_trans_id = global_sm_trans_id++;
    DPRINTF(UpDownBASim, "NWID:%d, Lane:%d Trans:%lu\n", nwid, lane_num, sm_intf->sm_trans_id);
    switch(m->getType()){
        case basim::MType::M1Type:
        case basim::MType::M3Type:
        case basim::MType::M4Type:
        {
            // Send Message to another lane
            basim::eventword_t ev = m->getXe();
            //basim::operands_t* op0 = new basim::operands_t(m->getLen(), m->getXc());  
            basim::operands_t op0(m->getLen(), m->getXc());  // num opernads + cont
            op0.setData((m->getpayload()));
            basim::eventoperands_t eops(&ev, &op0);
            uint32_t dest_nwid = ev.getNWID().networkid;
            uint32_t dest_lane_num = ev.getNWID().getLaneID();
            uint32_t dest_stack = ev.getNWID().getStackID();
            uint32_t dest_node = ev.getNWID().getNodeID();
            uint32_t dest_ud = ev.getNWID().getUDID();
        #ifdef SENDPOLICY // only policy 7 here
            int policy = (ev.getNWID()).getSendPolicy();
            if(policy == 7){
                gem5::Addr policy_addr = op0[1];
                basim::network_id dst = getDestForAddr(ev.getNWID(), policy_addr);
                dest_nwid = dst.networkid;
                dest_lane_num = dst.getLaneID();
                dest_stack = dst.getStackID();
                dest_node = dst.getNodeID();
                dest_ud = dst.getUDID();
            }
        #endif
            uint32_t src_node = basim::networkid_t(this->nwid).getNodeID();
            uint32_t src_stack = basim::networkid_t(this->nwid).getStackID();
            uint32_t src_ud = basim::networkid_t(this->nwid).getUDID();

            if ((dest_nwid & 0xFFFFFFC0) == this->nwid){ 
                // Headed for same UD
                DPRINTF(UpDownBASim, "NWID:%d, Lane:%d\n", dest_nwid, dest_lane_num);
                udaccel->pushEventOperands(eops, dest_lane_num);
                if(!exec_stat[dest_lane_num])
                    schedule(new gem5::EventFunctionWrapper([this, dest_lane_num]{ execute(&dest_lane_num); },
                                              name() + ".execute", true),
                    gem5::curTick() + LANE_LANE_ACC_LATENCY * period);
                upstats.numEvents[dest_lane_num]++;
            } else{
                DPRINTF(UpDownBASim, "NWID:%d, Dest NWID:%d\n", this->nwid, dest_nwid);
                
                // Get the EventQ address to which this packet has to be sent
                uint64_t destCtrlAddr = getEventQueueAddr(dest_nwid, upCtrlAddrBase, 32);
                
                // Create the request
                uint32_t udPort_num = (lane_num) % (num_ud_channels); 

                uint32_t pktsize = wordSize; // operand+event

                gem5::Request::Flags reqflags = gem5::Request::UNCACHEABLE;

                gem5::RequestPtr reqptr = std::make_shared<gem5::Request>((gem5::Addr)destCtrlAddr, 
                                    pktsize, 
                                    reqflags, 
                                    updown_system_id);
                
                // Creat the gem5 packet
                gem5::Packet *pkt1;

                pkt1 = new gem5::Packet(reqptr, gem5::MemCmd::UDSend);

                pkt1->allocate(); // Not sure if this is actually needed. Probably is.
                // Put the message in the packet

                pkt1->udmsg = m;
                pkt1->eops = &eops; // This is redundant, but will replace m above
                pkt1->mtype = MessageType::NW;

                // These nwids needed? 
                pkt1->setsrcnwid(this->nwid);
                pkt1->setdstnwid(dest_nwid);
                // Hack to make cluster latency 10 cycles
                uint64_t sched_time;
                if(src_stack == dest_stack && src_node == dest_node){
                    sched_time = period * LANE_LANE_CLUSTER_LATENCY;
                }
                else
                    sched_time = period;

                upstats.bytesSent_InterUDMessages += pktsize;  // remove event and continuation?
                DPRINTF(UpDownBASim, "NWID:%d DestUD:%d: %lx\n", this->nwid, dest_nwid, pkt1->getAddr());
                DPRINTF(UpDownBASim, "SRCStack:%d DestStack:%d: %lx\n", src_stack, dest_stack, pkt1->getAddr());

                schedule(new gem5::EventFunctionWrapper([this, pkt1, udPort_num]{ udOutPorts[udPort_num].sendPacket(pkt1, 1); },
                                                  name() + ".SendMessage", true),
                         gem5::curTick() + sched_time);

                ud_reqs.insert(std::pair<uint64_t, sendmsg_tptr>(sm_intf->sm_trans_id, sm_intf));
            }

            break;
        }
        case (basim::MType::M2Type):
        case (basim::MType::M3Type_M):
        case (basim::MType::M4Type_M):
        {
            // Send to Memory
            sm_intf->msg = m;
            basim::eventword_t cont = m->getXc();
            if (m->isStore()){
                // Get data from message (this could potentially be skipped)
                sm_intf->sdata = (reinterpret_cast<uint8_t*>((m->getpayload())));
            }else {
                sm_intf->sdata = nullptr;
            }
            sm_intf->sdest = m->getdestaddr();
            sm_intf->sdest_VA = sm_intf->sdest;
            int sendPort = (sm_intf->sdest >> 6) % num_mc;
            gem5::Request::Flags reqflags = gem5::Request::UNCACHEABLE;
            if (sm_intf->ssize > 1 && ((dblksize - (sm_intf->sdest % dblksize)) < sm_intf->ssize)){
                // gem5 stuff
                sm_intf->partial = true;
                int bytesleft = m->getLen() * WORDSIZE;
                int dataindex = 0;
                while (bytesleft > 0){
                    gem5::RequestPtr reqptr;
                    if (sm_intf->num_partials==0){
                        int size = dblksize - (sm_intf->sdest % dblksize);
                        DPRINTF(UpDownBASim, "NWID:%d, Before Translation:%lu sdest 0x%lx\n",
                                            nwid, sm_intf->sm_trans_id, sm_intf->sdest);
                        uint64_t sdest_pa = this->udtrans_table.getPA(sm_intf->sdest);
                        DPRINTF(UpDownBASim, "NWID:%d After Translation:%lu sdest 0x%lx\n", 
                                            nwid, sm_intf->sm_trans_id, sdest_pa);
                        reqptr = std::make_shared<gem5::Request>((gem5::Addr)sdest_pa, 
                                            size, reqflags, updown_system_id);
                        dataindex = sm_intf->ssize - bytesleft;
                        bytesleft -= size;
                        sm_intf->num_partials++;
                        DPRINTF(UpDownBASim, "NWID:%d Partial packet : %d, Request size :%d, BytesLeft:%d, index:%d\n", 
                                               nwid, sm_intf->num_partials, reqptr->getSize(), bytesleft, dataindex);
                    }else if (bytesleft > dblksize){
                        uint64_t ndest = sm_intf->sdest + dblksize*(sm_intf->num_partials-1) + (dblksize - (sm_intf->sdest%dblksize));
                        DPRINTF(UpDownBASim, "NWID:%d Before Translation:%lu sdest 0x%lx\n", 
                                                nwid, sm_intf->sm_trans_id, ndest);
                        uint64_t ndest_pa = this->udtrans_table.getPA(ndest);
                        DPRINTF(UpDownBASim, "NWID:%d, After Translation:%lu sdest 0x%lx\n", 
                                                nwid, sm_intf->sm_trans_id, ndest_pa);
                        reqptr = std::make_shared<gem5::Request>((gem5::Addr)ndest_pa, 
                                             dblksize, reqflags, updown_system_id);
                        sm_intf->num_partials++;
                        dataindex = sm_intf->ssize - bytesleft;
                        bytesleft -= dblksize;
                        DPRINTF(UpDownBASim, "NWID:%d Partial packet : %d, Request size :%d, BytesLeft:%d, index:%d\n", 
                                             nwid, sm_intf->num_partials, reqptr->getSize(), bytesleft, dataindex);
                    }else{
                        uint64_t ndest = sm_intf->sdest + dblksize*(sm_intf->num_partials-1) + (dblksize - (sm_intf->sdest%dblksize));
                        DPRINTF(UpDownBASim, "NWID:%d Before Translation:%lu sdest 0x%lx\n", 
                                            nwid, sm_intf->sm_trans_id, ndest);
                        uint64_t ndest_pa = this->udtrans_table.getPA(ndest);
                        DPRINTF(UpDownBASim, "NWID:%d After Translation:%lu sdest 0x%lx\n", 
                                            nwid, sm_intf->sm_trans_id, ndest_pa);
                        reqptr = std::make_shared<gem5::Request>((gem5::Addr)ndest_pa, 
                                                                  bytesleft, reqflags, 
                                                                  updown_system_id);
                        sm_intf->num_partials++;
                        dataindex = sm_intf->ssize - bytesleft;
                        bytesleft -= bytesleft;
                        DPRINTF(UpDownBASim, "NWID:%d, Partial packet : %d, Request size :%d, BytesLeft:%d, index:%d\n",
                                                nwid, sm_intf->num_partials, reqptr->getSize(), bytesleft, dataindex);
                    }
                    reqptr->setTransID(sm_intf->sm_trans_id);
                    gem5::Packet *pkt1;
                    if (!m->isStore()){
                        pkt1 = new gem5::Packet(reqptr, gem5::MemCmd::ReadReq);
                        pkt1->allocate(); // Not sure if this is actually needed. Probably is.
                        upstats.dram_load_bytes_acc += pkt1->getSize();
                    }
                    else{
                        pkt1 = new gem5::Packet(reqptr, gem5::MemCmd::WriteReq);
                        pkt1->allocate(); // Not sure if this is actually needed. Probably is.
                        pkt1->setData(&sm_intf->sdata[dataindex]); // Change this to point to correct array index
                        upstats.dram_store_bytes_acc += pkt1->getSize();
                    }
                    DPRINTF(UpDownBASim, "NWID:%d Writing packet into map: trans_id:%d\n", 
                                        nwid, sm_intf->sm_trans_id);
                    DDUMP(UpDown, pkt1->getConstPtr<uint8_t>(), pkt1->getSize());

                    std::map<uint64_t, sendmsg_tptr>::iterator it;
                    it = mem_reqs.find(sm_intf->sm_trans_id);
                    if (it == mem_reqs.end())
                        mem_reqs.insert(std::pair<uint64_t, sendmsg_tptr>(sm_intf->sm_trans_id, sm_intf));
                    else
                        mem_reqs[sm_intf->sm_trans_id] = sm_intf;
                    DPRINTF(UpDownBASim, "NWID:%d Checking packet Packet:%lx MemReqTrans:%d\n",
                            this->nwid, pkt1->getAddr(), mem_reqs[sm_intf->sm_trans_id]->sm_trans_id);
                    schedule(new gem5::EventFunctionWrapper([this, pkt1, sendPort]
                        { memPorts[sendPort].sendPacket(pkt1, 1); },
                                                  name() + ".SendMessage", true),
                         clockEdge(gem5::Cycles(latency)));
                    DPRINTF(UpDownBASim, "NWID:%d Trans:%ld:%ld sent to memory Port:%d with addr: %lx\n",
                            nwid, (pkt1->req)->getTransID(), sm_intf->sm_trans_id, sendPort, pkt1->getAddr());
                }
                // Allocate the data buffer here itself?
            } else{
                // the full 64B
                sm_intf->partial = false;
                uint64_t sdest_pa = this->udtrans_table.getPA(sm_intf->sdest);
                gem5::RequestPtr reqptr = std::make_shared<gem5::Request>((gem5::Addr)sdest_pa, 
                                            sm_intf->ssize, reqflags, updown_system_id);
                sm_intf->num_partials = 0;
                sm_intf->num_recvd = 0;
                sm_intf->num_recvd = 0;
                DPRINTF(UpDownBASim, "NWID:%d, 64B packet : %d, Request size :%d\n", 
                                           nwid, sm_intf->num_partials, reqptr->getSize());

                reqptr->setTransID(sm_intf->sm_trans_id);
                gem5::Packet *pkt1;
                if (!m->isStore()){
                    pkt1 = new gem5::Packet(reqptr, gem5::MemCmd::ReadReq);
                    pkt1->allocate(); // Not sure if this is actually needed. Probably is.
                    upstats.dram_load_bytes_acc += pkt1->getSize();
                }
                else{
                    pkt1 = new gem5::Packet(reqptr, gem5::MemCmd::WriteReq);
                    pkt1->allocate(); // Not sure if this is actually needed. Probably is.
                    pkt1->setData(sm_intf->sdata); 
                    upstats.dram_store_bytes_acc += pkt1->getSize();
                }
                DPRINTF(UpDownBASim, "NWID:%d, Writing packet into map: trans_id:%d\n", 
                                    nwid, sm_intf->sm_trans_id);
                DDUMP(UpDown, pkt1->getConstPtr<uint8_t>(), pkt1->getSize());

                std::map<uint64_t, sendmsg_tptr>::iterator it;
                mem_reqs.insert(std::pair<uint64_t, sendmsg_tptr>(sm_intf->sm_trans_id, sm_intf));
                DPRINTF(UpDownBASim, "NWID:%d, Checking packet Packet:%lx MemReqTrans:%d\n",
                        this->nwid, pkt1->getAddr(), mem_reqs[sm_intf->sm_trans_id]->sm_trans_id);
                schedule(new gem5::EventFunctionWrapper([this, pkt1, sendPort]
                    { memPorts[sendPort].sendPacket(pkt1, 1); },
                                              name() + ".SendMessage", true),
                     clockEdge(gem5::Cycles(latency)));
                DPRINTF(UpDownBASim, "NWID:%d, Trans:%ld:%ld sent to memory Port:%d with addr: %lx\n",
                            nwid, (pkt1->req)->getTransID(), sm_intf->sm_trans_id, sendPort, pkt1->getAddr());
            }
            break;
        }
        default:
            BASIM_ERROR("Undefined Message type in Send Buffer");
            break;
        }
    //udaccel->removeSendMessage(lane_num);
}

void
UpDownBASim::read(gem5::PacketPtr pkt)
{
    // Size is always in bytes in packets Check if > 65536 then 
    // do it lane by lane
    DPRINTF(UpDownBASim, "NWID:%d Reading %s\n", nwid, pkt->print());

    DDUMP(UpDown, pkt->getConstPtr<uint8_t>(), wordSize);
    if (pkt->getAddr() >= sRange.start() && pkt->getAddr() < sRange.end()){
        int lane_num = (pkt->getAddr() - sRange.start())/(scratchsize / UD_NUM_LANES);
        DPRINTF(UpDownBASim, "NWID:%d, ScratchPad Read Lane:%d Addr: %lx, sStart :%lx\n", 
                        nwid, lane_num, pkt->getAddr(), sRange.start());
        basim::Addr laneaddr = (pkt->getAddr()); 
        uint8_t *ledata; 
        uint32_t size = pkt->getSize();
        ledata = new uint8_t[size];
        udaccel->readScratchPad(size, laneaddr, ledata);
        upstats.lm_load_bytes_top += size;
        DPRINTF(UpDownBASim, "NWID:%d Scratch Read Output:%d\n", nwid, ledata[0]);
        pkt->setData(ledata);
        DDUMP(UpDown, ledata, pkt->getSize());
        delete ledata;
    }
}


gem5::AddrRangeList
UpDownBASim::getAddrRanges() const
{
    // Just use the same ranges as whatever is on the memory side.
    gem5::AddrRangeList returnRange;
    //returnRange.merge(upAddrRange);
    for (auto const &i: upAddrRange)
        returnRange.push_back(i);
    for (auto const &i: upCtrlAddrRange)
        returnRange.push_back(i);
    return returnRange;
}

void
UpDownBASim::sendRangeChange() const
{
    for (auto& port : cpuPorts) {
        port.sendRangeChange();
    }
}

