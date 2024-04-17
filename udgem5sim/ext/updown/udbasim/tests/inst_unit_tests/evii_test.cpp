#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"

using namespace basim;

class EVII : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    UDLane lane0 = UDLane(0);
};
TEST_F(EVII, random_0){
    lane0.initSetup(0,"testprogs/binaries/evii_0.bin", 0);
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
    EventWord new_ev(lane0.readReg(RegId::X2));
    if (6 & 0x8) {
        new_ev.setNWIDbits(275 & NWIDBITS);}
    if (6 & 0x4) {
        if (6 & 0x8)
            new_ev.setThreadID(3441 & THREADIDBITS);
        else
            new_ev.setThreadID(275 & THREADIDBITS);}
    if (6 & 0x2) {
        if (6 & 0xC)
            new_ev.setNumOperands(3441 & NUMOPBITS);
        else
            new_ev.setNumOperands(275 & NUMOPBITS);}
    if (6 & 0x1) {
        new_ev.setEventLabel(3441 & ELABELBITS);}
    EXPECT_TRUE(lane0.testReg(RegId::X16, new_ev.eventword, 0xFFFFFFFFFFF00000));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 7396342334865196507u));
}
TEST_F(EVII, random_1){
    lane0.initSetup(0,"testprogs/binaries/evii_1.bin", 0);
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
    EventWord new_ev(lane0.readReg(RegId::X2));
    if (5 & 0x8) {
        new_ev.setNWIDbits(3337 & NWIDBITS);}
    if (5 & 0x4) {
        if (5 & 0x8)
            new_ev.setThreadID(462712 & THREADIDBITS);
        else
            new_ev.setThreadID(3337 & THREADIDBITS);}
    if (5 & 0x2) {
        if (5 & 0xC)
            new_ev.setNumOperands(462712 & NUMOPBITS);
        else
            new_ev.setNumOperands(3337 & NUMOPBITS);}
    if (5 & 0x1) {
        new_ev.setEventLabel(462712 & ELABELBITS);}
    EXPECT_TRUE(lane0.testReg(RegId::X16, new_ev.eventword, 0xFFFFFFFFFFF00000));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 9708371753346372129u));
}
TEST_F(EVII, random_2){
    lane0.initSetup(0,"testprogs/binaries/evii_2.bin", 0);
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
    EventWord new_ev(lane0.readReg(RegId::X2));
    if (10 & 0x8) {
        new_ev.setNWIDbits(2556 & NWIDBITS);}
    if (10 & 0x4) {
        if (10 & 0x8)
            new_ev.setThreadID(3000 & THREADIDBITS);
        else
            new_ev.setThreadID(2556 & THREADIDBITS);}
    if (10 & 0x2) {
        if (10 & 0xC)
            new_ev.setNumOperands(3000 & NUMOPBITS);
        else
            new_ev.setNumOperands(2556 & NUMOPBITS);}
    if (10 & 0x1) {
        new_ev.setEventLabel(3000 & ELABELBITS);}
    EXPECT_TRUE(lane0.testReg(RegId::X16, new_ev.eventword, 0xFFFFFFFFFFF00000));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 7766351602141564138u));
}
TEST_F(EVII, random_3){
    lane0.initSetup(0,"testprogs/binaries/evii_3.bin", 0);
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
    EventWord new_ev(lane0.readReg(RegId::X2));
    if (5 & 0x8) {
        new_ev.setNWIDbits(228 & NWIDBITS);}
    if (5 & 0x4) {
        if (5 & 0x8)
            new_ev.setThreadID(838091 & THREADIDBITS);
        else
            new_ev.setThreadID(228 & THREADIDBITS);}
    if (5 & 0x2) {
        if (5 & 0xC)
            new_ev.setNumOperands(838091 & NUMOPBITS);
        else
            new_ev.setNumOperands(228 & NUMOPBITS);}
    if (5 & 0x1) {
        new_ev.setEventLabel(838091 & ELABELBITS);}
    EXPECT_TRUE(lane0.testReg(RegId::X16, new_ev.eventword, 0xFFFFFFFFFFF00000));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 12303954885491945154u));
}
TEST_F(EVII, random_4){
    lane0.initSetup(0,"testprogs/binaries/evii_4.bin", 0);
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
    EventWord new_ev(lane0.readReg(RegId::X2));
    if (5 & 0x8) {
        new_ev.setNWIDbits(3739 & NWIDBITS);}
    if (5 & 0x4) {
        if (5 & 0x8)
            new_ev.setThreadID(496296 & THREADIDBITS);
        else
            new_ev.setThreadID(3739 & THREADIDBITS);}
    if (5 & 0x2) {
        if (5 & 0xC)
            new_ev.setNumOperands(496296 & NUMOPBITS);
        else
            new_ev.setNumOperands(3739 & NUMOPBITS);}
    if (5 & 0x1) {
        new_ev.setEventLabel(496296 & ELABELBITS);}
    EXPECT_TRUE(lane0.testReg(RegId::X16, new_ev.eventword, 0xFFFFFFFFFFF00000));
    EXPECT_TRUE(lane0.testReg(RegId::X17, 18176692132299073186u));
}
