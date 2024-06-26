#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"
#include <cmath>
#include <cfenv>

using namespace basim;

class Vseq_b16Test : public ::testing::Test {
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
TEST_F(Vseq_b16Test, vseq_b16_0){
    acc0.initSetup(0,"testprogs/binaries/vseq_b16_0.bin", 0);
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
    uint32_t w0_0 = 4027628062u<<16, w0_1 = 1371649604u<<16, w0_2 = 3147293597u<<16, w0_3 = 241620380u<<16;
    float val0_0 = *reinterpret_cast<float*>(&w0_0), val0_1 = *reinterpret_cast<float*>(&w0_1), val0_2 = *reinterpret_cast<float*>(&w0_2), val0_3 = *reinterpret_cast<float*>(&w0_3);
    uint32_t w1_0 = 2825826994u<<16, w1_1 = 2295398940u<<16, w1_2 = 1551087805u<<16, w1_3 = 1057135101u<<16;
    float val1_0 = *reinterpret_cast<float*>(&w1_0), val1_1 = *reinterpret_cast<float*>(&w1_1), val1_2 = *reinterpret_cast<float*>(&w1_2), val1_3 = *reinterpret_cast<float*>(&w1_3);
    uint32_t w2_0 = 2549328732u<<16, w2_1 = 2952938803u<<16, w2_2 = 1924983923u<<16, w2_3 = 2881315748u<<16;
    float val2_0 = *reinterpret_cast<float*>(&w2_0), val2_1 = *reinterpret_cast<float*>(&w2_1), val2_2 = *reinterpret_cast<float*>(&w2_2), val2_3 = *reinterpret_cast<float*>(&w2_3);
    uint32_t w3_0 = 576334287u<<16, w3_1 = 1606525838u<<16, w3_2 = 3190699314u<<16, w3_3 = 3059739400u<<16;
    float val3_0 = *reinterpret_cast<float*>(&w3_0), val3_1 = *reinterpret_cast<float*>(&w3_1), val3_2 = *reinterpret_cast<float*>(&w3_2), val3_3 = *reinterpret_cast<float*>(&w3_3);
    uint32_t w4_0 = 1521690220u<<16, w4_1 = 644454042u<<16, w4_2 = 2931011062u<<16, w4_3 = 3043357233u<<16;
    float val4_0 = *reinterpret_cast<float*>(&w4_0), val4_1 = *reinterpret_cast<float*>(&w4_1), val4_2 = *reinterpret_cast<float*>(&w4_2), val4_3 = *reinterpret_cast<float*>(&w4_3);
    uint32_t w5_0 = 2942064497u<<16, w5_1 = 2323023381u<<16, w5_2 = 1001989201u<<16, w5_3 = 2855956438u<<16;
    float val5_0 = *reinterpret_cast<float*>(&w5_0), val5_1 = *reinterpret_cast<float*>(&w5_1), val5_2 = *reinterpret_cast<float*>(&w5_2), val5_3 = *reinterpret_cast<float*>(&w5_3);
    uint32_t w6_0 = 3314208787u<<16, w6_1 = 3271670551u<<16, w6_2 = 1035795313u<<16, w6_3 = 1408289254u<<16;
    float val6_0 = *reinterpret_cast<float*>(&w6_0), val6_1 = *reinterpret_cast<float*>(&w6_1), val6_2 = *reinterpret_cast<float*>(&w6_2), val6_3 = *reinterpret_cast<float*>(&w6_3);
    uint32_t w7_0 = 2702037751u<<16, w7_1 = 3244672361u<<16, w7_2 = 3193053963u<<16, w7_3 = 2403397910u<<16;
    float val7_0 = *reinterpret_cast<float*>(&w7_0), val7_1 = *reinterpret_cast<float*>(&w7_1), val7_2 = *reinterpret_cast<float*>(&w7_2), val7_3 = *reinterpret_cast<float*>(&w7_3);
    uint32_t *val0_0_cast = reinterpret_cast<uint32_t*>(&val0_0);
    uint32_t *val1_0_cast = reinterpret_cast<uint32_t*>(&val1_0);
    uint32_t *val2_0_cast = reinterpret_cast<uint32_t*>(&val2_0);
    uint32_t *val3_0_cast = reinterpret_cast<uint32_t*>(&val3_0);
    uint32_t *val4_0_cast = reinterpret_cast<uint32_t*>(&val4_0);
    uint32_t *val5_0_cast = reinterpret_cast<uint32_t*>(&val5_0);
    uint32_t *val6_0_cast = reinterpret_cast<uint32_t*>(&val6_0);
    uint32_t *val7_0_cast = reinterpret_cast<uint32_t*>(&val7_0);
    uint32_t result = 0;
    mask = 2;
    val0_0 = 3.625;
    val0_1 = 3.625;
    val0_2 = 3.625;
    val0_3 = 3.625;
    w0_0 = (*((reinterpret_cast<uint32_t*>(&val0_0))) >> 16) << 16;
    val0_0 = *reinterpret_cast<float*>(&w0_0);
    w0_1 = (*((reinterpret_cast<uint32_t*>(&val0_1))) >> 16) << 16;
    val0_1 = *reinterpret_cast<float*>(&w0_1);
    w0_2 = (*((reinterpret_cast<uint32_t*>(&val0_2))) >> 16) << 16;
    val0_2 = *reinterpret_cast<float*>(&w0_2);
    w0_3 = (*((reinterpret_cast<uint32_t*>(&val0_3))) >> 16) << 16;
    val0_3 = *reinterpret_cast<float*>(&w0_3);
    mask = 1;
    val1_0 = 2.875;
    val1_1 = 2.875;
    val1_2 = 2.875;
    val1_3 = 2.875;
    w1_0 = (*((reinterpret_cast<uint32_t*>(&val1_0))) >> 16) << 16;
    val1_0 = *reinterpret_cast<float*>(&w1_0);
    w1_1 = (*((reinterpret_cast<uint32_t*>(&val1_1))) >> 16) << 16;
    val1_1 = *reinterpret_cast<float*>(&w1_1);
    w1_2 = (*((reinterpret_cast<uint32_t*>(&val1_2))) >> 16) << 16;
    val1_2 = *reinterpret_cast<float*>(&w1_2);
    w1_3 = (*((reinterpret_cast<uint32_t*>(&val1_3))) >> 16) << 16;
    val1_3 = *reinterpret_cast<float*>(&w1_3);
    mask = 12;
    val2_0 = 12.375;
    val2_1 = 12.375;
    val2_2 = 12.375;
    val2_3 = 12.375;
    w2_0 = (*((reinterpret_cast<uint32_t*>(&val2_0))) >> 16) << 16;
    val2_0 = *reinterpret_cast<float*>(&w2_0);
    w2_1 = (*((reinterpret_cast<uint32_t*>(&val2_1))) >> 16) << 16;
    val2_1 = *reinterpret_cast<float*>(&w2_1);
    w2_2 = (*((reinterpret_cast<uint32_t*>(&val2_2))) >> 16) << 16;
    val2_2 = *reinterpret_cast<float*>(&w2_2);
    w2_3 = (*((reinterpret_cast<uint32_t*>(&val2_3))) >> 16) << 16;
    val2_3 = *reinterpret_cast<float*>(&w2_3);
    mask = 5;
    val3_0 = 18.25;
    val3_1 = 18.25;
    val3_2 = 18.25;
    val3_3 = 18.25;
    w3_0 = (*((reinterpret_cast<uint32_t*>(&val3_0))) >> 16) << 16;
    val3_0 = *reinterpret_cast<float*>(&w3_0);
    w3_1 = (*((reinterpret_cast<uint32_t*>(&val3_1))) >> 16) << 16;
    val3_1 = *reinterpret_cast<float*>(&w3_1);
    w3_2 = (*((reinterpret_cast<uint32_t*>(&val3_2))) >> 16) << 16;
    val3_2 = *reinterpret_cast<float*>(&w3_2);
    w3_3 = (*((reinterpret_cast<uint32_t*>(&val3_3))) >> 16) << 16;
    val3_3 = *reinterpret_cast<float*>(&w3_3);
    mask = 13;
    val4_0 = 2.375;
    val4_1 = 2.375;
    val4_2 = 2.375;
    val4_3 = 2.375;
    w4_0 = (*((reinterpret_cast<uint32_t*>(&val4_0))) >> 16) << 16;
    val4_0 = *reinterpret_cast<float*>(&w4_0);
    w4_1 = (*((reinterpret_cast<uint32_t*>(&val4_1))) >> 16) << 16;
    val4_1 = *reinterpret_cast<float*>(&w4_1);
    w4_2 = (*((reinterpret_cast<uint32_t*>(&val4_2))) >> 16) << 16;
    val4_2 = *reinterpret_cast<float*>(&w4_2);
    w4_3 = (*((reinterpret_cast<uint32_t*>(&val4_3))) >> 16) << 16;
    val4_3 = *reinterpret_cast<float*>(&w4_3);
    mask = 3;
    val5_0 = 15.875;
    val5_1 = 15.875;
    val5_2 = 15.875;
    val5_3 = 15.875;
    w5_0 = (*((reinterpret_cast<uint32_t*>(&val5_0))) >> 16) << 16;
    val5_0 = *reinterpret_cast<float*>(&w5_0);
    w5_1 = (*((reinterpret_cast<uint32_t*>(&val5_1))) >> 16) << 16;
    val5_1 = *reinterpret_cast<float*>(&w5_1);
    w5_2 = (*((reinterpret_cast<uint32_t*>(&val5_2))) >> 16) << 16;
    val5_2 = *reinterpret_cast<float*>(&w5_2);
    w5_3 = (*((reinterpret_cast<uint32_t*>(&val5_3))) >> 16) << 16;
    val5_3 = *reinterpret_cast<float*>(&w5_3);
    mask = 1;
    val6_0 = 16.375;
    val6_1 = 16.375;
    val6_2 = 16.375;
    val6_3 = 16.375;
    w6_0 = (*((reinterpret_cast<uint32_t*>(&val6_0))) >> 16) << 16;
    val6_0 = *reinterpret_cast<float*>(&w6_0);
    w6_1 = (*((reinterpret_cast<uint32_t*>(&val6_1))) >> 16) << 16;
    val6_1 = *reinterpret_cast<float*>(&w6_1);
    w6_2 = (*((reinterpret_cast<uint32_t*>(&val6_2))) >> 16) << 16;
    val6_2 = *reinterpret_cast<float*>(&w6_2);
    w6_3 = (*((reinterpret_cast<uint32_t*>(&val6_3))) >> 16) << 16;
    val6_3 = *reinterpret_cast<float*>(&w6_3);
    mask = 14;
    val7_0 = 10.375;
    val7_1 = 10.375;
    val7_2 = 10.375;
    val7_3 = 10.375;
    w7_0 = (*((reinterpret_cast<uint32_t*>(&val7_0))) >> 16) << 16;
    val7_0 = *reinterpret_cast<float*>(&w7_0);
    w7_1 = (*((reinterpret_cast<uint32_t*>(&val7_1))) >> 16) << 16;
    val7_1 = *reinterpret_cast<float*>(&w7_1);
    w7_2 = (*((reinterpret_cast<uint32_t*>(&val7_2))) >> 16) << 16;
    val7_2 = *reinterpret_cast<float*>(&w7_2);
    w7_3 = (*((reinterpret_cast<uint32_t*>(&val7_3))) >> 16) << 16;
    val7_3 = *reinterpret_cast<float*>(&w7_3);
    mask = 9;
    val7_0 = (mask >> 0 & 1) ? val5_0 / val6_0 : val7_0;
    val7_1 = (mask >> 1 & 1) ? val5_1 / val6_1 : val7_1;
    val7_2 = (mask >> 2 & 1) ? val5_2 / val6_2 : val7_2;
    val7_3 = (mask >> 3 & 1) ? val5_3 / val6_3 : val7_3;
    w7_0 = (*((reinterpret_cast<uint32_t*>(&val7_0))) >> 16) << 16;
    val7_0 = *reinterpret_cast<float*>(&w7_0);
    w7_1 = (*((reinterpret_cast<uint32_t*>(&val7_1))) >> 16) << 16;
    val7_1 = *reinterpret_cast<float*>(&w7_1);
    w7_2 = (*((reinterpret_cast<uint32_t*>(&val7_2))) >> 16) << 16;
    val7_2 = *reinterpret_cast<float*>(&w7_2);
    w7_3 = (*((reinterpret_cast<uint32_t*>(&val7_3))) >> 16) << 16;
    val7_3 = *reinterpret_cast<float*>(&w7_3);
    mask = 3;
    result = 0;
    result |= (mask >> 0 & 1) & (val1_0 > val2_0);
    result |= (mask >> 1 & 1) & (val1_1 > val2_1);
    result |= (mask >> 2 & 1) & (val1_2 > val2_2);
    result |= (mask >> 3 & 1) & (val1_3 > val2_3);
    *val3_0_cast = (*val3_0_cast & ~mask) | result;
    w3_0 = (*((reinterpret_cast<uint32_t*>(&val3_0))) >> 16) << 16;
    val3_0 = *reinterpret_cast<float*>(&w3_0);
    w3_1 = (*((reinterpret_cast<uint32_t*>(&val3_1))) >> 16) << 16;
    val3_1 = *reinterpret_cast<float*>(&w3_1);
    w3_2 = (*((reinterpret_cast<uint32_t*>(&val3_2))) >> 16) << 16;
    val3_2 = *reinterpret_cast<float*>(&w3_2);
    w3_3 = (*((reinterpret_cast<uint32_t*>(&val3_3))) >> 16) << 16;
    val3_3 = *reinterpret_cast<float*>(&w3_3);
    mask = 13;
    val4_0 = 17.125;
    val4_1 = 17.125;
    val4_2 = 17.125;
    val4_3 = 17.125;
    w4_0 = (*((reinterpret_cast<uint32_t*>(&val4_0))) >> 16) << 16;
    val4_0 = *reinterpret_cast<float*>(&w4_0);
    w4_1 = (*((reinterpret_cast<uint32_t*>(&val4_1))) >> 16) << 16;
    val4_1 = *reinterpret_cast<float*>(&w4_1);
    w4_2 = (*((reinterpret_cast<uint32_t*>(&val4_2))) >> 16) << 16;
    val4_2 = *reinterpret_cast<float*>(&w4_2);
    w4_3 = (*((reinterpret_cast<uint32_t*>(&val4_3))) >> 16) << 16;
    val4_3 = *reinterpret_cast<float*>(&w4_3);
    mask = 8;
    val4_0 = (mask >> 0 & 1) ? val6_0 * val5_0 + val4_0 : val4_0;
    val4_1 = (mask >> 1 & 1) ? val6_1 * val5_1 + val4_1 : val4_1;
    val4_2 = (mask >> 2 & 1) ? val6_2 * val5_2 + val4_2 : val4_2;
    val4_3 = (mask >> 3 & 1) ? val6_3 * val5_3 + val4_3 : val4_3;
    w4_0 = (*((reinterpret_cast<uint32_t*>(&val4_0))) >> 16) << 16;
    val4_0 = *reinterpret_cast<float*>(&w4_0);
    w4_1 = (*((reinterpret_cast<uint32_t*>(&val4_1))) >> 16) << 16;
    val4_1 = *reinterpret_cast<float*>(&w4_1);
    w4_2 = (*((reinterpret_cast<uint32_t*>(&val4_2))) >> 16) << 16;
    val4_2 = *reinterpret_cast<float*>(&w4_2);
    w4_3 = (*((reinterpret_cast<uint32_t*>(&val4_3))) >> 16) << 16;
    val4_3 = *reinterpret_cast<float*>(&w4_3);
    mask = 6;
    val4_0 = 10.125;
    val4_1 = 10.125;
    val4_2 = 10.125;
    val4_3 = 10.125;
    w4_0 = (*((reinterpret_cast<uint32_t*>(&val4_0))) >> 16) << 16;
    val4_0 = *reinterpret_cast<float*>(&w4_0);
    w4_1 = (*((reinterpret_cast<uint32_t*>(&val4_1))) >> 16) << 16;
    val4_1 = *reinterpret_cast<float*>(&w4_1);
    w4_2 = (*((reinterpret_cast<uint32_t*>(&val4_2))) >> 16) << 16;
    val4_2 = *reinterpret_cast<float*>(&w4_2);
    w4_3 = (*((reinterpret_cast<uint32_t*>(&val4_3))) >> 16) << 16;
    val4_3 = *reinterpret_cast<float*>(&w4_3);
    mask = 3;
    val3_0 = 15.125;
    val3_1 = 15.125;
    val3_2 = 15.125;
    val3_3 = 15.125;
    w3_0 = (*((reinterpret_cast<uint32_t*>(&val3_0))) >> 16) << 16;
    val3_0 = *reinterpret_cast<float*>(&w3_0);
    w3_1 = (*((reinterpret_cast<uint32_t*>(&val3_1))) >> 16) << 16;
    val3_1 = *reinterpret_cast<float*>(&w3_1);
    w3_2 = (*((reinterpret_cast<uint32_t*>(&val3_2))) >> 16) << 16;
    val3_2 = *reinterpret_cast<float*>(&w3_2);
    w3_3 = (*((reinterpret_cast<uint32_t*>(&val3_3))) >> 16) << 16;
    val3_3 = *reinterpret_cast<float*>(&w3_3);
    mask = 1;
    val5_0 = (mask >> 0 & 1) ? val1_0 * val2_0 + val5_0 : val5_0;
    val5_1 = (mask >> 1 & 1) ? val1_1 * val2_1 + val5_1 : val5_1;
    val5_2 = (mask >> 2 & 1) ? val1_2 * val2_2 + val5_2 : val5_2;
    val5_3 = (mask >> 3 & 1) ? val1_3 * val2_3 + val5_3 : val5_3;
    w5_0 = (*((reinterpret_cast<uint32_t*>(&val5_0))) >> 16) << 16;
    val5_0 = *reinterpret_cast<float*>(&w5_0);
    w5_1 = (*((reinterpret_cast<uint32_t*>(&val5_1))) >> 16) << 16;
    val5_1 = *reinterpret_cast<float*>(&w5_1);
    w5_2 = (*((reinterpret_cast<uint32_t*>(&val5_2))) >> 16) << 16;
    val5_2 = *reinterpret_cast<float*>(&w5_2);
    w5_3 = (*((reinterpret_cast<uint32_t*>(&val5_3))) >> 16) << 16;
    val5_3 = *reinterpret_cast<float*>(&w5_3);
    mask = 1;
    val3_0 = (mask >> 0 & 1) ? val5_0 - val6_0 : val3_0;
    val3_1 = (mask >> 1 & 1) ? val5_1 - val6_1 : val3_1;
    val3_2 = (mask >> 2 & 1) ? val5_2 - val6_2 : val3_2;
    val3_3 = (mask >> 3 & 1) ? val5_3 - val6_3 : val3_3;
    w3_0 = (*((reinterpret_cast<uint32_t*>(&val3_0))) >> 16) << 16;
    val3_0 = *reinterpret_cast<float*>(&w3_0);
    w3_1 = (*((reinterpret_cast<uint32_t*>(&val3_1))) >> 16) << 16;
    val3_1 = *reinterpret_cast<float*>(&w3_1);
    w3_2 = (*((reinterpret_cast<uint32_t*>(&val3_2))) >> 16) << 16;
    val3_2 = *reinterpret_cast<float*>(&w3_2);
    w3_3 = (*((reinterpret_cast<uint32_t*>(&val3_3))) >> 16) << 16;
    val3_3 = *reinterpret_cast<float*>(&w3_3);
    mask = 11;
    val4_0 = (mask >> 0 & 1) ? val5_0 - val1_0 : val4_0;
    val4_1 = (mask >> 1 & 1) ? val5_1 - val1_1 : val4_1;
    val4_2 = (mask >> 2 & 1) ? val5_2 - val1_2 : val4_2;
    val4_3 = (mask >> 3 & 1) ? val5_3 - val1_3 : val4_3;
    w4_0 = (*((reinterpret_cast<uint32_t*>(&val4_0))) >> 16) << 16;
    val4_0 = *reinterpret_cast<float*>(&w4_0);
    w4_1 = (*((reinterpret_cast<uint32_t*>(&val4_1))) >> 16) << 16;
    val4_1 = *reinterpret_cast<float*>(&w4_1);
    w4_2 = (*((reinterpret_cast<uint32_t*>(&val4_2))) >> 16) << 16;
    val4_2 = *reinterpret_cast<float*>(&w4_2);
    w4_3 = (*((reinterpret_cast<uint32_t*>(&val4_3))) >> 16) << 16;
    val4_3 = *reinterpret_cast<float*>(&w4_3);
    mask = 15;
    val1_0 = (mask >> 0 & 1) ? val7_0 + val2_0 : val1_0;
    val1_1 = (mask >> 1 & 1) ? val7_1 + val2_1 : val1_1;
    val1_2 = (mask >> 2 & 1) ? val7_2 + val2_2 : val1_2;
    val1_3 = (mask >> 3 & 1) ? val7_3 + val2_3 : val1_3;
    w1_0 = (*((reinterpret_cast<uint32_t*>(&val1_0))) >> 16) << 16;
    val1_0 = *reinterpret_cast<float*>(&w1_0);
    w1_1 = (*((reinterpret_cast<uint32_t*>(&val1_1))) >> 16) << 16;
    val1_1 = *reinterpret_cast<float*>(&w1_1);
    w1_2 = (*((reinterpret_cast<uint32_t*>(&val1_2))) >> 16) << 16;
    val1_2 = *reinterpret_cast<float*>(&w1_2);
    w1_3 = (*((reinterpret_cast<uint32_t*>(&val1_3))) >> 16) << 16;
    val1_3 = *reinterpret_cast<float*>(&w1_3);
    mask = 12;
    val1_0 = (mask >> 0 & 1) ? val1_0 * val6_0 : val1_0;
    val1_1 = (mask >> 1 & 1) ? val1_1 * val6_1 : val1_1;
    val1_2 = (mask >> 2 & 1) ? val1_2 * val6_2 : val1_2;
    val1_3 = (mask >> 3 & 1) ? val1_3 * val6_3 : val1_3;
    w1_0 = (*((reinterpret_cast<uint32_t*>(&val1_0))) >> 16) << 16;
    val1_0 = *reinterpret_cast<float*>(&w1_0);
    w1_1 = (*((reinterpret_cast<uint32_t*>(&val1_1))) >> 16) << 16;
    val1_1 = *reinterpret_cast<float*>(&w1_1);
    w1_2 = (*((reinterpret_cast<uint32_t*>(&val1_2))) >> 16) << 16;
    val1_2 = *reinterpret_cast<float*>(&w1_2);
    w1_3 = (*((reinterpret_cast<uint32_t*>(&val1_3))) >> 16) << 16;
    val1_3 = *reinterpret_cast<float*>(&w1_3);
    mask = 14;
    val7_0 = 12.75;
    val7_1 = 12.75;
    val7_2 = 12.75;
    val7_3 = 12.75;
    w7_0 = (*((reinterpret_cast<uint32_t*>(&val7_0))) >> 16) << 16;
    val7_0 = *reinterpret_cast<float*>(&w7_0);
    w7_1 = (*((reinterpret_cast<uint32_t*>(&val7_1))) >> 16) << 16;
    val7_1 = *reinterpret_cast<float*>(&w7_1);
    w7_2 = (*((reinterpret_cast<uint32_t*>(&val7_2))) >> 16) << 16;
    val7_2 = *reinterpret_cast<float*>(&w7_2);
    w7_3 = (*((reinterpret_cast<uint32_t*>(&val7_3))) >> 16) << 16;
    val7_3 = *reinterpret_cast<float*>(&w7_3);
    mask = 6;
    val2_0 = (mask >> 0 & 1) ? val6_0 * val2_0 : val2_0;
    val2_1 = (mask >> 1 & 1) ? val6_1 * val2_1 : val2_1;
    val2_2 = (mask >> 2 & 1) ? val6_2 * val2_2 : val2_2;
    val2_3 = (mask >> 3 & 1) ? val6_3 * val2_3 : val2_3;
    w2_0 = (*((reinterpret_cast<uint32_t*>(&val2_0))) >> 16) << 16;
    val2_0 = *reinterpret_cast<float*>(&w2_0);
    w2_1 = (*((reinterpret_cast<uint32_t*>(&val2_1))) >> 16) << 16;
    val2_1 = *reinterpret_cast<float*>(&w2_1);
    w2_2 = (*((reinterpret_cast<uint32_t*>(&val2_2))) >> 16) << 16;
    val2_2 = *reinterpret_cast<float*>(&w2_2);
    w2_3 = (*((reinterpret_cast<uint32_t*>(&val2_3))) >> 16) << 16;
    val2_3 = *reinterpret_cast<float*>(&w2_3);
    mask = 11;
    val2_0 = (mask >> 0 & 1) ? val4_0 - val3_0 : val2_0;
    val2_1 = (mask >> 1 & 1) ? val4_1 - val3_1 : val2_1;
    val2_2 = (mask >> 2 & 1) ? val4_2 - val3_2 : val2_2;
    val2_3 = (mask >> 3 & 1) ? val4_3 - val3_3 : val2_3;
    w2_0 = (*((reinterpret_cast<uint32_t*>(&val2_0))) >> 16) << 16;
    val2_0 = *reinterpret_cast<float*>(&w2_0);
    w2_1 = (*((reinterpret_cast<uint32_t*>(&val2_1))) >> 16) << 16;
    val2_1 = *reinterpret_cast<float*>(&w2_1);
    w2_2 = (*((reinterpret_cast<uint32_t*>(&val2_2))) >> 16) << 16;
    val2_2 = *reinterpret_cast<float*>(&w2_2);
    w2_3 = (*((reinterpret_cast<uint32_t*>(&val2_3))) >> 16) << 16;
    val2_3 = *reinterpret_cast<float*>(&w2_3);
    mask = 2;
    val1_0 = (mask >> 0 & 1) ? val3_0 + val2_0 : val1_0;
    val1_1 = (mask >> 1 & 1) ? val3_1 + val2_1 : val1_1;
    val1_2 = (mask >> 2 & 1) ? val3_2 + val2_2 : val1_2;
    val1_3 = (mask >> 3 & 1) ? val3_3 + val2_3 : val1_3;
    w1_0 = (*((reinterpret_cast<uint32_t*>(&val1_0))) >> 16) << 16;
    val1_0 = *reinterpret_cast<float*>(&w1_0);
    w1_1 = (*((reinterpret_cast<uint32_t*>(&val1_1))) >> 16) << 16;
    val1_1 = *reinterpret_cast<float*>(&w1_1);
    w1_2 = (*((reinterpret_cast<uint32_t*>(&val1_2))) >> 16) << 16;
    val1_2 = *reinterpret_cast<float*>(&w1_2);
    w1_3 = (*((reinterpret_cast<uint32_t*>(&val1_3))) >> 16) << 16;
    val1_3 = *reinterpret_cast<float*>(&w1_3);
    mask = 11;
    val1_0 = (mask >> 0 & 1) ? val6_0 + val3_0 : val1_0;
    val1_1 = (mask >> 1 & 1) ? val6_1 + val3_1 : val1_1;
    val1_2 = (mask >> 2 & 1) ? val6_2 + val3_2 : val1_2;
    val1_3 = (mask >> 3 & 1) ? val6_3 + val3_3 : val1_3;
    w1_0 = (*((reinterpret_cast<uint32_t*>(&val1_0))) >> 16) << 16;
    val1_0 = *reinterpret_cast<float*>(&w1_0);
    w1_1 = (*((reinterpret_cast<uint32_t*>(&val1_1))) >> 16) << 16;
    val1_1 = *reinterpret_cast<float*>(&w1_1);
    w1_2 = (*((reinterpret_cast<uint32_t*>(&val1_2))) >> 16) << 16;
    val1_2 = *reinterpret_cast<float*>(&w1_2);
    w1_3 = (*((reinterpret_cast<uint32_t*>(&val1_3))) >> 16) << 16;
    val1_3 = *reinterpret_cast<float*>(&w1_3);
    mask = 5;
    val3_0 = (mask >> 0 & 1) ? val3_0 + val3_0 : val3_0;
    val3_1 = (mask >> 1 & 1) ? val3_1 + val3_1 : val3_1;
    val3_2 = (mask >> 2 & 1) ? val3_2 + val3_2 : val3_2;
    val3_3 = (mask >> 3 & 1) ? val3_3 + val3_3 : val3_3;
    w3_0 = (*((reinterpret_cast<uint32_t*>(&val3_0))) >> 16) << 16;
    val3_0 = *reinterpret_cast<float*>(&w3_0);
    w3_1 = (*((reinterpret_cast<uint32_t*>(&val3_1))) >> 16) << 16;
    val3_1 = *reinterpret_cast<float*>(&w3_1);
    w3_2 = (*((reinterpret_cast<uint32_t*>(&val3_2))) >> 16) << 16;
    val3_2 = *reinterpret_cast<float*>(&w3_2);
    w3_3 = (*((reinterpret_cast<uint32_t*>(&val3_3))) >> 16) << 16;
    val3_3 = *reinterpret_cast<float*>(&w3_3);
    mask = 13;
    val7_0 = (mask >> 0 & 1) ? val5_0 * val6_0 : val7_0;
    val7_1 = (mask >> 1 & 1) ? val5_1 * val6_1 : val7_1;
    val7_2 = (mask >> 2 & 1) ? val5_2 * val6_2 : val7_2;
    val7_3 = (mask >> 3 & 1) ? val5_3 * val6_3 : val7_3;
    w7_0 = (*((reinterpret_cast<uint32_t*>(&val7_0))) >> 16) << 16;
    val7_0 = *reinterpret_cast<float*>(&w7_0);
    w7_1 = (*((reinterpret_cast<uint32_t*>(&val7_1))) >> 16) << 16;
    val7_1 = *reinterpret_cast<float*>(&w7_1);
    w7_2 = (*((reinterpret_cast<uint32_t*>(&val7_2))) >> 16) << 16;
    val7_2 = *reinterpret_cast<float*>(&w7_2);
    w7_3 = (*((reinterpret_cast<uint32_t*>(&val7_3))) >> 16) << 16;
    val7_3 = *reinterpret_cast<float*>(&w7_3);
    mask = 13;
    val1_0 = 18.125;
    val1_1 = 18.125;
    val1_2 = 18.125;
    val1_3 = 18.125;
    w1_0 = (*((reinterpret_cast<uint32_t*>(&val1_0))) >> 16) << 16;
    val1_0 = *reinterpret_cast<float*>(&w1_0);
    w1_1 = (*((reinterpret_cast<uint32_t*>(&val1_1))) >> 16) << 16;
    val1_1 = *reinterpret_cast<float*>(&w1_1);
    w1_2 = (*((reinterpret_cast<uint32_t*>(&val1_2))) >> 16) << 16;
    val1_2 = *reinterpret_cast<float*>(&w1_2);
    w1_3 = (*((reinterpret_cast<uint32_t*>(&val1_3))) >> 16) << 16;
    val1_3 = *reinterpret_cast<float*>(&w1_3);
    mask = 11;
    val7_0 = (mask >> 0 & 1) ? val2_0 - val5_0 : val7_0;
    val7_1 = (mask >> 1 & 1) ? val2_1 - val5_1 : val7_1;
    val7_2 = (mask >> 2 & 1) ? val2_2 - val5_2 : val7_2;
    val7_3 = (mask >> 3 & 1) ? val2_3 - val5_3 : val7_3;
    w7_0 = (*((reinterpret_cast<uint32_t*>(&val7_0))) >> 16) << 16;
    val7_0 = *reinterpret_cast<float*>(&w7_0);
    w7_1 = (*((reinterpret_cast<uint32_t*>(&val7_1))) >> 16) << 16;
    val7_1 = *reinterpret_cast<float*>(&w7_1);
    w7_2 = (*((reinterpret_cast<uint32_t*>(&val7_2))) >> 16) << 16;
    val7_2 = *reinterpret_cast<float*>(&w7_2);
    w7_3 = (*((reinterpret_cast<uint32_t*>(&val7_3))) >> 16) << 16;
    val7_3 = *reinterpret_cast<float*>(&w7_3);
    mask = 10;
    val2_0 = 5.375;
    val2_1 = 5.375;
    val2_2 = 5.375;
    val2_3 = 5.375;
    w2_0 = (*((reinterpret_cast<uint32_t*>(&val2_0))) >> 16) << 16;
    val2_0 = *reinterpret_cast<float*>(&w2_0);
    w2_1 = (*((reinterpret_cast<uint32_t*>(&val2_1))) >> 16) << 16;
    val2_1 = *reinterpret_cast<float*>(&w2_1);
    w2_2 = (*((reinterpret_cast<uint32_t*>(&val2_2))) >> 16) << 16;
    val2_2 = *reinterpret_cast<float*>(&w2_2);
    w2_3 = (*((reinterpret_cast<uint32_t*>(&val2_3))) >> 16) << 16;
    val2_3 = *reinterpret_cast<float*>(&w2_3);
    mask = 2;
    val3_0 = (mask >> 0 & 1) ? val4_0 * val3_0 + val3_0 : val3_0;
    val3_1 = (mask >> 1 & 1) ? val4_1 * val3_1 + val3_1 : val3_1;
    val3_2 = (mask >> 2 & 1) ? val4_2 * val3_2 + val3_2 : val3_2;
    val3_3 = (mask >> 3 & 1) ? val4_3 * val3_3 + val3_3 : val3_3;
    w3_0 = (*((reinterpret_cast<uint32_t*>(&val3_0))) >> 16) << 16;
    val3_0 = *reinterpret_cast<float*>(&w3_0);
    w3_1 = (*((reinterpret_cast<uint32_t*>(&val3_1))) >> 16) << 16;
    val3_1 = *reinterpret_cast<float*>(&w3_1);
    w3_2 = (*((reinterpret_cast<uint32_t*>(&val3_2))) >> 16) << 16;
    val3_2 = *reinterpret_cast<float*>(&w3_2);
    w3_3 = (*((reinterpret_cast<uint32_t*>(&val3_3))) >> 16) << 16;
    val3_3 = *reinterpret_cast<float*>(&w3_3);
    mask = 1;
    val3_0 = (mask >> 0 & 1) ? val4_0 * val4_0 + val3_0 : val3_0;
    val3_1 = (mask >> 1 & 1) ? val4_1 * val4_1 + val3_1 : val3_1;
    val3_2 = (mask >> 2 & 1) ? val4_2 * val4_2 + val3_2 : val3_2;
    val3_3 = (mask >> 3 & 1) ? val4_3 * val4_3 + val3_3 : val3_3;
    w3_0 = (*((reinterpret_cast<uint32_t*>(&val3_0))) >> 16) << 16;
    val3_0 = *reinterpret_cast<float*>(&w3_0);
    w3_1 = (*((reinterpret_cast<uint32_t*>(&val3_1))) >> 16) << 16;
    val3_1 = *reinterpret_cast<float*>(&w3_1);
    w3_2 = (*((reinterpret_cast<uint32_t*>(&val3_2))) >> 16) << 16;
    val3_2 = *reinterpret_cast<float*>(&w3_2);
    w3_3 = (*((reinterpret_cast<uint32_t*>(&val3_3))) >> 16) << 16;
    val3_3 = *reinterpret_cast<float*>(&w3_3);
    mask = 6;
    val6_0 = (mask >> 0 & 1) ? val4_0 * val3_0 : val6_0;
    val6_1 = (mask >> 1 & 1) ? val4_1 * val3_1 : val6_1;
    val6_2 = (mask >> 2 & 1) ? val4_2 * val3_2 : val6_2;
    val6_3 = (mask >> 3 & 1) ? val4_3 * val3_3 : val6_3;
    w6_0 = (*((reinterpret_cast<uint32_t*>(&val6_0))) >> 16) << 16;
    val6_0 = *reinterpret_cast<float*>(&w6_0);
    w6_1 = (*((reinterpret_cast<uint32_t*>(&val6_1))) >> 16) << 16;
    val6_1 = *reinterpret_cast<float*>(&w6_1);
    w6_2 = (*((reinterpret_cast<uint32_t*>(&val6_2))) >> 16) << 16;
    val6_2 = *reinterpret_cast<float*>(&w6_2);
    w6_3 = (*((reinterpret_cast<uint32_t*>(&val6_3))) >> 16) << 16;
    val6_3 = *reinterpret_cast<float*>(&w6_3);
    mask = 5;
    val3_0 = (mask >> 0 & 1) ? val6_0 * val4_0 + val3_0 : val3_0;
    val3_1 = (mask >> 1 & 1) ? val6_1 * val4_1 + val3_1 : val3_1;
    val3_2 = (mask >> 2 & 1) ? val6_2 * val4_2 + val3_2 : val3_2;
    val3_3 = (mask >> 3 & 1) ? val6_3 * val4_3 + val3_3 : val3_3;
    w3_0 = (*((reinterpret_cast<uint32_t*>(&val3_0))) >> 16) << 16;
    val3_0 = *reinterpret_cast<float*>(&w3_0);
    w3_1 = (*((reinterpret_cast<uint32_t*>(&val3_1))) >> 16) << 16;
    val3_1 = *reinterpret_cast<float*>(&w3_1);
    w3_2 = (*((reinterpret_cast<uint32_t*>(&val3_2))) >> 16) << 16;
    val3_2 = *reinterpret_cast<float*>(&w3_2);
    w3_3 = (*((reinterpret_cast<uint32_t*>(&val3_3))) >> 16) << 16;
    val3_3 = *reinterpret_cast<float*>(&w3_3);
    mask = 13;
    val3_0 = (mask >> 0 & 1) ? val5_0 + val6_0 : val3_0;
    val3_1 = (mask >> 1 & 1) ? val5_1 + val6_1 : val3_1;
    val3_2 = (mask >> 2 & 1) ? val5_2 + val6_2 : val3_2;
    val3_3 = (mask >> 3 & 1) ? val5_3 + val6_3 : val3_3;
    w3_0 = (*((reinterpret_cast<uint32_t*>(&val3_0))) >> 16) << 16;
    val3_0 = *reinterpret_cast<float*>(&w3_0);
    w3_1 = (*((reinterpret_cast<uint32_t*>(&val3_1))) >> 16) << 16;
    val3_1 = *reinterpret_cast<float*>(&w3_1);
    w3_2 = (*((reinterpret_cast<uint32_t*>(&val3_2))) >> 16) << 16;
    val3_2 = *reinterpret_cast<float*>(&w3_2);
    w3_3 = (*((reinterpret_cast<uint32_t*>(&val3_3))) >> 16) << 16;
    val3_3 = *reinterpret_cast<float*>(&w3_3);
    mask = 5;
    val2_0 = (mask >> 0 & 1) ? val6_0 - val5_0 : val2_0;
    val2_1 = (mask >> 1 & 1) ? val6_1 - val5_1 : val2_1;
    val2_2 = (mask >> 2 & 1) ? val6_2 - val5_2 : val2_2;
    val2_3 = (mask >> 3 & 1) ? val6_3 - val5_3 : val2_3;
    w2_0 = (*((reinterpret_cast<uint32_t*>(&val2_0))) >> 16) << 16;
    val2_0 = *reinterpret_cast<float*>(&w2_0);
    w2_1 = (*((reinterpret_cast<uint32_t*>(&val2_1))) >> 16) << 16;
    val2_1 = *reinterpret_cast<float*>(&w2_1);
    w2_2 = (*((reinterpret_cast<uint32_t*>(&val2_2))) >> 16) << 16;
    val2_2 = *reinterpret_cast<float*>(&w2_2);
    w2_3 = (*((reinterpret_cast<uint32_t*>(&val2_3))) >> 16) << 16;
    val2_3 = *reinterpret_cast<float*>(&w2_3);
    mask = 13;
    val2_0 = (mask >> 0 & 1) ? val5_0 + val1_0 : val2_0;
    val2_1 = (mask >> 1 & 1) ? val5_1 + val1_1 : val2_1;
    val2_2 = (mask >> 2 & 1) ? val5_2 + val1_2 : val2_2;
    val2_3 = (mask >> 3 & 1) ? val5_3 + val1_3 : val2_3;
    w2_0 = (*((reinterpret_cast<uint32_t*>(&val2_0))) >> 16) << 16;
    val2_0 = *reinterpret_cast<float*>(&w2_0);
    w2_1 = (*((reinterpret_cast<uint32_t*>(&val2_1))) >> 16) << 16;
    val2_1 = *reinterpret_cast<float*>(&w2_1);
    w2_2 = (*((reinterpret_cast<uint32_t*>(&val2_2))) >> 16) << 16;
    val2_2 = *reinterpret_cast<float*>(&w2_2);
    w2_3 = (*((reinterpret_cast<uint32_t*>(&val2_3))) >> 16) << 16;
    val2_3 = *reinterpret_cast<float*>(&w2_3);
    mask = 12;
    val4_0 = 18.375;
    val4_1 = 18.375;
    val4_2 = 18.375;
    val4_3 = 18.375;
    w4_0 = (*((reinterpret_cast<uint32_t*>(&val4_0))) >> 16) << 16;
    val4_0 = *reinterpret_cast<float*>(&w4_0);
    w4_1 = (*((reinterpret_cast<uint32_t*>(&val4_1))) >> 16) << 16;
    val4_1 = *reinterpret_cast<float*>(&w4_1);
    w4_2 = (*((reinterpret_cast<uint32_t*>(&val4_2))) >> 16) << 16;
    val4_2 = *reinterpret_cast<float*>(&w4_2);
    w4_3 = (*((reinterpret_cast<uint32_t*>(&val4_3))) >> 16) << 16;
    val4_3 = *reinterpret_cast<float*>(&w4_3);
    mask = 5;
    val5_0 = 16.625;
    val5_1 = 16.625;
    val5_2 = 16.625;
    val5_3 = 16.625;
    w5_0 = (*((reinterpret_cast<uint32_t*>(&val5_0))) >> 16) << 16;
    val5_0 = *reinterpret_cast<float*>(&w5_0);
    w5_1 = (*((reinterpret_cast<uint32_t*>(&val5_1))) >> 16) << 16;
    val5_1 = *reinterpret_cast<float*>(&w5_1);
    w5_2 = (*((reinterpret_cast<uint32_t*>(&val5_2))) >> 16) << 16;
    val5_2 = *reinterpret_cast<float*>(&w5_2);
    w5_3 = (*((reinterpret_cast<uint32_t*>(&val5_3))) >> 16) << 16;
    val5_3 = *reinterpret_cast<float*>(&w5_3);
    mask = 13;
    val5_0 = (mask >> 0 & 1) ? val1_0 + val1_0 : val5_0;
    val5_1 = (mask >> 1 & 1) ? val1_1 + val1_1 : val5_1;
    val5_2 = (mask >> 2 & 1) ? val1_2 + val1_2 : val5_2;
    val5_3 = (mask >> 3 & 1) ? val1_3 + val1_3 : val5_3;
    w5_0 = (*((reinterpret_cast<uint32_t*>(&val5_0))) >> 16) << 16;
    val5_0 = *reinterpret_cast<float*>(&w5_0);
    w5_1 = (*((reinterpret_cast<uint32_t*>(&val5_1))) >> 16) << 16;
    val5_1 = *reinterpret_cast<float*>(&w5_1);
    w5_2 = (*((reinterpret_cast<uint32_t*>(&val5_2))) >> 16) << 16;
    val5_2 = *reinterpret_cast<float*>(&w5_2);
    w5_3 = (*((reinterpret_cast<uint32_t*>(&val5_3))) >> 16) << 16;
    val5_3 = *reinterpret_cast<float*>(&w5_3);
    mask = 2;
    val5_0 = (mask >> 0 & 1) ? sqrt(val3_0) : val5_0;
    val5_1 = (mask >> 1 & 1) ? sqrt(val3_1) : val5_1;
    val5_2 = (mask >> 2 & 1) ? sqrt(val3_2) : val5_2;
    val5_3 = (mask >> 3 & 1) ? sqrt(val3_3) : val5_3;
    w5_0 = (*((reinterpret_cast<uint32_t*>(&val5_0))) >> 16) << 16;
    val5_0 = *reinterpret_cast<float*>(&w5_0);
    w5_1 = (*((reinterpret_cast<uint32_t*>(&val5_1))) >> 16) << 16;
    val5_1 = *reinterpret_cast<float*>(&w5_1);
    w5_2 = (*((reinterpret_cast<uint32_t*>(&val5_2))) >> 16) << 16;
    val5_2 = *reinterpret_cast<float*>(&w5_2);
    w5_3 = (*((reinterpret_cast<uint32_t*>(&val5_3))) >> 16) << 16;
    val5_3 = *reinterpret_cast<float*>(&w5_3);
    uint64_t final_result_0 = (uint64_t)(*reinterpret_cast<uint32_t*>(&val0_0) >> 16) << 0 | (uint64_t)(*reinterpret_cast<uint32_t*>(&val0_1) >> 16) << 16 |(uint64_t)(*reinterpret_cast<uint32_t*>(&val0_2) >> 16) << 32 |(uint64_t)(*reinterpret_cast<uint32_t*>(&val0_3) >> 16) << 48;
    EXPECT_TRUE(acc0.testReg(0, RegId::X16, final_result_0));
    uint64_t final_result_1 = (uint64_t)(*reinterpret_cast<uint32_t*>(&val1_0) >> 16) << 0 | (uint64_t)(*reinterpret_cast<uint32_t*>(&val1_1) >> 16) << 16 |(uint64_t)(*reinterpret_cast<uint32_t*>(&val1_2) >> 16) << 32 |(uint64_t)(*reinterpret_cast<uint32_t*>(&val1_3) >> 16) << 48;
    EXPECT_TRUE(acc0.testReg(0, RegId::X17, final_result_1));
    uint64_t final_result_2 = (uint64_t)(*reinterpret_cast<uint32_t*>(&val2_0) >> 16) << 0 | (uint64_t)(*reinterpret_cast<uint32_t*>(&val2_1) >> 16) << 16 |(uint64_t)(*reinterpret_cast<uint32_t*>(&val2_2) >> 16) << 32 |(uint64_t)(*reinterpret_cast<uint32_t*>(&val2_3) >> 16) << 48;
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result_2));
    uint64_t final_result_3 = (uint64_t)(*reinterpret_cast<uint32_t*>(&val3_0) >> 16) << 0 | (uint64_t)(*reinterpret_cast<uint32_t*>(&val3_1) >> 16) << 16 |(uint64_t)(*reinterpret_cast<uint32_t*>(&val3_2) >> 16) << 32 |(uint64_t)(*reinterpret_cast<uint32_t*>(&val3_3) >> 16) << 48;
    EXPECT_TRUE(acc0.testReg(0, RegId::X19, final_result_3));
    uint64_t final_result_4 = (uint64_t)(*reinterpret_cast<uint32_t*>(&val4_0) >> 16) << 0 | (uint64_t)(*reinterpret_cast<uint32_t*>(&val4_1) >> 16) << 16 |(uint64_t)(*reinterpret_cast<uint32_t*>(&val4_2) >> 16) << 32 |(uint64_t)(*reinterpret_cast<uint32_t*>(&val4_3) >> 16) << 48;
    EXPECT_TRUE(acc0.testReg(0, RegId::X20, final_result_4));
    uint64_t final_result_5 = (uint64_t)(*reinterpret_cast<uint32_t*>(&val5_0) >> 16) << 0 | (uint64_t)(*reinterpret_cast<uint32_t*>(&val5_1) >> 16) << 16 |(uint64_t)(*reinterpret_cast<uint32_t*>(&val5_2) >> 16) << 32 |(uint64_t)(*reinterpret_cast<uint32_t*>(&val5_3) >> 16) << 48;
    EXPECT_TRUE(acc0.testReg(0, RegId::X21, final_result_5));
    uint64_t final_result_6 = (uint64_t)(*reinterpret_cast<uint32_t*>(&val6_0) >> 16) << 0 | (uint64_t)(*reinterpret_cast<uint32_t*>(&val6_1) >> 16) << 16 |(uint64_t)(*reinterpret_cast<uint32_t*>(&val6_2) >> 16) << 32 |(uint64_t)(*reinterpret_cast<uint32_t*>(&val6_3) >> 16) << 48;
    EXPECT_TRUE(acc0.testReg(0, RegId::X22, final_result_6));
    uint64_t final_result_7 = (uint64_t)(*reinterpret_cast<uint32_t*>(&val7_0) >> 16) << 0 | (uint64_t)(*reinterpret_cast<uint32_t*>(&val7_1) >> 16) << 16 |(uint64_t)(*reinterpret_cast<uint32_t*>(&val7_2) >> 16) << 32 |(uint64_t)(*reinterpret_cast<uint32_t*>(&val7_3) >> 16) << 48;
    EXPECT_TRUE(acc0.testReg(0, RegId::X23, final_result_7));
}
