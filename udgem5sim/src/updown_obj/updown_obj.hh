#ifndef __UPDOWN_OBJECT_HH__
#define __UPDOWN_OBJECT_HH__

/**
 * @file updown_obj.hh
 *
 * @author Andronicus based on work by Jose M Monsalve Diaz
 * @brief Definition of a simple updown object
 * @version 0.1
 * @date 2021-09-14
 *
 * @copyright Copyright (c) 2021
 *
 * This file is based on the simple_cache.hh example
 * in the learning_gem5 folder. The following Copyright applies:
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
 *  ======= FILE DESCRIPTION =========
 *
 * This file implements the first and simplest version of the
 * updown object. The idea is that the CPU will send memory
 * requests to this object that can either store the scratchpad memory.
 * or it can be part of the EventQ or Operand Buffer
 * The scratchpad memory will be allocated here, and pass to the
 * spike simulator as a memory mapped plugin. Therefore,
 * Gem5 and spike can communicate with each other.
 *
 * For now the CPU communicates to the updown,
 * but the updown never send messages (other than ACK)
 * to the CPU. The updown only send messages to
 * DRAM in the form of stores (and eventually loads?)
 *
 * TODO: Questions
 * * How does the updown know the location in DRAM of the result?
 * * It is still not clear now the clock information between
 *   spike and gem5 will work. Therefore, timing is still not working
 *
 */

#include <thread>
#include <vector>
#include <iostream>
#include <fstream>
//#include "updown/upstream_pyintf.hh"
#include <unistd.h>
#include <cstdlib>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string>
#include <queue>

#include "debug/UpDown.hh"
#include "base/statistics.hh"
#include "mem/port.hh"
#include "params/UpDownObj.hh"
#include "sim/clocked_object.hh" // subclass of sim_object
#include "updown/runtime/include/updown_config.h"
#include "updown/simruntime/include/sim_stats.hh"
#include "updown/udbasim/common/include/mmessage.hh"
#define UD_NUM_LANES DEF_NUM_LANES
#define MEM_ORDERING_DEPRECATED
#define UD_NUM_STACKS DEF_NUM_STACKS
#define UD_NUM_NODES DEF_NUM_NODES

class Upstream_PyIntf;

struct sendmsg{
  uint8_t rw;
  uint32_t lane_id;
  uint64_t saddr;
  uint32_t sdest;
  uint32_t ssize;
  uint32_t smode;
  uint32_t snum_oper;
  uint32_t sevent_word;
};

struct sendmsg_intf{
  uint64_t sm_trans_id;
  uint64_t sst_id;
  uint64_t gseq;
  uint64_t gseq_stat; // Arrived and Pushed or not
  uint32_t send_policy; // Lane ID for continuation
  uint32_t node_id; // Lane ID for continuation
  uint32_t stack_id; // Lane ID for continuation
  uint32_t ud_num; // Lane ID for continuation
  uint32_t lane_id; // Lane ID for continuation
  uint64_t sevent; // Dest Event
  uint64_t sdest; // Dest Addr / Lane Num
  uint64_t sdest_VA; // Dest Addr / Lane Num
  uint64_t scont; // Continuation Word
  uint32_t ssize; // Size in bytes 
  uint32_t smode_0; // Mode - lane/mem
  uint32_t smode_1; // Mode - return to same lane?
  uint32_t smode_2; // Mode - load/store
  uint8_t* sdata; // Store Data / Data to be sent to another lane etc.. in bytes
  uint64_t* sdata_64; // Store Data / Data to be sent to another lane etc.. in bytes
  bool old_send; // Old send interface!
  bool partial=false;
  int num_partials=0;
  int num_recvd=0;
  int bytes_recvd=0;
  uint8_t* partial_data;
  char sendmsg_str[300];
  int sendmsg_size=0;
  char *sendmsg_data; 
  int sendmsg_dsize=0;
  uint64_t *lat_start;
  void print_msg(void){
        this->sendmsg_size = sprintf(this->sendmsg_str, "SendMsg_Intf TransID:%d->[Event:%ld, Dest:%lx, Cont:%ld, \
        Size:%d, SM0:%d, SM1:%d, SM2:%d, OldSend:%d, Partial:%d, \
        Num_partials:%d, Num_Recvd:%d]\n", this->sm_trans_id, this->sevent, this->sdest, this->scont, this->ssize,\
        this->smode_0, this->smode_1, this->smode_2, this->old_send, this->partial, this->num_partials,\
        this->num_recvd);
  }
  void print_pdata(void){
        this->sendmsg_dsize = sizeof(char)*(this->ssize+1);
        this->sendmsg_data = (char*)malloc(sizeof(char)*this->sendmsg_dsize);
        int i=0;
        for(i =0; i<this->ssize;i++)
          this->sendmsg_data[i] = (char)this->partial_data[i];
        this->sendmsg_data[i] = '\0';
        //int n = sprintf(this->sendmsg_data,"%s", this->sendmsg_data);
  }
};

struct exec_param{
  int cont;
  int lane_num;
};

struct super_trans{
   int num_seq;
   uint64_t *trans_id; 
   int *trans_stat; 
   int all_done;
   int seq_done;
   // 0 - not arrived
   // 1 - arrived not pushed
   // 2 - pushed into operand
};


struct event_operand{
    uint32_t event_word;
    uint32_t *ops;
    uint32_t num_ops;
};

enum TransType {
    Local,
    Global
};

struct udtrans_entry{
   TransType ttype;
   gem5::Addr base; // Virtual Addr Base?
   long offset; // VA/PA offset PA = VA + offset (can be negative)
   gem5::Addr limit; // Limit for the segment
   // For Global
   gem5::Addr pa_base;
   uint64_t swizzle_mask;
};

class UDTranslations{
    protected:
        uint32_t node_id;
        uint32_t network_id;
        std::vector<udtrans_entry> translations;
    public:
        UDTranslations():node_id(0), network_id(0){};
        UDTranslations(uint32_t _node_id, uint32_t _nwid):node_id(_node_id), network_id(_nwid)
        {}
        void addTranslation(struct udtrans_entry udtrans){
            translations.push_back(udtrans);
        }
        gem5::Addr getPA(gem5::Addr _va){
            bool trans_exists = false;
            gem5::Addr pa;
            for(const auto& entry : translations){
                if(entry.ttype == TransType::Local){
                    if(_va >= entry.base && _va < entry.limit){
                        trans_exists = true;
                        //pa = _va + entry.offset;
                        pa = (_va - entry.base) + entry.pa_base;
                        break;
                    }
                }else{
                        // for now this calculation can remain the same -- will change when there are other translations
                    if(_va >= entry.base && _va < entry.limit){
                        trans_exists = true;
                        //pa = _va + entry.offset;
                        pa = (_va - entry.base) + entry.pa_base;
                        break;
                    }    
                }
            }
            if(trans_exists)
                return pa;
            else
                fatal("%ld: PA/VA mapping does not exist in UD:%d, VA:%ld", gem5::curTick(), this->network_id, _va);

        }
        gem5::Addr getVA(gem5::Addr _pa){
            bool trans_exists = false;
            gem5::Addr va;
            for(const auto& entry : translations){
                va = _pa - entry.pa_base + entry.base;
                if(va >= entry.base && va < entry.limit){
                        trans_exists = true;
                        break;
                }
            }
            if(trans_exists)
                return va;
            else
                fatal("%ld: VA/PA mapping does not exist in UD:%d, VA:%ld", gem5::curTick(), this->network_id, _pa);

        }
        ~UDTranslations(){
        }
};


typedef enum addr_region {EVQ, OPB, SPD, SPD2, STAT, EXEC, INV} addr_region_t;

typedef std::vector<gem5::PacketPtr> PacketPtr_vec;

class UpDownObj : public gem5::ClockedObject
{
  private:

  uint32_t updown_id;
  uint32_t udidx;
  uint32_t nwid;
    /**
     * Port on the CPU-side that receives requests.
     */
    class CPUSidePort : public gem5::ResponsePort
    {
      private:
        /// Since this is a vector port, need to know what number this one is
        int id;

        UpDownObj *owner;

        /// True if the port needs to send a retry req.
        bool needRetry;

        /// If we tried to send a packet and it was blocked, store it here
        gem5::PacketPtr blockedPacket;
        std::vector<gem5::PacketPtr> blockedPacket_vec;

      public:
        /**
         * Constructor. Just calls the superclass constructor.
         */
        CPUSidePort(const std::string& name, int id, UpDownObj *owner) :
            ResponsePort(name, owner), id(id), owner(owner), needRetry(false),
            blockedPacket(nullptr)
        { }

        /**
         * Send a packet across this port. This is called by the owner and
         * all of the flow control is hanled in this function.
         * This is a convenience function for the SimpleCache to send pkts.
         *
         * @param packet to send.
         */
        void sendPacket(gem5::PacketPtr pkt, int ins_new);

        /**
         * Get a list of the non-overlapping address ranges the owner is
         * responsible for. All response ports must override this function
         * and return a populated list with at least one item.
         *
         * @return a list of ranges responded to
         */
        gem5::AddrRangeList getAddrRanges() const override;

        /**
         * Send a retry to the peer port only if it is needed.
         */
        void trySendRetry();

      protected:
        /**
         * Receive an atomic request packet from the request port.
         */
        gem5::Tick recvAtomic(gem5::PacketPtr pkt) override;
        //{ panic("recvAtomic unimpl."); }

        /**
         * Receive a functional request packet from the request port.
         *
         * @param packet the requestor sent.
         */
        void recvFunctional(gem5::PacketPtr pkt) override;

        /**
         * Receive a timing request from the request port.
         *
         * @param the packet that the requestor sent
         * @return whether this object can consume to packet. If false, we
         *         will call sendRetry() when we can try to receive this
         *         request again.
         */
        bool recvTimingReq(gem5::PacketPtr pkt) override;

        /**
         * Called by the request port if sendTimingResp was called on this
         * response port (causing recvTimingResp to be called on the request
         * port) and was unsuccessful.
         */
        void recvRespRetry() override;
    };


    /**
     * Port on the memory-side that receives responses.
     */
    class MemSidePort : public gem5::RequestPort
    {
      private:
        UpDownObj *owner;
        int id;

        /// If we tried to send a packet and it was blocked, store it here
        gem5::PacketPtr blockedPacket;
        std::vector<gem5::PacketPtr> blockedPacket_vec;
        bool retrystate;

      public:
        /**
         * Constructor. Just calls the superclass constructor.
         */
        MemSidePort(const std::string& name, int id,UpDownObj *owner) :
            RequestPort(name, owner), id(id), owner(owner), blockedPacket(nullptr)
        { }

        /**
         * Send a packet across this port. This is called by the owner and
         * all of the flow control is hanled in this function.
         *
         * @param packet to send.
         */
        void sendPacket(gem5::PacketPtr pkt, int ins_new);

      protected:
        /**
         * Receive a timing response from the response port.
         */
        bool recvTimingResp(gem5::PacketPtr pkt) override;

        /**
         * Called by the response port if sendTimingReq was called on this
         * request port (causing recvTimingReq to be called on the response
         * port) and was unsuccesful.
         */
        void recvReqRetry() override;

        /**
         * Called to receive an address range change from the peer response
         * port. The default implementation ignores the change and does
         * nothing. Override this function in a derived class if the owner
         * needs to be aware of the address ranges, e.g. in an
         * interconnect component like a bus.
         */
        //void recvRangeChange() override;
    };
//  
     /* In coming Requests from other UpDowns */   
    // class UDSideInPort : public gem5::ResponsePort
    //{
    //  private:

    //    UpDownObj *owner;
    //    int id;

    //    /// True if the port needs to send a retry req.
    //    bool needRetry;

    //    /// If we tried to send a packet and it was blocked, store it here
    //    gem5::PacketPtr blockedPacket;
    //    std::vector<gem5::PacketPtr> blockedPacket_vec;

    //  public:
    //    /**
    //     * Constructor. Just calls the superclass constructor.
    //     */
    //    UDSideInPort(const std::string& name, int id, UpDownObj *owner) :
    //        ResponsePort(name, owner), id(id),owner(owner), needRetry(false),
    //        blockedPacket(nullptr)
    //    { }

    //    /**
    //     * Send a packet across this port. This is called by the owner and
    //     * all of the flow control is hanled in this function.
    //     * This is a convenience function for the SimpleCache to send pkts.
    //     *
    //     * @param packet to send.
    //     */
    //    void sendPacket(gem5::PacketPtr pkt, int ins_new);

    //    /**
    //     * Get a list of the non-overlapping address ranges the owner is
    //     * responsible for. All response ports must override this function
    //     * and return a populated list with at least one item.
    //     *
    //     * @return a list of ranges responded to
    //     */
    //    gem5::AddrRangeList getAddrRanges() const override;

    //    /**
    //     * Send a retry to the peer port only if it is needed.
    //     */
    //    void trySendRetry();

    //  protected:
    //    /**
    //     * Receive an atomic request packet from the request port.
    //     */
    //    gem5::Tick recvAtomic(gem5::PacketPtr pkt) override
    //    { panic("recvAtomic unimpl."); }

    //    /**
    //     * Receive a functional request packet from the request port.
    //     *
    //     * @param packet the requestor sent.
    //     */
    //    void recvFunctional(gem5::PacketPtr pkt) override;

    //    /**
    //     * Receive a timing request from the request port.
    //     *
    //     * @param the packet that the requestor sent
    //     * @return whether this object can consume to packet. If false, we
    //     *         will call sendRetry() when we can try to receive this
    //     *         request again.
    //     */
    //    bool recvTimingReq(gem5::PacketPtr pkt) override;

    //    /**
    //     * Called by the request port if sendTimingResp was called on this
    //     * response port (causing recvTimingResp to be called on the request
    //     * port) and was unsuccessful.
    //     */
    //    void recvRespRetry() override;
    //};


     /* 
     * Outgoing Requests to other UpDowns 
     */   
    class UDSideOutPort : public gem5::RequestPort
    {
      private:
        UpDownObj *owner;
        int id;

        /// If we tried to send a packet and it was blocked, store it here
        gem5::PacketPtr blockedPacket;
        std::vector<gem5::PacketPtr> blockedPacket_vec;
        bool retrystate;

      public:
        /**
         * Constructor. Just calls the superclass constructor.
         */
        UDSideOutPort(const std::string& name, int id, UpDownObj *owner) :
            RequestPort(name, owner), id(id), owner(owner), blockedPacket(nullptr)
        { }

        /**
         * Send a packet across this port. This is called by the owner and
         * all of the flow control is hanled in this function.
         *
         * @param packet to send.
         */
        void sendPacket(gem5::PacketPtr pkt, int ins_new);

      protected:
        /**
         * Receive a timing response from the response port.
         */
        bool recvTimingResp(gem5::PacketPtr pkt) override;

        /**
         * Called by the response port if sendTimingReq was called on this
         * request port (causing recvTimingReq to be called on the response
         * port) and was unsuccesful.
         */
        void recvReqRetry() override;

        /**
         * Called to receive an address range change from the peer response
         * port. The default implementation ignores the change and does
         * nothing. Override this function in a derived class if the owner
         * needs to be aware of the address ranges, e.g. in an
         * interconnect component like a bus.
         */
        //void recvRangeChange() override;
    };   
    /**
     * Handle the request from the CPU side. Called from the CPU port
     * on a timing request.
     *
     * @param requesting packet
     * @param id of the port to send the response
     * @return true if we can handle the request this cycle, false if the
     *         requestor needs to retry later
     */
    bool handleCPURequest(gem5::PacketPtr pkt, int port_id);
    bool handleUDRequest(gem5::PacketPtr pkt, int port_id);

    /**
     * Handle the respone from the memory side. Called from the memory port
     * on a timing response.
     *
     * @param responding packet
     * @return true if we can handle the response this cycle, false if the
     *         responder needs to retry later
     */
    bool handleDRAMResponse(gem5::PacketPtr pkt);

    /**
     * Send the packet to the CPU side.
     * This function assumes the pkt is already a response packet and forwards
     * it to the correct port. This function also unblocks this object and
     * cleans up the whole request.
     *
     * @param the packet to send to the cpu side
     */
    void sendCPUResponse(gem5::PacketPtr pkt);
    //void sendUDResponse(gem5::PacketPtr pkt, int port_id);

    /**
     * Handle a packet functionally. Update the data on a write and get the
     * data on a read. Called from CPU port on a recv functional.
     *
     * @param packet to functionally handle
     */
    void handleCPUFunctional(gem5::PacketPtr pkt);
    void handleUDFunctional(gem5::PacketPtr pkt);

    /**
     * For timing request
     */
    void accessCPUTiming(gem5::PacketPtr pkt);
    void accessUDTiming(gem5::PacketPtr pkt);

    /**
     * For timing and functional access
     *
     * @return true once the data has been "stored"
     */
    bool accessCPUFunctional(gem5::PacketPtr pkt);
    bool accessUDFunctional(gem5::PacketPtr pkt);

    /**
     * Write the element into the scratchpad memory to be loaded into spark
     *
     * @param packet with the data (and address) to write into memory
     */
    void write(gem5::PacketPtr pkt);
    void writeUD(gem5::PacketPtr pkt);

    /**
     * Read the element from the scratchpad memory
     *
     * @param packet with the data (and address) to read from sp memory
     */
    void read(gem5::PacketPtr pkt);

    /**
     * Return the address ranges this scratchpad is responsible for.
     *
     * @return the address ranges this scratchpad is responsible for
     */
    gem5::AddrRangeList getAddrRanges() const;
    //gem5::AddrRangeList getCtrlAddrRanges() const;

    /**
     * Tell the CPU side to ask for our memory ranges.
     */
    void sendRangeChange() const;
    //void sendCtrlRangeChange() const;

    
    //void send_msg(struct sendmsg* sm);
    void send_msg(struct sendmsg_intf* sm);
    /**
     * Send Message stored in sm to memory 
     *
     * @param sm with address and size of data to be read/written
     */

    void execute(struct exec_param *ep);
    /**
    * Execute on the received packet
    *
    * @param pkt
    */
    uint64_t getEventQueueAddr(uint32_t nwid, uint64_t ctrlbase, int ctrlsize){
        uint64_t node_id = (nwid >> 11) & 0xffff;
        uint64_t cl_id = (nwid >> 8) & 0x7;
        uint64_t ud_id = (nwid >> 6) & 0x3;
        uint64_t lane_id = nwid & 0x3f;
        uint64_t return_addr = ctrlbase + ctrlsize * (node_id * numstacks * numuds * numlanes  +  cl_id * numuds * numlanes + ud_id * numlanes + lane_id);
        return return_addr;
    }

    /// Memory address range
    void init() override;
    gem5::AddrRangeList upAddrRange;
    gem5::AddrRangeList upCtrlAddrRange;
    gem5::Addr upCtrlAddrBase;
    //std::vector<gem5::AddrRange> upCtrlAddrRange;
    //gem5::AddrRangeList upCtrlAddrRange;
    //std::map<uint32_t, gem5::AddrRange> upCtrlMap;
    gem5::AddrRangeList evRange;
    gem5::AddrRangeList obRange;
    gem5::AddrRange sRange;
    gem5::AddrRange sbRange;
    gem5::AddrRange resRange;
    gem5::AddrRangeList statRange;
    gem5::AddrRangeList execRange;

    /// Instantiation of the CPU-side port
    std::vector<CPUSidePort> cpuPorts;
    std::vector<MemSidePort> memPorts;
    //std::vector<UDSideInPort> udInPorts;
    std::vector<UDSideOutPort> udOutPorts;

    /// True if this memory is currently blocked waiting for a reponse.
    bool blocked_cpu;
    bool blocked_ud;
    bool blocked_mem;
    int num_mc;
    int num_ud_channels;
    int numuds;
    int numstacks;
    int numnodes;
    int num_outstanding_cpu;

    /// Packet that we are currently handling.
    gem5::PacketPtr originalPacket;
    std::string progfile;
    std::string progname;
    std::string simdir;
    int lm_mode;
    uint32_t lmsize;
    bool recode_endianness;

    /// The port to send the response when we recieve it back
    int waitingPortId;

    /// An incredibly simple storage mapping address to data
    //std::map<gem5::Addr, uint32_t> statStore;
    int statStore[UD_NUM_LANES];

    std::map<gem5::Addr, struct sendmsg> memory_reqs[UD_NUM_LANES];
    uint64_t prev_yield_cycles[UD_NUM_LANES];
    uint64_t prev_yield_term_cycles[UD_NUM_LANES];
    uint64_t least_poss_exec_cycle[UD_NUM_LANES];
    uint64_t num_outstanding_exec_events[UD_NUM_LANES];
    std::map<uint64_t, struct sendmsg_intf *> mem_reqs;
    std::map<uint64_t, struct super_trans *> super_trans_map;
    std::map<uint64_t, struct sendmsg_intf *> ud_reqs;
    std::queue<gem5::PacketPtr>pending_response[UD_NUM_LANES];
    std::queue<struct event_operand*> pending_events[UD_NUM_LANES];

    int execstate = 0;
    gem5::PacketPtr execpkt;
    uint32_t lmbase = 0;
    uint32_t avg_interlane_delay;

    Upstream_PyIntf *upstream_pyintf;
    uint32_t* sendmap; //make this parametric? 
    uint64_t execstart[UD_NUM_LANES]; // parameterize ? 
    uint64_t execstop[UD_NUM_LANES]; // parameterize ?
    uint32_t active_thrds[UD_NUM_LANES]; // parameterize ?
    uint32_t kernel_exec_time;
    uint64_t global_sm_trans_id=0;
    uint64_t global_super_sm_trans_id=0;
    gem5::Tick* eventtime; //make it parametric
    struct event_operand* top_event[UD_NUM_LANES];
    struct SimStats em_stats[UD_NUM_LANES];
    UDTranslations udtrans_table;

    public:
    struct UpDownStats : public gem5::statistics::Group
    {
      //UpDownStats(UpDownObj &u);

      void regStats() override;

      const UpDownObj &upobj;

      gem5::statistics::Vector numEvents;
      /** The number of events per UpDown Accelerator */
      gem5::statistics::Vector numActions;
      /** The number of Actions per UpDown Accelerator */
      gem5::statistics::Vector numTransitions;
      /** The number of Transitions per UpDown Accelerator */
      gem5::statistics::Vector numInstructions;
      /** The number of Instructions per UpDown Accelerator */
      
      gem5::statistics::Scalar upDramReadBytes;
      /** The number of DRAM Read bytes by UpDown Accelerator */
      
      gem5::statistics::Scalar upDramWriteBytes;
      /** The number of DRAM Write bytes by UpDown Accelerator */
      
      gem5::statistics::Vector upLmReadBytes;
      /** The number of LM Read bytes by UpDown Accelerator */
      
      gem5::statistics::Vector upLmWriteBytes;
      /** The number of LM Write bytes by UpDown Accelerator */
      
      gem5::statistics::Scalar topLmWriteBytes;
      /** The number of Write bytes from TOP to LM */
      
      gem5::statistics::Scalar topLmReadBytes;
      /** The number of Read bytes from TOP to LM */
      
      gem5::statistics::Vector numThreads;
      /** The number of threads per UpDown Lane */
      gem5::statistics::Vector numVertices;
      /** The number of Vertices per UpDown Lane */

      gem5::statistics::Vector numEdges;
      /** The number of Edges per UpDown Lane */
      gem5::statistics::Vector MessageInstructions;
      /** The number of Message Instructions per UpDown Lane */
      gem5::statistics::Vector MovInstructions;
      /** The number of Move Instructions UpDown Lane */
      gem5::statistics::Vector BranchInstructions;
      /** The number of Branch Instructions UpDown Lane */
      gem5::statistics::Vector ALUInstructions;
      /** The number of ALU Instructions UpDown Lane */
      gem5::statistics::Vector YieldInstructions;
      /** The number of Yield Instructions UpDown Lane */
      gem5::statistics::Vector CompareInstructions;
      /** The number of Compare Instructions UpDown Lane */
      gem5::statistics::Vector AtomicInstructions;
      /** The number of Atomic Instructions UpDown Lane */

      
      gem5::statistics::Formula avgThreadExecCycles;
      /** Average Thread Execution time */

      gem5::statistics::Vector upLaneBusyCycles;
      /** The number of Cycles per lane */
      
      gem5::statistics::Vector upLaneIdleCycles_old;
      /** The number of Cycles per lane */
      gem5::statistics::Vector upLaneExecCycles;
      /** The number of Cycles per lane */
      gem5::statistics::Vector upLaneStallCycles;
      /** The number of Cycles per lane */
      gem5::statistics::Vector upLaneIdleCycles;
      /** The number of Cycles per lane */

      gem5::statistics::Vector upLaneEventQMax;
      gem5::statistics::Vector upLaneEventQMean;
      gem5::statistics::Vector upLaneOperandQMax;
      gem5::statistics::Vector upLaneOperandQMean;
      
      
      gem5::statistics::Scalar numPollLoads;
      /** The number of UpDown Accelerator Cycles  */
      
      gem5::statistics::Scalar numSends_DmLm;
      /** The number of UpDown Accelerator Cycles  */
      
      gem5::statistics::Scalar numSends_InterLane;
      /** The number of UpDown Accelerator Cycles  */
      
      gem5::statistics::Scalar TotalLat_SendsDmLm;
      /** The number of UpDown Accelerator Cycles  */
      
      gem5::statistics::Scalar TotalLat_SendsInterLane;
      /** The number of UpDown Accelerator Cycles  */
      
      gem5::statistics::Scalar InterUDMessageLatency;
      /** The number of UpDown Accelerator Cycles  */
      
      gem5::statistics::Scalar num_InterUDMessages;
      /** The number of UpDown Accelerator Cycles  */
      
      gem5::statistics::Scalar bytesSent_InterUDMessages;
      /** The number of UpDown Accelerator Cycles  */
      
      gem5::statistics::Scalar bytesReceived_InterUDMessages;
      /** The number of UpDown Accelerator Cycles  */
      
      gem5::statistics::Formula avgDmLmSendLatency;
      /** Average Latency for send instructions to Global Memory */
      
      gem5::statistics::Formula avgInterLaneSendLatency;
      /** Average Latency for send instructions between lanes */
      
      gem5::statistics::Histogram cyclesPerEvent;
      /** The number of updownCycles per Event*/
      
      gem5::statistics::Scalar eventProcCycles;
      /** The number of updownCycles per Thread*/
      
      gem5::statistics::Scalar opProcCycles;
      /** The number of updownCycles per Thread*/

      gem5::statistics::Vector updownPerLaneUserCtr0;
      gem5::statistics::Vector updownPerLaneUserCtr1;
      gem5::statistics::Vector updownPerLaneUserCtr2;
      gem5::statistics::Vector updownPerLaneUserCtr3;
      gem5::statistics::Vector updownPerLaneUserCtr4;
      gem5::statistics::Vector updownPerLaneUserCtr5;
      gem5::statistics::Vector updownPerLaneUserCtr6;
      gem5::statistics::Vector updownPerLaneUserCtr7;
      gem5::statistics::Vector updownPerLaneUserCtr8;
      gem5::statistics::Vector updownPerLaneUserCtr9;
      gem5::statistics::Vector updownPerLaneUserCtr10;
      gem5::statistics::Vector updownPerLaneUserCtr11;
      gem5::statistics::Vector updownPerLaneUserCtr12;
      gem5::statistics::Vector updownPerLaneUserCtr13;
      gem5::statistics::Vector updownPerLaneUserCtr14;
      gem5::statistics::Vector updownPerLaneUserCtr15;

      UpDownStats(UpDownObj &u)
        : gem5::statistics::Group(&u), upobj(u),
          ADD_STAT(numEvents, gem5::statistics::units::Count::get(),
                  ("number of   numEvents")),
          ADD_STAT(numActions, gem5::statistics::units::Count::get(),
                  ("number of  numActions per lane")),
          ADD_STAT(numTransitions, gem5::statistics::units::Count::get(),
                  ("number of  numTransitions per lane")),
          ADD_STAT(numInstructions, gem5::statistics::units::Count::get(),
                  ("number of  numInstructions per lane")),
          ADD_STAT(upDramReadBytes, gem5::statistics::units::Byte::get(),
                  ("number of  upDRAMReadBytes")),
          ADD_STAT(upDramWriteBytes, gem5::statistics::units::Byte::get(),
                  ("number of  upDRAMWriteBytes")),
          ADD_STAT(upLmReadBytes, gem5::statistics::units::Byte::get(),
                  ("number of  upLMReadBytes")),
          ADD_STAT(upLmWriteBytes, gem5::statistics::units::Byte::get(),
                  ("number of  upLMWriteBytes")),
          ADD_STAT(topLmReadBytes, gem5::statistics::units::Byte::get(),
                  ("number of  topLMReadBytes")),
          ADD_STAT(topLmWriteBytes, gem5::statistics::units::Byte::get(),
                  ("number of  topLMWriteBytes")),
          ADD_STAT(numThreads, gem5::statistics::units::Count::get(),
                  ("number of  numThreads")),
          ADD_STAT(MessageInstructions, gem5::statistics::units::Count::get(),
                  ("number of  MessageInstructions per lane")),
          ADD_STAT(MovInstructions, gem5::statistics::units::Count::get(),
                  ("number of  MoveInstructions per lane")),
          ADD_STAT(BranchInstructions, gem5::statistics::units::Count::get(),
                  ("number of  BranchInstructions per lane")),
          ADD_STAT(ALUInstructions, gem5::statistics::units::Count::get(),
                  ("number of  ALUInstructions per lane")),
          ADD_STAT(CompareInstructions, gem5::statistics::units::Count::get(),
                  ("number of  CompareInstructions per lane")),
          ADD_STAT(YieldInstructions, gem5::statistics::units::Count::get(),
                  ("number of  YieldInstructions per lane")),
          ADD_STAT(AtomicInstructions, gem5::statistics::units::Count::get(),
                  ("number of  AtomicInstructions per lane")),
          ADD_STAT(numVertices, gem5::statistics::units::Count::get(),
                  ("number of  numVertices/VertexPairs per lane")),
          ADD_STAT(numEdges, gem5::statistics::units::Count::get(),
                  ("number of  numEdges Processed per lane")),
          ADD_STAT(upLaneBusyCycles, gem5::statistics::units::Cycle::get(),
                  ("number of  upLaneBusyCycles")),
          ADD_STAT(upLaneIdleCycles_old, gem5::statistics::units::Cycle::get(),
                  ("number of  upLaneIdleCycles (old definition)")),
          ADD_STAT(upLaneExecCycles, gem5::statistics::units::Cycle::get(),
                  ("number of  upLane Instruction Execution Cycles")),
          ADD_STAT(upLaneStallCycles, gem5::statistics::units::Cycle::get(),
                  ("number of  upLaneStallCycles (waiting for memory returns no active thread)")),
          ADD_STAT(upLaneIdleCycles, gem5::statistics::units::Cycle::get(),
                  ("number of  upLaneIdleCycles (No active threads launched on lane)")),
          ADD_STAT(avgThreadExecCycles, gem5::statistics::units::Cycle::get(),
                  ("Average  ThreadExecCycles")),
          ADD_STAT(TotalLat_SendsDmLm, gem5::statistics::units::Tick::get(),
                  ("Total  SendsDmLmLatency")),
          ADD_STAT(TotalLat_SendsInterLane, gem5::statistics::units::Tick::get(),
                  ("Total  SendsInterLaneLatency")),
          ADD_STAT(numSends_DmLm, gem5::statistics::units::Count::get(),
                  ("Total  numSends_DmLm")),
          ADD_STAT(num_InterUDMessages , gem5::statistics::units::Count::get(),
                  ("Total  InterUDMessages received")),
          ADD_STAT(bytesReceived_InterUDMessages , gem5::statistics::units::Count::get(),
                  ("Total  InterUDMessages received")),
          ADD_STAT(bytesSent_InterUDMessages , gem5::statistics::units::Count::get(),
                  ("Total  InterUDMessages received")),
          ADD_STAT(InterUDMessageLatency , gem5::statistics::units::Count::get(),
                  ("Total  Total InterUDMessage Latency")),
          ADD_STAT(numSends_InterLane, gem5::statistics::units::Count::get(),
                  ("Total  numSends_InterLane")),
          ADD_STAT(numPollLoads, gem5::statistics::units::Count::get(),
                  ("Poll Load Instructions")),
          ADD_STAT(cyclesPerEvent, gem5::statistics::units::Cycle::get(),
                  ("number of  cyclesPerEvent")),
          ADD_STAT(avgDmLmSendLatency, gem5::statistics::units::Tick::get(),
                  ("Average  SendDmLmLatencyCycles")),
          ADD_STAT(avgInterLaneSendLatency, gem5::statistics::units::Tick::get(),
                  ("Average  InterLaneSendLatencyCycles")),
          ADD_STAT(upLaneEventQMax, gem5::statistics::units::Count::get(),
                   ("Max event queue length per lane")),
          ADD_STAT(upLaneEventQMean, gem5::statistics::units::Count::get(),
                   ("Mean event queue length per lane")),
          ADD_STAT(upLaneOperandQMax, gem5::statistics::units::Count::get(),
                   ("Max operand queue length per lane")),
          ADD_STAT(upLaneOperandQMean, gem5::statistics::units::Count::get(),
                   ("Mean operand queue length per lane")),
          ADD_STAT(updownPerLaneUserCtr0, gem5::statistics::units::Count::get(),
                   ("UpDown user counter 0")),
          ADD_STAT(updownPerLaneUserCtr1, gem5::statistics::units::Count::get(),
                   ("UpDown user counter 1")),
          ADD_STAT(updownPerLaneUserCtr2, gem5::statistics::units::Count::get(),
                   ("UpDown user counter 2")),
          ADD_STAT(updownPerLaneUserCtr3, gem5::statistics::units::Count::get(),
                   ("UpDown user counter 3")),
          ADD_STAT(updownPerLaneUserCtr4, gem5::statistics::units::Count::get(),
                   ("UpDown user counter 4")),
          ADD_STAT(updownPerLaneUserCtr5, gem5::statistics::units::Count::get(),
                   ("UpDown user counter 5")),
          ADD_STAT(updownPerLaneUserCtr6, gem5::statistics::units::Count::get(),
                   ("UpDown user counter 6")),
          ADD_STAT(updownPerLaneUserCtr7, gem5::statistics::units::Count::get(),
                   ("UpDown user counter 7")),
          ADD_STAT(updownPerLaneUserCtr8, gem5::statistics::units::Count::get(),
                   ("UpDown user counter 8")),
          ADD_STAT(updownPerLaneUserCtr9, gem5::statistics::units::Count::get(),
                   ("UpDown user counter 9")),
          ADD_STAT(updownPerLaneUserCtr10, gem5::statistics::units::Count::get(),
                   ("UpDown user counter 10")),
          ADD_STAT(updownPerLaneUserCtr11, gem5::statistics::units::Count::get(),
                   ("UpDown user counter 11")),
          ADD_STAT(updownPerLaneUserCtr12, gem5::statistics::units::Count::get(),
                   ("UpDown user counter 12")),
          ADD_STAT(updownPerLaneUserCtr13, gem5::statistics::units::Count::get(),
                   ("UpDown user counter 13")),
          ADD_STAT(updownPerLaneUserCtr14, gem5::statistics::units::Count::get(),
                   ("UpDown user counter 14")),
          ADD_STAT(updownPerLaneUserCtr15, gem5::statistics::units::Count::get(),
                   ("UpDown user counter 15"))
        {
        }

    } upstats; 

  public:
    UpDownObj(const gem5::UpDownObjParams &p);

    /// Latency to store memory
    const gem5::Cycles latency;

    /// Latency to store memory
    const unsigned wordSize;
    const unsigned numlanes;
    const unsigned period;

    /// Size of scratchpad memory
    const unsigned capacity;
    const uint64_t scratchsize;
    const unsigned dblksize;


     /**
     * Get a port with a given name and index. This is used at
     * binding time and returns a reference to a protocol-agnostic
     * port.
     *
     * @param if_name Port name
     * @param idx Index in the case of a VectorPort
     *
     * @return A reference to the given port
     */
    gem5::Port &getPort(const std::string &if_name,
                  gem5::PortID idx=gem5::InvalidPortID) override;

    ~UpDownObj() {
      // delete upstream_pyintf;
    }
};

#endif // __UPDOWN_OBJECT_HH__

