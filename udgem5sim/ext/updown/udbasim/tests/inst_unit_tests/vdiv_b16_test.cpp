#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"
#include <cmath>
#include <cfenv>

using namespace basim;

class Vdiv_b16Test : public ::testing::Test {
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
TEST_F(Vdiv_b16Test, vdiv_b16_0){
    acc0.initSetup(0,"testprogs/binaries/vdiv_b16_0.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 10490u<<16, uargs1 = 20196u<<16, uargs2 = 51649u<<16, uargs3 = 61612u<<16;
    uint32_t uargs4 = 64436u<<16, uargs5 = 60294u<<16, uargs6 = 7551u<<16, uargs7 = 36589u<<16;
    uint32_t uargs8 = 22367u<<16, uargs9 = 1175u<<16, uargs10 = 39334u<<16, uargs11 = 23285u<<16;
    uint32_t mask = 13;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 / *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 / *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 / *fargs7) : (*fargs11);
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
TEST_F(Vdiv_b16Test, vdiv_b16_1){
    acc0.initSetup(0,"testprogs/binaries/vdiv_b16_1.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 9699u<<16, uargs1 = 4118u<<16, uargs2 = 44265u<<16, uargs3 = 1349u<<16;
    uint32_t uargs4 = 50608u<<16, uargs5 = 7503u<<16, uargs6 = 15777u<<16, uargs7 = 7996u<<16;
    uint32_t uargs8 = 14846u<<16, uargs9 = 49180u<<16, uargs10 = 47371u<<16, uargs11 = 26364u<<16;
    uint32_t mask = 8;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 / *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 / *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 / *fargs7) : (*fargs11);
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
TEST_F(Vdiv_b16Test, vdiv_b16_2){
    acc0.initSetup(0,"testprogs/binaries/vdiv_b16_2.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 36478u<<16, uargs1 = 40085u<<16, uargs2 = 49217u<<16, uargs3 = 53409u<<16;
    uint32_t uargs4 = 63003u<<16, uargs5 = 22891u<<16, uargs6 = 11446u<<16, uargs7 = 37610u<<16;
    uint32_t uargs8 = 22328u<<16, uargs9 = 44118u<<16, uargs10 = 64534u<<16, uargs11 = 32151u<<16;
    uint32_t mask = 4;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 / *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 / *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 / *fargs7) : (*fargs11);
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
TEST_F(Vdiv_b16Test, vdiv_b16_3){
    acc0.initSetup(0,"testprogs/binaries/vdiv_b16_3.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 22123u<<16, uargs1 = 64921u<<16, uargs2 = 14958u<<16, uargs3 = 4809u<<16;
    uint32_t uargs4 = 20636u<<16, uargs5 = 34011u<<16, uargs6 = 57405u<<16, uargs7 = 43826u<<16;
    uint32_t uargs8 = 4887u<<16, uargs9 = 37513u<<16, uargs10 = 16305u<<16, uargs11 = 29902u<<16;
    uint32_t mask = 14;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 / *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 / *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 / *fargs7) : (*fargs11);
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
TEST_F(Vdiv_b16Test, vdiv_b16_4){
    acc0.initSetup(0,"testprogs/binaries/vdiv_b16_4.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 4890u<<16, uargs1 = 18133u<<16, uargs2 = 35517u<<16, uargs3 = 59298u<<16;
    uint32_t uargs4 = 51426u<<16, uargs5 = 56793u<<16, uargs6 = 24169u<<16, uargs7 = 16206u<<16;
    uint32_t uargs8 = 4803u<<16, uargs9 = 50937u<<16, uargs10 = 28046u<<16, uargs11 = 18021u<<16;
    uint32_t mask = 8;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 / *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 / *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 / *fargs7) : (*fargs11);
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
TEST_F(Vdiv_b16Test, vdiv_b16_5){
    acc0.initSetup(0,"testprogs/binaries/vdiv_b16_5.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 57634u<<16, uargs1 = 7701u<<16, uargs2 = 58275u<<16, uargs3 = 10894u<<16;
    uint32_t uargs4 = 10506u<<16, uargs5 = 51731u<<16, uargs6 = 47686u<<16, uargs7 = 41277u<<16;
    uint32_t uargs8 = 19624u<<16, uargs9 = 55529u<<16, uargs10 = 17545u<<16, uargs11 = 31512u<<16;
    uint32_t mask = 6;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 / *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 / *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 / *fargs7) : (*fargs11);
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
TEST_F(Vdiv_b16Test, vdiv_b16_6){
    acc0.initSetup(0,"testprogs/binaries/vdiv_b16_6.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 38582u<<16, uargs1 = 16272u<<16, uargs2 = 35380u<<16, uargs3 = 30405u<<16;
    uint32_t uargs4 = 7024u<<16, uargs5 = 56396u<<16, uargs6 = 21061u<<16, uargs7 = 26406u<<16;
    uint32_t uargs8 = 8446u<<16, uargs9 = 24781u<<16, uargs10 = 45541u<<16, uargs11 = 56821u<<16;
    uint32_t mask = 8;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 / *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 / *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 / *fargs7) : (*fargs11);
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
TEST_F(Vdiv_b16Test, vdiv_b16_7){
    acc0.initSetup(0,"testprogs/binaries/vdiv_b16_7.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 6634u<<16, uargs1 = 41326u<<16, uargs2 = 49303u<<16, uargs3 = 52829u<<16;
    uint32_t uargs4 = 34475u<<16, uargs5 = 287u<<16, uargs6 = 30256u<<16, uargs7 = 45355u<<16;
    uint32_t uargs8 = 28958u<<16, uargs9 = 13170u<<16, uargs10 = 49420u<<16, uargs11 = 12114u<<16;
    uint32_t mask = 7;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 / *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 / *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 / *fargs7) : (*fargs11);
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
TEST_F(Vdiv_b16Test, vdiv_b16_8){
    acc0.initSetup(0,"testprogs/binaries/vdiv_b16_8.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 12496u<<16, uargs1 = 6779u<<16, uargs2 = 11109u<<16, uargs3 = 14583u<<16;
    uint32_t uargs4 = 56362u<<16, uargs5 = 4589u<<16, uargs6 = 31152u<<16, uargs7 = 47506u<<16;
    uint32_t uargs8 = 1944u<<16, uargs9 = 24821u<<16, uargs10 = 44825u<<16, uargs11 = 55242u<<16;
    uint32_t mask = 1;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 / *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 / *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 / *fargs7) : (*fargs11);
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
TEST_F(Vdiv_b16Test, vdiv_b16_9){
    acc0.initSetup(0,"testprogs/binaries/vdiv_b16_9.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 45100u<<16, uargs1 = 1581u<<16, uargs2 = 23603u<<16, uargs3 = 54675u<<16;
    uint32_t uargs4 = 29217u<<16, uargs5 = 37012u<<16, uargs6 = 54926u<<16, uargs7 = 50741u<<16;
    uint32_t uargs8 = 4647u<<16, uargs9 = 8776u<<16, uargs10 = 23857u<<16, uargs11 = 6259u<<16;
    uint32_t mask = 13;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 / *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 / *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 / *fargs7) : (*fargs11);
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
TEST_F(Vdiv_b16Test, vdiv_b16_10){
    acc0.initSetup(0,"testprogs/binaries/vdiv_b16_10.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 25099u<<16, uargs1 = 60653u<<16, uargs2 = 25376u<<16, uargs3 = 53112u<<16;
    uint32_t uargs4 = 16044u<<16, uargs5 = 31071u<<16, uargs6 = 4212u<<16, uargs7 = 2573u<<16;
    uint32_t uargs8 = 47220u<<16, uargs9 = 41900u<<16, uargs10 = 32565u<<16, uargs11 = 3795u<<16;
    uint32_t mask = 3;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 / *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 / *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 / *fargs7) : (*fargs11);
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
TEST_F(Vdiv_b16Test, vdiv_b16_11){
    acc0.initSetup(0,"testprogs/binaries/vdiv_b16_11.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 15193u<<16, uargs1 = 27642u<<16, uargs2 = 56235u<<16, uargs3 = 259u<<16;
    uint32_t uargs4 = 41045u<<16, uargs5 = 12614u<<16, uargs6 = 37497u<<16, uargs7 = 6053u<<16;
    uint32_t uargs8 = 41073u<<16, uargs9 = 35313u<<16, uargs10 = 42528u<<16, uargs11 = 43647u<<16;
    uint32_t mask = 3;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 / *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 / *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 / *fargs7) : (*fargs11);
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
TEST_F(Vdiv_b16Test, vdiv_b16_12){
    acc0.initSetup(0,"testprogs/binaries/vdiv_b16_12.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 60543u<<16, uargs1 = 34969u<<16, uargs2 = 41399u<<16, uargs3 = 34870u<<16;
    uint32_t uargs4 = 28085u<<16, uargs5 = 33125u<<16, uargs6 = 61061u<<16, uargs7 = 35722u<<16;
    uint32_t uargs8 = 14557u<<16, uargs9 = 29914u<<16, uargs10 = 41939u<<16, uargs11 = 31722u<<16;
    uint32_t mask = 12;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 / *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 / *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 / *fargs7) : (*fargs11);
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
TEST_F(Vdiv_b16Test, vdiv_b16_13){
    acc0.initSetup(0,"testprogs/binaries/vdiv_b16_13.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 16961u<<16, uargs1 = 34876u<<16, uargs2 = 5422u<<16, uargs3 = 15597u<<16;
    uint32_t uargs4 = 22665u<<16, uargs5 = 35534u<<16, uargs6 = 36924u<<16, uargs7 = 3439u<<16;
    uint32_t uargs8 = 47986u<<16, uargs9 = 6648u<<16, uargs10 = 37884u<<16, uargs11 = 25819u<<16;
    uint32_t mask = 6;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 / *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 / *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 / *fargs7) : (*fargs11);
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
TEST_F(Vdiv_b16Test, vdiv_b16_14){
    acc0.initSetup(0,"testprogs/binaries/vdiv_b16_14.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 52686u<<16, uargs1 = 13882u<<16, uargs2 = 52107u<<16, uargs3 = 35203u<<16;
    uint32_t uargs4 = 41783u<<16, uargs5 = 30721u<<16, uargs6 = 48370u<<16, uargs7 = 46631u<<16;
    uint32_t uargs8 = 50955u<<16, uargs9 = 64715u<<16, uargs10 = 20847u<<16, uargs11 = 37437u<<16;
    uint32_t mask = 12;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 / *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 / *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 / *fargs7) : (*fargs11);
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
TEST_F(Vdiv_b16Test, vdiv_b16_15){
    acc0.initSetup(0,"testprogs/binaries/vdiv_b16_15.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 42422u<<16, uargs1 = 23254u<<16, uargs2 = 40179u<<16, uargs3 = 36433u<<16;
    uint32_t uargs4 = 26628u<<16, uargs5 = 5007u<<16, uargs6 = 30928u<<16, uargs7 = 63254u<<16;
    uint32_t uargs8 = 38816u<<16, uargs9 = 34057u<<16, uargs10 = 629u<<16, uargs11 = 60860u<<16;
    uint32_t mask = 14;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 / *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 / *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 / *fargs7) : (*fargs11);
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
TEST_F(Vdiv_b16Test, vdiv_b16_16){
    acc0.initSetup(0,"testprogs/binaries/vdiv_b16_16.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 10728u<<16, uargs1 = 29375u<<16, uargs2 = 38976u<<16, uargs3 = 53561u<<16;
    uint32_t uargs4 = 36795u<<16, uargs5 = 18551u<<16, uargs6 = 33387u<<16, uargs7 = 38627u<<16;
    uint32_t uargs8 = 2398u<<16, uargs9 = 10901u<<16, uargs10 = 40200u<<16, uargs11 = 63171u<<16;
    uint32_t mask = 1;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 / *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 / *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 / *fargs7) : (*fargs11);
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
TEST_F(Vdiv_b16Test, vdiv_b16_17){
    acc0.initSetup(0,"testprogs/binaries/vdiv_b16_17.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 22404u<<16, uargs1 = 9843u<<16, uargs2 = 45146u<<16, uargs3 = 12713u<<16;
    uint32_t uargs4 = 23770u<<16, uargs5 = 36903u<<16, uargs6 = 5576u<<16, uargs7 = 17012u<<16;
    uint32_t uargs8 = 8916u<<16, uargs9 = 12260u<<16, uargs10 = 62328u<<16, uargs11 = 34329u<<16;
    uint32_t mask = 1;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 / *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 / *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 / *fargs7) : (*fargs11);
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
TEST_F(Vdiv_b16Test, vdiv_b16_18){
    acc0.initSetup(0,"testprogs/binaries/vdiv_b16_18.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 8418u<<16, uargs1 = 42820u<<16, uargs2 = 7394u<<16, uargs3 = 60079u<<16;
    uint32_t uargs4 = 36458u<<16, uargs5 = 10190u<<16, uargs6 = 11537u<<16, uargs7 = 52148u<<16;
    uint32_t uargs8 = 52719u<<16, uargs9 = 19957u<<16, uargs10 = 27132u<<16, uargs11 = 2558u<<16;
    uint32_t mask = 14;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 / *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 / *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 / *fargs7) : (*fargs11);
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
TEST_F(Vdiv_b16Test, vdiv_b16_19){
    acc0.initSetup(0,"testprogs/binaries/vdiv_b16_19.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 46822u<<16, uargs1 = 20567u<<16, uargs2 = 55617u<<16, uargs3 = 30159u<<16;
    uint32_t uargs4 = 62165u<<16, uargs5 = 16863u<<16, uargs6 = 18818u<<16, uargs7 = 4745u<<16;
    uint32_t uargs8 = 28705u<<16, uargs9 = 2659u<<16, uargs10 = 57614u<<16, uargs11 = 20992u<<16;
    uint32_t mask = 2;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 / *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 / *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 / *fargs7) : (*fargs11);
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
