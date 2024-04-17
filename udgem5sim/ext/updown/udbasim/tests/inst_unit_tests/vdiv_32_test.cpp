#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"
#include <cmath>
#include <cfenv>

using namespace basim;

class Vdiv_32Test : public ::testing::Test {
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
TEST_F(Vdiv_32Test, vdiv_32_0){
    acc0.initSetup(0,"testprogs/binaries/vdiv_32_0.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 666398421, uargs1 = 1582447683;
    uint32_t uargs2 = 2273367241, uargs3 =  1378550133;
    uint32_t uargs4 = 2444064419, uargs5 =  3590145371;
    uint32_t mask = 3;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 / *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs3) : (*fargs5);
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
TEST_F(Vdiv_32Test, vdiv_32_1){
    acc0.initSetup(0,"testprogs/binaries/vdiv_32_1.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 1504040920, uargs1 = 4190886329;
    uint32_t uargs2 = 2615919600, uargs3 =  4010543015;
    uint32_t uargs4 = 1223893816, uargs5 =  31258894;
    uint32_t mask = 1;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 / *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs3) : (*fargs5);
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
TEST_F(Vdiv_32Test, vdiv_32_2){
    acc0.initSetup(0,"testprogs/binaries/vdiv_32_2.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 769730269, uargs1 = 2960558081;
    uint32_t uargs2 = 1181169035, uargs3 =  2099902191;
    uint32_t uargs4 = 2797422095, uargs5 =  1558470471;
    uint32_t mask = 2;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 / *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs3) : (*fargs5);
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
TEST_F(Vdiv_32Test, vdiv_32_3){
    acc0.initSetup(0,"testprogs/binaries/vdiv_32_3.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 4277602511, uargs1 = 3247708022;
    uint32_t uargs2 = 3560877499, uargs3 =  4083312408;
    uint32_t uargs4 = 3813728328, uargs5 =  3182419913;
    uint32_t mask = 1;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 / *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs3) : (*fargs5);
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
TEST_F(Vdiv_32Test, vdiv_32_4){
    acc0.initSetup(0,"testprogs/binaries/vdiv_32_4.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 3892300902, uargs1 = 1440076385;
    uint32_t uargs2 = 2997505248, uargs3 =  3016919149;
    uint32_t uargs4 = 1314576026, uargs5 =  106909165;
    uint32_t mask = 3;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 / *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs3) : (*fargs5);
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
TEST_F(Vdiv_32Test, vdiv_32_5){
    acc0.initSetup(0,"testprogs/binaries/vdiv_32_5.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 2023379318, uargs1 = 691855746;
    uint32_t uargs2 = 827759372, uargs3 =  3306289946;
    uint32_t uargs4 = 434772737, uargs5 =  947855374;
    uint32_t mask = 3;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 / *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs3) : (*fargs5);
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
TEST_F(Vdiv_32Test, vdiv_32_6){
    acc0.initSetup(0,"testprogs/binaries/vdiv_32_6.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 2945341812, uargs1 = 3848328950;
    uint32_t uargs2 = 3653567940, uargs3 =  3102719487;
    uint32_t uargs4 = 1912028839, uargs5 =  2560102003;
    uint32_t mask = 3;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 / *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs3) : (*fargs5);
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
TEST_F(Vdiv_32Test, vdiv_32_7){
    acc0.initSetup(0,"testprogs/binaries/vdiv_32_7.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 627887663, uargs1 = 3644376459;
    uint32_t uargs2 = 2392164875, uargs3 =  4146946417;
    uint32_t uargs4 = 1737169449, uargs5 =  427802265;
    uint32_t mask = 1;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 / *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs3) : (*fargs5);
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
TEST_F(Vdiv_32Test, vdiv_32_8){
    acc0.initSetup(0,"testprogs/binaries/vdiv_32_8.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 783381830, uargs1 = 1773054238;
    uint32_t uargs2 = 3852486233, uargs3 =  2629552378;
    uint32_t uargs4 = 2339807977, uargs5 =  1065930272;
    uint32_t mask = 3;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 / *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs3) : (*fargs5);
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
TEST_F(Vdiv_32Test, vdiv_32_9){
    acc0.initSetup(0,"testprogs/binaries/vdiv_32_9.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 1328664636, uargs1 = 585133756;
    uint32_t uargs2 = 1658435385, uargs3 =  184888246;
    uint32_t uargs4 = 4246448707, uargs5 =  948023801;
    uint32_t mask = 1;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 / *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs3) : (*fargs5);
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
TEST_F(Vdiv_32Test, vdiv_32_10){
    acc0.initSetup(0,"testprogs/binaries/vdiv_32_10.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 2024631267, uargs1 = 2838166325;
    uint32_t uargs2 = 4012489137, uargs3 =  433117490;
    uint32_t uargs4 = 3029038956, uargs5 =  4223038749;
    uint32_t mask = 2;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 / *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs3) : (*fargs5);
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
TEST_F(Vdiv_32Test, vdiv_32_11){
    acc0.initSetup(0,"testprogs/binaries/vdiv_32_11.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 1100067764, uargs1 = 1351458326;
    uint32_t uargs2 = 599070796, uargs3 =  2530070774;
    uint32_t uargs4 = 3709454032, uargs5 =  2938851851;
    uint32_t mask = 3;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 / *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs3) : (*fargs5);
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
TEST_F(Vdiv_32Test, vdiv_32_12){
    acc0.initSetup(0,"testprogs/binaries/vdiv_32_12.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 1627339297, uargs1 = 2523189445;
    uint32_t uargs2 = 4207940240, uargs3 =  4232751419;
    uint32_t uargs4 = 1797182057, uargs5 =  619953939;
    uint32_t mask = 3;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 / *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs3) : (*fargs5);
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
TEST_F(Vdiv_32Test, vdiv_32_13){
    acc0.initSetup(0,"testprogs/binaries/vdiv_32_13.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 401738894, uargs1 = 3786106209;
    uint32_t uargs2 = 1757393799, uargs3 =  3721494871;
    uint32_t uargs4 = 2891175382, uargs5 =  3869770068;
    uint32_t mask = 1;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 / *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs3) : (*fargs5);
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
TEST_F(Vdiv_32Test, vdiv_32_14){
    acc0.initSetup(0,"testprogs/binaries/vdiv_32_14.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 1222370604, uargs1 = 723431220;
    uint32_t uargs2 = 2441266005, uargs3 =  3677261768;
    uint32_t uargs4 = 3169517417, uargs5 =  3246196677;
    uint32_t mask = 3;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 / *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs3) : (*fargs5);
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
TEST_F(Vdiv_32Test, vdiv_32_15){
    acc0.initSetup(0,"testprogs/binaries/vdiv_32_15.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 1057448120, uargs1 = 1029458802;
    uint32_t uargs2 = 2451454836, uargs3 =  3588536346;
    uint32_t uargs4 = 1664922677, uargs5 =  3054457291;
    uint32_t mask = 2;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 / *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs3) : (*fargs5);
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
TEST_F(Vdiv_32Test, vdiv_32_16){
    acc0.initSetup(0,"testprogs/binaries/vdiv_32_16.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 1061808315, uargs1 = 2670032346;
    uint32_t uargs2 = 3454646347, uargs3 =  1372649924;
    uint32_t uargs4 = 3112025528, uargs5 =  938351251;
    uint32_t mask = 1;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 / *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs3) : (*fargs5);
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
TEST_F(Vdiv_32Test, vdiv_32_17){
    acc0.initSetup(0,"testprogs/binaries/vdiv_32_17.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 3731968709, uargs1 = 2417462622;
    uint32_t uargs2 = 1994394776, uargs3 =  3813847931;
    uint32_t uargs4 = 3143264956, uargs5 =  902624577;
    uint32_t mask = 2;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 / *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs3) : (*fargs5);
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
TEST_F(Vdiv_32Test, vdiv_32_18){
    acc0.initSetup(0,"testprogs/binaries/vdiv_32_18.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 3774917580, uargs1 = 3114022134;
    uint32_t uargs2 = 1017727937, uargs3 =  3697901716;
    uint32_t uargs4 = 4180838553, uargs5 =  1593807928;
    uint32_t mask = 2;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 / *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs3) : (*fargs5);
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
TEST_F(Vdiv_32Test, vdiv_32_19){
    acc0.initSetup(0,"testprogs/binaries/vdiv_32_19.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 490289524, uargs1 = 2788612687;
    uint32_t uargs2 = 1734503775, uargs3 =  1178141238;
    uint32_t uargs4 = 767388649, uargs5 =  1079682618;
    uint32_t mask = 1;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 / *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs3) : (*fargs5);
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
