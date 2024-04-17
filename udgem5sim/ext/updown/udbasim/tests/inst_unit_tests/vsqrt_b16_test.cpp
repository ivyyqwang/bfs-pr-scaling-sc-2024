#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"
#include <cmath>
#include <cfenv>

using namespace basim;

class Vsqrt_b16Test : public ::testing::Test {
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
TEST_F(Vsqrt_b16Test, vsqrt_b16_0){
    acc0.initSetup(0,"testprogs/binaries/vsqrt_b16_0.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 26466u<<16, uargs1 = 42079u<<16, uargs2 = 20557u<<16, uargs3 = 59230u<<16;
    uint32_t uargs8 = 22438u<<16, uargs9 = 41737u<<16, uargs10 = 42802u<<16, uargs11 = 44417u<<16;
    uint32_t mask = 9;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? sqrt(*fargs0) : (*fargs8);
    val1 = (mask >> 1 & 1) ? sqrt(*fargs1) : (*fargs9);
    val2 = (mask >> 2 & 1) ? sqrt(*fargs2) : (*fargs10);
    val3 = (mask >> 3 & 1) ? sqrt(*fargs3) : (*fargs11);
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
TEST_F(Vsqrt_b16Test, vsqrt_b16_1){
    acc0.initSetup(0,"testprogs/binaries/vsqrt_b16_1.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 36572u<<16, uargs1 = 58633u<<16, uargs2 = 7015u<<16, uargs3 = 30247u<<16;
    uint32_t uargs8 = 41462u<<16, uargs9 = 23388u<<16, uargs10 = 37963u<<16, uargs11 = 30979u<<16;
    uint32_t mask = 14;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? sqrt(*fargs0) : (*fargs8);
    val1 = (mask >> 1 & 1) ? sqrt(*fargs1) : (*fargs9);
    val2 = (mask >> 2 & 1) ? sqrt(*fargs2) : (*fargs10);
    val3 = (mask >> 3 & 1) ? sqrt(*fargs3) : (*fargs11);
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
TEST_F(Vsqrt_b16Test, vsqrt_b16_2){
    acc0.initSetup(0,"testprogs/binaries/vsqrt_b16_2.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 59866u<<16, uargs1 = 33283u<<16, uargs2 = 8142u<<16, uargs3 = 31639u<<16;
    uint32_t uargs8 = 54463u<<16, uargs9 = 28178u<<16, uargs10 = 43214u<<16, uargs11 = 57988u<<16;
    uint32_t mask = 13;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? sqrt(*fargs0) : (*fargs8);
    val1 = (mask >> 1 & 1) ? sqrt(*fargs1) : (*fargs9);
    val2 = (mask >> 2 & 1) ? sqrt(*fargs2) : (*fargs10);
    val3 = (mask >> 3 & 1) ? sqrt(*fargs3) : (*fargs11);
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
TEST_F(Vsqrt_b16Test, vsqrt_b16_3){
    acc0.initSetup(0,"testprogs/binaries/vsqrt_b16_3.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 25578u<<16, uargs1 = 61994u<<16, uargs2 = 31022u<<16, uargs3 = 60137u<<16;
    uint32_t uargs8 = 49984u<<16, uargs9 = 46681u<<16, uargs10 = 6886u<<16, uargs11 = 36408u<<16;
    uint32_t mask = 5;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? sqrt(*fargs0) : (*fargs8);
    val1 = (mask >> 1 & 1) ? sqrt(*fargs1) : (*fargs9);
    val2 = (mask >> 2 & 1) ? sqrt(*fargs2) : (*fargs10);
    val3 = (mask >> 3 & 1) ? sqrt(*fargs3) : (*fargs11);
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
TEST_F(Vsqrt_b16Test, vsqrt_b16_4){
    acc0.initSetup(0,"testprogs/binaries/vsqrt_b16_4.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 28603u<<16, uargs1 = 25147u<<16, uargs2 = 21555u<<16, uargs3 = 28735u<<16;
    uint32_t uargs8 = 54641u<<16, uargs9 = 42984u<<16, uargs10 = 30083u<<16, uargs11 = 47344u<<16;
    uint32_t mask = 12;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? sqrt(*fargs0) : (*fargs8);
    val1 = (mask >> 1 & 1) ? sqrt(*fargs1) : (*fargs9);
    val2 = (mask >> 2 & 1) ? sqrt(*fargs2) : (*fargs10);
    val3 = (mask >> 3 & 1) ? sqrt(*fargs3) : (*fargs11);
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
TEST_F(Vsqrt_b16Test, vsqrt_b16_5){
    acc0.initSetup(0,"testprogs/binaries/vsqrt_b16_5.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 64202u<<16, uargs1 = 16761u<<16, uargs2 = 47381u<<16, uargs3 = 52315u<<16;
    uint32_t uargs8 = 39458u<<16, uargs9 = 27420u<<16, uargs10 = 28067u<<16, uargs11 = 61651u<<16;
    uint32_t mask = 13;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? sqrt(*fargs0) : (*fargs8);
    val1 = (mask >> 1 & 1) ? sqrt(*fargs1) : (*fargs9);
    val2 = (mask >> 2 & 1) ? sqrt(*fargs2) : (*fargs10);
    val3 = (mask >> 3 & 1) ? sqrt(*fargs3) : (*fargs11);
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
TEST_F(Vsqrt_b16Test, vsqrt_b16_6){
    acc0.initSetup(0,"testprogs/binaries/vsqrt_b16_6.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 38798u<<16, uargs1 = 39622u<<16, uargs2 = 54974u<<16, uargs3 = 37454u<<16;
    uint32_t uargs8 = 35103u<<16, uargs9 = 45051u<<16, uargs10 = 39976u<<16, uargs11 = 9237u<<16;
    uint32_t mask = 5;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? sqrt(*fargs0) : (*fargs8);
    val1 = (mask >> 1 & 1) ? sqrt(*fargs1) : (*fargs9);
    val2 = (mask >> 2 & 1) ? sqrt(*fargs2) : (*fargs10);
    val3 = (mask >> 3 & 1) ? sqrt(*fargs3) : (*fargs11);
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
TEST_F(Vsqrt_b16Test, vsqrt_b16_7){
    acc0.initSetup(0,"testprogs/binaries/vsqrt_b16_7.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 23588u<<16, uargs1 = 61604u<<16, uargs2 = 13857u<<16, uargs3 = 36142u<<16;
    uint32_t uargs8 = 56370u<<16, uargs9 = 29584u<<16, uargs10 = 10585u<<16, uargs11 = 64744u<<16;
    uint32_t mask = 4;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? sqrt(*fargs0) : (*fargs8);
    val1 = (mask >> 1 & 1) ? sqrt(*fargs1) : (*fargs9);
    val2 = (mask >> 2 & 1) ? sqrt(*fargs2) : (*fargs10);
    val3 = (mask >> 3 & 1) ? sqrt(*fargs3) : (*fargs11);
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
TEST_F(Vsqrt_b16Test, vsqrt_b16_8){
    acc0.initSetup(0,"testprogs/binaries/vsqrt_b16_8.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 59246u<<16, uargs1 = 41276u<<16, uargs2 = 11955u<<16, uargs3 = 42682u<<16;
    uint32_t uargs8 = 5057u<<16, uargs9 = 47443u<<16, uargs10 = 24469u<<16, uargs11 = 46812u<<16;
    uint32_t mask = 2;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? sqrt(*fargs0) : (*fargs8);
    val1 = (mask >> 1 & 1) ? sqrt(*fargs1) : (*fargs9);
    val2 = (mask >> 2 & 1) ? sqrt(*fargs2) : (*fargs10);
    val3 = (mask >> 3 & 1) ? sqrt(*fargs3) : (*fargs11);
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
TEST_F(Vsqrt_b16Test, vsqrt_b16_9){
    acc0.initSetup(0,"testprogs/binaries/vsqrt_b16_9.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 12043u<<16, uargs1 = 34612u<<16, uargs2 = 16457u<<16, uargs3 = 3505u<<16;
    uint32_t uargs8 = 17804u<<16, uargs9 = 59701u<<16, uargs10 = 59522u<<16, uargs11 = 6592u<<16;
    uint32_t mask = 14;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? sqrt(*fargs0) : (*fargs8);
    val1 = (mask >> 1 & 1) ? sqrt(*fargs1) : (*fargs9);
    val2 = (mask >> 2 & 1) ? sqrt(*fargs2) : (*fargs10);
    val3 = (mask >> 3 & 1) ? sqrt(*fargs3) : (*fargs11);
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
TEST_F(Vsqrt_b16Test, vsqrt_b16_10){
    acc0.initSetup(0,"testprogs/binaries/vsqrt_b16_10.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 28725u<<16, uargs1 = 61655u<<16, uargs2 = 46610u<<16, uargs3 = 53247u<<16;
    uint32_t uargs8 = 44192u<<16, uargs9 = 55226u<<16, uargs10 = 24385u<<16, uargs11 = 11105u<<16;
    uint32_t mask = 7;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? sqrt(*fargs0) : (*fargs8);
    val1 = (mask >> 1 & 1) ? sqrt(*fargs1) : (*fargs9);
    val2 = (mask >> 2 & 1) ? sqrt(*fargs2) : (*fargs10);
    val3 = (mask >> 3 & 1) ? sqrt(*fargs3) : (*fargs11);
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
TEST_F(Vsqrt_b16Test, vsqrt_b16_11){
    acc0.initSetup(0,"testprogs/binaries/vsqrt_b16_11.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 39738u<<16, uargs1 = 39804u<<16, uargs2 = 52683u<<16, uargs3 = 45349u<<16;
    uint32_t uargs8 = 49159u<<16, uargs9 = 36991u<<16, uargs10 = 6468u<<16, uargs11 = 64215u<<16;
    uint32_t mask = 2;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? sqrt(*fargs0) : (*fargs8);
    val1 = (mask >> 1 & 1) ? sqrt(*fargs1) : (*fargs9);
    val2 = (mask >> 2 & 1) ? sqrt(*fargs2) : (*fargs10);
    val3 = (mask >> 3 & 1) ? sqrt(*fargs3) : (*fargs11);
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
TEST_F(Vsqrt_b16Test, vsqrt_b16_12){
    acc0.initSetup(0,"testprogs/binaries/vsqrt_b16_12.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 33610u<<16, uargs1 = 47123u<<16, uargs2 = 8990u<<16, uargs3 = 20952u<<16;
    uint32_t uargs8 = 6285u<<16, uargs9 = 31969u<<16, uargs10 = 882u<<16, uargs11 = 50890u<<16;
    uint32_t mask = 12;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? sqrt(*fargs0) : (*fargs8);
    val1 = (mask >> 1 & 1) ? sqrt(*fargs1) : (*fargs9);
    val2 = (mask >> 2 & 1) ? sqrt(*fargs2) : (*fargs10);
    val3 = (mask >> 3 & 1) ? sqrt(*fargs3) : (*fargs11);
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
TEST_F(Vsqrt_b16Test, vsqrt_b16_13){
    acc0.initSetup(0,"testprogs/binaries/vsqrt_b16_13.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 43004u<<16, uargs1 = 58021u<<16, uargs2 = 7170u<<16, uargs3 = 4680u<<16;
    uint32_t uargs8 = 8170u<<16, uargs9 = 32238u<<16, uargs10 = 20800u<<16, uargs11 = 61989u<<16;
    uint32_t mask = 5;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? sqrt(*fargs0) : (*fargs8);
    val1 = (mask >> 1 & 1) ? sqrt(*fargs1) : (*fargs9);
    val2 = (mask >> 2 & 1) ? sqrt(*fargs2) : (*fargs10);
    val3 = (mask >> 3 & 1) ? sqrt(*fargs3) : (*fargs11);
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
TEST_F(Vsqrt_b16Test, vsqrt_b16_14){
    acc0.initSetup(0,"testprogs/binaries/vsqrt_b16_14.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 11874u<<16, uargs1 = 44730u<<16, uargs2 = 47417u<<16, uargs3 = 6099u<<16;
    uint32_t uargs8 = 35974u<<16, uargs9 = 4385u<<16, uargs10 = 6083u<<16, uargs11 = 49915u<<16;
    uint32_t mask = 14;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? sqrt(*fargs0) : (*fargs8);
    val1 = (mask >> 1 & 1) ? sqrt(*fargs1) : (*fargs9);
    val2 = (mask >> 2 & 1) ? sqrt(*fargs2) : (*fargs10);
    val3 = (mask >> 3 & 1) ? sqrt(*fargs3) : (*fargs11);
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
TEST_F(Vsqrt_b16Test, vsqrt_b16_15){
    acc0.initSetup(0,"testprogs/binaries/vsqrt_b16_15.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 44350u<<16, uargs1 = 17693u<<16, uargs2 = 57754u<<16, uargs3 = 43639u<<16;
    uint32_t uargs8 = 41181u<<16, uargs9 = 37915u<<16, uargs10 = 58142u<<16, uargs11 = 42639u<<16;
    uint32_t mask = 11;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? sqrt(*fargs0) : (*fargs8);
    val1 = (mask >> 1 & 1) ? sqrt(*fargs1) : (*fargs9);
    val2 = (mask >> 2 & 1) ? sqrt(*fargs2) : (*fargs10);
    val3 = (mask >> 3 & 1) ? sqrt(*fargs3) : (*fargs11);
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
TEST_F(Vsqrt_b16Test, vsqrt_b16_16){
    acc0.initSetup(0,"testprogs/binaries/vsqrt_b16_16.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 55878u<<16, uargs1 = 22728u<<16, uargs2 = 25140u<<16, uargs3 = 12086u<<16;
    uint32_t uargs8 = 65037u<<16, uargs9 = 39624u<<16, uargs10 = 28322u<<16, uargs11 = 48114u<<16;
    uint32_t mask = 7;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? sqrt(*fargs0) : (*fargs8);
    val1 = (mask >> 1 & 1) ? sqrt(*fargs1) : (*fargs9);
    val2 = (mask >> 2 & 1) ? sqrt(*fargs2) : (*fargs10);
    val3 = (mask >> 3 & 1) ? sqrt(*fargs3) : (*fargs11);
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
TEST_F(Vsqrt_b16Test, vsqrt_b16_17){
    acc0.initSetup(0,"testprogs/binaries/vsqrt_b16_17.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 50078u<<16, uargs1 = 28975u<<16, uargs2 = 58232u<<16, uargs3 = 22173u<<16;
    uint32_t uargs8 = 20816u<<16, uargs9 = 26490u<<16, uargs10 = 45248u<<16, uargs11 = 15948u<<16;
    uint32_t mask = 6;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? sqrt(*fargs0) : (*fargs8);
    val1 = (mask >> 1 & 1) ? sqrt(*fargs1) : (*fargs9);
    val2 = (mask >> 2 & 1) ? sqrt(*fargs2) : (*fargs10);
    val3 = (mask >> 3 & 1) ? sqrt(*fargs3) : (*fargs11);
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
TEST_F(Vsqrt_b16Test, vsqrt_b16_18){
    acc0.initSetup(0,"testprogs/binaries/vsqrt_b16_18.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 19422u<<16, uargs1 = 15209u<<16, uargs2 = 48975u<<16, uargs3 = 63995u<<16;
    uint32_t uargs8 = 19881u<<16, uargs9 = 45911u<<16, uargs10 = 58434u<<16, uargs11 = 43762u<<16;
    uint32_t mask = 4;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? sqrt(*fargs0) : (*fargs8);
    val1 = (mask >> 1 & 1) ? sqrt(*fargs1) : (*fargs9);
    val2 = (mask >> 2 & 1) ? sqrt(*fargs2) : (*fargs10);
    val3 = (mask >> 3 & 1) ? sqrt(*fargs3) : (*fargs11);
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
TEST_F(Vsqrt_b16Test, vsqrt_b16_19){
    acc0.initSetup(0,"testprogs/binaries/vsqrt_b16_19.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 55136u<<16, uargs1 = 48937u<<16, uargs2 = 55706u<<16, uargs3 = 36953u<<16;
    uint32_t uargs8 = 2942u<<16, uargs9 = 55568u<<16, uargs10 = 40944u<<16, uargs11 = 39241u<<16;
    uint32_t mask = 9;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? sqrt(*fargs0) : (*fargs8);
    val1 = (mask >> 1 & 1) ? sqrt(*fargs1) : (*fargs9);
    val2 = (mask >> 2 & 1) ? sqrt(*fargs2) : (*fargs10);
    val3 = (mask >> 3 & 1) ? sqrt(*fargs3) : (*fargs11);
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
