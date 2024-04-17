#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"
#include <cmath>
#include <cfenv>

using namespace basim;

class Vdiv_i32Test : public ::testing::Test {
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
TEST_F(Vdiv_i32Test, vdiv_i32_0){
    acc0.initSetup(0,"testprogs/binaries/vdiv_i32_0.bin", 0);
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
    uint32_t uargs0 = 713149591, uargs1 = 2021094657;
    uint32_t uargs2 = -213459848, uargs3 =  37643193;
    uint32_t uargs4 = 815489285, uargs5 =  700270974;
    uint32_t mask = 2;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 / *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vdiv_i32Test, vdiv_i32_1){
    acc0.initSetup(0,"testprogs/binaries/vdiv_i32_1.bin", 0);
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
    uint32_t uargs0 = -1882684912, uargs1 = 84250778;
    uint32_t uargs2 = -159574190, uargs3 =  -1328169801;
    uint32_t uargs4 = -550736783, uargs5 =  -1572591189;
    uint32_t mask = 2;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 / *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vdiv_i32Test, vdiv_i32_2){
    acc0.initSetup(0,"testprogs/binaries/vdiv_i32_2.bin", 0);
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
    uint32_t uargs0 = -487183571, uargs1 = 172776407;
    uint32_t uargs2 = -2010778401, uargs3 =  -145020537;
    uint32_t uargs4 = -194138048, uargs5 =  -1717531998;
    uint32_t mask = 2;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 / *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vdiv_i32Test, vdiv_i32_3){
    acc0.initSetup(0,"testprogs/binaries/vdiv_i32_3.bin", 0);
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
    uint32_t uargs0 = 231973582, uargs1 = -1692738604;
    uint32_t uargs2 = -482458296, uargs3 =  212564753;
    uint32_t uargs4 = 1519631403, uargs5 =  1302117436;
    uint32_t mask = 3;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 / *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vdiv_i32Test, vdiv_i32_4){
    acc0.initSetup(0,"testprogs/binaries/vdiv_i32_4.bin", 0);
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
    uint32_t uargs0 = 1564041692, uargs1 = 711856654;
    uint32_t uargs2 = -917952473, uargs3 =  1189939846;
    uint32_t uargs4 = -1159387687, uargs5 =  21463538;
    uint32_t mask = 3;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 / *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vdiv_i32Test, vdiv_i32_5){
    acc0.initSetup(0,"testprogs/binaries/vdiv_i32_5.bin", 0);
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
    uint32_t uargs0 = -1187844047, uargs1 = -1598937945;
    uint32_t uargs2 = -1474505614, uargs3 =  -653778960;
    uint32_t uargs4 = -1903902258, uargs5 =  -1593236030;
    uint32_t mask = 3;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 / *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vdiv_i32Test, vdiv_i32_6){
    acc0.initSetup(0,"testprogs/binaries/vdiv_i32_6.bin", 0);
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
    uint32_t uargs0 = -1948534764, uargs1 = 1110309158;
    uint32_t uargs2 = -1027800070, uargs3 =  -1445830726;
    uint32_t uargs4 = -2017709722, uargs5 =  -1464266316;
    uint32_t mask = 2;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 / *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vdiv_i32Test, vdiv_i32_7){
    acc0.initSetup(0,"testprogs/binaries/vdiv_i32_7.bin", 0);
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
    uint32_t uargs0 = -185038309, uargs1 = -1023585402;
    uint32_t uargs2 = -2068736015, uargs3 =  -1802578135;
    uint32_t uargs4 = 1861091143, uargs5 =  1164830930;
    uint32_t mask = 3;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 / *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vdiv_i32Test, vdiv_i32_8){
    acc0.initSetup(0,"testprogs/binaries/vdiv_i32_8.bin", 0);
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
    uint32_t uargs0 = -2119272157, uargs1 = 301419322;
    uint32_t uargs2 = -640405526, uargs3 =  -1920260794;
    uint32_t uargs4 = 392023705, uargs5 =  -885768778;
    uint32_t mask = 1;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 / *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vdiv_i32Test, vdiv_i32_9){
    acc0.initSetup(0,"testprogs/binaries/vdiv_i32_9.bin", 0);
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
    uint32_t uargs0 = -977752583, uargs1 = -308583982;
    uint32_t uargs2 = 1285075234, uargs3 =  1291935551;
    uint32_t uargs4 = 2065722401, uargs5 =  1597985922;
    uint32_t mask = 3;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 / *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vdiv_i32Test, vdiv_i32_10){
    acc0.initSetup(0,"testprogs/binaries/vdiv_i32_10.bin", 0);
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
    uint32_t uargs0 = -553221398, uargs1 = 2028889601;
    uint32_t uargs2 = 1705700111, uargs3 =  501530752;
    uint32_t uargs4 = 1094528270, uargs5 =  -1811697291;
    uint32_t mask = 2;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 / *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vdiv_i32Test, vdiv_i32_11){
    acc0.initSetup(0,"testprogs/binaries/vdiv_i32_11.bin", 0);
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
    uint32_t uargs0 = -415291916, uargs1 = -604567384;
    uint32_t uargs2 = -1653770309, uargs3 =  499308321;
    uint32_t uargs4 = 2105397135, uargs5 =  -1484392135;
    uint32_t mask = 1;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 / *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vdiv_i32Test, vdiv_i32_12){
    acc0.initSetup(0,"testprogs/binaries/vdiv_i32_12.bin", 0);
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
    uint32_t uargs0 = 1463111839, uargs1 = 1992302090;
    uint32_t uargs2 = 1998080108, uargs3 =  2054406862;
    uint32_t uargs4 = 231142006, uargs5 =  -1771474886;
    uint32_t mask = 3;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 / *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vdiv_i32Test, vdiv_i32_13){
    acc0.initSetup(0,"testprogs/binaries/vdiv_i32_13.bin", 0);
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
    uint32_t uargs0 = -791471284, uargs1 = -687919307;
    uint32_t uargs2 = 1427167393, uargs3 =  -1425331579;
    uint32_t uargs4 = -1330423340, uargs5 =  -1616280979;
    uint32_t mask = 3;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 / *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vdiv_i32Test, vdiv_i32_14){
    acc0.initSetup(0,"testprogs/binaries/vdiv_i32_14.bin", 0);
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
    uint32_t uargs0 = 283278178, uargs1 = 728427818;
    uint32_t uargs2 = -743016024, uargs3 =  331066418;
    uint32_t uargs4 = -951580091, uargs5 =  91989001;
    uint32_t mask = 2;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 / *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vdiv_i32Test, vdiv_i32_15){
    acc0.initSetup(0,"testprogs/binaries/vdiv_i32_15.bin", 0);
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
    uint32_t uargs0 = -691747634, uargs1 = -692739986;
    uint32_t uargs2 = 2144322416, uargs3 =  -79448895;
    uint32_t uargs4 = -1047605046, uargs5 =  1494069448;
    uint32_t mask = 3;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 / *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vdiv_i32Test, vdiv_i32_16){
    acc0.initSetup(0,"testprogs/binaries/vdiv_i32_16.bin", 0);
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
    uint32_t uargs0 = -637958362, uargs1 = 1156433923;
    uint32_t uargs2 = -1904199371, uargs3 =  -1404002602;
    uint32_t uargs4 = 1138096861, uargs5 =  1337569020;
    uint32_t mask = 2;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 / *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vdiv_i32Test, vdiv_i32_17){
    acc0.initSetup(0,"testprogs/binaries/vdiv_i32_17.bin", 0);
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
    uint32_t uargs0 = -2114620096, uargs1 = 1284031171;
    uint32_t uargs2 = 1188870615, uargs3 =  965672608;
    uint32_t uargs4 = 1507403691, uargs5 =  1923922203;
    uint32_t mask = 3;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 / *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vdiv_i32Test, vdiv_i32_18){
    acc0.initSetup(0,"testprogs/binaries/vdiv_i32_18.bin", 0);
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
    uint32_t uargs0 = -1526597635, uargs1 = 2038456788;
    uint32_t uargs2 = -1130249232, uargs3 =  -185078152;
    uint32_t uargs4 = -1679640827, uargs5 =  -1121247153;
    uint32_t mask = 2;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 / *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vdiv_i32Test, vdiv_i32_19){
    acc0.initSetup(0,"testprogs/binaries/vdiv_i32_19.bin", 0);
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
    uint32_t uargs0 = 1869959138, uargs1 = -748818716;
    uint32_t uargs2 = -1997069673, uargs3 =  1628964386;
    uint32_t uargs4 = -2098443978, uargs5 =  -1096613091;
    uint32_t mask = 1;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 / *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 / *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
