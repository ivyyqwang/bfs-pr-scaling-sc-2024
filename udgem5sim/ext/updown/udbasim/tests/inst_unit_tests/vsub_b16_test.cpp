#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"
#include <cmath>
#include <cfenv>

using namespace basim;

class Vsub_b16Test : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    int num_lanes = 64;
    UDAccelerator acc0 = UDAccelerator(num_lanes, 0, 0);
    int buffsize1 = 1024;
    int buffsize2 = 1024;
};
static inline float BF16ToFloat(uint16_t var) {
    uint32_t var32 = static_cast<uint32_t>(var) << 16;
    return *reinterpret_cast<float *>(&var32);
}
TEST_F(Vsub_b16Test, vsub_b16_0){
    acc0.initSetup(0,"testprogs/binaries/vsub_b16_0.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    float val0, val1, val2, val3;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 44518u<<16, uargs1 = 40671u<<16, uargs2 = 61732u<<16, uargs3 = 56158u<<16;
    uint32_t uargs4 = 26296u<<16, uargs5 = 64275u<<16, uargs6 = 46121u<<16, uargs7 = 51761u<<16;
    uint32_t uargs8 = 56363u<<16, uargs9 = 39054u<<16, uargs10 = 13531u<<16, uargs11 = 43481u<<16;
    uint32_t mask = 13;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 - *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 - *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 - *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 - *fargs7) : (*fargs11);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1), *w2 = reinterpret_cast<uint32_t*>(&val2), *w3 = reinterpret_cast<uint32_t*>(&val3);
    uint16_t bf16_val0 = uint16_t((*w0)>>16), bf16_val1 = uint16_t((*w1)>>16), bf16_val2 = uint16_t((*w2)>>16), bf16_val3 = uint16_t((*w3)>>16);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val0 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val0) != val0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val0 & 0x7F80) == 0x7F80 && (bf16_val0 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w0 != 0 && (bf16_val0 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val1 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val1) != val1) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val1 & 0x7F80) == 0x7F80 && (bf16_val1 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w1 != 0 && (bf16_val1 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val2 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val2) != val2) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val2 & 0x7F80) == 0x7F80 && (bf16_val2 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w2 != 0 && (bf16_val2 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val3 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val3) != val3) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val3 & 0x7F80) == 0x7F80 && (bf16_val3 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w3 != 0 && (bf16_val3 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    uint64_t final_result = (uint64_t)(bf16_val0) | ((uint64_t)(bf16_val1) << 16) | ((uint64_t)(bf16_val2) << 32) | ((uint64_t)(bf16_val3) << 48);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vsub_b16Test, vsub_b16_1){
    acc0.initSetup(0,"testprogs/binaries/vsub_b16_1.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    float val0, val1, val2, val3;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 49851u<<16, uargs1 = 24690u<<16, uargs2 = 54057u<<16, uargs3 = 57426u<<16;
    uint32_t uargs4 = 11222u<<16, uargs5 = 18401u<<16, uargs6 = 25083u<<16, uargs7 = 58053u<<16;
    uint32_t uargs8 = 57865u<<16, uargs9 = 28897u<<16, uargs10 = 49266u<<16, uargs11 = 63759u<<16;
    uint32_t mask = 1;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 - *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 - *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 - *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 - *fargs7) : (*fargs11);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1), *w2 = reinterpret_cast<uint32_t*>(&val2), *w3 = reinterpret_cast<uint32_t*>(&val3);
    uint16_t bf16_val0 = uint16_t((*w0)>>16), bf16_val1 = uint16_t((*w1)>>16), bf16_val2 = uint16_t((*w2)>>16), bf16_val3 = uint16_t((*w3)>>16);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val0 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val0) != val0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val0 & 0x7F80) == 0x7F80 && (bf16_val0 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w0 != 0 && (bf16_val0 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val1 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val1) != val1) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val1 & 0x7F80) == 0x7F80 && (bf16_val1 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w1 != 0 && (bf16_val1 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val2 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val2) != val2) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val2 & 0x7F80) == 0x7F80 && (bf16_val2 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w2 != 0 && (bf16_val2 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val3 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val3) != val3) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val3 & 0x7F80) == 0x7F80 && (bf16_val3 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w3 != 0 && (bf16_val3 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    uint64_t final_result = (uint64_t)(bf16_val0) | ((uint64_t)(bf16_val1) << 16) | ((uint64_t)(bf16_val2) << 32) | ((uint64_t)(bf16_val3) << 48);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vsub_b16Test, vsub_b16_2){
    acc0.initSetup(0,"testprogs/binaries/vsub_b16_2.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    float val0, val1, val2, val3;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 41227u<<16, uargs1 = 62025u<<16, uargs2 = 28641u<<16, uargs3 = 2147u<<16;
    uint32_t uargs4 = 32306u<<16, uargs5 = 38224u<<16, uargs6 = 807u<<16, uargs7 = 19417u<<16;
    uint32_t uargs8 = 2013u<<16, uargs9 = 42129u<<16, uargs10 = 8896u<<16, uargs11 = 890u<<16;
    uint32_t mask = 10;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 - *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 - *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 - *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 - *fargs7) : (*fargs11);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1), *w2 = reinterpret_cast<uint32_t*>(&val2), *w3 = reinterpret_cast<uint32_t*>(&val3);
    uint16_t bf16_val0 = uint16_t((*w0)>>16), bf16_val1 = uint16_t((*w1)>>16), bf16_val2 = uint16_t((*w2)>>16), bf16_val3 = uint16_t((*w3)>>16);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val0 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val0) != val0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val0 & 0x7F80) == 0x7F80 && (bf16_val0 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w0 != 0 && (bf16_val0 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val1 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val1) != val1) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val1 & 0x7F80) == 0x7F80 && (bf16_val1 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w1 != 0 && (bf16_val1 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val2 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val2) != val2) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val2 & 0x7F80) == 0x7F80 && (bf16_val2 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w2 != 0 && (bf16_val2 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val3 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val3) != val3) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val3 & 0x7F80) == 0x7F80 && (bf16_val3 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w3 != 0 && (bf16_val3 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    uint64_t final_result = (uint64_t)(bf16_val0) | ((uint64_t)(bf16_val1) << 16) | ((uint64_t)(bf16_val2) << 32) | ((uint64_t)(bf16_val3) << 48);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vsub_b16Test, vsub_b16_3){
    acc0.initSetup(0,"testprogs/binaries/vsub_b16_3.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    float val0, val1, val2, val3;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 4980u<<16, uargs1 = 56970u<<16, uargs2 = 26153u<<16, uargs3 = 46341u<<16;
    uint32_t uargs4 = 54942u<<16, uargs5 = 31033u<<16, uargs6 = 40955u<<16, uargs7 = 64057u<<16;
    uint32_t uargs8 = 50906u<<16, uargs9 = 51450u<<16, uargs10 = 23678u<<16, uargs11 = 40297u<<16;
    uint32_t mask = 2;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 - *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 - *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 - *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 - *fargs7) : (*fargs11);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1), *w2 = reinterpret_cast<uint32_t*>(&val2), *w3 = reinterpret_cast<uint32_t*>(&val3);
    uint16_t bf16_val0 = uint16_t((*w0)>>16), bf16_val1 = uint16_t((*w1)>>16), bf16_val2 = uint16_t((*w2)>>16), bf16_val3 = uint16_t((*w3)>>16);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val0 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val0) != val0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val0 & 0x7F80) == 0x7F80 && (bf16_val0 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w0 != 0 && (bf16_val0 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val1 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val1) != val1) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val1 & 0x7F80) == 0x7F80 && (bf16_val1 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w1 != 0 && (bf16_val1 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val2 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val2) != val2) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val2 & 0x7F80) == 0x7F80 && (bf16_val2 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w2 != 0 && (bf16_val2 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val3 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val3) != val3) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val3 & 0x7F80) == 0x7F80 && (bf16_val3 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w3 != 0 && (bf16_val3 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    uint64_t final_result = (uint64_t)(bf16_val0) | ((uint64_t)(bf16_val1) << 16) | ((uint64_t)(bf16_val2) << 32) | ((uint64_t)(bf16_val3) << 48);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vsub_b16Test, vsub_b16_4){
    acc0.initSetup(0,"testprogs/binaries/vsub_b16_4.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    float val0, val1, val2, val3;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 14123u<<16, uargs1 = 63291u<<16, uargs2 = 43746u<<16, uargs3 = 36084u<<16;
    uint32_t uargs4 = 29806u<<16, uargs5 = 29139u<<16, uargs6 = 40564u<<16, uargs7 = 6434u<<16;
    uint32_t uargs8 = 18639u<<16, uargs9 = 59358u<<16, uargs10 = 51866u<<16, uargs11 = 20179u<<16;
    uint32_t mask = 11;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 - *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 - *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 - *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 - *fargs7) : (*fargs11);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1), *w2 = reinterpret_cast<uint32_t*>(&val2), *w3 = reinterpret_cast<uint32_t*>(&val3);
    uint16_t bf16_val0 = uint16_t((*w0)>>16), bf16_val1 = uint16_t((*w1)>>16), bf16_val2 = uint16_t((*w2)>>16), bf16_val3 = uint16_t((*w3)>>16);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val0 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val0) != val0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val0 & 0x7F80) == 0x7F80 && (bf16_val0 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w0 != 0 && (bf16_val0 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val1 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val1) != val1) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val1 & 0x7F80) == 0x7F80 && (bf16_val1 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w1 != 0 && (bf16_val1 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val2 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val2) != val2) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val2 & 0x7F80) == 0x7F80 && (bf16_val2 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w2 != 0 && (bf16_val2 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val3 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val3) != val3) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val3 & 0x7F80) == 0x7F80 && (bf16_val3 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w3 != 0 && (bf16_val3 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    uint64_t final_result = (uint64_t)(bf16_val0) | ((uint64_t)(bf16_val1) << 16) | ((uint64_t)(bf16_val2) << 32) | ((uint64_t)(bf16_val3) << 48);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vsub_b16Test, vsub_b16_5){
    acc0.initSetup(0,"testprogs/binaries/vsub_b16_5.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    float val0, val1, val2, val3;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 24566u<<16, uargs1 = 51743u<<16, uargs2 = 45675u<<16, uargs3 = 50705u<<16;
    uint32_t uargs4 = 26500u<<16, uargs5 = 29650u<<16, uargs6 = 51222u<<16, uargs7 = 60381u<<16;
    uint32_t uargs8 = 30137u<<16, uargs9 = 56541u<<16, uargs10 = 59972u<<16, uargs11 = 61754u<<16;
    uint32_t mask = 12;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 - *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 - *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 - *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 - *fargs7) : (*fargs11);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1), *w2 = reinterpret_cast<uint32_t*>(&val2), *w3 = reinterpret_cast<uint32_t*>(&val3);
    uint16_t bf16_val0 = uint16_t((*w0)>>16), bf16_val1 = uint16_t((*w1)>>16), bf16_val2 = uint16_t((*w2)>>16), bf16_val3 = uint16_t((*w3)>>16);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val0 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val0) != val0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val0 & 0x7F80) == 0x7F80 && (bf16_val0 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w0 != 0 && (bf16_val0 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val1 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val1) != val1) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val1 & 0x7F80) == 0x7F80 && (bf16_val1 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w1 != 0 && (bf16_val1 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val2 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val2) != val2) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val2 & 0x7F80) == 0x7F80 && (bf16_val2 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w2 != 0 && (bf16_val2 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val3 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val3) != val3) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val3 & 0x7F80) == 0x7F80 && (bf16_val3 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w3 != 0 && (bf16_val3 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    uint64_t final_result = (uint64_t)(bf16_val0) | ((uint64_t)(bf16_val1) << 16) | ((uint64_t)(bf16_val2) << 32) | ((uint64_t)(bf16_val3) << 48);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vsub_b16Test, vsub_b16_6){
    acc0.initSetup(0,"testprogs/binaries/vsub_b16_6.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    float val0, val1, val2, val3;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 55621u<<16, uargs1 = 35216u<<16, uargs2 = 40105u<<16, uargs3 = 36430u<<16;
    uint32_t uargs4 = 11415u<<16, uargs5 = 23760u<<16, uargs6 = 44267u<<16, uargs7 = 14559u<<16;
    uint32_t uargs8 = 51308u<<16, uargs9 = 43663u<<16, uargs10 = 11409u<<16, uargs11 = 22953u<<16;
    uint32_t mask = 15;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 - *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 - *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 - *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 - *fargs7) : (*fargs11);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1), *w2 = reinterpret_cast<uint32_t*>(&val2), *w3 = reinterpret_cast<uint32_t*>(&val3);
    uint16_t bf16_val0 = uint16_t((*w0)>>16), bf16_val1 = uint16_t((*w1)>>16), bf16_val2 = uint16_t((*w2)>>16), bf16_val3 = uint16_t((*w3)>>16);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val0 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val0) != val0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val0 & 0x7F80) == 0x7F80 && (bf16_val0 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w0 != 0 && (bf16_val0 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val1 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val1) != val1) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val1 & 0x7F80) == 0x7F80 && (bf16_val1 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w1 != 0 && (bf16_val1 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val2 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val2) != val2) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val2 & 0x7F80) == 0x7F80 && (bf16_val2 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w2 != 0 && (bf16_val2 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val3 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val3) != val3) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val3 & 0x7F80) == 0x7F80 && (bf16_val3 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w3 != 0 && (bf16_val3 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    uint64_t final_result = (uint64_t)(bf16_val0) | ((uint64_t)(bf16_val1) << 16) | ((uint64_t)(bf16_val2) << 32) | ((uint64_t)(bf16_val3) << 48);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vsub_b16Test, vsub_b16_7){
    acc0.initSetup(0,"testprogs/binaries/vsub_b16_7.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    float val0, val1, val2, val3;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 24670u<<16, uargs1 = 9471u<<16, uargs2 = 43899u<<16, uargs3 = 61766u<<16;
    uint32_t uargs4 = 1115u<<16, uargs5 = 50549u<<16, uargs6 = 39750u<<16, uargs7 = 53990u<<16;
    uint32_t uargs8 = 54957u<<16, uargs9 = 54752u<<16, uargs10 = 6157u<<16, uargs11 = 57466u<<16;
    uint32_t mask = 15;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 - *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 - *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 - *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 - *fargs7) : (*fargs11);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1), *w2 = reinterpret_cast<uint32_t*>(&val2), *w3 = reinterpret_cast<uint32_t*>(&val3);
    uint16_t bf16_val0 = uint16_t((*w0)>>16), bf16_val1 = uint16_t((*w1)>>16), bf16_val2 = uint16_t((*w2)>>16), bf16_val3 = uint16_t((*w3)>>16);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val0 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val0) != val0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val0 & 0x7F80) == 0x7F80 && (bf16_val0 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w0 != 0 && (bf16_val0 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val1 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val1) != val1) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val1 & 0x7F80) == 0x7F80 && (bf16_val1 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w1 != 0 && (bf16_val1 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val2 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val2) != val2) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val2 & 0x7F80) == 0x7F80 && (bf16_val2 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w2 != 0 && (bf16_val2 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val3 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val3) != val3) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val3 & 0x7F80) == 0x7F80 && (bf16_val3 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w3 != 0 && (bf16_val3 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    uint64_t final_result = (uint64_t)(bf16_val0) | ((uint64_t)(bf16_val1) << 16) | ((uint64_t)(bf16_val2) << 32) | ((uint64_t)(bf16_val3) << 48);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vsub_b16Test, vsub_b16_8){
    acc0.initSetup(0,"testprogs/binaries/vsub_b16_8.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    float val0, val1, val2, val3;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 28296u<<16, uargs1 = 6012u<<16, uargs2 = 17954u<<16, uargs3 = 36548u<<16;
    uint32_t uargs4 = 29388u<<16, uargs5 = 64938u<<16, uargs6 = 48707u<<16, uargs7 = 37472u<<16;
    uint32_t uargs8 = 21389u<<16, uargs9 = 42378u<<16, uargs10 = 28908u<<16, uargs11 = 18113u<<16;
    uint32_t mask = 7;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 - *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 - *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 - *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 - *fargs7) : (*fargs11);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1), *w2 = reinterpret_cast<uint32_t*>(&val2), *w3 = reinterpret_cast<uint32_t*>(&val3);
    uint16_t bf16_val0 = uint16_t((*w0)>>16), bf16_val1 = uint16_t((*w1)>>16), bf16_val2 = uint16_t((*w2)>>16), bf16_val3 = uint16_t((*w3)>>16);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val0 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val0) != val0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val0 & 0x7F80) == 0x7F80 && (bf16_val0 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w0 != 0 && (bf16_val0 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val1 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val1) != val1) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val1 & 0x7F80) == 0x7F80 && (bf16_val1 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w1 != 0 && (bf16_val1 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val2 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val2) != val2) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val2 & 0x7F80) == 0x7F80 && (bf16_val2 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w2 != 0 && (bf16_val2 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val3 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val3) != val3) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val3 & 0x7F80) == 0x7F80 && (bf16_val3 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w3 != 0 && (bf16_val3 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    uint64_t final_result = (uint64_t)(bf16_val0) | ((uint64_t)(bf16_val1) << 16) | ((uint64_t)(bf16_val2) << 32) | ((uint64_t)(bf16_val3) << 48);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vsub_b16Test, vsub_b16_9){
    acc0.initSetup(0,"testprogs/binaries/vsub_b16_9.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    float val0, val1, val2, val3;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 35993u<<16, uargs1 = 61537u<<16, uargs2 = 18381u<<16, uargs3 = 54558u<<16;
    uint32_t uargs4 = 29679u<<16, uargs5 = 58923u<<16, uargs6 = 38818u<<16, uargs7 = 52634u<<16;
    uint32_t uargs8 = 55340u<<16, uargs9 = 60783u<<16, uargs10 = 51688u<<16, uargs11 = 41214u<<16;
    uint32_t mask = 1;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 - *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 - *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 - *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 - *fargs7) : (*fargs11);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1), *w2 = reinterpret_cast<uint32_t*>(&val2), *w3 = reinterpret_cast<uint32_t*>(&val3);
    uint16_t bf16_val0 = uint16_t((*w0)>>16), bf16_val1 = uint16_t((*w1)>>16), bf16_val2 = uint16_t((*w2)>>16), bf16_val3 = uint16_t((*w3)>>16);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val0 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val0) != val0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val0 & 0x7F80) == 0x7F80 && (bf16_val0 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w0 != 0 && (bf16_val0 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val1 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val1) != val1) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val1 & 0x7F80) == 0x7F80 && (bf16_val1 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w1 != 0 && (bf16_val1 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val2 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val2) != val2) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val2 & 0x7F80) == 0x7F80 && (bf16_val2 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w2 != 0 && (bf16_val2 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val3 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val3) != val3) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val3 & 0x7F80) == 0x7F80 && (bf16_val3 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w3 != 0 && (bf16_val3 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    uint64_t final_result = (uint64_t)(bf16_val0) | ((uint64_t)(bf16_val1) << 16) | ((uint64_t)(bf16_val2) << 32) | ((uint64_t)(bf16_val3) << 48);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vsub_b16Test, vsub_b16_10){
    acc0.initSetup(0,"testprogs/binaries/vsub_b16_10.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    float val0, val1, val2, val3;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 27927u<<16, uargs1 = 51195u<<16, uargs2 = 26891u<<16, uargs3 = 25190u<<16;
    uint32_t uargs4 = 37434u<<16, uargs5 = 7036u<<16, uargs6 = 4268u<<16, uargs7 = 31103u<<16;
    uint32_t uargs8 = 23823u<<16, uargs9 = 53828u<<16, uargs10 = 4734u<<16, uargs11 = 30558u<<16;
    uint32_t mask = 3;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 - *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 - *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 - *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 - *fargs7) : (*fargs11);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1), *w2 = reinterpret_cast<uint32_t*>(&val2), *w3 = reinterpret_cast<uint32_t*>(&val3);
    uint16_t bf16_val0 = uint16_t((*w0)>>16), bf16_val1 = uint16_t((*w1)>>16), bf16_val2 = uint16_t((*w2)>>16), bf16_val3 = uint16_t((*w3)>>16);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val0 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val0) != val0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val0 & 0x7F80) == 0x7F80 && (bf16_val0 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w0 != 0 && (bf16_val0 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val1 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val1) != val1) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val1 & 0x7F80) == 0x7F80 && (bf16_val1 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w1 != 0 && (bf16_val1 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val2 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val2) != val2) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val2 & 0x7F80) == 0x7F80 && (bf16_val2 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w2 != 0 && (bf16_val2 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val3 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val3) != val3) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val3 & 0x7F80) == 0x7F80 && (bf16_val3 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w3 != 0 && (bf16_val3 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    uint64_t final_result = (uint64_t)(bf16_val0) | ((uint64_t)(bf16_val1) << 16) | ((uint64_t)(bf16_val2) << 32) | ((uint64_t)(bf16_val3) << 48);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vsub_b16Test, vsub_b16_11){
    acc0.initSetup(0,"testprogs/binaries/vsub_b16_11.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    float val0, val1, val2, val3;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 61803u<<16, uargs1 = 27895u<<16, uargs2 = 12906u<<16, uargs3 = 20560u<<16;
    uint32_t uargs4 = 48928u<<16, uargs5 = 59070u<<16, uargs6 = 11781u<<16, uargs7 = 22009u<<16;
    uint32_t uargs8 = 13656u<<16, uargs9 = 17431u<<16, uargs10 = 56742u<<16, uargs11 = 29559u<<16;
    uint32_t mask = 2;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 - *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 - *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 - *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 - *fargs7) : (*fargs11);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1), *w2 = reinterpret_cast<uint32_t*>(&val2), *w3 = reinterpret_cast<uint32_t*>(&val3);
    uint16_t bf16_val0 = uint16_t((*w0)>>16), bf16_val1 = uint16_t((*w1)>>16), bf16_val2 = uint16_t((*w2)>>16), bf16_val3 = uint16_t((*w3)>>16);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val0 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val0) != val0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val0 & 0x7F80) == 0x7F80 && (bf16_val0 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w0 != 0 && (bf16_val0 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val1 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val1) != val1) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val1 & 0x7F80) == 0x7F80 && (bf16_val1 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w1 != 0 && (bf16_val1 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val2 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val2) != val2) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val2 & 0x7F80) == 0x7F80 && (bf16_val2 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w2 != 0 && (bf16_val2 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val3 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val3) != val3) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val3 & 0x7F80) == 0x7F80 && (bf16_val3 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w3 != 0 && (bf16_val3 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    uint64_t final_result = (uint64_t)(bf16_val0) | ((uint64_t)(bf16_val1) << 16) | ((uint64_t)(bf16_val2) << 32) | ((uint64_t)(bf16_val3) << 48);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vsub_b16Test, vsub_b16_12){
    acc0.initSetup(0,"testprogs/binaries/vsub_b16_12.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    float val0, val1, val2, val3;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 5733u<<16, uargs1 = 10633u<<16, uargs2 = 18411u<<16, uargs3 = 24087u<<16;
    uint32_t uargs4 = 58045u<<16, uargs5 = 15194u<<16, uargs6 = 35719u<<16, uargs7 = 55503u<<16;
    uint32_t uargs8 = 50205u<<16, uargs9 = 20474u<<16, uargs10 = 36048u<<16, uargs11 = 29251u<<16;
    uint32_t mask = 1;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 - *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 - *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 - *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 - *fargs7) : (*fargs11);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1), *w2 = reinterpret_cast<uint32_t*>(&val2), *w3 = reinterpret_cast<uint32_t*>(&val3);
    uint16_t bf16_val0 = uint16_t((*w0)>>16), bf16_val1 = uint16_t((*w1)>>16), bf16_val2 = uint16_t((*w2)>>16), bf16_val3 = uint16_t((*w3)>>16);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val0 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val0) != val0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val0 & 0x7F80) == 0x7F80 && (bf16_val0 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w0 != 0 && (bf16_val0 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val1 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val1) != val1) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val1 & 0x7F80) == 0x7F80 && (bf16_val1 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w1 != 0 && (bf16_val1 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val2 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val2) != val2) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val2 & 0x7F80) == 0x7F80 && (bf16_val2 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w2 != 0 && (bf16_val2 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val3 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val3) != val3) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val3 & 0x7F80) == 0x7F80 && (bf16_val3 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w3 != 0 && (bf16_val3 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    uint64_t final_result = (uint64_t)(bf16_val0) | ((uint64_t)(bf16_val1) << 16) | ((uint64_t)(bf16_val2) << 32) | ((uint64_t)(bf16_val3) << 48);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vsub_b16Test, vsub_b16_13){
    acc0.initSetup(0,"testprogs/binaries/vsub_b16_13.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    float val0, val1, val2, val3;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 51641u<<16, uargs1 = 17764u<<16, uargs2 = 59906u<<16, uargs3 = 56868u<<16;
    uint32_t uargs4 = 60572u<<16, uargs5 = 828u<<16, uargs6 = 48679u<<16, uargs7 = 49600u<<16;
    uint32_t uargs8 = 33107u<<16, uargs9 = 39937u<<16, uargs10 = 30714u<<16, uargs11 = 12305u<<16;
    uint32_t mask = 7;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 - *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 - *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 - *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 - *fargs7) : (*fargs11);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1), *w2 = reinterpret_cast<uint32_t*>(&val2), *w3 = reinterpret_cast<uint32_t*>(&val3);
    uint16_t bf16_val0 = uint16_t((*w0)>>16), bf16_val1 = uint16_t((*w1)>>16), bf16_val2 = uint16_t((*w2)>>16), bf16_val3 = uint16_t((*w3)>>16);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val0 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val0) != val0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val0 & 0x7F80) == 0x7F80 && (bf16_val0 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w0 != 0 && (bf16_val0 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val1 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val1) != val1) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val1 & 0x7F80) == 0x7F80 && (bf16_val1 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w1 != 0 && (bf16_val1 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val2 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val2) != val2) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val2 & 0x7F80) == 0x7F80 && (bf16_val2 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w2 != 0 && (bf16_val2 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val3 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val3) != val3) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val3 & 0x7F80) == 0x7F80 && (bf16_val3 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w3 != 0 && (bf16_val3 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    uint64_t final_result = (uint64_t)(bf16_val0) | ((uint64_t)(bf16_val1) << 16) | ((uint64_t)(bf16_val2) << 32) | ((uint64_t)(bf16_val3) << 48);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vsub_b16Test, vsub_b16_14){
    acc0.initSetup(0,"testprogs/binaries/vsub_b16_14.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    float val0, val1, val2, val3;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 6037u<<16, uargs1 = 60153u<<16, uargs2 = 38229u<<16, uargs3 = 16038u<<16;
    uint32_t uargs4 = 36974u<<16, uargs5 = 47586u<<16, uargs6 = 2219u<<16, uargs7 = 53776u<<16;
    uint32_t uargs8 = 8272u<<16, uargs9 = 30539u<<16, uargs10 = 37867u<<16, uargs11 = 64604u<<16;
    uint32_t mask = 10;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 - *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 - *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 - *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 - *fargs7) : (*fargs11);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1), *w2 = reinterpret_cast<uint32_t*>(&val2), *w3 = reinterpret_cast<uint32_t*>(&val3);
    uint16_t bf16_val0 = uint16_t((*w0)>>16), bf16_val1 = uint16_t((*w1)>>16), bf16_val2 = uint16_t((*w2)>>16), bf16_val3 = uint16_t((*w3)>>16);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val0 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val0) != val0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val0 & 0x7F80) == 0x7F80 && (bf16_val0 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w0 != 0 && (bf16_val0 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val1 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val1) != val1) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val1 & 0x7F80) == 0x7F80 && (bf16_val1 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w1 != 0 && (bf16_val1 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val2 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val2) != val2) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val2 & 0x7F80) == 0x7F80 && (bf16_val2 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w2 != 0 && (bf16_val2 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val3 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val3) != val3) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val3 & 0x7F80) == 0x7F80 && (bf16_val3 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w3 != 0 && (bf16_val3 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    uint64_t final_result = (uint64_t)(bf16_val0) | ((uint64_t)(bf16_val1) << 16) | ((uint64_t)(bf16_val2) << 32) | ((uint64_t)(bf16_val3) << 48);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vsub_b16Test, vsub_b16_15){
    acc0.initSetup(0,"testprogs/binaries/vsub_b16_15.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    float val0, val1, val2, val3;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 8002u<<16, uargs1 = 36018u<<16, uargs2 = 53789u<<16, uargs3 = 45266u<<16;
    uint32_t uargs4 = 34728u<<16, uargs5 = 15921u<<16, uargs6 = 6747u<<16, uargs7 = 64908u<<16;
    uint32_t uargs8 = 10350u<<16, uargs9 = 61304u<<16, uargs10 = 3487u<<16, uargs11 = 36710u<<16;
    uint32_t mask = 2;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 - *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 - *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 - *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 - *fargs7) : (*fargs11);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1), *w2 = reinterpret_cast<uint32_t*>(&val2), *w3 = reinterpret_cast<uint32_t*>(&val3);
    uint16_t bf16_val0 = uint16_t((*w0)>>16), bf16_val1 = uint16_t((*w1)>>16), bf16_val2 = uint16_t((*w2)>>16), bf16_val3 = uint16_t((*w3)>>16);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val0 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val0) != val0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val0 & 0x7F80) == 0x7F80 && (bf16_val0 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w0 != 0 && (bf16_val0 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val1 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val1) != val1) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val1 & 0x7F80) == 0x7F80 && (bf16_val1 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w1 != 0 && (bf16_val1 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val2 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val2) != val2) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val2 & 0x7F80) == 0x7F80 && (bf16_val2 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w2 != 0 && (bf16_val2 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val3 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val3) != val3) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val3 & 0x7F80) == 0x7F80 && (bf16_val3 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w3 != 0 && (bf16_val3 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    uint64_t final_result = (uint64_t)(bf16_val0) | ((uint64_t)(bf16_val1) << 16) | ((uint64_t)(bf16_val2) << 32) | ((uint64_t)(bf16_val3) << 48);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vsub_b16Test, vsub_b16_16){
    acc0.initSetup(0,"testprogs/binaries/vsub_b16_16.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    float val0, val1, val2, val3;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 31353u<<16, uargs1 = 62238u<<16, uargs2 = 55096u<<16, uargs3 = 38686u<<16;
    uint32_t uargs4 = 48524u<<16, uargs5 = 16648u<<16, uargs6 = 26165u<<16, uargs7 = 33041u<<16;
    uint32_t uargs8 = 42096u<<16, uargs9 = 17706u<<16, uargs10 = 61041u<<16, uargs11 = 24657u<<16;
    uint32_t mask = 3;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 - *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 - *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 - *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 - *fargs7) : (*fargs11);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1), *w2 = reinterpret_cast<uint32_t*>(&val2), *w3 = reinterpret_cast<uint32_t*>(&val3);
    uint16_t bf16_val0 = uint16_t((*w0)>>16), bf16_val1 = uint16_t((*w1)>>16), bf16_val2 = uint16_t((*w2)>>16), bf16_val3 = uint16_t((*w3)>>16);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val0 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val0) != val0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val0 & 0x7F80) == 0x7F80 && (bf16_val0 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w0 != 0 && (bf16_val0 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val1 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val1) != val1) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val1 & 0x7F80) == 0x7F80 && (bf16_val1 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w1 != 0 && (bf16_val1 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val2 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val2) != val2) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val2 & 0x7F80) == 0x7F80 && (bf16_val2 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w2 != 0 && (bf16_val2 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val3 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val3) != val3) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val3 & 0x7F80) == 0x7F80 && (bf16_val3 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w3 != 0 && (bf16_val3 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    uint64_t final_result = (uint64_t)(bf16_val0) | ((uint64_t)(bf16_val1) << 16) | ((uint64_t)(bf16_val2) << 32) | ((uint64_t)(bf16_val3) << 48);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vsub_b16Test, vsub_b16_17){
    acc0.initSetup(0,"testprogs/binaries/vsub_b16_17.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    float val0, val1, val2, val3;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 11669u<<16, uargs1 = 41248u<<16, uargs2 = 51371u<<16, uargs3 = 51541u<<16;
    uint32_t uargs4 = 4522u<<16, uargs5 = 57504u<<16, uargs6 = 52740u<<16, uargs7 = 8991u<<16;
    uint32_t uargs8 = 23800u<<16, uargs9 = 33833u<<16, uargs10 = 49139u<<16, uargs11 = 9649u<<16;
    uint32_t mask = 15;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 - *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 - *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 - *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 - *fargs7) : (*fargs11);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1), *w2 = reinterpret_cast<uint32_t*>(&val2), *w3 = reinterpret_cast<uint32_t*>(&val3);
    uint16_t bf16_val0 = uint16_t((*w0)>>16), bf16_val1 = uint16_t((*w1)>>16), bf16_val2 = uint16_t((*w2)>>16), bf16_val3 = uint16_t((*w3)>>16);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val0 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val0) != val0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val0 & 0x7F80) == 0x7F80 && (bf16_val0 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w0 != 0 && (bf16_val0 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val1 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val1) != val1) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val1 & 0x7F80) == 0x7F80 && (bf16_val1 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w1 != 0 && (bf16_val1 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val2 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val2) != val2) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val2 & 0x7F80) == 0x7F80 && (bf16_val2 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w2 != 0 && (bf16_val2 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val3 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val3) != val3) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val3 & 0x7F80) == 0x7F80 && (bf16_val3 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w3 != 0 && (bf16_val3 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    uint64_t final_result = (uint64_t)(bf16_val0) | ((uint64_t)(bf16_val1) << 16) | ((uint64_t)(bf16_val2) << 32) | ((uint64_t)(bf16_val3) << 48);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vsub_b16Test, vsub_b16_18){
    acc0.initSetup(0,"testprogs/binaries/vsub_b16_18.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    float val0, val1, val2, val3;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 56982u<<16, uargs1 = 49482u<<16, uargs2 = 49329u<<16, uargs3 = 957u<<16;
    uint32_t uargs4 = 47973u<<16, uargs5 = 58723u<<16, uargs6 = 27445u<<16, uargs7 = 36034u<<16;
    uint32_t uargs8 = 24246u<<16, uargs9 = 43594u<<16, uargs10 = 19168u<<16, uargs11 = 44553u<<16;
    uint32_t mask = 13;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 - *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 - *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 - *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 - *fargs7) : (*fargs11);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1), *w2 = reinterpret_cast<uint32_t*>(&val2), *w3 = reinterpret_cast<uint32_t*>(&val3);
    uint16_t bf16_val0 = uint16_t((*w0)>>16), bf16_val1 = uint16_t((*w1)>>16), bf16_val2 = uint16_t((*w2)>>16), bf16_val3 = uint16_t((*w3)>>16);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val0 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val0) != val0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val0 & 0x7F80) == 0x7F80 && (bf16_val0 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w0 != 0 && (bf16_val0 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val1 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val1) != val1) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val1 & 0x7F80) == 0x7F80 && (bf16_val1 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w1 != 0 && (bf16_val1 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val2 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val2) != val2) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val2 & 0x7F80) == 0x7F80 && (bf16_val2 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w2 != 0 && (bf16_val2 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val3 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val3) != val3) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val3 & 0x7F80) == 0x7F80 && (bf16_val3 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w3 != 0 && (bf16_val3 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    uint64_t final_result = (uint64_t)(bf16_val0) | ((uint64_t)(bf16_val1) << 16) | ((uint64_t)(bf16_val2) << 32) | ((uint64_t)(bf16_val3) << 48);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vsub_b16Test, vsub_b16_19){
    acc0.initSetup(0,"testprogs/binaries/vsub_b16_19.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    float val0, val1, val2, val3;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 5468u<<16, uargs1 = 38278u<<16, uargs2 = 36836u<<16, uargs3 = 64924u<<16;
    uint32_t uargs4 = 30945u<<16, uargs5 = 58099u<<16, uargs6 = 4071u<<16, uargs7 = 39175u<<16;
    uint32_t uargs8 = 36558u<<16, uargs9 = 20611u<<16, uargs10 = 5385u<<16, uargs11 = 401u<<16;
    uint32_t mask = 13;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 - *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 - *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 - *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 - *fargs7) : (*fargs11);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1), *w2 = reinterpret_cast<uint32_t*>(&val2), *w3 = reinterpret_cast<uint32_t*>(&val3);
    uint16_t bf16_val0 = uint16_t((*w0)>>16), bf16_val1 = uint16_t((*w1)>>16), bf16_val2 = uint16_t((*w2)>>16), bf16_val3 = uint16_t((*w3)>>16);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val0 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val0) != val0) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val0 & 0x7F80) == 0x7F80 && (bf16_val0 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w0 != 0 && (bf16_val0 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val1 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val1) != val1) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val1 & 0x7F80) == 0x7F80 && (bf16_val1 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w1 != 0 && (bf16_val1 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val2 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val2) != val2) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val2 & 0x7F80) == 0x7F80 && (bf16_val2 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w2 != 0 && (bf16_val2 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    if ((bf16_val3 & 0x7F80) != 0x7F80 && BF16ToFloat(bf16_val3) != val3) {
        FSCR |= (1ULL<<59);
    }
    if ((bf16_val3 & 0x7F80) == 0x7F80 && (bf16_val3 & 0x007F) == 0) {
        FSCR |= (1ULL<<61);
    }
    if (*w3 != 0 && (bf16_val3 & 0x7FFF) == 0) {
        FSCR |= (1ULL<<60);
    }
    uint64_t final_result = (uint64_t)(bf16_val0) | ((uint64_t)(bf16_val1) << 16) | ((uint64_t)(bf16_val2) << 32) | ((uint64_t)(bf16_val3) << 48);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
