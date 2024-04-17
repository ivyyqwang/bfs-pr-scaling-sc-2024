import os
import sys
import pathlib
import json


class PerfLogSchema:
    # top level packet
    packet = {
        # 'wall_ts': None,
        'sim_ts': None,  # simulation timestamp, 64-bit counter
        'area_id': None,  # integer
        'area_pkt': None,  # Packet for the corresponding area
    }

    # map from area name to area id
    map_area_id = {
        'sys': 0,
        'top': 1,
        'ud': 2,
    }

    # map from payload id to payload packet schema
    map_payload_packets = {
        # system area payloads
        0x000: None,
        # top area payloads
        0x400: None,
        # updown area payloads
        0x800: None,
    }

    # system area log schema
    packet_system = {
        'cycle': None,
        'pl_id': None,  # Payload ID
        'pl_pkt': None,  # Payload Packet
    }

    # top area log schema
    packet_top = {
        'skt_id': None,  # Socket ID
        'core_id': None,  # Core ID
        'thd_id': None,  # Software Thread ID
        'cycle': None,

        'pl_id': None,  # Payload ID
        'pl_pkt': None,  # Payload Packet
    }

    # updown area log schema
    packet_updown = {
        'ud_id': None,  # UpDown ID
        'lane_id': None,  # Lane ID
        'evt_lbl': None,  # Event Label
        'thd_id': None,  # Thread ID
        'cycle': None,

        'pl_id': None,  # Payload ID
        'pl_pkt': None,  # Payload Packet
    }

    def dump_json(dir_path):
        '''
            Dump the schema to .json files for other language bindings.
        '''
        pathlib.Path(dir_path).mkdir(parents=True, exist_ok=True)
        with open(os.path.join(dir_path, 'packet.json'), 'w') as f:
            json.dump(PerfLogSchema.packet, f, indent=4)
        with open(os.path.join(dir_path, 'map_area_id.json'), 'w') as f:
            json.dump(PerfLogSchema.map_area_id, f, indent=4)
        with open(os.path.join(dir_path, 'map_payload_packets.json'), 'w') as f:
            json.dump(PerfLogSchema.map_payload_packets, f, indent=4)
        with open(os.path.join(dir_path, 'packet_system.json'), 'w') as f:
            json.dump(PerfLogSchema.packet_system, f, indent=4)
        with open(os.path.join(dir_path, 'packet_top.json'), 'w') as f:
            json.dump(PerfLogSchema.packet_top, f, indent=4)
        with open(os.path.join(dir_path, 'packet_updown.json'), 'w') as f:
            json.dump(PerfLogSchema.packet_updown, f, indent=4)
        print('Dumped all schema json files to {} .'.format(dir_path))


if __name__ == '__main__':
    if len(sys.argv) != 2:
        sys.exit("Usage: {} <folder for json schema dumping>".format(sys.argv[0]))
    PerfLogSchema.dump_json(sys.argv[1])
