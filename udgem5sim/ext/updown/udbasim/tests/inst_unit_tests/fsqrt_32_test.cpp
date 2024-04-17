#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"
#include <cmath>
#include <cfenv>

using namespace basim;

class Fsqrt_32Test : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    int num_lanes = 64;
    UDAccelerator acc0 = UDAccelerator(num_lanes, 0, 0);
    int buffsize1 = 1024;
    int buffsize2 = 1024;
};
TEST_F(Fsqrt_32Test, fsqrt_32_0){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_0.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 3377788124u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_1){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_1.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 454836670u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_2){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_2.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 484994412u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_3){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_3.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 2511454728u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_4){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_4.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 1278698247u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_5){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_5.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 2228953522u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_6){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_6.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 1785661128u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_7){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_7.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 3912678399u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_8){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_8.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 423391359u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_9){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_9.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 2929954978u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_10){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_10.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 2608071693u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_11){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_11.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 2602227149u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_12){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_12.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 3282948531u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_13){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_13.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 2183455308u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_14){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_14.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 4216994109u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_15){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_15.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 419531245u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_16){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_16.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 377037664u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_17){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_17.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 1348727474u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_18){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_18.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 1168478268u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_19){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_19.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 363907922u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_20){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_20.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 3248737876u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_21){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_21.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 3337059975u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_22){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_22.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 4150537860u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_23){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_23.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 3848489790u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_24){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_24.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 2954651507u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_25){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_25.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 3767626784u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_26){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_26.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 4128728947u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_27){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_27.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 3576636038u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_28){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_28.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 2970864336u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_29){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_29.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 3810266197u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_30){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_30.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 709985265u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_31){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_31.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 1162622065u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_32){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_32.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 432425624u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_33){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_33.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 4190298066u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_34){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_34.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 854922505u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_35){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_35.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 1078795404u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_36){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_36.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 2493261616u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_37){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_37.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 123693941u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_38){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_38.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 2636444552u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_39){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_39.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 1000419470u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_40){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_40.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 3775124660u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_41){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_41.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 1731611697u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_42){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_42.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 113196228u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_43){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_43.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 1030495426u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_44){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_44.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 2305511396u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_45){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_45.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 212392678u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_46){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_46.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 691223256u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_47){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_47.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 1421384932u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_48){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_48.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 1511661692u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_49){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_49.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 245357918u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_50){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_50.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 3087119790u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_51){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_51.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 3769818585u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_52){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_52.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 2104505383u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_53){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_53.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 2696256483u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_54){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_54.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 1625644945u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_55){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_55.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 3633017738u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_56){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_56.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 1468227932u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_57){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_57.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 1577680903u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_58){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_58.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 3989812447u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_59){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_59.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 2377996659u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_60){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_60.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 4078043474u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_61){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_61.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 362577345u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_62){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_62.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 3718455u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_63){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_63.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 1641407510u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_64){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_64.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 1736703748u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_65){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_65.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 2608974018u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_66){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_66.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 1565328371u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_67){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_67.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 190649281u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_68){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_68.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 4162710204u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_69){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_69.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 117133399u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_70){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_70.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 1829909645u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_71){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_71.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 1528228931u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_72){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_72.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 593532200u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_73){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_73.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 1075216195u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_74){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_74.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 2595626125u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_75){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_75.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 2369066835u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_76){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_76.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 2643306001u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_77){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_77.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 4132303171u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_78){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_78.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 1628313460u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_79){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_79.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 974226884u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_80){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_80.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 4259143151u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_81){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_81.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 1835529686u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_82){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_82.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 3177996941u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_83){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_83.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 53075535u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_84){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_84.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 190790362u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_85){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_85.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 1790984356u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_86){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_86.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 2080032833u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_87){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_87.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 3241257404u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_88){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_88.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 3201936473u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_89){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_89.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 530514702u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_90){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_90.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 328585391u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_91){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_91.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 1276844912u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_92){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_92.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 401275231u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_93){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_93.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 3925595362u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_94){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_94.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 3758977268u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_95){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_95.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 137291563u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_96){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_96.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 1642968909u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_97){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_97.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 252188355u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_98){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_98.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 2987889723u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
TEST_F(Fsqrt_32Test, fsqrt_32_99){
    acc0.initSetup(0,"testprogs/binaries/fsqrt_32_99.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
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
    uint32_t uargs0 = 2603214394u;
    float args0 = *reinterpret_cast<float*>(&uargs0);
    std::feclearexcept(FE_ALL_EXCEPT);
    float val = sqrt(args0);
    if (std::fetestexcept(FE_INVALID)) {
        FSCR |= (1ULL<<63);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        FSCR |= (1ULL<<62);
    }
    if (std::fetestexcept(FE_OVERFLOW)) {
        FSCR |= (1ULL<<61);
    }
    if (std::fetestexcept(FE_UNDERFLOW)) {
        FSCR |= (1ULL<<60);
    }
    if (std::fetestexcept(FE_INEXACT)) {
        FSCR |= (1ULL<<59);
    }
    uint32_t* uint_val = reinterpret_cast<uint32_t*>(&val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, *uint_val));
    EXPECT_TRUE(acc0.testReg(0, RegId::X4, FSCR));
}
