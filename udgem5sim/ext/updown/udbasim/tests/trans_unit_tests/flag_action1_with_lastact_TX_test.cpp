#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"

using namespace basim;

class flag_action1_with_lastact_TX : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    int numLanes = 64;
    UDAccelerator acc0 = UDAccelerator(numLanes, 0, 1); // UDAccelerator(numLanes, UDID/networkID, lmmode (0: accelerator based addressing, 1:bank/lane based addressing))
    int buffsize1 = 1024;
    int buffsize2 = 1024;
};
TEST_F(flag_action1_with_lastact_TX, Basic_flag_action1_with_lastact_TX_0){
    acc0.initSetup(0, "testprogs/binaries/flag_action1_with_lastact_TX_0.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(5156);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 71));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 10119883615933300760u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
    }
}
TEST_F(flag_action1_with_lastact_TX, Basic_flag_action1_with_lastact_TX_1){
    acc0.initSetup(0, "testprogs/binaries/flag_action1_with_lastact_TX_1.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(5156);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 196));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 5890640288908574726u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
    }
}
TEST_F(flag_action1_with_lastact_TX, Basic_flag_action1_with_lastact_TX_2){
    acc0.initSetup(0, "testprogs/binaries/flag_action1_with_lastact_TX_2.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(5156);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 200));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 12734072493514424341u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
    }
}
TEST_F(flag_action1_with_lastact_TX, Basic_flag_action1_with_lastact_TX_3){
    acc0.initSetup(0, "testprogs/binaries/flag_action1_with_lastact_TX_3.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(5156);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 254));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 13398376601310199832u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
    }
}
TEST_F(flag_action1_with_lastact_TX, Basic_flag_action1_with_lastact_TX_4){
    acc0.initSetup(0, "testprogs/binaries/flag_action1_with_lastact_TX_4.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(5156);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 3));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 3784673250785624079u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
    }
}
TEST_F(flag_action1_with_lastact_TX, Basic_flag_action1_with_lastact_TX_5){
    acc0.initSetup(0, "testprogs/binaries/flag_action1_with_lastact_TX_5.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(5156);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 197));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 9588872890455949333u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
    }
}
TEST_F(flag_action1_with_lastact_TX, Basic_flag_action1_with_lastact_TX_6){
    acc0.initSetup(0, "testprogs/binaries/flag_action1_with_lastact_TX_6.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(5156);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 249));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 4384558286569996312u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
    }
}
TEST_F(flag_action1_with_lastact_TX, Basic_flag_action1_with_lastact_TX_7){
    acc0.initSetup(0, "testprogs/binaries/flag_action1_with_lastact_TX_7.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(5156);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 178));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 924471876305027090u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
    }
}
TEST_F(flag_action1_with_lastact_TX, Basic_flag_action1_with_lastact_TX_8){
    acc0.initSetup(0, "testprogs/binaries/flag_action1_with_lastact_TX_8.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(5156);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 207));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 2550560655077802005u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
    }
}
TEST_F(flag_action1_with_lastact_TX, Basic_flag_action1_with_lastact_TX_9){
    acc0.initSetup(0, "testprogs/binaries/flag_action1_with_lastact_TX_9.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(5156);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 36));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 10863645628022390796u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
    }
}
TEST_F(flag_action1_with_lastact_TX, Basic_flag_action1_with_lastact_TX_10){
    acc0.initSetup(0, "testprogs/binaries/flag_action1_with_lastact_TX_10.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(5156);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 47));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 9444485294079344658u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
    }
}
TEST_F(flag_action1_with_lastact_TX, Basic_flag_action1_with_lastact_TX_11){
    acc0.initSetup(0, "testprogs/binaries/flag_action1_with_lastact_TX_11.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(5156);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 124));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 16001514077067149330u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
    }
}
TEST_F(flag_action1_with_lastact_TX, Basic_flag_action1_with_lastact_TX_12){
    acc0.initSetup(0, "testprogs/binaries/flag_action1_with_lastact_TX_12.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(5156);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 51));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 3827220240496853016u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
    }
}
TEST_F(flag_action1_with_lastact_TX, Basic_flag_action1_with_lastact_TX_13){
    acc0.initSetup(0, "testprogs/binaries/flag_action1_with_lastact_TX_13.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(5156);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 174));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 7656547441625268239u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
    }
}
TEST_F(flag_action1_with_lastact_TX, Basic_flag_action1_with_lastact_TX_14){
    acc0.initSetup(0, "testprogs/binaries/flag_action1_with_lastact_TX_14.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(5156);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 41));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 7615991882220306444u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
    }
}
TEST_F(flag_action1_with_lastact_TX, Basic_flag_action1_with_lastact_TX_15){
    acc0.initSetup(0, "testprogs/binaries/flag_action1_with_lastact_TX_15.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(5156);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 121));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 507368781643776024u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
    }
}
TEST_F(flag_action1_with_lastact_TX, Basic_flag_action1_with_lastact_TX_16){
    acc0.initSetup(0, "testprogs/binaries/flag_action1_with_lastact_TX_16.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(5156);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 234));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 4290339601882546185u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 19))));
    }
}
TEST_F(flag_action1_with_lastact_TX, Basic_flag_action1_with_lastact_TX_17){
    acc0.initSetup(0, "testprogs/binaries/flag_action1_with_lastact_TX_17.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(5156);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 65));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 16831838732645564434u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
    }
}
TEST_F(flag_action1_with_lastact_TX, Basic_flag_action1_with_lastact_TX_18){
    acc0.initSetup(0, "testprogs/binaries/flag_action1_with_lastact_TX_18.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(5156);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 72));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 9529205890519924751u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
    }
}
TEST_F(flag_action1_with_lastact_TX, Basic_flag_action1_with_lastact_TX_19){
    acc0.initSetup(0, "testprogs/binaries/flag_action1_with_lastact_TX_19.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(5156);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 155));
        EXPECT_TRUE(acc0.testReg(i, RegId::X31, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X4, 9895035180270223366u));
        EXPECT_TRUE(acc0.testReg(i, RegId::X5,  ((i << 16))));
    }
}
