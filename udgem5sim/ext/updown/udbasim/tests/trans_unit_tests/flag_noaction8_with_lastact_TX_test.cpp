#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"

using namespace basim;

class flag_noaction8_with_lastact_TX : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    int numLanes = 64;
    UDAccelerator acc0 = UDAccelerator(numLanes, 0, 1); // UDAccelerator(numLanes, UDID/networkID, lmmode (0: accelerator based addressing, 1:bank/lane based addressing))
    int buffsize1 = 1024;
    int buffsize2 = 1024;
};
TEST_F(flag_noaction8_with_lastact_TX, Basic_flag_noaction8_with_lastact_TX_0){
    acc0.initSetup(0, "testprogs/binaries/flag_noaction8_with_lastact_TX_0.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(26604);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 108));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 13));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 710451929368494092u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
TEST_F(flag_noaction8_with_lastact_TX, Basic_flag_noaction8_with_lastact_TX_1){
    acc0.initSetup(0, "testprogs/binaries/flag_noaction8_with_lastact_TX_1.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(26604);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 48));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 13));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 1585947816855863305u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 19))));
    }
}
TEST_F(flag_noaction8_with_lastact_TX, Basic_flag_noaction8_with_lastact_TX_2){
    acc0.initSetup(0, "testprogs/binaries/flag_noaction8_with_lastact_TX_2.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(26604);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 98));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 13));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 4705982493562503183u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
TEST_F(flag_noaction8_with_lastact_TX, Basic_flag_noaction8_with_lastact_TX_3){
    acc0.initSetup(0, "testprogs/binaries/flag_noaction8_with_lastact_TX_3.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(26604);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 150));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 13));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 14808271131722645513u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
TEST_F(flag_noaction8_with_lastact_TX, Basic_flag_noaction8_with_lastact_TX_4){
    acc0.initSetup(0, "testprogs/binaries/flag_noaction8_with_lastact_TX_4.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(26604);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 50));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 13));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 18445842555779153929u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
TEST_F(flag_noaction8_with_lastact_TX, Basic_flag_noaction8_with_lastact_TX_5){
    acc0.initSetup(0, "testprogs/binaries/flag_noaction8_with_lastact_TX_5.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(26604);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 13));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 15117964120877432847u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
TEST_F(flag_noaction8_with_lastact_TX, Basic_flag_noaction8_with_lastact_TX_6){
    acc0.initSetup(0, "testprogs/binaries/flag_noaction8_with_lastact_TX_6.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(26604);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 209));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 13));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 4238390241565605912u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 19))));
    }
}
TEST_F(flag_noaction8_with_lastact_TX, Basic_flag_noaction8_with_lastact_TX_7){
    acc0.initSetup(0, "testprogs/binaries/flag_noaction8_with_lastact_TX_7.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(26604);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 178));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 13));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 534470489138003980u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
TEST_F(flag_noaction8_with_lastact_TX, Basic_flag_noaction8_with_lastact_TX_8){
    acc0.initSetup(0, "testprogs/binaries/flag_noaction8_with_lastact_TX_8.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(26604);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 203));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 13));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 13971209845710258191u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 19))));
    }
}
TEST_F(flag_noaction8_with_lastact_TX, Basic_flag_noaction8_with_lastact_TX_9){
    acc0.initSetup(0, "testprogs/binaries/flag_noaction8_with_lastact_TX_9.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(26604);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 231));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 13));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 8220194416699113487u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 19))));
    }
}
TEST_F(flag_noaction8_with_lastact_TX, Basic_flag_noaction8_with_lastact_TX_10){
    acc0.initSetup(0, "testprogs/binaries/flag_noaction8_with_lastact_TX_10.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(26604);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 122));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 13));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 5696695169437401097u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
TEST_F(flag_noaction8_with_lastact_TX, Basic_flag_noaction8_with_lastact_TX_11){
    acc0.initSetup(0, "testprogs/binaries/flag_noaction8_with_lastact_TX_11.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(26604);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 88));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 13));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 9297206750920835096u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
TEST_F(flag_noaction8_with_lastact_TX, Basic_flag_noaction8_with_lastact_TX_12){
    acc0.initSetup(0, "testprogs/binaries/flag_noaction8_with_lastact_TX_12.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(26604);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 45));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 13));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 8752211611927707669u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
TEST_F(flag_noaction8_with_lastact_TX, Basic_flag_noaction8_with_lastact_TX_13){
    acc0.initSetup(0, "testprogs/binaries/flag_noaction8_with_lastact_TX_13.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(26604);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 33));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 13));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 13567219526721863701u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
TEST_F(flag_noaction8_with_lastact_TX, Basic_flag_noaction8_with_lastact_TX_14){
    acc0.initSetup(0, "testprogs/binaries/flag_noaction8_with_lastact_TX_14.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(26604);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 112));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 13));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 8515541927322451980u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
TEST_F(flag_noaction8_with_lastact_TX, Basic_flag_noaction8_with_lastact_TX_15){
    acc0.initSetup(0, "testprogs/binaries/flag_noaction8_with_lastact_TX_15.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(26604);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 55));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 13));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 8622620216540528661u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 19))));
    }
}
TEST_F(flag_noaction8_with_lastact_TX, Basic_flag_noaction8_with_lastact_TX_16){
    acc0.initSetup(0, "testprogs/binaries/flag_noaction8_with_lastact_TX_16.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(26604);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 13));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 39270449355423756u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
TEST_F(flag_noaction8_with_lastact_TX, Basic_flag_noaction8_with_lastact_TX_17){
    acc0.initSetup(0, "testprogs/binaries/flag_noaction8_with_lastact_TX_17.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(26604);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 71));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 13));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 16612384917640183811u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
TEST_F(flag_noaction8_with_lastact_TX, Basic_flag_noaction8_with_lastact_TX_18){
    acc0.initSetup(0, "testprogs/binaries/flag_noaction8_with_lastact_TX_18.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(26604);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 83));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 13));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 2712231887048278040u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
TEST_F(flag_noaction8_with_lastact_TX, Basic_flag_noaction8_with_lastact_TX_19){
    acc0.initSetup(0, "testprogs/binaries/flag_noaction8_with_lastact_TX_19.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(26604);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 18));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 13));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 6460901191495712789u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 19))));
    }
}
