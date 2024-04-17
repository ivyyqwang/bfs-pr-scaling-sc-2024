#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"
#include <cmath>
#include <cfenv>

using namespace basim;

class Fmul_64Test : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    int num_lanes = 64;
    UDAccelerator acc0 = UDAccelerator(num_lanes, 0, 0);
    int buffsize1 = 1024;
    int buffsize2 = 1024;
};
TEST_F(Fmul_64Test, fmul_64_0){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_0.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 18358709277278524546u, uargs1 = 8776797939075774284u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_1){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_1.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 14223716933965507363u, uargs1 = 9193297781272456091u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_2){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_2.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 6361439000398336430u, uargs1 = 5374520392652572423u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_3){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_3.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 8929170367196418124u, uargs1 = 8928563326002887414u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_4){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_4.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 17005546920338685298u, uargs1 = 14645974767683744323u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_5){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_5.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 6276590293365829889u, uargs1 = 1414369492898450272u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_6){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_6.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 11807333879740778294u, uargs1 = 7161080794785397265u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_7){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_7.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 12944896877740686000u, uargs1 = 2187986649929427119u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_8){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_8.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 12859991709107698720u, uargs1 = 10275253530275532137u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_9){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_9.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 9295940012227462595u, uargs1 = 2918865763166409178u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_10){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_10.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 4045422644534516065u, uargs1 = 5802090506667964707u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_11){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_11.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 11490461699689516958u, uargs1 = 7263687529751493684u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_12){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_12.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 6058500451866764825u, uargs1 = 17723949096634263923u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_13){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_13.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 7080752444548109134u, uargs1 = 8429127786021423821u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_14){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_14.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 86058334963987221u, uargs1 = 12367784238242286888u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_15){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_15.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 11480024253230734370u, uargs1 = 10708398962692162981u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_16){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_16.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 1876620913131125313u, uargs1 = 16374915656383612761u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_17){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_17.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 39380538793849226u, uargs1 = 5441092222874508991u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_18){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_18.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 6030124124758545725u, uargs1 = 16977358209019364652u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_19){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_19.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 3973377072788005781u, uargs1 = 1832144700979329693u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_20){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_20.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 919134862370298263u, uargs1 = 17992281178533571805u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_21){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_21.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 10882305015616733066u, uargs1 = 4490694164944206715u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_22){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_22.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 7458033682585476418u, uargs1 = 4328922655146986483u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_23){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_23.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 4938482938706955838u, uargs1 = 12994731741380462461u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_24){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_24.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 3926229620556570077u, uargs1 = 16786975866610016750u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_25){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_25.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 3599967750186600628u, uargs1 = 889704045700104915u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_26){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_26.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 7902615733487589313u, uargs1 = 8782081877749252824u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_27){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_27.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 7462920259284060780u, uargs1 = 7317276998046171291u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_28){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_28.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 16479533068249637923u, uargs1 = 10446545849843017409u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_29){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_29.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 9805395624029290264u, uargs1 = 12252657974327381950u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_30){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_30.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 5265077230099947793u, uargs1 = 4075659506200094605u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_31){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_31.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 13652816890612246466u, uargs1 = 12054318721287890834u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_32){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_32.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 15361036603215039148u, uargs1 = 9849695497005934164u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_33){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_33.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 2321388681156143950u, uargs1 = 5528196095334573037u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_34){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_34.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 10775741561385219702u, uargs1 = 4968050251479265509u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_35){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_35.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 10318667152681208126u, uargs1 = 6998800544722614361u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_36){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_36.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 13614616095385532279u, uargs1 = 4046232882247495939u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_37){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_37.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 15398958469987636211u, uargs1 = 15836036182055710525u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_38){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_38.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 12272526055697564055u, uargs1 = 18229824355815199878u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_39){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_39.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 18296704448415765864u, uargs1 = 8825193766275709594u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_40){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_40.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 7818468428318999530u, uargs1 = 7404730787506022070u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_41){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_41.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 7384020445467323569u, uargs1 = 3053700894774237032u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_42){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_42.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 9600578272632588152u, uargs1 = 11365094377791255930u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_43){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_43.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 11964195457773142972u, uargs1 = 3313305033671496116u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_44){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_44.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 434723404155222348u, uargs1 = 14849085750934674391u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_45){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_45.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 12568180930107722893u, uargs1 = 16213291359371602058u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_46){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_46.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 13246774072774026107u, uargs1 = 9199956295362997666u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_47){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_47.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 7992656388181133192u, uargs1 = 16130368968435492921u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_48){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_48.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 1634392746452326578u, uargs1 = 5415232854779637473u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_49){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_49.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 3810230996460147548u, uargs1 = 15098034876272113496u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_50){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_50.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 1730720158969224845u, uargs1 = 6682999870920776062u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_51){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_51.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 1364408374809619054u, uargs1 = 1407294097223104602u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_52){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_52.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 11187419121635649919u, uargs1 = 12909766866763052624u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_53){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_53.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 16388315846644932524u, uargs1 = 4165102381463926831u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_54){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_54.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 4374849883033933085u, uargs1 = 8814557864424590823u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_55){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_55.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 13818124466710341177u, uargs1 = 5738804765205826454u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_56){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_56.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 3915608501065216214u, uargs1 = 185837485379194900u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_57){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_57.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 6489474849316494319u, uargs1 = 3688152430091697948u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_58){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_58.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 14257519986117555088u, uargs1 = 1258643806943918731u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_59){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_59.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 16656898801335426879u, uargs1 = 7408952989973312067u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_60){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_60.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 1859532961614922293u, uargs1 = 3146976994984888141u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_61){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_61.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 7032474165021175096u, uargs1 = 10353355266101631193u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_62){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_62.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 234771363531789296u, uargs1 = 13358297214583211870u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_63){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_63.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 643950764308265574u, uargs1 = 10237610280692099390u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_64){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_64.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 2826462450400157350u, uargs1 = 15750426049254720780u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_65){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_65.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 6341875365719534397u, uargs1 = 10005790997913620256u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_66){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_66.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 7967453191989631613u, uargs1 = 7508687673746937348u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_67){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_67.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 10956289906177535164u, uargs1 = 16620382125573876544u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_68){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_68.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 18293536907452919899u, uargs1 = 7149787116891424088u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_69){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_69.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 3621066720993272446u, uargs1 = 292776248140175367u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_70){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_70.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 4144397511539305426u, uargs1 = 14610037417371485017u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_71){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_71.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 16517011948638431341u, uargs1 = 4224362712437751440u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_72){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_72.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 13159217782373153600u, uargs1 = 2855302444997554795u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_73){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_73.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 2763692795990890631u, uargs1 = 8773582116044409469u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_74){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_74.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 7030045258812742207u, uargs1 = 18334458702636098004u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_75){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_75.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 10962594165985506581u, uargs1 = 7239340561106523339u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_76){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_76.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 15218537586333295319u, uargs1 = 13747080181132921349u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_77){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_77.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 11715102485482045078u, uargs1 = 17180716542123963226u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_78){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_78.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 16497688013204299011u, uargs1 = 16081521041439441807u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_79){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_79.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 18250747648704218053u, uargs1 = 16730122765560105126u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_80){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_80.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 15635125764203068084u, uargs1 = 9964185032888679074u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_81){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_81.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 17688404287245799173u, uargs1 = 10619575428090014762u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_82){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_82.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 17218639325325273340u, uargs1 = 6855704224080816789u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_83){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_83.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 17735598522142882442u, uargs1 = 14101905426179202403u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_84){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_84.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 851134700649845280u, uargs1 = 13225321590380296783u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_85){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_85.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 15032665718904123279u, uargs1 = 13177604904297626653u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_86){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_86.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 12297547860836925599u, uargs1 = 14532969256630217513u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_87){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_87.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 10058062690342434459u, uargs1 = 9368559185989213826u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_88){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_88.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 9938202579977993917u, uargs1 = 11232914818876204215u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_89){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_89.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 3823376113945472646u, uargs1 = 16408388514893109791u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_90){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_90.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 6194790711155593078u, uargs1 = 14863781465254746122u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_91){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_91.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 5355295312910359331u, uargs1 = 3804466781963046589u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_92){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_92.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 1037657510823892240u, uargs1 = 2897307120429416049u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_93){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_93.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 7344230623367033766u, uargs1 = 969237855051142906u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_94){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_94.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 8623148653411182309u, uargs1 = 10405691388144280439u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_95){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_95.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 7345471709119835461u, uargs1 = 18288050924675604006u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_96){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_96.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 14362316873043996410u, uargs1 = 15305630268122756996u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_97){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_97.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 6024615293311059283u, uargs1 = 9988325320643384984u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_98){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_98.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 11794285849632904798u, uargs1 = 10334246078270585882u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fmul_64Test, fmul_64_99){
    acc0.initSetup(0,"testprogs/binaries/fmul_64_99.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 17838935023546064988u, uargs1 = 17193913981861546641u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    word_t* uint_val = reinterpret_cast<word_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
