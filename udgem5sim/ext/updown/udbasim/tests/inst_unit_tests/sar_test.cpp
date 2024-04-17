#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"

using namespace basim;

class SAR : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    UDLane lane0 = UDLane(0);
};
TEST_F(SAR, random_0){
    lane0.initSetup(0,"testprogs/binaries/sar_0.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 2666860071871324056u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 8019950626692966619u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 0u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 2666860071871324056u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 8019950626692966619u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 0u));
}
TEST_F(SAR, random_1){
    lane0.initSetup(0,"testprogs/binaries/sar_1.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 5273719840194038274u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 742209686144806934u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 0u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 5273719840194038274u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 742209686144806934u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 0u));
}
TEST_F(SAR, random_2){
    lane0.initSetup(0,"testprogs/binaries/sar_2.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 16113102246164344299u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 14356809474265233753u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 18446744073709551615u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 16113102246164344299u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 14356809474265233753u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 18446744073709551615u));
}
TEST_F(SAR, random_3){
    lane0.initSetup(0,"testprogs/binaries/sar_3.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 11424867832675975414u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 6545593352604456413u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 18446744073709551615u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 11424867832675975414u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 6545593352604456413u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 18446744073709551615u));
}
TEST_F(SAR, random_4){
    lane0.initSetup(0,"testprogs/binaries/sar_4.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 4570178460191313051u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 2633331866432670588u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 0u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 4570178460191313051u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 2633331866432670588u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 0u));
}
