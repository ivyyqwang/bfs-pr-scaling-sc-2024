#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"
#include <cmath>
#include <cfenv>

using namespace basim;

class Fcnvt_i32_32Test : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    int num_lanes = 64;
    UDAccelerator acc0 = UDAccelerator(num_lanes, 0, 0);
    int buffsize1 = 1024;
    int buffsize2 = 1024;
};
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_0){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_0.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = 343297260;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_1){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_1.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = 367338663;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_2){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_2.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -2008116877;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_3){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_3.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -365060682;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_4){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_4.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = 1635778826;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_5){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_5.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -1014016760;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_6){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_6.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = 1155986215;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_7){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_7.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -199014253;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_8){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_8.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = 166551632;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_9){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_9.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -1741678499;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_10){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_10.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = 1581594942;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_11){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_11.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -1103357115;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_12){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_12.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -318739020;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_13){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_13.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -1054825419;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_14){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_14.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = 89041880;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_15){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_15.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -1132575996;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_16){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_16.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -1883093159;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_17){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_17.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -956638265;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_18){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_18.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -1116995141;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_19){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_19.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = 1500984701;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_20){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_20.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -275034261;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_21){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_21.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -152622307;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_22){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_22.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = 1053083849;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_23){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_23.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -1640108147;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_24){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_24.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = 2072095760;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_25){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_25.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = 655380676;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_26){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_26.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = 1471554994;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_27){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_27.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -1392413892;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_28){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_28.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = 266833885;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_29){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_29.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -1701925224;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_30){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_30.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -724213829;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_31){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_31.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = 484338288;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_32){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_32.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -1035904044;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_33){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_33.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -472967405;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_34){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_34.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = 506814507;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_35){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_35.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = 1224296992;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_36){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_36.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = 448721029;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_37){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_37.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = 1597282017;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_38){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_38.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -1448570575;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_39){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_39.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -73810513;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_40){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_40.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = 73448752;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_41){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_41.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -1375526211;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_42){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_42.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = 454055461;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_43){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_43.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -1430384650;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_44){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_44.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -1565342727;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_45){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_45.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = 1621443873;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_46){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_46.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -1842519527;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_47){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_47.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -2084970868;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_48){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_48.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = 738643093;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_49){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_49.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = 1127423643;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_50){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_50.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = 304780860;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_51){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_51.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = 1969945480;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_52){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_52.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -129722543;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_53){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_53.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = 28503771;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_54){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_54.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = 817005291;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_55){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_55.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = 122507176;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_56){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_56.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -1616096502;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_57){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_57.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = 1829999318;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_58){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_58.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = 26151701;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_59){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_59.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -1028952778;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_60){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_60.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -1695719276;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_61){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_61.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -166214229;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_62){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_62.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -1484060925;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_63){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_63.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = 481552084;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_64){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_64.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -1378300978;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_65){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_65.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = 592853531;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_66){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_66.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -1225914412;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_67){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_67.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -1062566157;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_68){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_68.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = 108953596;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_69){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_69.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -645048806;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_70){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_70.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -337197123;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_71){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_71.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -1663685706;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_72){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_72.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -692775797;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_73){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_73.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -1349647533;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_74){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_74.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = 1856664082;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_75){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_75.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -1384035072;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_76){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_76.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -199528877;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_77){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_77.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -80300084;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_78){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_78.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = 1934217861;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_79){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_79.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = 763216971;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_80){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_80.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -1722348596;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_81){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_81.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = 2059749041;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_82){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_82.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = 64065760;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_83){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_83.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -1449420308;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_84){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_84.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -60270695;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_85){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_85.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -30590354;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_86){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_86.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = 648556139;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_87){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_87.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -1426601811;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_88){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_88.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -306582908;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_89){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_89.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = 2137902838;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_90){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_90.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -606705010;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_91){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_91.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = 924967366;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_92){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_92.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -2107786181;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_93){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_93.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = 750002052;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_94){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_94.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = 2072729284;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_95){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_95.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = 628935857;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_96){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_96.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = 420986442;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_97){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_97.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -244847550;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_98){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_98.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = 2111755603;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_i32_32Test, fcnvt_i32_32_99){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i32_32_99.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int val = -1236437051;
    float fval = float(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
