#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"

using namespace basim;

class SL : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    UDLane lane0 = UDLane(0);
};
TEST_F(SL, random_0){
    lane0.initSetup(0,"testprogs/binaries/sl_0.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 8960694148824456848u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 15248274460901046183u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 0u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 8960694148824456848u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 15248274460901046183u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 0u));
}
TEST_F(SL, random_1){
    lane0.initSetup(0,"testprogs/binaries/sl_1.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 2079268653494314576u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 8319204184837603261u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 0u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 2079268653494314576u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 8319204184837603261u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 0u));
}
TEST_F(SL, random_2){
    lane0.initSetup(0,"testprogs/binaries/sl_2.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 14282799905038612604u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 1512869637390330767u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 0u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 14282799905038612604u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 1512869637390330767u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 0u));
}
TEST_F(SL, random_3){
    lane0.initSetup(0,"testprogs/binaries/sl_3.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 17664622552638875496u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 5737391845071017191u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 0u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 17664622552638875496u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 5737391845071017191u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 0u));
}
TEST_F(SL, random_4){
    lane0.initSetup(0,"testprogs/binaries/sl_4.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 12347818551597416680u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 14213971804683094985u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 0u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 12347818551597416680u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 14213971804683094985u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 0u));
}
