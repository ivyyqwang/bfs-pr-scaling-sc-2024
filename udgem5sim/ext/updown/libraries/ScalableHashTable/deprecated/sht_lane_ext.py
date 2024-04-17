from EFA_v2 import EFA, State, Transition
import sht_macros
from memcpy import Memcpy
import math


class SHTLane:
    """
    struct SHTLaneDesc {
        WORD NUM_ALLOC_LANES(0:31) | START_NWID(32:63);
        WORD LANE_DESC_LM_OFFSET(0:31) | BUCKETS_PER_LANE(32:63);
        WORD ENTRIES_PER_BUCKET(0:31) | VAL_NUM_WORDS(32:63);
    // -------- EXTENSION --------
    // for next SHT
        WORD NUM_ALLOC_LANES(0:31) | START_NWID(32:63);
        WORD LANE_DESC_LM_OFFSET(0:31) | BUCKETS_PER_LANE(32:63);
        WORD ENTRIES_PER_BUCKET(0:31) | VAL_NUM_WORDS(32:63);
    // -------- PER BUCKET DESC (x BUCKETS_PER_LANE) -------
        struct SHTBucketDesc {
            WORD LOCK(0:31) | ENTRY_COUNT(32:63);
            WORD DRAM_KEY_START_ADDR;
            WORD DRAM_VAL_START_ADDR;
            WORD BUCKET_LM_BUF[8];
        }
    }
    """

    WORD_SIZE = 8
    KEY_SIZE = 8
    LM_BUF_SIZE = 64

    LANE_DESC_SIZE = 3 * WORD_SIZE
    # LITTLE ENDIAN
    # LANE_DESC_STURCT_OFF_NUM_ALLOC_LANES = 0  # 4 bytes
    # LANE_DESC_STURCT_OFF_START_NWID = 4  # 4 bytes
    # LANE_DESC_STURCT_OFF_LANE_DESC_LM_OFFSET = 8  # 4 bytes
    # LANE_DESC_STURCT_OFF_BUCKETS_PER_LANE = 12  # 4 bytes
    # LANE_DESC_STURCT_OFF_ENTRIES_PER_BUCKET = 16  # 4 bytes
    # LANE_DESC_STURCT_OFF_VAL_NUM_WORDS = 20  # 4 bytes
    # BIG ENDIAN
    LANE_DESC_STURCT_OFF_START_NWID = 0  # 4 bytes
    LANE_DESC_STURCT_OFF_NUM_ALLOC_LANES = 4  # 4 bytes
    LANE_DESC_STURCT_OFF_BUCKETS_PER_LANE = 8  # 4 bytes
    LANE_DESC_STURCT_OFF_LANE_DESC_LM_OFFSET = 12  # 4 bytes
    LANE_DESC_STURCT_OFF_VAL_NUM_WORDS = 16  # 4 bytes
    LANE_DESC_STURCT_OFF_ENTRIES_PER_BUCKET = 20  # 4 bytes

    EXT_LANE_DESC_SIZE = 3 * WORD_SIZE
    # LITTLE ENDIAN
    # EXT_LANE_DESC_STURCT_OFF_NUM_ALLOC_LANES = LANE_DESC_SIZE + 0  # 4 bytes
    # EXT_LANE_DESC_STURCT_OFF_START_NWID = LANE_DESC_SIZE + 4  # 4 bytes
    # EXT_LANE_DESC_STURCT_OFF_LANE_DESC_LM_OFFSET = LANE_DESC_SIZE + 8  # 4 bytes
    # EXT_LANE_DESC_STURCT_OFF_BUCKETS_PER_LANE = LANE_DESC_SIZE + 12  # 4 bytes
    # EXT_LANE_DESC_STURCT_OFF_ENTRIES_PER_BUCKET = LANE_DESC_SIZE + 16  # 4 bytes
    # EXT_LANE_DESC_STURCT_OFF_VAL_NUM_WORDS = LANE_DESC_SIZE + 20  # 4 bytes
    # BIG ENDIAN
    EXT_LANE_DESC_STURCT_OFF_START_NWID = LANE_DESC_SIZE + 0  # 4 bytes
    EXT_LANE_DESC_STURCT_OFF_NUM_ALLOC_LANES = LANE_DESC_SIZE + 4  # 4 bytes
    EXT_LANE_DESC_STURCT_OFF_BUCKETS_PER_LANE = LANE_DESC_SIZE + 8  # 4 bytes
    EXT_LANE_DESC_STURCT_OFF_LANE_DESC_LM_OFFSET = LANE_DESC_SIZE + 12  # 4 bytes
    EXT_LANE_DESC_STURCT_OFF_VAL_NUM_WORDS = LANE_DESC_SIZE + 16  # 4 bytes
    EXT_LANE_DESC_STURCT_OFF_ENTRIES_PER_BUCKET = LANE_DESC_SIZE + 20  # 4 bytes

    BUCKET_DESC_SIZE = 11 * WORD_SIZE
    BUCKET_DESC_STURCT_OFF_LOCK = 0  # 4 bytes
    BUCKET_DESC_STURCT_OFF_ENTRY_COUNT = 4  # 4 bytes
    BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR = 8  # 8 bytes
    BUCKET_DESC_STURCT_OFF_DRAM_VAL_START_ADDR = 16  # 8 bytes
    BUCKET_DESC_STURCT_OFF_LM_BUF = 24  # 64 bytes

    @classmethod
    def setup(cls, state: State, debug=False) -> None:
        cls.DEBUG = debug
        cls.lock = sht_macros.MRSWLock(atomic=False, debug=debug)
        # cls.lock = sht_macros.MRSWLock(atomic=True, debug=debug)  # remove locks for experiemnt

        CLS_NAME = cls.__name__
        cls.tran_initialize = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-initialize-TR")
        cls.tran_update = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-update-TR")
        cls.tran_update_with_mask = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-update_with_mask-TR")
        cls.tran_get = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-get-TR")
        cls.tran_get_with_mask = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-get_with_mask-TR")
        cls.tran_get_with_offset = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-get_with_offset-TR")
        cls.tran_delete = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-delete-TR")
        cls.tran_ext_graph_append = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-ext_graph_append-TR")
        cls.tran_ext_graph_append_migrate = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-ext_graph_append_migrate-TR")
        cls.tran_ext_graph_get_with_offset = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-ext_graph_get_with_offset-TR")
        cls.tran_ext_graph_get_word_cnt = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-ext_graph_get_word_cnt-TR")

        # TODO: code injection
        Memcpy.setup(state, debug=debug)
        cls._initialize(state)
        cls._update(state)
        cls._get(state)
        # cls._delete(state)
        cls._get_with_offset(state)
        cls._get_with_mask(state)
        cls._update_with_mask(state)
        cls._ext_graph_append(state)
        cls._ext_graph_append_migrate(state)
        cls._ext_graph_get_with_offset(state)
        cls._ext_graph_get_word_cnt(state)

    @classmethod
    def _initialize(cls, state: State):
        """
        X8  - NUM_ALLOC_LANES(0:31) | START_NWID(32:63);
        X9  - LANE_DESC_LM_OFFSET(0:31) | BUCKETS_PER_LANE(32:63);
        X10 - ENTRIES_PER_BUCKET(0:31) | VAL_NUM_WORDS(32:63);
        X11 - LANE_DRAM_START_ADDR

        // extension SHT
        X12 - NUM_ALLOC_LANES(0:31) | START_NWID(32:63);
        X13 - LANE_DESC_LM_OFFSET(0:31) | BUCKETS_PER_LANE(32:63);
        X14 - ENTRIES_PER_BUCKET(0:31) | VAL_NUM_WORDS(32:63);
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._initialize.__name__

        OB_NUM_ALLOC_LANES__START_NWID = "X8"
        OB_LANE_DESC_LM_OFFSET__BUCKETS_PER_LANE = "X9"
        OB_ENTRIES_PER_BUCKET__VAL_NUM_WORDS = "X10"
        OB_LANE_DRAM_START_ADDR = "X11"

        OB_EXT__NUM_ALLOC_LANES__START_NWID = "X12"
        OB_EXT__LANE_DESC_LM_OFFSET__BUCKETS_PER_LANE = "X13"
        OB_EXT__ENTRIES_PER_BUCKET__VAL_NUM_WORDS = "X14"

        REG_CUR_LM_ADDR = "X16"
        REG_CUR_KEY_DRAM_ADDR = "X17"
        REG_CUR_VAL_DRAM_ADDR = "X19"
        REG_BUCKET_DRAM_SIZE = "X18"
        REG_TMP0 = "X20"
        REG_TMP1 = "X21"

        REG_TMP3 = "X23"
        REG_DESC_TOTAL_SIZE = "X24"

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_initialize
        if tran is None:
            return
        cls.tran_label_initialize = tran.getLabel()

        """==================== TRAN - entry ===================="""
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] INIT: start' {'X0'}")

        tran.writeAction(f"lshift {OB_LANE_DESC_LM_OFFSET__BUCKETS_PER_LANE} {REG_CUR_LM_ADDR} {32}")
        tran.writeAction(f"rshift {REG_CUR_LM_ADDR} {REG_CUR_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_CUR_LM_ADDR} {'X7'} {REG_CUR_LM_ADDR}")

        # ---- copy operands ----
        tran.writeAction(f"move {OB_NUM_ALLOC_LANES__START_NWID} {0}({REG_CUR_LM_ADDR}) 0 8")
        tran.writeAction(f"move {OB_LANE_DESC_LM_OFFSET__BUCKETS_PER_LANE} {cls.WORD_SIZE}({REG_CUR_LM_ADDR}) 0 8")
        tran.writeAction(f"move {OB_ENTRIES_PER_BUCKET__VAL_NUM_WORDS} {cls.WORD_SIZE * 2}({REG_CUR_LM_ADDR}) 0 8")
        tran.writeAction(f"move {OB_EXT__NUM_ALLOC_LANES__START_NWID} {cls.WORD_SIZE * 3}({REG_CUR_LM_ADDR}) 0 8")
        tran.writeAction(f"move {OB_EXT__LANE_DESC_LM_OFFSET__BUCKETS_PER_LANE} {cls.WORD_SIZE * 4}({REG_CUR_LM_ADDR}) 0 8")
        tran.writeAction(f"move {OB_EXT__ENTRIES_PER_BUCKET__VAL_NUM_WORDS} {cls.WORD_SIZE * 5}({REG_CUR_LM_ADDR}) 0 8")

        # ----- init lane desc -----
        tran.writeAction(f"mov_imm2reg {REG_DESC_TOTAL_SIZE} {cls.LANE_DESC_SIZE + cls.EXT_LANE_DESC_SIZE}")

        tran.writeAction(f"mov_imm2reg {REG_TMP0} {cls.LANE_DESC_SIZE + cls.EXT_LANE_DESC_SIZE}")
        tran.writeAction(f"add {REG_CUR_LM_ADDR} {REG_TMP0} {REG_CUR_LM_ADDR}")
        tran.writeAction(f"addi {OB_LANE_DRAM_START_ADDR} {REG_CUR_KEY_DRAM_ADDR} {0}")

        tran.writeAction(f"lshift {OB_ENTRIES_PER_BUCKET__VAL_NUM_WORDS} {REG_TMP0} {32}")
        tran.writeAction(f"rshift {REG_TMP0} {REG_TMP0} {32}")
        tran.writeAction(f"lshift {REG_TMP0} {REG_CUR_VAL_DRAM_ADDR} {int(math.log2(cls.WORD_SIZE))}")
        tran.writeAction(f"add {REG_CUR_VAL_DRAM_ADDR} {REG_CUR_KEY_DRAM_ADDR} {REG_CUR_VAL_DRAM_ADDR}")

        tran.writeAction(f"rshift_add_imm {OB_ENTRIES_PER_BUCKET__VAL_NUM_WORDS} {REG_TMP1} {32} {1}")  # REG_TMP1 => KEY_NUM_WORD + VAL_NUM_WORDS
        tran.writeAction(f"mul {REG_TMP1} {REG_TMP0} {REG_TMP1}")
        tran.writeAction(f"lshift {REG_TMP1} {REG_BUCKET_DRAM_SIZE} {int(math.log2(cls.WORD_SIZE))}")

        tran.writeAction(f"rshift {OB_LANE_DESC_LM_OFFSET__BUCKETS_PER_LANE} {REG_TMP1} {32}")  # REG_TMP1 => BUCKETS_PER_LANE
        tran.writeAction(f"muli {REG_TMP1} {REG_TMP0} {cls.BUCKET_DESC_SIZE}")
        tran.writeAction(f"add {REG_DESC_TOTAL_SIZE} {REG_TMP0} {REG_DESC_TOTAL_SIZE}")
        tran.writeAction(f"mov_imm2reg {REG_TMP0} {0}")  # REG_TMP2 => 0

        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-bucket_init_next'}: subi {REG_TMP1} {REG_TMP1} {1}")
        cls.lock.init(tran, REG_CUR_LM_ADDR, REG_TMP3)
        tran.writeAction(f"move {REG_TMP0} {cls.BUCKET_DESC_STURCT_OFF_ENTRY_COUNT}({REG_CUR_LM_ADDR}) 0 4")
        tran.writeAction(f"move {REG_CUR_KEY_DRAM_ADDR} {cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR}({REG_CUR_LM_ADDR}) 0 8")
        tran.writeAction(f"move {REG_CUR_VAL_DRAM_ADDR} {cls.BUCKET_DESC_STURCT_OFF_DRAM_VAL_START_ADDR}({REG_CUR_LM_ADDR}) 0 8")
        tran.writeAction(f"addi {REG_CUR_LM_ADDR} {REG_CUR_LM_ADDR} {cls.BUCKET_DESC_SIZE}")
        tran.writeAction(f"add {REG_CUR_KEY_DRAM_ADDR} {REG_BUCKET_DRAM_SIZE} {REG_CUR_KEY_DRAM_ADDR}")
        tran.writeAction(f"add {REG_CUR_VAL_DRAM_ADDR} {REG_BUCKET_DRAM_SIZE} {REG_CUR_VAL_DRAM_ADDR}")
        tran.writeAction(f"bgti {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-bucket_init_next'}")

        # ----- return -----
        sht_macros.return_wreg(tran, 'X1', "X0", REG_DESC_TOTAL_SIZE)  # return format: (NWID, DESC_TOTAL_SIZE)
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] INIT: done' {'X0'}")
        tran.writeAction("yield_terminate")

    @classmethod
    def initialize(cls, tran: Transition, ret: int, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_initialize.getLabel(), ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=7)

    @classmethod
    def initialize_wcont(cls, tran: Transition, ret: str, tmp_reg0: str, arg_lm_addr_reg: str, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_initialize.getLabel(), cont_reg=ret, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=7)

    @classmethod
    def _update(cls, state: State):
        """
        X8 - LANE_DESC_LM_OFFSET(0:31) | BUCKET_DESC_LM_OFFSET(32:63)
        X9 - KEY
        X10 ~ X15 - Elem e
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._update.__name__

        OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET = "X8"
        OB_KEY = "X9"
        OB_VAL = "X10"
        MAX_VAL_NUM_WORDS = 6

        REG_TMP0 = "X16"
        REG_TMP1 = "X17"
        REG_TMP2 = "X18"

        REG_LD_CONCURRENCY = "X20"
        REG_KEY_WR_ADDR = "X21"
        REG_VAL_WR_ADDR = "X22"
        REG_ST_CONCURRENCY = "X23"
        REG_NUM_VAL_OP = "X24"  # number of value operations
        REG_LAST_LOAD_EFFECTIVE_WORDS = "X25"
        REG_LAST_LOAD_ADDR = "X26"

        REG_LANE_DESC_LM_ADDR = "X27"
        REG_BUCKET_DESC_LM_ADDR = "X28"
        REG_BUCKET_BUF_LM_ADDR = "X29"
        REG_KEY = "X30"

        REG_CONT = "X31"

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_update
        if tran is None:
            return
        cls.tran_label_update = tran.getLabel()
        tran_key_ld_ret = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-key_ld_ret")
        tran_key_st_ret = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-key_st_ret")

        """==================== TRAN - function entry ===================="""
        """----- Prep -----"""
        # calc desc lm addr
        tran.writeAction(f"rshift {OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET} {REG_BUCKET_DESC_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_BUCKET_DESC_LM_ADDR} {'X7'} {REG_BUCKET_DESC_LM_ADDR}")

        # get lock
        cls.lock.write_begin_var(tran, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: lock admitted, TID = %d' {'X0'} {'TID'}")
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: REG_BUCKET_DESC_LM_ADDR = 0x%x' {'X0'} {REG_BUCKET_DESC_LM_ADDR}")

        # calc desc lm addr
        tran.writeAction(f"lshift {OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET} {REG_LANE_DESC_LM_ADDR} {32}")
        tran.writeAction(f"rshift {REG_LANE_DESC_LM_ADDR} {REG_LANE_DESC_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_LANE_DESC_LM_ADDR} {'X7'} {REG_LANE_DESC_LM_ADDR}")

        # copy ob regs
        tran.writeAction(f"mov_reg2reg {OB_KEY} {REG_KEY}")
        # save cont
        tran.writeAction(f"mov_reg2reg {'X1'} {REG_CONT}")

        # load desc
        tran.writeAction(f"addi {REG_BUCKET_DESC_LM_ADDR} {REG_BUCKET_BUF_LM_ADDR} {cls.BUCKET_DESC_STURCT_OFF_LM_BUF}")

        # extract num_elem_op
        # since there is an offset of 2 in the encoding, the desc & key counts are skipped
        tran.writeAction(f"rshift_and_imm {'X2'} {REG_NUM_VAL_OP} {20} {0b111}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: number of val operands = %d' {'X0'} {REG_NUM_VAL_OP}")
        # copy val to buffer
        tran.writeAction(f"bcopy_ops {OB_VAL} {REG_BUCKET_BUF_LM_ADDR} {REG_NUM_VAL_OP}")

        tran.writeAction(f"move {cls.BUCKET_DESC_STURCT_OFF_ENTRY_COUNT}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP1} 0 4")  # tmp1 => entry_count

        """----- Empty Bucket -----"""
        # ----- if entry count is zero, write directly -----
        tran.writeAction(f"bgti {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-setup_send_ld'}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: empty bucket, writing without search' {'X0'}")
        # update entry count
        tran.writeAction(f"addi {REG_TMP1} {REG_TMP1} {1}")
        tran.writeAction(f"move {REG_TMP1} {cls.BUCKET_DESC_STURCT_OFF_ENTRY_COUNT}({REG_BUCKET_DESC_LM_ADDR}) 0 4")

        tran.writeAction(f"mov_imm2reg {REG_LD_CONCURRENCY} {0}")
        tran.writeAction(f"mov_imm2reg {REG_ST_CONCURRENCY} {2}")
        tran.writeAction(f"move {cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_KEY_WR_ADDR} 0 8")
        tran.writeAction(f"move {cls.BUCKET_DESC_STURCT_OFF_DRAM_VAL_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_VAL_WR_ADDR} 0 8")
        # tran.writeAction(f"sendr_dmlm_wret {REG_KEY_WR_ADDR} {tran_key_st_ret.getLabel()} {REG_KEY} {REG_KEY}")
        # tran.writeAction(f"sendr_dmlm_wret {REG_KEY_WR_ADDR} {tran_key_st_ret.getLabel()} {REG_KEY}")  # writing only one word
        sht_macros.dram_write_reg_ret(tran=tran, addr_reg=REG_KEY_WR_ADDR, ret_tran_label=tran_key_st_ret.getLabel(), tmp_reg=REG_TMP2, arg_reg0=REG_KEY)
        # calling with the proper number of operands
        for i in range(1, MAX_VAL_NUM_WORDS + 1):
            tran.writeAction(f"beqi {REG_NUM_VAL_OP} {i} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_val_{i}'}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: shouldn't reach here!' {'X0'}")
        for i in range(1, MAX_VAL_NUM_WORDS + 1):
            # tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_val_{i}'}: send_dmlm_wret {REG_VAL_WR_ADDR} {tran_key_st_ret.getLabel()} {REG_BUCKET_BUF_LM_ADDR} {i}")
            sht_macros.dram_write_lm_ret(tran=tran, addr_reg=REG_VAL_WR_ADDR, ret_tran_label=tran_key_st_ret.getLabel(), tmp_reg=REG_TMP2, arg_lm_addr_reg=REG_BUCKET_BUF_LM_ADDR, arg_lm_words=i, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-LB-send_val_{i}')
            if cls.DEBUG:
                tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: writing {i} words value' {'X0'}")
            tran.writeAction("yield")

        """----- Filled Bucket -----"""
        # ----- already have entires, send load entries -----
        # init
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-setup_send_ld'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_LAST_LOAD_ADDR} 0 8")  # tmp3 => key load start address
        tran.writeAction(f"mov_imm2reg {REG_LD_CONCURRENCY} {0}")
        tran.writeAction(f"mov_imm2reg {REG_ST_CONCURRENCY} {-1}")

        tran.writeAction(f"blei {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_done'}")  # tmp1 => entry_count
        # tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_ld'}: send_dmlm_ld_wret {REG_LAST_LOAD_ADDR} {tran_key_ld_ret.getLabel()} {8}")
        sht_macros.dram_read_ret(tran=tran, addr_reg=REG_LAST_LOAD_ADDR, ret_tran_label=tran_key_ld_ret.getLabel(), tmp_reg=REG_TMP2, arg_lm_words=8, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-LB-send_ld')
        tran.writeAction(f"addi {REG_LD_CONCURRENCY} {REG_LD_CONCURRENCY} {1}")  # concurrency++
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: loading, DRAM addr = 0x%x' {'X0'} {REG_LAST_LOAD_ADDR}")
        # check if number of valid entries in the send is greater than 8
        tran.writeAction(f"bgti {REG_TMP1} {64 // cls.KEY_SIZE} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}")
        # last send, retain last send addr & valid size
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: all loads sent' {'X0'}")
        tran.writeAction(f"mov_reg2reg {REG_TMP1} {REG_LAST_LOAD_EFFECTIVE_WORDS}")  # record last load effective size
        tran.writeAction("yield")
        # full 8 word send
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}: subi {REG_TMP1} {REG_TMP1} {64 // cls.KEY_SIZE}")
        tran.writeAction(f"addi {REG_LAST_LOAD_ADDR} {REG_LAST_LOAD_ADDR} {64}")
        tran.writeAction(f"bgti {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_ld'}")
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_done'}: yield")

        """==================== TRAN - load key return ===================="""
        OB_LD_RET_ADDR = "X3"

        """----- synchronization check -----"""
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: load from 0x%x returns, mlp = %d' {'X0'} {OB_LD_RET_ADDR} {REG_LD_CONCURRENCY}")
        tran_key_ld_ret.writeAction(f"subi {REG_LD_CONCURRENCY} {REG_LD_CONCURRENCY} {1}")
        # possible situations:
        # ld concurrency >= 0
        # st concurrency == -1, no store yet, match
        # st concurrency == 0, store done, if ld concurrency == 0, terminate
        # st concurrency == 1, store not done, yield
        # st concurrency == 2 (impossible, as it is only set when the last load is processed)
        tran_key_ld_ret.writeAction(f"beqi {REG_ST_CONCURRENCY} {-1} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}")
        tran_key_ld_ret.writeAction(f"beqi {REG_ST_CONCURRENCY} {1} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}")
        tran_key_ld_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: last in-flight load & store finished, terminating... TID = %d' {'X0'} {'TID'}")
        # unlocked already, no need to unlock
        # return format: (key, val_addr)
        sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, REG_KEY, REG_VAL_WR_ADDR)
        tran_key_ld_ret.writeAction("yield_terminate")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}: yield")

        """----- Check returned keys -----"""
        # check if return is matched with (last) send address
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}: bne {OB_LD_RET_ADDR} {REG_LAST_LOAD_ADDR} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{7 * cls.KEY_SIZE}'}")  # tmp3 => last send addr
        # if it is the last send, branch to check only the valid entries
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: tail send load returns, num entries = %d' {'X0'} {REG_LAST_LOAD_EFFECTIVE_WORDS}")  # tmp2 => last send num valid entries
        for i in range(8, 0, -1):
            tran_key_ld_ret.writeAction(f"beqi {REG_LAST_LOAD_EFFECTIVE_WORDS} {i} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}'}")
        # match return data
        for i in range(8, 0, -1):
            tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}'}: beq {f'X{i + 8 - 1}'} {REG_KEY} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}_match'}")

        """-> not matched (fall through)"""
        # if not the last send came back (check concurrency counter), yield wait
        # if mlp is 0, finished, need to write entry & terminate
        tran_key_ld_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait_ld'}")
        # from here, all in-flight loads are done & no match found
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: no matched entry found' {'X0'}")
        # check if there is space at the end of the allocation area
        tran_key_ld_ret.writeAction(f"move {cls.LANE_DESC_STURCT_OFF_ENTRIES_PER_BUCKET}({REG_LANE_DESC_LM_ADDR}) {REG_TMP1} 0 4")  # REG_TMP1 => num_alloc_entries
        tran_key_ld_ret.writeAction(f"move {cls.BUCKET_DESC_STURCT_OFF_ENTRY_COUNT}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP2} 0 4")  # REG_TMP2 => entry count
        tran_key_ld_ret.writeAction(f"blt {REG_TMP2} {REG_TMP1} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-new_entry'}")
        # -> out of space!
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: bucket full, add FAILED!' {'X0'}")
        # return format: (key, val_addr)
        tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_TMP1} {0}")  # indicate failue with addr == 0
        sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, REG_KEY, REG_TMP1)
        # sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, 'X0', REG_TMP3)  # for debug
        cls.lock.write_end(tran_key_ld_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        tran_key_ld_ret.writeAction("yield_terminate")  # only if running out of space!
        # -> new entry
        # calculate the address of the key
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-new_entry'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_KEY_WR_ADDR} 0 8")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: storing in a new entry' {'X0'}")
        tran_key_ld_ret.writeAction(f"lshift {REG_TMP2} {REG_TMP1} {int(math.log2(cls.KEY_SIZE))}")
        tran_key_ld_ret.writeAction(f"add {REG_KEY_WR_ADDR} {REG_TMP1} {REG_KEY_WR_ADDR}")
        # store key
        # tran_key_ld_ret.writeAction(f"sendr_dmlm_wret {REG_KEY_WR_ADDR} {tran_key_st_ret.getLabel()} {REG_KEY}")  # writing only one word
        sht_macros.dram_write_reg_ret(tran=tran_key_ld_ret, addr_reg=REG_KEY_WR_ADDR, ret_tran_label=tran_key_st_ret.getLabel(), tmp_reg=REG_TMP0, arg_reg0=REG_KEY)
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: sending key write to addr = 0x%x' {'X0'} {REG_VAL_WR_ADDR}")
        # calculate the address of the value
        tran_key_ld_ret.writeAction(f"move {cls.BUCKET_DESC_STURCT_OFF_DRAM_VAL_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_VAL_WR_ADDR} 0 8")
        tran_key_ld_ret.writeAction(f"move {cls.LANE_DESC_STURCT_OFF_VAL_NUM_WORDS}({REG_LANE_DESC_LM_ADDR}) {REG_TMP1} 0 4")
        tran_key_ld_ret.writeAction(f"mul {REG_TMP2} {REG_TMP1} {REG_TMP1}")
        tran_key_ld_ret.writeAction(f"lshift {REG_TMP1} {REG_TMP1} {int(math.log2(cls.WORD_SIZE))}")
        tran_key_ld_ret.writeAction(f"add {REG_VAL_WR_ADDR} {REG_TMP1} {REG_VAL_WR_ADDR}")
        # store value
        # calling with the proper number of operands
        for i in range(1, MAX_VAL_NUM_WORDS + 1):
            tran_key_ld_ret.writeAction(f"beqi {REG_NUM_VAL_OP} {i} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-nomatch_send_val_{i}'}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: shouldn't reach here!' {'X0'}")
        for i in range(1, MAX_VAL_NUM_WORDS + 1):
            # tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-nomatch_send_val_{i}'}: send_dmlm_wret {REG_VAL_WR_ADDR} {tran_key_st_ret.getLabel()} {REG_BUCKET_BUF_LM_ADDR} {i}")
            sht_macros.dram_write_lm_ret(tran=tran_key_ld_ret, addr_reg=REG_VAL_WR_ADDR, ret_tran_label=tran_key_st_ret.getLabel(), tmp_reg=REG_TMP0, arg_lm_addr_reg=REG_BUCKET_BUF_LM_ADDR, arg_lm_words=i, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-nomatch_send_val_{i}')
            if cls.DEBUG:
                tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: writing {i} words value' {'X0'}")
            tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-nomatch_send_val_done'}")
        # count up the entries
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-nomatch_send_val_done'}: addi {REG_TMP2} {REG_TMP2} {1}")
        tran_key_ld_ret.writeAction(f"move {REG_TMP2} {cls.BUCKET_DESC_STURCT_OFF_ENTRY_COUNT}({REG_BUCKET_DESC_LM_ADDR}) 0 4")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: sending value write to addr = 0x%x' {'X0'} {REG_VAL_WR_ADDR}")
        tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_ST_CONCURRENCY} {2}")  # mark value written & all loads done
        # -> wait for in-flight load to come back
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait_ld'}: yield")

        """-> matched"""
        for i in range(0, 8):
            # calculate the entry index from key address
            tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{i * cls.KEY_SIZE}_match'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP1} 0 8")
            if cls.DEBUG:
                tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: matched at word offset {i}' {'X0'}")
            tran_key_ld_ret.writeAction(f"sub {OB_LD_RET_ADDR} {REG_TMP1} {REG_TMP1}")
            tran_key_ld_ret.writeAction(f"rshift {REG_TMP1} {REG_TMP1} {int(math.log2(cls.KEY_SIZE))}")
            tran_key_ld_ret.writeAction(f"addi {REG_TMP1} {REG_TMP1} {i}")  # REG_TMP1 => entry index
            tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_st'}")

        """----- Send store value -----"""
        # calculate value address
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_st'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_VAL_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_VAL_WR_ADDR} 0 8")
        tran_key_ld_ret.writeAction(f"move {cls.LANE_DESC_STURCT_OFF_VAL_NUM_WORDS}({REG_LANE_DESC_LM_ADDR}) {REG_TMP2} 0 4")
        tran_key_ld_ret.writeAction(f"mul {REG_TMP2} {REG_TMP1} {REG_TMP1}")
        tran_key_ld_ret.writeAction(f"lshift {REG_TMP1} {REG_TMP1} {int(math.log2(cls.WORD_SIZE))}")
        tran_key_ld_ret.writeAction(f"add {REG_VAL_WR_ADDR} {REG_TMP1} {REG_VAL_WR_ADDR}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: sending write to addr = 0x%x' {'X0'} {REG_VAL_WR_ADDR}")
        # calling with the proper number of operands
        for i in range(1, MAX_VAL_NUM_WORDS + 1):
            tran_key_ld_ret.writeAction(f"beqi {REG_NUM_VAL_OP} {i} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_{i}'}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: shouldn't reach here!' {'X0'}")
        for i in range(1, MAX_VAL_NUM_WORDS + 1):
            # tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_{i}'}: send_dmlm_wret {REG_VAL_WR_ADDR} {tran_key_st_ret.getLabel()} {REG_BUCKET_BUF_LM_ADDR} {i}")
            sht_macros.dram_write_lm_ret(tran=tran_key_ld_ret, addr_reg=REG_VAL_WR_ADDR, ret_tran_label=tran_key_st_ret.getLabel(), tmp_reg=REG_TMP0, arg_lm_addr_reg=REG_BUCKET_BUF_LM_ADDR, arg_lm_words=i, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_{i}')
            if cls.DEBUG:
                tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: writing {i} words value' {'X0'}")
            tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_done'}")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_done'}: mov_imm2reg {REG_ST_CONCURRENCY} {1}")  # mark value written
        tran_key_ld_ret.writeAction("yield")

        """==================== TRAN - store key val return ===================="""
        tran_key_st_ret.writeAction(f"subi {REG_ST_CONCURRENCY} {REG_ST_CONCURRENCY} {1}")
        tran_key_st_ret.writeAction(f"bgti {REG_ST_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_st_ret-LB-wait'}")
        tran_key_st_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_st_ret-LB-ld_wait'}")
        if cls.DEBUG:
            tran_key_st_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: write to 0x%x returns & no load waiting, terminating... TID = %d' {'X0'} {'X8'} {'TID'}")
        cls.lock.write_end(tran_key_st_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        sht_macros.return_wreg(tran_key_st_ret, REG_CONT, REG_KEY, REG_VAL_WR_ADDR)
        # sht_macros.return_wreg(tran_key_st_ret, REG_CONT, 'X0', REG_VAL_WR_ADDR)  # debug
        tran_key_st_ret.writeAction("yield_terminate")
        tran_key_st_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_st_ret-LB-ld_wait'}: addi {REG_TMP1} {REG_TMP1} {0}")  # dummy instruction
        cls.lock.write_end(tran_key_st_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        if cls.DEBUG:
            tran_key_st_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: write to 0x%x returns & all stores done, waiting loads return...' {'X0'} {'X8'}")
        tran_key_st_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_st_ret-LB-wait'}: yield")

    @classmethod
    def update(cls, tran: Transition, ret: int, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, arg_lm_words: int, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_update.getLabel(), ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=arg_lm_words)

    @classmethod
    def update_wcont(cls, tran: Transition, ret: str, tmp_reg0: str, arg_lm_addr_reg: str, arg_lm_words: int, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_update.getLabel(), cont_reg=ret, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=arg_lm_words)

    @classmethod
    def _get(cls, state: State):
        """
        X8 - LANE_DESC_LM_OFFSET(0:31) | BUCKET_DESC_LM_OFFSET(32:63)
        X9 - KEY
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._get.__name__

        OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET = "X8"
        OB_KEY = "X9"

        REG_TMP1 = "X17"
        REG_TMP2 = "X18"

        REG_LD_CONCURRENCY = "X20"
        REG_VAL_RD_ADDR = "X22"
        REG_MATCH_STATUS = "X23"
        REG_NUM_VAL_WORDS = "X24"  # number of value operations
        REG_LAST_LOAD_EFFECTIVE_WORDS = "X25"
        REG_LAST_LOAD_ADDR = "X26"

        REG_LANE_DESC_LM_ADDR = "X27"
        REG_BUCKET_DESC_LM_ADDR = "X28"
        REG_BUCKET_BUF_LM_ADDR = "X29"
        REG_KEY = "X30"

        REG_CONT = "X31"

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_get
        if tran is None:
            return
        cls.tran_label_get = tran.getLabel()
        tran_key_ld_ret = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-key_ld_ret")
        tran_val_ld_ret = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-val_ld_ret")

        """==================== TRAN - function entry ===================="""
        """----- Prep -----"""
        # calc desc lm addr
        tran.writeAction(f"rshift {OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET} {REG_BUCKET_DESC_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_BUCKET_DESC_LM_ADDR} {'X7'} {REG_BUCKET_DESC_LM_ADDR}")
        # get lock
        cls.lock.read_begin(tran, REG_BUCKET_DESC_LM_ADDR, REG_TMP1, 2)
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: lock admitted, TID = %d' {'X0'} {'TID'}")
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: REG_BUCKET_DESC_LM_ADDR = 0x%x' {'X0'} {REG_BUCKET_DESC_LM_ADDR}")

        # calc desc lm addr
        tran.writeAction(f"lshift {OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET} {REG_LANE_DESC_LM_ADDR} {32}")
        tran.writeAction(f"rshift {REG_LANE_DESC_LM_ADDR} {REG_LANE_DESC_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_LANE_DESC_LM_ADDR} {'X7'} {REG_LANE_DESC_LM_ADDR}")

        # copy ob regs
        tran.writeAction(f"mov_reg2reg {OB_KEY} {REG_KEY}")
        # save cont
        tran.writeAction(f"mov_reg2reg {'X1'} {REG_CONT}")

        # load desc
        tran.writeAction(f"addi {REG_BUCKET_DESC_LM_ADDR} {REG_BUCKET_BUF_LM_ADDR} {cls.BUCKET_DESC_STURCT_OFF_LM_BUF}")
        tran.writeAction(f"move {cls.LANE_DESC_STURCT_OFF_VAL_NUM_WORDS}({REG_LANE_DESC_LM_ADDR}) {REG_NUM_VAL_WORDS} 0 4")

        tran.writeAction(f"move {cls.BUCKET_DESC_STURCT_OFF_ENTRY_COUNT}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP1} 0 4")  # tmp1 => entry_count

        """----- Empty Bucket -----"""
        # ----- if entry count is zero, return not found -----
        tran.writeAction(f"bgti {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-setup_send_ld'}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: empty bucket, return without search' {'X0'}")
        # return format: (key, 0)
        # tran.writeAction(f"mov_imm2reg {REG_TMP1} {0}")  # indicate failue
        sht_macros.return_wreg(tran, REG_CONT, REG_KEY, REG_TMP1)
        # sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, 'X0', REG_TMP3)  # for debug
        cls.lock.read_end(tran, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        tran.writeAction("yield_terminate")  # only if running out of space!

        """----- Filled Bucket -----"""
        # ----- already have entires, send load entries -----
        # init
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-setup_send_ld'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_LAST_LOAD_ADDR} 0 8")  # tmp3 => key load start address
        tran.writeAction(f"mov_imm2reg {REG_LD_CONCURRENCY} {0}")
        tran.writeAction(f"mov_imm2reg {REG_MATCH_STATUS} {0}")

        tran.writeAction(f"blei {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_done'}")  # tmp1 => entry_count
        # tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_ld'}: send_dmlm_ld_wret {REG_LAST_LOAD_ADDR} {tran_key_ld_ret.getLabel()} {8}")
        sht_macros.dram_read_ret(tran=tran, addr_reg=REG_LAST_LOAD_ADDR, ret_tran_label=tran_key_ld_ret.getLabel(), tmp_reg=REG_TMP2, arg_lm_words=8, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-LB-send_ld')
        tran.writeAction(f"addi {REG_LD_CONCURRENCY} {REG_LD_CONCURRENCY} {1}")  # concurrency++
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: loading, DRAM addr = 0x%x' {'X0'} {REG_LAST_LOAD_ADDR}")
        # check if number of valid entries in the send is greater than 8
        tran.writeAction(f"bgti {REG_TMP1} {64 // cls.KEY_SIZE} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}")
        # last send, retain last send addr & valid size
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: all loads sent' {'X0'}")
        tran.writeAction(f"mov_reg2reg {REG_TMP1} {REG_LAST_LOAD_EFFECTIVE_WORDS}")  # record last load effective size
        tran.writeAction("yield")
        # full 8 word send
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}: subi {REG_TMP1} {REG_TMP1} {64 // cls.KEY_SIZE}")
        tran.writeAction(f"addi {REG_LAST_LOAD_ADDR} {REG_LAST_LOAD_ADDR} {64}")
        tran.writeAction(f"bgti {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_ld'}")
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_done'}: yield")

        """==================== TRAN - load key return ===================="""
        OB_LD_RET_ADDR = "X3"

        """----- synchronization check -----"""
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: load from 0x%x returns, mlp = %d' {'X0'} {OB_LD_RET_ADDR} {REG_LD_CONCURRENCY}")
        tran_key_ld_ret.writeAction(f"subi {REG_LD_CONCURRENCY} {REG_LD_CONCURRENCY} {1}")
        # wait the load value return processed before terminating
        tran_key_ld_ret.writeAction(f"beqi {REG_MATCH_STATUS} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}")
        tran_key_ld_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}")
        tran_key_ld_ret.writeAction(f"beqi {REG_MATCH_STATUS} {1} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: last in-flight load key & value returned already, terminating... TID = %d' {'X0'} {'TID'}")
        # unlocked already, no need to unlock
        tran_key_ld_ret.writeAction("yield_terminate")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}: yield")

        """----- Check returned keys -----"""
        # check if return is matched with (last) send address
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}: bne {OB_LD_RET_ADDR} {REG_LAST_LOAD_ADDR} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{7 * cls.KEY_SIZE}'}")  # tmp3 => last send addr
        # if it is the last send, branch to check only the valid entries
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: tail send load returns, num entries = %d' {'X0'} {REG_LAST_LOAD_EFFECTIVE_WORDS}")  # tmp2 => last send num valid entries
        for i in range(8, 0, -1):
            tran_key_ld_ret.writeAction(f"beqi {REG_LAST_LOAD_EFFECTIVE_WORDS} {i} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}'}")
        # match return data
        for i in range(8, 0, -1):
            tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}'}: beq {f'X{i + 8 - 1}'} {REG_KEY} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}_match'}")

        """-> not matched (fall through)"""
        tran_key_ld_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait_ld'}")
        # from here, all in-flight loads are done & no match found
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: no matched entry found' {'X0'}")
        # return format: (key, 0)
        tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_TMP1} {0}")  # indicate failue
        sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, REG_KEY, REG_TMP1)
        # sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, 'X0', REG_TMP3)  # for debug
        cls.lock.read_end(tran_key_ld_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        tran_key_ld_ret.writeAction("yield_terminate")  # only if running out of space!

        # -> wait for in-flight load to come back
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait_ld'}: yield")

        """-> matched"""
        for i in range(0, 8):
            # calculate the entry index from key address
            tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{i * cls.KEY_SIZE}_match'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP1} 0 8")
            if cls.DEBUG:
                tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: matched at word offset {i}' {'X0'}")
            tran_key_ld_ret.writeAction(f"sub {OB_LD_RET_ADDR} {REG_TMP1} {REG_TMP1}")
            tran_key_ld_ret.writeAction(f"rshift {REG_TMP1} {REG_TMP1} {int(math.log2(cls.KEY_SIZE))}")
            tran_key_ld_ret.writeAction(f"addi {REG_TMP1} {REG_TMP1} {i}")  # REG_TMP1 => entry index
            tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_ld'}")

        """----- Send load value -----"""
        # calculate value address
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_ld'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_VAL_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_VAL_RD_ADDR} 0 8")
        tran_key_ld_ret.writeAction(f"move {cls.LANE_DESC_STURCT_OFF_VAL_NUM_WORDS}({REG_LANE_DESC_LM_ADDR}) {REG_TMP2} 0 4")
        tran_key_ld_ret.writeAction(f"mul {REG_TMP2} {REG_TMP1} {REG_TMP1}")
        tran_key_ld_ret.writeAction(f"lshift {REG_TMP1} {REG_TMP1} {int(math.log2(cls.WORD_SIZE))}")
        tran_key_ld_ret.writeAction(f"add {REG_VAL_RD_ADDR} {REG_TMP1} {REG_VAL_RD_ADDR}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: sending load to addr = 0x%x' {'X0'} {REG_VAL_RD_ADDR}")

        # calling with the proper number of operands
        for i in range(1, 9):
            tran_key_ld_ret.writeAction(f"beqi {REG_NUM_VAL_WORDS} {i} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_{i}'}")
        tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_8'}")  # for value words > 8, load the first 8 words
        for i in range(1, 9):
            # tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_{i}'}: send_dmlm_ld_wret {REG_VAL_RD_ADDR} {tran_val_ld_ret.getLabel()} {i}")
            sht_macros.dram_read_ret(tran=tran_key_ld_ret, addr_reg=REG_VAL_RD_ADDR, ret_tran_label=tran_val_ld_ret.getLabel(), tmp_reg=REG_TMP2, arg_lm_words=i, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_{i}')
            if i <= 6:
                tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_TMP2} {i}")  # words to be copied
            else:
                tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_TMP2} {6}")  # words to be copied
            if cls.DEBUG:
                tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: loading {i} words value' {'X0'}")
            tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_done'}")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_done'}: mov_imm2reg {REG_MATCH_STATUS} {1}")  # mark key found
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: key found and value load issued' {'X0'}")
        tran_key_ld_ret.writeAction("yield")

        """==================== TRAN - load val return ===================="""
        if cls.DEBUG:
            tran_val_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: value load returns' {'X0'}")
        tran_val_ld_ret.writeAction(f"mov_imm2reg {REG_MATCH_STATUS} {2}")  # mark value returned
        cls.lock.read_end(tran_val_ld_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)

        # return format (key, addr, val0~5)
        tran_val_ld_ret.writeAction(f"move {REG_KEY} 8({REG_BUCKET_BUF_LM_ADDR}) 0 8")  # key
        tran_val_ld_ret.writeAction(f"move {REG_VAL_RD_ADDR} 16({REG_BUCKET_BUF_LM_ADDR}) 0 8")  # value address
        tran_val_ld_ret.writeAction(f"addi {REG_BUCKET_BUF_LM_ADDR} {REG_TMP1} {cls.WORD_SIZE * 2}")
        tran_val_ld_ret.writeAction(f"bcopy_ops {'X8'} {REG_TMP1} {REG_TMP2}")

        for i in range(1, 7):
            tran_val_ld_ret.writeAction(f"beqi {REG_NUM_VAL_WORDS} {i} {f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-ret_val_{i}'}")
        tran_val_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-ret_val_6'}")  # for value words > 6, load the first 6 words
        for i in range(1, 7):
            tran_val_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-ret_val_{i}'}: addi {REG_TMP1} {REG_TMP1} {0}")  # FIXME: dummy
            sht_macros.return_wlm(tran_val_ld_ret, REG_CONT, REG_BUCKET_BUF_LM_ADDR, i + 2)
            tran_val_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-ret_val_done'}")

        tran_val_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-ret_val_done'}: bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-wait_after_ld_val'}")
        tran_val_ld_ret.writeAction("yield_terminate")
        tran_val_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-wait_after_ld_val'}: yield")

    @classmethod
    def _get_fast(cls, state: State):
        """
        X8 - LANE_DESC_LM_OFFSET(0:31) | BUCKET_DESC_LM_OFFSET(32:63)
        X9 - KEY
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._get_fast.__name__

        OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET = "X8"
        OB_KEY = "X9"

        REG_TMP1 = "X17"
        REG_TMP2 = "X18"

        REG_LD_CONCURRENCY = "X20"
        REG_VAL_RD_ADDR = "X22"
        REG_MATCH_STATUS = "X23"
        REG_NUM_VAL_WORDS = "X24"  # number of value operations
        REG_LAST_LOAD_EFFECTIVE_WORDS = "X25"
        REG_LAST_LOAD_ADDR = "X26"

        REG_LANE_DESC_LM_ADDR = "X27"
        REG_BUCKET_DESC_LM_ADDR = "X28"
        # REG_BUCKET_BUF_LM_ADDR = "X29"
        REG_KEY = "X30"

        REG_CONT = "X31"

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR")
        if tran is None:
            return
        cls.tran_label_get_fast = tran.getLabel()
        tran_key_ld_ret = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-key_ld_ret")

        """==================== TRAN - function entry ===================="""
        """----- Prep -----"""
        # calc desc lm addr
        tran.writeAction(f"rshift {OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET} {REG_BUCKET_DESC_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_BUCKET_DESC_LM_ADDR} {'X7'} {REG_BUCKET_DESC_LM_ADDR}")
        # get lock
        cls.lock.read_begin(tran, REG_BUCKET_DESC_LM_ADDR, REG_TMP1, 2)
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: lock admitted, TID = %d' {'X0'} {'TID'}")
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: REG_BUCKET_DESC_LM_ADDR = 0x%x' {'X0'} {REG_BUCKET_DESC_LM_ADDR}")

        # copy ob regs
        tran.writeAction(f"mov_reg2reg {OB_KEY} {REG_KEY}")
        # save cont
        tran.writeAction(f"mov_reg2reg {'X1'} {REG_CONT}")

        # load desc
        # tran.writeAction(f"move {cls.BUCKET_DESC_STURCT_OFF_LM_BUF_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_BUF_LM_ADDR} 0 8")
        tran.writeAction(f"move {cls.LANE_DESC_STURCT_OFF_VAL_NUM_WORDS}({REG_LANE_DESC_LM_ADDR}) {REG_NUM_VAL_WORDS} 0 4")

        tran.writeAction(f"move {cls.BUCKET_DESC_STURCT_OFF_ENTRY_COUNT}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP1} 0 4")  # tmp1 => entry_count

        """----- Empty Bucket -----"""
        # ----- if entry count is zero, return not found -----
        tran.writeAction(f"bgti {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-setup_send_ld'}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: empty bucket, return without search' {'X0'}")
        # return format: (key, 0)
        # tran.writeAction(f"mov_imm2reg {REG_TMP1} {0}")  # indicate failue
        sht_macros.return_wreg(tran, REG_CONT, REG_KEY, REG_TMP1)
        # sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, 'X0', REG_TMP3)  # for debug
        cls.lock.read_end(tran, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        tran.writeAction("yield_terminate")  # only if running out of space!

        """----- Filled Bucket -----"""
        # ----- already have entires, send load entries -----
        # init
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-setup_send_ld'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_LAST_LOAD_ADDR} 0 8")  # tmp3 => key load start address
        tran.writeAction(f"mov_imm2reg {REG_LD_CONCURRENCY} {0}")
        tran.writeAction(f"mov_imm2reg {REG_MATCH_STATUS} {0}")

        tran.writeAction(f"blei {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_done'}")  # tmp1 => entry_count
        # tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_ld'}: send_dmlm_ld_wret {REG_LAST_LOAD_ADDR} {tran_key_ld_ret.getLabel()} {8}")
        sht_macros.dram_read_ret(tran=tran, addr_reg=REG_LAST_LOAD_ADDR, ret_tran_label=tran_key_ld_ret.getLabel(), tmp_reg=REG_TMP2, arg_lm_words=8, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-LB-send_ld')
        tran.writeAction(f"addi {REG_LD_CONCURRENCY} {REG_LD_CONCURRENCY} {1}")  # concurrency++
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: loading, DRAM addr = 0x%x' {'X0'} {REG_LAST_LOAD_ADDR}")
        # check if number of valid entries in the send is greater than 8
        tran.writeAction(f"bgti {REG_TMP1} {64 // cls.KEY_SIZE} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}")
        # last send, retain last send addr & valid size
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: all loads sent' {'X0'}")
        tran.writeAction(f"mov_reg2reg {REG_TMP1} {REG_LAST_LOAD_EFFECTIVE_WORDS}")  # record last load effective size
        tran.writeAction("yield")
        # full 8 word send
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}: subi {REG_TMP1} {REG_TMP1} {64 // cls.KEY_SIZE}")
        tran.writeAction(f"addi {REG_LAST_LOAD_ADDR} {REG_LAST_LOAD_ADDR} {64}")
        tran.writeAction(f"bgti {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_ld'}")
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_done'}: yield")

        """==================== TRAN - load key return ===================="""
        OB_LD_RET_ADDR = "X3"

        """----- synchronization check -----"""
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: load from 0x%x returns, mlp = %d' {'X0'} {OB_LD_RET_ADDR} {REG_LD_CONCURRENCY}")
        tran_key_ld_ret.writeAction(f"subi {REG_LD_CONCURRENCY} {REG_LD_CONCURRENCY} {1}")
        tran_key_ld_ret.writeAction(f"beqi {REG_MATCH_STATUS} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}")
        tran_key_ld_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: last in-flight load key & key found already, terminating... TID = %d' {'X0'} {'TID'}")
        # unlocked already, no need to unlock
        tran_key_ld_ret.writeAction("yield_terminate")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}: yield")

        """----- Check returned keys -----"""
        # check if return is matched with (last) send address
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}: bne {OB_LD_RET_ADDR} {REG_LAST_LOAD_ADDR} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{7 * cls.KEY_SIZE}'}")  # tmp3 => last send addr
        # if it is the last send, branch to check only the valid entries
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: tail send load returns, num entries = %d' {'X0'} {REG_LAST_LOAD_EFFECTIVE_WORDS}")  # tmp2 => last send num valid entries
        for i in range(8, 0, -1):
            tran_key_ld_ret.writeAction(f"beqi {REG_LAST_LOAD_EFFECTIVE_WORDS} {i} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}'}")
        # match return data
        for i in range(8, 0, -1):
            tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}'}: beq {f'X{i + 8 - 1}'} {REG_KEY} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}_match'}")

        """-> not matched (fall through)"""
        tran_key_ld_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait_ld'}")
        # from here, all in-flight loads are done & no match found
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: no matched entry found' {'X0'}")
        # return format: (key, 0)
        tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_TMP1} {0}")  # indicate failue
        sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, REG_KEY, REG_TMP1)
        # sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, 'X0', REG_TMP3)  # for debug
        cls.lock.read_end(tran_key_ld_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        tran_key_ld_ret.writeAction("yield_terminate")

        # -> wait for in-flight load to come back
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait_ld'}: yield")

        """-> matched"""
        for i in range(0, 8):
            # calculate the entry index from key address
            tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{i * cls.KEY_SIZE}_match'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP1} 0 8")
            if cls.DEBUG:
                tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: matched at word offset {i}' {'X0'}")
            tran_key_ld_ret.writeAction(f"sub {OB_LD_RET_ADDR} {REG_TMP1} {REG_TMP1}")
            tran_key_ld_ret.writeAction(f"rshift {REG_TMP1} {REG_TMP1} {int(math.log2(cls.KEY_SIZE))}")
            tran_key_ld_ret.writeAction(f"addi {REG_TMP1} {REG_TMP1} {i}")  # REG_TMP1 => entry index
            tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_ld'}")

        """----- Send load value -----"""
        # calculate value address
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_ld'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_VAL_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_VAL_RD_ADDR} 0 8")
        tran_key_ld_ret.writeAction(f"move {cls.LANE_DESC_STURCT_OFF_VAL_NUM_WORDS}({REG_LANE_DESC_LM_ADDR}) {REG_TMP2} 0 4")
        tran_key_ld_ret.writeAction(f"mul {REG_TMP2} {REG_TMP1} {REG_TMP1}")
        tran_key_ld_ret.writeAction(f"lshift {REG_TMP1} {REG_TMP1} {int(math.log2(cls.WORD_SIZE))}")
        tran_key_ld_ret.writeAction(f"add {REG_VAL_RD_ADDR} {REG_TMP1} {REG_VAL_RD_ADDR}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: sending load to addr = 0x%x' {'X0'} {REG_VAL_RD_ADDR}")

        # calling with the proper number of operands
        for i in range(1, 9):
            tran_key_ld_ret.writeAction(f"beqi {REG_NUM_VAL_WORDS} {i} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_{i}'}")
        tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_8'}")  # for value words > 8, load the first 8 words
        for i in range(1, 9):
            # tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_{i}'}: send_dmlm_ld {REG_VAL_RD_ADDR} {REG_CONT} {i}")  # directly return to caller
            sht_macros.dram_read_cont(tran=tran_key_ld_ret, addr_reg=REG_VAL_RD_ADDR, cont_reg=REG_CONT, tmp_reg=REG_TMP2, arg_lm_words=i, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_{i}')
            if cls.DEBUG:
                tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: loading {i} words value' {'X0'}")
            tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_done'}")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_done'}: bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait_after_ld_val'}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: key found, bucket terminating' {'X0'}")
        cls.lock.read_end(tran_key_ld_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        tran_key_ld_ret.writeAction("yield_terminate")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait_after_ld_val'}: mov_imm2reg {REG_MATCH_STATUS} {1}")  # mark key found
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: key found, wait for rest of key loads' {'X0'}")
        cls.lock.read_end(tran_key_ld_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        tran_key_ld_ret.writeAction("yield")

    @classmethod
    def get(cls, tran: Transition, ret: int, tmp_reg0: str, tmp_reg1: str, desc_lm_offset_reg: str, key_reg: str, dst_nwid_reg: str = 'X0'):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_get.getLabel(), ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=desc_lm_offset_reg, arg_reg1=key_reg)

    @classmethod
    def get_wcont(cls, tran: Transition, ret: str, tmp_reg: str, desc_lm_offset_reg: str, key_reg: str, dst_nwid_reg: str = 'X0'):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_get.getLabel(), cont_reg=ret, tmp_reg=tmp_reg, arg_reg0=desc_lm_offset_reg, arg_reg1=key_reg)

    @classmethod
    def _delete(cls, state: State):
        """
        TODO: WIP

        X8 - LANE_DESC_LM_OFFSET(0:31) | BUCKET_DESC_LM_OFFSET(32:63)
        X9 - KEY
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._delete.__name__

        OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET = "X8"
        OB_KEY = "X9"

        REG_TMP1 = "X17"
        REG_TMP2 = "X18"

        REG_LD_CONCURRENCY = "X20"
        REG_VAL_RD_ADDR = "X22"
        REG_MATCH_STATUS = "X23"
        REG_NUM_VAL_WORDS = "X24"  # number of value operations
        REG_LAST_LOAD_EFFECTIVE_WORDS = "X25"
        REG_LAST_LOAD_ADDR = "X26"

        REG_LANE_DESC_LM_ADDR = "X27"
        REG_BUCKET_DESC_LM_ADDR = "X28"
        REG_BUCKET_BUF_LM_ADDR = "X29"
        REG_KEY = "X30"

        REG_CONT = "X31"

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_delete
        if tran is None:
            return
        cls.tran_label_delete = tran.getLabel()
        tran_key_ld_ret = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-key_ld_ret")
        tran_val_ld_ret = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-val_ld_ret")

        """==================== TRAN - function entry ===================="""
        """----- Prep -----"""
        # calc desc lm addr
        tran.writeAction(f"rshift {OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET} {REG_BUCKET_DESC_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_BUCKET_DESC_LM_ADDR} {'X7'} {REG_BUCKET_DESC_LM_ADDR}")

        # get lock
        cls.lock.write_begin_var(tran, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: lock admitted, TID = %d' {'X0'} {'TID'}")
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: REG_BUCKET_DESC_LM_ADDR = 0x%x' {'X0'} {REG_BUCKET_DESC_LM_ADDR}")

        # calc desc lm addr
        tran.writeAction(f"lshift {OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET} {REG_LANE_DESC_LM_ADDR} {32}")
        tran.writeAction(f"rshift {REG_LANE_DESC_LM_ADDR} {REG_LANE_DESC_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_LANE_DESC_LM_ADDR} {'X7'} {REG_LANE_DESC_LM_ADDR}")

        # copy ob regs
        tran.writeAction(f"mov_reg2reg {OB_KEY} {REG_KEY}")
        # save cont
        tran.writeAction(f"mov_reg2reg {'X1'} {REG_CONT}")

        # load desc
        tran.writeAction(f"addi {REG_BUCKET_DESC_LM_ADDR} {REG_BUCKET_BUF_LM_ADDR} {cls.BUCKET_DESC_STURCT_OFF_LM_BUF}")
        tran.writeAction(f"move {cls.LANE_DESC_STURCT_OFF_VAL_NUM_WORDS}({REG_LANE_DESC_LM_ADDR}) {REG_NUM_VAL_WORDS} 0 4")

        tran.writeAction(f"move {cls.BUCKET_DESC_STURCT_OFF_ENTRY_COUNT}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP1} 0 4")  # tmp1 => entry_count

        """----- Empty Bucket -----"""
        # ----- if entry count is zero, return not found -----
        tran.writeAction(f"bgti {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-setup_send_ld'}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: empty bucket, return without search' {'X0'}")
        # return format: (key, 0)
        # tran.writeAction(f"mov_imm2reg {REG_TMP1} {0}")  # indicate failue
        sht_macros.return_wreg(tran, REG_CONT, REG_KEY, REG_TMP1)
        # sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, 'X0', REG_TMP3)  # for debug
        cls.lock.write_end(tran, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        tran.writeAction("yield_terminate")

        """----- Filled Bucket -----"""
        # ----- already have entires, send load entries -----
        # init
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-setup_send_ld'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_LAST_LOAD_ADDR} 0 8")  # tmp3 => key load start address
        tran.writeAction(f"mov_imm2reg {REG_LD_CONCURRENCY} {0}")
        tran.writeAction(f"mov_imm2reg {REG_MATCH_STATUS} {0}")

        tran.writeAction(f"blei {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_done'}")  # tmp1 => entry_count
        # tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_ld'}: send_dmlm_ld_wret {REG_LAST_LOAD_ADDR} {tran_key_ld_ret.getLabel()} {8}")
        sht_macros.dram_read_ret(tran=tran, addr_reg=REG_LAST_LOAD_ADDR, ret_tran_label=tran_key_ld_ret.getLabel(), tmp_reg=REG_TMP2, arg_lm_words=8, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-LB-send_ld')
        tran.writeAction(f"addi {REG_LD_CONCURRENCY} {REG_LD_CONCURRENCY} {1}")  # concurrency++
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: loading, DRAM addr = 0x%x' {'X0'} {REG_LAST_LOAD_ADDR}")
        # check if number of valid entries in the send is greater than 8
        tran.writeAction(f"bgti {REG_TMP1} {64 // cls.KEY_SIZE} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}")
        # last send, retain last send addr & valid size
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: all loads sent' {'X0'}")
        tran.writeAction(f"mov_reg2reg {REG_TMP1} {REG_LAST_LOAD_EFFECTIVE_WORDS}")  # record last load effective size
        tran.writeAction("yield")
        # full 8 word send
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}: subi {REG_TMP1} {REG_TMP1} {64 // cls.KEY_SIZE}")
        tran.writeAction(f"addi {REG_LAST_LOAD_ADDR} {REG_LAST_LOAD_ADDR} {64}")
        tran.writeAction(f"bgti {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_ld'}")
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_done'}: yield")

        """==================== TRAN - load key return ===================="""
        OB_LD_RET_ADDR = "X3"

        """----- synchronization check -----"""
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: load from 0x%x returns, mlp = %d' {'X0'} {OB_LD_RET_ADDR} {REG_LD_CONCURRENCY}")
        tran_key_ld_ret.writeAction(f"subi {REG_LD_CONCURRENCY} {REG_LD_CONCURRENCY} {1}")
        # wait the load value return processed before terminating
        tran_key_ld_ret.writeAction(f"beqi {REG_MATCH_STATUS} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}")
        tran_key_ld_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}")
        tran_key_ld_ret.writeAction(f"beqi {REG_MATCH_STATUS} {1} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: last in-flight load key & value returned already, terminating... TID = %d' {'X0'} {'TID'}")
        # unlocked already, no need to unlock
        tran_key_ld_ret.writeAction("yield_terminate")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}: yield")

        """----- Check returned keys -----"""
        # check if return is matched with (last) send address
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}: bne {OB_LD_RET_ADDR} {REG_LAST_LOAD_ADDR} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{7 * cls.KEY_SIZE}'}")  # tmp3 => last send addr
        # if it is the last send, branch to check only the valid entries
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: tail send load returns, num entries = %d' {'X0'} {REG_LAST_LOAD_EFFECTIVE_WORDS}")  # tmp2 => last send num valid entries
        for i in range(8, 0, -1):
            tran_key_ld_ret.writeAction(f"beqi {REG_LAST_LOAD_EFFECTIVE_WORDS} {i} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}'}")
        # match return data
        for i in range(8, 0, -1):
            tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}'}: beq {f'X{i + 8 - 1}'} {REG_KEY} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}_match'}")

        """-> not matched (fall through)"""
        tran_key_ld_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait_ld'}")
        # from here, all in-flight loads are done & no match found
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: no matched entry found' {'X0'}")
        # return format: (key, 0)
        tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_TMP1} {0}")  # indicate failue
        sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, REG_KEY, REG_TMP1)
        # sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, 'X0', REG_TMP3)  # for debug
        cls.lock.write_end(tran_key_ld_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        tran_key_ld_ret.writeAction("yield_terminate")  # only if running out of space!

        # -> wait for in-flight load to come back
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait_ld'}: yield")

        """-> matched"""
        # TODO: move the last entry to overwrite the matched entry
        for i in range(0, 8):
            # calculate the entry index from key address
            tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{i * cls.KEY_SIZE}_match'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP1} 0 8")
            if cls.DEBUG:
                tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: matched at word offset {i}' {'X0'}")
            tran_key_ld_ret.writeAction(f"sub {OB_LD_RET_ADDR} {REG_TMP1} {REG_TMP1}")
            tran_key_ld_ret.writeAction(f"rshift {REG_TMP1} {REG_TMP1} {int(math.log2(cls.KEY_SIZE))}")
            tran_key_ld_ret.writeAction(f"addi {REG_TMP1} {REG_TMP1} {i}")  # REG_TMP1 => entry index
            tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_ld'}")

        """----- Send store value -----"""
        # calculate value address
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_ld'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_VAL_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_VAL_RD_ADDR} 0 8")
        tran_key_ld_ret.writeAction(f"move {cls.LANE_DESC_STURCT_OFF_VAL_NUM_WORDS}({REG_LANE_DESC_LM_ADDR}) {REG_TMP2} 0 4")
        tran_key_ld_ret.writeAction(f"mul {REG_TMP2} {REG_TMP1} {REG_TMP1}")
        tran_key_ld_ret.writeAction(f"lshift {REG_TMP1} {REG_TMP1} {int(math.log2(cls.WORD_SIZE))}")
        tran_key_ld_ret.writeAction(f"add {REG_VAL_RD_ADDR} {REG_TMP1} {REG_VAL_RD_ADDR}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: sending load to addr = 0x%x' {'X0'} {REG_VAL_RD_ADDR}")

        # calling with the proper number of operands
        for i in range(1, 9):
            tran_key_ld_ret.writeAction(f"beqi {REG_NUM_VAL_WORDS} {i} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_{i}'}")
        tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_8'}")  # for value words > 8, load the first 8 words
        for i in range(1, 9):
            # tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_{i}'}: send_dmlm_ld_wret {REG_VAL_RD_ADDR} {tran_val_ld_ret.getLabel()} {i}")
            sht_macros.dram_read_ret(tran=tran_key_ld_ret, addr_reg=REG_VAL_RD_ADDR, ret_tran_label=tran_val_ld_ret.getLabel(), tmp_reg=REG_TMP2, arg_lm_words=i, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_{i}')
            if i <= 5:
                tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_TMP2} {i}")  # words to be copied
            else:
                tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_TMP2} {5}")  # words to be copied
            if cls.DEBUG:
                tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: loading {i} words value' {'X0'}")
            tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_done'}")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_done'}: mov_imm2reg {REG_MATCH_STATUS} {1}")  # mark key found
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: key found and value load issued' {'X0'}")
        tran_key_ld_ret.writeAction("yield")

        """==================== TRAN - load val return ===================="""
        if cls.DEBUG:
            tran_val_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: value load returns' {'X0'}")
        tran_val_ld_ret.writeAction(f"mov_imm2reg {REG_MATCH_STATUS} {2}")  # mark value returned
        cls.lock.write_end(tran_val_ld_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)

        tran_val_ld_ret.writeAction(f"mov_imm2reg {REG_TMP1} {1}")  # indicate success
        tran_val_ld_ret.writeAction(f"move {REG_TMP1} 0({REG_BUCKET_BUF_LM_ADDR}) 0 8")  # status
        tran_val_ld_ret.writeAction(f"move {REG_KEY} 8({REG_BUCKET_BUF_LM_ADDR}) 0 8")  # key
        tran_val_ld_ret.writeAction(f"move {REG_VAL_RD_ADDR} 16({REG_BUCKET_BUF_LM_ADDR}) 0 8")  # value address
        tran_val_ld_ret.writeAction(f"addi {REG_BUCKET_BUF_LM_ADDR} {REG_TMP1} {cls.WORD_SIZE * 3}")
        tran_val_ld_ret.writeAction(f"bcopy_ops {'X8'} {REG_TMP1} {REG_TMP2}")

        for i in range(1, 6):
            tran_val_ld_ret.writeAction(f"beqi {REG_NUM_VAL_WORDS} {i} {f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-ret_val_{i}'}")
        tran_val_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-ret_val_5'}")  # for value words > 5, load the first 5 words
        for i in range(1, 6):
            tran_val_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-ret_val_{i}'}: addi {REG_TMP1} {REG_TMP1} {0}")  # FIXME: dummy
            sht_macros.return_wlm(tran_val_ld_ret, REG_CONT, REG_BUCKET_BUF_LM_ADDR, i + 3)
            tran_val_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-ret_val_done'}")

        tran_val_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-ret_val_done'}: bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-wait_after_ld_val'}")
        tran_val_ld_ret.writeAction("yield_terminate")
        tran_val_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-wait_after_ld_val'}: yield")

    @classmethod
    def delete(cls, tran: Transition):
        """
        TODO
        """
        pass

    @classmethod
    def _ext_graph_append(cls, state: State):
        """
        Extension for Graph Abstraction Neighbor List Store
        - It uses the first word in the value to store the number of filled words in the value
        - It triggers specified plugin function (entry migration in this particular case) when the number of filled words reaches the limit

        X8 - LANE_DESC_LM_OFFSET(0:31) | BUCKET_DESC_LM_OFFSET(32:63)
        X9 - KEY
        X10 ~ X15 - Elem e
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._ext_graph_append.__name__

        from sht_ext import SHTExt

        OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET = "X8"
        OB_KEY = "X9"
        OB_VAL = "X10"
        MAX_VAL_NUM_WORDS = 6

        REG_TMP0 = "X16"
        REG_TMP1 = "X17"
        REG_TMP2 = "X18"
        REG_TMP3 = "X19"
        REG_LD_CONCURRENCY = "X20"
        REG_KEY_WR_ADDR = "X21"
        REG_VAL_WR_ADDR = "X22"
        REG_ST_CONCURRENCY = "X23"
        REG_NUM_VAL_OP = "X24"  # number of value operations
        REG_LAST_LOAD_EFFECTIVE_WORDS = "X25"
        REG_LAST_LOAD_ADDR = "X26"

        REG_LANE_DESC_LM_ADDR = "X27"
        REG_BUCKET_DESC_LM_ADDR = "X28"
        REG_BUCKET_BUF_LM_ADDR = "X29"
        REG_KEY = "X30"

        REG_CONT = "X31"

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_ext_graph_append
        if tran is None:
            return
        cls.tran_label_ext_graph_append = tran.getLabel()
        tran_key_ld_ret = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-key_ld_ret")
        tran_word_cnt_ld_ret = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret")
        tran_migration_ret = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-migration_ret")
        tran_key_val_st_ret = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-key_val_st_ret")

        """==================== TRAN - function entry ===================="""
        """----- Prep -----"""
        # calc desc lm addr
        tran.writeAction(f"rshift {OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET} {REG_BUCKET_DESC_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_BUCKET_DESC_LM_ADDR} {'X7'} {REG_BUCKET_DESC_LM_ADDR}")

        # get lock
        cls.lock.write_begin_var(tran, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: lock admitted, TID = %d' {'X0'} {'TID'}")
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: REG_BUCKET_DESC_LM_ADDR = 0x%x' {'X0'} {REG_BUCKET_DESC_LM_ADDR}")

        # calc desc lm addr
        tran.writeAction(f"lshift {OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET} {REG_LANE_DESC_LM_ADDR} {32}")
        tran.writeAction(f"rshift {REG_LANE_DESC_LM_ADDR} {REG_LANE_DESC_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_LANE_DESC_LM_ADDR} {'X7'} {REG_LANE_DESC_LM_ADDR}")

        # copy ob regs
        tran.writeAction(f"mov_reg2reg {OB_KEY} {REG_KEY}")
        # save cont
        tran.writeAction(f"mov_reg2reg {'X1'} {REG_CONT}")

        # load desc
        tran.writeAction(f"addi {REG_BUCKET_DESC_LM_ADDR} {REG_BUCKET_BUF_LM_ADDR} {cls.BUCKET_DESC_STURCT_OFF_LM_BUF}")
        tran.writeAction(f"addi {REG_BUCKET_BUF_LM_ADDR} {REG_BUCKET_BUF_LM_ADDR} {cls.WORD_SIZE}")  # WARNING: reserve the first word for call redirection

        # extract num_elem_op
        # since there is an offset of 2 in the encoding, the desc & key counts are skipped
        tran.writeAction(f"rshift_and_imm {'X2'} {REG_NUM_VAL_OP} {20} {0b111}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: number of val operands = %d' {'X0'} {REG_NUM_VAL_OP}")

        # copy val to buffer, using the number of val operands
        tran.writeAction(f"addi {REG_BUCKET_BUF_LM_ADDR} {REG_TMP1} {cls.WORD_SIZE}")
        tran.writeAction(f"bcopy_ops {OB_VAL} {REG_TMP1} {REG_NUM_VAL_OP}")

        # read entry count
        tran.writeAction(f"move {cls.BUCKET_DESC_STURCT_OFF_ENTRY_COUNT}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP1} 0 4")  # tmp1 => entry_count

        """----- Empty Bucket -----"""
        # ----- if entry count is zero, write directly -----
        tran.writeAction(f"bgti {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-setup_send_ld'}")
        tran.writeAction(f"move {cls.LANE_DESC_STURCT_OFF_VAL_NUM_WORDS}({REG_LANE_DESC_LM_ADDR}) {REG_TMP0} 0 4")  # REG_TMP0 => value num words
        tran.writeAction(f"bge {REG_NUM_VAL_OP} {REG_TMP0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-oob_redirect'}")  # check if the number of input words reached (value num words - 1)
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: empty bucket, writing without search' {'X0'}")
        # filling word counter
        tran.writeAction(f"move {REG_NUM_VAL_OP} {0}({REG_BUCKET_BUF_LM_ADDR}) 0 8")  # set word counter for the value to 0 in the buffer
        # update entry count
        tran.writeAction(f"addi {REG_TMP1} {REG_TMP1} {1}")
        tran.writeAction(f"move {REG_TMP1} {cls.BUCKET_DESC_STURCT_OFF_ENTRY_COUNT}({REG_BUCKET_DESC_LM_ADDR}) 0 4")
        # prep
        tran.writeAction(f"mov_imm2reg {REG_LD_CONCURRENCY} {0}")
        tran.writeAction(f"mov_imm2reg {REG_ST_CONCURRENCY} {2}")
        tran.writeAction(f"move {cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_KEY_WR_ADDR} 0 8")
        tran.writeAction(f"move {cls.BUCKET_DESC_STURCT_OFF_DRAM_VAL_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_VAL_WR_ADDR} 0 8")
        # write key
        # tran.writeAction(f"sendr_dmlm_wret {REG_KEY_WR_ADDR} {tran_key_val_st_ret.getLabel()} {REG_KEY}")  # writing only one word
        sht_macros.dram_write_reg_ret(tran=tran, addr_reg=REG_KEY_WR_ADDR, ret_tran_label=tran_key_val_st_ret.getLabel(), tmp_reg=REG_TMP2, arg_reg0=REG_KEY)

        # calling with the proper number of operands
        for i in range(1, MAX_VAL_NUM_WORDS + 1):
            tran.writeAction(f"beqi {REG_NUM_VAL_OP} {i} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_val_{i}'}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: shouldn't reach here!' {'X0'}")
        for i in range(1, MAX_VAL_NUM_WORDS + 1):
            # tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_val_{i}'}: send_dmlm_wret {REG_VAL_WR_ADDR} {tran_key_val_st_ret.getLabel()} {REG_BUCKET_BUF_LM_ADDR} {i + 1}")  # include the word counter
            sht_macros.dram_write_lm_ret(tran=tran, addr_reg=REG_VAL_WR_ADDR, ret_tran_label=tran_key_val_st_ret.getLabel(), tmp_reg=REG_TMP2, arg_lm_addr_reg=REG_BUCKET_BUF_LM_ADDR, arg_lm_words=(i + 1), branch_label=f'{CLS_NAME}-{FN_NAME}-TR-LB-send_val_{i}')
            if cls.DEBUG:
                tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: writing {i} words value' {'X0'}")
            tran.writeAction("yield")

        # ----- input size larger than value size, mark redirected and redirect call -----
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-oob_redirect'}: subi {REG_BUCKET_BUF_LM_ADDR} {REG_BUCKET_BUF_LM_ADDR} {cls.WORD_SIZE}")  # WARNING: release the reserved word
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: input size greater than allocated, redirecting call...' {'X0'}")
        tran.writeAction(f"sub {REG_LANE_DESC_LM_ADDR} {'X7'} {REG_TMP2}")
        tran.writeAction(f"addi {REG_TMP2} {REG_TMP2} {cls.LANE_DESC_SIZE}")  # REG_TMP2 => ext sht desc lm offset
        tran.writeAction(f"sub {REG_BUCKET_BUF_LM_ADDR} {'X7'} {REG_TMP3}")  # REG_TMP3 => tmp buf lm offset
        tran.writeAction(f"lshift_or {REG_TMP3} {REG_TMP2} {32}")  # REG_TMP2 => SHT_DESC_LM_OFFSET(0:31) | TMP_BUF_LM_OFFSET(32:63)
        tran.writeAction(f"move {REG_TMP2} {0}({REG_BUCKET_BUF_LM_ADDR}) 0 8")  # SHT_DESC_LM_OFFSET(0:31) | TMP_BUF_LM_OFFSET(32:63)
        tran.writeAction(f"move {REG_KEY} {cls.WORD_SIZE}({REG_BUCKET_BUF_LM_ADDR}) 0 8")  # KEY
        # call append with appropriate number of operands
        for i in range(1, MAX_VAL_NUM_WORDS + 1):
            tran.writeAction(f"beqi {REG_NUM_VAL_OP} {i} {f'{CLS_NAME}-{FN_NAME}-TR-LB-ret_val_{i}'}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: shouldn't reach here!' {'X0'}")
        for i in range(1, MAX_VAL_NUM_WORDS + 1):
            tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-ret_val_{i}'}: addi {REG_TMP1} {REG_TMP1} {0}")  # FIXME: dummy
            SHTExt.ext_graph_append_wcont(tran=tran, ret=REG_CONT, tmp_reg0=REG_TMP0, arg_lm_addr_reg=REG_BUCKET_BUF_LM_ADDR, num_val_words=i)
            tran.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-LB-mark_migrated'}")
        """-> mark the existing entry as migrated"""
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-mark_migrated'}: mov_imm2reg {REG_TMP0} {-1}")  # use -1 as marker of migrated
        # update entry count
        tran.writeAction(f"mov_imm2reg {REG_TMP1} {1}")
        tran.writeAction(f"move {REG_TMP1} {cls.BUCKET_DESC_STURCT_OFF_ENTRY_COUNT}({REG_BUCKET_DESC_LM_ADDR}) 0 4")
        # prep
        tran.writeAction(f"move {cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_KEY_WR_ADDR} 0 8")
        tran.writeAction(f"move {cls.BUCKET_DESC_STURCT_OFF_DRAM_VAL_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_VAL_WR_ADDR} 0 8")
        # tran.writeAction(f"sendr_dmlm_wret {REG_KEY_WR_ADDR} {tran_key_val_st_ret.getLabel()} {REG_KEY}")  # writing only one word
        # tran.writeAction(f"sendr_dmlm_wret {REG_VAL_WR_ADDR} {tran_key_val_st_ret.getLabel()} {REG_TMP0}")  # writing only one word
        sht_macros.dram_write_reg_ret(tran=tran, addr_reg=REG_KEY_WR_ADDR, ret_tran_label=tran_key_val_st_ret.getLabel(), tmp_reg=REG_TMP1, arg_reg0=REG_KEY)
        sht_macros.dram_write_reg_ret(tran=tran, addr_reg=REG_VAL_WR_ADDR, ret_tran_label=tran_key_val_st_ret.getLabel(), tmp_reg=REG_TMP1, arg_reg0=REG_TMP0)
        tran.writeAction(f"mov_imm2reg {REG_LD_CONCURRENCY} {0}")
        tran.writeAction(f"mov_imm2reg {REG_ST_CONCURRENCY} {2}")
        tran.writeAction(f"mov_imm2reg {REG_VAL_WR_ADDR} {-1}")  # use -1 as marker of migrated, should not reply
        tran.writeAction("yield")

        """----- Filled Bucket -----"""
        # ----- already have entires, send load keys -----
        # init
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-setup_send_ld'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_LAST_LOAD_ADDR} 0 8")  # tmp3 => key load start address
        tran.writeAction(f"mov_imm2reg {REG_LD_CONCURRENCY} {0}")
        tran.writeAction(f"mov_imm2reg {REG_ST_CONCURRENCY} {-1}")

        tran.writeAction(f"blei {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_done'}")  # tmp1 => entry_count
        # tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_ld'}: send_dmlm_ld_wret {REG_LAST_LOAD_ADDR} {tran_key_ld_ret.getLabel()} {8}")
        sht_macros.dram_read_ret(tran=tran, addr_reg=REG_LAST_LOAD_ADDR, ret_tran_label=tran_key_ld_ret.getLabel(), tmp_reg=REG_TMP2, arg_lm_words=8, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-LB-send_ld')
        tran.writeAction(f"addi {REG_LD_CONCURRENCY} {REG_LD_CONCURRENCY} {1}")  # concurrency++
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: loading, DRAM addr = 0x%x' {'X0'} {REG_LAST_LOAD_ADDR}")
        # check if number of valid entries in the send is greater than 8
        tran.writeAction(f"bgti {REG_TMP1} {64 // cls.KEY_SIZE} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}")
        # last send, retain last send addr & valid size
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: all loads sent' {'X0'}")
        tran.writeAction(f"mov_reg2reg {REG_TMP1} {REG_LAST_LOAD_EFFECTIVE_WORDS}")  # record last load effective size
        tran.writeAction("yield")
        # full 8 word send
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}: subi {REG_TMP1} {REG_TMP1} {64 // cls.KEY_SIZE}")
        tran.writeAction(f"addi {REG_LAST_LOAD_ADDR} {REG_LAST_LOAD_ADDR} {64}")
        tran.writeAction(f"bgti {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_ld'}")
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_done'}: yield")

        """==================== TRAN - load key return ===================="""
        OB_LD_RET_ADDR = "X3"

        """----- synchronization check -----"""
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: load from 0x%x returns, mlp = %d' {'X0'} {OB_LD_RET_ADDR} {REG_LD_CONCURRENCY}")
        tran_key_ld_ret.writeAction(f"subi {REG_LD_CONCURRENCY} {REG_LD_CONCURRENCY} {1}")
        # possible situations:
        # ld concurrency >= 0
        # st concurrency == -2, call redirected, terminate without reply
        # st concurrency == -1, no store yet, match
        # st concurrency == 0, store done, if ld concurrency == 0, terminate
        # st concurrency == 1, store not done, yield
        # st concurrency == 2
        tran_key_ld_ret.writeAction(f"beqi {REG_ST_CONCURRENCY} {-1} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}")
        tran_key_ld_ret.writeAction(f"bgti {REG_ST_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}")
        tran_key_ld_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}")
        tran_key_ld_ret.writeAction(f"beqi {REG_ST_CONCURRENCY} {-2} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-term_no_reply'}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: last in-flight load & store finished, terminating... TID = %d' {'X0'} {'TID'}")
        # unlocked already, no need to unlock
        # return format: (key, val_addr)
        sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, REG_KEY, REG_VAL_WR_ADDR)
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-term_no_reply'}: yield_terminate")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}: yield")

        """----- Check returned keys -----"""
        # check if return is matched with (last) send address
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}: bne {OB_LD_RET_ADDR} {REG_LAST_LOAD_ADDR} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{7 * cls.KEY_SIZE}'}")  # tmp3 => last send addr
        # if it is the last send, branch to check only the valid entries
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: tail send load returns, num entries = %d' {'X0'} {REG_LAST_LOAD_EFFECTIVE_WORDS}")  # tmp2 => last send num valid entries
        for i in range(8, 0, -1):
            tran_key_ld_ret.writeAction(f"beqi {REG_LAST_LOAD_EFFECTIVE_WORDS} {i} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}'}")
        # match return data
        for i in range(8, 0, -1):
            tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}'}: beq {f'X{i + 8 - 1}'} {REG_KEY} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}_match'}")

        """-> not matched (fall through)"""
        # if not the last send came back (check concurrency counter), yield wait
        # if mlp is 0, finished, need to write entry & terminate
        tran_key_ld_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait_ld'}")
        # from here, all in-flight loads are done & no match found
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: no matched entry found' {'X0'}")
        # check if there is space at the end of the allocation area
        tran_key_ld_ret.writeAction(f"move {cls.LANE_DESC_STURCT_OFF_ENTRIES_PER_BUCKET}({REG_LANE_DESC_LM_ADDR}) {REG_TMP1} 0 4")  # REG_TMP1 => num_alloc_entries
        tran_key_ld_ret.writeAction(f"move {cls.BUCKET_DESC_STURCT_OFF_ENTRY_COUNT}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP2} 0 4")  # REG_TMP2 => entry count
        tran_key_ld_ret.writeAction(f"blt {REG_TMP2} {REG_TMP1} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-new_entry'}")
        """--> out of space!"""
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: bucket full, add FAILED!' {'X0'}")
        # return format: (key, val_addr)
        tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_TMP1} {0}")  # indicate failue
        sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, REG_KEY, REG_TMP1)
        # sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, 'X0', REG_TMP3)  # for debug
        cls.lock.write_end(tran_key_ld_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        tran_key_ld_ret.writeAction("yield_terminate")  # only if running out of space!
        """-> new entry"""
        # calculate the address of the key
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-new_entry'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_KEY_WR_ADDR} 0 8")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: storing in a new entry' {'X0'}")
        tran_key_ld_ret.writeAction(f"lshift {REG_TMP2} {REG_TMP1} {int(math.log2(cls.KEY_SIZE))}")
        tran_key_ld_ret.writeAction(f"add {REG_KEY_WR_ADDR} {REG_TMP1} {REG_KEY_WR_ADDR}")
        # store key
        # tran_key_ld_ret.writeAction(f"sendr_dmlm_wret {REG_KEY_WR_ADDR} {tran_key_val_st_ret.getLabel()} {REG_KEY}")  # writing only one word
        sht_macros.dram_write_reg_ret(tran=tran_key_ld_ret, addr_reg=REG_KEY_WR_ADDR, ret_tran_label=tran_key_val_st_ret.getLabel(), tmp_reg=REG_TMP0, arg_reg0=REG_KEY)
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: sending key write to addr = 0x%x' {'X0'} {REG_VAL_WR_ADDR}")
        # calculate the address of the value
        tran_key_ld_ret.writeAction(f"move {cls.BUCKET_DESC_STURCT_OFF_DRAM_VAL_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_VAL_WR_ADDR} 0 8")
        tran_key_ld_ret.writeAction(f"move {cls.LANE_DESC_STURCT_OFF_VAL_NUM_WORDS}({REG_LANE_DESC_LM_ADDR}) {REG_TMP1} 0 4")
        tran_key_ld_ret.writeAction(f"mul {REG_TMP2} {REG_TMP1} {REG_TMP1}")
        tran_key_ld_ret.writeAction(f"lshift {REG_TMP1} {REG_TMP1} {int(math.log2(cls.WORD_SIZE))}")
        tran_key_ld_ret.writeAction(f"add {REG_VAL_WR_ADDR} {REG_TMP1} {REG_VAL_WR_ADDR}")
        # store value
        # calling with the proper number of operands
        for i in range(1, MAX_VAL_NUM_WORDS + 1):
            tran_key_ld_ret.writeAction(f"beqi {REG_NUM_VAL_OP} {i} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-nomatch_send_val_{i}'}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: shouldn't reach here!' {'X0'}")
        for i in range(1, MAX_VAL_NUM_WORDS + 1):
            # tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-nomatch_send_val_{i}'}: send_dmlm_wret {REG_VAL_WR_ADDR} {tran_key_val_st_ret.getLabel()} {REG_BUCKET_BUF_LM_ADDR} {i + 1}")  # include the word counter
            sht_macros.dram_write_lm_ret(tran=tran_key_ld_ret, addr_reg=REG_VAL_WR_ADDR, ret_tran_label=tran_key_val_st_ret.getLabel(), tmp_reg=REG_TMP0, arg_lm_addr_reg=REG_BUCKET_BUF_LM_ADDR, arg_lm_words=(i + 1), branch_label=f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-nomatch_send_val_{i}')
            if cls.DEBUG:
                tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: writing {i} words value' {'X0'}")
            tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-nomatch_send_val_done'}")
        # count up the entries
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-nomatch_send_val_done'}: addi {REG_TMP2} {REG_TMP2} {1}")
        tran_key_ld_ret.writeAction(f"move {REG_TMP2} {cls.BUCKET_DESC_STURCT_OFF_ENTRY_COUNT}({REG_BUCKET_DESC_LM_ADDR}) 0 4")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: sending value write to addr = 0x%x' {'X0'} {REG_VAL_WR_ADDR}")
        tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_ST_CONCURRENCY} {2}")  # mark value written & all loads done
        # wait in-flight load to come back
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait_ld'}: yield")

        """-> matched"""
        for i in range(0, 8):
            # calculate the value index from key address
            tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{i * cls.KEY_SIZE}_match'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP1} 0 8")
            if cls.DEBUG:
                tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: matched at word offset {i}' {'X0'}")
            tran_key_ld_ret.writeAction(f"sub {OB_LD_RET_ADDR} {REG_TMP1} {REG_TMP1}")
            tran_key_ld_ret.writeAction(f"rshift {REG_TMP1} {REG_TMP1} {int(math.log2(cls.KEY_SIZE))}")
            tran_key_ld_ret.writeAction(f"addi {REG_TMP1} {REG_TMP1} {i}")  # REG_TMP1 => value index
            tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_load_word_cnt'}")

        # load word counter (first word of value)
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_load_word_cnt'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_VAL_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_VAL_WR_ADDR} 0 8")
        tran_key_ld_ret.writeAction(f"move {cls.LANE_DESC_STURCT_OFF_VAL_NUM_WORDS}({REG_LANE_DESC_LM_ADDR}) {REG_TMP2} 0 4")  # REG_TMP2 => value num words
        tran_key_ld_ret.writeAction(f"mul {REG_TMP2} {REG_TMP1} {REG_TMP1}")
        tran_key_ld_ret.writeAction(f"lshift {REG_TMP1} {REG_TMP1} {int(math.log2(cls.WORD_SIZE))}")
        tran_key_ld_ret.writeAction(f"add {REG_VAL_WR_ADDR} {REG_TMP1} {REG_VAL_WR_ADDR}")
        # tran_key_ld_ret.writeAction(f"send_dmlm_ld_wret {REG_VAL_WR_ADDR} {tran_word_cnt_ld_ret.getLabel()} {1}")
        sht_macros.dram_read_ret(tran=tran_key_ld_ret, addr_reg=REG_VAL_WR_ADDR, ret_tran_label=tran_word_cnt_ld_ret.getLabel(), tmp_reg=REG_TMP0, arg_lm_words=1)
        tran_key_ld_ret.writeAction("yield")

        """==================== TRAN - load word counter return ===================="""
        # TODO: optimization, when less than 7 words exists, merge the word counter write and value write
        # FIXME: check if there is no next SHT registered, if so, reply error
        # check if the entry is migrated
        if cls.DEBUG:
            tran_word_cnt_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: word counter = %d' {'X0'} {'X8'}")
        tran_word_cnt_ld_ret.writeAction(f"beqi {'X8'} {-1} {f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-redirect'}")
        tran_word_cnt_ld_ret.writeAction(f"add {'X8'} {REG_NUM_VAL_OP} {REG_TMP1}")  # calc updated word counter
        tran_word_cnt_ld_ret.writeAction(f"bge {REG_TMP1} {REG_TMP2} {f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-migrate'}")  # check if the word counter reached (value num words - 1)

        """----- Values fit in existing entry, append -----"""
        """-> Send store updated word counter"""
        # tran_word_cnt_ld_ret.writeAction(f"sendr_dmlm_wret {REG_VAL_WR_ADDR} {tran_key_val_st_ret.getLabel()} {REG_TMP1}")  # writing only one word
        sht_macros.dram_write_reg_ret(tran=tran_word_cnt_ld_ret, addr_reg=REG_VAL_WR_ADDR, ret_tran_label=tran_key_val_st_ret.getLabel(), tmp_reg=REG_TMP0, arg_reg0=REG_TMP1)
        """-> Send store value"""
        # calculate the address of the append value
        tran_word_cnt_ld_ret.writeAction(f"lshift_add_imm {'X8'} {REG_TMP1} {int(math.log2(cls.WORD_SIZE))} {cls.WORD_SIZE}")  # skip the word counter
        tran_word_cnt_ld_ret.writeAction(f"add {REG_VAL_WR_ADDR} {REG_TMP1} {REG_TMP1}")
        # skip the word counter position for writing value
        tran_word_cnt_ld_ret.writeAction(f"addi {REG_BUCKET_BUF_LM_ADDR} {REG_TMP3} {cls.WORD_SIZE}")
        # append the value to the end of the value list
        if cls.DEBUG:
            tran_word_cnt_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: sending write to addr = 0x%x' {'X0'} {REG_TMP1}")
        # calling with the proper number of operands
        for i in range(1, MAX_VAL_NUM_WORDS + 1):
            tran_word_cnt_ld_ret.writeAction(f"beqi {REG_NUM_VAL_OP} {i} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_{i}'}")
        if cls.DEBUG:
            tran_word_cnt_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: shouldn't reach here!' {'X0'}")
        for i in range(1, MAX_VAL_NUM_WORDS + 1):
            # tran_word_cnt_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_{i}'}: send_dmlm_wret {REG_TMP1} {tran_key_val_st_ret.getLabel()} {REG_TMP3} {i}")
            sht_macros.dram_write_lm_ret(tran=tran_word_cnt_ld_ret, addr_reg=REG_TMP1, ret_tran_label=tran_key_val_st_ret.getLabel(), tmp_reg=REG_TMP0, arg_lm_addr_reg=REG_TMP3, arg_lm_words=i, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_{i}')
            if cls.DEBUG:
                tran_word_cnt_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: writing {i} words value' {'X0'}")
            tran_word_cnt_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_done'}")
        tran_word_cnt_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_done'}: mov_imm2reg {REG_ST_CONCURRENCY} {2}")  # mark word counter & value written
        tran_word_cnt_ld_ret.writeAction("yield")

        """----- Values do not fit in existing entry, migrate -----"""
        # call for migration if exceeded value size
        """-> call migration function"""
        tran_word_cnt_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-migrate'}: subi {REG_BUCKET_BUF_LM_ADDR} {REG_BUCKET_BUF_LM_ADDR} {cls.WORD_SIZE}")  # WARNING: release the reserved word
        if cls.DEBUG:
            tran_word_cnt_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: migrating entry...' {'X0'}")
        # save the third and fourth word of the buffer
        tran_word_cnt_ld_ret.writeAction(f"move {cls.WORD_SIZE * 2}({REG_BUCKET_BUF_LM_ADDR}) {REG_TMP0} 0 8")  # REG_TMP0 => third word
        tran_word_cnt_ld_ret.writeAction(f"move {cls.WORD_SIZE * 3}({REG_BUCKET_BUF_LM_ADDR}) {REG_TMP1} 0 8")  # REG_TMP1 => fourth word
        # prepare migrate arguments
        tran_word_cnt_ld_ret.writeAction(f"sub {REG_LANE_DESC_LM_ADDR} {'X7'} {REG_TMP2}")
        tran_word_cnt_ld_ret.writeAction(f"addi {REG_TMP2} {REG_TMP2} {cls.LANE_DESC_SIZE}")  # REG_TMP2 => ext sht desc lm offset
        tran_word_cnt_ld_ret.writeAction(f"sub {REG_BUCKET_BUF_LM_ADDR} {'X7'} {REG_TMP3}")  # REG_TMP3 => tmp buf lm offset
        tran_word_cnt_ld_ret.writeAction(f"lshift_or {REG_TMP3} {REG_TMP2} {32}")  # REG_TMP2 => SHT_DESC_LM_OFFSET(0:31) | TMP_BUF_LM_OFFSET(32:63)
        tran_word_cnt_ld_ret.writeAction(f"move {REG_TMP2} {0}({REG_BUCKET_BUF_LM_ADDR}) 0 8")  # SHT_DESC_LM_OFFSET(0:31) | TMP_BUF_LM_OFFSET(32:63)
        tran_word_cnt_ld_ret.writeAction(f"move {REG_KEY} {cls.WORD_SIZE}({REG_BUCKET_BUF_LM_ADDR}) 0 8")  # KEY
        tran_word_cnt_ld_ret.writeAction(f"move {REG_VAL_WR_ADDR} {cls.WORD_SIZE * 2}({REG_BUCKET_BUF_LM_ADDR}) 0 8")  # SRC_VAL_ADDR
        tran_word_cnt_ld_ret.writeAction(f"addi {'X8'} {REG_TMP3} {1}")
        tran_word_cnt_ld_ret.writeAction(f"move {REG_TMP3} {cls.WORD_SIZE * 3}({REG_BUCKET_BUF_LM_ADDR}) 0 8")  # COPY_NUM_WORDS (X8 + 1)
        SHTExt.ext_graph_append_migrate(tran=tran_word_cnt_ld_ret, ret=tran_migration_ret.getLabel(), tmp_reg0=REG_TMP3, tmp_reg1=REG_TMP2, arg_lm_addr_reg=REG_BUCKET_BUF_LM_ADDR)
        tran_word_cnt_ld_ret.writeAction(f"move {0}({REG_BUCKET_BUF_LM_ADDR}) {REG_TMP2} 0 8")  # restore REG_TMP2, SHT_DESC_LM_OFFSET(0:31) | TMP_BUF_LM_OFFSET(32:63)
        tran_word_cnt_ld_ret.writeAction("yield")

        """----- Entry migrated, redirect call -----"""
        tran_word_cnt_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-redirect'}: subi {REG_BUCKET_BUF_LM_ADDR} {REG_BUCKET_BUF_LM_ADDR} {cls.WORD_SIZE}")  # WARNING: release the reserved word
        # prepare redirect arguments
        tran_word_cnt_ld_ret.writeAction(f"sub {REG_LANE_DESC_LM_ADDR} {'X7'} {REG_TMP2}")
        if cls.DEBUG:
            tran_word_cnt_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: entry already migrated, redirecting call...' {'X0'}")
        tran_word_cnt_ld_ret.writeAction(f"addi {REG_TMP2} {REG_TMP2} {cls.LANE_DESC_SIZE}")  # REG_TMP2 => ext sht desc lm offset
        tran_word_cnt_ld_ret.writeAction(f"sub {REG_BUCKET_BUF_LM_ADDR} {'X7'} {REG_TMP3}")  # REG_TMP3 => tmp buf lm offset
        tran_word_cnt_ld_ret.writeAction(f"lshift_or {REG_TMP3} {REG_TMP2} {32}")  # REG_TMP2 => SHT_DESC_LM_OFFSET(0:31) | TMP_BUF_LM_OFFSET(32:63)
        tran_word_cnt_ld_ret.writeAction(f"move {REG_TMP2} {0}({REG_BUCKET_BUF_LM_ADDR}) 0 8")  # SHT_DESC_LM_OFFSET(0:31) | TMP_BUF_LM_OFFSET(32:63)
        tran_word_cnt_ld_ret.writeAction(f"move {REG_KEY} {cls.WORD_SIZE}({REG_BUCKET_BUF_LM_ADDR}) 0 8")  # KEY
        # call append with appropriate number of operands
        for i in range(1, MAX_VAL_NUM_WORDS + 1):
            tran_word_cnt_ld_ret.writeAction(f"beqi {REG_NUM_VAL_OP} {i} {f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-ret_val_{i}'}")
        if cls.DEBUG:
            tran_word_cnt_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: shouldn't reach here!' {'X0'}")
        for i in range(1, MAX_VAL_NUM_WORDS + 1):
            tran_word_cnt_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-ret_val_{i}'}: addi {REG_TMP1} {REG_TMP1} {0}")  # FIXME: dummy
            SHTExt.ext_graph_append_wcont(tran=tran_word_cnt_ld_ret, ret=REG_CONT, tmp_reg0=REG_TMP0, arg_lm_addr_reg=REG_BUCKET_BUF_LM_ADDR, num_val_words=i)
            tran_word_cnt_ld_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-wait_key_ld'}")
            cls.lock.write_end(tran_word_cnt_ld_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
            tran_word_cnt_ld_ret.writeAction("yield_terminate")
        tran_word_cnt_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-wait_key_ld'}: mov_imm2reg {REG_ST_CONCURRENCY} {-2}")
        tran_word_cnt_ld_ret.writeAction("yield")

        """==================== TRAN - migrate return ===================="""
        # FIXME: check failure case
        """-> redirect append call to next sht"""
        if cls.DEBUG:
            tran_migration_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: migration complete, redirecting call...' {'X0'}")
        tran_migration_ret.writeAction(f"move {REG_TMP2} {0}({REG_BUCKET_BUF_LM_ADDR}) 0 8")  # SHT_DESC_LM_OFFSET(0:31) | TMP_BUF_LM_OFFSET(32:63), WARNING: have to guarantee REG_TMP2 is not overwritten between transitions
        tran_migration_ret.writeAction(f"move {REG_KEY} {cls.WORD_SIZE}({REG_BUCKET_BUF_LM_ADDR}) 0 8")  # KEY
        # restore the third and fourth word of the buffer
        tran_migration_ret.writeAction(f"move {REG_TMP0} {cls.WORD_SIZE * 2}({REG_BUCKET_BUF_LM_ADDR}) 0 8")
        tran_migration_ret.writeAction(f"move {REG_TMP1} {cls.WORD_SIZE * 3}({REG_BUCKET_BUF_LM_ADDR}) 0 8")

        # call append with appropriate number of operands
        for i in range(1, MAX_VAL_NUM_WORDS + 1):
            tran_migration_ret.writeAction(f"beqi {REG_NUM_VAL_OP} {i} {f'{CLS_NAME}-{FN_NAME}-TR-migration_ret-LB-ret_val_{i}'}")
        if cls.DEBUG:
            tran_migration_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: shouldn't reach here!' {'X0'}")
        for i in range(1, MAX_VAL_NUM_WORDS + 1):
            tran_migration_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-migration_ret-LB-ret_val_{i}'}: addi {REG_TMP1} {REG_TMP1} {0}")  # FIXME: dummy
            SHTExt.ext_graph_append_wcont(tran=tran_migration_ret, ret=REG_CONT, tmp_reg0=REG_TMP0, arg_lm_addr_reg=REG_BUCKET_BUF_LM_ADDR, num_val_words=i)
            tran_migration_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-migration_ret-LB-mark_migrated'}")
        """-> mark the existing entry as migrated"""
        tran_migration_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-migration_ret-LB-mark_migrated'}: mov_imm2reg {REG_TMP0} {-1}")  # use -1 as marker of migrated
        # tran_migration_ret.writeAction(f"sendr_dmlm_wret {REG_VAL_WR_ADDR} {tran_key_val_st_ret.getLabel()} {REG_TMP0}")  # writing only one word
        sht_macros.dram_write_reg_ret(tran=tran_migration_ret, addr_reg=REG_VAL_WR_ADDR, ret_tran_label=tran_key_val_st_ret.getLabel(), tmp_reg=REG_TMP1, arg_reg0=REG_TMP0)
        tran_migration_ret.writeAction(f"mov_imm2reg {REG_ST_CONCURRENCY} {1}")
        tran_migration_ret.writeAction(f"mov_imm2reg {REG_VAL_WR_ADDR} {-1}")
        tran_migration_ret.writeAction("yield")

        """==================== TRAN - store key val return ===================="""
        tran_key_val_st_ret.writeAction(f"subi {REG_ST_CONCURRENCY} {REG_ST_CONCURRENCY} {1}")
        # restore the third and fourth word of the buffer
        tran_key_val_st_ret.writeAction(f"bgti {REG_ST_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_val_st_ret-LB-wait'}")
        tran_key_val_st_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_val_st_ret-LB-ld_wait'}")
        tran_key_val_st_ret.writeAction(f"beqi {REG_VAL_WR_ADDR} {-1} {f'{CLS_NAME}-{FN_NAME}-TR-key_val_st_ret-LB-ld_silent_term'}")

        if cls.DEBUG:
            tran_key_val_st_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: write to 0x%x returns & no load waiting, terminating... TID = %d' {'X0'} {'X8'} {'TID'}")
        cls.lock.write_end(tran_key_val_st_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        # return format: (key, val_start_addr)
        sht_macros.return_wreg(tran_key_val_st_ret, REG_CONT, REG_KEY, REG_VAL_WR_ADDR)
        # sht_macros.return_wreg(tran_key_st_ret, REG_CONT, 'X0', REG_VAL_WR_ADDR)  # debug
        tran_key_val_st_ret.writeAction("yield_terminate")

        tran_key_val_st_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_val_st_ret-LB-ld_wait'}: addi {REG_TMP1} {REG_TMP1} {0}")  # FIXME: dummy instruction
        cls.lock.write_end(tran_key_val_st_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        if cls.DEBUG:
            tran_key_val_st_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: write to 0x%x returns & all stores done, waiting loads return...' {'X0'} {'X8'}")
        tran_key_val_st_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_val_st_ret-LB-wait'}: yield")

        tran_key_val_st_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_val_st_ret-LB-ld_silent_term'}: addi {REG_TMP1} {REG_TMP1} {0}")  # FIXME: dummy instruction
        cls.lock.write_end(tran_key_val_st_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        if cls.DEBUG:
            tran_key_val_st_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: call migrated, terminating sliently... TID = %d' {'X0'} {'TID'}")
        tran_key_val_st_ret.writeAction("yield_terminate")

    @classmethod
    def ext_graph_append(cls, tran: Transition, ret: int, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, arg_lm_words: int, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_ext_graph_append.getLabel(), ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=arg_lm_words)

    @classmethod
    def ext_graph_append_wcont(cls, tran: Transition, ret: str, tmp_reg0: str, arg_lm_addr_reg: str, arg_lm_words: int, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_ext_graph_append.getLabel(), cont_reg=ret, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=arg_lm_words)

    @classmethod
    def _ext_graph_append_migrate(cls, state: State):
        """
        Executed on the SHT instance which is being migrated to.

        X8  - LANE_DESC_LM_OFFSET(0:31) | BUCKET_DESC_LM_OFFSET(32:63)
        X9  - KEY
        X10 - SRC_VAL_ADDR
        X11 - COPY_NUM_WORDS
        """

        CLS_NAME = cls.__name__
        FN_NAME = cls._ext_graph_append_migrate.__name__

        OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET = "X8"
        OB_KEY = "X9"
        OB_SRC_VAL_ADDR = "X10"
        OB_COPY_NUM_WORDS = "X11"

        REG_TMP0 = "X16"
        REG_TMP1 = "X17"
        REG_KEY_WR_ADDR = "X18"
        REG_VAL_WR_ADDR = "X19"
        REG_LANE_DESC_LM_ADDR = "X20"
        REG_BUCKET_DESC_LM_ADDR = "X21"
        REG_KEY = "X22"
        REG_TMP2 = "X23"

        REG_CONT = "X31"

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_ext_graph_append_migrate
        if tran is None:
            return
        cls.tran_label_ext_graph_append_migrate = tran.getLabel()
        tran_key_val_st_ret = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-key_val_st_ret")

        """==================== TRAN - function entry ===================="""
        """----- Prep -----"""
        # calc desc lm addr
        tran.writeAction(f"rshift {OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET} {REG_BUCKET_DESC_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_BUCKET_DESC_LM_ADDR} {'X7'} {REG_BUCKET_DESC_LM_ADDR}")

        # get lock
        cls.lock.write_begin(tran, REG_BUCKET_DESC_LM_ADDR, REG_TMP0, 4)
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: lock admitted, TID = %d' {'X0'} {'TID'}")
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: REG_BUCKET_DESC_LM_ADDR = 0x%x' {'X0'} {REG_BUCKET_DESC_LM_ADDR}")

        # calc desc lm addr
        tran.writeAction(f"lshift {OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET} {REG_LANE_DESC_LM_ADDR} {32}")
        tran.writeAction(f"rshift {REG_LANE_DESC_LM_ADDR} {REG_LANE_DESC_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_LANE_DESC_LM_ADDR} {'X7'} {REG_LANE_DESC_LM_ADDR}")

        # save cont
        tran.writeAction(f"addi {'X1'} {REG_CONT} {0}")
        tran.writeAction(f"addi {OB_KEY} {REG_KEY} {0}")

        # check if there is space at the end of the allocation area
        tran.writeAction(f"move {cls.LANE_DESC_STURCT_OFF_ENTRIES_PER_BUCKET}({REG_LANE_DESC_LM_ADDR}) {REG_TMP0} 0 4")  # REG_TMP0 => num_alloc_entries
        tran.writeAction(f"move {cls.BUCKET_DESC_STURCT_OFF_ENTRY_COUNT}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP1} 0 4")  # REG_TMP1 => entry count
        tran.writeAction(f"blt {REG_TMP1} {REG_TMP0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-new_entry'}")
        """--> out of space!"""
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: bucket full, add FAILED!' {'X0'}")
        # return format: (key, val_addr)
        tran.writeAction(f"mov_imm2reg {REG_TMP0} {0}")  # indicate failue
        sht_macros.return_wreg(tran, REG_CONT, REG_KEY, REG_TMP0)
        # sht_macros.return_wreg(tran, REG_CONT, 'X0', REG_TMP3)  # for debug
        cls.lock.write_end(tran, REG_BUCKET_DESC_LM_ADDR, REG_TMP0)
        tran.writeAction("yield_terminate")  # only if running out of space!
        """-> new entry"""
        # calculate the address of the key
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-new_entry'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_KEY_WR_ADDR} 0 8")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: storing in a new entry' {'X0'}")
        tran.writeAction(f"lshift {REG_TMP1} {REG_TMP0} {int(math.log2(cls.KEY_SIZE))}")
        tran.writeAction(f"add {REG_KEY_WR_ADDR} {REG_TMP0} {REG_KEY_WR_ADDR}")
        # store key
        # tran.writeAction(f"sendr_dmlm_wret {REG_KEY_WR_ADDR} {tran_key_val_st_ret.getLabel()} {REG_KEY}")  # writing only one word
        sht_macros.dram_write_reg_ret(tran=tran, addr_reg=REG_KEY_WR_ADDR, ret_tran_label=tran_key_val_st_ret.getLabel(), tmp_reg=REG_TMP2, arg_reg0=REG_KEY)
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: sending key write to addr = 0x%x' {'X0'} {REG_VAL_WR_ADDR}")
        # calculate the address of the value
        tran.writeAction(f"move {cls.BUCKET_DESC_STURCT_OFF_DRAM_VAL_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_VAL_WR_ADDR} 0 8")
        tran.writeAction(f"move {cls.LANE_DESC_STURCT_OFF_VAL_NUM_WORDS}({REG_LANE_DESC_LM_ADDR}) {REG_TMP0} 0 4")
        tran.writeAction(f"mul {REG_TMP1} {REG_TMP0} {REG_TMP0}")
        tran.writeAction(f"lshift {REG_TMP0} {REG_TMP0} {int(math.log2(cls.WORD_SIZE))}")
        tran.writeAction(f"add {REG_VAL_WR_ADDR} {REG_TMP0} {REG_VAL_WR_ADDR}")
        # store value
        Memcpy.memcpy(tran=tran, ret_tran_label=tran_key_val_st_ret.getLabel(), tmp_reg0=REG_TMP0, tmp_reg1=REG_TMP2, src_dram_addr_reg=OB_SRC_VAL_ADDR, dst_dram_addr_reg=REG_VAL_WR_ADDR, num_words_reg=OB_COPY_NUM_WORDS)
        # count up the entries
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-nomatch_send_val_done'}: addi {REG_TMP1} {REG_TMP1} {1}")
        tran.writeAction(f"move {REG_TMP1} {cls.BUCKET_DESC_STURCT_OFF_ENTRY_COUNT}({REG_BUCKET_DESC_LM_ADDR}) 0 4")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: copying value to to dram addr = 0x%x' {'X0'} {REG_VAL_WR_ADDR}")
        tran.writeAction(f"mov_imm2reg {REG_TMP0} {2}")  # concurrency
        tran.writeAction("yield")

        """==================== TRAN - store key val return ===================="""
        tran_key_val_st_ret.writeAction(f"subi {REG_TMP0} {REG_TMP0} {1}")
        tran_key_val_st_ret.writeAction(f"bgti {REG_TMP0} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_val_st_ret-LB-wait'}")
        # return format: (key, val_addr)
        sht_macros.return_wreg(tran_key_val_st_ret, REG_CONT, REG_KEY, REG_VAL_WR_ADDR)
        cls.lock.write_end(tran_key_val_st_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP0)
        tran_key_val_st_ret.writeAction("yield_terminate")
        tran_key_val_st_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_val_st_ret-LB-wait'}: yield")

    @classmethod
    def ext_graph_append_migrate(cls, tran: Transition, ret: int, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_ext_graph_append_migrate.getLabel(), ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=4)

    @classmethod
    def ext_graph_append_migrate_wcont(cls, tran: Transition, ret: str, tmp_reg: str, arg_lm_addr_reg: str, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_ext_graph_append_migrate.getLabel(), cont_reg=ret, tmp_reg=tmp_reg, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=4)

    @classmethod
    def _ext_graph_get_with_offset(cls, state: State):
        """
        Extended to support offset + call redirection

        X8  - LANE_DESC_LM_OFFSET(0:31) | BUCKET_DESC_LM_OFFSET(32:63)
        X9  - KEY
        X10 - OFFSET (in words, ignore the counter word)

        Return format: (KEY, NUM_NB, NB_VID0, NB_VID1, ...)
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._ext_graph_get_with_offset.__name__

        from sht_ext import SHTExt

        OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET = "X8"
        OB_KEY = "X9"
        OB_OFFSET = "X10"

        REG_TMP1 = "X17"
        REG_TMP2 = "X18"
        REG_TMP3 = "X19"

        REG_LD_CONCURRENCY = "X20"
        REG_VAL_RD_ADDR = "X22"
        REG_MATCH_STATUS = "X23"
        REG_NUM_VAL_WORDS = "X24"
        REG_LAST_LOAD_EFFECTIVE_WORDS = "X25"
        REG_LAST_LOAD_ADDR = "X26"

        REG_LANE_DESC_LM_ADDR = "X27"
        REG_BUCKET_DESC_LM_ADDR = "X28"
        REG_BUCKET_BUF_LM_ADDR = "X29"
        REG_KEY = "X30"
        REG_OFFSET = "X16"

        REG_CONT = "X31"

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_ext_graph_get_with_offset
        if tran is None:
            return
        cls.tran_label_ext_graph_get_with_offset = tran.getLabel()
        tran_key_ld_ret = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-key_ld_ret")
        tran_word_cnt_ld_ret = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret")
        tran_val_ld_ret = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-val_ld_ret")

        """==================== TRAN - function entry ===================="""
        """----- Prep -----"""
        # calc desc lm addr
        tran.writeAction(f"rshift {OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET} {REG_BUCKET_DESC_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_BUCKET_DESC_LM_ADDR} {'X7'} {REG_BUCKET_DESC_LM_ADDR}")
        # get lock
        cls.lock.read_begin(tran, REG_BUCKET_DESC_LM_ADDR, REG_TMP1, 3)
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: lock admitted, TID = %d' {'X0'} {'TID'}")
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: REG_BUCKET_DESC_LM_ADDR = 0x%x' {'X0'} {REG_BUCKET_DESC_LM_ADDR}")

        # calc desc lm addr
        tran.writeAction(f"lshift {OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET} {REG_LANE_DESC_LM_ADDR} {32}")
        tran.writeAction(f"rshift {REG_LANE_DESC_LM_ADDR} {REG_LANE_DESC_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_LANE_DESC_LM_ADDR} {'X7'} {REG_LANE_DESC_LM_ADDR}")

        # copy ob regs
        tran.writeAction(f"addi {OB_KEY} {REG_KEY} {0}")
        tran.writeAction(f"addi {OB_OFFSET} {REG_OFFSET} {0}")
        # save cont
        tran.writeAction(f"addi {'X1'} {REG_CONT} {0}")

        # load desc
        tran.writeAction(f"addi {REG_BUCKET_DESC_LM_ADDR} {REG_BUCKET_BUF_LM_ADDR} {cls.BUCKET_DESC_STURCT_OFF_LM_BUF}")
        tran.writeAction(f"move {cls.LANE_DESC_STURCT_OFF_VAL_NUM_WORDS}({REG_LANE_DESC_LM_ADDR}) {REG_NUM_VAL_WORDS} 0 4")
        tran.writeAction(f"subi {REG_NUM_VAL_WORDS} {REG_NUM_VAL_WORDS} {1}")  # adjust for the word counter
        tran.writeAction(f"sub {REG_NUM_VAL_WORDS} {REG_OFFSET} {REG_NUM_VAL_WORDS}")  # WARNING: adjusted for the offset
        tran.writeAction(f"move {cls.BUCKET_DESC_STURCT_OFF_ENTRY_COUNT}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP1} 0 4")  # REG_TMP1 => entry_count

        """----- Empty Bucket -----"""
        # ----- if entry count is zero, return not found -----
        tran.writeAction(f"bgti {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-setup_send_ld'}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: empty bucket, return without search' {'X0'}")
        # return format: (key, 0)
        # tran.writeAction(f"mov_imm2reg {REG_TMP1} {0}")  # indicate failue
        sht_macros.return_wreg(tran, REG_CONT, REG_KEY, REG_TMP1)
        # sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, 'X0', REG_TMP3)  # for debug
        cls.lock.read_end(tran, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        tran.writeAction("yield_terminate")

        """----- Filled Bucket -----"""
        # ----- already have entires, send load entries -----
        # init
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-setup_send_ld'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_LAST_LOAD_ADDR} 0 8")  # tmp3 => key load start address
        tran.writeAction(f"mov_imm2reg {REG_LD_CONCURRENCY} {0}")
        tran.writeAction(f"mov_imm2reg {REG_MATCH_STATUS} {0}")

        tran.writeAction(f"blei {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_done'}")  # tmp1 => entry_count
        # tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_ld'}: send_dmlm_ld_wret {REG_LAST_LOAD_ADDR} {tran_key_ld_ret.getLabel()} {8}")
        sht_macros.dram_read_ret(tran=tran, addr_reg=REG_LAST_LOAD_ADDR, ret_tran_label=tran_key_ld_ret.getLabel(), tmp_reg=REG_TMP2, arg_lm_words=8, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-LB-send_ld')
        tran.writeAction(f"addi {REG_LD_CONCURRENCY} {REG_LD_CONCURRENCY} {1}")  # concurrency++
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: loading, DRAM addr = 0x%x' {'X0'} {REG_LAST_LOAD_ADDR}")
        # check if number of valid entries in the send is greater than 8
        tran.writeAction(f"bgti {REG_TMP1} {64 // cls.KEY_SIZE} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}")
        # last send, retain last send addr & valid size
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: all loads sent' {'X0'}")
        tran.writeAction(f"mov_reg2reg {REG_TMP1} {REG_LAST_LOAD_EFFECTIVE_WORDS}")  # record last load effective size
        tran.writeAction("yield")
        # full 8 word send
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}: subi {REG_TMP1} {REG_TMP1} {64 // cls.KEY_SIZE}")
        tran.writeAction(f"addi {REG_LAST_LOAD_ADDR} {REG_LAST_LOAD_ADDR} {64}")
        tran.writeAction(f"bgti {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_ld'}")
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_done'}: yield")

        """==================== TRAN - load key return ===================="""
        OB_LD_RET_ADDR = "X3"

        """----- synchronization check -----"""
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: load from 0x%x returns, mlp = %d' {'X0'} {OB_LD_RET_ADDR} {REG_LD_CONCURRENCY}")
        tran_key_ld_ret.writeAction(f"subi {REG_LD_CONCURRENCY} {REG_LD_CONCURRENCY} {1}")
        # wait the load value return processed before terminating
        tran_key_ld_ret.writeAction(f"beqi {REG_MATCH_STATUS} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}")
        tran_key_ld_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}")
        tran_key_ld_ret.writeAction(f"beqi {REG_MATCH_STATUS} {1} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: last in-flight load key & value returned already, terminating... TID = %d' {'X0'} {'TID'}")
        # unlocked already, no need to unlock
        tran_key_ld_ret.writeAction("yield_terminate")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}: yield")

        """----- Check returned keys -----"""
        # check if return is matched with (last) send address
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}: bne {OB_LD_RET_ADDR} {REG_LAST_LOAD_ADDR} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{7 * cls.KEY_SIZE}'}")  # tmp3 => last send addr
        # if it is the last send, branch to check only the valid entries
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: tail send load returns, num entries = %d' {'X0'} {REG_LAST_LOAD_EFFECTIVE_WORDS}")  # tmp2 => last send num valid entries
        for i in range(8, 0, -1):
            tran_key_ld_ret.writeAction(f"beqi {REG_LAST_LOAD_EFFECTIVE_WORDS} {i} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}'}")
        # match return data
        for i in range(8, 0, -1):
            tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}'}: beq {f'X{i + 8 - 1}'} {REG_KEY} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}_match'}")

        """-> not matched (fall through)"""
        tran_key_ld_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait_ld'}")
        # from here, all in-flight loads are done & no match found
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: no matched entry found' {'X0'}")
        # return format: (key, 0)
        tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_TMP1} {0}")  # indicate failue
        sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, REG_KEY, REG_TMP1)
        # sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, 'X0', REG_TMP3)  # for debug
        cls.lock.read_end(tran_key_ld_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        tran_key_ld_ret.writeAction("yield_terminate")  # only if running out of space!

        # -> wait for in-flight load to come back
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait_ld'}: yield")

        """-> matched"""
        for i in range(0, 8):
            # calculate the entry index from key address
            tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{i * cls.KEY_SIZE}_match'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP1} 0 8")
            if cls.DEBUG:
                tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: matched at word offset {i}' {'X0'}")
            tran_key_ld_ret.writeAction(f"sub {OB_LD_RET_ADDR} {REG_TMP1} {REG_TMP1}")
            tran_key_ld_ret.writeAction(f"rshift {REG_TMP1} {REG_TMP1} {int(math.log2(cls.KEY_SIZE))}")
            tran_key_ld_ret.writeAction(f"addi {REG_TMP1} {REG_TMP1} {i}")  # REG_TMP1 => entry index
            tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_load_word_cnt'}")

        # load word counter (first word of value)
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_load_word_cnt'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_VAL_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_VAL_RD_ADDR} 0 8")
        tran_key_ld_ret.writeAction(f"move {cls.LANE_DESC_STURCT_OFF_VAL_NUM_WORDS}({REG_LANE_DESC_LM_ADDR}) {REG_TMP2} 0 4")  # REG_TMP2 => value num words
        tran_key_ld_ret.writeAction(f"mul {REG_TMP2} {REG_TMP1} {REG_TMP1}")
        tran_key_ld_ret.writeAction(f"lshift {REG_TMP1} {REG_TMP1} {int(math.log2(cls.WORD_SIZE))}")
        tran_key_ld_ret.writeAction(f"add {REG_VAL_RD_ADDR} {REG_TMP1} {REG_VAL_RD_ADDR}")
        # tran_key_ld_ret.writeAction(f"send_dmlm_ld_wret {REG_VAL_RD_ADDR} {tran_word_cnt_ld_ret.getLabel()} {1}")
        sht_macros.dram_read_ret(tran=tran_key_ld_ret, addr_reg=REG_VAL_RD_ADDR, ret_tran_label=tran_word_cnt_ld_ret.getLabel(), tmp_reg=REG_TMP3, arg_lm_words=1)
        tran_key_ld_ret.writeAction("yield")

        """==================== TRAN - load word counter return ===================="""
        # FIXME: check if there is no next SHT registered, if so, reply error
        if cls.DEBUG:
            tran_word_cnt_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: word counter = %d' {'X0'} {'X8'}")
        # check if the entry is migrated
        tran_word_cnt_ld_ret.writeAction(f"beqi {'X8'} {-1} {f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-redirect'}")
        # bundary check
        tran_word_cnt_ld_ret.writeAction(f"bge {REG_OFFSET} {'X8'} {f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-out_of_bound'}")
        # handle less equal than 8 words case
        tran_word_cnt_ld_ret.writeAction(f"sub {'X8'} {REG_OFFSET} {REG_NUM_VAL_WORDS}")  # WARNING: REG_NUM_VAL_WORDS represents the number of valid words adjusted for the offset

        """----- Send load value -----"""
        tran_word_cnt_ld_ret.writeAction(f"move {'X8'} {cls.WORD_SIZE * 1}({REG_BUCKET_BUF_LM_ADDR}) 0 8")  # store word counter in the buffer
        tran_word_cnt_ld_ret.writeAction(f"lshift_add_imm {REG_OFFSET} {REG_TMP1} {int(math.log2(cls.WORD_SIZE))} {cls.WORD_SIZE}")  # skip the word counter
        tran_word_cnt_ld_ret.writeAction(f"add {REG_VAL_RD_ADDR} {REG_TMP1} {REG_TMP1}")

        if cls.DEBUG:
            tran_word_cnt_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: sending load to addr = 0x%x' {'X0'} {REG_TMP1}")

        # calling with the proper number of operands
        for i in range(1, 9):
            tran_word_cnt_ld_ret.writeAction(f"beqi {REG_NUM_VAL_WORDS} {i} {f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-match_send_val_{i}'}")
        tran_word_cnt_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-match_send_val_8'}")  # for value words > 8, load the first 8 words
        for i in range(1, 9):
            # tran_word_cnt_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-match_send_val_{i}'}: send_dmlm_ld_wret {REG_TMP1} {tran_val_ld_ret.getLabel()} {i}")
            sht_macros.dram_read_ret(tran=tran_word_cnt_ld_ret, addr_reg=REG_TMP1, ret_tran_label=tran_val_ld_ret.getLabel(), tmp_reg=REG_TMP2, arg_lm_words=i, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-match_send_val_{i}')
            if i <= 6:
                tran_word_cnt_ld_ret.writeAction(f"mov_imm2reg {REG_TMP2} {i}")  # words to be copied
            else:
                tran_word_cnt_ld_ret.writeAction(f"mov_imm2reg {REG_TMP2} {6}")  # words to be copied
            if cls.DEBUG:
                tran_word_cnt_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: loading {i} words value' {'X0'}")
            tran_word_cnt_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-match_send_val_done'}")
        tran_word_cnt_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-match_send_val_done'}: mov_imm2reg {REG_MATCH_STATUS} {1}")  # mark key found
        if cls.DEBUG:
            tran_word_cnt_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: key found and value load issued' {'X0'}")
        tran_word_cnt_ld_ret.writeAction("yield")

        """----- Entry migrated, redirect call -----"""
        # prepare redirect arguments
        tran_word_cnt_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-redirect'}: sub {REG_LANE_DESC_LM_ADDR} {'X7'} {REG_TMP2}")
        if cls.DEBUG:
            tran_word_cnt_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: entry already migrated, redirecting call...' {'X0'}")
        tran_word_cnt_ld_ret.writeAction(f"addi {REG_TMP2} {REG_TMP2} {cls.LANE_DESC_SIZE}")  # REG_TMP2 => ext sht desc lm offset

        SHTExt.ext_graph_get_with_offset_wcont(tran=tran_word_cnt_ld_ret, ret=REG_CONT, tmp_reg=REG_TMP3, desc_lm_offset_reg=REG_TMP2, key_reg=REG_KEY, offset_reg=REG_OFFSET)  # redirect call

        tran_word_cnt_ld_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-wait_key_ld'}")
        cls.lock.read_end(tran_word_cnt_ld_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        tran_word_cnt_ld_ret.writeAction("yield_terminate")
        tran_word_cnt_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-wait_key_ld'}: mov_imm2reg {REG_MATCH_STATUS} {2}")  # mark redirect / oob
        tran_word_cnt_ld_ret.writeAction("yield")

        """----- Out of bound -----"""
        # return format: (key, 0)
        # FIXME: are we guroanteed that all of the in-flight loads are done?
        tran_word_cnt_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-out_of_bound'}: mov_imm2reg {REG_TMP1} {0}")
        if cls.DEBUG:
            tran_word_cnt_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: offset out of bound, return with failure.' {'X0'}")
        sht_macros.return_wreg(tran_word_cnt_ld_ret, REG_CONT, REG_KEY, REG_TMP1)
        cls.lock.read_end(tran_word_cnt_ld_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        tran_word_cnt_ld_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-wait_key_ld'}")  # jump back
        tran_word_cnt_ld_ret.writeAction("yield_terminate")

        """==================== TRAN - load val return ===================="""
        if cls.DEBUG:
            tran_val_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: value load returns' {'X0'}")
        tran_val_ld_ret.writeAction(f"mov_imm2reg {REG_MATCH_STATUS} {2}")  # mark value returned
        cls.lock.read_end(tran_val_ld_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)

        # return format (key, num_nb, val0~5)
        tran_val_ld_ret.writeAction(f"move {REG_KEY} {0}({REG_BUCKET_BUF_LM_ADDR}) 0 8")  # key
        # NOTE: num_nb/word_counter is already put into the buffer
        tran_val_ld_ret.writeAction(f"addi {REG_BUCKET_BUF_LM_ADDR} {REG_TMP1} {cls.WORD_SIZE * 2}")
        tran_val_ld_ret.writeAction(f"bcopy_ops {'X8'} {REG_TMP1} {REG_TMP2}")

        for i in range(1, 7):
            tran_val_ld_ret.writeAction(f"beqi {REG_NUM_VAL_WORDS} {i} {f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-ret_val_{i}'}")
        tran_val_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-ret_val_6'}")  # for value words > 6, load the first 6 words
        for i in range(1, 7):
            tran_val_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-ret_val_{i}'}: addi {REG_TMP1} {REG_TMP1} {0}")  # FIXME: dummy
            sht_macros.return_wlm(tran_val_ld_ret, REG_CONT, REG_BUCKET_BUF_LM_ADDR, i + 2)
            tran_val_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-ret_val_done'}")

        tran_val_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-ret_val_done'}: bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-wait_after_ld_val'}")
        tran_val_ld_ret.writeAction("yield_terminate")
        tran_val_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-wait_after_ld_val'}: yield")

    @classmethod
    def ext_graph_get_with_offset(cls, tran: Transition, ret_label: int, tmp_reg0: str, tmp_reg1: str, desc_lm_offset_reg: str, key_reg: str, offset_reg: str, dst_nwid_reg: str = 'X0'):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_ext_graph_get_with_offset.getLabel(), ret_tran_label=ret_label, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=desc_lm_offset_reg, arg_reg1=key_reg, arg_reg2=offset_reg)

    @classmethod
    def ext_graph_get_with_offset_wcont(cls, tran: Transition, cont_reg: str, tmp_reg: str, desc_lm_offset_reg: str, key_reg: str, offset_reg: str, dst_nwid_reg: str = 'X0'):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_ext_graph_get_with_offset.getLabel(), cont_reg=cont_reg, tmp_reg=tmp_reg, arg_reg0=desc_lm_offset_reg, arg_reg1=key_reg, arg_reg2=offset_reg)

    @classmethod
    def _ext_graph_get_word_cnt(cls, state: State):
        """
        Extended to get word counter + call redirection

        X8  - LANE_DESC_LM_OFFSET(0:31) | BUCKET_DESC_LM_OFFSET(32:63)
        X9  - KEY
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._ext_graph_get_word_cnt.__name__

        from sht_ext import SHTExt

        OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET = "X8"
        OB_KEY = "X9"

        REG_TMP1 = "X17"
        REG_TMP2 = "X18"
        REG_TMP3 = "X19"

        REG_LD_CONCURRENCY = "X20"
        REG_VAL_RD_ADDR = "X22"
        REG_MATCH_STATUS = "X23"
        REG_LAST_LOAD_EFFECTIVE_WORDS = "X25"
        REG_LAST_LOAD_ADDR = "X26"

        REG_LANE_DESC_LM_ADDR = "X27"
        REG_BUCKET_DESC_LM_ADDR = "X28"
        REG_BUCKET_BUF_LM_ADDR = "X29"
        REG_KEY = "X30"

        REG_CONT = "X31"

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_ext_graph_get_word_cnt
        if tran is None:
            return
        cls.tran_label_ext_graph_get_word_cnt = tran.getLabel()
        tran_key_ld_ret = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-key_ld_ret")
        tran_word_cnt_ld_ret = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret")

        """==================== TRAN - function entry ===================="""
        """----- Prep -----"""
        # calc desc lm addr
        tran.writeAction(f"rshift {OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET} {REG_BUCKET_DESC_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_BUCKET_DESC_LM_ADDR} {'X7'} {REG_BUCKET_DESC_LM_ADDR}")
        # get lock
        cls.lock.read_begin(tran, REG_BUCKET_DESC_LM_ADDR, REG_TMP1, 2)
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: lock admitted, TID = %d' {'X0'} {'TID'}")
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: REG_BUCKET_DESC_LM_ADDR = 0x%x' {'X0'} {REG_BUCKET_DESC_LM_ADDR}")

        # calc desc lm addr
        tran.writeAction(f"lshift {OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET} {REG_LANE_DESC_LM_ADDR} {32}")
        tran.writeAction(f"rshift {REG_LANE_DESC_LM_ADDR} {REG_LANE_DESC_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_LANE_DESC_LM_ADDR} {'X7'} {REG_LANE_DESC_LM_ADDR}")

        # copy ob regs
        tran.writeAction(f"addi {OB_KEY} {REG_KEY} {0}")
        # save cont
        tran.writeAction(f"addi {'X1'} {REG_CONT} {0}")

        # load desc
        tran.writeAction(f"addi {REG_BUCKET_DESC_LM_ADDR} {REG_BUCKET_BUF_LM_ADDR} {cls.BUCKET_DESC_STURCT_OFF_LM_BUF}")

        """----- Empty Bucket -----"""
        # ----- if entry count is zero, return not found -----
        tran.writeAction(f"bgti {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-setup_send_ld'}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: empty bucket, return without search' {'X0'}")
        # return format: (key, 0)
        # tran.writeAction(f"mov_imm2reg {REG_TMP1} {0}")  # indicate failue
        sht_macros.return_wreg(tran, REG_CONT, REG_KEY, REG_TMP1)
        # sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, 'X0', REG_TMP3)  # for debug
        cls.lock.read_end(tran, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        tran.writeAction("yield_terminate")

        """----- Filled Bucket -----"""
        # ----- already have entires, send load entries -----
        # init
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-setup_send_ld'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_LAST_LOAD_ADDR} 0 8")  # tmp3 => key load start address
        tran.writeAction(f"mov_imm2reg {REG_LD_CONCURRENCY} {0}")
        tran.writeAction(f"mov_imm2reg {REG_MATCH_STATUS} {0}")

        tran.writeAction(f"blei {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_done'}")  # tmp1 => entry_count
        # tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_ld'}: send_dmlm_ld_wret {REG_LAST_LOAD_ADDR} {tran_key_ld_ret.getLabel()} {8}")
        sht_macros.dram_read_ret(tran=tran, addr_reg=REG_LAST_LOAD_ADDR, ret_tran_label=tran_key_ld_ret.getLabel(), tmp_reg=REG_TMP2, arg_lm_words=8, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-LB-send_ld')
        tran.writeAction(f"addi {REG_LD_CONCURRENCY} {REG_LD_CONCURRENCY} {1}")  # concurrency++
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: loading, DRAM addr = 0x%x' {'X0'} {REG_LAST_LOAD_ADDR}")
        # check if number of valid entries in the send is greater than 8
        tran.writeAction(f"bgti {REG_TMP1} {64 // cls.KEY_SIZE} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}")
        # last send, retain last send addr & valid size
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: all loads sent' {'X0'}")
        tran.writeAction(f"mov_reg2reg {REG_TMP1} {REG_LAST_LOAD_EFFECTIVE_WORDS}")  # record last load effective size
        tran.writeAction("yield")
        # full 8 word send
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}: subi {REG_TMP1} {REG_TMP1} {64 // cls.KEY_SIZE}")
        tran.writeAction(f"addi {REG_LAST_LOAD_ADDR} {REG_LAST_LOAD_ADDR} {64}")
        tran.writeAction(f"bgti {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_ld'}")
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_done'}: yield")

        """==================== TRAN - load key return ===================="""
        OB_LD_RET_ADDR = "X3"

        """----- synchronization check -----"""
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: load from 0x%x returns, mlp = %d' {'X0'} {OB_LD_RET_ADDR} {REG_LD_CONCURRENCY}")
        tran_key_ld_ret.writeAction(f"subi {REG_LD_CONCURRENCY} {REG_LD_CONCURRENCY} {1}")
        # wait the load value return processed before terminating
        tran_key_ld_ret.writeAction(f"beqi {REG_MATCH_STATUS} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}")
        tran_key_ld_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}")
        tran_key_ld_ret.writeAction(f"beqi {REG_MATCH_STATUS} {1} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: last in-flight load key & value returned already, terminating... TID = %d' {'X0'} {'TID'}")
        # unlocked already, no need to unlock
        tran_key_ld_ret.writeAction("yield_terminate")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}: yield")

        """----- Check returned keys -----"""
        # check if return is matched with (last) send address
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}: bne {OB_LD_RET_ADDR} {REG_LAST_LOAD_ADDR} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{7 * cls.KEY_SIZE}'}")  # tmp3 => last send addr
        # if it is the last send, branch to check only the valid entries
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: tail send load returns, num entries = %d' {'X0'} {REG_LAST_LOAD_EFFECTIVE_WORDS}")  # tmp2 => last send num valid entries
        for i in range(8, 0, -1):
            tran_key_ld_ret.writeAction(f"beqi {REG_LAST_LOAD_EFFECTIVE_WORDS} {i} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}'}")
        # match return data
        for i in range(8, 0, -1):
            tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}'}: beq {f'X{i + 8 - 1}'} {REG_KEY} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}_match'}")

        """-> not matched (fall through)"""
        tran_key_ld_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait_ld'}")
        # from here, all in-flight loads are done & no match found
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: no matched entry found' {'X0'}")
        # return format: (key, 0)
        tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_TMP1} {0}")  # indicate failue
        sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, REG_KEY, REG_TMP1)
        # sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, 'X0', REG_TMP3)  # for debug
        cls.lock.read_end(tran_key_ld_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        tran_key_ld_ret.writeAction("yield_terminate")  # only if running out of space!

        # -> wait for in-flight load to come back
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait_ld'}: yield")

        """-> matched"""
        for i in range(0, 8):
            # calculate the entry index from key address
            tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{i * cls.KEY_SIZE}_match'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP1} 0 8")
            if cls.DEBUG:
                tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: matched at word offset {i}' {'X0'}")
            tran_key_ld_ret.writeAction(f"sub {OB_LD_RET_ADDR} {REG_TMP1} {REG_TMP1}")
            tran_key_ld_ret.writeAction(f"rshift {REG_TMP1} {REG_TMP1} {int(math.log2(cls.KEY_SIZE))}")
            tran_key_ld_ret.writeAction(f"addi {REG_TMP1} {REG_TMP1} {i}")  # REG_TMP1 => entry index
            tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_load_word_cnt'}")

        # load word counter (first word of value)
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_load_word_cnt'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_VAL_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_VAL_RD_ADDR} 0 8")
        tran_key_ld_ret.writeAction(f"move {cls.LANE_DESC_STURCT_OFF_VAL_NUM_WORDS}({REG_LANE_DESC_LM_ADDR}) {REG_TMP2} 0 4")  # REG_TMP2 => value num words
        tran_key_ld_ret.writeAction(f"mul {REG_TMP2} {REG_TMP1} {REG_TMP1}")
        tran_key_ld_ret.writeAction(f"lshift {REG_TMP1} {REG_TMP1} {int(math.log2(cls.WORD_SIZE))}")
        tran_key_ld_ret.writeAction(f"add {REG_VAL_RD_ADDR} {REG_TMP1} {REG_VAL_RD_ADDR}")
        # tran_key_ld_ret.writeAction(f"send_dmlm_ld_wret {REG_VAL_RD_ADDR} {tran_word_cnt_ld_ret.getLabel()} {1}")
        sht_macros.dram_read_ret(tran=tran_key_ld_ret, addr_reg=REG_VAL_RD_ADDR, ret_tran_label=tran_word_cnt_ld_ret.getLabel(), tmp_reg=REG_TMP3, arg_lm_words=1)
        tran_key_ld_ret.writeAction("yield")

        """==================== TRAN - load word counter return ===================="""
        # FIXME: check if there is no next SHT registered, if so, reply error
        # check if the entry is migrated
        tran_word_cnt_ld_ret.writeAction(f"beqi {'X8'} {-1} {f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-redirect'}")

        """----- reply word counter -----"""
        # return format: (key, val_start_addr, word_cnt)
        sht_macros.return_wreg(tran_word_cnt_ld_ret, REG_CONT, REG_KEY, REG_VAL_RD_ADDR, 'X8')
        cls.lock.read_end(tran_word_cnt_ld_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        tran_word_cnt_ld_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-wait_key_ld'}")
        tran_word_cnt_ld_ret.writeAction("yield_terminate")

        """----- Entry migrated, redirect call -----"""
        # prepare redirect arguments
        tran_word_cnt_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-redirect'}: sub {REG_LANE_DESC_LM_ADDR} {'X7'} {REG_TMP2}")
        tran_word_cnt_ld_ret.writeAction(f"addi {REG_TMP2} {REG_TMP2} {cls.LANE_DESC_SIZE}")  # REG_TMP2 => ext sht desc lm offset
        tran_word_cnt_ld_ret.writeAction(f"sub {REG_BUCKET_BUF_LM_ADDR} {'X7'} {REG_TMP3}")  # REG_TMP3 => tmp buf lm offset
        tran_word_cnt_ld_ret.writeAction(f"lshift_or {REG_TMP3} {REG_TMP2} {32}")  # REG_TMP2 => SHT_DESC_LM_OFFSET(0:31) | TMP_BUF_LM_OFFSET(32:63)

        SHTExt.ext_graph_get_word_cnt_wcont(tran=tran_word_cnt_ld_ret, ret=REG_CONT, tmp_reg=REG_TMP3, desc_lm_offset_reg=REG_TMP2, key_reg=REG_KEY)  # redirect call

        tran_word_cnt_ld_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-wait_key_ld'}")
        tran_word_cnt_ld_ret.writeAction("yield_terminate")
        tran_word_cnt_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-wait_key_ld'}: mov_imm2reg {REG_MATCH_STATUS} {2}")  # mark redirect
        tran_word_cnt_ld_ret.writeAction("yield")

    @classmethod
    def ext_graph_get_word_cnt(cls, tran: Transition, ret_label: int, tmp_reg0: str, tmp_reg1: str, desc_lm_offset_reg: str, key_reg: str, dst_nwid_reg: str = 'X0'):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_ext_graph_get_word_cnt.getLabel(), ret_tran_label=ret_label, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=desc_lm_offset_reg, arg_reg1=key_reg)

    @classmethod
    def ext_graph_get_word_cnt_wcont(cls, tran: Transition, cont_reg: str, tmp_reg: str, desc_lm_offset_reg: str, key_reg: str, dst_nwid_reg: str = 'X0'):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_ext_graph_get_word_cnt.getLabel(), cont_reg=cont_reg, tmp_reg=tmp_reg, arg_reg0=desc_lm_offset_reg, arg_reg1=key_reg)

    @classmethod
    def _get_with_offset(cls, state: State):
        """
        Extended to support offset

        X8  - LANE_DESC_LM_OFFSET(0:31) | BUCKET_DESC_LM_OFFSET(32:63)
        X9  - KEY
        X10 - OFFSET
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._get_with_offset.__name__

        OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET = "X8"
        OB_KEY = "X9"
        OB_OFFSET = "X10"

        REG_TMP1 = "X17"
        REG_TMP2 = "X18"

        REG_LD_CONCURRENCY = "X20"
        REG_VAL_RD_ADDR = "X22"
        REG_MATCH_STATUS = "X23"
        REG_NUM_VAL_WORDS = "X24"  # number of value operations
        REG_LAST_LOAD_EFFECTIVE_WORDS = "X25"
        REG_LAST_LOAD_ADDR = "X26"

        REG_LANE_DESC_LM_ADDR = "X27"
        REG_BUCKET_DESC_LM_ADDR = "X28"
        REG_BUCKET_BUF_LM_ADDR = "X29"
        REG_KEY = "X30"
        REG_OFFSET = "X16"

        REG_CONT = "X31"

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_get_with_offset
        if tran is None:
            return
        cls.tran_label_get_with_offset = tran.getLabel()
        tran_key_ld_ret = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-key_ld_ret")
        tran_val_ld_ret = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-val_ld_ret")

        """==================== TRAN - function entry ===================="""
        """----- Prep -----"""
        # calc desc lm addr
        tran.writeAction(f"rshift {OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET} {REG_BUCKET_DESC_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_BUCKET_DESC_LM_ADDR} {'X7'} {REG_BUCKET_DESC_LM_ADDR}")
        # get lock
        cls.lock.read_begin(tran, REG_BUCKET_DESC_LM_ADDR, REG_TMP1, 3)
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: lock admitted, TID = %d' {'X0'} {'TID'}")
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: REG_BUCKET_DESC_LM_ADDR = 0x%x' {'X0'} {REG_BUCKET_DESC_LM_ADDR}")

        # calc desc lm addr
        tran.writeAction(f"lshift {OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET} {REG_LANE_DESC_LM_ADDR} {32}")
        tran.writeAction(f"rshift {REG_LANE_DESC_LM_ADDR} {REG_LANE_DESC_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_LANE_DESC_LM_ADDR} {'X7'} {REG_LANE_DESC_LM_ADDR}")

        # copy ob regs
        tran.writeAction(f"addi {OB_KEY} {REG_KEY} {0}")
        tran.writeAction(f"addi {OB_OFFSET} {REG_OFFSET} {0}")
        # save cont
        tran.writeAction(f"addi {'X1'} {REG_CONT} {0}")

        # load desc
        tran.writeAction(f"addi {REG_BUCKET_DESC_LM_ADDR} {REG_BUCKET_BUF_LM_ADDR} {cls.BUCKET_DESC_STURCT_OFF_LM_BUF}")
        tran.writeAction(f"move {cls.LANE_DESC_STURCT_OFF_VAL_NUM_WORDS}({REG_LANE_DESC_LM_ADDR}) {REG_NUM_VAL_WORDS} 0 4")
        tran.writeAction(f"sub {REG_NUM_VAL_WORDS} {REG_OFFSET} {REG_NUM_VAL_WORDS}")  # WARNING: adjusted for the offset

        tran.writeAction(f"move {cls.BUCKET_DESC_STURCT_OFF_ENTRY_COUNT}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP1} 0 4")  # tmp1 => entry_count

        """----- Empty Bucket -----"""
        # ----- if entry count is zero, return not found -----
        tran.writeAction(f"bgti {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-setup_send_ld'}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: empty bucket, return without search' {'X0'}")
        # return format: (key, -1)
        tran.writeAction(f"mov_imm2reg {REG_TMP1} {-1}")  # indicate failue
        sht_macros.return_wreg(tran, REG_CONT, REG_KEY, REG_TMP1)
        # sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, 'X0', REG_TMP3)  # for debug
        cls.lock.read_end(tran, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        tran.writeAction("yield_terminate")  # only if running out of space!

        """----- Filled Bucket -----"""
        # ----- already have entires, send load entries -----
        # init
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-setup_send_ld'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_LAST_LOAD_ADDR} 0 8")  # tmp3 => key load start address
        tran.writeAction(f"mov_imm2reg {REG_LD_CONCURRENCY} {0}")
        tran.writeAction(f"mov_imm2reg {REG_MATCH_STATUS} {0}")

        tran.writeAction(f"blei {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_done'}")  # tmp1 => entry_count
        # tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_ld'}: send_dmlm_ld_wret {REG_LAST_LOAD_ADDR} {tran_key_ld_ret.getLabel()} {8}")
        sht_macros.dram_read_ret(tran=tran, addr_reg=REG_LAST_LOAD_ADDR, ret_tran_label=tran_key_ld_ret.getLabel(), tmp_reg=REG_TMP2, arg_lm_words=8, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-LB-send_ld')
        tran.writeAction(f"addi {REG_LD_CONCURRENCY} {REG_LD_CONCURRENCY} {1}")  # concurrency++
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: loading, DRAM addr = 0x%x' {'X0'} {REG_LAST_LOAD_ADDR}")
        # check if number of valid entries in the send is greater than 8
        tran.writeAction(f"bgti {REG_TMP1} {64 // cls.KEY_SIZE} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}")
        # last send, retain last send addr & valid size
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: all loads sent' {'X0'}")
        tran.writeAction(f"mov_reg2reg {REG_TMP1} {REG_LAST_LOAD_EFFECTIVE_WORDS}")  # record last load effective size
        tran.writeAction("yield")
        # full 8 word send
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}: subi {REG_TMP1} {REG_TMP1} {64 // cls.KEY_SIZE}")
        tran.writeAction(f"addi {REG_LAST_LOAD_ADDR} {REG_LAST_LOAD_ADDR} {64}")
        tran.writeAction(f"bgti {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_ld'}")
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_done'}: yield")

        """==================== TRAN - load key return ===================="""
        OB_LD_RET_ADDR = "X3"

        """----- synchronization check -----"""
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: load from 0x%x returns, mlp = %d' {'X0'} {OB_LD_RET_ADDR} {REG_LD_CONCURRENCY}")
        tran_key_ld_ret.writeAction(f"subi {REG_LD_CONCURRENCY} {REG_LD_CONCURRENCY} {1}")
        # wait the load value return processed before terminating
        tran_key_ld_ret.writeAction(f"beqi {REG_MATCH_STATUS} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}")
        tran_key_ld_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}")
        tran_key_ld_ret.writeAction(f"beqi {REG_MATCH_STATUS} {1} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: last in-flight load key & value returned already, terminating... TID = %d' {'X0'} {'TID'}")
        # unlocked already, no need to unlock
        tran_key_ld_ret.writeAction("yield_terminate")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}: yield")

        """----- Check returned keys -----"""
        # check if return is matched with (last) send address
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}: bne {OB_LD_RET_ADDR} {REG_LAST_LOAD_ADDR} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{7 * cls.KEY_SIZE}'}")  # tmp3 => last send addr
        # if it is the last send, branch to check only the valid entries
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: tail send load returns, num entries = %d' {'X0'} {REG_LAST_LOAD_EFFECTIVE_WORDS}")  # tmp2 => last send num valid entries
        for i in range(8, 0, -1):
            tran_key_ld_ret.writeAction(f"beqi {REG_LAST_LOAD_EFFECTIVE_WORDS} {i} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}'}")
        # match return data
        for i in range(8, 0, -1):
            tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}'}: beq {f'X{i + 8 - 1}'} {REG_KEY} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}_match'}")

        """-> not matched (fall through)"""
        tran_key_ld_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait_ld'}")
        # from here, all in-flight loads are done & no match found
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: no matched entry found' {'X0'}")
        # return format: (key, -1)
        tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_TMP1} {-1}")  # indicate failue
        sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, REG_KEY, REG_TMP1)
        # sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, 'X0', REG_TMP3)  # for debug
        cls.lock.read_end(tran_key_ld_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        tran_key_ld_ret.writeAction("yield_terminate")  # only if running out of space!

        # -> wait for in-flight load to come back
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait_ld'}: yield")

        """-> matched"""
        for i in range(0, 8):
            # calculate the entry index from key address
            tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{i * cls.KEY_SIZE}_match'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP1} 0 8")
            if cls.DEBUG:
                tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: matched at word offset {i}' {'X0'}")
            tran_key_ld_ret.writeAction(f"sub {OB_LD_RET_ADDR} {REG_TMP1} {REG_TMP1}")
            tran_key_ld_ret.writeAction(f"rshift {REG_TMP1} {REG_TMP1} {int(math.log2(cls.KEY_SIZE))}")
            tran_key_ld_ret.writeAction(f"addi {REG_TMP1} {REG_TMP1} {i}")  # REG_TMP1 => entry index
            tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_ld'}")

        """----- Send load value -----"""
        # calculate value address
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_ld'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_VAL_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_VAL_RD_ADDR} 0 8")
        tran_key_ld_ret.writeAction(f"move {cls.LANE_DESC_STURCT_OFF_VAL_NUM_WORDS}({REG_LANE_DESC_LM_ADDR}) {REG_TMP2} 0 4")
        tran_key_ld_ret.writeAction(f"mul {REG_TMP2} {REG_TMP1} {REG_TMP1}")
        tran_key_ld_ret.writeAction(f"add {REG_TMP1} {REG_OFFSET} {REG_TMP1}")  # add the offset
        tran_key_ld_ret.writeAction(f"lshift {REG_TMP1} {REG_TMP1} {int(math.log2(cls.WORD_SIZE))}")
        tran_key_ld_ret.writeAction(f"add {REG_VAL_RD_ADDR} {REG_TMP1} {REG_VAL_RD_ADDR}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: sending load to addr = 0x%x' {'X0'} {REG_VAL_RD_ADDR}")

        # calling with the proper number of operands
        for i in range(1, 9):
            tran_key_ld_ret.writeAction(f"beqi {REG_NUM_VAL_WORDS} {i} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_{i}'}")
        tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_8'}")  # for value words > 8, load the first 8 words
        for i in range(1, 9):
            # tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_{i}'}: send_dmlm_ld_wret {REG_VAL_RD_ADDR} {tran_val_ld_ret.getLabel()} {i}")
            sht_macros.dram_read_ret(tran=tran_key_ld_ret, addr_reg=REG_VAL_RD_ADDR, ret_tran_label=tran_val_ld_ret.getLabel(), tmp_reg=REG_TMP2, arg_lm_words=i, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_{i}')
            if i <= 6:
                tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_TMP2} {i}")  # words to be copied
            else:
                tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_TMP2} {6}")  # words to be copied
            if cls.DEBUG:
                tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: loading {i} words value' {'X0'}")
            tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_done'}")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_done'}: mov_imm2reg {REG_MATCH_STATUS} {1}")  # mark key found
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: key found and value load issued' {'X0'}")
        tran_key_ld_ret.writeAction("yield")

        """==================== TRAN - load val return ===================="""
        if cls.DEBUG:
            tran_val_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: value load returns' {'X0'}")
        tran_val_ld_ret.writeAction(f"mov_imm2reg {REG_MATCH_STATUS} {2}")  # mark value returned
        cls.lock.read_end(tran_val_ld_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)

        # return format (key, offset, val0~5)
        tran_val_ld_ret.writeAction(f"move {REG_KEY} {0}({REG_BUCKET_BUF_LM_ADDR}) 0 8")  # key
        tran_val_ld_ret.writeAction(f"move {REG_OFFSET} {8}({REG_BUCKET_BUF_LM_ADDR}) 0 8")  # offset
        tran_val_ld_ret.writeAction(f"addi {REG_BUCKET_BUF_LM_ADDR} {REG_TMP1} {cls.WORD_SIZE * 2}")
        tran_val_ld_ret.writeAction(f"bcopy_ops {'X8'} {REG_TMP1} {REG_TMP2}")

        for i in range(1, 7):
            tran_val_ld_ret.writeAction(f"beqi {REG_NUM_VAL_WORDS} {i} {f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-ret_val_{i}'}")
        tran_val_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-ret_val_6'}")  # for value words > 6, load the first 6 words
        for i in range(1, 7):
            tran_val_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-ret_val_{i}'}: addi {REG_TMP1} {REG_TMP1} {0}")  # FIXME: dummy
            sht_macros.return_wlm(tran_val_ld_ret, REG_CONT, REG_BUCKET_BUF_LM_ADDR, i + 2)
            tran_val_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-ret_val_done'}")

        tran_val_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-ret_val_done'}: bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-wait_after_ld_val'}")
        tran_val_ld_ret.writeAction("yield_terminate")
        tran_val_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-wait_after_ld_val'}: yield")

    @classmethod
    def get_with_offset(cls, tran: Transition, ret_label: int, tmp_reg0: str, tmp_reg1: str, desc_lm_offset_reg: str, key_reg: str, offset_reg: str, dst_nwid_reg: str = 'X0'):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_get_with_offset.getLabel(), ret_tran_label=ret_label, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=desc_lm_offset_reg, arg_reg1=key_reg, arg_reg2=offset_reg)

    @classmethod
    def get_with_offset_wcont(cls, tran: Transition, cont_reg: str, tmp_reg: str, desc_lm_offset_reg: str, key_reg: str, offset_reg: str, dst_nwid_reg: str = 'X0'):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_get_with_offset.getLabel(), cont_reg=cont_reg, tmp_reg=tmp_reg, arg_reg0=desc_lm_offset_reg, arg_reg1=key_reg, arg_reg2=offset_reg)

    @classmethod
    def _get_with_mask(cls, state: State):
        """
        Extended to support mask

        X8  - LANE_DESC_LM_OFFSET(0:31) | BUCKET_DESC_LM_OFFSET(32:63)
        X9  - KEY
        X10 - MASK
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._get_with_mask.__name__

        OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET = "X8"
        OB_KEY = "X9"
        OB_MASK = "X10"

        REG_TMP1 = "X17"
        REG_TMP2 = "X18"
        REG_TMP3 = "X19"

        REG_LD_CONCURRENCY = "X20"
        REG_VAL_RD_ADDR = "X22"
        REG_MATCH_STATUS = "X23"
        REG_NUM_VAL_WORDS = "X24"  # number of value operations
        REG_LAST_LOAD_EFFECTIVE_WORDS = "X25"
        REG_LAST_LOAD_ADDR = "X26"

        REG_LANE_DESC_LM_ADDR = "X27"
        REG_BUCKET_DESC_LM_ADDR = "X28"
        REG_BUCKET_BUF_LM_ADDR = "X29"
        REG_KEY = "X30"
        REG_MASK = "X16"

        REG_CONT = "X31"

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_get_with_mask
        if tran is None:
            return
        cls.tran_label_get_with_mask = tran.getLabel()
        tran_key_ld_ret = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-key_ld_ret")
        tran_val_ld_ret = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-val_ld_ret")

        """==================== TRAN - function entry ===================="""
        """----- Prep -----"""
        # calc desc lm addr
        tran.writeAction(f"rshift {OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET} {REG_BUCKET_DESC_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_BUCKET_DESC_LM_ADDR} {'X7'} {REG_BUCKET_DESC_LM_ADDR}")
        # get lock
        cls.lock.read_begin(tran, REG_BUCKET_DESC_LM_ADDR, REG_TMP1, 3)
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: lock admitted, TID = %d' {'X0'} {'TID'}")
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: REG_BUCKET_DESC_LM_ADDR = 0x%x' {'X0'} {REG_BUCKET_DESC_LM_ADDR}")

        # calc desc lm addr
        tran.writeAction(f"lshift {OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET} {REG_LANE_DESC_LM_ADDR} {32}")
        tran.writeAction(f"rshift {REG_LANE_DESC_LM_ADDR} {REG_LANE_DESC_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_LANE_DESC_LM_ADDR} {'X7'} {REG_LANE_DESC_LM_ADDR}")

        # copy ob regs
        tran.writeAction(f"addi {OB_KEY} {REG_KEY} {0}")
        tran.writeAction(f"addi {OB_MASK} {REG_MASK} {0}")
        # save cont
        tran.writeAction(f"addi {'X1'} {REG_CONT} {0}")

        # load desc
        tran.writeAction(f"addi {REG_BUCKET_DESC_LM_ADDR} {REG_BUCKET_BUF_LM_ADDR} {cls.BUCKET_DESC_STURCT_OFF_LM_BUF}")
        tran.writeAction(f"move {cls.LANE_DESC_STURCT_OFF_VAL_NUM_WORDS}({REG_LANE_DESC_LM_ADDR}) {REG_NUM_VAL_WORDS} 0 4")
        # tran.writeAction(f"sub {REG_NUM_VAL_WORDS} {REG_MASK} {REG_NUM_VAL_WORDS}")  # WARNING: adjusted for the offset

        tran.writeAction(f"move {cls.BUCKET_DESC_STURCT_OFF_ENTRY_COUNT}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP1} 0 4")  # tmp1 => entry_count

        """----- Empty Bucket -----"""
        # ----- if entry count is zero, return not found -----
        tran.writeAction(f"bgti {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-setup_send_ld'}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: empty bucket, return without search' {'X0'}")
        # return format: (key, 0)
        # tran.writeAction(f"mov_imm2reg {REG_TMP1} {0}")  # indicate failue
        sht_macros.return_wreg(tran, REG_CONT, REG_KEY, REG_TMP1)
        # sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, 'X0', REG_TMP3)  # for debug
        cls.lock.read_end(tran, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        tran.writeAction("yield_terminate")  # only if running out of space!

        """----- Filled Bucket -----"""
        # ----- already have entires, send load entries -----
        # init
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-setup_send_ld'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_LAST_LOAD_ADDR} 0 8")  # tmp3 => key load start address
        tran.writeAction(f"mov_imm2reg {REG_LD_CONCURRENCY} {0}")
        tran.writeAction(f"mov_imm2reg {REG_MATCH_STATUS} {0}")

        tran.writeAction(f"blei {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_done'}")  # tmp1 => entry_count
        # tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_ld'}: send_dmlm_ld_wret {REG_LAST_LOAD_ADDR} {tran_key_ld_ret.getLabel()} {8}")
        sht_macros.dram_read_ret(tran=tran, addr_reg=REG_LAST_LOAD_ADDR, ret_tran_label=tran_key_ld_ret.getLabel(), tmp_reg=REG_TMP2, arg_lm_words=8, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-LB-send_ld')
        tran.writeAction(f"addi {REG_LD_CONCURRENCY} {REG_LD_CONCURRENCY} {1}")  # concurrency++
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: loading, DRAM addr = 0x%x' {'X0'} {REG_LAST_LOAD_ADDR}")
        # check if number of valid entries in the send is greater than 8
        tran.writeAction(f"bgti {REG_TMP1} {64 // cls.KEY_SIZE} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}")
        # last send, retain last send addr & valid size
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: all loads sent' {'X0'}")
        tran.writeAction(f"mov_reg2reg {REG_TMP1} {REG_LAST_LOAD_EFFECTIVE_WORDS}")  # record last load effective size
        tran.writeAction("yield")
        # full 8 word send
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}: subi {REG_TMP1} {REG_TMP1} {64 // cls.KEY_SIZE}")
        tran.writeAction(f"addi {REG_LAST_LOAD_ADDR} {REG_LAST_LOAD_ADDR} {64}")
        tran.writeAction(f"bgti {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_ld'}")
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_done'}: yield")

        """==================== TRAN - load key return ===================="""
        OB_LD_RET_ADDR = "X3"

        """----- synchronization check -----"""
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: load from 0x%x returns, mlp = %d' {'X0'} {OB_LD_RET_ADDR} {REG_LD_CONCURRENCY}")
        tran_key_ld_ret.writeAction(f"subi {REG_LD_CONCURRENCY} {REG_LD_CONCURRENCY} {1}")
        # wait the load value return processed before terminating
        tran_key_ld_ret.writeAction(f"beqi {REG_MATCH_STATUS} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}")
        tran_key_ld_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}")
        tran_key_ld_ret.writeAction(f"beqi {REG_MATCH_STATUS} {1} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: last in-flight load key & value returned already, terminating... TID = %d' {'X0'} {'TID'}")
        # unlocked already, no need to unlock
        tran_key_ld_ret.writeAction("yield_terminate")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}: yield")

        """----- Check returned keys -----"""
        # check if return is matched with (last) send address
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}: bne {OB_LD_RET_ADDR} {REG_LAST_LOAD_ADDR} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{7 * cls.KEY_SIZE}'}")  # tmp3 => last send addr
        # if it is the last send, branch to check only the valid entries
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: tail send load returns, num entries = %d' {'X0'} {REG_LAST_LOAD_EFFECTIVE_WORDS}")  # tmp2 => last send num valid entries
        for i in range(8, 0, -1):
            tran_key_ld_ret.writeAction(f"beqi {REG_LAST_LOAD_EFFECTIVE_WORDS} {i} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}'}")
        # match return data
        for i in range(8, 0, -1):
            tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}'}: beq {f'X{i + 8 - 1}'} {REG_KEY} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}_match'}")

        """-> not matched (fall through)"""
        tran_key_ld_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait_ld'}")
        # from here, all in-flight loads are done & no match found
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: no matched entry found' {'X0'}")
        # return format: (key, 0)
        tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_TMP1} {0}")  # indicate failue
        sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, REG_KEY, REG_TMP1)
        # sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, 'X0', REG_TMP3)  # for debug
        cls.lock.read_end(tran_key_ld_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        tran_key_ld_ret.writeAction("yield_terminate")  # only if running out of space!

        # -> wait for in-flight load to come back
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait_ld'}: yield")

        """-> matched"""
        for i in range(0, 8):
            # calculate the entry index from key address
            tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{i * cls.KEY_SIZE}_match'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP1} 0 8")
            if cls.DEBUG:
                tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: matched at word offset {i}' {'X0'}")
            tran_key_ld_ret.writeAction(f"sub {OB_LD_RET_ADDR} {REG_TMP1} {REG_TMP1}")
            tran_key_ld_ret.writeAction(f"rshift {REG_TMP1} {REG_TMP1} {int(math.log2(cls.KEY_SIZE))}")
            tran_key_ld_ret.writeAction(f"addi {REG_TMP1} {REG_TMP1} {i}")  # REG_TMP1 => entry index
            tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_ld'}")

        """----- Send load value -----"""
        # calculate value address
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_ld'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_VAL_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_VAL_RD_ADDR} 0 8")
        tran_key_ld_ret.writeAction(f"move {cls.LANE_DESC_STURCT_OFF_VAL_NUM_WORDS}({REG_LANE_DESC_LM_ADDR}) {REG_TMP2} 0 4")
        tran_key_ld_ret.writeAction(f"mul {REG_TMP2} {REG_TMP1} {REG_TMP1}")
        tran_key_ld_ret.writeAction(f"lshift {REG_TMP1} {REG_TMP1} {int(math.log2(cls.WORD_SIZE))}")
        tran_key_ld_ret.writeAction(f"add {REG_VAL_RD_ADDR} {REG_TMP1} {REG_VAL_RD_ADDR}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: sending load to addr = 0x%x' {'X0'} {REG_VAL_RD_ADDR}")

        # calling with the proper number of operands
        for i in range(1, 9):
            tran_key_ld_ret.writeAction(f"beqi {REG_NUM_VAL_WORDS} {i} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_{i}'}")
        tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_8'}")  # for value words > 8, load the first 8 words
        for i in range(1, 9):
            # tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_{i}'}: send_dmlm_ld_wret {REG_VAL_RD_ADDR} {tran_val_ld_ret.getLabel()} {i}")
            sht_macros.dram_read_ret(tran=tran_key_ld_ret, addr_reg=REG_VAL_RD_ADDR, ret_tran_label=tran_val_ld_ret.getLabel(), tmp_reg=REG_TMP2, arg_lm_words=i, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_{i}')
            tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_TMP2} {i}")  # words to be copied
            if cls.DEBUG:
                tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: loading {i} words value' {'X0'}")
            tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_done'}")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_done'}: mov_imm2reg {REG_MATCH_STATUS} {1}")  # mark key found
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: key found and value load issued' {'X0'}")
        tran_key_ld_ret.writeAction("yield")

        """==================== TRAN - load val return ===================="""
        if cls.DEBUG:
            tran_val_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: value load returns' {'X0'}")
        tran_val_ld_ret.writeAction(f"mov_imm2reg {REG_MATCH_STATUS} {2}")  # mark value returned
        cls.lock.read_end(tran_val_ld_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)

        # return format (key, mask, selected val0~5)
        tran_val_ld_ret.writeAction(f"move {REG_KEY} {0}({REG_BUCKET_BUF_LM_ADDR}) 0 8")  # key
        # tran_val_ld_ret.writeAction(f"move {REG_VAL_RD_ADDR} {8}({REG_BUCKET_BUF_LM_ADDR}) 0 8")  # value address
        tran_val_ld_ret.writeAction(f"move {REG_MASK} {8}({REG_BUCKET_BUF_LM_ADDR}) 0 8")  # mask
        tran_val_ld_ret.writeAction(f"addi {REG_BUCKET_BUF_LM_ADDR} {REG_TMP1} {cls.WORD_SIZE * 2}")

        # mask out and pack values
        tran_val_ld_ret.writeAction(f"mov_imm2reg {REG_NUM_VAL_WORDS} {0}")  # WARNING: change definition to num masked words
        for i in range(1, 9):
            tran_val_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-pack_next_{i}'}: blei {REG_TMP2} {0} {f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-pack_next_9'}")  # branch to done packing
            tran_val_ld_ret.writeAction(f"subi {REG_TMP2} {REG_TMP2} {1}")
            tran_val_ld_ret.writeAction(f"andi {REG_MASK} {REG_TMP3} {0b1 << (i - 1)}")
            tran_val_ld_ret.writeAction(f"beqi {REG_TMP3} {0} {f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-pack_next_{i + 1}'}")
            tran_val_ld_ret.writeAction(f"move {f'X{i + 8 - 1}'} {0}({REG_TMP1}) 1 8")
            tran_val_ld_ret.writeAction(f"addi {REG_NUM_VAL_WORDS} {REG_NUM_VAL_WORDS} {1}")
        tran_val_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-pack_next_9'}: addi {REG_TMP1} {REG_TMP1} {0}")  # FIXME: dummy

        # return appropriate number of values
        for i in range(0, 7):
            tran_val_ld_ret.writeAction(f"beqi {REG_NUM_VAL_WORDS} {i} {f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-ret_val_{i}'}")
        tran_val_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-ret_val_6'}")  # for value words > 6, load the first 6 words
        for i in range(0, 7):
            tran_val_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-ret_val_{i}'}: addi {REG_TMP1} {REG_TMP1} {0}")  # FIXME: dummy
            sht_macros.return_wlm(tran_val_ld_ret, REG_CONT, REG_BUCKET_BUF_LM_ADDR, i + 2)
            tran_val_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-ret_val_done'}")

        tran_val_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-ret_val_done'}: bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-wait_after_ld_val'}")
        tran_val_ld_ret.writeAction("yield_terminate")
        tran_val_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-wait_after_ld_val'}: yield")

    @classmethod
    def get_with_mask(cls, tran: Transition, ret_label: int, tmp_reg0: str, tmp_reg1: str, desc_lm_offset_reg: str, key_reg: str, mask_reg: str, dst_nwid_reg: str = 'X0'):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_get_with_mask.getLabel(), ret_tran_label=ret_label, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=desc_lm_offset_reg, arg_reg1=key_reg, arg_reg2=mask_reg)

    @classmethod
    def get_with_mask_wcont(cls, tran: Transition, cont_reg: str, tmp_reg: str, desc_lm_offset_reg: str, key_reg: str, mask_reg: str, dst_nwid_reg: str = 'X0'):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_get_with_mask.getLabel(), cont_reg=cont_reg, tmp_reg=tmp_reg, arg_reg0=desc_lm_offset_reg, arg_reg1=key_reg, arg_reg2=mask_reg)

    @classmethod
    def _update_with_mask(cls, state: State):
        """
        Extended to support mask

        X8  - LANE_DESC_LM_OFFSET(0:31) | BUCKET_DESC_LM_OFFSET(32:63)
        X9  - KEY
        X10 - MASK
        X11 ~ X15 - Elem e
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._update_with_mask.__name__

        OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET = "X8"
        OB_KEY = "X9"
        OB_MASK = "X10"
        OB_VAL = "X11"
        MAX_VAL_NUM_WORDS = 5

        REG_TMP1 = "X17"
        REG_TMP2 = "X18"
        REG_TMP3 = "X19"

        REG_LD_CONCURRENCY = "X20"
        REG_KEY_WR_ADDR = "X21"
        REG_VAL_WR_ADDR = "X22"
        REG_ST_CONCURRENCY = "X23"
        REG_NUM_VAL_OP = "X24"  # number of value operations
        REG_LAST_LOAD_EFFECTIVE_WORDS = "X25"
        REG_LAST_LOAD_ADDR = "X26"

        REG_LANE_DESC_LM_ADDR = "X27"
        REG_BUCKET_DESC_LM_ADDR = "X28"
        REG_BUCKET_BUF_LM_ADDR = "X29"
        REG_KEY = "X30"
        REG_MASK = "X16"

        REG_CONT = "X31"

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_update_with_mask
        if tran is None:
            return
        cls.tran_label_update_with_mask = tran.getLabel()
        tran_key_ld_ret = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-key_ld_ret")
        tran_val_ld_ret = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-val_ld_ret")
        tran_key_st_ret = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-key_st_ret")

        """==================== TRAN - function entry ===================="""
        """----- Prep -----"""
        # calc desc lm addr
        tran.writeAction(f"rshift {OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET} {REG_BUCKET_DESC_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_BUCKET_DESC_LM_ADDR} {'X7'} {REG_BUCKET_DESC_LM_ADDR}")

        # get lock
        cls.lock.write_begin_var(tran, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: lock admitted, TID = %d' {'X0'} {'TID'}")
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: REG_BUCKET_DESC_LM_ADDR = 0x%x' {'X0'} {REG_BUCKET_DESC_LM_ADDR}")

        # calc desc lm addr
        tran.writeAction(f"lshift {OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET} {REG_LANE_DESC_LM_ADDR} {32}")
        tran.writeAction(f"rshift {REG_LANE_DESC_LM_ADDR} {REG_LANE_DESC_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_LANE_DESC_LM_ADDR} {'X7'} {REG_LANE_DESC_LM_ADDR}")

        # copy ob regs
        tran.writeAction(f"addi {OB_KEY} {REG_KEY} {0}")
        tran.writeAction(f"addi {OB_MASK} {REG_MASK} {0}")
        # save cont
        tran.writeAction(f"addi {'X1'} {REG_CONT} {0}")

        # load desc
        tran.writeAction(f"addi {REG_BUCKET_DESC_LM_ADDR} {REG_BUCKET_BUF_LM_ADDR} {cls.BUCKET_DESC_STURCT_OFF_LM_BUF}")

        # # extract num_elem_op
        # # since there is an offset of 2 in the encoding, the desc & key counts are skipped
        # tran.writeAction(f"rshift_and_imm {'X2'} {REG_NUM_VAL_OP} {20} {0b111}")
        # tran.writeAction(f"subi {REG_NUM_VAL_OP} {REG_NUM_VAL_OP} {1}")
        # if cls.DEBUG:
        #     tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: number of val operands = %d' {'X0'} {REG_NUM_VAL_OP}")
        # # copy val to buffer

        # unpack value words in buffer with mask
        tran.writeAction(f"addi {REG_BUCKET_BUF_LM_ADDR} {REG_TMP1} {0}")  # REG_TMP1 => current LM buffer address
        tran.writeAction(f"addi {REG_MASK} {REG_TMP2} {0}")  # REG_TMP2 => current mask
        for i in range(6):  # 5 value operands
            #  for each operand, find the next '1' position
            tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-next_bit_{i}'}: andi {REG_TMP2} {REG_TMP3} {1}")
            tran.writeAction(f"rshift {REG_TMP2} {REG_TMP2} {1}")
            tran.writeAction(f"beqi {REG_TMP3} {1} {f'{CLS_NAME}-{FN_NAME}-TR-LB-bit_set_{i}'}")
            tran.writeAction(f"addi {REG_TMP1} {REG_TMP1} {cls.WORD_SIZE}")  # no gurantee of the masked out value
            tran.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-LB-next_bit_{i}'}")
            tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-bit_set_{i}'}: move {f'X{i + 11}'} 0({REG_TMP1}) 1 8")
            tran.writeAction(f"beqi {REG_TMP2} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-unpack_done'}")

        # TODO: optimization: find the last 1 position, and do not need to read/write beyond that
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-unpack_done'}: move {cls.LANE_DESC_STURCT_OFF_VAL_NUM_WORDS}({REG_LANE_DESC_LM_ADDR}) {REG_NUM_VAL_OP} 0 4")  # WARNING: change REG_NUM_VAL_OP definition to number of words to be read/written
        tran.writeAction(f"blei {REG_NUM_VAL_OP} {8} {f'{CLS_NAME}-{FN_NAME}-TR-LB-skip_cap_update_words'}")
        tran.writeAction(f"mov_imm2reg {REG_NUM_VAL_OP} {8}")  # cap the max update number of words to 8

        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-skip_cap_update_words'}: move {cls.BUCKET_DESC_STURCT_OFF_ENTRY_COUNT}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP1} 0 4")  # tmp1 => entry_count

        """----- Empty Bucket -----"""
        # ----- if entry count is zero, write directly -----
        tran.writeAction(f"bgti {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-setup_send_ld'}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: empty bucket, writing without search' {'X0'}")
        # update entry count
        tran.writeAction(f"addi {REG_TMP1} {REG_TMP1} {1}")
        tran.writeAction(f"move {REG_TMP1} {cls.BUCKET_DESC_STURCT_OFF_ENTRY_COUNT}({REG_BUCKET_DESC_LM_ADDR}) 0 4")

        tran.writeAction(f"mov_imm2reg {REG_LD_CONCURRENCY} {0}")
        tran.writeAction(f"mov_imm2reg {REG_ST_CONCURRENCY} {2}")
        tran.writeAction(f"move {cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_KEY_WR_ADDR} 0 8")
        tran.writeAction(f"move {cls.BUCKET_DESC_STURCT_OFF_DRAM_VAL_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_VAL_WR_ADDR} 0 8")
        # tran.writeAction(f"sendr_dmlm_wret {REG_KEY_WR_ADDR} {tran_key_st_ret.getLabel()} {REG_KEY} {REG_KEY}")
        # tran.writeAction(f"sendr_dmlm_wret {REG_KEY_WR_ADDR} {tran_key_st_ret.getLabel()} {REG_KEY}")  # writing only one word
        sht_macros.dram_write_reg_ret(tran=tran, addr_reg=REG_KEY_WR_ADDR, ret_tran_label=tran_key_st_ret.getLabel(), tmp_reg=REG_TMP2, arg_reg0=REG_KEY)
        # calling with the proper number of operands
        for i in range(1, 8 + 1):
            tran.writeAction(f"beqi {REG_NUM_VAL_OP} {i} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_val_{i}'}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: shouldn't reach here!' {'X0'}")
        for i in range(1, 8 + 1):
            # tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_val_{i}'}: send_dmlm_wret {REG_VAL_WR_ADDR} {tran_key_st_ret.getLabel()} {REG_BUCKET_BUF_LM_ADDR} {i}")
            sht_macros.dram_write_lm_ret(tran=tran, addr_reg=REG_VAL_WR_ADDR, ret_tran_label=tran_key_st_ret.getLabel(), tmp_reg=REG_TMP2, arg_lm_addr_reg=REG_BUCKET_BUF_LM_ADDR, arg_lm_words=i, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-LB-send_val_{i}')
            if cls.DEBUG:
                tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: writing {i} words value' {'X0'}")
            tran.writeAction("yield")

        """----- Filled Bucket -----"""
        # ----- already have entires, send load entries -----
        # init
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-setup_send_ld'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_LAST_LOAD_ADDR} 0 8")  # tmp3 => key load start address
        tran.writeAction(f"mov_imm2reg {REG_LD_CONCURRENCY} {0}")
        tran.writeAction(f"mov_imm2reg {REG_ST_CONCURRENCY} {-1}")

        tran.writeAction(f"blei {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_done'}")  # tmp1 => entry_count
        # tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_ld'}: send_dmlm_ld_wret {REG_LAST_LOAD_ADDR} {tran_key_ld_ret.getLabel()} {8}")
        sht_macros.dram_read_ret(tran=tran, addr_reg=REG_LAST_LOAD_ADDR, ret_tran_label=tran_key_ld_ret.getLabel(), tmp_reg=REG_TMP2, arg_lm_words=8, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-LB-send_ld')
        tran.writeAction(f"addi {REG_LD_CONCURRENCY} {REG_LD_CONCURRENCY} {1}")  # concurrency++
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: loading, DRAM addr = 0x%x' {'X0'} {REG_LAST_LOAD_ADDR}")
        # check if number of valid entries in the send is greater than 8
        tran.writeAction(f"bgti {REG_TMP1} {64 // cls.KEY_SIZE} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}")
        # last send, retain last send addr & valid size
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: all loads sent' {'X0'}")
        tran.writeAction(f"mov_reg2reg {REG_TMP1} {REG_LAST_LOAD_EFFECTIVE_WORDS}")  # record last load effective size
        tran.writeAction("yield")
        # full 8 word send
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}: subi {REG_TMP1} {REG_TMP1} {64 // cls.KEY_SIZE}")
        tran.writeAction(f"addi {REG_LAST_LOAD_ADDR} {REG_LAST_LOAD_ADDR} {64}")
        tran.writeAction(f"bgti {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_ld'}")
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_done'}: yield")

        """==================== TRAN - load key return ===================="""
        OB_LD_RET_ADDR = "X3"

        """----- synchronization check -----"""
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: load from 0x%x returns, mlp = %d' {'X0'} {OB_LD_RET_ADDR} {REG_LD_CONCURRENCY}")
        tran_key_ld_ret.writeAction(f"subi {REG_LD_CONCURRENCY} {REG_LD_CONCURRENCY} {1}")
        # possible situations:
        # ld concurrency >= 0
        # st concurrency == -1, no store yet, match
        # st concurrency == 0, store done, if ld concurrency == 0, terminate
        # st concurrency == 1, store not done, yield
        # st concurrency == 2 (impossible, as it is only set when the last load is processed)
        tran_key_ld_ret.writeAction(f"beqi {REG_ST_CONCURRENCY} {-1} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}")
        tran_key_ld_ret.writeAction(f"beqi {REG_ST_CONCURRENCY} {1} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}")
        tran_key_ld_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: last in-flight load & store finished, terminating... TID = %d' {'X0'} {'TID'}")
        # unlocked already, no need to unlock
        # return format: (key, mask)
        sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, REG_KEY, REG_VAL_WR_ADDR)
        tran_key_ld_ret.writeAction("yield_terminate")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}: yield")

        """----- Check returned keys -----"""
        # check if return is matched with (last) send address
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}: bne {OB_LD_RET_ADDR} {REG_LAST_LOAD_ADDR} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{7 * cls.KEY_SIZE}'}")  # tmp3 => last send addr
        # if it is the last send, branch to check only the valid entries
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: tail send load returns, num entries = %d' {'X0'} {REG_LAST_LOAD_EFFECTIVE_WORDS}")  # tmp2 => last send num valid entries
        for i in range(8, 0, -1):
            tran_key_ld_ret.writeAction(f"beqi {REG_LAST_LOAD_EFFECTIVE_WORDS} {i} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}'}")
        # match return data
        for i in range(8, 0, -1):
            tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}'}: beq {f'X{i + 8 - 1}'} {REG_KEY} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}_match'}")

        """-> not matched (fall through)"""
        # if not the last send came back (check concurrency counter), yield wait
        # if mlp is 0, finished, need to write entry & terminate
        tran_key_ld_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait_ld'}")
        # from here, all in-flight loads are done & no match found
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: no matched entry found' {'X0'}")
        # check if there is space at the end of the allocation area
        tran_key_ld_ret.writeAction(f"move {cls.LANE_DESC_STURCT_OFF_ENTRIES_PER_BUCKET}({REG_LANE_DESC_LM_ADDR}) {REG_TMP1} 0 4")  # REG_TMP1 => num_alloc_entries
        tran_key_ld_ret.writeAction(f"move {cls.BUCKET_DESC_STURCT_OFF_ENTRY_COUNT}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP2} 0 4")  # REG_TMP2 => entry count
        tran_key_ld_ret.writeAction(f"blt {REG_TMP2} {REG_TMP1} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-new_entry'}")
        # -> out of space!
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: bucket full, add FAILED!' {'X0'}")
        # return format: (key, mask)
        tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_TMP1} {0}")  # indicate failue with addr == 0
        sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, REG_KEY, REG_TMP1)
        # sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, 'X0', REG_TMP3)  # for debug
        cls.lock.write_end(tran_key_ld_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        tran_key_ld_ret.writeAction("yield_terminate")  # only if running out of space!
        # -> new entry
        # calculate the address of the key
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-new_entry'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_KEY_WR_ADDR} 0 8")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: storing in a new entry' {'X0'}")
        tran_key_ld_ret.writeAction(f"lshift {REG_TMP2} {REG_TMP1} {int(math.log2(cls.KEY_SIZE))}")
        tran_key_ld_ret.writeAction(f"add {REG_KEY_WR_ADDR} {REG_TMP1} {REG_KEY_WR_ADDR}")
        # store key
        # tran_key_ld_ret.writeAction(f"sendr_dmlm_wret {REG_KEY_WR_ADDR} {tran_key_st_ret.getLabel()} {REG_KEY}")  # writing only one word
        sht_macros.dram_write_reg_ret(tran=tran_key_ld_ret, addr_reg=REG_KEY_WR_ADDR, ret_tran_label=tran_key_st_ret.getLabel(), tmp_reg=REG_TMP3, arg_reg0=REG_KEY)
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: sending key write to addr = 0x%x' {'X0'} {REG_VAL_WR_ADDR}")
        # calculate the address of the value
        tran_key_ld_ret.writeAction(f"move {cls.BUCKET_DESC_STURCT_OFF_DRAM_VAL_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_VAL_WR_ADDR} 0 8")
        tran_key_ld_ret.writeAction(f"move {cls.LANE_DESC_STURCT_OFF_VAL_NUM_WORDS}({REG_LANE_DESC_LM_ADDR}) {REG_TMP1} 0 4")
        tran_key_ld_ret.writeAction(f"mul {REG_TMP2} {REG_TMP1} {REG_TMP1}")
        tran_key_ld_ret.writeAction(f"lshift {REG_TMP1} {REG_TMP1} {int(math.log2(cls.WORD_SIZE))}")
        tran_key_ld_ret.writeAction(f"add {REG_VAL_WR_ADDR} {REG_TMP1} {REG_VAL_WR_ADDR}")
        # store value
        # calling with the proper number of operands
        for i in range(1, 8 + 1):
            tran_key_ld_ret.writeAction(f"beqi {REG_NUM_VAL_OP} {i} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-nomatch_send_val_{i}'}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: shouldn't reach here!' {'X0'}")
        for i in range(1, 8 + 1):
            # tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-nomatch_send_val_{i}'}: send_dmlm_wret {REG_VAL_WR_ADDR} {tran_key_st_ret.getLabel()} {REG_BUCKET_BUF_LM_ADDR} {i}")
            sht_macros.dram_write_lm_ret(tran=tran_key_ld_ret, addr_reg=REG_VAL_WR_ADDR, ret_tran_label=tran_key_st_ret.getLabel(), tmp_reg=REG_TMP3, arg_lm_addr_reg=REG_BUCKET_BUF_LM_ADDR, arg_lm_words=i, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-nomatch_send_val_{i}')
            if cls.DEBUG:
                tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: writing {i} words value' {'X0'}")
            tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-nomatch_send_val_done'}")
        # count up the entries
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-nomatch_send_val_done'}: addi {REG_TMP2} {REG_TMP2} {1}")
        tran_key_ld_ret.writeAction(f"move {REG_TMP2} {cls.BUCKET_DESC_STURCT_OFF_ENTRY_COUNT}({REG_BUCKET_DESC_LM_ADDR}) 0 4")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: sending value write to addr = 0x%x' {'X0'} {REG_VAL_WR_ADDR}")
        tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_ST_CONCURRENCY} {2}")  # mark value written & all loads done
        # -> wait for in-flight load to come back
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait_ld'}: yield")

        """-> matched"""
        for i in range(0, 8):
            # calculate the entry index from key address
            tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{i * cls.KEY_SIZE}_match'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP1} 0 8")
            if cls.DEBUG:
                tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: matched at word offset {i}' {'X0'}")
            tran_key_ld_ret.writeAction(f"sub {OB_LD_RET_ADDR} {REG_TMP1} {REG_TMP1}")
            tran_key_ld_ret.writeAction(f"rshift {REG_TMP1} {REG_TMP1} {int(math.log2(cls.KEY_SIZE))}")
            tran_key_ld_ret.writeAction(f"addi {REG_TMP1} {REG_TMP1} {i}")  # REG_TMP1 => entry index
            tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_val_ld'}")

        """----- Send load value -----"""
        # calculate value address
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_val_ld'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_VAL_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_VAL_WR_ADDR} 0 8")
        tran_key_ld_ret.writeAction(f"move {cls.LANE_DESC_STURCT_OFF_VAL_NUM_WORDS}({REG_LANE_DESC_LM_ADDR}) {REG_TMP2} 0 4")
        tran_key_ld_ret.writeAction(f"mul {REG_TMP2} {REG_TMP1} {REG_TMP1}")
        tran_key_ld_ret.writeAction(f"lshift {REG_TMP1} {REG_TMP1} {int(math.log2(cls.WORD_SIZE))}")
        tran_key_ld_ret.writeAction(f"add {REG_VAL_WR_ADDR} {REG_TMP1} {REG_VAL_WR_ADDR}")

        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: sending load to addr = 0x%x' {'X0'} {REG_VAL_WR_ADDR}")

        # calling with the proper number of operands
        for i in range(1, 9):
            tran_key_ld_ret.writeAction(f"beqi {REG_NUM_VAL_OP} {i} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_{i}'}")
        tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_8'}")  # for value words > 8, load the first 8 words
        for i in range(1, 9):
            # tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_{i}'}: send_dmlm_ld_wret {REG_VAL_WR_ADDR} {tran_val_ld_ret.getLabel()} {i}")
            sht_macros.dram_read_ret(tran=tran_key_ld_ret, addr_reg=REG_VAL_WR_ADDR, ret_tran_label=tran_val_ld_ret.getLabel(), tmp_reg=REG_TMP3, arg_lm_words=i, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_{i}')
            if cls.DEBUG:
                tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: loading {i} words value' {'X0'}")
            tran_key_ld_ret.writeAction("yield")

        """==================== TRAN - load val return ===================="""
        """----- fill in the masked out words -----"""
        tran_val_ld_ret.writeAction(f"addi {REG_BUCKET_BUF_LM_ADDR} {REG_TMP1} {0}")
        tran_val_ld_ret.writeAction(f"addi {REG_NUM_VAL_OP} {REG_TMP2} {0}")
        for i in range(8):
            tran_val_ld_ret.writeAction(f"blei {REG_TMP2} {0} {f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-unpack_done'}")  # branch to done packing
            tran_val_ld_ret.writeAction(f"subi {REG_TMP2} {REG_TMP2} {1}")
            tran_val_ld_ret.writeAction(f"andi {REG_MASK} {REG_TMP3} {0b1 << i}")
            tran_val_ld_ret.writeAction(f"bnei {REG_TMP3} {0} {f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-unpack_skip_{i}'}")
            tran_val_ld_ret.writeAction(f"move {f'X{i + 8}'} 0({REG_TMP1}) 0 8")
            tran_val_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-unpack_skip_{i}'}: addi {REG_TMP1} {REG_TMP1} {cls.WORD_SIZE}")
        tran_val_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-unpack_done'}: addi {REG_TMP1} {REG_TMP1} {0}")  # FIXME: dummy

        """----- Send store value -----"""
        if cls.DEBUG:
            tran_val_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: sending write to addr = 0x%x' {'X0'} {REG_VAL_WR_ADDR}")
        # calling with the proper number of operands
        for i in range(1, 9):
            tran_val_ld_ret.writeAction(f"beqi {REG_NUM_VAL_OP} {i} {f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-match_send_val_{i}'}")
        if cls.DEBUG:
            tran_val_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: shouldn't reach here!' {'X0'}")
        for i in range(1, 9):
            # tran_val_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-match_send_val_{i}'}: send_dmlm_wret {REG_VAL_WR_ADDR} {tran_key_st_ret.getLabel()} {REG_BUCKET_BUF_LM_ADDR} {i}")
            sht_macros.dram_write_lm_ret(tran=tran_val_ld_ret, addr_reg=REG_VAL_WR_ADDR, ret_tran_label=tran_key_st_ret.getLabel(), tmp_reg=REG_TMP1, arg_lm_addr_reg=REG_BUCKET_BUF_LM_ADDR, arg_lm_words=i, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-match_send_val_{i}')
            if cls.DEBUG:
                tran_val_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: writing {i} words value' {'X0'}")
            tran_val_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-match_send_val_done'}")
        tran_val_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-match_send_val_done'}: mov_imm2reg {REG_ST_CONCURRENCY} {1}")  # mark value written
        tran_val_ld_ret.writeAction("yield")

        """==================== TRAN - store key val return ===================="""
        tran_key_st_ret.writeAction(f"subi {REG_ST_CONCURRENCY} {REG_ST_CONCURRENCY} {1}")
        tran_key_st_ret.writeAction(f"bgti {REG_ST_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_st_ret-LB-wait'}")
        tran_key_st_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_st_ret-LB-ld_wait'}")
        if cls.DEBUG:
            tran_key_st_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: write to 0x%x returns & no load waiting, terminating... TID = %d' {'X0'} {'X8'} {'TID'}")
        cls.lock.write_end(tran_key_st_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        # return format: (key, mask)
        sht_macros.return_wreg(tran_key_st_ret, REG_CONT, REG_KEY, REG_MASK)
        # sht_macros.return_wreg(tran_key_st_ret, REG_CONT, 'X0', REG_VAL_WR_ADDR)  # debug
        tran_key_st_ret.writeAction("yield_terminate")
        tran_key_st_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_st_ret-LB-ld_wait'}: addi {REG_TMP1} {REG_TMP1} {0}")  # FIXME: dummy
        cls.lock.write_end(tran_key_st_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        if cls.DEBUG:
            tran_key_st_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: write to 0x%x returns & all stores done, waiting loads return...' {'X0'} {'X8'}")
        tran_key_st_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_st_ret-LB-wait'}: yield")

    @classmethod
    def update_with_mask(cls, tran: Transition, ret_label: int, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, arg_lm_words: int, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_update_with_mask.getLabel(), ret_tran_label=ret_label, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=arg_lm_words)

    @classmethod
    def update_with_mask_wcont(cls, tran: Transition, cont_reg: str, tmp_reg0: str, arg_lm_addr_reg: str, arg_lm_words: int, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_update_with_mask.getLabel(), cont_reg=cont_reg, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=arg_lm_words)

    # TODO: implement iterate
