#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "udaccelerator.hh"

using namespace basim;

class BNEI : public ::testing::Test {
 protected:
    UDAccelerator acc0 = UDAccelerator(1,0,1);
};
TEST_F(BNEI, edge){
    acc0.initSetup(0,"testprogs/binaries/bnei.bin", 0);
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
TEST_F(BNEI, random_0){
    acc0.initSetup(0,"testprogs/binaries/bnei_0.bin", 0);
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
TEST_F(BNEI, random_1){
    acc0.initSetup(0,"testprogs/binaries/bnei_1.bin", 0);
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
TEST_F(BNEI, random_2){
    acc0.initSetup(0,"testprogs/binaries/bnei_2.bin", 0);
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
TEST_F(BNEI, random_3){
    acc0.initSetup(0,"testprogs/binaries/bnei_3.bin", 0);
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
TEST_F(BNEI, random_4){
    acc0.initSetup(0,"testprogs/binaries/bnei_4.bin", 0);
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
TEST_F(BNEI, random_5){
    acc0.initSetup(0,"testprogs/binaries/bnei_5.bin", 0);
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
TEST_F(BNEI, random_6){
    acc0.initSetup(0,"testprogs/binaries/bnei_6.bin", 0);
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
TEST_F(BNEI, random_7){
    acc0.initSetup(0,"testprogs/binaries/bnei_7.bin", 0);
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
TEST_F(BNEI, random_8){
    acc0.initSetup(0,"testprogs/binaries/bnei_8.bin", 0);
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
TEST_F(BNEI, random_9){
    acc0.initSetup(0,"testprogs/binaries/bnei_9.bin", 0);
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
TEST_F(BNEI, random_10){
    acc0.initSetup(0,"testprogs/binaries/bnei_10.bin", 0);
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
TEST_F(BNEI, random_11){
    acc0.initSetup(0,"testprogs/binaries/bnei_11.bin", 0);
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
TEST_F(BNEI, random_12){
    acc0.initSetup(0,"testprogs/binaries/bnei_12.bin", 0);
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
TEST_F(BNEI, random_13){
    acc0.initSetup(0,"testprogs/binaries/bnei_13.bin", 0);
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
TEST_F(BNEI, random_14){
    acc0.initSetup(0,"testprogs/binaries/bnei_14.bin", 0);
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
TEST_F(BNEI, random_15){
    acc0.initSetup(0,"testprogs/binaries/bnei_15.bin", 0);
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
TEST_F(BNEI, random_16){
    acc0.initSetup(0,"testprogs/binaries/bnei_16.bin", 0);
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
TEST_F(BNEI, random_17){
    acc0.initSetup(0,"testprogs/binaries/bnei_17.bin", 0);
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
TEST_F(BNEI, random_18){
    acc0.initSetup(0,"testprogs/binaries/bnei_18.bin", 0);
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
TEST_F(BNEI, random_19){
    acc0.initSetup(0,"testprogs/binaries/bnei_19.bin", 0);
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
TEST_F(BNEI, random_20){
    acc0.initSetup(0,"testprogs/binaries/bnei_20.bin", 0);
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
TEST_F(BNEI, random_21){
    acc0.initSetup(0,"testprogs/binaries/bnei_21.bin", 0);
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
TEST_F(BNEI, random_22){
    acc0.initSetup(0,"testprogs/binaries/bnei_22.bin", 0);
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
TEST_F(BNEI, random_23){
    acc0.initSetup(0,"testprogs/binaries/bnei_23.bin", 0);
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
TEST_F(BNEI, random_24){
    acc0.initSetup(0,"testprogs/binaries/bnei_24.bin", 0);
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
TEST_F(BNEI, random_25){
    acc0.initSetup(0,"testprogs/binaries/bnei_25.bin", 0);
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
TEST_F(BNEI, random_26){
    acc0.initSetup(0,"testprogs/binaries/bnei_26.bin", 0);
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
TEST_F(BNEI, random_27){
    acc0.initSetup(0,"testprogs/binaries/bnei_27.bin", 0);
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
TEST_F(BNEI, random_28){
    acc0.initSetup(0,"testprogs/binaries/bnei_28.bin", 0);
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
TEST_F(BNEI, random_29){
    acc0.initSetup(0,"testprogs/binaries/bnei_29.bin", 0);
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
TEST_F(BNEI, random_30){
    acc0.initSetup(0,"testprogs/binaries/bnei_30.bin", 0);
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
TEST_F(BNEI, random_31){
    acc0.initSetup(0,"testprogs/binaries/bnei_31.bin", 0);
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
TEST_F(BNEI, random_32){
    acc0.initSetup(0,"testprogs/binaries/bnei_32.bin", 0);
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
TEST_F(BNEI, random_33){
    acc0.initSetup(0,"testprogs/binaries/bnei_33.bin", 0);
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
TEST_F(BNEI, random_34){
    acc0.initSetup(0,"testprogs/binaries/bnei_34.bin", 0);
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
TEST_F(BNEI, random_35){
    acc0.initSetup(0,"testprogs/binaries/bnei_35.bin", 0);
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
TEST_F(BNEI, random_36){
    acc0.initSetup(0,"testprogs/binaries/bnei_36.bin", 0);
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
TEST_F(BNEI, random_37){
    acc0.initSetup(0,"testprogs/binaries/bnei_37.bin", 0);
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
TEST_F(BNEI, random_38){
    acc0.initSetup(0,"testprogs/binaries/bnei_38.bin", 0);
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
TEST_F(BNEI, random_39){
    acc0.initSetup(0,"testprogs/binaries/bnei_39.bin", 0);
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
TEST_F(BNEI, random_40){
    acc0.initSetup(0,"testprogs/binaries/bnei_40.bin", 0);
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
TEST_F(BNEI, random_41){
    acc0.initSetup(0,"testprogs/binaries/bnei_41.bin", 0);
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
TEST_F(BNEI, random_42){
    acc0.initSetup(0,"testprogs/binaries/bnei_42.bin", 0);
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
TEST_F(BNEI, random_43){
    acc0.initSetup(0,"testprogs/binaries/bnei_43.bin", 0);
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
TEST_F(BNEI, random_44){
    acc0.initSetup(0,"testprogs/binaries/bnei_44.bin", 0);
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
TEST_F(BNEI, random_45){
    acc0.initSetup(0,"testprogs/binaries/bnei_45.bin", 0);
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
TEST_F(BNEI, random_46){
    acc0.initSetup(0,"testprogs/binaries/bnei_46.bin", 0);
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
TEST_F(BNEI, random_47){
    acc0.initSetup(0,"testprogs/binaries/bnei_47.bin", 0);
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
TEST_F(BNEI, random_48){
    acc0.initSetup(0,"testprogs/binaries/bnei_48.bin", 0);
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
TEST_F(BNEI, random_49){
    acc0.initSetup(0,"testprogs/binaries/bnei_49.bin", 0);
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
TEST_F(BNEI, random_50){
    acc0.initSetup(0,"testprogs/binaries/bnei_50.bin", 0);
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
TEST_F(BNEI, random_51){
    acc0.initSetup(0,"testprogs/binaries/bnei_51.bin", 0);
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
TEST_F(BNEI, random_52){
    acc0.initSetup(0,"testprogs/binaries/bnei_52.bin", 0);
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
TEST_F(BNEI, random_53){
    acc0.initSetup(0,"testprogs/binaries/bnei_53.bin", 0);
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
TEST_F(BNEI, random_54){
    acc0.initSetup(0,"testprogs/binaries/bnei_54.bin", 0);
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
TEST_F(BNEI, random_55){
    acc0.initSetup(0,"testprogs/binaries/bnei_55.bin", 0);
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
TEST_F(BNEI, random_56){
    acc0.initSetup(0,"testprogs/binaries/bnei_56.bin", 0);
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
TEST_F(BNEI, random_57){
    acc0.initSetup(0,"testprogs/binaries/bnei_57.bin", 0);
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
TEST_F(BNEI, random_58){
    acc0.initSetup(0,"testprogs/binaries/bnei_58.bin", 0);
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
TEST_F(BNEI, random_59){
    acc0.initSetup(0,"testprogs/binaries/bnei_59.bin", 0);
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
TEST_F(BNEI, random_60){
    acc0.initSetup(0,"testprogs/binaries/bnei_60.bin", 0);
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
TEST_F(BNEI, random_61){
    acc0.initSetup(0,"testprogs/binaries/bnei_61.bin", 0);
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
TEST_F(BNEI, random_62){
    acc0.initSetup(0,"testprogs/binaries/bnei_62.bin", 0);
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
TEST_F(BNEI, random_63){
    acc0.initSetup(0,"testprogs/binaries/bnei_63.bin", 0);
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
TEST_F(BNEI, random_64){
    acc0.initSetup(0,"testprogs/binaries/bnei_64.bin", 0);
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
TEST_F(BNEI, random_65){
    acc0.initSetup(0,"testprogs/binaries/bnei_65.bin", 0);
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
TEST_F(BNEI, random_66){
    acc0.initSetup(0,"testprogs/binaries/bnei_66.bin", 0);
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
TEST_F(BNEI, random_67){
    acc0.initSetup(0,"testprogs/binaries/bnei_67.bin", 0);
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
TEST_F(BNEI, random_68){
    acc0.initSetup(0,"testprogs/binaries/bnei_68.bin", 0);
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
TEST_F(BNEI, random_69){
    acc0.initSetup(0,"testprogs/binaries/bnei_69.bin", 0);
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
TEST_F(BNEI, random_70){
    acc0.initSetup(0,"testprogs/binaries/bnei_70.bin", 0);
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
TEST_F(BNEI, random_71){
    acc0.initSetup(0,"testprogs/binaries/bnei_71.bin", 0);
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
TEST_F(BNEI, random_72){
    acc0.initSetup(0,"testprogs/binaries/bnei_72.bin", 0);
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
TEST_F(BNEI, random_73){
    acc0.initSetup(0,"testprogs/binaries/bnei_73.bin", 0);
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
TEST_F(BNEI, random_74){
    acc0.initSetup(0,"testprogs/binaries/bnei_74.bin", 0);
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
TEST_F(BNEI, random_75){
    acc0.initSetup(0,"testprogs/binaries/bnei_75.bin", 0);
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
TEST_F(BNEI, random_76){
    acc0.initSetup(0,"testprogs/binaries/bnei_76.bin", 0);
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
TEST_F(BNEI, random_77){
    acc0.initSetup(0,"testprogs/binaries/bnei_77.bin", 0);
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
TEST_F(BNEI, random_78){
    acc0.initSetup(0,"testprogs/binaries/bnei_78.bin", 0);
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
TEST_F(BNEI, random_79){
    acc0.initSetup(0,"testprogs/binaries/bnei_79.bin", 0);
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
TEST_F(BNEI, random_80){
    acc0.initSetup(0,"testprogs/binaries/bnei_80.bin", 0);
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
TEST_F(BNEI, random_81){
    acc0.initSetup(0,"testprogs/binaries/bnei_81.bin", 0);
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
TEST_F(BNEI, random_82){
    acc0.initSetup(0,"testprogs/binaries/bnei_82.bin", 0);
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
TEST_F(BNEI, random_83){
    acc0.initSetup(0,"testprogs/binaries/bnei_83.bin", 0);
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
TEST_F(BNEI, random_84){
    acc0.initSetup(0,"testprogs/binaries/bnei_84.bin", 0);
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
TEST_F(BNEI, random_85){
    acc0.initSetup(0,"testprogs/binaries/bnei_85.bin", 0);
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
TEST_F(BNEI, random_86){
    acc0.initSetup(0,"testprogs/binaries/bnei_86.bin", 0);
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
TEST_F(BNEI, random_87){
    acc0.initSetup(0,"testprogs/binaries/bnei_87.bin", 0);
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
TEST_F(BNEI, random_88){
    acc0.initSetup(0,"testprogs/binaries/bnei_88.bin", 0);
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
TEST_F(BNEI, random_89){
    acc0.initSetup(0,"testprogs/binaries/bnei_89.bin", 0);
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
TEST_F(BNEI, random_90){
    acc0.initSetup(0,"testprogs/binaries/bnei_90.bin", 0);
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
TEST_F(BNEI, random_91){
    acc0.initSetup(0,"testprogs/binaries/bnei_91.bin", 0);
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
TEST_F(BNEI, random_92){
    acc0.initSetup(0,"testprogs/binaries/bnei_92.bin", 0);
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
TEST_F(BNEI, random_93){
    acc0.initSetup(0,"testprogs/binaries/bnei_93.bin", 0);
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
TEST_F(BNEI, random_94){
    acc0.initSetup(0,"testprogs/binaries/bnei_94.bin", 0);
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
TEST_F(BNEI, random_95){
    acc0.initSetup(0,"testprogs/binaries/bnei_95.bin", 0);
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
TEST_F(BNEI, random_96){
    acc0.initSetup(0,"testprogs/binaries/bnei_96.bin", 0);
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
TEST_F(BNEI, random_97){
    acc0.initSetup(0,"testprogs/binaries/bnei_97.bin", 0);
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
TEST_F(BNEI, random_98){
    acc0.initSetup(0,"testprogs/binaries/bnei_98.bin", 0);
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
TEST_F(BNEI, random_99){
    acc0.initSetup(0,"testprogs/binaries/bnei_99.bin", 0);
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
