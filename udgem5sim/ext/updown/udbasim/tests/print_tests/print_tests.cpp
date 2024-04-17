#include <gtest/gtest.h>
#include "lanetypes.hh"
#include "basim.hh"
#include "udlane.hh"
#include "types.hh"
#include "udaccelerator.hh"


using namespace basim;

class ShtTest : public ::testing::Test {
 protected:
    void SetUp() override {
        m.NumLanes = 1;
        m.NumNodes = 1;
        m.NumUDs = 1;
        m.NumStacks = 1;
        m.LocalMemAddrMode = 1;
        sim = BASim(m);
    }

    // void TearDown() override {}
    BASim sim;
    machine_t m;
    int numlanes = 1;
};

/** Testing small instruction memory program parsing opcodes*/
TEST_F(ShtTest, Init)
{
    sim.initMachine("tests/print_tests/print_test.bin", 0);
}

TEST_F(ShtTest, Empty){
    sim.initMachine("tests/print_tests/print_test.bin", 0);
    sim.initMemoryArrays();
    
    // Setup initial events
    word_t* memdata = new word_t[numlanes];
    printf("Addr of memdata:%lx\n", (uint64_t)memdata);
    for(int i = 0; i < numlanes; i++){
        operands_t op0(2);
        op0.setDataWord(0, reinterpret_cast<uint64_t>(&memdata[i]));
        op0.setDataWord(1, i);
        eventword_t ev = EventWord(0);
        ev.setNumOperands(2);
        ev.setThreadID(0xFF);
        ev.setNWIDbits(i);
        eventoperands_t eops(&ev, &op0);
        networkid_t nwid = NetworkID(i);
        sim.pushEventOperands(nwid, eops);
    }

    // Launch simulation
    sim.simulate();
    bool status;
    // Check if all lanes are done
    uint64_t* val = new uint64_t[numlanes];
    while(1){
        status = true;
        for(int i = 0; i < numlanes; i++){
            sim.ud2t_memcpy(&val[i], 8, NetworkID(i), 0);
            status = status && ((val[i] == 1) || (val[i] == 2));
        }
        if(status)
            break;
    }
    printf("Total Sim Cycles :%ld\n", sim.getCurTick());
    for(int i = 0; i < numlanes; i++)
        EXPECT_EQ(val[i], 1);
}
