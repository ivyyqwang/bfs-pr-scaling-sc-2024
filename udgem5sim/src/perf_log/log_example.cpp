#include <iostream>
#include "protoio.hh"
#include "perf_log_packet.pb.h"

void write_log_stream()
{
  // Create log stream
  auto log_stream = new PerfLog::ProtoOutputStream("test_log.bin");

  // Write header
  ProtoPerfLog::PerfLogHeader header_msg;
  header_msg.set_obj_id("test_log");
  header_msg.set_tick_freq(12345);
  log_stream->write(header_msg);

  // Write packet
  ProtoPerfLog::PerfLogPacket packet_msg;
  packet_msg.set_sim_timestamp(54321);
  auto updown_msg = packet_msg.add_updown();
  updown_msg->set_updown_id(0);
  updown_msg->set_lane_id(0);
  updown_msg->set_thread_id(0);
  updown_msg->set_event_base(123);
  updown_msg->set_event_label(321);
  auto updown_q_stats_msg = updown_msg->mutable_queue_stats();
  updown_q_stats_msg->set_event_q_len(1);
  updown_q_stats_msg->set_operand_q_len(2);
  // updown_q_stats_msg->set_snoop_q_len(3);
  log_stream->write(packet_msg);
  
  // Close log stream
  if (log_stream != nullptr)
    delete log_stream;
}

void read_log_stream()
{
  auto log_stream = new PerfLog::ProtoInputStream("test_log.bin");

  // Read header
  ProtoPerfLog::PerfLogHeader header_msg;
  if (!log_stream->read(header_msg))
  {
    std::cerr << "error reading header!" << std::endl;
    exit(1);
  }
  std::cout << "obj_id = " << header_msg.obj_id() << std::endl;
  std::cout << "tick_freq = " << header_msg.tick_freq() << std::endl;

  // Read packet
  ProtoPerfLog::PerfLogPacket packet_msg;
  if (!log_stream->read(packet_msg))
  {
    std::cerr << "error reading header!" << std::endl;
    exit(1);
  }
  std::cout << "sim_timestamp = " << packet_msg.sim_timestamp() << std::endl;
  for (int i = 0; i < packet_msg.updown_size(); i++)
  {
    if (packet_msg.updown(i).has_queue_stats())
      std::cout << "event_q_len = " << packet_msg.updown(i).queue_stats().event_q_len() << std::endl;
  }
}

int main(int argc, char *argv[])
{
  write_log_stream();
  read_log_stream();
}

