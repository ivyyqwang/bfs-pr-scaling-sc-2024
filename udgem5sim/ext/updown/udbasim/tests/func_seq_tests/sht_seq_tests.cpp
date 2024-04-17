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
        m.NumLanes = 64;
        m.NumNodes = 1;
        m.NumUDs = 4;
        m.NumStacks = 8;
        m.LocalMemAddrMode = 1;
        sim = BASim(m);
    }

    // void TearDown() override {}
    BASim sim;
    machine_t m;
    int numlanes = 2;
};

/** Testing small instruction memory program parsing opcodes*/
TEST_F(ShtTest, Init)
{
    sim.initMachine("tests/func_seq_tests/sht_concurrency_test_out.bin", 0);
    // sim.initMachine("tests/func_seq_tests/sht_empty_test_out.bin", 0);
}

TEST_F(ShtTest, Empty){
    // sim.initMachine("tests/func_seq_tests/sht_concurrency_test_out.bin", 0);
    sim.initMachine("tests/func_seq_tests/sht_empty_test_out.bin", 0);
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

TEST_F(ShtTest, Concurency){
    sim.initMachine("tests/func_seq_tests/sht_concurrency_test_out.bin", 0);
    // sim.initMachine("tests/func_seq_tests/sht_empty_test_out.bin", 0);
    sim.initMemoryArrays();
    
    // // Setup initial events
    // word_t* memdata = new word_t[numlanes];
    // printf("Addr of memdata:%lx\n", (uint64_t)memdata);
    // for(int i = 0; i < numlanes; i++){
    //     operands_t op0(2);
    //     op0.setDataWord(0, reinterpret_cast<uint64_t>(&memdata[i]));
    //     op0.setDataWord(1, i);
    //     eventword_t ev = EventWord(0);
    //     ev.setNumOperands(2);
    //     ev.setThreadID(0xFF);
    //     ev.setNWIDbits(i);
    //     eventoperands_t eops(&ev, &op0);
    //     networkid_t nwid = NetworkID(i);
    //     sim.pushEventOperands(nwid, eops);
    // }

    // // Launch simulation
    // sim.simulate();
    // bool status;
    // // Check if all lanes are done
    // uint64_t* val = new uint64_t[numlanes];
    // while(1){
    //     status = true;
    //     for(int i = 0; i < numlanes; i++){
    //         sim.ud2t_memcpy(&val[i], 8, NetworkID(i), 0);
    //         status = status && ((val[i] == 1) || (val[i] == 2));
    //     }
    //     if(status)
    //         break;
    // }
    // printf("Total Sim Cycles :%ld\n", sim.getCurTick());
    // for(int i = 0; i < numlanes; i++)
    //     EXPECT_EQ(val[i], 1);
    
    // Setup initial events
    word_t lm_start_off = 8;
    word_t sht_desc_size = 40;
    word_t bucket_desc_lm_start_off = lm_start_off + sht_desc_size + 64;
    word_t entry_size = 16;
    word_t alloc_entries_per_bucket = 64;
    word_t num_lanes = 4;
    word_t num_buckets_per_lane = 4;
    uint32_t size = num_lanes * num_buckets_per_lane * entry_size * alloc_entries_per_bucket;
    word_t* memdata = new word_t[size];
    printf("Addr of memdata:%lx\n", (uint64_t)memdata);

    operands_t op0(8);
    // op0.setDataWord(0, reinterpret_cast<uint64_t>(&memdata[0]));
    op0.setDataWord(0, lm_start_off); // sht desc lm addr
    op0.setDataWord(1, lm_start_off + sht_desc_size); // LM buf addr
    op0.setDataWord(2, 0); // X10 - START_NWID
    op0.setDataWord(3, num_lanes); // X11 - NUM_ALLOC_LANES
    op0.setDataWord(4, bucket_desc_lm_start_off); // X12 - BUCKET_DESC_LM_OFFSET
    op0.setDataWord(5, reinterpret_cast<uint64_t>(&memdata[0])); // X13 - DRAM_ALLOC_ADDR
    op0.setDataWord(6, num_buckets_per_lane); // X14 - BUCKETS_PER_LANE
    op0.setDataWord(7, alloc_entries_per_bucket); // X15 - ENTRIES_PER_BUCKET
    eventword_t ev = EventWord(0);
    ev.setNumOperands(8);
    ev.setThreadID(0xFF);
    ev.setNWIDbits(0);
    eventoperands_t eops(&ev, &op0);
    networkid_t nwid = NetworkID(0);
    sim.pushEventOperands(nwid, eops);

    // Launch simulation
    printf("!!!!!!!!!!!!!!!!\n");

    sim.simulate();
    printf("!!!!!!!!!!!!!!!!\n");

    bool status;
    // Check if all lanes are done
    uint64_t* val = new uint64_t[1];
    while(1){
        status = true;
        sim.ud2t_memcpy(&val[0], 8, NetworkID(0), 0);
        status = status && ((val[0] == 1) || (val[0] == 2));
        if(status)
            break;
    }
    printf("Total Sim Cycles :%ld\n", sim.getCurTick());
    for(int i = 0; i < 1; i++)
        EXPECT_EQ(val[i], 1);
}
