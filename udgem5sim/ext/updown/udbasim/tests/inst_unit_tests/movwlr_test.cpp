#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"

using namespace basim;

class movwlr : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    int numLanes = 64;
    UDAccelerator acc0 = UDAccelerator(numLanes, 0, 1); // UDAccelerator(numLanes, UDID/networkID, lmmode (0: accelerator based addressing, 1:bank/lane based addressing))
    int buffsize1 = 1024;
    int buffsize2 = 1024;
};
TEST_F(movwlr, Basic_movwlr_0){
    acc0.initSetup(0, "testprogs/binaries/movwlr_0.bin", 0);
    int numop = 9;
    eventword_t ev0(0);
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
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 11973560148295466053u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 130u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, 90u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, 90u+0));
        EXPECT_TRUE(acc0.testMem((i << 16) + 23170, 11973560148295466053u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X20, 11973560148295466053u));
    }
}
TEST_F(movwlr, Basic_movwlr_1){
    acc0.initSetup(0, "testprogs/binaries/movwlr_1.bin", 0);
    int numop = 9;
    eventword_t ev0(0);
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
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 4960293681250408536u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 249u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, 196u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, 196u+1));
        EXPECT_TRUE(acc0.testMem((i << 16) + 50425, 4960293681250408536u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X20, 4960293681250408536u));
    }
}
TEST_F(movwlr, Basic_movwlr_2){
    acc0.initSetup(0, "testprogs/binaries/movwlr_2.bin", 0);
    int numop = 9;
    eventword_t ev0(0);
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
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 8974961704524099644u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 863u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, 34u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, 34u+1));
        EXPECT_TRUE(acc0.testMem((i << 16) + 35679, 8974961704524099644u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X20, 8974961704524099644u));
    }
}
TEST_F(movwlr, Basic_movwlr_3){
    acc0.initSetup(0, "testprogs/binaries/movwlr_3.bin", 0);
    int numop = 9;
    eventword_t ev0(0);
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
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 17462675375398326116u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 39u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, 904u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, 904u+1));
        EXPECT_TRUE(acc0.testMem((i << 16) + 57895, 17462675375398326116u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X20, 17462675375398326116u));
    }
}
TEST_F(movwlr, Basic_movwlr_4){
    acc0.initSetup(0, "testprogs/binaries/movwlr_4.bin", 0);
    int numop = 9;
    eventword_t ev0(0);
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
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 17139160397615410632u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 3u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, 722u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, 722u+1));
        EXPECT_TRUE(acc0.testMem((i << 16) + 46211, 17139160397615410632u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X20, 17139160397615410632u));
    }
}
TEST_F(movwlr, Basic_movwlr_5){
    acc0.initSetup(0, "testprogs/binaries/movwlr_5.bin", 0);
    int numop = 9;
    eventword_t ev0(0);
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
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 2767332331233753348u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 295u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, 30u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, 30u+1));
        EXPECT_TRUE(acc0.testMem((i << 16) + 15655, 2767332331233753348u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X20, 2767332331233753348u));
    }
}
TEST_F(movwlr, Basic_movwlr_6){
    acc0.initSetup(0, "testprogs/binaries/movwlr_6.bin", 0);
    int numop = 9;
    eventword_t ev0(0);
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
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 3992056671734678032u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 7u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, 2291u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, 2291u+0));
        EXPECT_TRUE(acc0.testMem((i << 16) + 18335, 3992056671734678032u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X20, 3992056671734678032u));
    }
}
TEST_F(movwlr, Basic_movwlr_7){
    acc0.initSetup(0, "testprogs/binaries/movwlr_7.bin", 0);
    int numop = 9;
    eventword_t ev0(0);
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
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 15501587856676639668u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 2u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, 1338u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, 1338u+1));
        EXPECT_TRUE(acc0.testMem((i << 16) + 21410, 15501587856676639668u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X20, 15501587856676639668u));
    }
}
TEST_F(movwlr, Basic_movwlr_8){
    acc0.initSetup(0, "testprogs/binaries/movwlr_8.bin", 0);
    int numop = 9;
    eventword_t ev0(0);
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
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 4406121012964502996u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 48u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, 125u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, 125u+0));
        EXPECT_TRUE(acc0.testMem((i << 16) + 64048, 4406121012964502996u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X20, 4406121012964502996u));
    }
}
TEST_F(movwlr, Basic_movwlr_9){
    acc0.initSetup(0, "testprogs/binaries/movwlr_9.bin", 0);
    int numop = 9;
    eventword_t ev0(0);
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
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 9098876975541918009u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 63u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, 512u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, 512u+1));
        EXPECT_TRUE(acc0.testMem((i << 16) + 32831, 9098876975541918009u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X20, 9098876975541918009u));
    }
}
TEST_F(movwlr, Basic_movwlr_10){
    acc0.initSetup(0, "testprogs/binaries/movwlr_10.bin", 0);
    int numop = 9;
    eventword_t ev0(0);
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
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 4067018941000484810u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 498u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, 68u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, 68u+0));
        EXPECT_TRUE(acc0.testMem((i << 16) + 35314, 4067018941000484810u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X20, 4067018941000484810u));
    }
}
TEST_F(movwlr, Basic_movwlr_11){
    acc0.initSetup(0, "testprogs/binaries/movwlr_11.bin", 0);
    int numop = 9;
    eventword_t ev0(0);
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
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 6885608629656274841u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 216u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, 121u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, 121u+0));
        EXPECT_TRUE(acc0.testMem((i << 16) + 62168, 6885608629656274841u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X20, 6885608629656274841u));
    }
}
TEST_F(movwlr, Basic_movwlr_12){
    acc0.initSetup(0, "testprogs/binaries/movwlr_12.bin", 0);
    int numop = 9;
    eventword_t ev0(0);
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
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 8233687084285748662u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 27u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, 435u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, 435u+0));
        EXPECT_TRUE(acc0.testMem((i << 16) + 13947, 8233687084285748662u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X20, 8233687084285748662u));
    }
}
TEST_F(movwlr, Basic_movwlr_13){
    acc0.initSetup(0, "testprogs/binaries/movwlr_13.bin", 0);
    int numop = 9;
    eventword_t ev0(0);
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
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 12449818878293260185u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 55u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, 349u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, 349u+1));
        EXPECT_TRUE(acc0.testMem((i << 16) + 22391, 12449818878293260185u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X20, 12449818878293260185u));
    }
}
TEST_F(movwlr, Basic_movwlr_14){
    acc0.initSetup(0, "testprogs/binaries/movwlr_14.bin", 0);
    int numop = 9;
    eventword_t ev0(0);
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
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 14596146039420500288u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 10u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, 707u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, 707u+0));
        EXPECT_TRUE(acc0.testMem((i << 16) + 45258, 14596146039420500288u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X20, 14596146039420500288u));
    }
}
TEST_F(movwlr, Basic_movwlr_15){
    acc0.initSetup(0, "testprogs/binaries/movwlr_15.bin", 0);
    int numop = 9;
    eventword_t ev0(0);
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
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 10124559546801673242u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 2u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, 6653u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, 6653u+1));
        EXPECT_TRUE(acc0.testMem((i << 16) + 53226, 10124559546801673242u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X20, 10124559546801673242u));
    }
}
TEST_F(movwlr, Basic_movwlr_16){
    acc0.initSetup(0, "testprogs/binaries/movwlr_16.bin", 0);
    int numop = 9;
    eventword_t ev0(0);
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
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 13480656785368407771u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 30u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, 635u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, 635u+1));
        EXPECT_TRUE(acc0.testMem((i << 16) + 40670, 13480656785368407771u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X20, 13480656785368407771u));
    }
}
TEST_F(movwlr, Basic_movwlr_17){
    acc0.initSetup(0, "testprogs/binaries/movwlr_17.bin", 0);
    int numop = 9;
    eventword_t ev0(0);
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
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 14850020551420636771u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 7u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, 3239u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, 3239u+1));
        EXPECT_TRUE(acc0.testMem((i << 16) + 25919, 14850020551420636771u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X20, 14850020551420636771u));
    }
}
TEST_F(movwlr, Basic_movwlr_18){
    acc0.initSetup(0, "testprogs/binaries/movwlr_18.bin", 0);
    int numop = 9;
    eventword_t ev0(0);
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
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 9341468156785131519u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 7u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, 1836u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, 1836u+0));
        EXPECT_TRUE(acc0.testMem((i << 16) + 29383, 9341468156785131519u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X20, 9341468156785131519u));
    }
}
TEST_F(movwlr, Basic_movwlr_19){
    acc0.initSetup(0, "testprogs/binaries/movwlr_19.bin", 0);
    int numop = 9;
    eventword_t ev0(0);
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
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 2432558270897545449u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 4u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, 7238u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, 7238u+1));
        EXPECT_TRUE(acc0.testMem((i << 16) + 57908, 2432558270897545449u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X20, 2432558270897545449u));
    }
}
