#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"

using namespace basim;

class SLANDI : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    UDLane lane0 = UDLane(0);
};
TEST_F(SLANDI, random_0){
    lane0.initSetup(0,"testprogs/binaries/slandi_0.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 10337829369317813944u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 2921182497121522944u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 10337829369317813944u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 2921182497121522944u));
}
TEST_F(SLANDI, random_1){
    lane0.initSetup(0,"testprogs/binaries/slandi_1.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 15542710167867897369u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 2378046857625468928u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 15542710167867897369u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 2378046857625468928u));
}
TEST_F(SLANDI, random_2){
    lane0.initSetup(0,"testprogs/binaries/slandi_2.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 7641208267798506416u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 76561605982158848u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 7641208267798506416u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 76561605982158848u));
}
TEST_F(SLANDI, random_3){
    lane0.initSetup(0,"testprogs/binaries/slandi_3.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 2706935315392948500u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 3170957030215452704u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 2706935315392948500u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 3170957030215452704u));
}
TEST_F(SLANDI, random_4){
    lane0.initSetup(0,"testprogs/binaries/slandi_4.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 831403749217721834u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 9540334850863529984u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 831403749217721834u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 9540334850863529984u));
}
