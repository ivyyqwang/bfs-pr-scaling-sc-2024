#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "udaccelerator.hh"

using namespace basim;

class BLEIU : public ::testing::Test {
 protected:
    UDAccelerator acc0 = UDAccelerator(1,0,1);
};
TEST_F(BLEIU, edge){
    acc0.initSetup(0,"testprogs/binaries/bleiu.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
}
TEST_F(BLEIU, random_0){
    acc0.initSetup(0,"testprogs/binaries/bleiu_0.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_1){
    acc0.initSetup(0,"testprogs/binaries/bleiu_1.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_2){
    acc0.initSetup(0,"testprogs/binaries/bleiu_2.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_3){
    acc0.initSetup(0,"testprogs/binaries/bleiu_3.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_4){
    acc0.initSetup(0,"testprogs/binaries/bleiu_4.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_5){
    acc0.initSetup(0,"testprogs/binaries/bleiu_5.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_6){
    acc0.initSetup(0,"testprogs/binaries/bleiu_6.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_7){
    acc0.initSetup(0,"testprogs/binaries/bleiu_7.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_8){
    acc0.initSetup(0,"testprogs/binaries/bleiu_8.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_9){
    acc0.initSetup(0,"testprogs/binaries/bleiu_9.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_10){
    acc0.initSetup(0,"testprogs/binaries/bleiu_10.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_11){
    acc0.initSetup(0,"testprogs/binaries/bleiu_11.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_12){
    acc0.initSetup(0,"testprogs/binaries/bleiu_12.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_13){
    acc0.initSetup(0,"testprogs/binaries/bleiu_13.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_14){
    acc0.initSetup(0,"testprogs/binaries/bleiu_14.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_15){
    acc0.initSetup(0,"testprogs/binaries/bleiu_15.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_16){
    acc0.initSetup(0,"testprogs/binaries/bleiu_16.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_17){
    acc0.initSetup(0,"testprogs/binaries/bleiu_17.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_18){
    acc0.initSetup(0,"testprogs/binaries/bleiu_18.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_19){
    acc0.initSetup(0,"testprogs/binaries/bleiu_19.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_20){
    acc0.initSetup(0,"testprogs/binaries/bleiu_20.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_21){
    acc0.initSetup(0,"testprogs/binaries/bleiu_21.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_22){
    acc0.initSetup(0,"testprogs/binaries/bleiu_22.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_23){
    acc0.initSetup(0,"testprogs/binaries/bleiu_23.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_24){
    acc0.initSetup(0,"testprogs/binaries/bleiu_24.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_25){
    acc0.initSetup(0,"testprogs/binaries/bleiu_25.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_26){
    acc0.initSetup(0,"testprogs/binaries/bleiu_26.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_27){
    acc0.initSetup(0,"testprogs/binaries/bleiu_27.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_28){
    acc0.initSetup(0,"testprogs/binaries/bleiu_28.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_29){
    acc0.initSetup(0,"testprogs/binaries/bleiu_29.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_30){
    acc0.initSetup(0,"testprogs/binaries/bleiu_30.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_31){
    acc0.initSetup(0,"testprogs/binaries/bleiu_31.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_32){
    acc0.initSetup(0,"testprogs/binaries/bleiu_32.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_33){
    acc0.initSetup(0,"testprogs/binaries/bleiu_33.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_34){
    acc0.initSetup(0,"testprogs/binaries/bleiu_34.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_35){
    acc0.initSetup(0,"testprogs/binaries/bleiu_35.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_36){
    acc0.initSetup(0,"testprogs/binaries/bleiu_36.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_37){
    acc0.initSetup(0,"testprogs/binaries/bleiu_37.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_38){
    acc0.initSetup(0,"testprogs/binaries/bleiu_38.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_39){
    acc0.initSetup(0,"testprogs/binaries/bleiu_39.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_40){
    acc0.initSetup(0,"testprogs/binaries/bleiu_40.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_41){
    acc0.initSetup(0,"testprogs/binaries/bleiu_41.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_42){
    acc0.initSetup(0,"testprogs/binaries/bleiu_42.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_43){
    acc0.initSetup(0,"testprogs/binaries/bleiu_43.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_44){
    acc0.initSetup(0,"testprogs/binaries/bleiu_44.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_45){
    acc0.initSetup(0,"testprogs/binaries/bleiu_45.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_46){
    acc0.initSetup(0,"testprogs/binaries/bleiu_46.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_47){
    acc0.initSetup(0,"testprogs/binaries/bleiu_47.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_48){
    acc0.initSetup(0,"testprogs/binaries/bleiu_48.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_49){
    acc0.initSetup(0,"testprogs/binaries/bleiu_49.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_50){
    acc0.initSetup(0,"testprogs/binaries/bleiu_50.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_51){
    acc0.initSetup(0,"testprogs/binaries/bleiu_51.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_52){
    acc0.initSetup(0,"testprogs/binaries/bleiu_52.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_53){
    acc0.initSetup(0,"testprogs/binaries/bleiu_53.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_54){
    acc0.initSetup(0,"testprogs/binaries/bleiu_54.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_55){
    acc0.initSetup(0,"testprogs/binaries/bleiu_55.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_56){
    acc0.initSetup(0,"testprogs/binaries/bleiu_56.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_57){
    acc0.initSetup(0,"testprogs/binaries/bleiu_57.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_58){
    acc0.initSetup(0,"testprogs/binaries/bleiu_58.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_59){
    acc0.initSetup(0,"testprogs/binaries/bleiu_59.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_60){
    acc0.initSetup(0,"testprogs/binaries/bleiu_60.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_61){
    acc0.initSetup(0,"testprogs/binaries/bleiu_61.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_62){
    acc0.initSetup(0,"testprogs/binaries/bleiu_62.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_63){
    acc0.initSetup(0,"testprogs/binaries/bleiu_63.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_64){
    acc0.initSetup(0,"testprogs/binaries/bleiu_64.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_65){
    acc0.initSetup(0,"testprogs/binaries/bleiu_65.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_66){
    acc0.initSetup(0,"testprogs/binaries/bleiu_66.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_67){
    acc0.initSetup(0,"testprogs/binaries/bleiu_67.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_68){
    acc0.initSetup(0,"testprogs/binaries/bleiu_68.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_69){
    acc0.initSetup(0,"testprogs/binaries/bleiu_69.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_70){
    acc0.initSetup(0,"testprogs/binaries/bleiu_70.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_71){
    acc0.initSetup(0,"testprogs/binaries/bleiu_71.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_72){
    acc0.initSetup(0,"testprogs/binaries/bleiu_72.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_73){
    acc0.initSetup(0,"testprogs/binaries/bleiu_73.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_74){
    acc0.initSetup(0,"testprogs/binaries/bleiu_74.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_75){
    acc0.initSetup(0,"testprogs/binaries/bleiu_75.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_76){
    acc0.initSetup(0,"testprogs/binaries/bleiu_76.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_77){
    acc0.initSetup(0,"testprogs/binaries/bleiu_77.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_78){
    acc0.initSetup(0,"testprogs/binaries/bleiu_78.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_79){
    acc0.initSetup(0,"testprogs/binaries/bleiu_79.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_80){
    acc0.initSetup(0,"testprogs/binaries/bleiu_80.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_81){
    acc0.initSetup(0,"testprogs/binaries/bleiu_81.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_82){
    acc0.initSetup(0,"testprogs/binaries/bleiu_82.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_83){
    acc0.initSetup(0,"testprogs/binaries/bleiu_83.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_84){
    acc0.initSetup(0,"testprogs/binaries/bleiu_84.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_85){
    acc0.initSetup(0,"testprogs/binaries/bleiu_85.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_86){
    acc0.initSetup(0,"testprogs/binaries/bleiu_86.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_87){
    acc0.initSetup(0,"testprogs/binaries/bleiu_87.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_88){
    acc0.initSetup(0,"testprogs/binaries/bleiu_88.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_89){
    acc0.initSetup(0,"testprogs/binaries/bleiu_89.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_90){
    acc0.initSetup(0,"testprogs/binaries/bleiu_90.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_91){
    acc0.initSetup(0,"testprogs/binaries/bleiu_91.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_92){
    acc0.initSetup(0,"testprogs/binaries/bleiu_92.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_93){
    acc0.initSetup(0,"testprogs/binaries/bleiu_93.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_94){
    acc0.initSetup(0,"testprogs/binaries/bleiu_94.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_95){
    acc0.initSetup(0,"testprogs/binaries/bleiu_95.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_96){
    acc0.initSetup(0,"testprogs/binaries/bleiu_96.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_97){
    acc0.initSetup(0,"testprogs/binaries/bleiu_97.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_98){
    acc0.initSetup(0,"testprogs/binaries/bleiu_98.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
TEST_F(BLEIU, random_99){
    acc0.initSetup(0,"testprogs/binaries/bleiu_99.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 1));
}
