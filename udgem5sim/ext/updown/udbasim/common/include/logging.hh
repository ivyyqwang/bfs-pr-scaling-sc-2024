#pragma once

#include <cstdint>
#include <cstdio>
#include <string>

namespace basim {

class Logging {
private:
  class Perflog {
  private:
    FILE *log_fp;

    // Perflog callback
    void (*perflog_cb)(uint32_t network_id, uint32_t thread_id, // IDs
                       uint32_t event_label,                    // event
                       uint32_t inc_exec_cycles,                // incremental exec cycles
                       uint64_t total_exec_cycles,              // total exec cycles
                       uint32_t msg_id, std::string &msg_str    // message
                       ) = nullptr;

  public:
    Perflog() : log_fp(nullptr){};

    ~Perflog() { this->close(); };

    Perflog(const std::string &filename) { this->open(filename); };

    bool isOpen() { return log_fp != nullptr; };

    void open(const std::string &filename) {
      if (log_fp != nullptr)
        std::fclose(log_fp);
      log_fp = std::fopen(filename.c_str(), "w");
      std::fprintf(log_fp, "HOST_SEC\t"
                           "FINAL_TICK\t"
                           "SIM_TICKS\t"
                           "SIM_SEC\t"
                           "CPU_ID\t"
                           "NETWORK_ID\t"
                           "THREAD_ID\t"
                           "EVENT_LABEL\t"
                           "LANE_EXEC_TICKS\t"
                           "MSG_ID\t"
                           "MSG_STR\n");
    };

    void close() {
      if (log_fp != nullptr) {
        std::fclose(log_fp);
        log_fp = nullptr;
      }
    };

    void write(double host_sec, uint64_t final_tick, uint64_t sim_ticks, double sim_sec, uint32_t cpu_id, uint32_t network_id, uint32_t thread_id,
               uint32_t event_label, uint64_t lane_exec_ticks, uint64_t msg_id, const std::string &msg_str) {
      std::fprintf(log_fp, "%.2f\t%lu\t%lu\t%f\t%u\t%u\t%u\t%u\t%lu\t%lu\t%s\n", host_sec, final_tick, sim_ticks, sim_sec, cpu_id, network_id, thread_id,
                   event_label, lane_exec_ticks, msg_id, msg_str.c_str());
    };

    void writeTop(double host_sec, uint64_t final_tick, uint64_t sim_ticks, double sim_sec, uint32_t cpu_id, uint64_t msg_id, const std::string &msg_str) {
      std::fprintf(log_fp, "%.2f\t%lu\t%lu\t%f\t%u\t\t\t\t\t%lu\t%s\n", host_sec, final_tick, sim_ticks, sim_sec, cpu_id, msg_id, msg_str.c_str());
    };

    void writeUpdown(double host_sec, uint64_t final_tick, uint64_t sim_ticks, double sim_sec, uint32_t network_id, uint32_t thread_id, uint32_t event_label,
                     uint64_t lane_exec_ticks, uint64_t msg_id, const std::string &msg_str) {
      std::fprintf(log_fp, "%.2f\t%lu\t%lu\t%f\t\t%u\t%u\t%u\t%lu\t%lu\t%s\n", host_sec, final_tick, sim_ticks, sim_sec, network_id, thread_id, event_label,
                   lane_exec_ticks, msg_id, msg_str.c_str());
    };

    /*
     * Register Perflog Callback
     */
    void registerPerflogCallback(void (*cb)(uint32_t network_id, uint32_t thread_id, // IDs
                                            uint32_t event_label,                    // event
                                            uint32_t inc_exec_cycles,                // incremental exec cycles
                                            uint64_t total_exec_cycles,              // total exec cycles
                                            uint32_t msg_id, std::string &msg_str    // message
                                            )) {
      perflog_cb = cb;
    }

    /*
     * Call Perflog Callback
     */
    void perflogCallback(uint32_t network_id, uint32_t thread_id, // IDs
                         uint32_t event_label,                    // event
                         uint32_t inc_exec_cycles,                // incremental exec cycles
                         uint64_t total_exec_cycles,              // total exec cycles
                         uint32_t msg_id, std::string &msg_str    // message
    ) {
      if (perflog_cb != nullptr) {
        perflog_cb(network_id, thread_id, event_label, inc_exec_cycles, total_exec_cycles, msg_id, msg_str);
      }
    }

  }; // class Perflog

  class Tracelog {
  private:
    FILE *log_fp;

    // Tracelog callback
    void (*tracelog_cb)(uint32_t inc_exec_cycles,  // incremental exec cycles
                        std::string &msg_type_str, // type of message
                        std::string &msg_str       // message
                        ) = nullptr;

  public:
    Tracelog() : log_fp(nullptr){};

    ~Tracelog() { this->close(); };

    Tracelog(const std::string &filename) { this->open(filename); };

    bool isOpen() { return log_fp != nullptr; };

    void open(const std::string &filename) {
      if (log_fp != nullptr)
        std::fclose(log_fp);
      log_fp = std::fopen(filename.c_str(), "w");
    };

    void close() {
      if (log_fp != nullptr) {
        std::fclose(log_fp);
        log_fp = nullptr;
      }
    };

    void registerTracelogCallback(void (*cb)(uint32_t inc_exec_cycles,  // incremental exec cycles
                                             std::string &msg_type_str, // type of message
                                             std::string &msg_str       // message
                                             )) {
      tracelog_cb = cb;
    }

    void write(uint64_t sim_ticks, const std::string &msg_type_str, const std::string &msg_str) {
      std::fprintf(log_fp, "%lu:\t[%s]\t%s\n", sim_ticks, msg_type_str.c_str(), msg_str.c_str());
    };

  }; // class Tracelog

public:
  Perflog perflog;
  Tracelog tracelog;
  Logging() : perflog(), tracelog(){};

}; // class Logging

extern Logging globalLogs;

}; // namespace basim