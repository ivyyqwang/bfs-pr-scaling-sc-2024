#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"

using namespace basim;

class SRANDII : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    UDLane lane0 = UDLane(0);
};
TEST_F(SRANDII, random_0){
    lane0.initSetup(0,"testprogs/binaries/srandii_0.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 11803646597787127076u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 4u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 11803646597787127076u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 4u));
}
TEST_F(SRANDII, random_1){
    lane0.initSetup(0,"testprogs/binaries/srandii_1.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 14163109579997640698u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 783u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 14163109579997640698u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 783u));
}
TEST_F(SRANDII, random_2){
    lane0.initSetup(0,"testprogs/binaries/srandii_2.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 12907946568400414762u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 129u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 12907946568400414762u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 129u));
}
TEST_F(SRANDII, random_3){
    lane0.initSetup(0,"testprogs/binaries/srandii_3.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 1023334490578257138u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 328u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 1023334490578257138u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 328u));
}
TEST_F(SRANDII, random_4){
    lane0.initSetup(0,"testprogs/binaries/srandii_4.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 6010312447629565211u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 2060u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 6010312447629565211u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 2060u));
}
