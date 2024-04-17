#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"
#include <cmath>
#include <cfenv>

using namespace basim;

class Fcnvt_32_64Test : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    int num_lanes = 64;
    UDAccelerator acc0 = UDAccelerator(num_lanes, 0, 0);
    int buffsize1 = 1024;
    int buffsize2 = 1024;
};
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_0){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_0.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1453283058u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_1){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_1.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 439859872u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_2){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_2.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 108784828u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_3){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_3.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3449285776u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_4){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_4.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1818270775u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_5){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_5.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 860934465u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_6){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_6.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2777129617u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_7){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_7.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1844895563u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_8){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_8.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3789511719u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_9){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_9.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1465278002u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_10){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_10.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2628258342u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_11){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_11.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1997028618u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_12){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_12.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3680305757u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_13){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_13.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2432573186u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_14){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_14.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 22170362u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_15){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_15.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3908501072u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_16){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_16.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1977385825u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_17){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_17.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3906689220u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_18){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_18.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3824763684u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_19){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_19.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3498463674u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_20){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_20.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 721120459u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_21){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_21.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 678142018u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_22){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_22.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1513822088u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_23){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_23.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2507902754u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_24){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_24.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1502433572u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_25){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_25.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3435735358u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_26){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_26.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2251105364u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_27){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_27.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 591471847u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_28){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_28.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3953659502u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_29){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_29.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2190697215u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_30){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_30.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2834476732u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_31){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_31.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2084719909u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_32){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_32.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 663548682u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_33){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_33.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1912403023u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_34){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_34.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 369523284u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_35){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_35.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3290588834u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_36){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_36.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3179629288u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_37){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_37.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1367472105u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_38){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_38.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3502051118u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_39){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_39.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3991565324u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_40){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_40.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1709019334u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_41){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_41.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2525468298u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_42){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_42.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3104203322u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_43){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_43.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1769117205u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_44){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_44.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1742177969u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_45){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_45.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 231629591u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_46){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_46.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 202719579u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_47){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_47.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1596824785u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_48){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_48.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3742365938u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_49){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_49.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2729722345u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_50){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_50.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1851422130u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_51){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_51.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1332165491u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_52){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_52.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2847464219u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_53){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_53.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3645517415u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_54){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_54.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2077281902u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_55){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_55.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1898843880u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_56){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_56.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 231224384u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_57){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_57.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 806338495u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_58){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_58.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2682122329u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_59){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_59.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 4252506528u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_60){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_60.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1275392789u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_61){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_61.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 600334392u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_62){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_62.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3767250766u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_63){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_63.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3026654655u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_64){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_64.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 362559677u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_65){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_65.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 854103094u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_66){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_66.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 4240623805u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_67){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_67.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 324247244u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_68){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_68.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 101042673u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_69){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_69.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3669003876u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_70){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_70.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2791722311u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_71){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_71.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3332981643u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_72){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_72.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 256089858u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_73){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_73.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1657458705u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_74){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_74.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3061741938u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_75){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_75.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2762063465u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_76){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_76.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3958802669u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_77){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_77.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 35857643u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_78){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_78.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1475026523u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_79){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_79.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 4165486726u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_80){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_80.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 245277326u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_81){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_81.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3253574907u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_82){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_82.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2032180905u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_83){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_83.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3437346277u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_84){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_84.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 680460375u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_85){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_85.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3663301523u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_86){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_86.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 448219292u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_87){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_87.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2510049433u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_88){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_88.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3697900442u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_89){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_89.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 935994790u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_90){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_90.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3249059738u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_91){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_91.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 38149554u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_92){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_92.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 4189925562u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_93){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_93.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2557538564u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_94){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_94.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3632403865u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_95){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_95.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1660227224u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_96){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_96.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 468561274u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_97){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_97.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3987104158u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_98){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_98.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1563520389u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_64Test, fcnvt_32_64_99){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_64_99.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1485448788u;
    float fval = *reinterpret_cast<float*>(&raw_val);
    double dval = double(fval);
    word_t uint64_val = *reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
