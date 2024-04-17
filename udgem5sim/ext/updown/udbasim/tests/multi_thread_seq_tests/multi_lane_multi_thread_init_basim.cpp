#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"

#define MAX_THREADS 127
#define MAX_LANES 64
using namespace basim;

class MultiLaneMultiThreadInitTest : public ::testing::Test {
 protected:
    uint8_t rand_num_lanes = (rand() % MAX_LANES) + 1;
    uint8_t rand_num_threads = (rand() % MAX_THREADS) + 1;
    UDAccelerator acc0;
    int buffsize1 = 1024;
    int buffsize2 = 1024;
};
TEST_F(MultiLaneMultiThreadInitTest, min_min){
    acc0 = UDAccelerator(1, 0, 0);
    acc0.initSetup(0,"testprogs/binaries/single_lane_multi_thread_init.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {5,6};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    acc0.pushEventOperands(eops, 0);
    std::cerr << "pushed operands" << std::endl;
    while(!acc0.isIdle())
        acc0.simulate(2);
    std::cerr << "while completed" << std::endl;
    EXPECT_TRUE(acc0.testMem(0, 1)); //must test al memory locations
}
TEST_F(MultiLaneMultiThreadInitTest, max_max){
    acc0 = UDAccelerator(MAX_LANES, 0, 0);
    acc0.initSetup(0,"testprogs/binaries/single_lane_multi_thread_init.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {MAX_THREADS, rand()};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    for(int i = 0; i < MAX_LANES; i++){
        acc0.pushEventOperands(eops, i);
    }
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
}
TEST_F(MultiLaneMultiThreadInitTest, rand_rand){
    acc0 = UDAccelerator(rand_num_lanes, 0, 0);
    acc0.initSetup(0,"testprogs/binaries/single_lane_multi_thread_init.bin", 0);
    uint8_t numop = 2;
    eventword_t ev0(0);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t data[] = {rand_num_threads, rand()};
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    for(int i = 0; i < rand_num_lanes; i++){
        acc0.pushEventOperands(eops, i);
    }
    while(!acc0.isIdle())
        acc0.simulate(2);
    EXPECT_TRUE(acc0.testMem(0, 1));
}
