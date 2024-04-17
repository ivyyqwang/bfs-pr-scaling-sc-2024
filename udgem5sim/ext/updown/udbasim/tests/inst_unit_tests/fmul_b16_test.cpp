#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"
#include <cmath>
#include <cfenv>

using namespace basim;

class Fmul_b16Test : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    int num_lanes = 64;
    UDAccelerator acc0 = UDAccelerator(num_lanes, 0, 0);
    int buffsize1 = 1024;
    int buffsize2 = 1024;
};
TEST_F(Fmul_b16Test, fmul_b16_0){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_0.bin", 0);
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
    uint32_t uargs0 = 55292u<<16, uargs1 = 37462u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_1){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_1.bin", 0);
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
    uint32_t uargs0 = 31346u<<16, uargs1 = 43369u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_2){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_2.bin", 0);
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
    uint32_t uargs0 = 9407u<<16, uargs1 = 44652u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_3){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_3.bin", 0);
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
    uint32_t uargs0 = 39229u<<16, uargs1 = 19305u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_4){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_4.bin", 0);
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
    uint32_t uargs0 = 57885u<<16, uargs1 = 20822u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_5){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_5.bin", 0);
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
    uint32_t uargs0 = 45692u<<16, uargs1 = 12153u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_6){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_6.bin", 0);
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
    uint32_t uargs0 = 8292u<<16, uargs1 = 16359u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_7){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_7.bin", 0);
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
    uint32_t uargs0 = 53264u<<16, uargs1 = 48017u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_8){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_8.bin", 0);
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
    uint32_t uargs0 = 63961u<<16, uargs1 = 32281u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_9){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_9.bin", 0);
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
    uint32_t uargs0 = 38769u<<16, uargs1 = 25384u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_10){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_10.bin", 0);
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
    uint32_t uargs0 = 35219u<<16, uargs1 = 63943u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_11){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_11.bin", 0);
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
    uint32_t uargs0 = 61204u<<16, uargs1 = 35112u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_12){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_12.bin", 0);
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
    uint32_t uargs0 = 16972u<<16, uargs1 = 46513u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_13){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_13.bin", 0);
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
    uint32_t uargs0 = 29480u<<16, uargs1 = 42202u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_14){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_14.bin", 0);
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
    uint32_t uargs0 = 60155u<<16, uargs1 = 48352u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_15){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_15.bin", 0);
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
    uint32_t uargs0 = 36084u<<16, uargs1 = 22534u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_16){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_16.bin", 0);
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
    uint32_t uargs0 = 46960u<<16, uargs1 = 18418u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_17){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_17.bin", 0);
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
    uint32_t uargs0 = 3596u<<16, uargs1 = 64645u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_18){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_18.bin", 0);
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
    uint32_t uargs0 = 2369u<<16, uargs1 = 61221u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_19){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_19.bin", 0);
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
    uint32_t uargs0 = 18252u<<16, uargs1 = 51037u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_20){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_20.bin", 0);
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
    uint32_t uargs0 = 50983u<<16, uargs1 = 57525u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_21){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_21.bin", 0);
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
    uint32_t uargs0 = 6681u<<16, uargs1 = 53021u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_22){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_22.bin", 0);
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
    uint32_t uargs0 = 58156u<<16, uargs1 = 21276u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_23){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_23.bin", 0);
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
    uint32_t uargs0 = 24549u<<16, uargs1 = 10010u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_24){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_24.bin", 0);
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
    uint32_t uargs0 = 62898u<<16, uargs1 = 5239u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_25){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_25.bin", 0);
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
    uint32_t uargs0 = 14659u<<16, uargs1 = 59375u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_26){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_26.bin", 0);
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
    uint32_t uargs0 = 34477u<<16, uargs1 = 22947u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_27){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_27.bin", 0);
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
    uint32_t uargs0 = 39406u<<16, uargs1 = 43204u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_28){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_28.bin", 0);
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
    uint32_t uargs0 = 7324u<<16, uargs1 = 46644u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_29){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_29.bin", 0);
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
    uint32_t uargs0 = 50738u<<16, uargs1 = 23791u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_30){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_30.bin", 0);
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
    uint32_t uargs0 = 63589u<<16, uargs1 = 57929u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_31){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_31.bin", 0);
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
    uint32_t uargs0 = 40889u<<16, uargs1 = 57774u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_32){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_32.bin", 0);
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
    uint32_t uargs0 = 44669u<<16, uargs1 = 19783u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_33){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_33.bin", 0);
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
    uint32_t uargs0 = 44954u<<16, uargs1 = 20491u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_34){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_34.bin", 0);
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
    uint32_t uargs0 = 41238u<<16, uargs1 = 46512u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_35){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_35.bin", 0);
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
    uint32_t uargs0 = 46366u<<16, uargs1 = 30596u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_36){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_36.bin", 0);
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
    uint32_t uargs0 = 15697u<<16, uargs1 = 37236u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_37){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_37.bin", 0);
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
    uint32_t uargs0 = 14739u<<16, uargs1 = 51328u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_38){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_38.bin", 0);
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
    uint32_t uargs0 = 44518u<<16, uargs1 = 25047u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_39){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_39.bin", 0);
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
    uint32_t uargs0 = 27125u<<16, uargs1 = 43660u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_40){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_40.bin", 0);
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
    uint32_t uargs0 = 52498u<<16, uargs1 = 57980u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_41){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_41.bin", 0);
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
    uint32_t uargs0 = 14172u<<16, uargs1 = 65033u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_42){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_42.bin", 0);
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
    uint32_t uargs0 = 38313u<<16, uargs1 = 24793u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_43){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_43.bin", 0);
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
    uint32_t uargs0 = 36218u<<16, uargs1 = 17038u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_44){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_44.bin", 0);
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
    uint32_t uargs0 = 15654u<<16, uargs1 = 61028u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_45){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_45.bin", 0);
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
    uint32_t uargs0 = 18898u<<16, uargs1 = 58694u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_46){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_46.bin", 0);
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
    uint32_t uargs0 = 64770u<<16, uargs1 = 6838u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_47){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_47.bin", 0);
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
    uint32_t uargs0 = 14822u<<16, uargs1 = 1804u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_48){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_48.bin", 0);
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
    uint32_t uargs0 = 11117u<<16, uargs1 = 43116u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_49){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_49.bin", 0);
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
    uint32_t uargs0 = 17995u<<16, uargs1 = 16024u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_50){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_50.bin", 0);
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
    uint32_t uargs0 = 8824u<<16, uargs1 = 31334u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_51){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_51.bin", 0);
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
    uint32_t uargs0 = 62554u<<16, uargs1 = 18273u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_52){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_52.bin", 0);
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
    uint32_t uargs0 = 49948u<<16, uargs1 = 18384u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_53){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_53.bin", 0);
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
    uint32_t uargs0 = 63159u<<16, uargs1 = 7419u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_54){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_54.bin", 0);
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
    uint32_t uargs0 = 36926u<<16, uargs1 = 62375u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_55){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_55.bin", 0);
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
    uint32_t uargs0 = 7222u<<16, uargs1 = 32468u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_56){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_56.bin", 0);
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
    uint32_t uargs0 = 31644u<<16, uargs1 = 45964u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_57){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_57.bin", 0);
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
    uint32_t uargs0 = 42283u<<16, uargs1 = 17383u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_58){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_58.bin", 0);
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
    uint32_t uargs0 = 212u<<16, uargs1 = 31540u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_59){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_59.bin", 0);
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
    uint32_t uargs0 = 53385u<<16, uargs1 = 5551u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_60){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_60.bin", 0);
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
    uint32_t uargs0 = 47665u<<16, uargs1 = 31095u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_61){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_61.bin", 0);
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
    uint32_t uargs0 = 62331u<<16, uargs1 = 25192u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_62){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_62.bin", 0);
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
    uint32_t uargs0 = 8805u<<16, uargs1 = 7104u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_63){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_63.bin", 0);
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
    uint32_t uargs0 = 50458u<<16, uargs1 = 29680u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_64){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_64.bin", 0);
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
    uint32_t uargs0 = 23100u<<16, uargs1 = 44097u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_65){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_65.bin", 0);
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
    uint32_t uargs0 = 63550u<<16, uargs1 = 46091u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_66){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_66.bin", 0);
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
    uint32_t uargs0 = 694u<<16, uargs1 = 44561u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_67){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_67.bin", 0);
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
    uint32_t uargs0 = 56438u<<16, uargs1 = 20836u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_68){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_68.bin", 0);
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
    uint32_t uargs0 = 11230u<<16, uargs1 = 63854u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_69){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_69.bin", 0);
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
    uint32_t uargs0 = 16633u<<16, uargs1 = 46602u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_70){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_70.bin", 0);
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
    uint32_t uargs0 = 35404u<<16, uargs1 = 58513u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_71){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_71.bin", 0);
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
    uint32_t uargs0 = 18575u<<16, uargs1 = 11367u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_72){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_72.bin", 0);
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
    uint32_t uargs0 = 5935u<<16, uargs1 = 26476u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_73){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_73.bin", 0);
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
    uint32_t uargs0 = 3860u<<16, uargs1 = 98u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_74){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_74.bin", 0);
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
    uint32_t uargs0 = 16801u<<16, uargs1 = 8518u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_75){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_75.bin", 0);
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
    uint32_t uargs0 = 10654u<<16, uargs1 = 51005u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_76){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_76.bin", 0);
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
    uint32_t uargs0 = 26672u<<16, uargs1 = 13553u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_77){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_77.bin", 0);
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
    uint32_t uargs0 = 9235u<<16, uargs1 = 13707u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_78){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_78.bin", 0);
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
    uint32_t uargs0 = 41585u<<16, uargs1 = 39186u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_79){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_79.bin", 0);
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
    uint32_t uargs0 = 18306u<<16, uargs1 = 36041u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_80){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_80.bin", 0);
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
    uint32_t uargs0 = 50237u<<16, uargs1 = 35501u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_81){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_81.bin", 0);
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
    uint32_t uargs0 = 35624u<<16, uargs1 = 15462u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_82){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_82.bin", 0);
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
    uint32_t uargs0 = 60851u<<16, uargs1 = 43677u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_83){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_83.bin", 0);
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
    uint32_t uargs0 = 54807u<<16, uargs1 = 49060u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_84){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_84.bin", 0);
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
    uint32_t uargs0 = 34218u<<16, uargs1 = 162u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_85){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_85.bin", 0);
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
    uint32_t uargs0 = 42757u<<16, uargs1 = 2986u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_86){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_86.bin", 0);
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
    uint32_t uargs0 = 11045u<<16, uargs1 = 47800u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_87){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_87.bin", 0);
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
    uint32_t uargs0 = 27836u<<16, uargs1 = 61392u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_88){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_88.bin", 0);
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
    uint32_t uargs0 = 34823u<<16, uargs1 = 33720u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_89){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_89.bin", 0);
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
    uint32_t uargs0 = 3331u<<16, uargs1 = 50122u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_90){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_90.bin", 0);
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
    uint32_t uargs0 = 37759u<<16, uargs1 = 20910u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_91){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_91.bin", 0);
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
    uint32_t uargs0 = 33889u<<16, uargs1 = 9413u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_92){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_92.bin", 0);
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
    uint32_t uargs0 = 54856u<<16, uargs1 = 64213u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_93){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_93.bin", 0);
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
    uint32_t uargs0 = 46524u<<16, uargs1 = 24063u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_94){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_94.bin", 0);
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
    uint32_t uargs0 = 41949u<<16, uargs1 = 50323u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_95){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_95.bin", 0);
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
    uint32_t uargs0 = 60188u<<16, uargs1 = 63592u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_96){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_96.bin", 0);
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
    uint32_t uargs0 = 23413u<<16, uargs1 = 41030u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_97){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_97.bin", 0);
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
    uint32_t uargs0 = 43908u<<16, uargs1 = 7603u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_98){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_98.bin", 0);
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
    uint32_t uargs0 = 191u<<16, uargs1 = 55001u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
TEST_F(Fmul_b16Test, fmul_b16_99){
    acc0.initSetup(0,"testprogs/binaries/fmul_b16_99.bin", 0);
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
    uint32_t uargs0 = 24492u<<16, uargs1 = 28802u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 * args1;
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
