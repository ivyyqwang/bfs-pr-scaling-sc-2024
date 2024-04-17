#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"
#include <cmath>
#include <cfenv>

using namespace basim;

class Vgt_b16Test : public ::testing::Test {
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
TEST_F(Vgt_b16Test, vgt_b16_0){
    acc0.initSetup(0,"testprogs/binaries/vgt_b16_0.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 14161u<<16, uargs1 = 21171u<<16, uargs2 = 22022u<<16, uargs3 = 61251u<<16;
    uint32_t uargs4 = 59472u<<16, uargs5 = 39993u<<16, uargs6 = 50571u<<16, uargs7 = 39166u<<16;
    uint32_t uargs8 = 58150u<<16, uargs9 = 40861u<<16, uargs10 = 54480u<<16, uargs11 = 3252u<<16;
    uint32_t mask = 1;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    uint64_t result = 0;
    result |= (mask & 1) & (*fargs0 > *fargs4);
    result |= ((mask >> 1 & 1) & (*fargs1 > *fargs5)) << 1;
    result |= ((mask >> 2 & 1) & (*fargs2 > *fargs6)) << 2;
    result |= ((mask >> 3 & 1) & (*fargs3 > *fargs7)) << 3;
    val0 = (*fargs8);
    val1 = (*fargs9);
    val2 = (*fargs10);
    val3 = (*fargs11);
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
    uint64_t final_result = (((uint64_t)(bf16_val0) | ((uint64_t)(bf16_val1) << 16) | ((uint64_t)(bf16_val2) << 32) | ((uint64_t)(bf16_val3) << 48)) &  (~(uint64_t)(mask))) | result;
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vgt_b16Test, vgt_b16_1){
    acc0.initSetup(0,"testprogs/binaries/vgt_b16_1.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 35162u<<16, uargs1 = 19202u<<16, uargs2 = 46608u<<16, uargs3 = 41134u<<16;
    uint32_t uargs4 = 580u<<16, uargs5 = 45276u<<16, uargs6 = 44060u<<16, uargs7 = 31749u<<16;
    uint32_t uargs8 = 1120u<<16, uargs9 = 25593u<<16, uargs10 = 35007u<<16, uargs11 = 54972u<<16;
    uint32_t mask = 3;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    uint64_t result = 0;
    result |= (mask & 1) & (*fargs0 > *fargs4);
    result |= ((mask >> 1 & 1) & (*fargs1 > *fargs5)) << 1;
    result |= ((mask >> 2 & 1) & (*fargs2 > *fargs6)) << 2;
    result |= ((mask >> 3 & 1) & (*fargs3 > *fargs7)) << 3;
    val0 = (*fargs8);
    val1 = (*fargs9);
    val2 = (*fargs10);
    val3 = (*fargs11);
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
    uint64_t final_result = (((uint64_t)(bf16_val0) | ((uint64_t)(bf16_val1) << 16) | ((uint64_t)(bf16_val2) << 32) | ((uint64_t)(bf16_val3) << 48)) &  (~(uint64_t)(mask))) | result;
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vgt_b16Test, vgt_b16_2){
    acc0.initSetup(0,"testprogs/binaries/vgt_b16_2.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 28264u<<16, uargs1 = 60303u<<16, uargs2 = 24614u<<16, uargs3 = 45609u<<16;
    uint32_t uargs4 = 33889u<<16, uargs5 = 3559u<<16, uargs6 = 53470u<<16, uargs7 = 1029u<<16;
    uint32_t uargs8 = 42708u<<16, uargs9 = 2173u<<16, uargs10 = 8012u<<16, uargs11 = 36169u<<16;
    uint32_t mask = 3;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    uint64_t result = 0;
    result |= (mask & 1) & (*fargs0 > *fargs4);
    result |= ((mask >> 1 & 1) & (*fargs1 > *fargs5)) << 1;
    result |= ((mask >> 2 & 1) & (*fargs2 > *fargs6)) << 2;
    result |= ((mask >> 3 & 1) & (*fargs3 > *fargs7)) << 3;
    val0 = (*fargs8);
    val1 = (*fargs9);
    val2 = (*fargs10);
    val3 = (*fargs11);
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
    uint64_t final_result = (((uint64_t)(bf16_val0) | ((uint64_t)(bf16_val1) << 16) | ((uint64_t)(bf16_val2) << 32) | ((uint64_t)(bf16_val3) << 48)) &  (~(uint64_t)(mask))) | result;
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vgt_b16Test, vgt_b16_3){
    acc0.initSetup(0,"testprogs/binaries/vgt_b16_3.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 12553u<<16, uargs1 = 3u<<16, uargs2 = 62864u<<16, uargs3 = 13877u<<16;
    uint32_t uargs4 = 3628u<<16, uargs5 = 4308u<<16, uargs6 = 33528u<<16, uargs7 = 36870u<<16;
    uint32_t uargs8 = 27472u<<16, uargs9 = 45829u<<16, uargs10 = 9230u<<16, uargs11 = 28456u<<16;
    uint32_t mask = 1;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    uint64_t result = 0;
    result |= (mask & 1) & (*fargs0 > *fargs4);
    result |= ((mask >> 1 & 1) & (*fargs1 > *fargs5)) << 1;
    result |= ((mask >> 2 & 1) & (*fargs2 > *fargs6)) << 2;
    result |= ((mask >> 3 & 1) & (*fargs3 > *fargs7)) << 3;
    val0 = (*fargs8);
    val1 = (*fargs9);
    val2 = (*fargs10);
    val3 = (*fargs11);
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
    uint64_t final_result = (((uint64_t)(bf16_val0) | ((uint64_t)(bf16_val1) << 16) | ((uint64_t)(bf16_val2) << 32) | ((uint64_t)(bf16_val3) << 48)) &  (~(uint64_t)(mask))) | result;
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vgt_b16Test, vgt_b16_4){
    acc0.initSetup(0,"testprogs/binaries/vgt_b16_4.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 10992u<<16, uargs1 = 52834u<<16, uargs2 = 8462u<<16, uargs3 = 28613u<<16;
    uint32_t uargs4 = 61371u<<16, uargs5 = 61913u<<16, uargs6 = 43305u<<16, uargs7 = 6100u<<16;
    uint32_t uargs8 = 6043u<<16, uargs9 = 29258u<<16, uargs10 = 30434u<<16, uargs11 = 6257u<<16;
    uint32_t mask = 3;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    uint64_t result = 0;
    result |= (mask & 1) & (*fargs0 > *fargs4);
    result |= ((mask >> 1 & 1) & (*fargs1 > *fargs5)) << 1;
    result |= ((mask >> 2 & 1) & (*fargs2 > *fargs6)) << 2;
    result |= ((mask >> 3 & 1) & (*fargs3 > *fargs7)) << 3;
    val0 = (*fargs8);
    val1 = (*fargs9);
    val2 = (*fargs10);
    val3 = (*fargs11);
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
    uint64_t final_result = (((uint64_t)(bf16_val0) | ((uint64_t)(bf16_val1) << 16) | ((uint64_t)(bf16_val2) << 32) | ((uint64_t)(bf16_val3) << 48)) &  (~(uint64_t)(mask))) | result;
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vgt_b16Test, vgt_b16_5){
    acc0.initSetup(0,"testprogs/binaries/vgt_b16_5.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 20315u<<16, uargs1 = 43687u<<16, uargs2 = 52250u<<16, uargs3 = 14966u<<16;
    uint32_t uargs4 = 51684u<<16, uargs5 = 22752u<<16, uargs6 = 4509u<<16, uargs7 = 26287u<<16;
    uint32_t uargs8 = 33088u<<16, uargs9 = 52442u<<16, uargs10 = 53089u<<16, uargs11 = 27403u<<16;
    uint32_t mask = 1;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    uint64_t result = 0;
    result |= (mask & 1) & (*fargs0 > *fargs4);
    result |= ((mask >> 1 & 1) & (*fargs1 > *fargs5)) << 1;
    result |= ((mask >> 2 & 1) & (*fargs2 > *fargs6)) << 2;
    result |= ((mask >> 3 & 1) & (*fargs3 > *fargs7)) << 3;
    val0 = (*fargs8);
    val1 = (*fargs9);
    val2 = (*fargs10);
    val3 = (*fargs11);
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
    uint64_t final_result = (((uint64_t)(bf16_val0) | ((uint64_t)(bf16_val1) << 16) | ((uint64_t)(bf16_val2) << 32) | ((uint64_t)(bf16_val3) << 48)) &  (~(uint64_t)(mask))) | result;
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vgt_b16Test, vgt_b16_6){
    acc0.initSetup(0,"testprogs/binaries/vgt_b16_6.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 7410u<<16, uargs1 = 19110u<<16, uargs2 = 1699u<<16, uargs3 = 41266u<<16;
    uint32_t uargs4 = 6304u<<16, uargs5 = 13237u<<16, uargs6 = 4422u<<16, uargs7 = 25606u<<16;
    uint32_t uargs8 = 40540u<<16, uargs9 = 4472u<<16, uargs10 = 38010u<<16, uargs11 = 27870u<<16;
    uint32_t mask = 3;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    uint64_t result = 0;
    result |= (mask & 1) & (*fargs0 > *fargs4);
    result |= ((mask >> 1 & 1) & (*fargs1 > *fargs5)) << 1;
    result |= ((mask >> 2 & 1) & (*fargs2 > *fargs6)) << 2;
    result |= ((mask >> 3 & 1) & (*fargs3 > *fargs7)) << 3;
    val0 = (*fargs8);
    val1 = (*fargs9);
    val2 = (*fargs10);
    val3 = (*fargs11);
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
    uint64_t final_result = (((uint64_t)(bf16_val0) | ((uint64_t)(bf16_val1) << 16) | ((uint64_t)(bf16_val2) << 32) | ((uint64_t)(bf16_val3) << 48)) &  (~(uint64_t)(mask))) | result;
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vgt_b16Test, vgt_b16_7){
    acc0.initSetup(0,"testprogs/binaries/vgt_b16_7.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 53807u<<16, uargs1 = 55451u<<16, uargs2 = 26603u<<16, uargs3 = 17759u<<16;
    uint32_t uargs4 = 13284u<<16, uargs5 = 11251u<<16, uargs6 = 8808u<<16, uargs7 = 39470u<<16;
    uint32_t uargs8 = 16217u<<16, uargs9 = 57000u<<16, uargs10 = 43382u<<16, uargs11 = 51739u<<16;
    uint32_t mask = 1;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    uint64_t result = 0;
    result |= (mask & 1) & (*fargs0 > *fargs4);
    result |= ((mask >> 1 & 1) & (*fargs1 > *fargs5)) << 1;
    result |= ((mask >> 2 & 1) & (*fargs2 > *fargs6)) << 2;
    result |= ((mask >> 3 & 1) & (*fargs3 > *fargs7)) << 3;
    val0 = (*fargs8);
    val1 = (*fargs9);
    val2 = (*fargs10);
    val3 = (*fargs11);
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
    uint64_t final_result = (((uint64_t)(bf16_val0) | ((uint64_t)(bf16_val1) << 16) | ((uint64_t)(bf16_val2) << 32) | ((uint64_t)(bf16_val3) << 48)) &  (~(uint64_t)(mask))) | result;
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vgt_b16Test, vgt_b16_8){
    acc0.initSetup(0,"testprogs/binaries/vgt_b16_8.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 16506u<<16, uargs1 = 20548u<<16, uargs2 = 6048u<<16, uargs3 = 6556u<<16;
    uint32_t uargs4 = 15887u<<16, uargs5 = 64707u<<16, uargs6 = 14914u<<16, uargs7 = 11865u<<16;
    uint32_t uargs8 = 10000u<<16, uargs9 = 10333u<<16, uargs10 = 46710u<<16, uargs11 = 33957u<<16;
    uint32_t mask = 2;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    uint64_t result = 0;
    result |= (mask & 1) & (*fargs0 > *fargs4);
    result |= ((mask >> 1 & 1) & (*fargs1 > *fargs5)) << 1;
    result |= ((mask >> 2 & 1) & (*fargs2 > *fargs6)) << 2;
    result |= ((mask >> 3 & 1) & (*fargs3 > *fargs7)) << 3;
    val0 = (*fargs8);
    val1 = (*fargs9);
    val2 = (*fargs10);
    val3 = (*fargs11);
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
    uint64_t final_result = (((uint64_t)(bf16_val0) | ((uint64_t)(bf16_val1) << 16) | ((uint64_t)(bf16_val2) << 32) | ((uint64_t)(bf16_val3) << 48)) &  (~(uint64_t)(mask))) | result;
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vgt_b16Test, vgt_b16_9){
    acc0.initSetup(0,"testprogs/binaries/vgt_b16_9.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 60800u<<16, uargs1 = 28835u<<16, uargs2 = 13618u<<16, uargs3 = 1423u<<16;
    uint32_t uargs4 = 572u<<16, uargs5 = 14694u<<16, uargs6 = 57128u<<16, uargs7 = 11645u<<16;
    uint32_t uargs8 = 63353u<<16, uargs9 = 18906u<<16, uargs10 = 26521u<<16, uargs11 = 11157u<<16;
    uint32_t mask = 2;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    uint64_t result = 0;
    result |= (mask & 1) & (*fargs0 > *fargs4);
    result |= ((mask >> 1 & 1) & (*fargs1 > *fargs5)) << 1;
    result |= ((mask >> 2 & 1) & (*fargs2 > *fargs6)) << 2;
    result |= ((mask >> 3 & 1) & (*fargs3 > *fargs7)) << 3;
    val0 = (*fargs8);
    val1 = (*fargs9);
    val2 = (*fargs10);
    val3 = (*fargs11);
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
    uint64_t final_result = (((uint64_t)(bf16_val0) | ((uint64_t)(bf16_val1) << 16) | ((uint64_t)(bf16_val2) << 32) | ((uint64_t)(bf16_val3) << 48)) &  (~(uint64_t)(mask))) | result;
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vgt_b16Test, vgt_b16_10){
    acc0.initSetup(0,"testprogs/binaries/vgt_b16_10.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 19115u<<16, uargs1 = 4511u<<16, uargs2 = 44689u<<16, uargs3 = 14536u<<16;
    uint32_t uargs4 = 58575u<<16, uargs5 = 26751u<<16, uargs6 = 976u<<16, uargs7 = 6680u<<16;
    uint32_t uargs8 = 28007u<<16, uargs9 = 30338u<<16, uargs10 = 22200u<<16, uargs11 = 49339u<<16;
    uint32_t mask = 1;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    uint64_t result = 0;
    result |= (mask & 1) & (*fargs0 > *fargs4);
    result |= ((mask >> 1 & 1) & (*fargs1 > *fargs5)) << 1;
    result |= ((mask >> 2 & 1) & (*fargs2 > *fargs6)) << 2;
    result |= ((mask >> 3 & 1) & (*fargs3 > *fargs7)) << 3;
    val0 = (*fargs8);
    val1 = (*fargs9);
    val2 = (*fargs10);
    val3 = (*fargs11);
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
    uint64_t final_result = (((uint64_t)(bf16_val0) | ((uint64_t)(bf16_val1) << 16) | ((uint64_t)(bf16_val2) << 32) | ((uint64_t)(bf16_val3) << 48)) &  (~(uint64_t)(mask))) | result;
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vgt_b16Test, vgt_b16_11){
    acc0.initSetup(0,"testprogs/binaries/vgt_b16_11.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 35120u<<16, uargs1 = 39161u<<16, uargs2 = 55193u<<16, uargs3 = 35199u<<16;
    uint32_t uargs4 = 30211u<<16, uargs5 = 52366u<<16, uargs6 = 64381u<<16, uargs7 = 36228u<<16;
    uint32_t uargs8 = 11662u<<16, uargs9 = 59135u<<16, uargs10 = 42691u<<16, uargs11 = 19282u<<16;
    uint32_t mask = 1;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    uint64_t result = 0;
    result |= (mask & 1) & (*fargs0 > *fargs4);
    result |= ((mask >> 1 & 1) & (*fargs1 > *fargs5)) << 1;
    result |= ((mask >> 2 & 1) & (*fargs2 > *fargs6)) << 2;
    result |= ((mask >> 3 & 1) & (*fargs3 > *fargs7)) << 3;
    val0 = (*fargs8);
    val1 = (*fargs9);
    val2 = (*fargs10);
    val3 = (*fargs11);
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
    uint64_t final_result = (((uint64_t)(bf16_val0) | ((uint64_t)(bf16_val1) << 16) | ((uint64_t)(bf16_val2) << 32) | ((uint64_t)(bf16_val3) << 48)) &  (~(uint64_t)(mask))) | result;
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vgt_b16Test, vgt_b16_12){
    acc0.initSetup(0,"testprogs/binaries/vgt_b16_12.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 22429u<<16, uargs1 = 4173u<<16, uargs2 = 9046u<<16, uargs3 = 29709u<<16;
    uint32_t uargs4 = 42407u<<16, uargs5 = 58067u<<16, uargs6 = 29739u<<16, uargs7 = 10618u<<16;
    uint32_t uargs8 = 10255u<<16, uargs9 = 53449u<<16, uargs10 = 29244u<<16, uargs11 = 57673u<<16;
    uint32_t mask = 2;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    uint64_t result = 0;
    result |= (mask & 1) & (*fargs0 > *fargs4);
    result |= ((mask >> 1 & 1) & (*fargs1 > *fargs5)) << 1;
    result |= ((mask >> 2 & 1) & (*fargs2 > *fargs6)) << 2;
    result |= ((mask >> 3 & 1) & (*fargs3 > *fargs7)) << 3;
    val0 = (*fargs8);
    val1 = (*fargs9);
    val2 = (*fargs10);
    val3 = (*fargs11);
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
    uint64_t final_result = (((uint64_t)(bf16_val0) | ((uint64_t)(bf16_val1) << 16) | ((uint64_t)(bf16_val2) << 32) | ((uint64_t)(bf16_val3) << 48)) &  (~(uint64_t)(mask))) | result;
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vgt_b16Test, vgt_b16_13){
    acc0.initSetup(0,"testprogs/binaries/vgt_b16_13.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 50973u<<16, uargs1 = 12501u<<16, uargs2 = 32172u<<16, uargs3 = 10829u<<16;
    uint32_t uargs4 = 7251u<<16, uargs5 = 926u<<16, uargs6 = 4516u<<16, uargs7 = 64852u<<16;
    uint32_t uargs8 = 32936u<<16, uargs9 = 38384u<<16, uargs10 = 35387u<<16, uargs11 = 6354u<<16;
    uint32_t mask = 2;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    uint64_t result = 0;
    result |= (mask & 1) & (*fargs0 > *fargs4);
    result |= ((mask >> 1 & 1) & (*fargs1 > *fargs5)) << 1;
    result |= ((mask >> 2 & 1) & (*fargs2 > *fargs6)) << 2;
    result |= ((mask >> 3 & 1) & (*fargs3 > *fargs7)) << 3;
    val0 = (*fargs8);
    val1 = (*fargs9);
    val2 = (*fargs10);
    val3 = (*fargs11);
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
    uint64_t final_result = (((uint64_t)(bf16_val0) | ((uint64_t)(bf16_val1) << 16) | ((uint64_t)(bf16_val2) << 32) | ((uint64_t)(bf16_val3) << 48)) &  (~(uint64_t)(mask))) | result;
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vgt_b16Test, vgt_b16_14){
    acc0.initSetup(0,"testprogs/binaries/vgt_b16_14.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 10346u<<16, uargs1 = 2169u<<16, uargs2 = 42453u<<16, uargs3 = 53625u<<16;
    uint32_t uargs4 = 56729u<<16, uargs5 = 55175u<<16, uargs6 = 36454u<<16, uargs7 = 60865u<<16;
    uint32_t uargs8 = 39412u<<16, uargs9 = 61872u<<16, uargs10 = 19880u<<16, uargs11 = 37254u<<16;
    uint32_t mask = 2;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    uint64_t result = 0;
    result |= (mask & 1) & (*fargs0 > *fargs4);
    result |= ((mask >> 1 & 1) & (*fargs1 > *fargs5)) << 1;
    result |= ((mask >> 2 & 1) & (*fargs2 > *fargs6)) << 2;
    result |= ((mask >> 3 & 1) & (*fargs3 > *fargs7)) << 3;
    val0 = (*fargs8);
    val1 = (*fargs9);
    val2 = (*fargs10);
    val3 = (*fargs11);
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
    uint64_t final_result = (((uint64_t)(bf16_val0) | ((uint64_t)(bf16_val1) << 16) | ((uint64_t)(bf16_val2) << 32) | ((uint64_t)(bf16_val3) << 48)) &  (~(uint64_t)(mask))) | result;
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vgt_b16Test, vgt_b16_15){
    acc0.initSetup(0,"testprogs/binaries/vgt_b16_15.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 12906u<<16, uargs1 = 48982u<<16, uargs2 = 30388u<<16, uargs3 = 31162u<<16;
    uint32_t uargs4 = 19303u<<16, uargs5 = 41690u<<16, uargs6 = 37776u<<16, uargs7 = 19135u<<16;
    uint32_t uargs8 = 34044u<<16, uargs9 = 41382u<<16, uargs10 = 43380u<<16, uargs11 = 12124u<<16;
    uint32_t mask = 3;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    uint64_t result = 0;
    result |= (mask & 1) & (*fargs0 > *fargs4);
    result |= ((mask >> 1 & 1) & (*fargs1 > *fargs5)) << 1;
    result |= ((mask >> 2 & 1) & (*fargs2 > *fargs6)) << 2;
    result |= ((mask >> 3 & 1) & (*fargs3 > *fargs7)) << 3;
    val0 = (*fargs8);
    val1 = (*fargs9);
    val2 = (*fargs10);
    val3 = (*fargs11);
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
    uint64_t final_result = (((uint64_t)(bf16_val0) | ((uint64_t)(bf16_val1) << 16) | ((uint64_t)(bf16_val2) << 32) | ((uint64_t)(bf16_val3) << 48)) &  (~(uint64_t)(mask))) | result;
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vgt_b16Test, vgt_b16_16){
    acc0.initSetup(0,"testprogs/binaries/vgt_b16_16.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 804u<<16, uargs1 = 46063u<<16, uargs2 = 18594u<<16, uargs3 = 28630u<<16;
    uint32_t uargs4 = 37397u<<16, uargs5 = 1689u<<16, uargs6 = 24712u<<16, uargs7 = 26058u<<16;
    uint32_t uargs8 = 39560u<<16, uargs9 = 38227u<<16, uargs10 = 52691u<<16, uargs11 = 5363u<<16;
    uint32_t mask = 2;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    uint64_t result = 0;
    result |= (mask & 1) & (*fargs0 > *fargs4);
    result |= ((mask >> 1 & 1) & (*fargs1 > *fargs5)) << 1;
    result |= ((mask >> 2 & 1) & (*fargs2 > *fargs6)) << 2;
    result |= ((mask >> 3 & 1) & (*fargs3 > *fargs7)) << 3;
    val0 = (*fargs8);
    val1 = (*fargs9);
    val2 = (*fargs10);
    val3 = (*fargs11);
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
    uint64_t final_result = (((uint64_t)(bf16_val0) | ((uint64_t)(bf16_val1) << 16) | ((uint64_t)(bf16_val2) << 32) | ((uint64_t)(bf16_val3) << 48)) &  (~(uint64_t)(mask))) | result;
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vgt_b16Test, vgt_b16_17){
    acc0.initSetup(0,"testprogs/binaries/vgt_b16_17.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 26012u<<16, uargs1 = 44272u<<16, uargs2 = 15372u<<16, uargs3 = 3838u<<16;
    uint32_t uargs4 = 1512u<<16, uargs5 = 43113u<<16, uargs6 = 39354u<<16, uargs7 = 33300u<<16;
    uint32_t uargs8 = 21574u<<16, uargs9 = 53338u<<16, uargs10 = 62804u<<16, uargs11 = 63692u<<16;
    uint32_t mask = 3;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    uint64_t result = 0;
    result |= (mask & 1) & (*fargs0 > *fargs4);
    result |= ((mask >> 1 & 1) & (*fargs1 > *fargs5)) << 1;
    result |= ((mask >> 2 & 1) & (*fargs2 > *fargs6)) << 2;
    result |= ((mask >> 3 & 1) & (*fargs3 > *fargs7)) << 3;
    val0 = (*fargs8);
    val1 = (*fargs9);
    val2 = (*fargs10);
    val3 = (*fargs11);
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
    uint64_t final_result = (((uint64_t)(bf16_val0) | ((uint64_t)(bf16_val1) << 16) | ((uint64_t)(bf16_val2) << 32) | ((uint64_t)(bf16_val3) << 48)) &  (~(uint64_t)(mask))) | result;
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vgt_b16Test, vgt_b16_18){
    acc0.initSetup(0,"testprogs/binaries/vgt_b16_18.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 29804u<<16, uargs1 = 1962u<<16, uargs2 = 22505u<<16, uargs3 = 10353u<<16;
    uint32_t uargs4 = 3646u<<16, uargs5 = 39499u<<16, uargs6 = 51437u<<16, uargs7 = 9420u<<16;
    uint32_t uargs8 = 37178u<<16, uargs9 = 51770u<<16, uargs10 = 53493u<<16, uargs11 = 54643u<<16;
    uint32_t mask = 1;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    uint64_t result = 0;
    result |= (mask & 1) & (*fargs0 > *fargs4);
    result |= ((mask >> 1 & 1) & (*fargs1 > *fargs5)) << 1;
    result |= ((mask >> 2 & 1) & (*fargs2 > *fargs6)) << 2;
    result |= ((mask >> 3 & 1) & (*fargs3 > *fargs7)) << 3;
    val0 = (*fargs8);
    val1 = (*fargs9);
    val2 = (*fargs10);
    val3 = (*fargs11);
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
    uint64_t final_result = (((uint64_t)(bf16_val0) | ((uint64_t)(bf16_val1) << 16) | ((uint64_t)(bf16_val2) << 32) | ((uint64_t)(bf16_val3) << 48)) &  (~(uint64_t)(mask))) | result;
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vgt_b16Test, vgt_b16_19){
    acc0.initSetup(0,"testprogs/binaries/vgt_b16_19.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 65034u<<16, uargs1 = 33586u<<16, uargs2 = 39243u<<16, uargs3 = 17565u<<16;
    uint32_t uargs4 = 18857u<<16, uargs5 = 29653u<<16, uargs6 = 28587u<<16, uargs7 = 29362u<<16;
    uint32_t uargs8 = 21981u<<16, uargs9 = 65010u<<16, uargs10 = 17736u<<16, uargs11 = 37054u<<16;
    uint32_t mask = 2;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1), *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5), *fargs6 = reinterpret_cast<float*>(&uargs6), *fargs7 = reinterpret_cast<float*>(&uargs7);
    float *fargs8 = reinterpret_cast<float*>(&uargs8), *fargs9 = reinterpret_cast<float*>(&uargs9), *fargs10 = reinterpret_cast<float*>(&uargs10), *fargs11 = reinterpret_cast<float*>(&uargs11);
    std::feclearexcept(FE_ALL_EXCEPT);
    uint64_t result = 0;
    result |= (mask & 1) & (*fargs0 > *fargs4);
    result |= ((mask >> 1 & 1) & (*fargs1 > *fargs5)) << 1;
    result |= ((mask >> 2 & 1) & (*fargs2 > *fargs6)) << 2;
    result |= ((mask >> 3 & 1) & (*fargs3 > *fargs7)) << 3;
    val0 = (*fargs8);
    val1 = (*fargs9);
    val2 = (*fargs10);
    val3 = (*fargs11);
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
    uint64_t final_result = (((uint64_t)(bf16_val0) | ((uint64_t)(bf16_val1) << 16) | ((uint64_t)(bf16_val2) << 32) | ((uint64_t)(bf16_val3) << 48)) &  (~(uint64_t)(mask))) | result;
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
