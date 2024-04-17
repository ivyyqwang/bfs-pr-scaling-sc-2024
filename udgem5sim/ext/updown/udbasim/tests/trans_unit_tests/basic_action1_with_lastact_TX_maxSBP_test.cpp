#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"

using namespace basim;

class basic_action1_with_lastact_TX_maxSBP : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    int numLanes = 64;
    UDAccelerator acc0 = UDAccelerator(numLanes, 0, 1); // UDAccelerator(numLanes, UDID/networkID, lmmode (0: accelerator based addressing, 1:bank/lane based addressing))
    int buffsize1 = 1024;
    int buffsize2 = 1024;
};
TEST_F(basic_action1_with_lastact_TX_maxSBP, Basic_basic_action1_with_lastact_TX_maxSBP_0){
    acc0.initSetup(0, "testprogs/binaries/basic_action1_with_lastact_TX_maxSBP_0.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(5160);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 13890578122559979525u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 5)));
    }
}
TEST_F(basic_action1_with_lastact_TX_maxSBP, Basic_basic_action1_with_lastact_TX_maxSBP_1){
    acc0.initSetup(0, "testprogs/binaries/basic_action1_with_lastact_TX_maxSBP_1.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(5160);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 191611375976453u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 5)));
    }
}
TEST_F(basic_action1_with_lastact_TX_maxSBP, Basic_basic_action1_with_lastact_TX_maxSBP_2){
    acc0.initSetup(0, "testprogs/binaries/basic_action1_with_lastact_TX_maxSBP_2.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(5160);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 5001112511336939525u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 5)));
    }
}
TEST_F(basic_action1_with_lastact_TX_maxSBP, Basic_basic_action1_with_lastact_TX_maxSBP_3){
    acc0.initSetup(0, "testprogs/binaries/basic_action1_with_lastact_TX_maxSBP_3.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(5160);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 132237748076549u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 5)));
    }
}
TEST_F(basic_action1_with_lastact_TX_maxSBP, Basic_basic_action1_with_lastact_TX_maxSBP_4){
    acc0.initSetup(0, "testprogs/binaries/basic_action1_with_lastact_TX_maxSBP_4.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(5160);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 11978233690518978564u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 4)));
    }
}
TEST_F(basic_action1_with_lastact_TX_maxSBP, Basic_basic_action1_with_lastact_TX_maxSBP_5){
    acc0.initSetup(0, "testprogs/binaries/basic_action1_with_lastact_TX_maxSBP_5.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(5160);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 12418194480870457350u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 6)));
    }
}
TEST_F(basic_action1_with_lastact_TX_maxSBP, Basic_basic_action1_with_lastact_TX_maxSBP_6){
    acc0.initSetup(0, "testprogs/binaries/basic_action1_with_lastact_TX_maxSBP_6.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(5160);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 15392427387383709704u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 8)));
    }
}
TEST_F(basic_action1_with_lastact_TX_maxSBP, Basic_basic_action1_with_lastact_TX_maxSBP_7){
    acc0.initSetup(0, "testprogs/binaries/basic_action1_with_lastact_TX_maxSBP_7.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(5160);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 10134664956335882245u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 5)));
    }
}
TEST_F(basic_action1_with_lastact_TX_maxSBP, Basic_basic_action1_with_lastact_TX_maxSBP_8){
    acc0.initSetup(0, "testprogs/binaries/basic_action1_with_lastact_TX_maxSBP_8.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(5160);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 8767303560070168579u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 3)));
    }
}
TEST_F(basic_action1_with_lastact_TX_maxSBP, Basic_basic_action1_with_lastact_TX_maxSBP_9){
    acc0.initSetup(0, "testprogs/binaries/basic_action1_with_lastact_TX_maxSBP_9.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(5160);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 15726430415419867140u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 4)));
    }
}
TEST_F(basic_action1_with_lastact_TX_maxSBP, Basic_basic_action1_with_lastact_TX_maxSBP_10){
    acc0.initSetup(0, "testprogs/binaries/basic_action1_with_lastact_TX_maxSBP_10.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(5160);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 7854293302210723845u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 5)));
    }
}
TEST_F(basic_action1_with_lastact_TX_maxSBP, Basic_basic_action1_with_lastact_TX_maxSBP_11){
    acc0.initSetup(0, "testprogs/binaries/basic_action1_with_lastact_TX_maxSBP_11.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(5160);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 8004416230410682375u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 7)));
    }
}
TEST_F(basic_action1_with_lastact_TX_maxSBP, Basic_basic_action1_with_lastact_TX_maxSBP_12){
    acc0.initSetup(0, "testprogs/binaries/basic_action1_with_lastact_TX_maxSBP_12.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(5160);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 9141215656148992005u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 5)));
    }
}
TEST_F(basic_action1_with_lastact_TX_maxSBP, Basic_basic_action1_with_lastact_TX_maxSBP_13){
    acc0.initSetup(0, "testprogs/binaries/basic_action1_with_lastact_TX_maxSBP_13.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(5160);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 6274518371266461703u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 7)));
    }
}
TEST_F(basic_action1_with_lastact_TX_maxSBP, Basic_basic_action1_with_lastact_TX_maxSBP_14){
    acc0.initSetup(0, "testprogs/binaries/basic_action1_with_lastact_TX_maxSBP_14.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(5160);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 15203366706585010184u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 8)));
    }
}
TEST_F(basic_action1_with_lastact_TX_maxSBP, Basic_basic_action1_with_lastact_TX_maxSBP_15){
    acc0.initSetup(0, "testprogs/binaries/basic_action1_with_lastact_TX_maxSBP_15.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(5160);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 584115552264u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 8)));
    }
}
TEST_F(basic_action1_with_lastact_TX_maxSBP, Basic_basic_action1_with_lastact_TX_maxSBP_16){
    acc0.initSetup(0, "testprogs/binaries/basic_action1_with_lastact_TX_maxSBP_16.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(5160);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 9418145256085389318u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 6)));
    }
}
TEST_F(basic_action1_with_lastact_TX_maxSBP, Basic_basic_action1_with_lastact_TX_maxSBP_17){
    acc0.initSetup(0, "testprogs/binaries/basic_action1_with_lastact_TX_maxSBP_17.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(5160);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 11821724811669798917u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 5)));
    }
}
TEST_F(basic_action1_with_lastact_TX_maxSBP, Basic_basic_action1_with_lastact_TX_maxSBP_18){
    acc0.initSetup(0, "testprogs/binaries/basic_action1_with_lastact_TX_maxSBP_18.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(5160);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 864818830717747205u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 5)));
    }
}
TEST_F(basic_action1_with_lastact_TX_maxSBP, Basic_basic_action1_with_lastact_TX_maxSBP_19){
    acc0.initSetup(0, "testprogs/binaries/basic_action1_with_lastact_TX_maxSBP_19.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(5160);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 1050613558255026183u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 7)));
    }
}
