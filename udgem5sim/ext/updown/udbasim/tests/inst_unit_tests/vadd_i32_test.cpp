#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"
#include <cmath>
#include <cfenv>

using namespace basim;

class Vadd_i32Test : public ::testing::Test {
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
TEST_F(Vadd_i32Test, vadd_i32_0){
    acc0.initSetup(0,"testprogs/binaries/vadd_i32_0.bin", 0);
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
    uint32_t uargs0 = 194123289, uargs1 = 1365078506;
    uint32_t uargs2 = -1775005667, uargs3 =  -1019096506;
    uint32_t uargs4 = -1698845822, uargs5 =  1970645840;
    uint32_t mask = 1;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 + *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 + *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vadd_i32Test, vadd_i32_1){
    acc0.initSetup(0,"testprogs/binaries/vadd_i32_1.bin", 0);
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
    uint32_t uargs0 = -1367830290, uargs1 = -255490830;
    uint32_t uargs2 = -1896961573, uargs3 =  -315335343;
    uint32_t uargs4 = -561812987, uargs5 =  1854233143;
    uint32_t mask = 1;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 + *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 + *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vadd_i32Test, vadd_i32_2){
    acc0.initSetup(0,"testprogs/binaries/vadd_i32_2.bin", 0);
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
    uint32_t uargs0 = -525302330, uargs1 = 1447886293;
    uint32_t uargs2 = 1087045551, uargs3 =  -1296768456;
    uint32_t uargs4 = 151777863, uargs5 =  1708140637;
    uint32_t mask = 1;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 + *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 + *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vadd_i32Test, vadd_i32_3){
    acc0.initSetup(0,"testprogs/binaries/vadd_i32_3.bin", 0);
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
    uint32_t uargs0 = 1933214935, uargs1 = 1704379467;
    uint32_t uargs2 = 819823439, uargs3 =  1733597062;
    uint32_t uargs4 = -1588473664, uargs5 =  -743646012;
    uint32_t mask = 2;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 + *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 + *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vadd_i32Test, vadd_i32_4){
    acc0.initSetup(0,"testprogs/binaries/vadd_i32_4.bin", 0);
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
    uint32_t uargs0 = 1228115079, uargs1 = 428262781;
    uint32_t uargs2 = -941799282, uargs3 =  1272714150;
    uint32_t uargs4 = 1326184716, uargs5 =  -66192336;
    uint32_t mask = 2;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 + *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 + *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vadd_i32Test, vadd_i32_5){
    acc0.initSetup(0,"testprogs/binaries/vadd_i32_5.bin", 0);
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
    uint32_t uargs0 = 366758751, uargs1 = -322302572;
    uint32_t uargs2 = -1756489471, uargs3 =  102377765;
    uint32_t uargs4 = 186298393, uargs5 =  10563056;
    uint32_t mask = 2;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 + *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 + *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vadd_i32Test, vadd_i32_6){
    acc0.initSetup(0,"testprogs/binaries/vadd_i32_6.bin", 0);
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
    uint32_t uargs0 = -2083637430, uargs1 = -201342864;
    uint32_t uargs2 = 112111634, uargs3 =  -1922795841;
    uint32_t uargs4 = 934492524, uargs5 =  277833879;
    uint32_t mask = 1;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 + *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 + *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vadd_i32Test, vadd_i32_7){
    acc0.initSetup(0,"testprogs/binaries/vadd_i32_7.bin", 0);
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
    uint32_t uargs0 = -1353490520, uargs1 = 1839810103;
    uint32_t uargs2 = -2026471387, uargs3 =  -374258623;
    uint32_t uargs4 = 2019054763, uargs5 =  -1232010007;
    uint32_t mask = 2;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 + *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 + *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vadd_i32Test, vadd_i32_8){
    acc0.initSetup(0,"testprogs/binaries/vadd_i32_8.bin", 0);
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
    uint32_t uargs0 = -1303985004, uargs1 = -807087198;
    uint32_t uargs2 = 1727029444, uargs3 =  8101415;
    uint32_t uargs4 = 1594452309, uargs5 =  914506330;
    uint32_t mask = 2;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 + *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 + *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vadd_i32Test, vadd_i32_9){
    acc0.initSetup(0,"testprogs/binaries/vadd_i32_9.bin", 0);
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
    uint32_t uargs0 = 1792594899, uargs1 = -1122578537;
    uint32_t uargs2 = 1151663471, uargs3 =  480118115;
    uint32_t uargs4 = -1368260029, uargs5 =  1942853790;
    uint32_t mask = 2;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 + *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 + *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vadd_i32Test, vadd_i32_10){
    acc0.initSetup(0,"testprogs/binaries/vadd_i32_10.bin", 0);
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
    uint32_t uargs0 = -812480, uargs1 = -1191386828;
    uint32_t uargs2 = 1493101797, uargs3 =  1532241362;
    uint32_t uargs4 = 1279288252, uargs5 =  1692331301;
    uint32_t mask = 1;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 + *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 + *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vadd_i32Test, vadd_i32_11){
    acc0.initSetup(0,"testprogs/binaries/vadd_i32_11.bin", 0);
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
    uint32_t uargs0 = -1658882183, uargs1 = -667678177;
    uint32_t uargs2 = -610523344, uargs3 =  -1387398302;
    uint32_t uargs4 = 2125454447, uargs5 =  1932767472;
    uint32_t mask = 3;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 + *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 + *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vadd_i32Test, vadd_i32_12){
    acc0.initSetup(0,"testprogs/binaries/vadd_i32_12.bin", 0);
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
    uint32_t uargs0 = -2077725124, uargs1 = -1092316794;
    uint32_t uargs2 = -1012803979, uargs3 =  -1807542922;
    uint32_t uargs4 = -1712756095, uargs5 =  805061072;
    uint32_t mask = 3;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 + *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 + *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vadd_i32Test, vadd_i32_13){
    acc0.initSetup(0,"testprogs/binaries/vadd_i32_13.bin", 0);
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
    uint32_t uargs0 = -346976475, uargs1 = -602964072;
    uint32_t uargs2 = 558887297, uargs3 =  -2063955286;
    uint32_t uargs4 = -1474880581, uargs5 =  1845964750;
    uint32_t mask = 3;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 + *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 + *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vadd_i32Test, vadd_i32_14){
    acc0.initSetup(0,"testprogs/binaries/vadd_i32_14.bin", 0);
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
    uint32_t uargs0 = -380402443, uargs1 = -885882375;
    uint32_t uargs2 = -712337968, uargs3 =  598748870;
    uint32_t uargs4 = -381244368, uargs5 =  -1340602093;
    uint32_t mask = 1;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 + *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 + *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vadd_i32Test, vadd_i32_15){
    acc0.initSetup(0,"testprogs/binaries/vadd_i32_15.bin", 0);
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
    uint32_t uargs0 = -1741871690, uargs1 = -1369229259;
    uint32_t uargs2 = -1055083164, uargs3 =  -1976694493;
    uint32_t uargs4 = 1983201564, uargs5 =  1498619446;
    uint32_t mask = 1;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 + *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 + *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vadd_i32Test, vadd_i32_16){
    acc0.initSetup(0,"testprogs/binaries/vadd_i32_16.bin", 0);
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
    uint32_t uargs0 = -72590744, uargs1 = 1807723819;
    uint32_t uargs2 = 33565298, uargs3 =  -1231344304;
    uint32_t uargs4 = -1369880787, uargs5 =  -487258291;
    uint32_t mask = 1;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 + *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 + *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vadd_i32Test, vadd_i32_17){
    acc0.initSetup(0,"testprogs/binaries/vadd_i32_17.bin", 0);
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
    uint32_t uargs0 = 393049499, uargs1 = -1130131693;
    uint32_t uargs2 = -843316300, uargs3 =  1537094861;
    uint32_t uargs4 = -992356409, uargs5 =  1722887695;
    uint32_t mask = 2;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 + *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 + *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vadd_i32Test, vadd_i32_18){
    acc0.initSetup(0,"testprogs/binaries/vadd_i32_18.bin", 0);
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
    uint32_t uargs0 = -1710643128, uargs1 = -1572387352;
    uint32_t uargs2 = 847754819, uargs3 =  1658306579;
    uint32_t uargs4 = 597193602, uargs5 =  1586361263;
    uint32_t mask = 3;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 + *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 + *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vadd_i32Test, vadd_i32_19){
    acc0.initSetup(0,"testprogs/binaries/vadd_i32_19.bin", 0);
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
    uint32_t uargs0 = -654640155, uargs1 = 421334079;
    uint32_t uargs2 = -792523087, uargs3 =  -1197589407;
    uint32_t uargs4 = -1474366251, uargs5 =  767735930;
    uint32_t mask = 3;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 + *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 + *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
