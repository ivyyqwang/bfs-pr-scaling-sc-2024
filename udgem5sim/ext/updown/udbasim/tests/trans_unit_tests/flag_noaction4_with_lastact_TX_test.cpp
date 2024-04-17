#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"

using namespace basim;

class flag_noaction4_with_lastact_TX : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    int numLanes = 64;
    UDAccelerator acc0 = UDAccelerator(numLanes, 0, 1); // UDAccelerator(numLanes, UDID/networkID, lmmode (0: accelerator based addressing, 1:bank/lane based addressing))
    int buffsize1 = 1024;
    int buffsize2 = 1024;
};
TEST_F(flag_noaction4_with_lastact_TX, Basic_flag_noaction4_with_lastact_TX_0){
    acc0.initSetup(0, "testprogs/binaries/flag_noaction4_with_lastact_TX_0.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(14348);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 19));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 9));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 16710675171194699800u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
TEST_F(flag_noaction4_with_lastact_TX, Basic_flag_noaction4_with_lastact_TX_1){
    acc0.initSetup(0, "testprogs/binaries/flag_noaction4_with_lastact_TX_1.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(14348);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 242));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 9));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 2134566752900612117u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 19))));
    }
}
TEST_F(flag_noaction4_with_lastact_TX, Basic_flag_noaction4_with_lastact_TX_2){
    acc0.initSetup(0, "testprogs/binaries/flag_noaction4_with_lastact_TX_2.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(14348);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 41));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 9));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 7621104409426001935u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
TEST_F(flag_noaction4_with_lastact_TX, Basic_flag_noaction4_with_lastact_TX_3){
    acc0.initSetup(0, "testprogs/binaries/flag_noaction4_with_lastact_TX_3.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(14348);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 164));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 9));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 13633005502139990034u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
TEST_F(flag_noaction4_with_lastact_TX, Basic_flag_noaction4_with_lastact_TX_4){
    acc0.initSetup(0, "testprogs/binaries/flag_noaction4_with_lastact_TX_4.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(14348);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 125));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 9));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 3238062920621359110u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 19))));
    }
}
TEST_F(flag_noaction4_with_lastact_TX, Basic_flag_noaction4_with_lastact_TX_5){
    acc0.initSetup(0, "testprogs/binaries/flag_noaction4_with_lastact_TX_5.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(14348);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 37));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 9));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 13187175518719442956u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
TEST_F(flag_noaction4_with_lastact_TX, Basic_flag_noaction4_with_lastact_TX_6){
    acc0.initSetup(0, "testprogs/binaries/flag_noaction4_with_lastact_TX_6.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(14348);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 147));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 9));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 13807900702191648792u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
TEST_F(flag_noaction4_with_lastact_TX, Basic_flag_noaction4_with_lastact_TX_7){
    acc0.initSetup(0, "testprogs/binaries/flag_noaction4_with_lastact_TX_7.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(14348);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 76));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 9));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 14586510777545392143u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
TEST_F(flag_noaction4_with_lastact_TX, Basic_flag_noaction4_with_lastact_TX_8){
    acc0.initSetup(0, "testprogs/binaries/flag_noaction4_with_lastact_TX_8.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(14348);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 117));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 9));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 14344225706668458008u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 19))));
    }
}
TEST_F(flag_noaction4_with_lastact_TX, Basic_flag_noaction4_with_lastact_TX_9){
    acc0.initSetup(0, "testprogs/binaries/flag_noaction4_with_lastact_TX_9.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(14348);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 103));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 9));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 16808390551966580757u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
TEST_F(flag_noaction4_with_lastact_TX, Basic_flag_noaction4_with_lastact_TX_10){
    acc0.initSetup(0, "testprogs/binaries/flag_noaction4_with_lastact_TX_10.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(14348);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 73));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 9));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 5933301352951185423u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
TEST_F(flag_noaction4_with_lastact_TX, Basic_flag_noaction4_with_lastact_TX_11){
    acc0.initSetup(0, "testprogs/binaries/flag_noaction4_with_lastact_TX_11.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(14348);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 230));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 9));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 7971753382081724437u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 19))));
    }
}
TEST_F(flag_noaction4_with_lastact_TX, Basic_flag_noaction4_with_lastact_TX_12){
    acc0.initSetup(0, "testprogs/binaries/flag_noaction4_with_lastact_TX_12.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(14348);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 184));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 9));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 13775399890093867029u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 19))));
    }
}
TEST_F(flag_noaction4_with_lastact_TX, Basic_flag_noaction4_with_lastact_TX_13){
    acc0.initSetup(0, "testprogs/binaries/flag_noaction4_with_lastact_TX_13.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(14348);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 176));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 9));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 12285405705669705746u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 19))));
    }
}
TEST_F(flag_noaction4_with_lastact_TX, Basic_flag_noaction4_with_lastact_TX_14){
    acc0.initSetup(0, "testprogs/binaries/flag_noaction4_with_lastact_TX_14.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(14348);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 86));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 9));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 16605973076928102424u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
TEST_F(flag_noaction4_with_lastact_TX, Basic_flag_noaction4_with_lastact_TX_15){
    acc0.initSetup(0, "testprogs/binaries/flag_noaction4_with_lastact_TX_15.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(14348);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 227));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 9));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 17998453975971528728u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
TEST_F(flag_noaction4_with_lastact_TX, Basic_flag_noaction4_with_lastact_TX_16){
    acc0.initSetup(0, "testprogs/binaries/flag_noaction4_with_lastact_TX_16.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(14348);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 109));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 9));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 3146975413121581077u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 19))));
    }
}
TEST_F(flag_noaction4_with_lastact_TX, Basic_flag_noaction4_with_lastact_TX_17){
    acc0.initSetup(0, "testprogs/binaries/flag_noaction4_with_lastact_TX_17.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(14348);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 76));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 9));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 18368403973309726744u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
TEST_F(flag_noaction4_with_lastact_TX, Basic_flag_noaction4_with_lastact_TX_18){
    acc0.initSetup(0, "testprogs/binaries/flag_noaction4_with_lastact_TX_18.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(14348);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 65));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 9));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 17518138484655652873u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
TEST_F(flag_noaction4_with_lastact_TX, Basic_flag_noaction4_with_lastact_TX_19){
    acc0.initSetup(0, "testprogs/binaries/flag_noaction4_with_lastact_TX_19.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(14348);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 241));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 9));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 1249404234059743256u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
