#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"

using namespace basim;

class XORI : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    UDLane lane0 = UDLane(0);
};
TEST_F(XORI, random_0){
    lane0.initSetup(0,"testprogs/binaries/xori_0.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 504624969974261883u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 504624969974248896u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 504624969974261883u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 504624969974248896u));
}
TEST_F(XORI, random_1){
    lane0.initSetup(0,"testprogs/binaries/xori_1.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 11535159543400746635u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 11535159543400724899u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 11535159543400746635u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 11535159543400724899u));
}
TEST_F(XORI, random_2){
    lane0.initSetup(0,"testprogs/binaries/xori_2.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 4056969130668640288u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 4056969130668612141u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 4056969130668640288u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 4056969130668612141u));
}
TEST_F(XORI, random_3){
    lane0.initSetup(0,"testprogs/binaries/xori_3.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 3644828858308634512u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 3644828858308658290u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 3644828858308634512u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 3644828858308658290u));
}
TEST_F(XORI, random_4){
    lane0.initSetup(0,"testprogs/binaries/xori_4.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 13666893809692335231u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 13666893809692341548u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 13666893809692335231u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 13666893809692341548u));
}
