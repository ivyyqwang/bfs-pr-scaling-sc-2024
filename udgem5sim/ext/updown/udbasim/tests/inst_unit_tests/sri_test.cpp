#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"

using namespace basim;

class SRI : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    UDLane lane0 = UDLane(0);
};
TEST_F(SRI, random_0){
    lane0.initSetup(0,"testprogs/binaries/sri_0.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 8779774015232522107u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 33492179928712u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 8779774015232522107u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 33492179928712u));
}
TEST_F(SRI, random_1){
    lane0.initSetup(0,"testprogs/binaries/sri_1.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 12599014520782397149u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 179042u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 12599014520782397149u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 179042u));
}
TEST_F(SRI, random_2){
    lane0.initSetup(0,"testprogs/binaries/sri_2.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 5623378414309483376u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 20948717051u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 5623378414309483376u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 20948717051u));
}
TEST_F(SRI, random_3){
    lane0.initSetup(0,"testprogs/binaries/sri_3.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 16834016996167847632u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 30620898u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 16834016996167847632u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 30620898u));
}
TEST_F(SRI, random_4){
    lane0.initSetup(0,"testprogs/binaries/sri_4.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 11384847910537831693u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 21714874096942u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 11384847910537831693u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 21714874096942u));
}
