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

#include <iostream>
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <thread>
#include <future>
#include <thread>
#include <chrono>
#include <iostream>
#include <inttypes.h>
#include "base/random.hh"
#include "base/types.hh"
#include "debug/UpDown.hh"
#include "sim/system.hh"
#include "mem/packet.hh"
#include "updown_obj/updown_obj.hh"
#include "updown_obj.hh"
#include "base/output.hh"
#include "base/callback.hh"
#include "base/random.hh"
#include "base/types.hh"
#include "debug/UpDown.hh"
#include "sim/system.hh"
#include "string.h"
#include "debug/AddrRanges.hh"
#include "updown/simruntime/include/upstream_pyintf.hh"
#include "mem/request.hh"
#define NUMLANES 64

using namespace std::chrono_literals;
using namespace gem5;
//struct emulator_stats;

UpDownObj::UpDownObj(const gem5::UpDownObjParams &params) :
    ClockedObject(params),
    blocked_cpu(false), blocked_mem(false), blocked_ud(false), originalPacket(nullptr), waitingPortId(-1),
    upstats(*this),
    latency(params.latency),
    nwid(params.nwid),
    udidx(params.udidx),
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
    registerExitCallback([this]() {  delete this->upstream_pyintf; });

    upAddrRange.push_back(params.addrRange);
    upCtrlAddrRange.push_back(params.ctrladdrRange);
    uint64_t upCtrlAddrBase_local = params.ctrladdrRange.start();
    udidx = params.udidx;
    nwid = params.nwid;
    num_outstanding_cpu = 0;
    uint32_t node_id = (uint32_t)(nwid &0x07fff800) >> 11;
    DPRINTF(UpDown, "Setting addresses for UDID:%d, NWID:%d\n", udidx, nwid);
    sRange = params.addrRange;

    for(int i=0; i< NUMLANES; i++){
        gem5::AddrRange eRange = gem5::AddrRange(upCtrlAddrBase_local+i*32, upCtrlAddrBase_local+i*32+7);
        gem5::AddrRange oRange = gem5::AddrRange(upCtrlAddrBase_local+i*32+8, upCtrlAddrBase_local+i*32+15);
        gem5::AddrRange exRange = gem5::AddrRange(upCtrlAddrBase_local+i*32+16, upCtrlAddrBase_local+i*32+23);
        gem5::AddrRange stRange = gem5::AddrRange(upCtrlAddrBase_local+i*32+24, upCtrlAddrBase_local+i*32+31);
        DPRINTF(AddrRanges, "Lane:%d, EventAddrRange: %lx-%lx\n",i, eRange.start(), eRange.end());
        DPRINTF(AddrRanges, "Lane:%d, OpRange: %lx-%lx\n",i, oRange.start(), oRange.end());
        DPRINTF(AddrRanges, "Lane:%d, statRange: %lx-%lx\n", i, stRange.start(), stRange.end());
        DPRINTF(AddrRanges, "Lane:%d, ExecRange: %lx-%lx\n", i, exRange.start(), exRange.end());
        evRange.push_back(eRange);
        obRange.push_back(oRange);
        execRange.push_back(exRange);
        statRange.push_back(stRange);
    }
    DPRINTF(AddrRanges, "sRange: %lx-%lx\n",sRange.start(), sRange.end());
    for(auto i=0; i < UD_NUM_LANES; i++){
        statStore[i] = 0;
    }
    updown_id = params.system->getRequestorId(this, "data");
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

    eventtime = new gem5::Tick[num_mc];
    for (int i = 0; i < num_mc; i++) {
        eventtime[i]=0;
    }

    //DPRINTF(UpDown, "Creating the UpDown %d lanes."
    //                    "Scratchpad size is %d!\n", params.numlanes, scratchsize);
    progname = params.efa;
    progfile = params.progfile;
    simdir = params.simdir;
    lm_mode = params.lm_mode;
    lmsize = params.lmsize;
    recode_endianness=params.recode;
    uint64_t lmbase = sRange.start();
    upstream_pyintf = new Upstream_PyIntf(nwid, udidx, numlanes, progfile, progname, simdir, lm_mode, lmsize, lmbase, gem5::simout.directory(), gem5::sim_clock::Frequency, params.print_level, params.print_threshold, params.perf_log_enable, params.perf_log_internal_enable);
    int fd = -1;
    std::string s = "./" + simdir + "/" + "ud" + std::to_string(udidx) +"_send.txt";
    char *filename = s.c_str();
    if((fd = open(filename, O_RDWR, 0)) == -1){
        printf("unable to open %s\n", filename);
        exit(EXIT_FAILURE);
    }
    sendmap = (uint32_t*) mmap(NULL, 8*64*262144*sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(sendmap == MAP_FAILED){
     printf("SendMap Failed\n");
      exit(EXIT_FAILURE);
    }
    for(int i=0; i < numlanes; i++){
        execstart[i]=0; 
        execstop[i]=0; 
        prev_yield_cycles[i]=0;
        prev_yield_term_cycles[i]=0;
        least_poss_exec_cycle[i]=0;
        num_outstanding_exec_events[i]=0;
        active_thrds[i]=0;
    }
    // One entry for now
    udtrans_table = UDTranslations(node_id, this->nwid); 
    int num_entries = params.lseg_size/ params.lseg_block_size;
    //pa_start = lseg_start + base_phys + (j/nstacks)*block_size + ((j%nstacks) * stack_size)
    for(int i = 0;i < num_entries; i++){
        udtrans_entry ud_entry;
        uint64_t va_start;
        ud_entry.ttype = TransType::Local;
        ud_entry.base = params.lseg_start + params.lseg_block_size * i;
        ud_entry.pa_base = params.pa_base + params.lseg_start + (i / (params.num_stacks))* params.lseg_block_size + (i%(params.num_stacks)) * params.stack_size;
        //ud_entry.offset = params.pa_base + (i/params.num_stacks)*params.lseg_block_size + (i%params.num_stacks)*(1UL <<34); 
        //ud_entry.offset = -params.lseg_block_size*i + (i%params.num_stacks)*(1UL <<34); 
        ud_entry.limit = params.lseg_start + params.lseg_block_size * (i+1); //0x7FFFFFFF; //0x2000000000;
        DPRINTF(UpDown, "Local Entry: base:%lx, pa_base:%lx, limit:%lx\n", ud_entry.base, ud_entry.pa_base, ud_entry.limit);
        udtrans_table.addTranslation(ud_entry);
    }
    num_entries = params.gseg_size/ params.gseg_block_size;
    uint64_t pa_start_addr = params.lseg_start + params.lseg_size/params.num_stacks;
    //pa_start = gseg_start + int(j / (nstacks*nnodes))*gblock_size + (j%(nstacks*nnodes))*stack_size 
    for(int i = 0;i < num_entries; i++){
        udtrans_entry ud_entry;
        uint64_t va_start;
        ud_entry.ttype = TransType::Global;
        ud_entry.base = params.gseg_start + params.gseg_block_size * i;
        ud_entry.pa_base = pa_start_addr + (i/(params.num_stacks * params.num_nodes))*params.gseg_block_size + (i% (params.num_stacks*params.num_nodes))*(params.stack_size); 
        //ud_entry.offset = -params.gseg_block_size*i + (i% (params.num_stacks*params.num_nodes))*(1UL <<34); 
        ud_entry.limit = params.gseg_start + params.gseg_block_size * (i+1); //0x7FFFFFFF; //0x2000000000;
        DPRINTF(UpDown, "Global Entry: base:%lx, pa_base:%lx, limit:%lx\n", ud_entry.base, ud_entry.pa_base, ud_entry.limit);
        udtrans_table.addTranslation(ud_entry);
    }
}

void
UpDownObj::init(){
    //for (auto& port : udInPorts) {
    //    if(port.isConnected())
    //        port.sendRangeChange();
    //}
    for (auto& port : cpuPorts) {
        if(port.isConnected())
            port.sendRangeChange();
    }
}


void 
UpDownObj::UpDownStats::regStats()
{
    using namespace statistics;

    statistics::Group::regStats();

    const auto num_lanes = upobj.numlanes;

    cyclesPerEvent.init(20);
    //cyclesPerThread.init(20);

    numEvents.init(num_lanes);
    numActions.init(num_lanes);
    numTransitions.init(num_lanes);
    numInstructions.init(num_lanes);
    numVertices.init(num_lanes);
    numEdges.init(num_lanes);
    MessageInstructions.init(num_lanes);
    MovInstructions.init(num_lanes);
    BranchInstructions.init(num_lanes);
    ALUInstructions.init(num_lanes);
    YieldInstructions.init(num_lanes);
    CompareInstructions.init(num_lanes);
    AtomicInstructions.init(num_lanes);
    numThreads.init(num_lanes);
    upLaneBusyCycles.init(num_lanes);
    upLaneIdleCycles_old.init(num_lanes);
    upLaneExecCycles.init(num_lanes);
    upLaneStallCycles.init(num_lanes);
    upLaneIdleCycles.init(num_lanes);
    upLmReadBytes.init(num_lanes);
    upLmWriteBytes.init(num_lanes);
    upLaneEventQMax.init(num_lanes);
    upLaneEventQMean.init(num_lanes);
    upLaneOperandQMax.init(num_lanes);
    upLaneOperandQMean.init(num_lanes);
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

    avgThreadExecCycles.flags(nonan).precision(2);
    upLaneEventQMean.flags(nonan).precision(2);
    upLaneOperandQMean.flags(nonan).precision(2);      

    for (int i = 0; i < num_lanes; i++) {
        const std::string  lane = std::string("Lane[") + std::to_string(i) + std::string("]");
        numEvents.subname(i, lane);
        numActions.subname(i, lane);
        numThreads.subname(i, lane);
        avgThreadExecCycles.subname(i, lane);
        numTransitions.subname(i, lane);
        numInstructions.subname(i, lane);
        MessageInstructions.subname(i, lane);
        MovInstructions.subname(i, lane);
        BranchInstructions.subname(i, lane);
        ALUInstructions.subname(i, lane);
        YieldInstructions.subname(i, lane);
        CompareInstructions.subname(i, lane);
        AtomicInstructions.subname(i, lane);
        numThreads.subname(i, lane);
        upLaneBusyCycles.subname(i, lane);
        upLaneIdleCycles_old.subname(i, lane);
        upLaneExecCycles.subname(i, lane);
        upLaneStallCycles.subname(i, lane);
        upLaneIdleCycles.subname(i, lane);
        upLmReadBytes.subname(i, lane);
        upLmWriteBytes.subname(i, lane);
        upLaneEventQMax.subname(i, lane);
        upLaneEventQMean.subname(i, lane);
        upLaneOperandQMax.subname(i, lane);
        upLaneOperandQMean.subname(i, lane);
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
    avgThreadExecCycles = upLaneBusyCycles/numThreads;
    avgDmLmSendLatency = TotalLat_SendsDmLm/numSends_DmLm;
    avgInterLaneSendLatency = TotalLat_SendsInterLane/numSends_InterLane;

    // More calculations on the stats here

}


gem5::Port &
UpDownObj::getPort(const std::string &if_name, gem5::PortID idx)
{
    // This is the name from the Python UpDownObj
    // declaration in UpDownObj.py
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
UpDownObj::CPUSidePort::sendPacket(gem5::PacketPtr pkt, int ins_new)
{

    if(blockedPacket_vec.size()>0 && ins_new){
        blockedPacket_vec.push_back(pkt);
        DPRINTF(UpDown, "CPUSidePort: Outstanding packets adding to blocked queue %s, Size:%d \n", pkt->print(), blockedPacket_vec.size());
        return;
    }

    // If we can't send the packet across the port, store it for later.
    DPRINTF(UpDown, "Sending %s to CPU\n", pkt->print());
    if (!sendTimingResp(pkt)) {
        DPRINTF(UpDown, "failed pushing to blocked queue!\n");
        if(ins_new)
            blockedPacket_vec.push_back(pkt);
    }else{
        DPRINTF(UpDown, "Successfully sent to CPU\n");
        if(!ins_new)
            blockedPacket_vec.erase(blockedPacket_vec.begin());
    }
}


gem5::AddrRangeList
UpDownObj::CPUSidePort::getAddrRanges() const
{
    return owner->getAddrRanges();
}


void
UpDownObj::CPUSidePort::trySendRetry()
{
    if (needRetry && blockedPacket_vec.size() == 0) {
        // Only send a retry if the port is now completely free
        needRetry = false;
        DPRINTF(UpDown, "Sending retry req, %d\n", owner->num_outstanding_cpu);
        sendRetryReq();
    }
}

gem5::Tick 
UpDownObj::CPUSidePort::recvAtomic(gem5::PacketPtr pkt)
{
    pkt->setCPUport(this->id);
    owner->handleCPUFunctional(pkt);
    return gem5::curTick();
}


void
UpDownObj::CPUSidePort::recvFunctional(gem5::PacketPtr pkt)
{
    // Just forward to the downstream.
    if(pkt->mtype == MessageType::NW){
        return owner->handleUDFunctional(pkt);
    }else{
        pkt->setCPUport(this->id);
        return owner->handleCPUFunctional(pkt);
    }
}


bool
UpDownObj::CPUSidePort::recvTimingReq(gem5::PacketPtr pkt)
{
    if(pkt->mtype == MessageType::NW){
        DPRINTF(UpDown, "Got timing request %s from UD:%d on port:%d \n", pkt->print(), pkt->getsrcnwid(), this->id);
        // update stats
        (owner->upstats).InterUDMessageLatency += (gem5::curTick() - pkt->getSendtick());
        (owner->upstats).num_InterUDMessages++; 
        (owner->upstats).bytesReceived_InterUDMessages += ((pkt->numOb+2)*8);  // remove event and continuation?
        if (needRetry) {
            // The downstream may not be able to send a reply if this is blocked
            DPRINTF(UpDown, "UD Request blocked\n");
            return false;
        }

        pkt->setCPUport(this->id);
        // Just forward to the cache. ??
        if (!owner->handleUDRequest(pkt, this->id)) {
            DPRINTF(UpDown, "UD Request failed\n");
            // stalling
            needRetry = true;
            return false;
        } else {
            DPRINTF(UpDown, "UD Request succeeded\n");
            return true;
        }

    }else{
        DPRINTF(UpDown, "Got timing request %s from CPU port ID:%d\n", pkt->print(), this->id);
        pkt->setCPUport(this->id);
        owner->num_outstanding_cpu++;
        DPRINTF(UpDown, "Set port ID:%d in packet, outstanding:%d \n", pkt->getCPUport(), owner->num_outstanding_cpu);

        if (needRetry) {
            // The downstream may not be able to send a reply if this is blocked
            DPRINTF(UpDown, "UD Request blocked, outstanding:%d\n", owner->num_outstanding_cpu);
            return false;
        }

        // Just forward to the cache. ??
        if (!owner->handleCPURequest(pkt, id)) {
            DPRINTF(UpDown, "CPU Request failed, outstanding:%d\n", owner->num_outstanding_cpu);
            // stalling
            needRetry = true;
            return false;
        } else {
            owner->num_outstanding_cpu--;
            DPRINTF(UpDown, "CPU Request succeeded, outstanding:%d\n", owner->num_outstanding_cpu);
            return true;
        }
    }
}


void
UpDownObj::CPUSidePort::recvRespRetry()
{
    // We should have a blocked packet if this function is called.
    if(blockedPacket_vec.size() == 0){
        panic("Retry called when nothing blocked\n");
    }
    gem5::PacketPtr pkt = blockedPacket_vec.front();
    gem5::Tick latency_t = 1;

    // Grab the blocked packet.

    DPRINTF(UpDown, "Retrying response pkt %s, blocked_size %d to port %d\n", pkt->print(), blockedPacket_vec.size(),\
                        pkt->getCPUport());
    // Try to resend it. It's possible that it fails again.
    sendPacket(pkt, 0);
    if(blockedPacket_vec.size()>0){
        gem5::PacketPtr pkt_2_send = blockedPacket_vec.front();
        owner->schedule(new gem5::EventFunctionWrapper([this, pkt_2_send]{ (owner->cpuPorts[pkt_2_send->getCPUport()]).sendPacket(pkt_2_send, 0); },
                                      name() + ".sendPacket", true),
             gem5::curTick()+latency_t);
    }

    // We may now be able to accept new packets
    trySendRetry();
    DPRINTF(UpDown, "After all the Retrying blocked_size %d\n", blockedPacket_vec.size());
}

/*  UD Out Port Functions */


void
UpDownObj::UDSideOutPort::sendPacket(gem5::PacketPtr pkt, int ins_new)
{
    // Note: This flow control is very simple since the cache is blocking.
    int portid = id;
    gem5::Tick latency_t = 1;
    if(blockedPacket_vec.size() > 0 && ins_new){
        blockedPacket_vec.push_back(pkt);
    }else if(blockedPacket_vec.size() == 0 && ins_new){
        pkt->setSendtick(gem5::curTick());
        if(!sendTimingReq(pkt)){
            blockedPacket_vec.push_back(pkt);
        }
    }else{
        pkt->setSendtick(gem5::curTick());
        if(sendTimingReq(pkt)){
            blockedPacket_vec.erase(blockedPacket_vec.begin());
            if(blockedPacket_vec.size()>0){
                gem5::PacketPtr pkt_2_send = blockedPacket_vec.front();
                owner->schedule(new gem5::EventFunctionWrapper([this, pkt_2_send, portid]{(owner->udOutPorts[portid]).sendPacket(pkt_2_send, 0); },
                                              name() + ".sendPacket", true),
                     gem5::curTick()+owner->period);
                     //gem5::curTick()+latency_t);
            }

        }
    }
}


bool
UpDownObj::UDSideOutPort::recvTimingResp(gem5::PacketPtr pkt)
{

    std::map<uint64_t, struct sendmsg_intf *>::iterator it;
    struct sendmsg_intf *sm_intf; // = new struct sendmsg_intf();
    it = owner->ud_reqs.find((pkt->req)->getTransID());
    if(it != owner->ud_reqs.end()){
        owner->ud_reqs.erase(it);
        return true;
    }else{
        return true;
        //printf("\nThis should never happen: No entry in UD_Req\n");
        //exit(1);
    }
}

void
UpDownObj::UDSideOutPort::recvReqRetry()
{
    // We should have a blocked packet if this function is called.
    assert(blockedPacket_vec.size() > 0);

    // Grab the blocked packet.
    gem5::PacketPtr pkt = blockedPacket_vec.front();

    sendPacket(pkt, 0);
}

/* Memory Side Port Functions */

void
UpDownObj::MemSidePort::sendPacket(gem5::PacketPtr pkt, int ins_new)
{
    // Note: This flow control is very simple since the cache is blocking.
    int portid = id;
    gem5::Tick latency_t = 1;
    if(blockedPacket_vec.size() > 0 && ins_new){
        blockedPacket_vec.push_back(pkt);
    }else if(blockedPacket_vec.size() == 0 && ins_new){
        if(!sendTimingReq(pkt)){
            DPRINTF(UpDown, "Packet :%lu pushed into blockedPacket \n", pkt->getAddr());
            blockedPacket_vec.push_back(pkt);
        }else{
            DPRINTF(UpDown, "Packet :%lu sent to memory (sendPacket-1) \n", pkt->getAddr());
        }
    }else{
        if(sendTimingReq(pkt)){
            DPRINTF(UpDown, "Packet :%lu sent to memory (sendPacket-2) \n", pkt->getAddr());
            blockedPacket_vec.erase(blockedPacket_vec.begin());
            if(blockedPacket_vec.size()>0){
                gem5::PacketPtr pkt_2_send = blockedPacket_vec.front();
                owner->schedule(new gem5::EventFunctionWrapper([this, pkt_2_send, portid]{ (owner->memPorts[portid]).sendPacket(pkt_2_send, 0); },
                                              name() + ".sendPacket", true),
                     gem5::curTick()+owner->period);
                     //gem5::curTick()+latency_t);
            }

        }
    }
}


bool
UpDownObj::MemSidePort::recvTimingResp(gem5::PacketPtr pkt)
{
    std::map<uint64_t, struct sendmsg_intf *>::iterator it;
    struct sendmsg_intf *sm_intf; // = new struct sendmsg_intf();
    it = owner->mem_reqs.find((pkt->req)->getTransID());
    DPRINTF(UpDown, "MemSidePort Trans:%d Response for addr : %#x %s\n", (pkt->req)->getTransID(), pkt->getAddr(), pkt->print());
    if(it != owner->mem_reqs.end()){
        sm_intf = it->second;
        DPRINTF(UpDown, "PTID:%d, STID:%d\n", (pkt->req)->getTransID(), sm_intf->sm_trans_id);
        assert(sm_intf->sm_trans_id == (pkt->req)->getTransID());
        int lane_num = sm_intf->lane_id & 0x3f;
        if(owner->statStore[lane_num]==1){
        //if(owner->statStore[pkt->getAddr()+lane_num*8]==1){
            DPRINTF(UpDown, "Top requests in flight, pushing into Pending Queue:%d\n", owner->pending_response[lane_num].size());
            owner->pending_response[lane_num].push(pkt);
            //delete sm_intf;
            return true; // Return true to Memory sendtimingResponse function
        }else if(owner->pending_response[lane_num].size()>0){
            DPRINTF(UpDown, "%lu responses still in queue\n", owner->pending_response[lane_num].size());
            owner->pending_response[lane_num].push(pkt);
            DPRINTF(UpDown, "%lu Updated responses still in queue\n", owner->pending_response[lane_num].size());
            int num_remaining=owner->pending_response[lane_num].size();
            for(int i=0; i< num_remaining;i++){
                //gem5::PacketPtr pkt_rem = owner->pending_response[lane_num][i];
                gem5::PacketPtr pkt_rem = owner->pending_response[lane_num].front();
                if(owner->handleDRAMResponse(pkt_rem)){
                    DPRINTF(UpDown, "UDID:%d Lane:i%d Handled: %d\n",owner->udidx, lane_num, owner->pending_response[lane_num].size());
                    owner->pending_response[lane_num].pop(); //erase(owner->pending_response[lane_num].begin()+i);
                    DPRINTF(UpDown, "Lane_num:%d Remdaining pending responses: %d\n",lane_num, owner->pending_response[lane_num].size());
                }else{
                    printf("Error handling Response from pending queue \n");
                    exit(1);
                }
            }
            return true;
        
        }else{
            if(owner->handleDRAMResponse(pkt)){
                delete pkt;
                return true;
            }
            
        }
    }else{
        printf("Size of Map:%d, What's left ?\n", owner->mem_reqs.size());
        for(it=owner->mem_reqs.begin(); it != owner->mem_reqs.end(); ++it){
            printf("%d, ", (it->second)->sm_trans_id );
        }
        printf("\nThis should never happen: No entry in Mem_Req\n");
        exit(1);
    }
}

void
UpDownObj::MemSidePort::recvReqRetry()
{
    // We should have a blocked packet if this function is called.
    assert(blockedPacket_vec.size() > 0);

    // Grab the blocked packet.
    gem5::PacketPtr pkt = blockedPacket_vec.front();

    sendPacket(pkt, 0);
}


bool
UpDownObj::handleCPURequest(gem5::PacketPtr pkt, int port_id)
{
    if (blocked_cpu) {
        // There is currently an outstanding request so we can't respond. Stall
        return false;
    }

    DPRINTF(UpDown, "Got request for addr %#x\n", pkt->getAddr());

    // This upstream is now blocked waiting for the response to this packet.
    blocked_cpu = true;

    // Store the port for when we get the response
    assert(waitingPortId == -1);
    waitingPortId = port_id;

    accessCPUTiming(pkt);

    return true;
}

bool
UpDownObj::handleUDRequest(gem5::PacketPtr pkt, int port_id)
{
    //if (blocked_ud) {
    //    // There is currently an outstanding request so we can't respond. Stall
    //    return false;
    //}

    DPRINTF(UpDown, "Got UD request for addr %#x\n", pkt->getAddr());

    // This upstream is now blocked waiting for the response to this packet.
    //blocked_ud = true;

    // Store the port for when we get the response
    //assert(waitingPortId == -1);
    //waitingPortId = port_id;

    accessUDTiming(pkt);

    return true;
}



///////////////////// MEMORY ACCESS STORE

bool
UpDownObj::handleDRAMResponse(gem5::PacketPtr pkt)
{
    std::map<uint64_t, struct sendmsg_intf*>::iterator it;
    DPRINTF(UpDown, "Got response for addr %#x, Trans:%d\n", pkt->getAddr(), (pkt->req)->getTransID());
    DDUMP(UpDown, pkt->getConstPtr<uint8_t>(), pkt->getSize());
    struct sendmsg_intf *sm_intf; // = new struct sendmsg_intf();
    it = mem_reqs.find((pkt->req)->getTransID());
    uint64_t gs_id; // = sm_intf->sst_id; //super trans ID (use in super trans map)
    struct super_trans *strans;
    if(it != mem_reqs.end()){
        sm_intf = it->second;
        sm_intf->print_msg();
        DPRINTF(UpDown, "%s", sm_intf->sendmsg_str);
        if(sm_intf->partial){
            //int index = (pkt->getAddr() - sm_intf->sdest);
            int index = (this->udtrans_table.getVA(pkt->getAddr()) - sm_intf->sdest_VA);
            DPRINTF(UpDown, "Addr %#x, Trans:%d is at Index:%d\n", pkt->getAddr(), (pkt->req)->getTransID(), index);
            upstats.TotalLat_SendsDmLm+= (gem5::curTick() - sm_intf->lat_start[sm_intf->num_recvd]);
            if(sm_intf->partial_data==NULL)
                sm_intf->partial_data = new uint8_t[sm_intf->ssize];
            // figure out index and write to the right index!
            pkt->writeData(&sm_intf->partial_data[index]);
            sm_intf->bytes_recvd+=pkt->getSize();
            sm_intf->print_msg();
            DPRINTF(UpDown, "After bytes_recvd %s", sm_intf->sendmsg_str);
            sm_intf->num_recvd++;
            if(sm_intf->bytes_recvd!=sm_intf->ssize)
                return true;
            
        }else{
            DPRINTF(UpDown, "Addr %#x, Trans:%d Non Partial Data%d\n", pkt->getAddr(), (pkt->req)->getTransID());
            upstats.TotalLat_SendsDmLm+= (gem5::curTick() - sm_intf->lat_start[sm_intf->num_recvd]);
            if(sm_intf->partial_data==NULL)
                sm_intf->partial_data = new uint8_t[sm_intf->ssize];
            pkt->writeData(sm_intf->partial_data);
            sm_intf->bytes_recvd+=pkt->getSize();
            sm_intf->print_msg();
            DPRINTF(UpDown, "After bytes_recvd %s", sm_intf->sendmsg_str);
            sm_intf->num_recvd++;
            // Continue with the rest
        }
#ifdef MEM_ORDERING_DEPRECATED
        if(!sm_intf->smode_2){
            //Loads
            DPRINTF(UpDown, "Processing:%d\n", sm_intf->sm_trans_id);
            uint64_t cont = sm_intf->scont;
            uint64_t nwid = cont >> 32;
            uint32_t lane_num = nwid & 0x3f; 
            uint32_t dest_ud = (nwid & 0x1C0) >> 6; 
            DPRINTF(UpDown, "NWID:%ld Dest UD:%d: ThisUD%d\n", nwid, dest_ud, this->udidx);
            assert((nwid & 0xffffffC0) == (this->nwid & 0xffffffC0));
            DPRINTF(UpDown, "Memreturn: smsize:%d\n", sm_intf->ssize);
            DDUMP(UpDown, pkt->getConstPtr<uint8_t>(), pkt->getSize());
            int num_oper = sm_intf->ssize / 8;
            uint8_t *ldata; // = new uint8_t[sm_intf->ssize];
            if(sm_intf->partial)
                ldata = sm_intf->partial_data;
            else{
                upstats.TotalLat_SendsDmLm+= (gem5::curTick() - sm_intf->lat_start[0]);
                ldata = sm_intf->partial_data;
            }
            DDUMP(UpDown, ldata, sm_intf->ssize);
            uint64_t edata = 0;
            uint64_t fake_cont = 0xffffffffffffffff;//sm_intf->sdest;
            upstream_pyintf->insert_operand(fake_cont, lane_num); // Insert continuation first!
            for(int i=0; i<num_oper;i++){
                if(!recode_endianness)
                	edata = (((((uint64_t)ldata[8*i+7] & 0xff) << 56) & 0xff00000000000000) | \
                             ((((uint64_t)ldata[8*i+6] & 0xff) << 48) & 0x00ff000000000000) | \
                             ((((uint64_t)ldata[8*i+5] & 0xff) << 40) & 0x0000ff0000000000) | \
                             ((((uint64_t)ldata[8*i+4] & 0xff) << 32) & 0x000000ff00000000) | \
                             ((((uint64_t)ldata[8*i+3] & 0xff) << 24) & 0x00000000ff000000) | \
                             ((((uint64_t)ldata[8*i+2] & 0xff) << 16) & 0x0000000000ff0000) | \
                             ((((uint64_t)ldata[8*i+1] & 0xff) << 8) & 0x000000000000ff00) | \
                             ((((uint64_t)ldata[8*i] & 0xff)) & 0x00000000000000ff));
                else
                    edata = (((((uint64_t)ldata[8*i] & 0xff) << 56) & 0xff00000000000000) | \
                             ((((uint64_t)ldata[8*i+1] & 0xff) << 48) & 0x00ff000000000000) | \
                             ((((uint64_t)ldata[8*i+2] & 0xff) << 40) & 0x0000ff0000000000) | \
                             ((((uint64_t)ldata[8*i+3] & 0xff) << 30) & 0x000000ff00000000) | \
                             ((((uint64_t)ldata[8*i+4] & 0xff) << 24) & 0x00000000ff000000) | \
                             ((((uint64_t)ldata[8*i+5] & 0xff) << 16) & 0x0000000000ff0000) | \
                             ((((uint64_t)ldata[8*i+6] & 0xff) << 8) & 0x000000000000ff00) | \
                             ((((uint64_t)ldata[8*i+7] & 0xff)) & 0x00000000000000ff));
                DPRINTF(UpDown, "edata[%d]:%ld\n", i, edata);
                upstream_pyintf->insert_operand(edata, lane_num);
            }
            upstream_pyintf->insert_operand(sm_intf->sdest_VA, lane_num); // Insert address!
            upstream_pyintf->insert_event(cont, num_oper+1, lane_num);
            upstats.numEvents[lane_num]++;
            struct exec_param ep = {1, lane_num};
            if(gem5::curTick() < least_poss_exec_cycle[lane_num]){// || num_outstanding_exec_events[lane_num]>0){
                schedule(new gem5::EventFunctionWrapper([this, ep]{ execute(&ep); },
                                              name() + ".execute", true),
                     least_poss_exec_cycle[lane_num]);
                num_outstanding_exec_events[lane_num]++;
            }
            else{
                num_outstanding_exec_events[lane_num]++;
                schedule(new gem5::EventFunctionWrapper([this, ep]{ execute(&ep); },
                                              name() + ".execute", true),
                     gem5::curTick()+2*period);
            }
            delete ldata;
        }else{
            //stores
            DPRINTF(UpDown, "Processing:%d\n", sm_intf->sm_trans_id);
            uint64_t cont = sm_intf->scont;
            uint32_t lane_num = (cont & 0x3f00000000) >> 32; 
            uint32_t dest_ud = (cont & 0xc000000000) >> 38; 
            DPRINTF(UpDown, "Memreturn: smsize:%d\n", sm_intf->ssize);
            DDUMP(UpDown, pkt->getConstPtr<uint8_t>(), pkt->getSize());
            int num_oper = 2;
            uint64_t fake_cont = 0xffffffffffffffff;
            upstream_pyintf->insert_operand(fake_cont, lane_num); // Insert continuation first!
            upstream_pyintf->insert_operand(sm_intf->sdest, lane_num); // Insert continuation first!
            upstream_pyintf->insert_operand(sm_intf->sdest, lane_num); // Insert continuation first!
            upstream_pyintf->insert_event(cont, num_oper, lane_num);
            upstats.numEvents[lane_num]++;
            struct exec_param ep = {1, lane_num};
            if(gem5::curTick() < least_poss_exec_cycle[lane_num]){ //| num_outstanding_exec_events[lane_num]>0){
                schedule(new gem5::EventFunctionWrapper([this, ep]{ execute(&ep); },
                                              name() + ".execute", true),
                     least_poss_exec_cycle[lane_num]);
                num_outstanding_exec_events[lane_num]++;
            }
            else{
                schedule(new gem5::EventFunctionWrapper([this, ep]{ execute(&ep); },
                                              name() + ".execute", true),
                     gem5::curTick()+2*period);
                num_outstanding_exec_events[lane_num]++;
            }
        }

#else
        gs_id = sm_intf->sst_id; //super trans ID (use in super trans map)
        strans= super_trans_map[gs_id];
        int cur_seq = sm_intf->gseq; 
        int num_seq = strans->num_seq;
        sm_intf->gseq_stat=1; // Arrived
        super_trans_map[gs_id]->trans_stat[cur_seq]=1;
        int all_sent=1;
        DPRINTF(UpDown, "Memreturn: Seq:%d/%d\n", cur_seq+1, num_seq);
        DPRINTF(UpDown, "SuperTrans ID:%lu, num_seq:%d, seq_done:%d \n", gs_id, strans->num_seq, strans->seq_done);
        if(num_seq > 0 && cur_seq > 0){
            for(int j=strans->seq_done; j < cur_seq; j++){
                DPRINTF(UpDown, "Pre Memreturn Stat: Seq:%d:%d\n", j+1, super_trans_map[gs_id]->trans_stat[j]);
                if(strans->trans_stat[j] != 2){// && !(mem_reqs[strans->trans_id[j]]->smode_2)){
                    // All load requests not satisfied upto this point
                    all_sent=0;
                    return true; //break;
                }
                strans->seq_done=j;
            }
        }
        // Others done ?
        for(int j=cur_seq; j< num_seq;j++){
            if(j != cur_seq){
                if(super_trans_map[gs_id]->trans_stat[j] < 1)
                    return true; // Something in the sequence not sent out even as yet
                DPRINTF(UpDown, "Check if Load/Store: Seq:%d:%d, Load/Store:%d\n", j+1, num_seq, mem_reqs[strans->trans_id[j]]->smode_2);
                // Load that has to be sent out
                sm_intf = mem_reqs[strans->trans_id[j]];
            }
            if(!sm_intf->smode_2){
                //Loads
                DPRINTF(UpDown, "Processing:%d:%d\n", j, sm_intf->sm_trans_id);
                uint64_t cont = sm_intf->scont;
                uint64_t nwid = cont >> 32;
                uint32_t lane_num = nwid & 0x3f; 
                uint32_t dest_ud = (nwid & 0x1C0) >> 6; 
                DPRINTF(UpDown, "NWID:%ld Dest UD:%d: ThisUD%d\n", nwid, dest_ud, this->udidx);
                assert((nwid & 0xffffffC0) == (this->nwid & 0xffffffC0));
                DPRINTF(UpDown, "Memreturn: smsize:%d\n", sm_intf->ssize);
                DDUMP(UpDown, pkt->getConstPtr<uint8_t>(), pkt->getSize());
                int num_oper = sm_intf->ssize / 8;
                uint8_t *ldata; // = new uint8_t[sm_intf->ssize];
                if(sm_intf->partial)
                    ldata = sm_intf->partial_data;
                else{
                    upstats.TotalLat_SendsDmLm+= (gem5::curTick() - sm_intf->lat_start[0]);
                    ldata = sm_intf->partial_data;
                }
                DDUMP(UpDown, ldata, sm_intf->ssize);
                uint64_t edata = 0;
                uint64_t fake_cont = 0xffffffffffffffff;//sm_intf->sdest;
                upstream_pyintf->insert_operand(fake_cont, lane_num); // Insert continuation first!
                for(int i=0; i<num_oper;i++){
                    if(!recode_endianness)
                    	edata = (((((uint64_t)ldata[8*i+7] & 0xff) << 56) & 0xff00000000000000) | \
                                 ((((uint64_t)ldata[8*i+6] & 0xff) << 48) & 0x00ff000000000000) | \
                                 ((((uint64_t)ldata[8*i+5] & 0xff) << 40) & 0x0000ff0000000000) | \
                                 ((((uint64_t)ldata[8*i+4] & 0xff) << 32) & 0x000000ff00000000) | \
                                 ((((uint64_t)ldata[8*i+3] & 0xff) << 24) & 0x00000000ff000000) | \
                                 ((((uint64_t)ldata[8*i+2] & 0xff) << 16) & 0x0000000000ff0000) | \
                                 ((((uint64_t)ldata[8*i+1] & 0xff) << 8) & 0x000000000000ff00) | \
                                 ((((uint64_t)ldata[8*i] & 0xff)) & 0x00000000000000ff));
                    else
                        edata = (((((uint64_t)ldata[8*i] & 0xff) << 56) & 0xff00000000000000) | \
                                 ((((uint64_t)ldata[8*i+1] & 0xff) << 48) & 0x00ff000000000000) | \
                                 ((((uint64_t)ldata[8*i+2] & 0xff) << 40) & 0x0000ff0000000000) | \
                                 ((((uint64_t)ldata[8*i+3] & 0xff) << 30) & 0x000000ff00000000) | \
                                 ((((uint64_t)ldata[8*i+4] & 0xff) << 24) & 0x00000000ff000000) | \
                                 ((((uint64_t)ldata[8*i+5] & 0xff) << 16) & 0x0000000000ff0000) | \
                                 ((((uint64_t)ldata[8*i+6] & 0xff) << 8) & 0x000000000000ff00) | \
                                 ((((uint64_t)ldata[8*i+7] & 0xff)) & 0x00000000000000ff));
                    DPRINTF(UpDown, "edata[%d]:%ld\n", i, edata);
                    upstream_pyintf->insert_operand(edata, lane_num);
                }
                upstream_pyintf->insert_operand(sm_intf->sdest_VA, lane_num); // Insert modified address inverse translation to VA
                upstream_pyintf->insert_event(cont, num_oper+1, lane_num);
                super_trans_map[gs_id]->trans_stat[j]=2;
                //sm_intf->gseq_stat = 2;
                upstats.numEvents[lane_num]++;
                struct exec_param ep = {1, lane_num};
                if(gem5::curTick() < least_poss_exec_cycle[lane_num]){// || num_outstanding_exec_events[lane_num]>0){
                    schedule(new gem5::EventFunctionWrapper([this, ep]{ execute(&ep); },
                                                  name() + ".execute", true),
                         least_poss_exec_cycle[lane_num]);
                    num_outstanding_exec_events[lane_num]++;
                }
                else{
                    num_outstanding_exec_events[lane_num]++;
                    schedule(new gem5::EventFunctionWrapper([this, ep]{ execute(&ep); },
                                                  name() + ".execute", true),
                         gem5::curTick()+2*period);
                    //execute(&ep);
                }
                delete ldata;
            }else{
                //stores
                DPRINTF(UpDown, "Processing:%d:%d\n", j, sm_intf->sm_trans_id);
                uint64_t cont = sm_intf->scont;
                uint32_t lane_num = (cont & 0x3f00000000) >> 32; 
                uint32_t dest_ud = (cont & 0xc000000000) >> 38; 
                //assert(dest_ud == this->udidx);
                assert((nwid & 0xffffffC0) == (this->nwid & 0xffffffC0));
                DPRINTF(UpDown, "Memreturn: smsize:%d\n", sm_intf->ssize);
                DDUMP(UpDown, pkt->getConstPtr<uint8_t>(), pkt->getSize());
                int num_oper = 2;
                uint64_t fake_cont = 0xffffffffffffffff;
                upstream_pyintf->insert_operand(fake_cont, lane_num); // Insert continuation first!
                upstream_pyintf->insert_operand(sm_intf->sdest_VA, lane_num); // Insert continuation first!
                upstream_pyintf->insert_operand(sm_intf->sdest_VA, lane_num); // Insert continuation first!
                upstream_pyintf->insert_event(cont, num_oper, lane_num);
                upstats.numEvents[lane_num]++;
                struct exec_param ep = {1, lane_num};
                if(gem5::curTick() < least_poss_exec_cycle[lane_num]){ //| num_outstanding_exec_events[lane_num]>0){
                    schedule(new gem5::EventFunctionWrapper([this, ep]{ execute(&ep); },
                                                  name() + ".execute", true),
                         least_poss_exec_cycle[lane_num]);
                    num_outstanding_exec_events[lane_num]++;
                }
                else{
                    schedule(new gem5::EventFunctionWrapper([this, ep]{ execute(&ep); },
                                                  name() + ".execute", true),
                         gem5::curTick()+2*period);
                    num_outstanding_exec_events[lane_num]++;
                }
                DPRINTF(UpDown, "Setting seq:%d to processed:%d\n", sm_intf->gseq+1,
                    strans->trans_stat[sm_intf->gseq]); // Arrived
                super_trans_map[gs_id]->trans_stat[sm_intf->gseq] = 2;
                prev_yield_cycles[lane_num]=0;
            }
            strans->seq_done=j;
        } 
        // Is everything done?
        int k;
        for(k=0; k<num_seq; k++){
            if(strans->trans_stat[k]!=2)
                break;
        }
        if(k==num_seq)
            strans->all_done=1;
        else
            strans->all_done=0;
#endif

    }else{
        printf("Pkt not in map\n");
        exit(1);
    }
#ifdef MEM_ORDERING_DEPRECATED

    DPRINTF(UpDown, "Actually Erasing from Map Trans:%ld\n", sm_intf->sm_trans_id);
    if(sm_intf->lat_start ) delete sm_intf->lat_start;
    if(sm_intf->sendmsg_data ) delete sm_intf->sendmsg_data;
    mem_reqs.erase(sm_intf->sm_trans_id);
    
#else

    if(strans->all_done==1){
        for(int j=0; j<strans->num_seq; j++) {
            sm_intf = mem_reqs[strans->trans_id[j]];
            DPRINTF(UpDown, "Actually Erasing from Map:%d, Trans:%ld\n", j, sm_intf->sm_trans_id);
            if(sm_intf->lat_start ) delete sm_intf->lat_start;
            //if(sm_intf->partial_data ) delete sm_intf->partial_data;
            if(sm_intf->sendmsg_data ) delete sm_intf->sendmsg_data;
            if(mem_reqs[strans->trans_id[j]])
                mem_reqs.erase(strans->trans_id[j]);
            if(sm_intf) delete sm_intf;
        }
        delete strans;
    }

#endif
    return true;
}


void UpDownObj::sendCPUResponse(gem5::PacketPtr pkt)
{
    //assert(blocked);

    //int port = waitingPortId;
    int port = pkt->getCPUport();
    DPRINTF(UpDown, "Sending resp for addr %#x to port%d\n", pkt->getAddr(), port);
    if(pkt->mtype != MessageType::NW){
        DPRINTF(UpDown, "Sending resp for addr %#x to CPU %d\n", pkt->getAddr(), port, num_outstanding_cpu);
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
UpDownObj::handleCPUFunctional(gem5::PacketPtr pkt)
{
    accessCPUFunctional(pkt);
    pkt->makeResponse();
}

void
UpDownObj::accessCPUTiming(gem5::PacketPtr pkt)
{
    accessCPUFunctional(pkt);
    pkt->makeResponse();
    schedule(new gem5::EventFunctionWrapper([this, pkt]{ sendCPUResponse(pkt); },
                                  name() + ".sendCPUResponse", true),
         clockEdge(latency));
}

bool
UpDownObj::accessCPUFunctional(gem5::PacketPtr pkt)
{
    DPRINTF(UpDown, "Accessfunction Before read:%s\n", pkt->print());
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
UpDownObj::handleUDFunctional(gem5::PacketPtr pkt)
{
    accessUDFunctional(pkt);
    //pkt->makeResponse();
}

void
UpDownObj::accessUDTiming(gem5::PacketPtr pkt)
{
    accessUDFunctional(pkt);
    //pkt->makeResponse();
    //schedule(new gem5::EventFunctionWrapper([this, pkt]{ sendCPUResponse(pkt ); },
    //                                  name() + ".sendUDResponse", true),
    //         clockEdge(latency));
}

bool
UpDownObj::accessUDFunctional(gem5::PacketPtr pkt)
{
    DPRINTF(UpDown, "Accessfunction Before read:%s\n", pkt->print());
    if (pkt->isWrite()) {
        // The packet should be aligned.
        writeUD(pkt);
    } else if (pkt->isRead()) {
        // The packet should be aligned.
        printf("cannot read from Remote LM as yet!\n");
        exit(1);
    }
    return true;
}

void
UpDownObj::writeUD(gem5::PacketPtr pkt)
{
    bool found = false;
    gem5::Addr baseAddr;
    uint32_t lane_num;
    int delay = 1;
    int i = 0;
    for (gem5::AddrRangeList::iterator it = evRange.begin(); it != evRange.end() && found == false; ++it, i++){
        if(pkt->getAddr() >= it->start() && pkt->getAddr() <= it->end()){
            found=true;
            lane_num=i;
        }
    }
    if(!found)
        fatal("Unknown EvQ addr received %lx", pkt->getAddr());

    //if(statStore[statRange.start()+lane_num*8]==0){
    if(statStore[lane_num]==0){
        DPRINTF(UpDown, "InterUD Message for Lane %d: %s\n", lane_num, pkt->print());
        DDUMP(UpDown, pkt->getConstPtr<uint8_t>(), pkt->getSize());
        uint64_t *ledata = new uint64_t[pkt->numOb];
        int numOb = pkt->numOb;
        DDUMP(UpDown, ledata, wordSize);
        // Insert Continuation first
        uint64_t edata = pkt->continuation_word;
        upstream_pyintf->insert_operand(edata, lane_num);
        for(int i=0; i< numOb; i++){
            upstream_pyintf->insert_operand(pkt->operand_data[i], lane_num);
        }
        edata = pkt->event_word;
        upstream_pyintf->insert_event(edata, numOb, lane_num);
        DPRINTF(UpDown, "InterUD Message inserted into Lane %d: EvQSize:%d\n", lane_num, upstream_pyintf->getEventQ_Size(lane_num) );
        DPRINTF(UpDown, "UD:%d Lane:%d Event:%ld, Continuation:%ld\n", this->udidx, lane_num, pkt->continuation_word, pkt->event_word);
        struct exec_param ep = {0, lane_num};
        DPRINTF(UpDown, "%lu: Least Exec:%lu \n", gem5::curTick(), least_poss_exec_cycle[lane_num]);
        if(gem5::curTick() < (least_poss_exec_cycle[lane_num] + 4)){
        //if(least_poss_exec_cycle[lane_num] > gem5::curTick()){
            DPRINTF(UpDown, "Scheduling for :%lu\n", least_poss_exec_cycle[lane_num]+period*4);
            schedule(new gem5::EventFunctionWrapper([this, ep]{ execute(&ep);},
                                                name() + ".execute", true),
                    least_poss_exec_cycle[lane_num]+period*4);
        }else {
            DPRINTF(UpDown, "Scheduling for :%lu\n", gem5::curTick()+period);
            schedule(new gem5::EventFunctionWrapper([this, ep]{ execute(&ep); },
                                                name() + ".execute", true),
                    gem5::curTick()+ 4*period);
        }
        delete ledata;
    }else{
        DPRINTF(UpDown, "Reschedule message from UD:%d due to conflict with Top\n", pkt->getsrcnwid());
        schedule(new gem5::EventFunctionWrapper([this, pkt]{ writeUD(pkt); },
                                      name() + ".writeUD", true),
             clockEdge(gem5::Cycles(latency)));
    }
}
void
UpDownObj::write(gem5::PacketPtr pkt)
{
    bool found = false;
    gem5::Addr baseAddr;
    uint32_t lane_num;
    DPRINTF(UpDown, "Writing %s\n", pkt->print());
    DDUMP(UpDown, pkt->getConstPtr<uint8_t>(), wordSize);
    // determine up front what is to be done 
    //bool not_in_spd = false;
    addr_region_t ar = INV;
    if(pkt->getAddr() >= sRange.start() && pkt->getAddr() <= sRange.end()){
        ar=SPD;
        found=true;
    }
    else{
        gem5::AddrRangeList::iterator it;
        int i=0;
        for (it = evRange.begin(); it != evRange.end() && found == false; ++it, i++){
            if(pkt->getAddr() >= it->start() && pkt->getAddr() <= it->end()){
                ar=EVQ;
                found=true;
                lane_num=i;
            }
        }
        for (it = obRange.begin(), i=0; it != obRange.end() && found == false; ++it, i++){
            if(pkt->getAddr() >= it->start() && pkt->getAddr() <= it->end()){
                ar=OPB;
                found=true;
                lane_num=i;
            }
        }
        for (it = execRange.begin(), i=0; it != execRange.end() && found == false; ++it, i++){
            if(pkt->getAddr() >= it->start() && pkt->getAddr() <= it->end()){
                ar=EXEC;
                found=true;
                lane_num=i;
            }
        }
        for (it = statRange.begin(), i=0; it != statRange.end() && found == false; ++it, i++){
            if(pkt->getAddr() >= it->start() && pkt->getAddr() <= it->end()){
                ar=STAT;
                found=true;
                lane_num=i;
            }
        }
    }


    //if(pkt->getAddr() >= execRange.start() && pkt->getAddr() <= execRange.end()){
    if(ar==EXEC){
        //lane_num = (pkt->getAddr() - execRange.start())/wordSize;
        DPRINTF(UpDown, "Exec: Inferred Lane Num:%ld\n", lane_num);
        struct exec_param ep = {0, lane_num};
        execstart[lane_num] = gem5::curTick();
        if(execstop[lane_num] != 0)
            upstats.upLaneIdleCycles_old[lane_num] += (execstart[lane_num] - execstop[lane_num])/period;
        if(gem5::curTick() < least_poss_exec_cycle[lane_num]){
            schedule(new gem5::EventFunctionWrapper([this, ep]{ execute(&ep); },
                                              name() + ".execute", true),
                    least_poss_exec_cycle[lane_num]);
            num_outstanding_exec_events[lane_num]++;
            if(active_thrds[lane_num]==0 && (least_poss_exec_cycle[lane_num]!=0)){
                upstats.upLaneIdleCycles[lane_num]+=(least_poss_exec_cycle[lane_num]-execstop[lane_num])/period;
            }
        }else{
            num_outstanding_exec_events[lane_num]++;
            if(active_thrds[lane_num]==0 && (least_poss_exec_cycle[lane_num]!=0)){
                upstats.upLaneIdleCycles[lane_num]+=(gem5::curTick()-execstop[lane_num])/period;
            }
            schedule(new gem5::EventFunctionWrapper([this, ep]{ execute(&ep); },
                                              name() + ".execute", true),
                        gem5::curTick()+period);
            //execute(&ep);
        }
        active_thrds[lane_num]++;
        prev_yield_term_cycles[lane_num]=0;
    }
    else if(ar==EVQ){
        //Write event into lane 
        uint8_t *ledata = new uint8_t[wordSize];
        pkt->writeData(ledata);
        DDUMP(UpDown, ledata, wordSize);
        uint64_t edata = ((((   (uint64_t)ledata[7] & 0xff) << 56) & 0xff00000000000000) | \
                            ((( (uint64_t)ledata[6] & 0xff) << 48) & 0x00ff000000000000) | \
                            ((( (uint64_t)ledata[5] & 0xff) << 40) & 0x0000ff0000000000) | \
                            ((( (uint64_t)ledata[4] & 0xff) << 32) & 0x000000ff00000000) | \
                            ((( (uint64_t)ledata[3] & 0xff) << 24) & 0x00000000ff000000) | \
                            ((( (uint64_t)ledata[2] & 0xff) << 16) & 0x0000000000ff0000) | \
                             ((((uint64_t)ledata[1] & 0xff) << 8) & 0x000000000000ff00) | \
                             ((((uint64_t)ledata[0] & 0xff)) & 0x00000000000000ff));
        int numOb = ((edata >> 20) & 0x7)+2;
        DPRINTF(UpDown, "Lane_num: %d Writing event data: %ld\n", lane_num, edata);
        upstream_pyintf->insert_event(edata, numOb, lane_num);
        upstats.numEvents[lane_num]++;
        upstats.numThreads[lane_num]++;
        delete ledata;
    }else if(ar==OPB){
        //Write operands into lane 
        uint8_t *ledata = new uint8_t[wordSize];
        pkt->writeData(ledata);
        DDUMP(UpDown, ledata, wordSize);
        uint64_t edata =   (((((uint64_t)ledata[7] & 0xff) << 56) & 0xff00000000000000) | \
                            ((((uint64_t)ledata[6] & 0xff) << 48) & 0x00ff000000000000) | \
                            ((((uint64_t)ledata[5] & 0xff) << 40) & 0x0000ff0000000000) | \
                            ((((uint64_t)ledata[4] & 0xff) << 32) & 0x000000ff00000000) | \
                            ((((uint64_t)ledata[3] & 0xff) << 24) & 0x00000000ff000000) | \
                            ((((uint64_t)ledata[2] & 0xff) << 16) & 0x0000000000ff0000) | \
                            ((((uint64_t)ledata[1] & 0xff) << 8) & 0x000000000000ff00) | \
                            ((((uint64_t)ledata[0] & 0xff)) & 0x00000000000000ff));
        DPRINTF(UpDown, "Lane_num:%d Writing operand data: %ld\n",lane_num, edata);
        upstream_pyintf->insert_operand(edata, lane_num);
        delete ledata;
    //}else if(pkt->getAddr() >= sRange.start() && pkt->getAddr() <= sRange.end()){
    }else if(ar==SPD){
        uint8_t *ledata = new uint8_t[wordSize];
        pkt->writeData(ledata);
        DDUMP(UpDown, ledata, wordSize);
        uint64_t edata =   (((((uint64_t)ledata[7] & 0xff) << 56) & 0xff00000000000000) | \
                            ((((uint64_t)ledata[6] & 0xff) << 48) & 0x00ff000000000000) | \
                            ((((uint64_t)ledata[5] & 0xff) << 40) & 0x0000ff0000000000) | \
                            ((((uint64_t)ledata[4] & 0xff) << 32) & 0x000000ff00000000) | \
                            ((((uint64_t)ledata[3] & 0xff) << 24) & 0x00000000ff000000) | \
                            ((((uint64_t)ledata[2] & 0xff) << 16) & 0x0000000000ff0000) | \
                            ((((uint64_t)ledata[1] & 0xff) << 8) & 0x000000000000ff00) | \
                            ((((uint64_t)ledata[0] & 0xff)) & 0x00000000000000ff));
        uint32_t saddr = pkt->getAddr() - sRange.start();
        DPRINTF(UpDown, "Writing scratch data: %ld at %ld\n", edata, saddr);
        upstream_pyintf->insert_scratch(saddr, edata);
        upstats.topLmWriteBytes+=pkt->getSize();
        delete ledata;
    }
    else if(STAT){
        //lane_num = (pkt->getAddr() - statRange.start())/wordSize;
        uint8_t *ledata = new uint8_t[wordSize];
        pkt->writeData(ledata);
        uint64_t edata =   (((((uint64_t)ledata[7] & 0xff) << 56) & 0xff00000000000000) | \
                            ((((uint64_t)ledata[6] & 0xff) << 48) & 0x00ff000000000000) | \
                            ((((uint64_t)ledata[5] & 0xff) << 40) & 0x0000ff0000000000) | \
                            ((((uint64_t)ledata[4] & 0xff) << 32) & 0x000000ff00000000) | \
                            ((((uint64_t)ledata[3] & 0xff) << 24) & 0x00000000ff000000) | \
                            ((((uint64_t)ledata[2] & 0xff) << 16) & 0x0000000000ff0000) | \
                            ((((uint64_t)ledata[1] & 0xff) << 8) & 0x000000000000ff00) | \
                            ((((uint64_t)ledata[0] & 0xff)) & 0x00000000000000ff));
        DDUMP(UpDown, ledata, wordSize);
        DPRINTF(UpDown, "Lane_num:%d Writing data into Stat area: %d\n",lane_num, edata);
        if(edata == 0){
            DPRINTF(UpDown, "Lane_num:%d Top Done: %d\n",lane_num, edata);
            DPRINTF(UpDown, "Lane_num:%d Removing all pending responses: %d\n",lane_num, pending_response[lane_num].size());
            int num_remaining=pending_response[lane_num].size();
            for(int i=0; i<num_remaining;i++){
                gem5::PacketPtr pkt_rem = pending_response[lane_num].front();
                if(handleDRAMResponse(pkt_rem)){
                    pending_response[lane_num].pop(); //erase(pending_response[lane_num].begin()+i);
                    DPRINTF(UpDown, "Lane_num:%d Remdaining pending responses: %d\n",lane_num, pending_response[lane_num].size());
                }else{
                    printf("Error handling Response from pending queue \n");
                    exit(1);
                }
            }
            DPRINTF(UpDown, "Finished working on pending requests\n");
            statStore[lane_num] = edata;
        }else{
            DPRINTF(UpDown, "Lane_num:%d Top Busy writing into Stat Area OpNum: %d\n",lane_num, edata);
            
            //top_event[lane_num] = (struct event_operand*) new (struct event_operand);
            //top_event[lane_num]->num_ops = edata;
            //top_event[lane_num]->ops = new uint32_t[num_ops];
            statStore[lane_num] = 1;
        }
        delete ledata;
    }else{
        // Write the data into scratchpad
        fatal("Invalid Address\n");
    }
}
void 
UpDownObj::execute(struct exec_param *ep){
    uint32_t lane_num = ep->lane_num;
    if(gem5::curTick() < least_poss_exec_cycle[lane_num]){
        struct exec_param ep1 = {ep->cont,ep->lane_num};
        schedule(new gem5::EventFunctionWrapper([this, ep1]{ execute(&ep1); },
                                          name() + ".execute", true),
                 least_poss_exec_cycle[lane_num]);
    }else{
        num_outstanding_exec_events[lane_num]--;
        uint32_t total_inst_cnt;
        uint32_t numsend_intf;
        uint32_t exec_time;
        int cont_state = ep->cont;
        struct SimStats em_stats;
        DPRINTF(UpDown, "UDID:%d Lane:%d Execute EFA, EvQSize:%d\n",this->udidx, lane_num, upstream_pyintf->getEventQ_Size(lane_num));
        DPRINTF(UpDown, "C++ Process will execute Python process now\n");
        //while(upstream_pyintf->getEventQ_Size(lane_num) > 0){
            if((gem5::curTick() > least_poss_exec_cycle[lane_num]) && (least_poss_exec_cycle[lane_num] != 0) && \
                (active_thrds[lane_num]>0)){
                    // Condition 3 is to check stall cycles are calculated only when threads are waiting
                upstats.upLaneStallCycles[lane_num]+=(gem5::curTick() - least_poss_exec_cycle[lane_num])/period;
            }
            int exec_state = upstream_pyintf->execute(cont_state, em_stats, lane_num, gem5::curTick());
        DPRINTF(UpDown, "UDID:%d Lane:%d After Execute EFA, EvQSize:%d\n",this->udidx, lane_num, upstream_pyintf->getEventQ_Size(lane_num));
            upstats.numActions[lane_num] += em_stats.total_inst_cnt;
            upstats.numTransitions[lane_num] += em_stats.transition_cnt;
            upstats.numInstructions[lane_num] += em_stats.transition_cnt + em_stats.total_inst_cnt;
            upstats.cyclesPerEvent.sample(em_stats.transition_cnt + em_stats.total_inst_cnt);
            upstats.MessageInstructions[lane_num] += em_stats.send_inst_cnt;
            upstats.MovInstructions[lane_num] += em_stats.move_inst_cnt;
            upstats.BranchInstructions[lane_num] += em_stats.branch_inst_cnt;
            upstats.AtomicInstructions[lane_num] += em_stats.cmp_swp_inst_cnt;
            upstats.YieldInstructions[lane_num] += em_stats.yield_inst_cnt;
            upstats.ALUInstructions[lane_num] += em_stats.alu_inst_cnt;
            upstats.CompareInstructions[lane_num] += em_stats.compare_inst_cnt;
            upstats.upLmReadBytes[lane_num] += em_stats.lm_read_bytes;
            upstats.upLmWriteBytes[lane_num] += em_stats.lm_write_bytes;
            upstats.upLaneExecCycles[lane_num] += em_stats.exec_cycles;
            upstats.upLaneEventQMax[lane_num] = em_stats.event_queue_max;
            upstats.upLaneEventQMean[lane_num] = em_stats.event_queue_mean;
            upstats.upLaneOperandQMax[lane_num] = em_stats.operand_queue_max;
            upstats.upLaneOperandQMean[lane_num] = em_stats.operand_queue_mean;
            upstats.updownPerLaneUserCtr0[lane_num] = em_stats.user_counter[0];
            upstats.updownPerLaneUserCtr1[lane_num] = em_stats.user_counter[1];
            upstats.updownPerLaneUserCtr2[lane_num] = em_stats.user_counter[2];
            upstats.updownPerLaneUserCtr3[lane_num] = em_stats.user_counter[3];
            upstats.updownPerLaneUserCtr4[lane_num] = em_stats.user_counter[4];
            upstats.updownPerLaneUserCtr5[lane_num] = em_stats.user_counter[5];
            upstats.updownPerLaneUserCtr6[lane_num] = em_stats.user_counter[6];
            upstats.updownPerLaneUserCtr7[lane_num] = em_stats.user_counter[7];
            upstats.updownPerLaneUserCtr8[lane_num] = em_stats.user_counter[8];
            upstats.updownPerLaneUserCtr9[lane_num] = em_stats.user_counter[9];
            upstats.updownPerLaneUserCtr10[lane_num] = em_stats.user_counter[10];
            upstats.updownPerLaneUserCtr11[lane_num] = em_stats.user_counter[11];
            upstats.updownPerLaneUserCtr12[lane_num] = em_stats.user_counter[12];
            upstats.updownPerLaneUserCtr13[lane_num] = em_stats.user_counter[13];
            upstats.updownPerLaneUserCtr14[lane_num] = em_stats.user_counter[14];
            upstats.updownPerLaneUserCtr15[lane_num] = em_stats.user_counter[15];
            DPRINTF(UpDown, "UDID:%d Lane:%d, numActions:%d, total_inst_cnt:%d\n", this->udidx, lane_num, upstats.numActions[lane_num].value(), em_stats.total_inst_cnt);
            exec_time = em_stats.exec_cycles;
            least_poss_exec_cycle[lane_num] = gem5::curTick()+ period*exec_time; // This needs to be changed to be parametric
            long last_send=0;
            long prev_sm_cycle=0, curr_cyc=0;
            if(exec_state == 0){
                prev_yield_cycles[lane_num] += em_stats.exec_cycles;
                DPRINTF(UpDown, "Nothing to be done until events arrive?\n");
            }
            else if(exec_state > 0 || ((exec_state == -1) && ( em_stats.num_sends > 0))){
                uint32_t numsend = sendmap[0];
                DPRINTF(UpDown, "UDID:%d Lane:%d Messages to be sent- numMessages :%d\n", this->udidx, lane_num, numsend);
                int offset = 1;
                struct super_trans* stm = new struct super_trans;
                stm->num_seq=0;
                stm->seq_done=0;
                stm->trans_id = (uint64_t *)malloc(sizeof(uint64_t)*numsend);
                stm->trans_stat = (int *)malloc(sizeof(int)*numsend);
                stm->all_done = 0;
                uint64_t gsst_id = global_super_sm_trans_id++;  
                super_trans_map[gsst_id] = stm; 
                DPRINTF(UpDown, "SuperTrans:%lx ID:%lu num_seq:%d\n", stm, gsst_id, super_trans_map[gsst_id]->num_seq);
                for(int i=0; i<numsend;i++){ // send out requests to memory for the size specified
                    struct sendmsg_intf *sm_intf = new struct sendmsg_intf();
                    sm_intf->sm_trans_id = global_sm_trans_id++;
                    DPRINTF(UpDown, "New SM_Intf:%d, Addr(sm_intf):%lx\n", sm_intf->sm_trans_id, &sm_intf);
                    DPRINTF(UpDown, "Offset to read:%d\n", 8*i+1);
                    uint32_t mode = sendmap[offset++];
                    sm_intf->smode_0 = (mode & 0x1);
                    sm_intf->smode_1 = (mode & 0x2) >> 1;
                    sm_intf->smode_2 = (mode & 0x4) >> 2;
                    DPRINTF(UpDown, "Send Mode:mode:%d, 0:%d,1:%d,2:%d\n", mode, sm_intf->smode_0, sm_intf->smode_1,\
                                                    sm_intf->smode_2);
                    uint32_t sm_cycle = sendmap[offset++];//[8*i+2];
                    curr_cyc = sm_cycle - prev_sm_cycle;
                    prev_sm_cycle = sm_cycle;
                    uint64_t temp_val=0;
                    uint64_t sevent_, scont_;  // Dest Event
                    sevent_ = sendmap[offset++] & 0xffffffff; //[8*i+3];
                    temp_val = sendmap[offset++];
                    sm_intf->sevent = sevent_ | ((temp_val << 32 ) & 0xffffffff00000000); //[8*i+3];
                    DPRINTF(UpDown, "Send Event:%ld, Cycle:%d, curr_cyc:%d prev_cyc:%d\n", sm_intf->sevent, sm_cycle,\
                                                    curr_cyc, prev_sm_cycle);
                    if(sm_intf->smode_0 == 0){ // Memory bound
                            sm_intf->sst_id = gsst_id;
                            sm_intf->gseq = stm->num_seq;
                            sm_intf->gseq_stat=0;
                            super_trans_map[gsst_id]->trans_id[stm->num_seq]=sm_intf->sm_trans_id; // Keep track of the mappings
                            super_trans_map[gsst_id]->trans_stat[stm->num_seq]=0; // Keep track of the mappings
                            stm->num_seq++;
                            uint64_t lower = sendmap[offset++];//[8*i+5];
                            uint64_t upper = sendmap[offset++];//[8*i+4];
                            sm_intf->sdest = (lower & 0xffffffff) | ((upper << 32)& 0xffffffff00000000);
                            DPRINTF(UpDown, "Memory Bound Load:%d, Store:%d\n", !sm_intf->smode_2, sm_intf->smode_2);
                            DPRINTF(UpDown, "Send Dest:%lx, Upper:%lx, Lower:%lx\n", sm_intf->sdest, upper, lower);
                            DPRINTF(UpDown, "Stm Details: stm:num_seq:%d, sst_id:%lu, trans_id:%lu\n", \
                                                            stm->num_seq-1, gsst_id, sm_intf->sm_trans_id);
                    }else{
                        uint64_t lower = sendmap[offset++]; //[8*i+5];
                        uint64_t upper = sendmap[offset++]; //[8*i+4];
                        sm_intf->sdest = (lower & 0xffffffff) | ((upper << 32) & 0xffffffff00000000);
                        DPRINTF(UpDown, "Send Dest:%d\n", sm_intf->sdest);
                    }
                    temp_val=0;
                    scont_ = sendmap[offset++] & 0xffffffff; //[8*i+3];
                    temp_val = sendmap[offset++];
                    sm_intf->scont = scont_ | ((temp_val << 32 ) & 0xffffffff00000000); //[8*i+3];
                    sm_intf->ssize = sendmap[offset++];//[8*i+7];
                    DPRINTF(UpDown, "Send Cont:%ld, Size:%d\n", sm_intf->scont, sm_intf->ssize);
                    if(sm_intf->smode_0 == 1){
                        sm_intf->sdata_64 = new uint64_t[sm_intf->ssize/wordSize];
                        sm_intf->sdata = new uint8_t[sm_intf->ssize];
                        DPRINTF(UpDown, "Send data to lane :%ld, Size:%d\n", sm_intf->sdest, sm_intf->ssize);
                        for (int j=0; j<sm_intf->ssize/wordSize;j++){
                            temp_val=0;
                            uint64_t sdata_64 = sendmap[offset++] & 0xffffffff; //[8*i+8+j];
                            temp_val = sendmap[offset++];
                            sm_intf->sdata_64[j] = sdata_64 | ((temp_val << 32 ) & 0xffffffff00000000); //[8*i+3];
                            DPRINTF(UpDown, "data[%d]:%d\n", j, sm_intf->sdata_64[j]);
                            sm_intf->sdata[8*j] = (uint8_t)(sm_intf->sdata_64[j] & 0xff); //[8*i+8+(j/4)] & 0xff);
                            sm_intf->sdata[8*j+1] = (uint8_t)((sm_intf->sdata_64[j] & 0xff00) >> 8);
                            sm_intf->sdata[8*j+2] = (uint8_t)((sm_intf->sdata_64[j] & 0xff0000) >> 16);
                            sm_intf->sdata[8*j+3] = (uint8_t)((sm_intf->sdata_64[j] & 0xff000000) >> 24);
                            sm_intf->sdata[8*j+4] = (uint8_t)((sm_intf->sdata_64[j] & 0xff00000000) >> 32);
                            sm_intf->sdata[8*j+5] = (uint8_t)((sm_intf->sdata_64[j] & 0xff0000000000) >> 40);
                            sm_intf->sdata[8*j+6] = (uint8_t)((sm_intf->sdata_64[j] & 0xff000000000000) >> 48);
                            sm_intf->sdata[8*j+7] = (uint8_t)((sm_intf->sdata_64[j] & 0xff00000000000000) >> 56);
                        }
                    }
                    if(sm_intf->smode_2 == 1){
                            sm_intf->sdata = new uint8_t[sm_intf->ssize];
                            for (int j=0; j<sm_intf->ssize;j+=8){
                                sm_intf->sdata[j] = (uint8_t)(sendmap[offset] & 0xff); //[8*i+8+(j/4)] & 0xff);
                                sm_intf->sdata[j+1] = (uint8_t)((sendmap[offset] & 0xff00) >> 8);
                                sm_intf->sdata[j+2] = (uint8_t)((sendmap[offset] & 0xff0000) >> 16);
                                sm_intf->sdata[j+3] = (uint8_t)((sendmap[offset] & 0xff000000) >> 24);
                                offset++;
                                sm_intf->sdata[j+4] = (uint8_t)((sendmap[offset] & 0xff));
                                sm_intf->sdata[j+5] = (uint8_t)((sendmap[offset] & 0xff00) >> 8);
                                sm_intf->sdata[j+6] = (uint8_t)((sendmap[offset] & 0xff0000) >> 16);
                                sm_intf->sdata[j+7] = (uint8_t)((sendmap[offset] & 0xff000000) >> 24);
                                offset++;
                                DPRINTF(UpDown, "Send Data[0]:%d, Data:[1]:%d, Data[2]:%d, Data[3]:%d, Data[4]:%d, Data:[5]:%d, Data[6]:%d, Data[7]:%d\n", sm_intf->sdata[j], sm_intf->sdata[j+1], sm_intf->sdata[j+2], sm_intf->sdata[j+3], sm_intf->sdata[j+4], sm_intf->sdata[j+5], sm_intf->sdata[j+6], sm_intf->sdata[j+7]);
                            }
                    }
                    sm_intf->send_policy = (sm_intf->scont & 0x3000000000000000) >> 60;
                    sm_intf->node_id = (sm_intf->scont & 0xFFFF00000000000) >> 44;
                    sm_intf->stack_id = (sm_intf->scont & 0xF0000000000) >> 40;
                    sm_intf->ud_num = (sm_intf->scont & 0xC000000000) >> 38;
                    sm_intf->lane_id = (sm_intf->scont & 0x3f00000000) >> 32;
                    //sm_intf->lane_id = (sm_intf->scont & 0x3f000000) >> 24; 
                    DPRINTF(UpDown, "Send LaneID:%d\n", sm_intf->lane_id);
                    if(!sm_intf->smode_0){ //memory bound messages
                        int portid=(sm_intf->sdest >> 6)%num_mc;
                        if(last_send+curr_cyc == eventtime[portid]){
                            eventtime[portid] = eventtime[portid]+0.5; //This needs to be made a function of Cycles+ticks
                            last_send = eventtime[portid];
                            DPRINTF(UpDown, "TM:%d Port:%d Schtime:%lu Conf\n", sm_intf->sm_trans_id,portid, eventtime[portid]);
                        }
                        else{
                            eventtime[portid] = last_send+curr_cyc;
                            last_send=eventtime[portid];
                            DPRINTF(UpDown, "TM:%d Port:%d Schtime:%lu Reg\n", sm_intf->sm_trans_id,portid, eventtime[portid]);
                        }
                        schedule(new gem5::EventFunctionWrapper([this, sm_intf]{ send_msg(sm_intf); },
                                                      name() + ".SendMessage", true),
                             clockEdge(gem5::Cycles(eventtime[portid])));
                    }else{
                        schedule(new gem5::EventFunctionWrapper([this, sm_intf]{ send_msg(sm_intf); },
                                                      name() + ".SendMessage", true),
                             clockEdge(gem5::Cycles(last_send+curr_cyc)));
                             last_send=last_send+curr_cyc;
                    }
                    
                }
            }// res = -1 yielded and terminated clean up
            if(exec_state == -1){
                //execstate = 0;
                exec_state = 0;
                prev_yield_term_cycles[lane_num]+= em_stats.exec_cycles;
                DPRINTF(UpDown, "UDID:%d Lane:%d Yielded and Terminated\n", this->udidx, lane_num);
                execstop[lane_num] = gem5::curTick()+period * (em_stats.exec_cycles);
                active_thrds[lane_num]--;
                upstats.upLaneBusyCycles[lane_num] += (execstop[lane_num] - execstart[lane_num])/period;
            }
        //} // while close
        // execute done. 
    }// else of current event
}


void
UpDownObj::send_msg(struct sendmsg_intf* sm_intf){
    DPRINTF(UpDown, "Send_Msg: TID:%lu Smode_0 : %d\n", sm_intf->sm_trans_id, sm_intf->smode_0);
    //printf("%lu: Send Messages:%d\n", gem5::curTick(), prev_yield_cycles[0], prev_yield_term_cycles[0]);
    if(!sm_intf->smode_0){
        // Memory bound messages
        // Update stats
        sm_intf->sdest_VA = sm_intf->sdest;
        int sendPort=(sm_intf->sdest >> 6)%num_mc;
        gem5::Request::Flags reqflags = gem5::Request::UNCACHEABLE;
        int i = 0;
        if(sm_intf->ssize > 1 && ((dblksize - (sm_intf->sdest % dblksize)) < sm_intf->ssize)){
            sm_intf->partial = true; // Need to split up requests
            int bytesleft = sm_intf->ssize;
            int dataindex = 0;
            while(bytesleft > 0){
                gem5::RequestPtr reqptr;
                if(sm_intf->num_partials==0){
                    int size = dblksize - (sm_intf->sdest%dblksize);
                    DPRINTF(UpDown, "Before Translation:%lu sdest 0x%lx\n", sm_intf->sm_trans_id, sm_intf->sdest);
                    uint64_t sdest_pa = this->udtrans_table.getPA(sm_intf->sdest);
                    DPRINTF(UpDown, "After Translation:%lu sdest 0x%lx\n", sm_intf->sm_trans_id, sdest_pa);
                    reqptr = std::make_shared<gem5::Request>((gem5::Addr)sdest_pa, \
                    size, reqflags, updown_id);
                    dataindex=sm_intf->ssize - bytesleft;
                    bytesleft-=size;
                    sm_intf->num_partials++;
                    DPRINTF(UpDown, "Partial packet : %d, Request size :%d, BytesLeft:%d\n", \
                    sm_intf->num_partials, reqptr->getSize(), bytesleft);
                }else if (bytesleft > dblksize){
                    uint64_t ndest = sm_intf->sdest + dblksize*(sm_intf->num_partials-1) + (dblksize - (sm_intf->sdest%dblksize));
                    DPRINTF(UpDown, "Before Translation:%lu sdest 0x%lx\n", sm_intf->sm_trans_id, ndest);
                    uint64_t ndest_pa = this->udtrans_table.getPA(ndest);
                    DPRINTF(UpDown, "After Translation:%lu sdest 0x%lx\n", sm_intf->sm_trans_id, ndest_pa);
                    reqptr = std::make_shared<gem5::Request>((gem5::Addr)ndest_pa, \
                    dblksize, reqflags, updown_id);
                    sm_intf->num_partials++;
                    dataindex=sm_intf->ssize - bytesleft;
                    bytesleft-=dblksize;
                    DPRINTF(UpDown, "Partial packet : %d, Request size :%d, BytesLeft:%d\n", \
                    sm_intf->num_partials, reqptr->getSize(), bytesleft);
                }else{
                    uint64_t ndest = sm_intf->sdest + dblksize*(sm_intf->num_partials-1) + (dblksize - (sm_intf->sdest%dblksize));
                    DPRINTF(UpDown, "Before Translation:%lu sdest 0x%lx\n", sm_intf->sm_trans_id, ndest);
                    uint64_t ndest_pa = this->udtrans_table.getPA(ndest);
                    DPRINTF(UpDown, "After Translation:%lu sdest 0x%lx\n", sm_intf->sm_trans_id, ndest_pa);
                    reqptr = std::make_shared<gem5::Request>((gem5::Addr)ndest_pa, \
                    bytesleft, reqflags, updown_id);
                    sm_intf->num_partials++;
                    dataindex=sm_intf->ssize - bytesleft;
                    bytesleft-=bytesleft;
                    DPRINTF(UpDown, "Partial packet : %d, Request size :%d, BytesLeft:%d\n", \
                    sm_intf->num_partials, reqptr->getSize(), bytesleft);
                }
                reqptr->setTransID(sm_intf->sm_trans_id);
                gem5::Packet *pkt1;
                if(sm_intf->smode_2 == 0){
                    pkt1 = new gem5::Packet(reqptr, gem5::MemCmd::ReadReq);
                    pkt1->allocate(); // Not sure if this is actually needed. Probably is.
                    upstats.upDramReadBytes+=pkt1->getSize();
                }
                else{
                    pkt1 = new gem5::Packet(reqptr, gem5::MemCmd::WriteReq);
                    pkt1->allocate(); // Not sure if this is actually needed. Probably is.
                    pkt1->setData(&sm_intf->sdata[dataindex]); // Change this to point to correct array index
                    upstats.upDramWriteBytes+=pkt1->getSize();
                }
                DPRINTF(UpDown, "Writing packet into map: %s, %x, trans_id:%d\n", pkt1->print(), pkt1, sm_intf->sm_trans_id);
                DDUMP(UpDown, pkt1->getConstPtr<uint8_t>(), pkt1->getSize());
                uint32_t lane_num = sm_intf->lane_id;
                pkt1->src_nwid = lane_num; 
                pkt1->dst_nwid = lane_num; // Will need to change this later

                std::map<uint64_t, struct sendmsg_intf *>::iterator it;
                it = mem_reqs.find(sm_intf->sm_trans_id);
                //if(sm_intf->num_partials == 1)
                if(it == mem_reqs.end())
                    mem_reqs.insert(std::pair<uint64_t, struct sendmsg_intf*>(sm_intf->sm_trans_id, sm_intf));
                else
                    mem_reqs[sm_intf->sm_trans_id] = sm_intf;
                DPRINTF(UpDown, "Checking packet MemReqTrans:%d, UDID:%d Lane:%d, SrcLane:%d, DestLane:%d: %lx\n", \
                          this->udidx, lane_num, pkt1->src_nwid, pkt1->dst_nwid, pkt1->getAddr(), mem_reqs[sm_intf->sm_trans_id]->sm_trans_id);
                upstats.numSends_DmLm++;
                schedule(new gem5::EventFunctionWrapper([this, pkt1, sendPort]{ memPorts[sendPort].sendPacket(pkt1, 1); },
                                              name() + ".SendMessage", true),
                     clockEdge(gem5::Cycles(latency+(i++))));
                DPRINTF(UpDown, "Trans:%ld sent to memory with addr: %lx\n",(pkt1->req)->getTransID(), pkt1->getAddr());
            }
            mem_reqs[sm_intf->sm_trans_id]->lat_start = (uint64_t *)malloc(sizeof(uint64_t)*sm_intf->num_partials);
            for(i=0;i<sm_intf->num_partials;i++){
                mem_reqs[sm_intf->sm_trans_id]->lat_start[i]=i+latency+curTick();
            }
        }else{
            sm_intf->partial = false; // Singe request is sufficient
            DPRINTF(UpDown, "Before Translation:%lu sdest 0x%lx\n", sm_intf->sm_trans_id, sm_intf->sdest);
            uint64_t sdest_pa = this->udtrans_table.getPA(sm_intf->sdest);
            DPRINTF(UpDown, "After Translation:%lu sdest 0x%lx\n", sm_intf->sm_trans_id, sdest_pa);
            gem5::RequestPtr reqptr = std::make_shared<gem5::Request>((gem5::Addr)sdest_pa, sm_intf->ssize, reqflags, updown_id);
            reqptr->setTransID(sm_intf->sm_trans_id);
            gem5::Packet *pkt1;
            if(sm_intf->smode_2 == 0){
                pkt1 = new gem5::Packet(reqptr, gem5::MemCmd::ReadReq);
                pkt1->allocate(); // Not sure if this is actually needed. Probably is.
                upstats.upDramReadBytes+=pkt1->getSize();
            }
            else{
                pkt1 = new gem5::Packet(reqptr, gem5::MemCmd::WriteReq);
                pkt1->allocate(); // Not sure if this is actually needed. Probably is.
                pkt1->setData(sm_intf->sdata);
                upstats.upDramWriteBytes+=pkt1->getSize();
            }
            DPRINTF(UpDown, "Writing packet into map: %s, %x\n", pkt1->print(), pkt1);
            DDUMP(UpDown, pkt1->getConstPtr<uint8_t>(), pkt1->getSize());
            uint32_t lane_num = sm_intf->lane_id;
            pkt1->src_nwid = lane_num; 
            pkt1->dst_nwid = lane_num; // Will need to change this later
            mem_reqs.insert(std::pair<uint64_t, struct sendmsg_intf*>(sm_intf->sm_trans_id, sm_intf));
            mem_reqs[sm_intf->sm_trans_id]->lat_start = (uint64_t *)malloc(sizeof(uint64_t));
            mem_reqs[sm_intf->sm_trans_id]->lat_start[0]=latency+curTick();
            upstats.numSends_DmLm++;
            DPRINTF(UpDown, "UDID:%d Lane:%d, SrcLane:%d, DestLane:%d: %lx\n", this->udidx, lane_num, pkt1->src_nwid, pkt1->dst_nwid, pkt1->getAddr());
            sm_intf->print_msg();
                DPRINTF(UpDown, "Message :%s\n", sm_intf->sendmsg_str);
                DPRINTF(UpDown, "Trans:%ld sent to memory with addr: %lx\n",(pkt1->req)->getTransID(), pkt1->getAddr());
                schedule(new gem5::EventFunctionWrapper([this, pkt1, sendPort]{ memPorts[sendPort].sendPacket(pkt1, 1); },
                                              name() + ".SendMessage", true),
                     gem5::curTick());
            DPRINTF(UpDown, "Trans:%ld sent to memory with addr: %lx, from mem_map:%ld\n",(pkt1->req)->getTransID(), pkt1->getAddr(),\
                            mem_reqs[sm_intf->sm_trans_id]->sm_trans_id);
        }
    }else{
        uint32_t lane_num = sm_intf->sdest & 0x3f; // 6 bits of lane_id
        uint32_t dest_ud = (sm_intf->sdest >> 6) & 0x3; // 2 bits of UD ID for now
        uint32_t dest_nwid = (sm_intf->sdest & 0xffffffc0); // only look at UpDown Network ID
        // Add cluster and node ID here
        DPRINTF(UpDown, "UDID:%d, NWID:%d, NWID:%d\n", this->udidx, this->nwid, dest_nwid);

        if(dest_nwid == this->nwid){ // Headed for same UD
            // write continuation and operands into operand buffer, continuation into operand buffer and event into event queue
            // Schedule execute
            if(statStore[lane_num]==0){
                upstream_pyintf->insert_operand(sm_intf->scont, lane_num); // insert continuation first
                DPRINTF(UpDown, "UDID:%d, Lane:%d, OB[0]:%ld\n", this->udidx, lane_num, sm_intf->scont);
                for(int i=0; i< sm_intf->ssize/wordSize;i++){
                    upstream_pyintf->insert_operand(sm_intf->sdata_64[i], lane_num); // insert all collected operands
                    DPRINTF(UpDown, "UDID:%d Lane:%d, OB[%d]:%d\n",this->udidx, lane_num, 1+i, sm_intf->sdata_64[i]);
                }
                upstream_pyintf->insert_event(sm_intf->sevent, sm_intf->ssize/8, lane_num); // insert all collected operands
                upstats.numEvents[lane_num]++;
                struct exec_param ep = {0, lane_num};
                if(least_poss_exec_cycle[lane_num] > gem5::curTick()){
                    schedule(new gem5::EventFunctionWrapper([this, ep]{ execute(&ep); },
                                                      name() + ".execute", true),
                            least_poss_exec_cycle[lane_num]+period);
                }else {
                    schedule(new gem5::EventFunctionWrapper([this, ep]{ execute(&ep); },
                                                        name() + ".execute", true),
                            gem5::curTick()+2*period);
                }
            if(sm_intf->sdata_64)
                delete sm_intf->sdata_64;
            if(sm_intf)
                delete sm_intf;
            }else{
                DPRINTF(UpDown, "Reschedule %d due to conflict with Top\n", sm_intf->sm_trans_id);
                int lat = 4 + sm_intf->ssize/(wordSize*2); // 4 clk cycles latency + BW of 2 words / clk
                schedule(new gem5::EventFunctionWrapper([this, sm_intf]{ send_msg(sm_intf); },
                                              name() + ".SendMessage", true),
                     clockEdge(gem5::Cycles(lat))); 
            }
        }else{
            uint32_t dest_nwid_full = dest_nwid | lane_num;
            DPRINTF(UpDown, "UDID:%d, NWID:%d, dest_gl_ud_id:%d Dest NWID:%d\n", this->udidx, this->nwid, dest_nwid, dest_nwid_full);
            uint64_t destCtrlAddr = getEventQueueAddr(dest_nwid_full, upCtrlAddrBase, 32);
            // this --> Send it to the event Queue address! 
            // Create the request
            uint32_t udPort_num = (lane_num)%(num_ud_channels); // same lane num of different UDs don't conflict. 
            //uint32_t pktsize = sm_intf->ssize+16; // operand+event
            uint32_t pktsize = wordSize; // operand+event
            gem5::Request::Flags reqflags = gem5::Request::UNCACHEABLE;
            gem5::RequestPtr reqptr = std::make_shared<gem5::Request>((gem5::Addr)destCtrlAddr, pktsize, reqflags, updown_id);
            gem5::Packet *pkt1;
            //pkt1 = new gem5::Packet(reqptr, gem5::MemCmd::WriteReq);
            pkt1 = new gem5::Packet(reqptr, gem5::MemCmd::UDSend);
            pkt1->allocate(); // Not sure if this is actually needed. Probably is.
            uint8_t *ledata = new uint8_t[wordSize];
            ledata[0] = sm_intf->sevent & 0xff; 
            ledata[1] = (sm_intf->sevent >> 8) & 0xff; 
            ledata[2] = (sm_intf->sevent >> 16) & 0xff; 
            ledata[3] = (sm_intf->sevent >> 24) & 0xff; 
            ledata[4] = (sm_intf->sevent >> 32) & 0xff; 
            ledata[5] = (sm_intf->sevent >> 40) & 0xff; 
            ledata[6] = (sm_intf->sevent >> 48) & 0xff; 
            ledata[7] = (sm_intf->sevent >> 56) & 0xff; 
            for(int i=0; i< sm_intf->ssize/wordSize;i++){
                pkt1->operand_data[i] = sm_intf->sdata_64[i];
            }
            pkt1->numOb = sm_intf->ssize/wordSize;
            pkt1->setData(ledata);
            pkt1->event_word = sm_intf->sevent;
            pkt1->continuation_word = sm_intf->scont;
            pkt1->mtype = MessageType::NW;
            DPRINTF(UpDown, "Sending Packet from %lx to %d: %s, %x\n", this->udidx, dest_ud,pkt1->print(), pkt1);
            DDUMP(UpDown, pkt1->getConstPtr<uint8_t>(), pkt1->getSize());
            pkt1->setsrcnwid(this->nwid);
            pkt1->setdstnwid(dest_nwid);
            upstats.bytesSent_InterUDMessages += pktsize;  // remove event and continuation?
            DPRINTF(UpDown, "UDID:%d DestUD:%d, DestLane:%d: %lx\n", this->udidx, dest_ud, lane_num, pkt1->getAddr());
            schedule(new gem5::EventFunctionWrapper([this, pkt1, udPort_num]{ udOutPorts[udPort_num].sendPacket(pkt1, 1); },
                                              name() + ".SendMessage", true),
                     gem5::curTick()+period);
            ud_reqs.insert(std::pair<uint64_t, struct sendmsg_intf*>(sm_intf->sm_trans_id, sm_intf));
            delete ledata;

        }
    }
}

void
UpDownObj::read(gem5::PacketPtr pkt)
{
    DPRINTF(UpDown, "Reading %s\n", pkt->print());

    DDUMP(UpDown, pkt->getConstPtr<uint8_t>(), wordSize);
    gem5::Addr baseAddr;
    if(pkt->getAddr() >= sRange.start() && pkt->getAddr() < sRange.end()){
        DPRINTF(UpDown, "Debug: SRange Read Packet Addr: %lx, sStart :%lx\n", pkt->getAddr(), sRange.start());
        int lane_num = (pkt->getAddr() - sRange.start())/(scratchsize / UD_NUM_LANES);
        uint32_t laneaddr = (pkt->getAddr() - sRange.start()); // - sRange.start())%65536; // Truncating the 64bit address
        uint8_t *ledata; //= new uint8_t[wordSize];
        uint32_t size = pkt->getSize();
        ledata = new uint8_t[size];
        upstream_pyintf->read_scratch(laneaddr, ledata, size);
        upstats.topLmReadBytes+=size;
        DPRINTF(UpDown, "Scratch Read Output:%d\n", ledata[0]);

        pkt->setData(ledata);
        DPRINTF(UpDown, "Packet: after read:%s\n", pkt->print());
        DDUMP(UpDown, ledata, pkt->getSize());
	    delete ledata;
    }
    DPRINTF(UpDown, "Packet: Just belofre leaving read:%s\n", pkt->print());
}


gem5::AddrRangeList
UpDownObj::getAddrRanges() const
{
    // Just use the same ranges as whatever is on the memory side.
    gem5::AddrRangeList returnRange;
    //returnRange.merge(upAddrRange);
    for(auto const &i: upAddrRange)
        returnRange.push_back(i);
    for(auto const &i: upCtrlAddrRange)
        returnRange.push_back(i);
    return returnRange;
}

void
UpDownObj::sendRangeChange() const
{
    for (auto& port : cpuPorts) {
        port.sendRangeChange();
    }
}

