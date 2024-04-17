#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"
#include <cmath>
#include <cfenv>

using namespace basim;

class Fsub_b16Test : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    int num_lanes = 64;
    UDAccelerator acc0 = UDAccelerator(num_lanes, 0, 0);
    int buffsize1 = 1024;
    int buffsize2 = 1024;
};
TEST_F(Fsub_b16Test, fsub_b16_0){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_0.bin", 0);
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
    uint32_t uargs0 = 55519u<<16, uargs1 = 51845u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_1){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_1.bin", 0);
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
    uint32_t uargs0 = 30928u<<16, uargs1 = 62072u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_2){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_2.bin", 0);
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
    uint32_t uargs0 = 63981u<<16, uargs1 = 2069u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_3){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_3.bin", 0);
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
    uint32_t uargs0 = 53476u<<16, uargs1 = 14251u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_4){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_4.bin", 0);
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
    uint32_t uargs0 = 1983u<<16, uargs1 = 61673u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_5){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_5.bin", 0);
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
    uint32_t uargs0 = 60561u<<16, uargs1 = 57673u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_6){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_6.bin", 0);
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
    uint32_t uargs0 = 38685u<<16, uargs1 = 56283u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_7){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_7.bin", 0);
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
    uint32_t uargs0 = 40258u<<16, uargs1 = 13120u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_8){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_8.bin", 0);
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
    uint32_t uargs0 = 3707u<<16, uargs1 = 33436u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_9){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_9.bin", 0);
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
    uint32_t uargs0 = 11968u<<16, uargs1 = 34231u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_10){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_10.bin", 0);
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
    uint32_t uargs0 = 59957u<<16, uargs1 = 29886u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_11){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_11.bin", 0);
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
    uint32_t uargs0 = 22967u<<16, uargs1 = 23442u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_12){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_12.bin", 0);
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
    uint32_t uargs0 = 42844u<<16, uargs1 = 62801u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_13){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_13.bin", 0);
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
    uint32_t uargs0 = 54008u<<16, uargs1 = 64007u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_14){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_14.bin", 0);
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
    uint32_t uargs0 = 28911u<<16, uargs1 = 15401u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_15){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_15.bin", 0);
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
    uint32_t uargs0 = 38010u<<16, uargs1 = 13933u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_16){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_16.bin", 0);
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
    uint32_t uargs0 = 59308u<<16, uargs1 = 37806u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_17){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_17.bin", 0);
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
    uint32_t uargs0 = 26348u<<16, uargs1 = 32332u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_18){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_18.bin", 0);
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
    uint32_t uargs0 = 15955u<<16, uargs1 = 22935u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_19){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_19.bin", 0);
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
    uint32_t uargs0 = 5669u<<16, uargs1 = 34188u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_20){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_20.bin", 0);
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
    uint32_t uargs0 = 40763u<<16, uargs1 = 47351u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_21){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_21.bin", 0);
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
    uint32_t uargs0 = 17806u<<16, uargs1 = 8340u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_22){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_22.bin", 0);
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
    uint32_t uargs0 = 49030u<<16, uargs1 = 13953u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_23){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_23.bin", 0);
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
    uint32_t uargs0 = 58236u<<16, uargs1 = 27425u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_24){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_24.bin", 0);
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
    uint32_t uargs0 = 3517u<<16, uargs1 = 43037u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_25){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_25.bin", 0);
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
    uint32_t uargs0 = 29126u<<16, uargs1 = 9646u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_26){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_26.bin", 0);
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
    uint32_t uargs0 = 59238u<<16, uargs1 = 38415u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_27){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_27.bin", 0);
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
    uint32_t uargs0 = 28801u<<16, uargs1 = 38082u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_28){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_28.bin", 0);
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
    uint32_t uargs0 = 30787u<<16, uargs1 = 5138u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_29){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_29.bin", 0);
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
    uint32_t uargs0 = 49719u<<16, uargs1 = 31572u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_30){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_30.bin", 0);
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
    uint32_t uargs0 = 31199u<<16, uargs1 = 18088u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_31){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_31.bin", 0);
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
    uint32_t uargs0 = 39314u<<16, uargs1 = 1113u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_32){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_32.bin", 0);
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
    uint32_t uargs0 = 56000u<<16, uargs1 = 61255u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_33){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_33.bin", 0);
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
    uint32_t uargs0 = 44837u<<16, uargs1 = 34927u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_34){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_34.bin", 0);
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
    uint32_t uargs0 = 64817u<<16, uargs1 = 40097u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_35){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_35.bin", 0);
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
    uint32_t uargs0 = 39629u<<16, uargs1 = 59708u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_36){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_36.bin", 0);
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
    uint32_t uargs0 = 41210u<<16, uargs1 = 44185u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_37){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_37.bin", 0);
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
    uint32_t uargs0 = 13185u<<16, uargs1 = 27132u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_38){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_38.bin", 0);
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
    uint32_t uargs0 = 63755u<<16, uargs1 = 2960u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_39){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_39.bin", 0);
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
    uint32_t uargs0 = 53990u<<16, uargs1 = 37834u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_40){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_40.bin", 0);
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
    uint32_t uargs0 = 6337u<<16, uargs1 = 34920u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_41){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_41.bin", 0);
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
    uint32_t uargs0 = 4560u<<16, uargs1 = 38517u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_42){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_42.bin", 0);
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
    uint32_t uargs0 = 11862u<<16, uargs1 = 47127u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_43){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_43.bin", 0);
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
    uint32_t uargs0 = 21267u<<16, uargs1 = 9035u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_44){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_44.bin", 0);
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
    uint32_t uargs0 = 32599u<<16, uargs1 = 44329u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_45){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_45.bin", 0);
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
    uint32_t uargs0 = 3779u<<16, uargs1 = 45884u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_46){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_46.bin", 0);
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
    uint32_t uargs0 = 38931u<<16, uargs1 = 45493u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_47){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_47.bin", 0);
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
    uint32_t uargs0 = 3054u<<16, uargs1 = 9091u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_48){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_48.bin", 0);
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
    uint32_t uargs0 = 38803u<<16, uargs1 = 56023u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_49){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_49.bin", 0);
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
    uint32_t uargs0 = 57863u<<16, uargs1 = 25927u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_50){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_50.bin", 0);
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
    uint32_t uargs0 = 36869u<<16, uargs1 = 64647u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_51){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_51.bin", 0);
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
    uint32_t uargs0 = 45882u<<16, uargs1 = 37057u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_52){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_52.bin", 0);
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
    uint32_t uargs0 = 50354u<<16, uargs1 = 750u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_53){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_53.bin", 0);
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
    uint32_t uargs0 = 1127u<<16, uargs1 = 9220u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_54){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_54.bin", 0);
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
    uint32_t uargs0 = 8452u<<16, uargs1 = 33001u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_55){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_55.bin", 0);
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
    uint32_t uargs0 = 19796u<<16, uargs1 = 60350u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_56){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_56.bin", 0);
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
    uint32_t uargs0 = 15354u<<16, uargs1 = 63652u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_57){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_57.bin", 0);
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
    uint32_t uargs0 = 24108u<<16, uargs1 = 20727u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_58){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_58.bin", 0);
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
    uint32_t uargs0 = 63342u<<16, uargs1 = 25350u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_59){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_59.bin", 0);
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
    uint32_t uargs0 = 60631u<<16, uargs1 = 45398u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_60){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_60.bin", 0);
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
    uint32_t uargs0 = 48005u<<16, uargs1 = 8783u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_61){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_61.bin", 0);
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
    uint32_t uargs0 = 58274u<<16, uargs1 = 10190u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_62){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_62.bin", 0);
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
    uint32_t uargs0 = 32053u<<16, uargs1 = 18943u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_63){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_63.bin", 0);
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
    uint32_t uargs0 = 24222u<<16, uargs1 = 10462u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_64){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_64.bin", 0);
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
    uint32_t uargs0 = 13779u<<16, uargs1 = 2808u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_65){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_65.bin", 0);
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
    uint32_t uargs0 = 30265u<<16, uargs1 = 5931u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_66){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_66.bin", 0);
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
    uint32_t uargs0 = 53053u<<16, uargs1 = 24437u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_67){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_67.bin", 0);
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
    uint32_t uargs0 = 24682u<<16, uargs1 = 61027u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_68){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_68.bin", 0);
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
    uint32_t uargs0 = 59434u<<16, uargs1 = 65348u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_69){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_69.bin", 0);
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
    uint32_t uargs0 = 56270u<<16, uargs1 = 22021u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_70){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_70.bin", 0);
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
    uint32_t uargs0 = 48607u<<16, uargs1 = 53119u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_71){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_71.bin", 0);
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
    uint32_t uargs0 = 5947u<<16, uargs1 = 12487u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_72){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_72.bin", 0);
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
    uint32_t uargs0 = 22988u<<16, uargs1 = 27884u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_73){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_73.bin", 0);
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
    uint32_t uargs0 = 34671u<<16, uargs1 = 4027u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_74){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_74.bin", 0);
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
    uint32_t uargs0 = 23305u<<16, uargs1 = 62308u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_75){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_75.bin", 0);
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
    uint32_t uargs0 = 65282u<<16, uargs1 = 32877u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_76){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_76.bin", 0);
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
    uint32_t uargs0 = 26177u<<16, uargs1 = 603u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_77){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_77.bin", 0);
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
    uint32_t uargs0 = 57661u<<16, uargs1 = 40025u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_78){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_78.bin", 0);
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
    uint32_t uargs0 = 45979u<<16, uargs1 = 21203u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_79){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_79.bin", 0);
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
    uint32_t uargs0 = 7669u<<16, uargs1 = 2792u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_80){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_80.bin", 0);
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
    uint32_t uargs0 = 51374u<<16, uargs1 = 43787u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_81){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_81.bin", 0);
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
    uint32_t uargs0 = 53338u<<16, uargs1 = 64823u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_82){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_82.bin", 0);
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
    uint32_t uargs0 = 39120u<<16, uargs1 = 25946u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_83){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_83.bin", 0);
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
    uint32_t uargs0 = 848u<<16, uargs1 = 43871u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_84){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_84.bin", 0);
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
    uint32_t uargs0 = 16520u<<16, uargs1 = 38001u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_85){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_85.bin", 0);
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
    uint32_t uargs0 = 30578u<<16, uargs1 = 60113u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_86){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_86.bin", 0);
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
    uint32_t uargs0 = 60089u<<16, uargs1 = 34266u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_87){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_87.bin", 0);
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
    uint32_t uargs0 = 63944u<<16, uargs1 = 4053u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_88){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_88.bin", 0);
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
    uint32_t uargs0 = 26000u<<16, uargs1 = 15876u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_89){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_89.bin", 0);
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
    uint32_t uargs0 = 31939u<<16, uargs1 = 24543u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_90){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_90.bin", 0);
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
    uint32_t uargs0 = 31314u<<16, uargs1 = 64126u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_91){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_91.bin", 0);
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
    uint32_t uargs0 = 15815u<<16, uargs1 = 52619u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_92){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_92.bin", 0);
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
    uint32_t uargs0 = 398u<<16, uargs1 = 3343u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_93){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_93.bin", 0);
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
    uint32_t uargs0 = 50531u<<16, uargs1 = 8816u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_94){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_94.bin", 0);
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
    uint32_t uargs0 = 14767u<<16, uargs1 = 935u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_95){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_95.bin", 0);
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
    uint32_t uargs0 = 7343u<<16, uargs1 = 10105u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_96){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_96.bin", 0);
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
    uint32_t uargs0 = 49782u<<16, uargs1 = 5007u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_97){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_97.bin", 0);
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
    uint32_t uargs0 = 58320u<<16, uargs1 = 25961u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_98){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_98.bin", 0);
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
    uint32_t uargs0 = 52016u<<16, uargs1 = 11670u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
TEST_F(Fsub_b16Test, fsub_b16_99){
    acc0.initSetup(0,"testprogs/binaries/fsub_b16_99.bin", 0);
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
    uint32_t uargs0 = 40925u<<16, uargs1 = 22660u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 - args1;
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
