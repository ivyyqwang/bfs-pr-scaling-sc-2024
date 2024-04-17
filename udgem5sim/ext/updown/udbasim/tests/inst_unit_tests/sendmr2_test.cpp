

#include <gtest/gtest.h>
#include "basim.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"
#include <iostream>
#include <cstdlib>

using namespace basim;

class Sendmr2 : public ::testing::Test {
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
            
            printf("Sendmr2 test is waiting...\n");
            if(status) break;
        }
        printf(".................Successfuly exit wait!.............\n");
    }
    BASim sim;
    machine_t m;
    int numlanes = 2;
    
};


TEST_F(Sendmr2, sendmr2_cw_ret0_lane1_nops2_store0){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendmr2_cw_ret0_lane1_nops2_store.bin", 0);
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
    data[0] = 24536;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 24664;
    data[3] =15825318323280093343u;
    data[4] =13925060750718246864u;
    data[5] =9931904013174375000u;
    data[6] =8769213828155483850u;
    data[7] =15686881355349988431u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 8);
    EXPECT_EQ(memdata[0][0], 24536u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 16);
    EXPECT_EQ(memdata[0][1], (word_t) memdata[0]);
     
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
    
TEST_F(Sendmr2, sendmr2_cw_ret0_lane2_nops2_store1){
    numlanes = 2;
    m.NumLanes = 2;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendmr2_cw_ret0_lane2_nops2_store.bin", 0);
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
    data[0] = 1176;
    data[1] = reinterpret_cast<uint64_t>(&memdata[1][0]);
    data[2] = 1304;
    data[3] =16257844663807656211u;
    data[4] =17832043743133789356u;
    data[5] =777393899038110659u;
    data[6] =13984041706282103076u;
    data[7] =4403907773217428485u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 8);
    EXPECT_EQ(memdata[1][0], 1176u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 16);
    EXPECT_EQ(memdata[1][1], (word_t) memdata[1]);
     
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
    
    