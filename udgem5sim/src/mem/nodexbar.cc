/*
 * Copyright (c) 2011-2015, 2018-2019 ARM Limited
 * All rights reserved
 *
 * The license below extends only to copyright in the software and shall
 * not be construed as granting a license to any other intellectual
 * property including but not limited to intellectual property relating
 * to a hardware implementation of the functionality of the software
 * licensed hereunder.  You may use the software subject to the license
 * terms below provided that you ensure that this notice is replicated
 * unmodified and in its entirety in all distributions of the software,
 * modified or unmodified, in source code or in binary form.
 *
 * Copyright (c) 2006 The Regents of The University of Michigan
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
 */

/**
 * @file
 * Definition of a non-coherent crossbar object.
 */

#include "mem/nodexbar.hh"

#include "base/logging.hh"
#include "base/trace.hh"
#include "debug/XBar.hh"
#include "debug/AddrRanges.hh"

namespace gem5
{

NodeXBar::NodeXBar(const NodeXBarParams &p)
    : BaseXBar(p),
    ctrl_base_addr(p.ctrl_base_addr),
    ctrl_addr_size(p.ctrl_addr_size),
    sp_base_addr(p.sp_base_addr),
    sp_addr_size(p.sp_addr_size),
    stack_base_addr(p.stack_base_addr),
    stack_addr_size(p.stack_addr_size),
    nodes(p.nodes),
    node_id(p.node_id),
    numPorts(p.numPorts),
    intlv_low_bit(p.intlv_low_bit)
{
    // create the ports based on the size of the memory-side port and
    // Node-side port vector ports, and the presence of the default port,
    // the ports are enumerated starting from zero
    for (int i = 0; i < p.port_mem_side_ports_connection_count; ++i) {
        std::string portName = csprintf("%s.mem_side_ports[%d]", name(), i);
        RequestPort* bp = new NodeXBarRequestPort(portName, *this, i);
        memSidePorts.push_back(bp);
        reqLayers.push_back(new ReqLayer(*bp, *this,
                                         csprintf("reqLayer%d", i)));
    }

    // see if we have a default Node-side-port device connected and if so add
    // our corresponding memory-side port
    if (p.port_default_connection_count) {
        defaultPortID = memSidePorts.size();
        std::string portName = name() + ".default";
        RequestPort* bp = new NodeXBarRequestPort(portName, *this,
                                                      defaultPortID);
        memSidePorts.push_back(bp);
        reqLayers.push_back(new ReqLayer(*bp, *this, csprintf("reqLayer%d",
                                                              defaultPortID)));
    }

    // create the Node-side ports, once again starting at zero
    for (int i = 0; i < p.port_cpu_in_ports_connection_count; ++i) {
        std::string portName = csprintf("%s.cpu_in_ports[%d]", name(), i);
        NodeXBarResponsePort* bp = new NodeXBarResponsePort(portName,
                                                                *this, i, PortType::CPUIN);
        cpuInPorts.push_back(bp);
        respLayers[PortType::CPUIN].push_back(new RespLayer(*bp, *this,
                                           csprintf("respLayercpuin%d", i)));
    }

    for (int i = 0; i < p.port_node_in_ports_connection_count; ++i) {
        std::string portName = csprintf("%s.node_in_ports[%d]", name(), i);
        NodeXBarResponsePort* bp = new NodeXBarResponsePort(portName,
                                                                *this, i, PortType::NODEIN);
        nodeInPorts.push_back(bp);
        respLayers[PortType::NODEIN].push_back(new RespLayer(*bp, *this,
                                           csprintf("respLayernodein%d", i)));
    }
    //for (int i = 0; i < p.port_clx_in_ports_connection_count; ++i) {
    //    std::string portName = csprintf("%s.clx_in_ports[%d]", name(), i);
    //    NodeXBarResponsePort* bp = new NodeXBarResponsePort(portName,
    //                                                            *this, i, PortType::CLXIN);
    //    clxInPorts.push_back(bp);
    //    respLayers[PortType::CLXIN].push_back(new RespLayer(*bp, *this,
    //                                       csprintf("respLayercpui%d", i)));
    //}

}

NodeXBar::~NodeXBar()
{
    for (auto l: reqLayers)
        delete l;
    for (int i = 0; i < NUM_PORTTYPES; i++){
        for (auto l: respLayers[i])
            delete l;
    }
}

Port &NodeXBar::getPort(const std::string &if_name, PortID idx)
{
    // This is the name from the Python UpDownObj
    // declaration in UDXBar.py
    if (if_name == "cpu_in_ports" && idx < cpuInPorts.size()) {
        return *cpuInPorts[idx];
    } else if (if_name == "node_in_ports" && idx < nodeInPorts.size()) {
        return *nodeInPorts[idx];
    } else if (if_name == "mem_side_ports" && idx < memSidePorts.size()) {
        return *memSidePorts[idx];
    }else{
        // pass it along to our super class
        return ClockedObject::getPort(if_name, idx);
    }
}

PortID
NodeXBar::findPort(AddrRange addr_range)
{
    // we should never see any address lookups before we've got the
    // ranges of all connected Node-side-port modules
    assert(gotAllAddrRanges);

    // Check the address map interval tree
    auto i = portMap.contains(addr_range);
    if (i != portMap.end()) {
        return i->second;
    }

    // Check if this matches the default range
    if (useDefaultRange) {
        if (addr_range.isSubset(defaultRange)) {
            DPRINTF(AddrRanges, "  found addr %s on default\n",
                    addr_range.to_string());
            return defaultPortID;
        }
    } else if (defaultPortID != InvalidPortID) {
        DPRINTF(AddrRanges, "Unable to find destination for %s, "
                "will use default port\n", addr_range.to_string());
        return defaultPortID;
    }

    // we should use the range for the default port and it did not
    // match, or the default port is not set
    fatal("Unable to find destination for %s on %s\n", addr_range.to_string(),
          name());
}

/** Function called by the port when the crossbar is receiving a range change.*/
void
NodeXBar::recvRangeChange(PortID mem_side_port_id)
{
    DPRINTF(AddrRanges, "Received range change from cpu_side_ports %s\n",
            memSidePorts[mem_side_port_id]->getPeer());

    // remember that we got a range from this memory-side port and thus the
    // connected Node-side-port module
    gotAddrRanges[mem_side_port_id] = true;

    // update the global flag
    if (!gotAllAddrRanges) {
        // take a logical AND of all the ports and see if we got
        // ranges from everyone
        gotAllAddrRanges = true;
        std::vector<bool>::const_iterator r = gotAddrRanges.begin();
        while (gotAllAddrRanges &&  r != gotAddrRanges.end()) {
            gotAllAddrRanges &= *r++;
        }
        if (gotAllAddrRanges)
            DPRINTF(AddrRanges, "Got address ranges from all responders\n");
    }

    // note that we could get the range from the default port at any
    // point in time, and we cannot assume that the default range is
    // set before the other ones are, so we do additional checks once
    // all ranges are provided
    if (mem_side_port_id == defaultPortID) {
        // only update if we are indeed checking ranges for the
        // default port since the port might not have a valid range
        // otherwise
        if (useDefaultRange) {
            AddrRangeList ranges = memSidePorts[mem_side_port_id]->
                                   getAddrRanges();

            if (ranges.size() != 1)
                fatal("Crossbar %s may only have a single default range",
                      name());

            defaultRange = ranges.front();
        }
    } else {
        // the ports are allowed to update their address ranges
        // dynamically, so remove any existing entries
        if (gotAddrRanges[mem_side_port_id]) {
            for (auto p = portMap.begin(); p != portMap.end(); ) {
                if (p->second == mem_side_port_id)
                    // erasing invalidates the iterator, so advance it
                    // before the deletion takes place
                    portMap.erase(p++);
                else
                    p++;
            }
        }

        AddrRangeList ranges = memSidePorts[mem_side_port_id]->
                               getAddrRanges();

        for (const auto& r: ranges) {
            DPRINTF(AddrRanges, "Adding range %s for id %d\n",
                    r.to_string(), mem_side_port_id);
            if (portMap.insert(r, mem_side_port_id) == portMap.end()) {
                PortID conflict_id = portMap.intersects(r)->second;
                fatal("%s has two ports responding within range "
                      "%s:\n\t%s\n\t%s\n",
                      name(),
                      r.to_string(),
                      memSidePorts[mem_side_port_id]->getPeer(),
                      memSidePorts[conflict_id]->getPeer());
            }
        }
    }

    // if we have received ranges from all our neighbouring Node-side-port
    // modules, go ahead and tell our connected memory-side-port modules in
    // turn, this effectively assumes a tree structure of the system
    if (gotAllAddrRanges) {
        DPRINTF(AddrRanges, "Aggregating address ranges\n");
        xbarRanges.clear();

        // start out with the default range
        if (useDefaultRange) {
            if (!gotAddrRanges[defaultPortID])
                fatal("Crossbar %s uses default range, but none provided",
                      name());

            xbarRanges.push_back(defaultRange);
            DPRINTF(AddrRanges, "-- Adding default %s\n",
                    defaultRange.to_string());
        }

        // merge all interleaved ranges and add any range that is not
        // a subset of the default range
        std::vector<AddrRange> intlv_ranges;
        for (const auto& r: portMap) {
            // if the range is interleaved then save it for now
            if (r.first.interleaved()) {
                // if we already got interleaved ranges that are not
                // part of the same range, then first do a merge
                // before we add the new one
                if (!intlv_ranges.empty() &&
                    !intlv_ranges.back().mergesWith(r.first)) {
                    DPRINTF(AddrRanges, "-- Merging range from %d ranges\n",
                            intlv_ranges.size());
                    AddrRange merged_range(intlv_ranges);
                    // next decide if we keep the merged range or not
                    if (!(useDefaultRange &&
                          merged_range.isSubset(defaultRange))) {
                        xbarRanges.push_back(merged_range);
                        DPRINTF(AddrRanges, "-- Adding merged range %s\n",
                                merged_range.to_string());
                    }
                    intlv_ranges.clear();
                }
                intlv_ranges.push_back(r.first);
            } else {
                // keep the current range if not a subset of the default
                if (!(useDefaultRange &&
                      r.first.isSubset(defaultRange))) {
                    xbarRanges.push_back(r.first);
                    DPRINTF(AddrRanges, "-- Adding range %s\n",
                            r.first.to_string());
                }
            }
        }

        // if there is still interleaved ranges waiting to be merged,
        // go ahead and do it
        if (!intlv_ranges.empty()) {
            DPRINTF(AddrRanges, "-- Merging range from %d ranges\n",
                    intlv_ranges.size());
            AddrRange merged_range(intlv_ranges);
            if (!(useDefaultRange && merged_range.isSubset(defaultRange))) {
                xbarRanges.push_back(merged_range);
                DPRINTF(AddrRanges, "-- Adding merged range %s\n",
                        merged_range.to_string());
            }
        }

        // also check that no range partially intersects with the
        // default range, this has to be done after all ranges are set
        // as there are no guarantees for when the default range is
        // update with respect to the other ones
        if (useDefaultRange) {
            for (const auto& r: xbarRanges) {
                // see if the new range is partially
                // overlapping the default range
                if (r.intersects(defaultRange) &&
                    !r.isSubset(defaultRange))
                    fatal("Range %s intersects the "                    \
                          "default range of %s but is not a "           \
                          "subset\n", r.to_string(), name());
            }
        }

        // tell all our neighbouring memory-side ports that our address
        // ranges have changed
        //for (const auto& port: cpuSidePorts)
        //    port->sendRangeChange();
    }
}


bool
NodeXBar::recvTimingReq(PacketPtr pkt, PortID cpu_side_port_id, PortType ptype)
{
    // Request could come from any of the UDs connected to the Cluster XBar 
    // Or it could come from another Cluster X Bar for Memory! 
    // distinguish this through packet-type! 
    // If NW pkt -> send to the corret UD or Node XBar
    ResponsePort *src_port; 
        //.init(cpuInPorts.size()+nodeInPorts.size(), memSidePorts.size())
    int stat_port;
    if(ptype == PortType::NODEIN){
        src_port = nodeInPorts[cpu_side_port_id];
        stat_port = cpuInPorts.size() + cpu_side_port_id;
    }
    else if(ptype == PortType::CPUIN){
        src_port = cpuInPorts[cpu_side_port_id];
        stat_port = cpu_side_port_id;
    }
    else{
        src_port = cpuSidePorts[cpu_side_port_id];
        stat_port = cpu_side_port_id;
    }

    // we should never see express snoops on a non-coherent crossbar
    assert(!pkt->isExpressSnoop());

    // determine the destination based on the address
    PortID mem_side_port_id = findPort(pkt->getAddrRange());

    // test if the layer should be considered occupied for the current
    // port
    if (!reqLayers[mem_side_port_id]->tryTiming(src_port)) {
        DPRINTF(NodeXBar, "recvTimingReq: src %s %s 0x%x BUSY\n",
                src_port->name(), pkt->cmdString(), pkt->getAddr());
        return false;
    }

    DPRINTF(NodeXBar, "recvTimingReq: src %s %s 0x%x\n",
            src_port->name(), pkt->cmdString(), pkt->getAddr());

    // store size and command as they might be modified when
    // forwarding the packet
    //unsigned int pkt_size = pkt->hasData() ? pkt->getSize() : 0;
    unsigned int pkt_size = (pkt->mtype == MessageType::NW)? (pkt->numOb * 8) : (pkt->hasData() ? pkt->getSize() : 0);
    unsigned int pkt_cmd = pkt->cmdToIndex();

    // store the old header delay so we can restore it if needed
    Tick old_header_delay = pkt->headerDelay;

    // a request sees the frontend and forward latency
    Tick xbar_delay = (frontendLatency + forwardLatency) * clockPeriod();

    // set the packet header and payload delay
    calcPacketTiming(pkt, xbar_delay);

    // determine how long to be crossbar layer is busy
    Tick packetFinishTime = clockEdge(Cycles(1)); // + pkt->payloadDelay + pkt->headerDelay;

    // before forwarding the packet (and possibly altering it),
    // remember if we are expecting a response
    const bool expect_response = pkt->needsResponse() &&
        !pkt->cacheResponding();

    // since it is a normal request, attempt to send the packet
    bool success = memSidePorts[mem_side_port_id]->sendTimingReq(pkt);

    if (!success)  {
        DPRINTF(NodeXBar, "recvTimingReq: src %s %s 0x%x RETRY\n",
                src_port->name(), pkt->cmdString(), pkt->getAddr());

        // restore the header delay as it is additive
        pkt->headerDelay = old_header_delay;

        // occupy until the header is sent
        reqLayers[mem_side_port_id]->failedTiming(src_port,
                                                clockEdge(Cycles(1)));

        return false;
    }

    // remember where to route the response to
    if (expect_response) {
        assert(routeTo[ptype].find(pkt->req) == routeTo[ptype].end());
        routeTo[ptype][pkt->req] = cpu_side_port_id;
    }

    reqLayers[mem_side_port_id]->succeededTiming(packetFinishTime);

    // stats updates
    pktCount[stat_port][mem_side_port_id]++;
    pktSize[stat_port][mem_side_port_id] += pkt_size;
    transDist[pkt_cmd]++;
    //pktCount[cpu_side_port_id][mem_side_port_id]++;
    //pktSize[cpu_side_port_id][mem_side_port_id] += pkt_size;
    //transDist[pkt_cmd]++;

    return true;
}

bool
NodeXBar::recvTimingResp(PacketPtr pkt, PortID mem_side_port_id)
{
    // determine the source port based on the id
    RequestPort *src_port = memSidePorts[mem_side_port_id];

    // determine the destination
    PortID cpu_side_port_id;
    PortType ptype;
    std::unordered_map<RequestPtr, PortID>::iterator route_lookup;
    for(int i = 0; i < NUM_PORTTYPES; i++){
        route_lookup = routeTo[i].find(pkt->req);
        if(route_lookup != routeTo[i].end()){
            cpu_side_port_id = route_lookup->second;
            ptype = (PortType)i;
            break;
        }
    }
    assert(cpu_side_port_id != InvalidPortID);
    assert(cpu_side_port_id < respLayers[ptype].size());

    // test if the layer should be considered occupied for the current
    // port
    if (!respLayers[ptype][cpu_side_port_id]->tryTiming(src_port)) {
        DPRINTF(NodeXBar, "recvTimingResp: src %s %s 0x%x BUSY\n",
                src_port->name(), pkt->cmdString(), pkt->getAddr());
        return false;
    }

    DPRINTF(NodeXBar, "recvTimingResp: src %s %s 0x%x\n",
            src_port->name(), pkt->cmdString(), pkt->getAddr());

    // store size and command as they might be modified when
    // forwarding the packet
    unsigned int pkt_size = pkt->hasData() ? pkt->getSize() : 0;
    unsigned int pkt_cmd = pkt->cmdToIndex();

    // a response sees the response latency
    Tick xbar_delay = responseLatency * clockPeriod();

    // set the packet header and payload delay
    calcPacketTiming(pkt, xbar_delay);

    // determine how long to be crossbar layer is busy
    Tick packetFinishTime = clockEdge(Cycles(1)) + pkt->payloadDelay;

    // send the packet through the destination Node-side port, and pay for
    // any outstanding latency
    Tick latency = pkt->headerDelay;
    pkt->headerDelay = 0;
    switch(ptype){
        case PortType::CPUIN:
            cpuInPorts[cpu_side_port_id]->schedTimingResp(pkt,
                                        curTick() + latency);
        break;
        case PortType::NODEIN:
            nodeInPorts[cpu_side_port_id]->schedTimingResp(pkt,
                                        curTick() + latency);
        break;
        //case PortType::CLXIN:
        //    clxInPorts[cpu_side_port_id]->schedTimingResp(pkt,
        //                                curTick() + latency);
        //break;
        default:
            cpuInPorts[cpu_side_port_id]->schedTimingResp(pkt,
                                        curTick() + latency);
    }
    // remove the request from the routing table
    routeTo[ptype].erase(route_lookup);

    respLayers[ptype][cpu_side_port_id]->succeededTiming(packetFinishTime);

    // stats updates
    pktCount[cpu_side_port_id][mem_side_port_id]++;
    pktSize[cpu_side_port_id][mem_side_port_id] += pkt_size;
    transDist[pkt_cmd]++;

    return true;
}

void
NodeXBar::recvReqRetry(PortID mem_side_port_id)
{
    // responses never block on forwarding them, so the retry will
    // always be coming from a port to which we tried to forward a
    // request
    reqLayers[mem_side_port_id]->recvRetry();
}

Tick
NodeXBar::recvAtomicBackdoor(PacketPtr pkt, PortID cpu_side_port_id, PortType ptype,
                                    MemBackdoorPtr *backdoor)
{
    //DPRINTF(NodeXBar, "recvAtomic: packet src %s addr 0x%x cmd %s\n",
    //        cpuSidePorts[cpu_side_port_id]->name(), pkt->getAddr(),
    //        pkt->cmdString());

    unsigned int pkt_size = pkt->hasData() ? pkt->getSize() : 0;
    unsigned int pkt_cmd = pkt->cmdToIndex();

    // determine the destination port
    PortID mem_side_port_id = findPort(pkt->getAddrRange());

    // stats updates for the request
    //pktCount[cpu_side_port_id][mem_side_port_id]++;
    //pktSize[cpu_side_port_id][mem_side_port_id] += pkt_size;
    //transDist[pkt_cmd]++;

    // forward the request to the appropriate destination
    auto mem_side_port = memSidePorts[mem_side_port_id];
    Tick response_latency = backdoor ?
        mem_side_port->sendAtomicBackdoor(pkt, *backdoor) :
        mem_side_port->sendAtomic(pkt);

    // add the response data
    if (pkt->isResponse()) {
        pkt_size = pkt->hasData() ? pkt->getSize() : 0;
        pkt_cmd = pkt->cmdToIndex();

        // stats updates
    //    pktCount[cpu_side_port_id][mem_side_port_id]++;
    //    pktSize[cpu_side_port_id][mem_side_port_id] += pkt_size;
    //    transDist[pkt_cmd]++;
    }

    // @todo: Not setting first-word time
    pkt->payloadDelay = response_latency;
    return response_latency;
}

void
NodeXBar::recvFunctional(PacketPtr pkt, PortID cpu_side_port_id, PortType ptype)
{
    //if (!pkt->isPrint()) {
    //    // don't do DPRINTFs on PrintReq as it clutters up the output
    //    DPRINTF(NodeXBar,
    //            "recvFunctional: packet src %s addr 0x%x cmd %s\n",
    //            cpuSidePorts[cpu_side_port_id]->name(), pkt->getAddr(),
    //            pkt->cmdString());
    //}

    // since our Node-side ports are queued ports we need to check them as well
    for (const auto& p : cpuInPorts) {
        // if we find a response that has the data, then the
        // downstream caches/memories may be out of date, so simply stop
        // here
        if (p->trySatisfyFunctional(pkt)) {
            if (pkt->needsResponse())
                pkt->makeResponse();
            return;
        }
    }
    //for (const auto& p : clxInPorts) {
    //    // if we find a response that has the data, then the
    //    // downstream caches/memories may be out of date, so simply stop
    //    // here
    //    if (p->trySatisfyFunctional(pkt)) {
    //        if (pkt->needsResponse())
    //            pkt->makeResponse();
    //        return;
    //    }
    //}
    for (const auto& p : nodeInPorts) {
        // if we find a response that has the data, then the
        // downstream caches/memories may be out of date, so simply stop
        // here
        if (p->trySatisfyFunctional(pkt)) {
            if (pkt->needsResponse())
                pkt->makeResponse();
            return;
        }
    }
    // for (const auto& p : l3InPorts) {
    //     // if we find a response that has the data, then the
    //     // downstream caches/memories may be out of date, so simply stop
    //     // here
    //     if (p->trySatisfyFunctional(pkt)) {
    //         if (pkt->needsResponse())
    //             pkt->makeResponse();
    //         return;
    //     }
    // }

    // determine the destination port
    PortID dest_id = findPort(pkt->getAddrRange());

    // forward the request to the appropriate destination
    memSidePorts[dest_id]->sendFunctional(pkt);
}

void
NodeXBar::regStats()
{
    ClockedObject::regStats();

    using namespace statistics;

    transDist
        .init(MemCmd::NUM_MEM_CMDS)
        .flags(nozero);

    // get the string representation of the commands
    for (int i = 0; i < MemCmd::NUM_MEM_CMDS; i++) {
        MemCmd cmd(i);
        const std::string &cstr = cmd.toString();
        transDist.subname(i, cstr);
    }

    pktCount
        .init(cpuInPorts.size()+nodeInPorts.size(), memSidePorts.size())
        .flags(total | nozero | nonan);

    pktSize
        .init(cpuInPorts.size()+nodeInPorts.size(), memSidePorts.size())
        .flags(total | nozero | nonan);

    // both the packet count and total size are two-dimensional
    // vectors, indexed by Node-side port id and memory-side port id, thus the
    // neighbouring memory-side ports and Node-side ports, they do not
    // differentiate what came from the memory-side ports and was forwarded to
    // the Node-side ports (requests and snoop responses) and what came from
    // the Node-side ports and was forwarded to the memory-side ports (responses
    // and snoop requests)
    for (int i = 0; i < cpuInPorts.size(); i++) {
        pktCount.subname(i, cpuInPorts[i]->getPeer().name());
        pktSize.subname(i, cpuInPorts[i]->getPeer().name());
        for (int j = 0; j < memSidePorts.size(); j++) {
            pktCount.ysubname(j, memSidePorts[j]->getPeer().name());
            pktSize.ysubname(j, memSidePorts[j]->getPeer().name());
        }
    }
    for (int i = 0; i < nodeInPorts.size(); i++) {
        pktCount.subname(i+cpuInPorts.size(), nodeInPorts[i]->getPeer().name());
        pktSize.subname(i+cpuInPorts.size(), nodeInPorts[i]->getPeer().name());
        for (int j = 0; j < memSidePorts.size(); j++) {
            pktCount.ysubname(j, memSidePorts[j]->getPeer().name());
            pktSize.ysubname(j, memSidePorts[j]->getPeer().name());
        }
    }
    // for (int i = 0; i < l3InPorts.size(); i++) {
    //     pktCount.subname(i+cpuSidePorts.size()+cpuInPorts.size(), l3InPorts[i]->getPeer().name());
    //     pktSize.subname(i+cpuSidePorts.size()+cpuInPorts.size(), l3InPorts[i]->getPeer().name());
    //     for (int j = 0; j < memSidePorts.size(); j++) {
    //         pktCount.ysubname(j, memSidePorts[j]->getPeer().name());
    //         pktSize.ysubname(j, memSidePorts[j]->getPeer().name());
    //     }
    // }
    //for (int i = 0; i < clxInPorts.size(); i++) {
    //    pktCount.subname(i+cpuSidePorts.size()+cpuInPorts.size()+l3InPorts.size(), clxInPorts[i]->getPeer().name());
    //    pktSize.subname(i+cpuSidePorts.size()+cpuInPorts.size()+l3InPorts.size(), clxInPorts[i]->getPeer().name());
    //    for (int j = 0; j < memSidePorts.size(); j++) {
    //        pktCount.ysubname(j, memSidePorts[j]->getPeer().name());
    //        pktSize.ysubname(j, memSidePorts[j]->getPeer().name());
    //    }
    //}
}
void
NodeXBar::init(){
    for (auto port : nodeInPorts) {
        if(port->isConnected())
            port->sendRangeChange();
    }
    for (auto port : cpuInPorts) {
        if(port->isConnected())
            port->sendRangeChange();
    }
    //for (auto port : clxInPorts) {
    //    if(port->isConnected())
    //        port->sendRangeChange();
    //}
    // for (auto port : l3InPorts) {
    //     if(port->isConnected())
    //         port->sendRangeChange();
    // }
}

AddrRangeList NodeXBar::NodeXBarResponsePort::getAddrRanges() const
{
    gem5::AddrRangeList inAddrRanges, finalAddrRanges;
    gem5::AddrRange r;
    int intlv_bits = (int)(log2(xbar.numPorts));
    if(this->ptype == PortType::NODEIN){
        r = gem5::AddrRange(xbar.ctrl_base_addr + xbar.node_id * xbar.ctrl_addr_size, xbar.ctrl_base_addr + (xbar.node_id+1)*xbar.ctrl_addr_size);
        inAddrRanges.push_back(r);
        r = gem5::AddrRange(xbar.sp_base_addr + xbar.node_id * xbar.sp_addr_size , xbar.sp_base_addr + (xbar.node_id + 1) * xbar.sp_addr_size);
        inAddrRanges.push_back(r);
        r = gem5::AddrRange(xbar.stack_base_addr + xbar.node_id * xbar.stack_addr_size, xbar.stack_base_addr + (xbar.node_id + 1) * xbar.stack_addr_size);
        inAddrRanges.push_back(r);
        return inAddrRanges;
    }else{
        // REst of the system's addresses
        for(int i = 0; i < xbar.nodes; i++){
            if(i == xbar.node_id)
                continue;
            r = gem5::AddrRange(xbar.ctrl_base_addr + i*xbar.ctrl_addr_size, xbar.ctrl_base_addr + (i+1)*xbar.ctrl_addr_size);
            inAddrRanges.push_back(r);
            r = gem5::AddrRange(xbar.stack_base_addr + i*xbar.stack_addr_size, xbar.stack_base_addr + (i+1)*xbar.stack_addr_size);
            inAddrRanges.push_back(r);
            r = gem5::AddrRange(xbar.sp_base_addr + i*xbar.sp_addr_size, xbar.sp_base_addr + (i+1)*xbar.sp_addr_size);
            inAddrRanges.push_back(r);
        }
        for(auto& r : inAddrRanges){
        AddrRange prange =  AddrRange(r.start(), r.end(), xbar.intlv_low_bit + intlv_bits-1,
              0, intlv_bits,
              (this->id) % xbar.numPorts);
        finalAddrRanges.push_back(prange);
        }
        return finalAddrRanges;
    }
}

} // namespace gem5
