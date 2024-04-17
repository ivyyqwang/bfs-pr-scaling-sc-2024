#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"

using namespace basim;

class bcpylli : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    int numLanes = 64;
    UDAccelerator acc0 = UDAccelerator(numLanes, 0, 1); // UDAccelerator(numLanes, UDID/networkID, lmmode (0: accelerator based addressing, 1:bank/lane based addressing))
    int buffsize1 = 1024;
    int buffsize2 = 1024;
};
TEST_F(bcpylli, Basic_bcpylli_0){
    acc0.initSetup(0, "testprogs/binaries/bcpylli_0.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X21, 39313));
        EXPECT_TRUE(acc0.testReg(i, RegId::X22, 51463));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 39313+12));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 51463+12));
        word_t val=0;
        acc0.readScratchPad(1, (i<<16) + 51463, (uint8_t*)&val);
        EXPECT_TRUE(val == 194u);
        acc0.readScratchPad(1, (i<<16) + 51464, (uint8_t*)&val);
        EXPECT_TRUE(val == 85u);
        acc0.readScratchPad(1, (i<<16) + 51465, (uint8_t*)&val);
        EXPECT_TRUE(val == 203u);
        acc0.readScratchPad(1, (i<<16) + 51466, (uint8_t*)&val);
        EXPECT_TRUE(val == 211u);
        acc0.readScratchPad(1, (i<<16) + 51467, (uint8_t*)&val);
        EXPECT_TRUE(val == 126u);
        acc0.readScratchPad(1, (i<<16) + 51468, (uint8_t*)&val);
        EXPECT_TRUE(val == 86u);
        acc0.readScratchPad(1, (i<<16) + 51469, (uint8_t*)&val);
        EXPECT_TRUE(val == 225u);
        acc0.readScratchPad(1, (i<<16) + 51470, (uint8_t*)&val);
        EXPECT_TRUE(val == 185u);
        acc0.readScratchPad(1, (i<<16) + 51471, (uint8_t*)&val);
        EXPECT_TRUE(val == 45u);
        acc0.readScratchPad(1, (i<<16) + 51472, (uint8_t*)&val);
        EXPECT_TRUE(val == 83u);
        acc0.readScratchPad(1, (i<<16) + 51473, (uint8_t*)&val);
        EXPECT_TRUE(val == 210u);
        acc0.readScratchPad(1, (i<<16) + 51474, (uint8_t*)&val);
        EXPECT_TRUE(val == 70u);
    }
}
TEST_F(bcpylli, Basic_bcpylli_1){
    acc0.initSetup(0, "testprogs/binaries/bcpylli_1.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X21, 44322));
        EXPECT_TRUE(acc0.testReg(i, RegId::X22, 4643));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 44322+5));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 4643+5));
        word_t val=0;
        acc0.readScratchPad(1, (i<<16) + 4643, (uint8_t*)&val);
        EXPECT_TRUE(val == 22u);
        acc0.readScratchPad(1, (i<<16) + 4644, (uint8_t*)&val);
        EXPECT_TRUE(val == 160u);
        acc0.readScratchPad(1, (i<<16) + 4645, (uint8_t*)&val);
        EXPECT_TRUE(val == 252u);
        acc0.readScratchPad(1, (i<<16) + 4646, (uint8_t*)&val);
        EXPECT_TRUE(val == 17u);
        acc0.readScratchPad(1, (i<<16) + 4647, (uint8_t*)&val);
        EXPECT_TRUE(val == 121u);
    }
}
TEST_F(bcpylli, Basic_bcpylli_2){
    acc0.initSetup(0, "testprogs/binaries/bcpylli_2.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X21, 57834));
        EXPECT_TRUE(acc0.testReg(i, RegId::X22, 52598));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 57834+1));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 52598+1));
        word_t val=0;
        acc0.readScratchPad(1, (i<<16) + 52598, (uint8_t*)&val);
        EXPECT_TRUE(val == 241u);
    }
}
TEST_F(bcpylli, Basic_bcpylli_3){
    acc0.initSetup(0, "testprogs/binaries/bcpylli_3.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X21, 9974));
        EXPECT_TRUE(acc0.testReg(i, RegId::X22, 28120));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 9974+29));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 28120+29));
        word_t val=0;
        acc0.readScratchPad(1, (i<<16) + 28120, (uint8_t*)&val);
        EXPECT_TRUE(val == 174u);
        acc0.readScratchPad(1, (i<<16) + 28121, (uint8_t*)&val);
        EXPECT_TRUE(val == 199u);
        acc0.readScratchPad(1, (i<<16) + 28122, (uint8_t*)&val);
        EXPECT_TRUE(val == 202u);
        acc0.readScratchPad(1, (i<<16) + 28123, (uint8_t*)&val);
        EXPECT_TRUE(val == 254u);
        acc0.readScratchPad(1, (i<<16) + 28124, (uint8_t*)&val);
        EXPECT_TRUE(val == 187u);
        acc0.readScratchPad(1, (i<<16) + 28125, (uint8_t*)&val);
        EXPECT_TRUE(val == 125u);
        acc0.readScratchPad(1, (i<<16) + 28126, (uint8_t*)&val);
        EXPECT_TRUE(val == 53u);
        acc0.readScratchPad(1, (i<<16) + 28127, (uint8_t*)&val);
        EXPECT_TRUE(val == 22u);
        acc0.readScratchPad(1, (i<<16) + 28128, (uint8_t*)&val);
        EXPECT_TRUE(val == 54u);
        acc0.readScratchPad(1, (i<<16) + 28129, (uint8_t*)&val);
        EXPECT_TRUE(val == 34u);
        acc0.readScratchPad(1, (i<<16) + 28130, (uint8_t*)&val);
        EXPECT_TRUE(val == 228u);
        acc0.readScratchPad(1, (i<<16) + 28131, (uint8_t*)&val);
        EXPECT_TRUE(val == 158u);
        acc0.readScratchPad(1, (i<<16) + 28132, (uint8_t*)&val);
        EXPECT_TRUE(val == 206u);
        acc0.readScratchPad(1, (i<<16) + 28133, (uint8_t*)&val);
        EXPECT_TRUE(val == 83u);
        acc0.readScratchPad(1, (i<<16) + 28134, (uint8_t*)&val);
        EXPECT_TRUE(val == 90u);
        acc0.readScratchPad(1, (i<<16) + 28135, (uint8_t*)&val);
        EXPECT_TRUE(val == 75u);
        acc0.readScratchPad(1, (i<<16) + 28136, (uint8_t*)&val);
        EXPECT_TRUE(val == 22u);
        acc0.readScratchPad(1, (i<<16) + 28137, (uint8_t*)&val);
        EXPECT_TRUE(val == 111u);
        acc0.readScratchPad(1, (i<<16) + 28138, (uint8_t*)&val);
        EXPECT_TRUE(val == 159u);
        acc0.readScratchPad(1, (i<<16) + 28139, (uint8_t*)&val);
        EXPECT_TRUE(val == 246u);
        acc0.readScratchPad(1, (i<<16) + 28140, (uint8_t*)&val);
        EXPECT_TRUE(val == 97u);
        acc0.readScratchPad(1, (i<<16) + 28141, (uint8_t*)&val);
        EXPECT_TRUE(val == 223u);
        acc0.readScratchPad(1, (i<<16) + 28142, (uint8_t*)&val);
        EXPECT_TRUE(val == 234u);
        acc0.readScratchPad(1, (i<<16) + 28143, (uint8_t*)&val);
        EXPECT_TRUE(val == 36u);
        acc0.readScratchPad(1, (i<<16) + 28144, (uint8_t*)&val);
        EXPECT_TRUE(val == 112u);
        acc0.readScratchPad(1, (i<<16) + 28145, (uint8_t*)&val);
        EXPECT_TRUE(val == 116u);
        acc0.readScratchPad(1, (i<<16) + 28146, (uint8_t*)&val);
        EXPECT_TRUE(val == 90u);
        acc0.readScratchPad(1, (i<<16) + 28147, (uint8_t*)&val);
        EXPECT_TRUE(val == 251u);
        acc0.readScratchPad(1, (i<<16) + 28148, (uint8_t*)&val);
        EXPECT_TRUE(val == 45u);
    }
}
TEST_F(bcpylli, Basic_bcpylli_4){
    acc0.initSetup(0, "testprogs/binaries/bcpylli_4.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X21, 38694));
        EXPECT_TRUE(acc0.testReg(i, RegId::X22, 49352));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 38694+17));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 49352+17));
        word_t val=0;
        acc0.readScratchPad(1, (i<<16) + 49352, (uint8_t*)&val);
        EXPECT_TRUE(val == 7u);
        acc0.readScratchPad(1, (i<<16) + 49353, (uint8_t*)&val);
        EXPECT_TRUE(val == 0u);
        acc0.readScratchPad(1, (i<<16) + 49354, (uint8_t*)&val);
        EXPECT_TRUE(val == 9u);
        acc0.readScratchPad(1, (i<<16) + 49355, (uint8_t*)&val);
        EXPECT_TRUE(val == 120u);
        acc0.readScratchPad(1, (i<<16) + 49356, (uint8_t*)&val);
        EXPECT_TRUE(val == 109u);
        acc0.readScratchPad(1, (i<<16) + 49357, (uint8_t*)&val);
        EXPECT_TRUE(val == 150u);
        acc0.readScratchPad(1, (i<<16) + 49358, (uint8_t*)&val);
        EXPECT_TRUE(val == 138u);
        acc0.readScratchPad(1, (i<<16) + 49359, (uint8_t*)&val);
        EXPECT_TRUE(val == 100u);
        acc0.readScratchPad(1, (i<<16) + 49360, (uint8_t*)&val);
        EXPECT_TRUE(val == 46u);
        acc0.readScratchPad(1, (i<<16) + 49361, (uint8_t*)&val);
        EXPECT_TRUE(val == 50u);
        acc0.readScratchPad(1, (i<<16) + 49362, (uint8_t*)&val);
        EXPECT_TRUE(val == 156u);
        acc0.readScratchPad(1, (i<<16) + 49363, (uint8_t*)&val);
        EXPECT_TRUE(val == 18u);
        acc0.readScratchPad(1, (i<<16) + 49364, (uint8_t*)&val);
        EXPECT_TRUE(val == 242u);
        acc0.readScratchPad(1, (i<<16) + 49365, (uint8_t*)&val);
        EXPECT_TRUE(val == 56u);
        acc0.readScratchPad(1, (i<<16) + 49366, (uint8_t*)&val);
        EXPECT_TRUE(val == 49u);
        acc0.readScratchPad(1, (i<<16) + 49367, (uint8_t*)&val);
        EXPECT_TRUE(val == 71u);
        acc0.readScratchPad(1, (i<<16) + 49368, (uint8_t*)&val);
        EXPECT_TRUE(val == 96u);
    }
}
TEST_F(bcpylli, Basic_bcpylli_5){
    acc0.initSetup(0, "testprogs/binaries/bcpylli_5.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X21, 41309));
        EXPECT_TRUE(acc0.testReg(i, RegId::X22, 29599));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 41309+10));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 29599+10));
        word_t val=0;
        acc0.readScratchPad(1, (i<<16) + 29599, (uint8_t*)&val);
        EXPECT_TRUE(val == 4u);
        acc0.readScratchPad(1, (i<<16) + 29600, (uint8_t*)&val);
        EXPECT_TRUE(val == 241u);
        acc0.readScratchPad(1, (i<<16) + 29601, (uint8_t*)&val);
        EXPECT_TRUE(val == 181u);
        acc0.readScratchPad(1, (i<<16) + 29602, (uint8_t*)&val);
        EXPECT_TRUE(val == 60u);
        acc0.readScratchPad(1, (i<<16) + 29603, (uint8_t*)&val);
        EXPECT_TRUE(val == 234u);
        acc0.readScratchPad(1, (i<<16) + 29604, (uint8_t*)&val);
        EXPECT_TRUE(val == 83u);
        acc0.readScratchPad(1, (i<<16) + 29605, (uint8_t*)&val);
        EXPECT_TRUE(val == 55u);
        acc0.readScratchPad(1, (i<<16) + 29606, (uint8_t*)&val);
        EXPECT_TRUE(val == 251u);
        acc0.readScratchPad(1, (i<<16) + 29607, (uint8_t*)&val);
        EXPECT_TRUE(val == 95u);
        acc0.readScratchPad(1, (i<<16) + 29608, (uint8_t*)&val);
        EXPECT_TRUE(val == 154u);
    }
}
TEST_F(bcpylli, Basic_bcpylli_6){
    acc0.initSetup(0, "testprogs/binaries/bcpylli_6.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X21, 48957));
        EXPECT_TRUE(acc0.testReg(i, RegId::X22, 36521));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 48957+26));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 36521+26));
        word_t val=0;
        acc0.readScratchPad(1, (i<<16) + 36521, (uint8_t*)&val);
        EXPECT_TRUE(val == 110u);
        acc0.readScratchPad(1, (i<<16) + 36522, (uint8_t*)&val);
        EXPECT_TRUE(val == 85u);
        acc0.readScratchPad(1, (i<<16) + 36523, (uint8_t*)&val);
        EXPECT_TRUE(val == 207u);
        acc0.readScratchPad(1, (i<<16) + 36524, (uint8_t*)&val);
        EXPECT_TRUE(val == 232u);
        acc0.readScratchPad(1, (i<<16) + 36525, (uint8_t*)&val);
        EXPECT_TRUE(val == 126u);
        acc0.readScratchPad(1, (i<<16) + 36526, (uint8_t*)&val);
        EXPECT_TRUE(val == 60u);
        acc0.readScratchPad(1, (i<<16) + 36527, (uint8_t*)&val);
        EXPECT_TRUE(val == 232u);
        acc0.readScratchPad(1, (i<<16) + 36528, (uint8_t*)&val);
        EXPECT_TRUE(val == 251u);
        acc0.readScratchPad(1, (i<<16) + 36529, (uint8_t*)&val);
        EXPECT_TRUE(val == 9u);
        acc0.readScratchPad(1, (i<<16) + 36530, (uint8_t*)&val);
        EXPECT_TRUE(val == 105u);
        acc0.readScratchPad(1, (i<<16) + 36531, (uint8_t*)&val);
        EXPECT_TRUE(val == 129u);
        acc0.readScratchPad(1, (i<<16) + 36532, (uint8_t*)&val);
        EXPECT_TRUE(val == 47u);
        acc0.readScratchPad(1, (i<<16) + 36533, (uint8_t*)&val);
        EXPECT_TRUE(val == 84u);
        acc0.readScratchPad(1, (i<<16) + 36534, (uint8_t*)&val);
        EXPECT_TRUE(val == 143u);
        acc0.readScratchPad(1, (i<<16) + 36535, (uint8_t*)&val);
        EXPECT_TRUE(val == 227u);
        acc0.readScratchPad(1, (i<<16) + 36536, (uint8_t*)&val);
        EXPECT_TRUE(val == 156u);
        acc0.readScratchPad(1, (i<<16) + 36537, (uint8_t*)&val);
        EXPECT_TRUE(val == 12u);
        acc0.readScratchPad(1, (i<<16) + 36538, (uint8_t*)&val);
        EXPECT_TRUE(val == 199u);
        acc0.readScratchPad(1, (i<<16) + 36539, (uint8_t*)&val);
        EXPECT_TRUE(val == 211u);
        acc0.readScratchPad(1, (i<<16) + 36540, (uint8_t*)&val);
        EXPECT_TRUE(val == 35u);
        acc0.readScratchPad(1, (i<<16) + 36541, (uint8_t*)&val);
        EXPECT_TRUE(val == 231u);
        acc0.readScratchPad(1, (i<<16) + 36542, (uint8_t*)&val);
        EXPECT_TRUE(val == 80u);
        acc0.readScratchPad(1, (i<<16) + 36543, (uint8_t*)&val);
        EXPECT_TRUE(val == 173u);
        acc0.readScratchPad(1, (i<<16) + 36544, (uint8_t*)&val);
        EXPECT_TRUE(val == 55u);
        acc0.readScratchPad(1, (i<<16) + 36545, (uint8_t*)&val);
        EXPECT_TRUE(val == 245u);
        acc0.readScratchPad(1, (i<<16) + 36546, (uint8_t*)&val);
        EXPECT_TRUE(val == 48u);
    }
}
TEST_F(bcpylli, Basic_bcpylli_7){
    acc0.initSetup(0, "testprogs/binaries/bcpylli_7.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X21, 23206));
        EXPECT_TRUE(acc0.testReg(i, RegId::X22, 39796));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 23206+18));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 39796+18));
        word_t val=0;
        acc0.readScratchPad(1, (i<<16) + 39796, (uint8_t*)&val);
        EXPECT_TRUE(val == 195u);
        acc0.readScratchPad(1, (i<<16) + 39797, (uint8_t*)&val);
        EXPECT_TRUE(val == 212u);
        acc0.readScratchPad(1, (i<<16) + 39798, (uint8_t*)&val);
        EXPECT_TRUE(val == 204u);
        acc0.readScratchPad(1, (i<<16) + 39799, (uint8_t*)&val);
        EXPECT_TRUE(val == 160u);
        acc0.readScratchPad(1, (i<<16) + 39800, (uint8_t*)&val);
        EXPECT_TRUE(val == 206u);
        acc0.readScratchPad(1, (i<<16) + 39801, (uint8_t*)&val);
        EXPECT_TRUE(val == 151u);
        acc0.readScratchPad(1, (i<<16) + 39802, (uint8_t*)&val);
        EXPECT_TRUE(val == 142u);
        acc0.readScratchPad(1, (i<<16) + 39803, (uint8_t*)&val);
        EXPECT_TRUE(val == 48u);
        acc0.readScratchPad(1, (i<<16) + 39804, (uint8_t*)&val);
        EXPECT_TRUE(val == 151u);
        acc0.readScratchPad(1, (i<<16) + 39805, (uint8_t*)&val);
        EXPECT_TRUE(val == 114u);
        acc0.readScratchPad(1, (i<<16) + 39806, (uint8_t*)&val);
        EXPECT_TRUE(val == 229u);
        acc0.readScratchPad(1, (i<<16) + 39807, (uint8_t*)&val);
        EXPECT_TRUE(val == 16u);
        acc0.readScratchPad(1, (i<<16) + 39808, (uint8_t*)&val);
        EXPECT_TRUE(val == 50u);
        acc0.readScratchPad(1, (i<<16) + 39809, (uint8_t*)&val);
        EXPECT_TRUE(val == 82u);
        acc0.readScratchPad(1, (i<<16) + 39810, (uint8_t*)&val);
        EXPECT_TRUE(val == 3u);
        acc0.readScratchPad(1, (i<<16) + 39811, (uint8_t*)&val);
        EXPECT_TRUE(val == 118u);
        acc0.readScratchPad(1, (i<<16) + 39812, (uint8_t*)&val);
        EXPECT_TRUE(val == 168u);
        acc0.readScratchPad(1, (i<<16) + 39813, (uint8_t*)&val);
        EXPECT_TRUE(val == 154u);
    }
}
TEST_F(bcpylli, Basic_bcpylli_8){
    acc0.initSetup(0, "testprogs/binaries/bcpylli_8.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X21, 43237));
        EXPECT_TRUE(acc0.testReg(i, RegId::X22, 46318));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 43237+6));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 46318+6));
        word_t val=0;
        acc0.readScratchPad(1, (i<<16) + 46318, (uint8_t*)&val);
        EXPECT_TRUE(val == 180u);
        acc0.readScratchPad(1, (i<<16) + 46319, (uint8_t*)&val);
        EXPECT_TRUE(val == 82u);
        acc0.readScratchPad(1, (i<<16) + 46320, (uint8_t*)&val);
        EXPECT_TRUE(val == 28u);
        acc0.readScratchPad(1, (i<<16) + 46321, (uint8_t*)&val);
        EXPECT_TRUE(val == 254u);
        acc0.readScratchPad(1, (i<<16) + 46322, (uint8_t*)&val);
        EXPECT_TRUE(val == 53u);
        acc0.readScratchPad(1, (i<<16) + 46323, (uint8_t*)&val);
        EXPECT_TRUE(val == 179u);
    }
}
TEST_F(bcpylli, Basic_bcpylli_9){
    acc0.initSetup(0, "testprogs/binaries/bcpylli_9.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X21, 56454));
        EXPECT_TRUE(acc0.testReg(i, RegId::X22, 60353));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 56454+4));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 60353+4));
        word_t val=0;
        acc0.readScratchPad(1, (i<<16) + 60353, (uint8_t*)&val);
        EXPECT_TRUE(val == 44u);
        acc0.readScratchPad(1, (i<<16) + 60354, (uint8_t*)&val);
        EXPECT_TRUE(val == 172u);
        acc0.readScratchPad(1, (i<<16) + 60355, (uint8_t*)&val);
        EXPECT_TRUE(val == 81u);
        acc0.readScratchPad(1, (i<<16) + 60356, (uint8_t*)&val);
        EXPECT_TRUE(val == 164u);
    }
}
TEST_F(bcpylli, Basic_bcpylli_10){
    acc0.initSetup(0, "testprogs/binaries/bcpylli_10.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X21, 36508));
        EXPECT_TRUE(acc0.testReg(i, RegId::X22, 42058));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 36508+12));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 42058+12));
        word_t val=0;
        acc0.readScratchPad(1, (i<<16) + 42058, (uint8_t*)&val);
        EXPECT_TRUE(val == 182u);
        acc0.readScratchPad(1, (i<<16) + 42059, (uint8_t*)&val);
        EXPECT_TRUE(val == 64u);
        acc0.readScratchPad(1, (i<<16) + 42060, (uint8_t*)&val);
        EXPECT_TRUE(val == 107u);
        acc0.readScratchPad(1, (i<<16) + 42061, (uint8_t*)&val);
        EXPECT_TRUE(val == 128u);
        acc0.readScratchPad(1, (i<<16) + 42062, (uint8_t*)&val);
        EXPECT_TRUE(val == 28u);
        acc0.readScratchPad(1, (i<<16) + 42063, (uint8_t*)&val);
        EXPECT_TRUE(val == 49u);
        acc0.readScratchPad(1, (i<<16) + 42064, (uint8_t*)&val);
        EXPECT_TRUE(val == 253u);
        acc0.readScratchPad(1, (i<<16) + 42065, (uint8_t*)&val);
        EXPECT_TRUE(val == 91u);
        acc0.readScratchPad(1, (i<<16) + 42066, (uint8_t*)&val);
        EXPECT_TRUE(val == 196u);
        acc0.readScratchPad(1, (i<<16) + 42067, (uint8_t*)&val);
        EXPECT_TRUE(val == 157u);
        acc0.readScratchPad(1, (i<<16) + 42068, (uint8_t*)&val);
        EXPECT_TRUE(val == 175u);
        acc0.readScratchPad(1, (i<<16) + 42069, (uint8_t*)&val);
        EXPECT_TRUE(val == 67u);
    }
}
TEST_F(bcpylli, Basic_bcpylli_11){
    acc0.initSetup(0, "testprogs/binaries/bcpylli_11.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X21, 64592));
        EXPECT_TRUE(acc0.testReg(i, RegId::X22, 31331));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 64592+23));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 31331+23));
        word_t val=0;
        acc0.readScratchPad(1, (i<<16) + 31331, (uint8_t*)&val);
        EXPECT_TRUE(val == 158u);
        acc0.readScratchPad(1, (i<<16) + 31332, (uint8_t*)&val);
        EXPECT_TRUE(val == 60u);
        acc0.readScratchPad(1, (i<<16) + 31333, (uint8_t*)&val);
        EXPECT_TRUE(val == 239u);
        acc0.readScratchPad(1, (i<<16) + 31334, (uint8_t*)&val);
        EXPECT_TRUE(val == 78u);
        acc0.readScratchPad(1, (i<<16) + 31335, (uint8_t*)&val);
        EXPECT_TRUE(val == 21u);
        acc0.readScratchPad(1, (i<<16) + 31336, (uint8_t*)&val);
        EXPECT_TRUE(val == 134u);
        acc0.readScratchPad(1, (i<<16) + 31337, (uint8_t*)&val);
        EXPECT_TRUE(val == 168u);
        acc0.readScratchPad(1, (i<<16) + 31338, (uint8_t*)&val);
        EXPECT_TRUE(val == 31u);
        acc0.readScratchPad(1, (i<<16) + 31339, (uint8_t*)&val);
        EXPECT_TRUE(val == 73u);
        acc0.readScratchPad(1, (i<<16) + 31340, (uint8_t*)&val);
        EXPECT_TRUE(val == 59u);
        acc0.readScratchPad(1, (i<<16) + 31341, (uint8_t*)&val);
        EXPECT_TRUE(val == 39u);
        acc0.readScratchPad(1, (i<<16) + 31342, (uint8_t*)&val);
        EXPECT_TRUE(val == 253u);
        acc0.readScratchPad(1, (i<<16) + 31343, (uint8_t*)&val);
        EXPECT_TRUE(val == 217u);
        acc0.readScratchPad(1, (i<<16) + 31344, (uint8_t*)&val);
        EXPECT_TRUE(val == 70u);
        acc0.readScratchPad(1, (i<<16) + 31345, (uint8_t*)&val);
        EXPECT_TRUE(val == 183u);
        acc0.readScratchPad(1, (i<<16) + 31346, (uint8_t*)&val);
        EXPECT_TRUE(val == 197u);
        acc0.readScratchPad(1, (i<<16) + 31347, (uint8_t*)&val);
        EXPECT_TRUE(val == 2u);
        acc0.readScratchPad(1, (i<<16) + 31348, (uint8_t*)&val);
        EXPECT_TRUE(val == 18u);
        acc0.readScratchPad(1, (i<<16) + 31349, (uint8_t*)&val);
        EXPECT_TRUE(val == 243u);
        acc0.readScratchPad(1, (i<<16) + 31350, (uint8_t*)&val);
        EXPECT_TRUE(val == 101u);
        acc0.readScratchPad(1, (i<<16) + 31351, (uint8_t*)&val);
        EXPECT_TRUE(val == 182u);
        acc0.readScratchPad(1, (i<<16) + 31352, (uint8_t*)&val);
        EXPECT_TRUE(val == 172u);
        acc0.readScratchPad(1, (i<<16) + 31353, (uint8_t*)&val);
        EXPECT_TRUE(val == 253u);
    }
}
TEST_F(bcpylli, Basic_bcpylli_12){
    acc0.initSetup(0, "testprogs/binaries/bcpylli_12.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X21, 15917));
        EXPECT_TRUE(acc0.testReg(i, RegId::X22, 51816));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 15917+29));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 51816+29));
        word_t val=0;
        acc0.readScratchPad(1, (i<<16) + 51816, (uint8_t*)&val);
        EXPECT_TRUE(val == 221u);
        acc0.readScratchPad(1, (i<<16) + 51817, (uint8_t*)&val);
        EXPECT_TRUE(val == 93u);
        acc0.readScratchPad(1, (i<<16) + 51818, (uint8_t*)&val);
        EXPECT_TRUE(val == 59u);
        acc0.readScratchPad(1, (i<<16) + 51819, (uint8_t*)&val);
        EXPECT_TRUE(val == 85u);
        acc0.readScratchPad(1, (i<<16) + 51820, (uint8_t*)&val);
        EXPECT_TRUE(val == 38u);
        acc0.readScratchPad(1, (i<<16) + 51821, (uint8_t*)&val);
        EXPECT_TRUE(val == 223u);
        acc0.readScratchPad(1, (i<<16) + 51822, (uint8_t*)&val);
        EXPECT_TRUE(val == 10u);
        acc0.readScratchPad(1, (i<<16) + 51823, (uint8_t*)&val);
        EXPECT_TRUE(val == 45u);
        acc0.readScratchPad(1, (i<<16) + 51824, (uint8_t*)&val);
        EXPECT_TRUE(val == 170u);
        acc0.readScratchPad(1, (i<<16) + 51825, (uint8_t*)&val);
        EXPECT_TRUE(val == 207u);
        acc0.readScratchPad(1, (i<<16) + 51826, (uint8_t*)&val);
        EXPECT_TRUE(val == 222u);
        acc0.readScratchPad(1, (i<<16) + 51827, (uint8_t*)&val);
        EXPECT_TRUE(val == 67u);
        acc0.readScratchPad(1, (i<<16) + 51828, (uint8_t*)&val);
        EXPECT_TRUE(val == 8u);
        acc0.readScratchPad(1, (i<<16) + 51829, (uint8_t*)&val);
        EXPECT_TRUE(val == 221u);
        acc0.readScratchPad(1, (i<<16) + 51830, (uint8_t*)&val);
        EXPECT_TRUE(val == 24u);
        acc0.readScratchPad(1, (i<<16) + 51831, (uint8_t*)&val);
        EXPECT_TRUE(val == 231u);
        acc0.readScratchPad(1, (i<<16) + 51832, (uint8_t*)&val);
        EXPECT_TRUE(val == 6u);
        acc0.readScratchPad(1, (i<<16) + 51833, (uint8_t*)&val);
        EXPECT_TRUE(val == 134u);
        acc0.readScratchPad(1, (i<<16) + 51834, (uint8_t*)&val);
        EXPECT_TRUE(val == 229u);
        acc0.readScratchPad(1, (i<<16) + 51835, (uint8_t*)&val);
        EXPECT_TRUE(val == 50u);
        acc0.readScratchPad(1, (i<<16) + 51836, (uint8_t*)&val);
        EXPECT_TRUE(val == 149u);
        acc0.readScratchPad(1, (i<<16) + 51837, (uint8_t*)&val);
        EXPECT_TRUE(val == 14u);
        acc0.readScratchPad(1, (i<<16) + 51838, (uint8_t*)&val);
        EXPECT_TRUE(val == 227u);
        acc0.readScratchPad(1, (i<<16) + 51839, (uint8_t*)&val);
        EXPECT_TRUE(val == 71u);
        acc0.readScratchPad(1, (i<<16) + 51840, (uint8_t*)&val);
        EXPECT_TRUE(val == 222u);
        acc0.readScratchPad(1, (i<<16) + 51841, (uint8_t*)&val);
        EXPECT_TRUE(val == 182u);
        acc0.readScratchPad(1, (i<<16) + 51842, (uint8_t*)&val);
        EXPECT_TRUE(val == 132u);
        acc0.readScratchPad(1, (i<<16) + 51843, (uint8_t*)&val);
        EXPECT_TRUE(val == 31u);
        acc0.readScratchPad(1, (i<<16) + 51844, (uint8_t*)&val);
        EXPECT_TRUE(val == 10u);
    }
}
TEST_F(bcpylli, Basic_bcpylli_13){
    acc0.initSetup(0, "testprogs/binaries/bcpylli_13.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X21, 45090));
        EXPECT_TRUE(acc0.testReg(i, RegId::X22, 28106));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 45090+25));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 28106+25));
        word_t val=0;
        acc0.readScratchPad(1, (i<<16) + 28106, (uint8_t*)&val);
        EXPECT_TRUE(val == 73u);
        acc0.readScratchPad(1, (i<<16) + 28107, (uint8_t*)&val);
        EXPECT_TRUE(val == 141u);
        acc0.readScratchPad(1, (i<<16) + 28108, (uint8_t*)&val);
        EXPECT_TRUE(val == 12u);
        acc0.readScratchPad(1, (i<<16) + 28109, (uint8_t*)&val);
        EXPECT_TRUE(val == 10u);
        acc0.readScratchPad(1, (i<<16) + 28110, (uint8_t*)&val);
        EXPECT_TRUE(val == 37u);
        acc0.readScratchPad(1, (i<<16) + 28111, (uint8_t*)&val);
        EXPECT_TRUE(val == 198u);
        acc0.readScratchPad(1, (i<<16) + 28112, (uint8_t*)&val);
        EXPECT_TRUE(val == 65u);
        acc0.readScratchPad(1, (i<<16) + 28113, (uint8_t*)&val);
        EXPECT_TRUE(val == 221u);
        acc0.readScratchPad(1, (i<<16) + 28114, (uint8_t*)&val);
        EXPECT_TRUE(val == 249u);
        acc0.readScratchPad(1, (i<<16) + 28115, (uint8_t*)&val);
        EXPECT_TRUE(val == 181u);
        acc0.readScratchPad(1, (i<<16) + 28116, (uint8_t*)&val);
        EXPECT_TRUE(val == 251u);
        acc0.readScratchPad(1, (i<<16) + 28117, (uint8_t*)&val);
        EXPECT_TRUE(val == 233u);
        acc0.readScratchPad(1, (i<<16) + 28118, (uint8_t*)&val);
        EXPECT_TRUE(val == 148u);
        acc0.readScratchPad(1, (i<<16) + 28119, (uint8_t*)&val);
        EXPECT_TRUE(val == 69u);
        acc0.readScratchPad(1, (i<<16) + 28120, (uint8_t*)&val);
        EXPECT_TRUE(val == 195u);
        acc0.readScratchPad(1, (i<<16) + 28121, (uint8_t*)&val);
        EXPECT_TRUE(val == 98u);
        acc0.readScratchPad(1, (i<<16) + 28122, (uint8_t*)&val);
        EXPECT_TRUE(val == 180u);
        acc0.readScratchPad(1, (i<<16) + 28123, (uint8_t*)&val);
        EXPECT_TRUE(val == 159u);
        acc0.readScratchPad(1, (i<<16) + 28124, (uint8_t*)&val);
        EXPECT_TRUE(val == 255u);
        acc0.readScratchPad(1, (i<<16) + 28125, (uint8_t*)&val);
        EXPECT_TRUE(val == 92u);
        acc0.readScratchPad(1, (i<<16) + 28126, (uint8_t*)&val);
        EXPECT_TRUE(val == 85u);
        acc0.readScratchPad(1, (i<<16) + 28127, (uint8_t*)&val);
        EXPECT_TRUE(val == 185u);
        acc0.readScratchPad(1, (i<<16) + 28128, (uint8_t*)&val);
        EXPECT_TRUE(val == 91u);
        acc0.readScratchPad(1, (i<<16) + 28129, (uint8_t*)&val);
        EXPECT_TRUE(val == 220u);
        acc0.readScratchPad(1, (i<<16) + 28130, (uint8_t*)&val);
        EXPECT_TRUE(val == 18u);
    }
}
TEST_F(bcpylli, Basic_bcpylli_14){
    acc0.initSetup(0, "testprogs/binaries/bcpylli_14.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X21, 3272));
        EXPECT_TRUE(acc0.testReg(i, RegId::X22, 51281));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 3272+13));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 51281+13));
        word_t val=0;
        acc0.readScratchPad(1, (i<<16) + 51281, (uint8_t*)&val);
        EXPECT_TRUE(val == 90u);
        acc0.readScratchPad(1, (i<<16) + 51282, (uint8_t*)&val);
        EXPECT_TRUE(val == 0u);
        acc0.readScratchPad(1, (i<<16) + 51283, (uint8_t*)&val);
        EXPECT_TRUE(val == 240u);
        acc0.readScratchPad(1, (i<<16) + 51284, (uint8_t*)&val);
        EXPECT_TRUE(val == 104u);
        acc0.readScratchPad(1, (i<<16) + 51285, (uint8_t*)&val);
        EXPECT_TRUE(val == 108u);
        acc0.readScratchPad(1, (i<<16) + 51286, (uint8_t*)&val);
        EXPECT_TRUE(val == 26u);
        acc0.readScratchPad(1, (i<<16) + 51287, (uint8_t*)&val);
        EXPECT_TRUE(val == 215u);
        acc0.readScratchPad(1, (i<<16) + 51288, (uint8_t*)&val);
        EXPECT_TRUE(val == 205u);
        acc0.readScratchPad(1, (i<<16) + 51289, (uint8_t*)&val);
        EXPECT_TRUE(val == 167u);
        acc0.readScratchPad(1, (i<<16) + 51290, (uint8_t*)&val);
        EXPECT_TRUE(val == 90u);
        acc0.readScratchPad(1, (i<<16) + 51291, (uint8_t*)&val);
        EXPECT_TRUE(val == 190u);
        acc0.readScratchPad(1, (i<<16) + 51292, (uint8_t*)&val);
        EXPECT_TRUE(val == 231u);
        acc0.readScratchPad(1, (i<<16) + 51293, (uint8_t*)&val);
        EXPECT_TRUE(val == 165u);
    }
}
TEST_F(bcpylli, Basic_bcpylli_15){
    acc0.initSetup(0, "testprogs/binaries/bcpylli_15.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X21, 45568));
        EXPECT_TRUE(acc0.testReg(i, RegId::X22, 54695));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 45568+12));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 54695+12));
        word_t val=0;
        acc0.readScratchPad(1, (i<<16) + 54695, (uint8_t*)&val);
        EXPECT_TRUE(val == 126u);
        acc0.readScratchPad(1, (i<<16) + 54696, (uint8_t*)&val);
        EXPECT_TRUE(val == 13u);
        acc0.readScratchPad(1, (i<<16) + 54697, (uint8_t*)&val);
        EXPECT_TRUE(val == 78u);
        acc0.readScratchPad(1, (i<<16) + 54698, (uint8_t*)&val);
        EXPECT_TRUE(val == 230u);
        acc0.readScratchPad(1, (i<<16) + 54699, (uint8_t*)&val);
        EXPECT_TRUE(val == 161u);
        acc0.readScratchPad(1, (i<<16) + 54700, (uint8_t*)&val);
        EXPECT_TRUE(val == 224u);
        acc0.readScratchPad(1, (i<<16) + 54701, (uint8_t*)&val);
        EXPECT_TRUE(val == 142u);
        acc0.readScratchPad(1, (i<<16) + 54702, (uint8_t*)&val);
        EXPECT_TRUE(val == 162u);
        acc0.readScratchPad(1, (i<<16) + 54703, (uint8_t*)&val);
        EXPECT_TRUE(val == 62u);
        acc0.readScratchPad(1, (i<<16) + 54704, (uint8_t*)&val);
        EXPECT_TRUE(val == 50u);
        acc0.readScratchPad(1, (i<<16) + 54705, (uint8_t*)&val);
        EXPECT_TRUE(val == 138u);
        acc0.readScratchPad(1, (i<<16) + 54706, (uint8_t*)&val);
        EXPECT_TRUE(val == 24u);
    }
}
TEST_F(bcpylli, Basic_bcpylli_16){
    acc0.initSetup(0, "testprogs/binaries/bcpylli_16.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X21, 28330));
        EXPECT_TRUE(acc0.testReg(i, RegId::X22, 29206));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 28330+20));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 29206+20));
        word_t val=0;
        acc0.readScratchPad(1, (i<<16) + 29206, (uint8_t*)&val);
        EXPECT_TRUE(val == 104u);
        acc0.readScratchPad(1, (i<<16) + 29207, (uint8_t*)&val);
        EXPECT_TRUE(val == 79u);
        acc0.readScratchPad(1, (i<<16) + 29208, (uint8_t*)&val);
        EXPECT_TRUE(val == 224u);
        acc0.readScratchPad(1, (i<<16) + 29209, (uint8_t*)&val);
        EXPECT_TRUE(val == 68u);
        acc0.readScratchPad(1, (i<<16) + 29210, (uint8_t*)&val);
        EXPECT_TRUE(val == 136u);
        acc0.readScratchPad(1, (i<<16) + 29211, (uint8_t*)&val);
        EXPECT_TRUE(val == 101u);
        acc0.readScratchPad(1, (i<<16) + 29212, (uint8_t*)&val);
        EXPECT_TRUE(val == 93u);
        acc0.readScratchPad(1, (i<<16) + 29213, (uint8_t*)&val);
        EXPECT_TRUE(val == 89u);
        acc0.readScratchPad(1, (i<<16) + 29214, (uint8_t*)&val);
        EXPECT_TRUE(val == 196u);
        acc0.readScratchPad(1, (i<<16) + 29215, (uint8_t*)&val);
        EXPECT_TRUE(val == 144u);
        acc0.readScratchPad(1, (i<<16) + 29216, (uint8_t*)&val);
        EXPECT_TRUE(val == 104u);
        acc0.readScratchPad(1, (i<<16) + 29217, (uint8_t*)&val);
        EXPECT_TRUE(val == 112u);
        acc0.readScratchPad(1, (i<<16) + 29218, (uint8_t*)&val);
        EXPECT_TRUE(val == 32u);
        acc0.readScratchPad(1, (i<<16) + 29219, (uint8_t*)&val);
        EXPECT_TRUE(val == 69u);
        acc0.readScratchPad(1, (i<<16) + 29220, (uint8_t*)&val);
        EXPECT_TRUE(val == 17u);
        acc0.readScratchPad(1, (i<<16) + 29221, (uint8_t*)&val);
        EXPECT_TRUE(val == 164u);
        acc0.readScratchPad(1, (i<<16) + 29222, (uint8_t*)&val);
        EXPECT_TRUE(val == 71u);
        acc0.readScratchPad(1, (i<<16) + 29223, (uint8_t*)&val);
        EXPECT_TRUE(val == 215u);
        acc0.readScratchPad(1, (i<<16) + 29224, (uint8_t*)&val);
        EXPECT_TRUE(val == 127u);
        acc0.readScratchPad(1, (i<<16) + 29225, (uint8_t*)&val);
        EXPECT_TRUE(val == 76u);
    }
}
TEST_F(bcpylli, Basic_bcpylli_17){
    acc0.initSetup(0, "testprogs/binaries/bcpylli_17.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X21, 15130));
        EXPECT_TRUE(acc0.testReg(i, RegId::X22, 44688));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 15130+9));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 44688+9));
        word_t val=0;
        acc0.readScratchPad(1, (i<<16) + 44688, (uint8_t*)&val);
        EXPECT_TRUE(val == 29u);
        acc0.readScratchPad(1, (i<<16) + 44689, (uint8_t*)&val);
        EXPECT_TRUE(val == 66u);
        acc0.readScratchPad(1, (i<<16) + 44690, (uint8_t*)&val);
        EXPECT_TRUE(val == 84u);
        acc0.readScratchPad(1, (i<<16) + 44691, (uint8_t*)&val);
        EXPECT_TRUE(val == 50u);
        acc0.readScratchPad(1, (i<<16) + 44692, (uint8_t*)&val);
        EXPECT_TRUE(val == 232u);
        acc0.readScratchPad(1, (i<<16) + 44693, (uint8_t*)&val);
        EXPECT_TRUE(val == 225u);
        acc0.readScratchPad(1, (i<<16) + 44694, (uint8_t*)&val);
        EXPECT_TRUE(val == 77u);
        acc0.readScratchPad(1, (i<<16) + 44695, (uint8_t*)&val);
        EXPECT_TRUE(val == 68u);
        acc0.readScratchPad(1, (i<<16) + 44696, (uint8_t*)&val);
        EXPECT_TRUE(val == 64u);
    }
}
TEST_F(bcpylli, Basic_bcpylli_18){
    acc0.initSetup(0, "testprogs/binaries/bcpylli_18.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X21, 43510));
        EXPECT_TRUE(acc0.testReg(i, RegId::X22, 29557));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 43510+17));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 29557+17));
        word_t val=0;
        acc0.readScratchPad(1, (i<<16) + 29557, (uint8_t*)&val);
        EXPECT_TRUE(val == 236u);
        acc0.readScratchPad(1, (i<<16) + 29558, (uint8_t*)&val);
        EXPECT_TRUE(val == 199u);
        acc0.readScratchPad(1, (i<<16) + 29559, (uint8_t*)&val);
        EXPECT_TRUE(val == 77u);
        acc0.readScratchPad(1, (i<<16) + 29560, (uint8_t*)&val);
        EXPECT_TRUE(val == 148u);
        acc0.readScratchPad(1, (i<<16) + 29561, (uint8_t*)&val);
        EXPECT_TRUE(val == 239u);
        acc0.readScratchPad(1, (i<<16) + 29562, (uint8_t*)&val);
        EXPECT_TRUE(val == 59u);
        acc0.readScratchPad(1, (i<<16) + 29563, (uint8_t*)&val);
        EXPECT_TRUE(val == 253u);
        acc0.readScratchPad(1, (i<<16) + 29564, (uint8_t*)&val);
        EXPECT_TRUE(val == 140u);
        acc0.readScratchPad(1, (i<<16) + 29565, (uint8_t*)&val);
        EXPECT_TRUE(val == 36u);
        acc0.readScratchPad(1, (i<<16) + 29566, (uint8_t*)&val);
        EXPECT_TRUE(val == 97u);
        acc0.readScratchPad(1, (i<<16) + 29567, (uint8_t*)&val);
        EXPECT_TRUE(val == 160u);
        acc0.readScratchPad(1, (i<<16) + 29568, (uint8_t*)&val);
        EXPECT_TRUE(val == 61u);
        acc0.readScratchPad(1, (i<<16) + 29569, (uint8_t*)&val);
        EXPECT_TRUE(val == 72u);
        acc0.readScratchPad(1, (i<<16) + 29570, (uint8_t*)&val);
        EXPECT_TRUE(val == 51u);
        acc0.readScratchPad(1, (i<<16) + 29571, (uint8_t*)&val);
        EXPECT_TRUE(val == 232u);
        acc0.readScratchPad(1, (i<<16) + 29572, (uint8_t*)&val);
        EXPECT_TRUE(val == 123u);
        acc0.readScratchPad(1, (i<<16) + 29573, (uint8_t*)&val);
        EXPECT_TRUE(val == 123u);
    }
}
TEST_F(bcpylli, Basic_bcpylli_19){
    acc0.initSetup(0, "testprogs/binaries/bcpylli_19.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X21, 61580));
        EXPECT_TRUE(acc0.testReg(i, RegId::X22, 32406));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 61580+8));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 32406+8));
        word_t val=0;
        acc0.readScratchPad(1, (i<<16) + 32406, (uint8_t*)&val);
        EXPECT_TRUE(val == 142u);
        acc0.readScratchPad(1, (i<<16) + 32407, (uint8_t*)&val);
        EXPECT_TRUE(val == 207u);
        acc0.readScratchPad(1, (i<<16) + 32408, (uint8_t*)&val);
        EXPECT_TRUE(val == 5u);
        acc0.readScratchPad(1, (i<<16) + 32409, (uint8_t*)&val);
        EXPECT_TRUE(val == 178u);
        acc0.readScratchPad(1, (i<<16) + 32410, (uint8_t*)&val);
        EXPECT_TRUE(val == 192u);
        acc0.readScratchPad(1, (i<<16) + 32411, (uint8_t*)&val);
        EXPECT_TRUE(val == 146u);
        acc0.readScratchPad(1, (i<<16) + 32412, (uint8_t*)&val);
        EXPECT_TRUE(val == 225u);
        acc0.readScratchPad(1, (i<<16) + 32413, (uint8_t*)&val);
        EXPECT_TRUE(val == 29u);
    }
}
