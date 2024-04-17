#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "udaccelerator.hh"

using namespace basim;

class BGT : public ::testing::Test {
 protected:
    UDAccelerator acc0 = UDAccelerator(1,0,1);
};
TEST_F(BGT, edge){
    acc0.initSetup(0,"testprogs/binaries/bgt.bin", 0);
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
TEST_F(BGT, random_0){
    acc0.initSetup(0,"testprogs/binaries/bgt_0.bin", 0);
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
TEST_F(BGT, random_1){
    acc0.initSetup(0,"testprogs/binaries/bgt_1.bin", 0);
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
TEST_F(BGT, random_2){
    acc0.initSetup(0,"testprogs/binaries/bgt_2.bin", 0);
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
TEST_F(BGT, random_3){
    acc0.initSetup(0,"testprogs/binaries/bgt_3.bin", 0);
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
TEST_F(BGT, random_4){
    acc0.initSetup(0,"testprogs/binaries/bgt_4.bin", 0);
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
TEST_F(BGT, random_5){
    acc0.initSetup(0,"testprogs/binaries/bgt_5.bin", 0);
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
TEST_F(BGT, random_6){
    acc0.initSetup(0,"testprogs/binaries/bgt_6.bin", 0);
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
TEST_F(BGT, random_7){
    acc0.initSetup(0,"testprogs/binaries/bgt_7.bin", 0);
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
TEST_F(BGT, random_8){
    acc0.initSetup(0,"testprogs/binaries/bgt_8.bin", 0);
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
TEST_F(BGT, random_9){
    acc0.initSetup(0,"testprogs/binaries/bgt_9.bin", 0);
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
TEST_F(BGT, random_10){
    acc0.initSetup(0,"testprogs/binaries/bgt_10.bin", 0);
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
TEST_F(BGT, random_11){
    acc0.initSetup(0,"testprogs/binaries/bgt_11.bin", 0);
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
TEST_F(BGT, random_12){
    acc0.initSetup(0,"testprogs/binaries/bgt_12.bin", 0);
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
TEST_F(BGT, random_13){
    acc0.initSetup(0,"testprogs/binaries/bgt_13.bin", 0);
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
TEST_F(BGT, random_14){
    acc0.initSetup(0,"testprogs/binaries/bgt_14.bin", 0);
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
TEST_F(BGT, random_15){
    acc0.initSetup(0,"testprogs/binaries/bgt_15.bin", 0);
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
TEST_F(BGT, random_16){
    acc0.initSetup(0,"testprogs/binaries/bgt_16.bin", 0);
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
TEST_F(BGT, random_17){
    acc0.initSetup(0,"testprogs/binaries/bgt_17.bin", 0);
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
TEST_F(BGT, random_18){
    acc0.initSetup(0,"testprogs/binaries/bgt_18.bin", 0);
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
TEST_F(BGT, random_19){
    acc0.initSetup(0,"testprogs/binaries/bgt_19.bin", 0);
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
TEST_F(BGT, random_20){
    acc0.initSetup(0,"testprogs/binaries/bgt_20.bin", 0);
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
TEST_F(BGT, random_21){
    acc0.initSetup(0,"testprogs/binaries/bgt_21.bin", 0);
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
TEST_F(BGT, random_22){
    acc0.initSetup(0,"testprogs/binaries/bgt_22.bin", 0);
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
TEST_F(BGT, random_23){
    acc0.initSetup(0,"testprogs/binaries/bgt_23.bin", 0);
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
TEST_F(BGT, random_24){
    acc0.initSetup(0,"testprogs/binaries/bgt_24.bin", 0);
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
TEST_F(BGT, random_25){
    acc0.initSetup(0,"testprogs/binaries/bgt_25.bin", 0);
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
TEST_F(BGT, random_26){
    acc0.initSetup(0,"testprogs/binaries/bgt_26.bin", 0);
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
TEST_F(BGT, random_27){
    acc0.initSetup(0,"testprogs/binaries/bgt_27.bin", 0);
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
TEST_F(BGT, random_28){
    acc0.initSetup(0,"testprogs/binaries/bgt_28.bin", 0);
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
TEST_F(BGT, random_29){
    acc0.initSetup(0,"testprogs/binaries/bgt_29.bin", 0);
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
TEST_F(BGT, random_30){
    acc0.initSetup(0,"testprogs/binaries/bgt_30.bin", 0);
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
TEST_F(BGT, random_31){
    acc0.initSetup(0,"testprogs/binaries/bgt_31.bin", 0);
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
TEST_F(BGT, random_32){
    acc0.initSetup(0,"testprogs/binaries/bgt_32.bin", 0);
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
TEST_F(BGT, random_33){
    acc0.initSetup(0,"testprogs/binaries/bgt_33.bin", 0);
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
TEST_F(BGT, random_34){
    acc0.initSetup(0,"testprogs/binaries/bgt_34.bin", 0);
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
TEST_F(BGT, random_35){
    acc0.initSetup(0,"testprogs/binaries/bgt_35.bin", 0);
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
TEST_F(BGT, random_36){
    acc0.initSetup(0,"testprogs/binaries/bgt_36.bin", 0);
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
TEST_F(BGT, random_37){
    acc0.initSetup(0,"testprogs/binaries/bgt_37.bin", 0);
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
TEST_F(BGT, random_38){
    acc0.initSetup(0,"testprogs/binaries/bgt_38.bin", 0);
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
TEST_F(BGT, random_39){
    acc0.initSetup(0,"testprogs/binaries/bgt_39.bin", 0);
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
TEST_F(BGT, random_40){
    acc0.initSetup(0,"testprogs/binaries/bgt_40.bin", 0);
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
TEST_F(BGT, random_41){
    acc0.initSetup(0,"testprogs/binaries/bgt_41.bin", 0);
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
TEST_F(BGT, random_42){
    acc0.initSetup(0,"testprogs/binaries/bgt_42.bin", 0);
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
TEST_F(BGT, random_43){
    acc0.initSetup(0,"testprogs/binaries/bgt_43.bin", 0);
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
TEST_F(BGT, random_44){
    acc0.initSetup(0,"testprogs/binaries/bgt_44.bin", 0);
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
TEST_F(BGT, random_45){
    acc0.initSetup(0,"testprogs/binaries/bgt_45.bin", 0);
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
TEST_F(BGT, random_46){
    acc0.initSetup(0,"testprogs/binaries/bgt_46.bin", 0);
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
TEST_F(BGT, random_47){
    acc0.initSetup(0,"testprogs/binaries/bgt_47.bin", 0);
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
TEST_F(BGT, random_48){
    acc0.initSetup(0,"testprogs/binaries/bgt_48.bin", 0);
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
TEST_F(BGT, random_49){
    acc0.initSetup(0,"testprogs/binaries/bgt_49.bin", 0);
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
TEST_F(BGT, random_50){
    acc0.initSetup(0,"testprogs/binaries/bgt_50.bin", 0);
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
TEST_F(BGT, random_51){
    acc0.initSetup(0,"testprogs/binaries/bgt_51.bin", 0);
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
TEST_F(BGT, random_52){
    acc0.initSetup(0,"testprogs/binaries/bgt_52.bin", 0);
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
TEST_F(BGT, random_53){
    acc0.initSetup(0,"testprogs/binaries/bgt_53.bin", 0);
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
TEST_F(BGT, random_54){
    acc0.initSetup(0,"testprogs/binaries/bgt_54.bin", 0);
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
TEST_F(BGT, random_55){
    acc0.initSetup(0,"testprogs/binaries/bgt_55.bin", 0);
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
TEST_F(BGT, random_56){
    acc0.initSetup(0,"testprogs/binaries/bgt_56.bin", 0);
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
TEST_F(BGT, random_57){
    acc0.initSetup(0,"testprogs/binaries/bgt_57.bin", 0);
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
TEST_F(BGT, random_58){
    acc0.initSetup(0,"testprogs/binaries/bgt_58.bin", 0);
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
TEST_F(BGT, random_59){
    acc0.initSetup(0,"testprogs/binaries/bgt_59.bin", 0);
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
TEST_F(BGT, random_60){
    acc0.initSetup(0,"testprogs/binaries/bgt_60.bin", 0);
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
TEST_F(BGT, random_61){
    acc0.initSetup(0,"testprogs/binaries/bgt_61.bin", 0);
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
TEST_F(BGT, random_62){
    acc0.initSetup(0,"testprogs/binaries/bgt_62.bin", 0);
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
TEST_F(BGT, random_63){
    acc0.initSetup(0,"testprogs/binaries/bgt_63.bin", 0);
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
TEST_F(BGT, random_64){
    acc0.initSetup(0,"testprogs/binaries/bgt_64.bin", 0);
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
TEST_F(BGT, random_65){
    acc0.initSetup(0,"testprogs/binaries/bgt_65.bin", 0);
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
TEST_F(BGT, random_66){
    acc0.initSetup(0,"testprogs/binaries/bgt_66.bin", 0);
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
TEST_F(BGT, random_67){
    acc0.initSetup(0,"testprogs/binaries/bgt_67.bin", 0);
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
TEST_F(BGT, random_68){
    acc0.initSetup(0,"testprogs/binaries/bgt_68.bin", 0);
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
TEST_F(BGT, random_69){
    acc0.initSetup(0,"testprogs/binaries/bgt_69.bin", 0);
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
TEST_F(BGT, random_70){
    acc0.initSetup(0,"testprogs/binaries/bgt_70.bin", 0);
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
TEST_F(BGT, random_71){
    acc0.initSetup(0,"testprogs/binaries/bgt_71.bin", 0);
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
TEST_F(BGT, random_72){
    acc0.initSetup(0,"testprogs/binaries/bgt_72.bin", 0);
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
TEST_F(BGT, random_73){
    acc0.initSetup(0,"testprogs/binaries/bgt_73.bin", 0);
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
TEST_F(BGT, random_74){
    acc0.initSetup(0,"testprogs/binaries/bgt_74.bin", 0);
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
TEST_F(BGT, random_75){
    acc0.initSetup(0,"testprogs/binaries/bgt_75.bin", 0);
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
TEST_F(BGT, random_76){
    acc0.initSetup(0,"testprogs/binaries/bgt_76.bin", 0);
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
TEST_F(BGT, random_77){
    acc0.initSetup(0,"testprogs/binaries/bgt_77.bin", 0);
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
TEST_F(BGT, random_78){
    acc0.initSetup(0,"testprogs/binaries/bgt_78.bin", 0);
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
TEST_F(BGT, random_79){
    acc0.initSetup(0,"testprogs/binaries/bgt_79.bin", 0);
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
TEST_F(BGT, random_80){
    acc0.initSetup(0,"testprogs/binaries/bgt_80.bin", 0);
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
TEST_F(BGT, random_81){
    acc0.initSetup(0,"testprogs/binaries/bgt_81.bin", 0);
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
TEST_F(BGT, random_82){
    acc0.initSetup(0,"testprogs/binaries/bgt_82.bin", 0);
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
TEST_F(BGT, random_83){
    acc0.initSetup(0,"testprogs/binaries/bgt_83.bin", 0);
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
TEST_F(BGT, random_84){
    acc0.initSetup(0,"testprogs/binaries/bgt_84.bin", 0);
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
TEST_F(BGT, random_85){
    acc0.initSetup(0,"testprogs/binaries/bgt_85.bin", 0);
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
TEST_F(BGT, random_86){
    acc0.initSetup(0,"testprogs/binaries/bgt_86.bin", 0);
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
TEST_F(BGT, random_87){
    acc0.initSetup(0,"testprogs/binaries/bgt_87.bin", 0);
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
TEST_F(BGT, random_88){
    acc0.initSetup(0,"testprogs/binaries/bgt_88.bin", 0);
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
TEST_F(BGT, random_89){
    acc0.initSetup(0,"testprogs/binaries/bgt_89.bin", 0);
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
TEST_F(BGT, random_90){
    acc0.initSetup(0,"testprogs/binaries/bgt_90.bin", 0);
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
TEST_F(BGT, random_91){
    acc0.initSetup(0,"testprogs/binaries/bgt_91.bin", 0);
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
TEST_F(BGT, random_92){
    acc0.initSetup(0,"testprogs/binaries/bgt_92.bin", 0);
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
TEST_F(BGT, random_93){
    acc0.initSetup(0,"testprogs/binaries/bgt_93.bin", 0);
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
TEST_F(BGT, random_94){
    acc0.initSetup(0,"testprogs/binaries/bgt_94.bin", 0);
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
TEST_F(BGT, random_95){
    acc0.initSetup(0,"testprogs/binaries/bgt_95.bin", 0);
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
TEST_F(BGT, random_96){
    acc0.initSetup(0,"testprogs/binaries/bgt_96.bin", 0);
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
TEST_F(BGT, random_97){
    acc0.initSetup(0,"testprogs/binaries/bgt_97.bin", 0);
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
TEST_F(BGT, random_98){
    acc0.initSetup(0,"testprogs/binaries/bgt_98.bin", 0);
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
TEST_F(BGT, random_99){
    acc0.initSetup(0,"testprogs/binaries/bgt_99.bin", 0);
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
