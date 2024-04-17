#include "archstate.hh"
#include "bitwise_inst.hh"
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
#include <gtest/gtest.h>
#include <random>

using namespace basim;

class Swiz : public ::testing::Test {
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

/* zero - one - zero - one */
TEST_F(Swiz, zozo) {
  ThreadStatePtr thread0;
  uint8_t tid0 = tstable->getTID();
  thread0 = new ThreadState(tid0, 0, 0, 0);
  tstable->addtoTST(thread0);
  archstate->threadstate = thread0;

  std::mt19937_64 rnd(std::random_device{}());
  uint64_t msk = 0b00000000'00000000'00000000'00000000'00000000'00111111'11000000'11111111ull;
  uint64_t dat = 0b00000000'00000000'00000000'00000000'00000000'00111111'11000000'11111111ull;
  uint64_t out_dat = 0b00000000'00000000'00000000'00000000'00000000'00000000'11111111'11111111ull;

  inst = constrInstSwiz(RegId::X16, RegId::X17);
  thread0->writeReg(RegId::X16, msk);
  thread0->writeReg(RegId::X17, dat);
  Cycles cycle = decodeInst(inst).exe(*archstate, inst);
  EXPECT_EQ(thread0->readReg(RegId::X16), msk);
  EXPECT_EQ(thread0->readReg(RegId::X17), out_dat);
}

/* one - zero - one - zero */
TEST_F(Swiz, ozoz) {
  ThreadStatePtr thread0;
  uint8_t tid0 = tstable->getTID();
  thread0 = new ThreadState(tid0, 0, 0, 0);
  tstable->addtoTST(thread0);
  archstate->threadstate = thread0;

  std::mt19937_64 rnd(std::random_device{}());
  uint64_t msk = 0b11111111'11111111'11111111'11111111'11111111'11000000'00111111'00000000ull;
  uint64_t dat = 0b11111111'11111111'11111111'11111111'11111111'11000000'00111111'00000000ull;
  uint64_t out_dat = 0b00000000'11111111'11111111'11111111'11111111'11111111'11000000'00111111ull;

  inst = constrInstSwiz(RegId::X16, RegId::X17);
  thread0->writeReg(RegId::X16, msk);
  thread0->writeReg(RegId::X17, dat);
  Cycles cycle = decodeInst(inst).exe(*archstate, inst);
  EXPECT_EQ(thread0->readReg(RegId::X16), msk);
  EXPECT_EQ(thread0->readReg(RegId::X17), out_dat);
}
