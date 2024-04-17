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

class Hashsb64 : public ::testing::Test {
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
    stbuff = new StreamBuffer(64);
    tstable = new TSTable();
    lanestate = LaneState::NULLSTATE;

    // Add elements to a combined archstate for convenience in instruction execution
    archstate = new ArchState();
    archstate->instmem = instmem;
    archstate->opbuff = opbuff;
    archstate->eventq = eventq;
    archstate->spd = spd;
    archstate->uip = uip;
    archstate->streambuffer = stbuff;
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
  StreamBufferPtr stbuff;
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
uint64_t crc64_helper_hashsb64(uint64_t input) {
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
TEST_F(Hashsb64, Random) {
  ThreadStatePtr thread0;
  uint8_t tid0 = tstable->getTID();
  thread0 = new ThreadState(tid0, 0, 0, 0);
  tstable->addtoTST(thread0);
  archstate->threadstate = thread0;

  std::mt19937_64 rnd(std::random_device{}());
  uint64_t s0 = rnd();
  uint64_t s1 = rnd();
  uint64_t s2 = rnd();
  uint64_t s3 = rnd();
  uint64_t s4 = rnd();
  uint64_t s5 = rnd();
  uint64_t s6 = rnd();
  uint64_t s7 = rnd();

  uint64_t v1 = (rnd() << 55) >> 55;
  v1 = v1 > ((0x0001 << 9) - 64) ? ((0x0001 << 9) - 64) : v1;
  uint64_t v2 = rnd();
  uint64_t v3 = rnd();
  uint64_t v4 = rnd();

  inst = constrInstHashsb64(RegId::X16, RegId::X17);
  thread0->writeReg(RegId::X5, v1);
  stbuff->writeIntoSB(0+8*0, (s0    )&0xFF); stbuff->writeIntoSB(1+8*0, (s0>>8 )&0xFF); stbuff->writeIntoSB(2+8*0, (s0>>16)&0xFF); stbuff->writeIntoSB(3+8*0, (s0>>24)&0xFF);
  stbuff->writeIntoSB(4+8*0, (s0>>32)&0xFF); stbuff->writeIntoSB(5+8*0, (s0>>40)&0xFF); stbuff->writeIntoSB(6+8*0, (s0>>48)&0xFF); stbuff->writeIntoSB(7+8*0, (s0>>56)&0xFF);
  stbuff->writeIntoSB(0+8*1, (s1    )&0xFF); stbuff->writeIntoSB(1+8*1, (s1>>8 )&0xFF); stbuff->writeIntoSB(2+8*1, (s1>>16)&0xFF); stbuff->writeIntoSB(3+8*1, (s1>>24)&0xFF);
  stbuff->writeIntoSB(4+8*1, (s1>>32)&0xFF); stbuff->writeIntoSB(5+8*1, (s1>>40)&0xFF); stbuff->writeIntoSB(6+8*1, (s1>>48)&0xFF); stbuff->writeIntoSB(7+8*1, (s1>>56)&0xFF);
  stbuff->writeIntoSB(0+8*2, (s2    )&0xFF); stbuff->writeIntoSB(1+8*2, (s2>>8 )&0xFF); stbuff->writeIntoSB(2+8*2, (s2>>16)&0xFF); stbuff->writeIntoSB(3+8*2, (s2>>24)&0xFF);
  stbuff->writeIntoSB(4+8*2, (s2>>32)&0xFF); stbuff->writeIntoSB(5+8*2, (s2>>40)&0xFF); stbuff->writeIntoSB(6+8*2, (s2>>48)&0xFF); stbuff->writeIntoSB(7+8*2, (s2>>56)&0xFF);
  stbuff->writeIntoSB(0+8*3, (s3    )&0xFF); stbuff->writeIntoSB(1+8*3, (s3>>8 )&0xFF); stbuff->writeIntoSB(2+8*3, (s3>>16)&0xFF); stbuff->writeIntoSB(3+8*3, (s3>>24)&0xFF);
  stbuff->writeIntoSB(4+8*3, (s3>>32)&0xFF); stbuff->writeIntoSB(5+8*3, (s3>>40)&0xFF); stbuff->writeIntoSB(6+8*3, (s3>>48)&0xFF); stbuff->writeIntoSB(7+8*3, (s3>>56)&0xFF);
  stbuff->writeIntoSB(0+8*4, (s4    )&0xFF); stbuff->writeIntoSB(1+8*4, (s4>>8 )&0xFF); stbuff->writeIntoSB(2+8*4, (s4>>16)&0xFF); stbuff->writeIntoSB(3+8*4, (s4>>24)&0xFF);
  stbuff->writeIntoSB(4+8*4, (s4>>32)&0xFF); stbuff->writeIntoSB(5+8*4, (s4>>40)&0xFF); stbuff->writeIntoSB(6+8*4, (s4>>48)&0xFF); stbuff->writeIntoSB(7+8*4, (s4>>56)&0xFF);
  stbuff->writeIntoSB(0+8*5, (s5    )&0xFF); stbuff->writeIntoSB(1+8*5, (s5>>8 )&0xFF); stbuff->writeIntoSB(2+8*5, (s5>>16)&0xFF); stbuff->writeIntoSB(3+8*5, (s5>>24)&0xFF);
  stbuff->writeIntoSB(4+8*5, (s5>>32)&0xFF); stbuff->writeIntoSB(5+8*5, (s5>>40)&0xFF); stbuff->writeIntoSB(6+8*5, (s5>>48)&0xFF); stbuff->writeIntoSB(7+8*5, (s5>>56)&0xFF);
  stbuff->writeIntoSB(0+8*6, (s6    )&0xFF); stbuff->writeIntoSB(1+8*6, (s6>>8 )&0xFF); stbuff->writeIntoSB(2+8*6, (s6>>16)&0xFF); stbuff->writeIntoSB(3+8*6, (s6>>24)&0xFF);
  stbuff->writeIntoSB(4+8*6, (s6>>32)&0xFF); stbuff->writeIntoSB(5+8*6, (s6>>40)&0xFF); stbuff->writeIntoSB(6+8*6, (s6>>48)&0xFF); stbuff->writeIntoSB(7+8*6, (s6>>56)&0xFF);
  stbuff->writeIntoSB(0+8*7, (s7    )&0xFF); stbuff->writeIntoSB(1+8*7, (s7>>8 )&0xFF); stbuff->writeIntoSB(2+8*7, (s7>>16)&0xFF); stbuff->writeIntoSB(3+8*7, (s7>>24)&0xFF);
  stbuff->writeIntoSB(4+8*7, (s7>>32)&0xFF); stbuff->writeIntoSB(5+8*7, (s7>>40)&0xFF); stbuff->writeIntoSB(6+8*7, (s7>>48)&0xFF); stbuff->writeIntoSB(7+8*7, (s7>>56)&0xFF);

  thread0->writeReg(RegId::X16, v3);
  thread0->writeReg(RegId::X17, v4);
  Cycles cycle = decodeInst(inst).exe(*archstate, inst);
  // std::cout << "Cycles:" << cycle << std::endl;
  //  read_reg() == reg + imm
  EXPECT_EQ(thread0->readReg(RegId::X5), v1);
  EXPECT_EQ(thread0->readReg(RegId::X16), v3);

  EXPECT_EQ((stbuff->getVarSymbol(0  , 8) << 0) | (stbuff->getVarSymbol(0  +8, 8) << 8) | (stbuff->getVarSymbol(0  +16, 8) << 16) | (stbuff->getVarSymbol(0  +24, 8) << 24) | (stbuff->getVarSymbol(0  +32, 8) << 32) | (stbuff->getVarSymbol(0  +40, 8) << 40) | (stbuff->getVarSymbol(0  +48, 8) << 48) | (stbuff->getVarSymbol(0  +56, 8) << 56), s0);
  EXPECT_EQ((stbuff->getVarSymbol(64 , 8) << 0) | (stbuff->getVarSymbol(64 +8, 8) << 8) | (stbuff->getVarSymbol(64 +16, 8) << 16) | (stbuff->getVarSymbol(64 +24, 8) << 24) | (stbuff->getVarSymbol(64 +32, 8) << 32) | (stbuff->getVarSymbol(64 +40, 8) << 40) | (stbuff->getVarSymbol(64 +48, 8) << 48) | (stbuff->getVarSymbol(64 +56, 8) << 56), s1);
  EXPECT_EQ((stbuff->getVarSymbol(128, 8) << 0) | (stbuff->getVarSymbol(128+8, 8) << 8) | (stbuff->getVarSymbol(128+16, 8) << 16) | (stbuff->getVarSymbol(128+24, 8) << 24) | (stbuff->getVarSymbol(128+32, 8) << 32) | (stbuff->getVarSymbol(128+40, 8) << 40) | (stbuff->getVarSymbol(128+48, 8) << 48) | (stbuff->getVarSymbol(128+56, 8) << 56), s2);
  EXPECT_EQ((stbuff->getVarSymbol(192, 8) << 0) | (stbuff->getVarSymbol(192+8, 8) << 8) | (stbuff->getVarSymbol(192+16, 8) << 16) | (stbuff->getVarSymbol(192+24, 8) << 24) | (stbuff->getVarSymbol(192+32, 8) << 32) | (stbuff->getVarSymbol(192+40, 8) << 40) | (stbuff->getVarSymbol(192+48, 8) << 48) | (stbuff->getVarSymbol(192+56, 8) << 56), s3);
  EXPECT_EQ((stbuff->getVarSymbol(256, 8) << 0) | (stbuff->getVarSymbol(256+8, 8) << 8) | (stbuff->getVarSymbol(256+16, 8) << 16) | (stbuff->getVarSymbol(256+24, 8) << 24) | (stbuff->getVarSymbol(256+32, 8) << 32) | (stbuff->getVarSymbol(256+40, 8) << 40) | (stbuff->getVarSymbol(256+48, 8) << 48) | (stbuff->getVarSymbol(256+56, 8) << 56), s4);
  EXPECT_EQ((stbuff->getVarSymbol(320, 8) << 0) | (stbuff->getVarSymbol(320+8, 8) << 8) | (stbuff->getVarSymbol(320+16, 8) << 16) | (stbuff->getVarSymbol(320+24, 8) << 24) | (stbuff->getVarSymbol(320+32, 8) << 32) | (stbuff->getVarSymbol(320+40, 8) << 40) | (stbuff->getVarSymbol(320+48, 8) << 48) | (stbuff->getVarSymbol(320+56, 8) << 56), s5);
  EXPECT_EQ((stbuff->getVarSymbol(384, 8) << 0) | (stbuff->getVarSymbol(384+8, 8) << 8) | (stbuff->getVarSymbol(384+16, 8) << 16) | (stbuff->getVarSymbol(384+24, 8) << 24) | (stbuff->getVarSymbol(384+32, 8) << 32) | (stbuff->getVarSymbol(384+40, 8) << 40) | (stbuff->getVarSymbol(384+48, 8) << 48) | (stbuff->getVarSymbol(384+56, 8) << 56), s6);
  EXPECT_EQ((stbuff->getVarSymbol(448, 8) << 0) | (stbuff->getVarSymbol(448+8, 8) << 8) | (stbuff->getVarSymbol(448+16, 8) << 16) | (stbuff->getVarSymbol(448+24, 8) << 24) | (stbuff->getVarSymbol(448+32, 8) << 32) | (stbuff->getVarSymbol(448+40, 8) << 40) | (stbuff->getVarSymbol(448+48, 8) << 48) | (stbuff->getVarSymbol(448+56, 8) << 56), s7);

  EXPECT_EQ(thread0->readReg(RegId::X17), crc64_helper_hashsb64((stbuff->getVarSymbol(v1, 8) << 0) | (stbuff->getVarSymbol(v1+8, 8) << 8) | (stbuff->getVarSymbol(v1+16, 8) << 16) | (stbuff->getVarSymbol(v1+24, 8) << 24) | (stbuff->getVarSymbol(v1+32, 8) << 32) | (stbuff->getVarSymbol(v1+40, 8) << 40) | (stbuff->getVarSymbol(v1+48, 8) << 48) | (stbuff->getVarSymbol(v1+56, 8) << 56)) + v3);
  EXPECT_EQ(cycle, basim::Cycles(1));
  // Expect to be empty.
}

/* Testing with max value */
TEST_F(Hashsb64, Max) {
  ThreadStatePtr thread0;
  uint8_t tid0 = tstable->getTID();
  thread0 = new ThreadState(tid0, 0, 0, 0);
  tstable->addtoTST(thread0);
  archstate->threadstate = thread0;

  std::mt19937_64 rnd(std::random_device{}());
  uint64_t s0 = 0xFFFFFFFFFFFFFFFF;
  uint64_t s1 = 0xFFFFFFFFFFFFFFFF;
  uint64_t s2 = 0xFFFFFFFFFFFFFFFF;
  uint64_t s3 = 0xFFFFFFFFFFFFFFFF;
  uint64_t s4 = 0xFFFFFFFFFFFFFFFF;
  uint64_t s5 = 0xFFFFFFFFFFFFFFFF;
  uint64_t s6 = 0xFFFFFFFFFFFFFFFF;
  uint64_t s7 = 0xFFFFFFFFFFFFFFFF;

  uint64_t v1 = (rnd() << 55) >> 55;
  v1 = v1 > ((0x0001 << 9) - 64) ? ((0x0001 << 9) - 64) : v1;
  uint64_t v2 = rnd();
  uint64_t v3 = rnd();
  uint64_t v4 = rnd();

  inst = constrInstHashsb64(RegId::X16, RegId::X17);
  thread0->writeReg(RegId::X5, v1);
  stbuff->writeIntoSB(0+8*0, (s0    )&0xFF); stbuff->writeIntoSB(1+8*0, (s0>>8 )&0xFF); stbuff->writeIntoSB(2+8*0, (s0>>16)&0xFF); stbuff->writeIntoSB(3+8*0, (s0>>24)&0xFF);
  stbuff->writeIntoSB(4+8*0, (s0>>32)&0xFF); stbuff->writeIntoSB(5+8*0, (s0>>40)&0xFF); stbuff->writeIntoSB(6+8*0, (s0>>48)&0xFF); stbuff->writeIntoSB(7+8*0, (s0>>56)&0xFF);
  stbuff->writeIntoSB(0+8*1, (s1    )&0xFF); stbuff->writeIntoSB(1+8*1, (s1>>8 )&0xFF); stbuff->writeIntoSB(2+8*1, (s1>>16)&0xFF); stbuff->writeIntoSB(3+8*1, (s1>>24)&0xFF);
  stbuff->writeIntoSB(4+8*1, (s1>>32)&0xFF); stbuff->writeIntoSB(5+8*1, (s1>>40)&0xFF); stbuff->writeIntoSB(6+8*1, (s1>>48)&0xFF); stbuff->writeIntoSB(7+8*1, (s1>>56)&0xFF);
  stbuff->writeIntoSB(0+8*2, (s2    )&0xFF); stbuff->writeIntoSB(1+8*2, (s2>>8 )&0xFF); stbuff->writeIntoSB(2+8*2, (s2>>16)&0xFF); stbuff->writeIntoSB(3+8*2, (s2>>24)&0xFF);
  stbuff->writeIntoSB(4+8*2, (s2>>32)&0xFF); stbuff->writeIntoSB(5+8*2, (s2>>40)&0xFF); stbuff->writeIntoSB(6+8*2, (s2>>48)&0xFF); stbuff->writeIntoSB(7+8*2, (s2>>56)&0xFF);
  stbuff->writeIntoSB(0+8*3, (s3    )&0xFF); stbuff->writeIntoSB(1+8*3, (s3>>8 )&0xFF); stbuff->writeIntoSB(2+8*3, (s3>>16)&0xFF); stbuff->writeIntoSB(3+8*3, (s3>>24)&0xFF);
  stbuff->writeIntoSB(4+8*3, (s3>>32)&0xFF); stbuff->writeIntoSB(5+8*3, (s3>>40)&0xFF); stbuff->writeIntoSB(6+8*3, (s3>>48)&0xFF); stbuff->writeIntoSB(7+8*3, (s3>>56)&0xFF);
  stbuff->writeIntoSB(0+8*4, (s4    )&0xFF); stbuff->writeIntoSB(1+8*4, (s4>>8 )&0xFF); stbuff->writeIntoSB(2+8*4, (s4>>16)&0xFF); stbuff->writeIntoSB(3+8*4, (s4>>24)&0xFF);
  stbuff->writeIntoSB(4+8*4, (s4>>32)&0xFF); stbuff->writeIntoSB(5+8*4, (s4>>40)&0xFF); stbuff->writeIntoSB(6+8*4, (s4>>48)&0xFF); stbuff->writeIntoSB(7+8*4, (s4>>56)&0xFF);
  stbuff->writeIntoSB(0+8*5, (s5    )&0xFF); stbuff->writeIntoSB(1+8*5, (s5>>8 )&0xFF); stbuff->writeIntoSB(2+8*5, (s5>>16)&0xFF); stbuff->writeIntoSB(3+8*5, (s5>>24)&0xFF);
  stbuff->writeIntoSB(4+8*5, (s5>>32)&0xFF); stbuff->writeIntoSB(5+8*5, (s5>>40)&0xFF); stbuff->writeIntoSB(6+8*5, (s5>>48)&0xFF); stbuff->writeIntoSB(7+8*5, (s5>>56)&0xFF);
  stbuff->writeIntoSB(0+8*6, (s6    )&0xFF); stbuff->writeIntoSB(1+8*6, (s6>>8 )&0xFF); stbuff->writeIntoSB(2+8*6, (s6>>16)&0xFF); stbuff->writeIntoSB(3+8*6, (s6>>24)&0xFF);
  stbuff->writeIntoSB(4+8*6, (s6>>32)&0xFF); stbuff->writeIntoSB(5+8*6, (s6>>40)&0xFF); stbuff->writeIntoSB(6+8*6, (s6>>48)&0xFF); stbuff->writeIntoSB(7+8*6, (s6>>56)&0xFF);
  stbuff->writeIntoSB(0+8*7, (s7    )&0xFF); stbuff->writeIntoSB(1+8*7, (s7>>8 )&0xFF); stbuff->writeIntoSB(2+8*7, (s7>>16)&0xFF); stbuff->writeIntoSB(3+8*7, (s7>>24)&0xFF);
  stbuff->writeIntoSB(4+8*7, (s7>>32)&0xFF); stbuff->writeIntoSB(5+8*7, (s7>>40)&0xFF); stbuff->writeIntoSB(6+8*7, (s7>>48)&0xFF); stbuff->writeIntoSB(7+8*7, (s7>>56)&0xFF);

  thread0->writeReg(RegId::X16, v3);
  thread0->writeReg(RegId::X17, v4);
  Cycles cycle = decodeInst(inst).exe(*archstate, inst);
  // std::cout << "Cycles:" << cycle << std::endl;
  //  read_reg() == reg + imm
  EXPECT_EQ(thread0->readReg(RegId::X5), v1);
  EXPECT_EQ(thread0->readReg(RegId::X16), v3);

  EXPECT_EQ((stbuff->getVarSymbol(0  , 8) << 0) | (stbuff->getVarSymbol(0  +8, 8) << 8) | (stbuff->getVarSymbol(0  +16, 8) << 16) | (stbuff->getVarSymbol(0  +24, 8) << 24) | (stbuff->getVarSymbol(0  +32, 8) << 32) | (stbuff->getVarSymbol(0  +40, 8) << 40) | (stbuff->getVarSymbol(0  +48, 8) << 48) | (stbuff->getVarSymbol(0  +56, 8) << 56), s0);
  EXPECT_EQ((stbuff->getVarSymbol(64 , 8) << 0) | (stbuff->getVarSymbol(64 +8, 8) << 8) | (stbuff->getVarSymbol(64 +16, 8) << 16) | (stbuff->getVarSymbol(64 +24, 8) << 24) | (stbuff->getVarSymbol(64 +32, 8) << 32) | (stbuff->getVarSymbol(64 +40, 8) << 40) | (stbuff->getVarSymbol(64 +48, 8) << 48) | (stbuff->getVarSymbol(64 +56, 8) << 56), s1);
  EXPECT_EQ((stbuff->getVarSymbol(128, 8) << 0) | (stbuff->getVarSymbol(128+8, 8) << 8) | (stbuff->getVarSymbol(128+16, 8) << 16) | (stbuff->getVarSymbol(128+24, 8) << 24) | (stbuff->getVarSymbol(128+32, 8) << 32) | (stbuff->getVarSymbol(128+40, 8) << 40) | (stbuff->getVarSymbol(128+48, 8) << 48) | (stbuff->getVarSymbol(128+56, 8) << 56), s2);
  EXPECT_EQ((stbuff->getVarSymbol(192, 8) << 0) | (stbuff->getVarSymbol(192+8, 8) << 8) | (stbuff->getVarSymbol(192+16, 8) << 16) | (stbuff->getVarSymbol(192+24, 8) << 24) | (stbuff->getVarSymbol(192+32, 8) << 32) | (stbuff->getVarSymbol(192+40, 8) << 40) | (stbuff->getVarSymbol(192+48, 8) << 48) | (stbuff->getVarSymbol(192+56, 8) << 56), s3);
  EXPECT_EQ((stbuff->getVarSymbol(256, 8) << 0) | (stbuff->getVarSymbol(256+8, 8) << 8) | (stbuff->getVarSymbol(256+16, 8) << 16) | (stbuff->getVarSymbol(256+24, 8) << 24) | (stbuff->getVarSymbol(256+32, 8) << 32) | (stbuff->getVarSymbol(256+40, 8) << 40) | (stbuff->getVarSymbol(256+48, 8) << 48) | (stbuff->getVarSymbol(256+56, 8) << 56), s4);
  EXPECT_EQ((stbuff->getVarSymbol(320, 8) << 0) | (stbuff->getVarSymbol(320+8, 8) << 8) | (stbuff->getVarSymbol(320+16, 8) << 16) | (stbuff->getVarSymbol(320+24, 8) << 24) | (stbuff->getVarSymbol(320+32, 8) << 32) | (stbuff->getVarSymbol(320+40, 8) << 40) | (stbuff->getVarSymbol(320+48, 8) << 48) | (stbuff->getVarSymbol(320+56, 8) << 56), s5);
  EXPECT_EQ((stbuff->getVarSymbol(384, 8) << 0) | (stbuff->getVarSymbol(384+8, 8) << 8) | (stbuff->getVarSymbol(384+16, 8) << 16) | (stbuff->getVarSymbol(384+24, 8) << 24) | (stbuff->getVarSymbol(384+32, 8) << 32) | (stbuff->getVarSymbol(384+40, 8) << 40) | (stbuff->getVarSymbol(384+48, 8) << 48) | (stbuff->getVarSymbol(384+56, 8) << 56), s6);
  EXPECT_EQ((stbuff->getVarSymbol(448, 8) << 0) | (stbuff->getVarSymbol(448+8, 8) << 8) | (stbuff->getVarSymbol(448+16, 8) << 16) | (stbuff->getVarSymbol(448+24, 8) << 24) | (stbuff->getVarSymbol(448+32, 8) << 32) | (stbuff->getVarSymbol(448+40, 8) << 40) | (stbuff->getVarSymbol(448+48, 8) << 48) | (stbuff->getVarSymbol(448+56, 8) << 56), s7);

  EXPECT_EQ(thread0->readReg(RegId::X17), crc64_helper_hashsb64(0xFFFFFFFFFFFFFFFF) + v3);
  EXPECT_EQ(cycle, basim::Cycles(1));
  // Expect to be empty.
}


/* Testing with min value */
TEST_F(Hashsb64, Min) {
  ThreadStatePtr thread0;
  uint8_t tid0 = tstable->getTID();
  thread0 = new ThreadState(tid0, 0, 0, 0);
  tstable->addtoTST(thread0);
  archstate->threadstate = thread0;

  std::mt19937_64 rnd(std::random_device{}());
  uint64_t s0 = 0x0000000000000000;
  uint64_t s1 = 0x0000000000000000;
  uint64_t s2 = 0x0000000000000000;
  uint64_t s3 = 0x0000000000000000;
  uint64_t s4 = 0x0000000000000000;
  uint64_t s5 = 0x0000000000000000;
  uint64_t s6 = 0x0000000000000000;
  uint64_t s7 = 0x0000000000000000;

  uint64_t v1 = (rnd() << 55) >> 55;
  v1 = v1 > ((0x0001 << 9) - 64) ? ((0x0001 << 9) - 64) : v1;
  uint64_t v2 = rnd();
  uint64_t v3 = rnd();
  uint64_t v4 = rnd();

  inst = constrInstHashsb64(RegId::X16, RegId::X17);
  thread0->writeReg(RegId::X5, v1);
  stbuff->writeIntoSB(0+8*0, (s0    )&0xFF); stbuff->writeIntoSB(1+8*0, (s0>>8 )&0xFF); stbuff->writeIntoSB(2+8*0, (s0>>16)&0xFF); stbuff->writeIntoSB(3+8*0, (s0>>24)&0xFF);
  stbuff->writeIntoSB(4+8*0, (s0>>32)&0xFF); stbuff->writeIntoSB(5+8*0, (s0>>40)&0xFF); stbuff->writeIntoSB(6+8*0, (s0>>48)&0xFF); stbuff->writeIntoSB(7+8*0, (s0>>56)&0xFF);
  stbuff->writeIntoSB(0+8*1, (s1    )&0xFF); stbuff->writeIntoSB(1+8*1, (s1>>8 )&0xFF); stbuff->writeIntoSB(2+8*1, (s1>>16)&0xFF); stbuff->writeIntoSB(3+8*1, (s1>>24)&0xFF);
  stbuff->writeIntoSB(4+8*1, (s1>>32)&0xFF); stbuff->writeIntoSB(5+8*1, (s1>>40)&0xFF); stbuff->writeIntoSB(6+8*1, (s1>>48)&0xFF); stbuff->writeIntoSB(7+8*1, (s1>>56)&0xFF);
  stbuff->writeIntoSB(0+8*2, (s2    )&0xFF); stbuff->writeIntoSB(1+8*2, (s2>>8 )&0xFF); stbuff->writeIntoSB(2+8*2, (s2>>16)&0xFF); stbuff->writeIntoSB(3+8*2, (s2>>24)&0xFF);
  stbuff->writeIntoSB(4+8*2, (s2>>32)&0xFF); stbuff->writeIntoSB(5+8*2, (s2>>40)&0xFF); stbuff->writeIntoSB(6+8*2, (s2>>48)&0xFF); stbuff->writeIntoSB(7+8*2, (s2>>56)&0xFF);
  stbuff->writeIntoSB(0+8*3, (s3    )&0xFF); stbuff->writeIntoSB(1+8*3, (s3>>8 )&0xFF); stbuff->writeIntoSB(2+8*3, (s3>>16)&0xFF); stbuff->writeIntoSB(3+8*3, (s3>>24)&0xFF);
  stbuff->writeIntoSB(4+8*3, (s3>>32)&0xFF); stbuff->writeIntoSB(5+8*3, (s3>>40)&0xFF); stbuff->writeIntoSB(6+8*3, (s3>>48)&0xFF); stbuff->writeIntoSB(7+8*3, (s3>>56)&0xFF);
  stbuff->writeIntoSB(0+8*4, (s4    )&0xFF); stbuff->writeIntoSB(1+8*4, (s4>>8 )&0xFF); stbuff->writeIntoSB(2+8*4, (s4>>16)&0xFF); stbuff->writeIntoSB(3+8*4, (s4>>24)&0xFF);
  stbuff->writeIntoSB(4+8*4, (s4>>32)&0xFF); stbuff->writeIntoSB(5+8*4, (s4>>40)&0xFF); stbuff->writeIntoSB(6+8*4, (s4>>48)&0xFF); stbuff->writeIntoSB(7+8*4, (s4>>56)&0xFF);
  stbuff->writeIntoSB(0+8*5, (s5    )&0xFF); stbuff->writeIntoSB(1+8*5, (s5>>8 )&0xFF); stbuff->writeIntoSB(2+8*5, (s5>>16)&0xFF); stbuff->writeIntoSB(3+8*5, (s5>>24)&0xFF);
  stbuff->writeIntoSB(4+8*5, (s5>>32)&0xFF); stbuff->writeIntoSB(5+8*5, (s5>>40)&0xFF); stbuff->writeIntoSB(6+8*5, (s5>>48)&0xFF); stbuff->writeIntoSB(7+8*5, (s5>>56)&0xFF);
  stbuff->writeIntoSB(0+8*6, (s6    )&0xFF); stbuff->writeIntoSB(1+8*6, (s6>>8 )&0xFF); stbuff->writeIntoSB(2+8*6, (s6>>16)&0xFF); stbuff->writeIntoSB(3+8*6, (s6>>24)&0xFF);
  stbuff->writeIntoSB(4+8*6, (s6>>32)&0xFF); stbuff->writeIntoSB(5+8*6, (s6>>40)&0xFF); stbuff->writeIntoSB(6+8*6, (s6>>48)&0xFF); stbuff->writeIntoSB(7+8*6, (s6>>56)&0xFF);
  stbuff->writeIntoSB(0+8*7, (s7    )&0xFF); stbuff->writeIntoSB(1+8*7, (s7>>8 )&0xFF); stbuff->writeIntoSB(2+8*7, (s7>>16)&0xFF); stbuff->writeIntoSB(3+8*7, (s7>>24)&0xFF);
  stbuff->writeIntoSB(4+8*7, (s7>>32)&0xFF); stbuff->writeIntoSB(5+8*7, (s7>>40)&0xFF); stbuff->writeIntoSB(6+8*7, (s7>>48)&0xFF); stbuff->writeIntoSB(7+8*7, (s7>>56)&0xFF);

  thread0->writeReg(RegId::X16, v3);
  thread0->writeReg(RegId::X17, v4);
  Cycles cycle = decodeInst(inst).exe(*archstate, inst);
  // std::cout << "Cycles:" << cycle << std::endl;
  //  read_reg() == reg + imm
  EXPECT_EQ(thread0->readReg(RegId::X5), v1);
  EXPECT_EQ(thread0->readReg(RegId::X16), v3);

  EXPECT_EQ((stbuff->getVarSymbol(0  , 8) << 0) | (stbuff->getVarSymbol(0  +8, 8) << 8) | (stbuff->getVarSymbol(0  +16, 8) << 16) | (stbuff->getVarSymbol(0  +24, 8) << 24) | (stbuff->getVarSymbol(0  +32, 8) << 32) | (stbuff->getVarSymbol(0  +40, 8) << 40) | (stbuff->getVarSymbol(0  +48, 8) << 48) | (stbuff->getVarSymbol(0  +56, 8) << 56), s0);
  EXPECT_EQ((stbuff->getVarSymbol(64 , 8) << 0) | (stbuff->getVarSymbol(64 +8, 8) << 8) | (stbuff->getVarSymbol(64 +16, 8) << 16) | (stbuff->getVarSymbol(64 +24, 8) << 24) | (stbuff->getVarSymbol(64 +32, 8) << 32) | (stbuff->getVarSymbol(64 +40, 8) << 40) | (stbuff->getVarSymbol(64 +48, 8) << 48) | (stbuff->getVarSymbol(64 +56, 8) << 56), s1);
  EXPECT_EQ((stbuff->getVarSymbol(128, 8) << 0) | (stbuff->getVarSymbol(128+8, 8) << 8) | (stbuff->getVarSymbol(128+16, 8) << 16) | (stbuff->getVarSymbol(128+24, 8) << 24) | (stbuff->getVarSymbol(128+32, 8) << 32) | (stbuff->getVarSymbol(128+40, 8) << 40) | (stbuff->getVarSymbol(128+48, 8) << 48) | (stbuff->getVarSymbol(128+56, 8) << 56), s2);
  EXPECT_EQ((stbuff->getVarSymbol(192, 8) << 0) | (stbuff->getVarSymbol(192+8, 8) << 8) | (stbuff->getVarSymbol(192+16, 8) << 16) | (stbuff->getVarSymbol(192+24, 8) << 24) | (stbuff->getVarSymbol(192+32, 8) << 32) | (stbuff->getVarSymbol(192+40, 8) << 40) | (stbuff->getVarSymbol(192+48, 8) << 48) | (stbuff->getVarSymbol(192+56, 8) << 56), s3);
  EXPECT_EQ((stbuff->getVarSymbol(256, 8) << 0) | (stbuff->getVarSymbol(256+8, 8) << 8) | (stbuff->getVarSymbol(256+16, 8) << 16) | (stbuff->getVarSymbol(256+24, 8) << 24) | (stbuff->getVarSymbol(256+32, 8) << 32) | (stbuff->getVarSymbol(256+40, 8) << 40) | (stbuff->getVarSymbol(256+48, 8) << 48) | (stbuff->getVarSymbol(256+56, 8) << 56), s4);
  EXPECT_EQ((stbuff->getVarSymbol(320, 8) << 0) | (stbuff->getVarSymbol(320+8, 8) << 8) | (stbuff->getVarSymbol(320+16, 8) << 16) | (stbuff->getVarSymbol(320+24, 8) << 24) | (stbuff->getVarSymbol(320+32, 8) << 32) | (stbuff->getVarSymbol(320+40, 8) << 40) | (stbuff->getVarSymbol(320+48, 8) << 48) | (stbuff->getVarSymbol(320+56, 8) << 56), s5);
  EXPECT_EQ((stbuff->getVarSymbol(384, 8) << 0) | (stbuff->getVarSymbol(384+8, 8) << 8) | (stbuff->getVarSymbol(384+16, 8) << 16) | (stbuff->getVarSymbol(384+24, 8) << 24) | (stbuff->getVarSymbol(384+32, 8) << 32) | (stbuff->getVarSymbol(384+40, 8) << 40) | (stbuff->getVarSymbol(384+48, 8) << 48) | (stbuff->getVarSymbol(384+56, 8) << 56), s6);
  EXPECT_EQ((stbuff->getVarSymbol(448, 8) << 0) | (stbuff->getVarSymbol(448+8, 8) << 8) | (stbuff->getVarSymbol(448+16, 8) << 16) | (stbuff->getVarSymbol(448+24, 8) << 24) | (stbuff->getVarSymbol(448+32, 8) << 32) | (stbuff->getVarSymbol(448+40, 8) << 40) | (stbuff->getVarSymbol(448+48, 8) << 48) | (stbuff->getVarSymbol(448+56, 8) << 56), s7);

  EXPECT_EQ(thread0->readReg(RegId::X17), crc64_helper_hashsb64(0x0000000000000000) + v3);
  EXPECT_EQ(cycle, basim::Cycles(1));
  // Expect to be empty.
}
