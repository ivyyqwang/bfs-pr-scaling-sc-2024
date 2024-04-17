#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"

using namespace basim;

class movsbr : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    int numLanes = 64;
    UDAccelerator acc0 = UDAccelerator(numLanes, 0, 1); // UDAccelerator(numLanes, UDID/networkID, lmmode (0: accelerator based addressing, 1:bank/lane based addressing))
    int buffsize1 = 1024;
    int buffsize2 = 1024;
};
TEST_F(movsbr, Basic_movsbr_0_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movsbr_0_common_TX.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), 0));
        EXPECT_TRUE(acc0.testMem((i << 16) + 0, 17725451227879275441u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 8, 1424457896458504161u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 16, 6438186643708224272u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 24, 9122040428459116078u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 32, 8012918337815350531u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 40, 6212199982969995997u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 48, 487873627579446368u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 56, 17359820209714493070u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 64, 11309251274969719741u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 72, 16129434873033211033u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 80, 377254664443122440u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 88, 14953803113359032964u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 96, 1880367203049771125u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 104, 16484617993008682948u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 112, 8785577258008471640u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 120, 12075273089494560301u));
    }
}
TEST_F(movsbr, Basic_movsbr_1_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movsbr_1_common_TX.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), 8));
        EXPECT_TRUE(acc0.testMem((i << 16) + 0, 13133768084753274643u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 8, 2232818645442308215u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 16, 6830493057212418076u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 24, 17134566793446019194u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 32, 17766308488778685049u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 40, 12154157738656534009u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 48, 651263256268739346u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 56, 5441762462940800258u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 64, 15400984153694318754u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 72, 469180476097223795u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 80, 17197994130943140100u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 88, 16249547392841190992u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 96, 5891939016733696223u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 104, 3516114540348158025u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 112, 7476269300966905297u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 120, 7706861474438358777u));
    }
}
TEST_F(movsbr, Basic_movsbr_2_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movsbr_2_common_TX.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), 75));
        EXPECT_TRUE(acc0.testMem((i << 16) + 0, 10112779883647217805u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 8, 6355341640861643476u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 16, 14744814085090750561u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 24, 15838687425808752791u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 32, 4038694506554700391u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 40, 9017319860048968994u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 48, 4825157274698414285u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 56, 9747615607397737899u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 64, 2764483044023827426u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 72, 989398115327902913u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 80, 3060788678071614595u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 88, 9010348090651435757u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 96, 14148243313545358697u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 104, 8766297647126730063u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 112, 12211429192495061641u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 120, 6189618613540361063u));
    }
}
TEST_F(movsbr, Basic_movsbr_3_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movsbr_3_common_TX.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), 23));
        EXPECT_TRUE(acc0.testMem((i << 16) + 0, 10443687967518447333u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 8, 17006437195675126132u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 16, 4183920567317794607u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 24, 14624685910983514944u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 32, 9592849891906882508u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 40, 8367979373210433958u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 48, 15334313217365600226u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 56, 2088170214444453848u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 64, 13163214512667799979u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 72, 7936619916286247703u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 80, 17588760850383437650u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 88, 17064508586909236590u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 96, 10266213402633638317u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 104, 16141844095962866354u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 112, 4476140755815693104u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 120, 3537791387753666224u));
    }
}
TEST_F(movsbr, Basic_movsbr_4_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movsbr_4_common_TX.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), 40));
        EXPECT_TRUE(acc0.testMem((i << 16) + 0, 5037631316850630937u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 8, 10942984872130688447u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 16, 16542703895286308700u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 24, 8573840975888160812u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 32, 1244986793328575661u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 40, 17068489503217978u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 48, 6460596691263256156u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 56, 3131180456921247765u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 64, 9386704458592217787u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 72, 17357625199992900939u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 80, 11272798903925123258u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 88, 9285095096246767442u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 96, 1624130205817837362u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 104, 18165808894237278280u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 112, 6685629872548568741u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 120, 8104717683387545895u));
    }
}
TEST_F(movsbr, Basic_movsbr_5_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movsbr_5_common_TX.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), 3));
        EXPECT_TRUE(acc0.testMem((i << 16) + 0, 12101432619042712843u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 8, 1598118723489036915u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 16, 12833480150309823165u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 24, 1610770143418165046u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 32, 3982712469249537979u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 40, 2375217644404968731u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 48, 13628676512575980446u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 56, 8497492380817270658u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 64, 287712342709480386u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 72, 8655715039621446679u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 80, 21454746431042362u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 88, 3673113521469807771u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 96, 8361314857289984940u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 104, 8617748707224276932u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 112, 3070942246442767123u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 120, 14706443348929845625u));
    }
}
TEST_F(movsbr, Basic_movsbr_6_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movsbr_6_common_TX.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), 3));
        EXPECT_TRUE(acc0.testMem((i << 16) + 0, 11313044272820118251u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 8, 16980699151720586618u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 16, 15668323718953333502u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 24, 6446702745872368496u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 32, 3027197372893732466u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 40, 15477728580663064369u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 48, 16597094782700842965u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 56, 16216395075230937918u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 64, 18043420381956814378u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 72, 15098512045263394172u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 80, 7093020301039910740u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 88, 3928221722031500868u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 96, 2885054675951592282u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 104, 12583907593290803671u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 112, 3712703896100276658u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 120, 5929792831080206547u));
    }
}
TEST_F(movsbr, Basic_movsbr_7_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movsbr_7_common_TX.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), 106));
        EXPECT_TRUE(acc0.testMem((i << 16) + 0, 4178663749268165982u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 8, 15748638053104765821u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 16, 3550140879488553571u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 24, 16677454316710364745u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 32, 4453888384030798760u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 40, 16806534998620777707u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 48, 296540107123301056u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 56, 7816327652944170767u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 64, 6843349265746603536u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 72, 958591725192785440u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 80, 14707382663058947866u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 88, 14230344267895753410u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 96, 7024011913559950040u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 104, 8322995565720199234u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 112, 9942748405990053626u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 120, 8857184843925257281u));
    }
}
TEST_F(movsbr, Basic_movsbr_8_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movsbr_8_common_TX.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), 8));
        EXPECT_TRUE(acc0.testMem((i << 16) + 0, 3178534253405965830u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 8, 10710759862407954768u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 16, 9001822234624101682u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 24, 7299662228525391627u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 32, 13459583933038871985u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 40, 5933306723920370893u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 48, 10185163395735027480u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 56, 14535776709698988268u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 64, 15002457690351426402u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 72, 1466725999905563648u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 80, 5443318750215024475u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 88, 2681621766577162037u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 96, 14287787572028317003u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 104, 11665467605594014911u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 112, 2951645389863123378u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 120, 10335427859123819485u));
    }
}
TEST_F(movsbr, Basic_movsbr_9_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movsbr_9_common_TX.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), 5));
        EXPECT_TRUE(acc0.testMem((i << 16) + 0, 10625238204293722289u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 8, 16888375379974296971u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 16, 10282488737735179791u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 24, 18157218135632491952u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 32, 6106144611138973686u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 40, 10309835254841467778u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 48, 6570287679600154022u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 56, 6682356724398887948u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 64, 7006522376973033228u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 72, 16491601535719078458u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 80, 16720731539994899018u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 88, 11586524842202397390u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 96, 13469180378464575238u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 104, 17960077579465439568u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 112, 18289519845133885033u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 120, 8946120751561715664u));
    }
}
TEST_F(movsbr, Basic_movsbr_10_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movsbr_10_common_TX.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), 62));
        EXPECT_TRUE(acc0.testMem((i << 16) + 0, 16101238652667215805u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 8, 8131451267373656220u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 16, 14049982059518880957u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 24, 17480174976083494424u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 32, 4490573743380080742u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 40, 1619324366831923272u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 48, 13592074892826389964u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 56, 17524707658921677042u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 64, 2980566219768473031u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 72, 8478937022881904365u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 80, 11217946300477603218u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 88, 17410583798855275119u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 96, 9500649060654296814u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 104, 15628017289974241734u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 112, 5517701922076597046u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 120, 677005069424419572u));
    }
}
TEST_F(movsbr, Basic_movsbr_11_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movsbr_11_common_TX.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), 5));
        EXPECT_TRUE(acc0.testMem((i << 16) + 0, 9570270537272472010u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 8, 6615801007898134009u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 16, 6168506897058953081u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 24, 5970415719440182857u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 32, 7269374912991574860u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 40, 1471110911851823269u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 48, 17082292782794424387u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 56, 4195873461520092519u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 64, 6764167822609413910u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 72, 16282349552164992344u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 80, 2508101500548136922u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 88, 1017219700905822772u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 96, 11242576056167302369u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 104, 16278476519892158991u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 112, 2610097498905638319u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 120, 13994946868211163310u));
    }
}
TEST_F(movsbr, Basic_movsbr_12_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movsbr_12_common_TX.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), 1));
        EXPECT_TRUE(acc0.testMem((i << 16) + 0, 16176274940005784324u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 8, 11646289724399411860u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 16, 10827500027659668566u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 24, 15433461211769484383u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 32, 1033755242873380384u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 40, 15674585651759536495u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 48, 11751319120116130153u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 56, 2383287000112229143u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 64, 4149286351221386949u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 72, 12838588629101583427u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 80, 9199134614946125661u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 88, 14724024160082931992u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 96, 11724634171552594420u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 104, 3606699484822322629u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 112, 8783927311641301336u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 120, 11964716980858011230u));
    }
}
TEST_F(movsbr, Basic_movsbr_13_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movsbr_13_common_TX.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), 4));
        EXPECT_TRUE(acc0.testMem((i << 16) + 0, 11598136397342790624u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 8, 2758223495458138597u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 16, 12421186532975932245u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 24, 11576708125639364145u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 32, 141406658654607042u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 40, 16623471619243379291u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 48, 17488193876631373227u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 56, 15298959098474885782u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 64, 10614770612820929195u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 72, 15701733499046758065u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 80, 13395844226371755078u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 88, 17952504113807400602u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 96, 11744327766312939776u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 104, 16117928048716619708u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 112, 11177801646012978921u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 120, 3914334425994881161u));
    }
}
TEST_F(movsbr, Basic_movsbr_14_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movsbr_14_common_TX.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), 0));
        EXPECT_TRUE(acc0.testMem((i << 16) + 0, 2235061334230742866u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 8, 6592454346784223017u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 16, 5600351128695967217u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 24, 12847168136649970887u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 32, 14633833273918347723u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 40, 724343750948653562u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 48, 9883833841732829858u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 56, 16370706611085385478u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 64, 190136456045355336u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 72, 616277076284558266u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 80, 3818036460296290681u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 88, 5502321821532032560u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 96, 14541266496362607892u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 104, 15909205194023056752u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 112, 4011337562551477897u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 120, 3078162408003578404u));
    }
}
TEST_F(movsbr, Basic_movsbr_15_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movsbr_15_common_TX.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), 63));
        EXPECT_TRUE(acc0.testMem((i << 16) + 0, 13384848024093293007u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 8, 2130313787265953629u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 16, 15149554335620184717u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 24, 12023912530780069899u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 32, 17322556511154191934u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 40, 2348324130363425054u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 48, 5787177331998868868u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 56, 17255409819536300771u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 64, 10160039594889308859u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 72, 470693436075506793u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 80, 11808579291530429792u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 88, 14543949458535479805u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 96, 3007773525408958141u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 104, 2268357040128971157u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 112, 14484014168343941037u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 120, 17624188162908537057u));
    }
}
TEST_F(movsbr, Basic_movsbr_16_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movsbr_16_common_TX.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), 6));
        EXPECT_TRUE(acc0.testMem((i << 16) + 0, 10554029250114990179u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 8, 14509775484670402719u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 16, 1157676750006150083u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 24, 17761824720319803866u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 32, 18113778830054380838u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 40, 3406874914128572807u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 48, 11814181459863199897u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 56, 9548824760532957850u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 64, 11636981147754975802u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 72, 10877071203377646562u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 80, 2877717575241149357u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 88, 5938776337654707733u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 96, 6379101640483961120u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 104, 16023534584344067488u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 112, 11260551562102555539u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 120, 15146839721392447333u));
    }
}
TEST_F(movsbr, Basic_movsbr_17_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movsbr_17_common_TX.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), 15));
        EXPECT_TRUE(acc0.testMem((i << 16) + 0, 8256326086900331595u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 8, 17195365117465233395u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 16, 17773465879654396939u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 24, 10890857526337366444u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 32, 16131939995317387331u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 40, 6840566041927750448u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 48, 371254208849450698u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 56, 12200516692235480875u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 64, 6511220587006482616u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 72, 6021800361483258931u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 80, 16400306044278214603u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 88, 1969871586399321937u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 96, 13202612118707660826u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 104, 12591992913140898584u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 112, 14991192618748471987u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 120, 12401603309967943555u));
    }
}
TEST_F(movsbr, Basic_movsbr_18_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movsbr_18_common_TX.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), 0));
        EXPECT_TRUE(acc0.testMem((i << 16) + 0, 2787269694862547695u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 8, 1297603884267002893u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 16, 10372965160837005844u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 24, 7466091547254946211u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 32, 14172054202281548909u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 40, 4320485982168947684u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 48, 2418541881343584443u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 56, 5585876511885390062u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 64, 12045281505323233490u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 72, 8903349672894493227u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 80, 9674782303944855362u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 88, 7439977373954683434u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 96, 9024061272722653728u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 104, 15219295252023273854u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 112, 16560501198459422432u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 120, 6955803560081719728u));
    }
}
TEST_F(movsbr, Basic_movsbr_19_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movsbr_19_common_TX.bin", 0);
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
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16)));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), 13));
        EXPECT_TRUE(acc0.testMem((i << 16) + 0, 18072978970659189668u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 8, 5203548489635325846u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 16, 13333678751374652551u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 24, 1117196750866328500u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 32, 16249113632428186345u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 40, 14726665990490278739u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 48, 6947568789659564662u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 56, 15933879054449836163u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 64, 16724355868291326230u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 72, 18342620097570070220u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 80, 2228012910617248931u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 88, 12501527390564284824u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 96, 3501762273704229314u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 104, 4720903258058302918u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 112, 14116651225947861333u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 120, 5971697379972769906u));
    }
}
