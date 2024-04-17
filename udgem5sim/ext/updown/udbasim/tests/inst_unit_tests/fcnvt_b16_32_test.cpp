#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"
#include <cmath>
#include <cfenv>

using namespace basim;

class Fcnvt_b16_32Test : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    int num_lanes = 64;
    UDAccelerator acc0 = UDAccelerator(num_lanes, 0, 0);
    int buffsize1 = 1024;
    int buffsize2 = 1024;
};
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_0){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_0.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 6805u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_1){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_1.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 49264u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_2){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_2.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 24003u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_3){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_3.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 36959u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_4){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_4.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 11996u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_5){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_5.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 13126u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_6){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_6.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 62362u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_7){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_7.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 25375u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_8){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_8.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 23115u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_9){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_9.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 29140u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_10){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_10.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 15302u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_11){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_11.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 31419u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_12){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_12.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 4724u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_13){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_13.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 6350u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_14){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_14.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 58667u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_15){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_15.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 10553u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_16){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_16.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 37871u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_17){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_17.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 8337u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_18){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_18.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 64202u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_19){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_19.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 372u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_20){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_20.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 16497u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_21){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_21.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 16850u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_22){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_22.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 41742u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_23){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_23.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 36329u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_24){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_24.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 47353u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_25){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_25.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 54542u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_26){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_26.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 28170u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_27){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_27.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 885u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_28){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_28.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 64203u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_29){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_29.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 52492u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_30){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_30.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 43733u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_31){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_31.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 62203u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_32){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_32.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 60870u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_33){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_33.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 26753u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_34){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_34.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 41895u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_35){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_35.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 9502u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_36){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_36.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 983u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_37){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_37.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 20721u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_38){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_38.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 43089u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_39){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_39.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 4922u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_40){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_40.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 15010u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_41){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_41.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 17581u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_42){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_42.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 64521u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_43){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_43.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 37657u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_44){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_44.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 24769u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_45){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_45.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 26983u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_46){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_46.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 7957u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_47){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_47.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 56917u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_48){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_48.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 61191u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_49){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_49.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 57894u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_50){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_50.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 14582u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_51){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_51.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 33753u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_52){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_52.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 44988u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_53){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_53.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 49000u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_54){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_54.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 13622u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_55){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_55.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 26172u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_56){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_56.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 64526u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_57){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_57.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 29883u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_58){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_58.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 27774u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_59){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_59.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 19887u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_60){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_60.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 5476u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_61){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_61.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 20628u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_62){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_62.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 44926u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_63){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_63.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 34717u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_64){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_64.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 6725u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_65){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_65.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 3015u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_66){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_66.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 45446u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_67){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_67.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 64989u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_68){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_68.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 3566u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_69){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_69.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 64113u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_70){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_70.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 47441u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_71){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_71.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 61980u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_72){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_72.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 2960u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_73){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_73.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 35445u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_74){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_74.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 56866u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_75){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_75.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 25337u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_76){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_76.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 17980u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_77){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_77.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 13471u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_78){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_78.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 13379u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_79){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_79.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 4028u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_80){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_80.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 48287u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_81){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_81.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 20796u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_82){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_82.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 22641u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_83){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_83.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 10349u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_84){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_84.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 17370u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_85){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_85.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 45448u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_86){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_86.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 22043u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_87){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_87.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 44337u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_88){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_88.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 6144u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_89){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_89.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 26033u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_90){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_90.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 23229u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_91){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_91.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 49686u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_92){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_92.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 44777u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_93){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_93.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 28455u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_94){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_94.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 29246u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_95){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_95.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 6989u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_96){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_96.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 20535u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_97){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_97.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 60032u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_98){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_98.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 31541u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_32Test, fcnvt_b16_32_99){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_32_99.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t val = 10841u<<16;
    word_t uint64_val = word_t(val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
