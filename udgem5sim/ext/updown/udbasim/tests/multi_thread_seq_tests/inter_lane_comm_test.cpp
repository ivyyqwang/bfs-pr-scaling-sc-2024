#include "types.hh"
#include "udaccelerator.hh"
#include <gtest/gtest.h>

using namespace basim;

class INTER_LANE_COMM : public ::testing::Test {
protected:
  UDAccelerator acc0 = UDAccelerator(64, 0, 0);
};
TEST_F(INTER_LANE_COMM, random_0) {
  acc0.initSetup(0, "testprogs/binaries/inter_lane_comm.bin", 0);
  uint8_t numop = 2;
  eventword_t ev0(0);
  ev0.setNumOperands(numop);
  operands_t op0(numop);
  word_t op_data[] = {1, rand()};
  op0.setData(op_data);
  eventoperands_t eops(&ev0, &op0);
  acc0.pushEventOperands(eops, 0);

  while (!acc0.isIdle())
    acc0.simulate(2);

  EXPECT_TRUE(acc0.testMem(0, 1));
}
