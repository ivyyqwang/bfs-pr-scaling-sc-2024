#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"

using namespace basim;

class basic_action8_with_lastact_TX : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    int numLanes = 64;
    UDAccelerator acc0 = UDAccelerator(numLanes, 0, 1); // UDAccelerator(numLanes, UDID/networkID, lmmode (0: accelerator based addressing, 1:bank/lane based addressing))
    int buffsize1 = 1024;
    int buffsize2 = 1024;
};
TEST_F(basic_action8_with_lastact_TX, Basic_basic_action8_with_lastact_TX_0){
    acc0.initSetup(0, "testprogs/binaries/basic_action8_with_lastact_TX_0.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(14372);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 584115552280u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 8)));
    }
}
TEST_F(basic_action8_with_lastact_TX, Basic_basic_action8_with_lastact_TX_1){
    acc0.initSetup(0, "testprogs/binaries/basic_action8_with_lastact_TX_1.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(14372);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 292057776140u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 4)));
    }
}
TEST_F(basic_action8_with_lastact_TX, Basic_basic_action8_with_lastact_TX_2){
    acc0.initSetup(0, "testprogs/binaries/basic_action8_with_lastact_TX_2.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(14372);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 584115552280u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 8)));
    }
}
TEST_F(basic_action8_with_lastact_TX, Basic_basic_action8_with_lastact_TX_3){
    acc0.initSetup(0, "testprogs/binaries/basic_action8_with_lastact_TX_3.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(14372);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 584115552280u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 8)));
    }
}
TEST_F(basic_action8_with_lastact_TX, Basic_basic_action8_with_lastact_TX_4){
    acc0.initSetup(0, "testprogs/binaries/basic_action8_with_lastact_TX_4.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(14372);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 7181215375093137426u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 6)));
    }
}
TEST_F(basic_action8_with_lastact_TX, Basic_basic_action8_with_lastact_TX_5){
    acc0.initSetup(0, "testprogs/binaries/basic_action8_with_lastact_TX_5.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(14372);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 16723601910359130127u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 5)));
    }
}
TEST_F(basic_action8_with_lastact_TX, Basic_basic_action8_with_lastact_TX_6){
    acc0.initSetup(0, "testprogs/binaries/basic_action8_with_lastact_TX_6.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(14372);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 9195351494122012693u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 7)));
    }
}
TEST_F(basic_action8_with_lastact_TX, Basic_basic_action8_with_lastact_TX_7){
    acc0.initSetup(0, "testprogs/binaries/basic_action8_with_lastact_TX_7.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(14372);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 163024073654287u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 5)));
    }
}
TEST_F(basic_action8_with_lastact_TX, Basic_basic_action8_with_lastact_TX_8){
    acc0.initSetup(0, "testprogs/binaries/basic_action8_with_lastact_TX_8.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(14372);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 13066511689598369813u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 7)));
    }
}
TEST_F(basic_action8_with_lastact_TX, Basic_basic_action8_with_lastact_TX_9){
    acc0.initSetup(0, "testprogs/binaries/basic_action8_with_lastact_TX_9.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(14372);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 584115552280u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 8)));
    }
}
TEST_F(basic_action8_with_lastact_TX, Basic_basic_action8_with_lastact_TX_10){
    acc0.initSetup(0, "testprogs/binaries/basic_action8_with_lastact_TX_10.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(14372);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 3742652128280182808u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 8)));
    }
}
TEST_F(basic_action8_with_lastact_TX, Basic_basic_action8_with_lastact_TX_11){
    acc0.initSetup(0, "testprogs/binaries/basic_action8_with_lastact_TX_11.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(14372);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 2945112353936506895u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 5)));
    }
}
TEST_F(basic_action8_with_lastact_TX, Basic_basic_action8_with_lastact_TX_12){
    acc0.initSetup(0, "testprogs/binaries/basic_action8_with_lastact_TX_12.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(14372);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 3118128484321329170u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 6)));
    }
}
TEST_F(basic_action8_with_lastact_TX, Basic_basic_action8_with_lastact_TX_13){
    acc0.initSetup(0, "testprogs/binaries/basic_action8_with_lastact_TX_13.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(14372);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 3083280502661054488u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 8)));
    }
}
TEST_F(basic_action8_with_lastact_TX, Basic_basic_action8_with_lastact_TX_14){
    acc0.initSetup(0, "testprogs/binaries/basic_action8_with_lastact_TX_14.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(14372);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 13851444446438096914u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 6)));
    }
}
TEST_F(basic_action8_with_lastact_TX, Basic_basic_action8_with_lastact_TX_15){
    acc0.initSetup(0, "testprogs/binaries/basic_action8_with_lastact_TX_15.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(14372);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 15896327312921067544u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 8)));
    }
}
TEST_F(basic_action8_with_lastact_TX, Basic_basic_action8_with_lastact_TX_16){
    acc0.initSetup(0, "testprogs/binaries/basic_action8_with_lastact_TX_16.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(14372);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 11591244432636117010u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 6)));
    }
}
TEST_F(basic_action8_with_lastact_TX, Basic_basic_action8_with_lastact_TX_17){
    acc0.initSetup(0, "testprogs/binaries/basic_action8_with_lastact_TX_17.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(14372);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 1268897187945775119u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 5)));
    }
}
TEST_F(basic_action8_with_lastact_TX, Basic_basic_action8_with_lastact_TX_18){
    acc0.initSetup(0, "testprogs/binaries/basic_action8_with_lastact_TX_18.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(14372);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 12127834840322015256u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 19)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19) + 8)));
    }
}
TEST_F(basic_action8_with_lastact_TX, Basic_basic_action8_with_lastact_TX_19){
    acc0.initSetup(0, "testprogs/binaries/basic_action8_with_lastact_TX_19.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(14372);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X24, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X25, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X26, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X27, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X28, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X29, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X30, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 584115552280u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16) + 8)));
    }
}
