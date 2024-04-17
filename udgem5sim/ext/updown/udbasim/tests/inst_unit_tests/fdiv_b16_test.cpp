#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"
#include <cmath>
#include <cfenv>

using namespace basim;

class Fdiv_b16Test : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    int num_lanes = 64;
    UDAccelerator acc0 = UDAccelerator(num_lanes, 0, 0);
    int buffsize1 = 1024;
    int buffsize2 = 1024;
};
TEST_F(Fdiv_b16Test, fdiv_b16_0){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_0.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 1330u<<16, uargs1 = 17031u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_1){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_1.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 2531u<<16, uargs1 = 36798u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_2){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_2.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 32305u<<16, uargs1 = 44741u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_3){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_3.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 63018u<<16, uargs1 = 14494u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_4){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_4.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 33997u<<16, uargs1 = 42181u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_5){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_5.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 14308u<<16, uargs1 = 28560u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_6){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_6.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 56956u<<16, uargs1 = 62797u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_7){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_7.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 41999u<<16, uargs1 = 3965u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_8){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_8.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 49898u<<16, uargs1 = 27360u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_9){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_9.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 59293u<<16, uargs1 = 25976u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_10){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_10.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 22232u<<16, uargs1 = 3595u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_11){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_11.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 39743u<<16, uargs1 = 10084u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_12){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_12.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 19895u<<16, uargs1 = 13826u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_13){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_13.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 25362u<<16, uargs1 = 5508u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_14){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_14.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 15382u<<16, uargs1 = 52734u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_15){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_15.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 2025u<<16, uargs1 = 62406u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_16){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_16.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 26990u<<16, uargs1 = 23480u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_17){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_17.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 22070u<<16, uargs1 = 34388u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_18){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_18.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 4620u<<16, uargs1 = 30554u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_19){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_19.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 56276u<<16, uargs1 = 22120u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_20){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_20.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 47961u<<16, uargs1 = 58718u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_21){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_21.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 16650u<<16, uargs1 = 2569u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_22){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_22.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 45376u<<16, uargs1 = 33558u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_23){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_23.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 41154u<<16, uargs1 = 61425u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_24){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_24.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 42932u<<16, uargs1 = 60518u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_25){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_25.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 43166u<<16, uargs1 = 45237u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_26){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_26.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 46658u<<16, uargs1 = 23478u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_27){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_27.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 41075u<<16, uargs1 = 15546u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_28){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_28.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 15463u<<16, uargs1 = 10268u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_29){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_29.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 5685u<<16, uargs1 = 11164u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_30){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_30.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 34419u<<16, uargs1 = 63097u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_31){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_31.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 48634u<<16, uargs1 = 55737u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_32){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_32.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 49783u<<16, uargs1 = 33896u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_33){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_33.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 64546u<<16, uargs1 = 53895u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_34){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_34.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 16228u<<16, uargs1 = 9923u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_35){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_35.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 4390u<<16, uargs1 = 6143u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_36){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_36.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 4453u<<16, uargs1 = 27319u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_37){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_37.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 13505u<<16, uargs1 = 2758u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_38){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_38.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 56079u<<16, uargs1 = 31042u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_39){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_39.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 31716u<<16, uargs1 = 33129u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_40){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_40.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 60753u<<16, uargs1 = 37180u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_41){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_41.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 38014u<<16, uargs1 = 17946u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_42){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_42.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 54713u<<16, uargs1 = 47661u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_43){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_43.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 9270u<<16, uargs1 = 22973u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_44){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_44.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 33753u<<16, uargs1 = 50131u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_45){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_45.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 39556u<<16, uargs1 = 15682u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_46){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_46.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 12029u<<16, uargs1 = 42753u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_47){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_47.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 44101u<<16, uargs1 = 49397u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_48){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_48.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 48417u<<16, uargs1 = 15651u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_49){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_49.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 31449u<<16, uargs1 = 3243u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_50){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_50.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 22978u<<16, uargs1 = 29739u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_51){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_51.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 62657u<<16, uargs1 = 1840u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_52){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_52.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 10624u<<16, uargs1 = 35373u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_53){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_53.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 26635u<<16, uargs1 = 703u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_54){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_54.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 53716u<<16, uargs1 = 27584u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_55){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_55.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 36707u<<16, uargs1 = 56391u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_56){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_56.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 25373u<<16, uargs1 = 55379u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_57){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_57.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 42473u<<16, uargs1 = 32542u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_58){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_58.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 45998u<<16, uargs1 = 41295u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_59){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_59.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 25388u<<16, uargs1 = 1952u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_60){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_60.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 8003u<<16, uargs1 = 46513u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_61){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_61.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 24292u<<16, uargs1 = 18303u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_62){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_62.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 37652u<<16, uargs1 = 18379u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_63){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_63.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 20725u<<16, uargs1 = 34109u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_64){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_64.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 29972u<<16, uargs1 = 3384u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_65){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_65.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 20579u<<16, uargs1 = 47158u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_66){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_66.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 5971u<<16, uargs1 = 12484u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_67){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_67.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 32122u<<16, uargs1 = 36220u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_68){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_68.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 1118u<<16, uargs1 = 5634u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_69){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_69.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 160u<<16, uargs1 = 29655u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_70){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_70.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 6384u<<16, uargs1 = 40752u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_71){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_71.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 45442u<<16, uargs1 = 52684u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_72){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_72.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 48256u<<16, uargs1 = 742u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_73){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_73.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 17312u<<16, uargs1 = 33806u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_74){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_74.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 57975u<<16, uargs1 = 31704u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_75){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_75.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 797u<<16, uargs1 = 16258u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_76){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_76.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 26239u<<16, uargs1 = 34272u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_77){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_77.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 33909u<<16, uargs1 = 60000u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_78){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_78.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 59852u<<16, uargs1 = 64120u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_79){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_79.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 23630u<<16, uargs1 = 2791u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_80){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_80.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 32489u<<16, uargs1 = 21995u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_81){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_81.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 37649u<<16, uargs1 = 41880u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_82){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_82.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 36072u<<16, uargs1 = 24883u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_83){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_83.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 8989u<<16, uargs1 = 57379u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_84){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_84.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 10950u<<16, uargs1 = 28536u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_85){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_85.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 49993u<<16, uargs1 = 58597u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_86){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_86.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 16445u<<16, uargs1 = 20555u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_87){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_87.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 15275u<<16, uargs1 = 37613u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_88){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_88.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 47053u<<16, uargs1 = 1927u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_89){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_89.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 10699u<<16, uargs1 = 57144u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_90){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_90.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 10341u<<16, uargs1 = 10588u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_91){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_91.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 50603u<<16, uargs1 = 64459u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_92){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_92.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 8563u<<16, uargs1 = 45057u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_93){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_93.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 46696u<<16, uargs1 = 6722u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_94){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_94.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 48535u<<16, uargs1 = 34025u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_95){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_95.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 23771u<<16, uargs1 = 56155u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_96){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_96.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 48122u<<16, uargs1 = 39926u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_97){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_97.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 29173u<<16, uargs1 = 26965u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_98){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_98.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 21443u<<16, uargs1 = 39195u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fdiv_b16Test, fdiv_b16_99){
    acc0.initSetup(0,"testprogs/binaries/fdiv_b16_99.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 31899u<<16, uargs1 = 48417u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 / args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
