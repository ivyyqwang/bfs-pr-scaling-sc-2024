#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"

using namespace basim;

class basic_action4_without_lastact_TX : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    int numLanes = 64;
    UDAccelerator acc0 = UDAccelerator(numLanes, 0, 1); // UDAccelerator(numLanes, UDID/networkID, lmmode (0: accelerator based addressing, 1:bank/lane based addressing))
    int buffsize1 = 1024;
    int buffsize2 = 1024;
};
TEST_F(basic_action4_without_lastact_TX, Basic_basic_action4_without_lastact_TX_0){
    acc0.initSetup(0, "testprogs/binaries/basic_action4_without_lastact_TX_0.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(10276);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 1781967667524010005u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, ((i << 16) + 7)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 7)));
    }
}
TEST_F(basic_action4_without_lastact_TX, Basic_basic_action4_without_lastact_TX_1){
    acc0.initSetup(0, "testprogs/binaries/basic_action4_without_lastact_TX_1.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(10276);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 584115552280u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, ((i << 16) + 8)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 8)));
    }
}
TEST_F(basic_action4_without_lastact_TX, Basic_basic_action4_without_lastact_TX_2){
    acc0.initSetup(0, "testprogs/binaries/basic_action4_without_lastact_TX_2.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(10276);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 5860259610107052035u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, ((i << 19) + 1)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 1)));
    }
}
TEST_F(basic_action4_without_lastact_TX, Basic_basic_action4_without_lastact_TX_3){
    acc0.initSetup(0, "testprogs/binaries/basic_action4_without_lastact_TX_3.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(10276);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 11556869447134216216u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, ((i << 19) + 8)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 8)));
    }
}
TEST_F(basic_action4_without_lastact_TX, Basic_basic_action4_without_lastact_TX_4){
    acc0.initSetup(0, "testprogs/binaries/basic_action4_without_lastact_TX_4.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(10276);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 16277294829086441496u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, ((i << 19) + 8)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 8)));
    }
}
TEST_F(basic_action4_without_lastact_TX, Basic_basic_action4_without_lastact_TX_5){
    acc0.initSetup(0, "testprogs/binaries/basic_action4_without_lastact_TX_5.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(10276);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 2327720430158217234u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, ((i << 19) + 6)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 6)));
    }
}
TEST_F(basic_action4_without_lastact_TX, Basic_basic_action4_without_lastact_TX_6){
    acc0.initSetup(0, "testprogs/binaries/basic_action4_without_lastact_TX_6.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(10276);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 13474454890327572495u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, ((i << 19) + 5)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 5)));
    }
}
TEST_F(basic_action4_without_lastact_TX, Basic_basic_action4_without_lastact_TX_7){
    acc0.initSetup(0, "testprogs/binaries/basic_action4_without_lastact_TX_7.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(10276);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 3607552729393659928u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, ((i << 16) + 8)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 8)));
    }
}
TEST_F(basic_action4_without_lastact_TX, Basic_basic_action4_without_lastact_TX_8){
    acc0.initSetup(0, "testprogs/binaries/basic_action4_without_lastact_TX_8.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(10276);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 5058211189549432853u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, ((i << 16) + 7)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 7)));
    }
}
TEST_F(basic_action4_without_lastact_TX, Basic_basic_action4_without_lastact_TX_9){
    acc0.initSetup(0, "testprogs/binaries/basic_action4_without_lastact_TX_9.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(10276);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 3767953059066413080u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, ((i << 19) + 8)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 8)));
    }
}
TEST_F(basic_action4_without_lastact_TX, Basic_basic_action4_without_lastact_TX_10){
    acc0.initSetup(0, "testprogs/binaries/basic_action4_without_lastact_TX_10.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(10276);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 15160252308744306709u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, ((i << 19) + 7)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 7)));
    }
}
TEST_F(basic_action4_without_lastact_TX, Basic_basic_action4_without_lastact_TX_11){
    acc0.initSetup(0, "testprogs/binaries/basic_action4_without_lastact_TX_11.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(10276);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 12369051860206616582u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, ((i << 19) + 2)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 2)));
    }
}
TEST_F(basic_action4_without_lastact_TX, Basic_basic_action4_without_lastact_TX_12){
    acc0.initSetup(0, "testprogs/binaries/basic_action4_without_lastact_TX_12.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(10276);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 17725428308033667078u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, ((i << 19) + 2)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 2)));
    }
}
TEST_F(basic_action4_without_lastact_TX, Basic_basic_action4_without_lastact_TX_13){
    acc0.initSetup(0, "testprogs/binaries/basic_action4_without_lastact_TX_13.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(10276);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 17237607047835418648u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, ((i << 16) + 8)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 8)));
    }
}
TEST_F(basic_action4_without_lastact_TX, Basic_basic_action4_without_lastact_TX_14){
    acc0.initSetup(0, "testprogs/binaries/basic_action4_without_lastact_TX_14.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(10276);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 8218294469196251157u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, ((i << 19) + 7)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 7)));
    }
}
TEST_F(basic_action4_without_lastact_TX, Basic_basic_action4_without_lastact_TX_15){
    acc0.initSetup(0, "testprogs/binaries/basic_action4_without_lastact_TX_15.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(10276);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 13670994797110755346u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, ((i << 19) + 6)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 6)));
    }
}
TEST_F(basic_action4_without_lastact_TX, Basic_basic_action4_without_lastact_TX_16){
    acc0.initSetup(0, "testprogs/binaries/basic_action4_without_lastact_TX_16.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(10276);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 17649689484641435657u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, ((i << 19) + 3)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 3)));
    }
}
TEST_F(basic_action4_without_lastact_TX, Basic_basic_action4_without_lastact_TX_17){
    acc0.initSetup(0, "testprogs/binaries/basic_action4_without_lastact_TX_17.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(10276);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 584115552280u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, ((i << 16) + 8)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 8)));
    }
}
TEST_F(basic_action4_without_lastact_TX, Basic_basic_action4_without_lastact_TX_18){
    acc0.initSetup(0, "testprogs/binaries/basic_action4_without_lastact_TX_18.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(10276);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 11720090350549729292u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, ((i << 16) + 4)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 4)));
    }
}
TEST_F(basic_action4_without_lastact_TX, Basic_basic_action4_without_lastact_TX_19){
    acc0.initSetup(0, "testprogs/binaries/basic_action4_without_lastact_TX_19.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(10276);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 584115552280u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, ((i << 16) + 8)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 8)));
    }
}
