#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"
#include <cmath>
#include <cfenv>

using namespace basim;

class Vsub_i32Test : public ::testing::Test {
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
TEST_F(Vsub_i32Test, vsub_i32_0){
    acc0.initSetup(0,"testprogs/binaries/vsub_i32_0.bin", 0);
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
    uint32_t uargs0 = 1604023720, uargs1 = -967998004;
    uint32_t uargs2 = 1855881651, uargs3 =  -857807051;
    uint32_t uargs4 = -1897837029, uargs5 =  2007134524;
    uint32_t mask = 3;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 - *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 - *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vsub_i32Test, vsub_i32_1){
    acc0.initSetup(0,"testprogs/binaries/vsub_i32_1.bin", 0);
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
    uint32_t uargs0 = -1107476011, uargs1 = -2008227949;
    uint32_t uargs2 = 119951098, uargs3 =  1040439511;
    uint32_t uargs4 = 932781671, uargs5 =  1815650024;
    uint32_t mask = 2;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 - *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 - *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vsub_i32Test, vsub_i32_2){
    acc0.initSetup(0,"testprogs/binaries/vsub_i32_2.bin", 0);
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
    uint32_t uargs0 = -251999869, uargs1 = 1266099915;
    uint32_t uargs2 = 1918475832, uargs3 =  1421200006;
    uint32_t uargs4 = -39935960, uargs5 =  -234006943;
    uint32_t mask = 2;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 - *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 - *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vsub_i32Test, vsub_i32_3){
    acc0.initSetup(0,"testprogs/binaries/vsub_i32_3.bin", 0);
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
    uint32_t uargs0 = -461537480, uargs1 = 1252895133;
    uint32_t uargs2 = -1860646853, uargs3 =  814926936;
    uint32_t uargs4 = 954758763, uargs5 =  1090752008;
    uint32_t mask = 3;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 - *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 - *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vsub_i32Test, vsub_i32_4){
    acc0.initSetup(0,"testprogs/binaries/vsub_i32_4.bin", 0);
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
    uint32_t uargs0 = 272638916, uargs1 = 1640223374;
    uint32_t uargs2 = 1489757051, uargs3 =  -1764232923;
    uint32_t uargs4 = 636230959, uargs5 =  -435466042;
    uint32_t mask = 2;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 - *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 - *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vsub_i32Test, vsub_i32_5){
    acc0.initSetup(0,"testprogs/binaries/vsub_i32_5.bin", 0);
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
    uint32_t uargs0 = 1425570473, uargs1 = 1602927403;
    uint32_t uargs2 = -1502645533, uargs3 =  2025027051;
    uint32_t uargs4 = 1591668918, uargs5 =  1652015884;
    uint32_t mask = 1;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 - *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 - *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vsub_i32Test, vsub_i32_6){
    acc0.initSetup(0,"testprogs/binaries/vsub_i32_6.bin", 0);
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
    uint32_t uargs0 = -890955351, uargs1 = -428664861;
    uint32_t uargs2 = 1147991785, uargs3 =  1857670951;
    uint32_t uargs4 = -1578869895, uargs5 =  -1056120190;
    uint32_t mask = 3;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 - *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 - *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vsub_i32Test, vsub_i32_7){
    acc0.initSetup(0,"testprogs/binaries/vsub_i32_7.bin", 0);
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
    uint32_t uargs0 = -1578888369, uargs1 = 1147200166;
    uint32_t uargs2 = 647912644, uargs3 =  -640484049;
    uint32_t uargs4 = -1626383270, uargs5 =  -1993044569;
    uint32_t mask = 1;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 - *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 - *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vsub_i32Test, vsub_i32_8){
    acc0.initSetup(0,"testprogs/binaries/vsub_i32_8.bin", 0);
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
    uint32_t uargs0 = 409298367, uargs1 = -279256003;
    uint32_t uargs2 = 655449188, uargs3 =  1878977416;
    uint32_t uargs4 = -50414131, uargs5 =  -182545464;
    uint32_t mask = 1;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 - *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 - *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vsub_i32Test, vsub_i32_9){
    acc0.initSetup(0,"testprogs/binaries/vsub_i32_9.bin", 0);
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
    uint32_t uargs0 = -740968432, uargs1 = -1221865274;
    uint32_t uargs2 = 1568249350, uargs3 =  30059485;
    uint32_t uargs4 = 1941926884, uargs5 =  -982633832;
    uint32_t mask = 2;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 - *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 - *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vsub_i32Test, vsub_i32_10){
    acc0.initSetup(0,"testprogs/binaries/vsub_i32_10.bin", 0);
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
    uint32_t uargs0 = 1672846298, uargs1 = 1646897767;
    uint32_t uargs2 = 475548224, uargs3 =  832979269;
    uint32_t uargs4 = -1873226700, uargs5 =  -312014533;
    uint32_t mask = 2;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 - *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 - *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vsub_i32Test, vsub_i32_11){
    acc0.initSetup(0,"testprogs/binaries/vsub_i32_11.bin", 0);
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
    uint32_t uargs0 = 773516147, uargs1 = 578805909;
    uint32_t uargs2 = 1982046137, uargs3 =  -186957658;
    uint32_t uargs4 = -1632219566, uargs5 =  1275558262;
    uint32_t mask = 3;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 - *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 - *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vsub_i32Test, vsub_i32_12){
    acc0.initSetup(0,"testprogs/binaries/vsub_i32_12.bin", 0);
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
    uint32_t uargs0 = -1642248355, uargs1 = 592952002;
    uint32_t uargs2 = -1657221922, uargs3 =  -1097327535;
    uint32_t uargs4 = -950994735, uargs5 =  -1476967088;
    uint32_t mask = 3;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 - *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 - *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vsub_i32Test, vsub_i32_13){
    acc0.initSetup(0,"testprogs/binaries/vsub_i32_13.bin", 0);
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
    uint32_t uargs0 = -1542341561, uargs1 = -552071410;
    uint32_t uargs2 = 2022524390, uargs3 =  1538087855;
    uint32_t uargs4 = -1038377260, uargs5 =  -1982557967;
    uint32_t mask = 1;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 - *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 - *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vsub_i32Test, vsub_i32_14){
    acc0.initSetup(0,"testprogs/binaries/vsub_i32_14.bin", 0);
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
    uint32_t uargs0 = 1432173559, uargs1 = -1957241182;
    uint32_t uargs2 = 468574579, uargs3 =  1137513127;
    uint32_t uargs4 = 1420242853, uargs5 =  32275894;
    uint32_t mask = 1;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 - *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 - *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vsub_i32Test, vsub_i32_15){
    acc0.initSetup(0,"testprogs/binaries/vsub_i32_15.bin", 0);
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
    uint32_t uargs0 = 593372278, uargs1 = 182727313;
    uint32_t uargs2 = 357252211, uargs3 =  1152719596;
    uint32_t uargs4 = -73708617, uargs5 =  1732177741;
    uint32_t mask = 2;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 - *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 - *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vsub_i32Test, vsub_i32_16){
    acc0.initSetup(0,"testprogs/binaries/vsub_i32_16.bin", 0);
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
    uint32_t uargs0 = 1960255889, uargs1 = -113014623;
    uint32_t uargs2 = -393466249, uargs3 =  1596018423;
    uint32_t uargs4 = -2019904788, uargs5 =  -1649226634;
    uint32_t mask = 3;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 - *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 - *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vsub_i32Test, vsub_i32_17){
    acc0.initSetup(0,"testprogs/binaries/vsub_i32_17.bin", 0);
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
    uint32_t uargs0 = -1834896757, uargs1 = -804529303;
    uint32_t uargs2 = -1028858637, uargs3 =  -642121475;
    uint32_t uargs4 = 761681432, uargs5 =  -157078865;
    uint32_t mask = 2;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 - *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 - *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vsub_i32Test, vsub_i32_18){
    acc0.initSetup(0,"testprogs/binaries/vsub_i32_18.bin", 0);
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
    uint32_t uargs0 = 987451111, uargs1 = 663972141;
    uint32_t uargs2 = 1742863180, uargs3 =  -1117268093;
    uint32_t uargs4 = -901615396, uargs5 =  -1515373045;
    uint32_t mask = 3;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 - *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 - *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vsub_i32Test, vsub_i32_19){
    acc0.initSetup(0,"testprogs/binaries/vsub_i32_19.bin", 0);
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
    uint32_t uargs0 = 2118637555, uargs1 = 117451525;
    uint32_t uargs2 = 1956648545, uargs3 =  -790878909;
    uint32_t uargs4 = 1325223, uargs5 =  -970141282;
    uint32_t mask = 1;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 - *fargs2) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 - *fargs3) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
