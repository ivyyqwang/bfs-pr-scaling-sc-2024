#include "perf_log/logger.hh"
#include "base/callback.hh"
#include "base/statistics.hh"
#include "base/stats/types.hh"
#include "base/time.hh"
#include "sim/core.hh"
#include "sim/cur_tick.hh"
#include "sim/global_event.hh"
#include "sim/root.hh"
#include "updown/simruntime/include/upstream_pyintf.hh"
#include "updown_obj/updown_obj.hh"
#include "logging.hh"
// #include "perf_log/proto/perf_log_packet.pb.h"
// #include "perf_log/proto/perf_log_packet_v2.pb.h"
// #include "proto/packet.pb.h"

#include <cstdint>
#include <cstdio>

using namespace gem5;

namespace PerfLog {

GlobalEvent *logEvent;
Tick lastTick = 0;
bool multi_cpu = false;
bool multi_updown = false;
uint64_t updown_period = 0;

// PerfLog::ProtoOutputStream *logStream;
// std::string perfLogFilename;
// bool newPerfLog;

std::FILE *tsvLogFp = nullptr;
std::string perfLogTsvFilename;
bool newTsvPerfLog;

class LogEvent : public GlobalEvent {
private:
  bool write;
  bool reset;
  Tick repeat;
  uint32_t cpu_id;
  uint32_t msg_id;
  std::string msg;

public:
  LogEvent(Tick _when, bool _write, bool _reset, Tick _repeat, uint32_t _cpu_id, uint32_t _msg_id, std::string _msg)
      : GlobalEvent(_when, Stat_Event_Pri, 0), write(_write), reset(_reset),
        repeat(_repeat), cpu_id(_cpu_id), msg_id(_msg_id), msg(_msg) {}

  virtual void process() {
    if (write) {
      writeCpuBasimPerflog(cpu_id, msg_id, msg);
      // writeTsvEventPerfLog(cpu_id, msg_id, msg);
      // if (msg.empty())
      //   writePerfLog();
      // else if (!tsvLogFp) {
      //   writeEventPerfLog(msg_id, msg);
      // } else {
      //   writeTsvEventPerfLog(cpu_id, msg_id, msg);
      // }
    }

    if (reset)
      Root::RootStats::instance.resetStats();

    if (repeat) {
      schedLogEvent(write, reset, curTick() + repeat, repeat, cpu_id, msg_id, msg);
    }
  }

  const char *description() const { return "GlobalLogEvent"; }
};

void schedLogEvent(bool write, bool reset, Tick when, Tick repeat,
                   uint32_t cpu_id, uint32_t msg_id, std::string msg) {
  // simQuantum is being added to the time when the stats would be
  // dumped so as to ensure that this event happens only after the next
  // sync amongst the event queues.  Asingle event queue simulation
  // should remain unaffected.
  logEvent = new LogEvent(when + simQuantum, write, reset, repeat, cpu_id, msg_id, msg);
}

// void
// periodicLogWrite(Tick period)
// {
//   /*
//    * If the period is set to 0, then we do not want to dump periodically,
//    * thus we deschedule the event. Else, if the period is not 0, but the
//    * event has already been scheduled, we need to get rid of the old event
//    * before we create a new one, as the old event will no longer be moved
//    * forward in the event that we resume from a checkpoint.
//    */
//   if (logEvent != NULL && (period == 0 || logEvent->scheduled())) {
//     // Event should AutoDelete, so we do not need to free it.
//     logEvent->deschedule();
//   }

//   /*
//    * If the period is not 0, we schedule the event. If this is called with a
//    * period that is less than the current tick, then we shift the first dump
//    * by curTick. This ensures that we do not schedule the event is the past.
//    */
//   if (period != 0) {
//     // Schedule the event
//     if (period >= curTick()) {
//       schedLogEvent(true, true, (Tick)period, (Tick)period);
//     } else {
//       schedLogEvent(true, true, (Tick)period + curTick(), (Tick)period);
//     }
//   }
// }

void updateLogEvents() {
  /*
   * If the logEvent has been scheduled, but is scheduled in the past, then
   * we need to shift the event to be at a valid point in time. Therefore, we
   * shift the event by curTick.
   */
  if (logEvent != NULL && (logEvent->scheduled() && logEvent->when() < curTick())) {
    // shift by curTick() and reschedule
    Tick _when = logEvent->when();
    logEvent->reschedule(_when + curTick());
  }
}

statistics::Result cast_stat_info_total(const statistics::Info *info) {
#define TRY_CAST(T)                                                            \
  do {                                                                         \
    auto _stat = dynamic_cast<const T *>(info);                                \
    if (_stat)                                                                 \
      return _stat->total();                                                   \
  } while (0)

  TRY_CAST(statistics::ScalarInfo);
  /* FormulaInfo is a subclass of VectorInfo. Therefore, a cast to
   * FormulaInfo must be attempted before a cast to VectorInfo. Otherwise
   * instances of ForumlaInfo will be cast to VectorInfo.
   */
  TRY_CAST(statistics::FormulaInfo);
  TRY_CAST(statistics::VectorInfo);

  return 0.0;

#undef TRY_CAST
}

statistics::VResult cast_stat_info_vresult(const statistics::Info *info) {
#define TRY_CAST(T)                                                            \
  do {                                                                         \
    auto _stat = dynamic_cast<const T *>(info);                                \
    if (_stat)                                                                 \
      return _stat->result();                                                  \
  } while (0)

  TRY_CAST(statistics::VectorInfo);

  return statistics::VResult();

#undef TRY_CAST
}

statistics::VCounter cast_stat_info_vcounter(const statistics::Info *info) {
#define TRY_CAST(T)                                                            \
  do {                                                                         \
    auto _stat = dynamic_cast<const T *>(info);                                \
    if (_stat)                                                                 \
      return _stat->value();                                                   \
  } while (0)

  TRY_CAST(statistics::VectorInfo);

  return statistics::VCounter();

#undef TRY_CAST
}

void openBasimPerflog(const std::string &filename) {
  basim::globalLogs.perflog.open(filename);
  newTsvPerfLog = true;

  registerExitCallback([]() { basim::globalLogs.perflog.close(); });
}

static void initBasimPerflog() {
  newTsvPerfLog = false;
  updown_period = 500;
  if (Root::root()->find("system.systems.updown0") != NULL) {
    // updown_period = static_cast<const UpDownObj *>(Root::root()->find("system.systems.updown0"))->period;
    multi_updown = true;
  } else if (Root::root()->find("system.systems.updown") != NULL) {
    // updown_period = static_cast<const UpDownObj *>(Root::root()->find("system.systems.updown"))->period;
    multi_updown = false;
  }
  if (Root::root()->find("system.systems.switch_cpus0") != NULL) {
    multi_cpu = true;
  } else {
    multi_cpu = false;
  }
}

void writeCpuBasimPerflog(uint32_t cpu_id, uint32_t msg_id, std::string msg_str) {

  if (!statistics::enabled())
    statistics::enable();

  // if (lastTick != curTick()) {
  //   Root::root()->preDumpStats();
  //   lastTick = curTick();
  // }

  if (newTsvPerfLog) {
    initBasimPerflog();
  }

  uint64_t final_tick = curTick();
  uint64_t sim_ticks = static_cast<uint64_t>(cast_stat_info_total(Root::root()->resolveStat("simTicks")));
  double sim_sec = sim_ticks / static_cast<double>(cast_stat_info_total(Root::root()->resolveStat("simFreq")));
  double host_sec = static_cast<double>(cast_stat_info_total(Root::root()->resolveStat("hostSeconds")));

  basim::globalLogs.perflog.writeTop(host_sec, final_tick, sim_ticks, sim_sec, cpu_id, msg_id, msg_str);
}

void writeUpdownBasimPerflog(uint32_t network_id, uint32_t thread_id, // IDs
                                uint32_t event_label,     // event
                                uint32_t inc_exec_cycles, // incremental exec cycles
                                uint64_t total_exec_cycles, // total exec cycles
                                uint32_t msg_id, std::string &msg_str // message
) {
  if (newTsvPerfLog) {
    initBasimPerflog();
  }

  uint64_t final_tick = curTick() + updown_period * inc_exec_cycles;
  uint64_t sim_ticks = static_cast<uint64_t>(cast_stat_info_total(Root::root()->resolveStat("simTicks"))) + updown_period * inc_exec_cycles;
  double sim_sec = sim_ticks / static_cast<double>(cast_stat_info_total(Root::root()->resolveStat("simFreq")));
  double host_sec = static_cast<double>(cast_stat_info_total(Root::root()->resolveStat("hostSeconds")));
  uint64_t lane_exec_ticks = updown_period * total_exec_cycles;

  basim::globalLogs.perflog.writeUpdown(host_sec, final_tick, sim_ticks, sim_sec, network_id, thread_id, event_label,
               lane_exec_ticks, msg_id, msg_str);
}

void openTsvPerfLog(const std::string &filename) {
  tsvLogFp = std::fopen(filename.c_str(), "w");
  perfLogTsvFilename = filename;
  newTsvPerfLog = true;

  registerExitCallback([]() { closeTsvPerfLog(); });
}

static void initTsvPerfLog() {
  newTsvPerfLog = false;
  updown_period = 500;
  if (Root::root()->find("system.systems.updown0") != NULL) {
    // updown_period = static_cast<const UpDownObj *>(Root::root()->find("system.systems.updown0"))->period;
    multi_updown = true;
  } else if (Root::root()->find("system.systems.updown") != NULL) {
    // updown_period = static_cast<const UpDownObj *>(Root::root()->find("system.systems.updown"))->period;
    multi_updown = false;
  }
  if (Root::root()->find("system.systems.switch_cpus0") != NULL) {
    multi_cpu = true;
  } else {
    multi_cpu = false;
  }
  std::fprintf(tsvLogFp,
               "host_sec\t"
               "final_tick\t"
               "sim_ticks\t"
               "sim_sec\t"
               "cpu_id\t"
               "network_id\t"
               "thread_id\t"
               "event_label\t"
               "lane_exec_ticks\t"
               "msg_id\t"
               "msg_str\n"
               );
}

void writeTsvEventPerfLog(uint32_t cpu_id, uint32_t msg_id, std::string msg_str) {

  if (!statistics::enabled())
    statistics::enable();

  // if (lastTick != curTick()) {
  //   Root::root()->preDumpStats();
  //   lastTick = curTick();
  // }

  if (newTsvPerfLog) {
    initTsvPerfLog();
  }

  uint64_t final_tick = curTick();
  uint64_t sim_ticks = static_cast<uint64_t>(cast_stat_info_total(Root::root()->resolveStat("simTicks")));
  double sim_sec = sim_ticks / static_cast<double>(cast_stat_info_total(Root::root()->resolveStat("simFreq")));
  double host_sec = static_cast<double>(cast_stat_info_total(Root::root()->resolveStat("hostSeconds")));

  std::fprintf(tsvLogFp,
               "%.2lf\t" // host_sec
               "%lu\t" // final_tick
               "%lu\t" // sim_ticks
               "%lf\t" // sim_sec
               "%u\t"  // cpu_id
               "\t"    // network_id
               "\t"    // thread_id
               "\t"    // event_label
               "\t"    // lane_exec_ticks
               "%u\t"  // msg_id
               "%s\n", // msg_str
               host_sec, final_tick, sim_ticks, sim_sec, cpu_id, msg_id, msg_str.c_str());
}

void writeTsvPerfLogUpdownEvent(uint32_t network_id, uint32_t thread_id, // IDs
                                uint32_t event_label,     // event
                                uint32_t inc_exec_cycles, // incremental exec cycles
                                uint64_t total_exec_cycles, // total exec cycles
                                uint32_t msg_id, std::string msg_str // message
) {
  if (newTsvPerfLog) {
    initTsvPerfLog();
  }

  uint64_t final_tick = curTick() + updown_period * inc_exec_cycles;
  uint64_t sim_ticks = static_cast<uint64_t>(cast_stat_info_total(Root::root()->resolveStat("simTicks"))) + updown_period * inc_exec_cycles;
  double sim_sec = sim_ticks / static_cast<double>(cast_stat_info_total(Root::root()->resolveStat("simFreq")));
  double host_sec = static_cast<double>(cast_stat_info_total(Root::root()->resolveStat("hostSeconds")));
  uint64_t lane_exec_ticks = updown_period * total_exec_cycles;

  std::fprintf(tsvLogFp, 
               "%.2lf\t" // host_sec
               "%lu\t" // final_tick
               "%lu\t" // sim_ticks
               "%lf\t" // sim_sec
               "\t"    // cpu_id
               "%u\t"  // network_id
               "%u\t"  // thread_id
               "%u\t"  // event_label
               "%lu\t" // lane_exec_ticks
               "%u\t"  // msg_id
               "%s\n", // msg_str
               host_sec, final_tick, sim_ticks, sim_sec, network_id, thread_id, event_label,
               lane_exec_ticks, msg_id, msg_str.c_str());
}

void closeTsvPerfLog() { std::fclose(tsvLogFp); }

// void
// openPerfLog(const std::string& filename)
// {
//   logStream = new PerfLog::ProtoOutputStream(filename);
//   perfLogFilename = filename;
//   newPerfLog = true;

//   registerExitCallback([]() {  closePerfLog(); });
// }

// static void fill_perf_stats(ProtoPerfLog::PerfLogPacket &pkt, uint32_t
// msg_id, std::string msg_str)
// {
//   auto cur_top = pkt.add_top();
//   cur_top->set_socket_id(0);  // TODO: fill correct id?
//   cur_top->set_core_id(0);  // TODO: fill correct id?

//   // message
//   if (msg_str.size() > 0) {
//     auto msg = cur_top->mutable_msg();
//     msg->set_id(msg_id);
//     msg->set_msg(msg_str);
//   }

//   // SWITCH CPUS STATS
//   auto switch_cpus =
//   Root::root()->getStatGroups().at("system")->getStatGroups().at("switch_cpus");

//   auto core_stats = cur_top->mutable_core_stats();
//   core_stats->set_cycles
//   (static_cast<uint64_t>(cast_stat_info_total(switch_cpus->resolveStat("numCycles"))));
//   core_stats->set_num_insts
//   (static_cast<uint64_t>(cast_stat_info_total(switch_cpus->resolveStat("numInsts"))));
//   core_stats->set_num_insts_issued
//   (static_cast<uint64_t>(cast_stat_info_total(switch_cpus->resolveStat("instsIssued"))));
//   core_stats->set_num_insts_committed
//   (static_cast<uint64_t>(cast_stat_info_total(switch_cpus->resolveStat("committedInsts"))));
//   core_stats->set_num_load_insts
//   (static_cast<uint64_t>(cast_stat_info_total(switch_cpus->resolveStat("numLoadInsts"))));
//   core_stats->set_num_store_insts
//   (static_cast<uint64_t>(cast_stat_info_total(switch_cpus->resolveStat("numStoreInsts"))));
//   core_stats->set_num_branch_insts
//   (static_cast<uint64_t>(cast_stat_info_total(switch_cpus->resolveStat("numBranches"))));
//   core_stats->set_num_integer_insts
//   (static_cast<uint64_t>(cast_stat_info_total(switch_cpus->getStatGroups().at("commit")->resolveStat("integer"))));
//   core_stats->set_num_float_insts
//   (static_cast<uint64_t>(cast_stat_info_total(switch_cpus->getStatGroups().at("commit")->resolveStat("floating"))));
//   core_stats->set_num_vector_insts
//   (static_cast<uint64_t>(cast_stat_info_total(switch_cpus->getStatGroups().at("commit")->resolveStat("vectorInstructions"))));

//   auto l1_cache_stats = cur_top->mutable_l1_cache_stats();

//   auto cpu_dcache =
//   Root::root()->getStatGroups().at("system")->getStatGroups().at("cpu")->getStatGroups().at("dcache");
//   l1_cache_stats->set_dcache_total_accesses
//   (static_cast<uint64_t>(cast_stat_info_total(cpu_dcache->resolveStat("overallAccesses"))));
//   l1_cache_stats->set_dcache_total_misses
//   (static_cast<uint64_t>(cast_stat_info_total(cpu_dcache->resolveStat("overallMisses"))));
//   l1_cache_stats->set_dcache_total_read_accesses
//   (static_cast<uint64_t>(cast_stat_info_total(cpu_dcache->getStatGroups().at("ReadReq")->resolveStat("accesses"))));
//   l1_cache_stats->set_dcache_total_read_misses
//   (static_cast<uint64_t>(cast_stat_info_total(cpu_dcache->getStatGroups().at("ReadReq")->resolveStat("misses"))));
//   l1_cache_stats->set_dcache_total_write_accesses
//   (static_cast<uint64_t>(cast_stat_info_total(cpu_dcache->getStatGroups().at("WriteReq")->resolveStat("accesses"))));
//   l1_cache_stats->set_dcache_total_write_misses
//   (static_cast<uint64_t>(cast_stat_info_total(cpu_dcache->getStatGroups().at("WriteReq")->resolveStat("misses"))));

//   auto cpu_icache =
//   Root::root()->getStatGroups().at("system")->getStatGroups().at("cpu")->getStatGroups().at("icache");
//   l1_cache_stats->set_icache_total_accesses
//   (static_cast<uint64_t>(cast_stat_info_total(cpu_icache->resolveStat("overallAccesses"))));
//   l1_cache_stats->set_icache_total_misses
//   (static_cast<uint64_t>(cast_stat_info_total(cpu_icache->resolveStat("overallMisses"))));
//   l1_cache_stats->set_icache_total_read_accesses
//   (static_cast<uint64_t>(cast_stat_info_total(cpu_icache->getStatGroups().at("ReadReq")->resolveStat("accesses"))));
//   l1_cache_stats->set_icache_total_read_misses
//   (static_cast<uint64_t>(cast_stat_info_total(cpu_icache->getStatGroups().at("ReadReq")->resolveStat("misses"))));
//   l1_cache_stats->set_icache_total_write_accesses
//   (static_cast<uint64_t>(cast_stat_info_total(cpu_icache->getStatGroups().at("WriteReq")->resolveStat("accesses"))));
//   l1_cache_stats->set_icache_total_write_misses
//   (static_cast<uint64_t>(cast_stat_info_total(cpu_icache->getStatGroups().at("WriteReq")->resolveStat("misses"))));

//   auto l2_cache_stats = cur_top->mutable_l2_cache_stats();

//   auto cpu_l2cache =
//   Root::root()->getStatGroups().at("system")->getStatGroups().at("cpu")->getStatGroups().at("l2cache");
//   l2_cache_stats->set_total_accesses
//   (static_cast<uint64_t>(cast_stat_info_total(cpu_l2cache->resolveStat("overallAccesses"))));
//   l2_cache_stats->set_total_misses
//   (static_cast<uint64_t>(cast_stat_info_total(cpu_l2cache->resolveStat("overallMisses"))));
//   l2_cache_stats->set_total_read_accesses
//   (static_cast<uint64_t>(cast_stat_info_total(cpu_l2cache->getStatGroups().at("ReadReq")->resolveStat("accesses"))));
//   l2_cache_stats->set_total_read_misses
//   (static_cast<uint64_t>(cast_stat_info_total(cpu_l2cache->getStatGroups().at("ReadReq")->resolveStat("misses"))));
//   l2_cache_stats->set_total_write_accesses
//   (static_cast<uint64_t>(cast_stat_info_total(cpu_l2cache->getStatGroups().at("WriteReq")->resolveStat("accesses"))));
//   l2_cache_stats->set_total_write_misses
//   (static_cast<uint64_t>(cast_stat_info_total(cpu_l2cache->getStatGroups().at("WriteReq")->resolveStat("misses"))));

//   // SYSTEM STATS
//   auto system = pkt.mutable_system();
//   auto l3_cache_stats = system->mutable_l3_cache_stats();

//   auto system_l3cache =
//   Root::root()->getStatGroups().at("system")->getStatGroups().at("l3");
//   l3_cache_stats->set_total_accesses
//   (static_cast<uint64_t>(cast_stat_info_total(system_l3cache->resolveStat("overallAccesses"))));
//   l3_cache_stats->set_total_misses
//   (static_cast<uint64_t>(cast_stat_info_total(system_l3cache->resolveStat("overallMisses"))));
//   l3_cache_stats->set_total_read_accesses
//   (static_cast<uint64_t>(cast_stat_info_total(system_l3cache->getStatGroups().at("ReadReq")->resolveStat("accesses"))));
//   l3_cache_stats->set_total_read_misses
//   (static_cast<uint64_t>(cast_stat_info_total(system_l3cache->getStatGroups().at("ReadReq")->resolveStat("misses"))));
//   l3_cache_stats->set_total_write_accesses
//   (static_cast<uint64_t>(cast_stat_info_total(system_l3cache->getStatGroups().at("WriteReq")->resolveStat("accesses"))));
//   l3_cache_stats->set_total_write_misses
//   (static_cast<uint64_t>(cast_stat_info_total(system_l3cache->getStatGroups().at("WriteReq")->resolveStat("misses"))));

//   for (int i = 0; i < 8; i++) {
//     auto cur_dram_stats = system->add_dram_per_ctrlr_stats();
//     std::string group_name = "mem_ctrls" + std::to_string(i);
//     auto mem_ctrls =
//     Root::root()->getStatGroups().at("system")->getStatGroups().at(group_name);
//     cur_dram_stats->set_ctrlr_id    (static_cast<uint32_t>(i));
//     cur_dram_stats->set_num_reads
//     (static_cast<uint64_t>(cast_stat_info_total(mem_ctrls->resolveStat("numReads"))));
//     cur_dram_stats->set_num_writes
//     (static_cast<uint64_t>(cast_stat_info_total(mem_ctrls->resolveStat("numWrites"))));
//     cur_dram_stats->set_bytes_read
//     (static_cast<uint64_t>(cast_stat_info_total(mem_ctrls->resolveStat("bytesRead"))));
//     cur_dram_stats->set_bytes_write
//     (static_cast<uint64_t>(cast_stat_info_total(mem_ctrls->resolveStat("bytesWritten"))));
//     cur_dram_stats->set_bw_read
//     (static_cast<uint64_t>(cast_stat_info_total(mem_ctrls->resolveStat("bwRead"))));
//     cur_dram_stats->set_bw_write
//     (static_cast<uint64_t>(cast_stat_info_total(mem_ctrls->resolveStat("bwWrite"))));
//   }

//   // UPDOWN STATS
//   if
//   (Root::root()->getStatGroups().at("system")->getStatGroups().find("upstream")
//   != Root::root()->getStatGroups().end()) {
//     auto updown =
//     Root::root()->getStatGroups().at("system")->getStatGroups().at("upstream");
//     auto exec_cycles =
//     cast_stat_info_vresult(updown->resolveStat("upLaneExecCycles")); auto
//     busy_cycles =
//     cast_stat_info_vresult(updown->resolveStat("upLaneBusyCycles")); auto
//     idle_cycles =
//     cast_stat_info_vresult(updown->resolveStat("upLaneIdleCycles")); auto
//     stall_cycles =
//     cast_stat_info_vresult(updown->resolveStat("upLaneStallCycles"));

//     for (int i = 0; i < idle_cycles.size(); i++) {
//       auto cur_updown = pkt.add_updown();
//       cur_updown->set_updown_id(0);  // TODO: fill correct id?
//       cur_updown->set_lane_id(i);
//       auto cycle_stats = cur_updown->mutable_cycle_stats();
//       cycle_stats->set_exec_cycles(static_cast<uint64_t>(exec_cycles[i]));
//       cycle_stats->set_busy_cycles(static_cast<uint64_t>(busy_cycles[i]));
//       cycle_stats->set_idle_cycles(static_cast<uint64_t>(idle_cycles[i]));
//       cycle_stats->set_stall_cycles(static_cast<uint64_t>(stall_cycles[i]));
//     }
//   }
// }

// static void fill_perf_stats_v2(ProtoPerfLogV2::PerfLogPacket &pkt, uint32_t
// msg_id, std::string msg_str)
// {
//   auto cur_top = pkt.add_top();
//   cur_top->set_socket_id(0);  // TODO: fill correct id?
//   cur_top->set_core_id(0);  // TODO: fill correct id?

//   // message
//   if (msg_str.size() > 0) {
//     auto msg = cur_top->mutable_top_msg();
//     msg->set_id(msg_id);
//     msg->set_str(msg_str);
//   }

//   // SWITCH CPUS STATS
//   auto switch_cpus =
//   Root::root()->getStatGroups().at("system")->getStatGroups().at("switch_cpus");

//   cur_top->set_core_cycles
//   (static_cast<uint64_t>(cast_stat_info_total(switch_cpus->resolveStat("numCycles"))));
//   cur_top->set_core_num_issue_insts
//   (static_cast<uint64_t>(cast_stat_info_total(switch_cpus->resolveStat("instsIssued"))));
//   cur_top->set_core_num_issue_load_insts
//   (static_cast<uint64_t>(cast_stat_info_total(switch_cpus->resolveStat("numLoadInsts"))));
//   cur_top->set_core_num_issue_store_insts
//   (static_cast<uint64_t>(cast_stat_info_total(switch_cpus->resolveStat("numStoreInsts"))));
//   cur_top->set_core_num_issue_branch_insts
//   (static_cast<uint64_t>(cast_stat_info_total(switch_cpus->resolveStat("numBranches"))));

//   cur_top->set_core_num_commit_insts
//   (static_cast<uint64_t>(cast_stat_info_total(switch_cpus->resolveStat("committedInsts"))));
//   cur_top->set_core_num_commit_load_insts
//   (static_cast<uint64_t>(cast_stat_info_total(switch_cpus->getStatGroups().at("commit")->resolveStat("loads"))));
//   cur_top->set_core_num_commit_store_insts
//   (static_cast<uint64_t>(cast_stat_info_total(switch_cpus->getStatGroups().at("commit")->resolveStat("memRefs")))
//   -
//   static_cast<uint64_t>(cast_stat_info_total(switch_cpus->getStatGroups().at("commit")->resolveStat("loads"))));
//   cur_top->set_core_num_commit_integer_insts(static_cast<uint64_t>(cast_stat_info_total(switch_cpus->getStatGroups().at("commit")->resolveStat("integer"))));
//   cur_top->set_core_num_commit_float_insts
//   (static_cast<uint64_t>(cast_stat_info_total(switch_cpus->getStatGroups().at("commit")->resolveStat("floating"))));
//   cur_top->set_core_num_commit_vector_insts
//   (static_cast<uint64_t>(cast_stat_info_total(switch_cpus->getStatGroups().at("commit")->resolveStat("vectorInstructions"))));
//   cur_top->set_core_num_commit_call_insts
//   (static_cast<uint64_t>(cast_stat_info_total(switch_cpus->getStatGroups().at("commit")->resolveStat("functionCalls"))));

//   auto cpu_dcache =
//   Root::root()->getStatGroups().at("system")->getStatGroups().at("cpu")->getStatGroups().at("dcache");
//   cur_top->set_l1_dcache_total_accesses
//   (static_cast<uint64_t>(cast_stat_info_total(cpu_dcache->resolveStat("overallAccesses"))));
//   cur_top->set_l1_dcache_total_misses
//   (static_cast<uint64_t>(cast_stat_info_total(cpu_dcache->resolveStat("overallMisses"))));
//   cur_top->set_l1_dcache_total_read_accesses
//   (static_cast<uint64_t>(cast_stat_info_total(cpu_dcache->getStatGroups().at("ReadReq")->resolveStat("accesses"))));
//   cur_top->set_l1_dcache_total_read_misses
//   (static_cast<uint64_t>(cast_stat_info_total(cpu_dcache->getStatGroups().at("ReadReq")->resolveStat("misses"))));
//   cur_top->set_l1_dcache_total_write_accesses
//   (static_cast<uint64_t>(cast_stat_info_total(cpu_dcache->getStatGroups().at("WriteReq")->resolveStat("accesses"))));
//   cur_top->set_l1_dcache_total_write_misses
//   (static_cast<uint64_t>(cast_stat_info_total(cpu_dcache->getStatGroups().at("WriteReq")->resolveStat("misses"))));

//   auto cpu_icache =
//   Root::root()->getStatGroups().at("system")->getStatGroups().at("cpu")->getStatGroups().at("icache");
//   cur_top->set_l1_icache_total_accesses
//   (static_cast<uint64_t>(cast_stat_info_total(cpu_icache->resolveStat("overallAccesses"))));
//   cur_top->set_l1_icache_total_misses
//   (static_cast<uint64_t>(cast_stat_info_total(cpu_icache->resolveStat("overallMisses"))));
//   cur_top->set_l1_icache_total_read_accesses
//   (static_cast<uint64_t>(cast_stat_info_total(cpu_icache->getStatGroups().at("ReadReq")->resolveStat("accesses"))));
//   cur_top->set_l1_icache_total_read_misses
//   (static_cast<uint64_t>(cast_stat_info_total(cpu_icache->getStatGroups().at("ReadReq")->resolveStat("misses"))));
//   cur_top->set_l1_icache_total_write_accesses
//   (static_cast<uint64_t>(cast_stat_info_total(cpu_icache->getStatGroups().at("WriteReq")->resolveStat("accesses"))));
//   cur_top->set_l1_icache_total_write_misses
//   (static_cast<uint64_t>(cast_stat_info_total(cpu_icache->getStatGroups().at("WriteReq")->resolveStat("misses"))));

//   auto cpu_l2cache =
//   Root::root()->getStatGroups().at("system")->getStatGroups().at("cpu")->getStatGroups().at("l2cache");
//   cur_top->set_l2_cache_total_accesses
//   (static_cast<uint64_t>(cast_stat_info_total(cpu_l2cache->resolveStat("overallAccesses"))));
//   cur_top->set_l2_cache_total_misses
//   (static_cast<uint64_t>(cast_stat_info_total(cpu_l2cache->resolveStat("overallMisses"))));
//   cur_top->set_l2_cache_total_read_accesses
//   (static_cast<uint64_t>(cast_stat_info_total(cpu_l2cache->getStatGroups().at("ReadReq")->resolveStat("accesses"))));
//   cur_top->set_l2_cache_total_read_misses
//   (static_cast<uint64_t>(cast_stat_info_total(cpu_l2cache->getStatGroups().at("ReadReq")->resolveStat("misses"))));
//   cur_top->set_l2_cache_total_write_accesses
//   (static_cast<uint64_t>(cast_stat_info_total(cpu_l2cache->getStatGroups().at("WriteReq")->resolveStat("accesses"))));
//   cur_top->set_l2_cache_total_write_misses
//   (static_cast<uint64_t>(cast_stat_info_total(cpu_l2cache->getStatGroups().at("WriteReq")->resolveStat("misses"))));

//   // SYSTEM STATS
//   auto system = pkt.mutable_system();

//   auto system_l3cache =
//   Root::root()->getStatGroups().at("system")->getStatGroups().at("l3");
//   system->set_l3_cache_total_accesses
//   (static_cast<uint64_t>(cast_stat_info_total(system_l3cache->resolveStat("overallAccesses"))));
//   system->set_l3_cache_total_misses
//   (static_cast<uint64_t>(cast_stat_info_total(system_l3cache->resolveStat("overallMisses"))));
//   system->set_l3_cache_total_read_accesses
//   (static_cast<uint64_t>(cast_stat_info_total(system_l3cache->getStatGroups().at("ReadReq")->resolveStat("accesses"))));
//   system->set_l3_cache_total_read_misses
//   (static_cast<uint64_t>(cast_stat_info_total(system_l3cache->getStatGroups().at("ReadReq")->resolveStat("misses"))));
//   system->set_l3_cache_total_write_accesses
//   (static_cast<uint64_t>(cast_stat_info_total(system_l3cache->getStatGroups().at("WriteReq")->resolveStat("accesses"))));
//   system->set_l3_cache_total_write_misses
//   (static_cast<uint64_t>(cast_stat_info_total(system_l3cache->getStatGroups().at("WriteReq")->resolveStat("misses"))));

//   for (int i = 0; i < 8; i++) {
//     auto cur_dram_stats = system->add_dram_per_ctrlr_stats();
//     std::string group_name = "mem_ctrls" + std::to_string(i);
//     auto mem_ctrls =
//     Root::root()->getStatGroups().at("system")->getStatGroups().at(group_name);
//     cur_dram_stats->set_ctrlr_id    (static_cast<uint32_t>(i));
//     cur_dram_stats->set_num_reads
//     (static_cast<uint64_t>(cast_stat_info_total(mem_ctrls->resolveStat("numReads"))));
//     cur_dram_stats->set_num_writes
//     (static_cast<uint64_t>(cast_stat_info_total(mem_ctrls->resolveStat("numWrites"))));
//     cur_dram_stats->set_bytes_read
//     (static_cast<uint64_t>(cast_stat_info_total(mem_ctrls->resolveStat("bytesRead"))));
//     cur_dram_stats->set_bytes_write
//     (static_cast<uint64_t>(cast_stat_info_total(mem_ctrls->resolveStat("bytesWritten"))));
//     cur_dram_stats->set_bw_read
//     (static_cast<uint64_t>(cast_stat_info_total(mem_ctrls->resolveStat("bwRead"))));
//     cur_dram_stats->set_bw_write
//     (static_cast<uint64_t>(cast_stat_info_total(mem_ctrls->resolveStat("bwWrite"))));
//   }

//   // UPDOWN STATS
//   if
//   (Root::root()->getStatGroups().at("system")->getStatGroups().find("upstream")
//   != Root::root()->getStatGroups().end()) {
//     auto updown =
//     Root::root()->getStatGroups().at("system")->getStatGroups().at("upstream");

//     auto exec_cycles =
//     cast_stat_info_vresult(updown->resolveStat("upLaneExecCycles")); auto
//     busy_cycles =
//     cast_stat_info_vresult(updown->resolveStat("upLaneBusyCycles")); auto
//     idle_cycles =
//     cast_stat_info_vresult(updown->resolveStat("upLaneIdleCycles")); auto
//     stall_cycles =
//     cast_stat_info_vresult(updown->resolveStat("upLaneStallCycles"));

//     auto total_actions =
//     cast_stat_info_vresult(updown->resolveStat("numActions")); auto msg_acts
//     = cast_stat_info_vresult(updown->resolveStat("MessageInstructions"));
//     auto mov_acts =
//     cast_stat_info_vresult(updown->resolveStat("MovInstructions")); auto
//     branch_acts =
//     cast_stat_info_vresult(updown->resolveStat("BranchInstructions")); auto
//     cmpswp_acts =
//     cast_stat_info_vresult(updown->resolveStat("AtomicInstructions")); auto
//     yield_acts =
//     cast_stat_info_vresult(updown->resolveStat("YieldInstructions")); auto
//     alu_acts =
//     cast_stat_info_vresult(updown->resolveStat("ALUInstructions")); auto
//     cmp_acts =
//     cast_stat_info_vresult(updown->resolveStat("CompareInstructions"));

//     auto total_transitions =
//     cast_stat_info_vresult(updown->resolveStat("numTransitions"));

//     for (int i = 0; i < idle_cycles.size(); i++) {
//       auto pkt_cur_updown = pkt.add_updown();
//       pkt_cur_updown->set_updown_id(0);  // TODO: fill correct id?
//       pkt_cur_updown->set_lane_id(i);
//       pkt_cur_updown->set_cycle_exec(static_cast<uint64_t>(exec_cycles[i]));
//       pkt_cur_updown->set_cycle_busy(static_cast<uint64_t>(busy_cycles[i]));
//       pkt_cur_updown->set_cycle_idle(static_cast<uint64_t>(idle_cycles[i]));
//       pkt_cur_updown->set_cycle_stall(static_cast<uint64_t>(stall_cycles[i]));

//       pkt_cur_updown->set_action_num_total
//       (static_cast<uint64_t>(total_actions[i]));
//       pkt_cur_updown->set_action_num_message
//       (static_cast<uint64_t>(msg_acts[i]));
//       pkt_cur_updown->set_action_num_move
//       (static_cast<uint64_t>(mov_acts[i]));
//       pkt_cur_updown->set_action_num_alu
//       (static_cast<uint64_t>(alu_acts[i]));
//       pkt_cur_updown->set_action_num_branch
//       (static_cast<uint64_t>(branch_acts[i]));
//       pkt_cur_updown->set_action_num_yield
//       (static_cast<uint64_t>(yield_acts[i]));
//       pkt_cur_updown->set_action_num_cmpswp
//       (static_cast<uint64_t>(cmpswp_acts[i]));
//       pkt_cur_updown->set_action_num_compare
//       (static_cast<uint64_t>(cmp_acts[i]));

//       pkt_cur_updown->set_trans_num_total(static_cast<uint64_t>(total_transitions[i]));
//     }
//   }
// }

// void
// writePerfLog()
// {
//   if (!statistics::enabled())
//     statistics::enable();

//   if (lastTick != curTick()) {
//     Root::root()->preDumpStats();
//     lastTick = curTick();
//   }

//   if (newPerfLog) {
//     ProtoPerfLog::PerfLogHeader hdr;
//     // ProtoPerfLogV2::PerfLogHeader hdr;
//     hdr.set_obj_id(perfLogFilename);
//     hdr.set_tick_freq(sim_clock::Frequency);
//     logStream->write(hdr);
//     newPerfLog = false;
//   }

//   ProtoPerfLog::PerfLogPacket pkt;
//   // ProtoPerfLogV2::PerfLogPacket pkt;
//   pkt.set_sim_timestamp(curTick());
//   fill_perf_stats(pkt, 0, "");
//   // fill_perf_stats_v2(pkt, 0, "");
//   logStream->write(pkt);
// }

// void
// writeEventPerfLog(uint32_t message_id, std::string message)
// {
//   if (!statistics::enabled())
//     statistics::enable();

//   if (lastTick != curTick()) {
//     Root::root()->preDumpStats();
//     lastTick = curTick();
//   }

//   if (newPerfLog) {
//     ProtoPerfLog::PerfLogHeader hdr;
//     // ProtoPerfLogV2::PerfLogHeader hdr;
//     hdr.set_obj_id(perfLogFilename);
//     hdr.set_tick_freq(sim_clock::Frequency);
//     logStream->write(hdr);
//     newPerfLog = false;
//   }

//   // {R } - Register/PMU
//   // {M } - Memory
//   // {Q } - Queue?

//   ProtoPerfLog::PerfLogPacket pkt;
//   // ProtoPerfLogV2::PerfLogPacket pkt;
//   pkt.set_sim_timestamp(curTick());

//   fill_perf_stats(pkt, message_id, message);
//   // fill_perf_stats_v2(pkt, message_id, message);
//   // TODO: parse message and fill in accordingly

//   logStream->write(pkt);
// }

// void writePerfLogUpdown(uint32_t updown_id, uint32_t lane_id, uint32_t
// thread_id, // IDs
//                         uint32_t event_base, uint32_t event_label, // event
//                         bool en_msg, bool en_cycle, bool en_action, bool
//                         en_trans, bool en_queue, bool en_lm, bool en_dram,
//                         bool en_sys_dram, uint32_t msg_id, std::string
//                         msg_str, std::vector<std::pair<std::string,
//                         uint64_t>> msg_regs, // message uint32_t
//                         inc_exec_cycles,
//                         // uint32_t inc_idle_cycles,
//                         // uint32_t inc_num_sends,
//                         uint32_t inc_total_trans,
//                         uint32_t inc_total_acts, uint32_t inc_msg_acts,
//                         uint32_t inc_mov_acts, uint32_t inc_branch_acts,
//                         uint32_t inc_alu_acts, uint32_t inc_yld_acts,
//                         uint32_t inc_cmp_acts, uint32_t inc_cmpswp_acts,
//                         uint32_t operand_q_len, uint32_t event_q_len,
//                         uint32_t inc_lm_rd_bytes, uint32_t inc_lm_wr_bytes
//                         // uint32_t inc_dram_rd_bytes, uint32_t
//                         inc_dram_wr_bytes ) {

//   // INITIALIZATION
//   if (!statistics::enabled())
//     statistics::enable();

//   if (lastTick != curTick()) {
//     Root::root()->preDumpStats();
//     lastTick = curTick();
//   }

//   if (newPerfLog) {
//     ProtoPerfLog::PerfLogHeader hdr;
//     hdr.set_obj_id(perfLogFilename);
//     hdr.set_tick_freq(sim_clock::Frequency);
//     logStream->write(hdr);
//     newPerfLog = false;
//   }

//   ProtoPerfLog::PerfLogPacket pkt;
//   // auto updown_simobj = Root::root()->find("upstream");
//   pkt.set_sim_timestamp(curTick() + static_cast<const UpDownObj
//   *>(Root::root()->find("system.upstream"))->period * inc_exec_cycles);

//   // UPDOWN STATS
//   if
//   (Root::root()->getStatGroups().at("system")->getStatGroups().find("upstream")
//   != Root::root()->getStatGroups().end()) {
//     auto cur_updown =
//     Root::root()->getStatGroups().at("system")->getStatGroups().at("upstream");

//     auto pkt_cur_updown = pkt.add_updown();
//     pkt_cur_updown->set_updown_id(updown_id);
//     pkt_cur_updown->set_lane_id(lane_id);
//     pkt_cur_updown->set_thread_id(thread_id);
//     pkt_cur_updown->set_event_base(event_base);
//     pkt_cur_updown->set_event_label(event_label);

//     // UpDown message
//     if (en_msg) {
//       auto pkt_updown_msg = pkt_cur_updown->mutable_msg();
//       pkt_updown_msg->set_id(msg_id);
//       pkt_updown_msg->set_msg(msg_str);
//       for (auto reg_pair: msg_regs) {
//         auto pkt_cur_int_reg = pkt_updown_msg->add_int_regs();
//         pkt_cur_int_reg->set_name(reg_pair.first);
//         pkt_cur_int_reg->set_value(reg_pair.second);
//       }
//     }

//     if (en_cycle) {
//       auto exec_cycles =
//       cast_stat_info_vresult(cur_updown->resolveStat("upLaneExecCycles"));
//       auto busy_cycles =
//       cast_stat_info_vresult(cur_updown->resolveStat("upLaneBusyCycles"));
//       auto idle_cycles =
//       cast_stat_info_vresult(cur_updown->resolveStat("upLaneIdleCycles"));
//       auto stall_cycles =
//       cast_stat_info_vresult(cur_updown->resolveStat("upLaneStallCycles"));
//       auto pkt_cycle_stats = pkt_cur_updown->mutable_cycle_stats();
//       pkt_cycle_stats->set_exec_cycles(static_cast<uint64_t>(exec_cycles[lane_id])
//       + inc_exec_cycles);
//       pkt_cycle_stats->set_busy_cycles(static_cast<uint64_t>(busy_cycles[lane_id])
//       + inc_exec_cycles);
//       pkt_cycle_stats->set_idle_cycles(static_cast<uint64_t>(idle_cycles[lane_id]));
//       pkt_cycle_stats->set_stall_cycles(static_cast<uint64_t>(stall_cycles[lane_id]));
//     }

//     if (en_action) {
//       auto total_actions =
//       cast_stat_info_vresult(cur_updown->resolveStat("numActions")); auto
//       msg_acts =
//       cast_stat_info_vresult(cur_updown->resolveStat("MessageInstructions"));
//       auto mov_acts =
//       cast_stat_info_vresult(cur_updown->resolveStat("MovInstructions"));
//       auto branch_acts =
//       cast_stat_info_vresult(cur_updown->resolveStat("BranchInstructions"));
//       auto cmpswp_acts =
//       cast_stat_info_vresult(cur_updown->resolveStat("AtomicInstructions"));
//       auto yield_acts =
//       cast_stat_info_vresult(cur_updown->resolveStat("YieldInstructions"));
//       auto alu_acts =
//       cast_stat_info_vresult(cur_updown->resolveStat("ALUInstructions"));
//       auto cmp_acts =
//       cast_stat_info_vresult(cur_updown->resolveStat("CompareInstructions"));
//       auto pkt_action_stats = pkt_cur_updown->mutable_action_stats();
//       pkt_action_stats->set_total_actions(total_actions[lane_id] +
//       inc_total_acts);
//       pkt_action_stats->set_message_actions(msg_acts[lane_id] +
//       inc_msg_acts); pkt_action_stats->set_move_actions(mov_acts[lane_id] +
//       inc_mov_acts); pkt_action_stats->set_alu_actions(alu_acts[lane_id] +
//       inc_alu_acts);
//       pkt_action_stats->set_branch_actions(branch_acts[lane_id] +
//       inc_branch_acts);
//       pkt_action_stats->set_yield_actions(yield_acts[lane_id] +
//       inc_yld_acts);
//       pkt_action_stats->set_cmpswp_actions(cmpswp_acts[lane_id] +
//       inc_cmpswp_acts);
//       pkt_action_stats->set_compare_actions(cmp_acts[lane_id] +
//       inc_cmp_acts);
//     }

//     if (en_trans) {
//       auto total_transitions =
//       cast_stat_info_vresult(cur_updown->resolveStat("numTransitions")); auto
//       pkt_trans_stats = pkt_cur_updown->mutable_trans_stats();
//       pkt_trans_stats->set_total_trans(total_transitions[lane_id] +
//       inc_total_trans);
//       //TODO: add more?
//     }

//     // auto total_instructions =
//     cast_stat_info_vresult(cur_updown->resolveStat("numInstructions"));

//     if (en_queue) {
//       auto pkt_queue_stats = pkt_cur_updown->mutable_queue_stats();
//       pkt_queue_stats->set_operand_q_len(operand_q_len);
//       pkt_queue_stats->set_event_q_len(event_q_len);
//     }

//     if (en_lm) {
//       auto lm_rd_bytes =
//       cast_stat_info_vresult(cur_updown->resolveStat("upLmReadBytes")); auto
//       lm_wr_bytes =
//       cast_stat_info_vresult(cur_updown->resolveStat("upLmWriteBytes")); auto
//       pkt_local_mem_stats = pkt_cur_updown->mutable_local_mem_stats();
//       pkt_local_mem_stats->set_read_bytes(lm_rd_bytes[lane_id] +
//       inc_lm_rd_bytes);
//       pkt_local_mem_stats->set_write_bytes(lm_wr_bytes[lane_id] +
//       inc_lm_wr_bytes);
//     }

//     if (en_dram) {
//       auto pkt_mem_intf_stats = pkt_cur_updown->mutable_mem_intf_stats();
//       pkt_mem_intf_stats->set_read_bytes(static_cast<uint64_t>(cast_stat_info_total(cur_updown->resolveStat("upDramReadBytes"))));
//       pkt_mem_intf_stats->set_write_bytes(static_cast<uint64_t>(cast_stat_info_total(cur_updown->resolveStat("upDramWriteBytes"))));
//     }
//   }

//   // SYSTEM STATS
//   if (en_sys_dram) {
//     auto system = pkt.mutable_system();

//     // auto l3_cache_stats = system->mutable_l3_cache_stats();
//     // auto system_l3cache =
//     Root::root()->getStatGroups().at("system")->getStatGroups().at("l3");
//     // l3_cache_stats->set_total_accesses
//     (static_cast<uint64_t>(cast_stat_info_total(system_l3cache->resolveStat("overallAccesses"))));
//     // l3_cache_stats->set_total_misses
//     (static_cast<uint64_t>(cast_stat_info_total(system_l3cache->resolveStat("overallMisses"))));
//     // l3_cache_stats->set_total_read_accesses
//     (static_cast<uint64_t>(cast_stat_info_total(system_l3cache->getStatGroups().at("ReadReq")->resolveStat("accesses"))));
//     // l3_cache_stats->set_total_read_misses
//     (static_cast<uint64_t>(cast_stat_info_total(system_l3cache->getStatGroups().at("ReadReq")->resolveStat("misses"))));
//     // l3_cache_stats->set_total_write_accesses
//     (static_cast<uint64_t>(cast_stat_info_total(system_l3cache->getStatGroups().at("WriteReq")->resolveStat("accesses"))));
//     // l3_cache_stats->set_total_write_misses
//     (static_cast<uint64_t>(cast_stat_info_total(system_l3cache->getStatGroups().at("WriteReq")->resolveStat("misses"))));

//     for (int i = 0; i < 8; i++) {
//       auto cur_dram_stats = system->add_dram_per_ctrlr_stats();
//       std::string group_name = "mem_ctrls" + std::to_string(i);
//       auto mem_ctrls =
//       Root::root()->getStatGroups().at("system")->getStatGroups().at(group_name);
//       cur_dram_stats->set_ctrlr_id    (static_cast<uint32_t>(i));
//       cur_dram_stats->set_num_reads
//       (static_cast<uint64_t>(cast_stat_info_total(mem_ctrls->resolveStat("numReads"))));
//       cur_dram_stats->set_num_writes
//       (static_cast<uint64_t>(cast_stat_info_total(mem_ctrls->resolveStat("numWrites"))));
//       cur_dram_stats->set_bytes_read
//       (static_cast<uint64_t>(cast_stat_info_total(mem_ctrls->resolveStat("bytesRead"))));
//       cur_dram_stats->set_bytes_write
//       (static_cast<uint64_t>(cast_stat_info_total(mem_ctrls->resolveStat("bytesWritten"))));
//       cur_dram_stats->set_bw_read
//       (static_cast<uint64_t>(cast_stat_info_total(mem_ctrls->resolveStat("bwRead"))));
//       cur_dram_stats->set_bw_write
//       (static_cast<uint64_t>(cast_stat_info_total(mem_ctrls->resolveStat("bwWrite"))));
//     }
//   }

//   logStream->write(pkt);
// }

// void writePerfLogUpdownV2(uint32_t updown_id, uint32_t lane_id, uint32_t
// thread_id, // IDs
//                           uint32_t event_base, uint32_t event_label, // event
//                           bool en_msg, bool en_cycle, bool en_action, bool
//                           en_trans, bool en_queue, bool en_lm, bool en_dram,
//                           bool en_sys_dram, uint32_t msg_id, std::string
//                           msg_str, std::vector<std::pair<std::string,
//                           uint64_t>> msg_regs, // message uint32_t
//                           inc_exec_cycles,
//                           // uint32_t inc_idle_cycles,
//                           // uint32_t inc_num_sends,
//                           uint32_t inc_total_trans,
//                           uint32_t inc_total_acts, uint32_t inc_msg_acts,
//                           uint32_t inc_mov_acts, uint32_t inc_branch_acts,
//                           uint32_t inc_alu_acts, uint32_t inc_yld_acts,
//                           uint32_t inc_cmp_acts, uint32_t inc_cmpswp_acts,
//                           uint32_t operand_q_len, uint32_t event_q_len,
//                           uint32_t inc_lm_rd_bytes, uint32_t inc_lm_wr_bytes
//                           // uint32_t inc_dram_rd_bytes, uint32_t
//                           inc_dram_wr_bytes ) {

//   // INITIALIZATION
//   if (!statistics::enabled())
//     statistics::enable();

//   if (lastTick != curTick()) {
//     Root::root()->preDumpStats();
//     lastTick = curTick();
//   }

//   if (newPerfLog) {
//     ProtoPerfLogV2::PerfLogHeader hdr;
//     hdr.set_obj_id(perfLogFilename);
//     hdr.set_tick_freq(sim_clock::Frequency);
//     logStream->write(hdr);
//     newPerfLog = false;
//   }

//   ProtoPerfLogV2::PerfLogPacket pkt;
//   // auto updown_simobj = Root::root()->find("upstream");
//   pkt.set_sim_timestamp(curTick() + static_cast<const UpDownObj
//   *>(Root::root()->find("system.upstream"))->period * inc_exec_cycles);

//   // UPDOWN STATS
//   if
//   (Root::root()->getStatGroups().at("system")->getStatGroups().find("upstream")
//   != Root::root()->getStatGroups().end()) {
//     auto cur_updown =
//     Root::root()->getStatGroups().at("system")->getStatGroups().at("upstream");

//     auto pkt_cur_updown = pkt.add_updown();
//     pkt_cur_updown->set_updown_id(updown_id);
//     pkt_cur_updown->set_lane_id(lane_id);
//     pkt_cur_updown->set_thread_id(thread_id);
//     pkt_cur_updown->set_event_base(event_base);
//     pkt_cur_updown->set_event_label(event_label);

//     // UpDown message
//     if (en_msg) {
//       auto pkt_updown_msg = pkt_cur_updown->mutable_updown_msg();
//       pkt_updown_msg->set_id(msg_id);
//       pkt_updown_msg->set_str(msg_str);
//       for (auto reg_pair: msg_regs) {
//         auto pkt_cur_int_reg = pkt_updown_msg->add_int_regs();
//         pkt_cur_int_reg->set_name(reg_pair.first);
//         pkt_cur_int_reg->set_value(reg_pair.second);
//       }
//     }

//     if (en_cycle) {
//       auto exec_cycles =
//       cast_stat_info_vresult(cur_updown->resolveStat("upLaneExecCycles"));
//       auto busy_cycles =
//       cast_stat_info_vresult(cur_updown->resolveStat("upLaneBusyCycles"));
//       auto idle_cycles =
//       cast_stat_info_vresult(cur_updown->resolveStat("upLaneIdleCycles"));
//       auto stall_cycles =
//       cast_stat_info_vresult(cur_updown->resolveStat("upLaneStallCycles"));
//       pkt_cur_updown->set_cycle_exec(static_cast<uint64_t>(exec_cycles[lane_id])
//       + inc_exec_cycles);
//       pkt_cur_updown->set_cycle_busy(static_cast<uint64_t>(busy_cycles[lane_id])
//       + inc_exec_cycles);
//       pkt_cur_updown->set_cycle_idle(static_cast<uint64_t>(idle_cycles[lane_id]));
//       pkt_cur_updown->set_cycle_stall(static_cast<uint64_t>(stall_cycles[lane_id]));
//     }

//     if (en_action) {
//       auto total_actions =
//       cast_stat_info_vresult(cur_updown->resolveStat("numActions")); auto
//       msg_acts =
//       cast_stat_info_vresult(cur_updown->resolveStat("MessageInstructions"));
//       auto mov_acts =
//       cast_stat_info_vresult(cur_updown->resolveStat("MovInstructions"));
//       auto branch_acts =
//       cast_stat_info_vresult(cur_updown->resolveStat("BranchInstructions"));
//       auto cmpswp_acts =
//       cast_stat_info_vresult(cur_updown->resolveStat("AtomicInstructions"));
//       auto yield_acts =
//       cast_stat_info_vresult(cur_updown->resolveStat("YieldInstructions"));
//       auto alu_acts =
//       cast_stat_info_vresult(cur_updown->resolveStat("ALUInstructions"));
//       auto cmp_acts =
//       cast_stat_info_vresult(cur_updown->resolveStat("CompareInstructions"));
//       pkt_cur_updown->set_action_num_total   (total_actions[lane_id] +
//       inc_total_acts); pkt_cur_updown->set_action_num_message
//       (msg_acts[lane_id] + inc_msg_acts); pkt_cur_updown->set_action_num_move
//       (mov_acts[lane_id] + inc_mov_acts); pkt_cur_updown->set_action_num_alu
//       (alu_acts[lane_id] + inc_alu_acts);
//       pkt_cur_updown->set_action_num_branch  (branch_acts[lane_id] +
//       inc_branch_acts); pkt_cur_updown->set_action_num_yield
//       (yield_acts[lane_id] + inc_yld_acts);
//       pkt_cur_updown->set_action_num_cmpswp  (cmpswp_acts[lane_id] +
//       inc_cmpswp_acts); pkt_cur_updown->set_action_num_compare
//       (cmp_acts[lane_id] + inc_cmp_acts);
//     }

//     if (en_trans) {
//       auto total_transitions =
//       cast_stat_info_vresult(cur_updown->resolveStat("numTransitions"));
//       pkt_cur_updown->set_trans_num_total(total_transitions[lane_id] +
//       inc_total_trans);
//       //TODO: add more?
//     }

//     // auto total_instructions =
//     cast_stat_info_vresult(cur_updown->resolveStat("numInstructions"));

//     if (en_queue) {
//       pkt_cur_updown->set_queue_len_event(event_q_len);
//       pkt_cur_updown->set_queue_len_operand(operand_q_len);
//     }

//     if (en_lm) {
//       auto lm_rd_bytes =
//       cast_stat_info_vresult(cur_updown->resolveStat("upLmReadBytes")); auto
//       lm_wr_bytes =
//       cast_stat_info_vresult(cur_updown->resolveStat("upLmWriteBytes"));
//       pkt_cur_updown->set_local_mem_bytes_read(lm_rd_bytes[lane_id] +
//       inc_lm_rd_bytes);
//       pkt_cur_updown->set_local_mem_bytes_write(lm_wr_bytes[lane_id] +
//       inc_lm_wr_bytes);
//     }

//     if (en_dram) {
//       pkt_cur_updown->set_dram_bytes_read(static_cast<uint64_t>(cast_stat_info_total(cur_updown->resolveStat("upDramReadBytes"))));
//       pkt_cur_updown->set_dram_bytes_write(static_cast<uint64_t>(cast_stat_info_total(cur_updown->resolveStat("upDramWriteBytes"))));
//     }
//   }

//   // SYSTEM STATS
//   if (en_sys_dram) {
//     auto system = pkt.mutable_system();
//     for (int i = 0; i < 8; i++) {
//       auto cur_dram_stats = system->add_dram_per_ctrlr_stats();
//       std::string group_name = "mem_ctrls" + std::to_string(i);
//       auto mem_ctrls =
//       Root::root()->getStatGroups().at("system")->getStatGroups().at(group_name);
//       cur_dram_stats->set_ctrlr_id    (static_cast<uint32_t>(i));
//       cur_dram_stats->set_num_reads
//       (static_cast<uint64_t>(cast_stat_info_total(mem_ctrls->resolveStat("numReads"))));
//       cur_dram_stats->set_num_writes
//       (static_cast<uint64_t>(cast_stat_info_total(mem_ctrls->resolveStat("numWrites"))));
//       cur_dram_stats->set_bytes_read
//       (static_cast<uint64_t>(cast_stat_info_total(mem_ctrls->resolveStat("bytesRead"))));
//       cur_dram_stats->set_bytes_write
//       (static_cast<uint64_t>(cast_stat_info_total(mem_ctrls->resolveStat("bytesWritten"))));
//       cur_dram_stats->set_bw_read
//       (static_cast<uint64_t>(cast_stat_info_total(mem_ctrls->resolveStat("bwRead"))));
//       cur_dram_stats->set_bw_write
//       (static_cast<uint64_t>(cast_stat_info_total(mem_ctrls->resolveStat("bwWrite"))));
//     }
//   }

//   logStream->write(pkt);
// }

// void closePerfLog() { delete logStream; }

} // namespace PerfLog
