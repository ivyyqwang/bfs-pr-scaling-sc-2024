#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"

using namespace basim;

class movrr : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    int numLanes = 64;
    UDAccelerator acc0 = UDAccelerator(numLanes, 0, 1); // UDAccelerator(numLanes, UDID/networkID, lmmode (0: accelerator based addressing, 1:bank/lane based addressing))
    int buffsize1 = 1024;
    int buffsize2 = 1024;
};
TEST_F(movrr, Basic_movrr_0){
    acc0.initSetup(0, "testprogs/binaries/movrr_0.bin", 0);
    int numop = 9;
    eventword_t ev0(0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X23, 1488906445714679933u));
        word_t reg_val=0;
        acc0.readScratchPad(8, i << 16, (uint8_t*)&reg_val);
        EXPECT_TRUE(acc0.testReg(i, RegId::X23, reg_val));
    }
}
TEST_F(movrr, Basic_movrr_1){
    acc0.initSetup(0, "testprogs/binaries/movrr_1.bin", 0);
    int numop = 9;
    eventword_t ev0(0);
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
        word_t reg_val=0;
        acc0.readScratchPad(8, i << 16, (uint8_t*)&reg_val);
        EXPECT_TRUE(acc0.testReg(i, RegId::X20, reg_val));
    }
}
TEST_F(movrr, Basic_movrr_2){
    acc0.initSetup(0, "testprogs/binaries/movrr_2.bin", 0);
    int numop = 9;
    eventword_t ev0(0);
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
        word_t reg_val=0;
        acc0.readScratchPad(8, i << 16, (uint8_t*)&reg_val);
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, reg_val));
    }
}
TEST_F(movrr, Basic_movrr_3){
    acc0.initSetup(0, "testprogs/binaries/movrr_3.bin", 0);
    int numop = 9;
    eventword_t ev0(0);
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
        word_t reg_val=0;
        acc0.readScratchPad(8, i << 16, (uint8_t*)&reg_val);
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, reg_val));
    }
}
TEST_F(movrr, Basic_movrr_4){
    acc0.initSetup(0, "testprogs/binaries/movrr_4.bin", 0);
    int numop = 9;
    eventword_t ev0(0);
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
        word_t reg_val=0;
        acc0.readScratchPad(8, i << 16, (uint8_t*)&reg_val);
        EXPECT_TRUE(acc0.testReg(i, RegId::X20, reg_val));
    }
}
TEST_F(movrr, Basic_movrr_5){
    acc0.initSetup(0, "testprogs/binaries/movrr_5.bin", 0);
    int numop = 9;
    eventword_t ev0(0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 10809647217147908502u));
        word_t reg_val=0;
        acc0.readScratchPad(8, i << 16, (uint8_t*)&reg_val);
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, reg_val));
    }
}
TEST_F(movrr, Basic_movrr_6){
    acc0.initSetup(0, "testprogs/binaries/movrr_6.bin", 0);
    int numop = 9;
    eventword_t ev0(0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X21, 8897801524192230066u));
        word_t reg_val=0;
        acc0.readScratchPad(8, i << 16, (uint8_t*)&reg_val);
        EXPECT_TRUE(acc0.testReg(i, RegId::X21, reg_val));
    }
}
TEST_F(movrr, Basic_movrr_7){
    acc0.initSetup(0, "testprogs/binaries/movrr_7.bin", 0);
    int numop = 9;
    eventword_t ev0(0);
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
        word_t reg_val=0;
        acc0.readScratchPad(8, i << 16, (uint8_t*)&reg_val);
        EXPECT_TRUE(acc0.testReg(i, RegId::X21, reg_val));
    }
}
TEST_F(movrr, Basic_movrr_8){
    acc0.initSetup(0, "testprogs/binaries/movrr_8.bin", 0);
    int numop = 9;
    eventword_t ev0(0);
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
        word_t reg_val=0;
        acc0.readScratchPad(8, i << 16, (uint8_t*)&reg_val);
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, reg_val));
    }
}
TEST_F(movrr, Basic_movrr_9){
    acc0.initSetup(0, "testprogs/binaries/movrr_9.bin", 0);
    int numop = 9;
    eventword_t ev0(0);
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
        word_t reg_val=0;
        acc0.readScratchPad(8, i << 16, (uint8_t*)&reg_val);
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, reg_val));
    }
}
TEST_F(movrr, Basic_movrr_10){
    acc0.initSetup(0, "testprogs/binaries/movrr_10.bin", 0);
    int numop = 9;
    eventword_t ev0(0);
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
        word_t reg_val=0;
        acc0.readScratchPad(8, i << 16, (uint8_t*)&reg_val);
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, reg_val));
    }
}
TEST_F(movrr, Basic_movrr_11){
    acc0.initSetup(0, "testprogs/binaries/movrr_11.bin", 0);
    int numop = 9;
    eventword_t ev0(0);
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
        word_t reg_val=0;
        acc0.readScratchPad(8, i << 16, (uint8_t*)&reg_val);
        EXPECT_TRUE(acc0.testReg(i, RegId::X23, reg_val));
    }
}
TEST_F(movrr, Basic_movrr_12){
    acc0.initSetup(0, "testprogs/binaries/movrr_12.bin", 0);
    int numop = 9;
    eventword_t ev0(0);
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
        word_t reg_val=0;
        acc0.readScratchPad(8, i << 16, (uint8_t*)&reg_val);
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, reg_val));
    }
}
TEST_F(movrr, Basic_movrr_13){
    acc0.initSetup(0, "testprogs/binaries/movrr_13.bin", 0);
    int numop = 9;
    eventword_t ev0(0);
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
        word_t reg_val=0;
        acc0.readScratchPad(8, i << 16, (uint8_t*)&reg_val);
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, reg_val));
    }
}
TEST_F(movrr, Basic_movrr_14){
    acc0.initSetup(0, "testprogs/binaries/movrr_14.bin", 0);
    int numop = 9;
    eventword_t ev0(0);
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
        word_t reg_val=0;
        acc0.readScratchPad(8, i << 16, (uint8_t*)&reg_val);
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, reg_val));
    }
}
TEST_F(movrr, Basic_movrr_15){
    acc0.initSetup(0, "testprogs/binaries/movrr_15.bin", 0);
    int numop = 9;
    eventword_t ev0(0);
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
        word_t reg_val=0;
        acc0.readScratchPad(8, i << 16, (uint8_t*)&reg_val);
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, reg_val));
    }
}
TEST_F(movrr, Basic_movrr_16){
    acc0.initSetup(0, "testprogs/binaries/movrr_16.bin", 0);
    int numop = 9;
    eventword_t ev0(0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 12430224935834047753u));
        word_t reg_val=0;
        acc0.readScratchPad(8, i << 16, (uint8_t*)&reg_val);
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, reg_val));
    }
}
TEST_F(movrr, Basic_movrr_17){
    acc0.initSetup(0, "testprogs/binaries/movrr_17.bin", 0);
    int numop = 9;
    eventword_t ev0(0);
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
        word_t reg_val=0;
        acc0.readScratchPad(8, i << 16, (uint8_t*)&reg_val);
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, reg_val));
    }
}
TEST_F(movrr, Basic_movrr_18){
    acc0.initSetup(0, "testprogs/binaries/movrr_18.bin", 0);
    int numop = 9;
    eventword_t ev0(0);
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
        word_t reg_val=0;
        acc0.readScratchPad(8, i << 16, (uint8_t*)&reg_val);
        EXPECT_TRUE(acc0.testReg(i, RegId::X23, reg_val));
    }
}
TEST_F(movrr, Basic_movrr_19){
    acc0.initSetup(0, "testprogs/binaries/movrr_19.bin", 0);
    int numop = 9;
    eventword_t ev0(0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 17977164648524612386u));
        word_t reg_val=0;
        acc0.readScratchPad(8, i << 16, (uint8_t*)&reg_val);
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, reg_val));
    }
}
