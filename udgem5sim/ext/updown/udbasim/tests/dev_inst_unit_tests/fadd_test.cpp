#include "archstate.hh"
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
#include <fenv.h>
#include <gtest/gtest.h>
#include <random>
#include <cfenv>

using namespace basim;

class Fadd : public ::testing::Test {
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
TEST_F(Fadd, Random32) {
  ThreadStatePtr thread0;
  uint8_t tid0 = tstable->getTID();
  thread0 = new ThreadState(tid0, 0, 0, 0);
  uint64_t FSCR = 0x0000000000000000;
  thread0->writeReg(RegId::X4, FSCR);
  tstable->addtoTST(thread0);
  archstate->threadstate = thread0;

  std::mt19937_64 rnd(std::random_device{}());
  float v1 = rnd() / (float) rnd();
  float v2 = rnd() / (float) rnd();
  float v3 = 0.0;

  std::feclearexcept(FE_ALL_EXCEPT);
  float result = v1 + v2;
  if (std::fetestexcept(FE_INVALID)) {
    FSCR |= 0x8000000000000000;
    std::cout << "Invalid floating point operation" << std::endl;
  }
  if (std::fetestexcept(FE_DIVBYZERO)) {
    FSCR |= 0x4000000000000000;
    std::cout << "Division by zero floating point operation" << std::endl;
  }
  if (std::fetestexcept(FE_OVERFLOW)) {
    FSCR |= 0x2000000000000000;
    std::cout << "Overflow" << std::endl;
  }
  if (std::fetestexcept(FE_UNDERFLOW)) {
    FSCR |= 0x1000000000000000;
    std::cout << "Underflow" << std::endl;
  }
  if (std::fetestexcept(FE_INEXACT)) {
    FSCR |= 0x0800000000000000;
    std::cout << "Invalid floating point operation" << std::endl;
  }

  uint32_t v1_32 = *(uint32_t*) &v1;
  uint32_t v2_32 = *(uint32_t*) &v2;
  uint32_t v3_32 = *(uint32_t*) &v3;
  uint32_t result_32 = *(uint32_t*) &result;

  inst = constrInstFmaddFaddFsubFmulFdivFsqrtFexp(1, 2, RegId::X16, RegId::X17, RegId::X18);
  thread0->writeReg(RegId::X16, v1_32);
  thread0->writeReg(RegId::X17, v2_32);
  thread0->writeReg(RegId::X18, v3_32);
  Cycles cycle = decodeInst(inst).exe(*archstate, inst);
  // std::cout << "Cycles:" << cycle << std::endl;
  
  EXPECT_EQ(static_cast<int64_t>(thread0->readReg(RegId::X16)), v1_32);
  EXPECT_EQ(static_cast<int64_t>(thread0->readReg(RegId::X17)), v2_32);
  EXPECT_EQ(static_cast<int64_t>(thread0->readReg(RegId::X18)), result_32);
  EXPECT_EQ(static_cast<uint64_t>(thread0->readReg(RegId::X4)), FSCR);
  EXPECT_EQ(cycle, basim::Cycles(1));
  // Expect to be empty.
}

/* Testing with random value */
TEST_F(Fadd, Random64) {
  ThreadStatePtr thread0;
  uint8_t tid0 = tstable->getTID();
  thread0 = new ThreadState(tid0, 0, 0, 0);
  uint64_t FSCR = 0x0000000000000000;
  thread0->writeReg(RegId::X4, FSCR);
  tstable->addtoTST(thread0);
  archstate->threadstate = thread0;

  std::mt19937_64 rnd(std::random_device{}());
  double v1 = (double) rnd() / (double) rnd();
  double v2 = (double) rnd() / (double) rnd();
  double v3 = 0.0;

  std::feclearexcept(FE_ALL_EXCEPT);
  double result = v1 + v2;
  if (std::fetestexcept(FE_INVALID)) {
    FSCR |= 0x8000000000000000;
    std::cout << "Invalid floating point operation" << std::endl;
  }
  if (std::fetestexcept(FE_DIVBYZERO)) {
    FSCR |= 0x4000000000000000;
    std::cout << "Division by zero floating point operation" << std::endl;
  }
  if (std::fetestexcept(FE_OVERFLOW)) {
    FSCR |= 0x2000000000000000;
    std::cout << "Overflow" << std::endl;
  }
  if (std::fetestexcept(FE_UNDERFLOW)) {
    FSCR |= 0x1000000000000000;
    std::cout << "Underflow" << std::endl;
  }
  if (std::fetestexcept(FE_INEXACT)) {
    FSCR |= 0x0800000000000000;
    std::cout << "Invalid floating point operation" << std::endl;
  }

  uint64_t v1_64 = *(uint64_t*) &v1;
  uint64_t v2_64 = *(uint64_t*) &v2;
  uint64_t v3_64 = *(uint64_t*) &v3;
  uint64_t result_64 = *(uint64_t*) &result;

  inst = constrInstFmaddFaddFsubFmulFdivFsqrtFexp(1, 1, RegId::X16, RegId::X17, RegId::X18);
  thread0->writeReg(RegId::X16, v1_64);
  thread0->writeReg(RegId::X17, v2_64);
  thread0->writeReg(RegId::X18, v3_64);
  Cycles cycle = decodeInst(inst).exe(*archstate, inst);
  // std::cout << "Cycles:" << cycle << std::endl;
  
  EXPECT_EQ(static_cast<int64_t>(thread0->readReg(RegId::X18)), result_64);
  EXPECT_EQ(static_cast<int64_t>(thread0->readReg(RegId::X16)), v1_64);
  EXPECT_EQ(static_cast<int64_t>(thread0->readReg(RegId::X17)), v2_64);
  EXPECT_EQ(static_cast<uint64_t>(thread0->readReg(RegId::X4)), FSCR);
  EXPECT_EQ(cycle, basim::Cycles(1));
  // Expect to be empty.
}

/* Testing overflow*/
// TEST_F(Fadd, overflow64) {
//   ThreadStatePtr thread0;
//   uint8_t tid0 = tstable->getTID();
//   thread0 = new ThreadState(tid0, 0, 0, 0);
//   uint64_t FSCR = 0x0000000000000000;
//   thread0->writeReg(RegId::X4, FSCR);
//   tstable->addtoTST(thread0);
//   archstate->threadstate = thread0;

//   std::mt19937_64 rnd(std::random_device{}());
//   uint64_t max_fp64  = 0x7FEFFFFFFFFFFFFF;
//   double v1 = 1.0;
//   double v3 = 0.0;

//   uint64_t v1_64 = *(uint64_t*) &v1;
//   uint64_t v3_64 = *(uint64_t*) &v3;

//   inst = constrInstFmaddFaddFsubFmulFdivFsqrtFexp(1, 1, RegId::X16, RegId::X17, RegId::X18);
//   thread0->writeReg(RegId::X16, v1_64);
//   thread0->writeReg(RegId::X17, max_fp64);
//   thread0->writeReg(RegId::X18, v3_64);
//   Cycles cycle = decodeInst(inst).exe(*archstate, inst);
//   std::cout << "FSCR:" << static_cast<uint64_t>(thread0->readReg(RegId::X4)) << std::endl;
//   //  read_reg() == reg + imm
//   EXPECT_EQ(static_cast<int64_t>(thread0->readReg(RegId::X16)), v1_64);
//   EXPECT_EQ(static_cast<int64_t>(thread0->readReg(RegId::X17)), max_fp64);
//   EXPECT_EQ(static_cast<uint64_t>(thread0->readReg(RegId::X4)), 0x2000000000000000);
//   EXPECT_EQ(cycle, basim::Cycles(1));
//   // Expect to be empty.
// }
