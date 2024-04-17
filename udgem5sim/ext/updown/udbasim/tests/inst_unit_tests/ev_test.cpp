#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"

using namespace basim;

class EV : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    UDLane lane0 = UDLane(0);
};
TEST_F(EV, random_0){
    lane0.initSetup(0,"testprogs/binaries/ev_0.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 1342524238596441384u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 1342524238596808483u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 501473588723457827u));
    EXPECT_TRUE(lane0.testReg(RegId::X19, 9244172812281535840u));
}
TEST_F(EV, random_1){
    lane0.initSetup(0,"testprogs/binaries/ev_1.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 3466566600066573089u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 3466566600066605438u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 13831131536748192126u));
    EXPECT_TRUE(lane0.testReg(RegId::X19, 16125157525551831914u));
}
TEST_F(EV, random_2){
    lane0.initSetup(0,"testprogs/binaries/ev_2.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 2824527321751560592u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 2824527320845590928u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 12891215167772930849u));
    EXPECT_TRUE(lane0.testReg(RegId::X19, 14594704972377488541u));
}
TEST_F(EV, random_3){
    lane0.initSetup(0,"testprogs/binaries/ev_3.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 13932081030596515192u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 10639136755873863032u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 3652645653641023106u));
    EXPECT_TRUE(lane0.testReg(RegId::X19, 12798736010582582884u));
}
TEST_F(EV, random_4){
    lane0.initSetup(0,"testprogs/binaries/ev_4.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 17405860900428059136u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 17405860901132702208u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 17500893801379558389u));
    EXPECT_TRUE(lane0.testReg(RegId::X19, 12686458774082118701u));
}
