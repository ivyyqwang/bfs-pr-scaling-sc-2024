/*
 * Copyright (c) 2011-2015, 2019 ARM Limited
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
 * Copyright (c) 2002-2005 The Regents of The University of Michigan
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
 * Declaration of a non-coherent crossbar specifically for UpDown Node
 */

#ifndef __CLX_XBAR_HH__
#define __CLX_XBAR_HH__

#include "mem/xbar.hh"
#include "params/CLXBar.hh"

namespace gem5
{

  enum PortType {
        CPUIN,
        UDIN,
        CPUSIDE
  };
  #define NUM_PORTTYPES 3

/**
 * A non-coherent crossbar connects a number of non-snooping memory-side ports
 * and cpu_sides, and routes the request and response packets based on
 * the address. The request packets issued by the memory-side port connected to
 * a non-coherent crossbar could still snoop in caches attached to a
 * coherent crossbar, as is the case with the I/O bus and memory bus
 * in most system configurations. No snoops will, however, reach any
 * memory-side port on the non-coherent crossbar itself.
 *
 * The non-coherent crossbar can be used as a template for modelling
 * PCIe, and non-coherent AMBA and OCP buses, and is typically used
 * for the I/O buses.
 */
class CLXBar : public BaseXBar
{

  protected:
    /**
     * Network ID for Cluster needs to be embedded here 
     * And the Address Range of the Stack 
    */

    /**
     * Declare the layerscls this crossbar, one vector for requests
     * and one for responses.
     */
    std::vector<ReqLayer*> reqLayers;
    std::vector<RespLayer*> respLayers[NUM_PORTTYPES];
    uint64_t node_id;
    uint64_t cluster_id;
    uint32_t nodes;
    uint32_t clusters;
    uint32_t nuds;
    Addr ctrl_base_addr;
    uint64_t ctrl_addr_size;
    Addr sp_base_addr;
    uint64_t sp_addr_size;
    Addr stack_base_addr;
    uint64_t stack_addr_size;
    Addr gseg_base_addr;
    uint64_t gseg_size; 
    uint64_t node_ctrl_base;
    uint64_t node_mem_base;
    uint64_t node_sp_base;
    std::unordered_map<RequestPtr, PortID> routeTo[NUM_PORTTYPES];

    /**
     * Declaration of the non-coherent crossbar CL-side port type, one
     * will be instantiated for each of the memory-side ports connecting to
     * the crossbar.
     */
    class CLXBarResponsePort : public QueuedResponsePort
    {
      private:

        /** A reference to the crossbar to which this port belongs. */
        CLXBar &xbar;

        /** Port Type to distinguish CL, L3 and other cpuside ports*/
        PortType ptype;

        /** A normal packet queue used to store responses. */
        RespPacketQueue queue;

      public:

        CLXBarResponsePort(const std::string &_name,
                                CLXBar &_xbar, PortID _id, PortType ptype)
            : QueuedResponsePort(_name, &_xbar, queue, _id), xbar(_xbar), ptype(ptype), 
              queue(_xbar, *this)
        { }

      protected:

        bool
        recvTimingReq(PacketPtr pkt) override
        {
            return xbar.recvTimingReq(pkt, id, ptype);
        }

        Tick
        recvAtomic(PacketPtr pkt) override
        {
            return xbar.recvAtomicBackdoor(pkt, id, ptype);
        }

        Tick
        recvAtomicBackdoor(PacketPtr pkt, MemBackdoorPtr &backdoor) override
        {
            return xbar.recvAtomicBackdoor(pkt, id, ptype, &backdoor);
        }

        void
        recvFunctional(PacketPtr pkt) override
        {
            xbar.recvFunctional(pkt, id, ptype);
        }

        AddrRangeList getAddrRanges() const override;
        //{
        //    return xbar.getAddrRanges();
        //}
    };

    /**
     * Declaration of the crossbar memory-side port type, one will be
     * instantiated for each of the CL-side ports connecting to the
     * crossbar.
     */
    class CLXBarRequestPort : public RequestPort
    {
      private:

        /** A reference to the crossbar to which this port belongs. */
        CLXBar &xbar;

      public:

        CLXBarRequestPort(const std::string &_name,
                                 CLXBar &_xbar, PortID _id)
            : RequestPort(_name, &_xbar, _id), xbar(_xbar)
        { }

      protected:

        bool
        recvTimingResp(PacketPtr pkt) override
        {
            return xbar.recvTimingResp(pkt, id);
        }

        void
        recvRangeChange() override
        {
            xbar.recvRangeChange(id);
        }

        void
        recvReqRetry() override
        {
            xbar.recvReqRetry(id);
        }
    };
    void init() override;
    virtual bool recvTimingReq(PacketPtr pkt, PortID cpu_side_port_id, PortType ptype);
    virtual bool recvTimingResp(PacketPtr pkt, PortID mem_side_port_id);
    void recvReqRetry(PortID mem_side_port_id);
    Tick recvAtomicBackdoor(PacketPtr pkt, PortID cpu_side_port_id, PortType ptype,
                            MemBackdoorPtr *backdoor=nullptr);
    void recvFunctional(PacketPtr pkt, PortID cpu_side_port_id, PortType ptype);

    /**
     * Function called by the port when the crossbar is recieving a
     * range change.
     *
     * @param mem_side_port_id id of the port that received the change
     */
    virtual void recvRangeChange(PortID mem_side_port_id);

    /**
     * Find which port connected to this crossbar (if any) should be
     * given a packet with this address range.
     *
     * @param addr_range Address range to find port for.
     * @return id of port that the packet should be sent out of.
     */
    PortID findPort(AddrRange addr_range);

    // New Special Response ports
    std::vector<CLXBarResponsePort*> cpuInPorts;
    std::vector<CLXBarResponsePort*> udInPorts;
    std::vector<CLXBarResponsePort*> cpuSidePorts;
    std::vector<RequestPort*> memSidePorts;
    int num_channels;

    //statistics::Vector transDist;
    //statistics::Vector2d pktCount;
    //statistics::Vector2d pktSize;
  public:

    CLXBar(const CLXBarParams &p);
    Port &getPort(const std::string &if_name,
                  PortID idx=InvalidPortID) override;
    void regStats() override;

    virtual ~CLXBar();
};

} // namespace gem5

#endif //__UD_NONCOHERENT_XBAR_HH__
