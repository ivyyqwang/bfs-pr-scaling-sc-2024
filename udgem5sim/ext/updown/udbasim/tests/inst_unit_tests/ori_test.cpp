#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"

using namespace basim;

class ORI : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    UDLane lane0 = UDLane(0);
};
TEST_F(ORI, random_0){
    lane0.initSetup(0,"testprogs/binaries/ori_0.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 9714825768684572330u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 9714825768684576427u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 9714825768684572330u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 9714825768684576427u));
}
TEST_F(ORI, random_1){
    lane0.initSetup(0,"testprogs/binaries/ori_1.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 13280200542397101191u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 13280200542397134215u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 13280200542397101191u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 13280200542397134215u));
}
TEST_F(ORI, random_2){
    lane0.initSetup(0,"testprogs/binaries/ori_2.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 18282683452307668664u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 18282683452307668985u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 18282683452307668664u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 18282683452307668985u));
}
TEST_F(ORI, random_3){
    lane0.initSetup(0,"testprogs/binaries/ori_3.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 877414622679215038u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 877414622679215038u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 877414622679215038u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 877414622679215038u));
}
TEST_F(ORI, random_4){
    lane0.initSetup(0,"testprogs/binaries/ori_4.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 8606832497264821422u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 8606832497264823998u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 8606832497264821422u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 8606832497264823998u));
}
