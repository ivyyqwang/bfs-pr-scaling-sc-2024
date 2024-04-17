#ifndef __sht_concurrency_test_out_H__
#define __sht_concurrency_test_out_H__

namespace sht_concurrency_test_out {

    typedef unsigned int EventSymbol;

    constexpr EventSymbol entry_init = 0;
    constexpr EventSymbol gather_0 = 1;
    constexpr EventSymbol gather_1 = 2;
    constexpr EventSymbol gather_2 = 3;
    constexpr EventSymbol gather_3 = 4;
    constexpr EventSymbol gather_4 = 5;
    constexpr EventSymbol gather_5 = 6;
    constexpr EventSymbol gather_6 = 7;
    constexpr EventSymbol gather_7 = 8;
    constexpr EventSymbol gather_8 = 9;
    constexpr EventSymbol gather_9 = 10;
    constexpr EventSymbol gather_10 = 11;
    constexpr EventSymbol gather_11 = 12;
    constexpr EventSymbol desc_replicate = 13;
    constexpr EventSymbol update_send = 14;
    constexpr EventSymbol update_receive = 15;
    constexpr EventSymbol get_send = 16;
    constexpr EventSymbol get_receive = 17;
    constexpr EventSymbol delete_send = 18;
    constexpr EventSymbol delete_receive = 19;
    constexpr EventSymbol SHTArrayBucket__initialize_TR = 20;
    constexpr EventSymbol SHTArrayBucket__update_TR = 21;
    constexpr EventSymbol SHTArrayBucket__update_TR_key_ld_ret = 22;
    constexpr EventSymbol SHTArrayBucket__update_TR_key_st_ret = 23;
    constexpr EventSymbol SHTArrayBucket__get_TR = 24;
    constexpr EventSymbol SHTArrayBucket__get_TR_key_ld_ret = 25;
    constexpr EventSymbol SHT__initialize_TR = 26;
    constexpr EventSymbol SHT__initialize_TR_lane_init_ret = 27;
    constexpr EventSymbol SHT__finalize_TR = 28;
    constexpr EventSymbol SHT__update_TR = 29;
    constexpr EventSymbol SHT__get_TR = 30;

} // namespace

#endif