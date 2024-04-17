#include "archstate.hh"
#include "dat_mov_inst.hh"
#include "encodings.hh"
#include "eventq.hh"
#include "inst_decode.hh"
#include "instructionmemory.hh"
#include "lanetypes.hh"
#include "opbuffer.hh"
#include "scratchpadbank.hh"
#include "threadstate.hh"
#include "tstable.hh"
#include "types.hh"
#include "udlane.hh"
#include <cstdint>
#include <gtest/gtest.h>
#include <random>

using namespace basim;

class Vfill_i32 : public ::testing::Test {
protected:
  // Setup arch state
  // push data
  // execute instructions
  // Check

  /* Setup arch state for execution */
  void SetUp() override {
    // Add two threads to the thread state table
    // add these to the constructor
    uint32_t nwid = 0;
    instmem = new InstructionMemory(0);
    opbuff = new OpBuffer<operands_t>();
    eventq = new EventQ<eventword_t>();
    spd = new ScratchPad(1);
    tstable = new TSTable();
    lanestate = LaneState::NULLSTATE;

    // Add elements to a combined archstate for convenience in instruction execution
    archstate = new ArchState();
    archstate->instmem = instmem;
    archstate->opbuff = opbuff;
    archstate->eventq = eventq;
    archstate->spd = spd;
    archstate->uip = uip;
    archstate->lanestate = &lanestate;
    archstate->lanestats = new LaneStats();
    //
    cyclesRemaining = basim::Cycles(0);
    instCycles = basim::Cycles(0);
  }

  InstructionMemoryPtr instmem;
  OpBufferPtr opbuff;
  EventQPtr eventq;
  ScratchPadPtr spd;
  TSTablePtr tstable;
  ArchStatePtr archstate;
  lanestate_t lanestate;
  Addr uip;
  ThreadStatePtr ts;
  basim::Cycles cyclesRemaining;
  basim::Cycles instCycles;

  // Instruction/s under test
  EncInst inst;
};

/* Testing with random value */
TEST_F(Vfill_i32, Random) {
  ThreadStatePtr thread0;
  uint8_t tid0 = tstable->getTID();
  thread0 = new ThreadState(tid0, 0, 0, 0);
  tstable->addtoTST(thread0);
  archstate->threadstate = thread0;

  std::mt19937_64 rnd(std::random_device{}());
  uint64_t v1 = rnd();
  uint64_t v2 = rnd() >> 48;

  inst = constrInstVfill(7, v2 & 0x000000000000000F, RegId::X16, (v2 & 0x000000000000FFF0) >> 4);
  thread0->writeReg(RegId::X16, v1);
  if (v2 & 0x0000000000008000) {
    v2 |= 0x00000000FFFF0000;
  }
  Cycles cycle = decodeInst(inst).exe(*archstate, inst);
  // std::cout << "Cycles:" << cycle << std::endl;
  EXPECT_EQ(thread0->readReg(RegId::X16), (v2 << 32) | (v2));
  // Expect to be empty.
}

/* Testing with max value */
TEST_F(Vfill_i32, Max) {
  ThreadStatePtr thread0;
  uint8_t tid0 = tstable->getTID();
  thread0 = new ThreadState(tid0, 0, 0, 0);
  tstable->addtoTST(thread0);
  archstate->threadstate = thread0;

  std::mt19937_64 rnd(std::random_device{}());
  uint64_t v1 = rnd();
  uint64_t v2 = 0x000000000000FFFF;

  inst = constrInstVfill(7, v2 & 0x000000000000000F, RegId::X16, (v2 & 0x000000000000FFF0) >> 4);
  thread0->writeReg(RegId::X16, v1);

  Cycles cycle = decodeInst(inst).exe(*archstate, inst);
  // std::cout << "Cycles:" << cycle << std::endl;
  EXPECT_EQ(thread0->readReg(RegId::X16), 0xFFFFFFFFFFFFFFFF);
  // Expect to be empty.
}

/* Testing with empty value */
TEST_F(Vfill_i32, Empty) {
  ThreadStatePtr thread0;
  uint8_t tid0 = tstable->getTID();
  thread0 = new ThreadState(tid0, 0, 0, 0);
  tstable->addtoTST(thread0);
  archstate->threadstate = thread0;

  std::mt19937_64 rnd(std::random_device{}());
  uint64_t v1 = rnd();
  uint64_t v2 = 0x0000000000000000;

  inst = constrInstVfill(7, v2 & 0x000000000000000F, RegId::X16, (v2 & 0x000000000000FFF0) >> 4);
  thread0->writeReg(RegId::X16, v1);

  Cycles cycle = decodeInst(inst).exe(*archstate, inst);
  // std::cout << "Cycles:" << cycle << std::endl;
  EXPECT_EQ(thread0->readReg(RegId::X16), 0x0000000000000000);
  // Expect to be empty.
}
