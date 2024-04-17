import sys
from perf_logger import PerfLogger
import perf_log_packet_pb2

if __name__ == '__main__':
    logger = PerfLogger(sys.argv[1], write=False)
    hdr = logger.read(perf_log_packet_pb2.PerfLogHeader())
    pkts = []
    pkt = logger.read(perf_log_packet_pb2.PerfLogPacket())
    while pkt is not None:
        print('>>>> Packet Timestamp', pkt.sim_timestamp, '>>>>')
        if pkt.HasField('updown'):
            print('@ UpDown @')
            print('updown_id =', pkt.updown.updown_id)
            print('lane_id =', pkt.updown.lane_id)
            if pkt.updown.HasField('thread_id'):
                print('thread_id =', pkt.updown.thread_id)
            if pkt.updown.HasField('event_base'):
                print('event_base =', pkt.updown.event_base)
            if pkt.updown.HasField('event_label'):
                print('event_label =', pkt.updown.event_label)
            print()

            if pkt.updown.HasField('queue_stats'):
                print('# Queue Stats')
                print('event_q_len =', pkt.updown.queue_stats.event_q_len)
                print('operand_q_len =', pkt.updown.queue_stats.operand_q_len)
                print()

            if pkt.updown.HasField('cycle_stats'):
                print('# Cycle Stats')
                print('cycles =', pkt.updown.cycle_stats.cycles)
                print('exec_cycles =', pkt.updown.cycle_stats.exec_cycles)
                print('idle_cycles =', pkt.updown.cycle_stats.idle_cycles)
                print('last_exec_cycles =', pkt.updown.cycle_stats.last_exec_cycles)
                print()

            if pkt.updown.HasField('action_stats'):
                print('# Action Stats')
                print('total_actions =', pkt.updown.action_stats.total_actions)
                print('message_actions =', pkt.updown.action_stats.message_actions)
                print('move_actions =', pkt.updown.action_stats.move_actions)
                print('alu_actions =', pkt.updown.action_stats.alu_actions)
                print('branch_actions =', pkt.updown.action_stats.branch_actions)
                print('yield_actions =', pkt.updown.action_stats.yield_actions)
                print('cmpswp_actions =', pkt.updown.action_stats.cmpswp_actions)
                print()

            if pkt.updown.HasField('local_mem_stats'):
                print('# Local Memory Stats')
                print('read_bytes =', pkt.updown.local_mem_stats.read_bytes)
                print('write_bytes =', pkt.updown.local_mem_stats.write_bytes)
                print()

            if pkt.updown.HasField('mem_intf_stats'):
                print('# Memory Interface Stats')
                print('read_bytes =', pkt.updown.mem_intf_stats.read_bytes)
                print('write_bytes =', pkt.updown.mem_intf_stats.write_bytes)
                print()
        print()
        pkts.append(pkt)
        pkt = logger.read(perf_log_packet_pb2.PerfLogPacket())

