#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"

using namespace basim;

class SRORII : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    UDLane lane0 = UDLane(0);
};
TEST_F(SRORII, random_0){
    lane0.initSetup(0,"testprogs/binaries/srorii_0.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 16202049590642493881u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 31644628106725247u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 16202049590642493881u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 31644628106725247u));
}
TEST_F(SRORII, random_1){
    lane0.initSetup(0,"testprogs/binaries/srorii_1.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 1162967362974879190u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 1162967362974879230u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 1162967362974879190u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 1162967362974879230u));
}
TEST_F(SRORII, random_2){
    lane0.initSetup(0,"testprogs/binaries/srorii_2.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 8286843936102411921u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 258963873003200508u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 8286843936102411921u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 258963873003200508u));
}
TEST_F(SRORII, random_3){
    lane0.initSetup(0,"testprogs/binaries/srorii_3.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 8836992827012353114u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 4418496413506176831u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 8836992827012353114u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 4418496413506176831u));
}
TEST_F(SRORII, random_4){
    lane0.initSetup(0,"testprogs/binaries/srorii_4.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 16792656105814118740u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 262385251653347149u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 16792656105814118740u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 262385251653347149u));
}
