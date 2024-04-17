#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"

using namespace basim;

class basic_action4_with_lastact_TX_maxSBP : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    int numLanes = 64;
    UDAccelerator acc0 = UDAccelerator(numLanes, 0, 1); // UDAccelerator(numLanes, UDID/networkID, lmmode (0: accelerator based addressing, 1:bank/lane based addressing))
    int buffsize1 = 1024;
    int buffsize2 = 1024;
};
TEST_F(basic_action4_with_lastact_TX_maxSBP, Basic_basic_action4_with_lastact_TX_maxSBP_0){
    acc0.initSetup(0, "testprogs/binaries/basic_action4_with_lastact_TX_maxSBP_0.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8232);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 14999134208432013320u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 8)));
    }
}
TEST_F(basic_action4_with_lastact_TX_maxSBP, Basic_basic_action4_with_lastact_TX_maxSBP_1){
    acc0.initSetup(0, "testprogs/binaries/basic_action4_with_lastact_TX_maxSBP_1.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8232);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 346582854102155269u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 5)));
    }
}
TEST_F(basic_action4_with_lastact_TX_maxSBP, Basic_basic_action4_with_lastact_TX_maxSBP_2){
    acc0.initSetup(0, "testprogs/binaries/basic_action4_with_lastact_TX_maxSBP_2.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8232);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 6336547182308491271u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 7)));
    }
}
TEST_F(basic_action4_with_lastact_TX_maxSBP, Basic_basic_action4_with_lastact_TX_maxSBP_3){
    acc0.initSetup(0, "testprogs/binaries/basic_action4_with_lastact_TX_maxSBP_3.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8232);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 17041504527636758532u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 4)));
    }
}
TEST_F(basic_action4_with_lastact_TX_maxSBP, Basic_basic_action4_with_lastact_TX_maxSBP_4){
    acc0.initSetup(0, "testprogs/binaries/basic_action4_with_lastact_TX_maxSBP_4.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8232);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 16536828016177709063u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 7)));
    }
}
TEST_F(basic_action4_with_lastact_TX_maxSBP, Basic_basic_action4_with_lastact_TX_maxSBP_5){
    acc0.initSetup(0, "testprogs/binaries/basic_action4_with_lastact_TX_maxSBP_5.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8232);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 6062697451880448006u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 6)));
    }
}
TEST_F(basic_action4_with_lastact_TX_maxSBP, Basic_basic_action4_with_lastact_TX_maxSBP_6){
    acc0.initSetup(0, "testprogs/binaries/basic_action4_with_lastact_TX_maxSBP_6.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8232);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 9840355659567071238u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 6)));
    }
}
TEST_F(basic_action4_with_lastact_TX_maxSBP, Basic_basic_action4_with_lastact_TX_maxSBP_7){
    acc0.initSetup(0, "testprogs/binaries/basic_action4_with_lastact_TX_maxSBP_7.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8232);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 9519744807711277063u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 7)));
    }
}
TEST_F(basic_action4_with_lastact_TX_maxSBP, Basic_basic_action4_with_lastact_TX_maxSBP_8){
    acc0.initSetup(0, "testprogs/binaries/basic_action4_with_lastact_TX_maxSBP_8.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8232);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 57251733667053574u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 6)));
    }
}
TEST_F(basic_action4_with_lastact_TX_maxSBP, Basic_basic_action4_with_lastact_TX_maxSBP_9){
    acc0.initSetup(0, "testprogs/binaries/basic_action4_with_lastact_TX_maxSBP_9.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8232);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 292057776132u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 4)));
    }
}
TEST_F(basic_action4_with_lastact_TX_maxSBP, Basic_basic_action4_with_lastact_TX_maxSBP_10){
    acc0.initSetup(0, "testprogs/binaries/basic_action4_with_lastact_TX_maxSBP_10.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8232);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 17554818192558260227u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 3)));
    }
}
TEST_F(basic_action4_with_lastact_TX_maxSBP, Basic_basic_action4_with_lastact_TX_maxSBP_11){
    acc0.initSetup(0, "testprogs/binaries/basic_action4_with_lastact_TX_maxSBP_11.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8232);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 4022912204771688454u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 6)));
    }
}
TEST_F(basic_action4_with_lastact_TX_maxSBP, Basic_basic_action4_with_lastact_TX_maxSBP_12){
    acc0.initSetup(0, "testprogs/binaries/basic_action4_with_lastact_TX_maxSBP_12.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8232);
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
TEST_F(basic_action4_with_lastact_TX_maxSBP, Basic_basic_action4_with_lastact_TX_maxSBP_13){
    acc0.initSetup(0, "testprogs/binaries/basic_action4_with_lastact_TX_maxSBP_13.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8232);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 7044717474725494792u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 8)));
    }
}
TEST_F(basic_action4_with_lastact_TX_maxSBP, Basic_basic_action4_with_lastact_TX_maxSBP_14){
    acc0.initSetup(0, "testprogs/binaries/basic_action4_with_lastact_TX_maxSBP_14.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8232);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 9650348840422735876u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 4)));
    }
}
TEST_F(basic_action4_with_lastact_TX_maxSBP, Basic_basic_action4_with_lastact_TX_maxSBP_15){
    acc0.initSetup(0, "testprogs/binaries/basic_action4_with_lastact_TX_maxSBP_15.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8232);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 45913707200380934u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 6)));
    }
}
TEST_F(basic_action4_with_lastact_TX_maxSBP, Basic_basic_action4_with_lastact_TX_maxSBP_16){
    acc0.initSetup(0, "testprogs/binaries/basic_action4_with_lastact_TX_maxSBP_16.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8232);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 3960009071532179461u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 5)));
    }
}
TEST_F(basic_action4_with_lastact_TX_maxSBP, Basic_basic_action4_with_lastact_TX_maxSBP_17){
    acc0.initSetup(0, "testprogs/binaries/basic_action4_with_lastact_TX_maxSBP_17.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8232);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 2162002857958572037u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 5)));
    }
}
TEST_F(basic_action4_with_lastact_TX_maxSBP, Basic_basic_action4_with_lastact_TX_maxSBP_18){
    acc0.initSetup(0, "testprogs/binaries/basic_action4_with_lastact_TX_maxSBP_18.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8232);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 11385192375883137029u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 5)));
    }
}
TEST_F(basic_action4_with_lastact_TX_maxSBP, Basic_basic_action4_with_lastact_TX_maxSBP_19){
    acc0.initSetup(0, "testprogs/binaries/basic_action4_with_lastact_TX_maxSBP_19.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(8232);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 6177295429969903623u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 7)));
    }
}
