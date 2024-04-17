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

class Ev : public ::testing::Test {
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
TEST_F(Ev, Evi_random) {
  ThreadStatePtr thread0;
  uint8_t tid0 = tstable->getTID();
  thread0 = new ThreadState(tid0, 0, 0, 0);
  tstable->addtoTST(thread0);
  archstate->threadstate = thread0;

  std::mt19937_64 rnd(std::random_device{}());
  uint64_t v1 = rnd();
  uint64_t selarray[4] = {0x8, 0x4, 0x2, 0x1};
  uint64_t selbits[4] = {0xFFF, 0xFF, 0x7, 0xFFF};
  uint64_t selidx = (rnd() & 0x3);
  uint64_t sel = selarray[selidx];
  uint64_t imm = (rnd() & selbits[selidx]);
  printf("sel:%lu, imm:%lu\n", sel, imm);


  inst = constrInstEvi(RegId::X16, RegId::X17, imm, sel);
  thread0->writeReg(RegId::X16, v1);
  Cycles cycle = decodeInst(inst).exe(*archstate, inst);
  uint64_t invmask[4] = {0x00000000FFFFFFFF, 0xFFFFFFFF00FFFFFF, 0xFFFFFFFFFF8FFFFF, 0xFFFFFFFFFFF00000};
  uint64_t posmask[4] = {0xFFFFFFFF00000000, 0x00000000FF000000, 0x0000000000700000, 0x00000000000FFFFF};
  uint64_t pos[4]     = {32, 24, 20, 0};
  v1 = (v1 & invmask[selidx]) | ((imm << pos[selidx]) & posmask[selidx]);
  EXPECT_EQ(thread0->readReg(RegId::X17), v1);
}

TEST_F(Ev, Evi) {
  ThreadStatePtr thread0;
  uint8_t tid0 = tstable->getTID();
  thread0 = new ThreadState(tid0, 0, 0, 0);
  tstable->addtoTST(thread0);
  archstate->threadstate = thread0;

  std::mt19937_64 rnd(std::random_device{}());
  uint64_t v1 = 10;
  uint64_t selarray[4] = {0x8, 0x4, 0x2, 0x1};
  uint64_t selbits[4] = {0xFFF, 0xFF, 0x7, 0xFFF};
  uint64_t selidx = (rnd() & 0x3);
  uint64_t sel = selarray[selidx];
  uint64_t imm = (20 & selbits[selidx]);
  printf("sel:%lu, imm:%lu\n", sel, imm);


  inst = constrInstEvi(RegId::X16, RegId::X17, imm, sel);
  thread0->writeReg(RegId::X16, v1);
  Cycles cycle = decodeInst(inst).exe(*archstate, inst);
  uint64_t invmask[4] = {0x00000000FFFFFFFF, 0xFFFFFFFF00FFFFFF, 0xFFFFFFFFFF8FFFFF, 0xFFFFFFFFFFF00000};
  uint64_t posmask[4] = {0xFFFFFFFF00000000, 0x00000000FF000000, 0x0000000000700000, 0x00000000000FFFFF};
  uint64_t pos[4]     = {32, 24, 20, 0};
  v1 = (v1 & invmask[selidx]) | ((imm << pos[selidx]) & posmask[selidx]);
  EXPECT_EQ(thread0->readReg(RegId::X17), v1);
}

TEST_F(Ev, Evii_random) {
  ThreadStatePtr thread0;
  uint8_t tid0 = tstable->getTID();
  thread0 = new ThreadState(tid0, 0, 0, 0);
  tstable->addtoTST(thread0);
  archstate->threadstate = thread0;

  std::mt19937_64 rnd(std::random_device{}());
  uint64_t v1 = rnd();
  thread0->writeEvent(v1);
  uint64_t selarray[6] = {0x3, 0x5, 0x9, 0x6, 0xA, 0xC};
  uint64_t selbits1[6] = {0x1F, 0x1F, 0x1F, 0x7, 0x7, 0x1F};
  uint64_t selbits2[6] = {0x7, 0xFF, 0xFFF, 0xFF, 0xFFF, 0xFFF};
  uint64_t selidx = (rnd() & 0x7);
  selidx = selidx > 5 ? 0: selidx;
  uint64_t sel = selarray[selidx];
  uint64_t v2 = (rnd() & selbits1[selidx]);
  uint64_t v3 = (rnd() & selbits2[selidx]);
  printf("sel:%lu, v2:%lu, v3:%lu\n", sel, v2, v3);

  inst = constrInstEvii(RegId::X17, v2, v3, sel);
  Cycles cycle = decodeInst(inst).exe(*archstate, inst);

  uint64_t invmask[4] = {0xFFFFFFFFFFF00000, 0xFFFFFFFFFF8FFFFF, 0xFFFFFFFF00FFFFFF, 0x00000000FFFFFFFF};
  uint64_t posmask[4] = {0x00000000000FFFFF, 0x0000000000700000, 0x00000000FF000000, 0xFFFFFFFF00000000};
  uint64_t pos[4]     = {0, 20, 24, 32};
  bool first = true;
  for(auto i = 0; i < 4; i++){
    if(((sel >> i) & 0x1)){
      if(first){
        v1 = (v1 & invmask[i]) | ((v2 << pos[i]) & posmask[i]);
        first = false;
        printf("v1:%lu, first:%d\n", v1, first);
      }else{
        v1 = (v1 & invmask[i]) | ((v3 << pos[i]) & posmask[i]);
        printf("v1:%lu, first:%d\n", v1, first);
        break;
      }
    }
  }
  EXPECT_EQ(thread0->readReg(RegId::X17), v1);
}

TEST_F(Ev, Evl_random) {
  ThreadStatePtr thread0;
  uint8_t tid0 = tstable->getTID();
  thread0 = new ThreadState(tid0, 0, 0, 0);
  tstable->addtoTST(thread0);
  archstate->threadstate = thread0;

  std::mt19937_64 rnd(std::random_device{}());
  uint64_t v1 = rnd();
  thread0->writeEvent(v1);
  thread0->writeReg(RegId::X17, v1);
  uint64_t imm = (rnd() & 0xFFFFF);
  printf("ev:%lu, imm:%lu\n", v1, imm);
  
  inst = constrInstEvlb(RegId::X17, imm);
  Cycles cycle = decodeInst(inst).exe(*archstate, inst);
  v1 = (v1 & 0xFFFFFFFFFFF00000) | (imm & 0xFFFFF);
  EXPECT_EQ(thread0->readReg(RegId::X17), v1);
  // Expect to be empty.
}

TEST_F(Ev, Evl) {
  ThreadStatePtr thread0;
  uint8_t tid0 = tstable->getTID();
  thread0 = new ThreadState(tid0, 0, 0, 0);
  tstable->addtoTST(thread0);
  archstate->threadstate = thread0;

  std::mt19937_64 rnd(std::random_device{}());
  uint64_t v1 = 25;
  thread0->writeEvent(v1);
  uint64_t imm = (7 & 0xFFFFF);
  printf("ev:%lu, imm:%lu\n", v1, imm);
  
  inst = constrInstEvlb(RegId::X17, imm);
  Cycles cycle = decodeInst(inst).exe(*archstate, inst);
  v1 = (v1 & 0xFFFFFFFFFFF00000) | (imm & 0xFFFFF);
  EXPECT_EQ(thread0->readReg(RegId::X17), v1);
}

TEST_F(Ev, Ev_random) {
  ThreadStatePtr thread0;
  uint8_t tid0 = tstable->getTID();
  thread0 = new ThreadState(tid0, 0, 0, 0);
  tstable->addtoTST(thread0);
  archstate->threadstate = thread0;

  std::mt19937_64 rnd(std::random_device{}());
  uint64_t v1 = rnd();
  uint64_t selarray[6] = {0x3, 0x5, 0x9, 0x6, 0xA, 0xC};
  uint64_t selbits1[6] = {0x1F, 0x1F, 0x1F, 0x7, 0x7, 0x1F};
  uint64_t selbits2[6] = {0x7, 0xFF, 0xFFF, 0xFF, 0xFFF, 0xFFF};
  //uint64_t selbits1[6] = {0xFFFFF, 0xFFFFF, 0xFFFFF, 0x7, 0x7, 0xFF};
  //uint64_t selbits2[6] = {0x7, 0xFF, 0xFFFFFFFF, 0xFF, 0xFFFFFFFF, 0xFFFFFFFF};
  uint64_t selidx = (rnd() & 0x7);
  selidx = selidx > 5 ? 0: selidx;
  uint64_t sel = selarray[selidx];
  uint64_t v2 = (rnd() & selbits1[selidx]);
  uint64_t v3 = (rnd() & selbits2[selidx]);
  printf("sel:%lu, v2:%lu, v3:%lu\n", sel, v2, v3);

  inst = constrInstEv(RegId::X16, RegId::X17, RegId::X18, RegId::X19, sel);
  thread0->writeReg(RegId::X16, v1);
  thread0->writeReg(RegId::X18, v2);
  thread0->writeReg(RegId::X19, v3);
  Cycles cycle = decodeInst(inst).exe(*archstate, inst);
  uint64_t invmask[4] = {0xFFFFFFFFFFF00000, 0xFFFFFFFFFF8FFFFF, 0xFFFFFFFF00FFFFFF, 0x00000000FFFFFFFF};
  uint64_t posmask[4] = {0x00000000000FFFFF, 0x0000000000700000, 0x00000000FF000000, 0xFFFFFFFF00000000};
  uint64_t pos[4]     = {0, 20, 24, 32};
  bool first = true;
  for(auto i = 0; i < 4; i++){
    if(((sel >> i) & 0x1)){
      if(first){
        v1 = (v1 & invmask[i]) | ((v2 << pos[i]) & posmask[i]);
        first = false;
        printf("v1:%lu, first:%d\n", v1, first);
      }else{
        v1 = (v1 & invmask[i]) | ((v3 << pos[i]) & posmask[i]);
        printf("v1:%lu, first:%d\n", v1, first);
        break;
      }
    }
  }

  EXPECT_EQ(thread0->readReg(RegId::X17), v1);
}

TEST_F(Ev, Ev) {
  ThreadStatePtr thread0;
  uint8_t tid0 = tstable->getTID();
  thread0 = new ThreadState(tid0, 0, 0, 0);
  tstable->addtoTST(thread0);
  archstate->threadstate = thread0;

  std::mt19937_64 rnd(std::random_device{}());
  uint64_t v1 = 70;
  thread0->writeEvent(v1);
  uint64_t selarray[6] = {0x3, 0x5, 0x9, 0x6, 0xA, 0xC};
  //uint64_t selbits1[6] = {0x1F, 0x1F, 0x1F, 0x7, 0x7, 0x1F};
  //uint64_t selbits2[6] = {0x7, 0xFF, 0xFFF, 0xFF, 0xFFF, 0xFFF};
  uint64_t selbits1[6] = {0xFFFFF, 0xFFFFF, 0xFFFFF, 0x7, 0x7, 0xFF};
  uint64_t selbits2[6] = {0x7, 0xFF, 0xFFFFFFFF, 0xFF, 0xFFFFFFFF, 0xFFFFFFFF};
  uint64_t selidx = (rnd() & 0x7);
  selidx = selidx > 5 ? 0: selidx;
  uint64_t sel = selarray[selidx];
  uint64_t v2 = (3 & selbits1[selidx]);
  uint64_t v3 = (5 & selbits2[selidx]);

  inst = constrInstEv(RegId::X16, RegId::X17, RegId::X18, RegId::X19, sel);
  thread0->writeReg(RegId::X16, v1);
  thread0->writeReg(RegId::X18, v2);
  thread0->writeReg(RegId::X19, v3);
  Cycles cycle = decodeInst(inst).exe(*archstate, inst);

  uint64_t invmask[4] = {0xFFFFFFFFFFF00000, 0xFFFFFFFFFF8FFFFF, 0xFFFFFFFF00FFFFFF, 0x00000000FFFFFFFF};
  uint64_t posmask[4] = {0x00000000000FFFFF, 0x0000000000700000, 0x00000000FF000000, 0xFFFFFFFF00000000};
  uint64_t pos[4]     = {0, 20, 24, 32};
  bool first = true;
  for(auto i = 0; i < 4; i++){
    if(((sel >> i) & 0x1)){
      if(first){
        v1 = (v1 & invmask[i]) | ((v2 << pos[i]) & posmask[i]);
        first = false;
        printf("v1:%lu, first:%d\n", v1, first);
      }else{
        v1 = (v1 & invmask[i]) | ((v3 << pos[i]) & posmask[i]);
        printf("v1:%lu, first:%d\n", v1, first);
        break;
      }
    }
  }
  EXPECT_EQ(thread0->readReg(RegId::X17), v1);
}



