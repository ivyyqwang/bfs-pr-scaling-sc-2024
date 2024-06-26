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

class Modi : public ::testing::Test {
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
TEST_F(Modi, Random) {
  ThreadStatePtr thread0;
  uint8_t tid0 = tstable->getTID();
  thread0 = new ThreadState(tid0, 0, 0, 0);
  tstable->addtoTST(thread0);
  archstate->threadstate = thread0;

  std::mt19937_64 rnd(std::random_device{}());
  uint64_t v1 = static_cast<uint64_t>((static_cast<int64_t>(rnd() << 48)) >> 48);
  v1 = v1 == 0 ? 0x0000000000000001 : v1;
  uint64_t v2 = rnd();
  uint64_t v3 = rnd();

  inst = constrInstModi(RegId::X16, RegId::X17, v1 & 0x000000000000FFFF);
  thread0->writeReg(RegId::X16, v2);
  thread0->writeReg(RegId::X17, v3);
  Cycles cycle = decodeInst(inst).exe(*archstate, inst);
  // std::cout << "Cycles:" << cycle << std::endl;
  //  read_reg() == reg + imm
  EXPECT_EQ(thread0->readReg(RegId::X17), static_cast<uint64_t>((static_cast<int64_t>(v2)) % (static_cast<int64_t>(v1))));
  EXPECT_EQ(thread0->readReg(RegId::X16), v2);
  EXPECT_EQ(cycle, basim::Cycles(1));
  // Expect to be empty.
}

/* Testing mod by 0 */
TEST_F(Modi, By0) {
  ThreadStatePtr thread0;
  uint8_t tid0 = tstable->getTID();
  thread0 = new ThreadState(tid0, 0, 0, 0);
  tstable->addtoTST(thread0);
  archstate->threadstate = thread0;

  std::mt19937_64 rnd(std::random_device{}());
  uint64_t v1 = 0;
  uint64_t v2 = rnd();
  uint64_t v3 = rnd();

  inst = constrInstModi(RegId::X16, RegId::X17, v1 & 0x000000000000FFFF);
  thread0->writeReg(RegId::X16, v2);
  thread0->writeReg(RegId::X17, v3);
  // Cycles cycle = decodeInst(inst).exe(*archstate, inst);
  // std::cout << "Cycles:" << cycle << std::endl;
  // read_reg() == reg + imm
  EXPECT_EXIT(decodeInst(inst).exe(*archstate, inst), ::testing::ExitedWithCode(2 && "Mod by zero"), ".*");
  // Expect to be empty.
}

/* Testing pos mod pos */
TEST_F(Modi, PosPos) {
  ThreadStatePtr thread0;
  uint8_t tid0 = tstable->getTID();
  thread0 = new ThreadState(tid0, 0, 0, 0);
  tstable->addtoTST(thread0);
  archstate->threadstate = thread0;

  std::mt19937_64 rnd(std::random_device{}());
  uint64_t v1 = static_cast<uint64_t>((static_cast<int64_t>((rnd() << 48) & 0x7FFFFFFFFFFFFFFF)) >> 48);
  v1 = v1 == 0 ? 0x0000000000000001 : v1;
  uint64_t v2 = rnd() & 0x7FFFFFFFFFFFFFFF;
  uint64_t v3 = rnd();

  inst = constrInstModi(RegId::X16, RegId::X17, v1 & 0x000000000000FFFF);
  thread0->writeReg(RegId::X16, v2);
  thread0->writeReg(RegId::X17, v3);
  Cycles cycle = decodeInst(inst).exe(*archstate, inst);
  // std::cout << "Cycles:" << cycle << std::endl;
  //  read_reg() == reg + imm
  EXPECT_EQ(thread0->readReg(RegId::X17), static_cast<uint64_t>((static_cast<int64_t>(v2)) % (static_cast<int64_t>(v1))));
  EXPECT_EQ(thread0->readReg(RegId::X16), v2);
  EXPECT_EQ(cycle, basim::Cycles(1));
  // Expect to be empty.
}

/* Testing pos mod neg */
TEST_F(Modi, PosNeg) {
  ThreadStatePtr thread0;
  uint8_t tid0 = tstable->getTID();
  thread0 = new ThreadState(tid0, 0, 0, 0);
  tstable->addtoTST(thread0);
  archstate->threadstate = thread0;

  std::mt19937_64 rnd(std::random_device{}());
  uint64_t v1 = static_cast<uint64_t>((static_cast<int64_t>((rnd() << 48) | 0x8000000000000000)) >> 48);
  v1 = v1 == 0 ? 0xFFFFFFFFFFFFFFFF : v1;
  uint64_t v2 = rnd() & 0x7FFFFFFFFFFFFFFF;
  uint64_t v3 = rnd();

  inst = constrInstModi(RegId::X16, RegId::X17, v1 & 0x000000000000FFFF);
  thread0->writeReg(RegId::X16, v2);
  thread0->writeReg(RegId::X17, v3);
  Cycles cycle = decodeInst(inst).exe(*archstate, inst);
  // std::cout << "Cycles:" << cycle << std::endl;
  //  read_reg() == reg + imm
  EXPECT_EQ(thread0->readReg(RegId::X17), static_cast<uint64_t>((static_cast<int64_t>(v2)) % (static_cast<int64_t>(v1))));
  EXPECT_EQ(thread0->readReg(RegId::X16), v2);
  EXPECT_EQ(cycle, basim::Cycles(1));
  // Expect to be empty.
}

/* Testing neg mod pos */
TEST_F(Modi, NegPos) {
  ThreadStatePtr thread0;
  uint8_t tid0 = tstable->getTID();
  thread0 = new ThreadState(tid0, 0, 0, 0);
  tstable->addtoTST(thread0);
  archstate->threadstate = thread0;

  std::mt19937_64 rnd(std::random_device{}());
  uint64_t v1 = static_cast<uint64_t>((static_cast<int64_t>((rnd() << 48) & 0x7FFFFFFFFFFFFFFF)) >> 48);
  v1 = v1 == 0 ? 0x0000000000000001 : v1;
  uint64_t v2 = rnd() | 0x8000000000000000;
  uint64_t v3 = rnd();

  inst = constrInstModi(RegId::X16, RegId::X17, v1 & 0x000000000000FFFF);
  thread0->writeReg(RegId::X16, v2);
  thread0->writeReg(RegId::X17, v3);
  Cycles cycle = decodeInst(inst).exe(*archstate, inst);
  // std::cout << "Cycles:" << cycle << std::endl;
  //  read_reg() == reg + imm
  EXPECT_EQ(thread0->readReg(RegId::X17), static_cast<uint64_t>((static_cast<int64_t>(v2)) % (static_cast<int64_t>(v1))));
  EXPECT_EQ(thread0->readReg(RegId::X16), v2);
  EXPECT_EQ(cycle, basim::Cycles(1));
  // Expect to be empty.
}

/* Testing neg mod neg */
TEST_F(Modi, NegNeg) {
  ThreadStatePtr thread0;
  uint8_t tid0 = tstable->getTID();
  thread0 = new ThreadState(tid0, 0, 0, 0);
  tstable->addtoTST(thread0);
  archstate->threadstate = thread0;

  std::mt19937_64 rnd(std::random_device{}());
  uint64_t v1 = static_cast<uint64_t>((static_cast<int64_t>((rnd() << 48) | 0x8000000000000000)) >> 48);
  v1 = v1 == 0 ? 0xFFFFFFFFFFFFFFFF : v1;
  uint64_t v2 = rnd() | 0x8000000000000000;
  uint64_t v3 = rnd();

  inst = constrInstModi(RegId::X16, RegId::X17, v1 & 0x000000000000FFFF);
  thread0->writeReg(RegId::X16, v2);
  thread0->writeReg(RegId::X17, v3);
  Cycles cycle = decodeInst(inst).exe(*archstate, inst);
  // std::cout << "Cycles:" << cycle << std::endl;
  //  read_reg() == reg + imm
  EXPECT_EQ(thread0->readReg(RegId::X17), static_cast<uint64_t>((static_cast<int64_t>(v2)) % (static_cast<int64_t>(v1))));
  EXPECT_EQ(thread0->readReg(RegId::X16), v2);
  EXPECT_EQ(cycle, basim::Cycles(1));
  // Expect to be empty.
}
