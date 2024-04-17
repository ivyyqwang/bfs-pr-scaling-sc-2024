#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "udaccelerator.hh"

using namespace basim;

class CEQI : public ::testing::Test {
 protected:
    UDAccelerator acc0 = UDAccelerator(1,0,1);
};
TEST_F(CEQI, edge){
    acc0.initSetup(0,"testprogs/binaries/ceqi.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
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
TEST_F(CEQI, random_0){
    acc0.initSetup(0,"testprogs/binaries/ceqi_0.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_1){
    acc0.initSetup(0,"testprogs/binaries/ceqi_1.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_2){
    acc0.initSetup(0,"testprogs/binaries/ceqi_2.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_3){
    acc0.initSetup(0,"testprogs/binaries/ceqi_3.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_4){
    acc0.initSetup(0,"testprogs/binaries/ceqi_4.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_5){
    acc0.initSetup(0,"testprogs/binaries/ceqi_5.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_6){
    acc0.initSetup(0,"testprogs/binaries/ceqi_6.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_7){
    acc0.initSetup(0,"testprogs/binaries/ceqi_7.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_8){
    acc0.initSetup(0,"testprogs/binaries/ceqi_8.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_9){
    acc0.initSetup(0,"testprogs/binaries/ceqi_9.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_10){
    acc0.initSetup(0,"testprogs/binaries/ceqi_10.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_11){
    acc0.initSetup(0,"testprogs/binaries/ceqi_11.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_12){
    acc0.initSetup(0,"testprogs/binaries/ceqi_12.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_13){
    acc0.initSetup(0,"testprogs/binaries/ceqi_13.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_14){
    acc0.initSetup(0,"testprogs/binaries/ceqi_14.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_15){
    acc0.initSetup(0,"testprogs/binaries/ceqi_15.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_16){
    acc0.initSetup(0,"testprogs/binaries/ceqi_16.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_17){
    acc0.initSetup(0,"testprogs/binaries/ceqi_17.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_18){
    acc0.initSetup(0,"testprogs/binaries/ceqi_18.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_19){
    acc0.initSetup(0,"testprogs/binaries/ceqi_19.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_20){
    acc0.initSetup(0,"testprogs/binaries/ceqi_20.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_21){
    acc0.initSetup(0,"testprogs/binaries/ceqi_21.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_22){
    acc0.initSetup(0,"testprogs/binaries/ceqi_22.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_23){
    acc0.initSetup(0,"testprogs/binaries/ceqi_23.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_24){
    acc0.initSetup(0,"testprogs/binaries/ceqi_24.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_25){
    acc0.initSetup(0,"testprogs/binaries/ceqi_25.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_26){
    acc0.initSetup(0,"testprogs/binaries/ceqi_26.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_27){
    acc0.initSetup(0,"testprogs/binaries/ceqi_27.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_28){
    acc0.initSetup(0,"testprogs/binaries/ceqi_28.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_29){
    acc0.initSetup(0,"testprogs/binaries/ceqi_29.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_30){
    acc0.initSetup(0,"testprogs/binaries/ceqi_30.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_31){
    acc0.initSetup(0,"testprogs/binaries/ceqi_31.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_32){
    acc0.initSetup(0,"testprogs/binaries/ceqi_32.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_33){
    acc0.initSetup(0,"testprogs/binaries/ceqi_33.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_34){
    acc0.initSetup(0,"testprogs/binaries/ceqi_34.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_35){
    acc0.initSetup(0,"testprogs/binaries/ceqi_35.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_36){
    acc0.initSetup(0,"testprogs/binaries/ceqi_36.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_37){
    acc0.initSetup(0,"testprogs/binaries/ceqi_37.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_38){
    acc0.initSetup(0,"testprogs/binaries/ceqi_38.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_39){
    acc0.initSetup(0,"testprogs/binaries/ceqi_39.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_40){
    acc0.initSetup(0,"testprogs/binaries/ceqi_40.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_41){
    acc0.initSetup(0,"testprogs/binaries/ceqi_41.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_42){
    acc0.initSetup(0,"testprogs/binaries/ceqi_42.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_43){
    acc0.initSetup(0,"testprogs/binaries/ceqi_43.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_44){
    acc0.initSetup(0,"testprogs/binaries/ceqi_44.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_45){
    acc0.initSetup(0,"testprogs/binaries/ceqi_45.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_46){
    acc0.initSetup(0,"testprogs/binaries/ceqi_46.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_47){
    acc0.initSetup(0,"testprogs/binaries/ceqi_47.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_48){
    acc0.initSetup(0,"testprogs/binaries/ceqi_48.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_49){
    acc0.initSetup(0,"testprogs/binaries/ceqi_49.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_50){
    acc0.initSetup(0,"testprogs/binaries/ceqi_50.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_51){
    acc0.initSetup(0,"testprogs/binaries/ceqi_51.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_52){
    acc0.initSetup(0,"testprogs/binaries/ceqi_52.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_53){
    acc0.initSetup(0,"testprogs/binaries/ceqi_53.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_54){
    acc0.initSetup(0,"testprogs/binaries/ceqi_54.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_55){
    acc0.initSetup(0,"testprogs/binaries/ceqi_55.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_56){
    acc0.initSetup(0,"testprogs/binaries/ceqi_56.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_57){
    acc0.initSetup(0,"testprogs/binaries/ceqi_57.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_58){
    acc0.initSetup(0,"testprogs/binaries/ceqi_58.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_59){
    acc0.initSetup(0,"testprogs/binaries/ceqi_59.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_60){
    acc0.initSetup(0,"testprogs/binaries/ceqi_60.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_61){
    acc0.initSetup(0,"testprogs/binaries/ceqi_61.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_62){
    acc0.initSetup(0,"testprogs/binaries/ceqi_62.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_63){
    acc0.initSetup(0,"testprogs/binaries/ceqi_63.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_64){
    acc0.initSetup(0,"testprogs/binaries/ceqi_64.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_65){
    acc0.initSetup(0,"testprogs/binaries/ceqi_65.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_66){
    acc0.initSetup(0,"testprogs/binaries/ceqi_66.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_67){
    acc0.initSetup(0,"testprogs/binaries/ceqi_67.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_68){
    acc0.initSetup(0,"testprogs/binaries/ceqi_68.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_69){
    acc0.initSetup(0,"testprogs/binaries/ceqi_69.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_70){
    acc0.initSetup(0,"testprogs/binaries/ceqi_70.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_71){
    acc0.initSetup(0,"testprogs/binaries/ceqi_71.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_72){
    acc0.initSetup(0,"testprogs/binaries/ceqi_72.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_73){
    acc0.initSetup(0,"testprogs/binaries/ceqi_73.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_74){
    acc0.initSetup(0,"testprogs/binaries/ceqi_74.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_75){
    acc0.initSetup(0,"testprogs/binaries/ceqi_75.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_76){
    acc0.initSetup(0,"testprogs/binaries/ceqi_76.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_77){
    acc0.initSetup(0,"testprogs/binaries/ceqi_77.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_78){
    acc0.initSetup(0,"testprogs/binaries/ceqi_78.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_79){
    acc0.initSetup(0,"testprogs/binaries/ceqi_79.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_80){
    acc0.initSetup(0,"testprogs/binaries/ceqi_80.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_81){
    acc0.initSetup(0,"testprogs/binaries/ceqi_81.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_82){
    acc0.initSetup(0,"testprogs/binaries/ceqi_82.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_83){
    acc0.initSetup(0,"testprogs/binaries/ceqi_83.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_84){
    acc0.initSetup(0,"testprogs/binaries/ceqi_84.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_85){
    acc0.initSetup(0,"testprogs/binaries/ceqi_85.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_86){
    acc0.initSetup(0,"testprogs/binaries/ceqi_86.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_87){
    acc0.initSetup(0,"testprogs/binaries/ceqi_87.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_88){
    acc0.initSetup(0,"testprogs/binaries/ceqi_88.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_89){
    acc0.initSetup(0,"testprogs/binaries/ceqi_89.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_90){
    acc0.initSetup(0,"testprogs/binaries/ceqi_90.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_91){
    acc0.initSetup(0,"testprogs/binaries/ceqi_91.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_92){
    acc0.initSetup(0,"testprogs/binaries/ceqi_92.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_93){
    acc0.initSetup(0,"testprogs/binaries/ceqi_93.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_94){
    acc0.initSetup(0,"testprogs/binaries/ceqi_94.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_95){
    acc0.initSetup(0,"testprogs/binaries/ceqi_95.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_96){
    acc0.initSetup(0,"testprogs/binaries/ceqi_96.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_97){
    acc0.initSetup(0,"testprogs/binaries/ceqi_97.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_98){
    acc0.initSetup(0,"testprogs/binaries/ceqi_98.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
TEST_F(CEQI, random_99){
    acc0.initSetup(0,"testprogs/binaries/ceqi_99.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {8,0};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
    EXPECT_TRUE(acc0.testMem(8, 0));
}
