#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"

using namespace basim;

class SLORI : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    UDLane lane0 = UDLane(0);
};
TEST_F(SLORI, random_0){
    lane0.initSetup(0,"testprogs/binaries/slori_0.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 12690886691170692210u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 18407275904486963762u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 12690886691170692210u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 18407275904486963762u));
}
TEST_F(SLORI, random_1){
    lane0.initSetup(0,"testprogs/binaries/slori_1.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 2796637160117046845u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 6701179217501327624u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 2796637160117046845u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 6701179217501327624u));
}
TEST_F(SLORI, random_2){
    lane0.initSetup(0,"testprogs/binaries/slori_2.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 11246828877523970848u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 13690304637023527137u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 11246828877523970848u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 13690304637023527137u));
}
TEST_F(SLORI, random_3){
    lane0.initSetup(0,"testprogs/binaries/slori_3.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 1102295582379858975u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 9107298723202789624u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 1102295582379858975u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 9107298723202789624u));
}
TEST_F(SLORI, random_4){
    lane0.initSetup(0,"testprogs/binaries/slori_4.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 3010606470370839335u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 17082070254408484700u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 3010606470370839335u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 17082070254408484700u));
}
