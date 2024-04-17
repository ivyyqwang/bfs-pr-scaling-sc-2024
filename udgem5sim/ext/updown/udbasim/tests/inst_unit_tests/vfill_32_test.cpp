#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"
#include <cmath>
#include <cfenv>

using namespace basim;

class Vfill_32Test : public ::testing::Test {
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
TEST_F(Vfill_32Test, vfill_32_0){
    acc0.initSetup(0,"testprogs/binaries/vfill_32_0.bin", 0);
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
    float val0, val1;
    uint32_t uargs0 = 1565702867, uargs1 = 2642733823;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    val0 = 11.125;
    val1 = 11.125;
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vfill_32Test, vfill_32_1){
    acc0.initSetup(0,"testprogs/binaries/vfill_32_1.bin", 0);
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
    float val0, val1;
    uint32_t uargs0 = 1711590823, uargs1 = 2303798007;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    val0 = 17.0;
    val1 = 17.0;
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vfill_32Test, vfill_32_2){
    acc0.initSetup(0,"testprogs/binaries/vfill_32_2.bin", 0);
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
    float val0, val1;
    uint32_t uargs0 = 306291336, uargs1 = 919946631;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    val0 = 1.0;
    val1 = 1.0;
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vfill_32Test, vfill_32_3){
    acc0.initSetup(0,"testprogs/binaries/vfill_32_3.bin", 0);
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
    float val0, val1;
    uint32_t uargs0 = 1013273745, uargs1 = 70568928;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    val0 = 5.125;
    val1 = 5.125;
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vfill_32Test, vfill_32_4){
    acc0.initSetup(0,"testprogs/binaries/vfill_32_4.bin", 0);
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
    float val0, val1;
    uint32_t uargs0 = 1480452789, uargs1 = 2733514078;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    val0 = 3.0;
    val1 = 3.0;
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vfill_32Test, vfill_32_5){
    acc0.initSetup(0,"testprogs/binaries/vfill_32_5.bin", 0);
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
    float val0, val1;
    uint32_t uargs0 = 2257503075, uargs1 = 966675900;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    val0 = 3.625;
    val1 = 3.625;
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vfill_32Test, vfill_32_6){
    acc0.initSetup(0,"testprogs/binaries/vfill_32_6.bin", 0);
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
    float val0, val1;
    uint32_t uargs0 = 3731336443, uargs1 = 818786302;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    val0 = 7.5;
    val1 = 7.5;
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vfill_32Test, vfill_32_7){
    acc0.initSetup(0,"testprogs/binaries/vfill_32_7.bin", 0);
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
    float val0, val1;
    uint32_t uargs0 = 369353339, uargs1 = 2762823462;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    val0 = 18.25;
    val1 = 18.25;
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vfill_32Test, vfill_32_8){
    acc0.initSetup(0,"testprogs/binaries/vfill_32_8.bin", 0);
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
    float val0, val1;
    uint32_t uargs0 = 1108230515, uargs1 = 2137135870;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    val0 = 10.125;
    val1 = 10.125;
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vfill_32Test, vfill_32_9){
    acc0.initSetup(0,"testprogs/binaries/vfill_32_9.bin", 0);
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
    float val0, val1;
    uint32_t uargs0 = 3863604163, uargs1 = 360163172;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    val0 = 6.0;
    val1 = 6.0;
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vfill_32Test, vfill_32_10){
    acc0.initSetup(0,"testprogs/binaries/vfill_32_10.bin", 0);
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
    float val0, val1;
    uint32_t uargs0 = 4265289686, uargs1 = 1926011396;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    val0 = 9.75;
    val1 = 9.75;
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vfill_32Test, vfill_32_11){
    acc0.initSetup(0,"testprogs/binaries/vfill_32_11.bin", 0);
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
    float val0, val1;
    uint32_t uargs0 = 3868558673, uargs1 = 750741387;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    val0 = 18.75;
    val1 = 18.75;
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vfill_32Test, vfill_32_12){
    acc0.initSetup(0,"testprogs/binaries/vfill_32_12.bin", 0);
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
    float val0, val1;
    uint32_t uargs0 = 2674360802, uargs1 = 87086433;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    val0 = 16.875;
    val1 = 16.875;
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vfill_32Test, vfill_32_13){
    acc0.initSetup(0,"testprogs/binaries/vfill_32_13.bin", 0);
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
    float val0, val1;
    uint32_t uargs0 = 2349903843, uargs1 = 3118781100;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    val0 = 1.25;
    val1 = 1.25;
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vfill_32Test, vfill_32_14){
    acc0.initSetup(0,"testprogs/binaries/vfill_32_14.bin", 0);
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
    float val0, val1;
    uint32_t uargs0 = 901642536, uargs1 = 2168010250;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    val0 = 11.5;
    val1 = 11.5;
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vfill_32Test, vfill_32_15){
    acc0.initSetup(0,"testprogs/binaries/vfill_32_15.bin", 0);
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
    float val0, val1;
    uint32_t uargs0 = 2319071057, uargs1 = 2776159665;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    val0 = 8.625;
    val1 = 8.625;
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vfill_32Test, vfill_32_16){
    acc0.initSetup(0,"testprogs/binaries/vfill_32_16.bin", 0);
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
    float val0, val1;
    uint32_t uargs0 = 1423994010, uargs1 = 2748368242;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    val0 = 8.5;
    val1 = 8.5;
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vfill_32Test, vfill_32_17){
    acc0.initSetup(0,"testprogs/binaries/vfill_32_17.bin", 0);
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
    float val0, val1;
    uint32_t uargs0 = 2785954516, uargs1 = 3789560874;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    val0 = 17.25;
    val1 = 17.25;
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vfill_32Test, vfill_32_18){
    acc0.initSetup(0,"testprogs/binaries/vfill_32_18.bin", 0);
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
    float val0, val1;
    uint32_t uargs0 = 4247469575, uargs1 = 1566395620;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    val0 = 7.75;
    val1 = 7.75;
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
TEST_F(Vfill_32Test, vfill_32_19){
    acc0.initSetup(0,"testprogs/binaries/vfill_32_19.bin", 0);
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
    float val0, val1;
    uint32_t uargs0 = 744429472, uargs1 = 2421718708;
    float *fargs0 = reinterpret_cast<float*>(&uargs0), *fargs1 = reinterpret_cast<float*>(&uargs1);
    val0 = 0.375;
    val1 = 0.375;
    uint32_t *w0 = reinterpret_cast<uint32_t*>(&val0), *w1 = reinterpret_cast<uint32_t*>(&val1);
    uint64_t final_result = (uint64_t)(*w0) | ((uint64_t)(*w1) << 32);
    EXPECT_TRUE(acc0.testReg(0, RegId::X18, final_result));
}
