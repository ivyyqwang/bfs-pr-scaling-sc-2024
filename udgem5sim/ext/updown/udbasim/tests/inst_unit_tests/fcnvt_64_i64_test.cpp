#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"
#include <cmath>
#include <cfenv>

using namespace basim;

class Fcnvt_64_i64Test : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    int num_lanes = 64;
    UDAccelerator acc0 = UDAccelerator(num_lanes, 0, 0);
    int buffsize1 = 1024;
    int buffsize2 = 1024;
};
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_0){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_0.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 7695841509132530330u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_1){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_1.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 2358703235183911119u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_2){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_2.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 2926509926436862134u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_3){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_3.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 6594525596001730076u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_4){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_4.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 18441470306663256122u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_5){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_5.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 14275933911693766771u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_6){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_6.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 15597768238615896086u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_7){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_7.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 9919430519848008663u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_8){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_8.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 15796999247748337097u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_9){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_9.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 13058678144643358831u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_10){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_10.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 16171451581184476377u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_11){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_11.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 13853959552802589237u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_12){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_12.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 8560125272641783388u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_13){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_13.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 6482352586510210655u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_14){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_14.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 7500754220102625419u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_15){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_15.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 3150325497301141292u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_16){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_16.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 1267780118240448806u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_17){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_17.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 1461289310308997878u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_18){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_18.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 526070599109917430u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_19){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_19.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 13971256044037968874u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_20){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_20.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 771311274748114824u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_21){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_21.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 17669653048020173671u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_22){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_22.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 15523858951431873137u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_23){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_23.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 3301938653151178528u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_24){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_24.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 10002146253624626141u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_25){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_25.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 2615549805666922951u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_26){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_26.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 1155792542154949847u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_27){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_27.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 3460518274132325604u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_28){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_28.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 10000289470299053395u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_29){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_29.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 11580138020603244982u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_30){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_30.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 17386812116990020936u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_31){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_31.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 4962548130872747690u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_32){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_32.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 2899819970675557348u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_33){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_33.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 126258888512040049u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_34){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_34.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 6143866240252043119u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_35){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_35.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 6800982237524684824u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_36){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_36.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 14564911295762631406u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_37){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_37.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 15967454401650595880u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_38){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_38.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 7118602351545773933u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_39){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_39.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 11974671496587220246u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_40){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_40.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 10717488363591881975u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_41){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_41.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 9684576113249882000u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_42){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_42.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 6974533617629512833u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_43){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_43.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 7247456774608369173u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_44){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_44.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 3938119180014317074u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_45){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_45.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 17913134886783260519u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_46){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_46.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 12770558307999838384u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_47){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_47.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 13269019423569007863u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_48){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_48.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 1639961244671575456u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_49){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_49.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 17062474268513172648u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_50){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_50.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 12271923319488241675u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_51){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_51.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 5971824293082506394u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_52){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_52.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 14126215200992768521u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_53){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_53.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 2959339246902612888u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_54){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_54.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 2667094589900962444u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_55){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_55.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 2610303303927691362u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_56){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_56.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 1639891152204089418u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_57){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_57.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 15207431851209930736u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_58){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_58.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 12307901368468070183u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_59){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_59.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 570811870148690827u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_60){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_60.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 2767496354056752388u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_61){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_61.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 13457393179590595361u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_62){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_62.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 11126560786491433351u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_63){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_63.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 11457908760826918172u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_64){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_64.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 9076239325798076230u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_65){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_65.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 377616735999148110u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_66){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_66.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 5864858697413535266u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_67){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_67.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 11817749402493694187u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_68){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_68.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 8897034490071289034u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_69){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_69.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 5247477104350080383u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_70){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_70.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 9091242157125609759u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_71){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_71.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 13488381492124481563u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_72){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_72.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 10728907210919654431u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_73){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_73.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 17040938390739478546u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_74){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_74.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 4780844248918245795u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_75){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_75.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 10203070181988529587u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_76){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_76.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 6796101040055801841u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_77){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_77.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 7617682323749353693u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_78){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_78.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 8902304238207045029u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_79){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_79.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 12781811176050565510u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_80){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_80.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 12992116505581191917u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_81){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_81.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 7469154757196257854u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_82){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_82.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 4693031407163944152u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_83){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_83.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 11639480879620912938u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_84){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_84.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 8960066691291024180u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_85){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_85.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 3708929602198353875u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_86){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_86.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 469388360169898618u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_87){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_87.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 3215146763922719328u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_88){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_88.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 6308052598756084140u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_89){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_89.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 5145106861179756852u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_90){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_90.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 12814782445451971791u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_91){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_91.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 5632686080085935403u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_92){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_92.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 2720217231248564211u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_93){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_93.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 13363755570449310394u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_94){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_94.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 11322864796999011150u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_95){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_95.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 17253644510281211609u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_96){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_96.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 16835527116951272384u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_97){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_97.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 15796699624213358997u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_98){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_98.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 9818309275602655968u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_64_i64Test, fcnvt_64_i64_99){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_64_i64_99.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    uint64_t raw_val = 11576467486559336882u;
    double val = *reinterpret_cast<double*>(&raw_val);
    int64_t int_val = int64_t(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&int_val);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
