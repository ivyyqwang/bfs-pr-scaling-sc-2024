#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"

using namespace basim;

class ssprop : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    int numLanes = 64;
    UDAccelerator acc0 = UDAccelerator(numLanes, 0, 1); // UDAccelerator(numLanes, UDID/networkID, lmmode (0: accelerator based addressing, 1:bank/lane based addressing))
    int buffsize1 = 1024;
    int buffsize2 = 1024;
};
TEST_F(ssprop, Basic_ssprop_0_common_TX){
    acc0.initSetup(0, "testprogs/binaries/ssprop_0_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(60);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t *data = new word_t[numop];
    data[0] = reinterpret_cast<word_t>((uint64_t)8);
    data[1] = reinterpret_cast<word_t>((uint64_t)9);
    data[2] = reinterpret_cast<word_t>((uint64_t)10);
    data[3] = reinterpret_cast<word_t>((uint64_t)11);
    data[4] = reinterpret_cast<word_t>((uint64_t)12);
    data[5] = reinterpret_cast<word_t>((uint64_t)13);
    data[6] = reinterpret_cast<word_t>((uint64_t)14);
    data[7] = reinterpret_cast<word_t>((uint64_t)15);
    
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        word_t val=0;
        acc0.readScratchPad(8, (i<<16), (uint8_t*)&val);
        EXPECT_TRUE((val & 0b1111) == 10);
        EXPECT_TRUE(((val >> 16) & 0b111111111111) == 987);
    }
}
TEST_F(ssprop, Basic_ssprop_1_common_TX){
    acc0.initSetup(0, "testprogs/binaries/ssprop_1_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(60);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t *data = new word_t[numop];
    data[0] = reinterpret_cast<word_t>((uint64_t)8);
    data[1] = reinterpret_cast<word_t>((uint64_t)9);
    data[2] = reinterpret_cast<word_t>((uint64_t)10);
    data[3] = reinterpret_cast<word_t>((uint64_t)11);
    data[4] = reinterpret_cast<word_t>((uint64_t)12);
    data[5] = reinterpret_cast<word_t>((uint64_t)13);
    data[6] = reinterpret_cast<word_t>((uint64_t)14);
    data[7] = reinterpret_cast<word_t>((uint64_t)15);
    
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        word_t val=0;
        acc0.readScratchPad(8, (i<<16), (uint8_t*)&val);
        EXPECT_TRUE((val & 0b1111) == 1);
        EXPECT_TRUE(((val >> 16) & 0b111111111111) == 3062);
    }
}
TEST_F(ssprop, Basic_ssprop_2_common_TX){
    acc0.initSetup(0, "testprogs/binaries/ssprop_2_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(60);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t *data = new word_t[numop];
    data[0] = reinterpret_cast<word_t>((uint64_t)8);
    data[1] = reinterpret_cast<word_t>((uint64_t)9);
    data[2] = reinterpret_cast<word_t>((uint64_t)10);
    data[3] = reinterpret_cast<word_t>((uint64_t)11);
    data[4] = reinterpret_cast<word_t>((uint64_t)12);
    data[5] = reinterpret_cast<word_t>((uint64_t)13);
    data[6] = reinterpret_cast<word_t>((uint64_t)14);
    data[7] = reinterpret_cast<word_t>((uint64_t)15);
    
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        word_t val=0;
        acc0.readScratchPad(8, (i<<16), (uint8_t*)&val);
        EXPECT_TRUE((val & 0b1111) == 6);
        EXPECT_TRUE(((val >> 16) & 0b111111111111) == 2158);
    }
}
TEST_F(ssprop, Basic_ssprop_3_common_TX){
    acc0.initSetup(0, "testprogs/binaries/ssprop_3_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(60);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t *data = new word_t[numop];
    data[0] = reinterpret_cast<word_t>((uint64_t)8);
    data[1] = reinterpret_cast<word_t>((uint64_t)9);
    data[2] = reinterpret_cast<word_t>((uint64_t)10);
    data[3] = reinterpret_cast<word_t>((uint64_t)11);
    data[4] = reinterpret_cast<word_t>((uint64_t)12);
    data[5] = reinterpret_cast<word_t>((uint64_t)13);
    data[6] = reinterpret_cast<word_t>((uint64_t)14);
    data[7] = reinterpret_cast<word_t>((uint64_t)15);
    
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        word_t val=0;
        acc0.readScratchPad(8, (i<<16), (uint8_t*)&val);
        EXPECT_TRUE((val & 0b1111) == 11);
        EXPECT_TRUE(((val >> 16) & 0b111111111111) == 2188);
    }
}
TEST_F(ssprop, Basic_ssprop_4_common_TX){
    acc0.initSetup(0, "testprogs/binaries/ssprop_4_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(60);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t *data = new word_t[numop];
    data[0] = reinterpret_cast<word_t>((uint64_t)8);
    data[1] = reinterpret_cast<word_t>((uint64_t)9);
    data[2] = reinterpret_cast<word_t>((uint64_t)10);
    data[3] = reinterpret_cast<word_t>((uint64_t)11);
    data[4] = reinterpret_cast<word_t>((uint64_t)12);
    data[5] = reinterpret_cast<word_t>((uint64_t)13);
    data[6] = reinterpret_cast<word_t>((uint64_t)14);
    data[7] = reinterpret_cast<word_t>((uint64_t)15);
    
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        word_t val=0;
        acc0.readScratchPad(8, (i<<16), (uint8_t*)&val);
        EXPECT_TRUE((val & 0b1111) == 1);
        EXPECT_TRUE(((val >> 16) & 0b111111111111) == 579);
    }
}
TEST_F(ssprop, Basic_ssprop_5_common_TX){
    acc0.initSetup(0, "testprogs/binaries/ssprop_5_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(60);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t *data = new word_t[numop];
    data[0] = reinterpret_cast<word_t>((uint64_t)8);
    data[1] = reinterpret_cast<word_t>((uint64_t)9);
    data[2] = reinterpret_cast<word_t>((uint64_t)10);
    data[3] = reinterpret_cast<word_t>((uint64_t)11);
    data[4] = reinterpret_cast<word_t>((uint64_t)12);
    data[5] = reinterpret_cast<word_t>((uint64_t)13);
    data[6] = reinterpret_cast<word_t>((uint64_t)14);
    data[7] = reinterpret_cast<word_t>((uint64_t)15);
    
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        word_t val=0;
        acc0.readScratchPad(8, (i<<16), (uint8_t*)&val);
        EXPECT_TRUE((val & 0b1111) == 11);
        EXPECT_TRUE(((val >> 16) & 0b111111111111) == 898);
    }
}
TEST_F(ssprop, Basic_ssprop_6_common_TX){
    acc0.initSetup(0, "testprogs/binaries/ssprop_6_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(60);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t *data = new word_t[numop];
    data[0] = reinterpret_cast<word_t>((uint64_t)8);
    data[1] = reinterpret_cast<word_t>((uint64_t)9);
    data[2] = reinterpret_cast<word_t>((uint64_t)10);
    data[3] = reinterpret_cast<word_t>((uint64_t)11);
    data[4] = reinterpret_cast<word_t>((uint64_t)12);
    data[5] = reinterpret_cast<word_t>((uint64_t)13);
    data[6] = reinterpret_cast<word_t>((uint64_t)14);
    data[7] = reinterpret_cast<word_t>((uint64_t)15);
    
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        word_t val=0;
        acc0.readScratchPad(8, (i<<16), (uint8_t*)&val);
        EXPECT_TRUE((val & 0b1111) == 3);
        EXPECT_TRUE(((val >> 16) & 0b111111111111) == 814);
    }
}
TEST_F(ssprop, Basic_ssprop_7_common_TX){
    acc0.initSetup(0, "testprogs/binaries/ssprop_7_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(60);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t *data = new word_t[numop];
    data[0] = reinterpret_cast<word_t>((uint64_t)8);
    data[1] = reinterpret_cast<word_t>((uint64_t)9);
    data[2] = reinterpret_cast<word_t>((uint64_t)10);
    data[3] = reinterpret_cast<word_t>((uint64_t)11);
    data[4] = reinterpret_cast<word_t>((uint64_t)12);
    data[5] = reinterpret_cast<word_t>((uint64_t)13);
    data[6] = reinterpret_cast<word_t>((uint64_t)14);
    data[7] = reinterpret_cast<word_t>((uint64_t)15);
    
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        word_t val=0;
        acc0.readScratchPad(8, (i<<16), (uint8_t*)&val);
        EXPECT_TRUE((val & 0b1111) == 3);
        EXPECT_TRUE(((val >> 16) & 0b111111111111) == 1366);
    }
}
TEST_F(ssprop, Basic_ssprop_8_common_TX){
    acc0.initSetup(0, "testprogs/binaries/ssprop_8_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(60);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t *data = new word_t[numop];
    data[0] = reinterpret_cast<word_t>((uint64_t)8);
    data[1] = reinterpret_cast<word_t>((uint64_t)9);
    data[2] = reinterpret_cast<word_t>((uint64_t)10);
    data[3] = reinterpret_cast<word_t>((uint64_t)11);
    data[4] = reinterpret_cast<word_t>((uint64_t)12);
    data[5] = reinterpret_cast<word_t>((uint64_t)13);
    data[6] = reinterpret_cast<word_t>((uint64_t)14);
    data[7] = reinterpret_cast<word_t>((uint64_t)15);
    
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        word_t val=0;
        acc0.readScratchPad(8, (i<<16), (uint8_t*)&val);
        EXPECT_TRUE((val & 0b1111) == 0);
        EXPECT_TRUE(((val >> 16) & 0b111111111111) == 3359);
    }
}
TEST_F(ssprop, Basic_ssprop_9_common_TX){
    acc0.initSetup(0, "testprogs/binaries/ssprop_9_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(60);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t *data = new word_t[numop];
    data[0] = reinterpret_cast<word_t>((uint64_t)8);
    data[1] = reinterpret_cast<word_t>((uint64_t)9);
    data[2] = reinterpret_cast<word_t>((uint64_t)10);
    data[3] = reinterpret_cast<word_t>((uint64_t)11);
    data[4] = reinterpret_cast<word_t>((uint64_t)12);
    data[5] = reinterpret_cast<word_t>((uint64_t)13);
    data[6] = reinterpret_cast<word_t>((uint64_t)14);
    data[7] = reinterpret_cast<word_t>((uint64_t)15);
    
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        word_t val=0;
        acc0.readScratchPad(8, (i<<16), (uint8_t*)&val);
        EXPECT_TRUE((val & 0b1111) == 3);
        EXPECT_TRUE(((val >> 16) & 0b111111111111) == 3504);
    }
}
TEST_F(ssprop, Basic_ssprop_10_common_TX){
    acc0.initSetup(0, "testprogs/binaries/ssprop_10_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(60);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t *data = new word_t[numop];
    data[0] = reinterpret_cast<word_t>((uint64_t)8);
    data[1] = reinterpret_cast<word_t>((uint64_t)9);
    data[2] = reinterpret_cast<word_t>((uint64_t)10);
    data[3] = reinterpret_cast<word_t>((uint64_t)11);
    data[4] = reinterpret_cast<word_t>((uint64_t)12);
    data[5] = reinterpret_cast<word_t>((uint64_t)13);
    data[6] = reinterpret_cast<word_t>((uint64_t)14);
    data[7] = reinterpret_cast<word_t>((uint64_t)15);
    
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        word_t val=0;
        acc0.readScratchPad(8, (i<<16), (uint8_t*)&val);
        EXPECT_TRUE((val & 0b1111) == 2);
        EXPECT_TRUE(((val >> 16) & 0b111111111111) == 41);
    }
}
TEST_F(ssprop, Basic_ssprop_11_common_TX){
    acc0.initSetup(0, "testprogs/binaries/ssprop_11_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(60);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t *data = new word_t[numop];
    data[0] = reinterpret_cast<word_t>((uint64_t)8);
    data[1] = reinterpret_cast<word_t>((uint64_t)9);
    data[2] = reinterpret_cast<word_t>((uint64_t)10);
    data[3] = reinterpret_cast<word_t>((uint64_t)11);
    data[4] = reinterpret_cast<word_t>((uint64_t)12);
    data[5] = reinterpret_cast<word_t>((uint64_t)13);
    data[6] = reinterpret_cast<word_t>((uint64_t)14);
    data[7] = reinterpret_cast<word_t>((uint64_t)15);
    
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        word_t val=0;
        acc0.readScratchPad(8, (i<<16), (uint8_t*)&val);
        EXPECT_TRUE((val & 0b1111) == 11);
        EXPECT_TRUE(((val >> 16) & 0b111111111111) == 2892);
    }
}
TEST_F(ssprop, Basic_ssprop_12_common_TX){
    acc0.initSetup(0, "testprogs/binaries/ssprop_12_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(60);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t *data = new word_t[numop];
    data[0] = reinterpret_cast<word_t>((uint64_t)8);
    data[1] = reinterpret_cast<word_t>((uint64_t)9);
    data[2] = reinterpret_cast<word_t>((uint64_t)10);
    data[3] = reinterpret_cast<word_t>((uint64_t)11);
    data[4] = reinterpret_cast<word_t>((uint64_t)12);
    data[5] = reinterpret_cast<word_t>((uint64_t)13);
    data[6] = reinterpret_cast<word_t>((uint64_t)14);
    data[7] = reinterpret_cast<word_t>((uint64_t)15);
    
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        word_t val=0;
        acc0.readScratchPad(8, (i<<16), (uint8_t*)&val);
        EXPECT_TRUE((val & 0b1111) == 4);
        EXPECT_TRUE(((val >> 16) & 0b111111111111) == 2674);
    }
}
TEST_F(ssprop, Basic_ssprop_13_common_TX){
    acc0.initSetup(0, "testprogs/binaries/ssprop_13_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(60);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t *data = new word_t[numop];
    data[0] = reinterpret_cast<word_t>((uint64_t)8);
    data[1] = reinterpret_cast<word_t>((uint64_t)9);
    data[2] = reinterpret_cast<word_t>((uint64_t)10);
    data[3] = reinterpret_cast<word_t>((uint64_t)11);
    data[4] = reinterpret_cast<word_t>((uint64_t)12);
    data[5] = reinterpret_cast<word_t>((uint64_t)13);
    data[6] = reinterpret_cast<word_t>((uint64_t)14);
    data[7] = reinterpret_cast<word_t>((uint64_t)15);
    
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        word_t val=0;
        acc0.readScratchPad(8, (i<<16), (uint8_t*)&val);
        EXPECT_TRUE((val & 0b1111) == 1);
        EXPECT_TRUE(((val >> 16) & 0b111111111111) == 2223);
    }
}
TEST_F(ssprop, Basic_ssprop_14_common_TX){
    acc0.initSetup(0, "testprogs/binaries/ssprop_14_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(60);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t *data = new word_t[numop];
    data[0] = reinterpret_cast<word_t>((uint64_t)8);
    data[1] = reinterpret_cast<word_t>((uint64_t)9);
    data[2] = reinterpret_cast<word_t>((uint64_t)10);
    data[3] = reinterpret_cast<word_t>((uint64_t)11);
    data[4] = reinterpret_cast<word_t>((uint64_t)12);
    data[5] = reinterpret_cast<word_t>((uint64_t)13);
    data[6] = reinterpret_cast<word_t>((uint64_t)14);
    data[7] = reinterpret_cast<word_t>((uint64_t)15);
    
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        word_t val=0;
        acc0.readScratchPad(8, (i<<16), (uint8_t*)&val);
        EXPECT_TRUE((val & 0b1111) == 5);
        EXPECT_TRUE(((val >> 16) & 0b111111111111) == 3116);
    }
}
TEST_F(ssprop, Basic_ssprop_15_common_TX){
    acc0.initSetup(0, "testprogs/binaries/ssprop_15_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(60);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t *data = new word_t[numop];
    data[0] = reinterpret_cast<word_t>((uint64_t)8);
    data[1] = reinterpret_cast<word_t>((uint64_t)9);
    data[2] = reinterpret_cast<word_t>((uint64_t)10);
    data[3] = reinterpret_cast<word_t>((uint64_t)11);
    data[4] = reinterpret_cast<word_t>((uint64_t)12);
    data[5] = reinterpret_cast<word_t>((uint64_t)13);
    data[6] = reinterpret_cast<word_t>((uint64_t)14);
    data[7] = reinterpret_cast<word_t>((uint64_t)15);
    
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        word_t val=0;
        acc0.readScratchPad(8, (i<<16), (uint8_t*)&val);
        EXPECT_TRUE((val & 0b1111) == 6);
        EXPECT_TRUE(((val >> 16) & 0b111111111111) == 2178);
    }
}
TEST_F(ssprop, Basic_ssprop_16_common_TX){
    acc0.initSetup(0, "testprogs/binaries/ssprop_16_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(60);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t *data = new word_t[numop];
    data[0] = reinterpret_cast<word_t>((uint64_t)8);
    data[1] = reinterpret_cast<word_t>((uint64_t)9);
    data[2] = reinterpret_cast<word_t>((uint64_t)10);
    data[3] = reinterpret_cast<word_t>((uint64_t)11);
    data[4] = reinterpret_cast<word_t>((uint64_t)12);
    data[5] = reinterpret_cast<word_t>((uint64_t)13);
    data[6] = reinterpret_cast<word_t>((uint64_t)14);
    data[7] = reinterpret_cast<word_t>((uint64_t)15);
    
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        word_t val=0;
        acc0.readScratchPad(8, (i<<16), (uint8_t*)&val);
        EXPECT_TRUE((val & 0b1111) == 5);
        EXPECT_TRUE(((val >> 16) & 0b111111111111) == 3279);
    }
}
TEST_F(ssprop, Basic_ssprop_17_common_TX){
    acc0.initSetup(0, "testprogs/binaries/ssprop_17_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(60);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t *data = new word_t[numop];
    data[0] = reinterpret_cast<word_t>((uint64_t)8);
    data[1] = reinterpret_cast<word_t>((uint64_t)9);
    data[2] = reinterpret_cast<word_t>((uint64_t)10);
    data[3] = reinterpret_cast<word_t>((uint64_t)11);
    data[4] = reinterpret_cast<word_t>((uint64_t)12);
    data[5] = reinterpret_cast<word_t>((uint64_t)13);
    data[6] = reinterpret_cast<word_t>((uint64_t)14);
    data[7] = reinterpret_cast<word_t>((uint64_t)15);
    
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        word_t val=0;
        acc0.readScratchPad(8, (i<<16), (uint8_t*)&val);
        EXPECT_TRUE((val & 0b1111) == 9);
        EXPECT_TRUE(((val >> 16) & 0b111111111111) == 3279);
    }
}
TEST_F(ssprop, Basic_ssprop_18_common_TX){
    acc0.initSetup(0, "testprogs/binaries/ssprop_18_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(60);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t *data = new word_t[numop];
    data[0] = reinterpret_cast<word_t>((uint64_t)8);
    data[1] = reinterpret_cast<word_t>((uint64_t)9);
    data[2] = reinterpret_cast<word_t>((uint64_t)10);
    data[3] = reinterpret_cast<word_t>((uint64_t)11);
    data[4] = reinterpret_cast<word_t>((uint64_t)12);
    data[5] = reinterpret_cast<word_t>((uint64_t)13);
    data[6] = reinterpret_cast<word_t>((uint64_t)14);
    data[7] = reinterpret_cast<word_t>((uint64_t)15);
    
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        word_t val=0;
        acc0.readScratchPad(8, (i<<16), (uint8_t*)&val);
        EXPECT_TRUE((val & 0b1111) == 11);
        EXPECT_TRUE(((val >> 16) & 0b111111111111) == 2973);
    }
}
TEST_F(ssprop, Basic_ssprop_19_common_TX){
    acc0.initSetup(0, "testprogs/binaries/ssprop_19_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(60);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t *data = new word_t[numop];
    data[0] = reinterpret_cast<word_t>((uint64_t)8);
    data[1] = reinterpret_cast<word_t>((uint64_t)9);
    data[2] = reinterpret_cast<word_t>((uint64_t)10);
    data[3] = reinterpret_cast<word_t>((uint64_t)11);
    data[4] = reinterpret_cast<word_t>((uint64_t)12);
    data[5] = reinterpret_cast<word_t>((uint64_t)13);
    data[6] = reinterpret_cast<word_t>((uint64_t)14);
    data[7] = reinterpret_cast<word_t>((uint64_t)15);
    
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        word_t val=0;
        acc0.readScratchPad(8, (i<<16), (uint8_t*)&val);
        EXPECT_TRUE((val & 0b1111) == 4);
        EXPECT_TRUE(((val >> 16) & 0b111111111111) == 3931);
    }
}
