#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"
#include <cmath>
#include <cfenv>

using namespace basim;

class Fcnvt_i64_64Test : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    int num_lanes = 64;
    UDAccelerator acc0 = UDAccelerator(num_lanes, 0, 0);
    int buffsize1 = 1024;
    int buffsize2 = 1024;
};
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_0){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_0.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -2264520655742088386;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_1){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_1.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = 2603096526409027721;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_2){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_2.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -2769025666064056485;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_3){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_3.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -1313838486507012685;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_4){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_4.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = 7687958811687883619;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_5){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_5.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -5399381412851553518;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_6){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_6.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -7790725558643047847;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_7){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_7.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -1007691038091957252;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_8){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_8.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = 7433077871198848409;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_9){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_9.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = 2364611560014322143;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_10){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_10.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -3671782953439171314;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_11){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_11.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -1873412720963613033;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_12){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_12.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = 4572280041979412797;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_13){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_13.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = 7309697498431544131;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_14){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_14.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = 7802258520740346546;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_15){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_15.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = 8209087015173160038;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_16){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_16.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = 6004132311483588028;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_17){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_17.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = 7603923690248553892;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_18){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_18.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -1139916262383672096;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_19){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_19.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = 4421601221619277230;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_20){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_20.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -1581427708548381356;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_21){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_21.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = 4816234020511844235;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_22){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_22.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = 7143733906392903618;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_23){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_23.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -5088116711614695944;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_24){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_24.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = 5704273880379694492;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_25){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_25.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = 6332458463680258971;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_26){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_26.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -3149682738397711214;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_27){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_27.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = 8037888238188316099;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_28){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_28.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -5309893816559659591;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_29){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_29.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -6388089965430642287;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_30){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_30.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -5645766408905020989;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_31){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_31.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -5572030901217495001;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_32){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_32.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -983206079485275484;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_33){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_33.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = 8951975353244705638;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_34){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_34.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = 8682847099051921844;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_35){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_35.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -5404644148731026591;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_36){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_36.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -3803587785911067777;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_37){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_37.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -5564872471455659624;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_38){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_38.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = 3270589966496835525;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_39){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_39.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = 1890019927656577260;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_40){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_40.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = 8413420670464995179;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_41){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_41.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -8667071570711958225;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_42){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_42.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -6876825528593729969;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_43){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_43.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = 4246253161258176985;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_44){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_44.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = 7736646317750177613;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_45){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_45.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = 3766410207652529553;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_46){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_46.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -7377159278505201539;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_47){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_47.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -6784473769870224228;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_48){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_48.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -1323307490033802814;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_49){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_49.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = 7550479170547386258;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_50){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_50.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = 2191878277690946947;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_51){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_51.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = 2156680069624334318;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_52){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_52.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -8207037082675100754;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_53){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_53.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -5940062924891107400;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_54){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_54.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -4855956353656718627;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_55){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_55.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -8310397683562117030;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_56){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_56.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = 6230416364679859272;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_57){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_57.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -7406234824815270000;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_58){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_58.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -7466272922464659799;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_59){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_59.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = 6545941303084715399;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_60){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_60.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -3552293611044969741;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_61){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_61.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -1099799268016213765;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_62){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_62.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = 7856702033862220620;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_63){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_63.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = 1544872585634728390;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_64){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_64.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -904621180041636359;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_65){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_65.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -1933578150538852236;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_66){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_66.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -4231382534994726985;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_67){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_67.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -5049443023780736049;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_68){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_68.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = 2749793275710056433;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_69){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_69.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -4173026737191957087;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_70){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_70.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = 457471677040839303;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_71){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_71.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = 5122948279932545357;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_72){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_72.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -7886228056774951454;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_73){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_73.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = 5993326530352228377;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_74){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_74.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -7090195272055632915;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_75){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_75.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -5471591684049908038;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_76){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_76.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -2578274206562993881;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_77){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_77.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = 732743145134104695;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_78){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_78.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -3759087501020217945;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_79){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_79.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = 2133836350455271141;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_80){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_80.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -376491305650402512;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_81){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_81.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = 5904136568484357515;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_82){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_82.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -3608103690368316113;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_83){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_83.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = 8419672966793539767;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_84){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_84.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -1797232129718543807;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_85){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_85.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = 8021273197784643111;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_86){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_86.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -2424940761673094641;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_87){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_87.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -3468804677237840946;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_88){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_88.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -1701742335873905180;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_89){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_89.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = 8199974603598529213;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_90){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_90.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = 4791495943691717921;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_91){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_91.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = 2960895610245317364;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_92){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_92.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -4584015594125990051;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_93){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_93.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = 4490341085037257859;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_94){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_94.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -354220047894575592;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_95){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_95.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -4154465495095007808;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_96){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_96.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -8243819494692411998;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_97){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_97.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -1760977167384896489;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_98){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_98.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -6820940487950524245;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
TEST_F(Fcnvt_i64_64Test, fcnvt_i64_64_99){
    acc0.initSetup(0,"testprogs/binaries/fcnvt_i64_64_99.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int64_t val = -6323317079536847106;
    double dval = double(val);
    word_t* uint_val = reinterpret_cast<word_t*>(&dval);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, *uint_val));
}
