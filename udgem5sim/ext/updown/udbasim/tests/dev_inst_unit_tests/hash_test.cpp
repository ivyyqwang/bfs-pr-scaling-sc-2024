#include "archstate.hh"
#include "bitwise_inst.hh"
#include "encodings.hh"
#include "eventq.hh"
#include "hash_inst.hh"
#include "inst_decode.hh"
#include "instructionmemory.hh"
#include "lanetypes.hh"
#include "opbuffer.hh"
#include "scratchpadbank.hh"
#include "threadstate.hh"
#include "tstable.hh"
#include "types.hh"
#include "udlane.hh"
#include <gtest/gtest.h>
#include <random>

using namespace basim;

class Hash : public ::testing::Test {
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

TEST_F(Hash, Zero) {
  ThreadStatePtr thread0;
  uint8_t tid0 = tstable->getTID();
  thread0 = new ThreadState(tid0, 0, 0, 0);
  tstable->addtoTST(thread0);
  archstate->threadstate = thread0;

  int64_t v1 = 0;
  int64_t v2 = 0;

  inst = constrInstHash(RegId::X16, RegId::X17);
  thread0->writeReg(RegId::X16, v1);
  thread0->writeReg(RegId::X17, v2);
  Cycles cycle = decodeInst(inst).exe(*archstate, inst);

  EXPECT_EQ(static_cast<int64_t>(thread0->readReg(RegId::X16)), v1);
  EXPECT_EQ(static_cast<int64_t>(thread0->readReg(RegId::X17)), 0xB66A73654282CAC0ull);
  EXPECT_EQ(cycle, basim::Cycles(1));
}

TEST_F(Hash, One) {
  ThreadStatePtr thread0;
  uint8_t tid0 = tstable->getTID();
  thread0 = new ThreadState(tid0, 0, 0, 0);
  tstable->addtoTST(thread0);
  archstate->threadstate = thread0;

  int64_t v1 = 1;
  int64_t v2 = 0;

  inst = constrInstHash(RegId::X16, RegId::X17);
  thread0->writeReg(RegId::X16, v1);
  thread0->writeReg(RegId::X17, v2);
  Cycles cycle = decodeInst(inst).exe(*archstate, inst);

  EXPECT_EQ(static_cast<uint64_t>(thread0->readReg(RegId::X16)), v1);
  EXPECT_EQ(static_cast<uint64_t>(thread0->readReg(RegId::X17)), 0x6CD4E6CA85059580ull);
  EXPECT_EQ(cycle, basim::Cycles(1));
}

TEST_F(Hash, Random0) {
  ThreadStatePtr thread0;
  uint8_t tid0 = tstable->getTID();
  thread0 = new ThreadState(tid0, 0, 0, 0);
  tstable->addtoTST(thread0);
  archstate->threadstate = thread0;

  int64_t v1 = -4972264472110413858;
  int64_t v2 = -5766241645424604240;

  inst = constrInstHash(RegId::X16, RegId::X17);
  thread0->writeReg(RegId::X16, v1);
  thread0->writeReg(RegId::X17, v2);
  Cycles cycle = decodeInst(inst).exe(*archstate, inst);

  EXPECT_EQ(static_cast<uint64_t>(thread0->readReg(RegId::X16)), v1);
  auto output = static_cast<uint64_t>(thread0->readReg(RegId::X17));
  EXPECT_EQ(output, 0x532ba0b5d1c3ca60ull);
  EXPECT_EQ(cycle, basim::Cycles(1));
}