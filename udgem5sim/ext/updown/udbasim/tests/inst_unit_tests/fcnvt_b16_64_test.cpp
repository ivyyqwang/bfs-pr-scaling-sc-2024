#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"
#include <cmath>
#include <cfenv>

using namespace basim;

class Fcnvt_b16_64Test : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    int num_lanes = 64;
    UDAccelerator acc0 = UDAccelerator(num_lanes, 0, 0);
    int buffsize1 = 1024;
    int buffsize2 = 1024;
};
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_0){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_0.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 14915u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_1){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_1.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 36467u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_2){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_2.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 25834u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_3){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_3.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 41905u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_4){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_4.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 58776u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_5){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_5.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 62624u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_6){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_6.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 8117u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_7){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_7.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 53869u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_8){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_8.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 12048u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_9){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_9.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 26087u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_10){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_10.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 4376u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_11){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_11.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 18550u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_12){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_12.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 42943u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_13){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_13.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 4588u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_14){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_14.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 57214u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_15){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_15.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 31994u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_16){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_16.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 40789u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_17){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_17.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 4770u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_18){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_18.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 48776u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_19){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_19.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 14595u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_20){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_20.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 44086u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_21){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_21.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 47595u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_22){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_22.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 43086u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_23){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_23.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 22240u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_24){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_24.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 36833u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_25){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_25.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 58184u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_26){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_26.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 49390u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_27){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_27.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 27195u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_28){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_28.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 24111u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_29){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_29.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 22093u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_30){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_30.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 31054u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_31){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_31.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 20195u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_32){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_32.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 54170u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_33){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_33.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 52290u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_34){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_34.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 52838u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_35){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_35.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 56426u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_36){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_36.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 60032u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_37){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_37.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 47846u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_38){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_38.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 10496u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_39){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_39.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1071u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_40){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_40.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 51217u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_41){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_41.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 13627u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_42){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_42.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 12447u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_43){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_43.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 41939u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_44){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_44.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 16745u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_45){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_45.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 27457u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_46){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_46.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 26252u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_47){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_47.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 59689u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_48){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_48.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 27899u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_49){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_49.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 45918u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_50){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_50.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 23862u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_51){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_51.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 56875u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_52){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_52.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 23155u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_53){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_53.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 4497u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_54){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_54.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 13598u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_55){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_55.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 23399u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_56){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_56.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 5092u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_57){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_57.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 12795u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_58){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_58.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 33201u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_59){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_59.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 38468u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_60){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_60.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 42255u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_61){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_61.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 13774u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_62){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_62.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3373u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_63){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_63.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1644u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_64){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_64.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 52263u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_65){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_65.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 34513u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_66){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_66.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 57393u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_67){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_67.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 54953u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_68){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_68.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 27851u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_69){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_69.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 37871u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_70){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_70.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 50531u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_71){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_71.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 9986u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_72){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_72.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 22700u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_73){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_73.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 55665u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_74){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_74.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 17156u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_75){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_75.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 14789u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_76){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_76.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 25578u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_77){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_77.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 41230u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_78){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_78.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 18062u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_79){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_79.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 59672u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_80){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_80.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 56030u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_81){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_81.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 26276u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_82){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_82.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 21374u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_83){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_83.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 46983u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_84){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_84.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 43858u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_85){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_85.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 29318u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_86){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_86.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 13932u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_87){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_87.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 29372u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_88){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_88.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 13606u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_89){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_89.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 30809u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_90){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_90.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 42711u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_91){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_91.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 50218u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_92){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_92.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 50735u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_93){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_93.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 59924u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_94){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_94.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 22905u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_95){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_95.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 60296u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_96){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_96.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 19746u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_97){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_97.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 50777u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_98){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_98.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 10921u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_b16_64Test, fcnvt_b16_64_99){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_b16_64_99.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 33573u<<16;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
