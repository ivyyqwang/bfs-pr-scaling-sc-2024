#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"

using namespace basim;

class common_event_common_TX_maxSBP : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    int numLanes = 64;
    UDAccelerator acc0 = UDAccelerator(numLanes, 0, 1); // UDAccelerator(numLanes, UDID/networkID, lmmode (0: accelerator based addressing, 1:bank/lane based addressing))
    int buffsize1 = 1024;
    int buffsize2 = 1024;
};
TEST_F(common_event_common_TX_maxSBP, Basic_common_event_common_TX_maxSBP_0){
    acc0.initSetup(0, "testprogs/binaries/common_event_common_TX_maxSBP_0.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 2));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 15423318291120128015u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X20, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 16)) + 5);
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, ((i << 16) + 5)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 5)));
    }
}
TEST_F(common_event_common_TX_maxSBP, Basic_common_event_common_TX_maxSBP_1){
    acc0.initSetup(0, "testprogs/binaries/common_event_common_TX_maxSBP_1.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 2));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 18346268661053915151u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X20, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 16)) + 5);
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, ((i << 16) + 5)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 5)));
    }
}
TEST_F(common_event_common_TX_maxSBP, Basic_common_event_common_TX_maxSBP_2){
    acc0.initSetup(0, "testprogs/binaries/common_event_common_TX_maxSBP_2.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 2));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 12719490624277970959u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X20, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 19) + 5));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, ((i << 19) + 5)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 5)));
    }
}
TEST_F(common_event_common_TX_maxSBP, Basic_common_event_common_TX_maxSBP_3){
    acc0.initSetup(0, "testprogs/binaries/common_event_common_TX_maxSBP_3.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 2));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 16205200813725843480u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X20, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 16)) + 8);
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, ((i << 16) + 8)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 8)));
    }
}
TEST_F(common_event_common_TX_maxSBP, Basic_common_event_common_TX_maxSBP_4){
    acc0.initSetup(0, "testprogs/binaries/common_event_common_TX_maxSBP_4.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 2));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 13649252757830369283u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X20, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 19) + 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, ((i << 19) + 1)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 1)));
    }
}
TEST_F(common_event_common_TX_maxSBP, Basic_common_event_common_TX_maxSBP_5){
    acc0.initSetup(0, "testprogs/binaries/common_event_common_TX_maxSBP_5.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 2));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 13736431205140660245u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X20, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 19) + 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, ((i << 19) + 7)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 7)));
    }
}
TEST_F(common_event_common_TX_maxSBP, Basic_common_event_common_TX_maxSBP_6){
    acc0.initSetup(0, "testprogs/binaries/common_event_common_TX_maxSBP_6.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 2));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 17340348575430737944u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X20, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 19) + 8));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, ((i << 19) + 8)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 8)));
    }
}
TEST_F(common_event_common_TX_maxSBP, Basic_common_event_common_TX_maxSBP_7){
    acc0.initSetup(0, "testprogs/binaries/common_event_common_TX_maxSBP_7.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 2));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 8262052751354101772u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X20, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 19) + 4));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, ((i << 19) + 4)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 4)));
    }
}
TEST_F(common_event_common_TX_maxSBP, Basic_common_event_common_TX_maxSBP_8){
    acc0.initSetup(0, "testprogs/binaries/common_event_common_TX_maxSBP_8.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 2));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 4634625224006959122u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X20, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 19) + 6));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, ((i << 19) + 6)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 6)));
    }
}
TEST_F(common_event_common_TX_maxSBP, Basic_common_event_common_TX_maxSBP_9){
    acc0.initSetup(0, "testprogs/binaries/common_event_common_TX_maxSBP_9.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 2));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 17415566290440945679u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X20, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 19) + 5));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, ((i << 19) + 5)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 5)));
    }
}
TEST_F(common_event_common_TX_maxSBP, Basic_common_event_common_TX_maxSBP_10){
    acc0.initSetup(0, "testprogs/binaries/common_event_common_TX_maxSBP_10.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 2));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 16568688126529110019u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X20, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 16)) + 1);
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, ((i << 16) + 1)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 1)));
    }
}
TEST_F(common_event_common_TX_maxSBP, Basic_common_event_common_TX_maxSBP_11){
    acc0.initSetup(0, "testprogs/binaries/common_event_common_TX_maxSBP_11.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 2));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 9131993098644094997u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X20, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 19) + 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, ((i << 19) + 7)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 7)));
    }
}
TEST_F(common_event_common_TX_maxSBP, Basic_common_event_common_TX_maxSBP_12){
    acc0.initSetup(0, "testprogs/binaries/common_event_common_TX_maxSBP_12.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 2));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 14042065892582359064u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X20, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 16)) + 8);
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, ((i << 16) + 8)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 8)));
    }
}
TEST_F(common_event_common_TX_maxSBP, Basic_common_event_common_TX_maxSBP_13){
    acc0.initSetup(0, "testprogs/binaries/common_event_common_TX_maxSBP_13.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 2));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 4520436539120943119u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X20, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 19) + 5));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, ((i << 19) + 5)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 5)));
    }
}
TEST_F(common_event_common_TX_maxSBP, Basic_common_event_common_TX_maxSBP_14){
    acc0.initSetup(0, "testprogs/binaries/common_event_common_TX_maxSBP_14.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 2));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 6428835103102730261u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X20, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 19) + 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, ((i << 19) + 7)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 7)));
    }
}
TEST_F(common_event_common_TX_maxSBP, Basic_common_event_common_TX_maxSBP_15){
    acc0.initSetup(0, "testprogs/binaries/common_event_common_TX_maxSBP_15.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 2));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 14134907481905692693u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X20, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 19) + 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, ((i << 19) + 7)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 7)));
    }
}
TEST_F(common_event_common_TX_maxSBP, Basic_common_event_common_TX_maxSBP_16){
    acc0.initSetup(0, "testprogs/binaries/common_event_common_TX_maxSBP_16.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 2));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 7625976770650439704u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X20, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 19) + 8));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, ((i << 19) + 8)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 8)));
    }
}
TEST_F(common_event_common_TX_maxSBP, Basic_common_event_common_TX_maxSBP_17){
    acc0.initSetup(0, "testprogs/binaries/common_event_common_TX_maxSBP_17.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 2));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 5101715845298520088u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X20, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 19) + 8));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, ((i << 19) + 8)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 8)));
    }
}
TEST_F(common_event_common_TX_maxSBP, Basic_common_event_common_TX_maxSBP_18){
    acc0.initSetup(0, "testprogs/binaries/common_event_common_TX_maxSBP_18.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 2));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 2918672891744616472u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X20, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 19) + 8));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, ((i << 19) + 8)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 8)));
    }
}
TEST_F(common_event_common_TX_maxSBP, Basic_common_event_common_TX_maxSBP_19){
    acc0.initSetup(0, "testprogs/binaries/common_event_common_TX_maxSBP_19.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 2));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 1812209726256054287u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X20, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, (i << 19) + 5));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, ((i << 19) + 5)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 5)));
    }
}
