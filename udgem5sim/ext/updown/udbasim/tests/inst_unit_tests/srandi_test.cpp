#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"

using namespace basim;

class SRANDI : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    UDLane lane0 = UDLane(0);
};
TEST_F(SRANDI, random_0){
    lane0.initSetup(0,"testprogs/binaries/srandi_0.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 11248790743895645983u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 0u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 11248790743895645983u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 0u));
}
TEST_F(SRANDI, random_1){
    lane0.initSetup(0,"testprogs/binaries/srandi_1.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 11891841506564989037u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 5503977888u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 11891841506564989037u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 5503977888u));
}
TEST_F(SRANDI, random_2){
    lane0.initSetup(0,"testprogs/binaries/srandi_2.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 2066441794518856457u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 8969052810u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 2066441794518856457u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 8969052810u));
}
TEST_F(SRANDI, random_3){
    lane0.initSetup(0,"testprogs/binaries/srandi_3.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 740173745808999116u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 64u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 740173745808999116u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 64u));
}
TEST_F(SRANDI, random_4){
    lane0.initSetup(0,"testprogs/binaries/srandi_4.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 335946893894876776u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 18u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 335946893894876776u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 18u));
}
