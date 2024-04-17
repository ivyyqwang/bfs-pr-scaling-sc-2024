#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"

using namespace basim;

class ANDI : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    UDLane lane0 = UDLane(0);
};
TEST_F(ANDI, random_0){
    lane0.initSetup(0,"testprogs/binaries/andi_0.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 6566582315636748965u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 62080u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 6566582315636748965u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 62080u));
}
TEST_F(ANDI, random_1){
    lane0.initSetup(0,"testprogs/binaries/andi_1.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 136868195275244397u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 873u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 136868195275244397u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 873u));
}
TEST_F(ANDI, random_2){
    lane0.initSetup(0,"testprogs/binaries/andi_2.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 17466389657205783338u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 37128u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 17466389657205783338u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 37128u));
}
TEST_F(ANDI, random_3){
    lane0.initSetup(0,"testprogs/binaries/andi_3.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 18277625206866699525u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 40960u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 18277625206866699525u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 40960u));
}
TEST_F(ANDI, random_4){
    lane0.initSetup(0,"testprogs/binaries/andi_4.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 17811611212268228278u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 1042u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 17811611212268228278u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 1042u));
}
