#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"

using namespace basim;

class SR : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    UDLane lane0 = UDLane(0);
};
TEST_F(SR, random_0){
    lane0.initSetup(0,"testprogs/binaries/sr_0.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 341892876384791884u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 9223558920039918865u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 0u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 341892876384791884u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 9223558920039918865u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 0u));
}
TEST_F(SR, random_1){
    lane0.initSetup(0,"testprogs/binaries/sr_1.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 9140534486964946304u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 14776449347434806473u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 0u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 9140534486964946304u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 14776449347434806473u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 0u));
}
TEST_F(SR, random_2){
    lane0.initSetup(0,"testprogs/binaries/sr_2.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 7150883672584181301u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 10207773470806323047u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 0u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 7150883672584181301u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 10207773470806323047u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 0u));
}
TEST_F(SR, random_3){
    lane0.initSetup(0,"testprogs/binaries/sr_3.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 1084802125127712120u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 11588859770034410380u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 0u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 1084802125127712120u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 11588859770034410380u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 0u));
}
TEST_F(SR, random_4){
    lane0.initSetup(0,"testprogs/binaries/sr_4.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 3143121400130716292u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 16347120324347868244u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 0u));
    EXPECT_TRUE(lane0.testReg(RegId::X16, 3143121400130716292u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 16347120324347868244u));
    EXPECT_TRUE(lane0.testReg(RegId::X18, 0u));
}
