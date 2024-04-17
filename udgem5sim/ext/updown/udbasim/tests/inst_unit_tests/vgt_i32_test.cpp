#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"
#include <cmath>
#include <cfenv>

using namespace basim;

class Vgt_i32Test : public ::testing::Test {
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
TEST_F(Vgt_i32Test, vgt_i32_0){
    acc0.initSetup(0,"testprogs/binaries/vgt_i32_0.bin", 0);
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
    int val0, val1;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 333480956, uargs1 = 45055947;
    uint32_t uargs2 = 1169397265, uargs3 =  81344178;
    uint32_t uargs4 = -1624262504, uargs5 =  631943734;
    uint32_t mask = 2;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    uint64_t result = 0;
    result |= (mask & 1) & (*fargs0 > *fargs2);
    result |= ((mask >> 1 & 1) & (*fargs1 > *fargs3)) << 1;
    val0 = (*fargs4);
    val1 = (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (((uint64_t)(*w0) | ((uint64_t)(*w1) << 32)) & (~(uint64_t)(mask))) | result;
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vgt_i32Test, vgt_i32_1){
    acc0.initSetup(0,"testprogs/binaries/vgt_i32_1.bin", 0);
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
    int val0, val1;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 1982787732, uargs1 = 2062807338;
    uint32_t uargs2 = -1054859658, uargs3 =  -1650986485;
    uint32_t uargs4 = -258148992, uargs5 =  770517264;
    uint32_t mask = 3;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    uint64_t result = 0;
    result |= (mask & 1) & (*fargs0 > *fargs2);
    result |= ((mask >> 1 & 1) & (*fargs1 > *fargs3)) << 1;
    val0 = (*fargs4);
    val1 = (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (((uint64_t)(*w0) | ((uint64_t)(*w1) << 32)) & (~(uint64_t)(mask))) | result;
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vgt_i32Test, vgt_i32_2){
    acc0.initSetup(0,"testprogs/binaries/vgt_i32_2.bin", 0);
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
    int val0, val1;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 1104811397, uargs1 = -1832926988;
    uint32_t uargs2 = 751785866, uargs3 =  1370659316;
    uint32_t uargs4 = -866064959, uargs5 =  148567189;
    uint32_t mask = 2;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    uint64_t result = 0;
    result |= (mask & 1) & (*fargs0 > *fargs2);
    result |= ((mask >> 1 & 1) & (*fargs1 > *fargs3)) << 1;
    val0 = (*fargs4);
    val1 = (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (((uint64_t)(*w0) | ((uint64_t)(*w1) << 32)) & (~(uint64_t)(mask))) | result;
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vgt_i32Test, vgt_i32_3){
    acc0.initSetup(0,"testprogs/binaries/vgt_i32_3.bin", 0);
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
    int val0, val1;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 1295791515, uargs1 = -198771805;
    uint32_t uargs2 = 1831623106, uargs3 =  1900072089;
    uint32_t uargs4 = -1479324394, uargs5 =  431973928;
    uint32_t mask = 2;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    uint64_t result = 0;
    result |= (mask & 1) & (*fargs0 > *fargs2);
    result |= ((mask >> 1 & 1) & (*fargs1 > *fargs3)) << 1;
    val0 = (*fargs4);
    val1 = (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (((uint64_t)(*w0) | ((uint64_t)(*w1) << 32)) & (~(uint64_t)(mask))) | result;
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vgt_i32Test, vgt_i32_4){
    acc0.initSetup(0,"testprogs/binaries/vgt_i32_4.bin", 0);
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
    int val0, val1;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 1984102827, uargs1 = 1516120268;
    uint32_t uargs2 = -708698194, uargs3 =  1602173052;
    uint32_t uargs4 = 2103372878, uargs5 =  322571013;
    uint32_t mask = 2;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    uint64_t result = 0;
    result |= (mask & 1) & (*fargs0 > *fargs2);
    result |= ((mask >> 1 & 1) & (*fargs1 > *fargs3)) << 1;
    val0 = (*fargs4);
    val1 = (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (((uint64_t)(*w0) | ((uint64_t)(*w1) << 32)) & (~(uint64_t)(mask))) | result;
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vgt_i32Test, vgt_i32_5){
    acc0.initSetup(0,"testprogs/binaries/vgt_i32_5.bin", 0);
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
    int val0, val1;
    uint64_t FSCR = 0;
    uint32_t uargs0 = -1333386399, uargs1 = -1750612643;
    uint32_t uargs2 = 1928391854, uargs3 =  -403212389;
    uint32_t uargs4 = 191732669, uargs5 =  1687176847;
    uint32_t mask = 2;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    uint64_t result = 0;
    result |= (mask & 1) & (*fargs0 > *fargs2);
    result |= ((mask >> 1 & 1) & (*fargs1 > *fargs3)) << 1;
    val0 = (*fargs4);
    val1 = (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (((uint64_t)(*w0) | ((uint64_t)(*w1) << 32)) & (~(uint64_t)(mask))) | result;
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vgt_i32Test, vgt_i32_6){
    acc0.initSetup(0,"testprogs/binaries/vgt_i32_6.bin", 0);
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
    int val0, val1;
    uint64_t FSCR = 0;
    uint32_t uargs0 = -663205008, uargs1 = -483791032;
    uint32_t uargs2 = 121101836, uargs3 =  -798070691;
    uint32_t uargs4 = -278528829, uargs5 =  1542447893;
    uint32_t mask = 1;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    uint64_t result = 0;
    result |= (mask & 1) & (*fargs0 > *fargs2);
    result |= ((mask >> 1 & 1) & (*fargs1 > *fargs3)) << 1;
    val0 = (*fargs4);
    val1 = (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (((uint64_t)(*w0) | ((uint64_t)(*w1) << 32)) & (~(uint64_t)(mask))) | result;
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vgt_i32Test, vgt_i32_7){
    acc0.initSetup(0,"testprogs/binaries/vgt_i32_7.bin", 0);
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
    int val0, val1;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 683714563, uargs1 = -1687199854;
    uint32_t uargs2 = -703585940, uargs3 =  -1912388752;
    uint32_t uargs4 = 732731037, uargs5 =  -86113889;
    uint32_t mask = 3;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    uint64_t result = 0;
    result |= (mask & 1) & (*fargs0 > *fargs2);
    result |= ((mask >> 1 & 1) & (*fargs1 > *fargs3)) << 1;
    val0 = (*fargs4);
    val1 = (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (((uint64_t)(*w0) | ((uint64_t)(*w1) << 32)) & (~(uint64_t)(mask))) | result;
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vgt_i32Test, vgt_i32_8){
    acc0.initSetup(0,"testprogs/binaries/vgt_i32_8.bin", 0);
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
    int val0, val1;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 219043389, uargs1 = -410561239;
    uint32_t uargs2 = 2094386168, uargs3 =  -1119421499;
    uint32_t uargs4 = -1506114209, uargs5 =  -889277603;
    uint32_t mask = 2;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    uint64_t result = 0;
    result |= (mask & 1) & (*fargs0 > *fargs2);
    result |= ((mask >> 1 & 1) & (*fargs1 > *fargs3)) << 1;
    val0 = (*fargs4);
    val1 = (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (((uint64_t)(*w0) | ((uint64_t)(*w1) << 32)) & (~(uint64_t)(mask))) | result;
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vgt_i32Test, vgt_i32_9){
    acc0.initSetup(0,"testprogs/binaries/vgt_i32_9.bin", 0);
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
    int val0, val1;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 468450945, uargs1 = -1087639910;
    uint32_t uargs2 = -1169243633, uargs3 =  -508934344;
    uint32_t uargs4 = 2009947411, uargs5 =  -642022257;
    uint32_t mask = 2;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    uint64_t result = 0;
    result |= (mask & 1) & (*fargs0 > *fargs2);
    result |= ((mask >> 1 & 1) & (*fargs1 > *fargs3)) << 1;
    val0 = (*fargs4);
    val1 = (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (((uint64_t)(*w0) | ((uint64_t)(*w1) << 32)) & (~(uint64_t)(mask))) | result;
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vgt_i32Test, vgt_i32_10){
    acc0.initSetup(0,"testprogs/binaries/vgt_i32_10.bin", 0);
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
    int val0, val1;
    uint64_t FSCR = 0;
    uint32_t uargs0 = -669835918, uargs1 = -1946754791;
    uint32_t uargs2 = 1604376334, uargs3 =  -2006969482;
    uint32_t uargs4 = 1628943804, uargs5 =  18969812;
    uint32_t mask = 3;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    uint64_t result = 0;
    result |= (mask & 1) & (*fargs0 > *fargs2);
    result |= ((mask >> 1 & 1) & (*fargs1 > *fargs3)) << 1;
    val0 = (*fargs4);
    val1 = (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (((uint64_t)(*w0) | ((uint64_t)(*w1) << 32)) & (~(uint64_t)(mask))) | result;
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vgt_i32Test, vgt_i32_11){
    acc0.initSetup(0,"testprogs/binaries/vgt_i32_11.bin", 0);
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
    int val0, val1;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 238352570, uargs1 = -1519067045;
    uint32_t uargs2 = 2125832628, uargs3 =  -1435664038;
    uint32_t uargs4 = 360399586, uargs5 =  -2122234310;
    uint32_t mask = 1;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    uint64_t result = 0;
    result |= (mask & 1) & (*fargs0 > *fargs2);
    result |= ((mask >> 1 & 1) & (*fargs1 > *fargs3)) << 1;
    val0 = (*fargs4);
    val1 = (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (((uint64_t)(*w0) | ((uint64_t)(*w1) << 32)) & (~(uint64_t)(mask))) | result;
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vgt_i32Test, vgt_i32_12){
    acc0.initSetup(0,"testprogs/binaries/vgt_i32_12.bin", 0);
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
    int val0, val1;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 214020617, uargs1 = -267530424;
    uint32_t uargs2 = 2029428032, uargs3 =  1253981581;
    uint32_t uargs4 = -1933078172, uargs5 =  -1479526231;
    uint32_t mask = 1;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    uint64_t result = 0;
    result |= (mask & 1) & (*fargs0 > *fargs2);
    result |= ((mask >> 1 & 1) & (*fargs1 > *fargs3)) << 1;
    val0 = (*fargs4);
    val1 = (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (((uint64_t)(*w0) | ((uint64_t)(*w1) << 32)) & (~(uint64_t)(mask))) | result;
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vgt_i32Test, vgt_i32_13){
    acc0.initSetup(0,"testprogs/binaries/vgt_i32_13.bin", 0);
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
    int val0, val1;
    uint64_t FSCR = 0;
    uint32_t uargs0 = -1746462376, uargs1 = -1568260485;
    uint32_t uargs2 = 1778384093, uargs3 =  -724892996;
    uint32_t uargs4 = 1905001337, uargs5 =  704530893;
    uint32_t mask = 3;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    uint64_t result = 0;
    result |= (mask & 1) & (*fargs0 > *fargs2);
    result |= ((mask >> 1 & 1) & (*fargs1 > *fargs3)) << 1;
    val0 = (*fargs4);
    val1 = (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (((uint64_t)(*w0) | ((uint64_t)(*w1) << 32)) & (~(uint64_t)(mask))) | result;
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vgt_i32Test, vgt_i32_14){
    acc0.initSetup(0,"testprogs/binaries/vgt_i32_14.bin", 0);
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
    int val0, val1;
    uint64_t FSCR = 0;
    uint32_t uargs0 = -918770954, uargs1 = 3555612;
    uint32_t uargs2 = 1908988756, uargs3 =  -699700747;
    uint32_t uargs4 = -604439848, uargs5 =  1747960479;
    uint32_t mask = 2;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    uint64_t result = 0;
    result |= (mask & 1) & (*fargs0 > *fargs2);
    result |= ((mask >> 1 & 1) & (*fargs1 > *fargs3)) << 1;
    val0 = (*fargs4);
    val1 = (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (((uint64_t)(*w0) | ((uint64_t)(*w1) << 32)) & (~(uint64_t)(mask))) | result;
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vgt_i32Test, vgt_i32_15){
    acc0.initSetup(0,"testprogs/binaries/vgt_i32_15.bin", 0);
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
    int val0, val1;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 12178212, uargs1 = -1826241346;
    uint32_t uargs2 = 1527565617, uargs3 =  1480761478;
    uint32_t uargs4 = 1132545763, uargs5 =  406813371;
    uint32_t mask = 3;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    uint64_t result = 0;
    result |= (mask & 1) & (*fargs0 > *fargs2);
    result |= ((mask >> 1 & 1) & (*fargs1 > *fargs3)) << 1;
    val0 = (*fargs4);
    val1 = (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (((uint64_t)(*w0) | ((uint64_t)(*w1) << 32)) & (~(uint64_t)(mask))) | result;
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vgt_i32Test, vgt_i32_16){
    acc0.initSetup(0,"testprogs/binaries/vgt_i32_16.bin", 0);
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
    int val0, val1;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 270537411, uargs1 = 649717661;
    uint32_t uargs2 = 522944198, uargs3 =  -1016143843;
    uint32_t uargs4 = 269706216, uargs5 =  -1194224958;
    uint32_t mask = 1;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    uint64_t result = 0;
    result |= (mask & 1) & (*fargs0 > *fargs2);
    result |= ((mask >> 1 & 1) & (*fargs1 > *fargs3)) << 1;
    val0 = (*fargs4);
    val1 = (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (((uint64_t)(*w0) | ((uint64_t)(*w1) << 32)) & (~(uint64_t)(mask))) | result;
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vgt_i32Test, vgt_i32_17){
    acc0.initSetup(0,"testprogs/binaries/vgt_i32_17.bin", 0);
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
    int val0, val1;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 1905780059, uargs1 = 460393126;
    uint32_t uargs2 = -455024673, uargs3 =  929685834;
    uint32_t uargs4 = 417545056, uargs5 =  1428381770;
    uint32_t mask = 2;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    uint64_t result = 0;
    result |= (mask & 1) & (*fargs0 > *fargs2);
    result |= ((mask >> 1 & 1) & (*fargs1 > *fargs3)) << 1;
    val0 = (*fargs4);
    val1 = (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (((uint64_t)(*w0) | ((uint64_t)(*w1) << 32)) & (~(uint64_t)(mask))) | result;
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vgt_i32Test, vgt_i32_18){
    acc0.initSetup(0,"testprogs/binaries/vgt_i32_18.bin", 0);
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
    int val0, val1;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 983944147, uargs1 = -1726270399;
    uint32_t uargs2 = 653183718, uargs3 =  424841089;
    uint32_t uargs4 = 1151089479, uargs5 =  -558705699;
    uint32_t mask = 1;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    uint64_t result = 0;
    result |= (mask & 1) & (*fargs0 > *fargs2);
    result |= ((mask >> 1 & 1) & (*fargs1 > *fargs3)) << 1;
    val0 = (*fargs4);
    val1 = (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (((uint64_t)(*w0) | ((uint64_t)(*w1) << 32)) & (~(uint64_t)(mask))) | result;
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vgt_i32Test, vgt_i32_19){
    acc0.initSetup(0,"testprogs/binaries/vgt_i32_19.bin", 0);
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
    int val0, val1;
    uint64_t FSCR = 0;
    uint32_t uargs0 = 648578580, uargs1 = 701075262;
    uint32_t uargs2 = 1984231305, uargs3 =  835753202;
    uint32_t uargs4 = 2112370243, uargs5 =  322371900;
    uint32_t mask = 2;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    uint64_t result = 0;
    result |= (mask & 1) & (*fargs0 > *fargs2);
    result |= ((mask >> 1 & 1) & (*fargs1 > *fargs3)) << 1;
    val0 = (*fargs4);
    val1 = (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (((uint64_t)(*w0) | ((uint64_t)(*w1) << 32)) & (~(uint64_t)(mask))) | result;
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
