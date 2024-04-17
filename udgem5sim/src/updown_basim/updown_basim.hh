#ifndef __UPDOWN_BASIM_HH__
#define __UPDOWN_BASIM_HH__

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

#include "updown_obj/updown_obj.hh"
#include "debug/UpDownBASim.hh"
#include "base/statistics.hh"
#include "mem/port.hh"
#include "params/UpDownBASim.hh"
#include "sim/clocked_object.hh" // subclass of sim_object
#include "udaccelerator.hh"
#include "updown/runtime/include/updown_config.h"
#include "updown/basimruntime/include/basim_stats.hh" // Should be BASim Stats
#include "updown/udbasim/common/include/util.hh"
#include "updown/udbasim/common/include/types.hh"
#include "updown/udbasim/common/include/lanetypes.hh"
#include "updown/udbasim/common/include/mmessage.hh"
#include "updown/udbasim/common/include/stats.hh"
#include "updown/common/include/memorySegments.h"
#define UD_NUM_LANES DEF_NUM_LANES
#define UD_NUM_STACKS DEF_NUM_STACKS
#define UD_NUM_NODES DEF_NUM_NODES





struct sendmsg_basim{
  uint64_t sm_trans_id;
  uint64_t sdest; // Dest Addr / Lane Num
  uint64_t sdest_VA; // Dest Addr / Lane Num
  bool partial=false;
  int num_partials=0;
  int num_recvd=0;
  int bytes_recvd=0;
  uint8_t* partial_data;
  uint8_t* sdata;
  basim::MMessagePtr msg;
  int ssize;
};

typedef struct sendmsg_basim sendmsg_t;
typedef struct sendmsg_basim* sendmsg_tptr;




class UpDownBASim : public gem5::ClockedObject
{
  private:

  uint32_t updown_system_id;
  uint32_t nwid;

  //class MemoryMsg{
  //  private:
  //    uint64_t sm_trans_id;
  //    uint64_t sdest; 
  //    uint64_t sdest_VA;
  //    bool partial; 
  //    int num_partials;
  //    int num_recvd;
  //    int bytes_recvd;
  //    uint8_t* partial_data; 
  //    uint8_t *sdata;
  //    basim::MMessagePtr msg; 
  //    int ssize;
  
  //  public:
  //    MemoryMsg(): sm_trans_id(0), 
  //      partial(false), 
  //      num_partials(0), 
  //      num_recvd(0),
  //      bytes_recvd(0),
  //      partial_data(nullptr),
  //      sdata(nullptr),
  //      msg(nullptr),
  //      ssize(0){};

  //    MemoryMsg(uint64_t id, int size): sm_trans_id(id),
  //      partial(false), 
  //      num_partials(0), 
  //      num_recvd(0),
  //      bytes_recvd(0),
  //      partial_data(nullptr),
  //      sdata(nullptr),
  //      msg(nullptr),
  //      ssize(size){
  //        partial_data = new uint8_t[size];
  //        sdata = new uint8_t[size];
  //      };
  //    
  //    void setPartial(bool _partial){partial = _partial;}
  //    void setNumRecvd(int numrecvd){num_recvd = numrecvd;}
  //    void setBytesRecvd(int bytesrecvd){bytes_recvd = bytesrecvd;}
  //    void setPartialData(int index, int size, uint8_t dataptr){
  //      for(int i = index; i < size; i++)
  //        partial_data[i] = dataptr[i];
  //    }
  //    void setSData(int index, int size, uint8_t dataptr){
  //      for(int i = index; i < size; i++)
  //        sdata[i] = dataptr[i];
  //    }
  //    uint8_t* getPartialData(){
  //      return partial_data;
  //    }
  //    uint8_t* getSData(){
  //      return sdata;
  //    }
  //    void setMsg(basim::MMessagePtr _msg){
  //      msg = _msg;
  //    }
  //    basim::MessagePtr getMsg(){ return msg; }


  //};  


    /**
     * Port on the CPU-side that receives requests.
     */
    class CPUSidePort : public gem5::ResponsePort
    {
      private:
        // Since this is a vector port, need to know what number this one is
        int id;

        UpDownBASim *owner;

        /// True if the port needs to send a retry req.
        bool needRetry;

        /// If we tried to send a packet and it was blocked, store it here
        gem5::PacketPtr blockedPacket;
        std::vector<gem5::PacketPtr> blockedPacket_vec;

      public:
        /**
         * Constructor. Just calls the superclass constructor.
         */
        CPUSidePort(const std::string& name, int id, UpDownBASim *owner) :
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
        UpDownBASim *owner;
        int id;

        /// If we tried to send a packet and it was blocked, store it here
        gem5::PacketPtr blockedPacket;
        std::vector<gem5::PacketPtr> blockedPacket_vec;
        bool retrystate;

      public:
        /**
         * Constructor. Just calls the superclass constructor.
         */
        MemSidePort(const std::string& name, int id,UpDownBASim *owner) :
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

     /* 
     * Outgoing Requests to other UpDowns 
     */   
    class UDSideOutPort : public gem5::RequestPort
    {
      private:
        UpDownBASim *owner;
        int id;

        /// If we tried to send a packet and it was blocked, store it here
        gem5::PacketPtr blockedPacket;
        std::vector<gem5::PacketPtr> blockedPacket_vec;
        bool retrystate;

      public:
        /**
         * Constructor. Just calls the superclass constructor.
         */
        UDSideOutPort(const std::string& name, int id, UpDownBASim *owner) :
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

    /**
     * Similar to CPU side but for UD requests 
    */
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

    /**
     * Send Message stored in sm to memory 
     *
     * @param sm with address and size of data to be read/written
     */
    //void send_msg(struct sendmsg_intf* sm);

    /**
     * @brief post tick functions
     * 
     * @param lane_num on which to execute  
     */
    void postTick(int* lane_num);

    /**
    * Execute on the received packet
    *
    * @param pkt
    */
    void execute(const int *lane_num);

    /**
     * InterLane Messaging 
    */
    //void interlaneMessage(basim::eventoperands_t* eops, const int* dest_lane_num);
    basim::networkid_t UpDownBASim::getDestForAddr(basim::networkid_t netid, gem5::Addr pol_addr);

    /**
     * Calculate th global eventQueue address from nwid
    */
    uint64_t getEventQueueAddr(uint32_t nwid, uint64_t ctrlbase, int ctrlsize){
        uint64_t node_id = (nwid >> 11) & 0xffff;
        uint64_t cl_id = (nwid >> 8) & 0x7;
        uint64_t ud_id = (nwid >> 6) & 0x3;
        uint64_t lane_id = nwid & 0x3f;
        uint64_t return_addr = ctrlbase + ctrlsize * (node_id * numstacks * numuds * numlanes  +  cl_id * numuds * numlanes + ud_id * numlanes + lane_id);
        return return_addr;
    }

    // Memory address range
    void init() override;
    // Ctrl Address base
    gem5::Addr upCtrlAddrBase;

    // Scratchpad Range
    gem5::AddrRange sRange;

    // ScratchPad Address range?
    gem5::AddrRangeList upAddrRange;

    // Ctrl Address range
    gem5::AddrRangeList upCtrlAddrRange;

    // Event Queue Range
    gem5::AddrRangeList evRange;

    // Operand Buffer Range
    gem5::AddrRangeList obRange;

    // Lock Range 
    gem5::AddrRangeList statRange;

    // Execute Range
    gem5::AddrRangeList execRange;

    // Instantiation of the CPU-side port
    std::vector<CPUSidePort> cpuPorts;

    // Instantiation of the Mem-side port
    std::vector<MemSidePort> memPorts;

    // Instantiation of the UD out Ports
    std::vector<UDSideOutPort> udOutPorts;

    // True if this memory is currently blocked waiting for a reponse.
    bool blocked_cpu;
    bool blocked_ud;
    bool blocked_mem;
    bool exec_stat[DEF_NUM_LANES];

    // Number of Memory channels
    int num_mc;

    // Number of UD channels - is this still relevant?
    int num_ud_channels;

    // Number of UDS??
    int numuds;

    // Number of stacks??
    int numstacks;
    
    // Number of Nodes ?? why?
    int numnodes;

    // Number of outstanding CPU requests
    int num_outstanding_cpu;

    // Program File (UpDown) / .bin file
    std::string progfile;
    
    // Program Name (EFA function)
    std::string progname;

    // Simulation Directory
    std::string simdir;

    // LM Mode
    int lm_mode;

    // LM ScratchPad size
    uint32_t lmsize;

    /// The port to send the response when we recieve it back
    int waitingPortId;

    // An incredibly simple storage mapping address to data
    int statStore[UD_NUM_LANES];


    // Transaction ID map for outstanding memory requests
    std::map<uint64_t, sendmsg_tptr> mem_reqs;
    
    // Transaction ID map for outgoing UD messages (for gem5 acks)
    std::map<uint64_t, sendmsg_tptr> ud_reqs;


    uint64_t least_poss_exec_cycle[UD_NUM_LANES];
    uint64_t num_outstanding_exec_events[UD_NUM_LANES];

    // Pending Responses to be processed 
    std::queue<gem5::PacketPtr>pending_response[UD_NUM_LANES];

    // Scratchpad Base
    uint32_t lmbase = 0;

    /** BASIM related datastructures */

    // UpDown BASim Component 
    basim::UDAcceleratorPtr udaccel;

    // BASim specific ones
    // Event Operand from CPU (one outstanding per CPU)
    basim::eventoperands_t cpu_evops[UD_NUM_LANES];


    // Eventword from CPU (one outstanding per CPU)
    basim::eventwordptr_t cpu_ev[UD_NUM_LANES];
    
    // Operands collected from CPU (one outstanding per CPU)
    basim::operandsptr_t cpu_ops[UD_NUM_LANES];

    // Number of operands
    uint64_t cpu_ops_temp[UD_NUM_LANES][8];
    int cur_opnum[UD_NUM_LANES]; // = 0;


    uint64_t global_sm_trans_id=0;
    gem5::Tick* eventtime; //make it parametric
    
    //struct SimStats em_stats[UD_NUM_LANES];
    
    // Tranlsation Table -- needs to go soon
    UDTranslations udtrans_table;

    // Symbol Map for Top Events to be translated
    std::unordered_map<uint32_t, uint32_t> symbolMap;

    public:
    struct UpDownStats : public gem5::statistics::Group
    {
      const basim::LaneStats* lnstats;

      void regStats() override;
      
      void preDumpStats() override;

      const UpDownBASim &upobj;

      gem5::statistics::Vector numEvents;
      /** The number of events per UpDown Accelerator */
      
      /** The number of Actions per UpDown Accelerator */
      gem5::statistics::Vector inst_count;
      
      /** The number of Transitions per UpDown Accelerator */
      gem5::statistics::Vector tran_count;
      
      /** The number of DRAM Read bytes by UpDown Accelerator */
      gem5::statistics::Vector dram_load_bytes;
      
      /** The number of DRAM Write bytes by UpDown Accelerator */
      gem5::statistics::Vector dram_store_bytes;

	  /** The number of DRAM Read bytes by UpDown Accelerator */
      gem5::statistics::Scalar dram_load_bytes_acc;
      
      /** The number of DRAM Write bytes by UpDown Accelerator */
      gem5::statistics::Scalar dram_store_bytes_acc;
      
      /** The number of LM Read bytes by UpDown Accelerator */
      gem5::statistics::Vector lm_load_bytes;
      
      /** The number of LM Write bytes by UpDown Accelerator */
      gem5::statistics::Vector lm_store_bytes;
      
      /** The number of Write bytes from TOP to LM */
      gem5::statistics::Scalar lm_store_bytes_top;
      
      /** The number of Read bytes from TOP to LM */
      gem5::statistics::Scalar lm_load_bytes_top;
      
      /** The number of Message Instructions per UpDown Lane */
      gem5::statistics::Vector inst_count_msg;
      
      /** The number of Move Instructions UpDown Lane */
      gem5::statistics::Vector inst_count_datmov;
      
      /** The number of Branch Instructions UpDown Lane */
      gem5::statistics::Vector inst_count_ctrlflow;

      /** The number of ALU Instructions UpDown Lane */
      gem5::statistics::Vector inst_count_intarith;
      
      /** The number of Yield Instructions UpDown Lane */
      gem5::statistics::Vector inst_count_threadctrl;

      /** The number of Compare Instructions UpDown Lane */
      gem5::statistics::Vector inst_count_intcmp;
      
      /** The number of Atomic Instructions UpDown Lane */
      gem5::statistics::Vector inst_count_atomic;
      
      /** The number of bitwise Instructions UpDown Lane */
      gem5::statistics::Vector inst_count_bitwise;
      
      /** The number of Ev Instructions UpDown Lane */
      gem5::statistics::Vector inst_count_ev;
      
      /** The number of Ev Instructions UpDown Lane */
      gem5::statistics::Vector inst_count_fparith;
      
      /** The number of Ev Instructions UpDown Lane */
      gem5::statistics::Vector inst_count_hash;
      
      /** The number of Ev Instructions UpDown Lane */
      gem5::statistics::Vector inst_count_tranctrl;
      
      /** The number of Ev Instructions UpDown Lane */
      gem5::statistics::Vector inst_count_vec;

		// Transition counts
      gem5::statistics::Vector tran_count_basic;
      gem5::statistics::Vector tran_count_majority;
      gem5::statistics::Vector tran_count_default;
      gem5::statistics::Vector tran_count_epsilon;
      gem5::statistics::Vector tran_count_common;
      gem5::statistics::Vector tran_count_flagged;
      gem5::statistics::Vector tran_count_refill;
      gem5::statistics::Vector tran_count_event;

      
    /** Average Thread Execution time */
    //gem5::statistics::Formula avgThreadExecCycles;

    /** The number of Cycles per lane */
    gem5::statistics::Vector lane_busy_cycles;
    
    /** The number of Cycles per lane */
	gem5::statistics::Vector lane_exec_cycles;
    
    /** The number of Cycles per lane */
	gem5::statistics::Vector lane_stall_cycles;
    
    /** The number of Cycles per lane */
	gem5::statistics::Vector lane_idle_cycles;

    gem5::statistics::Vector eventq_len_max;
    //gem5::statistics::Vector upLaneEventQMean;
    //gem5::statistics::Vector upLaneOperandQMean;
	gem5::statistics::Vector opbuff_len_max;
      
      
    gem5::statistics::Vector dram_load_count;
    gem5::statistics::Vector dram_store_count;
      
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
    
    //gem5::statistics::Formula avgDmLmSendLatency;
    /** Average Latency for send instructions to Global Memory */
    
    //gem5::statistics::Formula avgInterLaneSendLatency;
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

      UpDownStats(UpDownBASim &u)
        : gem5::statistics::Group(&u), upobj(u),
        ADD_STAT(inst_count, gem5::statistics::units::Count::get(),
                ("number of  Instructions per lane")),
        ADD_STAT(tran_count, gem5::statistics::units::Count::get(),
                ("number of  Transitions per lane")),
        ADD_STAT(dram_load_bytes, gem5::statistics::units::Byte::get(),
                ("number of  DRAM Load Bytes")),
        ADD_STAT(dram_store_bytes, gem5::statistics::units::Byte::get(),
                ("number of  upDRAMWriteBytes")),
        ADD_STAT(lm_load_bytes, gem5::statistics::units::Byte::get(),
                ("number of  upLMReadBytes")),
        ADD_STAT(lm_store_bytes, gem5::statistics::units::Byte::get(),
                ("number of  upLMWriteBytes")),
        ADD_STAT(lm_load_bytes_top, gem5::statistics::units::Byte::get(),
                ("number of  topLMReadBytes")),
        ADD_STAT(lm_store_bytes_top, gem5::statistics::units::Byte::get(),
                ("number of  topLMWriteBytes")),
        ADD_STAT(inst_count_msg, gem5::statistics::units::Count::get(),
                ("number of  MessageInstructions per lane")),
        ADD_STAT(inst_count_datmov, gem5::statistics::units::Count::get(),
                ("number of  MoveInstructions per lane")),
        ADD_STAT(inst_count_ctrlflow, gem5::statistics::units::Count::get(),
                ("number of  BranchInstructions per lane")),
        ADD_STAT(inst_count_intarith, gem5::statistics::units::Count::get(),
                ("number of  ALUInstructions per lane")),
        ADD_STAT(inst_count_intcmp, gem5::statistics::units::Count::get(),
                ("number of  CompareInstructions per lane")),
        ADD_STAT(inst_count_threadctrl, gem5::statistics::units::Count::get(),
                ("number of  YieldInstructions per lane")),
        ADD_STAT(inst_count_atomic, gem5::statistics::units::Count::get(),
                ("number of  AtomicInstructions per lane")),
        ADD_STAT(inst_count_bitwise, gem5::statistics::units::Count::get(),
                ("number of  BitwiseInstructions per lane")),
        ADD_STAT(inst_count_fparith, gem5::statistics::units::Count::get(),
                ("number of  FPArithInstructions per lane")),
        ADD_STAT(inst_count_hash, gem5::statistics::units::Count::get(),
                ("number of  HashInstructions per lane")),
        ADD_STAT(inst_count_vec, gem5::statistics::units::Count::get(),
                ("number of  VectorInstructions per lane")),
        ADD_STAT(inst_count_ev, gem5::statistics::units::Count::get(),
                ("number of EvInstructions per lane")),
		ADD_STAT(tran_count_basic, gem5::statistics::units::Count::get(),
				("TransCount Basic")),
		ADD_STAT(tran_count_majority, gem5::statistics::units::Count::get(),
				("TransCount_Majority")),
		ADD_STAT(tran_count_default, gem5::statistics::units::Count::get(),
				("TransCount_Default")),
		ADD_STAT(tran_count_epsilon, gem5::statistics::units::Count::get(),
				("TransCount_Epsilon")),
		ADD_STAT(tran_count_common, gem5::statistics::units::Count::get(),
				("TransCount_Common")),
		ADD_STAT(tran_count_flagged, gem5::statistics::units::Count::get(),
				("TransCount_Flagged")),
		ADD_STAT(tran_count_refill, gem5::statistics::units::Count::get(),
				("TransCount_Refill")),
		ADD_STAT(tran_count_event, gem5::statistics::units::Count::get(),
				("TransCount_Event")),
		ADD_STAT(lane_busy_cycles, gem5::statistics::units::Cycle::get(),
                  ("number of  upLaneBusyCycles")),
        ADD_STAT(lane_exec_cycles, gem5::statistics::units::Cycle::get(),
                  ("number of  upLane Instruction Execution Cycles")),
        ADD_STAT(lane_stall_cycles, gem5::statistics::units::Cycle::get(),
                  ("number of  upLaneStallCycles (waiting for memory returns no active thread)")),
        ADD_STAT(lane_idle_cycles, gem5::statistics::units::Cycle::get(),
                  ("number of  upLaneIdleCycles (No active threads launched on lane)")),
        //ADD_STAT(avgThreadExecCycles, gem5::statistics::units::Cycle::get(),
        //          ("Average  ThreadExecCycles")),
        ADD_STAT(TotalLat_SendsDmLm, gem5::statistics::units::Tick::get(),
                ("Total  SendsDmLmLatency")),
        ADD_STAT(TotalLat_SendsInterLane, gem5::statistics::units::Tick::get(),
                ("Total  SendsInterLaneLatency")),
        ADD_STAT(dram_load_count, gem5::statistics::units::Count::get(),
                ("Total  numSends_DmLm")),
        ADD_STAT(dram_store_count, gem5::statistics::units::Count::get(),
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
        ADD_STAT(cyclesPerEvent, gem5::statistics::units::Cycle::get(),
                ("number of  cyclesPerEvent")),
        //ADD_STAT(avgDmLmSendLatency, gem5::statistics::units::Tick::get(),
        //        ("Average  SendDmLmLatencyCycles")),
        //ADD_STAT(avgInterLaneSendLatency, gem5::statistics::units::Tick::get(),
        //        ("Average  InterLaneSendLatencyCycles")),
        ADD_STAT(eventq_len_max, gem5::statistics::units::Count::get(),
                 ("Max event queue length per lane")),
        //ADD_STAT(upLaneEventQMean, gem5::statistics::units::Count::get(),
        //         ("Mean event queue length per lane")),
        ADD_STAT(opbuff_len_max, gem5::statistics::units::Count::get(),
                 ("Max operand queue length per lane")),
        //ADD_STAT(upLaneOperandQMean, gem5::statistics::units::Count::get(),
        //         ("Mean operand queue length per lane")),
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
    UpDownBASim(const gem5::UpDownBASimParams &p);

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

    ~UpDownBASim() {
      // delete upstream_pyintf;
    }
};

#endif // __UPDOWN_BASIM_HH__

