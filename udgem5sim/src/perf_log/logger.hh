#ifndef __PERF_LOG_LOGGER_HH__
#define __PERF_LOG_LOGGER_HH__

#include "perf_log/protoio.hh"

#include "base/compiler.hh"
#include "base/types.hh"
#include "sim/cur_tick.hh"

#include <string>
#include <vector>
#include <utility>

using namespace gem5;

namespace PerfLog
{
void schedLogEvent(bool write, bool reset, Tick when = curTick(), Tick repeat = 0, uint32_t cpu_id = 0xFFFFFFFF, uint32_t msg_id = 0, std::string msg = "");

// void periodicLogWrite(Tick period = 0);

void updateLogEvents();

void openBasimPerflog(const std::string &filename);

void writeCpuBasimPerflog(uint32_t cpu_id, uint32_t msg_id, std::string msg_str);

void writeUpdownBasimPerflog(uint32_t network_id, uint32_t thread_id, // IDs
                                uint32_t event_label,     // event
                                uint32_t inc_exec_cycles, // incremental exec cycles
                                uint64_t total_exec_cycles, // total exec cycles
                                uint32_t msg_id, std::string &msg_str // message
);

// void openPerfLog(const std::string& filename);

void openTsvPerfLog(const std::string& filename);

// void writePerfLog();

// void writeEventPerfLog(uint32_t message_id, std::string message);

void writeTsvEventPerfLog(uint32_t cpu_id, uint32_t msg_id, std::string msg_str);

// void writePerfLogUpdown(uint32_t updown_id, uint32_t lane_id, uint32_t thread_id, // IDs
//                         uint32_t event_base, uint32_t event_label, // event
//                         bool en_msg, bool en_cycle, bool en_action, bool en_trans, bool en_queue, bool en_lm, bool en_dram, bool en_sys_dram,
//                         uint32_t msg_id, std::string msg_str, std::vector<std::pair<std::string, uint64_t>> msg_regs, // message
//                         uint32_t inc_exec_cycles,
//                         // uint32_t inc_idle_cycles,
//                         // uint32_t inc_num_sends,
//                         uint32_t inc_total_trans,
//                         uint32_t inc_total_acts, uint32_t inc_msg_acts, uint32_t inc_mov_acts, uint32_t inc_branch_acts,
//                         uint32_t inc_alu_acts, uint32_t inc_yld_acts, uint32_t inc_cmp_acts, uint32_t inc_cmpswp_acts,
//                         uint32_t operand_q_len, uint32_t event_q_len,
//                         uint32_t inc_lm_rd_bytes, uint32_t inc_lm_wr_bytes
//                         // uint32_t inc_dram_rd_bytes, uint32_t inc_dram_wr_bytes
//                         );

// void writePerfLogUpdownV2(uint32_t updown_id, uint32_t lane_id, uint32_t thread_id, // IDs
//                           uint32_t event_base, uint32_t event_label, // event
//                           bool en_msg, bool en_cycle, bool en_action, bool en_trans, bool en_queue, bool en_lm, bool en_dram, bool en_sys_dram,
//                           uint32_t msg_id, std::string msg_str, std::vector<std::pair<std::string, uint64_t>> msg_regs, // message
//                           uint32_t inc_exec_cycles,
//                           // uint32_t inc_idle_cycles,
//                           // uint32_t inc_num_sends,
//                           uint32_t inc_total_trans,
//                           uint32_t inc_total_acts, uint32_t inc_msg_acts, uint32_t inc_mov_acts, uint32_t inc_branch_acts,
//                           uint32_t inc_alu_acts, uint32_t inc_yld_acts, uint32_t inc_cmp_acts, uint32_t inc_cmpswp_acts,
//                           uint32_t operand_q_len, uint32_t event_q_len,
//                           uint32_t inc_lm_rd_bytes, uint32_t inc_lm_wr_bytes
//                           // uint32_t inc_dram_rd_bytes, uint32_t inc_dram_wr_bytes
//                           );

void writeTsvPerfLogUpdownEvent(uint32_t network_id, uint32_t thread_id, // IDs
                                uint32_t event_label,     // event
                                uint32_t inc_exec_cycles, // incremental exec cycles
                                uint64_t total_exec_cycles, // total exec cycles
                                uint32_t msg_id, std::string msg_str // message
                               );

// void closePerfLog();

void closeTsvPerfLog();
}

#endif // !__PERF_LOG_LOGGER_HH__
