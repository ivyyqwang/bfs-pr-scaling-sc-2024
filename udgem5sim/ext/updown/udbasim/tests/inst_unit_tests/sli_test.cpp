#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"

using namespace basim;

class SLI : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    UDLane lane0 = UDLane(0);
};
TEST_F(SLI, random_0){
    lane0.initSetup(0,"testprogs/binaries/sli_0.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 9980656367752052027u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 4586740298616406016u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 9980656367752052027u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 4586740298616406016u));
}
TEST_F(SLI, random_1){
    lane0.initSetup(0,"testprogs/binaries/sli_1.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 16128221365611919208u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 0u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 16128221365611919208u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 0u));
}
TEST_F(SLI, random_2){
    lane0.initSetup(0,"testprogs/binaries/sli_2.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 14484212259543418879u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 6275906749509664768u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 14484212259543418879u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 6275906749509664768u));
}
TEST_F(SLI, random_3){
    lane0.initSetup(0,"testprogs/binaries/sli_3.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 12597317418350524001u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 6517824442305871872u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 12597317418350524001u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 6517824442305871872u));
}
TEST_F(SLI, random_4){
    lane0.initSetup(0,"testprogs/binaries/sli_4.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 14430052585066792536u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 12682136550675316736u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 14430052585066792536u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 12682136550675316736u));
}
