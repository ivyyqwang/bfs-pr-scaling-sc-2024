#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"

using namespace basim;

class movsbr_cycle : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    int numLanes = 64;
    UDAccelerator acc0 = UDAccelerator(numLanes, 0, 1); // UDAccelerator(numLanes, UDID/networkID, lmmode (0: accelerator based addressing, 1:bank/lane based addressing))
    int buffsize1 = 1024;
    int buffsize2 = 1024;
};
TEST_F(movsbr_cycle, Basic_movsbr_cycle_0_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movsbr_cycle_0_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(72);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t *data = new word_t[numop];
    data[0] = reinterpret_cast<word_t>((uint64_t)8);
    data[1] = reinterpret_cast<word_t>((uint64_t)9);
    data[2] = reinterpret_cast<word_t>((uint64_t)10);
    data[3] = reinterpret_cast<word_t>((uint64_t)11);
    data[4] = reinterpret_cast<word_t>((uint64_t)12);
    data[5] = reinterpret_cast<word_t>((uint64_t)13);
    data[6] = reinterpret_cast<word_t>((uint64_t)14);
    data[7] = reinterpret_cast<word_t>((uint64_t)15);
    
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16) + 63));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), 17));
        EXPECT_TRUE(acc0.testMem((i << 16) + 0, 5315425572927115857u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 8, 16369891694061108058u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 16, 358694176531363562u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 24, 9385688290991663116u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 32, 15466731902741433697u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 40, 13423007074618033250u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 48, 18340748291791964540u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 56, 14455682703345607048u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 64, 16318321004016492968u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 72, 2006610021029854803u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 80, 8130259365573725898u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 88, 5640259622515666216u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 96, 4842213849258906321u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 104, 4916713809707667985u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 112, 2273314880712394959u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 120, 7062542028525295960u));
    }
}
TEST_F(movsbr_cycle, Basic_movsbr_cycle_1_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movsbr_cycle_1_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(72);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t *data = new word_t[numop];
    data[0] = reinterpret_cast<word_t>((uint64_t)8);
    data[1] = reinterpret_cast<word_t>((uint64_t)9);
    data[2] = reinterpret_cast<word_t>((uint64_t)10);
    data[3] = reinterpret_cast<word_t>((uint64_t)11);
    data[4] = reinterpret_cast<word_t>((uint64_t)12);
    data[5] = reinterpret_cast<word_t>((uint64_t)13);
    data[6] = reinterpret_cast<word_t>((uint64_t)14);
    data[7] = reinterpret_cast<word_t>((uint64_t)15);
    
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16) + 63));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), 3));
        EXPECT_TRUE(acc0.testMem((i << 16) + 0, 7309047800740850525u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 8, 17845255730054340207u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 16, 8771937438725555679u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 24, 11854973635061668078u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 32, 15707877195623282361u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 40, 12083024584653706466u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 48, 2843831937306392799u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 56, 16540810155917914822u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 64, 5174508047113182943u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 72, 9704232124869306388u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 80, 15692511216270162828u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 88, 10522757486917844150u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 96, 7209086143150012018u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 104, 1806091254743724617u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 112, 13629911030865185043u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 120, 12334005070024551977u));
    }
}
TEST_F(movsbr_cycle, Basic_movsbr_cycle_2_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movsbr_cycle_2_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(72);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t *data = new word_t[numop];
    data[0] = reinterpret_cast<word_t>((uint64_t)8);
    data[1] = reinterpret_cast<word_t>((uint64_t)9);
    data[2] = reinterpret_cast<word_t>((uint64_t)10);
    data[3] = reinterpret_cast<word_t>((uint64_t)11);
    data[4] = reinterpret_cast<word_t>((uint64_t)12);
    data[5] = reinterpret_cast<word_t>((uint64_t)13);
    data[6] = reinterpret_cast<word_t>((uint64_t)14);
    data[7] = reinterpret_cast<word_t>((uint64_t)15);
    
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16) + 63));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), 3));
        EXPECT_TRUE(acc0.testMem((i << 16) + 0, 9979197417764277757u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 8, 5033780985240373592u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 16, 5182123139357375722u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 24, 3852142470250064719u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 32, 987402240015481676u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 40, 12862284980395840936u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 48, 14729796647266533968u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 56, 16282463210001071924u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 64, 10400896659467820229u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 72, 15762727869270704058u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 80, 11439424207804976552u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 88, 371218008549026488u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 96, 8681066895893656095u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 104, 9837184550381691045u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 112, 15874338327463355675u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 120, 7539534403284054675u));
    }
}
TEST_F(movsbr_cycle, Basic_movsbr_cycle_3_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movsbr_cycle_3_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(72);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t *data = new word_t[numop];
    data[0] = reinterpret_cast<word_t>((uint64_t)8);
    data[1] = reinterpret_cast<word_t>((uint64_t)9);
    data[2] = reinterpret_cast<word_t>((uint64_t)10);
    data[3] = reinterpret_cast<word_t>((uint64_t)11);
    data[4] = reinterpret_cast<word_t>((uint64_t)12);
    data[5] = reinterpret_cast<word_t>((uint64_t)13);
    data[6] = reinterpret_cast<word_t>((uint64_t)14);
    data[7] = reinterpret_cast<word_t>((uint64_t)15);
    
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16) + 63));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), 0));
        EXPECT_TRUE(acc0.testMem((i << 16) + 0, 11863401831602756737u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 8, 867570069374739008u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 16, 1886471224204293729u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 24, 1967170580533665331u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 32, 8665299943993859330u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 40, 10564836913747082660u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 48, 17320815979177930715u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 56, 1587133862175511599u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 64, 11661125038360027336u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 72, 13666419299275323338u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 80, 18213953465640798116u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 88, 2150919788224411501u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 96, 3121402382849003287u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 104, 15525599514181114807u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 112, 6605467782785442498u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 120, 10281150438064113332u));
    }
}
TEST_F(movsbr_cycle, Basic_movsbr_cycle_4_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movsbr_cycle_4_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(72);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t *data = new word_t[numop];
    data[0] = reinterpret_cast<word_t>((uint64_t)8);
    data[1] = reinterpret_cast<word_t>((uint64_t)9);
    data[2] = reinterpret_cast<word_t>((uint64_t)10);
    data[3] = reinterpret_cast<word_t>((uint64_t)11);
    data[4] = reinterpret_cast<word_t>((uint64_t)12);
    data[5] = reinterpret_cast<word_t>((uint64_t)13);
    data[6] = reinterpret_cast<word_t>((uint64_t)14);
    data[7] = reinterpret_cast<word_t>((uint64_t)15);
    
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16) + 63));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), 66));
        EXPECT_TRUE(acc0.testMem((i << 16) + 0, 7972252328619354513u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 8, 850299294906093307u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 16, 16152943831989409822u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 24, 17248107286706154085u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 32, 8833974249914761014u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 40, 2372254264705032725u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 48, 17918256527276265993u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 56, 2812340145507972330u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 64, 359107624380947681u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 72, 10180105327849677774u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 80, 6941277318832988117u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 88, 12898698855521868520u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 96, 11394176427877876766u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 104, 5048491246449120074u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 112, 7579300069584324521u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 120, 13524226376557216457u));
    }
}
TEST_F(movsbr_cycle, Basic_movsbr_cycle_5_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movsbr_cycle_5_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(72);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t *data = new word_t[numop];
    data[0] = reinterpret_cast<word_t>((uint64_t)8);
    data[1] = reinterpret_cast<word_t>((uint64_t)9);
    data[2] = reinterpret_cast<word_t>((uint64_t)10);
    data[3] = reinterpret_cast<word_t>((uint64_t)11);
    data[4] = reinterpret_cast<word_t>((uint64_t)12);
    data[5] = reinterpret_cast<word_t>((uint64_t)13);
    data[6] = reinterpret_cast<word_t>((uint64_t)14);
    data[7] = reinterpret_cast<word_t>((uint64_t)15);
    
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16) + 63));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), 102));
        EXPECT_TRUE(acc0.testMem((i << 16) + 0, 13912787261557263624u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 8, 7018426955211276207u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 16, 18149457805487361280u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 24, 4350109492191172084u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 32, 5327755730027346136u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 40, 1108676350133362290u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 48, 17132380456845616855u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 56, 1230335486109358259u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 64, 16604841570375999411u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 72, 14120206322279309653u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 80, 13778521697613986261u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 88, 10858513974510081686u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 96, 12590923167022288675u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 104, 11235926593847644812u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 112, 17812106093389257066u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 120, 12044530329585674716u));
    }
}
TEST_F(movsbr_cycle, Basic_movsbr_cycle_6_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movsbr_cycle_6_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(72);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t *data = new word_t[numop];
    data[0] = reinterpret_cast<word_t>((uint64_t)8);
    data[1] = reinterpret_cast<word_t>((uint64_t)9);
    data[2] = reinterpret_cast<word_t>((uint64_t)10);
    data[3] = reinterpret_cast<word_t>((uint64_t)11);
    data[4] = reinterpret_cast<word_t>((uint64_t)12);
    data[5] = reinterpret_cast<word_t>((uint64_t)13);
    data[6] = reinterpret_cast<word_t>((uint64_t)14);
    data[7] = reinterpret_cast<word_t>((uint64_t)15);
    
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16) + 63));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), 11));
        EXPECT_TRUE(acc0.testMem((i << 16) + 0, 11446651223314605254u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 8, 11928584126855039082u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 16, 7396084198033233846u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 24, 15994647543993913553u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 32, 11708682647294348019u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 40, 10148511375340251230u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 48, 12887895681540354556u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 56, 11958252169476541093u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 64, 8132965176821897845u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 72, 7959544703135628867u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 80, 938672200457189603u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 88, 9215062676754897524u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 96, 5372660034098167037u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 104, 15931407897865870576u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 112, 8963020585825894359u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 120, 12071209177449461981u));
    }
}
TEST_F(movsbr_cycle, Basic_movsbr_cycle_7_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movsbr_cycle_7_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(72);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t *data = new word_t[numop];
    data[0] = reinterpret_cast<word_t>((uint64_t)8);
    data[1] = reinterpret_cast<word_t>((uint64_t)9);
    data[2] = reinterpret_cast<word_t>((uint64_t)10);
    data[3] = reinterpret_cast<word_t>((uint64_t)11);
    data[4] = reinterpret_cast<word_t>((uint64_t)12);
    data[5] = reinterpret_cast<word_t>((uint64_t)13);
    data[6] = reinterpret_cast<word_t>((uint64_t)14);
    data[7] = reinterpret_cast<word_t>((uint64_t)15);
    
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16) + 63));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), 0));
        EXPECT_TRUE(acc0.testMem((i << 16) + 0, 2248054577651294510u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 8, 10380505454027245560u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 16, 4629625023933747584u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 24, 17575495470279091377u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 32, 14669340730744794322u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 40, 16434070007269987006u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 48, 16793078404362335831u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 56, 5175014755324113907u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 64, 1543688430390427812u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 72, 9069175932988141096u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 80, 17099921882649973689u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 88, 1441892070345064116u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 96, 7814729846487523692u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 104, 6559006609605975923u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 112, 10104782909385889965u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 120, 5602536543127419318u));
    }
}
TEST_F(movsbr_cycle, Basic_movsbr_cycle_8_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movsbr_cycle_8_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(72);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t *data = new word_t[numop];
    data[0] = reinterpret_cast<word_t>((uint64_t)8);
    data[1] = reinterpret_cast<word_t>((uint64_t)9);
    data[2] = reinterpret_cast<word_t>((uint64_t)10);
    data[3] = reinterpret_cast<word_t>((uint64_t)11);
    data[4] = reinterpret_cast<word_t>((uint64_t)12);
    data[5] = reinterpret_cast<word_t>((uint64_t)13);
    data[6] = reinterpret_cast<word_t>((uint64_t)14);
    data[7] = reinterpret_cast<word_t>((uint64_t)15);
    
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16) + 63));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), 3));
        EXPECT_TRUE(acc0.testMem((i << 16) + 0, 7291544779284714340u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 8, 5297481374249437788u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 16, 6445187594962627530u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 24, 2498290048875614630u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 32, 6068379245808661025u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 40, 16074756773754135481u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 48, 2573087666014937262u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 56, 13189783561253836863u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 64, 662159159732643361u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 72, 5692337052278335044u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 80, 14493862870981156676u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 88, 15558798927650683807u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 96, 17199429388620144878u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 104, 13812604370567396095u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 112, 1482750676268168348u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 120, 2989719707298049562u));
    }
}
TEST_F(movsbr_cycle, Basic_movsbr_cycle_9_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movsbr_cycle_9_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(72);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t *data = new word_t[numop];
    data[0] = reinterpret_cast<word_t>((uint64_t)8);
    data[1] = reinterpret_cast<word_t>((uint64_t)9);
    data[2] = reinterpret_cast<word_t>((uint64_t)10);
    data[3] = reinterpret_cast<word_t>((uint64_t)11);
    data[4] = reinterpret_cast<word_t>((uint64_t)12);
    data[5] = reinterpret_cast<word_t>((uint64_t)13);
    data[6] = reinterpret_cast<word_t>((uint64_t)14);
    data[7] = reinterpret_cast<word_t>((uint64_t)15);
    
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16) + 63));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), 41));
        EXPECT_TRUE(acc0.testMem((i << 16) + 0, 12817847730914793452u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 8, 17801172315820182032u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 16, 6548444808812307939u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 24, 14323892675688869671u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 32, 3612086517720718861u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 40, 12979201466133670556u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 48, 2488714641132749422u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 56, 14936715893278930501u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 64, 2263583848566340884u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 72, 8751374348455752499u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 80, 4839274452745047230u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 88, 11555849651611900822u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 96, 17459193544814747846u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 104, 12459686351761701751u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 112, 363710810505214059u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 120, 15961417103197542394u));
    }
}
TEST_F(movsbr_cycle, Basic_movsbr_cycle_10_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movsbr_cycle_10_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(72);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t *data = new word_t[numop];
    data[0] = reinterpret_cast<word_t>((uint64_t)8);
    data[1] = reinterpret_cast<word_t>((uint64_t)9);
    data[2] = reinterpret_cast<word_t>((uint64_t)10);
    data[3] = reinterpret_cast<word_t>((uint64_t)11);
    data[4] = reinterpret_cast<word_t>((uint64_t)12);
    data[5] = reinterpret_cast<word_t>((uint64_t)13);
    data[6] = reinterpret_cast<word_t>((uint64_t)14);
    data[7] = reinterpret_cast<word_t>((uint64_t)15);
    
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16) + 63));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), 43));
        EXPECT_TRUE(acc0.testMem((i << 16) + 0, 7605597222427814276u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 8, 7355478844561691467u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 16, 14950912002390363080u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 24, 1944813802826694509u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 32, 2790408390860751702u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 40, 272986690276073465u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 48, 3811646605690103646u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 56, 11310785983260464144u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 64, 7198570442730536053u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 72, 12820385243934220700u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 80, 10830217080116939918u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 88, 6895282773707583523u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 96, 9428065178759617855u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 104, 8972927618929511755u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 112, 1331133949347599686u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 120, 6924084533255862307u));
    }
}
TEST_F(movsbr_cycle, Basic_movsbr_cycle_11_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movsbr_cycle_11_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(72);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t *data = new word_t[numop];
    data[0] = reinterpret_cast<word_t>((uint64_t)8);
    data[1] = reinterpret_cast<word_t>((uint64_t)9);
    data[2] = reinterpret_cast<word_t>((uint64_t)10);
    data[3] = reinterpret_cast<word_t>((uint64_t)11);
    data[4] = reinterpret_cast<word_t>((uint64_t)12);
    data[5] = reinterpret_cast<word_t>((uint64_t)13);
    data[6] = reinterpret_cast<word_t>((uint64_t)14);
    data[7] = reinterpret_cast<word_t>((uint64_t)15);
    
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16) + 63));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), 46));
        EXPECT_TRUE(acc0.testMem((i << 16) + 0, 5279471188323876051u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 8, 7616461031582695143u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 16, 14454350219630122931u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 24, 4345061555607119378u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 32, 6363004107904425273u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 40, 2805196251513916556u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 48, 17218496383398868794u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 56, 4776851708963580980u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 64, 11933219557433975991u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 72, 3349390066165093513u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 80, 11561066627801968576u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 88, 7218322976121583331u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 96, 17598638521234013497u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 104, 16275625484725708542u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 112, 6852352951990150011u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 120, 17988638649325056533u));
    }
}
TEST_F(movsbr_cycle, Basic_movsbr_cycle_12_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movsbr_cycle_12_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(72);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t *data = new word_t[numop];
    data[0] = reinterpret_cast<word_t>((uint64_t)8);
    data[1] = reinterpret_cast<word_t>((uint64_t)9);
    data[2] = reinterpret_cast<word_t>((uint64_t)10);
    data[3] = reinterpret_cast<word_t>((uint64_t)11);
    data[4] = reinterpret_cast<word_t>((uint64_t)12);
    data[5] = reinterpret_cast<word_t>((uint64_t)13);
    data[6] = reinterpret_cast<word_t>((uint64_t)14);
    data[7] = reinterpret_cast<word_t>((uint64_t)15);
    
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16) + 63));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), 0));
        EXPECT_TRUE(acc0.testMem((i << 16) + 0, 8917799266040520772u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 8, 10510080340234789246u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 16, 10979697370627176398u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 24, 16613560278446899383u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 32, 2130914013565841697u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 40, 1991430700144355274u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 48, 2798480816291023893u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 56, 880571127382698022u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 64, 17394924827234862968u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 72, 2364544084971220707u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 80, 494278221559788151u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 88, 14176672818310490604u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 96, 4471622518703085563u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 104, 7209947080839745609u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 112, 3161247349790621979u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 120, 16635085825594462293u));
    }
}
TEST_F(movsbr_cycle, Basic_movsbr_cycle_13_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movsbr_cycle_13_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(72);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t *data = new word_t[numop];
    data[0] = reinterpret_cast<word_t>((uint64_t)8);
    data[1] = reinterpret_cast<word_t>((uint64_t)9);
    data[2] = reinterpret_cast<word_t>((uint64_t)10);
    data[3] = reinterpret_cast<word_t>((uint64_t)11);
    data[4] = reinterpret_cast<word_t>((uint64_t)12);
    data[5] = reinterpret_cast<word_t>((uint64_t)13);
    data[6] = reinterpret_cast<word_t>((uint64_t)14);
    data[7] = reinterpret_cast<word_t>((uint64_t)15);
    
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16) + 63));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), 17));
        EXPECT_TRUE(acc0.testMem((i << 16) + 0, 9353140667429109160u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 8, 3986172086750404488u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 16, 4830430315410456921u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 24, 15361182515443724096u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 32, 16916331444984760130u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 40, 6964224425220918027u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 48, 10435931146297944966u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 56, 14358932127417561646u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 64, 18255571264526130024u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 72, 17238319086317252009u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 80, 3723291962817502950u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 88, 13627948362635124091u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 96, 4031926645569117068u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 104, 11245237017831209563u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 112, 2742477967011645575u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 120, 5147150731843503297u));
    }
}
TEST_F(movsbr_cycle, Basic_movsbr_cycle_14_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movsbr_cycle_14_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(72);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t *data = new word_t[numop];
    data[0] = reinterpret_cast<word_t>((uint64_t)8);
    data[1] = reinterpret_cast<word_t>((uint64_t)9);
    data[2] = reinterpret_cast<word_t>((uint64_t)10);
    data[3] = reinterpret_cast<word_t>((uint64_t)11);
    data[4] = reinterpret_cast<word_t>((uint64_t)12);
    data[5] = reinterpret_cast<word_t>((uint64_t)13);
    data[6] = reinterpret_cast<word_t>((uint64_t)14);
    data[7] = reinterpret_cast<word_t>((uint64_t)15);
    
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16) + 63));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), 5));
        EXPECT_TRUE(acc0.testMem((i << 16) + 0, 6192914923468644496u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 8, 3399235665267607987u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 16, 3562700421199697467u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 24, 15217105603774199082u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 32, 16546082778576626054u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 40, 4414961655251934823u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 48, 11932042141602399145u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 56, 13341205417114913527u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 64, 6223408571348487314u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 72, 7421950454601507657u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 80, 10358388319054258030u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 88, 13150075864825253192u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 96, 3954230822283776355u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 104, 328783812360778844u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 112, 13731408624008296506u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 120, 16546849146812586835u));
    }
}
TEST_F(movsbr_cycle, Basic_movsbr_cycle_15_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movsbr_cycle_15_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(72);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t *data = new word_t[numop];
    data[0] = reinterpret_cast<word_t>((uint64_t)8);
    data[1] = reinterpret_cast<word_t>((uint64_t)9);
    data[2] = reinterpret_cast<word_t>((uint64_t)10);
    data[3] = reinterpret_cast<word_t>((uint64_t)11);
    data[4] = reinterpret_cast<word_t>((uint64_t)12);
    data[5] = reinterpret_cast<word_t>((uint64_t)13);
    data[6] = reinterpret_cast<word_t>((uint64_t)14);
    data[7] = reinterpret_cast<word_t>((uint64_t)15);
    
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16) + 63));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), 115));
        EXPECT_TRUE(acc0.testMem((i << 16) + 0, 15173949038747029741u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 8, 7784826480682502068u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 16, 7675153094722900028u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 24, 10927237666821372198u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 32, 14351312203474347266u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 40, 12385739721889258295u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 48, 2516464357360466196u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 56, 14566749983374882285u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 64, 15649094994882169273u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 72, 13260707070757257349u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 80, 16094718915584501366u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 88, 9621121022773444934u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 96, 12264008403139491742u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 104, 17618319741347117752u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 112, 3539506336986925081u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 120, 18118676840503874640u));
    }
}
TEST_F(movsbr_cycle, Basic_movsbr_cycle_16_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movsbr_cycle_16_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(72);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t *data = new word_t[numop];
    data[0] = reinterpret_cast<word_t>((uint64_t)8);
    data[1] = reinterpret_cast<word_t>((uint64_t)9);
    data[2] = reinterpret_cast<word_t>((uint64_t)10);
    data[3] = reinterpret_cast<word_t>((uint64_t)11);
    data[4] = reinterpret_cast<word_t>((uint64_t)12);
    data[5] = reinterpret_cast<word_t>((uint64_t)13);
    data[6] = reinterpret_cast<word_t>((uint64_t)14);
    data[7] = reinterpret_cast<word_t>((uint64_t)15);
    
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16) + 63));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), 49));
        EXPECT_TRUE(acc0.testMem((i << 16) + 0, 16181186240003928896u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 8, 10399914594206936446u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 16, 1661952511390944816u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 24, 14809571790379564675u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 32, 6611650323998874088u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 40, 6895601235167115618u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 48, 17804706958648613086u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 56, 13515662797802073504u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 64, 2322490544074583224u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 72, 13499152017642921777u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 80, 2764893045562195942u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 88, 6979368034708457172u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 96, 2034630956299125823u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 104, 15671788282010067010u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 112, 16259983032032435931u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 120, 7998682462658717087u));
    }
}
TEST_F(movsbr_cycle, Basic_movsbr_cycle_17_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movsbr_cycle_17_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(72);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t *data = new word_t[numop];
    data[0] = reinterpret_cast<word_t>((uint64_t)8);
    data[1] = reinterpret_cast<word_t>((uint64_t)9);
    data[2] = reinterpret_cast<word_t>((uint64_t)10);
    data[3] = reinterpret_cast<word_t>((uint64_t)11);
    data[4] = reinterpret_cast<word_t>((uint64_t)12);
    data[5] = reinterpret_cast<word_t>((uint64_t)13);
    data[6] = reinterpret_cast<word_t>((uint64_t)14);
    data[7] = reinterpret_cast<word_t>((uint64_t)15);
    
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16) + 63));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), 38));
        EXPECT_TRUE(acc0.testMem((i << 16) + 0, 6450727798505207226u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 8, 3406697810252320062u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 16, 1551437987671070008u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 24, 4574558925645026326u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 32, 8769994841344862352u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 40, 17122179647664674281u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 48, 9220232778536505592u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 56, 2790597702552855004u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 64, 10548551824272671123u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 72, 14949860026970519311u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 80, 10948529460032295470u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 88, 8737623231673157002u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 96, 10717698701111091108u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 104, 8978954576952070319u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 112, 3843143882754381443u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 120, 166597992232935299u));
    }
}
TEST_F(movsbr_cycle, Basic_movsbr_cycle_18_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movsbr_cycle_18_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(72);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t *data = new word_t[numop];
    data[0] = reinterpret_cast<word_t>((uint64_t)8);
    data[1] = reinterpret_cast<word_t>((uint64_t)9);
    data[2] = reinterpret_cast<word_t>((uint64_t)10);
    data[3] = reinterpret_cast<word_t>((uint64_t)11);
    data[4] = reinterpret_cast<word_t>((uint64_t)12);
    data[5] = reinterpret_cast<word_t>((uint64_t)13);
    data[6] = reinterpret_cast<word_t>((uint64_t)14);
    data[7] = reinterpret_cast<word_t>((uint64_t)15);
    
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16) + 63));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), 6));
        EXPECT_TRUE(acc0.testMem((i << 16) + 0, 18049016692832506758u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 8, 15479427607888226324u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 16, 11390572456089852673u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 24, 8531900958149666769u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 32, 10850195393946937555u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 40, 11934050931976375764u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 48, 287937851189968465u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 56, 2479421241003496233u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 64, 141489407034557467u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 72, 14312591120798142645u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 80, 13881932734309437501u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 88, 1222862715418644787u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 96, 11120651507428072752u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 104, 7277190988230956543u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 112, 316520618904189373u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 120, 3252420247189224644u));
    }
}
TEST_F(movsbr_cycle, Basic_movsbr_cycle_19_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movsbr_cycle_19_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(72);
    ev0.setNumOperands(numop);
    operands_t op0(numop);
    word_t *data = new word_t[numop];
    data[0] = reinterpret_cast<word_t>((uint64_t)8);
    data[1] = reinterpret_cast<word_t>((uint64_t)9);
    data[2] = reinterpret_cast<word_t>((uint64_t)10);
    data[3] = reinterpret_cast<word_t>((uint64_t)11);
    data[4] = reinterpret_cast<word_t>((uint64_t)12);
    data[5] = reinterpret_cast<word_t>((uint64_t)13);
    data[6] = reinterpret_cast<word_t>((uint64_t)14);
    data[7] = reinterpret_cast<word_t>((uint64_t)15);
    
    op0.setData(data);
    eventoperands_t eops(&ev0, &op0);
    for(auto i = 0; i < numLanes; i++)
        acc0.pushEventOperands(eops, i);
    while(!acc0.isIdle()){
        acc0.simulate(2); // 2 is num stick
    }
    // Checks specific for tests being written
    for(auto i = 0; i < numLanes; i++){
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16) + 63));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), 42));
        EXPECT_TRUE(acc0.testMem((i << 16) + 0, 14976908479171189628u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 8, 4232748275391462919u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 16, 7950360579884927533u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 24, 6198292075189398860u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 32, 13712953025923584783u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 40, 3325096399800150326u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 48, 7832873503627957461u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 56, 3571835388567787963u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 64, 3080140869186463861u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 72, 1262376410477544579u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 80, 1655150613214050090u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 88, 5878104947905867367u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 96, 4675163826447387519u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 104, 8588475336690370344u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 112, 12652256054339147181u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 120, 7341789361877225918u));
    }
}
