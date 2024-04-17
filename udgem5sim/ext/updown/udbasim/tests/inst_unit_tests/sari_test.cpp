#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"

using namespace basim;

class SARI : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    UDLane lane0 = UDLane(0);
};
TEST_F(SARI, random_0){
    lane0.initSetup(0,"testprogs/binaries/sari_0.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 13545515597342897260u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 18446744073709549439u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 13545515597342897260u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 18446744073709549439u));
}
TEST_F(SARI, random_1){
    lane0.initSetup(0,"testprogs/binaries/sari_1.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 1840131576085954710u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 13710048616u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 1840131576085954710u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 13710048616u));
}
TEST_F(SARI, random_2){
    lane0.initSetup(0,"testprogs/binaries/sari_2.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 13656055391234194249u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 18444404870251311695u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 13656055391234194249u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 18444404870251311695u));
}
TEST_F(SARI, random_3){
    lane0.initSetup(0,"testprogs/binaries/sari_3.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 7137207699940498852u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 50712u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 7137207699940498852u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 50712u));
}
TEST_F(SARI, random_4){
    lane0.initSetup(0,"testprogs/binaries/sari_4.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 8588426550612249431u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 122048u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 8588426550612249431u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 122048u));
}
