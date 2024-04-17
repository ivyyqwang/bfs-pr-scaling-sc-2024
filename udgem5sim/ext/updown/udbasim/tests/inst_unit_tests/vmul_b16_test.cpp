#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"
#include <cmath>
#include <cfenv>

using namespace basim;

class Vmul_b16Test : public ::testing::Test {
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
TEST_F(Vmul_b16Test, vmul_b16_0){
    acc0.initSetup(0,"testprogs/binaries/vmul_b16_0.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 46869u<<16, uargs1 = 54372u<<16, uargs2 = 63248u<<16, uargs3 = 36052u<<16;
    uint32_t uargs4 = 25086u<<16, uargs5 = 51201u<<16, uargs6 = 51371u<<16, uargs7 = 58504u<<16;
    uint32_t uargs8 = 31969u<<16, uargs9 = 18810u<<16, uargs10 = 14652u<<16, uargs11 = 51682u<<16;
    uint32_t mask = 7;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 * *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 * *fargs7) : (*fargs11);
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
TEST_F(Vmul_b16Test, vmul_b16_1){
    acc0.initSetup(0,"testprogs/binaries/vmul_b16_1.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 38627u<<16, uargs1 = 8647u<<16, uargs2 = 897u<<16, uargs3 = 20654u<<16;
    uint32_t uargs4 = 54688u<<16, uargs5 = 14262u<<16, uargs6 = 60897u<<16, uargs7 = 46901u<<16;
    uint32_t uargs8 = 29787u<<16, uargs9 = 13310u<<16, uargs10 = 2325u<<16, uargs11 = 58508u<<16;
    uint32_t mask = 9;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 * *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 * *fargs7) : (*fargs11);
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
TEST_F(Vmul_b16Test, vmul_b16_2){
    acc0.initSetup(0,"testprogs/binaries/vmul_b16_2.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 55075u<<16, uargs1 = 16537u<<16, uargs2 = 19045u<<16, uargs3 = 16741u<<16;
    uint32_t uargs4 = 36991u<<16, uargs5 = 16220u<<16, uargs6 = 18115u<<16, uargs7 = 24583u<<16;
    uint32_t uargs8 = 44951u<<16, uargs9 = 38216u<<16, uargs10 = 58754u<<16, uargs11 = 3102u<<16;
    uint32_t mask = 15;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 * *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 * *fargs7) : (*fargs11);
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
TEST_F(Vmul_b16Test, vmul_b16_3){
    acc0.initSetup(0,"testprogs/binaries/vmul_b16_3.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 13041u<<16, uargs1 = 7562u<<16, uargs2 = 6430u<<16, uargs3 = 44240u<<16;
    uint32_t uargs4 = 42975u<<16, uargs5 = 23401u<<16, uargs6 = 46103u<<16, uargs7 = 51068u<<16;
    uint32_t uargs8 = 46168u<<16, uargs9 = 31529u<<16, uargs10 = 49351u<<16, uargs11 = 55900u<<16;
    uint32_t mask = 5;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 * *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 * *fargs7) : (*fargs11);
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
TEST_F(Vmul_b16Test, vmul_b16_4){
    acc0.initSetup(0,"testprogs/binaries/vmul_b16_4.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 57962u<<16, uargs1 = 52722u<<16, uargs2 = 16774u<<16, uargs3 = 379u<<16;
    uint32_t uargs4 = 62683u<<16, uargs5 = 20305u<<16, uargs6 = 34797u<<16, uargs7 = 41946u<<16;
    uint32_t uargs8 = 37056u<<16, uargs9 = 29618u<<16, uargs10 = 37409u<<16, uargs11 = 39062u<<16;
    uint32_t mask = 7;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 * *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 * *fargs7) : (*fargs11);
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
TEST_F(Vmul_b16Test, vmul_b16_5){
    acc0.initSetup(0,"testprogs/binaries/vmul_b16_5.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 15896u<<16, uargs1 = 50778u<<16, uargs2 = 10523u<<16, uargs3 = 5992u<<16;
    uint32_t uargs4 = 20413u<<16, uargs5 = 58689u<<16, uargs6 = 27287u<<16, uargs7 = 13839u<<16;
    uint32_t uargs8 = 58550u<<16, uargs9 = 6265u<<16, uargs10 = 61392u<<16, uargs11 = 48383u<<16;
    uint32_t mask = 7;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 * *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 * *fargs7) : (*fargs11);
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
TEST_F(Vmul_b16Test, vmul_b16_6){
    acc0.initSetup(0,"testprogs/binaries/vmul_b16_6.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 29537u<<16, uargs1 = 26852u<<16, uargs2 = 5327u<<16, uargs3 = 5601u<<16;
    uint32_t uargs4 = 14870u<<16, uargs5 = 62132u<<16, uargs6 = 50107u<<16, uargs7 = 10093u<<16;
    uint32_t uargs8 = 26214u<<16, uargs9 = 56509u<<16, uargs10 = 60713u<<16, uargs11 = 25450u<<16;
    uint32_t mask = 11;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 * *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 * *fargs7) : (*fargs11);
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
TEST_F(Vmul_b16Test, vmul_b16_7){
    acc0.initSetup(0,"testprogs/binaries/vmul_b16_7.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 51104u<<16, uargs1 = 61832u<<16, uargs2 = 33974u<<16, uargs3 = 48284u<<16;
    uint32_t uargs4 = 49245u<<16, uargs5 = 2011u<<16, uargs6 = 42766u<<16, uargs7 = 39471u<<16;
    uint32_t uargs8 = 18450u<<16, uargs9 = 44382u<<16, uargs10 = 44875u<<16, uargs11 = 47702u<<16;
    uint32_t mask = 1;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 * *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 * *fargs7) : (*fargs11);
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
TEST_F(Vmul_b16Test, vmul_b16_8){
    acc0.initSetup(0,"testprogs/binaries/vmul_b16_8.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 28641u<<16, uargs1 = 8248u<<16, uargs2 = 23822u<<16, uargs3 = 25316u<<16;
    uint32_t uargs4 = 11314u<<16, uargs5 = 36878u<<16, uargs6 = 44816u<<16, uargs7 = 30782u<<16;
    uint32_t uargs8 = 33627u<<16, uargs9 = 15059u<<16, uargs10 = 36584u<<16, uargs11 = 44787u<<16;
    uint32_t mask = 8;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 * *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 * *fargs7) : (*fargs11);
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
TEST_F(Vmul_b16Test, vmul_b16_9){
    acc0.initSetup(0,"testprogs/binaries/vmul_b16_9.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 58425u<<16, uargs1 = 34932u<<16, uargs2 = 40867u<<16, uargs3 = 40609u<<16;
    uint32_t uargs4 = 25329u<<16, uargs5 = 14844u<<16, uargs6 = 29125u<<16, uargs7 = 51542u<<16;
    uint32_t uargs8 = 7717u<<16, uargs9 = 39770u<<16, uargs10 = 44581u<<16, uargs11 = 59297u<<16;
    uint32_t mask = 15;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 * *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 * *fargs7) : (*fargs11);
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
TEST_F(Vmul_b16Test, vmul_b16_10){
    acc0.initSetup(0,"testprogs/binaries/vmul_b16_10.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 20487u<<16, uargs1 = 40568u<<16, uargs2 = 64521u<<16, uargs3 = 14741u<<16;
    uint32_t uargs4 = 22685u<<16, uargs5 = 22217u<<16, uargs6 = 61386u<<16, uargs7 = 47919u<<16;
    uint32_t uargs8 = 56317u<<16, uargs9 = 12497u<<16, uargs10 = 46233u<<16, uargs11 = 2771u<<16;
    uint32_t mask = 5;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 * *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 * *fargs7) : (*fargs11);
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
TEST_F(Vmul_b16Test, vmul_b16_11){
    acc0.initSetup(0,"testprogs/binaries/vmul_b16_11.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 46645u<<16, uargs1 = 11352u<<16, uargs2 = 18225u<<16, uargs3 = 58155u<<16;
    uint32_t uargs4 = 13572u<<16, uargs5 = 46393u<<16, uargs6 = 34340u<<16, uargs7 = 23285u<<16;
    uint32_t uargs8 = 47655u<<16, uargs9 = 7438u<<16, uargs10 = 42710u<<16, uargs11 = 5504u<<16;
    uint32_t mask = 11;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 * *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 * *fargs7) : (*fargs11);
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
TEST_F(Vmul_b16Test, vmul_b16_12){
    acc0.initSetup(0,"testprogs/binaries/vmul_b16_12.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 18450u<<16, uargs1 = 9153u<<16, uargs2 = 14212u<<16, uargs3 = 7344u<<16;
    uint32_t uargs4 = 41642u<<16, uargs5 = 62719u<<16, uargs6 = 36372u<<16, uargs7 = 32114u<<16;
    uint32_t uargs8 = 46700u<<16, uargs9 = 41579u<<16, uargs10 = 50109u<<16, uargs11 = 4295u<<16;
    uint32_t mask = 1;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 * *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 * *fargs7) : (*fargs11);
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
TEST_F(Vmul_b16Test, vmul_b16_13){
    acc0.initSetup(0,"testprogs/binaries/vmul_b16_13.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 40317u<<16, uargs1 = 25970u<<16, uargs2 = 14535u<<16, uargs3 = 63388u<<16;
    uint32_t uargs4 = 465u<<16, uargs5 = 26604u<<16, uargs6 = 34270u<<16, uargs7 = 1140u<<16;
    uint32_t uargs8 = 17468u<<16, uargs9 = 52517u<<16, uargs10 = 56445u<<16, uargs11 = 53008u<<16;
    uint32_t mask = 3;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 * *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 * *fargs7) : (*fargs11);
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
TEST_F(Vmul_b16Test, vmul_b16_14){
    acc0.initSetup(0,"testprogs/binaries/vmul_b16_14.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 39512u<<16, uargs1 = 53205u<<16, uargs2 = 38737u<<16, uargs3 = 36580u<<16;
    uint32_t uargs4 = 32558u<<16, uargs5 = 5802u<<16, uargs6 = 31357u<<16, uargs7 = 3981u<<16;
    uint32_t uargs8 = 59149u<<16, uargs9 = 300u<<16, uargs10 = 59054u<<16, uargs11 = 15817u<<16;
    uint32_t mask = 15;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 * *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 * *fargs7) : (*fargs11);
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
TEST_F(Vmul_b16Test, vmul_b16_15){
    acc0.initSetup(0,"testprogs/binaries/vmul_b16_15.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 58712u<<16, uargs1 = 2205u<<16, uargs2 = 40708u<<16, uargs3 = 10331u<<16;
    uint32_t uargs4 = 6539u<<16, uargs5 = 41838u<<16, uargs6 = 46182u<<16, uargs7 = 58u<<16;
    uint32_t uargs8 = 45194u<<16, uargs9 = 41721u<<16, uargs10 = 22322u<<16, uargs11 = 23344u<<16;
    uint32_t mask = 15;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 * *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 * *fargs7) : (*fargs11);
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
TEST_F(Vmul_b16Test, vmul_b16_16){
    acc0.initSetup(0,"testprogs/binaries/vmul_b16_16.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 49314u<<16, uargs1 = 41207u<<16, uargs2 = 45393u<<16, uargs3 = 35326u<<16;
    uint32_t uargs4 = 30898u<<16, uargs5 = 26734u<<16, uargs6 = 22506u<<16, uargs7 = 41341u<<16;
    uint32_t uargs8 = 257u<<16, uargs9 = 15960u<<16, uargs10 = 38864u<<16, uargs11 = 44744u<<16;
    uint32_t mask = 8;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 * *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 * *fargs7) : (*fargs11);
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
TEST_F(Vmul_b16Test, vmul_b16_17){
    acc0.initSetup(0,"testprogs/binaries/vmul_b16_17.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 10462u<<16, uargs1 = 57078u<<16, uargs2 = 63280u<<16, uargs3 = 23755u<<16;
    uint32_t uargs4 = 1790u<<16, uargs5 = 17497u<<16, uargs6 = 22902u<<16, uargs7 = 7897u<<16;
    uint32_t uargs8 = 28955u<<16, uargs9 = 27836u<<16, uargs10 = 29037u<<16, uargs11 = 10379u<<16;
    uint32_t mask = 7;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 * *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 * *fargs7) : (*fargs11);
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
TEST_F(Vmul_b16Test, vmul_b16_18){
    acc0.initSetup(0,"testprogs/binaries/vmul_b16_18.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 40684u<<16, uargs1 = 10517u<<16, uargs2 = 32947u<<16, uargs3 = 51344u<<16;
    uint32_t uargs4 = 49017u<<16, uargs5 = 49097u<<16, uargs6 = 3991u<<16, uargs7 = 51759u<<16;
    uint32_t uargs8 = 4787u<<16, uargs9 = 9125u<<16, uargs10 = 39429u<<16, uargs11 = 55319u<<16;
    uint32_t mask = 8;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 * *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 * *fargs7) : (*fargs11);
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
TEST_F(Vmul_b16Test, vmul_b16_19){
    acc0.initSetup(0,"testprogs/binaries/vmul_b16_19.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 21266u<<16, uargs1 = 50697u<<16, uargs2 = 13364u<<16, uargs3 = 7429u<<16;
    uint32_t uargs4 = 55369u<<16, uargs5 = 10527u<<16, uargs6 = 58514u<<16, uargs7 = 23036u<<16;
    uint32_t uargs8 = 38553u<<16, uargs9 = 36258u<<16, uargs10 = 24937u<<16, uargs11 = 455u<<16;
    uint32_t mask = 3;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs4) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs5) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 * *fargs6) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 * *fargs7) : (*fargs11);
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
