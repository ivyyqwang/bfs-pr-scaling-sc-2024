#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"

using namespace basim;

class flag_action4_with_lastact_TX : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    int numLanes = 64;
    UDAccelerator acc0 = UDAccelerator(numLanes, 0, 1); // UDAccelerator(numLanes, UDID/networkID, lmmode (0: accelerator based addressing, 1:bank/lane based addressing))
    int buffsize1 = 1024;
    int buffsize2 = 1024;
};
TEST_F(flag_action4_with_lastact_TX, Basic_flag_action4_with_lastact_TX_0){
    acc0.initSetup(0, "testprogs/binaries/flag_action4_with_lastact_TX_0.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 91));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 9));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 17255732428299829272u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 19))));
    }
}
TEST_F(flag_action4_with_lastact_TX, Basic_flag_action4_with_lastact_TX_1){
    acc0.initSetup(0, "testprogs/binaries/flag_action4_with_lastact_TX_1.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 108));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 9));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 1622455047461797903u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
TEST_F(flag_action4_with_lastact_TX, Basic_flag_action4_with_lastact_TX_2){
    acc0.initSetup(0, "testprogs/binaries/flag_action4_with_lastact_TX_2.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 133));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 9));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 9159300633856049170u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 19))));
    }
}
TEST_F(flag_action4_with_lastact_TX, Basic_flag_action4_with_lastact_TX_3){
    acc0.initSetup(0, "testprogs/binaries/flag_action4_with_lastact_TX_3.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 112));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 9));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 14762678932889141266u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
TEST_F(flag_action4_with_lastact_TX, Basic_flag_action4_with_lastact_TX_4){
    acc0.initSetup(0, "testprogs/binaries/flag_action4_with_lastact_TX_4.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 56));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 9));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 9159916287353159695u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 19))));
    }
}
TEST_F(flag_action4_with_lastact_TX, Basic_flag_action4_with_lastact_TX_5){
    acc0.initSetup(0, "testprogs/binaries/flag_action4_with_lastact_TX_5.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 190));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 9));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 840432839634714645u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 19))));
    }
}
TEST_F(flag_action4_with_lastact_TX, Basic_flag_action4_with_lastact_TX_6){
    acc0.initSetup(0, "testprogs/binaries/flag_action4_with_lastact_TX_6.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 136));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 9));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 7534781747234340876u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
TEST_F(flag_action4_with_lastact_TX, Basic_flag_action4_with_lastact_TX_7){
    acc0.initSetup(0, "testprogs/binaries/flag_action4_with_lastact_TX_7.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 253));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 9));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 2006802380766576646u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
TEST_F(flag_action4_with_lastact_TX, Basic_flag_action4_with_lastact_TX_8){
    acc0.initSetup(0, "testprogs/binaries/flag_action4_with_lastact_TX_8.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 4));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 9));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 1168410565425496088u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 19))));
    }
}
TEST_F(flag_action4_with_lastact_TX, Basic_flag_action4_with_lastact_TX_9){
    acc0.initSetup(0, "testprogs/binaries/flag_action4_with_lastact_TX_9.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 188));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 9));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 13413077071773564952u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
TEST_F(flag_action4_with_lastact_TX, Basic_flag_action4_with_lastact_TX_10){
    acc0.initSetup(0, "testprogs/binaries/flag_action4_with_lastact_TX_10.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 249));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 9));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 3129407343318532114u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 19))));
    }
}
TEST_F(flag_action4_with_lastact_TX, Basic_flag_action4_with_lastact_TX_11){
    acc0.initSetup(0, "testprogs/binaries/flag_action4_with_lastact_TX_11.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 165));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 9));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 9555113481141747730u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 19))));
    }
}
TEST_F(flag_action4_with_lastact_TX, Basic_flag_action4_with_lastact_TX_12){
    acc0.initSetup(0, "testprogs/binaries/flag_action4_with_lastact_TX_12.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 204));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 9));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 8478705143875895320u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 19))));
    }
}
TEST_F(flag_action4_with_lastact_TX, Basic_flag_action4_with_lastact_TX_13){
    acc0.initSetup(0, "testprogs/binaries/flag_action4_with_lastact_TX_13.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 44));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 9));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 4891764718449983512u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
TEST_F(flag_action4_with_lastact_TX, Basic_flag_action4_with_lastact_TX_14){
    acc0.initSetup(0, "testprogs/binaries/flag_action4_with_lastact_TX_14.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 72));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 9));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 10958887515653668870u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
TEST_F(flag_action4_with_lastact_TX, Basic_flag_action4_with_lastact_TX_15){
    acc0.initSetup(0, "testprogs/binaries/flag_action4_with_lastact_TX_15.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 157));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 9));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 8732620500859093004u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
TEST_F(flag_action4_with_lastact_TX, Basic_flag_action4_with_lastact_TX_16){
    acc0.initSetup(0, "testprogs/binaries/flag_action4_with_lastact_TX_16.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 9456246696947220495u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
TEST_F(flag_action4_with_lastact_TX, Basic_flag_action4_with_lastact_TX_17){
    acc0.initSetup(0, "testprogs/binaries/flag_action4_with_lastact_TX_17.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 199));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 9));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 8238717678638858252u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 16))));
    }
}
TEST_F(flag_action4_with_lastact_TX, Basic_flag_action4_with_lastact_TX_18){
    acc0.initSetup(0, "testprogs/binaries/flag_action4_with_lastact_TX_18.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 112));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 9));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 18323859939769974808u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 19))));
    }
}
TEST_F(flag_action4_with_lastact_TX, Basic_flag_action4_with_lastact_TX_19){
    acc0.initSetup(0, "testprogs/binaries/flag_action4_with_lastact_TX_19.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 100));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 9));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 14360714116182573077u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17,  ((i << 19))));
    }
}
