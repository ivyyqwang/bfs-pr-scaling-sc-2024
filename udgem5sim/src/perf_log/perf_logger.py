import pathlib
from google.protobuf.internal.encoder import _VarintBytes
from google.protobuf.internal.decoder import _DecodeVarint32


class PerfLogger:
    def __init__(self, file_name=None, write=False, append=False):
        self.disabled = False
        self.file = None
        self.write_mode = None
        self.read_buf = None
        self.read_cursor = 0
        if file_name is not None:
            self.open(file_name, write, append)

    def disable(self):
        self.disabled = True

    def enable(self):
        self.disabled = False

    def open(self, file_name, write=False, append=False):
        if self.file is not None:
            raise Exception('Log not closed.')
        self.write_mode = write
        if write:
            p = pathlib.Path(file_name)
            pathlib.Path(p.parent).mkdir(parents=True, exist_ok=True)
            if not append:
                self.file = open(file_name, 'wb')
            else:
                self.file = open(file_name, 'ab')
        else:
            self.file = open(file_name, 'rb')
            self.read_cursor = 0
            # currently reading whole file
            self.read_buf = self.file.read()

    def flush(self):
        if self.disabled:
            return
        if self.file is None:
            raise Exception('Log is not opened.')
        if self.write_mode is None or self.write_mode is False:
            raise Exception('Log is not opened in write mode.')
        self.file.flush()

    def close(self):
        if self.file is None:
            raise Exception('Log is not opened.')
        self.file.close()
        self.file = None
        self.write_mode = None

    def reset(self):
        if self.file is None:
            raise Exception('Log is not opened.')
        self.read_cursor = 0

    def write(self, packet):
        if self.disabled:
            return
        if self.file is None:
            raise Exception('Log is not opened.')
        if self.write_mode is None or self.write_mode is False:
            raise Exception('Log is not opened in write mode.')
        size = packet.ByteSize()
        self.file.write(_VarintBytes(size))
        self.file.write(packet.SerializeToString())

    def read(self, packet):
        if self.file is None:
            raise Exception('Log is not opened.')
        if self.write_mode is None or self.write_mode is True:
            raise Exception('Log is not opened in read mode.')
        if self.read_cursor < len(self.read_buf):
            msg_len, new_pos = _DecodeVarint32(self.read_buf, self.read_cursor)
            self.read_cursor = new_pos
            msg_buf = self.read_buf[self.read_cursor : self.read_cursor + msg_len]
            self.read_cursor += msg_len
            packet.ParseFromString(msg_buf)
            return packet
        else:
            return None


def read_example():
    logger = PerfLogger('test_log2.bin', write=False)

    hdr = logger.read(perf_log_packet_pb2.PerfLogHeader())
    print(hdr.obj_id)

    pkt = logger.read(perf_log_packet_pb2.PerfLogPacket())
    print(pkt.sim_timestamp)
    for cur_updown in pkt.updown:
        print(cur_updown.updown_id)
        print(cur_updown.lane_id)
        print(cur_updown.thread_id)
        print(cur_updown.event_base)
        print(cur_updown.event_label)
        if cur_updown.HasField('queue_stats'):
            print(cur_updown.queue_stats.event_q_len)
            print(cur_updown.queue_stats.operand_q_len)

    logger.close()


def write_example():
    logger = PerfLogger('test_log2.bin', write=True)

    hdr = perf_log_packet_pb2.PerfLogHeader()
    hdr.obj_id = 'py_test_write'
    hdr.tick_freq = 123456
    logger.write(hdr)

    pkt = perf_log_packet_pb2.PerfLogPacket()
    pkt.sim_timestamp = 789
    cur_updown = pkt.updown.add()
    cur_updown.updown_id = 0
    cur_updown.lane_id = 0
    cur_updown.thread_id = 0
    cur_updown.event_base = 0
    cur_updown.event_label = 0
    cur_updown.queue_stats.event_q_len = 987
    cur_updown.queue_stats.operand_q_len = 123
    logger.write(pkt)

    logger.close()


if __name__ == '__main__':
    import perf_log_packet_pb2
    # write_example()
    read_example()
