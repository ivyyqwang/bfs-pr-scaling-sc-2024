#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"

using namespace basim;

class SLANDII : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    UDLane lane0 = UDLane(0);
};
TEST_F(SLANDII, random_0){
    lane0.initSetup(0,"testprogs/binaries/slandii_0.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    lane0.pushEventOperands(eops);
    while(!lane0.isIdle())
        lane0.tick();
    EXPECT_TRUE(lane0.testReg(RegId::X16, 13698351882150987610u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 0u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 13698351882150987610u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 0u));
}
TEST_F(SLANDII, random_1){
    lane0.initSetup(0,"testprogs/binaries/slandii_1.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    lane0.pushEventOperands(eops);
    while(!lane0.isIdle())
        lane0.tick();
    EXPECT_TRUE(lane0.testReg(RegId::X16, 2619368900839771139u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 0u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 2619368900839771139u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 0u));
}
TEST_F(SLANDII, random_2){
    lane0.initSetup(0,"testprogs/binaries/slandii_2.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    lane0.pushEventOperands(eops);
    while(!lane0.isIdle())
        lane0.tick();
    EXPECT_TRUE(lane0.testReg(RegId::X16, 12427183496670466823u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 0u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 12427183496670466823u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 0u));
}
TEST_F(SLANDII, random_3){
    lane0.initSetup(0,"testprogs/binaries/slandii_3.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    lane0.pushEventOperands(eops);
    while(!lane0.isIdle())
        lane0.tick();
    EXPECT_TRUE(lane0.testReg(RegId::X16, 1462602305453350749u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 0u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 1462602305453350749u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 0u));
}
TEST_F(SLANDII, random_4){
    lane0.initSetup(0,"testprogs/binaries/slandii_4.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    lane0.pushEventOperands(eops);
    while(!lane0.isIdle())
        lane0.tick();
    EXPECT_TRUE(lane0.testReg(RegId::X16, 10255889722207030101u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 2048u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 10255889722207030101u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 2048u));
}
