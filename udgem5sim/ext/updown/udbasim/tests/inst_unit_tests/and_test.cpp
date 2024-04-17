#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"

using namespace basim;

class AND : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    UDLane lane0 = UDLane(0);
};
TEST_F(AND, random_0){
    lane0.initSetup(0,"testprogs/binaries/and_0.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 9295943469273311711u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 11296097542337511813u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 9223864983171940741u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 9295943469273311711u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 11296097542337511813u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 9223864983171940741u));
}
TEST_F(AND, random_1){
    lane0.initSetup(0,"testprogs/binaries/and_1.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 9788762845276661429u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 11641702613061273288u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 9333889244113995392u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 9788762845276661429u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 11641702613061273288u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 9333889244113995392u));
}
TEST_F(AND, random_2){
    lane0.initSetup(0,"testprogs/binaries/and_2.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 13743141378679964166u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 12532318802069485635u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 12441528243620675586u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 13743141378679964166u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 12532318802069485635u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 12441528243620675586u));
}
TEST_F(AND, random_3){
    lane0.initSetup(0,"testprogs/binaries/and_3.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 15530897332347521840u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 12617724666180059610u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 9730027623760838928u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 15530897332347521840u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 12617724666180059610u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 9730027623760838928u));
}
TEST_F(AND, random_4){
    lane0.initSetup(0,"testprogs/binaries/and_4.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 9303133286433018341u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 17774932445680401916u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 9225938718224830948u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 9303133286433018341u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 17774932445680401916u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 9225938718224830948u));
}
