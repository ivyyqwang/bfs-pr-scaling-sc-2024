#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"

using namespace basim;

class XOR : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    UDLane lane0 = UDLane(0);
};
TEST_F(XOR, random_0){
    lane0.initSetup(0,"testprogs/binaries/xor_0.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 7960813246030054442u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 6605000113792324786u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 3878674480219361432u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 7960813246030054442u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 6605000113792324786u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 3878674480219361432u));
}
TEST_F(XOR, random_1){
    lane0.initSetup(0,"testprogs/binaries/xor_1.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 16244656677493483254u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 5744346715655661675u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 12594485446601035421u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 16244656677493483254u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 5744346715655661675u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 12594485446601035421u));
}
TEST_F(XOR, random_2){
    lane0.initSetup(0,"testprogs/binaries/xor_2.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 17249315576461645002u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 2656121531993624236u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 14681050157427251814u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 17249315576461645002u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 2656121531993624236u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 14681050157427251814u));
}
TEST_F(XOR, random_3){
    lane0.initSetup(0,"testprogs/binaries/xor_3.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 15011032708646674272u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 6971471540124539543u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 12749201101626656247u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 15011032708646674272u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 6971471540124539543u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 12749201101626656247u));
}
TEST_F(XOR, random_4){
    lane0.initSetup(0,"testprogs/binaries/xor_4.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 10425744358250593377u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 14165573996342805169u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 6069046069785345744u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 10425744358250593377u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 14165573996342805169u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 6069046069785345744u));
}
