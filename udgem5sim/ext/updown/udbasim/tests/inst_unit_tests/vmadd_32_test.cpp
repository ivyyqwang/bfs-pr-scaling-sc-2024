#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"
#include <cmath>
#include <cfenv>

using namespace basim;

class Vmadd_32Test : public ::testing::Test {
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
TEST_F(Vmadd_32Test, vmadd_32_0){
    acc0.initSetup(0,"testprogs/binaries/vmadd_32_0.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    float val0, val1;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 2852625973, uargs1 = 3983750352;
    uint32_t uargs2 = 3920820433, uargs3 =  3269724867;
    uint32_t uargs4 = 2704677041, uargs5 =  667910403;
    uint32_t mask = 2;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs2 + *fargs4) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs3 + *fargs5) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vmadd_32Test, vmadd_32_1){
    acc0.initSetup(0,"testprogs/binaries/vmadd_32_1.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    float val0, val1;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 2119671945, uargs1 = 1769209532;
    uint32_t uargs2 = 4225610154, uargs3 =  572458600;
    uint32_t uargs4 = 182992653, uargs5 =  648529457;
    uint32_t mask = 1;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs2 + *fargs4) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs3 + *fargs5) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vmadd_32Test, vmadd_32_2){
    acc0.initSetup(0,"testprogs/binaries/vmadd_32_2.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    float val0, val1;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 2597764629, uargs1 = 263953060;
    uint32_t uargs2 = 1215943703, uargs3 =  1304050209;
    uint32_t uargs4 = 2488481266, uargs5 =  2846990938;
    uint32_t mask = 2;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs2 + *fargs4) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs3 + *fargs5) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vmadd_32Test, vmadd_32_3){
    acc0.initSetup(0,"testprogs/binaries/vmadd_32_3.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    float val0, val1;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 1271891685, uargs1 = 2372418927;
    uint32_t uargs2 = 1289819479, uargs3 =  3629512037;
    uint32_t uargs4 = 2409284435, uargs5 =  115166526;
    uint32_t mask = 1;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs2 + *fargs4) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs3 + *fargs5) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vmadd_32Test, vmadd_32_4){
    acc0.initSetup(0,"testprogs/binaries/vmadd_32_4.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    float val0, val1;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 2428980963, uargs1 = 2172197538;
    uint32_t uargs2 = 2226530831, uargs3 =  3605559777;
    uint32_t uargs4 = 875751938, uargs5 =  2126625514;
    uint32_t mask = 3;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs2 + *fargs4) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs3 + *fargs5) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vmadd_32Test, vmadd_32_5){
    acc0.initSetup(0,"testprogs/binaries/vmadd_32_5.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    float val0, val1;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 3323446856, uargs1 = 248455410;
    uint32_t uargs2 = 3820990142, uargs3 =  3015356824;
    uint32_t uargs4 = 2174754574, uargs5 =  2041223753;
    uint32_t mask = 3;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs2 + *fargs4) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs3 + *fargs5) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vmadd_32Test, vmadd_32_6){
    acc0.initSetup(0,"testprogs/binaries/vmadd_32_6.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    float val0, val1;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 2720896545, uargs1 = 3283637757;
    uint32_t uargs2 = 1110570868, uargs3 =  3110835054;
    uint32_t uargs4 = 68329732, uargs5 =  3011603539;
    uint32_t mask = 3;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs2 + *fargs4) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs3 + *fargs5) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vmadd_32Test, vmadd_32_7){
    acc0.initSetup(0,"testprogs/binaries/vmadd_32_7.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    float val0, val1;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 1551330532, uargs1 = 3167720188;
    uint32_t uargs2 = 1355005521, uargs3 =  13374786;
    uint32_t uargs4 = 125611237, uargs5 =  4013907659;
    uint32_t mask = 3;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs2 + *fargs4) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs3 + *fargs5) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vmadd_32Test, vmadd_32_8){
    acc0.initSetup(0,"testprogs/binaries/vmadd_32_8.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    float val0, val1;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 4099295545, uargs1 = 1119852007;
    uint32_t uargs2 = 2299015866, uargs3 =  3082959807;
    uint32_t uargs4 = 1782473890, uargs5 =  179544543;
    uint32_t mask = 3;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs2 + *fargs4) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs3 + *fargs5) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vmadd_32Test, vmadd_32_9){
    acc0.initSetup(0,"testprogs/binaries/vmadd_32_9.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    float val0, val1;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 2585284774, uargs1 = 778603600;
    uint32_t uargs2 = 3599183112, uargs3 =  2930760144;
    uint32_t uargs4 = 384541185, uargs5 =  1271584260;
    uint32_t mask = 1;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs2 + *fargs4) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs3 + *fargs5) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vmadd_32Test, vmadd_32_10){
    acc0.initSetup(0,"testprogs/binaries/vmadd_32_10.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    float val0, val1;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 4112744023, uargs1 = 1871277230;
    uint32_t uargs2 = 2936564409, uargs3 =  2162343786;
    uint32_t uargs4 = 1811224181, uargs5 =  1952677303;
    uint32_t mask = 3;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs2 + *fargs4) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs3 + *fargs5) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vmadd_32Test, vmadd_32_11){
    acc0.initSetup(0,"testprogs/binaries/vmadd_32_11.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    float val0, val1;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 2449713160, uargs1 = 463018133;
    uint32_t uargs2 = 3185842605, uargs3 =  3661819808;
    uint32_t uargs4 = 799852957, uargs5 =  4155757572;
    uint32_t mask = 1;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs2 + *fargs4) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs3 + *fargs5) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vmadd_32Test, vmadd_32_12){
    acc0.initSetup(0,"testprogs/binaries/vmadd_32_12.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    float val0, val1;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 358798176, uargs1 = 1132470714;
    uint32_t uargs2 = 608792746, uargs3 =  1182527968;
    uint32_t uargs4 = 2707563894, uargs5 =  1822391061;
    uint32_t mask = 1;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs2 + *fargs4) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs3 + *fargs5) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vmadd_32Test, vmadd_32_13){
    acc0.initSetup(0,"testprogs/binaries/vmadd_32_13.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    float val0, val1;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 2483305677, uargs1 = 123762510;
    uint32_t uargs2 = 1575682019, uargs3 =  3636430512;
    uint32_t uargs4 = 2430862831, uargs5 =  2253927422;
    uint32_t mask = 3;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs2 + *fargs4) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs3 + *fargs5) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vmadd_32Test, vmadd_32_14){
    acc0.initSetup(0,"testprogs/binaries/vmadd_32_14.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    float val0, val1;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 716241971, uargs1 = 1310205622;
    uint32_t uargs2 = 494050910, uargs3 =  3380640475;
    uint32_t uargs4 = 304112814, uargs5 =  649524821;
    uint32_t mask = 3;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs2 + *fargs4) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs3 + *fargs5) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vmadd_32Test, vmadd_32_15){
    acc0.initSetup(0,"testprogs/binaries/vmadd_32_15.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    float val0, val1;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 1810044799, uargs1 = 1955810408;
    uint32_t uargs2 = 2541239624, uargs3 =  3280096293;
    uint32_t uargs4 = 243277190, uargs5 =  3384536547;
    uint32_t mask = 3;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs2 + *fargs4) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs3 + *fargs5) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vmadd_32Test, vmadd_32_16){
    acc0.initSetup(0,"testprogs/binaries/vmadd_32_16.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    float val0, val1;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 824796313, uargs1 = 4207604343;
    uint32_t uargs2 = 4121057099, uargs3 =  3947383963;
    uint32_t uargs4 = 1662082109, uargs5 =  2299506534;
    uint32_t mask = 1;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs2 + *fargs4) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs3 + *fargs5) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vmadd_32Test, vmadd_32_17){
    acc0.initSetup(0,"testprogs/binaries/vmadd_32_17.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    float val0, val1;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 1918630538, uargs1 = 452999578;
    uint32_t uargs2 = 74166565, uargs3 =  206962533;
    uint32_t uargs4 = 2005145930, uargs5 =  2983837761;
    uint32_t mask = 1;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs2 + *fargs4) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs3 + *fargs5) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vmadd_32Test, vmadd_32_18){
    acc0.initSetup(0,"testprogs/binaries/vmadd_32_18.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    float val0, val1;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 1782752161, uargs1 = 1362827903;
    uint32_t uargs2 = 3760810470, uargs3 =  3524286227;
    uint32_t uargs4 = 4016933974, uargs5 =  3604911990;
    uint32_t mask = 3;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs2 + *fargs4) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs3 + *fargs5) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Vmadd_32Test, vmadd_32_19){
    acc0.initSetup(0,"testprogs/binaries/vmadd_32_19.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    float val0, val1;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 2125612049, uargs1 = 1112892656;
    uint32_t uargs2 = 2223640362, uargs3 =  1514968177;
    uint32_t uargs4 = 3462181302, uargs5 =  938223985;
    uint32_t mask = 1;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 * *fargs2 + *fargs4) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs3 + *fargs5) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
