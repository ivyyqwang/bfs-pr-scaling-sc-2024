

#include <gtest/gtest.h>
#include "basim.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"
#include <iostream>
#include <cstdlib>

using namespace basim;

class Sendm : public ::testing::Test {
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
            
            printf("Sendm test is waiting...\n");
            if(status) break;
        }
        printf(".................Successfuly exit wait!.............\n");
    }
    BASim sim;
    machine_t m;
    int numlanes = 2;
    
};


TEST_F(Sendm, sendm_cw_ret0_lane1_nops1_load0){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendm_cw_ret0_lane1_nops1_load.bin", 0);
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
    data[0] = 29384;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 29512;
    data[3] =11928860821730209988u;
    data[4] =15567436101703807079u;
    data[5] =14786454844823665284u;
    data[6] =10845272494667641160u;
    data[7] =5509987354887724086u;
    
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
    EXPECT_EQ(val, memdata[0][0]);
     
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
    
TEST_F(Sendm, sendm_cw_ret0_lane2_nops1_load1){
    numlanes = 2;
    m.NumLanes = 2;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendm_cw_ret0_lane2_nops1_load.bin", 0);
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
    data[0] = 11872;
    data[1] = reinterpret_cast<uint64_t>(&memdata[1][0]);
    data[2] = 12000;
    data[3] =14063757622994346392u;
    data[4] =443875083496946365u;
    data[5] =7857121762431067138u;
    data[6] =9017019731877214332u;
    data[7] =2163870658700866315u;
    
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
    EXPECT_EQ(val, memdata[1][0]);
     
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
    
TEST_F(Sendm, sendm_cw_ret0_lane1_nops1_store0){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendm_cw_ret0_lane1_nops1_store.bin", 0);
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
    data[0] = 10328;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 10456;
    data[3] =14833390581586716751u;
    data[4] =11333765058059741673u;
    data[5] =17801496920709811308u;
    data[6] =7066258368195232023u;
    data[7] =2418655531543354835u;
    
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
    EXPECT_EQ(memdata[0][0], data[0]);
     
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
    
TEST_F(Sendm, sendm_cw_ret0_lane2_nops1_store1){
    numlanes = 2;
    m.NumLanes = 2;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendm_cw_ret0_lane2_nops1_store.bin", 0);
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
    data[0] = 12528;
    data[1] = reinterpret_cast<uint64_t>(&memdata[1][0]);
    data[2] = 12656;
    data[3] =10521975707629259677u;
    data[4] =14729501829198200703u;
    data[5] =15089806422701070313u;
    data[6] =11134506721559208079u;
    data[7] =14027500330281195743u;
    
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
    EXPECT_EQ(memdata[1][0], data[0]);
     
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
    
TEST_F(Sendm, sendm_cl_ret0_lane1_nops1_load0){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendm_cl_ret0_lane1_nops1_load.bin", 0);
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
    data[0] = 23072;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 23200;
    data[3] =9742938339293107747u;
    data[4] =8774897168954506029u;
    data[5] =2549638478965951923u;
    data[6] =12778101752595622842u;
    data[7] =9211471908540096192u;
    
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
    EXPECT_EQ(val, memdata[0][0]);
     
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
    
TEST_F(Sendm, sendm_cl_ret0_lane1_nops1_store0){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendm_cl_ret0_lane1_nops1_store.bin", 0);
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
    data[0] = 30144;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 30272;
    data[3] =9474554737372432613u;
    data[4] =13859919632669511118u;
    data[5] =9727349452599226559u;
    data[6] =363640689829526279u;
    data[7] =1195123059552042135u;
    
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
    EXPECT_EQ(memdata[0][0], data[0]);
     
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
    
TEST_F(Sendm, sendm_cw_ret0_lane1_nops2_load0){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendm_cw_ret0_lane1_nops2_load.bin", 0);
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
    data[0] = 30432;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 30560;
    data[3] =15396872010734907919u;
    data[4] =18262165909662520894u;
    data[5] =9177097086310549889u;
    data[6] =11357634001321645525u;
    data[7] =7462736691478962009u;
    
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
    EXPECT_EQ(val, memdata[0][0]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 16);
    EXPECT_EQ(val, memdata[0][1]);
     
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
    
TEST_F(Sendm, sendm_cw_ret0_lane2_nops2_load1){
    numlanes = 2;
    m.NumLanes = 2;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendm_cw_ret0_lane2_nops2_load.bin", 0);
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
    data[0] = 32496;
    data[1] = reinterpret_cast<uint64_t>(&memdata[1][0]);
    data[2] = 32624;
    data[3] =4707177973201255854u;
    data[4] =12260761706086950853u;
    data[5] =15766656660757757546u;
    data[6] =9184621562985649754u;
    data[7] =9543829104822971613u;
    
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
    EXPECT_EQ(val, memdata[1][0]);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 16);
    EXPECT_EQ(val, memdata[1][1]);
     
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
    
TEST_F(Sendm, sendm_cw_ret0_lane1_nops2_store0){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendm_cw_ret0_lane1_nops2_store.bin", 0);
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
    data[0] = 3896;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 4024;
    data[3] =15000121695983961891u;
    data[4] =18439858807992895530u;
    data[5] =2870828432347719022u;
    data[6] =5673336059015354568u;
    data[7] =3140233503821249716u;
    
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
    EXPECT_EQ(memdata[0][0], data[0]);
    EXPECT_EQ(memdata[0][1], data[1]);
     
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
    
TEST_F(Sendm, sendm_cw_ret0_lane2_nops2_store1){
    numlanes = 2;
    m.NumLanes = 2;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendm_cw_ret0_lane2_nops2_store.bin", 0);
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
    data[0] = 20096;
    data[1] = reinterpret_cast<uint64_t>(&memdata[1][0]);
    data[2] = 20224;
    data[3] =6697497467262334830u;
    data[4] =1076604729192077360u;
    data[5] =16702148640884442373u;
    data[6] =9850340803015195961u;
    data[7] =9268758360653658929u;
    
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
    EXPECT_EQ(memdata[1][0], data[0]);
    EXPECT_EQ(memdata[1][1], data[1]);
     
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
    
TEST_F(Sendm, sendm_cl_ret0_lane1_nops2_load0){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendm_cl_ret0_lane1_nops2_load.bin", 0);
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
    data[0] = 29464;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 29592;
    data[3] =17552379127905300052u;
    data[4] =5673078093260811712u;
    data[5] =17107468912200561298u;
    data[6] =3935244287365493911u;
    data[7] =3274697255214398330u;
    
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
    EXPECT_EQ(val, memdata[0][0]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 16);
    EXPECT_EQ(val, memdata[0][1]);
     
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
    
TEST_F(Sendm, sendm_cl_ret0_lane1_nops2_store0){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendm_cl_ret0_lane1_nops2_store.bin", 0);
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
    data[0] = 1456;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 1584;
    data[3] =608486600093760115u;
    data[4] =18244387763931278257u;
    data[5] =12254468752424472972u;
    data[6] =3587317159298338939u;
    data[7] =14016280576051707215u;
    
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
    EXPECT_EQ(memdata[0][0], data[0]);
    EXPECT_EQ(memdata[0][1], data[1]);
     
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
    
TEST_F(Sendm, sendm_cw_ret0_lane1_nops3_load0){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendm_cw_ret0_lane1_nops3_load.bin", 0);
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
    data[0] = 18632;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 18760;
    data[3] =6326910997167722067u;
    data[4] =11907106787660983249u;
    data[5] =9000758882240836270u;
    data[6] =15406346837042631951u;
    data[7] =4431220926665179857u;
    
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
    EXPECT_EQ(val, memdata[0][0]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 16);
    EXPECT_EQ(val, memdata[0][1]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 24);
    EXPECT_EQ(val, memdata[0][2]);
     
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
    
TEST_F(Sendm, sendm_cw_ret0_lane2_nops3_load1){
    numlanes = 2;
    m.NumLanes = 2;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendm_cw_ret0_lane2_nops3_load.bin", 0);
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
    data[0] = 12096;
    data[1] = reinterpret_cast<uint64_t>(&memdata[1][0]);
    data[2] = 12224;
    data[3] =1635107366797051109u;
    data[4] =5856073467921082882u;
    data[5] =14736044071915624266u;
    data[6] =13046944757537653227u;
    data[7] =8444690425361819651u;
    
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
    EXPECT_EQ(val, memdata[1][0]);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 16);
    EXPECT_EQ(val, memdata[1][1]);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 24);
    EXPECT_EQ(val, memdata[1][2]);
     
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
    
TEST_F(Sendm, sendm_cw_ret0_lane1_nops3_store0){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendm_cw_ret0_lane1_nops3_store.bin", 0);
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
    data[0] = 3816;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 3944;
    data[3] =6889083152730138810u;
    data[4] =13883526334044733223u;
    data[5] =2275605676718175136u;
    data[6] =7998755823206739873u;
    data[7] =7616961064098592304u;
    
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
    EXPECT_EQ(memdata[0][0], data[0]);
    EXPECT_EQ(memdata[0][1], data[1]);
    EXPECT_EQ(memdata[0][2], data[2]);
     
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
    
TEST_F(Sendm, sendm_cw_ret0_lane2_nops3_store1){
    numlanes = 2;
    m.NumLanes = 2;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendm_cw_ret0_lane2_nops3_store.bin", 0);
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
    data[0] = 19808;
    data[1] = reinterpret_cast<uint64_t>(&memdata[1][0]);
    data[2] = 19936;
    data[3] =4150984969799401361u;
    data[4] =811263022111639042u;
    data[5] =131346431660824092u;
    data[6] =8685092940327779527u;
    data[7] =15660918194516082732u;
    
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
    EXPECT_EQ(memdata[1][0], data[0]);
    EXPECT_EQ(memdata[1][1], data[1]);
    EXPECT_EQ(memdata[1][2], data[2]);
     
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
    
TEST_F(Sendm, sendm_cl_ret0_lane1_nops3_load0){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendm_cl_ret0_lane1_nops3_load.bin", 0);
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
    data[0] = 23120;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 23248;
    data[3] =16604635788312631495u;
    data[4] =10641147331897502849u;
    data[5] =16074938849232617494u;
    data[6] =14748270712197424163u;
    data[7] =4113041174098863449u;
    
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
    EXPECT_EQ(val, memdata[0][0]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 16);
    EXPECT_EQ(val, memdata[0][1]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 24);
    EXPECT_EQ(val, memdata[0][2]);
     
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
    
TEST_F(Sendm, sendm_cl_ret0_lane1_nops3_store0){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendm_cl_ret0_lane1_nops3_store.bin", 0);
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
    data[0] = 2096;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 2224;
    data[3] =7238283413115565415u;
    data[4] =10527190481805898675u;
    data[5] =12679741419205831277u;
    data[6] =17981285825262667774u;
    data[7] =7887876418069781720u;
    
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
    EXPECT_EQ(memdata[0][0], data[0]);
    EXPECT_EQ(memdata[0][1], data[1]);
    EXPECT_EQ(memdata[0][2], data[2]);
     
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
    
TEST_F(Sendm, sendm_cw_ret0_lane1_nops4_load0){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendm_cw_ret0_lane1_nops4_load.bin", 0);
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
    data[0] = 27528;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 27656;
    data[3] =14227097519469155534u;
    data[4] =9805946235619733313u;
    data[5] =7366429494241113793u;
    data[6] =11758771068649095229u;
    data[7] =13288267477017505973u;
    
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
    EXPECT_EQ(val, memdata[0][0]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 16);
    EXPECT_EQ(val, memdata[0][1]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 24);
    EXPECT_EQ(val, memdata[0][2]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 32);
    EXPECT_EQ(val, memdata[0][3]);
     
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
    
TEST_F(Sendm, sendm_cw_ret0_lane2_nops4_load1){
    numlanes = 2;
    m.NumLanes = 2;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendm_cw_ret0_lane2_nops4_load.bin", 0);
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
    data[0] = 6576;
    data[1] = reinterpret_cast<uint64_t>(&memdata[1][0]);
    data[2] = 6704;
    data[3] =9274200869949223589u;
    data[4] =6969891988164066749u;
    data[5] =11547846924975449885u;
    data[6] =16987665343733638635u;
    data[7] =3771016555108668491u;
    
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
    EXPECT_EQ(val, memdata[1][0]);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 16);
    EXPECT_EQ(val, memdata[1][1]);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 24);
    EXPECT_EQ(val, memdata[1][2]);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 32);
    EXPECT_EQ(val, memdata[1][3]);
     
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
    
TEST_F(Sendm, sendm_cw_ret0_lane1_nops4_store0){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendm_cw_ret0_lane1_nops4_store.bin", 0);
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
    data[0] = 21168;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 21296;
    data[3] =16553989324802221783u;
    data[4] =8160606370840182719u;
    data[5] =16031151064360347314u;
    data[6] =6397711484764344112u;
    data[7] =15099203789979478637u;
    
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
    EXPECT_EQ(memdata[0][0], data[0]);
    EXPECT_EQ(memdata[0][1], data[1]);
    EXPECT_EQ(memdata[0][2], data[2]);
    EXPECT_EQ(memdata[0][3], data[3]);
     
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
    
TEST_F(Sendm, sendm_cw_ret0_lane2_nops4_store1){
    numlanes = 2;
    m.NumLanes = 2;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendm_cw_ret0_lane2_nops4_store.bin", 0);
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
    data[0] = 19152;
    data[1] = reinterpret_cast<uint64_t>(&memdata[1][0]);
    data[2] = 19280;
    data[3] =6456768876874133567u;
    data[4] =12661063678232228512u;
    data[5] =13951079688677444012u;
    data[6] =11624724698677518039u;
    data[7] =17746621100382698268u;
    
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
    EXPECT_EQ(memdata[1][0], data[0]);
    EXPECT_EQ(memdata[1][1], data[1]);
    EXPECT_EQ(memdata[1][2], data[2]);
    EXPECT_EQ(memdata[1][3], data[3]);
     
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
    
TEST_F(Sendm, sendm_cl_ret0_lane1_nops4_load0){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendm_cl_ret0_lane1_nops4_load.bin", 0);
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
    data[0] = 31936;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 32064;
    data[3] =11980477456126934286u;
    data[4] =10454222748051983529u;
    data[5] =724946565277933398u;
    data[6] =1144846711509718420u;
    data[7] =4998825822100758567u;
    
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
    EXPECT_EQ(val, memdata[0][0]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 16);
    EXPECT_EQ(val, memdata[0][1]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 24);
    EXPECT_EQ(val, memdata[0][2]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 32);
    EXPECT_EQ(val, memdata[0][3]);
     
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
    
TEST_F(Sendm, sendm_cl_ret0_lane1_nops4_store0){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendm_cl_ret0_lane1_nops4_store.bin", 0);
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
    data[0] = 15528;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 15656;
    data[3] =4917196811203052448u;
    data[4] =10936789247924362916u;
    data[5] =11879450399701868405u;
    data[6] =2761542915955676079u;
    data[7] =11741451396345470395u;
    
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
    EXPECT_EQ(memdata[0][0], data[0]);
    EXPECT_EQ(memdata[0][1], data[1]);
    EXPECT_EQ(memdata[0][2], data[2]);
    EXPECT_EQ(memdata[0][3], data[3]);
     
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
    
TEST_F(Sendm, sendm_cw_ret0_lane1_nops5_load0){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendm_cw_ret0_lane1_nops5_load.bin", 0);
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
    data[0] = 16776;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 16904;
    data[3] =10087588266646443023u;
    data[4] =50916964991880330u;
    data[5] =8265474550790168558u;
    data[6] =3767613546884563531u;
    data[7] =2088037294727129378u;
    
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
    EXPECT_EQ(val, memdata[0][0]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 16);
    EXPECT_EQ(val, memdata[0][1]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 24);
    EXPECT_EQ(val, memdata[0][2]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 32);
    EXPECT_EQ(val, memdata[0][3]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 40);
    EXPECT_EQ(val, memdata[0][4]);
     
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
    
TEST_F(Sendm, sendm_cw_ret0_lane2_nops5_load1){
    numlanes = 2;
    m.NumLanes = 2;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendm_cw_ret0_lane2_nops5_load.bin", 0);
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
    data[0] = 10232;
    data[1] = reinterpret_cast<uint64_t>(&memdata[1][0]);
    data[2] = 10360;
    data[3] =6093811956132395022u;
    data[4] =7195880933221026421u;
    data[5] =1788503350839844881u;
    data[6] =15480398633774135664u;
    data[7] =15498902746916099178u;
    
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
    EXPECT_EQ(val, memdata[1][0]);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 16);
    EXPECT_EQ(val, memdata[1][1]);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 24);
    EXPECT_EQ(val, memdata[1][2]);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 32);
    EXPECT_EQ(val, memdata[1][3]);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 40);
    EXPECT_EQ(val, memdata[1][4]);
     
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
    
TEST_F(Sendm, sendm_cw_ret0_lane1_nops5_store0){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendm_cw_ret0_lane1_nops5_store.bin", 0);
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
    data[0] = 29248;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 29376;
    data[3] =15602451228470795767u;
    data[4] =10883757375690845152u;
    data[5] =3943499973746519532u;
    data[6] =5129727559622022938u;
    data[7] =1694981871224753687u;
    
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
    EXPECT_EQ(memdata[0][0], data[0]);
    EXPECT_EQ(memdata[0][1], data[1]);
    EXPECT_EQ(memdata[0][2], data[2]);
    EXPECT_EQ(memdata[0][3], data[3]);
    EXPECT_EQ(memdata[0][4], data[4]);
     
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
    
TEST_F(Sendm, sendm_cw_ret0_lane2_nops5_store1){
    numlanes = 2;
    m.NumLanes = 2;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendm_cw_ret0_lane2_nops5_store.bin", 0);
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
    data[0] = 22264;
    data[1] = reinterpret_cast<uint64_t>(&memdata[1][0]);
    data[2] = 22392;
    data[3] =2404280960794929731u;
    data[4] =7208291516937329465u;
    data[5] =17307869226741954807u;
    data[6] =2791084935559351668u;
    data[7] =12319516803757456041u;
    
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
    EXPECT_EQ(memdata[1][0], data[0]);
    EXPECT_EQ(memdata[1][1], data[1]);
    EXPECT_EQ(memdata[1][2], data[2]);
    EXPECT_EQ(memdata[1][3], data[3]);
    EXPECT_EQ(memdata[1][4], data[4]);
     
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
    
TEST_F(Sendm, sendm_cl_ret0_lane1_nops5_load0){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendm_cl_ret0_lane1_nops5_load.bin", 0);
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
    data[0] = 9128;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 9256;
    data[3] =6018005792989673797u;
    data[4] =15713287408366833382u;
    data[5] =17453900866011815133u;
    data[6] =17350886289750943232u;
    data[7] =5783513979146437899u;
    
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
    EXPECT_EQ(val, memdata[0][0]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 16);
    EXPECT_EQ(val, memdata[0][1]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 24);
    EXPECT_EQ(val, memdata[0][2]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 32);
    EXPECT_EQ(val, memdata[0][3]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 40);
    EXPECT_EQ(val, memdata[0][4]);
     
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
    
TEST_F(Sendm, sendm_cl_ret0_lane1_nops5_store0){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendm_cl_ret0_lane1_nops5_store.bin", 0);
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
    data[0] = 20536;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 20664;
    data[3] =14436627200743959051u;
    data[4] =13209439997455107053u;
    data[5] =13855434283733185084u;
    data[6] =13544871925681866728u;
    data[7] =1799177348537536431u;
    
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
    EXPECT_EQ(memdata[0][0], data[0]);
    EXPECT_EQ(memdata[0][1], data[1]);
    EXPECT_EQ(memdata[0][2], data[2]);
    EXPECT_EQ(memdata[0][3], data[3]);
    EXPECT_EQ(memdata[0][4], data[4]);
     
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
    
TEST_F(Sendm, sendm_cw_ret0_lane1_nops6_load0){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendm_cw_ret0_lane1_nops6_load.bin", 0);
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
    data[0] = 23448;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 23576;
    data[3] =5806665863646664807u;
    data[4] =3386785371370093414u;
    data[5] =17886485566227123595u;
    data[6] =7722024292731821735u;
    data[7] =6801142350543370601u;
    
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
    EXPECT_EQ(val, memdata[0][0]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 16);
    EXPECT_EQ(val, memdata[0][1]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 24);
    EXPECT_EQ(val, memdata[0][2]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 32);
    EXPECT_EQ(val, memdata[0][3]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 40);
    EXPECT_EQ(val, memdata[0][4]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 48);
    EXPECT_EQ(val, memdata[0][5]);
     
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
    
TEST_F(Sendm, sendm_cw_ret0_lane2_nops6_load1){
    numlanes = 2;
    m.NumLanes = 2;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendm_cw_ret0_lane2_nops6_load.bin", 0);
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
    data[0] = 17008;
    data[1] = reinterpret_cast<uint64_t>(&memdata[1][0]);
    data[2] = 17136;
    data[3] =2898224089192008795u;
    data[4] =13249201343741467161u;
    data[5] =4250909773184561067u;
    data[6] =2999105574934013584u;
    data[7] =12267765729713942729u;
    
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
    EXPECT_EQ(val, memdata[1][0]);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 16);
    EXPECT_EQ(val, memdata[1][1]);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 24);
    EXPECT_EQ(val, memdata[1][2]);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 32);
    EXPECT_EQ(val, memdata[1][3]);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 40);
    EXPECT_EQ(val, memdata[1][4]);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 48);
    EXPECT_EQ(val, memdata[1][5]);
     
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
    
TEST_F(Sendm, sendm_cw_ret0_lane1_nops6_store0){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendm_cw_ret0_lane1_nops6_store.bin", 0);
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
    data[0] = 15680;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 15808;
    data[3] =2777387501569920431u;
    data[4] =6559724549859111711u;
    data[5] =13286688800802389811u;
    data[6] =17585538041433070103u;
    data[7] =16838485649344810557u;
    
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
    EXPECT_EQ(memdata[0][0], data[0]);
    EXPECT_EQ(memdata[0][1], data[1]);
    EXPECT_EQ(memdata[0][2], data[2]);
    EXPECT_EQ(memdata[0][3], data[3]);
    EXPECT_EQ(memdata[0][4], data[4]);
    EXPECT_EQ(memdata[0][5], data[5]);
     
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
    
TEST_F(Sendm, sendm_cw_ret0_lane2_nops6_store1){
    numlanes = 2;
    m.NumLanes = 2;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendm_cw_ret0_lane2_nops6_store.bin", 0);
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
    data[0] = 30800;
    data[1] = reinterpret_cast<uint64_t>(&memdata[1][0]);
    data[2] = 30928;
    data[3] =6040609966794405856u;
    data[4] =760621078455144742u;
    data[5] =17208227970729777920u;
    data[6] =10813980244209362993u;
    data[7] =2925882579284718798u;
    
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
    EXPECT_EQ(memdata[1][0], data[0]);
    EXPECT_EQ(memdata[1][1], data[1]);
    EXPECT_EQ(memdata[1][2], data[2]);
    EXPECT_EQ(memdata[1][3], data[3]);
    EXPECT_EQ(memdata[1][4], data[4]);
    EXPECT_EQ(memdata[1][5], data[5]);
     
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
    
TEST_F(Sendm, sendm_cl_ret0_lane1_nops6_load0){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendm_cl_ret0_lane1_nops6_load.bin", 0);
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
    data[0] = 11456;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 11584;
    data[3] =16196199644622951372u;
    data[4] =9913383649535784490u;
    data[5] =12838590032789398098u;
    data[6] =3126643142157238979u;
    data[7] =5299333507845746725u;
    
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
    EXPECT_EQ(val, memdata[0][0]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 16);
    EXPECT_EQ(val, memdata[0][1]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 24);
    EXPECT_EQ(val, memdata[0][2]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 32);
    EXPECT_EQ(val, memdata[0][3]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 40);
    EXPECT_EQ(val, memdata[0][4]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 48);
    EXPECT_EQ(val, memdata[0][5]);
     
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
    
TEST_F(Sendm, sendm_cl_ret0_lane1_nops6_store0){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendm_cl_ret0_lane1_nops6_store.bin", 0);
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
    data[0] = 2584;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 2712;
    data[3] =7111521918430648099u;
    data[4] =9328375520855524256u;
    data[5] =15164664068022942599u;
    data[6] =2708625048204907480u;
    data[7] =9937411029146494566u;
    
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
    EXPECT_EQ(memdata[0][0], data[0]);
    EXPECT_EQ(memdata[0][1], data[1]);
    EXPECT_EQ(memdata[0][2], data[2]);
    EXPECT_EQ(memdata[0][3], data[3]);
    EXPECT_EQ(memdata[0][4], data[4]);
    EXPECT_EQ(memdata[0][5], data[5]);
     
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
    
TEST_F(Sendm, sendm_cw_ret0_lane1_nops7_load0){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendm_cw_ret0_lane1_nops7_load.bin", 0);
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
    data[0] = 19152;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 19280;
    data[3] =9022322257900403142u;
    data[4] =12929149648465309535u;
    data[5] =4750109862880260294u;
    data[6] =12125091175580496999u;
    data[7] =14049576014535663903u;
    
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
    EXPECT_EQ(val, memdata[0][0]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 16);
    EXPECT_EQ(val, memdata[0][1]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 24);
    EXPECT_EQ(val, memdata[0][2]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 32);
    EXPECT_EQ(val, memdata[0][3]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 40);
    EXPECT_EQ(val, memdata[0][4]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 48);
    EXPECT_EQ(val, memdata[0][5]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 56);
    EXPECT_EQ(val, memdata[0][6]);
     
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
    
TEST_F(Sendm, sendm_cw_ret0_lane2_nops7_load1){
    numlanes = 2;
    m.NumLanes = 2;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendm_cw_ret0_lane2_nops7_load.bin", 0);
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
    data[1] = reinterpret_cast<uint64_t>(&memdata[1][0]);
    data[2] = 24664;
    data[3] =2137345595489209420u;
    data[4] =1520407030159366866u;
    data[5] =8168694896645682158u;
    data[6] =4193051670961832337u;
    data[7] =5884782329830204914u;
    
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
    EXPECT_EQ(val, memdata[1][0]);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 16);
    EXPECT_EQ(val, memdata[1][1]);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 24);
    EXPECT_EQ(val, memdata[1][2]);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 32);
    EXPECT_EQ(val, memdata[1][3]);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 40);
    EXPECT_EQ(val, memdata[1][4]);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 48);
    EXPECT_EQ(val, memdata[1][5]);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 56);
    EXPECT_EQ(val, memdata[1][6]);
     
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
    
TEST_F(Sendm, sendm_cw_ret0_lane1_nops7_store0){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendm_cw_ret0_lane1_nops7_store.bin", 0);
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
    data[0] = 25040;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 25168;
    data[3] =16467522349375315040u;
    data[4] =1304591181870161345u;
    data[5] =10052209957723984906u;
    data[6] =5120150507748771637u;
    data[7] =9362120807006113141u;
    
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
    EXPECT_EQ(memdata[0][0], data[0]);
    EXPECT_EQ(memdata[0][1], data[1]);
    EXPECT_EQ(memdata[0][2], data[2]);
    EXPECT_EQ(memdata[0][3], data[3]);
    EXPECT_EQ(memdata[0][4], data[4]);
    EXPECT_EQ(memdata[0][5], data[5]);
    EXPECT_EQ(memdata[0][6], data[6]);
     
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
    
TEST_F(Sendm, sendm_cw_ret0_lane2_nops7_store1){
    numlanes = 2;
    m.NumLanes = 2;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendm_cw_ret0_lane2_nops7_store.bin", 0);
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
    data[0] = 8272;
    data[1] = reinterpret_cast<uint64_t>(&memdata[1][0]);
    data[2] = 8400;
    data[3] =17339338859124813703u;
    data[4] =13698566660083383203u;
    data[5] =1786181757974789267u;
    data[6] =17144249517578820759u;
    data[7] =1270143829116255073u;
    
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
    EXPECT_EQ(memdata[1][0], data[0]);
    EXPECT_EQ(memdata[1][1], data[1]);
    EXPECT_EQ(memdata[1][2], data[2]);
    EXPECT_EQ(memdata[1][3], data[3]);
    EXPECT_EQ(memdata[1][4], data[4]);
    EXPECT_EQ(memdata[1][5], data[5]);
    EXPECT_EQ(memdata[1][6], data[6]);
     
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
    
TEST_F(Sendm, sendm_cl_ret0_lane1_nops7_load0){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendm_cl_ret0_lane1_nops7_load.bin", 0);
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
    data[0] = 21152;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 21280;
    data[3] =8829322029483299146u;
    data[4] =11286953155606662037u;
    data[5] =6387841046538902503u;
    data[6] =10356266008992941453u;
    data[7] =4341351912087564223u;
    
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
    EXPECT_EQ(val, memdata[0][0]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 16);
    EXPECT_EQ(val, memdata[0][1]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 24);
    EXPECT_EQ(val, memdata[0][2]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 32);
    EXPECT_EQ(val, memdata[0][3]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 40);
    EXPECT_EQ(val, memdata[0][4]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 48);
    EXPECT_EQ(val, memdata[0][5]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 56);
    EXPECT_EQ(val, memdata[0][6]);
     
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
    
TEST_F(Sendm, sendm_cl_ret0_lane1_nops7_store0){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendm_cl_ret0_lane1_nops7_store.bin", 0);
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
    data[0] = 1224;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 1352;
    data[3] =12375705924935595450u;
    data[4] =17189204107574247582u;
    data[5] =16418389936854959132u;
    data[6] =14391792652968076127u;
    data[7] =18370579468250921587u;
    
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
    EXPECT_EQ(memdata[0][0], data[0]);
    EXPECT_EQ(memdata[0][1], data[1]);
    EXPECT_EQ(memdata[0][2], data[2]);
    EXPECT_EQ(memdata[0][3], data[3]);
    EXPECT_EQ(memdata[0][4], data[4]);
    EXPECT_EQ(memdata[0][5], data[5]);
    EXPECT_EQ(memdata[0][6], data[6]);
     
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
    
TEST_F(Sendm, sendm_cw_ret0_lane1_nops8_load0){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendm_cw_ret0_lane1_nops8_load.bin", 0);
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
    data[0] = 18016;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 18144;
    data[3] =3647333967328617945u;
    data[4] =16246564694837776126u;
    data[5] =18247269452864892009u;
    data[6] =10264874019600629208u;
    data[7] =13771802296732484331u;
    
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
    EXPECT_EQ(val, memdata[0][0]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 16);
    EXPECT_EQ(val, memdata[0][1]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 24);
    EXPECT_EQ(val, memdata[0][2]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 32);
    EXPECT_EQ(val, memdata[0][3]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 40);
    EXPECT_EQ(val, memdata[0][4]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 48);
    EXPECT_EQ(val, memdata[0][5]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 56);
    EXPECT_EQ(val, memdata[0][6]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 64);
    EXPECT_EQ(val, memdata[0][7]);
     
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
    
TEST_F(Sendm, sendm_cw_ret0_lane2_nops8_load1){
    numlanes = 2;
    m.NumLanes = 2;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendm_cw_ret0_lane2_nops8_load.bin", 0);
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
    data[0] = 14080;
    data[1] = reinterpret_cast<uint64_t>(&memdata[1][0]);
    data[2] = 14208;
    data[3] =15302206202121011382u;
    data[4] =1691044212278963093u;
    data[5] =1630944560549849857u;
    data[6] =8089514689808522027u;
    data[7] =14419338091527675041u;
    
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
    EXPECT_EQ(val, memdata[1][0]);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 16);
    EXPECT_EQ(val, memdata[1][1]);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 24);
    EXPECT_EQ(val, memdata[1][2]);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 32);
    EXPECT_EQ(val, memdata[1][3]);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 40);
    EXPECT_EQ(val, memdata[1][4]);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 48);
    EXPECT_EQ(val, memdata[1][5]);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 56);
    EXPECT_EQ(val, memdata[1][6]);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 64);
    EXPECT_EQ(val, memdata[1][7]);
     
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
    
TEST_F(Sendm, sendm_cw_ret0_lane1_nops8_store0){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendm_cw_ret0_lane1_nops8_store.bin", 0);
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
    data[0] = 11136;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 11264;
    data[3] =4721996405732860544u;
    data[4] =17311527355929499809u;
    data[5] =7668059679087532050u;
    data[6] =15716791092730029328u;
    data[7] =9144079549123752903u;
    
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
    EXPECT_EQ(memdata[0][0], data[0]);
    EXPECT_EQ(memdata[0][1], data[1]);
    EXPECT_EQ(memdata[0][2], data[2]);
    EXPECT_EQ(memdata[0][3], data[3]);
    EXPECT_EQ(memdata[0][4], data[4]);
    EXPECT_EQ(memdata[0][5], data[5]);
    EXPECT_EQ(memdata[0][6], data[6]);
    EXPECT_EQ(memdata[0][7], data[7]);
     
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
    
TEST_F(Sendm, sendm_cw_ret0_lane2_nops8_store1){
    numlanes = 2;
    m.NumLanes = 2;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendm_cw_ret0_lane2_nops8_store.bin", 0);
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
    data[0] = 19408;
    data[1] = reinterpret_cast<uint64_t>(&memdata[1][0]);
    data[2] = 19536;
    data[3] =14783979733047547878u;
    data[4] =7741447941941717231u;
    data[5] =9893388813861185223u;
    data[6] =4125301298731665297u;
    data[7] =11872905585450296599u;
    
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
    EXPECT_EQ(memdata[1][0], data[0]);
    EXPECT_EQ(memdata[1][1], data[1]);
    EXPECT_EQ(memdata[1][2], data[2]);
    EXPECT_EQ(memdata[1][3], data[3]);
    EXPECT_EQ(memdata[1][4], data[4]);
    EXPECT_EQ(memdata[1][5], data[5]);
    EXPECT_EQ(memdata[1][6], data[6]);
    EXPECT_EQ(memdata[1][7], data[7]);
     
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
    
TEST_F(Sendm, sendm_cl_ret0_lane1_nops8_load0){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendm_cl_ret0_lane1_nops8_load.bin", 0);
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
    data[0] = 16032;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 16160;
    data[3] =7655445112741928766u;
    data[4] =8084015292624356809u;
    data[5] =3619185194433817389u;
    data[6] =7502000192285800333u;
    data[7] =16199745648033238453u;
    
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
    EXPECT_EQ(val, memdata[0][0]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 16);
    EXPECT_EQ(val, memdata[0][1]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 24);
    EXPECT_EQ(val, memdata[0][2]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 32);
    EXPECT_EQ(val, memdata[0][3]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 40);
    EXPECT_EQ(val, memdata[0][4]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 48);
    EXPECT_EQ(val, memdata[0][5]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 56);
    EXPECT_EQ(val, memdata[0][6]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 64);
    EXPECT_EQ(val, memdata[0][7]);
     
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
    
TEST_F(Sendm, sendm_cl_ret0_lane1_nops8_store0){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendm_cl_ret0_lane1_nops8_store.bin", 0);
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
    data[0] = 13104;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 13232;
    data[3] =9355602364056802962u;
    data[4] =11822749015169033124u;
    data[5] =17834646081554461018u;
    data[6] =4934822490762409983u;
    data[7] =7424950934205272823u;
    
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
    EXPECT_EQ(memdata[0][0], data[0]);
    EXPECT_EQ(memdata[0][1], data[1]);
    EXPECT_EQ(memdata[0][2], data[2]);
    EXPECT_EQ(memdata[0][3], data[3]);
    EXPECT_EQ(memdata[0][4], data[4]);
    EXPECT_EQ(memdata[0][5], data[5]);
    EXPECT_EQ(memdata[0][6], data[6]);
    EXPECT_EQ(memdata[0][7], data[7]);
     
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
    
    