#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"

using namespace basim;

class SRORI : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    UDLane lane0 = UDLane(0);
};
TEST_F(SRORI, random_0){
    lane0.initSetup(0,"testprogs/binaries/srori_0.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 412849748257284146u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 16058560835563093358u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 412849748257284146u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 16058560835563093358u));
}
TEST_F(SRORI, random_1){
    lane0.initSetup(0,"testprogs/binaries/srori_1.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 12020052372740127673u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 13194832771094149119u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 12020052372740127673u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 13194832771094149119u));
}
TEST_F(SRORI, random_2){
    lane0.initSetup(0,"testprogs/binaries/srori_2.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 6860034407051748633u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 14812891922745491429u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 6860034407051748633u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 14812891922745491429u));
}
TEST_F(SRORI, random_3){
    lane0.initSetup(0,"testprogs/binaries/srori_3.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 11882331142498609630u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 8269593388909040103u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 11882331142498609630u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 8269593388909040103u));
}
TEST_F(SRORI, random_4){
    lane0.initSetup(0,"testprogs/binaries/srori_4.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 1792627566180415947u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 12479802046479761286u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 1792627566180415947u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 12479802046479761286u));
}
