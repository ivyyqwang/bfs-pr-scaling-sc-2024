#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"

using namespace basim;

class flag_action2_with_lastact_TX : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    int numLanes = 64;
    UDAccelerator acc0 = UDAccelerator(numLanes, 0, 1); // UDAccelerator(numLanes, UDID/networkID, lmmode (0: accelerator based addressing, 1:bank/lane based addressing))
    int buffsize1 = 1024;
    int buffsize2 = 1024;
};
TEST_F(flag_action2_with_lastact_TX, Basic_flag_action2_with_lastact_TX_0){
    acc0.initSetup(0, "testprogs/binaries/flag_action2_with_lastact_TX_0.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8220);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 145));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 7269892903428685836u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 19))));
    }
}
TEST_F(flag_action2_with_lastact_TX, Basic_flag_action2_with_lastact_TX_1){
    acc0.initSetup(0, "testprogs/binaries/flag_action2_with_lastact_TX_1.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8220);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 12));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 7946309162596565007u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
TEST_F(flag_action2_with_lastact_TX, Basic_flag_action2_with_lastact_TX_2){
    acc0.initSetup(0, "testprogs/binaries/flag_action2_with_lastact_TX_2.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8220);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 99));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 11654646396262285330u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 19))));
    }
}
TEST_F(flag_action2_with_lastact_TX, Basic_flag_action2_with_lastact_TX_3){
    acc0.initSetup(0, "testprogs/binaries/flag_action2_with_lastact_TX_3.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8220);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 128));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 5277415187782041621u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 19))));
    }
}
TEST_F(flag_action2_with_lastact_TX, Basic_flag_action2_with_lastact_TX_4){
    acc0.initSetup(0, "testprogs/binaries/flag_action2_with_lastact_TX_4.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8220);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 188));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 15560586962023743506u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 19))));
    }
}
TEST_F(flag_action2_with_lastact_TX, Basic_flag_action2_with_lastact_TX_5){
    acc0.initSetup(0, "testprogs/binaries/flag_action2_with_lastact_TX_5.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8220);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 245));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 8602205244845195288u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
TEST_F(flag_action2_with_lastact_TX, Basic_flag_action2_with_lastact_TX_6){
    acc0.initSetup(0, "testprogs/binaries/flag_action2_with_lastact_TX_6.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8220);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 129));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 14785203811563601944u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
TEST_F(flag_action2_with_lastact_TX, Basic_flag_action2_with_lastact_TX_7){
    acc0.initSetup(0, "testprogs/binaries/flag_action2_with_lastact_TX_7.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8220);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 84));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 10840437136583294988u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
TEST_F(flag_action2_with_lastact_TX, Basic_flag_action2_with_lastact_TX_8){
    acc0.initSetup(0, "testprogs/binaries/flag_action2_with_lastact_TX_8.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8220);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 124));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 6454262482021122072u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 19))));
    }
}
TEST_F(flag_action2_with_lastact_TX, Basic_flag_action2_with_lastact_TX_9){
    acc0.initSetup(0, "testprogs/binaries/flag_action2_with_lastact_TX_9.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8220);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 221));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 3366150605008535564u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
TEST_F(flag_action2_with_lastact_TX, Basic_flag_action2_with_lastact_TX_10){
    acc0.initSetup(0, "testprogs/binaries/flag_action2_with_lastact_TX_10.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8220);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 198));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 262697822074175509u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
TEST_F(flag_action2_with_lastact_TX, Basic_flag_action2_with_lastact_TX_11){
    acc0.initSetup(0, "testprogs/binaries/flag_action2_with_lastact_TX_11.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8220);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 8));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 3002470860490539029u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 19))));
    }
}
TEST_F(flag_action2_with_lastact_TX, Basic_flag_action2_with_lastact_TX_12){
    acc0.initSetup(0, "testprogs/binaries/flag_action2_with_lastact_TX_12.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8220);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 87));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 7664899477978742805u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 19))));
    }
}
TEST_F(flag_action2_with_lastact_TX, Basic_flag_action2_with_lastact_TX_13){
    acc0.initSetup(0, "testprogs/binaries/flag_action2_with_lastact_TX_13.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8220);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 57));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 5687131020298551320u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 19))));
    }
}
TEST_F(flag_action2_with_lastact_TX, Basic_flag_action2_with_lastact_TX_14){
    acc0.initSetup(0, "testprogs/binaries/flag_action2_with_lastact_TX_14.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8220);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 12));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 6314281041053876245u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 19))));
    }
}
TEST_F(flag_action2_with_lastact_TX, Basic_flag_action2_with_lastact_TX_15){
    acc0.initSetup(0, "testprogs/binaries/flag_action2_with_lastact_TX_15.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8220);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 23));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 16295925770151264274u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
TEST_F(flag_action2_with_lastact_TX, Basic_flag_action2_with_lastact_TX_16){
    acc0.initSetup(0, "testprogs/binaries/flag_action2_with_lastact_TX_16.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8220);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 22));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 14524438797787070470u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
TEST_F(flag_action2_with_lastact_TX, Basic_flag_action2_with_lastact_TX_17){
    acc0.initSetup(0, "testprogs/binaries/flag_action2_with_lastact_TX_17.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8220);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 253));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 15011500613278105618u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
TEST_F(flag_action2_with_lastact_TX, Basic_flag_action2_with_lastact_TX_18){
    acc0.initSetup(0, "testprogs/binaries/flag_action2_with_lastact_TX_18.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8220);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 62));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 18056964418524151832u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 19))));
    }
}
TEST_F(flag_action2_with_lastact_TX, Basic_flag_action2_with_lastact_TX_19){
    acc0.initSetup(0, "testprogs/binaries/flag_action2_with_lastact_TX_19.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8220);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 187));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 436749327340142601u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 19))));
    }
}
