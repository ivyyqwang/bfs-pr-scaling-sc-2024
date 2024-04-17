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

class Vgt_b16 : public ::testing::Test {
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
TEST_F(Vgt_b16, Random) {
  ThreadStatePtr thread0;
  uint8_t tid0 = tstable->getTID();
  thread0 = new ThreadState(tid0, 0, 0, 0);
  tstable->addtoTST(thread0);
  archstate->threadstate = thread0;

  std::mt19937_64 rnd(std::random_device{}());
  uint64_t v1 = rnd();
  uint64_t v2 = rnd();
  uint64_t v3 = rnd();
  uint64_t mask = rnd() >> 60;

  inst = constrInstVgt(3, RegId::X16, RegId::X17, RegId::X18, mask);
  thread0->writeReg(RegId::X16, v1);
  thread0->writeReg(RegId::X17, v2);
  thread0->writeReg(RegId::X18, v3);

  Cycles cycle = decodeInst(inst).exe(*archstate, inst);
  // std::cout << "Cycles:" << cycle << std::endl;
  EXPECT_EQ(thread0->readReg(RegId::X16), v1);
  EXPECT_EQ(thread0->readReg(RegId::X17), v2);
  uint32_t v1_3 = static_cast<uint32_t>(((v1 <<  0) >> 48) << 16);
  uint32_t v2_3 = static_cast<uint32_t>(((v2 <<  0) >> 48) << 16);
  uint32_t v1_2 = static_cast<uint32_t>(((v1 << 16) >> 48) << 16);
  uint32_t v2_2 = static_cast<uint32_t>(((v2 << 16) >> 48) << 16);
  uint32_t v1_1 = static_cast<uint32_t>(((v1 << 32) >> 48) << 16);
  uint32_t v2_1 = static_cast<uint32_t>(((v2 << 32) >> 48) << 16);
  uint32_t v1_0 = static_cast<uint32_t>(((v1 << 48) >> 48) << 16);
  uint32_t v2_0 = static_cast<uint32_t>(((v2 << 48) >> 48) << 16);
  EXPECT_EQ(thread0->readReg(RegId::X18), (v3 & (~mask)) | (mask & (
    (static_cast<uint64_t>(*reinterpret_cast<float *>(&v1_3) > *reinterpret_cast<float *>(&v2_3)) << 3) | 
    (static_cast<uint64_t>(*reinterpret_cast<float *>(&v1_2) > *reinterpret_cast<float *>(&v2_2)) << 2) | 
    (static_cast<uint64_t>(*reinterpret_cast<float *>(&v1_1) > *reinterpret_cast<float *>(&v2_1)) << 1) | 
    (static_cast<uint64_t>(*reinterpret_cast<float *>(&v1_0) > *reinterpret_cast<float *>(&v2_0))     ))));
  // Expect to be empty.
}

/* Testing with full value */
TEST_F(Vgt_b16, Full) {
  ThreadStatePtr thread0;
  uint8_t tid0 = tstable->getTID();
  thread0 = new ThreadState(tid0, 0, 0, 0);
  tstable->addtoTST(thread0);
  archstate->threadstate = thread0;

  std::mt19937_64 rnd(std::random_device{}());
  uint64_t v1 = rnd();
  uint64_t v2 = rnd();
  uint64_t v3 = rnd();
  uint64_t mask = 0x000000000000000F;

  inst = constrInstVgt(3, RegId::X16, RegId::X17, RegId::X18, mask);
  thread0->writeReg(RegId::X16, v1);
  thread0->writeReg(RegId::X17, v2);
  thread0->writeReg(RegId::X18, v3);

  Cycles cycle = decodeInst(inst).exe(*archstate, inst);
  // std::cout << "Cycles:" << cycle << std::endl;
  EXPECT_EQ(thread0->readReg(RegId::X16), v1);
  EXPECT_EQ(thread0->readReg(RegId::X17), v2);
  uint32_t v1_3 = static_cast<uint32_t>(((v1 <<  0) >> 48) << 16);
  uint32_t v2_3 = static_cast<uint32_t>(((v2 <<  0) >> 48) << 16);
  uint32_t v1_2 = static_cast<uint32_t>(((v1 << 16) >> 48) << 16);
  uint32_t v2_2 = static_cast<uint32_t>(((v2 << 16) >> 48) << 16);
  uint32_t v1_1 = static_cast<uint32_t>(((v1 << 32) >> 48) << 16);
  uint32_t v2_1 = static_cast<uint32_t>(((v2 << 32) >> 48) << 16);
  uint32_t v1_0 = static_cast<uint32_t>(((v1 << 48) >> 48) << 16);
  uint32_t v2_0 = static_cast<uint32_t>(((v2 << 48) >> 48) << 16);
  EXPECT_EQ(thread0->readReg(RegId::X18), (v3 & (~mask)) | (mask & (
    (static_cast<uint64_t>(*reinterpret_cast<float *>(&v1_3) > *reinterpret_cast<float *>(&v2_3)) << 3) | 
    (static_cast<uint64_t>(*reinterpret_cast<float *>(&v1_2) > *reinterpret_cast<float *>(&v2_2)) << 2) | 
    (static_cast<uint64_t>(*reinterpret_cast<float *>(&v1_1) > *reinterpret_cast<float *>(&v2_1)) << 1) | 
    (static_cast<uint64_t>(*reinterpret_cast<float *>(&v1_0) > *reinterpret_cast<float *>(&v2_0))     ))));
  // Expect to be empty.
}

/* Testing with empty value */
TEST_F(Vgt_b16, Empty) {
  ThreadStatePtr thread0;
  uint8_t tid0 = tstable->getTID();
  thread0 = new ThreadState(tid0, 0, 0, 0);
  tstable->addtoTST(thread0);
  archstate->threadstate = thread0;

  std::mt19937_64 rnd(std::random_device{}());
  uint64_t v1 = rnd();
  uint64_t v2 = rnd();
  uint64_t v3 = rnd();
  uint64_t mask = 0x0000000000000000;

  inst = constrInstVgt(3, RegId::X16, RegId::X17, RegId::X18, mask);
  thread0->writeReg(RegId::X16, v1);
  thread0->writeReg(RegId::X17, v2);
  thread0->writeReg(RegId::X18, v3);

  Cycles cycle = decodeInst(inst).exe(*archstate, inst);
  // std::cout << "Cycles:" << cycle << std::endl;
  EXPECT_EQ(thread0->readReg(RegId::X16), v1);
  EXPECT_EQ(thread0->readReg(RegId::X17), v2);
  EXPECT_EQ(thread0->readReg(RegId::X18), (v3 & (~mask)) | (mask & (0x0000000000000000)));
  // Expect to be empty.
}
