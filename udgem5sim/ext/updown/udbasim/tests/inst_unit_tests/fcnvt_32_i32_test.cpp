#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"
#include <cmath>
#include <cfenv>

using namespace basim;

class Fcnvt_32_i32Test : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    int num_lanes = 64;
    UDAccelerator acc0 = UDAccelerator(num_lanes, 0, 0);
    int buffsize1 = 1024;
    int buffsize2 = 1024;
};
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_0){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_0.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3121931285u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_1){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_1.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2592699416u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_2){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_2.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1375417550u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_3){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_3.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1912837133u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_4){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_4.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3408060804u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_5){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_5.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2056693654u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_6){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_6.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3098797673u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_7){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_7.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2123628083u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_8){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_8.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3870491327u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_9){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_9.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2085665934u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_10){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_10.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3544099537u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_11){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_11.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3516226416u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_12){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_12.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3029900692u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_13){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_13.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 623691728u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_14){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_14.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2425590473u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_15){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_15.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1211212330u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_16){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_16.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 412995392u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_17){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_17.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 491321723u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_18){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_18.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1103225997u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_19){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_19.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1675099400u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_20){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_20.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 4131154655u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_21){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_21.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3947501152u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_22){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_22.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1331297111u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_23){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_23.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2627342546u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_24){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_24.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3919082377u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_25){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_25.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3281202386u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_26){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_26.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3102165798u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_27){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_27.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3965728438u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_28){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_28.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 107618887u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_29){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_29.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3073661291u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_30){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_30.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1146336233u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_31){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_31.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3884105494u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_32){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_32.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3042786238u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_33){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_33.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2275617753u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_34){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_34.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 312402328u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_35){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_35.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1539577345u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_36){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_36.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1809172507u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_37){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_37.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 4007586663u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_38){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_38.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 806963492u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_39){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_39.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2033889105u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_40){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_40.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 4281308595u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_41){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_41.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3237158355u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_42){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_42.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1087759332u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_43){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_43.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 710315016u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_44){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_44.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1528589415u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_45){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_45.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 426024933u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_46){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_46.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2478130701u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_47){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_47.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2255165394u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_48){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_48.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1997013841u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_49){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_49.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3395977106u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_50){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_50.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2691146893u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_51){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_51.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2532729082u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_52){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_52.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3830571207u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_53){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_53.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 4275341375u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_54){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_54.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1294027475u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_55){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_55.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 810024338u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_56){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_56.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3916732140u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_57){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_57.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3967131343u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_58){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_58.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3847816463u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_59){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_59.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1927273056u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_60){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_60.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3633279057u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_61){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_61.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3490075693u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_62){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_62.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2516043394u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_63){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_63.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1294736871u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_64){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_64.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1345100749u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_65){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_65.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3558581765u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_66){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_66.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1484447949u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_67){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_67.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3948336624u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_68){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_68.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3759950562u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_69){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_69.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2290191041u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_70){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_70.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1553071090u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_71){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_71.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3908039079u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_72){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_72.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 4098382706u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_73){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_73.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2387375652u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_74){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_74.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3119952826u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_75){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_75.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1806893927u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_76){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_76.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3996364201u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_77){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_77.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1079510174u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_78){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_78.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 275581112u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_79){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_79.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 877730557u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_80){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_80.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 42080625u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_81){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_81.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2973918640u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_82){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_82.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1869820636u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_83){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_83.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1036892171u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_84){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_84.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 262566281u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_85){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_85.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1864847765u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_86){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_86.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2293779778u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_87){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_87.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 4129053891u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_88){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_88.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2811095138u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_89){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_89.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1260534298u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_90){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_90.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 61908346u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_91){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_91.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2691039144u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_92){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_92.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 768575407u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_93){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_93.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1826310313u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_94){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_94.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2290584004u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_95){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_95.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 1075128424u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_96){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_96.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2087363904u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_97){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_97.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 2789957740u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_98){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_98.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3648997084u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_32_i32Test, fcnvt_32_i32_99){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_32_i32_99.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint32_t raw_val = 3462659836u;
    float val = *reinterpret_cast<float*>(&raw_val);
    int int_val = int(val);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&int_val);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
