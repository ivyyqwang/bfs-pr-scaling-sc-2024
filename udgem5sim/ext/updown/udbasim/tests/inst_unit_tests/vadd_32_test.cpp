#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"
#include <cmath>
#include <cfenv>

using namespace basim;

class Vadd_32Test : public ::testing::Test {
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
TEST_F(Vadd_32Test, vadd_32_0){
    acc0.initSetup(0,"testprogs/binaries/vadd_32_0.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 2315104202, uargs1 = 663844889;
    uint32_t uargs2 = 28099205, uargs3 =  1929833239;
    uint32_t uargs4 = 4284893040, uargs5 =  1826465012;
    uint32_t mask = 2;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 + *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 + *fargs3) : (*fargs5);
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
TEST_F(Vadd_32Test, vadd_32_1){
    acc0.initSetup(0,"testprogs/binaries/vadd_32_1.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 188184569, uargs1 = 2153519522;
    uint32_t uargs2 = 2665531642, uargs3 =  3619272636;
    uint32_t uargs4 = 1496906984, uargs5 =  994294204;
    uint32_t mask = 1;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 + *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 + *fargs3) : (*fargs5);
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
TEST_F(Vadd_32Test, vadd_32_2){
    acc0.initSetup(0,"testprogs/binaries/vadd_32_2.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 4188287955, uargs1 = 1456755678;
    uint32_t uargs2 = 231812838, uargs3 =  4216939540;
    uint32_t uargs4 = 3635399065, uargs5 =  1527371960;
    uint32_t mask = 3;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 + *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 + *fargs3) : (*fargs5);
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
TEST_F(Vadd_32Test, vadd_32_3){
    acc0.initSetup(0,"testprogs/binaries/vadd_32_3.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 2124928482, uargs1 = 2466084345;
    uint32_t uargs2 = 3289274838, uargs3 =  3034875375;
    uint32_t uargs4 = 3621415183, uargs5 =  245920037;
    uint32_t mask = 2;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 + *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 + *fargs3) : (*fargs5);
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
TEST_F(Vadd_32Test, vadd_32_4){
    acc0.initSetup(0,"testprogs/binaries/vadd_32_4.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 3088425684, uargs1 = 1590594831;
    uint32_t uargs2 = 1436263442, uargs3 =  793349056;
    uint32_t uargs4 = 656436008, uargs5 =  2215787184;
    uint32_t mask = 2;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 + *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 + *fargs3) : (*fargs5);
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
TEST_F(Vadd_32Test, vadd_32_5){
    acc0.initSetup(0,"testprogs/binaries/vadd_32_5.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 3317183278, uargs1 = 2275090770;
    uint32_t uargs2 = 3253788581, uargs3 =  736352738;
    uint32_t uargs4 = 4173701800, uargs5 =  318466211;
    uint32_t mask = 1;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 + *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 + *fargs3) : (*fargs5);
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
TEST_F(Vadd_32Test, vadd_32_6){
    acc0.initSetup(0,"testprogs/binaries/vadd_32_6.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 3673717178, uargs1 = 1872194170;
    uint32_t uargs2 = 994915033, uargs3 =  3228089382;
    uint32_t uargs4 = 1733257663, uargs5 =  547113670;
    uint32_t mask = 3;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 + *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 + *fargs3) : (*fargs5);
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
TEST_F(Vadd_32Test, vadd_32_7){
    acc0.initSetup(0,"testprogs/binaries/vadd_32_7.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 1811585986, uargs1 = 439757906;
    uint32_t uargs2 = 984018214, uargs3 =  3969613260;
    uint32_t uargs4 = 2670723408, uargs5 =  31534964;
    uint32_t mask = 3;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 + *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 + *fargs3) : (*fargs5);
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
TEST_F(Vadd_32Test, vadd_32_8){
    acc0.initSetup(0,"testprogs/binaries/vadd_32_8.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 3619996333, uargs1 = 1270525934;
    uint32_t uargs2 = 3196971008, uargs3 =  2336024889;
    uint32_t uargs4 = 966255425, uargs5 =  2262506615;
    uint32_t mask = 1;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 + *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 + *fargs3) : (*fargs5);
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
TEST_F(Vadd_32Test, vadd_32_9){
    acc0.initSetup(0,"testprogs/binaries/vadd_32_9.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 717908945, uargs1 = 1060291615;
    uint32_t uargs2 = 1052746834, uargs3 =  3630405484;
    uint32_t uargs4 = 597804511, uargs5 =  981842293;
    uint32_t mask = 3;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 + *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 + *fargs3) : (*fargs5);
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
TEST_F(Vadd_32Test, vadd_32_10){
    acc0.initSetup(0,"testprogs/binaries/vadd_32_10.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 3644341948, uargs1 = 4145816115;
    uint32_t uargs2 = 2323963233, uargs3 =  1300702949;
    uint32_t uargs4 = 3699365098, uargs5 =  688239141;
    uint32_t mask = 3;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 + *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 + *fargs3) : (*fargs5);
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
TEST_F(Vadd_32Test, vadd_32_11){
    acc0.initSetup(0,"testprogs/binaries/vadd_32_11.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 3688916881, uargs1 = 1188002424;
    uint32_t uargs2 = 923587314, uargs3 =  3650315695;
    uint32_t uargs4 = 1078760591, uargs5 =  3936154216;
    uint32_t mask = 1;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 + *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 + *fargs3) : (*fargs5);
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
TEST_F(Vadd_32Test, vadd_32_12){
    acc0.initSetup(0,"testprogs/binaries/vadd_32_12.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 2461643391, uargs1 = 2841581995;
    uint32_t uargs2 = 3929926711, uargs3 =  1996731730;
    uint32_t uargs4 = 2927242734, uargs5 =  1835136245;
    uint32_t mask = 2;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 + *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 + *fargs3) : (*fargs5);
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
TEST_F(Vadd_32Test, vadd_32_13){
    acc0.initSetup(0,"testprogs/binaries/vadd_32_13.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 374143278, uargs1 = 3163763753;
    uint32_t uargs2 = 2747852512, uargs3 =  1386790542;
    uint32_t uargs4 = 69427999, uargs5 =  990045910;
    uint32_t mask = 3;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 + *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 + *fargs3) : (*fargs5);
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
TEST_F(Vadd_32Test, vadd_32_14){
    acc0.initSetup(0,"testprogs/binaries/vadd_32_14.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 3562452122, uargs1 = 291734140;
    uint32_t uargs2 = 1961724871, uargs3 =  664684388;
    uint32_t uargs4 = 924631354, uargs5 =  544898515;
    uint32_t mask = 2;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 + *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 + *fargs3) : (*fargs5);
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
TEST_F(Vadd_32Test, vadd_32_15){
    acc0.initSetup(0,"testprogs/binaries/vadd_32_15.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 2633389489, uargs1 = 2839944609;
    uint32_t uargs2 = 513371394, uargs3 =  4101237371;
    uint32_t uargs4 = 1763026507, uargs5 =  2085302721;
    uint32_t mask = 3;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 + *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 + *fargs3) : (*fargs5);
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
TEST_F(Vadd_32Test, vadd_32_16){
    acc0.initSetup(0,"testprogs/binaries/vadd_32_16.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 2159644729, uargs1 = 18211893;
    uint32_t uargs2 = 2550466961, uargs3 =  1906011495;
    uint32_t uargs4 = 170756404, uargs5 =  641263535;
    uint32_t mask = 3;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 + *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 + *fargs3) : (*fargs5);
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
TEST_F(Vadd_32Test, vadd_32_17){
    acc0.initSetup(0,"testprogs/binaries/vadd_32_17.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 1760645429, uargs1 = 1084203209;
    uint32_t uargs2 = 721681131, uargs3 =  1517533862;
    uint32_t uargs4 = 3196790358, uargs5 =  805381993;
    uint32_t mask = 2;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 + *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 + *fargs3) : (*fargs5);
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
TEST_F(Vadd_32Test, vadd_32_18){
    acc0.initSetup(0,"testprogs/binaries/vadd_32_18.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 4122043399, uargs1 = 4007945364;
    uint32_t uargs2 = 2711908650, uargs3 =  3804207955;
    uint32_t uargs4 = 1366645410, uargs5 =  2718420961;
    uint32_t mask = 2;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 + *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 + *fargs3) : (*fargs5);
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
TEST_F(Vadd_32Test, vadd_32_19){
    acc0.initSetup(0,"testprogs/binaries/vadd_32_19.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 1118203622, uargs1 = 3745235233;
    uint32_t uargs2 = 635433961, uargs3 =  612460685;
    uint32_t uargs4 = 829320000, uargs5 =  2948657467;
    uint32_t mask = 3;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    float *fargs2 = reinterpret_cast<float*>(&uargs2), *fargs3 = reinterpret_cast<float*>(&uargs3);
    float *fargs4 = reinterpret_cast<float*>(&uargs4), *fargs5 = reinterpret_cast<float*>(&uargs5);
    std::feclearexcept(FE_ALL_EXCEPT);
    val0 = (mask & 1) ? (*fargs0 + *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 + *fargs3) : (*fargs5);
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
