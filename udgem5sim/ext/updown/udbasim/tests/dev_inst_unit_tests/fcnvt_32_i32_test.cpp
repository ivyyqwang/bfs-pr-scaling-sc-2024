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

class Fcnvt_32_i32 : public ::testing::Test {
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
TEST_F(Fcnvt_32_i32, Random) {
  ThreadStatePtr thread0;
  uint8_t tid0 = tstable->getTID();
  thread0 = new ThreadState(tid0, 0, 0, 0);
  tstable->addtoTST(thread0);
  archstate->threadstate = thread0;

  std::mt19937_64 rnd(std::random_device{}());
  uint64_t v1 = 0x00000000C3D60000;
  uint64_t v2 = rnd();
  uint64_t v3 = 0x00000000FFFFFE54;

  inst = constrInstFcnvt(0, 2, RegId::X16, RegId::X17);
  thread0->writeReg(RegId::X16, v1);
  thread0->writeReg(RegId::X17, v2);
  Cycles cycle = decodeInst(inst).exe(*archstate, inst);
  // std::cout << "Cycles:" << cycle << std::endl;
  //  read_reg() == reg + imm
  EXPECT_EQ(thread0->readReg(RegId::X16), v1);
  EXPECT_EQ(thread0->readReg(RegId::X17), v3);
  EXPECT_EQ(thread0->readReg(RegId::X4) >> 59, 0b00000);
  // Expect to be empty.
}

/* Testing with edge value */
TEST_F(Fcnvt_32_i32, Edge0) {
  ThreadStatePtr thread0;
  uint8_t tid0 = tstable->getTID();
  thread0 = new ThreadState(tid0, 0, 0, 0);
  tstable->addtoTST(thread0);
  archstate->threadstate = thread0;

  std::mt19937_64 rnd(std::random_device{}());
  uint64_t v1 = 0x0000000000000001;
  uint64_t v2 = rnd();
  uint64_t v3 = 0x0000000000000000;

  inst = constrInstFcnvt(0, 2, RegId::X16, RegId::X17);
  thread0->writeReg(RegId::X16, v1);
  thread0->writeReg(RegId::X17, v2);
  Cycles cycle = decodeInst(inst).exe(*archstate, inst);
  // std::cout << "Cycles:" << cycle << std::endl;
  //  read_reg() == reg + imm
  EXPECT_EQ(thread0->readReg(RegId::X16), v1);
  EXPECT_EQ(thread0->readReg(RegId::X17), v3);
  EXPECT_EQ(thread0->readReg(RegId::X4) >> 59, 0b00001);
  // Expect to be empty.
}

/* Testing with edge value */
TEST_F(Fcnvt_32_i32, Edge1) {
  ThreadStatePtr thread0;
  uint8_t tid0 = tstable->getTID();
  thread0 = new ThreadState(tid0, 0, 0, 0);
  tstable->addtoTST(thread0);
  archstate->threadstate = thread0;

  std::mt19937_64 rnd(std::random_device{}());
  uint64_t v1 = 0x0000000080000001;
  uint64_t v2 = rnd();
  uint64_t v3 = 0x0000000000000000;

  inst = constrInstFcnvt(0, 2, RegId::X16, RegId::X17);
  thread0->writeReg(RegId::X16, v1);
  thread0->writeReg(RegId::X17, v2);
  Cycles cycle = decodeInst(inst).exe(*archstate, inst);
  // std::cout << "Cycles:" << cycle << std::endl;
  //  read_reg() == reg + imm
  EXPECT_EQ(thread0->readReg(RegId::X16), v1);
  EXPECT_EQ(thread0->readReg(RegId::X17), v3);
  EXPECT_EQ(thread0->readReg(RegId::X4) >> 59, 0b00001);
  // Expect to be empty.
}

/* Testing with edge value */
TEST_F(Fcnvt_32_i32, Edge2) {
  ThreadStatePtr thread0;
  uint8_t tid0 = tstable->getTID();
  thread0 = new ThreadState(tid0, 0, 0, 0);
  tstable->addtoTST(thread0);
  archstate->threadstate = thread0;

  std::mt19937_64 rnd(std::random_device{}());
  uint64_t v1 = 0x000000007F7FFFFF;
  uint64_t v2 = rnd();
  uint64_t v3 = 0x0000000080000000;

  inst = constrInstFcnvt(0, 2, RegId::X16, RegId::X17);
  thread0->writeReg(RegId::X16, v1);
  thread0->writeReg(RegId::X17, v2);
  Cycles cycle = decodeInst(inst).exe(*archstate, inst);
  // std::cout << "Cycles:" << cycle << std::endl;
  //  read_reg() == reg + imm
  EXPECT_EQ(thread0->readReg(RegId::X16), v1);
  EXPECT_EQ(thread0->readReg(RegId::X17), v3);
  EXPECT_EQ(thread0->readReg(RegId::X4) >> 59, 0b00101);
  // Expect to be empty.
}

/* Testing with edge value */
TEST_F(Fcnvt_32_i32, Edge3) {
  ThreadStatePtr thread0;
  uint8_t tid0 = tstable->getTID();
  thread0 = new ThreadState(tid0, 0, 0, 0);
  tstable->addtoTST(thread0);
  archstate->threadstate = thread0;

  std::mt19937_64 rnd(std::random_device{}());
  uint64_t v1 = 0x00000000FF7FFFFF;
  uint64_t v2 = rnd();
  uint64_t v3 = 0x0000000080000000;

  inst = constrInstFcnvt(0, 2, RegId::X16, RegId::X17);
  thread0->writeReg(RegId::X16, v1);
  thread0->writeReg(RegId::X17, v2);
  Cycles cycle = decodeInst(inst).exe(*archstate, inst);
  // std::cout << "Cycles:" << cycle << std::endl;
  //  read_reg() == reg + imm
  EXPECT_EQ(thread0->readReg(RegId::X16), v1);
  EXPECT_EQ(thread0->readReg(RegId::X17), v3);
  EXPECT_EQ(thread0->readReg(RegId::X4) >> 59, 0b00101);
  // Expect to be empty.
}
