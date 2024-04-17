#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"

using namespace basim;

class bcpyll : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    int numLanes = 64;
    UDAccelerator acc0 = UDAccelerator(numLanes, 0, 1); // UDAccelerator(numLanes, UDID/networkID, lmmode (0: accelerator based addressing, 1:bank/lane based addressing))
    int buffsize1 = 1024;
    int buffsize2 = 1024;
};
TEST_F(bcpyll, Basic_bcpyll_0){
    acc0.initSetup(0, "testprogs/binaries/bcpyll_0.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X21, 32214));
        EXPECT_TRUE(acc0.testReg(i, RegId::X22, 18836));
        EXPECT_TRUE(acc0.testReg(i, RegId::X23, 24));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 32214+24));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 18836+24));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18,0));
        uint8_t val=0;
        acc0.readScratchPad(1, (i<<16) + 18836, (uint8_t*)&val);
        EXPECT_TRUE(val == 186u);
        acc0.readScratchPad(1, (i<<16) + 18837, (uint8_t*)&val);
        EXPECT_TRUE(val == 217u);
        acc0.readScratchPad(1, (i<<16) + 18838, (uint8_t*)&val);
        EXPECT_TRUE(val == 132u);
        acc0.readScratchPad(1, (i<<16) + 18839, (uint8_t*)&val);
        EXPECT_TRUE(val == 95u);
        acc0.readScratchPad(1, (i<<16) + 18840, (uint8_t*)&val);
        EXPECT_TRUE(val == 213u);
        acc0.readScratchPad(1, (i<<16) + 18841, (uint8_t*)&val);
        EXPECT_TRUE(val == 14u);
        acc0.readScratchPad(1, (i<<16) + 18842, (uint8_t*)&val);
        EXPECT_TRUE(val == 43u);
        acc0.readScratchPad(1, (i<<16) + 18843, (uint8_t*)&val);
        EXPECT_TRUE(val == 63u);
        acc0.readScratchPad(1, (i<<16) + 18844, (uint8_t*)&val);
        EXPECT_TRUE(val == 210u);
        acc0.readScratchPad(1, (i<<16) + 18845, (uint8_t*)&val);
        EXPECT_TRUE(val == 94u);
        acc0.readScratchPad(1, (i<<16) + 18846, (uint8_t*)&val);
        EXPECT_TRUE(val == 123u);
        acc0.readScratchPad(1, (i<<16) + 18847, (uint8_t*)&val);
        EXPECT_TRUE(val == 108u);
        acc0.readScratchPad(1, (i<<16) + 18848, (uint8_t*)&val);
        EXPECT_TRUE(val == 143u);
        acc0.readScratchPad(1, (i<<16) + 18849, (uint8_t*)&val);
        EXPECT_TRUE(val == 172u);
        acc0.readScratchPad(1, (i<<16) + 18850, (uint8_t*)&val);
        EXPECT_TRUE(val == 88u);
        acc0.readScratchPad(1, (i<<16) + 18851, (uint8_t*)&val);
        EXPECT_TRUE(val == 70u);
        acc0.readScratchPad(1, (i<<16) + 18852, (uint8_t*)&val);
        EXPECT_TRUE(val == 119u);
        acc0.readScratchPad(1, (i<<16) + 18853, (uint8_t*)&val);
        EXPECT_TRUE(val == 202u);
        acc0.readScratchPad(1, (i<<16) + 18854, (uint8_t*)&val);
        EXPECT_TRUE(val == 128u);
        acc0.readScratchPad(1, (i<<16) + 18855, (uint8_t*)&val);
        EXPECT_TRUE(val == 187u);
        acc0.readScratchPad(1, (i<<16) + 18856, (uint8_t*)&val);
        EXPECT_TRUE(val == 106u);
        acc0.readScratchPad(1, (i<<16) + 18857, (uint8_t*)&val);
        EXPECT_TRUE(val == 193u);
        acc0.readScratchPad(1, (i<<16) + 18858, (uint8_t*)&val);
        EXPECT_TRUE(val == 134u);
        acc0.readScratchPad(1, (i<<16) + 18859, (uint8_t*)&val);
        EXPECT_TRUE(val == 100u);
    }
}
TEST_F(bcpyll, Basic_bcpyll_1){
    acc0.initSetup(0, "testprogs/binaries/bcpyll_1.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X21, 37859));
        EXPECT_TRUE(acc0.testReg(i, RegId::X22, 46220));
        EXPECT_TRUE(acc0.testReg(i, RegId::X23, 6));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 37859+6));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 46220+6));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18,0));
        uint8_t val=0;
        acc0.readScratchPad(1, (i<<16) + 46220, (uint8_t*)&val);
        EXPECT_TRUE(val == 204u);
        acc0.readScratchPad(1, (i<<16) + 46221, (uint8_t*)&val);
        EXPECT_TRUE(val == 244u);
        acc0.readScratchPad(1, (i<<16) + 46222, (uint8_t*)&val);
        EXPECT_TRUE(val == 215u);
        acc0.readScratchPad(1, (i<<16) + 46223, (uint8_t*)&val);
        EXPECT_TRUE(val == 164u);
        acc0.readScratchPad(1, (i<<16) + 46224, (uint8_t*)&val);
        EXPECT_TRUE(val == 66u);
        acc0.readScratchPad(1, (i<<16) + 46225, (uint8_t*)&val);
        EXPECT_TRUE(val == 99u);
    }
}
TEST_F(bcpyll, Basic_bcpyll_2){
    acc0.initSetup(0, "testprogs/binaries/bcpyll_2.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X21, 53499));
        EXPECT_TRUE(acc0.testReg(i, RegId::X22, 6092));
        EXPECT_TRUE(acc0.testReg(i, RegId::X23, 30));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 53499+30));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 6092+30));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18,0));
        uint8_t val=0;
        acc0.readScratchPad(1, (i<<16) + 6092, (uint8_t*)&val);
        EXPECT_TRUE(val == 243u);
        acc0.readScratchPad(1, (i<<16) + 6093, (uint8_t*)&val);
        EXPECT_TRUE(val == 191u);
        acc0.readScratchPad(1, (i<<16) + 6094, (uint8_t*)&val);
        EXPECT_TRUE(val == 109u);
        acc0.readScratchPad(1, (i<<16) + 6095, (uint8_t*)&val);
        EXPECT_TRUE(val == 121u);
        acc0.readScratchPad(1, (i<<16) + 6096, (uint8_t*)&val);
        EXPECT_TRUE(val == 100u);
        acc0.readScratchPad(1, (i<<16) + 6097, (uint8_t*)&val);
        EXPECT_TRUE(val == 45u);
        acc0.readScratchPad(1, (i<<16) + 6098, (uint8_t*)&val);
        EXPECT_TRUE(val == 185u);
        acc0.readScratchPad(1, (i<<16) + 6099, (uint8_t*)&val);
        EXPECT_TRUE(val == 53u);
        acc0.readScratchPad(1, (i<<16) + 6100, (uint8_t*)&val);
        EXPECT_TRUE(val == 40u);
        acc0.readScratchPad(1, (i<<16) + 6101, (uint8_t*)&val);
        EXPECT_TRUE(val == 212u);
        acc0.readScratchPad(1, (i<<16) + 6102, (uint8_t*)&val);
        EXPECT_TRUE(val == 45u);
        acc0.readScratchPad(1, (i<<16) + 6103, (uint8_t*)&val);
        EXPECT_TRUE(val == 60u);
        acc0.readScratchPad(1, (i<<16) + 6104, (uint8_t*)&val);
        EXPECT_TRUE(val == 72u);
        acc0.readScratchPad(1, (i<<16) + 6105, (uint8_t*)&val);
        EXPECT_TRUE(val == 194u);
        acc0.readScratchPad(1, (i<<16) + 6106, (uint8_t*)&val);
        EXPECT_TRUE(val == 37u);
        acc0.readScratchPad(1, (i<<16) + 6107, (uint8_t*)&val);
        EXPECT_TRUE(val == 138u);
        acc0.readScratchPad(1, (i<<16) + 6108, (uint8_t*)&val);
        EXPECT_TRUE(val == 112u);
        acc0.readScratchPad(1, (i<<16) + 6109, (uint8_t*)&val);
        EXPECT_TRUE(val == 36u);
        acc0.readScratchPad(1, (i<<16) + 6110, (uint8_t*)&val);
        EXPECT_TRUE(val == 136u);
        acc0.readScratchPad(1, (i<<16) + 6111, (uint8_t*)&val);
        EXPECT_TRUE(val == 120u);
        acc0.readScratchPad(1, (i<<16) + 6112, (uint8_t*)&val);
        EXPECT_TRUE(val == 2u);
        acc0.readScratchPad(1, (i<<16) + 6113, (uint8_t*)&val);
        EXPECT_TRUE(val == 249u);
        acc0.readScratchPad(1, (i<<16) + 6114, (uint8_t*)&val);
        EXPECT_TRUE(val == 29u);
        acc0.readScratchPad(1, (i<<16) + 6115, (uint8_t*)&val);
        EXPECT_TRUE(val == 125u);
        acc0.readScratchPad(1, (i<<16) + 6116, (uint8_t*)&val);
        EXPECT_TRUE(val == 20u);
        acc0.readScratchPad(1, (i<<16) + 6117, (uint8_t*)&val);
        EXPECT_TRUE(val == 80u);
        acc0.readScratchPad(1, (i<<16) + 6118, (uint8_t*)&val);
        EXPECT_TRUE(val == 7u);
        acc0.readScratchPad(1, (i<<16) + 6119, (uint8_t*)&val);
        EXPECT_TRUE(val == 62u);
        acc0.readScratchPad(1, (i<<16) + 6120, (uint8_t*)&val);
        EXPECT_TRUE(val == 179u);
        acc0.readScratchPad(1, (i<<16) + 6121, (uint8_t*)&val);
        EXPECT_TRUE(val == 118u);
    }
}
TEST_F(bcpyll, Basic_bcpyll_3){
    acc0.initSetup(0, "testprogs/binaries/bcpyll_3.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X21, 32070));
        EXPECT_TRUE(acc0.testReg(i, RegId::X22, 7718));
        EXPECT_TRUE(acc0.testReg(i, RegId::X23, 26));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 32070+26));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 7718+26));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18,0));
        uint8_t val=0;
        acc0.readScratchPad(1, (i<<16) + 7718, (uint8_t*)&val);
        EXPECT_TRUE(val == 85u);
        acc0.readScratchPad(1, (i<<16) + 7719, (uint8_t*)&val);
        EXPECT_TRUE(val == 178u);
        acc0.readScratchPad(1, (i<<16) + 7720, (uint8_t*)&val);
        EXPECT_TRUE(val == 149u);
        acc0.readScratchPad(1, (i<<16) + 7721, (uint8_t*)&val);
        EXPECT_TRUE(val == 111u);
        acc0.readScratchPad(1, (i<<16) + 7722, (uint8_t*)&val);
        EXPECT_TRUE(val == 102u);
        acc0.readScratchPad(1, (i<<16) + 7723, (uint8_t*)&val);
        EXPECT_TRUE(val == 15u);
        acc0.readScratchPad(1, (i<<16) + 7724, (uint8_t*)&val);
        EXPECT_TRUE(val == 157u);
        acc0.readScratchPad(1, (i<<16) + 7725, (uint8_t*)&val);
        EXPECT_TRUE(val == 112u);
        acc0.readScratchPad(1, (i<<16) + 7726, (uint8_t*)&val);
        EXPECT_TRUE(val == 198u);
        acc0.readScratchPad(1, (i<<16) + 7727, (uint8_t*)&val);
        EXPECT_TRUE(val == 199u);
        acc0.readScratchPad(1, (i<<16) + 7728, (uint8_t*)&val);
        EXPECT_TRUE(val == 246u);
        acc0.readScratchPad(1, (i<<16) + 7729, (uint8_t*)&val);
        EXPECT_TRUE(val == 220u);
        acc0.readScratchPad(1, (i<<16) + 7730, (uint8_t*)&val);
        EXPECT_TRUE(val == 23u);
        acc0.readScratchPad(1, (i<<16) + 7731, (uint8_t*)&val);
        EXPECT_TRUE(val == 51u);
        acc0.readScratchPad(1, (i<<16) + 7732, (uint8_t*)&val);
        EXPECT_TRUE(val == 53u);
        acc0.readScratchPad(1, (i<<16) + 7733, (uint8_t*)&val);
        EXPECT_TRUE(val == 244u);
        acc0.readScratchPad(1, (i<<16) + 7734, (uint8_t*)&val);
        EXPECT_TRUE(val == 197u);
        acc0.readScratchPad(1, (i<<16) + 7735, (uint8_t*)&val);
        EXPECT_TRUE(val == 135u);
        acc0.readScratchPad(1, (i<<16) + 7736, (uint8_t*)&val);
        EXPECT_TRUE(val == 82u);
        acc0.readScratchPad(1, (i<<16) + 7737, (uint8_t*)&val);
        EXPECT_TRUE(val == 244u);
        acc0.readScratchPad(1, (i<<16) + 7738, (uint8_t*)&val);
        EXPECT_TRUE(val == 237u);
        acc0.readScratchPad(1, (i<<16) + 7739, (uint8_t*)&val);
        EXPECT_TRUE(val == 221u);
        acc0.readScratchPad(1, (i<<16) + 7740, (uint8_t*)&val);
        EXPECT_TRUE(val == 48u);
        acc0.readScratchPad(1, (i<<16) + 7741, (uint8_t*)&val);
        EXPECT_TRUE(val == 67u);
        acc0.readScratchPad(1, (i<<16) + 7742, (uint8_t*)&val);
        EXPECT_TRUE(val == 37u);
        acc0.readScratchPad(1, (i<<16) + 7743, (uint8_t*)&val);
        EXPECT_TRUE(val == 137u);
    }
}
TEST_F(bcpyll, Basic_bcpyll_4){
    acc0.initSetup(0, "testprogs/binaries/bcpyll_4.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X21, 12308));
        EXPECT_TRUE(acc0.testReg(i, RegId::X22, 24050));
        EXPECT_TRUE(acc0.testReg(i, RegId::X23, 4));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 12308+4));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 24050+4));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18,0));
        uint8_t val=0;
        acc0.readScratchPad(1, (i<<16) + 24050, (uint8_t*)&val);
        EXPECT_TRUE(val == 197u);
        acc0.readScratchPad(1, (i<<16) + 24051, (uint8_t*)&val);
        EXPECT_TRUE(val == 0u);
        acc0.readScratchPad(1, (i<<16) + 24052, (uint8_t*)&val);
        EXPECT_TRUE(val == 109u);
        acc0.readScratchPad(1, (i<<16) + 24053, (uint8_t*)&val);
        EXPECT_TRUE(val == 243u);
    }
}
TEST_F(bcpyll, Basic_bcpyll_5){
    acc0.initSetup(0, "testprogs/binaries/bcpyll_5.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X21, 22490));
        EXPECT_TRUE(acc0.testReg(i, RegId::X22, 32304));
        EXPECT_TRUE(acc0.testReg(i, RegId::X23, 24));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 22490+24));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 32304+24));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18,0));
        uint8_t val=0;
        acc0.readScratchPad(1, (i<<16) + 32304, (uint8_t*)&val);
        EXPECT_TRUE(val == 168u);
        acc0.readScratchPad(1, (i<<16) + 32305, (uint8_t*)&val);
        EXPECT_TRUE(val == 232u);
        acc0.readScratchPad(1, (i<<16) + 32306, (uint8_t*)&val);
        EXPECT_TRUE(val == 69u);
        acc0.readScratchPad(1, (i<<16) + 32307, (uint8_t*)&val);
        EXPECT_TRUE(val == 110u);
        acc0.readScratchPad(1, (i<<16) + 32308, (uint8_t*)&val);
        EXPECT_TRUE(val == 212u);
        acc0.readScratchPad(1, (i<<16) + 32309, (uint8_t*)&val);
        EXPECT_TRUE(val == 141u);
        acc0.readScratchPad(1, (i<<16) + 32310, (uint8_t*)&val);
        EXPECT_TRUE(val == 204u);
        acc0.readScratchPad(1, (i<<16) + 32311, (uint8_t*)&val);
        EXPECT_TRUE(val == 152u);
        acc0.readScratchPad(1, (i<<16) + 32312, (uint8_t*)&val);
        EXPECT_TRUE(val == 80u);
        acc0.readScratchPad(1, (i<<16) + 32313, (uint8_t*)&val);
        EXPECT_TRUE(val == 248u);
        acc0.readScratchPad(1, (i<<16) + 32314, (uint8_t*)&val);
        EXPECT_TRUE(val == 120u);
        acc0.readScratchPad(1, (i<<16) + 32315, (uint8_t*)&val);
        EXPECT_TRUE(val == 122u);
        acc0.readScratchPad(1, (i<<16) + 32316, (uint8_t*)&val);
        EXPECT_TRUE(val == 103u);
        acc0.readScratchPad(1, (i<<16) + 32317, (uint8_t*)&val);
        EXPECT_TRUE(val == 52u);
        acc0.readScratchPad(1, (i<<16) + 32318, (uint8_t*)&val);
        EXPECT_TRUE(val == 29u);
        acc0.readScratchPad(1, (i<<16) + 32319, (uint8_t*)&val);
        EXPECT_TRUE(val == 126u);
        acc0.readScratchPad(1, (i<<16) + 32320, (uint8_t*)&val);
        EXPECT_TRUE(val == 198u);
        acc0.readScratchPad(1, (i<<16) + 32321, (uint8_t*)&val);
        EXPECT_TRUE(val == 83u);
        acc0.readScratchPad(1, (i<<16) + 32322, (uint8_t*)&val);
        EXPECT_TRUE(val == 147u);
        acc0.readScratchPad(1, (i<<16) + 32323, (uint8_t*)&val);
        EXPECT_TRUE(val == 131u);
        acc0.readScratchPad(1, (i<<16) + 32324, (uint8_t*)&val);
        EXPECT_TRUE(val == 61u);
        acc0.readScratchPad(1, (i<<16) + 32325, (uint8_t*)&val);
        EXPECT_TRUE(val == 117u);
        acc0.readScratchPad(1, (i<<16) + 32326, (uint8_t*)&val);
        EXPECT_TRUE(val == 99u);
        acc0.readScratchPad(1, (i<<16) + 32327, (uint8_t*)&val);
        EXPECT_TRUE(val == 214u);
    }
}
TEST_F(bcpyll, Basic_bcpyll_6){
    acc0.initSetup(0, "testprogs/binaries/bcpyll_6.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X21, 14479));
        EXPECT_TRUE(acc0.testReg(i, RegId::X22, 52904));
        EXPECT_TRUE(acc0.testReg(i, RegId::X23, 28));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 14479+28));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 52904+28));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18,0));
        uint8_t val=0;
        acc0.readScratchPad(1, (i<<16) + 52904, (uint8_t*)&val);
        EXPECT_TRUE(val == 69u);
        acc0.readScratchPad(1, (i<<16) + 52905, (uint8_t*)&val);
        EXPECT_TRUE(val == 95u);
        acc0.readScratchPad(1, (i<<16) + 52906, (uint8_t*)&val);
        EXPECT_TRUE(val == 221u);
        acc0.readScratchPad(1, (i<<16) + 52907, (uint8_t*)&val);
        EXPECT_TRUE(val == 178u);
        acc0.readScratchPad(1, (i<<16) + 52908, (uint8_t*)&val);
        EXPECT_TRUE(val == 157u);
        acc0.readScratchPad(1, (i<<16) + 52909, (uint8_t*)&val);
        EXPECT_TRUE(val == 244u);
        acc0.readScratchPad(1, (i<<16) + 52910, (uint8_t*)&val);
        EXPECT_TRUE(val == 131u);
        acc0.readScratchPad(1, (i<<16) + 52911, (uint8_t*)&val);
        EXPECT_TRUE(val == 224u);
        acc0.readScratchPad(1, (i<<16) + 52912, (uint8_t*)&val);
        EXPECT_TRUE(val == 78u);
        acc0.readScratchPad(1, (i<<16) + 52913, (uint8_t*)&val);
        EXPECT_TRUE(val == 41u);
        acc0.readScratchPad(1, (i<<16) + 52914, (uint8_t*)&val);
        EXPECT_TRUE(val == 165u);
        acc0.readScratchPad(1, (i<<16) + 52915, (uint8_t*)&val);
        EXPECT_TRUE(val == 153u);
        acc0.readScratchPad(1, (i<<16) + 52916, (uint8_t*)&val);
        EXPECT_TRUE(val == 72u);
        acc0.readScratchPad(1, (i<<16) + 52917, (uint8_t*)&val);
        EXPECT_TRUE(val == 225u);
        acc0.readScratchPad(1, (i<<16) + 52918, (uint8_t*)&val);
        EXPECT_TRUE(val == 249u);
        acc0.readScratchPad(1, (i<<16) + 52919, (uint8_t*)&val);
        EXPECT_TRUE(val == 131u);
        acc0.readScratchPad(1, (i<<16) + 52920, (uint8_t*)&val);
        EXPECT_TRUE(val == 142u);
        acc0.readScratchPad(1, (i<<16) + 52921, (uint8_t*)&val);
        EXPECT_TRUE(val == 57u);
        acc0.readScratchPad(1, (i<<16) + 52922, (uint8_t*)&val);
        EXPECT_TRUE(val == 101u);
        acc0.readScratchPad(1, (i<<16) + 52923, (uint8_t*)&val);
        EXPECT_TRUE(val == 67u);
        acc0.readScratchPad(1, (i<<16) + 52924, (uint8_t*)&val);
        EXPECT_TRUE(val == 236u);
        acc0.readScratchPad(1, (i<<16) + 52925, (uint8_t*)&val);
        EXPECT_TRUE(val == 246u);
        acc0.readScratchPad(1, (i<<16) + 52926, (uint8_t*)&val);
        EXPECT_TRUE(val == 140u);
        acc0.readScratchPad(1, (i<<16) + 52927, (uint8_t*)&val);
        EXPECT_TRUE(val == 177u);
        acc0.readScratchPad(1, (i<<16) + 52928, (uint8_t*)&val);
        EXPECT_TRUE(val == 156u);
        acc0.readScratchPad(1, (i<<16) + 52929, (uint8_t*)&val);
        EXPECT_TRUE(val == 73u);
        acc0.readScratchPad(1, (i<<16) + 52930, (uint8_t*)&val);
        EXPECT_TRUE(val == 202u);
        acc0.readScratchPad(1, (i<<16) + 52931, (uint8_t*)&val);
        EXPECT_TRUE(val == 100u);
    }
}
TEST_F(bcpyll, Basic_bcpyll_7){
    acc0.initSetup(0, "testprogs/binaries/bcpyll_7.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X21, 13651));
        EXPECT_TRUE(acc0.testReg(i, RegId::X22, 1736));
        EXPECT_TRUE(acc0.testReg(i, RegId::X23, 30));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 13651+30));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 1736+30));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18,0));
        uint8_t val=0;
        acc0.readScratchPad(1, (i<<16) + 1736, (uint8_t*)&val);
        EXPECT_TRUE(val == 174u);
        acc0.readScratchPad(1, (i<<16) + 1737, (uint8_t*)&val);
        EXPECT_TRUE(val == 78u);
        acc0.readScratchPad(1, (i<<16) + 1738, (uint8_t*)&val);
        EXPECT_TRUE(val == 44u);
        acc0.readScratchPad(1, (i<<16) + 1739, (uint8_t*)&val);
        EXPECT_TRUE(val == 189u);
        acc0.readScratchPad(1, (i<<16) + 1740, (uint8_t*)&val);
        EXPECT_TRUE(val == 85u);
        acc0.readScratchPad(1, (i<<16) + 1741, (uint8_t*)&val);
        EXPECT_TRUE(val == 192u);
        acc0.readScratchPad(1, (i<<16) + 1742, (uint8_t*)&val);
        EXPECT_TRUE(val == 53u);
        acc0.readScratchPad(1, (i<<16) + 1743, (uint8_t*)&val);
        EXPECT_TRUE(val == 30u);
        acc0.readScratchPad(1, (i<<16) + 1744, (uint8_t*)&val);
        EXPECT_TRUE(val == 213u);
        acc0.readScratchPad(1, (i<<16) + 1745, (uint8_t*)&val);
        EXPECT_TRUE(val == 80u);
        acc0.readScratchPad(1, (i<<16) + 1746, (uint8_t*)&val);
        EXPECT_TRUE(val == 65u);
        acc0.readScratchPad(1, (i<<16) + 1747, (uint8_t*)&val);
        EXPECT_TRUE(val == 109u);
        acc0.readScratchPad(1, (i<<16) + 1748, (uint8_t*)&val);
        EXPECT_TRUE(val == 246u);
        acc0.readScratchPad(1, (i<<16) + 1749, (uint8_t*)&val);
        EXPECT_TRUE(val == 195u);
        acc0.readScratchPad(1, (i<<16) + 1750, (uint8_t*)&val);
        EXPECT_TRUE(val == 1u);
        acc0.readScratchPad(1, (i<<16) + 1751, (uint8_t*)&val);
        EXPECT_TRUE(val == 232u);
        acc0.readScratchPad(1, (i<<16) + 1752, (uint8_t*)&val);
        EXPECT_TRUE(val == 138u);
        acc0.readScratchPad(1, (i<<16) + 1753, (uint8_t*)&val);
        EXPECT_TRUE(val == 166u);
        acc0.readScratchPad(1, (i<<16) + 1754, (uint8_t*)&val);
        EXPECT_TRUE(val == 32u);
        acc0.readScratchPad(1, (i<<16) + 1755, (uint8_t*)&val);
        EXPECT_TRUE(val == 116u);
        acc0.readScratchPad(1, (i<<16) + 1756, (uint8_t*)&val);
        EXPECT_TRUE(val == 26u);
        acc0.readScratchPad(1, (i<<16) + 1757, (uint8_t*)&val);
        EXPECT_TRUE(val == 171u);
        acc0.readScratchPad(1, (i<<16) + 1758, (uint8_t*)&val);
        EXPECT_TRUE(val == 38u);
        acc0.readScratchPad(1, (i<<16) + 1759, (uint8_t*)&val);
        EXPECT_TRUE(val == 178u);
        acc0.readScratchPad(1, (i<<16) + 1760, (uint8_t*)&val);
        EXPECT_TRUE(val == 182u);
        acc0.readScratchPad(1, (i<<16) + 1761, (uint8_t*)&val);
        EXPECT_TRUE(val == 141u);
        acc0.readScratchPad(1, (i<<16) + 1762, (uint8_t*)&val);
        EXPECT_TRUE(val == 151u);
        acc0.readScratchPad(1, (i<<16) + 1763, (uint8_t*)&val);
        EXPECT_TRUE(val == 6u);
        acc0.readScratchPad(1, (i<<16) + 1764, (uint8_t*)&val);
        EXPECT_TRUE(val == 111u);
        acc0.readScratchPad(1, (i<<16) + 1765, (uint8_t*)&val);
        EXPECT_TRUE(val == 149u);
    }
}
TEST_F(bcpyll, Basic_bcpyll_8){
    acc0.initSetup(0, "testprogs/binaries/bcpyll_8.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X21, 51245));
        EXPECT_TRUE(acc0.testReg(i, RegId::X22, 63963));
        EXPECT_TRUE(acc0.testReg(i, RegId::X23, 27));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 51245+27));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 63963+27));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18,0));
        uint8_t val=0;
        acc0.readScratchPad(1, (i<<16) + 63963, (uint8_t*)&val);
        EXPECT_TRUE(val == 61u);
        acc0.readScratchPad(1, (i<<16) + 63964, (uint8_t*)&val);
        EXPECT_TRUE(val == 229u);
        acc0.readScratchPad(1, (i<<16) + 63965, (uint8_t*)&val);
        EXPECT_TRUE(val == 9u);
        acc0.readScratchPad(1, (i<<16) + 63966, (uint8_t*)&val);
        EXPECT_TRUE(val == 196u);
        acc0.readScratchPad(1, (i<<16) + 63967, (uint8_t*)&val);
        EXPECT_TRUE(val == 169u);
        acc0.readScratchPad(1, (i<<16) + 63968, (uint8_t*)&val);
        EXPECT_TRUE(val == 211u);
        acc0.readScratchPad(1, (i<<16) + 63969, (uint8_t*)&val);
        EXPECT_TRUE(val == 176u);
        acc0.readScratchPad(1, (i<<16) + 63970, (uint8_t*)&val);
        EXPECT_TRUE(val == 95u);
        acc0.readScratchPad(1, (i<<16) + 63971, (uint8_t*)&val);
        EXPECT_TRUE(val == 77u);
        acc0.readScratchPad(1, (i<<16) + 63972, (uint8_t*)&val);
        EXPECT_TRUE(val == 150u);
        acc0.readScratchPad(1, (i<<16) + 63973, (uint8_t*)&val);
        EXPECT_TRUE(val == 149u);
        acc0.readScratchPad(1, (i<<16) + 63974, (uint8_t*)&val);
        EXPECT_TRUE(val == 221u);
        acc0.readScratchPad(1, (i<<16) + 63975, (uint8_t*)&val);
        EXPECT_TRUE(val == 155u);
        acc0.readScratchPad(1, (i<<16) + 63976, (uint8_t*)&val);
        EXPECT_TRUE(val == 80u);
        acc0.readScratchPad(1, (i<<16) + 63977, (uint8_t*)&val);
        EXPECT_TRUE(val == 233u);
        acc0.readScratchPad(1, (i<<16) + 63978, (uint8_t*)&val);
        EXPECT_TRUE(val == 168u);
        acc0.readScratchPad(1, (i<<16) + 63979, (uint8_t*)&val);
        EXPECT_TRUE(val == 129u);
        acc0.readScratchPad(1, (i<<16) + 63980, (uint8_t*)&val);
        EXPECT_TRUE(val == 64u);
        acc0.readScratchPad(1, (i<<16) + 63981, (uint8_t*)&val);
        EXPECT_TRUE(val == 81u);
        acc0.readScratchPad(1, (i<<16) + 63982, (uint8_t*)&val);
        EXPECT_TRUE(val == 250u);
        acc0.readScratchPad(1, (i<<16) + 63983, (uint8_t*)&val);
        EXPECT_TRUE(val == 111u);
        acc0.readScratchPad(1, (i<<16) + 63984, (uint8_t*)&val);
        EXPECT_TRUE(val == 247u);
        acc0.readScratchPad(1, (i<<16) + 63985, (uint8_t*)&val);
        EXPECT_TRUE(val == 112u);
        acc0.readScratchPad(1, (i<<16) + 63986, (uint8_t*)&val);
        EXPECT_TRUE(val == 69u);
        acc0.readScratchPad(1, (i<<16) + 63987, (uint8_t*)&val);
        EXPECT_TRUE(val == 109u);
        acc0.readScratchPad(1, (i<<16) + 63988, (uint8_t*)&val);
        EXPECT_TRUE(val == 17u);
        acc0.readScratchPad(1, (i<<16) + 63989, (uint8_t*)&val);
        EXPECT_TRUE(val == 209u);
    }
}
TEST_F(bcpyll, Basic_bcpyll_9){
    acc0.initSetup(0, "testprogs/binaries/bcpyll_9.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X21, 63639));
        EXPECT_TRUE(acc0.testReg(i, RegId::X22, 13359));
        EXPECT_TRUE(acc0.testReg(i, RegId::X23, 15));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 63639+15));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 13359+15));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18,0));
        uint8_t val=0;
        acc0.readScratchPad(1, (i<<16) + 13359, (uint8_t*)&val);
        EXPECT_TRUE(val == 108u);
        acc0.readScratchPad(1, (i<<16) + 13360, (uint8_t*)&val);
        EXPECT_TRUE(val == 171u);
        acc0.readScratchPad(1, (i<<16) + 13361, (uint8_t*)&val);
        EXPECT_TRUE(val == 218u);
        acc0.readScratchPad(1, (i<<16) + 13362, (uint8_t*)&val);
        EXPECT_TRUE(val == 167u);
        acc0.readScratchPad(1, (i<<16) + 13363, (uint8_t*)&val);
        EXPECT_TRUE(val == 176u);
        acc0.readScratchPad(1, (i<<16) + 13364, (uint8_t*)&val);
        EXPECT_TRUE(val == 13u);
        acc0.readScratchPad(1, (i<<16) + 13365, (uint8_t*)&val);
        EXPECT_TRUE(val == 84u);
        acc0.readScratchPad(1, (i<<16) + 13366, (uint8_t*)&val);
        EXPECT_TRUE(val == 70u);
        acc0.readScratchPad(1, (i<<16) + 13367, (uint8_t*)&val);
        EXPECT_TRUE(val == 184u);
        acc0.readScratchPad(1, (i<<16) + 13368, (uint8_t*)&val);
        EXPECT_TRUE(val == 165u);
        acc0.readScratchPad(1, (i<<16) + 13369, (uint8_t*)&val);
        EXPECT_TRUE(val == 138u);
        acc0.readScratchPad(1, (i<<16) + 13370, (uint8_t*)&val);
        EXPECT_TRUE(val == 198u);
        acc0.readScratchPad(1, (i<<16) + 13371, (uint8_t*)&val);
        EXPECT_TRUE(val == 219u);
        acc0.readScratchPad(1, (i<<16) + 13372, (uint8_t*)&val);
        EXPECT_TRUE(val == 108u);
        acc0.readScratchPad(1, (i<<16) + 13373, (uint8_t*)&val);
        EXPECT_TRUE(val == 19u);
    }
}
TEST_F(bcpyll, Basic_bcpyll_10){
    acc0.initSetup(0, "testprogs/binaries/bcpyll_10.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X21, 15601));
        EXPECT_TRUE(acc0.testReg(i, RegId::X22, 46175));
        EXPECT_TRUE(acc0.testReg(i, RegId::X23, 11));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 15601+11));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 46175+11));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18,0));
        uint8_t val=0;
        acc0.readScratchPad(1, (i<<16) + 46175, (uint8_t*)&val);
        EXPECT_TRUE(val == 226u);
        acc0.readScratchPad(1, (i<<16) + 46176, (uint8_t*)&val);
        EXPECT_TRUE(val == 18u);
        acc0.readScratchPad(1, (i<<16) + 46177, (uint8_t*)&val);
        EXPECT_TRUE(val == 73u);
        acc0.readScratchPad(1, (i<<16) + 46178, (uint8_t*)&val);
        EXPECT_TRUE(val == 245u);
        acc0.readScratchPad(1, (i<<16) + 46179, (uint8_t*)&val);
        EXPECT_TRUE(val == 49u);
        acc0.readScratchPad(1, (i<<16) + 46180, (uint8_t*)&val);
        EXPECT_TRUE(val == 7u);
        acc0.readScratchPad(1, (i<<16) + 46181, (uint8_t*)&val);
        EXPECT_TRUE(val == 59u);
        acc0.readScratchPad(1, (i<<16) + 46182, (uint8_t*)&val);
        EXPECT_TRUE(val == 33u);
        acc0.readScratchPad(1, (i<<16) + 46183, (uint8_t*)&val);
        EXPECT_TRUE(val == 181u);
        acc0.readScratchPad(1, (i<<16) + 46184, (uint8_t*)&val);
        EXPECT_TRUE(val == 110u);
        acc0.readScratchPad(1, (i<<16) + 46185, (uint8_t*)&val);
        EXPECT_TRUE(val == 208u);
    }
}
TEST_F(bcpyll, Basic_bcpyll_11){
    acc0.initSetup(0, "testprogs/binaries/bcpyll_11.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X21, 46243));
        EXPECT_TRUE(acc0.testReg(i, RegId::X22, 8389));
        EXPECT_TRUE(acc0.testReg(i, RegId::X23, 11));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 46243+11));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 8389+11));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18,0));
        uint8_t val=0;
        acc0.readScratchPad(1, (i<<16) + 8389, (uint8_t*)&val);
        EXPECT_TRUE(val == 50u);
        acc0.readScratchPad(1, (i<<16) + 8390, (uint8_t*)&val);
        EXPECT_TRUE(val == 32u);
        acc0.readScratchPad(1, (i<<16) + 8391, (uint8_t*)&val);
        EXPECT_TRUE(val == 172u);
        acc0.readScratchPad(1, (i<<16) + 8392, (uint8_t*)&val);
        EXPECT_TRUE(val == 13u);
        acc0.readScratchPad(1, (i<<16) + 8393, (uint8_t*)&val);
        EXPECT_TRUE(val == 101u);
        acc0.readScratchPad(1, (i<<16) + 8394, (uint8_t*)&val);
        EXPECT_TRUE(val == 195u);
        acc0.readScratchPad(1, (i<<16) + 8395, (uint8_t*)&val);
        EXPECT_TRUE(val == 78u);
        acc0.readScratchPad(1, (i<<16) + 8396, (uint8_t*)&val);
        EXPECT_TRUE(val == 202u);
        acc0.readScratchPad(1, (i<<16) + 8397, (uint8_t*)&val);
        EXPECT_TRUE(val == 12u);
        acc0.readScratchPad(1, (i<<16) + 8398, (uint8_t*)&val);
        EXPECT_TRUE(val == 213u);
        acc0.readScratchPad(1, (i<<16) + 8399, (uint8_t*)&val);
        EXPECT_TRUE(val == 223u);
    }
}
TEST_F(bcpyll, Basic_bcpyll_12){
    acc0.initSetup(0, "testprogs/binaries/bcpyll_12.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X21, 36746));
        EXPECT_TRUE(acc0.testReg(i, RegId::X22, 63851));
        EXPECT_TRUE(acc0.testReg(i, RegId::X23, 24));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 36746+24));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 63851+24));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18,0));
        uint8_t val=0;
        acc0.readScratchPad(1, (i<<16) + 63851, (uint8_t*)&val);
        EXPECT_TRUE(val == 121u);
        acc0.readScratchPad(1, (i<<16) + 63852, (uint8_t*)&val);
        EXPECT_TRUE(val == 133u);
        acc0.readScratchPad(1, (i<<16) + 63853, (uint8_t*)&val);
        EXPECT_TRUE(val == 155u);
        acc0.readScratchPad(1, (i<<16) + 63854, (uint8_t*)&val);
        EXPECT_TRUE(val == 116u);
        acc0.readScratchPad(1, (i<<16) + 63855, (uint8_t*)&val);
        EXPECT_TRUE(val == 24u);
        acc0.readScratchPad(1, (i<<16) + 63856, (uint8_t*)&val);
        EXPECT_TRUE(val == 173u);
        acc0.readScratchPad(1, (i<<16) + 63857, (uint8_t*)&val);
        EXPECT_TRUE(val == 80u);
        acc0.readScratchPad(1, (i<<16) + 63858, (uint8_t*)&val);
        EXPECT_TRUE(val == 94u);
        acc0.readScratchPad(1, (i<<16) + 63859, (uint8_t*)&val);
        EXPECT_TRUE(val == 184u);
        acc0.readScratchPad(1, (i<<16) + 63860, (uint8_t*)&val);
        EXPECT_TRUE(val == 201u);
        acc0.readScratchPad(1, (i<<16) + 63861, (uint8_t*)&val);
        EXPECT_TRUE(val == 95u);
        acc0.readScratchPad(1, (i<<16) + 63862, (uint8_t*)&val);
        EXPECT_TRUE(val == 172u);
        acc0.readScratchPad(1, (i<<16) + 63863, (uint8_t*)&val);
        EXPECT_TRUE(val == 136u);
        acc0.readScratchPad(1, (i<<16) + 63864, (uint8_t*)&val);
        EXPECT_TRUE(val == 54u);
        acc0.readScratchPad(1, (i<<16) + 63865, (uint8_t*)&val);
        EXPECT_TRUE(val == 152u);
        acc0.readScratchPad(1, (i<<16) + 63866, (uint8_t*)&val);
        EXPECT_TRUE(val == 109u);
        acc0.readScratchPad(1, (i<<16) + 63867, (uint8_t*)&val);
        EXPECT_TRUE(val == 129u);
        acc0.readScratchPad(1, (i<<16) + 63868, (uint8_t*)&val);
        EXPECT_TRUE(val == 94u);
        acc0.readScratchPad(1, (i<<16) + 63869, (uint8_t*)&val);
        EXPECT_TRUE(val == 65u);
        acc0.readScratchPad(1, (i<<16) + 63870, (uint8_t*)&val);
        EXPECT_TRUE(val == 152u);
        acc0.readScratchPad(1, (i<<16) + 63871, (uint8_t*)&val);
        EXPECT_TRUE(val == 229u);
        acc0.readScratchPad(1, (i<<16) + 63872, (uint8_t*)&val);
        EXPECT_TRUE(val == 27u);
        acc0.readScratchPad(1, (i<<16) + 63873, (uint8_t*)&val);
        EXPECT_TRUE(val == 31u);
        acc0.readScratchPad(1, (i<<16) + 63874, (uint8_t*)&val);
        EXPECT_TRUE(val == 57u);
    }
}
TEST_F(bcpyll, Basic_bcpyll_13){
    acc0.initSetup(0, "testprogs/binaries/bcpyll_13.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X21, 60115));
        EXPECT_TRUE(acc0.testReg(i, RegId::X22, 25669));
        EXPECT_TRUE(acc0.testReg(i, RegId::X23, 28));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 60115+28));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 25669+28));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18,0));
        uint8_t val=0;
        acc0.readScratchPad(1, (i<<16) + 25669, (uint8_t*)&val);
        EXPECT_TRUE(val == 238u);
        acc0.readScratchPad(1, (i<<16) + 25670, (uint8_t*)&val);
        EXPECT_TRUE(val == 240u);
        acc0.readScratchPad(1, (i<<16) + 25671, (uint8_t*)&val);
        EXPECT_TRUE(val == 255u);
        acc0.readScratchPad(1, (i<<16) + 25672, (uint8_t*)&val);
        EXPECT_TRUE(val == 94u);
        acc0.readScratchPad(1, (i<<16) + 25673, (uint8_t*)&val);
        EXPECT_TRUE(val == 124u);
        acc0.readScratchPad(1, (i<<16) + 25674, (uint8_t*)&val);
        EXPECT_TRUE(val == 158u);
        acc0.readScratchPad(1, (i<<16) + 25675, (uint8_t*)&val);
        EXPECT_TRUE(val == 165u);
        acc0.readScratchPad(1, (i<<16) + 25676, (uint8_t*)&val);
        EXPECT_TRUE(val == 15u);
        acc0.readScratchPad(1, (i<<16) + 25677, (uint8_t*)&val);
        EXPECT_TRUE(val == 158u);
        acc0.readScratchPad(1, (i<<16) + 25678, (uint8_t*)&val);
        EXPECT_TRUE(val == 142u);
        acc0.readScratchPad(1, (i<<16) + 25679, (uint8_t*)&val);
        EXPECT_TRUE(val == 139u);
        acc0.readScratchPad(1, (i<<16) + 25680, (uint8_t*)&val);
        EXPECT_TRUE(val == 224u);
        acc0.readScratchPad(1, (i<<16) + 25681, (uint8_t*)&val);
        EXPECT_TRUE(val == 172u);
        acc0.readScratchPad(1, (i<<16) + 25682, (uint8_t*)&val);
        EXPECT_TRUE(val == 2u);
        acc0.readScratchPad(1, (i<<16) + 25683, (uint8_t*)&val);
        EXPECT_TRUE(val == 160u);
        acc0.readScratchPad(1, (i<<16) + 25684, (uint8_t*)&val);
        EXPECT_TRUE(val == 83u);
        acc0.readScratchPad(1, (i<<16) + 25685, (uint8_t*)&val);
        EXPECT_TRUE(val == 1u);
        acc0.readScratchPad(1, (i<<16) + 25686, (uint8_t*)&val);
        EXPECT_TRUE(val == 219u);
        acc0.readScratchPad(1, (i<<16) + 25687, (uint8_t*)&val);
        EXPECT_TRUE(val == 176u);
        acc0.readScratchPad(1, (i<<16) + 25688, (uint8_t*)&val);
        EXPECT_TRUE(val == 232u);
        acc0.readScratchPad(1, (i<<16) + 25689, (uint8_t*)&val);
        EXPECT_TRUE(val == 221u);
        acc0.readScratchPad(1, (i<<16) + 25690, (uint8_t*)&val);
        EXPECT_TRUE(val == 11u);
        acc0.readScratchPad(1, (i<<16) + 25691, (uint8_t*)&val);
        EXPECT_TRUE(val == 118u);
        acc0.readScratchPad(1, (i<<16) + 25692, (uint8_t*)&val);
        EXPECT_TRUE(val == 219u);
        acc0.readScratchPad(1, (i<<16) + 25693, (uint8_t*)&val);
        EXPECT_TRUE(val == 252u);
        acc0.readScratchPad(1, (i<<16) + 25694, (uint8_t*)&val);
        EXPECT_TRUE(val == 135u);
        acc0.readScratchPad(1, (i<<16) + 25695, (uint8_t*)&val);
        EXPECT_TRUE(val == 153u);
        acc0.readScratchPad(1, (i<<16) + 25696, (uint8_t*)&val);
        EXPECT_TRUE(val == 178u);
    }
}
TEST_F(bcpyll, Basic_bcpyll_14){
    acc0.initSetup(0, "testprogs/binaries/bcpyll_14.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X21, 27320));
        EXPECT_TRUE(acc0.testReg(i, RegId::X22, 24854));
        EXPECT_TRUE(acc0.testReg(i, RegId::X23, 0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 27320+0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 24854+0));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18,0));
        uint8_t val=0;
    }
}
TEST_F(bcpyll, Basic_bcpyll_15){
    acc0.initSetup(0, "testprogs/binaries/bcpyll_15.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X21, 26689));
        EXPECT_TRUE(acc0.testReg(i, RegId::X22, 42781));
        EXPECT_TRUE(acc0.testReg(i, RegId::X23, 19));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 26689+19));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 42781+19));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18,0));
        uint8_t val=0;
        acc0.readScratchPad(1, (i<<16) + 42781, (uint8_t*)&val);
        EXPECT_TRUE(val == 52u);
        acc0.readScratchPad(1, (i<<16) + 42782, (uint8_t*)&val);
        EXPECT_TRUE(val == 113u);
        acc0.readScratchPad(1, (i<<16) + 42783, (uint8_t*)&val);
        EXPECT_TRUE(val == 16u);
        acc0.readScratchPad(1, (i<<16) + 42784, (uint8_t*)&val);
        EXPECT_TRUE(val == 108u);
        acc0.readScratchPad(1, (i<<16) + 42785, (uint8_t*)&val);
        EXPECT_TRUE(val == 85u);
        acc0.readScratchPad(1, (i<<16) + 42786, (uint8_t*)&val);
        EXPECT_TRUE(val == 231u);
        acc0.readScratchPad(1, (i<<16) + 42787, (uint8_t*)&val);
        EXPECT_TRUE(val == 6u);
        acc0.readScratchPad(1, (i<<16) + 42788, (uint8_t*)&val);
        EXPECT_TRUE(val == 63u);
        acc0.readScratchPad(1, (i<<16) + 42789, (uint8_t*)&val);
        EXPECT_TRUE(val == 146u);
        acc0.readScratchPad(1, (i<<16) + 42790, (uint8_t*)&val);
        EXPECT_TRUE(val == 200u);
        acc0.readScratchPad(1, (i<<16) + 42791, (uint8_t*)&val);
        EXPECT_TRUE(val == 30u);
        acc0.readScratchPad(1, (i<<16) + 42792, (uint8_t*)&val);
        EXPECT_TRUE(val == 200u);
        acc0.readScratchPad(1, (i<<16) + 42793, (uint8_t*)&val);
        EXPECT_TRUE(val == 175u);
        acc0.readScratchPad(1, (i<<16) + 42794, (uint8_t*)&val);
        EXPECT_TRUE(val == 29u);
        acc0.readScratchPad(1, (i<<16) + 42795, (uint8_t*)&val);
        EXPECT_TRUE(val == 216u);
        acc0.readScratchPad(1, (i<<16) + 42796, (uint8_t*)&val);
        EXPECT_TRUE(val == 130u);
        acc0.readScratchPad(1, (i<<16) + 42797, (uint8_t*)&val);
        EXPECT_TRUE(val == 210u);
        acc0.readScratchPad(1, (i<<16) + 42798, (uint8_t*)&val);
        EXPECT_TRUE(val == 149u);
        acc0.readScratchPad(1, (i<<16) + 42799, (uint8_t*)&val);
        EXPECT_TRUE(val == 16u);
    }
}
TEST_F(bcpyll, Basic_bcpyll_16){
    acc0.initSetup(0, "testprogs/binaries/bcpyll_16.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X21, 57736));
        EXPECT_TRUE(acc0.testReg(i, RegId::X22, 11230));
        EXPECT_TRUE(acc0.testReg(i, RegId::X23, 5));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 57736+5));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 11230+5));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18,0));
        uint8_t val=0;
        acc0.readScratchPad(1, (i<<16) + 11230, (uint8_t*)&val);
        EXPECT_TRUE(val == 213u);
        acc0.readScratchPad(1, (i<<16) + 11231, (uint8_t*)&val);
        EXPECT_TRUE(val == 151u);
        acc0.readScratchPad(1, (i<<16) + 11232, (uint8_t*)&val);
        EXPECT_TRUE(val == 211u);
        acc0.readScratchPad(1, (i<<16) + 11233, (uint8_t*)&val);
        EXPECT_TRUE(val == 58u);
        acc0.readScratchPad(1, (i<<16) + 11234, (uint8_t*)&val);
        EXPECT_TRUE(val == 125u);
    }
}
TEST_F(bcpyll, Basic_bcpyll_17){
    acc0.initSetup(0, "testprogs/binaries/bcpyll_17.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X21, 42565));
        EXPECT_TRUE(acc0.testReg(i, RegId::X22, 14162));
        EXPECT_TRUE(acc0.testReg(i, RegId::X23, 25));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 42565+25));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 14162+25));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18,0));
        uint8_t val=0;
        acc0.readScratchPad(1, (i<<16) + 14162, (uint8_t*)&val);
        EXPECT_TRUE(val == 169u);
        acc0.readScratchPad(1, (i<<16) + 14163, (uint8_t*)&val);
        EXPECT_TRUE(val == 229u);
        acc0.readScratchPad(1, (i<<16) + 14164, (uint8_t*)&val);
        EXPECT_TRUE(val == 145u);
        acc0.readScratchPad(1, (i<<16) + 14165, (uint8_t*)&val);
        EXPECT_TRUE(val == 57u);
        acc0.readScratchPad(1, (i<<16) + 14166, (uint8_t*)&val);
        EXPECT_TRUE(val == 31u);
        acc0.readScratchPad(1, (i<<16) + 14167, (uint8_t*)&val);
        EXPECT_TRUE(val == 2u);
        acc0.readScratchPad(1, (i<<16) + 14168, (uint8_t*)&val);
        EXPECT_TRUE(val == 145u);
        acc0.readScratchPad(1, (i<<16) + 14169, (uint8_t*)&val);
        EXPECT_TRUE(val == 65u);
        acc0.readScratchPad(1, (i<<16) + 14170, (uint8_t*)&val);
        EXPECT_TRUE(val == 126u);
        acc0.readScratchPad(1, (i<<16) + 14171, (uint8_t*)&val);
        EXPECT_TRUE(val == 210u);
        acc0.readScratchPad(1, (i<<16) + 14172, (uint8_t*)&val);
        EXPECT_TRUE(val == 8u);
        acc0.readScratchPad(1, (i<<16) + 14173, (uint8_t*)&val);
        EXPECT_TRUE(val == 126u);
        acc0.readScratchPad(1, (i<<16) + 14174, (uint8_t*)&val);
        EXPECT_TRUE(val == 138u);
        acc0.readScratchPad(1, (i<<16) + 14175, (uint8_t*)&val);
        EXPECT_TRUE(val == 135u);
        acc0.readScratchPad(1, (i<<16) + 14176, (uint8_t*)&val);
        EXPECT_TRUE(val == 176u);
        acc0.readScratchPad(1, (i<<16) + 14177, (uint8_t*)&val);
        EXPECT_TRUE(val == 40u);
        acc0.readScratchPad(1, (i<<16) + 14178, (uint8_t*)&val);
        EXPECT_TRUE(val == 131u);
        acc0.readScratchPad(1, (i<<16) + 14179, (uint8_t*)&val);
        EXPECT_TRUE(val == 88u);
        acc0.readScratchPad(1, (i<<16) + 14180, (uint8_t*)&val);
        EXPECT_TRUE(val == 69u);
        acc0.readScratchPad(1, (i<<16) + 14181, (uint8_t*)&val);
        EXPECT_TRUE(val == 67u);
        acc0.readScratchPad(1, (i<<16) + 14182, (uint8_t*)&val);
        EXPECT_TRUE(val == 177u);
        acc0.readScratchPad(1, (i<<16) + 14183, (uint8_t*)&val);
        EXPECT_TRUE(val == 195u);
        acc0.readScratchPad(1, (i<<16) + 14184, (uint8_t*)&val);
        EXPECT_TRUE(val == 170u);
        acc0.readScratchPad(1, (i<<16) + 14185, (uint8_t*)&val);
        EXPECT_TRUE(val == 17u);
        acc0.readScratchPad(1, (i<<16) + 14186, (uint8_t*)&val);
        EXPECT_TRUE(val == 195u);
    }
}
TEST_F(bcpyll, Basic_bcpyll_18){
    acc0.initSetup(0, "testprogs/binaries/bcpyll_18.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X21, 54822));
        EXPECT_TRUE(acc0.testReg(i, RegId::X22, 6770));
        EXPECT_TRUE(acc0.testReg(i, RegId::X23, 14));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 54822+14));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 6770+14));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18,0));
        uint8_t val=0;
        acc0.readScratchPad(1, (i<<16) + 6770, (uint8_t*)&val);
        EXPECT_TRUE(val == 88u);
        acc0.readScratchPad(1, (i<<16) + 6771, (uint8_t*)&val);
        EXPECT_TRUE(val == 201u);
        acc0.readScratchPad(1, (i<<16) + 6772, (uint8_t*)&val);
        EXPECT_TRUE(val == 224u);
        acc0.readScratchPad(1, (i<<16) + 6773, (uint8_t*)&val);
        EXPECT_TRUE(val == 114u);
        acc0.readScratchPad(1, (i<<16) + 6774, (uint8_t*)&val);
        EXPECT_TRUE(val == 150u);
        acc0.readScratchPad(1, (i<<16) + 6775, (uint8_t*)&val);
        EXPECT_TRUE(val == 151u);
        acc0.readScratchPad(1, (i<<16) + 6776, (uint8_t*)&val);
        EXPECT_TRUE(val == 198u);
        acc0.readScratchPad(1, (i<<16) + 6777, (uint8_t*)&val);
        EXPECT_TRUE(val == 38u);
        acc0.readScratchPad(1, (i<<16) + 6778, (uint8_t*)&val);
        EXPECT_TRUE(val == 140u);
        acc0.readScratchPad(1, (i<<16) + 6779, (uint8_t*)&val);
        EXPECT_TRUE(val == 128u);
        acc0.readScratchPad(1, (i<<16) + 6780, (uint8_t*)&val);
        EXPECT_TRUE(val == 238u);
        acc0.readScratchPad(1, (i<<16) + 6781, (uint8_t*)&val);
        EXPECT_TRUE(val == 19u);
        acc0.readScratchPad(1, (i<<16) + 6782, (uint8_t*)&val);
        EXPECT_TRUE(val == 193u);
        acc0.readScratchPad(1, (i<<16) + 6783, (uint8_t*)&val);
        EXPECT_TRUE(val == 64u);
    }
}
TEST_F(bcpyll, Basic_bcpyll_19){
    acc0.initSetup(0, "testprogs/binaries/bcpyll_19.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, RegId::X21, 26925));
        EXPECT_TRUE(acc0.testReg(i, RegId::X22, 12163));
        EXPECT_TRUE(acc0.testReg(i, RegId::X23, 7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X16, 26925+7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 12163+7));
        EXPECT_TRUE(acc0.testReg(i, RegId::X18,0));
        uint8_t val=0;
        acc0.readScratchPad(1, (i<<16) + 12163, (uint8_t*)&val);
        EXPECT_TRUE(val == 122u);
        acc0.readScratchPad(1, (i<<16) + 12164, (uint8_t*)&val);
        EXPECT_TRUE(val == 10u);
        acc0.readScratchPad(1, (i<<16) + 12165, (uint8_t*)&val);
        EXPECT_TRUE(val == 104u);
        acc0.readScratchPad(1, (i<<16) + 12166, (uint8_t*)&val);
        EXPECT_TRUE(val == 33u);
        acc0.readScratchPad(1, (i<<16) + 12167, (uint8_t*)&val);
        EXPECT_TRUE(val == 202u);
        acc0.readScratchPad(1, (i<<16) + 12168, (uint8_t*)&val);
        EXPECT_TRUE(val == 121u);
        acc0.readScratchPad(1, (i<<16) + 12169, (uint8_t*)&val);
        EXPECT_TRUE(val == 82u);
    }
}
