#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"
#include <cmath>
#include <cfenv>

using namespace basim;

class Vmadd_i32Test : public ::testing::Test {
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
TEST_F(Vmadd_i32Test, vmadd_i32_0){
    acc0.initSetup(0,"testprogs/binaries/vmadd_i32_0.bin", 0);
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
    uint32_t uargs0 = 1191455968, uargs1 = -2059870110;
    uint32_t uargs2 = -751109851, uargs3 =  -597158378;
    uint32_t uargs4 = -1647620021, uargs5 =  -706930427;
    uint32_t mask = 2;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 * *fargs2 + *fargs4) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs3 + *fargs5) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vmadd_i32Test, vmadd_i32_1){
    acc0.initSetup(0,"testprogs/binaries/vmadd_i32_1.bin", 0);
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
    uint32_t uargs0 = -150823105, uargs1 = 1357675734;
    uint32_t uargs2 = 434339847, uargs3 =  116603383;
    uint32_t uargs4 = 1288621512, uargs5 =  -1451022360;
    uint32_t mask = 1;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 * *fargs2 + *fargs4) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs3 + *fargs5) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vmadd_i32Test, vmadd_i32_2){
    acc0.initSetup(0,"testprogs/binaries/vmadd_i32_2.bin", 0);
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
    uint32_t uargs0 = 1668426359, uargs1 = 939055907;
    uint32_t uargs2 = 549215846, uargs3 =  1176037576;
    uint32_t uargs4 = 1343542591, uargs5 =  -1693978085;
    uint32_t mask = 2;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 * *fargs2 + *fargs4) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs3 + *fargs5) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vmadd_i32Test, vmadd_i32_3){
    acc0.initSetup(0,"testprogs/binaries/vmadd_i32_3.bin", 0);
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
    uint32_t uargs0 = 1297119785, uargs1 = 270538364;
    uint32_t uargs2 = 1891224189, uargs3 =  279727915;
    uint32_t uargs4 = -1798999230, uargs5 =  -2098459871;
    uint32_t mask = 3;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 * *fargs2 + *fargs4) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs3 + *fargs5) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vmadd_i32Test, vmadd_i32_4){
    acc0.initSetup(0,"testprogs/binaries/vmadd_i32_4.bin", 0);
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
    uint32_t uargs0 = -2117965706, uargs1 = 543248404;
    uint32_t uargs2 = -1495366623, uargs3 =  1564779903;
    uint32_t uargs4 = 1066695117, uargs5 =  -1716437678;
    uint32_t mask = 2;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 * *fargs2 + *fargs4) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs3 + *fargs5) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vmadd_i32Test, vmadd_i32_5){
    acc0.initSetup(0,"testprogs/binaries/vmadd_i32_5.bin", 0);
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
    uint32_t uargs0 = -2091636057, uargs1 = -897258954;
    uint32_t uargs2 = -396706989, uargs3 =  -1407434160;
    uint32_t uargs4 = -1870358870, uargs5 =  -781980520;
    uint32_t mask = 1;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 * *fargs2 + *fargs4) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs3 + *fargs5) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vmadd_i32Test, vmadd_i32_6){
    acc0.initSetup(0,"testprogs/binaries/vmadd_i32_6.bin", 0);
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
    uint32_t uargs0 = -1716976343, uargs1 = -1271828293;
    uint32_t uargs2 = 2066073710, uargs3 =  1076899923;
    uint32_t uargs4 = -1058807944, uargs5 =  1907295907;
    uint32_t mask = 2;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 * *fargs2 + *fargs4) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs3 + *fargs5) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vmadd_i32Test, vmadd_i32_7){
    acc0.initSetup(0,"testprogs/binaries/vmadd_i32_7.bin", 0);
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
    uint32_t uargs0 = 661509936, uargs1 = 417440737;
    uint32_t uargs2 = 1698356781, uargs3 =  -1111317007;
    uint32_t uargs4 = 978407305, uargs5 =  -1859966709;
    uint32_t mask = 2;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 * *fargs2 + *fargs4) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs3 + *fargs5) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vmadd_i32Test, vmadd_i32_8){
    acc0.initSetup(0,"testprogs/binaries/vmadd_i32_8.bin", 0);
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
    uint32_t uargs0 = -2118125001, uargs1 = -191766896;
    uint32_t uargs2 = 35653066, uargs3 =  -1981093698;
    uint32_t uargs4 = -1742717422, uargs5 =  694006447;
    uint32_t mask = 3;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 * *fargs2 + *fargs4) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs3 + *fargs5) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vmadd_i32Test, vmadd_i32_9){
    acc0.initSetup(0,"testprogs/binaries/vmadd_i32_9.bin", 0);
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
    uint32_t uargs0 = -565253194, uargs1 = -1028984853;
    uint32_t uargs2 = -289649549, uargs3 =  -1535953424;
    uint32_t uargs4 = -984151595, uargs5 =  -972799009;
    uint32_t mask = 2;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 * *fargs2 + *fargs4) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs3 + *fargs5) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vmadd_i32Test, vmadd_i32_10){
    acc0.initSetup(0,"testprogs/binaries/vmadd_i32_10.bin", 0);
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
    uint32_t uargs0 = -999539467, uargs1 = -1011159616;
    uint32_t uargs2 = 1828465045, uargs3 =  1718204362;
    uint32_t uargs4 = -1011085364, uargs5 =  1553170549;
    uint32_t mask = 1;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 * *fargs2 + *fargs4) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs3 + *fargs5) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vmadd_i32Test, vmadd_i32_11){
    acc0.initSetup(0,"testprogs/binaries/vmadd_i32_11.bin", 0);
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
    uint32_t uargs0 = 1425047658, uargs1 = 863482901;
    uint32_t uargs2 = -159837666, uargs3 =  -1200244339;
    uint32_t uargs4 = 1042794903, uargs5 =  380933526;
    uint32_t mask = 3;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 * *fargs2 + *fargs4) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs3 + *fargs5) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vmadd_i32Test, vmadd_i32_12){
    acc0.initSetup(0,"testprogs/binaries/vmadd_i32_12.bin", 0);
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
    uint32_t uargs0 = -1845671312, uargs1 = -1304434475;
    uint32_t uargs2 = -985123706, uargs3 =  -2119303286;
    uint32_t uargs4 = 1207571645, uargs5 =  1425834265;
    uint32_t mask = 1;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 * *fargs2 + *fargs4) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs3 + *fargs5) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vmadd_i32Test, vmadd_i32_13){
    acc0.initSetup(0,"testprogs/binaries/vmadd_i32_13.bin", 0);
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
    uint32_t uargs0 = -897208398, uargs1 = -1449530936;
    uint32_t uargs2 = 653372728, uargs3 =  1407292118;
    uint32_t uargs4 = -716013400, uargs5 =  1181503187;
    uint32_t mask = 2;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 * *fargs2 + *fargs4) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs3 + *fargs5) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vmadd_i32Test, vmadd_i32_14){
    acc0.initSetup(0,"testprogs/binaries/vmadd_i32_14.bin", 0);
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
    uint32_t uargs0 = -66223945, uargs1 = 414279879;
    uint32_t uargs2 = 627189419, uargs3 =  311795974;
    uint32_t uargs4 = 622186218, uargs5 =  -1210528229;
    uint32_t mask = 1;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 * *fargs2 + *fargs4) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs3 + *fargs5) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vmadd_i32Test, vmadd_i32_15){
    acc0.initSetup(0,"testprogs/binaries/vmadd_i32_15.bin", 0);
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
    uint32_t uargs0 = -1236934667, uargs1 = 1231180508;
    uint32_t uargs2 = 196688324, uargs3 =  524030853;
    uint32_t uargs4 = 1386986534, uargs5 =  1512330810;
    uint32_t mask = 3;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 * *fargs2 + *fargs4) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs3 + *fargs5) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vmadd_i32Test, vmadd_i32_16){
    acc0.initSetup(0,"testprogs/binaries/vmadd_i32_16.bin", 0);
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
    uint32_t uargs0 = -1065666335, uargs1 = -321833715;
    uint32_t uargs2 = 13537402, uargs3 =  155954126;
    uint32_t uargs4 = -1737924915, uargs5 =  -2120802863;
    uint32_t mask = 3;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 * *fargs2 + *fargs4) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs3 + *fargs5) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vmadd_i32Test, vmadd_i32_17){
    acc0.initSetup(0,"testprogs/binaries/vmadd_i32_17.bin", 0);
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
    uint32_t uargs0 = -1550215692, uargs1 = 1020522794;
    uint32_t uargs2 = -1000769241, uargs3 =  384070253;
    uint32_t uargs4 = 153303153, uargs5 =  -303862889;
    uint32_t mask = 3;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 * *fargs2 + *fargs4) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs3 + *fargs5) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vmadd_i32Test, vmadd_i32_18){
    acc0.initSetup(0,"testprogs/binaries/vmadd_i32_18.bin", 0);
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
    uint32_t uargs0 = -1453716947, uargs1 = 264476760;
    uint32_t uargs2 = 1702836976, uargs3 =  1656614420;
    uint32_t uargs4 = 1186806221, uargs5 =  1754226450;
    uint32_t mask = 1;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 * *fargs2 + *fargs4) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs3 + *fargs5) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vmadd_i32Test, vmadd_i32_19){
    acc0.initSetup(0,"testprogs/binaries/vmadd_i32_19.bin", 0);
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
    uint32_t uargs0 = 571558794, uargs1 = -1324881531;
    uint32_t uargs2 = -722175535, uargs3 =  -433621600;
    uint32_t uargs4 = 462365490, uargs5 =  2062796823;
    uint32_t mask = 2;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    int *fargs2 = reinterpret_cast<int*>(&uargs2), *fargs3 = reinterpret_cast<int*>(&uargs3);
    int *fargs4 = reinterpret_cast<int*>(&uargs4), *fargs5 = reinterpret_cast<int*>(&uargs5);
    val0 = (mask & 1) ? (*fargs0 * *fargs2 + *fargs4) : (*fargs4);
    val1 = (mask >> 1 & 1) ? (*fargs1 * *fargs3 + *fargs5) : (*fargs5);
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
