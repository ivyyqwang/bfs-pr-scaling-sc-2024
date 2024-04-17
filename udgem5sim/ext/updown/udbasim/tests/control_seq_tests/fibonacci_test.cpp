#include "types.hh"
#include "udaccelerator.hh"
#include <gtest/gtest.h>
#define N_MAX 46
using namespace basim;

//assembly model
uint32_t fib(uint32_t n, uint32_t *memo, uint32_t *memo_size){
	if(n < *memo_size){
		return memo[n];
	}

	memo[n] = fib(n-1,memo,memo_size)+fib(n-2,memo,memo_size);
	*memo_size += 1;
	printf("memo[%d]=%d\n",n,memo[n]);
	return memo[n];
}

uint32_t fibonacci(uint32_t n){
	uint32_t memo[n];
	uint32_t memo_size = 2;
	memo[0] = 0;
	memo[1] = 1;

	return fib(n,memo,&memo_size);
}

class FIBONACCI : public ::testing::Test {
protected:
  UDAccelerator acc0 = UDAccelerator(1, 0, 1);
};
TEST_F(FIBONACCI, random_0){
  srand((unsigned)time(NULL));
  int n = rand() % N_MAX;

  acc0.initSetup(0, "testprogs/binaries/fibonacci.bin", 0);
  uint8_t numop = 2;
  eventword_t ev0(0);
  ev0.setNumOperands(numop);
  operands_t op0(numop);
  word_t op_data[] = {n,fibonacci(n)};
  op0.setData(op_data);
  eventoperands_t eops(&ev0, &op0);
  acc0.pushEventOperands(eops, 0);

  while (!acc0.isIdle())
    acc0.simulate(2);

  EXPECT_TRUE(acc0.testMem(0, 1));
}
