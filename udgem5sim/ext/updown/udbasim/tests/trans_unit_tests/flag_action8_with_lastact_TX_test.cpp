#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"

using namespace basim;

class flag_action8_with_lastact_TX : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    int numLanes = 64;
    UDAccelerator acc0 = UDAccelerator(numLanes, 0, 1); // UDAccelerator(numLanes, UDID/networkID, lmmode (0: accelerator based addressing, 1:bank/lane based addressing))
    int buffsize1 = 1024;
    int buffsize2 = 1024;
};
TEST_F(flag_action8_with_lastact_TX, Basic_flag_action8_with_lastact_TX_0){
    acc0.initSetup(0, "testprogs/binaries/flag_action8_with_lastact_TX_0.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 54));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 13));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 18159220168138424344u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
TEST_F(flag_action8_with_lastact_TX, Basic_flag_action8_with_lastact_TX_1){
    acc0.initSetup(0, "testprogs/binaries/flag_action8_with_lastact_TX_1.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 16803129736720023576u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 19))));
    }
}
TEST_F(flag_action8_with_lastact_TX, Basic_flag_action8_with_lastact_TX_2){
    acc0.initSetup(0, "testprogs/binaries/flag_action8_with_lastact_TX_2.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 205));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 13));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 10272428416061931544u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 19))));
    }
}
TEST_F(flag_action8_with_lastact_TX, Basic_flag_action8_with_lastact_TX_3){
    acc0.initSetup(0, "testprogs/binaries/flag_action8_with_lastact_TX_3.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 157));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 13));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 6097444351485411343u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 19))));
    }
}
TEST_F(flag_action8_with_lastact_TX, Basic_flag_action8_with_lastact_TX_4){
    acc0.initSetup(0, "testprogs/binaries/flag_action8_with_lastact_TX_4.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 251));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 13));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 6589527284393181205u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
TEST_F(flag_action8_with_lastact_TX, Basic_flag_action8_with_lastact_TX_5){
    acc0.initSetup(0, "testprogs/binaries/flag_action8_with_lastact_TX_5.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 189));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 13));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 12276429163891523608u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 19))));
    }
}
TEST_F(flag_action8_with_lastact_TX, Basic_flag_action8_with_lastact_TX_6){
    acc0.initSetup(0, "testprogs/binaries/flag_action8_with_lastact_TX_6.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 242));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 13));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 17392426857781002252u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
TEST_F(flag_action8_with_lastact_TX, Basic_flag_action8_with_lastact_TX_7){
    acc0.initSetup(0, "testprogs/binaries/flag_action8_with_lastact_TX_7.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 100));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 13));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 6494610985347711000u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
TEST_F(flag_action8_with_lastact_TX, Basic_flag_action8_with_lastact_TX_8){
    acc0.initSetup(0, "testprogs/binaries/flag_action8_with_lastact_TX_8.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 7774514263212687384u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 19))));
    }
}
TEST_F(flag_action8_with_lastact_TX, Basic_flag_action8_with_lastact_TX_9){
    acc0.initSetup(0, "testprogs/binaries/flag_action8_with_lastact_TX_9.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 96));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 13));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 4034263777565212696u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 19))));
    }
}
TEST_F(flag_action8_with_lastact_TX, Basic_flag_action8_with_lastact_TX_10){
    acc0.initSetup(0, "testprogs/binaries/flag_action8_with_lastact_TX_10.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 77));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 13));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 16114858341318000664u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
TEST_F(flag_action8_with_lastact_TX, Basic_flag_action8_with_lastact_TX_11){
    acc0.initSetup(0, "testprogs/binaries/flag_action8_with_lastact_TX_11.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 47));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 13));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 3227670560053919762u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 19))));
    }
}
TEST_F(flag_action8_with_lastact_TX, Basic_flag_action8_with_lastact_TX_12){
    acc0.initSetup(0, "testprogs/binaries/flag_action8_with_lastact_TX_12.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 238));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 13));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 9451724624665509912u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 19))));
    }
}
TEST_F(flag_action8_with_lastact_TX, Basic_flag_action8_with_lastact_TX_13){
    acc0.initSetup(0, "testprogs/binaries/flag_action8_with_lastact_TX_13.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 25));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 13));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 5532612111466758165u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 19))));
    }
}
TEST_F(flag_action8_with_lastact_TX, Basic_flag_action8_with_lastact_TX_14){
    acc0.initSetup(0, "testprogs/binaries/flag_action8_with_lastact_TX_14.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 19));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 13));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 4744981075783057426u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 19))));
    }
}
TEST_F(flag_action8_with_lastact_TX, Basic_flag_action8_with_lastact_TX_15){
    acc0.initSetup(0, "testprogs/binaries/flag_action8_with_lastact_TX_15.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 227));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 13));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 10812427296909033493u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 19))));
    }
}
TEST_F(flag_action8_with_lastact_TX, Basic_flag_action8_with_lastact_TX_16){
    acc0.initSetup(0, "testprogs/binaries/flag_action8_with_lastact_TX_16.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 17));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 13));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 2687806906252132364u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
TEST_F(flag_action8_with_lastact_TX, Basic_flag_action8_with_lastact_TX_17){
    acc0.initSetup(0, "testprogs/binaries/flag_action8_with_lastact_TX_17.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 23));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 13));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 15289595974712819736u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
TEST_F(flag_action8_with_lastact_TX, Basic_flag_action8_with_lastact_TX_18){
    acc0.initSetup(0, "testprogs/binaries/flag_action8_with_lastact_TX_18.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 223));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 13));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 12249937595156398101u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 19))));
    }
}
TEST_F(flag_action8_with_lastact_TX, Basic_flag_action8_with_lastact_TX_19){
    acc0.initSetup(0, "testprogs/binaries/flag_action8_with_lastact_TX_19.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 101));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 13));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 17907488750485635084u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
