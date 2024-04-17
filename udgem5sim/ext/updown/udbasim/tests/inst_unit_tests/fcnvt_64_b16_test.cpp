#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"
#include <cmath>
#include <cfenv>

using namespace basim;

class Fcnvt_64_b16Test : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    int num_lanes = 64;
    UDAccelerator acc0 = UDAccelerator(num_lanes, 0, 0);
    int buffsize1 = 1024;
    int buffsize2 = 1024;
};
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_0){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_0.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 6459073917936703643u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_1){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_1.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 57641726445673572u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_2){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_2.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 5707792027727807148u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_3){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_3.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 876121865711293580u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_4){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_4.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 15400294015368873078u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_5){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_5.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 17303747303788326767u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_6){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_6.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 6193070926907860510u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_7){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_7.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 9422224182559619947u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_8){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_8.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 12912805927518239242u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_9){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_9.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 5537833817055780340u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_10){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_10.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 5536056971140529463u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_11){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_11.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 5362468722736928106u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_12){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_12.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 2709004484711229202u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_13){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_13.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 8800755771110537435u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_14){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_14.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 3131174553248732065u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_15){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_15.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 3382246462766516495u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_16){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_16.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 5851939533014256238u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_17){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_17.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 3859400782112367010u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_18){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_18.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 3635105027376961757u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_19){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_19.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 14548495701429808572u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_20){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_20.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 15609726778458166171u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_21){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_21.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 7672541390291491710u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_22){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_22.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 17362486384710241070u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_23){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_23.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 11541785989111281102u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_24){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_24.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 8023079783316715399u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_25){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_25.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 4659766078856963631u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_26){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_26.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 12186748007805690366u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_27){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_27.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 11884665892949098618u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_28){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_28.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 791536737402802560u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_29){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_29.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 13768250209567517445u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_30){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_30.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 908279842551707717u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_31){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_31.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 16865176890470265729u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_32){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_32.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 7195069426292650064u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_33){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_33.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 13930222269466324493u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_34){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_34.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 13283413464739451415u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_35){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_35.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 6190152985975604897u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_36){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_36.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 9084325051149473744u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_37){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_37.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 3962613399858671204u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_38){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_38.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 16704447993798441644u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_39){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_39.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 9988781297910016674u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_40){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_40.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 213094872819189812u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_41){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_41.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 1606838140645519508u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_42){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_42.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 4076398161356238693u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_43){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_43.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 14429036135264384592u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_44){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_44.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 9388812829569651341u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_45){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_45.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 4427674872118265101u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_46){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_46.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 10100606207350762912u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_47){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_47.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 2688241238094133786u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_48){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_48.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 4098456025080953681u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_49){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_49.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 449904511717881287u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_50){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_50.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 63203959257111054u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_51){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_51.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 3870995253829165071u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_52){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_52.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 5130584171248546263u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_53){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_53.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 18245831998905592475u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_54){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_54.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 12087068098817415675u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_55){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_55.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 165577386022431665u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_56){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_56.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 2466079803586524999u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_57){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_57.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 9688577732688527629u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_58){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_58.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 1227641465646746920u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_59){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_59.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 11668150391819591730u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_60){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_60.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 5181713078924115750u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_61){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_61.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 152739048932272764u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_62){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_62.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 16891065623596001717u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_63){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_63.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 18185515439806057189u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_64){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_64.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 9170266212164616461u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_65){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_65.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 4619401797161430537u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_66){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_66.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 7716937948767952360u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_67){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_67.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 13945136878757877148u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_68){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_68.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 13363136146920331425u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_69){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_69.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 10733568048059736818u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_70){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_70.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 17924913930613989174u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_71){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_71.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 13243643369034002444u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_72){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_72.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 1955846059073679123u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_73){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_73.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 9494878250671548967u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_74){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_74.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 8367947842594361212u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_75){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_75.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 3724401463346249110u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_76){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_76.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 3390320864624981623u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_77){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_77.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 5603912569701179717u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_78){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_78.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 7264358305016122166u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_79){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_79.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 8561511518795304900u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_80){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_80.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 67950079513308028u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_81){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_81.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 2615059298797629867u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_82){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_82.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 12737128220879058756u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_83){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_83.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 4797750712757726751u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_84){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_84.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 10491136239266963679u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_85){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_85.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 4663245855522854127u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_86){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_86.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 2919147412916676385u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_87){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_87.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 10626811252350444611u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_88){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_88.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 3727179187737938214u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_89){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_89.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 2999759256370054246u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_90){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_90.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 10068985406682389478u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_91){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_91.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 6772109147803000569u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_92){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_92.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 12570300483702903548u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_93){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_93.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 8836893778670707880u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_94){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_94.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 16725820811478778041u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_95){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_95.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 7891328254904048702u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_96){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_96.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 5608373023319522284u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_97){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_97.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 5189547652009063919u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_98){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_98.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 15474609115665089379u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
TEST_F(Fcnvt_64_b16Test, fcnvt_64_b16_99){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_b16_99.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 17475924911272117764u;
    double dval = *reinterpret_cast<double*>(&raw_val);
    float fval = float(dval);
    uint32_t uint32_val = *reinterpret_cast<uint32_t*>(&fval);
    word_t uint64_val = word_t(uint32_val>>16);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, uint64_val));
}
