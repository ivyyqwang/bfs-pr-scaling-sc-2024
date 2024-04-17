#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"

using namespace basim;

class epsilon_noaction_TX : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    int numLanes = 64;
    UDAccelerator acc0 = UDAccelerator(numLanes, 0, 1); // UDAccelerator(numLanes, UDID/networkID, lmmode (0: accelerator based addressing, 1:bank/lane based addressing))
    int buffsize1 = 1024;
    int buffsize2 = 1024;
};
TEST_F(epsilon_noaction_TX, Basic_epsilon_noaction_TX_0){
    acc0.initSetup(0, "testprogs/binaries/epsilon_noaction_TX_0.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(60);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 4));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 11136966635091394578u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
    }
}
TEST_F(epsilon_noaction_TX, Basic_epsilon_noaction_TX_1){
    acc0.initSetup(0, "testprogs/binaries/epsilon_noaction_TX_1.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(60);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 4));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 11786024833052049420u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
    }
}
TEST_F(epsilon_noaction_TX, Basic_epsilon_noaction_TX_2){
    acc0.initSetup(0, "testprogs/binaries/epsilon_noaction_TX_2.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(60);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 4));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 8378077689377980431u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
    }
}
TEST_F(epsilon_noaction_TX, Basic_epsilon_noaction_TX_3){
    acc0.initSetup(0, "testprogs/binaries/epsilon_noaction_TX_3.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(60);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 4));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 7659492079793340437u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
    }
}
TEST_F(epsilon_noaction_TX, Basic_epsilon_noaction_TX_4){
    acc0.initSetup(0, "testprogs/binaries/epsilon_noaction_TX_4.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(60);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 4));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 969363020511707160u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
    }
}
TEST_F(epsilon_noaction_TX, Basic_epsilon_noaction_TX_5){
    acc0.initSetup(0, "testprogs/binaries/epsilon_noaction_TX_5.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(60);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 4));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 6902444904929034246u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
    }
}
TEST_F(epsilon_noaction_TX, Basic_epsilon_noaction_TX_6){
    acc0.initSetup(0, "testprogs/binaries/epsilon_noaction_TX_6.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(60);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 4));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 1498225639570800664u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
    }
}
TEST_F(epsilon_noaction_TX, Basic_epsilon_noaction_TX_7){
    acc0.initSetup(0, "testprogs/binaries/epsilon_noaction_TX_7.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(60);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 4));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 6480793624584912917u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
    }
}
TEST_F(epsilon_noaction_TX, Basic_epsilon_noaction_TX_8){
    acc0.initSetup(0, "testprogs/binaries/epsilon_noaction_TX_8.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(60);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 4));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 5967314070846570520u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
    }
}
TEST_F(epsilon_noaction_TX, Basic_epsilon_noaction_TX_9){
    acc0.initSetup(0, "testprogs/binaries/epsilon_noaction_TX_9.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(60);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 4));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 6095710159655403544u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
    }
}
TEST_F(epsilon_noaction_TX, Basic_epsilon_noaction_TX_10){
    acc0.initSetup(0, "testprogs/binaries/epsilon_noaction_TX_10.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(60);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 4));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 11421363297664892952u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
    }
}
TEST_F(epsilon_noaction_TX, Basic_epsilon_noaction_TX_11){
    acc0.initSetup(0, "testprogs/binaries/epsilon_noaction_TX_11.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(60);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 4));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 17356510206653104137u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
    }
}
TEST_F(epsilon_noaction_TX, Basic_epsilon_noaction_TX_12){
    acc0.initSetup(0, "testprogs/binaries/epsilon_noaction_TX_12.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(60);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 4));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 1577894327974101016u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
    }
}
TEST_F(epsilon_noaction_TX, Basic_epsilon_noaction_TX_13){
    acc0.initSetup(0, "testprogs/binaries/epsilon_noaction_TX_13.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(60);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 4));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 4023238553566707730u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
    }
}
TEST_F(epsilon_noaction_TX, Basic_epsilon_noaction_TX_14){
    acc0.initSetup(0, "testprogs/binaries/epsilon_noaction_TX_14.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(60);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 4));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 5473041323093131282u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
    }
}
TEST_F(epsilon_noaction_TX, Basic_epsilon_noaction_TX_15){
    acc0.initSetup(0, "testprogs/binaries/epsilon_noaction_TX_15.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(60);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 4));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 11396020366393475087u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
    }
}
TEST_F(epsilon_noaction_TX, Basic_epsilon_noaction_TX_16){
    acc0.initSetup(0, "testprogs/binaries/epsilon_noaction_TX_16.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(60);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 4));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 15730907918825947160u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
    }
}
TEST_F(epsilon_noaction_TX, Basic_epsilon_noaction_TX_17){
    acc0.initSetup(0, "testprogs/binaries/epsilon_noaction_TX_17.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(60);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 4));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 5490455452678357007u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
    }
}
TEST_F(epsilon_noaction_TX, Basic_epsilon_noaction_TX_18){
    acc0.initSetup(0, "testprogs/binaries/epsilon_noaction_TX_18.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(60);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 4));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 16553077479481278476u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, ((i << 16))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
    }
}
TEST_F(epsilon_noaction_TX, Basic_epsilon_noaction_TX_19){
    acc0.initSetup(0, "testprogs/binaries/epsilon_noaction_TX_19.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(60);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 4));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 8678752488456716312u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, ((i << 19))));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
    }
}
