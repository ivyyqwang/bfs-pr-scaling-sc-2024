#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"

using namespace basim;

class OR : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    UDLane lane0 = UDLane(0);
};
TEST_F(OR, random_0){
    lane0.initSetup(0,"testprogs/binaries/or_0.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 5460536881685268494u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 2564377616145358169u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 7770961015223590239u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 5460536881685268494u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 2564377616145358169u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 7770961015223590239u));
}
TEST_F(OR, random_1){
    lane0.initSetup(0,"testprogs/binaries/or_1.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 15528029365932655885u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 18007749931241669381u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 18446433392954803981u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 15528029365932655885u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 18007749931241669381u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 18446433392954803981u));
}
TEST_F(OR, random_2){
    lane0.initSetup(0,"testprogs/binaries/or_2.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 7485640573760943347u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 12053959125957320938u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 16711266081381528827u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 7485640573760943347u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 12053959125957320938u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 16711266081381528827u));
}
TEST_F(OR, random_3){
    lane0.initSetup(0,"testprogs/binaries/or_3.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 11855957925038644132u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 16606614888755608417u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 16644986377833806821u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 11855957925038644132u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 16606614888755608417u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 16644986377833806821u));
}
TEST_F(OR, random_4){
    lane0.initSetup(0,"testprogs/binaries/or_4.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 11118810246583600436u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 10294320865798261238u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 11447577731116486134u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 11118810246583600436u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 10294320865798261238u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 11447577731116486134u));
}
