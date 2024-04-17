#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"

using namespace basim;

class common_event_common_TX : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    int numLanes = 64;
    UDAccelerator acc0 = UDAccelerator(numLanes, 0, 1); // UDAccelerator(numLanes, UDID/networkID, lmmode (0: accelerator based addressing, 1:bank/lane based addressing))
    int buffsize1 = 1024;
    int buffsize2 = 1024;
};
TEST_F(common_event_common_TX, Basic_common_event_common_TX_0){
    acc0.initSetup(0, "testprogs/binaries/common_event_common_TX_0.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(72);
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
    eventword_t ev1(0);
    ev1.setEventLabel(400);
    ev1.setNumOperands(numop);
    eventoperands_t eops1(&ev1, &op0);
    for(auto i = 0; i < numLanes; i++){
        acc0.pushEventOperands(eops, i);
        acc0.pushEventOperands(eops1, i);
    }
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 2));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 6796167214794801161u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 16)) + 3);
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, ((i << 16) + 3)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 3)));
    }
}
TEST_F(common_event_common_TX, Basic_common_event_common_TX_1){
    acc0.initSetup(0, "testprogs/binaries/common_event_common_TX_1.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(72);
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
    eventword_t ev1(0);
    ev1.setEventLabel(400);
    ev1.setNumOperands(numop);
    eventoperands_t eops1(&ev1, &op0);
    for(auto i = 0; i < numLanes; i++){
        acc0.pushEventOperands(eops, i);
        acc0.pushEventOperands(eops1, i);
    }
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 2));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 11712472332697075736u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 19) + 8));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, ((i << 19) + 8)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 8)));
    }
}
TEST_F(common_event_common_TX, Basic_common_event_common_TX_2){
    acc0.initSetup(0, "testprogs/binaries/common_event_common_TX_2.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(72);
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
    eventword_t ev1(0);
    ev1.setEventLabel(400);
    ev1.setNumOperands(numop);
    eventoperands_t eops1(&ev1, &op0);
    for(auto i = 0; i < numLanes; i++){
        acc0.pushEventOperands(eops, i);
        acc0.pushEventOperands(eops1, i);
    }
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 2));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 11597347967710789656u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 16)) + 8);
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, ((i << 16) + 8)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 8)));
    }
}
TEST_F(common_event_common_TX, Basic_common_event_common_TX_3){
    acc0.initSetup(0, "testprogs/binaries/common_event_common_TX_3.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(72);
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
    eventword_t ev1(0);
    ev1.setEventLabel(400);
    ev1.setNumOperands(numop);
    eventoperands_t eops1(&ev1, &op0);
    for(auto i = 0; i < numLanes; i++){
        acc0.pushEventOperands(eops, i);
        acc0.pushEventOperands(eops1, i);
    }
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 2));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 5175373228754862104u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 16)) + 8);
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, ((i << 16) + 8)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 8)));
    }
}
TEST_F(common_event_common_TX, Basic_common_event_common_TX_4){
    acc0.initSetup(0, "testprogs/binaries/common_event_common_TX_4.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(72);
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
    eventword_t ev1(0);
    ev1.setEventLabel(400);
    ev1.setNumOperands(numop);
    eventoperands_t eops1(&ev1, &op0);
    for(auto i = 0; i < numLanes; i++){
        acc0.pushEventOperands(eops, i);
        acc0.pushEventOperands(eops1, i);
    }
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 2));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 10791851908185194502u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 16)) + 2);
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, ((i << 16) + 2)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 2)));
    }
}
TEST_F(common_event_common_TX, Basic_common_event_common_TX_5){
    acc0.initSetup(0, "testprogs/binaries/common_event_common_TX_5.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(72);
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
    eventword_t ev1(0);
    ev1.setEventLabel(400);
    ev1.setNumOperands(numop);
    eventoperands_t eops1(&ev1, &op0);
    for(auto i = 0; i < numLanes; i++){
        acc0.pushEventOperands(eops, i);
        acc0.pushEventOperands(eops1, i);
    }
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 2));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 15880070604007669772u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 16)) + 4);
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, ((i << 16) + 4)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 4)));
    }
}
TEST_F(common_event_common_TX, Basic_common_event_common_TX_6){
    acc0.initSetup(0, "testprogs/binaries/common_event_common_TX_6.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(72);
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
    eventword_t ev1(0);
    ev1.setEventLabel(400);
    ev1.setNumOperands(numop);
    eventoperands_t eops1(&ev1, &op0);
    for(auto i = 0; i < numLanes; i++){
        acc0.pushEventOperands(eops, i);
        acc0.pushEventOperands(eops1, i);
    }
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 2));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 432008314805551122u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 19) + 6));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, ((i << 19) + 6)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 6)));
    }
}
TEST_F(common_event_common_TX, Basic_common_event_common_TX_7){
    acc0.initSetup(0, "testprogs/binaries/common_event_common_TX_7.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(72);
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
    eventword_t ev1(0);
    ev1.setEventLabel(400);
    ev1.setNumOperands(numop);
    eventoperands_t eops1(&ev1, &op0);
    for(auto i = 0; i < numLanes; i++){
        acc0.pushEventOperands(eops, i);
        acc0.pushEventOperands(eops1, i);
    }
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 2));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 3577015374480146456u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 16)) + 8);
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, ((i << 16) + 8)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 8)));
    }
}
TEST_F(common_event_common_TX, Basic_common_event_common_TX_8){
    acc0.initSetup(0, "testprogs/binaries/common_event_common_TX_8.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(72);
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
    eventword_t ev1(0);
    ev1.setEventLabel(400);
    ev1.setNumOperands(numop);
    eventoperands_t eops1(&ev1, &op0);
    for(auto i = 0; i < numLanes; i++){
        acc0.pushEventOperands(eops, i);
        acc0.pushEventOperands(eops1, i);
    }
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 2));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 2210523563062984728u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 19) + 8));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, ((i << 19) + 8)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 8)));
    }
}
TEST_F(common_event_common_TX, Basic_common_event_common_TX_9){
    acc0.initSetup(0, "testprogs/binaries/common_event_common_TX_9.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(72);
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
    eventword_t ev1(0);
    ev1.setEventLabel(400);
    ev1.setNumOperands(numop);
    eventoperands_t eops1(&ev1, &op0);
    for(auto i = 0; i < numLanes; i++){
        acc0.pushEventOperands(eops, i);
        acc0.pushEventOperands(eops1, i);
    }
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 2));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 6121144543665455128u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 16)) + 8);
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, ((i << 16) + 8)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 8)));
    }
}
TEST_F(common_event_common_TX, Basic_common_event_common_TX_10){
    acc0.initSetup(0, "testprogs/binaries/common_event_common_TX_10.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(72);
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
    eventword_t ev1(0);
    ev1.setEventLabel(400);
    ev1.setNumOperands(numop);
    eventoperands_t eops1(&ev1, &op0);
    for(auto i = 0; i < numLanes; i++){
        acc0.pushEventOperands(eops, i);
        acc0.pushEventOperands(eops1, i);
    }
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 2));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 3058607590582779922u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 19) + 6));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, ((i << 19) + 6)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 6)));
    }
}
TEST_F(common_event_common_TX, Basic_common_event_common_TX_11){
    acc0.initSetup(0, "testprogs/binaries/common_event_common_TX_11.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(72);
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
    eventword_t ev1(0);
    ev1.setEventLabel(400);
    ev1.setNumOperands(numop);
    eventoperands_t eops1(&ev1, &op0);
    for(auto i = 0; i < numLanes; i++){
        acc0.pushEventOperands(eops, i);
        acc0.pushEventOperands(eops1, i);
    }
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 2));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 18276530362240729112u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 19) + 8));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, ((i << 19) + 8)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 8)));
    }
}
TEST_F(common_event_common_TX, Basic_common_event_common_TX_12){
    acc0.initSetup(0, "testprogs/binaries/common_event_common_TX_12.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(72);
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
    eventword_t ev1(0);
    ev1.setEventLabel(400);
    ev1.setNumOperands(numop);
    eventoperands_t eops1(&ev1, &op0);
    for(auto i = 0; i < numLanes; i++){
        acc0.pushEventOperands(eops, i);
        acc0.pushEventOperands(eops1, i);
    }
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 2));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 3386172711750336524u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 16)) + 4);
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, ((i << 16) + 4)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 4)));
    }
}
TEST_F(common_event_common_TX, Basic_common_event_common_TX_13){
    acc0.initSetup(0, "testprogs/binaries/common_event_common_TX_13.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(72);
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
    eventword_t ev1(0);
    ev1.setEventLabel(400);
    ev1.setNumOperands(numop);
    eventoperands_t eops1(&ev1, &op0);
    for(auto i = 0; i < numLanes; i++){
        acc0.pushEventOperands(eops, i);
        acc0.pushEventOperands(eops1, i);
    }
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 2));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 11348153411146088469u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 19) + 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, ((i << 19) + 7)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 7)));
    }
}
TEST_F(common_event_common_TX, Basic_common_event_common_TX_14){
    acc0.initSetup(0, "testprogs/binaries/common_event_common_TX_14.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(72);
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
    eventword_t ev1(0);
    ev1.setEventLabel(400);
    ev1.setNumOperands(numop);
    eventoperands_t eops1(&ev1, &op0);
    for(auto i = 0; i < numLanes; i++){
        acc0.pushEventOperands(eops, i);
        acc0.pushEventOperands(eops1, i);
    }
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 2));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 6453878258541789199u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 16)) + 5);
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, ((i << 16) + 5)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 5)));
    }
}
TEST_F(common_event_common_TX, Basic_common_event_common_TX_15){
    acc0.initSetup(0, "testprogs/binaries/common_event_common_TX_15.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(72);
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
    eventword_t ev1(0);
    ev1.setEventLabel(400);
    ev1.setNumOperands(numop);
    eventoperands_t eops1(&ev1, &op0);
    for(auto i = 0; i < numLanes; i++){
        acc0.pushEventOperands(eops, i);
        acc0.pushEventOperands(eops1, i);
    }
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 2));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 4126928070638567445u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 19) + 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, ((i << 19) + 7)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 7)));
    }
}
TEST_F(common_event_common_TX, Basic_common_event_common_TX_16){
    acc0.initSetup(0, "testprogs/binaries/common_event_common_TX_16.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(72);
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
    eventword_t ev1(0);
    ev1.setEventLabel(400);
    ev1.setNumOperands(numop);
    eventoperands_t eops1(&ev1, &op0);
    for(auto i = 0; i < numLanes; i++){
        acc0.pushEventOperands(eops, i);
        acc0.pushEventOperands(eops1, i);
    }
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 2));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 7814167720571699212u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 16)) + 4);
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, ((i << 16) + 4)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 4)));
    }
}
TEST_F(common_event_common_TX, Basic_common_event_common_TX_17){
    acc0.initSetup(0, "testprogs/binaries/common_event_common_TX_17.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(72);
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
    eventword_t ev1(0);
    ev1.setEventLabel(400);
    ev1.setNumOperands(numop);
    eventoperands_t eops1(&ev1, &op0);
    for(auto i = 0; i < numLanes; i++){
        acc0.pushEventOperands(eops, i);
        acc0.pushEventOperands(eops1, i);
    }
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 2));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 4914933618880544786u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 16)) + 6);
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, ((i << 16) + 6)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 6)));
    }
}
TEST_F(common_event_common_TX, Basic_common_event_common_TX_18){
    acc0.initSetup(0, "testprogs/binaries/common_event_common_TX_18.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(72);
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
    eventword_t ev1(0);
    ev1.setEventLabel(400);
    ev1.setNumOperands(numop);
    eventoperands_t eops1(&ev1, &op0);
    for(auto i = 0; i < numLanes; i++){
        acc0.pushEventOperands(eops, i);
        acc0.pushEventOperands(eops1, i);
    }
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 2));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 9949462393119571983u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 19) + 5));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, ((i << 19) + 5)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 5)));
    }
}
TEST_F(common_event_common_TX, Basic_common_event_common_TX_19){
    acc0.initSetup(0, "testprogs/binaries/common_event_common_TX_19.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(72);
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
    eventword_t ev1(0);
    ev1.setEventLabel(400);
    ev1.setNumOperands(numop);
    eventoperands_t eops1(&ev1, &op0);
    for(auto i = 0; i < numLanes; i++){
        acc0.pushEventOperands(eops, i);
        acc0.pushEventOperands(eops1, i);
    }
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 2));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 8794165878972219410u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 19) + 6));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, ((i << 19) + 6)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 6)));
    }
}
