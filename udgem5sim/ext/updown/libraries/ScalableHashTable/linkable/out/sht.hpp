#ifndef __sht_H__
#define __sht_H__

namespace sht {

    typedef unsigned int EventSymbol;

    constexpr EventSymbol SHT_initialize_TR = 0;
    constexpr EventSymbol SHT_finalize_TR = 1;
    constexpr EventSymbol SHT_update_TR = 2;
    constexpr EventSymbol SHT_get_TR = 3;
    constexpr EventSymbol SHT_get_iterators_TR = 4;
    constexpr EventSymbol SHTArrayBucket_initialize_TR = 5;
    constexpr EventSymbol SHTArrayBucket_update_TR = 6;
    constexpr EventSymbol SHTArrayBucket_get_TR = 7;
    constexpr EventSymbol SHTArrayBucket_get_next_TR = 8;
    constexpr EventSymbol SHTArrayBucket__update_TR_key_ld_ret = 9;
    constexpr EventSymbol SHTArrayBucket__update_TR_key_st_ret = 10;
    constexpr EventSymbol SHTArrayBucket__get_TR_key_ld_ret = 11;
    constexpr EventSymbol SHTArrayBucket__get_next_TR_entry_ld_ret = 12;
    constexpr EventSymbol SHT__initialize_TR_lane_init_ret = 13;
    constexpr EventSymbol SHT__get_iterators_TR_iter_st_ret = 14;

} // namespace

#endif