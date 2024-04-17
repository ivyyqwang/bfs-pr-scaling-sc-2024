#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"
#include <cmath>
#include <cfenv>

using namespace basim;

class Vmadd_b16Test : public ::testing::Test {
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
TEST_F(Vmadd_b16Test, vmadd_b16_0){
    acc0.initSetup(0,"testprogs/binaries/vmadd_b16_0.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 38655u<<16, uargs1 = 8022u<<16, uargs2 = 25049u<<16, uargs3 = 11175u<<16;
    uint32_t uargs4 = 64061u<<16, uargs5 = 17592u<<16, uargs6 = 29877u<<16, uargs7 = 27908u<<16;
    uint32_t uargs8 = 52418u<<16, uargs9 = 33038u<<16, uargs10 = 22202u<<16, uargs11 = 10053u<<16;
    uint32_t mask = 2;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs4 + *fargs8) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs5 + *fargs9) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 * *fargs6 + *fargs10) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 * *fargs7 + *fargs11) : (*fargs11);
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
TEST_F(Vmadd_b16Test, vmadd_b16_1){
    acc0.initSetup(0,"testprogs/binaries/vmadd_b16_1.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 22141u<<16, uargs1 = 34242u<<16, uargs2 = 55482u<<16, uargs3 = 59766u<<16;
    uint32_t uargs4 = 1240u<<16, uargs5 = 46125u<<16, uargs6 = 8959u<<16, uargs7 = 58513u<<16;
    uint32_t uargs8 = 17789u<<16, uargs9 = 9440u<<16, uargs10 = 9359u<<16, uargs11 = 4861u<<16;
    uint32_t mask = 10;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs4 + *fargs8) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs5 + *fargs9) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 * *fargs6 + *fargs10) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 * *fargs7 + *fargs11) : (*fargs11);
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
TEST_F(Vmadd_b16Test, vmadd_b16_2){
    acc0.initSetup(0,"testprogs/binaries/vmadd_b16_2.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 3991u<<16, uargs1 = 39451u<<16, uargs2 = 25694u<<16, uargs3 = 21609u<<16;
    uint32_t uargs4 = 25212u<<16, uargs5 = 52730u<<16, uargs6 = 26119u<<16, uargs7 = 59826u<<16;
    uint32_t uargs8 = 26102u<<16, uargs9 = 54528u<<16, uargs10 = 35450u<<16, uargs11 = 53963u<<16;
    uint32_t mask = 8;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs4 + *fargs8) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs5 + *fargs9) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 * *fargs6 + *fargs10) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 * *fargs7 + *fargs11) : (*fargs11);
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
TEST_F(Vmadd_b16Test, vmadd_b16_3){
    acc0.initSetup(0,"testprogs/binaries/vmadd_b16_3.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 49891u<<16, uargs1 = 43069u<<16, uargs2 = 58592u<<16, uargs3 = 60493u<<16;
    uint32_t uargs4 = 25392u<<16, uargs5 = 62545u<<16, uargs6 = 50485u<<16, uargs7 = 22680u<<16;
    uint32_t uargs8 = 57491u<<16, uargs9 = 22704u<<16, uargs10 = 47591u<<16, uargs11 = 38987u<<16;
    uint32_t mask = 15;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs4 + *fargs8) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs5 + *fargs9) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 * *fargs6 + *fargs10) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 * *fargs7 + *fargs11) : (*fargs11);
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
TEST_F(Vmadd_b16Test, vmadd_b16_4){
    acc0.initSetup(0,"testprogs/binaries/vmadd_b16_4.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 43521u<<16, uargs1 = 7213u<<16, uargs2 = 47043u<<16, uargs3 = 7963u<<16;
    uint32_t uargs4 = 24775u<<16, uargs5 = 1972u<<16, uargs6 = 6590u<<16, uargs7 = 27742u<<16;
    uint32_t uargs8 = 21857u<<16, uargs9 = 40218u<<16, uargs10 = 41019u<<16, uargs11 = 9673u<<16;
    uint32_t mask = 14;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs4 + *fargs8) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs5 + *fargs9) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 * *fargs6 + *fargs10) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 * *fargs7 + *fargs11) : (*fargs11);
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
TEST_F(Vmadd_b16Test, vmadd_b16_5){
    acc0.initSetup(0,"testprogs/binaries/vmadd_b16_5.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 61203u<<16, uargs1 = 11287u<<16, uargs2 = 13068u<<16, uargs3 = 54089u<<16;
    uint32_t uargs4 = 41792u<<16, uargs5 = 19422u<<16, uargs6 = 61559u<<16, uargs7 = 25633u<<16;
    uint32_t uargs8 = 4571u<<16, uargs9 = 42480u<<16, uargs10 = 16616u<<16, uargs11 = 15095u<<16;
    uint32_t mask = 1;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs4 + *fargs8) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs5 + *fargs9) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 * *fargs6 + *fargs10) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 * *fargs7 + *fargs11) : (*fargs11);
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
TEST_F(Vmadd_b16Test, vmadd_b16_6){
    acc0.initSetup(0,"testprogs/binaries/vmadd_b16_6.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 20926u<<16, uargs1 = 12308u<<16, uargs2 = 60551u<<16, uargs3 = 45723u<<16;
    uint32_t uargs4 = 22901u<<16, uargs5 = 56179u<<16, uargs6 = 52187u<<16, uargs7 = 46590u<<16;
    uint32_t uargs8 = 7093u<<16, uargs9 = 44411u<<16, uargs10 = 48023u<<16, uargs11 = 42826u<<16;
    uint32_t mask = 7;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs4 + *fargs8) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs5 + *fargs9) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 * *fargs6 + *fargs10) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 * *fargs7 + *fargs11) : (*fargs11);
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
TEST_F(Vmadd_b16Test, vmadd_b16_7){
    acc0.initSetup(0,"testprogs/binaries/vmadd_b16_7.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 47747u<<16, uargs1 = 47261u<<16, uargs2 = 52054u<<16, uargs3 = 48415u<<16;
    uint32_t uargs4 = 65072u<<16, uargs5 = 7512u<<16, uargs6 = 54313u<<16, uargs7 = 29585u<<16;
    uint32_t uargs8 = 37217u<<16, uargs9 = 44547u<<16, uargs10 = 2861u<<16, uargs11 = 19214u<<16;
    uint32_t mask = 1;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs4 + *fargs8) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs5 + *fargs9) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 * *fargs6 + *fargs10) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 * *fargs7 + *fargs11) : (*fargs11);
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
TEST_F(Vmadd_b16Test, vmadd_b16_8){
    acc0.initSetup(0,"testprogs/binaries/vmadd_b16_8.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 19045u<<16, uargs1 = 62167u<<16, uargs2 = 48178u<<16, uargs3 = 64495u<<16;
    uint32_t uargs4 = 44584u<<16, uargs5 = 20647u<<16, uargs6 = 35368u<<16, uargs7 = 49665u<<16;
    uint32_t uargs8 = 10241u<<16, uargs9 = 35000u<<16, uargs10 = 53318u<<16, uargs11 = 48489u<<16;
    uint32_t mask = 11;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs4 + *fargs8) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs5 + *fargs9) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 * *fargs6 + *fargs10) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 * *fargs7 + *fargs11) : (*fargs11);
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
TEST_F(Vmadd_b16Test, vmadd_b16_9){
    acc0.initSetup(0,"testprogs/binaries/vmadd_b16_9.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 10196u<<16, uargs1 = 52641u<<16, uargs2 = 47838u<<16, uargs3 = 22165u<<16;
    uint32_t uargs4 = 1127u<<16, uargs5 = 27449u<<16, uargs6 = 12841u<<16, uargs7 = 9345u<<16;
    uint32_t uargs8 = 10216u<<16, uargs9 = 38736u<<16, uargs10 = 3846u<<16, uargs11 = 39399u<<16;
    uint32_t mask = 13;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs4 + *fargs8) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs5 + *fargs9) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 * *fargs6 + *fargs10) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 * *fargs7 + *fargs11) : (*fargs11);
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
TEST_F(Vmadd_b16Test, vmadd_b16_10){
    acc0.initSetup(0,"testprogs/binaries/vmadd_b16_10.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 15922u<<16, uargs1 = 40025u<<16, uargs2 = 34387u<<16, uargs3 = 30541u<<16;
    uint32_t uargs4 = 10733u<<16, uargs5 = 51030u<<16, uargs6 = 1601u<<16, uargs7 = 19291u<<16;
    uint32_t uargs8 = 38091u<<16, uargs9 = 7325u<<16, uargs10 = 27979u<<16, uargs11 = 25503u<<16;
    uint32_t mask = 9;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs4 + *fargs8) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs5 + *fargs9) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 * *fargs6 + *fargs10) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 * *fargs7 + *fargs11) : (*fargs11);
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
TEST_F(Vmadd_b16Test, vmadd_b16_11){
    acc0.initSetup(0,"testprogs/binaries/vmadd_b16_11.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 13683u<<16, uargs1 = 52322u<<16, uargs2 = 2304u<<16, uargs3 = 18142u<<16;
    uint32_t uargs4 = 14657u<<16, uargs5 = 25558u<<16, uargs6 = 20345u<<16, uargs7 = 48264u<<16;
    uint32_t uargs8 = 56735u<<16, uargs9 = 63762u<<16, uargs10 = 65023u<<16, uargs11 = 36859u<<16;
    uint32_t mask = 11;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs4 + *fargs8) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs5 + *fargs9) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 * *fargs6 + *fargs10) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 * *fargs7 + *fargs11) : (*fargs11);
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
TEST_F(Vmadd_b16Test, vmadd_b16_12){
    acc0.initSetup(0,"testprogs/binaries/vmadd_b16_12.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 28201u<<16, uargs1 = 61528u<<16, uargs2 = 61291u<<16, uargs3 = 39555u<<16;
    uint32_t uargs4 = 61047u<<16, uargs5 = 47619u<<16, uargs6 = 24872u<<16, uargs7 = 43830u<<16;
    uint32_t uargs8 = 20415u<<16, uargs9 = 46338u<<16, uargs10 = 60092u<<16, uargs11 = 26538u<<16;
    uint32_t mask = 6;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs4 + *fargs8) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs5 + *fargs9) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 * *fargs6 + *fargs10) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 * *fargs7 + *fargs11) : (*fargs11);
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
TEST_F(Vmadd_b16Test, vmadd_b16_13){
    acc0.initSetup(0,"testprogs/binaries/vmadd_b16_13.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 14335u<<16, uargs1 = 64066u<<16, uargs2 = 60180u<<16, uargs3 = 46856u<<16;
    uint32_t uargs4 = 17465u<<16, uargs5 = 30381u<<16, uargs6 = 56389u<<16, uargs7 = 10613u<<16;
    uint32_t uargs8 = 56456u<<16, uargs9 = 20792u<<16, uargs10 = 60859u<<16, uargs11 = 22966u<<16;
    uint32_t mask = 5;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs4 + *fargs8) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs5 + *fargs9) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 * *fargs6 + *fargs10) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 * *fargs7 + *fargs11) : (*fargs11);
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
TEST_F(Vmadd_b16Test, vmadd_b16_14){
    acc0.initSetup(0,"testprogs/binaries/vmadd_b16_14.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 43318u<<16, uargs1 = 15421u<<16, uargs2 = 28790u<<16, uargs3 = 60415u<<16;
    uint32_t uargs4 = 63158u<<16, uargs5 = 62944u<<16, uargs6 = 30888u<<16, uargs7 = 24288u<<16;
    uint32_t uargs8 = 53836u<<16, uargs9 = 58682u<<16, uargs10 = 5816u<<16, uargs11 = 7599u<<16;
    uint32_t mask = 1;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs4 + *fargs8) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs5 + *fargs9) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 * *fargs6 + *fargs10) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 * *fargs7 + *fargs11) : (*fargs11);
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
TEST_F(Vmadd_b16Test, vmadd_b16_15){
    acc0.initSetup(0,"testprogs/binaries/vmadd_b16_15.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 61439u<<16, uargs1 = 33817u<<16, uargs2 = 17054u<<16, uargs3 = 64879u<<16;
    uint32_t uargs4 = 27778u<<16, uargs5 = 12973u<<16, uargs6 = 16869u<<16, uargs7 = 54794u<<16;
    uint32_t uargs8 = 16640u<<16, uargs9 = 8903u<<16, uargs10 = 61073u<<16, uargs11 = 54467u<<16;
    uint32_t mask = 9;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs4 + *fargs8) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs5 + *fargs9) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 * *fargs6 + *fargs10) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 * *fargs7 + *fargs11) : (*fargs11);
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
TEST_F(Vmadd_b16Test, vmadd_b16_16){
    acc0.initSetup(0,"testprogs/binaries/vmadd_b16_16.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 122u<<16, uargs1 = 14772u<<16, uargs2 = 38223u<<16, uargs3 = 891u<<16;
    uint32_t uargs4 = 26660u<<16, uargs5 = 46417u<<16, uargs6 = 57657u<<16, uargs7 = 63751u<<16;
    uint32_t uargs8 = 6466u<<16, uargs9 = 43094u<<16, uargs10 = 38146u<<16, uargs11 = 35633u<<16;
    uint32_t mask = 5;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs4 + *fargs8) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs5 + *fargs9) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 * *fargs6 + *fargs10) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 * *fargs7 + *fargs11) : (*fargs11);
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
TEST_F(Vmadd_b16Test, vmadd_b16_17){
    acc0.initSetup(0,"testprogs/binaries/vmadd_b16_17.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 63274u<<16, uargs1 = 6468u<<16, uargs2 = 48445u<<16, uargs3 = 25426u<<16;
    uint32_t uargs4 = 25185u<<16, uargs5 = 28058u<<16, uargs6 = 37857u<<16, uargs7 = 27742u<<16;
    uint32_t uargs8 = 65155u<<16, uargs9 = 48588u<<16, uargs10 = 54550u<<16, uargs11 = 14957u<<16;
    uint32_t mask = 14;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs4 + *fargs8) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs5 + *fargs9) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 * *fargs6 + *fargs10) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 * *fargs7 + *fargs11) : (*fargs11);
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
TEST_F(Vmadd_b16Test, vmadd_b16_18){
    acc0.initSetup(0,"testprogs/binaries/vmadd_b16_18.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 33715u<<16, uargs1 = 51221u<<16, uargs2 = 34219u<<16, uargs3 = 12834u<<16;
    uint32_t uargs4 = 10807u<<16, uargs5 = 64390u<<16, uargs6 = 27352u<<16, uargs7 = 576u<<16;
    uint32_t uargs8 = 1379u<<16, uargs9 = 34773u<<16, uargs10 = 25480u<<16, uargs11 = 18948u<<16;
    uint32_t mask = 7;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs4 + *fargs8) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs5 + *fargs9) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 * *fargs6 + *fargs10) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 * *fargs7 + *fargs11) : (*fargs11);
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
TEST_F(Vmadd_b16Test, vmadd_b16_19){
    acc0.initSetup(0,"testprogs/binaries/vmadd_b16_19.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 5145u<<16, uargs1 = 36176u<<16, uargs2 = 39812u<<16, uargs3 = 36665u<<16;
    uint32_t uargs4 = 46697u<<16, uargs5 = 38500u<<16, uargs6 = 237u<<16, uargs7 = 64167u<<16;
    uint32_t uargs8 = 43619u<<16, uargs9 = 40907u<<16, uargs10 = 51096u<<16, uargs11 = 31047u<<16;
    uint32_t mask = 15;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs4 + *fargs8) : (*fargs8);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs5 + *fargs9) : (*fargs9);
    val2 = (mask >> 2 & 1) ? (*fargs2 * *fargs6 + *fargs10) : (*fargs10);
    val3 = (mask >> 3 & 1) ? (*fargs3 * *fargs7 + *fargs11) : (*fargs11);
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
