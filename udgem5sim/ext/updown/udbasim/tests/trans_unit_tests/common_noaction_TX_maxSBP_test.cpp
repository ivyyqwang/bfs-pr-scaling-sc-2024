#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"

using namespace basim;

class common_noaction_TX_maxSBP : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    int numLanes = 64;
    UDAccelerator acc0 = UDAccelerator(numLanes, 0, 1); // UDAccelerator(numLanes, UDID/networkID, lmmode (0: accelerator based addressing, 1:bank/lane based addressing))
    int buffsize1 = 1024;
    int buffsize2 = 1024;
};
TEST_F(common_noaction_TX_maxSBP, Basic_common_noaction_TX_maxSBP_0){
    acc0.initSetup(0, "testprogs/binaries/common_noaction_TX_maxSBP_0.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(44);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X4,  13402198503728349192u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5, ((i << 16) + 8)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
    }
}
TEST_F(common_noaction_TX_maxSBP, Basic_common_noaction_TX_maxSBP_1){
    acc0.initSetup(0, "testprogs/binaries/common_noaction_TX_maxSBP_1.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(44);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 5324823934443454472u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5, (i << 19) + 8));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
    }
}
TEST_F(common_noaction_TX_maxSBP, Basic_common_noaction_TX_maxSBP_2){
    acc0.initSetup(0, "testprogs/binaries/common_noaction_TX_maxSBP_2.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(44);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X4,  15623820833514848261u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5, ((i << 16) + 5)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
    }
}
TEST_F(common_noaction_TX_maxSBP, Basic_common_noaction_TX_maxSBP_3){
    acc0.initSetup(0, "testprogs/binaries/common_noaction_TX_maxSBP_3.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(44);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 3867806148140728323u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5, (i << 19) + 3));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
    }
}
TEST_F(common_noaction_TX_maxSBP, Basic_common_noaction_TX_maxSBP_4){
    acc0.initSetup(0, "testprogs/binaries/common_noaction_TX_maxSBP_4.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(44);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 18148043421988683783u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5, (i << 19) + 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
    }
}
TEST_F(common_noaction_TX_maxSBP, Basic_common_noaction_TX_maxSBP_5){
    acc0.initSetup(0, "testprogs/binaries/common_noaction_TX_maxSBP_5.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(44);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 4118481901486866440u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5, (i << 19) + 8));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
    }
}
TEST_F(common_noaction_TX_maxSBP, Basic_common_noaction_TX_maxSBP_6){
    acc0.initSetup(0, "testprogs/binaries/common_noaction_TX_maxSBP_6.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(44);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X4,  1413728016357392388u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5, ((i << 16) + 4)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
    }
}
TEST_F(common_noaction_TX_maxSBP, Basic_common_noaction_TX_maxSBP_7){
    acc0.initSetup(0, "testprogs/binaries/common_noaction_TX_maxSBP_7.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(44);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X4,  18249386718685822984u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5, ((i << 16) + 8)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
    }
}
TEST_F(common_noaction_TX_maxSBP, Basic_common_noaction_TX_maxSBP_8){
    acc0.initSetup(0, "testprogs/binaries/common_noaction_TX_maxSBP_8.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(44);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X4,  10019420740287201284u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5, ((i << 16) + 4)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
    }
}
TEST_F(common_noaction_TX_maxSBP, Basic_common_noaction_TX_maxSBP_9){
    acc0.initSetup(0, "testprogs/binaries/common_noaction_TX_maxSBP_9.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(44);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X4,  10912580642852044807u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5, ((i << 16) + 7)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
    }
}
TEST_F(common_noaction_TX_maxSBP, Basic_common_noaction_TX_maxSBP_10){
    acc0.initSetup(0, "testprogs/binaries/common_noaction_TX_maxSBP_10.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(44);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 6695954649842712583u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5, (i << 19) + 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
    }
}
TEST_F(common_noaction_TX_maxSBP, Basic_common_noaction_TX_maxSBP_11){
    acc0.initSetup(0, "testprogs/binaries/common_noaction_TX_maxSBP_11.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(44);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 2939664342540353541u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5, (i << 19) + 5));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
    }
}
TEST_F(common_noaction_TX_maxSBP, Basic_common_noaction_TX_maxSBP_12){
    acc0.initSetup(0, "testprogs/binaries/common_noaction_TX_maxSBP_12.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(44);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 8564926500673945606u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5, (i << 19) + 6));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
    }
}
TEST_F(common_noaction_TX_maxSBP, Basic_common_noaction_TX_maxSBP_13){
    acc0.initSetup(0, "testprogs/binaries/common_noaction_TX_maxSBP_13.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(44);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 14398557176106844167u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5, (i << 19) + 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
    }
}
TEST_F(common_noaction_TX_maxSBP, Basic_common_noaction_TX_maxSBP_14){
    acc0.initSetup(0, "testprogs/binaries/common_noaction_TX_maxSBP_14.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(44);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 8672935792772907015u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5, (i << 19) + 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
    }
}
TEST_F(common_noaction_TX_maxSBP, Basic_common_noaction_TX_maxSBP_15){
    acc0.initSetup(0, "testprogs/binaries/common_noaction_TX_maxSBP_15.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(44);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X4,  2203491816836169730u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5, ((i << 16) + 2)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
    }
}
TEST_F(common_noaction_TX_maxSBP, Basic_common_noaction_TX_maxSBP_16){
    acc0.initSetup(0, "testprogs/binaries/common_noaction_TX_maxSBP_16.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(44);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 5740212821757526022u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5, (i << 19) + 6));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
    }
}
TEST_F(common_noaction_TX_maxSBP, Basic_common_noaction_TX_maxSBP_17){
    acc0.initSetup(0, "testprogs/binaries/common_noaction_TX_maxSBP_17.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(44);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X4,  12932781526285811719u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5, ((i << 16) + 7)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
    }
}
TEST_F(common_noaction_TX_maxSBP, Basic_common_noaction_TX_maxSBP_18){
    acc0.initSetup(0, "testprogs/binaries/common_noaction_TX_maxSBP_18.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(44);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X4,  6627959540816019462u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5, ((i << 16) + 6)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
    }
}
TEST_F(common_noaction_TX_maxSBP, Basic_common_noaction_TX_maxSBP_19){
    acc0.initSetup(0, "testprogs/binaries/common_noaction_TX_maxSBP_19.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(44);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X4,  10877730307549691909u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5, ((i << 16) + 5)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
    }
}
