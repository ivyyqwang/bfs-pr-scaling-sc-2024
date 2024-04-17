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

class Bcpyol : public ::testing::Test {
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
TEST_F(Bcpyol, Random) {
  ThreadStatePtr thread0;
  uint8_t tid0 = tstable->getTID();
  thread0 = new ThreadState(tid0, 0, 0, 0);
  tstable->addtoTST(thread0);
  archstate->threadstate = thread0;
  auto op = Operands(10);
  thread0->writeOperands(op);

  std::mt19937_64 rnd(std::random_device{}());
  uint64_t v16 = ((rnd() << 48) >> 51) << 3;
  v16 = v16 > (65536 - 8 * 32) ? (65536 - 8 * 32) : v16;
  uint64_t v17 = (rnd() << 58) >> 58;
  v17 = v17 > 40 ? (v17 - 40) : v17;
  uint64_t v18 = (rnd() << 59) >> 59;
  uint64_t v19 = rnd();
  uint64_t v20 = rnd();
  uint64_t v21 = rnd();
  uint64_t v22 = rnd();
  uint64_t v23 = rnd();
  uint64_t v24 = rnd();
  uint64_t v25 = rnd();
  uint64_t v26 = rnd();
  uint64_t v27 = rnd();
  uint64_t v28 = rnd();
  uint64_t v29 = rnd();
  uint64_t v30 = rnd();
  uint64_t v31 = rnd();

  inst = constrInstBcpyol(static_cast<basim::RegId>(v18), RegId::X16, RegId::X17);
  thread0->writeReg(RegId::X16, v16);
  thread0->writeReg(RegId::X17, v17);
  thread0->writeReg(RegId::X18, v18);
  thread0->writeReg(RegId::X19, v19);
  thread0->writeReg(RegId::X20, v20);
  thread0->writeReg(RegId::X21, v21);
  thread0->writeReg(RegId::X22, v22);
  thread0->writeReg(RegId::X23, v23);
  thread0->writeReg(RegId::X24, v24);
  thread0->writeReg(RegId::X25, v25);
  thread0->writeReg(RegId::X26, v26);
  thread0->writeReg(RegId::X27, v27);
  thread0->writeReg(RegId::X28, v28);
  thread0->writeReg(RegId::X29, v29);
  thread0->writeReg(RegId::X30, v30);
  thread0->writeReg(RegId::X31, v31);
  Cycles cycle = decodeInst(inst).exe(*archstate, inst);
  // std::cout << "Cycles:" << cycle << std::endl;
  //  read_reg() == reg + imm

  EXPECT_EQ(thread0->readReg(RegId::X16), v16);
  EXPECT_EQ(thread0->readReg(RegId::X17), v17);
  EXPECT_EQ(thread0->readReg(RegId::X18), v18);
  EXPECT_EQ(thread0->readReg(RegId::X19), v19);
  EXPECT_EQ(thread0->readReg(RegId::X20), v20);
  EXPECT_EQ(thread0->readReg(RegId::X21), v21);
  EXPECT_EQ(thread0->readReg(RegId::X22), v22);
  EXPECT_EQ(thread0->readReg(RegId::X23), v23);
  EXPECT_EQ(thread0->readReg(RegId::X24), v24);
  EXPECT_EQ(thread0->readReg(RegId::X25), v25);
  EXPECT_EQ(thread0->readReg(RegId::X26), v26);
  EXPECT_EQ(thread0->readReg(RegId::X27), v27);
  EXPECT_EQ(thread0->readReg(RegId::X28), v28);
  EXPECT_EQ(thread0->readReg(RegId::X29), v29);
  EXPECT_EQ(thread0->readReg(RegId::X30), v30);
  EXPECT_EQ(thread0->readReg(RegId::X31), v31);

  for (uint8_t i = v18; (i < (v18 + v17)) && (i < 32); i++) {
    EXPECT_EQ(thread0->readReg(static_cast<basim::RegId>(i)), spd->readWord(v16 + 8 * (i - v18)));
  }
  // Expect to be empty.
}

/* Testing with out of bound */
TEST_F(Bcpyol, OutOfBound) {
  ThreadStatePtr thread0;
  uint8_t tid0 = tstable->getTID();
  thread0 = new ThreadState(tid0, 0, 0, 0);
  tstable->addtoTST(thread0);
  archstate->threadstate = thread0;
  auto op = Operands(10);
  thread0->writeOperands(op);

  std::mt19937_64 rnd(std::random_device{}());
  uint64_t v16 = ((rnd() << 48) >> 51) << 3;
  v16 = v16 > (65536 - 8 * 32) ? (65536 - 8 * 32) : v16;
  uint64_t v17 = (rnd() << 58) >> 58;
  v17 = v17 < 32 ? 32 : v17;
  uint64_t v18 = (rnd() << 59) >> 59;
  uint64_t v19 = rnd();
  uint64_t v20 = rnd();
  uint64_t v21 = rnd();
  uint64_t v22 = rnd();
  uint64_t v23 = rnd();
  uint64_t v24 = rnd();
  uint64_t v25 = rnd();
  uint64_t v26 = rnd();
  uint64_t v27 = rnd();
  uint64_t v28 = rnd();
  uint64_t v29 = rnd();
  uint64_t v30 = rnd();
  uint64_t v31 = rnd();

  inst = constrInstBcpyol(static_cast<basim::RegId>(v18), RegId::X16, RegId::X17);
  thread0->writeReg(RegId::X16, v16);
  thread0->writeReg(RegId::X17, v17);
  thread0->writeReg(RegId::X18, v18);
  thread0->writeReg(RegId::X19, v19);
  thread0->writeReg(RegId::X20, v20);
  thread0->writeReg(RegId::X21, v21);
  thread0->writeReg(RegId::X22, v22);
  thread0->writeReg(RegId::X23, v23);
  thread0->writeReg(RegId::X24, v24);
  thread0->writeReg(RegId::X25, v25);
  thread0->writeReg(RegId::X26, v26);
  thread0->writeReg(RegId::X27, v27);
  thread0->writeReg(RegId::X28, v28);
  thread0->writeReg(RegId::X29, v29);
  thread0->writeReg(RegId::X30, v30);
  thread0->writeReg(RegId::X31, v31);
  Cycles cycle = decodeInst(inst).exe(*archstate, inst);
  // std::cout << "Cycles:" << cycle << std::endl;
  //  read_reg() == reg + imm

  EXPECT_EQ(thread0->readReg(RegId::X16), v16);
  EXPECT_EQ(thread0->readReg(RegId::X17), v17);
  EXPECT_EQ(thread0->readReg(RegId::X18), v18);
  EXPECT_EQ(thread0->readReg(RegId::X19), v19);
  EXPECT_EQ(thread0->readReg(RegId::X20), v20);
  EXPECT_EQ(thread0->readReg(RegId::X21), v21);
  EXPECT_EQ(thread0->readReg(RegId::X22), v22);
  EXPECT_EQ(thread0->readReg(RegId::X23), v23);
  EXPECT_EQ(thread0->readReg(RegId::X24), v24);
  EXPECT_EQ(thread0->readReg(RegId::X25), v25);
  EXPECT_EQ(thread0->readReg(RegId::X26), v26);
  EXPECT_EQ(thread0->readReg(RegId::X27), v27);
  EXPECT_EQ(thread0->readReg(RegId::X28), v28);
  EXPECT_EQ(thread0->readReg(RegId::X29), v29);
  EXPECT_EQ(thread0->readReg(RegId::X30), v30);
  EXPECT_EQ(thread0->readReg(RegId::X31), v31);

  for (uint8_t i = v18; (i < (v18 + v17)) && (i < 32); i++) {
    EXPECT_EQ(thread0->readReg(static_cast<basim::RegId>(i)), spd->readWord(v16 + 8 * (i - v18)));
  }
  // Expect to be empty.
}

/* Testing with all */
TEST_F(Bcpyol, All) {
  ThreadStatePtr thread0;
  uint8_t tid0 = tstable->getTID();
  thread0 = new ThreadState(tid0, 0, 0, 0);
  tstable->addtoTST(thread0);
  archstate->threadstate = thread0;
  auto op = Operands(10);
  thread0->writeOperands(op);

  std::mt19937_64 rnd(std::random_device{}());
  uint64_t v16 = ((rnd() << 48) >> 51) << 3;
  v16 = v16 > (65536 - 8 * 32) ? (65536 - 8 * 32) : v16;
  uint64_t v17 = 32;
  uint64_t v18 = rnd();
  uint64_t v19 = rnd();
  uint64_t v20 = rnd();
  uint64_t v21 = rnd();
  uint64_t v22 = rnd();
  uint64_t v23 = rnd();
  uint64_t v24 = rnd();
  uint64_t v25 = rnd();
  uint64_t v26 = rnd();
  uint64_t v27 = rnd();
  uint64_t v28 = rnd();
  uint64_t v29 = rnd();
  uint64_t v30 = rnd();
  uint64_t v31 = rnd();

  inst = constrInstBcpyol(RegId::X0, RegId::X16, RegId::X17);
  thread0->writeReg(RegId::X16, v16);
  thread0->writeReg(RegId::X17, v17);
  thread0->writeReg(RegId::X18, v18);
  thread0->writeReg(RegId::X19, v19);
  thread0->writeReg(RegId::X20, v20);
  thread0->writeReg(RegId::X21, v21);
  thread0->writeReg(RegId::X22, v22);
  thread0->writeReg(RegId::X23, v23);
  thread0->writeReg(RegId::X24, v24);
  thread0->writeReg(RegId::X25, v25);
  thread0->writeReg(RegId::X26, v26);
  thread0->writeReg(RegId::X27, v27);
  thread0->writeReg(RegId::X28, v28);
  thread0->writeReg(RegId::X29, v29);
  thread0->writeReg(RegId::X30, v30);
  thread0->writeReg(RegId::X31, v31);
  Cycles cycle = decodeInst(inst).exe(*archstate, inst);
  // std::cout << "Cycles:" << cycle << std::endl;
  //  read_reg() == reg + imm

  EXPECT_EQ(thread0->readReg(RegId::X16), v16);
  EXPECT_EQ(thread0->readReg(RegId::X17), v17);
  EXPECT_EQ(thread0->readReg(RegId::X18), v18);
  EXPECT_EQ(thread0->readReg(RegId::X19), v19);
  EXPECT_EQ(thread0->readReg(RegId::X20), v20);
  EXPECT_EQ(thread0->readReg(RegId::X21), v21);
  EXPECT_EQ(thread0->readReg(RegId::X22), v22);
  EXPECT_EQ(thread0->readReg(RegId::X23), v23);
  EXPECT_EQ(thread0->readReg(RegId::X24), v24);
  EXPECT_EQ(thread0->readReg(RegId::X25), v25);
  EXPECT_EQ(thread0->readReg(RegId::X26), v26);
  EXPECT_EQ(thread0->readReg(RegId::X27), v27);
  EXPECT_EQ(thread0->readReg(RegId::X28), v28);
  EXPECT_EQ(thread0->readReg(RegId::X29), v29);
  EXPECT_EQ(thread0->readReg(RegId::X30), v30);
  EXPECT_EQ(thread0->readReg(RegId::X31), v31);

  EXPECT_EQ(thread0->readReg(RegId::X0), spd->readWord(v16 + 8 * 0));
  EXPECT_EQ(thread0->readReg(RegId::X1), spd->readWord(v16 + 8 * 1));
  EXPECT_EQ(thread0->readReg(RegId::X2), spd->readWord(v16 + 8 * 2));
  EXPECT_EQ(thread0->readReg(RegId::X3), spd->readWord(v16 + 8 * 3));
  EXPECT_EQ(thread0->readReg(RegId::X4), spd->readWord(v16 + 8 * 4));
  EXPECT_EQ(thread0->readReg(RegId::X5), spd->readWord(v16 + 8 * 5));
  EXPECT_EQ(thread0->readReg(RegId::X6), spd->readWord(v16 + 8 * 6));
  EXPECT_EQ(thread0->readReg(RegId::X7), spd->readWord(v16 + 8 * 7));
  EXPECT_EQ(thread0->readReg(RegId::X8), spd->readWord(v16 + 8 * 8));
  EXPECT_EQ(thread0->readReg(RegId::X9), spd->readWord(v16 + 8 * 9));
  EXPECT_EQ(thread0->readReg(RegId::X10), spd->readWord(v16 + 8 * 10));
  EXPECT_EQ(thread0->readReg(RegId::X11), spd->readWord(v16 + 8 * 11));
  EXPECT_EQ(thread0->readReg(RegId::X12), spd->readWord(v16 + 8 * 12));
  EXPECT_EQ(thread0->readReg(RegId::X13), spd->readWord(v16 + 8 * 13));
  EXPECT_EQ(thread0->readReg(RegId::X14), spd->readWord(v16 + 8 * 14));
  EXPECT_EQ(thread0->readReg(RegId::X15), spd->readWord(v16 + 8 * 15));
  EXPECT_EQ(thread0->readReg(RegId::X16), spd->readWord(v16 + 8 * 16));
  EXPECT_EQ(thread0->readReg(RegId::X17), spd->readWord(v16 + 8 * 17));
  EXPECT_EQ(thread0->readReg(RegId::X18), spd->readWord(v16 + 8 * 18));
  EXPECT_EQ(thread0->readReg(RegId::X19), spd->readWord(v16 + 8 * 19));
  EXPECT_EQ(thread0->readReg(RegId::X20), spd->readWord(v16 + 8 * 20));
  EXPECT_EQ(thread0->readReg(RegId::X21), spd->readWord(v16 + 8 * 21));
  EXPECT_EQ(thread0->readReg(RegId::X22), spd->readWord(v16 + 8 * 22));
  EXPECT_EQ(thread0->readReg(RegId::X23), spd->readWord(v16 + 8 * 23));
  EXPECT_EQ(thread0->readReg(RegId::X24), spd->readWord(v16 + 8 * 24));
  EXPECT_EQ(thread0->readReg(RegId::X25), spd->readWord(v16 + 8 * 25));
  EXPECT_EQ(thread0->readReg(RegId::X26), spd->readWord(v16 + 8 * 26));
  EXPECT_EQ(thread0->readReg(RegId::X27), spd->readWord(v16 + 8 * 27));
  EXPECT_EQ(thread0->readReg(RegId::X28), spd->readWord(v16 + 8 * 28));
  EXPECT_EQ(thread0->readReg(RegId::X29), spd->readWord(v16 + 8 * 29));
  EXPECT_EQ(thread0->readReg(RegId::X30), spd->readWord(v16 + 8 * 30));
  EXPECT_EQ(thread0->readReg(RegId::X31), spd->readWord(v16 + 8 * 31));
  // Expect to be empty.
}

/* Testing with out of bound write */
TEST_F(Bcpyol, OutOfBoundWrite) {
  ThreadStatePtr thread0;
  uint8_t tid0 = tstable->getTID();
  thread0 = new ThreadState(tid0, 0, 0, 0);
  tstable->addtoTST(thread0);
  archstate->threadstate = thread0;
  auto op = Operands(10);
  thread0->writeOperands(op);

  std::mt19937_64 rnd(std::random_device{}());
  uint64_t v16 = ((rnd() << 48) >> 51) << 3;
  v16 = v16 > (65536 - 2 * 8 * 32) ? (65536 - 2 * 8 * 32) : v16;
  uint64_t v17 = 32;
  uint64_t v18 = rnd();
  uint64_t v19 = rnd();
  uint64_t v20 = rnd();
  uint64_t v21 = rnd();
  uint64_t v22 = rnd();
  uint64_t v23 = rnd();
  uint64_t v24 = rnd();
  uint64_t v25 = rnd();
  uint64_t v26 = rnd();
  uint64_t v27 = rnd();
  uint64_t v28 = rnd();
  uint64_t v29 = rnd();
  uint64_t v30 = rnd();
  uint64_t v31 = rnd();

  uint64_t off = (rnd() << 62) >> 59;

  inst = constrInstBcpyol(RegId::X24, RegId::X16, RegId::X17);
  thread0->writeReg(RegId::X16, v16);
  thread0->writeReg(RegId::X17, 8);
  thread0->writeReg(RegId::X24, 0);
  thread0->writeReg(RegId::X25, 0);
  thread0->writeReg(RegId::X26, 0);
  thread0->writeReg(RegId::X27, 0);
  thread0->writeReg(RegId::X28, 0);
  thread0->writeReg(RegId::X29, 0);
  thread0->writeReg(RegId::X30, 0);
  thread0->writeReg(RegId::X31, 0);
  Cycles cycle = decodeInst(inst).exe(*archstate, inst);
  // std::cout << "Cycles:" << cycle << std::endl;
  //  read_reg() == reg + imm
  inst = constrInstBcpyol(RegId::X24, RegId::X16, RegId::X17);
  thread0->writeReg(RegId::X16, v16 + 8 * 8);
  cycle = decodeInst(inst).exe(*archstate, inst);

  inst = constrInstBcpyol(RegId::X24, RegId::X16, RegId::X17);
  thread0->writeReg(RegId::X16, v16 + 16 * 8);
  cycle = decodeInst(inst).exe(*archstate, inst);

  inst = constrInstBcpyol(RegId::X24, RegId::X16, RegId::X17);
  thread0->writeReg(RegId::X16, v16 + 24 * 8);
  cycle = decodeInst(inst).exe(*archstate, inst);

  inst = constrInstBcpyol(RegId::X24, RegId::X16, RegId::X17);
  thread0->writeReg(RegId::X16, v16 + 32 * 8);
  cycle = decodeInst(inst).exe(*archstate, inst);

  inst = constrInstBcpyol(RegId::X24, RegId::X16, RegId::X17);
  thread0->writeReg(RegId::X16, v16 + 40 * 8);
  cycle = decodeInst(inst).exe(*archstate, inst);

  inst = constrInstBcpyol(RegId::X24, RegId::X16, RegId::X17);
  thread0->writeReg(RegId::X16, v16 + 48 * 8);
  cycle = decodeInst(inst).exe(*archstate, inst);

  inst = constrInstBcpyol(RegId::X24, RegId::X16, RegId::X17);
  thread0->writeReg(RegId::X16, v16 + 56 * 8);
  cycle = decodeInst(inst).exe(*archstate, inst);

  inst = constrInstBcpyol(RegId::X0, RegId::X16, RegId::X17);
  thread0->writeReg(RegId::X16, v16 + off);
  thread0->writeReg(RegId::X17, v17);
  thread0->writeReg(RegId::X18, v18);
  thread0->writeReg(RegId::X19, v19);
  thread0->writeReg(RegId::X20, v20);
  thread0->writeReg(RegId::X21, v21);
  thread0->writeReg(RegId::X22, v22);
  thread0->writeReg(RegId::X23, v23);
  thread0->writeReg(RegId::X24, v24);
  thread0->writeReg(RegId::X25, v25);
  thread0->writeReg(RegId::X26, v26);
  thread0->writeReg(RegId::X27, v27);
  thread0->writeReg(RegId::X28, v28);
  thread0->writeReg(RegId::X29, v29);
  thread0->writeReg(RegId::X30, v30);
  thread0->writeReg(RegId::X31, v31);
  cycle = decodeInst(inst).exe(*archstate, inst);

  EXPECT_EQ(thread0->readReg(RegId::X16), v16 + off);
  EXPECT_EQ(thread0->readReg(RegId::X17), v17);
  EXPECT_EQ(thread0->readReg(RegId::X18), v18);
  EXPECT_EQ(thread0->readReg(RegId::X19), v19);
  EXPECT_EQ(thread0->readReg(RegId::X20), v20);
  EXPECT_EQ(thread0->readReg(RegId::X21), v21);
  EXPECT_EQ(thread0->readReg(RegId::X22), v22);
  EXPECT_EQ(thread0->readReg(RegId::X23), v23);
  EXPECT_EQ(thread0->readReg(RegId::X24), v24);
  EXPECT_EQ(thread0->readReg(RegId::X25), v25);
  EXPECT_EQ(thread0->readReg(RegId::X26), v26);
  EXPECT_EQ(thread0->readReg(RegId::X27), v27);
  EXPECT_EQ(thread0->readReg(RegId::X28), v28);
  EXPECT_EQ(thread0->readReg(RegId::X29), v29);
  EXPECT_EQ(thread0->readReg(RegId::X30), v30);
  EXPECT_EQ(thread0->readReg(RegId::X31), v31);

  for (uint64_t i = 0; i < off; i += 8) {
    EXPECT_EQ(spd->readWord(v16 + i), 0);
  }
  EXPECT_EQ(thread0->readReg(RegId::X0), spd->readWord(v16 + off + 8 * 0));
  EXPECT_EQ(thread0->readReg(RegId::X1), spd->readWord(v16 + off + 8 * 1));
  EXPECT_EQ(thread0->readReg(RegId::X2), spd->readWord(v16 + off + 8 * 2));
  EXPECT_EQ(thread0->readReg(RegId::X3), spd->readWord(v16 + off + 8 * 3));
  EXPECT_EQ(thread0->readReg(RegId::X4), spd->readWord(v16 + off + 8 * 4));
  EXPECT_EQ(thread0->readReg(RegId::X5), spd->readWord(v16 + off + 8 * 5));
  EXPECT_EQ(thread0->readReg(RegId::X6), spd->readWord(v16 + off + 8 * 6));
  EXPECT_EQ(thread0->readReg(RegId::X7), spd->readWord(v16 + off + 8 * 7));
  EXPECT_EQ(thread0->readReg(RegId::X8), spd->readWord(v16 + off + 8 * 8));
  EXPECT_EQ(thread0->readReg(RegId::X9), spd->readWord(v16 + off + 8 * 9));
  EXPECT_EQ(thread0->readReg(RegId::X10), spd->readWord(v16 + off + 8 * 10));
  EXPECT_EQ(thread0->readReg(RegId::X11), spd->readWord(v16 + off + 8 * 11));
  EXPECT_EQ(thread0->readReg(RegId::X12), spd->readWord(v16 + off + 8 * 12));
  EXPECT_EQ(thread0->readReg(RegId::X13), spd->readWord(v16 + off + 8 * 13));
  EXPECT_EQ(thread0->readReg(RegId::X14), spd->readWord(v16 + off + 8 * 14));
  EXPECT_EQ(thread0->readReg(RegId::X15), spd->readWord(v16 + off + 8 * 15));
  EXPECT_EQ(thread0->readReg(RegId::X16), spd->readWord(v16 + off + 8 * 16));
  EXPECT_EQ(thread0->readReg(RegId::X17), spd->readWord(v16 + off + 8 * 17));
  EXPECT_EQ(thread0->readReg(RegId::X18), spd->readWord(v16 + off + 8 * 18));
  EXPECT_EQ(thread0->readReg(RegId::X19), spd->readWord(v16 + off + 8 * 19));
  EXPECT_EQ(thread0->readReg(RegId::X20), spd->readWord(v16 + off + 8 * 20));
  EXPECT_EQ(thread0->readReg(RegId::X21), spd->readWord(v16 + off + 8 * 21));
  EXPECT_EQ(thread0->readReg(RegId::X22), spd->readWord(v16 + off + 8 * 22));
  EXPECT_EQ(thread0->readReg(RegId::X23), spd->readWord(v16 + off + 8 * 23));
  EXPECT_EQ(thread0->readReg(RegId::X24), spd->readWord(v16 + off + 8 * 24));
  EXPECT_EQ(thread0->readReg(RegId::X25), spd->readWord(v16 + off + 8 * 25));
  EXPECT_EQ(thread0->readReg(RegId::X26), spd->readWord(v16 + off + 8 * 26));
  EXPECT_EQ(thread0->readReg(RegId::X27), spd->readWord(v16 + off + 8 * 27));
  EXPECT_EQ(thread0->readReg(RegId::X28), spd->readWord(v16 + off + 8 * 28));
  EXPECT_EQ(thread0->readReg(RegId::X29), spd->readWord(v16 + off + 8 * 29));
  EXPECT_EQ(thread0->readReg(RegId::X30), spd->readWord(v16 + off + 8 * 30));
  EXPECT_EQ(thread0->readReg(RegId::X31), spd->readWord(v16 + off + 8 * 31));
  for (uint64_t i = off + 8 * 32; i < 8 * 64; i += 8) {
    EXPECT_EQ(spd->readWord(v16 + i), 0);
  }
  // Expect to be empty.
}
