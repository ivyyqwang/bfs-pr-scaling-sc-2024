#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"

using namespace basim;

class epsilonTX : public ::testing::Test {
 protected:
    size_t num_threads = 1;
    int numLanes = 1;
    UDAccelerator acc0 = UDAccelerator(numLanes, 0, 1); // UDAccelerator(numLanes, UDID/networkID, lmmode (0: accelerator based addressing, 1:bank/lane based addressing))
};
TEST_F(epsilonTX, epsilonTX_0){
    acc0.initSetup(0, "testprogs/binaries/epsilon_tx_0.bin", 0); //(_pgbase,progfile,_lmbase)
    
    int numop = 2;
    eventword_t ev0(0);
    ev0.setEventLabel(64);      //TODO: make sure this is based on the generated binary (this relies on the program)
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t *data = new word_t[numop];
    data[0] = reinterpret_cast<word_t>((uint64_t)0);
    data[1] = reinterpret_cast<word_t>((uint64_t)8);
    
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num tick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){

        //word_t sbp = acc0.readReg(i, RegId::X7) + data[0]; 
        EXPECT_TRUE(acc0.testReg(i, RegId::X17, 2));     //X17 = 2 in the last common tx
    }
}
