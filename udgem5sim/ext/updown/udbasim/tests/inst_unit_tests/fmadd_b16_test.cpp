#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"
#include <cmath>
#include <cfenv>

using namespace basim;

class Fmadd_b16Test : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    int num_lanes = 64;
    UDAccelerator acc0 = UDAccelerator(num_lanes, 0, 0);
    int buffsize1 = 1024;
    int buffsize2 = 1024;
};
TEST_F(Fmadd_b16Test, fmadd_b16_0){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_0.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 46737u<<16, uargs1 = 64471u<<16, uargs2 = 17768u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_1){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_1.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 29399u<<16, uargs1 = 25009u<<16, uargs2 = 857u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_2){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_2.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 49151u<<16, uargs1 = 9438u<<16, uargs2 = 9360u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_3){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_3.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 19970u<<16, uargs1 = 8119u<<16, uargs2 = 20797u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_4){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_4.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 39562u<<16, uargs1 = 38615u<<16, uargs2 = 14709u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_5){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_5.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 1158u<<16, uargs1 = 28837u<<16, uargs2 = 41959u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_6){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_6.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 13802u<<16, uargs1 = 12117u<<16, uargs2 = 26370u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_7){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_7.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 43159u<<16, uargs1 = 54898u<<16, uargs2 = 2197u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_8){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_8.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 39015u<<16, uargs1 = 50428u<<16, uargs2 = 42880u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_9){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_9.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 22906u<<16, uargs1 = 55349u<<16, uargs2 = 46733u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_10){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_10.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 31762u<<16, uargs1 = 6986u<<16, uargs2 = 58137u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_11){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_11.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 34328u<<16, uargs1 = 28535u<<16, uargs2 = 60959u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_12){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_12.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 16379u<<16, uargs1 = 52671u<<16, uargs2 = 9812u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_13){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_13.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 5597u<<16, uargs1 = 757u<<16, uargs2 = 12785u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_14){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_14.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 1695u<<16, uargs1 = 64623u<<16, uargs2 = 34321u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_15){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_15.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 19840u<<16, uargs1 = 50288u<<16, uargs2 = 53554u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_16){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_16.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 1324u<<16, uargs1 = 13493u<<16, uargs2 = 32541u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_17){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_17.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 30305u<<16, uargs1 = 20351u<<16, uargs2 = 59656u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_18){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_18.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 39274u<<16, uargs1 = 14050u<<16, uargs2 = 50902u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_19){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_19.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 40073u<<16, uargs1 = 32788u<<16, uargs2 = 39123u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_20){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_20.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 5583u<<16, uargs1 = 51979u<<16, uargs2 = 31362u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_21){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_21.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 39947u<<16, uargs1 = 51425u<<16, uargs2 = 25409u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_22){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_22.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 32956u<<16, uargs1 = 29176u<<16, uargs2 = 56602u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_23){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_23.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 39200u<<16, uargs1 = 59317u<<16, uargs2 = 55445u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_24){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_24.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 14751u<<16, uargs1 = 15959u<<16, uargs2 = 43722u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_25){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_25.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 35193u<<16, uargs1 = 64913u<<16, uargs2 = 1577u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_26){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_26.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 51590u<<16, uargs1 = 56388u<<16, uargs2 = 56439u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_27){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_27.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 43174u<<16, uargs1 = 30772u<<16, uargs2 = 16940u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_28){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_28.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 4725u<<16, uargs1 = 48793u<<16, uargs2 = 56828u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_29){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_29.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 39787u<<16, uargs1 = 51268u<<16, uargs2 = 57641u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_30){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_30.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 33149u<<16, uargs1 = 46463u<<16, uargs2 = 33719u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_31){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_31.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 27050u<<16, uargs1 = 37977u<<16, uargs2 = 23414u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_32){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_32.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 37937u<<16, uargs1 = 31664u<<16, uargs2 = 48730u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_33){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_33.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 1631u<<16, uargs1 = 63059u<<16, uargs2 = 62213u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_34){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_34.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 1730u<<16, uargs1 = 50766u<<16, uargs2 = 15727u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_35){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_35.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 33981u<<16, uargs1 = 34388u<<16, uargs2 = 58998u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_36){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_36.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 58391u<<16, uargs1 = 64047u<<16, uargs2 = 7703u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_37){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_37.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 64818u<<16, uargs1 = 52886u<<16, uargs2 = 14627u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_38){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_38.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 28482u<<16, uargs1 = 10361u<<16, uargs2 = 59082u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_39){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_39.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 5366u<<16, uargs1 = 36491u<<16, uargs2 = 20255u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_40){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_40.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 32311u<<16, uargs1 = 1179u<<16, uargs2 = 44255u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_41){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_41.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 25166u<<16, uargs1 = 49403u<<16, uargs2 = 1551u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_42){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_42.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 23384u<<16, uargs1 = 6803u<<16, uargs2 = 10639u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_43){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_43.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 62918u<<16, uargs1 = 63540u<<16, uargs2 = 28237u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_44){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_44.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 45404u<<16, uargs1 = 34180u<<16, uargs2 = 59052u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_45){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_45.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 36568u<<16, uargs1 = 53259u<<16, uargs2 = 16065u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_46){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_46.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 17547u<<16, uargs1 = 52167u<<16, uargs2 = 1321u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_47){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_47.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 13588u<<16, uargs1 = 50046u<<16, uargs2 = 44292u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_48){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_48.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 59003u<<16, uargs1 = 1515u<<16, uargs2 = 31020u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_49){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_49.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 23799u<<16, uargs1 = 28972u<<16, uargs2 = 6189u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_50){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_50.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 2088u<<16, uargs1 = 24003u<<16, uargs2 = 25080u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_51){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_51.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 58067u<<16, uargs1 = 4008u<<16, uargs2 = 45861u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_52){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_52.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 17047u<<16, uargs1 = 60167u<<16, uargs2 = 40286u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_53){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_53.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 35638u<<16, uargs1 = 2260u<<16, uargs2 = 38039u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_54){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_54.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 57581u<<16, uargs1 = 47898u<<16, uargs2 = 4806u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_55){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_55.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 41231u<<16, uargs1 = 57076u<<16, uargs2 = 43752u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_56){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_56.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 17646u<<16, uargs1 = 35744u<<16, uargs2 = 37220u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_57){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_57.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 6651u<<16, uargs1 = 25422u<<16, uargs2 = 12570u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_58){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_58.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 37876u<<16, uargs1 = 61520u<<16, uargs2 = 52471u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_59){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_59.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 62633u<<16, uargs1 = 2590u<<16, uargs2 = 10859u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_60){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_60.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 14187u<<16, uargs1 = 61839u<<16, uargs2 = 37666u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_61){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_61.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 34638u<<16, uargs1 = 24491u<<16, uargs2 = 41283u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_62){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_62.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 36937u<<16, uargs1 = 50674u<<16, uargs2 = 30801u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_63){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_63.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 29792u<<16, uargs1 = 50159u<<16, uargs2 = 15921u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_64){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_64.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 15918u<<16, uargs1 = 3621u<<16, uargs2 = 24146u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_65){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_65.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 15550u<<16, uargs1 = 27828u<<16, uargs2 = 45813u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_66){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_66.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 52626u<<16, uargs1 = 20811u<<16, uargs2 = 9970u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_67){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_67.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 53656u<<16, uargs1 = 25432u<<16, uargs2 = 11468u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_68){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_68.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 24241u<<16, uargs1 = 58066u<<16, uargs2 = 11167u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_69){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_69.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 13845u<<16, uargs1 = 41285u<<16, uargs2 = 44762u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_70){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_70.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 49166u<<16, uargs1 = 48236u<<16, uargs2 = 16466u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_71){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_71.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 60819u<<16, uargs1 = 44168u<<16, uargs2 = 40050u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_72){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_72.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 38166u<<16, uargs1 = 28428u<<16, uargs2 = 62935u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_73){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_73.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 29749u<<16, uargs1 = 26859u<<16, uargs2 = 27850u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_74){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_74.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 42837u<<16, uargs1 = 24132u<<16, uargs2 = 14415u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_75){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_75.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 9325u<<16, uargs1 = 54571u<<16, uargs2 = 55272u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_76){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_76.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 41276u<<16, uargs1 = 52091u<<16, uargs2 = 27710u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_77){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_77.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 15623u<<16, uargs1 = 1922u<<16, uargs2 = 30092u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_78){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_78.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 9055u<<16, uargs1 = 14369u<<16, uargs2 = 4633u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_79){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_79.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 35516u<<16, uargs1 = 26121u<<16, uargs2 = 50575u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_80){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_80.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 59940u<<16, uargs1 = 6197u<<16, uargs2 = 19498u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_81){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_81.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 55024u<<16, uargs1 = 38437u<<16, uargs2 = 32178u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_82){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_82.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 37405u<<16, uargs1 = 8942u<<16, uargs2 = 64324u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_83){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_83.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 899u<<16, uargs1 = 45428u<<16, uargs2 = 29291u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_84){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_84.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 27579u<<16, uargs1 = 63537u<<16, uargs2 = 21642u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_85){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_85.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 28170u<<16, uargs1 = 24956u<<16, uargs2 = 37481u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_86){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_86.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 48063u<<16, uargs1 = 51814u<<16, uargs2 = 34329u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_87){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_87.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 3084u<<16, uargs1 = 18989u<<16, uargs2 = 9687u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_88){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_88.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 63852u<<16, uargs1 = 13718u<<16, uargs2 = 27764u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_89){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_89.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 32520u<<16, uargs1 = 47287u<<16, uargs2 = 33467u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_90){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_90.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 9367u<<16, uargs1 = 5729u<<16, uargs2 = 51177u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_91){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_91.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 56014u<<16, uargs1 = 46681u<<16, uargs2 = 57271u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_92){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_92.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 55909u<<16, uargs1 = 64804u<<16, uargs2 = 25139u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_93){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_93.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 12532u<<16, uargs1 = 832u<<16, uargs2 = 19800u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_94){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_94.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 21466u<<16, uargs1 = 22235u<<16, uargs2 = 39245u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_95){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_95.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 49868u<<16, uargs1 = 61974u<<16, uargs2 = 33573u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_96){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_96.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 58993u<<16, uargs1 = 60313u<<16, uargs2 = 29222u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_97){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_97.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 12297u<<16, uargs1 = 19661u<<16, uargs2 = 60582u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_98){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_98.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 13930u<<16, uargs1 = 36476u<<16, uargs2 = 54238u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmadd_b16Test, fmadd_b16_99){
    acc0.initSetup(0,"testprogs/binaries/fmadd_b16_99.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 17730u<<16, uargs1 = 24444u<<16, uargs2 = 19014u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1), args2 = *reinterpret_cast<float*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
