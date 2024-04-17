#include <gtest/gtest.h>
#include "udlane.hh"
#include "types.hh"
#include "lanetypes.hh"
#include "udaccelerator.hh"

using namespace basim;

class movlsb : public ::testing::Test {
 protected:
    size_t num_threads = 2;
    int numLanes = 64;
    UDAccelerator acc0 = UDAccelerator(numLanes, 0, 1); // UDAccelerator(numLanes, UDID/networkID, lmmode (0: accelerator based addressing, 1:bank/lane based addressing))
    int buffsize1 = 1024;
    int buffsize2 = 1024;
};
TEST_F(movlsb, Basic_movlsb_0_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movlsb_0_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(1092);
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
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), (i << 16) + 19));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16) + 19));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X18), (i << 16) + 128 + 64));
        EXPECT_TRUE(acc0.testMem((i << 16) + 128, 8222625761318613008u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 136, 1507916959288525948u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 144, 15328192309521608976u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 152, 13029110136283690218u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 160, 18000391300833368639u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 168, 8425909735331779439u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 176, 13574504411217657600u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 184, 1782933583763218434u));
    }
}
TEST_F(movlsb, Basic_movlsb_1_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movlsb_1_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(1092);
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
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), (i << 16) + 4));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16) + 4));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X18), (i << 16) + 128 + 64));
        EXPECT_TRUE(acc0.testMem((i << 16) + 128, 9819203490187142028u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 136, 7060779607740816322u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 144, 3023128832006827017u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 152, 13925857992237574207u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 160, 11714990014424547848u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 168, 17564698032076433808u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 176, 1022814394118826982u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 184, 12105554531411268796u));
    }
}
TEST_F(movlsb, Basic_movlsb_2_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movlsb_2_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(1092);
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
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), (i << 16) + 62));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16) + 62));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X18), (i << 16) + 128 + 64));
        EXPECT_TRUE(acc0.testMem((i << 16) + 128, 2883073906463075015u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 136, 7073646699764467981u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 144, 11682828565448405486u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 152, 8719457880739477810u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 160, 18116335459448399193u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 168, 7161410561290288306u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 176, 14721048012181571664u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 184, 4008410642472972761u));
    }
}
TEST_F(movlsb, Basic_movlsb_3_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movlsb_3_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(1092);
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
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), (i << 16) + 43));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16) + 43));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X18), (i << 16) + 128 + 64));
        EXPECT_TRUE(acc0.testMem((i << 16) + 128, 11713152220808136884u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 136, 13772950859847500207u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 144, 5841868355264736855u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 152, 1754564496616976458u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 160, 4364556340966898621u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 168, 17477098691787905233u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 176, 17044629330706118747u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 184, 1887930015725597945u));
    }
}
TEST_F(movlsb, Basic_movlsb_4_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movlsb_4_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(1092);
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
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), (i << 16) + 46));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16) + 46));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X18), (i << 16) + 128 + 64));
        EXPECT_TRUE(acc0.testMem((i << 16) + 128, 15104845396761734470u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 136, 3269372879485983268u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 144, 5938872562748563596u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 152, 17140184039074203290u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 160, 14588735202956954075u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 168, 3634138253806854189u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 176, 14025668645741442133u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 184, 11113163428987745742u));
    }
}
TEST_F(movlsb, Basic_movlsb_5_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movlsb_5_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(1092);
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
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), (i << 16) + 22));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16) + 22));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X18), (i << 16) + 128 + 64));
        EXPECT_TRUE(acc0.testMem((i << 16) + 128, 2538123997801160228u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 136, 6196019304244509997u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 144, 4770794354977678141u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 152, 12142566121721949052u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 160, 6305587468861000905u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 168, 11882432046338184659u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 176, 13820931994160063175u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 184, 12075916542300734849u));
    }
}
TEST_F(movlsb, Basic_movlsb_6_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movlsb_6_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(1092);
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
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), (i << 16) + 2));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16) + 2));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X18), (i << 16) + 128 + 64));
        EXPECT_TRUE(acc0.testMem((i << 16) + 128, 5606593041937814345u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 136, 8873148451886301340u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 144, 3886462578058819667u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 152, 14396135896631322446u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 160, 9845995528933000200u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 168, 12894685019420091544u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 176, 14280032379400200455u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 184, 13921639155240607120u));
    }
}
TEST_F(movlsb, Basic_movlsb_7_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movlsb_7_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(1092);
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
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), (i << 16) + 12));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16) + 12));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X18), (i << 16) + 128 + 64));
        EXPECT_TRUE(acc0.testMem((i << 16) + 128, 7923334056161436842u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 136, 3938473703710834059u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 144, 4906066354717122828u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 152, 4468554977383193947u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 160, 17965642767776388301u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 168, 16934121477930879823u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 176, 13927749212559261751u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 184, 11140969345752736314u));
    }
}
TEST_F(movlsb, Basic_movlsb_8_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movlsb_8_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(1092);
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
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), (i << 16) + 39));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16) + 39));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X18), (i << 16) + 128 + 64));
        EXPECT_TRUE(acc0.testMem((i << 16) + 128, 9299950452734801632u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 136, 5262570146814964836u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 144, 10571032656071917149u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 152, 3844033106187957427u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 160, 7870044806595064428u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 168, 14091431028695046840u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 176, 24419468258217238u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 184, 10459745312142020488u));
    }
}
TEST_F(movlsb, Basic_movlsb_9_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movlsb_9_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(1092);
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
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), (i << 16) + 27));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16) + 27));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X18), (i << 16) + 128 + 64));
        EXPECT_TRUE(acc0.testMem((i << 16) + 128, 17876231210338479521u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 136, 17834638442624350843u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 144, 10647847347794192183u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 152, 18249276108716550765u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 160, 7857641353076154336u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 168, 3619770457389165056u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 176, 2032205520262431371u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 184, 8131089591187372886u));
    }
}
TEST_F(movlsb, Basic_movlsb_10_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movlsb_10_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(1092);
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
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), (i << 16) + 31));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16) + 31));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X18), (i << 16) + 128 + 64));
        EXPECT_TRUE(acc0.testMem((i << 16) + 128, 5093319414580375212u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 136, 5767542260955137110u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 144, 6223893690134263340u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 152, 2452991933080719482u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 160, 16783671582331036673u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 168, 10460351334802776599u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 176, 7692162645621899302u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 184, 17920594597348869946u));
    }
}
TEST_F(movlsb, Basic_movlsb_11_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movlsb_11_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(1092);
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
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), (i << 16) + 38));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16) + 38));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X18), (i << 16) + 128 + 64));
        EXPECT_TRUE(acc0.testMem((i << 16) + 128, 6360131283313884797u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 136, 15900543755421998228u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 144, 788248544977331102u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 152, 7569006903958650469u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 160, 10679750709109901154u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 168, 470748740568528827u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 176, 10821964429223796243u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 184, 11938638659211704084u));
    }
}
TEST_F(movlsb, Basic_movlsb_12_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movlsb_12_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(1092);
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
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), (i << 16) + 45));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16) + 45));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X18), (i << 16) + 128 + 64));
        EXPECT_TRUE(acc0.testMem((i << 16) + 128, 631415787739830416u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 136, 8187531919774266842u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 144, 6238564738928506120u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 152, 3028266804999681156u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 160, 15142585766465499265u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 168, 4204204461000771024u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 176, 10402232822924070678u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 184, 11827920716198268435u));
    }
}
TEST_F(movlsb, Basic_movlsb_13_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movlsb_13_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(1092);
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
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), (i << 16) + 33));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16) + 33));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X18), (i << 16) + 128 + 64));
        EXPECT_TRUE(acc0.testMem((i << 16) + 128, 5815409588179922762u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 136, 11842646185907730296u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 144, 4183610986332709410u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 152, 6448555033388913045u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 160, 11401303019867452254u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 168, 7874843036771923673u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 176, 14147717029893459418u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 184, 8267136947029266866u));
    }
}
TEST_F(movlsb, Basic_movlsb_14_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movlsb_14_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(1092);
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
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), (i << 16) + 53));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16) + 53));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X18), (i << 16) + 128 + 64));
        EXPECT_TRUE(acc0.testMem((i << 16) + 128, 1510623644446186712u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 136, 12453365315423919486u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 144, 17567786823098664983u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 152, 13755018062440803364u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 160, 14322323667176276743u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 168, 249704075635777485u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 176, 9648660715440418531u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 184, 18285221716814541683u));
    }
}
TEST_F(movlsb, Basic_movlsb_15_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movlsb_15_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(1092);
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
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), (i << 16) + 26));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16) + 26));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X18), (i << 16) + 128 + 64));
        EXPECT_TRUE(acc0.testMem((i << 16) + 128, 12850848471109380360u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 136, 4917484763196322778u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 144, 12514303344889267339u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 152, 9064418127552918721u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 160, 4319728703923036424u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 168, 18072115437050987005u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 176, 10978651882708357946u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 184, 6259301297934799073u));
    }
}
TEST_F(movlsb, Basic_movlsb_16_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movlsb_16_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(1092);
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
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), (i << 16) + 49));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16) + 49));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X18), (i << 16) + 128 + 64));
        EXPECT_TRUE(acc0.testMem((i << 16) + 128, 2699316578973835521u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 136, 17718165599041803380u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 144, 9048781299645641318u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 152, 2228007505573588491u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 160, 6216271813522513761u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 168, 14535151752616378827u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 176, 5002663301671790104u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 184, 10236788301328136793u));
    }
}
TEST_F(movlsb, Basic_movlsb_17_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movlsb_17_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(1092);
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
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), (i << 16) + 49));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16) + 49));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X18), (i << 16) + 128 + 64));
        EXPECT_TRUE(acc0.testMem((i << 16) + 128, 8886205537547932468u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 136, 4927386600294181408u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 144, 6276524912775932040u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 152, 4746200693785169938u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 160, 4889405724609326046u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 168, 2725876235510445306u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 176, 11144383084983860315u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 184, 15566725052632799566u));
    }
}
TEST_F(movlsb, Basic_movlsb_18_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movlsb_18_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(1092);
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
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), (i << 16) + 13));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16) + 13));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X18), (i << 16) + 128 + 64));
        EXPECT_TRUE(acc0.testMem((i << 16) + 128, 7138710093640743935u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 136, 17106495752112939055u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 144, 9945952363924700099u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 152, 11720144100893157785u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 160, 8225453239841796364u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 168, 15052588722547519880u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 176, 472519408478977200u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 184, 14511424663434707736u));
    }
}
TEST_F(movlsb, Basic_movlsb_19_common_TX){
    acc0.initSetup(0, "testprogs/binaries/movlsb_19_common_TX.bin", 0);
    int numop = 8;
    eventword_t ev0(0);
    ev0.setEventLabel(1092);
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
        EXPECT_TRUE(acc0.testReg(i, (RegId::X16), (i << 16) + 3));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X17), (i << 16) + 3));
        EXPECT_TRUE(acc0.testReg(i, (RegId::X18), (i << 16) + 128 + 64));
        EXPECT_TRUE(acc0.testMem((i << 16) + 128, 13269153674955905151u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 136, 8516241748905643182u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 144, 9024444666523570244u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 152, 1822807261314978856u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 160, 11260736359106263614u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 168, 11046514745705481394u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 176, 14760161228759430743u));
        EXPECT_TRUE(acc0.testMem((i << 16) + 184, 16152635137100561685u));
    }
}
