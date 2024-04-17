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
#include <gtest/gtest.h>
#include <random>

using namespace basim;

class Hashl : public ::testing::Test {
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

/* Vanila implementation of CRC64-ECMA-182 */
uint64_t crc64_helper_hashl(uint64_t input) {
    uint64_t poly = 0xC96C5795D7870F42;
    uint64_t crc = input ^ 0xFFFFFFFFFFFFFFFF;
    for (int i = 0; i < 64; i++) {
        if (crc & 1) {
            crc = (crc >> 1) ^ poly;
        } else {
            crc = crc >> 1;
        }
    }
    return crc ^ 0xFFFFFFFFFFFFFFFF;
}

/* Testing with random value */
TEST_F(Hashl, Random) {
  ThreadStatePtr thread0;
  uint8_t tid0 = tstable->getTID();
  thread0 = new ThreadState(tid0, 0, 0, 0);
  tstable->addtoTST(thread0);
  archstate->threadstate = thread0;

  std::mt19937_64 rnd(std::random_device{}());
  uint64_t v1 = rnd();
  uint64_t v2 = rnd();
  uint64_t v3 = rnd();
  uint64_t v4 = rnd();
  uint64_t v5 = rnd();
  uint64_t v6 = rnd();
  uint64_t v7 = rnd();
  uint64_t v8 = rnd();
  uint64_t v9 = ((rnd() << 48) >> 51) << 3;
  v9 = v9 > (65536 - 8*8) ? (65536 - 8*8) : v9;
  uint64_t v10 = rnd();
  uint64_t v11 = rnd() >> 61;
  v11 += 1;

  inst = constrInstHashl(RegId::X16, RegId::X17, v11 - 1);
  spd->writeWord(v9+8*0, v1);
  spd->writeWord(v9+8*1, v2);
  spd->writeWord(v9+8*2, v3);
  spd->writeWord(v9+8*3, v4);
  spd->writeWord(v9+8*4, v5);
  spd->writeWord(v9+8*5, v6);
  spd->writeWord(v9+8*6, v7);
  spd->writeWord(v9+8*7, v8);
  thread0->writeReg(RegId::X16, v9);
  thread0->writeReg(RegId::X17, v10);
  Cycles cycle = decodeInst(inst).exe(*archstate, inst);
  // std::cout << "Cycles:" << cycle << std::endl;
  //  read_reg() == reg + imm
  EXPECT_EQ(spd->readWord(v9+8*0), v1);
  EXPECT_EQ(spd->readWord(v9+8*1), v2);
  EXPECT_EQ(spd->readWord(v9+8*2), v3);
  EXPECT_EQ(spd->readWord(v9+8*3), v4);
  EXPECT_EQ(spd->readWord(v9+8*4), v5);
  EXPECT_EQ(spd->readWord(v9+8*5), v6);
  EXPECT_EQ(spd->readWord(v9+8*6), v7);
  EXPECT_EQ(spd->readWord(v9+8*7), v8);
  for (int i = 0; i < v11; i++) {
    v10 = crc64_helper_hashl(spd->readWord(v9)+v10);
    v9 += 8;
  }
  EXPECT_EQ(thread0->readReg(RegId::X16), v9);
  EXPECT_EQ(thread0->readReg(RegId::X17), v10);
  EXPECT_EQ(cycle, basim::Cycles(1));
  // Expect to be empty.
}

/* Testing with max value */
TEST_F(Hashl, Max) {
  ThreadStatePtr thread0;
  uint8_t tid0 = tstable->getTID();
  thread0 = new ThreadState(tid0, 0, 0, 0);
  tstable->addtoTST(thread0);
  archstate->threadstate = thread0;

  std::mt19937_64 rnd(std::random_device{}());
  uint64_t v1 = 0xFFFFFFFFFFFFFFFF;
  uint64_t v2 = 0xFFFFFFFFFFFFFFFF;
  uint64_t v3 = 0xFFFFFFFFFFFFFFFF;
  uint64_t v4 = 0xFFFFFFFFFFFFFFFF;
  uint64_t v5 = 0xFFFFFFFFFFFFFFFF;
  uint64_t v6 = 0xFFFFFFFFFFFFFFFF;
  uint64_t v7 = 0xFFFFFFFFFFFFFFFF;
  uint64_t v8 = 0xFFFFFFFFFFFFFFFF;
  uint64_t v9 = ((rnd() << 48) >> 51) << 3;
  v9 = v9 > (65536 - 8*8) ? (65536 - 8*8) : v9;
  uint64_t v10 = rnd();
  uint64_t v11 = rnd() >> 61;
  v11 += 1;

  inst = constrInstHashl(RegId::X16, RegId::X17, v11 - 1);
  spd->writeWord(v9+8*0, v1);
  spd->writeWord(v9+8*1, v2);
  spd->writeWord(v9+8*2, v3);
  spd->writeWord(v9+8*3, v4);
  spd->writeWord(v9+8*4, v5);
  spd->writeWord(v9+8*5, v6);
  spd->writeWord(v9+8*6, v7);
  spd->writeWord(v9+8*7, v8);
  thread0->writeReg(RegId::X16, v9);
  thread0->writeReg(RegId::X17, v10);
  Cycles cycle = decodeInst(inst).exe(*archstate, inst);
  // std::cout << "Cycles:" << cycle << std::endl;
  //  read_reg() == reg + imm
  EXPECT_EQ(spd->readWord(v9+8*0), v1);
  EXPECT_EQ(spd->readWord(v9+8*1), v2);
  EXPECT_EQ(spd->readWord(v9+8*2), v3);
  EXPECT_EQ(spd->readWord(v9+8*3), v4);
  EXPECT_EQ(spd->readWord(v9+8*4), v5);
  EXPECT_EQ(spd->readWord(v9+8*5), v6);
  EXPECT_EQ(spd->readWord(v9+8*6), v7);
  EXPECT_EQ(spd->readWord(v9+8*7), v8);
  for (int i = 0; i < v11; i++) {
    v10 = crc64_helper_hashl(spd->readWord(v9)+v10);
    v9 += 8;
  }
  EXPECT_EQ(thread0->readReg(RegId::X16), v9);
  EXPECT_EQ(thread0->readReg(RegId::X17), v10);
  EXPECT_EQ(cycle, basim::Cycles(1));
  // Expect to be empty.
}

/* Testing with min value */
TEST_F(Hashl, Min) {
  ThreadStatePtr thread0;
  uint8_t tid0 = tstable->getTID();
  thread0 = new ThreadState(tid0, 0, 0, 0);
  tstable->addtoTST(thread0);
  archstate->threadstate = thread0;

  std::mt19937_64 rnd(std::random_device{}());
  uint64_t v1 = 0x0000000000000000;
  uint64_t v2 = 0x0000000000000000;
  uint64_t v3 = 0x0000000000000000;
  uint64_t v4 = 0x0000000000000000;
  uint64_t v5 = 0x0000000000000000;
  uint64_t v6 = 0x0000000000000000;
  uint64_t v7 = 0x0000000000000000;
  uint64_t v8 = 0x0000000000000000;
  uint64_t v9 = ((rnd() << 48) >> 51) << 3;
  v9 = v9 > (65536 - 8*8) ? (65536 - 8*8) : v9;
  uint64_t v10 = rnd();
  uint64_t v11 = rnd() >> 61;
  v11 += 1;

  inst = constrInstHashl(RegId::X16, RegId::X17, v11 - 1);
  spd->writeWord(v9+8*0, v1);
  spd->writeWord(v9+8*1, v2);
  spd->writeWord(v9+8*2, v3);
  spd->writeWord(v9+8*3, v4);
  spd->writeWord(v9+8*4, v5);
  spd->writeWord(v9+8*5, v6);
  spd->writeWord(v9+8*6, v7);
  spd->writeWord(v9+8*7, v8);
  thread0->writeReg(RegId::X16, v9);
  thread0->writeReg(RegId::X17, v10);
  Cycles cycle = decodeInst(inst).exe(*archstate, inst);
  // std::cout << "Cycles:" << cycle << std::endl;
  //  read_reg() == reg + imm
  EXPECT_EQ(spd->readWord(v9+8*0), v1);
  EXPECT_EQ(spd->readWord(v9+8*1), v2);
  EXPECT_EQ(spd->readWord(v9+8*2), v3);
  EXPECT_EQ(spd->readWord(v9+8*3), v4);
  EXPECT_EQ(spd->readWord(v9+8*4), v5);
  EXPECT_EQ(spd->readWord(v9+8*5), v6);
  EXPECT_EQ(spd->readWord(v9+8*6), v7);
  EXPECT_EQ(spd->readWord(v9+8*7), v8);
  for (int i = 0; i < v11; i++) {
    v10 = crc64_helper_hashl(spd->readWord(v9)+v10);
    v9 += 8;
  }
  EXPECT_EQ(thread0->readReg(RegId::X16), v9);
  EXPECT_EQ(thread0->readReg(RegId::X17), v10);
  EXPECT_EQ(cycle, basim::Cycles(1));
  // Expect to be empty.
}

/* Testing with max length */
TEST_F(Hashl, MaxLength) {
  ThreadStatePtr thread0;
  uint8_t tid0 = tstable->getTID();
  thread0 = new ThreadState(tid0, 0, 0, 0);
  tstable->addtoTST(thread0);
  archstate->threadstate = thread0;

  std::mt19937_64 rnd(std::random_device{}());
  uint64_t v1 = rnd();
  uint64_t v2 = rnd();
  uint64_t v3 = rnd();
  uint64_t v4 = rnd();
  uint64_t v5 = rnd();
  uint64_t v6 = rnd();
  uint64_t v7 = rnd();
  uint64_t v8 = rnd();
  uint64_t v9 = ((rnd() << 48) >> 51) << 3;
  v9 = v9 > (65536 - 8*8) ? (65536 - 8*8) : v9;
  uint64_t v10 = rnd();
  uint64_t v11 = 0x0000000000000007;
  v11 += 1;

  inst = constrInstHashl(RegId::X16, RegId::X17, v11 - 1);
  spd->writeWord(v9+8*0, v1);
  spd->writeWord(v9+8*1, v2);
  spd->writeWord(v9+8*2, v3);
  spd->writeWord(v9+8*3, v4);
  spd->writeWord(v9+8*4, v5);
  spd->writeWord(v9+8*5, v6);
  spd->writeWord(v9+8*6, v7);
  spd->writeWord(v9+8*7, v8);
  thread0->writeReg(RegId::X16, v9);
  thread0->writeReg(RegId::X17, v10);
  Cycles cycle = decodeInst(inst).exe(*archstate, inst);
  // std::cout << "Cycles:" << cycle << std::endl;
  //  read_reg() == reg + imm
  EXPECT_EQ(spd->readWord(v9+8*0), v1);
  EXPECT_EQ(spd->readWord(v9+8*1), v2);
  EXPECT_EQ(spd->readWord(v9+8*2), v3);
  EXPECT_EQ(spd->readWord(v9+8*3), v4);
  EXPECT_EQ(spd->readWord(v9+8*4), v5);
  EXPECT_EQ(spd->readWord(v9+8*5), v6);
  EXPECT_EQ(spd->readWord(v9+8*6), v7);
  EXPECT_EQ(spd->readWord(v9+8*7), v8);
  for (int i = 0; i < v11; i++) {
    v10 = crc64_helper_hashl(spd->readWord(v9)+v10);
    v9 += 8;
  }
  EXPECT_EQ(thread0->readReg(RegId::X16), v9);
  EXPECT_EQ(thread0->readReg(RegId::X17), v10);
  EXPECT_EQ(cycle, basim::Cycles(1));
  // Expect to be empty.
}


/* Testing with min length */
TEST_F(Hashl, MinLength) {
  ThreadStatePtr thread0;
  uint8_t tid0 = tstable->getTID();
  thread0 = new ThreadState(tid0, 0, 0, 0);
  tstable->addtoTST(thread0);
  archstate->threadstate = thread0;

  std::mt19937_64 rnd(std::random_device{}());
  uint64_t v1 = rnd();
  uint64_t v2 = rnd();
  uint64_t v3 = rnd();
  uint64_t v4 = rnd();
  uint64_t v5 = rnd();
  uint64_t v6 = rnd();
  uint64_t v7 = rnd();
  uint64_t v8 = rnd();
  uint64_t v9 = ((rnd() << 48) >> 51) << 3;
  v9 = v9 > (65536 - 8*8) ? (65536 - 8*8) : v9;
  uint64_t v10 = rnd();
  uint64_t v11 = 0x0000000000000000;
  v11 += 1;

  inst = constrInstHashl(RegId::X16, RegId::X17, v11 - 1);
  spd->writeWord(v9+8*0, v1);
  spd->writeWord(v9+8*1, v2);
  spd->writeWord(v9+8*2, v3);
  spd->writeWord(v9+8*3, v4);
  spd->writeWord(v9+8*4, v5);
  spd->writeWord(v9+8*5, v6);
  spd->writeWord(v9+8*6, v7);
  spd->writeWord(v9+8*7, v8);
  thread0->writeReg(RegId::X16, v9);
  thread0->writeReg(RegId::X17, v10);
  Cycles cycle = decodeInst(inst).exe(*archstate, inst);
  // std::cout << "Cycles:" << cycle << std::endl;
  //  read_reg() == reg + imm
  EXPECT_EQ(spd->readWord(v9+8*0), v1);
  EXPECT_EQ(spd->readWord(v9+8*1), v2);
  EXPECT_EQ(spd->readWord(v9+8*2), v3);
  EXPECT_EQ(spd->readWord(v9+8*3), v4);
  EXPECT_EQ(spd->readWord(v9+8*4), v5);
  EXPECT_EQ(spd->readWord(v9+8*5), v6);
  EXPECT_EQ(spd->readWord(v9+8*6), v7);
  EXPECT_EQ(spd->readWord(v9+8*7), v8);
  for (int i = 0; i < v11; i++) {
    v10 = crc64_helper_hashl(spd->readWord(v9)+v10);
    v9 += 8;
  }
  EXPECT_EQ(thread0->readReg(RegId::X16), v9);
  EXPECT_EQ(thread0->readReg(RegId::X17), v10);
  EXPECT_EQ(cycle, basim::Cycles(1));
  // Expect to be empty.
}
