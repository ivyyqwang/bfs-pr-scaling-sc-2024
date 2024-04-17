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
#include <gtest/gtest.h>
#include <random>

using namespace basim;

class Movil1 : public ::testing::Test {
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
TEST_F(Movil1, Random) {
  ThreadStatePtr thread0;
  uint8_t tid0 = tstable->getTID();
  thread0 = new ThreadState(tid0, 0, 0, 0);
  tstable->addtoTST(thread0);
  archstate->threadstate = thread0;

  std::mt19937_64 rnd(std::random_device{}());
  uint64_t v1 = (rnd() << 48) >> 48;
  v1 = v1 > (65536 - 1) ? (65536 - 1) : v1;
  uint64_t v2 = (v1 >> 3) << 3;
  uint64_t v3 = rnd() >> 48;
  uint64_t v4 = rnd();

  spd->writeWord(v2, v4);

  inst = constrInstMovil1(RegId::X16, v3 & 0x00000000000000FF);
  thread0->writeReg(RegId::X16, v1);
  Cycles cycle = decodeInst(inst).exe(*archstate, inst);
  // std::cout << "Cycles:" << cycle << std::endl;
  //  read_reg() == reg + imm
#ifdef LITTLEENDIAN
  EXPECT_EQ(spd->readWord(v2), (v4&(~(static_cast<uint64_t>(0x00000000000000FF)<<(8*(v1-v2))))) | ((v3&0x00000000000000FF)<<(8*(v1-v2))));
#else
  EXPECT_EQ(spd->readWord(v2), (v4&(~(0xFF00000000000000>>(8*(v1-v2))))) | ((v3&0x00000000000000FF)<<(56-8*(v1-v2))));
#endif
  EXPECT_EQ(thread0->readReg(RegId::X16), v1+1);
  EXPECT_EQ(cycle, basim::Cycles(1));
  // Expect to be empty.
}

/* Testing with out of bound imm */
TEST_F(Movil1, OutofBoundImm) {
  ThreadStatePtr thread0;
  uint8_t tid0 = tstable->getTID();
  thread0 = new ThreadState(tid0, 0, 0, 0);
  tstable->addtoTST(thread0);
  archstate->threadstate = thread0;

  std::mt19937_64 rnd(std::random_device{}());
  uint64_t v1 = (rnd() << 48) >> 48;
  v1 = v1 > (65536 - 1) ? (65536 - 1) : v1;
  uint64_t v2 = (v1 >> 3) << 3;
  uint64_t v3 = 0xFFFFFFFFFFFFFFFF;
  uint64_t v4 = rnd();

  spd->writeWord(v2, v4);

  inst = constrInstMovil1(RegId::X16, v3);
  thread0->writeReg(RegId::X16, v1);
  Cycles cycle = decodeInst(inst).exe(*archstate, inst);
  // std::cout << "Cycles:" << cycle << std::endl;
  //  read_reg() == reg + imm
#ifdef LITTLEENDIAN
  EXPECT_EQ(spd->readWord(v2), (v4&(~(static_cast<uint64_t>(0x00000000000000FF)<<(8*(v1-v2))))) | ((v3&0x00000000000000FF)<<(8*(v1-v2))));
#else
  EXPECT_EQ(spd->readWord(v2), (v4&(~(0xFF00000000000000>>(8*(v1-v2))))) | ((v3&0x00000000000000FF)<<(56-8*(v1-v2))));
#endif
  EXPECT_EQ(thread0->readReg(RegId::X16), v1+1);
  EXPECT_EQ(cycle, basim::Cycles(1));
  // Expect to be empty.
}

/* Testing with low imm */
TEST_F(Movil1, LowImm) {
  ThreadStatePtr thread0;
  uint8_t tid0 = tstable->getTID();
  thread0 = new ThreadState(tid0, 0, 0, 0);
  tstable->addtoTST(thread0);
  archstate->threadstate = thread0;

  std::mt19937_64 rnd(std::random_device{}());
  uint64_t v1 = (rnd() << 48) >> 48;
  v1 = v1 > (65536 - 1) ? (65536 - 1) : v1;
  uint64_t v2 = (v1 >> 3) << 3;
  uint64_t v3 = 0x0000000000000000;
  uint64_t v4 = rnd();

  spd->writeWord(v2, v4);

  inst = constrInstMovil1(RegId::X16, v3 & 0x000000000000FFFF);
  thread0->writeReg(RegId::X16, v1);
  Cycles cycle = decodeInst(inst).exe(*archstate, inst);
  // std::cout << "Cycles:" << cycle << std::endl;
  //  read_reg() == reg + imm
#ifdef LITTLEENDIAN
  EXPECT_EQ(spd->readWord(v2), (v4&(~(static_cast<uint64_t>(0x00000000000000FF)<<(8*(v1-v2))))) | ((v3&0x00000000000000FF)<<(8*(v1-v2))));
#else
  EXPECT_EQ(spd->readWord(v2), (v4&(~(0xFF00000000000000>>(8*(v1-v2))))) | ((v3&0x00000000000000FF)<<(56-8*(v1-v2))));
#endif
  EXPECT_EQ(thread0->readReg(RegId::X16), v1+1);
  EXPECT_EQ(cycle, basim::Cycles(1));
  // Expect to be empty.
}

/* Testing with high imm */
TEST_F(Movil1, HighImm) {
  ThreadStatePtr thread0;
  uint8_t tid0 = tstable->getTID();
  thread0 = new ThreadState(tid0, 0, 0, 0);
  tstable->addtoTST(thread0);
  archstate->threadstate = thread0;

  std::mt19937_64 rnd(std::random_device{}());
  uint64_t v1 = (rnd() << 48) >> 48;
  v1 = v1 > (65536 - 1) ? (65536 - 1) : v1;
  uint64_t v2 = (v1 >> 3) << 3;
  uint64_t v3 = 0x00000000000000FF;
  uint64_t v4 = rnd();

  spd->writeWord(v2, v4);

  inst = constrInstMovil1(RegId::X16, v3 & 0x000000000000FFFF);
  thread0->writeReg(RegId::X16, v1);
  Cycles cycle = decodeInst(inst).exe(*archstate, inst);
  // std::cout << "Cycles:" << cycle << std::endl;
  //  read_reg() == reg + imm
#ifdef LITTLEENDIAN
  EXPECT_EQ(spd->readWord(v2), (v4&(~(static_cast<uint64_t>(0x00000000000000FF)<<(8*(v1-v2))))) | ((v3&0x00000000000000FF)<<(8*(v1-v2))));
#else
  EXPECT_EQ(spd->readWord(v2), (v4&(~(0xFF00000000000000>>(8*(v1-v2))))) | ((v3&0x00000000000000FF)<<(56-8*(v1-v2))));
#endif
  EXPECT_EQ(thread0->readReg(RegId::X16), v1+1);
  EXPECT_EQ(cycle, basim::Cycles(1));
  // Expect to be empty.
}
