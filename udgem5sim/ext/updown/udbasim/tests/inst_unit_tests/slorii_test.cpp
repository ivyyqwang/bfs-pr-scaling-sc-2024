#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"

using namespace basim;

class SLORII : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    UDLane lane0 = UDLane(0);
};
TEST_F(SLORII, random_0){
    lane0.initSetup(0,"testprogs/binaries/slorii_0.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 17568576922705816729u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 17568576922705817599u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 17568576922705816729u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 17568576922705817599u));
}
TEST_F(SLORII, random_1){
    lane0.initSetup(0,"testprogs/binaries/slorii_1.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 2740802105294797083u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 13918691074595301344u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 2740802105294797083u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 13918691074595301344u));
}
TEST_F(SLORII, random_2){
    lane0.initSetup(0,"testprogs/binaries/slorii_2.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 1575810909124454508u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 6303243636497819569u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 1575810909124454508u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 6303243636497819569u));
}
TEST_F(SLORII, random_3){
    lane0.initSetup(0,"testprogs/binaries/slorii_3.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 12046528962302613635u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 14661346565275659263u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 12046528962302613635u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 14661346565275659263u));
}
TEST_F(SLORII, random_4){
    lane0.initSetup(0,"testprogs/binaries/slorii_4.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 14082563823685123610u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 14082563823685124063u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 14082563823685123610u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 14082563823685124063u));
}
