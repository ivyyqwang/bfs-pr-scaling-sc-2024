from libraries.LMStaticMaps.LMStaticMap import *
from KVMSRMachineConfig import *


UDKVMSR_INIT_NUM_OPS = 5

SEND_BUFFER_SIZE = 8
FLAG = 1

DEBUG_FLAG = False

SPLIT_V_SHT_OFFSET  = SHT_0_OFFSET
HIGH_DEG_SHT_OFFSET = SHT_1_OFFSET
UDKVMSR_LM_OFFSET   = UDKVMSR_0_OFFSET

KVMSR_SEND_BUFFER_OFFSET = UDKVMSR_LM_OFFSET + (8 * WORD_SIZE)
KVMSR_INPUT_OFFSET  = UDKVMSR_LM_OFFSET + (16 * WORD_SIZE)
KVMSR_OUTPUT_OFFSET = UDKVMSR_LM_OFFSET + (24 * WORD_SIZE)

SPLIT_V_DATA_OFFSET = UDKVMSR_LM_OFFSET + (24 * WORD_SIZE)
ALLOC_E_DATA_OFFSET = UDKVMSR_LM_OFFSET + (24 * WORD_SIZE)
BUILD_N_DATA_OFFSET = UDKVMSR_LM_OFFSET + ((16 + 2) * WORD_SIZE)

'''
Struct Edge {
    int64_t src;
    int64_t dst;
}
'''
EDGE_STRUCT_SIZE    = 2
'''
Struct Vertex {
    int64_t     degree;
    int64_t     orig_vid;
    int64_t     vid;
    int64_t*    neighbors; 
    int64_t     distance;
    int64_t     parent;
    int64_t     split_vids; (optional)
    int64_t     padding;
}
'''
VERTEX_STRUCT_SIZE  = 8
'''
struct Vertex_Count {
    int64_t     vid;
    int64_t     count;
}
'''
VERTEX_COUNT_STRUCT_SIZE = 1

SHT_INIT_NUM_OPS    = 5
SHT_DESC_SIZE       = 4 
SHT_DESC_BSIZE      = SHT_DESC_SIZE * WORD_SIZE

SINGLE_WORD_SHT_INIT_NUM_OPS = 8
SINGLE_WORD_SHT_DESC_SIZE    = 5

KVMSR_CACHE_OFFSET      = HEAP_OFFSET
KVMSR_CAHCE_ENTRY_SIZE  = 2
KVMSR_CACHE_NUM_ENTRIES = ((1<<(16 - LOG2_WORD_SIZE)) - KVMSR_CACHE_OFFSET) // KVMSR_CAHCE_ENTRY_SIZE

MAX_SAMPLING_MAP_THREADS        = 40
MAX_SAMPLING_REDUCE_THREADS     = 175
MAX_VERTEX_SPLIT_MAP_THREADS    = 120
MAX_EDGE_SPLIT_MAP_THREADS      = 2
MAX_EDGE_SPLIT_REDUCE_THREADS   = 142
MAX_ALLOC_NLIST_MAP_THREADS     = 125
MAX_BUILD_NLSIT_MAP_THREADS     = 155

'''
Original vertex ID -> (split base vertex ID, number of split vertices)
Split vertex ID -> (original vertex ID, [split vertex ID base | split vertex ID boundary])
'''
SPLIT_V_SHT_VALUE_SIZE  = 2

LM_CACHE_META_OFFSET    = CACHE_0_OFFSET
LM_CACHE_OFFSET         = HEAP_OFFSET
LM_CACHE_ENTRY_SIZE     = 2
LM_CACHE_NUM_ENTRIES    = ((1<<(16 - LOG2_WORD_SIZE)) - LM_CACHE_OFFSET) // LM_CACHE_ENTRY_SIZE

SHT_INIT_EV_LABEL       = "SHT_init"
SHT_INIT_RET_EV_LABEL   = "SHT_init_return"
BCST_SHT_EV_LABEL       = "broadcast_sht_descriptor"
SINGLE_WORD_SHT_INIT_EV_LABEL   = "single_word_SHT_init"

BROADCAST_ID = "Broadcast"
BCST_EV_LABEL = f"{BROADCAST_ID}::broadcast_global"
BCST_VALUE_EV_LABEL = f"{BROADCAST_ID}::broadcast_value_to_scratchpad"

SAMPLING_RATE   = 1
