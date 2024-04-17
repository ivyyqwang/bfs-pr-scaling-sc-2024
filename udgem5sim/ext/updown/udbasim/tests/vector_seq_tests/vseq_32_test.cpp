#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"
#include <cmath>
#include <cfenv>

using namespace basim;

class Vseq_32Test : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    int num_lanes = 64;
    UDAccelerator acc0 = UDAccelerator(num_lanes, 0, 0);
    int buffsize1 = 1024;
    int buffsize2 = 1024;
};
static inline float BF16ToFloat(uint16_t var) {
    uint32_t var32 = static_cast<uint32_t>(var) << 16;
    return *reinterpret_cast<float *>(&var32);
}
TEST_F(Vseq_32Test, vseq_32_0){
    acc0.initSetup(0,"testprogs/binaries/vseq_32_0.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t* data = new word_t[numop];
    for(auto i = 0; i < numop; i++)
        data[i] = i+5;
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    acc0.pushEventOperands(eops, 1);
    while(!acc0.isIdle())
        acc0.simulate(2);
    int mask;
    uint32_t w0_0 = 1523300707, w0_1 = 1213072093;
    float val0_0 = *reinterpret_cast<float*>(&w0_0), val0_1 = *reinterpret_cast<float*>(&w0_1);
    uint32_t w1_0 = 290381687, w1_1 = 1142563087;
    float val1_0 = *reinterpret_cast<float*>(&w1_0), val1_1 = *reinterpret_cast<float*>(&w1_1);
    uint32_t w2_0 = 1670776870, w2_1 = 4168314076;
    float val2_0 = *reinterpret_cast<float*>(&w2_0), val2_1 = *reinterpret_cast<float*>(&w2_1);
    uint32_t w3_0 = 3253602391, w3_1 = 499207373;
    float val3_0 = *reinterpret_cast<float*>(&w3_0), val3_1 = *reinterpret_cast<float*>(&w3_1);
    uint32_t w4_0 = 4091307253, w4_1 = 4019894405;
    float val4_0 = *reinterpret_cast<float*>(&w4_0), val4_1 = *reinterpret_cast<float*>(&w4_1);
    uint32_t w5_0 = 3577965663, w5_1 = 1548142683;
    float val5_0 = *reinterpret_cast<float*>(&w5_0), val5_1 = *reinterpret_cast<float*>(&w5_1);
    uint32_t w6_0 = 3911714747, w6_1 = 885094305;
    float val6_0 = *reinterpret_cast<float*>(&w6_0), val6_1 = *reinterpret_cast<float*>(&w6_1);
    uint32_t w7_0 = 1627798387, w7_1 = 347121409;
    float val7_0 = *reinterpret_cast<float*>(&w7_0), val7_1 = *reinterpret_cast<float*>(&w7_1);
    uint32_t *val0_0_cast = reinterpret_cast<uint32_t*>(&val0_0);
    uint32_t *val1_0_cast = reinterpret_cast<uint32_t*>(&val1_0);
    uint32_t *val2_0_cast = reinterpret_cast<uint32_t*>(&val2_0);
    uint32_t *val3_0_cast = reinterpret_cast<uint32_t*>(&val3_0);
    uint32_t *val4_0_cast = reinterpret_cast<uint32_t*>(&val4_0);
    uint32_t *val5_0_cast = reinterpret_cast<uint32_t*>(&val5_0);
    uint32_t *val6_0_cast = reinterpret_cast<uint32_t*>(&val6_0);
    uint32_t *val7_0_cast = reinterpret_cast<uint32_t*>(&val7_0);
    uint32_t result = 0;
    mask = 1;
    val0_0 = 16.0;
    val0_1 = 16.0;
    mask = 2;
    val1_0 = 3.0;
    val1_1 = 3.0;
    mask = 3;
    val2_0 = 11.75;
    val2_1 = 11.75;
    mask = 2;
    val3_0 = 8.5;
    val3_1 = 8.5;
    mask = 3;
    val4_0 = 6.5;
    val4_1 = 6.5;
    mask = 2;
    val5_0 = 15.5;
    val5_1 = 15.5;
    mask = 2;
    val6_0 = 2.5;
    val6_1 = 2.5;
    mask = 3;
    val7_0 = 9.375;
    val7_1 = 9.375;
    mask = 2;
    val7_0 = (mask >> 0 & 1) ? val5_0 / val6_0 : val7_0;
    val7_1 = (mask >> 1 & 1) ? val5_1 / val6_1 : val7_1;
    mask = 2;
    result = 0;
    result |= (mask >> 0 & 1) & (val1_0 > val2_0);
    result |= (mask >> 1 & 1) & (val1_1 > val2_1);
    *val3_0_cast = (*val3_0_cast & ~mask) | result;
    mask = 2;
    val7_0 = 6.5;
    val7_1 = 6.5;
    mask = 2;
    val6_0 = (mask >> 0 & 1) ? val2_0 * val6_0 + val6_0 : val6_0;
    val6_1 = (mask >> 1 & 1) ? val2_1 * val6_1 + val6_1 : val6_1;
    mask = 2;
    val1_0 = (mask >> 0 & 1) ? val2_0 * val6_0 : val1_0;
    val1_1 = (mask >> 1 & 1) ? val2_1 * val6_1 : val1_1;
    mask = 3;
    val3_0 = 18.625;
    val3_1 = 18.625;
    mask = 2;
    val7_0 = (mask >> 0 & 1) ? val5_0 * val5_0 : val7_0;
    val7_1 = (mask >> 1 & 1) ? val5_1 * val5_1 : val7_1;
    mask = 3;
    val7_0 = (mask >> 0 & 1) ? val3_0 * val2_0 : val7_0;
    val7_1 = (mask >> 1 & 1) ? val3_1 * val2_1 : val7_1;
    mask = 2;
    val2_0 = (mask >> 0 & 1) ? val1_0 * val4_0 + val2_0 : val2_0;
    val2_1 = (mask >> 1 & 1) ? val1_1 * val4_1 + val2_1 : val2_1;
    mask = 3;
    val7_0 = (mask >> 0 & 1) ? val7_0 * val5_0 : val7_0;
    val7_1 = (mask >> 1 & 1) ? val7_1 * val5_1 : val7_1;
    mask = 3;
    val4_0 = (mask >> 0 & 1) ? val7_0 - val6_0 : val4_0;
    val4_1 = (mask >> 1 & 1) ? val7_1 - val6_1 : val4_1;
    mask = 2;
    val4_0 = (mask >> 0 & 1) ? val5_0 - val2_0 : val4_0;
    val4_1 = (mask >> 1 & 1) ? val5_1 - val2_1 : val4_1;
    mask = 2;
    val1_0 = (mask >> 0 & 1) ? val6_0 - val2_0 : val1_0;
    val1_1 = (mask >> 1 & 1) ? val6_1 - val2_1 : val1_1;
    mask = 2;
    val5_0 = (mask >> 0 & 1) ? val2_0 * val4_0 : val5_0;
    val5_1 = (mask >> 1 & 1) ? val2_1 * val4_1 : val5_1;
    mask = 1;
    val3_0 = (mask >> 0 & 1) ? val2_0 - val3_0 : val3_0;
    val3_1 = (mask >> 1 & 1) ? val2_1 - val3_1 : val3_1;
    mask = 3;
    val3_0 = (mask >> 0 & 1) ? val1_0 - val2_0 : val3_0;
    val3_1 = (mask >> 1 & 1) ? val1_1 - val2_1 : val3_1;
    mask = 1;
    val4_0 = (mask >> 0 & 1) ? val2_0 * val3_0 + val4_0 : val4_0;
    val4_1 = (mask >> 1 & 1) ? val2_1 * val3_1 + val4_1 : val4_1;
    mask = 2;
    val5_0 = 3.5;
    val5_1 = 3.5;
    mask = 1;
    val7_0 = (mask >> 0 & 1) ? val1_0 * val3_0 : val7_0;
    val7_1 = (mask >> 1 & 1) ? val1_1 * val3_1 : val7_1;
    mask = 3;
    val4_0 = (mask >> 0 & 1) ? val6_0 + val4_0 : val4_0;
    val4_1 = (mask >> 1 & 1) ? val6_1 + val4_1 : val4_1;
    mask = 3;
    val3_0 = (mask >> 0 & 1) ? val6_0 - val5_0 : val3_0;
    val3_1 = (mask >> 1 & 1) ? val6_1 - val5_1 : val3_1;
    mask = 2;
    val2_0 = 8.125;
    val2_1 = 8.125;
    mask = 1;
    val5_0 = (mask >> 0 & 1) ? val3_0 + val5_0 : val5_0;
    val5_1 = (mask >> 1 & 1) ? val3_1 + val5_1 : val5_1;
    mask = 3;
    val4_0 = (mask >> 0 & 1) ? val4_0 * val2_0 + val4_0 : val4_0;
    val4_1 = (mask >> 1 & 1) ? val4_1 * val2_1 + val4_1 : val4_1;
    mask = 3;
    val1_0 = (mask >> 0 & 1) ? val1_0 + val1_0 : val1_0;
    val1_1 = (mask >> 1 & 1) ? val1_1 + val1_1 : val1_1;
    mask = 2;
    val7_0 = (mask >> 0 & 1) ? val5_0 * val5_0 : val7_0;
    val7_1 = (mask >> 1 & 1) ? val5_1 * val5_1 : val7_1;
    mask = 3;
    val6_0 = 11.875;
    val6_1 = 11.875;
    mask = 3;
    val2_0 = 2.25;
    val2_1 = 2.25;
    mask = 3;
    val2_0 = 15.625;
    val2_1 = 15.625;
    mask = 1;
    val2_0 = (mask >> 0 & 1) ? val4_0 * val7_0 + val2_0 : val2_0;
    val2_1 = (mask >> 1 & 1) ? val4_1 * val7_1 + val2_1 : val2_1;
    mask = 3;
    val5_0 = (mask >> 0 & 1) ? val1_0 * val7_0 : val5_0;
    val5_1 = (mask >> 1 & 1) ? val1_1 * val7_1 : val5_1;
    mask = 1;
    val5_0 = (mask >> 0 & 1) ? sqrt(val3_0) : val5_0;
    val5_1 = (mask >> 1 & 1) ? sqrt(val3_1) : val5_1;
    uint64_t final_result_0 = (uint64_t)(*reinterpret_cast<uint32_t*>(&val0_0)) | ((uint64_t)(*reinterpret_cast<uint32_t*>(&val0_1)) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, final_result_0));
    uint64_t final_result_1 = (uint64_t)(*reinterpret_cast<uint32_t*>(&val1_0)) | ((uint64_t)(*reinterpret_cast<uint32_t*>(&val1_1)) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, final_result_1));
    uint64_t final_result_2 = (uint64_t)(*reinterpret_cast<uint32_t*>(&val2_0)) | ((uint64_t)(*reinterpret_cast<uint32_t*>(&val2_1)) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result_2));
    uint64_t final_result_3 = (uint64_t)(*reinterpret_cast<uint32_t*>(&val3_0)) | ((uint64_t)(*reinterpret_cast<uint32_t*>(&val3_1)) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X19, final_result_3));
    uint64_t final_result_4 = (uint64_t)(*reinterpret_cast<uint32_t*>(&val4_0)) | ((uint64_t)(*reinterpret_cast<uint32_t*>(&val4_1)) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X20, final_result_4));
    uint64_t final_result_5 = (uint64_t)(*reinterpret_cast<uint32_t*>(&val5_0)) | ((uint64_t)(*reinterpret_cast<uint32_t*>(&val5_1)) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X21, final_result_5));
    uint64_t final_result_6 = (uint64_t)(*reinterpret_cast<uint32_t*>(&val6_0)) | ((uint64_t)(*reinterpret_cast<uint32_t*>(&val6_1)) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X22, final_result_6));
    uint64_t final_result_7 = (uint64_t)(*reinterpret_cast<uint32_t*>(&val7_0)) | ((uint64_t)(*reinterpret_cast<uint32_t*>(&val7_1)) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X23, final_result_7));
}