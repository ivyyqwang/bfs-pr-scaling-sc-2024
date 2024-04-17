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

class Bneu : public ::testing::Test {
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
TEST_F(Bneu, Random) {
  ThreadStatePtr thread0;
  uint8_t tid0 = tstable->getTID();
  thread0 = new ThreadState(tid0, 0, 0, 0);
  tstable->addtoTST(thread0);
  archstate->threadstate = thread0;

  std::mt19937_64 rnd(std::random_device{}());
  uint64_t v1 = rnd();
  uint64_t v2 = rnd();

  // Mask the number to keep only the lower 12 bits
  uint64_t maskedNum = rnd() & 0xFFF;
  // Check the sign bit and sign-extend if necessary
  if (maskedNum & 0x800) {
    maskedNum |= 0xFFFFFFFFFFFFF000;
  }
  int64_t target = static_cast<int64_t>(maskedNum);

  inst = constrInstBneuBequBgtuBleu(0, RegId::X16, RegId::X17, target & BF_BNEU_TARGETA_MASK, (target >> BF_BNEU_TARGETA_NBITS) & BF_BNEU_TARGETB_MASK);
  thread0->writeReg(RegId::X16, v1);
  thread0->writeReg(RegId::X17, v2);
  Addr exp_uip = archstate->uip;
  Cycles cycle = decodeInst(inst).exe(*archstate, inst);
  // std::cout << "Cycles:" << cycle << std::endl;
  //  read_reg() == reg + imm
  if (v1 != v2)
    exp_uip = exp_uip + target;
  else
    exp_uip += 4;
  EXPECT_EQ(archstate->uip, exp_uip);
  // Expect to be empty.
}

/* Testing for branch taken */
TEST_F(Bneu, Taken) {
  ThreadStatePtr thread0;
  uint8_t tid0 = tstable->getTID();
  thread0 = new ThreadState(tid0, 0, 0, 0);
  tstable->addtoTST(thread0);
  archstate->threadstate = thread0;

  std::mt19937_64 rnd(std::random_device{}());
  uint64_t v1 = 20;
  uint64_t v2 = 25;

  // Mask the number to keep only the lower 12 bits
  uint64_t maskedNum = rnd() & 0xFFF;
  // Check the sign bit and sign-extend if necessary
  if (maskedNum & 0x800) {
    maskedNum |= 0xFFFFFFFFFFFFF000;
  }
  int64_t target = static_cast<int64_t>(maskedNum);

  inst = constrInstBneuBequBgtuBleu(0, RegId::X16, RegId::X17, target & BF_BNEU_TARGETA_MASK, (target >> BF_BNEU_TARGETA_NBITS) & BF_BNEU_TARGETB_MASK);
  thread0->writeReg(RegId::X16, v1);
  thread0->writeReg(RegId::X17, v2);
  Addr exp_uip = archstate->uip;
  Cycles cycle = decodeInst(inst).exe(*archstate, inst);
  // std::cout << "Cycles:" << cycle << std::endl;
  //  read_reg() == reg + imm
  exp_uip = exp_uip + target;
  EXPECT_EQ(archstate->uip, exp_uip);
  // Expect to be empty.
}

/* Testing for branch not taken */

TEST_F(Bneu, NotTaken) {
  ThreadStatePtr thread0;
  uint8_t tid0 = tstable->getTID();
  thread0 = new ThreadState(tid0, 0, 0, 0);
  tstable->addtoTST(thread0);
  archstate->threadstate = thread0;

  std::mt19937_64 rnd(std::random_device{}());
  uint64_t v1 = 25;
  uint64_t v2 = 25;

  // Mask the number to keep only the lower 12 bits
  uint64_t maskedNum = rnd() & 0xFFF;
  // Check the sign bit and sign-extend if necessary
  if (maskedNum & 0x800) {
    maskedNum |= 0xFFFFFFFFFFFFF000;
  }
  int64_t target = static_cast<int64_t>(maskedNum);

  inst = constrInstBneuBequBgtuBleu(0, RegId::X16, RegId::X17, target & BF_BNEU_TARGETA_MASK, (target >> BF_BNEU_TARGETA_NBITS) & BF_BNEU_TARGETB_MASK);
  thread0->writeReg(RegId::X16, v1);
  thread0->writeReg(RegId::X17, v2);
  Addr exp_uip = archstate->uip;
  Cycles cycle = decodeInst(inst).exe(*archstate, inst);
  // std::cout << "Cycles:" << cycle << std::endl;
  //  read_reg() == reg + imm
  exp_uip += 4;
  EXPECT_EQ(archstate->uip, exp_uip);
  // Expect to be empty.
}