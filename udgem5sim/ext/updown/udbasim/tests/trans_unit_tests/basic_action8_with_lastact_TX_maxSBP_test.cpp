#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"

using namespace basim;

class basic_action8_with_lastact_TX_maxSBP : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    int numLanes = 64;
    UDAccelerator acc0 = UDAccelerator(numLanes, 0, 1); // UDAccelerator(numLanes, UDID/networkID, lmmode (0: accelerator based addressing, 1:bank/lane based addressing))
    int buffsize1 = 1024;
    int buffsize2 = 1024;
};
TEST_F(basic_action8_with_lastact_TX_maxSBP, Basic_basic_action8_with_lastact_TX_maxSBP_0){
    acc0.initSetup(0, "testprogs/binaries/basic_action8_with_lastact_TX_maxSBP_0.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(12328);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 15731428799574704133u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 5)));
    }
}
TEST_F(basic_action8_with_lastact_TX_maxSBP, Basic_basic_action8_with_lastact_TX_maxSBP_1){
    acc0.initSetup(0, "testprogs/binaries/basic_action8_with_lastact_TX_maxSBP_1.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(12328);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 584115552264u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 8)));
    }
}
TEST_F(basic_action8_with_lastact_TX_maxSBP, Basic_basic_action8_with_lastact_TX_maxSBP_2){
    acc0.initSetup(0, "testprogs/binaries/basic_action8_with_lastact_TX_maxSBP_2.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(12328);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 18104463101800742917u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 5)));
    }
}
TEST_F(basic_action8_with_lastact_TX_maxSBP, Basic_basic_action8_with_lastact_TX_maxSBP_3){
    acc0.initSetup(0, "testprogs/binaries/basic_action8_with_lastact_TX_maxSBP_3.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(12328);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 7539238424344002567u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 7)));
    }
}
TEST_F(basic_action8_with_lastact_TX_maxSBP, Basic_basic_action8_with_lastact_TX_maxSBP_4){
    acc0.initSetup(0, "testprogs/binaries/basic_action8_with_lastact_TX_maxSBP_4.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(12328);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 2464595050697326596u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 4)));
    }
}
TEST_F(basic_action8_with_lastact_TX_maxSBP, Basic_basic_action8_with_lastact_TX_maxSBP_5){
    acc0.initSetup(0, "testprogs/binaries/basic_action8_with_lastact_TX_maxSBP_5.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(12328);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 584115552264u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 8)));
    }
}
TEST_F(basic_action8_with_lastact_TX_maxSBP, Basic_basic_action8_with_lastact_TX_maxSBP_6){
    acc0.initSetup(0, "testprogs/binaries/basic_action8_with_lastact_TX_maxSBP_6.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(12328);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 584115552264u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 8)));
    }
}
TEST_F(basic_action8_with_lastact_TX_maxSBP, Basic_basic_action8_with_lastact_TX_maxSBP_7){
    acc0.initSetup(0, "testprogs/binaries/basic_action8_with_lastact_TX_maxSBP_7.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(12328);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 3325008134027608072u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 8)));
    }
}
TEST_F(basic_action8_with_lastact_TX_maxSBP, Basic_basic_action8_with_lastact_TX_maxSBP_8){
    acc0.initSetup(0, "testprogs/binaries/basic_action8_with_lastact_TX_maxSBP_8.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(12328);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 584115552264u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 8)));
    }
}
TEST_F(basic_action8_with_lastact_TX_maxSBP, Basic_basic_action8_with_lastact_TX_maxSBP_9){
    acc0.initSetup(0, "testprogs/binaries/basic_action8_with_lastact_TX_maxSBP_9.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(12328);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 14196088706921660423u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 7)));
    }
}
TEST_F(basic_action8_with_lastact_TX_maxSBP, Basic_basic_action8_with_lastact_TX_maxSBP_10){
    acc0.initSetup(0, "testprogs/binaries/basic_action8_with_lastact_TX_maxSBP_10.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(12328);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 9071595602080432131u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 3)));
    }
}
TEST_F(basic_action8_with_lastact_TX_maxSBP, Basic_basic_action8_with_lastact_TX_maxSBP_11){
    acc0.initSetup(0, "testprogs/binaries/basic_action8_with_lastact_TX_maxSBP_11.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(12328);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 408701820802695172u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 4)));
    }
}
TEST_F(basic_action8_with_lastact_TX_maxSBP, Basic_basic_action8_with_lastact_TX_maxSBP_12){
    acc0.initSetup(0, "testprogs/binaries/basic_action8_with_lastact_TX_maxSBP_12.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(12328);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 292057776132u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 4)));
    }
}
TEST_F(basic_action8_with_lastact_TX_maxSBP, Basic_basic_action8_with_lastact_TX_maxSBP_13){
    acc0.initSetup(0, "testprogs/binaries/basic_action8_with_lastact_TX_maxSBP_13.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(12328);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 7275127076993105928u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 8)));
    }
}
TEST_F(basic_action8_with_lastact_TX_maxSBP, Basic_basic_action8_with_lastact_TX_maxSBP_14){
    acc0.initSetup(0, "testprogs/binaries/basic_action8_with_lastact_TX_maxSBP_14.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(12328);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 8554685791106760711u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 7)));
    }
}
TEST_F(basic_action8_with_lastact_TX_maxSBP, Basic_basic_action8_with_lastact_TX_maxSBP_15){
    acc0.initSetup(0, "testprogs/binaries/basic_action8_with_lastact_TX_maxSBP_15.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(12328);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 584115552264u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 8)));
    }
}
TEST_F(basic_action8_with_lastact_TX_maxSBP, Basic_basic_action8_with_lastact_TX_maxSBP_16){
    acc0.initSetup(0, "testprogs/binaries/basic_action8_with_lastact_TX_maxSBP_16.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(12328);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 88257282965509u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 5)));
    }
}
TEST_F(basic_action8_with_lastact_TX_maxSBP, Basic_basic_action8_with_lastact_TX_maxSBP_17){
    acc0.initSetup(0, "testprogs/binaries/basic_action8_with_lastact_TX_maxSBP_17.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(12328);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 7703120774197936136u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 8)));
    }
}
TEST_F(basic_action8_with_lastact_TX_maxSBP, Basic_basic_action8_with_lastact_TX_maxSBP_18){
    acc0.initSetup(0, "testprogs/binaries/basic_action8_with_lastact_TX_maxSBP_18.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(12328);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 2577052077784039430u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 6)));
    }
}
TEST_F(basic_action8_with_lastact_TX_maxSBP, Basic_basic_action8_with_lastact_TX_maxSBP_19){
    acc0.initSetup(0, "testprogs/binaries/basic_action8_with_lastact_TX_maxSBP_19.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(12328);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 6655776094077059080u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 8)));
    }
}
