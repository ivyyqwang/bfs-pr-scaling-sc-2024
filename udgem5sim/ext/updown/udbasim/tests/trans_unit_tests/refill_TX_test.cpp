#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"

using namespace basim;

class refill_TX : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    int numLanes = 64;
    UDAccelerator acc0 = UDAccelerator(numLanes, 0, 1); // UDAccelerator(numLanes, UDID/networkID, lmmode (0: accelerator based addressing, 1:bank/lane based addressing))
    int buffsize1 = 1024;
    int buffsize2 = 1024;
};
TEST_F(refill_TX, Basic_refill_TX_0){
    acc0.initSetup(0, "testprogs/binaries/refill_TX_0.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8228);
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
    for(auto i = 0; i < numLanes; i++){
        acc0.pushEventOperands(eops, i);
    }
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 4644765190821249039u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 19) + 5 - 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 5 - 0)));
    }
}
TEST_F(refill_TX, Basic_refill_TX_1){
    acc0.initSetup(0, "testprogs/binaries/refill_TX_1.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8228);
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
    for(auto i = 0; i < numLanes; i++){
        acc0.pushEventOperands(eops, i);
    }
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 292057776140u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 16)) + 4 - 0);
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 4 - 0)));
    }
}
TEST_F(refill_TX, Basic_refill_TX_2){
    acc0.initSetup(0, "testprogs/binaries/refill_TX_2.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8228);
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
    for(auto i = 0; i < numLanes; i++){
        acc0.pushEventOperands(eops, i);
    }
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 18402264520513814543u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 16)) + 5 - 1);
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 5 - 1)));
    }
}
TEST_F(refill_TX, Basic_refill_TX_3){
    acc0.initSetup(0, "testprogs/binaries/refill_TX_3.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8228);
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
    for(auto i = 0; i < numLanes; i++){
        acc0.pushEventOperands(eops, i);
    }
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 3880963879236272146u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 16)) + 6 - 3);
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 6 - 3)));
    }
}
TEST_F(refill_TX, Basic_refill_TX_4){
    acc0.initSetup(0, "testprogs/binaries/refill_TX_4.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8228);
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
    for(auto i = 0; i < numLanes; i++){
        acc0.pushEventOperands(eops, i);
    }
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 165227391877138u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 16)) + 6 - 1);
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 6 - 1)));
    }
}
TEST_F(refill_TX, Basic_refill_TX_5){
    acc0.initSetup(0, "testprogs/binaries/refill_TX_5.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8228);
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
    for(auto i = 0; i < numLanes; i++){
        acc0.pushEventOperands(eops, i);
    }
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 4017218637210320899u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 19) + 1 - 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 1 - 0)));
    }
}
TEST_F(refill_TX, Basic_refill_TX_6){
    acc0.initSetup(0, "testprogs/binaries/refill_TX_6.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8228);
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
    for(auto i = 0; i < numLanes; i++){
        acc0.pushEventOperands(eops, i);
    }
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 17854671802479935512u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 19) + 8 - 2));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 8 - 2)));
    }
}
TEST_F(refill_TX, Basic_refill_TX_7){
    acc0.initSetup(0, "testprogs/binaries/refill_TX_7.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8228);
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
    for(auto i = 0; i < numLanes; i++){
        acc0.pushEventOperands(eops, i);
    }
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 2561008356298850328u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 19) + 8 - 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 8 - 0)));
    }
}
TEST_F(refill_TX, Basic_refill_TX_8){
    acc0.initSetup(0, "testprogs/binaries/refill_TX_8.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8228);
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
    for(auto i = 0; i < numLanes; i++){
        acc0.pushEventOperands(eops, i);
    }
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 8838304673757659154u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 19) + 6 - 2));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 6 - 2)));
    }
}
TEST_F(refill_TX, Basic_refill_TX_9){
    acc0.initSetup(0, "testprogs/binaries/refill_TX_9.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8228);
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
    for(auto i = 0; i < numLanes; i++){
        acc0.pushEventOperands(eops, i);
    }
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 6902012444693u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 16)) + 7 - 2);
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 7 - 2)));
    }
}
TEST_F(refill_TX, Basic_refill_TX_10){
    acc0.initSetup(0, "testprogs/binaries/refill_TX_10.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8228);
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
    for(auto i = 0; i < numLanes; i++){
        acc0.pushEventOperands(eops, i);
    }
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 17149938437382471695u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 16)) + 5 - 0);
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 5 - 0)));
    }
}
TEST_F(refill_TX, Basic_refill_TX_11){
    acc0.initSetup(0, "testprogs/binaries/refill_TX_11.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8228);
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
    for(auto i = 0; i < numLanes; i++){
        acc0.pushEventOperands(eops, i);
    }
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 296352743439u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 16)) + 5 - 1);
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 5 - 1)));
    }
}
TEST_F(refill_TX, Basic_refill_TX_12){
    acc0.initSetup(0, "testprogs/binaries/refill_TX_12.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8228);
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
    for(auto i = 0; i < numLanes; i++){
        acc0.pushEventOperands(eops, i);
    }
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 2114252455238696984u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 19) + 8 - 2));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 8 - 2)));
    }
}
TEST_F(refill_TX, Basic_refill_TX_13){
    acc0.initSetup(0, "testprogs/binaries/refill_TX_13.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8228);
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
    for(auto i = 0; i < numLanes; i++){
        acc0.pushEventOperands(eops, i);
    }
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 6800725790003560457u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 16)) + 3 - 0);
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 3 - 0)));
    }
}
TEST_F(refill_TX, Basic_refill_TX_14){
    acc0.initSetup(0, "testprogs/binaries/refill_TX_14.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8228);
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
    for(auto i = 0; i < numLanes; i++){
        acc0.pushEventOperands(eops, i);
    }
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 2866671059812220940u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 16)) + 4 - 1);
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 4 - 1)));
    }
}
TEST_F(refill_TX, Basic_refill_TX_15){
    acc0.initSetup(0, "testprogs/binaries/refill_TX_15.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8228);
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
    for(auto i = 0; i < numLanes; i++){
        acc0.pushEventOperands(eops, i);
    }
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 1853336142649229333u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 19) + 7 - 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 7 - 1)));
    }
}
TEST_F(refill_TX, Basic_refill_TX_16){
    acc0.initSetup(0, "testprogs/binaries/refill_TX_16.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8228);
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
    for(auto i = 0; i < numLanes; i++){
        acc0.pushEventOperands(eops, i);
    }
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 296352743439u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 16)) + 5 - 1);
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 5 - 1)));
    }
}
TEST_F(refill_TX, Basic_refill_TX_17){
    acc0.initSetup(0, "testprogs/binaries/refill_TX_17.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8228);
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
    for(auto i = 0; i < numLanes; i++){
        acc0.pushEventOperands(eops, i);
    }
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 17472281518268219416u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 19) + 8 - 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 8 - 1)));
    }
}
TEST_F(refill_TX, Basic_refill_TX_18){
    acc0.initSetup(0, "testprogs/binaries/refill_TX_18.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8228);
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
    for(auto i = 0; i < numLanes; i++){
        acc0.pushEventOperands(eops, i);
    }
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 124503504113893397u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 19) + 7 - 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 7 - 1)));
    }
}
TEST_F(refill_TX, Basic_refill_TX_19){
    acc0.initSetup(0, "testprogs/binaries/refill_TX_19.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8228);
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
    for(auto i = 0; i < numLanes; i++){
        acc0.pushEventOperands(eops, i);
    }
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 584115552280u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 16)) + 8 - 0);
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 8 - 0)));
    }
}
