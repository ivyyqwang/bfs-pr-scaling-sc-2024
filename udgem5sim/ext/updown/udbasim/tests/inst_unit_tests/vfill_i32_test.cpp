#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"
#include <cmath>
#include <cfenv>

using namespace basim;

class Vfill_i32Test : public ::testing::Test {
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
TEST_F(Vfill_i32Test, vfill_i32_0){
    acc0.initSetup(0,"testprogs/binaries/vfill_i32_0.bin", 0);
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
    uint32_t uargs0 = 583954991, uargs1 = 765755019;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    val0 = 91;
    val1 = 91;
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vfill_i32Test, vfill_i32_1){
    acc0.initSetup(0,"testprogs/binaries/vfill_i32_1.bin", 0);
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
    uint32_t uargs0 = -1509315179, uargs1 = 1132073964;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    val0 = 1577;
    val1 = 1577;
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vfill_i32Test, vfill_i32_2){
    acc0.initSetup(0,"testprogs/binaries/vfill_i32_2.bin", 0);
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
    uint32_t uargs0 = 196051757, uargs1 = -2087863053;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    val0 = 1101;
    val1 = 1101;
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vfill_i32Test, vfill_i32_3){
    acc0.initSetup(0,"testprogs/binaries/vfill_i32_3.bin", 0);
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
    uint32_t uargs0 = -813996508, uargs1 = -558057522;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    val0 = -1227;
    val1 = -1227;
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vfill_i32Test, vfill_i32_4){
    acc0.initSetup(0,"testprogs/binaries/vfill_i32_4.bin", 0);
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
    uint32_t uargs0 = 139290181, uargs1 = 1219095202;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    val0 = -207;
    val1 = -207;
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vfill_i32Test, vfill_i32_5){
    acc0.initSetup(0,"testprogs/binaries/vfill_i32_5.bin", 0);
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
    uint32_t uargs0 = -307369843, uargs1 = 2024459468;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    val0 = -687;
    val1 = -687;
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vfill_i32Test, vfill_i32_6){
    acc0.initSetup(0,"testprogs/binaries/vfill_i32_6.bin", 0);
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
    uint32_t uargs0 = 1430607954, uargs1 = 1772293412;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    val0 = -394;
    val1 = -394;
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vfill_i32Test, vfill_i32_7){
    acc0.initSetup(0,"testprogs/binaries/vfill_i32_7.bin", 0);
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
    uint32_t uargs0 = -51551250, uargs1 = 13810005;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    val0 = 549;
    val1 = 549;
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vfill_i32Test, vfill_i32_8){
    acc0.initSetup(0,"testprogs/binaries/vfill_i32_8.bin", 0);
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
    uint32_t uargs0 = 312395253, uargs1 = -1844726483;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    val0 = -517;
    val1 = -517;
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vfill_i32Test, vfill_i32_9){
    acc0.initSetup(0,"testprogs/binaries/vfill_i32_9.bin", 0);
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
    uint32_t uargs0 = -1061982246, uargs1 = -2075238738;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    val0 = -1960;
    val1 = -1960;
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vfill_i32Test, vfill_i32_10){
    acc0.initSetup(0,"testprogs/binaries/vfill_i32_10.bin", 0);
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
    uint32_t uargs0 = 1218964448, uargs1 = -2019049081;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    val0 = -727;
    val1 = -727;
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vfill_i32Test, vfill_i32_11){
    acc0.initSetup(0,"testprogs/binaries/vfill_i32_11.bin", 0);
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
    uint32_t uargs0 = -434616699, uargs1 = 1229827019;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    val0 = -1944;
    val1 = -1944;
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vfill_i32Test, vfill_i32_12){
    acc0.initSetup(0,"testprogs/binaries/vfill_i32_12.bin", 0);
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
    uint32_t uargs0 = 1521229622, uargs1 = 63305923;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    val0 = 985;
    val1 = 985;
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vfill_i32Test, vfill_i32_13){
    acc0.initSetup(0,"testprogs/binaries/vfill_i32_13.bin", 0);
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
    uint32_t uargs0 = -741932921, uargs1 = 1514492263;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    val0 = -1277;
    val1 = -1277;
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vfill_i32Test, vfill_i32_14){
    acc0.initSetup(0,"testprogs/binaries/vfill_i32_14.bin", 0);
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
    uint32_t uargs0 = -1669461610, uargs1 = 133278613;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    val0 = 1722;
    val1 = 1722;
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vfill_i32Test, vfill_i32_15){
    acc0.initSetup(0,"testprogs/binaries/vfill_i32_15.bin", 0);
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
    uint32_t uargs0 = 760806536, uargs1 = 168324685;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    val0 = 1597;
    val1 = 1597;
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vfill_i32Test, vfill_i32_16){
    acc0.initSetup(0,"testprogs/binaries/vfill_i32_16.bin", 0);
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
    uint32_t uargs0 = 752116720, uargs1 = -1545330286;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    val0 = 1120;
    val1 = 1120;
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vfill_i32Test, vfill_i32_17){
    acc0.initSetup(0,"testprogs/binaries/vfill_i32_17.bin", 0);
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
    uint32_t uargs0 = 589410534, uargs1 = -1534538851;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    val0 = 1512;
    val1 = 1512;
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vfill_i32Test, vfill_i32_18){
    acc0.initSetup(0,"testprogs/binaries/vfill_i32_18.bin", 0);
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
    uint32_t uargs0 = -1552877849, uargs1 = -174957186;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    val0 = -1357;
    val1 = -1357;
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vfill_i32Test, vfill_i32_19){
    acc0.initSetup(0,"testprogs/binaries/vfill_i32_19.bin", 0);
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
    uint32_t uargs0 = 870246973, uargs1 = 1450586902;
    int *fargs0 = reinterpret_cast<int*>(&uargs0), *fargs1 = reinterpret_cast<int*>(&uargs1);
    val0 = 681;
    val1 = 681;
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
