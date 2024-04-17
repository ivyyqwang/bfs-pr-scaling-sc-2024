

#include <gtest/gtest.h>
#include "basim.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"
#include <iostream>
#include <cstdlib>

using namespace basim;

class Sendr : public ::testing::Test {
 protected:
    void SetUp() override {
        m.NumLanes = numlanes;
        m.NumNodes = 1;
        m.NumUDs = 1;
        m.NumStacks = 1;
        m.LocalMemAddrMode = 1;
        sim = BASim(m);
    }
    void testWait(BASim& sim,int nwid){
        bool status;
        while(1){
            status = true;

            uint64_t val;
            sim.ud2t_memcpy(&val, 8, NetworkID(nwid), 0);
            status = status && (val == 1);
            
            printf("Sendr test is waiting...\n");
            if(status) break;
        }
        printf(".................Successfuly exit wait!.............\n");
    }
    BASim sim;
    machine_t m;
    int numlanes = 2;
    
};


TEST_F(Sendr, sendr_cw_ret0_lane1_nops20){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendr_cw_ret0_lane1_nops2.bin", 0);
    sim.initMemoryArrays();
    word_t** memdata = new word_t*[numlanes];
    for(int i = 0; i < numlanes; i++){
        memdata[i] = new word_t[32];
        for(int j = 0; j < 32; j++){
            memdata[i][j] = (word_t) rand() % 100;
        }
    }
    int numops = 8;
    eventword_t ev(0);
    ev.setNumOperands(numops);
    ev.setThreadID(0xFF);
    ev.setNWIDbits(0);
    operands_t ops(numops);
    word_t* data = new word_t[numops];
    // set data based on the instruction
    data[0] = 16768;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 16896;
    data[3] =18264127906448742773u;
    data[4] =10272934915651745814u;
    data[5] =16941586331166822465u;
    data[6] =13404440023448722613u;
    data[7] =14085646437863366844u;
    
    ops.setData(data);
    for(int j = 0; j < numops; j++){
        printf("data[%d] = %ld\n", j, (long)data[j]);
        }
    eventoperands_t evops(&ev, &ops);
    networkid_t nwid = NetworkID(0);
    sim.pushEventOperands(nwid, evops);
    sim.simulate();
    printf("\n After simulation.................\n");
    
    word_t val;
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 16776);
    EXPECT_EQ(val, 16768u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 16784);
    EXPECT_EQ(val, (word_t) memdata[0]);
     
    printf("numlanes: %d\n", numlanes);
    printf("memdata[0] = %lu\n", (uint64_t)memdata[0]);
    for(int i = 0; i < numlanes; i++){
        for(int j = 0; j < 8; j++){
            word_t val;
            sim.ud2t_memcpy(&val, 8, NetworkID(i), 8 * (j+1));
            printf("nwid: %d, j = %d, val:  %lu\n", i,j, val);
        }
        for(int j = 0; j < 32; j++){
            printf("memdata[%d][%d] = %lu, @ %lu\n", i, j, memdata[i][j], (uint64_t)&memdata[i][j]);
            }
        }
    
}
    
TEST_F(Sendr, sendr_cw_ret0_lane2_nops21){
    numlanes = 2;
    m.NumLanes = 2;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendr_cw_ret0_lane2_nops2.bin", 0);
    sim.initMemoryArrays();
    word_t** memdata = new word_t*[numlanes];
    for(int i = 0; i < numlanes; i++){
        memdata[i] = new word_t[32];
        for(int j = 0; j < 32; j++){
            memdata[i][j] = (word_t) rand() % 100;
        }
    }
    int numops = 8;
    eventword_t ev(0);
    ev.setNumOperands(numops);
    ev.setThreadID(0xFF);
    ev.setNWIDbits(0);
    operands_t ops(numops);
    word_t* data = new word_t[numops];
    // set data based on the instruction
    data[0] = 15792;
    data[1] = reinterpret_cast<uint64_t>(&memdata[1][0]);
    data[2] = 15920;
    data[3] =18430413259573701215u;
    data[4] =1367425297644465174u;
    data[5] =5271820245558423672u;
    data[6] =14970113209661315491u;
    data[7] =838568088486027171u;
    
    ops.setData(data);
    for(int j = 0; j < numops; j++){
        printf("data[%d] = %ld\n", j, (long)data[j]);
        }
    eventoperands_t evops(&ev, &ops);
    networkid_t nwid = NetworkID(0);
    sim.pushEventOperands(nwid, evops);
    sim.simulate();
    printf("\n After simulation.................\n");
    
    word_t val;
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 15800);
    EXPECT_EQ(val, 15792u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 15808);
    EXPECT_EQ(val, (word_t) memdata[1]);
     
    printf("numlanes: %d\n", numlanes);
    printf("memdata[0] = %lu\n", (uint64_t)memdata[0]);
    for(int i = 0; i < numlanes; i++){
        for(int j = 0; j < 8; j++){
            word_t val;
            sim.ud2t_memcpy(&val, 8, NetworkID(i), 8 * (j+1));
            printf("nwid: %d, j = %d, val:  %lu\n", i,j, val);
        }
        for(int j = 0; j < 32; j++){
            printf("memdata[%d][%d] = %lu, @ %lu\n", i, j, memdata[i][j], (uint64_t)&memdata[i][j]);
            }
        }
    
}
    
    