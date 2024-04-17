

#include <gtest/gtest.h>
#include "basim.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"
#include <iostream>
#include <cstdlib>

using namespace basim;

class Send : public ::testing::Test {
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
            
            printf("Send test is waiting...\n");
            if(status) break;
        }
        printf(".................Successfuly exit wait!.............\n");
    }
    BASim sim;
    machine_t m;
    int numlanes = 2;
    
};


TEST_F(Send, send_cw_ret0_lane1_nops10){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/send_cw_ret0_lane1_nops1.bin", 0);
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
    data[0] = 12488;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 12616;
    data[3] =7215432171506394471u;
    data[4] =12127694055540672152u;
    data[5] =14505315729418552286u;
    data[6] =14822471404340504504u;
    data[7] =1918267489177552956u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 12496);
    EXPECT_EQ(val, 12488u);
     
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
    
TEST_F(Send, send_cw_ret0_lane2_nops11){
    numlanes = 2;
    m.NumLanes = 2;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/send_cw_ret0_lane2_nops1.bin", 0);
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
    data[0] = 5984;
    data[1] = reinterpret_cast<uint64_t>(&memdata[1][0]);
    data[2] = 6112;
    data[3] =12188554230553950759u;
    data[4] =11526508503956520717u;
    data[5] =7235972799042107334u;
    data[6] =17969733564866401754u;
    data[7] =7304646281255708569u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 5992);
    EXPECT_EQ(val, 5984u);
     
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
    
TEST_F(Send, send_cl_ret0_lane1_nops10){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/send_cl_ret0_lane1_nops1.bin", 0);
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
    data[0] = 8472;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 8600;
    data[3] =5899999080839966320u;
    data[4] =3979860659370123249u;
    data[5] =6135438589475244979u;
    data[6] =1787571111275026764u;
    data[7] =1930079837923456751u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 8480);
    EXPECT_EQ(val, 8472u);
     
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
    
TEST_F(Send, send_cl_ret0_lane2_nops11){
    numlanes = 2;
    m.NumLanes = 2;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/send_cl_ret0_lane2_nops1.bin", 0);
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
    data[0] = 3888;
    data[1] = reinterpret_cast<uint64_t>(&memdata[1][0]);
    data[2] = 4016;
    data[3] =9087326834058167125u;
    data[4] =3223440192367012361u;
    data[5] =2147178616763131236u;
    data[6] =344313272755846942u;
    data[7] =15476156673476833216u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 3896);
    EXPECT_EQ(val, 3888u);
     
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
    
TEST_F(Send, send_cw_ret0_lane1_nops20){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/send_cw_ret0_lane1_nops2.bin", 0);
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
    data[0] = 7920;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 8048;
    data[3] =2522993142867131219u;
    data[4] =1911381399322808270u;
    data[5] =17291075683599170444u;
    data[6] =12718552568197264770u;
    data[7] =6885561705510853137u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 7928);
    EXPECT_EQ(val, 7920u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 7936);
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
    
TEST_F(Send, send_cw_ret0_lane2_nops21){
    numlanes = 2;
    m.NumLanes = 2;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/send_cw_ret0_lane2_nops2.bin", 0);
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
    data[0] = 30200;
    data[1] = reinterpret_cast<uint64_t>(&memdata[1][0]);
    data[2] = 30328;
    data[3] =12280652840031001347u;
    data[4] =9708550440134111140u;
    data[5] =2389530698024079407u;
    data[6] =7830485473449587262u;
    data[7] =8369885552849256764u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 30208);
    EXPECT_EQ(val, 30200u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 30216);
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
    
TEST_F(Send, send_cl_ret0_lane1_nops20){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/send_cl_ret0_lane1_nops2.bin", 0);
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
    data[0] = 1096;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 1224;
    data[3] =2781991274493261794u;
    data[4] =13856600329726280128u;
    data[5] =12629612657365066406u;
    data[6] =12422315487243920195u;
    data[7] =8565866585896099099u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 1104);
    EXPECT_EQ(val, 1096u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 1112);
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
    
TEST_F(Send, send_cl_ret0_lane2_nops21){
    numlanes = 2;
    m.NumLanes = 2;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/send_cl_ret0_lane2_nops2.bin", 0);
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
    data[0] = 15824;
    data[1] = reinterpret_cast<uint64_t>(&memdata[1][0]);
    data[2] = 15952;
    data[3] =14926614869147829276u;
    data[4] =12599621826995326679u;
    data[5] =2764561350389135551u;
    data[6] =10831013318712130203u;
    data[7] =5326282193843828635u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 15832);
    EXPECT_EQ(val, 15824u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 15840);
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
    
TEST_F(Send, send_cw_ret0_lane1_nops30){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/send_cw_ret0_lane1_nops3.bin", 0);
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
    data[0] = 28512;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 28640;
    data[3] =11050304735588096873u;
    data[4] =8433268415533957044u;
    data[5] =8789173764059265092u;
    data[6] =15234918506768577885u;
    data[7] =9747583515213496811u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 28520);
    EXPECT_EQ(val, 28512u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 28528);
    EXPECT_EQ(val, (word_t) memdata[0]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 28536);
    EXPECT_EQ(val, 28640u);
     
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
    
TEST_F(Send, send_cw_ret0_lane2_nops31){
    numlanes = 2;
    m.NumLanes = 2;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/send_cw_ret0_lane2_nops3.bin", 0);
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
    data[0] = 11432;
    data[1] = reinterpret_cast<uint64_t>(&memdata[1][0]);
    data[2] = 11560;
    data[3] =10226423063356611557u;
    data[4] =6850313095631214507u;
    data[5] =15577899277403661744u;
    data[6] =17418280824579044392u;
    data[7] =6139841961417321525u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 11440);
    EXPECT_EQ(val, 11432u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 11448);
    EXPECT_EQ(val, (word_t) memdata[1]);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 11456);
    EXPECT_EQ(val, 11560u);
     
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
    
TEST_F(Send, send_cl_ret0_lane1_nops30){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/send_cl_ret0_lane1_nops3.bin", 0);
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
    data[0] = 26600;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 26728;
    data[3] =16404540264616242603u;
    data[4] =2267842785106386486u;
    data[5] =7339253311047896950u;
    data[6] =8420828865023773687u;
    data[7] =10591375689829234616u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 26608);
    EXPECT_EQ(val, 26600u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 26616);
    EXPECT_EQ(val, (word_t) memdata[0]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 26624);
    EXPECT_EQ(val, 26728u);
     
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
    
TEST_F(Send, send_cl_ret0_lane2_nops31){
    numlanes = 2;
    m.NumLanes = 2;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/send_cl_ret0_lane2_nops3.bin", 0);
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
    data[0] = 26272;
    data[1] = reinterpret_cast<uint64_t>(&memdata[1][0]);
    data[2] = 26400;
    data[3] =10207690528370892792u;
    data[4] =15094065454273962559u;
    data[5] =15095916149894102081u;
    data[6] =1076934623982624449u;
    data[7] =3764030294395656215u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 26280);
    EXPECT_EQ(val, 26272u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 26288);
    EXPECT_EQ(val, (word_t) memdata[1]);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 26296);
    EXPECT_EQ(val, 26400u);
     
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
    
TEST_F(Send, send_cw_ret0_lane1_nops40){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/send_cw_ret0_lane1_nops4.bin", 0);
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
    data[0] = 7672;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 7800;
    data[3] =8871225285249555482u;
    data[4] =1999829445376772730u;
    data[5] =1576322814443291042u;
    data[6] =7714569352982284312u;
    data[7] =14471867783664178795u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 7680);
    EXPECT_EQ(val, 7672u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 7688);
    EXPECT_EQ(val, (word_t) memdata[0]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 7696);
    EXPECT_EQ(val, 7800u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 7704);
    EXPECT_EQ(val, 8871225285249555482u);
     
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
    
TEST_F(Send, send_cw_ret0_lane2_nops41){
    numlanes = 2;
    m.NumLanes = 2;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/send_cw_ret0_lane2_nops4.bin", 0);
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
    data[0] = 23696;
    data[1] = reinterpret_cast<uint64_t>(&memdata[1][0]);
    data[2] = 23824;
    data[3] =6865823824744774367u;
    data[4] =10337740861631897523u;
    data[5] =4917928018155278396u;
    data[6] =10747894375671648673u;
    data[7] =1923506052636725115u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 23704);
    EXPECT_EQ(val, 23696u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 23712);
    EXPECT_EQ(val, (word_t) memdata[1]);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 23720);
    EXPECT_EQ(val, 23824u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 23728);
    EXPECT_EQ(val, 6865823824744774367u);
     
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
    
TEST_F(Send, send_cl_ret0_lane1_nops40){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/send_cl_ret0_lane1_nops4.bin", 0);
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
    data[0] = 16760;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 16888;
    data[3] =12030677235697505938u;
    data[4] =14887542893851021221u;
    data[5] =17251799503938600151u;
    data[6] =10832262684658308488u;
    data[7] =9896873964037901388u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 16768);
    EXPECT_EQ(val, 16760u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 16776);
    EXPECT_EQ(val, (word_t) memdata[0]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 16784);
    EXPECT_EQ(val, 16888u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 16792);
    EXPECT_EQ(val, 12030677235697505938u);
     
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
    
TEST_F(Send, send_cl_ret0_lane2_nops41){
    numlanes = 2;
    m.NumLanes = 2;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/send_cl_ret0_lane2_nops4.bin", 0);
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
    data[0] = 17088;
    data[1] = reinterpret_cast<uint64_t>(&memdata[1][0]);
    data[2] = 17216;
    data[3] =176325028436304689u;
    data[4] =8068082010723089619u;
    data[5] =9363503761921426849u;
    data[6] =5554570017251185226u;
    data[7] =5889246773506954447u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 17096);
    EXPECT_EQ(val, 17088u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 17104);
    EXPECT_EQ(val, (word_t) memdata[1]);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 17112);
    EXPECT_EQ(val, 17216u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 17120);
    EXPECT_EQ(val, 176325028436304689u);
     
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
    
TEST_F(Send, send_cw_ret0_lane1_nops50){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/send_cw_ret0_lane1_nops5.bin", 0);
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
    data[0] = 11584;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 11712;
    data[3] =5039544443980661148u;
    data[4] =9477699538542789766u;
    data[5] =6269198175401546590u;
    data[6] =13804133927223717262u;
    data[7] =5439169941939266301u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 11592);
    EXPECT_EQ(val, 11584u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 11600);
    EXPECT_EQ(val, (word_t) memdata[0]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 11608);
    EXPECT_EQ(val, 11712u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 11616);
    EXPECT_EQ(val, 5039544443980661148u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 11624);
    EXPECT_EQ(val, 9477699538542789766u);
     
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
    
TEST_F(Send, send_cw_ret0_lane2_nops51){
    numlanes = 2;
    m.NumLanes = 2;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/send_cw_ret0_lane2_nops5.bin", 0);
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
    data[0] = 26176;
    data[1] = reinterpret_cast<uint64_t>(&memdata[1][0]);
    data[2] = 26304;
    data[3] =17893049375640129308u;
    data[4] =18216806167087054087u;
    data[5] =17921117596727657050u;
    data[6] =618213250776460565u;
    data[7] =16352814230084833129u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 26184);
    EXPECT_EQ(val, 26176u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 26192);
    EXPECT_EQ(val, (word_t) memdata[1]);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 26200);
    EXPECT_EQ(val, 26304u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 26208);
    EXPECT_EQ(val, 17893049375640129308u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 26216);
    EXPECT_EQ(val, 18216806167087054087u);
     
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
    
TEST_F(Send, send_cl_ret0_lane1_nops50){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/send_cl_ret0_lane1_nops5.bin", 0);
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
    data[0] = 1056;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 1184;
    data[3] =2150508194549404293u;
    data[4] =9788084652369647325u;
    data[5] =2621665886587394981u;
    data[6] =14526649143492463039u;
    data[7] =3700243736696134045u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 1064);
    EXPECT_EQ(val, 1056u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 1072);
    EXPECT_EQ(val, (word_t) memdata[0]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 1080);
    EXPECT_EQ(val, 1184u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 1088);
    EXPECT_EQ(val, 2150508194549404293u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 1096);
    EXPECT_EQ(val, 9788084652369647325u);
     
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
    
TEST_F(Send, send_cl_ret0_lane2_nops51){
    numlanes = 2;
    m.NumLanes = 2;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/send_cl_ret0_lane2_nops5.bin", 0);
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
    data[0] = 9440;
    data[1] = reinterpret_cast<uint64_t>(&memdata[1][0]);
    data[2] = 9568;
    data[3] =2038404861918532796u;
    data[4] =836362301324319675u;
    data[5] =6272310490970810180u;
    data[6] =1362234091946319255u;
    data[7] =3262431054221806204u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 9448);
    EXPECT_EQ(val, 9440u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 9456);
    EXPECT_EQ(val, (word_t) memdata[1]);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 9464);
    EXPECT_EQ(val, 9568u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 9472);
    EXPECT_EQ(val, 2038404861918532796u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 9480);
    EXPECT_EQ(val, 836362301324319675u);
     
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
    
TEST_F(Send, send_cw_ret0_lane1_nops60){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/send_cw_ret0_lane1_nops6.bin", 0);
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
    data[0] = 15648;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 15776;
    data[3] =10612258112790672437u;
    data[4] =1701583695911177275u;
    data[5] =15446840183141668854u;
    data[6] =11068820585443531226u;
    data[7] =11800962093927284168u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 15656);
    EXPECT_EQ(val, 15648u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 15664);
    EXPECT_EQ(val, (word_t) memdata[0]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 15672);
    EXPECT_EQ(val, 15776u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 15680);
    EXPECT_EQ(val, 10612258112790672437u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 15688);
    EXPECT_EQ(val, 1701583695911177275u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 15696);
    EXPECT_EQ(val, 15446840183141668854u);
     
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
    
TEST_F(Send, send_cw_ret0_lane2_nops61){
    numlanes = 2;
    m.NumLanes = 2;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/send_cw_ret0_lane2_nops6.bin", 0);
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
    data[0] = 16248;
    data[1] = reinterpret_cast<uint64_t>(&memdata[1][0]);
    data[2] = 16376;
    data[3] =15303263900378496811u;
    data[4] =11023311101308845978u;
    data[5] =5911779187769833211u;
    data[6] =9220667426489740462u;
    data[7] =11382046945211399847u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 16256);
    EXPECT_EQ(val, 16248u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 16264);
    EXPECT_EQ(val, (word_t) memdata[1]);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 16272);
    EXPECT_EQ(val, 16376u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 16280);
    EXPECT_EQ(val, 15303263900378496811u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 16288);
    EXPECT_EQ(val, 11023311101308845978u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 16296);
    EXPECT_EQ(val, 5911779187769833211u);
     
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
    
TEST_F(Send, send_cl_ret0_lane1_nops60){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/send_cl_ret0_lane1_nops6.bin", 0);
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
    data[0] = 22424;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 22552;
    data[3] =2604996017329169846u;
    data[4] =1805362744607885264u;
    data[5] =12568794506190770963u;
    data[6] =9412905334314093675u;
    data[7] =6956217125583779915u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 22432);
    EXPECT_EQ(val, 22424u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 22440);
    EXPECT_EQ(val, (word_t) memdata[0]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 22448);
    EXPECT_EQ(val, 22552u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 22456);
    EXPECT_EQ(val, 2604996017329169846u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 22464);
    EXPECT_EQ(val, 1805362744607885264u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 22472);
    EXPECT_EQ(val, 12568794506190770963u);
     
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
    
TEST_F(Send, send_cl_ret0_lane2_nops61){
    numlanes = 2;
    m.NumLanes = 2;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/send_cl_ret0_lane2_nops6.bin", 0);
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
    data[0] = 30680;
    data[1] = reinterpret_cast<uint64_t>(&memdata[1][0]);
    data[2] = 30808;
    data[3] =5820887431358418187u;
    data[4] =12149821181337789476u;
    data[5] =1635853263171736442u;
    data[6] =7669936696279445464u;
    data[7] =11656605651399178021u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 30688);
    EXPECT_EQ(val, 30680u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 30696);
    EXPECT_EQ(val, (word_t) memdata[1]);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 30704);
    EXPECT_EQ(val, 30808u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 30712);
    EXPECT_EQ(val, 5820887431358418187u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 30720);
    EXPECT_EQ(val, 12149821181337789476u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 30728);
    EXPECT_EQ(val, 1635853263171736442u);
     
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
    
TEST_F(Send, send_cw_ret0_lane1_nops70){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/send_cw_ret0_lane1_nops7.bin", 0);
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
    data[0] = 17216;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 17344;
    data[3] =6128461344492964111u;
    data[4] =472125739651127086u;
    data[5] =4308341576955463233u;
    data[6] =884633315400948078u;
    data[7] =8556644176347106926u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 17224);
    EXPECT_EQ(val, 17216u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 17232);
    EXPECT_EQ(val, (word_t) memdata[0]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 17240);
    EXPECT_EQ(val, 17344u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 17248);
    EXPECT_EQ(val, 6128461344492964111u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 17256);
    EXPECT_EQ(val, 472125739651127086u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 17264);
    EXPECT_EQ(val, 4308341576955463233u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 17272);
    EXPECT_EQ(val, 884633315400948078u);
     
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
    
TEST_F(Send, send_cw_ret0_lane2_nops71){
    numlanes = 2;
    m.NumLanes = 2;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/send_cw_ret0_lane2_nops7.bin", 0);
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
    data[0] = 368;
    data[1] = reinterpret_cast<uint64_t>(&memdata[1][0]);
    data[2] = 496;
    data[3] =15579590069599517816u;
    data[4] =13929986157795904536u;
    data[5] =9778837983500936728u;
    data[6] =9134349776864450735u;
    data[7] =14713059346316906116u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 376);
    EXPECT_EQ(val, 368u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 384);
    EXPECT_EQ(val, (word_t) memdata[1]);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 392);
    EXPECT_EQ(val, 496u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 400);
    EXPECT_EQ(val, 15579590069599517816u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 408);
    EXPECT_EQ(val, 13929986157795904536u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 416);
    EXPECT_EQ(val, 9778837983500936728u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 424);
    EXPECT_EQ(val, 9134349776864450735u);
     
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
    
TEST_F(Send, send_cl_ret0_lane1_nops70){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/send_cl_ret0_lane1_nops7.bin", 0);
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
    data[0] = 26392;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 26520;
    data[3] =9167852150841538869u;
    data[4] =7910144183345015661u;
    data[5] =10162281420956181514u;
    data[6] =11640648091275300262u;
    data[7] =8557267179541327132u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 26400);
    EXPECT_EQ(val, 26392u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 26408);
    EXPECT_EQ(val, (word_t) memdata[0]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 26416);
    EXPECT_EQ(val, 26520u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 26424);
    EXPECT_EQ(val, 9167852150841538869u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 26432);
    EXPECT_EQ(val, 7910144183345015661u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 26440);
    EXPECT_EQ(val, 10162281420956181514u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 26448);
    EXPECT_EQ(val, 11640648091275300262u);
     
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
    
TEST_F(Send, send_cl_ret0_lane2_nops71){
    numlanes = 2;
    m.NumLanes = 2;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/send_cl_ret0_lane2_nops7.bin", 0);
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
    data[0] = 9840;
    data[1] = reinterpret_cast<uint64_t>(&memdata[1][0]);
    data[2] = 9968;
    data[3] =12124903994204709097u;
    data[4] =7327168376485001756u;
    data[5] =14474438243300451068u;
    data[6] =11775580478001861503u;
    data[7] =9626663107172792565u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 9848);
    EXPECT_EQ(val, 9840u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 9856);
    EXPECT_EQ(val, (word_t) memdata[1]);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 9864);
    EXPECT_EQ(val, 9968u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 9872);
    EXPECT_EQ(val, 12124903994204709097u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 9880);
    EXPECT_EQ(val, 7327168376485001756u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 9888);
    EXPECT_EQ(val, 14474438243300451068u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 9896);
    EXPECT_EQ(val, 11775580478001861503u);
     
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
    
TEST_F(Send, send_cw_ret0_lane1_nops80){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/send_cw_ret0_lane1_nops8.bin", 0);
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
    data[0] = 9392;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 9520;
    data[3] =13809090569579527525u;
    data[4] =16692812790333559821u;
    data[5] =7435849988639835480u;
    data[6] =13735150304819073075u;
    data[7] =7042957479072935069u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 9400);
    EXPECT_EQ(val, 9392u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 9408);
    EXPECT_EQ(val, (word_t) memdata[0]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 9416);
    EXPECT_EQ(val, 9520u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 9424);
    EXPECT_EQ(val, 13809090569579527525u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 9432);
    EXPECT_EQ(val, 16692812790333559821u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 9440);
    EXPECT_EQ(val, 7435849988639835480u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 9448);
    EXPECT_EQ(val, 13735150304819073075u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 9456);
    EXPECT_EQ(val, 7042957479072935069u);
     
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
    
TEST_F(Send, send_cw_ret0_lane2_nops81){
    numlanes = 2;
    m.NumLanes = 2;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/send_cw_ret0_lane2_nops8.bin", 0);
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
    data[0] = 2208;
    data[1] = reinterpret_cast<uint64_t>(&memdata[1][0]);
    data[2] = 2336;
    data[3] =18209809087755351805u;
    data[4] =184554147713218965u;
    data[5] =3191890781268657167u;
    data[6] =14877899201969563139u;
    data[7] =11172255411213115050u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 2216);
    EXPECT_EQ(val, 2208u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 2224);
    EXPECT_EQ(val, (word_t) memdata[1]);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 2232);
    EXPECT_EQ(val, 2336u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 2240);
    EXPECT_EQ(val, 18209809087755351805u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 2248);
    EXPECT_EQ(val, 184554147713218965u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 2256);
    EXPECT_EQ(val, 3191890781268657167u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 2264);
    EXPECT_EQ(val, 14877899201969563139u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 2272);
    EXPECT_EQ(val, 11172255411213115050u);
     
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
    
TEST_F(Send, send_cl_ret0_lane1_nops80){
    numlanes = 1;
    m.NumLanes = 1;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/send_cl_ret0_lane1_nops8.bin", 0);
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
    data[0] = 30592;
    data[1] = reinterpret_cast<uint64_t>(&memdata[0][0]);
    data[2] = 30720;
    data[3] =4148239135621001186u;
    data[4] =12933208426243617531u;
    data[5] =9922077400164849479u;
    data[6] =8810802021808627009u;
    data[7] =2471868868302063260u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 30600);
    EXPECT_EQ(val, 30592u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 30608);
    EXPECT_EQ(val, (word_t) memdata[0]);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 30616);
    EXPECT_EQ(val, 30720u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 30624);
    EXPECT_EQ(val, 4148239135621001186u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 30632);
    EXPECT_EQ(val, 12933208426243617531u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 30640);
    EXPECT_EQ(val, 9922077400164849479u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 30648);
    EXPECT_EQ(val, 8810802021808627009u);
    sim.ud2t_memcpy(&val, 8, NetworkID(0), 30656);
    EXPECT_EQ(val, 2471868868302063260u);
     
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
    
TEST_F(Send, send_cl_ret0_lane2_nops81){
    numlanes = 2;
    m.NumLanes = 2;
    sim = BASim(m);
    printf("numlanes: %d\n", numlanes);
    sim.initMachine("testprogs/binaries/send_cl_ret0_lane2_nops8.bin", 0);
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
    data[0] = 11984;
    data[1] = reinterpret_cast<uint64_t>(&memdata[1][0]);
    data[2] = 12112;
    data[3] =12406333740261952262u;
    data[4] =15542539427142833517u;
    data[5] =17913225809946062445u;
    data[6] =17256148322875360688u;
    data[7] =18230010589873321023u;
    
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
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 11992);
    EXPECT_EQ(val, 11984u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 12000);
    EXPECT_EQ(val, (word_t) memdata[1]);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 12008);
    EXPECT_EQ(val, 12112u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 12016);
    EXPECT_EQ(val, 12406333740261952262u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 12024);
    EXPECT_EQ(val, 15542539427142833517u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 12032);
    EXPECT_EQ(val, 17913225809946062445u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 12040);
    EXPECT_EQ(val, 17256148322875360688u);
    sim.ud2t_memcpy(&val, 8, NetworkID(1), 12048);
    EXPECT_EQ(val, 18230010589873321023u);
     
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
    
    