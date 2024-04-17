

#include <gtest/gtest.h>
#include "basim.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"
#include <iostream>
#include <cstdlib>

using namespace basim;

class Sendops : public ::testing::Test {
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
            
            printf("Sendops test is waiting...\n");
            if(status) break;
        }
        printf(".................Successfuly exit wait!.............\n");
    }
    BASim sim;
    machine_t m;
    int numlanes = 2;
    
};


TEST_F(Sendops, sendops_cw_ret0_lane1_nops10){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendops_cw_ret0_lane1_nops1.bin", 0);
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
    data[0] = 13936;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 14064;
    data[3] =13787900802592353440u;
    data[4] =2791391229567214953u;
    data[5] =11407600885305687360u;
    data[6] =9115671424353236411u;
    data[7] =2402019715209566220u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 13944);
    EXPECT_EQ(val, 13936u);
     
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
    
TEST_F(Sendops, sendops_cw_ret0_lane2_nops11){
    numlanes = 2;
    m.NumLanes = 2;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendops_cw_ret0_lane2_nops1.bin", 0);
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
    data[0] = 24248;
    data[1] = reinterpret_cast<uint64_t>(&memdata[1][0]);
    data[2] = 24376;
    data[3] =14206917259796294280u;
    data[4] =13925676601164565536u;
    data[5] =15222230119416786657u;
    data[6] =3130639679022916770u;
    data[7] =16654041343774577367u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 24256);
    EXPECT_EQ(val, 24248u);
     
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
    
TEST_F(Sendops, sendops_cl_ret0_lane1_nops10){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendops_cl_ret0_lane1_nops1.bin", 0);
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
    data[0] = 11424;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 11552;
    data[3] =3855088485094711915u;
    data[4] =14149495267598881058u;
    data[5] =10069673314296191687u;
    data[6] =3479985305819819534u;
    data[7] =254626947825422381u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 11432);
    EXPECT_EQ(val, 11424u);
     
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
    
TEST_F(Sendops, sendops_cl_ret0_lane2_nops11){
    numlanes = 2;
    m.NumLanes = 2;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendops_cl_ret0_lane2_nops1.bin", 0);
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
    data[0] = 8768;
    data[1] = reinterpret_cast<uint64_t>(&memdata[1][0]);
    data[2] = 8896;
    data[3] =5207839981538425372u;
    data[4] =13362083120443531170u;
    data[5] =10953224567307626999u;
    data[6] =2255885301239527110u;
    data[7] =17147921751345090913u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 8776);
    EXPECT_EQ(val, 8768u);
     
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
    
TEST_F(Sendops, sendops_cw_ret0_lane1_nops20){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendops_cw_ret0_lane1_nops2.bin", 0);
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
    data[0] = 616;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 744;
    data[3] =6724386038862331388u;
    data[4] =7703969410651516862u;
    data[5] =9842045191167670722u;
    data[6] =492969199393465189u;
    data[7] =16142580145426088045u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 624);
    EXPECT_EQ(val, 616u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 632);
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
    
TEST_F(Sendops, sendops_cw_ret0_lane2_nops21){
    numlanes = 2;
    m.NumLanes = 2;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendops_cw_ret0_lane2_nops2.bin", 0);
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
    data[0] = 28952;
    data[1] = reinterpret_cast<uint64_t>(&memdata[1][0]);
    data[2] = 29080;
    data[3] =13266776984371154991u;
    data[4] =6755688423528913483u;
    data[5] =11182075881393142825u;
    data[6] =13788072395634568026u;
    data[7] =5508250195157992692u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 28960);
    EXPECT_EQ(val, 28952u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 28968);
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
    
TEST_F(Sendops, sendops_cl_ret0_lane1_nops20){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendops_cl_ret0_lane1_nops2.bin", 0);
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
    data[0] = 19488;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 19616;
    data[3] =16531319232334516837u;
    data[4] =18018857130966957415u;
    data[5] =773122686203651795u;
    data[6] =8338147757742010440u;
    data[7] =17733638345348917199u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 19496);
    EXPECT_EQ(val, 19488u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 19504);
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
    
TEST_F(Sendops, sendops_cl_ret0_lane2_nops21){
    numlanes = 2;
    m.NumLanes = 2;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendops_cl_ret0_lane2_nops2.bin", 0);
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
    data[0] = 22136;
    data[1] = reinterpret_cast<uint64_t>(&memdata[1][0]);
    data[2] = 22264;
    data[3] =16824525853689579413u;
    data[4] =12532764366931389308u;
    data[5] =16753206022764307975u;
    data[6] =3019356687066785628u;
    data[7] =4602203610167486256u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 22144);
    EXPECT_EQ(val, 22136u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 22152);
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
    
TEST_F(Sendops, sendops_cw_ret0_lane1_nops30){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendops_cw_ret0_lane1_nops3.bin", 0);
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
    data[0] = 11504;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 11632;
    data[3] =6749257821854740630u;
    data[4] =12420051964913214245u;
    data[5] =2921312343915820734u;
    data[6] =8979299316071331651u;
    data[7] =1394772018216445644u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 11512);
    EXPECT_EQ(val, 11504u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 11520);
    EXPECT_EQ(val, (word_t) memdata[0]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 11528);
    EXPECT_EQ(val, 11632u);
     
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
    
TEST_F(Sendops, sendops_cw_ret0_lane2_nops31){
    numlanes = 2;
    m.NumLanes = 2;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendops_cw_ret0_lane2_nops3.bin", 0);
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
    data[0] = 32184;
    data[1] = reinterpret_cast<uint64_t>(&memdata[1][0]);
    data[2] = 32312;
    data[3] =17202268601769711124u;
    data[4] =4557095156136833264u;
    data[5] =3521943119002762198u;
    data[6] =2639773640310505176u;
    data[7] =10729805663579670731u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 32192);
    EXPECT_EQ(val, 32184u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 32200);
    EXPECT_EQ(val, (word_t) memdata[1]);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 32208);
    EXPECT_EQ(val, 32312u);
     
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
    
TEST_F(Sendops, sendops_cl_ret0_lane1_nops30){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendops_cl_ret0_lane1_nops3.bin", 0);
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
    data[0] = 2384;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 2512;
    data[3] =14768003663641429689u;
    data[4] =18139114989279953961u;
    data[5] =8806330910415372676u;
    data[6] =5055550892359573713u;
    data[7] =18191890414506104329u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 2392);
    EXPECT_EQ(val, 2384u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 2400);
    EXPECT_EQ(val, (word_t) memdata[0]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 2408);
    EXPECT_EQ(val, 2512u);
     
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
    
TEST_F(Sendops, sendops_cl_ret0_lane2_nops31){
    numlanes = 2;
    m.NumLanes = 2;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendops_cl_ret0_lane2_nops3.bin", 0);
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
    data[0] = 23496;
    data[1] = reinterpret_cast<uint64_t>(&memdata[1][0]);
    data[2] = 23624;
    data[3] =11483055097874474340u;
    data[4] =6715631486202707516u;
    data[5] =14101426075783652646u;
    data[6] =8154686344949139446u;
    data[7] =638572780568332237u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 23504);
    EXPECT_EQ(val, 23496u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 23512);
    EXPECT_EQ(val, (word_t) memdata[1]);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 23520);
    EXPECT_EQ(val, 23624u);
     
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
    
TEST_F(Sendops, sendops_cw_ret0_lane1_nops40){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendops_cw_ret0_lane1_nops4.bin", 0);
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
    data[0] = 30360;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 30488;
    data[3] =823698501496547799u;
    data[4] =9415958403736831516u;
    data[5] =3843585840315239560u;
    data[6] =4078527327099969229u;
    data[7] =7150374193017146180u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 30368);
    EXPECT_EQ(val, 30360u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 30376);
    EXPECT_EQ(val, (word_t) memdata[0]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 30384);
    EXPECT_EQ(val, 30488u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 30392);
    EXPECT_EQ(val, 823698501496547799u);
     
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
    
TEST_F(Sendops, sendops_cw_ret0_lane2_nops41){
    numlanes = 2;
    m.NumLanes = 2;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendops_cw_ret0_lane2_nops4.bin", 0);
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
    data[0] = 12232;
    data[1] = reinterpret_cast<uint64_t>(&memdata[1][0]);
    data[2] = 12360;
    data[3] =3979062612880325857u;
    data[4] =14756206172952460093u;
    data[5] =6546535609672610382u;
    data[6] =17379561944066310811u;
    data[7] =706505918888673550u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 12240);
    EXPECT_EQ(val, 12232u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 12248);
    EXPECT_EQ(val, (word_t) memdata[1]);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 12256);
    EXPECT_EQ(val, 12360u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 12264);
    EXPECT_EQ(val, 3979062612880325857u);
     
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
    
TEST_F(Sendops, sendops_cl_ret0_lane1_nops40){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendops_cl_ret0_lane1_nops4.bin", 0);
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
    data[0] = 27016;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 27144;
    data[3] =10618401650870702153u;
    data[4] =11958111464434950944u;
    data[5] =8287299010304499122u;
    data[6] =14063987371113202918u;
    data[7] =7374890554522564096u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 27024);
    EXPECT_EQ(val, 27016u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 27032);
    EXPECT_EQ(val, (word_t) memdata[0]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 27040);
    EXPECT_EQ(val, 27144u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 27048);
    EXPECT_EQ(val, 10618401650870702153u);
     
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
    
TEST_F(Sendops, sendops_cl_ret0_lane2_nops41){
    numlanes = 2;
    m.NumLanes = 2;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendops_cl_ret0_lane2_nops4.bin", 0);
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
    data[0] = 29632;
    data[1] = reinterpret_cast<uint64_t>(&memdata[1][0]);
    data[2] = 29760;
    data[3] =13613528683288517308u;
    data[4] =4733013948073067400u;
    data[5] =5377173732523300325u;
    data[6] =676816507545121149u;
    data[7] =9488123546149640522u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 29640);
    EXPECT_EQ(val, 29632u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 29648);
    EXPECT_EQ(val, (word_t) memdata[1]);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 29656);
    EXPECT_EQ(val, 29760u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 29664);
    EXPECT_EQ(val, 13613528683288517308u);
     
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
    
TEST_F(Sendops, sendops_cw_ret0_lane1_nops50){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendops_cw_ret0_lane1_nops5.bin", 0);
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
    data[0] = 12232;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 12360;
    data[3] =10127969264691315249u;
    data[4] =8801008506102064377u;
    data[5] =9219774197055607271u;
    data[6] =7081318989332219617u;
    data[7] =13344328014365123253u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 12240);
    EXPECT_EQ(val, 12232u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 12248);
    EXPECT_EQ(val, (word_t) memdata[0]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 12256);
    EXPECT_EQ(val, 12360u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 12264);
    EXPECT_EQ(val, 10127969264691315249u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 12272);
    EXPECT_EQ(val, 8801008506102064377u);
     
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
    
TEST_F(Sendops, sendops_cw_ret0_lane2_nops51){
    numlanes = 2;
    m.NumLanes = 2;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendops_cw_ret0_lane2_nops5.bin", 0);
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
    data[0] = 3928;
    data[1] = reinterpret_cast<uint64_t>(&memdata[1][0]);
    data[2] = 4056;
    data[3] =12150201381048523601u;
    data[4] =12150847891861970384u;
    data[5] =8288130905978171737u;
    data[6] =3381961194607771321u;
    data[7] =3507072407717174459u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 3936);
    EXPECT_EQ(val, 3928u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 3944);
    EXPECT_EQ(val, (word_t) memdata[1]);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 3952);
    EXPECT_EQ(val, 4056u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 3960);
    EXPECT_EQ(val, 12150201381048523601u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 3968);
    EXPECT_EQ(val, 12150847891861970384u);
     
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
    
TEST_F(Sendops, sendops_cl_ret0_lane1_nops50){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendops_cl_ret0_lane1_nops5.bin", 0);
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
    data[0] = 7248;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 7376;
    data[3] =12317900714327211935u;
    data[4] =6374256897908108605u;
    data[5] =7000065082642634543u;
    data[6] =13701611086751440178u;
    data[7] =5288800732820407559u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 7256);
    EXPECT_EQ(val, 7248u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 7264);
    EXPECT_EQ(val, (word_t) memdata[0]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 7272);
    EXPECT_EQ(val, 7376u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 7280);
    EXPECT_EQ(val, 12317900714327211935u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 7288);
    EXPECT_EQ(val, 6374256897908108605u);
     
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
    
TEST_F(Sendops, sendops_cl_ret0_lane2_nops51){
    numlanes = 2;
    m.NumLanes = 2;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendops_cl_ret0_lane2_nops5.bin", 0);
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
    data[0] = 10200;
    data[1] = reinterpret_cast<uint64_t>(&memdata[1][0]);
    data[2] = 10328;
    data[3] =6902563906574603607u;
    data[4] =17588971622495942135u;
    data[5] =5238845041932482157u;
    data[6] =11304427096278387675u;
    data[7] =7441928115568473225u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 10208);
    EXPECT_EQ(val, 10200u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 10216);
    EXPECT_EQ(val, (word_t) memdata[1]);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 10224);
    EXPECT_EQ(val, 10328u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 10232);
    EXPECT_EQ(val, 6902563906574603607u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 10240);
    EXPECT_EQ(val, 17588971622495942135u);
     
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
    
TEST_F(Sendops, sendops_cw_ret0_lane1_nops60){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendops_cw_ret0_lane1_nops6.bin", 0);
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
    data[0] = 16064;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 16192;
    data[3] =6927794617014805266u;
    data[4] =6214523011027271586u;
    data[5] =15447271762978322782u;
    data[6] =14103744541686920692u;
    data[7] =357022520894188137u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 16072);
    EXPECT_EQ(val, 16064u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 16080);
    EXPECT_EQ(val, (word_t) memdata[0]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 16088);
    EXPECT_EQ(val, 16192u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 16096);
    EXPECT_EQ(val, 6927794617014805266u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 16104);
    EXPECT_EQ(val, 6214523011027271586u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 16112);
    EXPECT_EQ(val, 15447271762978322782u);
     
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
    
TEST_F(Sendops, sendops_cw_ret0_lane2_nops61){
    numlanes = 2;
    m.NumLanes = 2;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendops_cw_ret0_lane2_nops6.bin", 0);
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
    data[0] = 12024;
    data[1] = reinterpret_cast<uint64_t>(&memdata[1][0]);
    data[2] = 12152;
    data[3] =608213750588898360u;
    data[4] =4325227785992673907u;
    data[5] =14237804584535114738u;
    data[6] =8488600626363786786u;
    data[7] =6267114398054111174u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 12032);
    EXPECT_EQ(val, 12024u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 12040);
    EXPECT_EQ(val, (word_t) memdata[1]);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 12048);
    EXPECT_EQ(val, 12152u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 12056);
    EXPECT_EQ(val, 608213750588898360u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 12064);
    EXPECT_EQ(val, 4325227785992673907u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 12072);
    EXPECT_EQ(val, 14237804584535114738u);
     
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
    
TEST_F(Sendops, sendops_cl_ret0_lane1_nops60){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendops_cl_ret0_lane1_nops6.bin", 0);
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
    data[0] = 128;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 256;
    data[3] =4853061491257427794u;
    data[4] =5363168238450938364u;
    data[5] =3788179990682337216u;
    data[6] =14441586191128762296u;
    data[7] =11301336082367887211u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 136);
    EXPECT_EQ(val, 128u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 144);
    EXPECT_EQ(val, (word_t) memdata[0]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 152);
    EXPECT_EQ(val, 256u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 160);
    EXPECT_EQ(val, 4853061491257427794u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 168);
    EXPECT_EQ(val, 5363168238450938364u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 176);
    EXPECT_EQ(val, 3788179990682337216u);
     
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
    
TEST_F(Sendops, sendops_cl_ret0_lane2_nops61){
    numlanes = 2;
    m.NumLanes = 2;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendops_cl_ret0_lane2_nops6.bin", 0);
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
    data[3] =17338949260020692465u;
    data[4] =7142234079570289832u;
    data[5] =7905271035859139783u;
    data[6] =4121855435471108767u;
    data[7] =10066237524179558324u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 15816);
    EXPECT_EQ(val, 15920u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 15824);
    EXPECT_EQ(val, 17338949260020692465u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 15832);
    EXPECT_EQ(val, 7142234079570289832u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 15840);
    EXPECT_EQ(val, 7905271035859139783u);
     
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
    
TEST_F(Sendops, sendops_cw_ret0_lane1_nops70){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendops_cw_ret0_lane1_nops7.bin", 0);
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
    data[0] = 26408;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 26536;
    data[3] =17683784370852830471u;
    data[4] =397326278427926610u;
    data[5] =15057573671819081070u;
    data[6] =1789126358015060048u;
    data[7] =13793473445693572959u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 26416);
    EXPECT_EQ(val, 26408u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 26424);
    EXPECT_EQ(val, (word_t) memdata[0]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 26432);
    EXPECT_EQ(val, 26536u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 26440);
    EXPECT_EQ(val, 17683784370852830471u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 26448);
    EXPECT_EQ(val, 397326278427926610u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 26456);
    EXPECT_EQ(val, 15057573671819081070u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 26464);
    EXPECT_EQ(val, 1789126358015060048u);
     
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
    
TEST_F(Sendops, sendops_cw_ret0_lane2_nops71){
    numlanes = 2;
    m.NumLanes = 2;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendops_cw_ret0_lane2_nops7.bin", 0);
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
    data[0] = 12288;
    data[1] = reinterpret_cast<uint64_t>(&memdata[1][0]);
    data[2] = 12416;
    data[3] =1882097722167502030u;
    data[4] =49290382206977323u;
    data[5] =11494282866589535609u;
    data[6] =7237055038053416984u;
    data[7] =14840272008380937774u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 12296);
    EXPECT_EQ(val, 12288u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 12304);
    EXPECT_EQ(val, (word_t) memdata[1]);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 12312);
    EXPECT_EQ(val, 12416u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 12320);
    EXPECT_EQ(val, 1882097722167502030u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 12328);
    EXPECT_EQ(val, 49290382206977323u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 12336);
    EXPECT_EQ(val, 11494282866589535609u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 12344);
    EXPECT_EQ(val, 7237055038053416984u);
     
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
    
TEST_F(Sendops, sendops_cl_ret0_lane1_nops70){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendops_cl_ret0_lane1_nops7.bin", 0);
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
    data[0] = 2736;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 2864;
    data[3] =10169775523467028591u;
    data[4] =4921747591708315825u;
    data[5] =16449447458269513364u;
    data[6] =2690154477482520804u;
    data[7] =9219851011350000356u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 2744);
    EXPECT_EQ(val, 2736u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 2752);
    EXPECT_EQ(val, (word_t) memdata[0]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 2760);
    EXPECT_EQ(val, 2864u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 2768);
    EXPECT_EQ(val, 10169775523467028591u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 2776);
    EXPECT_EQ(val, 4921747591708315825u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 2784);
    EXPECT_EQ(val, 16449447458269513364u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 2792);
    EXPECT_EQ(val, 2690154477482520804u);
     
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
    
TEST_F(Sendops, sendops_cl_ret0_lane2_nops71){
    numlanes = 2;
    m.NumLanes = 2;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendops_cl_ret0_lane2_nops7.bin", 0);
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
    data[0] = 20696;
    data[1] = reinterpret_cast<uint64_t>(&memdata[1][0]);
    data[2] = 20824;
    data[3] =4253297199546134372u;
    data[4] =5799750472201701855u;
    data[5] =15660618735704798880u;
    data[6] =10783785359993784266u;
    data[7] =8552967626359009101u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 20704);
    EXPECT_EQ(val, 20696u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 20712);
    EXPECT_EQ(val, (word_t) memdata[1]);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 20720);
    EXPECT_EQ(val, 20824u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 20728);
    EXPECT_EQ(val, 4253297199546134372u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 20736);
    EXPECT_EQ(val, 5799750472201701855u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 20744);
    EXPECT_EQ(val, 15660618735704798880u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 20752);
    EXPECT_EQ(val, 10783785359993784266u);
     
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
    
TEST_F(Sendops, sendops_cw_ret0_lane1_nops80){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendops_cw_ret0_lane1_nops8.bin", 0);
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
    data[0] = 9992;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 10120;
    data[3] =15200868008710475293u;
    data[4] =7453123680966499916u;
    data[5] =14535862863633206630u;
    data[6] =871369219958511467u;
    data[7] =11827319567605304449u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 10000);
    EXPECT_EQ(val, 9992u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 10008);
    EXPECT_EQ(val, (word_t) memdata[0]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 10016);
    EXPECT_EQ(val, 10120u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 10024);
    EXPECT_EQ(val, 15200868008710475293u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 10032);
    EXPECT_EQ(val, 7453123680966499916u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 10040);
    EXPECT_EQ(val, 14535862863633206630u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 10048);
    EXPECT_EQ(val, 871369219958511467u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 10056);
    EXPECT_EQ(val, 11827319567605304449u);
     
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
    
TEST_F(Sendops, sendops_cw_ret0_lane2_nops81){
    numlanes = 2;
    m.NumLanes = 2;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendops_cw_ret0_lane2_nops8.bin", 0);
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
    data[0] = 3336;
    data[1] = reinterpret_cast<uint64_t>(&memdata[1][0]);
    data[2] = 3464;
    data[3] =4186281893238758584u;
    data[4] =11567677933781419794u;
    data[5] =17395484401125165404u;
    data[6] =9509506732438010208u;
    data[7] =4006067725693962626u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 3344);
    EXPECT_EQ(val, 3336u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 3352);
    EXPECT_EQ(val, (word_t) memdata[1]);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 3360);
    EXPECT_EQ(val, 3464u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 3368);
    EXPECT_EQ(val, 4186281893238758584u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 3376);
    EXPECT_EQ(val, 11567677933781419794u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 3384);
    EXPECT_EQ(val, 17395484401125165404u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 3392);
    EXPECT_EQ(val, 9509506732438010208u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 3400);
    EXPECT_EQ(val, 4006067725693962626u);
     
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
    
TEST_F(Sendops, sendops_cl_ret0_lane1_nops80){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendops_cl_ret0_lane1_nops8.bin", 0);
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
    data[0] = 13640;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 13768;
    data[3] =15714356043035777804u;
    data[4] =14535164484275822950u;
    data[5] =13562623620007067024u;
    data[6] =15156068733311219281u;
    data[7] =15122788920689083800u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 13648);
    EXPECT_EQ(val, 13640u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 13656);
    EXPECT_EQ(val, (word_t) memdata[0]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 13664);
    EXPECT_EQ(val, 13768u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 13672);
    EXPECT_EQ(val, 15714356043035777804u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 13680);
    EXPECT_EQ(val, 14535164484275822950u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 13688);
    EXPECT_EQ(val, 13562623620007067024u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 13696);
    EXPECT_EQ(val, 15156068733311219281u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 13704);
    EXPECT_EQ(val, 15122788920689083800u);
     
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
    
TEST_F(Sendops, sendops_cl_ret0_lane2_nops81){
    numlanes = 2;
    m.NumLanes = 2;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/sendops_cl_ret0_lane2_nops8.bin", 0);
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
    data[0] = 24696;
    data[1] = reinterpret_cast<uint64_t>(&memdata[1][0]);
    data[2] = 24824;
    data[3] =3345272387397057333u;
    data[4] =16569752177533199976u;
    data[5] =10509550723306399291u;
    data[6] =15369140361166491088u;
    data[7] =6175384550573275659u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 24704);
    EXPECT_EQ(val, 24696u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 24712);
    EXPECT_EQ(val, (word_t) memdata[1]);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 24720);
    EXPECT_EQ(val, 24824u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 24728);
    EXPECT_EQ(val, 3345272387397057333u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 24736);
    EXPECT_EQ(val, 16569752177533199976u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 24744);
    EXPECT_EQ(val, 10509550723306399291u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 24752);
    EXPECT_EQ(val, 15369140361166491088u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 24760);
    EXPECT_EQ(val, 6175384550573275659u);
     
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
    
    