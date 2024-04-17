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

class Hashl64 : public ::testing::Test {
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
uint64_t crc64_helper_hashl64(uint64_t input) {
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
TEST_F(Hashl64, Random) {
  ThreadStatePtr thread0;
  uint8_t tid0 = tstable->getTID();
  thread0 = new ThreadState(tid0, 0, 0, 0);
  tstable->addtoTST(thread0);
  archstate->threadstate = thread0;

  std::mt19937_64 rnd(std::random_device{}());
  uint64_t v1 = ((rnd() << 48) >> 51) << 3;
  uint64_t v2 = rnd();
  uint64_t v3 = rnd();
  uint64_t v4 = rnd();

  inst = constrInstHashl64(RegId::X16, RegId::X17);
  thread0->writeReg(RegId::X5, v1);
  spd->writeWord(v1, v2);
  thread0->writeReg(RegId::X16, v3);
  thread0->writeReg(RegId::X17, v4);
  Cycles cycle = decodeInst(inst).exe(*archstate, inst);
  // std::cout << "Cycles:" << cycle << std::endl;
  //  read_reg() == reg + imm
  EXPECT_EQ(thread0->readReg(RegId::X5), v1);
  EXPECT_EQ(spd->readWord(v1), v2);
  EXPECT_EQ(thread0->readReg(RegId::X16), v3);
  EXPECT_EQ(thread0->readReg(RegId::X17), crc64_helper_hashl64(v2) + v3);
  EXPECT_EQ(cycle, basim::Cycles(1));
  // Expect to be empty.
}

/* Testing with max value */
TEST_F(Hashl64, Max) {
  ThreadStatePtr thread0;
  uint8_t tid0 = tstable->getTID();
  thread0 = new ThreadState(tid0, 0, 0, 0);
  tstable->addtoTST(thread0);
  archstate->threadstate = thread0;

  std::mt19937_64 rnd(std::random_device{}());
  uint64_t v1 = ((rnd() << 48) >> 51) << 3;
  uint64_t v2 = 0xFFFFFFFFFFFFFFFF;
  uint64_t v3 = rnd();
  uint64_t v4 = rnd();

  inst = constrInstHashl64(RegId::X16, RegId::X17);
  thread0->writeReg(RegId::X5, v1);
  spd->writeWord(v1, v2);
  thread0->writeReg(RegId::X16, v3);
  thread0->writeReg(RegId::X17, v4);
  Cycles cycle = decodeInst(inst).exe(*archstate, inst);
  // std::cout << "Cycles:" << cycle << std::endl;
  //  read_reg() == reg + imm
  EXPECT_EQ(thread0->readReg(RegId::X5), v1);
  EXPECT_EQ(spd->readWord(v1), v2);
  EXPECT_EQ(thread0->readReg(RegId::X16), v3);
  EXPECT_EQ(thread0->readReg(RegId::X17), crc64_helper_hashl64(v2) + v3);
  EXPECT_EQ(cycle, basim::Cycles(1));
  // Expect to be empty.
}

/* Testing with min value */
TEST_F(Hashl64, Min) {
  ThreadStatePtr thread0;
  uint8_t tid0 = tstable->getTID();
  thread0 = new ThreadState(tid0, 0, 0, 0);
  tstable->addtoTST(thread0);
  archstate->threadstate = thread0;

  std::mt19937_64 rnd(std::random_device{}());
  uint64_t v1 = ((rnd() << 48) >> 51) << 3;
  uint64_t v2 = 0x0000000000000000;
  uint64_t v3 = rnd();
  uint64_t v4 = rnd();

  inst = constrInstHashl64(RegId::X16, RegId::X17);
  thread0->writeReg(RegId::X5, v1);
  spd->writeWord(v1, v2);
  thread0->writeReg(RegId::X16, v3);
  thread0->writeReg(RegId::X17, v4);
  Cycles cycle = decodeInst(inst).exe(*archstate, inst);
  // std::cout << "Cycles:" << cycle << std::endl;
  //  read_reg() == reg + imm
  EXPECT_EQ(thread0->readReg(RegId::X5), v1);
  EXPECT_EQ(spd->readWord(v1), v2);
  EXPECT_EQ(thread0->readReg(RegId::X16), v3);
  EXPECT_EQ(thread0->readReg(RegId::X17), crc64_helper_hashl64(v2) + v3);
  EXPECT_EQ(cycle, basim::Cycles(1));
  // Expect to be empty.
}
