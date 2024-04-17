#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"

using namespace basim;

class movlr : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    int numLanes = 64;
    UDAccelerator acc0 = UDAccelerator(numLanes, 0, 1); // UDAccelerator(numLanes, UDID/networkID, lmmode (0: accelerator based addressing, 1:bank/lane based addressing))
    int buffsize1 = 1024;
    int buffsize2 = 1024;
};
TEST_F(movlr, Basic_movlr_0){
    acc0.initSetup(0, "testprogs/binaries/movlr_0.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 10888525202712618476u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, 149));
        EXPECT_TRUE(acc0.testMem((i << 16) + 1654, 10888525202712618476u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, 228678614312428u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 155));
    }
}
TEST_F(movlr, Basic_movlr_1){
    acc0.initSetup(0, "testprogs/binaries/movlr_1.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 10882970040051435190u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, 46489));
        EXPECT_TRUE(acc0.testMem((i << 16) + 48155, 10882970040051435190u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, 1718u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 46491));
    }
}
TEST_F(movlr, Basic_movlr_2){
    acc0.initSetup(0, "testprogs/binaries/movlr_2.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 5635717296553924171u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, 56732));
        EXPECT_TRUE(acc0.testMem((i << 16) + 56607, 5635717296553924171u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, 2610894411u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 56736));
    }
}
TEST_F(movlr, Basic_movlr_3){
    acc0.initSetup(0, "testprogs/binaries/movlr_3.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 932338702461542209u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, 43788));
        EXPECT_TRUE(acc0.testMem((i << 16) + 43670, 932338702461542209u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, 9543489u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 43788));
    }
}
TEST_F(movlr, Basic_movlr_4){
    acc0.initSetup(0, "testprogs/binaries/movlr_4.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 29253022608555099u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, 33646));
        EXPECT_TRUE(acc0.testMem((i << 16) + 32753, 29253022608555099u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, 31835u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 33648));
    }
}
TEST_F(movlr, Basic_movlr_5){
    acc0.initSetup(0, "testprogs/binaries/movlr_5.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 5511500186423867249u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, 31347));
        EXPECT_TRUE(acc0.testMem((i << 16) + 30219, 5511500186423867249u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, 4929393u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 31347));
    }
}
TEST_F(movlr, Basic_movlr_6){
    acc0.initSetup(0, "testprogs/binaries/movlr_6.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 2387632295753962345u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, 39332));
        EXPECT_TRUE(acc0.testMem((i << 16) + 39183, 2387632295753962345u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, 161543294178153u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 39332));
    }
}
TEST_F(movlr, Basic_movlr_7){
    acc0.initSetup(0, "testprogs/binaries/movlr_7.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 11637632516533535821u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, 2459));
        EXPECT_TRUE(acc0.testMem((i << 16) + 4102, 11637632516533535821u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, 17485u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 2461));
    }
}
TEST_F(movlr, Basic_movlr_8){
    acc0.initSetup(0, "testprogs/binaries/movlr_8.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 13161505769144900103u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, 63458));
        EXPECT_TRUE(acc0.testMem((i << 16) + 64895, 13161505769144900103u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, 17333131336199u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 63458));
    }
}
TEST_F(movlr, Basic_movlr_9){
    acc0.initSetup(0, "testprogs/binaries/movlr_9.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 2637814718193798389u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, 46791));
        EXPECT_TRUE(acc0.testMem((i << 16) + 48358, 2637814718193798389u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, 2637814718193798389u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 46791));
    }
}
TEST_F(movlr, Basic_movlr_10){
    acc0.initSetup(0, "testprogs/binaries/movlr_10.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 5492845670612477502u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, 36956));
        EXPECT_TRUE(acc0.testMem((i << 16) + 35760, 5492845670612477502u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, 15083070u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 36959));
    }
}
TEST_F(movlr, Basic_movlr_11){
    acc0.initSetup(0, "testprogs/binaries/movlr_11.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 18338433467689561926u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, 44287));
        EXPECT_TRUE(acc0.testMem((i << 16) + 44839, 18338433467689561926u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, 18338433467689561926u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 44287));
    }
}
TEST_F(movlr, Basic_movlr_12){
    acc0.initSetup(0, "testprogs/binaries/movlr_12.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 277217392378627461u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, 46684));
        EXPECT_TRUE(acc0.testMem((i << 16) + 45852, 277217392378627461u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, 50565u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 46684));
    }
}
TEST_F(movlr, Basic_movlr_13){
    acc0.initSetup(0, "testprogs/binaries/movlr_13.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 4682875128255712826u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, 33750));
        EXPECT_TRUE(acc0.testMem((i << 16) + 35473, 4682875128255712826u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, 71189109828324922u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 33750));
    }
}
TEST_F(movlr, Basic_movlr_14){
    acc0.initSetup(0, "testprogs/binaries/movlr_14.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 17918385405323037263u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, 27432));
        EXPECT_TRUE(acc0.testMem((i << 16) + 29367, 17918385405323037263u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, 17918385405323037263u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 27432));
    }
}
TEST_F(movlr, Basic_movlr_15){
    acc0.initSetup(0, "testprogs/binaries/movlr_15.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 9306083422126053799u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, 56479));
        EXPECT_TRUE(acc0.testMem((i << 16) + 57174, 9306083422126053799u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, 9306083422126053799u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 56479));
    }
}
TEST_F(movlr, Basic_movlr_16){
    acc0.initSetup(0, "testprogs/binaries/movlr_16.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 11655971430505320463u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, 15976));
        EXPECT_TRUE(acc0.testMem((i << 16) + 17233, 11655971430505320463u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, 11655971430505320463u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 15984));
    }
}
TEST_F(movlr, Basic_movlr_17){
    acc0.initSetup(0, "testprogs/binaries/movlr_17.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 2827444875009019736u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, -177));
        EXPECT_TRUE(acc0.testMem((i << 16) + 295, 2827444875009019736u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, 15290200u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, -177));
    }
}
TEST_F(movlr, Basic_movlr_18){
    acc0.initSetup(0, "testprogs/binaries/movlr_18.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 15014503143993154928u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, 32773));
        EXPECT_TRUE(acc0.testMem((i << 16) + 32499, 15014503143993154928u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, 64936293342576u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 32779));
    }
}
TEST_F(movlr, Basic_movlr_19){
    acc0.initSetup(0, "testprogs/binaries/movlr_19.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 10127664495759722600u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18, 32491));
        EXPECT_TRUE(acc0.testMem((i << 16) + 34283, 10127664495759722600u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X19, 220152203368u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 32496));
    }
}
