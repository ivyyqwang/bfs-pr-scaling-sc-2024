#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"

using namespace basim;

class refill_noaction_TX : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    int numLanes = 64;
    UDAccelerator acc0 = UDAccelerator(numLanes, 0, 1); // UDAccelerator(numLanes, UDID/networkID, lmmode (0: accelerator based addressing, 1:bank/lane based addressing))
    int buffsize1 = 1024;
    int buffsize2 = 1024;
};
TEST_F(refill_noaction_TX, Basic_refill_noaction_TX_0){
    acc0.initSetup(0, "testprogs/binaries/refill_noaction_TX_0.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(7204);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 584115552280u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 16)) + 8 - 0);
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 8 - 0)));
    }
}
TEST_F(refill_noaction_TX, Basic_refill_noaction_TX_1){
    acc0.initSetup(0, "testprogs/binaries/refill_noaction_TX_1.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(7204);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 12375778964403126290u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 19) + 6 - 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 6 - 0)));
    }
}
TEST_F(refill_noaction_TX, Basic_refill_noaction_TX_2){
    acc0.initSetup(0, "testprogs/binaries/refill_noaction_TX_2.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(7204);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 5596843450457653269u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 19) + 7 - 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 7 - 0)));
    }
}
TEST_F(refill_noaction_TX, Basic_refill_noaction_TX_3){
    acc0.initSetup(0, "testprogs/binaries/refill_noaction_TX_3.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(7204);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 584115552280u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 16)) + 8 - 0);
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 8 - 0)));
    }
}
TEST_F(refill_noaction_TX, Basic_refill_noaction_TX_4){
    acc0.initSetup(0, "testprogs/binaries/refill_noaction_TX_4.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(7204);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 627875530925932568u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 19) + 8 - 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 8 - 1)));
    }
}
TEST_F(refill_noaction_TX, Basic_refill_noaction_TX_5){
    acc0.initSetup(0, "testprogs/binaries/refill_noaction_TX_5.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(7204);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 11795044058215219212u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 16)) + 4 - 1);
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 4 - 1)));
    }
}
TEST_F(refill_noaction_TX, Basic_refill_noaction_TX_6){
    acc0.initSetup(0, "testprogs/binaries/refill_noaction_TX_6.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(7204);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 584115552280u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 16)) + 8 - 0);
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 8 - 0)));
    }
}
TEST_F(refill_noaction_TX, Basic_refill_noaction_TX_7){
    acc0.initSetup(0, "testprogs/binaries/refill_noaction_TX_7.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(7204);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 12325082338672246802u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 19) + 6 - 3));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 6 - 3)));
    }
}
TEST_F(refill_noaction_TX, Basic_refill_noaction_TX_8){
    acc0.initSetup(0, "testprogs/binaries/refill_noaction_TX_8.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(7204);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 9720129337289605126u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 16)) + 2 - 0);
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 2 - 0)));
    }
}
TEST_F(refill_noaction_TX, Basic_refill_noaction_TX_9){
    acc0.initSetup(0, "testprogs/binaries/refill_noaction_TX_9.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(7204);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 15879647790247182360u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 19) + 8 - 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 8 - 0)));
    }
}
TEST_F(refill_noaction_TX, Basic_refill_noaction_TX_10){
    acc0.initSetup(0, "testprogs/binaries/refill_noaction_TX_10.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(7204);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 2809880270625308696u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 19) + 8 - 3));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 8 - 3)));
    }
}
TEST_F(refill_noaction_TX, Basic_refill_noaction_TX_11){
    acc0.initSetup(0, "testprogs/binaries/refill_noaction_TX_11.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(7204);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 292057776140u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 16)) + 4 - 0);
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 4 - 0)));
    }
}
TEST_F(refill_noaction_TX, Basic_refill_noaction_TX_12){
    acc0.initSetup(0, "testprogs/binaries/refill_noaction_TX_12.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(7204);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 2041121737852059672u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 19) + 8 - 2));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 8 - 2)));
    }
}
TEST_F(refill_noaction_TX, Basic_refill_noaction_TX_13){
    acc0.initSetup(0, "testprogs/binaries/refill_noaction_TX_13.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(7204);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 3635818287125757976u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 19) + 8 - 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 8 - 0)));
    }
}
TEST_F(refill_noaction_TX, Basic_refill_noaction_TX_14){
    acc0.initSetup(0, "testprogs/binaries/refill_noaction_TX_14.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(7204);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 9246171681767030808u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 16)) + 8 - 4);
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 8 - 4)));
    }
}
TEST_F(refill_noaction_TX, Basic_refill_noaction_TX_15){
    acc0.initSetup(0, "testprogs/binaries/refill_noaction_TX_15.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(7204);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 292057776140u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 16)) + 4 - 0);
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 4 - 0)));
    }
}
TEST_F(refill_noaction_TX, Basic_refill_noaction_TX_16){
    acc0.initSetup(0, "testprogs/binaries/refill_noaction_TX_16.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(7204);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 8847853781921038345u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 16)) + 3 - 1);
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 3 - 1)));
    }
}
TEST_F(refill_noaction_TX, Basic_refill_noaction_TX_17){
    acc0.initSetup(0, "testprogs/binaries/refill_noaction_TX_17.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(7204);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 584115552280u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 16)) + 8 - 0);
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 8 - 0)));
    }
}
TEST_F(refill_noaction_TX, Basic_refill_noaction_TX_18){
    acc0.initSetup(0, "testprogs/binaries/refill_noaction_TX_18.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(7204);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 309237645336u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 16)) + 8 - 4);
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 8 - 4)));
    }
}
TEST_F(refill_noaction_TX, Basic_refill_noaction_TX_19){
    acc0.initSetup(0, "testprogs/binaries/refill_noaction_TX_19.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(7204);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 584115552280u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 16)) + 8 - 0);
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 8 - 0)));
    }
}
