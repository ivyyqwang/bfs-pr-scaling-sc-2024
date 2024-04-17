from EFA_v2 import EFA, State, Transition
import sht_macros
from sht_bucket import SHTArrayBucket
import math


class SHT:
    """
    struct SHT_DESC {
        WORD START_NWID;
        WORD NUM_ALLOC_LANES;
        WORD BUCKET_DESC_LM_ADDR;
        WORD DRAM_ALLOC_ADDR;
        WORD BUCKETS_PER_LANE;
        # WORD ENTRY_SIZE;
        # WORD ENTRIES_PER_BUCKET;
        TODO: possible to calculate number of buckets bits and number of lanes bits once and store
    }
    """

    DESC_WORD_CNT = 5
    DESC_SIZE = DESC_WORD_CNT * 8

    DESC_STRUCT_OFF_START_NWID = 0
    DESC_STRUCT_OFF_NUM_ALLOC_LANES = 8
    DESC_STRUCT_OFF_BUCKET_DESC_LM_ADDR = 16
    DESC_STRUCT_OFF_DRAM_ALLOC_ADDR = 24
    DESC_STRUCT_OFF_BUCKETS_PER_LANE = 32

    LANES_PER_UD = 64
    LANES_MASK = LANES_PER_UD - 1

    KEY_SIZE = 8
    WORD_SIZE = 8
    ENTRY_SIZE = KEY_SIZE + WORD_SIZE

    @classmethod
    def setup(cls, state: State, debug=False) -> None:
        cls.DEBUG = debug

        # TODO: code injection
        SHTArrayBucket.setup(state, debug=debug)
        cls._initialize(state)
        cls._finalize(state)
        cls._update(state)
        cls._get(state)
        # cls._delete(state)

    @classmethod
    def _initialize(cls, state: State):
        """
        X8  - SHT_DESC_LM_OFFSET
        X9  - TMP_BUF_LM_OFFSET

        X10 - START_NWID
        X11 - NUM_ALLOC_LANES
        X12 - BUCKET_DESC_LM_ADDR
        X13 - DRAM_ALLOC_ADDR
        X14 - BUCKETS_PER_LANE
        X15 - ENTRIES_PER_BUCKET
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._initialize.__name__

        OB_SHT_DESC_LM_OFFSET           = 'X8'
        OB_TMP_BUF_LM_OFFSET            = 'X9'

        OB_START_NWID                 = 'X10'
        OB_NUM_ALLOC_LANES            = 'X11'
        OB_BUCKET_DESC_LM_OFFSET      = 'X12'
        OB_DRAM_ALLOC_ADDR            = 'X13'
        OB_BUCKETS_PER_LANE           = 'X14'
        OB_ENTRIES_PER_BUCKET         = 'X15'

        NUM_OPS = 8

        REG_TMP0 = "X16"
        REG_TMP1 = "X17"
        REG_TMP2 = "X18"
        REG_TMP3 = "X19"
        REG_TMP4 = "X20"
        REG_DRAM_ALLOC_SIZE_PER_BUCKET = "X21"
        REG_CUR_BUCKET_DRAM_ADDR = "X22"
        REG_TMP7 = "X23"
        REG_LANE_BUCKET_CNT = "X24"
        REG_TMP8 = "X25"

        REG_CONT = "X31"

        tran = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR")
        if tran is None:
            return
        tran_lane_init_ret = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-lane_init_ret")
        cls.tran_label_init = tran.getLabel()

        # TRAN - entry
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] INIT' {'X0'}")
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] INIT, num_alloc_lanes = %d, bucket_per_lane = %d, ent_per_bucket = %d' {'X0'} {OB_NUM_ALLOC_LANES} {OB_BUCKETS_PER_LANE} {OB_ENTRIES_PER_BUCKET}")
        # Save continuation
        tran.writeAction(f"addi {'X1'} {REG_CONT} {0}")

        # Copy OB and set descriptor (X10 ~ X14)
        tran.writeAction(f"mov_imm2reg {REG_TMP0} {NUM_OPS - 2}")
        tran.writeAction(f"add {OB_SHT_DESC_LM_OFFSET} {'X7'} {REG_TMP1}")
        tran.writeAction(f"bcopy_ops {OB_START_NWID} {REG_TMP1} {REG_TMP0}")

        # Initalize allocated lanes
        # TODO: use UDKVMSR?
        # tmp0 -> current nwid
        REG_ALIAS_NWID_CNT = REG_TMP0
        tran.writeAction(f"mov_reg2reg {OB_START_NWID} {REG_ALIAS_NWID_CNT}")
        # tmp1 -> end nwid
        tran.writeAction(f"add {OB_START_NWID} {OB_NUM_ALLOC_LANES} {REG_TMP1}")

        # tmp2 -> current bucket desc lm offset
        tran.writeAction(f"addi {OB_BUCKET_DESC_LM_OFFSET} {REG_TMP2} {0}")

        # tmp3 -> tmp buffer start lm offset
        tran.writeAction(f"muli {OB_BUCKETS_PER_LANE} {REG_TMP3} {SHTArrayBucket.DESC_SIZE}")
        tran.writeAction(f"add {REG_TMP3} {REG_TMP2} {REG_TMP3}")

        # tmp5 -> dram alloc size per bucket
        tran.writeAction(f"lshift {OB_ENTRIES_PER_BUCKET} {REG_DRAM_ALLOC_SIZE_PER_BUCKET} {int(math.log2(cls.ENTRY_SIZE))}")
        # tmp6 -> dram addr for current bucket
        tran.writeAction(f"addi {OB_DRAM_ALLOC_ADDR} {REG_CUR_BUCKET_DRAM_ADDR} {0}")
        # init the bucket per lane counter
        tran.writeAction(f"mov_imm2reg {REG_LANE_BUCKET_CNT} {0}")

        # Prepare call args
        tran.writeAction(f"add {OB_TMP_BUF_LM_OFFSET} {'X7'} {REG_TMP7}")
        tran.writeAction(f"move {OB_ENTRIES_PER_BUCKET} {cls.WORD_SIZE * 2}({REG_TMP7}) 0 8")  # num_entries
        tran.writeAction(f"move {REG_TMP3} {cls.WORD_SIZE * 3}({REG_TMP7}) 0 8")  # lm_buf_offset

        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-lane_init_next'}: move {REG_TMP2} {0}({REG_TMP7}) 0 8")  # desc_lm_offset
        tran.writeAction(f"move {REG_CUR_BUCKET_DRAM_ADDR} {cls.WORD_SIZE}({REG_TMP7}) 0 8")  # dram_alloc_start_addr

        # Call
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] INIT: dst nwid = %d, bucket = %d, bucket desc lm addr = %d' {'X0'} {REG_ALIAS_NWID_CNT} {REG_LANE_BUCKET_CNT} {REG_TMP2}")
        SHTArrayBucket.initialize(tran=tran, ret=tran_lane_init_ret.getLabel(), tmp_reg0=REG_TMP8, tmp_reg1=REG_TMP4, arg_lm_addr_reg=REG_TMP7, dst_nwid_reg=REG_ALIAS_NWID_CNT)

        # Prepare for the next call
        tran.writeAction(f"add {REG_CUR_BUCKET_DRAM_ADDR} {REG_DRAM_ALLOC_SIZE_PER_BUCKET} {REG_CUR_BUCKET_DRAM_ADDR}")
        tran.writeAction(f"addi {REG_TMP2} {REG_TMP2} {SHTArrayBucket.DESC_SIZE}")
        tran.writeAction(f"addi {REG_LANE_BUCKET_CNT} {REG_LANE_BUCKET_CNT} {1}")
        tran.writeAction(f"blt {REG_LANE_BUCKET_CNT} {OB_BUCKETS_PER_LANE} {f'{CLS_NAME}-{FN_NAME}-TR-LB-lane_init_next'}")

        # next lane
        tran.writeAction(f"addi {REG_ALIAS_NWID_CNT} {REG_ALIAS_NWID_CNT} {1}")
        tran.writeAction(f"bge {REG_ALIAS_NWID_CNT} {REG_TMP1} {f'{CLS_NAME}-{FN_NAME}-TR-LB-lane_init_done'}")
        tran.writeAction(f"mov_imm2reg {REG_LANE_BUCKET_CNT} {0}")  # reset the bucket per lane counter
        tran.writeAction(f"addi {OB_BUCKET_DESC_LM_OFFSET} {REG_TMP2} {0}")
        tran.writeAction(f"blt {REG_ALIAS_NWID_CNT} {REG_TMP1} {f'{CLS_NAME}-{FN_NAME}-TR-LB-lane_init_next'}")

        # Init barrier counter
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-lane_init_done'}: mul {OB_NUM_ALLOC_LANES} {OB_BUCKETS_PER_LANE} {REG_TMP7}")
        tran.writeAction("yield")

        # TRAN - return barrier
        tran_lane_init_ret.writeAction(f"subi {REG_TMP7} {REG_TMP7} {1}")
        if cls.DEBUG:
            tran_lane_init_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] INIT: bucket on NWID %d initialized.' {'X0'} {'X8'}")
        tran_lane_init_ret.writeAction(f"bnei {REG_TMP7} {0} {f'{CLS_NAME}-{FN_NAME}-TR-lane_init_ret-LB-yield'}")
        if cls.DEBUG:
            tran_lane_init_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] INIT: done, terminating' {'X0'}")
        sht_macros.return_wreg(tran_lane_init_ret, REG_CONT, 'X0', 'X0')
        tran_lane_init_ret.writeAction("yield_terminate")
        tran_lane_init_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-lane_init_ret-LB-yield'}: yield")

    @classmethod
    def _finalize(cls, state: State) -> None:
        """
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._finalize.__name__

        tran = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR")
        if tran is None:
            return
        REG_TMP0 = 'X16'
        sht_macros.return_wreg(tran, 'X1', 'X0', 'X0')
        tran.writeAction("yield_terminate")

    @classmethod
    def _update(cls, state: State) -> None:
        """
         X8 - sht_desc_lm_offset
         X9 - tmp_buf_lm_offset
        X10 - key
        X11 - value
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._update.__name__

        OB_SHT_DESC_LM_OFFSET = 'X8'
        OB_TMP_BUF_LM_OFFSET = 'X9'
        OB_KEY = 'X10'
        OB_VAL = 'X11'

        REG_TMP0 = 'X16'
        REG_TMP1 = 'X17'
        REG_TMP2 = 'X18'
        REG_TMP3 = 'X19'
        REG_TMP4 = 'X20'
        REG_TMP5 = 'X21'
        REG_SHT_DESC_LM_ADDR = 'X22'
        REG_TMP_BUF_LM_ADDR = 'X23'

        # REG_CONT = "X31"

        tran = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR")
        if tran is None:
            return
        cls.tran_label_update = tran.getLabel()

        tran.writeAction(f"add {OB_SHT_DESC_LM_OFFSET} {'X7'} {REG_SHT_DESC_LM_ADDR}")
        tran.writeAction(f"add {OB_TMP_BUF_LM_OFFSET} {'X7'} {REG_TMP_BUF_LM_ADDR}")
        # hash the destination lane id
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: key = %d' {'X0'} {OB_KEY}")
        tran.writeAction(f"mov_imm2reg {REG_TMP0} {0}")  # tmp0 -> seed
        tran.writeAction(f"hash {OB_KEY} {REG_TMP0}")  # tmp0 -> hash
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: hash = %d' {'X0'} {REG_TMP0}")
        # calc dest lane
        tran.writeAction(f"move {cls.DESC_STRUCT_OFF_NUM_ALLOC_LANES}({REG_SHT_DESC_LM_ADDR}) {REG_TMP1} 0 8")  # tmp1 -> num lane
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: num lane = %d' {'X0'} {REG_TMP1}")
        tran.writeAction(f"subi {REG_TMP1} {REG_TMP1} {1}")  # tmp1 -> lane mask
        tran.writeAction(f"andr {REG_TMP0} {REG_TMP1} {REG_TMP2}")  # tmp2 -> nwid offset
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: nwid offset = %d' {'X0'} {REG_TMP2}")
        tran.writeAction(f"move {cls.DESC_STRUCT_OFF_START_NWID}({REG_SHT_DESC_LM_ADDR}) {REG_TMP3} 0 8")  # tmp3 -> start nwid
        tran.writeAction(f"add {REG_TMP3} {REG_TMP2} {REG_TMP3}")  # tmp3 -> dest nwid
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: dst nwid = %d' {'X0'} {REG_TMP3}")

        tran.writeAction(f"andi {REG_TMP3} {REG_TMP2} {cls.LANES_MASK}")  # tmp2 -> lane offset in ud

        tran.writeAction(f"move {cls.DESC_STRUCT_OFF_BUCKETS_PER_LANE}({REG_SHT_DESC_LM_ADDR}) {REG_TMP1} 0 8")  # tmp1 -> number of bucket per lane

        # bucket per lane * lane offset
        tran.writeAction(f"subi {REG_TMP1} {REG_TMP1} {1}")  # tmp1 -> lane bucket off mask
        tran.writeAction(f"rshift {REG_TMP0} {REG_TMP0} {32}")  # low 32b hash for nwid
        tran.writeAction(f"andr {REG_TMP0} {REG_TMP1} {REG_TMP1}")  # tmp1 -> lane bucket offset
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: lane bucket off = %d' {'X0'} {REG_TMP1}")
        tran.writeAction(f"muli {REG_TMP1} {REG_TMP1} {SHTArrayBucket.DESC_SIZE}")

        tran.writeAction(f"move {cls.DESC_STRUCT_OFF_BUCKET_DESC_LM_ADDR}({REG_SHT_DESC_LM_ADDR}) {REG_TMP4} 0 8")  # tmp4 -> bucket desc lm offset base
        tran.writeAction(f"add {REG_TMP4} {REG_TMP1} {REG_TMP1}")  # tmp1 -> bucket desc lm addr

        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: bucket desc lm offset = %d' {'X0'} {REG_TMP1}")

        # write to LM buf for calling
        tran.writeAction(f"move {REG_TMP1} {0}({REG_TMP_BUF_LM_ADDR}) 0 8")
        tran.writeAction(f"move {OB_KEY} {cls.WORD_SIZE}({REG_TMP_BUF_LM_ADDR}) 0 8")
        tran.writeAction(f"move {OB_VAL} {cls.WORD_SIZE * 2}({REG_TMP_BUF_LM_ADDR}) 0 8")

        SHTArrayBucket.update_wcont(tran=tran, ret='X1', tmp_reg0=REG_TMP4, arg_lm_addr_reg=REG_TMP_BUF_LM_ADDR, arg_lm_words=3, dst_nwid_reg=REG_TMP3)
        tran.writeAction("yield_terminate")

    @classmethod
    def _get(cls, state: State) -> None:
        """
         X8 - sht_desc_lm_offset
         X9 - key
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._get.__name__

        OB_SHT_DESC_LM_OFFSET = 'X8'
        OB_KEY = 'X9'

        REG_TMP0 = 'X16'
        REG_TMP1 = 'X17'
        REG_TMP2 = 'X18'
        REG_TMP3 = 'X19'
        REG_TMP4 = 'X20'
        REG_TMP5 = 'X21'
        REG_SHT_DESC_LM_ADDR = 'X22'

        tran = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR")
        if tran is None:
            return
        cls.tran_label_get = tran.getLabel()

        tran.writeAction(f"add {OB_SHT_DESC_LM_OFFSET} {'X7'} {REG_SHT_DESC_LM_ADDR}")
        # hash the destination lane id
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] GET: key = %d' {'X0'} {OB_KEY}")
        tran.writeAction(f"mov_imm2reg {REG_TMP0} {0}")  # tmp0 -> seed
        tran.writeAction(f"hash {OB_KEY} {REG_TMP0}")  # tmp0 -> hash
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] GET: hash = %d' {'X0'} {REG_TMP0}")
        # calc dest lane
        tran.writeAction(f"move {cls.DESC_STRUCT_OFF_NUM_ALLOC_LANES}({REG_SHT_DESC_LM_ADDR}) {REG_TMP1} 0 8")  # tmp1 -> num lane
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] GET: num lane = %d' {'X0'} {REG_TMP1}")
        tran.writeAction(f"subi {REG_TMP1} {REG_TMP1} {1}")  # tmp1 -> lane mask
        tran.writeAction(f"andr {REG_TMP0} {REG_TMP1} {REG_TMP2}")  # tmp2 -> nwid offset
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] GET: nwid offset = %d' {'X0'} {REG_TMP2}")
        tran.writeAction(f"move {cls.DESC_STRUCT_OFF_START_NWID}({REG_SHT_DESC_LM_ADDR}) {REG_TMP3} 0 8")  # tmp3 -> start nwid
        tran.writeAction(f"add {REG_TMP3} {REG_TMP2} {REG_TMP3}")  # tmp3 -> dest nwid
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] GET: dst nwid = %d' {'X0'} {REG_TMP3}")

        tran.writeAction(f"andi {REG_TMP3} {REG_TMP2} {cls.LANES_MASK}")  # tmp2 -> lane offset in ud

        tran.writeAction(f"move {cls.DESC_STRUCT_OFF_BUCKETS_PER_LANE}({REG_SHT_DESC_LM_ADDR}) {REG_TMP1} 0 8")  # tmp1 -> number of bucket per lane

        tran.writeAction(f"subi {REG_TMP1} {REG_TMP1} {1}")  # tmp1 -> lane bucket off mask
        tran.writeAction(f"rshift {REG_TMP0} {REG_TMP0} {32}")  # low 32b hash for nwid
        tran.writeAction(f"andr {REG_TMP0} {REG_TMP1} {REG_TMP1}")  # tmp1 -> lane bucket offset
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] GET: lane bucket off = %d' {'X0'} {REG_TMP1}")
        tran.writeAction(f"muli {REG_TMP1} {REG_TMP1} {SHTArrayBucket.DESC_SIZE}")

        tran.writeAction(f"move {cls.DESC_STRUCT_OFF_BUCKET_DESC_LM_ADDR}({REG_SHT_DESC_LM_ADDR}) {REG_TMP4} 0 8")  # tmp4 -> bucket desc lm offset base
        tran.writeAction(f"add {REG_TMP4} {REG_TMP1} {REG_TMP1}")  # tmp1 -> bucket desc lm offset

        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] GET: bucket desc lm offset = %d' {'X0'} {REG_TMP1}")

        # FIXME
        SHTArrayBucket.get_wcont(tran=tran, ret='X1', tmp_reg=REG_TMP4, desc_lm_offset_reg=REG_TMP1, key_reg=OB_KEY, dst_nwid_reg=REG_TMP3)
        tran.writeAction("yield_terminate")
