import os
import json
from perf_log_schema import PerfLogSchema


class PerfLogger:
    def __init__(self, file_name=None, fmt='json', append=False):
        self.file = None
        self.fmt = None
        if file_name is not None:
            self.open(file_name, fmt, append)

    def open(self, file_name, fmt='json', append=False):
        if self.file is not None:
            raise Exception('Log not closed.')
        self.fmt = fmt
        if not append:
            self.file = open(file_name, 'w+')
            if fmt == 'json':
                self.file.write('[\n')
        else:
            self.file = open(file_name, 'a+')
            if fmt == 'json':
                # Remove the JSON file existing closing bracket
                cur_pos = self.file.tell() - 1
                cur_char = self.file.read(1)
                while cur_pos > 0 and cur_char != ']':
                    if cur_char != '' and cur_char != '\n' and cur_char != '\r' and cur_char != ' ':
                        raise Exception('JSON log not ending with \']\'?')
                    cur_pos -= 1
                    self.file.seek(cur_pos, os.SEEK_SET)
                    cur_char = self.file.read(1)
                cur_pos -= 1
                self.file.seek(cur_pos, os.SEEK_SET)
                self.file.truncate()
                self.file.write(',\n')

    def flush(self):
        if self.file is None:
            raise Exception('Log is not opened.')
        self.file.flush()

    def close(self):
        if self.file is None:
            raise Exception('Log is not opened.')
        if self.fmt == 'json':
            cur_pos = self.file.tell() - 2
            self.file.seek(cur_pos, os.SEEK_SET)
            self.file.truncate()
            self.file.write('\n]\n')
        self.file.close()
        self.file = None

    def write_record(self, packet):
        json.dump(packet, self.file)
        self.file.write(',\n')

    def record_system(self, sim_ts, pl_id=None, pl_pkt=None):
        if self.file is None:
            raise Exception('Log is not opened.')

        pkt = PerfLogSchema.packet.copy()
        pkt['sim_ts'] = sim_ts
        pkt['area_id'] = PerfLogSchema.map_area_id['sys']
        pkt['area_pkt'] = PerfLogSchema.packet_system.copy()
        pkt['area_pkt']['pl_id'] = pl_id
        pkt['area_pkt']['pl_pkt'] = pl_pkt
        self.write_record(pkt)

    def record_top(self, sim_ts, skt_id, core_id, thd_id, pl_id=None, pl_pkt=None):
        if self.file is None:
            raise Exception('Log is not opened.')

        pkt = PerfLogSchema.packet.copy()
        pkt['sim_ts'] = sim_ts
        pkt['area_id'] = PerfLogSchema.map_area_id['top']
        pkt['area_pkt'] = PerfLogSchema.packet_top.copy()
        pkt['area_pkt']['skt_id'] = skt_id
        pkt['area_pkt']['core_id'] = core_id
        pkt['area_pkt']['thd_id'] = thd_id
        pkt['area_pkt']['pl_id'] = pl_id
        pkt['area_pkt']['pl_pkt'] = pl_pkt
        self.write_record(pkt)

    def record_updown(self, sim_ts, ud_id, lane_id, evt_lbl, thd_id, pl_id=None, pl_pkt=None):
        if self.file is None:
            raise Exception('Log is not opened.')

        pkt = PerfLogSchema.packet.copy()
        pkt['sim_ts'] = sim_ts
        pkt['area_id'] = PerfLogSchema.map_area_id['ud']
        pkt['area_pkt'] = PerfLogSchema.packet_updown.copy()
        pkt['area_pkt']['ud_id'] = ud_id
        pkt['area_pkt']['lane_id'] = lane_id
        pkt['area_pkt']['evt_lbl'] = evt_lbl
        pkt['area_pkt']['thd_id'] = thd_id
        pkt['area_pkt']['pl_id'] = pl_id
        pkt['area_pkt']['pl_pkt'] = pl_pkt
        self.write_record(pkt)


if __name__ == '__main__':
    logger = PerfLogger('test_log.json')
    logger.record_system(123)
    logger.record_top(123, 0, 0, 0)
    logger.record_updown(123, 0, 0, 0, 'label', 0)
    logger.close()
    logger.open('test_log.json', append=True)
    logger.record_system(123)
    logger.close()
