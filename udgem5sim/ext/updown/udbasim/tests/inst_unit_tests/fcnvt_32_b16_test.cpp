#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"
#include <cmath>
#include <cfenv>

using namespace basim;

class Fcnvt_32_b16Test : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    int num_lanes = 64;
    UDAccelerator acc0 = UDAccelerator(num_lanes, 0, 0);
    int buffsize1 = 1024;
    int buffsize2 = 1024;
};
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_0){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_0.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2460553843u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_1){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_1.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3808656845u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_2){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_2.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3436651177u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_3){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_3.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1552225730u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_4){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_4.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1906127078u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_5){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_5.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 658829574u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_6){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_6.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 602015134u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_7){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_7.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3687207000u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_8){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_8.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 23787281u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_9){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_9.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2454176466u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_10){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_10.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2925809811u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_11){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_11.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2126947185u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_12){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_12.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 957043969u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_13){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_13.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3906763205u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_14){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_14.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3978271524u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_15){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_15.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1773453903u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_16){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_16.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 4052182124u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_17){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_17.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1209053873u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_18){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_18.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1531226025u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_19){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_19.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 4260756942u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_20){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_20.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 87293110u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_21){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_21.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3759566410u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_22){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_22.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 333469588u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_23){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_23.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1824602334u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_24){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_24.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3634087054u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_25){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_25.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2926817190u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_26){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_26.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1442696071u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_27){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_27.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 823452639u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_28){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_28.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1556771021u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_29){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_29.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1036757314u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_30){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_30.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2240337856u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_31){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_31.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2102451871u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_32){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_32.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 194582149u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_33){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_33.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3811242989u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_34){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_34.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3848291222u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_35){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_35.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1921508332u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_36){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_36.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3916544367u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_37){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_37.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1288983432u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_38){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_38.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 329784134u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_39){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_39.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 114218545u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_40){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_40.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 4119379419u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_41){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_41.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2625872288u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_42){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_42.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 311374718u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_43){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_43.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1944285472u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_44){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_44.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2197418896u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_45){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_45.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3080746148u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_46){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_46.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1319566996u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_47){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_47.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1092021934u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_48){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_48.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 90971928u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_49){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_49.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2189467011u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_50){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_50.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 167837915u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_51){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_51.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 998671711u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_52){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_52.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1598272119u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_53){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_53.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1486972839u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_54){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_54.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 4093762032u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_55){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_55.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 624359618u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_56){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_56.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 239837002u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_57){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_57.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1128561470u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_58){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_58.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1095363938u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_59){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_59.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1241090876u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_60){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_60.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 107639420u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_61){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_61.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 4041332655u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_62){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_62.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2358599681u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_63){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_63.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2874352246u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_64){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_64.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2402875460u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_65){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_65.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1047967537u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_66){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_66.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 981253821u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_67){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_67.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3141667691u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_68){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_68.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1937532586u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_69){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_69.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3537856936u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_70){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_70.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 4120258480u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_71){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_71.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1744681458u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_72){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_72.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2272964857u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_73){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_73.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 925619800u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_74){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_74.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1265483461u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_75){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_75.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1012214494u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_76){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_76.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2320848473u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_77){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_77.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1316288698u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_78){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_78.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1391557595u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_79){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_79.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2124375291u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_80){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_80.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2173662577u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_81){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_81.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 810890918u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_82){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_82.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 792250998u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_83){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_83.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1520105130u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_84){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_84.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1455781358u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_85){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_85.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2658844584u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_86){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_86.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 4229152512u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_87){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_87.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2512608526u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_88){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_88.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 83266963u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_89){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_89.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1254609650u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_90){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_90.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 4256190527u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_91){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_91.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1565507912u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_92){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_92.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3103140024u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_93){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_93.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2169306550u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_94){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_94.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 164923743u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_95){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_95.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 608762256u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_96){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_96.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3435783105u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_97){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_97.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3423120949u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_98){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_98.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 852957734u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_b16Test, fcnvt_32_b16_99){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_b16_99.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2283869627u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
