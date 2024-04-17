#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"
#include <cmath>
#include <cfenv>

using namespace basim;

class Fcnvt_64_32Test : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    int num_lanes = 64;
    UDAccelerator acc0 = UDAccelerator(num_lanes, 0, 0);
    int buffsize1 = 1024;
    int buffsize2 = 1024;
};
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_0){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_0.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 2875592872181427260u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_1){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_1.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 13137492842712494227u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_2){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_2.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 7681377799220898648u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_3){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_3.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 7601854603420760033u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_4){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_4.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 16009488119314069056u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_5){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_5.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 8512797565198558986u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_6){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_6.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 6801357722399711098u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_7){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_7.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 18076461180295443214u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_8){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_8.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 3733663658477051310u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_9){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_9.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 10463074948022664246u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_10){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_10.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 12404699133082178294u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_11){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_11.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 625816556336718357u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_12){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_12.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 7451933947937470263u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_13){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_13.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 8664987581952358834u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_14){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_14.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 3822923288645695324u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_15){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_15.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 14055389855385386900u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_16){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_16.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 423355306737253069u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_17){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_17.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 4178832161624159368u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_18){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_18.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 9421132023838148156u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_19){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_19.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 15160089398029464473u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_20){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_20.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 4366345380751084293u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_21){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_21.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 18246656013652984079u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_22){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_22.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 8252980840982805389u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_23){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_23.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 16573028739290432762u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_24){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_24.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 2380377043316097271u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_25){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_25.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 11914794479923178401u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_26){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_26.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 10922347481672452360u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_27){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_27.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 11727500473395090336u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_28){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_28.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 2142146537712166116u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_29){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_29.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 8406885336480675600u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_30){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_30.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 4317698799399450452u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_31){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_31.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 4378212431165869236u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_32){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_32.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 4434434375372693474u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_33){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_33.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 17462595548390431328u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_34){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_34.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 16933947264547307054u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_35){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_35.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 2483868941655368010u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_36){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_36.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 14001672957377163958u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_37){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_37.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 8871130837432991676u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_38){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_38.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 17299631504508429863u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_39){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_39.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 8010623692648122811u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_40){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_40.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 5672362067470124570u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_41){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_41.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 15448252883334138002u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_42){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_42.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 7582555507114490826u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_43){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_43.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 2487899904376709871u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_44){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_44.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 13761246749872869142u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_45){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_45.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 931618956145094231u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_46){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_46.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 11983280427193303447u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_47){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_47.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 11349918638017154081u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_48){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_48.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 1894013759137535608u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_49){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_49.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 15941332195633802070u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_50){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_50.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 450117777163293881u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_51){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_51.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 11765732263566148509u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_52){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_52.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 16061590298108186225u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_53){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_53.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 1767940607085483471u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_54){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_54.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 12224288441756103764u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_55){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_55.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 17036165126522175901u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_56){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_56.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 18311609334471678093u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_57){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_57.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 9459841995268301171u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_58){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_58.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 6692612822273688573u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_59){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_59.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 15088804299345765834u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_60){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_60.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 7287220546410576745u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_61){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_61.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 17015789650631235244u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_62){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_62.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 7823883444947413868u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_63){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_63.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 17682275161028079010u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_64){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_64.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 10529593116700226567u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_65){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_65.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 14775385039342298800u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_66){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_66.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 1176969833309765802u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_67){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_67.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 13669109825846355733u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_68){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_68.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 18162259180138671911u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_69){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_69.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 17676132339534384900u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_70){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_70.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 15986700946774955862u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_71){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_71.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 12006985941971265827u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_72){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_72.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 2799388354579462896u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_73){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_73.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 15136491227645125134u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_74){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_74.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 1715046753514955972u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_75){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_75.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 8577590354983532579u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_76){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_76.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 15100180844894884129u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_77){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_77.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 6948446562723447618u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_78){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_78.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 4803735279421050815u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_79){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_79.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 10536920294401658462u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_80){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_80.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 1026232410419443742u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_81){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_81.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 13789909479000682743u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_82){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_82.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 89822103833934659u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_83){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_83.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 6476951250445570478u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_84){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_84.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 4892458070223683498u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_85){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_85.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 8639420383335081362u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_86){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_86.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 6854080863585673925u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_87){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_87.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 11705650583748309939u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_88){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_88.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 3096103760051841489u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_89){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_89.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 6610063996926600346u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_90){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_90.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 1653797395201053878u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_91){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_91.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 4512309303430334729u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_92){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_92.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 13912933206329021420u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_93){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_93.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 2486977998653098919u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_94){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_94.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 3952303006603632865u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_95){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_95.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 11973296539710011211u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_96){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_96.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 3542603681030742163u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_97){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_97.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 6771541802628639123u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_98){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_98.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 15877879499055470884u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_32Test, fcnvt_64_32_99){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_32_99.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 18044199216648714378u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
