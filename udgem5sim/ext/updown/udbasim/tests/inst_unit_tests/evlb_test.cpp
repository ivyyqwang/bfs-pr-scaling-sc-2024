#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"

using namespace basim;

class EVLB : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    UDLane lane0 = UDLane(0);
};
TEST_F(EVLB, random_0){
    lane0.initSetup(0,"testprogs/binaries/evlb_0.bin", 0);
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
    EventWord new_ev(1956052763763540352u);
    new_ev.setEventLabel(901863 & ELABELBITS);
    EXPECT_TRUE(lane0.testReg(RegId::X16, new_ev.eventword, 0xFFFFFFFFFFF00000));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 5627724296466019946u));
}
TEST_F(EVLB, random_1){
    lane0.initSetup(0,"testprogs/binaries/evlb_1.bin", 0);
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
    EventWord new_ev(18030146700975002337u);
    new_ev.setEventLabel(259136 & ELABELBITS);
    EXPECT_TRUE(lane0.testReg(RegId::X16, new_ev.eventword, 0xFFFFFFFFFFF00000));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 12583740755808394491u));
}
TEST_F(EVLB, random_2){
    lane0.initSetup(0,"testprogs/binaries/evlb_2.bin", 0);
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
    EventWord new_ev(6946603834614952392u);
    new_ev.setEventLabel(916387 & ELABELBITS);
    EXPECT_TRUE(lane0.testReg(RegId::X16, new_ev.eventword, 0xFFFFFFFFFFF00000));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 2101424519121027997u));
}
TEST_F(EVLB, random_3){
    lane0.initSetup(0,"testprogs/binaries/evlb_3.bin", 0);
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
    EventWord new_ev(18349478153930063038u);
    new_ev.setEventLabel(739034 & ELABELBITS);
    EXPECT_TRUE(lane0.testReg(RegId::X16, new_ev.eventword, 0xFFFFFFFFFFF00000));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 12078452479358443545u));
}
TEST_F(EVLB, random_4){
    lane0.initSetup(0,"testprogs/binaries/evlb_4.bin", 0);
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
    EventWord new_ev(6691101768529707910u);
    new_ev.setEventLabel(374500 & ELABELBITS);
    EXPECT_TRUE(lane0.testReg(RegId::X16, new_ev.eventword, 0xFFFFFFFFFFF00000));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 6349913468726956540u));
}
