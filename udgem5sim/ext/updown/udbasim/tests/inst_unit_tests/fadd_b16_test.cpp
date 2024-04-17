#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"
#include <cmath>
#include <cfenv>

using namespace basim;

class Fadd_b16Test : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    int num_lanes = 64;
    UDAccelerator acc0 = UDAccelerator(num_lanes, 0, 0);
    int buffsize1 = 1024;
    int buffsize2 = 1024;
};
TEST_F(Fadd_b16Test, fadd_b16_0){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_0.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 11890u<<16, uargs1 = 48180u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_1){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_1.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 3352u<<16, uargs1 = 30165u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_2){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_2.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 18910u<<16, uargs1 = 32639u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_3){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_3.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 33691u<<16, uargs1 = 21217u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_4){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_4.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 55785u<<16, uargs1 = 21758u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_5){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_5.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 60327u<<16, uargs1 = 4930u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_6){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_6.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 57296u<<16, uargs1 = 39604u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_7){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_7.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 64453u<<16, uargs1 = 15140u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_8){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_8.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 31726u<<16, uargs1 = 61339u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_9){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_9.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 11499u<<16, uargs1 = 4368u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_10){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_10.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 46021u<<16, uargs1 = 2886u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_11){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_11.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 1223u<<16, uargs1 = 8067u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_12){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_12.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 8890u<<16, uargs1 = 57093u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_13){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_13.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 28785u<<16, uargs1 = 45838u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_14){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_14.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 64393u<<16, uargs1 = 49666u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_15){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_15.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 20773u<<16, uargs1 = 46196u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_16){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_16.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 40061u<<16, uargs1 = 30553u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_17){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_17.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 59974u<<16, uargs1 = 8623u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_18){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_18.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 31479u<<16, uargs1 = 7523u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_19){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_19.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 31924u<<16, uargs1 = 59651u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_20){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_20.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 40021u<<16, uargs1 = 29211u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_21){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_21.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 31722u<<16, uargs1 = 54467u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_22){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_22.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 40159u<<16, uargs1 = 38190u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_23){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_23.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 12068u<<16, uargs1 = 47307u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_24){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_24.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 14958u<<16, uargs1 = 828u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_25){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_25.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 20996u<<16, uargs1 = 252u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_26){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_26.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 15621u<<16, uargs1 = 52663u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_27){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_27.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 56809u<<16, uargs1 = 54042u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_28){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_28.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 4901u<<16, uargs1 = 50217u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_29){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_29.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 35463u<<16, uargs1 = 21657u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_30){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_30.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 2071u<<16, uargs1 = 49245u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_31){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_31.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 59361u<<16, uargs1 = 17101u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_32){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_32.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 15845u<<16, uargs1 = 20436u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_33){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_33.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 5911u<<16, uargs1 = 46239u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_34){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_34.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 18585u<<16, uargs1 = 31997u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_35){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_35.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 51178u<<16, uargs1 = 33981u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_36){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_36.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 22639u<<16, uargs1 = 62057u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_37){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_37.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 8954u<<16, uargs1 = 55079u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_38){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_38.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 1169u<<16, uargs1 = 21725u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_39){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_39.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 22302u<<16, uargs1 = 50954u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_40){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_40.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 33506u<<16, uargs1 = 8853u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_41){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_41.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 9133u<<16, uargs1 = 3174u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_42){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_42.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 18735u<<16, uargs1 = 52790u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_43){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_43.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 59885u<<16, uargs1 = 42387u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_44){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_44.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 64174u<<16, uargs1 = 19144u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_45){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_45.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 62458u<<16, uargs1 = 55755u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_46){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_46.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 11444u<<16, uargs1 = 3441u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_47){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_47.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 45639u<<16, uargs1 = 1068u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_48){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_48.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 29574u<<16, uargs1 = 453u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_49){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_49.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 7154u<<16, uargs1 = 28166u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_50){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_50.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 11042u<<16, uargs1 = 2693u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_51){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_51.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 39492u<<16, uargs1 = 60924u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_52){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_52.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 26229u<<16, uargs1 = 25685u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_53){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_53.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 1881u<<16, uargs1 = 14551u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_54){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_54.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 58034u<<16, uargs1 = 17222u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_55){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_55.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 21054u<<16, uargs1 = 9598u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_56){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_56.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 6675u<<16, uargs1 = 18659u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_57){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_57.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 55359u<<16, uargs1 = 11378u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_58){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_58.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 30595u<<16, uargs1 = 57813u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_59){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_59.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 26586u<<16, uargs1 = 33500u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_60){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_60.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 6846u<<16, uargs1 = 2263u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_61){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_61.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 631u<<16, uargs1 = 38335u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_62){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_62.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 63396u<<16, uargs1 = 37623u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_63){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_63.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 47949u<<16, uargs1 = 17180u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_64){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_64.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 42790u<<16, uargs1 = 57932u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_65){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_65.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 13217u<<16, uargs1 = 32414u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_66){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_66.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 62286u<<16, uargs1 = 55434u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_67){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_67.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 25250u<<16, uargs1 = 41430u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_68){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_68.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 22325u<<16, uargs1 = 53049u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_69){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_69.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 49807u<<16, uargs1 = 55132u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_70){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_70.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 37518u<<16, uargs1 = 19742u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_71){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_71.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 31159u<<16, uargs1 = 60479u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_72){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_72.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 16282u<<16, uargs1 = 13001u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_73){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_73.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 22758u<<16, uargs1 = 10651u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_74){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_74.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 5577u<<16, uargs1 = 35935u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_75){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_75.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 771u<<16, uargs1 = 43848u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_76){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_76.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 46981u<<16, uargs1 = 60272u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_77){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_77.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 5413u<<16, uargs1 = 49864u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_78){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_78.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 35700u<<16, uargs1 = 39776u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_79){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_79.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 29200u<<16, uargs1 = 63366u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_80){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_80.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 62668u<<16, uargs1 = 43143u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_81){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_81.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 61824u<<16, uargs1 = 57526u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_82){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_82.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 16825u<<16, uargs1 = 42808u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_83){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_83.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 48075u<<16, uargs1 = 2273u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_84){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_84.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 45100u<<16, uargs1 = 28714u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_85){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_85.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 15208u<<16, uargs1 = 57931u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_86){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_86.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 35226u<<16, uargs1 = 3808u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_87){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_87.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 43675u<<16, uargs1 = 47620u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_88){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_88.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 15104u<<16, uargs1 = 11629u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_89){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_89.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 17874u<<16, uargs1 = 58724u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_90){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_90.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 2027u<<16, uargs1 = 27018u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_91){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_91.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 57997u<<16, uargs1 = 33995u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_92){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_92.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 45585u<<16, uargs1 = 49984u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_93){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_93.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 55139u<<16, uargs1 = 58313u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_94){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_94.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 42051u<<16, uargs1 = 57092u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_95){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_95.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 11588u<<16, uargs1 = 15856u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_96){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_96.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 14836u<<16, uargs1 = 31781u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_97){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_97.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 4613u<<16, uargs1 = 63465u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_98){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_98.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 40730u<<16, uargs1 = 16420u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fadd_b16Test, fadd_b16_99){
    acc0.initSetup(0,"testprogs/binaries/fadd_b16_99.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t FSCR = 0;
    uint32_t uargs0 = 62955u<<16, uargs1 = 27401u<<16;
    float args0 = *reinterpret_cast<float*>(&uargs0), args1 = *reinterpret_cast<float*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = args0 + args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    uint16_t bf16_val = uint16_t((*uint_val)>>16);
    if ((*uint_val&0xffff) != 0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val & 0x7F80) == 0x7F80 && (bf16_val & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*uint_val != 0 && (bf16_val & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, bf16_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
