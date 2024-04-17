include(GoogleTest)
include(CMakePrintHelpers)

include_directories(BEFORE
  ../common/include
  ../isa/include
  ../lane/include
  ../accel/include
  ../sim/include
)

add_library(UDAcceleratorStandAlone STATIC
            ../sim/src/basim.cpp
            )

target_link_libraries(UDAcceleratorStandAlone PRIVATE UDAcceleratorStatic)

add_executable(
  inst_unit_tests
  dev_inst_unit_tests/dev_inst_unit_tests.cpp
  inst_unit_tests/movil2_test.cpp
  inst_unit_tests/movil1_test.cpp
  inst_unit_tests/movrl_test.cpp
  inst_unit_tests/movlr_test.cpp
  inst_unit_tests/movwrl_test.cpp
  inst_unit_tests/movwlr_test.cpp
  inst_unit_tests/bcpyol_test.cpp
  inst_unit_tests/bcpyoli_test.cpp
  inst_unit_tests/cswp_test.cpp
  inst_unit_tests/cswpi_test.cpp
  inst_unit_tests/movrr_test.cpp
  inst_unit_tests/movir_test.cpp
  inst_unit_tests/swiz_test.cpp
  inst_unit_tests/sli_test.cpp
  inst_unit_tests/sri_test.cpp
  inst_unit_tests/slori_test.cpp
  inst_unit_tests/srori_test.cpp
  inst_unit_tests/slandi_test.cpp
  inst_unit_tests/srandi_test.cpp
  inst_unit_tests/slorii_test.cpp
  inst_unit_tests/srorii_test.cpp
  inst_unit_tests/slandii_test.cpp
  inst_unit_tests/srandii_test.cpp
  inst_unit_tests/sari_test.cpp
  inst_unit_tests/sr_test.cpp
  inst_unit_tests/sl_test.cpp
  inst_unit_tests/sar_test.cpp
  inst_unit_tests/andi_test.cpp
  inst_unit_tests/and_test.cpp
  inst_unit_tests/ori_test.cpp
  inst_unit_tests/or_test.cpp
  inst_unit_tests/xori_test.cpp
  inst_unit_tests/xor_test.cpp
  inst_unit_tests/addi_test.cpp
  inst_unit_tests/subi_test.cpp
  inst_unit_tests/muli_test.cpp
  inst_unit_tests/divi_test.cpp
  inst_unit_tests/modi_test.cpp
  inst_unit_tests/add_test.cpp
  inst_unit_tests/sub_test.cpp
  inst_unit_tests/mul_test.cpp
  inst_unit_tests/div_test.cpp
  inst_unit_tests/mod_test.cpp
  inst_unit_tests/sladdii_test.cpp
  inst_unit_tests/slsubii_test.cpp
  inst_unit_tests/sraddii_test.cpp
  inst_unit_tests/srsubii_test.cpp
  inst_unit_tests/send_test.cpp
  inst_unit_tests/sendops_test.cpp
  inst_unit_tests/sendr_test.cpp
  inst_unit_tests/sendr3_test.cpp
  inst_unit_tests/sendm_test.cpp
  inst_unit_tests/sendmops_test.cpp
  inst_unit_tests/sendmr_test.cpp
  inst_unit_tests/sendmr2_test.cpp
  inst_unit_tests/movipr_test.cpp
  inst_unit_tests/bcpyll_test.cpp
  inst_unit_tests/bcpylli_test.cpp
  inst_unit_tests/movbil_test.cpp
  inst_unit_tests/movblr_test.cpp
  inst_unit_tests/fmadd_64_test.cpp
  inst_unit_tests/fadd_64_test.cpp
  inst_unit_tests/fsub_64_test.cpp
  inst_unit_tests/fmul_64_test.cpp
  inst_unit_tests/fdiv_64_test.cpp
  inst_unit_tests/fsqrt_64_test.cpp
  inst_unit_tests/fmadd_32_test.cpp
  inst_unit_tests/fadd_32_test.cpp
  inst_unit_tests/fsub_32_test.cpp
  inst_unit_tests/fmul_32_test.cpp
  inst_unit_tests/fdiv_32_test.cpp
  inst_unit_tests/fsqrt_32_test.cpp
  inst_unit_tests/fmadd_b16_test.cpp
  inst_unit_tests/fadd_b16_test.cpp
  inst_unit_tests/fsub_b16_test.cpp
  inst_unit_tests/fmul_b16_test.cpp
  inst_unit_tests/fdiv_b16_test.cpp
  inst_unit_tests/fsqrt_b16_test.cpp
  inst_unit_tests/evi_test.cpp
  inst_unit_tests/evii_test.cpp
  inst_unit_tests/evlb_test.cpp
  inst_unit_tests/ev_test.cpp
  inst_unit_tests/hashl64_test.cpp
  inst_unit_tests/hashsb64_test.cpp
  inst_unit_tests/siw_test.cpp
  inst_unit_tests/refill_test.cpp
  inst_unit_tests/movlsb_test.cpp
  inst_unit_tests/movsbr_test.cpp
  inst_unit_tests/movsbr_cycle_test.cpp
  inst_unit_tests/ssprop_test.cpp
  inst_unit_tests/hash_test.cpp
  inst_unit_tests/fcnvt_i64_64_test.cpp
  inst_unit_tests/fcnvt_i32_32_test.cpp
  inst_unit_tests/fcnvt_64_i64_test.cpp
  inst_unit_tests/fcnvt_32_i32_test.cpp
  inst_unit_tests/fcnvt_64_32_test.cpp
  inst_unit_tests/fcnvt_64_b16_test.cpp
  inst_unit_tests/fcnvt_32_64_test.cpp
  inst_unit_tests/fcnvt_32_b16_test.cpp
  inst_unit_tests/fcnvt_b16_64_test.cpp
  inst_unit_tests/fcnvt_b16_32_test.cpp
  inst_unit_tests/cstr_test.cpp
  inst_unit_tests/ceq_test.cpp
  inst_unit_tests/ceqi_test.cpp
  inst_unit_tests/cgt_test.cpp
  inst_unit_tests/cgti_test.cpp
  inst_unit_tests/clt_test.cpp
  inst_unit_tests/clti_test.cpp
  inst_unit_tests/beq_test.cpp
  inst_unit_tests/beqi_test.cpp
  inst_unit_tests/bequ_test.cpp
  inst_unit_tests/beqiu_test.cpp
  inst_unit_tests/bgei_test.cpp
  inst_unit_tests/bgeiu_test.cpp
  inst_unit_tests/bgt_test.cpp
  inst_unit_tests/bgti_test.cpp
  inst_unit_tests/bgtiu_test.cpp
  inst_unit_tests/bgtu_test.cpp
  inst_unit_tests/ble_test.cpp
  inst_unit_tests/blei_test.cpp
  inst_unit_tests/bleiu_test.cpp
  inst_unit_tests/bleu_test.cpp
  inst_unit_tests/blti_test.cpp
  inst_unit_tests/bltiu_test.cpp
  inst_unit_tests/bne_test.cpp
  inst_unit_tests/bnei_test.cpp
  inst_unit_tests/bneiu_test.cpp
  inst_unit_tests/bneu_test.cpp
  inst_unit_tests/jmp_test.cpp
  inst_unit_tests/hashl_test.cpp
  inst_unit_tests/vmadd_32_test.cpp
  inst_unit_tests/vadd_32_test.cpp
  inst_unit_tests/vsub_32_test.cpp
  inst_unit_tests/vmul_32_test.cpp
  inst_unit_tests/vdiv_32_test.cpp
  inst_unit_tests/vsqrt_32_test.cpp
  inst_unit_tests/vfill_32_test.cpp
  inst_unit_tests/vmadd_b16_test.cpp
  inst_unit_tests/vadd_b16_test.cpp
  inst_unit_tests/vsub_b16_test.cpp
  inst_unit_tests/vmul_b16_test.cpp
  inst_unit_tests/vdiv_b16_test.cpp
  inst_unit_tests/vsqrt_b16_test.cpp
  inst_unit_tests/vfill_b16_test.cpp
  inst_unit_tests/vmadd_i32_test.cpp
  inst_unit_tests/vadd_i32_test.cpp
  inst_unit_tests/vsub_i32_test.cpp
  inst_unit_tests/vmul_i32_test.cpp
  inst_unit_tests/vdiv_i32_test.cpp
  inst_unit_tests/vsqrt_i32_test.cpp    
  inst_unit_tests/vfill_i32_test.cpp
  inst_unit_tests/vgt_i32_test.cpp
  inst_unit_tests/vgt_32_test.cpp
  inst_unit_tests/vgt_b16_test.cpp
  inst_unit_tests/print_test.cpp
  inst_unit_tests/commonTX.cpp
  inst_unit_tests/flagTX.cpp
  inst_unit_tests/epsilonTX.cpp
  inst_unit_tests/refillTX.cpp
)

add_executable(
  vector_seq_tests
  dev_inst_unit_tests/dev_inst_unit_tests.cpp
  vector_seq_tests/vseq_i32_test.cpp
  vector_seq_tests/vseq_32_test.cpp
  vector_seq_tests/vseq_b16_test.cpp
)

add_executable(
  dev_inst_unit_tests
  dev_inst_unit_tests/dev_inst_unit_tests.cpp
  dev_inst_unit_tests/addi_test.cpp
  dev_inst_unit_tests/subi_test.cpp
  dev_inst_unit_tests/muli_test.cpp
  dev_inst_unit_tests/divi_test.cpp
  dev_inst_unit_tests/modi_test.cpp
  dev_inst_unit_tests/add_test.cpp
  dev_inst_unit_tests/sub_test.cpp
  dev_inst_unit_tests/mul_test.cpp
  dev_inst_unit_tests/div_test.cpp
  dev_inst_unit_tests/mod_test.cpp
  dev_inst_unit_tests/clti_test.cpp
  dev_inst_unit_tests/cgti_test.cpp
  dev_inst_unit_tests/ceqi_test.cpp
  dev_inst_unit_tests/clt_test.cpp
  dev_inst_unit_tests/cgt_test.cpp
  dev_inst_unit_tests/ceq_test.cpp
  dev_inst_unit_tests/andi_test.cpp
  dev_inst_unit_tests/ori_test.cpp
  dev_inst_unit_tests/xori_test.cpp
  dev_inst_unit_tests/and_test.cpp
  dev_inst_unit_tests/or_test.cpp
  dev_inst_unit_tests/xor_test.cpp
  dev_inst_unit_tests/sli_test.cpp
  dev_inst_unit_tests/sri_test.cpp
  dev_inst_unit_tests/sari_test.cpp
  dev_inst_unit_tests/sl_test.cpp
  dev_inst_unit_tests/sr_test.cpp
  dev_inst_unit_tests/sar_test.cpp
  dev_inst_unit_tests/slori_test.cpp
  dev_inst_unit_tests/srori_test.cpp
  dev_inst_unit_tests/movrr_test.cpp
  dev_inst_unit_tests/sladdii_test.cpp
  dev_inst_unit_tests/sraddii_test.cpp
  dev_inst_unit_tests/srsubii_test.cpp
  dev_inst_unit_tests/slsubii_test.cpp
  dev_inst_unit_tests/bcpyol_test.cpp
  dev_inst_unit_tests/slorii_test.cpp
  dev_inst_unit_tests/slandi_test.cpp
  dev_inst_unit_tests/srandi_test.cpp
  dev_inst_unit_tests/slandii_test.cpp
  dev_inst_unit_tests/srandii_test.cpp
  dev_inst_unit_tests/srorii_test.cpp
  dev_inst_unit_tests/bne_test.cpp
  dev_inst_unit_tests/beq_test.cpp
  dev_inst_unit_tests/bgt_test.cpp
  dev_inst_unit_tests/ble_test.cpp
  dev_inst_unit_tests/bneu_test.cpp
  dev_inst_unit_tests/bequ_test.cpp
  dev_inst_unit_tests/bgtu_test.cpp
  dev_inst_unit_tests/bleu_test.cpp
  dev_inst_unit_tests/bnei_test.cpp
  dev_inst_unit_tests/beqi_test.cpp
  dev_inst_unit_tests/bgti_test.cpp
  dev_inst_unit_tests/blei_test.cpp
  dev_inst_unit_tests/blti_test.cpp
  dev_inst_unit_tests/bgei_test.cpp
  dev_inst_unit_tests/bneiu_test.cpp
  dev_inst_unit_tests/beqiu_test.cpp
  dev_inst_unit_tests/bgtiu_test.cpp
  dev_inst_unit_tests/bleiu_test.cpp
  dev_inst_unit_tests/bltiu_test.cpp
  dev_inst_unit_tests/bgeiu_test.cpp
  dev_inst_unit_tests/jmp_test.cpp
  dev_inst_unit_tests/ev_test.cpp
  dev_inst_unit_tests/movipr_test.cpp
  dev_inst_unit_tests/bcpyll_test.cpp
  dev_inst_unit_tests/bcpylli_test.cpp
  dev_inst_unit_tests/movil2_test.cpp
  dev_inst_unit_tests/movil1_test.cpp
  dev_inst_unit_tests/siw_test.cpp
  dev_inst_unit_tests/refill_test.cpp
  dev_inst_unit_tests/cswp_test.cpp
  dev_inst_unit_tests/cswpi_test.cpp
  dev_inst_unit_tests/swiz_test.cpp
  dev_inst_unit_tests/hash_test.cpp
  dev_inst_unit_tests/hashl64_test.cpp
  dev_inst_unit_tests/hashl_test.cpp
  dev_inst_unit_tests/ssprop_test.cpp
  dev_inst_unit_tests/fadd_test.cpp
  dev_inst_unit_tests/hashsb64_test.cpp
  dev_inst_unit_tests/hashsb32_test.cpp
  dev_inst_unit_tests/vgt_32_test.cpp
  dev_inst_unit_tests/vgt_b16_test.cpp
  dev_inst_unit_tests/vgt_i32_test.cpp
  dev_inst_unit_tests/vfill_32_test.cpp
  dev_inst_unit_tests/vfill_b16_test.cpp
  dev_inst_unit_tests/vfill_i32_test.cpp
  dev_inst_unit_tests/fcnvt_64_i64_test.cpp
  dev_inst_unit_tests/fcnvt_32_i32_test.cpp
  dev_inst_unit_tests/fcnvt_i64_64_test.cpp
  dev_inst_unit_tests/fcnvt_i32_32_test.cpp
  dev_inst_unit_tests/fcnvt_64_32_test.cpp
  dev_inst_unit_tests/fcnvt_64_b16_test.cpp
  dev_inst_unit_tests/fcnvt_32_64_test.cpp
  dev_inst_unit_tests/fcnvt_32_b16_test.cpp
  dev_inst_unit_tests/fcnvt_b16_64_test.cpp
  dev_inst_unit_tests/fcnvt_b16_32_test.cpp
)

add_executable(
  control_seq_tests
  dev_inst_unit_tests/dev_inst_unit_tests.cpp
  control_seq_tests/dijkstra_test.cpp
  control_seq_tests/fibonacci_test.cpp
)

add_executable(
  multi_thread_seq_tests
  dev_inst_unit_tests/dev_inst_unit_tests.cpp
  multi_thread_seq_tests/inter_lane_comm_test.cpp
)

add_executable(
  trans_unit_tests
  dev_inst_unit_tests/dev_inst_unit_tests.cpp
  trans_unit_tests/common_action_TX_test.cpp
  trans_unit_tests/common_action_TX_maxSBP_test.cpp
  trans_unit_tests/common_noaction_TX_test.cpp
  trans_unit_tests/common_noaction_TX_maxSBP_test.cpp
  trans_unit_tests/epsilon_action_TX_test.cpp
  trans_unit_tests/epsilon_noaction_TX_test.cpp
  trans_unit_tests/basic_action_TX_test.cpp
  trans_unit_tests/basic_action1_without_lastact_TX_test.cpp
  trans_unit_tests/basic_action2_without_lastact_TX_test.cpp
  trans_unit_tests/basic_action4_without_lastact_TX_test.cpp
  trans_unit_tests/basic_action8_without_lastact_TX_test.cpp
  trans_unit_tests/basic_action1_with_lastact_TX_test.cpp
  trans_unit_tests/basic_action2_with_lastact_TX_test.cpp
  trans_unit_tests/basic_action4_with_lastact_TX_test.cpp
  trans_unit_tests/basic_action8_with_lastact_TX_test.cpp
  trans_unit_tests/basic_action_TX_maxSBP_test.cpp
  trans_unit_tests/basic_action1_with_lastact_TX_maxSBP_test.cpp
  trans_unit_tests/basic_action2_with_lastact_TX_maxSBP_test.cpp
  trans_unit_tests/basic_action4_with_lastact_TX_maxSBP_test.cpp
  trans_unit_tests/basic_action8_with_lastact_TX_maxSBP_test.cpp
  trans_unit_tests/basic_noaction1_with_lastact_TX_test.cpp
  trans_unit_tests/basic_noaction2_with_lastact_TX_test.cpp
  trans_unit_tests/basic_noaction4_with_lastact_TX_test.cpp
  trans_unit_tests/basic_noaction8_with_lastact_TX_test.cpp
  trans_unit_tests/basic_noaction1_with_lastact_TX_maxSBP_test.cpp
  trans_unit_tests/basic_noaction2_with_lastact_TX_maxSBP_test.cpp
  trans_unit_tests/basic_noaction4_with_lastact_TX_maxSBP_test.cpp
  trans_unit_tests/basic_noaction8_with_lastact_TX_maxSBP_test.cpp
  trans_unit_tests/flag_action1_with_lastact_TX_test.cpp
  trans_unit_tests/flag_action2_with_lastact_TX_test.cpp
  trans_unit_tests/flag_action4_with_lastact_TX_test.cpp
  trans_unit_tests/flag_action8_with_lastact_TX_test.cpp
  trans_unit_tests/flag_noaction1_with_lastact_TX_test.cpp
  trans_unit_tests/flag_noaction2_with_lastact_TX_test.cpp
  trans_unit_tests/flag_noaction4_with_lastact_TX_test.cpp
  trans_unit_tests/flag_noaction8_with_lastact_TX_test.cpp
  trans_unit_tests/common_event_common_TX_test.cpp
  trans_unit_tests/refill_TX_test.cpp
  trans_unit_tests/refill_noaction_TX_test.cpp
  trans_unit_tests/SB_automatic_refill_TX_test.cpp
  trans_unit_tests/common_event_common_TX_maxSBP_test.cpp
)

# add_executable(
#   func_seq_tests
#   dev_inst_unit_tests/dev_inst_unit_tests.cpp
#   func_seq_tests/sht_seq_tests.cpp
# )

add_executable(
  print_tests
  dev_inst_unit_tests/dev_inst_unit_tests.cpp
  print_tests/print_tests.cpp
)

target_compile_features(trans_unit_tests PRIVATE cxx_std_17)

target_link_libraries(trans_unit_tests PRIVATE gtest UDAcceleratorStandAlone)

gtest_add_tests(trans_unit_tests NULL AUTO)

# target_compile_features(func_seq_tests PRIVATE cxx_std_17)

# target_link_libraries(func_seq_tests PRIVATE gtest UDAcceleratorStandAlone)

# gtest_add_tests(func_seq_tests NULL AUTO)

target_compile_features(print_tests PRIVATE cxx_std_17)

target_link_libraries(print_tests PRIVATE gtest UDAcceleratorStandAlone)

gtest_add_tests(print_tests NULL AUTO)

target_compile_features(vector_seq_tests PRIVATE cxx_std_17)

target_link_libraries(vector_seq_tests PRIVATE gtest UDAcceleratorStandAlone)

gtest_add_tests(vector_seq_tests NULL AUTO)


target_compile_features(inst_unit_tests PRIVATE cxx_std_17)

target_link_libraries(inst_unit_tests PRIVATE gtest UDAcceleratorStandAlone)

gtest_add_tests(inst_unit_tests NULL AUTO)

target_compile_features(dev_inst_unit_tests PRIVATE cxx_std_17)

target_link_libraries(dev_inst_unit_tests PRIVATE gtest UDAcceleratorStandAlone)

gtest_add_tests(dev_inst_unit_tests NULL AUTO)


target_compile_features(control_seq_tests PRIVATE cxx_std_17)

target_link_libraries(control_seq_tests PRIVATE gtest UDAcceleratorStandAlone)

gtest_add_tests(control_seq_tests NULL AUTO)


target_compile_features(multi_thread_seq_tests PRIVATE cxx_std_17)

target_link_libraries(multi_thread_seq_tests PRIVATE gtest UDAcceleratorStandAlone)

gtest_add_tests(multi_thread_seq_tests NULL AUTO)

