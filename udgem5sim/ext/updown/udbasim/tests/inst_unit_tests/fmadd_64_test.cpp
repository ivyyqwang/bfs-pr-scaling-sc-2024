#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"
#include <cmath>
#include <cfenv>

using namespace basim;

class Fmadd_64Test : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    int num_lanes = 64;
    UDAccelerator acc0 = UDAccelerator(num_lanes, 0, 0);
    int buffsize1 = 1024;
    int buffsize2 = 1024;
};
TEST_F(Fmadd_64Test, fmadd_64_0){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_0.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 167127561869305001u, uargs1 = 13162166378011769250u, uargs2 = 18416359987478985481u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;

    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_1){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_1.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 17568604000407378927u, uargs1 = 1920452032538209377u, uargs2 = 6518609164396852118u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_2){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_2.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 7482487377670085983u, uargs1 = 17720597403317092740u, uargs2 = 16077820281310195706u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_3){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_3.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 16551779762806447442u, uargs1 = 8671288703276736685u, uargs2 = 263915821941048162u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_4){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_4.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 16713371604870479780u, uargs1 = 12724400270202242510u, uargs2 = 2946301266763598086u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_5){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_5.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 17593248068871652800u, uargs1 = 1986295819162972708u, uargs2 = 15803587545533372298u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_6){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_6.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 9784348955444755509u, uargs1 = 7206694301959645171u, uargs2 = 15048385584375796581u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_7){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_7.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 1103927136141461617u, uargs1 = 17993287710915852023u, uargs2 = 4092807628505111549u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_8){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_8.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 8512188976068068655u, uargs1 = 18393915430248669779u, uargs2 = 1750816840177943990u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_9){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_9.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 10913186048578676339u, uargs1 = 13492470360414543251u, uargs2 = 4531075928372709658u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_10){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_10.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 9603353188578127892u, uargs1 = 10895578860929759825u, uargs2 = 15929077954877391570u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_11){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_11.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 17049557400629035310u, uargs1 = 426927597342409675u, uargs2 = 9872789976704493098u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_12){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_12.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 6943925961662893576u, uargs1 = 16592967810412115456u, uargs2 = 14206263156146657894u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_13){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_13.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 5251992195803639934u, uargs1 = 1997918095775612204u, uargs2 = 6699255512974518785u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_14){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_14.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 8538429555945599191u, uargs1 = 11034208679968159700u, uargs2 = 11812409103019775858u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_15){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_15.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 16913239622050572730u, uargs1 = 7431571815756820815u, uargs2 = 18359989857201157527u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_16){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_16.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 8020694356119512542u, uargs1 = 13015503535982309667u, uargs2 = 9584457190360860734u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_17){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_17.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 2683317092291026652u, uargs1 = 12465895957576667207u, uargs2 = 8082406416527965998u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_18){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_18.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 5723945549923348284u, uargs1 = 2309122000517247690u, uargs2 = 2406191460744424825u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_19){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_19.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 15415507747001522480u, uargs1 = 14468911259399036630u, uargs2 = 13340060367461669864u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_20){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_20.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 11749323411634192308u, uargs1 = 17315862579277754541u, uargs2 = 13641113207927128310u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_21){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_21.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 15669762988553716771u, uargs1 = 15373232165431678068u, uargs2 = 13555845226760944176u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_22){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_22.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 11210005868371869684u, uargs1 = 210350117339221963u, uargs2 = 2372320070030129453u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_23){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_23.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 14196414133983610183u, uargs1 = 1653352797820457325u, uargs2 = 2925251228220188831u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_24){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_24.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 18071490122766328643u, uargs1 = 15941215974853976892u, uargs2 = 15196290032525469128u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_25){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_25.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 9809716961788198641u, uargs1 = 11207084532377334149u, uargs2 = 3662066293301054483u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_26){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_26.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 4216291269516172545u, uargs1 = 9014987527582886394u, uargs2 = 18273614231201252089u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_27){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_27.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 271691055038616664u, uargs1 = 16634840535576683120u, uargs2 = 7251040076108521943u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_28){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_28.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 4769974716483211885u, uargs1 = 1513550861943009864u, uargs2 = 10810402513218896444u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_29){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_29.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 3436076587683204401u, uargs1 = 17929726389516579887u, uargs2 = 16772304147774936947u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_30){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_30.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 388756019770019361u, uargs1 = 7798488954112119800u, uargs2 = 11380922717827663781u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_31){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_31.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 11884521835009154513u, uargs1 = 14919220267631109325u, uargs2 = 3839209265984550888u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_32){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_32.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 1935481897067183109u, uargs1 = 1726718464695984529u, uargs2 = 8770468313008318421u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_33){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_33.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 7113469046936892254u, uargs1 = 555971180305625569u, uargs2 = 12636183922559509127u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_34){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_34.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 7214814285123132912u, uargs1 = 10966121570592562362u, uargs2 = 12042807197251617439u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_35){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_35.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 9871027776724651855u, uargs1 = 8390407714041369763u, uargs2 = 14281207844753284179u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_36){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_36.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 2881127654928825205u, uargs1 = 580056725900231921u, uargs2 = 4055509790155851504u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_37){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_37.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 9568300731671123352u, uargs1 = 6659389725934106430u, uargs2 = 1064728440033216679u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_38){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_38.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 13200243328395396342u, uargs1 = 4779745559000593631u, uargs2 = 5944115185409331595u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_39){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_39.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 4372995578349305734u, uargs1 = 10879466107622739597u, uargs2 = 14969828626561318430u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_40){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_40.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 17604742826193467732u, uargs1 = 16093400275885204090u, uargs2 = 10945912248087906778u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_41){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_41.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 4076428745774336981u, uargs1 = 993876357708990637u, uargs2 = 9755546170054914349u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_42){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_42.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 1337715060466548900u, uargs1 = 9279812598027147486u, uargs2 = 15665732423322606735u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_43){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_43.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 13956962067033807759u, uargs1 = 7590525155211206225u, uargs2 = 5131821397953819488u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_44){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_44.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 582194296441387374u, uargs1 = 1417845674833483852u, uargs2 = 5145041375474787825u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_45){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_45.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 13971254346221333697u, uargs1 = 1305738182612088210u, uargs2 = 4854203404418329741u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_46){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_46.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 7999387178134700861u, uargs1 = 17810173553282656650u, uargs2 = 6572294761911658152u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_47){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_47.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 8825089428739079096u, uargs1 = 10366131574480172756u, uargs2 = 5511754956629842473u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_48){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_48.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 12689925982010631237u, uargs1 = 17259975170965519212u, uargs2 = 9977149497575259563u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_49){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_49.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 4464972143071604612u, uargs1 = 13756613130644173553u, uargs2 = 9790808673497999646u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_50){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_50.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 7204260904310279798u, uargs1 = 2165481976636501267u, uargs2 = 16716849159209330890u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_51){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_51.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 18081915398679436825u, uargs1 = 18415770057611914172u, uargs2 = 12821120312017630146u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_52){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_52.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 17535563282568314446u, uargs1 = 3516606395244629132u, uargs2 = 14436570560145347579u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_53){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_53.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 7587804304868628033u, uargs1 = 16008792339521750267u, uargs2 = 13942570367582302548u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_54){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_54.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 13649031903802066325u, uargs1 = 6111943817697792809u, uargs2 = 4414661445267280751u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_55){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_55.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 12231576106276048476u, uargs1 = 18054728342363228920u, uargs2 = 14247042964573298008u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_56){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_56.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 13526607340532074632u, uargs1 = 15302464295930836889u, uargs2 = 17151479814171409213u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_57){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_57.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 11964258733602945937u, uargs1 = 1940637806107089187u, uargs2 = 2848168742645262648u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_58){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_58.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 16127902198596592333u, uargs1 = 1735687252933273770u, uargs2 = 5457054968685307057u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_59){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_59.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 2023867482938971974u, uargs1 = 7724902534422658662u, uargs2 = 9808013830237057599u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_60){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_60.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 6888950247105783534u, uargs1 = 4347147707159777520u, uargs2 = 15143127224975017479u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_61){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_61.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 10131880903726495837u, uargs1 = 11426047024659993435u, uargs2 = 3833814533566537960u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_62){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_62.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 8826378421623638458u, uargs1 = 16132013072570072080u, uargs2 = 13124843835301292991u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_63){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_63.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 18396786539749816008u, uargs1 = 10175739647870072225u, uargs2 = 15033345959713393199u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_64){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_64.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 4036181066884311142u, uargs1 = 73617443032099472u, uargs2 = 263339888927606790u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_65){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_65.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 13658134723743781556u, uargs1 = 223700421061600842u, uargs2 = 15026360106383004482u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_66){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_66.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 14531840904145645417u, uargs1 = 6466654529151935157u, uargs2 = 12465436629679949841u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_67){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_67.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 10223777460313931557u, uargs1 = 12142683306536155869u, uargs2 = 4858802837668834510u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_68){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_68.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 14376256893020913241u, uargs1 = 10988536713747712886u, uargs2 = 1725928023325921873u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_69){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_69.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 14509176644788607829u, uargs1 = 818566286253603026u, uargs2 = 403842731570524285u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_70){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_70.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 6097886872311191375u, uargs1 = 9416557382090113328u, uargs2 = 10480084821921801729u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_71){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_71.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 220662352654699771u, uargs1 = 11353306054820887457u, uargs2 = 9176838319221932943u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_72){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_72.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 4142929865812550138u, uargs1 = 9551477301812660994u, uargs2 = 15927210769841271309u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_73){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_73.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 1119407664184759397u, uargs1 = 14365602895617740318u, uargs2 = 3326039311284851636u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_74){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_74.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 1524633107041534258u, uargs1 = 10026925834974214962u, uargs2 = 16223435075636202001u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_75){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_75.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 13284393295254732408u, uargs1 = 6928153076799673819u, uargs2 = 14339538149721582072u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_76){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_76.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 7860271490256315825u, uargs1 = 14884961611523399018u, uargs2 = 10748976558524807745u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_77){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_77.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 1866988828198694561u, uargs1 = 2632435805404566607u, uargs2 = 2982324057145240496u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_78){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_78.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 12907304056097978688u, uargs1 = 1806719876676852862u, uargs2 = 11050545183587350849u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_79){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_79.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 2914374369976612683u, uargs1 = 10937868981630312187u, uargs2 = 1501027993331508574u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_80){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_80.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 5000775043912266546u, uargs1 = 12132738335595229058u, uargs2 = 15157309163408914098u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_81){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_81.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 579400735425314601u, uargs1 = 1716883316150067216u, uargs2 = 539844460073097990u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_82){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_82.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 17543181473547229146u, uargs1 = 12890791405036746015u, uargs2 = 3940416983421894599u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_83){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_83.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 11727632363855993400u, uargs1 = 10457060406305276403u, uargs2 = 1228205066363743433u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_84){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_84.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 12589942408919407703u, uargs1 = 4567094414543734832u, uargs2 = 6810546589718559396u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_85){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_85.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 1568070176367918613u, uargs1 = 9725370175799736803u, uargs2 = 13306636981371292522u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_86){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_86.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 10062033985584011868u, uargs1 = 14648146139443565734u, uargs2 = 12162984403245485061u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_87){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_87.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 3491821724680833737u, uargs1 = 11396966233895495915u, uargs2 = 92972676389684700u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_88){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_88.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 9282166881739012716u, uargs1 = 13706019309308906318u, uargs2 = 14744183688584087446u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_89){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_89.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 10001945482074205343u, uargs1 = 16544620091704816483u, uargs2 = 12458371691604773920u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_90){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_90.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 15336533869237271049u, uargs1 = 7071769474432775105u, uargs2 = 14795601577915641676u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_91){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_91.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 10689259951278174520u, uargs1 = 18346946453419004474u, uargs2 = 18149604918579558550u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_92){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_92.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 16120429902833039787u, uargs1 = 2560159814749866368u, uargs2 = 647377401055901645u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_93){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_93.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 5130899036532796049u, uargs1 = 17893557864988496118u, uargs2 = 16064555443703702813u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_94){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_94.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 15737101598929744268u, uargs1 = 7507779315830916991u, uargs2 = 11016331905641509401u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_95){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_95.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 11028052000886465414u, uargs1 = 13250812420455474202u, uargs2 = 4694199803803044844u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_96){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_96.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 18371612525423638042u, uargs1 = 11308110309521024493u, uargs2 = 15102221827872327556u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_97){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_97.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 8316243477694781444u, uargs1 = 11559083501118146928u, uargs2 = 4026303990090833671u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_98){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_98.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 13901661614010407347u, uargs1 = 4651925582989505476u, uargs2 = 13593984327130526818u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
TEST_F(Fmadd_64Test, fmadd_64_99){
    acc0.initSetup(0,"testprogs/binaries/fmadd_64_99.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint64_t uargs0 = 17555852106833219195u, uargs1 = 18326794513872222411u, uargs2 = 11079019335374125124u;
    double args0 = *reinterpret_cast<double*>(&uargs0), args1 = *reinterpret_cast<double*>(&uargs1), args2 = *reinterpret_cast<double*>(&uargs2);
    std::feclearexcept(FE_ALL_EXCEPT);
    double val = args0 * args1 + args2;
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
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
