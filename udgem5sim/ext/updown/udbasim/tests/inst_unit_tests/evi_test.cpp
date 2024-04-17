#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"

using namespace basim;

class EVI : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    UDLane lane0 = UDLane(0);
};
TEST_F(EVI, random_0){
    lane0.initSetup(0,"testprogs/binaries/evi_0.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 7135989099151346348u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 7135989099144006316u, 0xFFFFFFFFFFF00000));
}
TEST_F(EVI, random_1){
    lane0.initSetup(0,"testprogs/binaries/evi_1.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 659335404225498358u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 659335404226546934u, 0xFFFFFFFFFFF00000));
}
TEST_F(EVI, random_2){
    lane0.initSetup(0,"testprogs/binaries/evi_2.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 18244408065023091941u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 18244408065022494496u, 0xFFFFFFFFFFF00000));
}
TEST_F(EVI, random_3){
    lane0.initSetup(0,"testprogs/binaries/evi_3.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 11833511387195475936u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 9461667432416u, 0xFFFFFFFFFFF00000));
}
TEST_F(EVI, random_4){
    lane0.initSetup(0,"testprogs/binaries/evi_4.bin", 0);
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
    EXPECT_TRUE(lane0.testReg(RegId::X16, 2887572351203462116u));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 2887572352428198884u, 0xFFFFFFFFFFF00000));
}
