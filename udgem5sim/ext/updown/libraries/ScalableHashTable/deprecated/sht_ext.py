from EFA_v2 import EFA, State, Transition
import sht_macros
from sht_lane_ext import SHTLane
import math


class SHTExt:
    """
    struct SHT_DESC {
        WORD NUM_ALLOC_LANES(0:31) | START_NWID(32:63);
        WORD LANE_DESC_LM_OFFSET(0:31) | BUCKETS_PER_LANE(32:63);
        WORD ENTRIES_PER_BUCKET(0:31) | VAL_NUM_WORDS(32:63);
        WORD DRAM_ALLOC_ADDR;
    }
    """

    LANES_PER_UD = 64
    LANES_MASK = LANES_PER_UD - 1

    KEY_SIZE = 8
    WORD_SIZE = 8

    SHT_DESC_SIZE = 4 * WORD_SIZE
    # LITTLE ENDIAN
    # SHT_DESC_STURCT_OFF_NUM_ALLOC_LANES = 0  # 4 bytes
    # SHT_DESC_STURCT_OFF_START_NWID = SHT_DESC_STURCT_OFF_NUM_ALLOC_LANES + 4  # 4 bytes
    # SHT_DESC_STURCT_OFF_LANE_DESC_LM_OFFSET = SHT_DESC_STURCT_OFF_START_NWID + 4  # 4 bytes
    # SHT_DESC_STURCT_OFF_BUCKETS_PER_LANE = SHT_DESC_STURCT_OFF_LANE_DESC_LM_OFFSET + 4  # 4 bytes
    # SHT_DESC_STURCT_OFF_ENTRIES_PER_BUCKET = SHT_DESC_STURCT_OFF_BUCKETS_PER_LANE + 4  # 4 bytes
    # SHT_DESC_STURCT_OFF_VAL_NUM_WORDS = SHT_DESC_STURCT_OFF_ENTRIES_PER_BUCKET + 4  # 4 bytes
    # SHT_DESC_STURCT_OFF_DRAM_ALLOC_ADDR = SHT_DESC_STURCT_OFF_VAL_NUM_WORDS + 4  # 8 bytes
    # BIG ENDIAN
    SHT_DESC_STURCT_OFF_START_NWID = 0  # 4 bytes
    SHT_DESC_STURCT_OFF_NUM_ALLOC_LANES = SHT_DESC_STURCT_OFF_START_NWID + 4  # 4 bytes
    SHT_DESC_STURCT_OFF_BUCKETS_PER_LANE = SHT_DESC_STURCT_OFF_NUM_ALLOC_LANES + 4  # 4 bytes
    SHT_DESC_STURCT_OFF_LANE_DESC_LM_OFFSET = SHT_DESC_STURCT_OFF_BUCKETS_PER_LANE + 4  # 4 bytes
    SHT_DESC_STURCT_OFF_VAL_NUM_WORDS = SHT_DESC_STURCT_OFF_LANE_DESC_LM_OFFSET + 4  # 4 bytes
    SHT_DESC_STURCT_OFF_ENTRIES_PER_BUCKET = SHT_DESC_STURCT_OFF_VAL_NUM_WORDS + 4  # 4 bytes
    SHT_DESC_STURCT_OFF_DRAM_ALLOC_ADDR = SHT_DESC_STURCT_OFF_ENTRIES_PER_BUCKET + 4  # 8 bytes

    @classmethod
    def setup(cls, state: State, debug=False) -> None:
        cls.DEBUG = debug

        CLS_NAME = cls.__name__
        cls.tran_initialize = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-initialize-TR")
        cls.tran_finalize = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-finalize-TR")
        cls.tran_update = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-update-TR")
        cls.tran_update_with_mask = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-update_with_mask-TR")
        cls.tran_get = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-get-TR")
        cls.tran_get_with_mask = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-get_with_mask-TR")
        # cls.tran_get_with_offset = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-get_with_offset-TR")
        cls.tran_delete = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-delete-TR")
        cls.tran_ext_graph_append = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-ext_graph_append-TR")
        cls.tran_ext_graph_append_migrate = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-ext_graph_append_migrate-TR")
        cls.tran_ext_graph_get_with_offset = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-ext_graph_get_with_offset-TR")
        cls.tran_ext_graph_get_word_cnt = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-ext_graph_get_word_cnt-TR")

        # TODO: code injection
        SHTLane.setup(state, debug=debug)
        cls._initialize(state)
        cls._finalize(state)
        cls._update(state)
        cls._get(state)
        # cls._delete(state)
        cls._update_with_mask(state)
        cls._get_with_mask(state)
        cls._ext_graph_append_migrate(state)
        cls._ext_graph_append(state)
        cls._ext_graph_get_with_offset(state)
        cls._ext_graph_get_word_cnt(state)

    @classmethod
    def _macro_hash_word(cls, tran: Transition, in_sht_desc_lm_addr_reg: str, in_key_reg: str, out_lane_desc_lm_off_reg: str, out_bucket_desc_lm_off_reg: str, out_dst_nwid_reg: str, fn_name: str) -> None:
        CLS_NAME = cls.__name__
        FN_NAME = fn_name

        REG_KEY = in_key_reg
        REG_SHT_DESC_LM_ADDR = in_sht_desc_lm_addr_reg
        REG_TMP0 = out_lane_desc_lm_off_reg
        REG_TMP1 = out_bucket_desc_lm_off_reg
        REG_TMP2 = out_dst_nwid_reg

        # hash the destination lane id
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: key = %d' {'X0'} {REG_KEY}")
        tran.writeAction(f"mov_imm2reg {REG_TMP0} {0}")  # REG_TMP0 -> seed
        tran.writeAction(f"hash {REG_KEY} {REG_TMP0}")  # REG_TMP0 -> hash
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: hash = %d' {'X0'} {REG_TMP0}")

        # calc dest lane
        tran.writeAction(f"move {cls.SHT_DESC_STURCT_OFF_NUM_ALLOC_LANES}({REG_SHT_DESC_LM_ADDR}) {REG_TMP1} 0 4")  # REG_TMP1 -> num lane
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: num lane = %d' {'X0'} {REG_TMP1}")
        tran.writeAction(f"subi {REG_TMP1} {REG_TMP1} {1}")  # REG_TMP1 -> lane mask (WARNING: assume num lane is power of 2)
        tran.writeAction(f"andr {REG_TMP0} {REG_TMP1} {REG_TMP1}")  # REG_TMP1 -> nwid offset
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: nwid offset = %d' {'X0'} {REG_TMP1}")
        tran.writeAction(f"move {cls.SHT_DESC_STURCT_OFF_START_NWID}({REG_SHT_DESC_LM_ADDR}) {REG_TMP2} 0 4")  # REG_TMP2 -> start nwid
        tran.writeAction(f"add {REG_TMP2} {REG_TMP1} {REG_TMP2}")  # REG_TMP2 -> [dest nwid]
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: dst nwid = %d' {'X0'} {REG_TMP2}")

        # calculate the address of the bucket descriptor on the destination lane
        tran.writeAction(f"move {cls.SHT_DESC_STURCT_OFF_BUCKETS_PER_LANE}({REG_SHT_DESC_LM_ADDR}) {REG_TMP1} 0 4")  # REG_TMP1 -> number of bucket per lane
        tran.writeAction(f"subi {REG_TMP1} {REG_TMP1} {1}")  # REG_TMP1 -> lane bucket off mask
        tran.writeAction(f"rshift {REG_TMP0} {REG_TMP0} {32}")  # low 32b hash for nwid, upper 32b for bucket
        tran.writeAction(f"andr {REG_TMP0} {REG_TMP1} {REG_TMP1}")  # REG_TMP1 -> lane bucket offset
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: lane bucket off = %d' {'X0'} {REG_TMP1}")
        tran.writeAction(f"muli {REG_TMP1} {REG_TMP1} {SHTLane.BUCKET_DESC_SIZE}")
        tran.writeAction(f"move {cls.SHT_DESC_STURCT_OFF_LANE_DESC_LM_OFFSET}({REG_SHT_DESC_LM_ADDR}) {REG_TMP0} 0 4")  # REG_TMP0 -> [lane desc lm offset base]
        tran.writeAction(f"add {REG_TMP0} {REG_TMP1} {REG_TMP1}")  # REG_TMP1 -> bucket desc lm addr
        tran.writeAction(f"addi {REG_TMP1} {REG_TMP1} {SHTLane.LANE_DESC_SIZE + SHTLane.EXT_LANE_DESC_SIZE}")  # REG_TMP1 -> [bucket desc lm addr]
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: LANE_DESC_LM_OFFSET = 0x%x, BUCKET_DESC_LM_OFFSET = 0x%x' {'X0'} {REG_TMP0} {REG_TMP1}")

    @classmethod
    def _initialize(cls, state: State):
        """
        X8  - SHT_DESC_LM_OFFSET(0:31) | TMP_BUF_LM_OFFSET(32:63)
        X9  - NUM_ALLOC_LANES(0:31) | START_NWID(32:63);
        X10 - LANE_DESC_LM_OFFSET(0:31) | BUCKETS_PER_LANE(32:63);
        X11 - ENTRIES_PER_BUCKET(0:31) | VAL_NUM_WORDS(32:63);
        X12 - DRAM_ALLOC_ADDR;

        // extension SHT
        X13 - NUM_ALLOC_LANES(0:31) | START_NWID(32:63);
        X14 - LANE_DESC_LM_OFFSET(0:31) | BUCKETS_PER_LANE(32:63);
        X15 - ENTRIES_PER_BUCKET(0:31) | VAL_NUM_WORDS(32:63);
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._initialize.__name__

        OB_SHT_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET = "X8"
        OB_NUM_ALLOC_LANES__START_NWID = "X9"
        OB_LANE_DESC_LM_OFFSET__BUCKETS_PER_LANE = "X10"
        OB_ENTRIES_PER_BUCKET__VAL_NUM_WORDS = "X11"
        OB_DRAM_ALLOC_ADDR = "X12"

        OB_EXT__NUM_ALLOC_LANES__START_NWID = "X13"
        OB_EXT__LANE_DESC_LM_OFFSET__BUCKETS_PER_LANE = "X14"
        OB_EXT__ENTRIES_PER_BUCKET__VAL_NUM_WORDS = "X15"

        REG_SHT_DESC_LM_ADDR = "X16"
        REG_TMP_BUF_LM_ADDR = "X17"
        REG_LANE_DRAM_SIZE = "X18"
        REG_CUR_DRAM_ADDR = "X19"
        REG_CUR_NWID = "X20"

        REG_TMP0 = "X21"
        REG_TMP1 = "X22"
        REG_TMP2 = "X23"
        REG_TMP3 = "X24"

        REG_CONT = "X31"

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_initialize
        if tran is None:
            return
        tran_lane_init_ret = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-lane_init_ret")
        cls.tran_label_initialize = tran.getLabel()

        """==================== TRAN - entry ===================="""
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: entry' {'X0'}")

        # Save continuation
        tran.writeAction(f"addi {'X1'} {REG_CONT} {0}")

        # calculate lm addr
        tran.writeAction(f"lshift {OB_SHT_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET} {REG_SHT_DESC_LM_ADDR} {32}")
        tran.writeAction(f"rshift {REG_SHT_DESC_LM_ADDR} {REG_SHT_DESC_LM_ADDR} {32}")
        tran.writeAction(f"rshift {OB_SHT_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET} {REG_TMP_BUF_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_SHT_DESC_LM_ADDR} {'X7'} {REG_SHT_DESC_LM_ADDR}")
        tran.writeAction(f"add {REG_TMP_BUF_LM_ADDR} {'X7'} {REG_TMP_BUF_LM_ADDR}")
        # copy SHT descriptor
        tran.writeAction(f"mov_imm2reg {REG_TMP0} {cls.SHT_DESC_SIZE // cls.WORD_SIZE}")
        tran.writeAction(f"bcopy_ops {OB_NUM_ALLOC_LANES__START_NWID} {REG_SHT_DESC_LM_ADDR} {REG_TMP0}")
        # copy send buffer
        tran.writeAction(f"mov_imm2reg {REG_TMP0} {cls.SHT_DESC_SIZE // cls.WORD_SIZE + 3}")
        tran.writeAction(f"bcopy_ops {OB_NUM_ALLOC_LANES__START_NWID} {REG_TMP_BUF_LM_ADDR} {REG_TMP0}")
        # calculate lane dram alloc size
        tran.writeAction(f"move {cls.SHT_DESC_STURCT_OFF_NUM_ALLOC_LANES}({REG_SHT_DESC_LM_ADDR}) {REG_LANE_DRAM_SIZE} 0 4")
        tran.writeAction(f"move {cls.SHT_DESC_STURCT_OFF_BUCKETS_PER_LANE}({REG_SHT_DESC_LM_ADDR}) {REG_TMP0} 0 4")
        tran.writeAction(f"mul {REG_LANE_DRAM_SIZE} {REG_TMP0} {REG_LANE_DRAM_SIZE}")
        tran.writeAction(f"move {cls.SHT_DESC_STURCT_OFF_ENTRIES_PER_BUCKET}({REG_SHT_DESC_LM_ADDR}) {REG_TMP0} 0 4")
        tran.writeAction(f"mul {REG_LANE_DRAM_SIZE} {REG_TMP0} {REG_LANE_DRAM_SIZE}")
        tran.writeAction(f"move {cls.SHT_DESC_STURCT_OFF_VAL_NUM_WORDS}({REG_SHT_DESC_LM_ADDR}) {REG_TMP0} 0 4")
        tran.writeAction(f"lshift_add_imm {REG_TMP0} {REG_TMP0} {int(math.log2(cls.WORD_SIZE))} {cls.WORD_SIZE}")
        tran.writeAction(f"mul {REG_LANE_DRAM_SIZE} {REG_TMP0} {REG_LANE_DRAM_SIZE}")
        # counter init
        tran.writeAction(f"addi {OB_DRAM_ALLOC_ADDR} {REG_CUR_DRAM_ADDR} {0}")
        tran.writeAction(f"move {cls.SHT_DESC_STURCT_OFF_START_NWID}({REG_SHT_DESC_LM_ADDR}) {REG_CUR_NWID} 0 4")
        tran.writeAction(f"move {cls.SHT_DESC_STURCT_OFF_NUM_ALLOC_LANES}({REG_SHT_DESC_LM_ADDR}) {REG_TMP1} 0 4")  # REG_TMP1 -> num lanes (as synchonization counter)
        tran.writeAction(f"add {REG_CUR_NWID} {REG_TMP1} {REG_TMP0}")  # REG_TMP0 -> end nwid
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: num_alloc_lanes = %d, start_nwid = %d, start_dram_addr = %d' {'X0'} {REG_TMP1} {REG_CUR_NWID} {REG_CUR_DRAM_ADDR}")
        # send loop
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: sending init to dst nwid = %d' {'X0'} {REG_CUR_NWID}")
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_loop_next'}: add {REG_CUR_DRAM_ADDR} {REG_LANE_DRAM_SIZE} {REG_CUR_DRAM_ADDR}")
        SHTLane.initialize(tran=tran, ret=tran_lane_init_ret.getLabel(), tmp_reg0=REG_TMP2, tmp_reg1=REG_TMP3, arg_lm_addr_reg=REG_TMP_BUF_LM_ADDR, dst_nwid_reg=REG_CUR_NWID)
        tran.writeAction(f"addi {REG_CUR_NWID} {REG_CUR_NWID} {1}")
        tran.writeAction(f"move {REG_CUR_DRAM_ADDR} {cls.WORD_SIZE * 3}({REG_TMP_BUF_LM_ADDR}) 0 8")
        tran.writeAction(f"blt {REG_CUR_NWID} {REG_TMP0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_loop_next'}")
        tran.writeAction("yield")

        """==================== TRAN - init return ===================="""
        tran_lane_init_ret.writeAction(f"subi {REG_TMP1} {REG_TMP1} {1}")
        if cls.DEBUG:
            tran_lane_init_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: bucket on NWID %d initialized.' {'X0'} {'X8'}")
        tran_lane_init_ret.writeAction(f"bgti {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-lane_init_ret-LB-yield'}")
        if cls.DEBUG:
            tran_lane_init_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: done, terminating' {'X0'}")
        tran_lane_init_ret.writeAction(f"mov_imm2reg {REG_TMP0} {cls.SHT_DESC_SIZE}")
        sht_macros.return_wreg(tran_lane_init_ret, REG_CONT, REG_TMP0, 'X9')  # return format: (SHT_DESC_SIZE, SHT_PER_LANE_DESC_SIZE)
        tran_lane_init_ret.writeAction("yield_terminate")
        tran_lane_init_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-lane_init_ret-LB-yield'}: yield")

    @classmethod
    def initialize(cls, tran: Transition, ret: int, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_initialize.getLabel(), ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=8)

    @classmethod
    def initialize_wcont(cls, tran: Transition, ret: str, tmp_reg0: str, arg_lm_addr_reg: str, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_initialize.getLabel(), cont_reg=ret, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=8)

    @classmethod
    def _finalize(cls, state: State) -> None:
        """
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._finalize.__name__

        REG_TMP0 = 'X16'

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_finalize
        if tran is None:
            return

        """==================== TRAN - entry ===================="""
        sht_macros.return_wreg(tran, 'X1', 'X0', 'X0')
        tran.writeAction("yield_terminate")

    @classmethod
    def finalize(cls, tran: Transition, ret: int, tmp_reg0: str, tmp_reg1: str, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_initialize.getLabel(), ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0='X0', arg_reg1='X0')

    @classmethod
    def finalize_wcont(cls, tran: Transition, ret: str, tmp_reg0: str, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_initialize.getLabel(), cont_reg=ret, tmp_reg=tmp_reg0, arg_reg0='X0', arg_reg1='X0')

    @classmethod
    def _update(cls, state: State) -> None:
        """
        X8  - SHT_DESC_LM_OFFSET(0:31) | TMP_BUF_LM_OFFSET(32:63)
        X9  - KEY
        X10 ~ X15 - value
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._update.__name__

        OB_SHT_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET = "X8"
        OB_KEY = "X9"
        OB_VAL = "X10"
        MAX_VAL_NUM_WORDS = 6

        REG_SHT_DESC_LM_ADDR = "X16"
        REG_TMP_BUF_LM_ADDR = "X17"
        REG_TMP0 = "X18"
        REG_TMP1 = "X19"
        REG_TMP2 = "X20"

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_update
        if tran is None:
            return
        cls.tran_label_update = tran.getLabel()

        """==================== TRAN - entry ===================="""
        # calculate lm addr
        tran.writeAction(f"lshift {OB_SHT_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET} {REG_SHT_DESC_LM_ADDR} {32}")
        tran.writeAction(f"rshift {REG_SHT_DESC_LM_ADDR} {REG_SHT_DESC_LM_ADDR} {32}")
        tran.writeAction(f"rshift {OB_SHT_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET} {REG_TMP_BUF_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_SHT_DESC_LM_ADDR} {'X7'} {REG_SHT_DESC_LM_ADDR}")
        tran.writeAction(f"add {REG_TMP_BUF_LM_ADDR} {'X7'} {REG_TMP_BUF_LM_ADDR}")

        # hash
        cls._macro_hash_word(tran=tran, in_sht_desc_lm_addr_reg=REG_SHT_DESC_LM_ADDR, in_key_reg=OB_KEY, out_lane_desc_lm_off_reg=REG_TMP0, out_bucket_desc_lm_off_reg=REG_TMP1, out_dst_nwid_reg=REG_TMP2, fn_name=FN_NAME)

        # write to LM buf for calling
        tran.writeAction(f"lshift_or {REG_TMP1} {REG_TMP0} {32}")  # combine LANE_DESC_LM_OFFSET(0:31) | BUCKET_DESC_LM_OFFSET(32:63)
        tran.writeAction(f"move {REG_TMP0} {0}({REG_TMP_BUF_LM_ADDR}) 0 8")

        # extract the number of value operands along with key
        tran.writeAction(f"rshift_and_imm {'X2'} {REG_TMP0} {20} {0b111}")
        tran.writeAction(f"addi {REG_TMP0} {REG_TMP0} {1}")  # add 1 for key
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: number of operands for key & val = %d' {'X0'} {REG_TMP0}")

        # copy key and values to LM buf for calling
        tran.writeAction(f"addi {REG_TMP_BUF_LM_ADDR} {REG_TMP1} {cls.WORD_SIZE}")
        tran.writeAction(f"bcopy_ops {OB_KEY} {REG_TMP1} {REG_TMP0}")

        # calling with the proper number of operands
        # mininum 3 words: X8, X9, X10
        for i in range(3, 8 + 1):
            tran.writeAction(f"beqi {REG_TMP0} {i - 1} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send{i}'}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: shouldn't reach here!' {'X0'}")
        for i in range(3, 8 + 1):
            tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send{i}'}: addi {REG_TMP1} {REG_TMP1} {0}")  # dummy
            SHTLane.update_wcont(tran=tran, ret='X1', tmp_reg0=REG_TMP1, arg_lm_addr_reg=REG_TMP_BUF_LM_ADDR, arg_lm_words=i, dst_nwid_reg=REG_TMP2)
            tran.writeAction("yield_terminate")

    @classmethod
    def update(cls, tran: Transition, ret: int, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, num_val_words: int, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_update.getLabel(), ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=(2 + num_val_words))

    @classmethod
    def update_wcont(cls, tran: Transition, ret: str, tmp_reg0: str, arg_lm_addr_reg: str, num_val_words: int, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_update.getLabel(), cont_reg=ret, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=(2 + num_val_words))

    @classmethod
    def _get(cls, state: State) -> None:
        """
        X8 - SHT_DESC_LM_OFFSET
        X9 - KEY
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._get.__name__

        OB_SHT_DESC_LM_OFFSET = 'X8'
        OB_KEY = 'X9'

        REG_SHT_DESC_LM_ADDR = 'X16'
        REG_TMP0 = 'X17'
        REG_TMP1 = 'X18'
        REG_TMP2 = 'X19'

        tran = cls.tran_get
        if tran is None:
            return
        cls.tran_label_get = tran.getLabel()

        # calculate lm addr
        tran.writeAction(f"add {OB_SHT_DESC_LM_OFFSET} {'X7'} {REG_SHT_DESC_LM_ADDR}")

        # hash
        cls._macro_hash_word(tran=tran, in_sht_desc_lm_addr_reg=REG_SHT_DESC_LM_ADDR, in_key_reg=OB_KEY, out_lane_desc_lm_off_reg=REG_TMP0, out_bucket_desc_lm_off_reg=REG_TMP1, out_dst_nwid_reg=REG_TMP2, fn_name=FN_NAME)

        tran.writeAction(f"lshift_or {REG_TMP1} {REG_TMP0} {32}")  # combine LANE_DESC_LM_OFFSET(0:31) | BUCKET_DESC_LM_OFFSET(32:63)

        # call
        SHTLane.get_wcont(tran=tran, ret='X1', tmp_reg=REG_TMP1, desc_lm_offset_reg=REG_TMP0, key_reg=OB_KEY, dst_nwid_reg=REG_TMP2)
        tran.writeAction("yield_terminate")

    @classmethod
    def get(cls, tran: Transition, ret: int, tmp_reg0: str, tmp_reg1: str, desc_lm_offset_reg: str, key_reg: str, dst_nwid_reg: str = 'X0'):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_get.getLabel(), ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=desc_lm_offset_reg, arg_reg1=key_reg)

    @classmethod
    def get_wcont(cls, tran: Transition, ret: str, tmp_reg: str, desc_lm_offset_reg: str, key_reg: str, dst_nwid_reg: str = 'X0'):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_get.getLabel(), cont_reg=ret, tmp_reg=tmp_reg, arg_reg0=desc_lm_offset_reg, arg_reg1=key_reg)

    @classmethod
    def _ext_graph_append(cls, state: State) -> None:
        """
        X8  - SHT_DESC_LM_OFFSET(0:31) | TMP_BUF_LM_OFFSET(32:63)
        X9  - KEY
        X10 ~ X15 - VALUE
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._ext_graph_append.__name__

        OB_SHT_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET = "X8"
        OB_KEY = "X9"
        MAX_VAL_NUM_WORDS = 6

        REG_SHT_DESC_LM_ADDR = "X16"
        REG_TMP_BUF_LM_ADDR = "X17"
        REG_TMP0 = "X18"
        REG_TMP1 = "X19"
        REG_TMP2 = "X20"

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_ext_graph_append
        if tran is None:
            return
        cls.tran_label_ext_graph_append = tran.getLabel()

        """==================== TRAN - entry ===================="""
        # calculate lm addr
        tran.writeAction(f"lshift {OB_SHT_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET} {REG_SHT_DESC_LM_ADDR} {32}")
        tran.writeAction(f"rshift {REG_SHT_DESC_LM_ADDR} {REG_SHT_DESC_LM_ADDR} {32}")
        tran.writeAction(f"rshift {OB_SHT_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET} {REG_TMP_BUF_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_SHT_DESC_LM_ADDR} {'X7'} {REG_SHT_DESC_LM_ADDR}")
        tran.writeAction(f"add {REG_TMP_BUF_LM_ADDR} {'X7'} {REG_TMP_BUF_LM_ADDR}")

        # hash
        cls._macro_hash_word(tran=tran, in_sht_desc_lm_addr_reg=REG_SHT_DESC_LM_ADDR, in_key_reg=OB_KEY, out_lane_desc_lm_off_reg=REG_TMP0, out_bucket_desc_lm_off_reg=REG_TMP1, out_dst_nwid_reg=REG_TMP2, fn_name=FN_NAME)

        # write to LM buf for calling
        tran.writeAction(f"lshift_or {REG_TMP1} {REG_TMP0} {32}")  # combine LANE_DESC_LM_OFFSET(0:31) | BUCKET_DESC_LM_OFFSET(32:63)
        tran.writeAction(f"move {REG_TMP0} {0}({REG_TMP_BUF_LM_ADDR}) 0 8")

        # extract the number of value operands along with key
        tran.writeAction(f"rshift_and_imm {'X2'} {REG_TMP0} {20} {0b111}")
        tran.writeAction(f"addi {REG_TMP0} {REG_TMP0} {1}")  # add 1 for key
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: number of operands for key & val = %d' {'X0'} {REG_TMP0}")

        # copy key and values to LM buf for calling
        tran.writeAction(f"addi {REG_TMP_BUF_LM_ADDR} {REG_TMP1} {cls.WORD_SIZE}")
        tran.writeAction(f"bcopy_ops {OB_KEY} {REG_TMP1} {REG_TMP0}")

        # calling with the proper number of operands
        # mininum 3 words: X8, X9, X10
        for i in range(3, 8 + 1):
            tran.writeAction(f"beqi {REG_TMP0} {i - 1} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send{i}'}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: shouldn't reach here!' {'X0'}")
        for i in range(3, 8 + 1):
            tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send{i}'}: addi {REG_TMP1} {REG_TMP1} {0}")  # dummy
            SHTLane.ext_graph_append_wcont(tran=tran, ret='X1', tmp_reg0=REG_TMP1, arg_lm_addr_reg=REG_TMP_BUF_LM_ADDR, arg_lm_words=i, dst_nwid_reg=REG_TMP2)
            tran.writeAction("yield_terminate")

    @classmethod
    def ext_graph_append(cls, tran: Transition, ret: int, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, num_val_words: int, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_ext_graph_append.getLabel(), ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=(2 + num_val_words))

    @classmethod
    def ext_graph_append_wcont(cls, tran: Transition, ret: str, tmp_reg0: str, arg_lm_addr_reg: str, num_val_words: int, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_ext_graph_append.getLabel(), cont_reg=ret, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=(2 + num_val_words))

    @classmethod
    def _ext_graph_append_migrate(cls, state: State) -> None:
        """
        X8  - SHT_DESC_LM_OFFSET(0:31) | TMP_BUF_LM_OFFSET(32:63)
        X9  - KEY
        X10 - SRC_VAL_ADDR
        X11 - COPY_NUM_WORDS
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._ext_graph_append_migrate.__name__

        OB_SHT_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET = "X8"
        OB_KEY = "X9"
        OB_SRC_VAL_ADDR = "X10"
        OB_COPY_NUM_WORDS = "X11"

        REG_SHT_DESC_LM_ADDR = "X16"
        REG_TMP_BUF_LM_ADDR = "X17"
        REG_TMP0 = "X18"
        REG_TMP1 = "X19"
        REG_TMP2 = "X20"

        tran = cls.tran_ext_graph_append_migrate
        if tran is None:
            return
        cls.tran_label_ext_graph_append_migrate = tran.getLabel()

        # calculate lm addr
        tran.writeAction(f"lshift {OB_SHT_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET} {REG_SHT_DESC_LM_ADDR} {32}")
        tran.writeAction(f"rshift {REG_SHT_DESC_LM_ADDR} {REG_SHT_DESC_LM_ADDR} {32}")
        tran.writeAction(f"rshift {OB_SHT_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET} {REG_TMP_BUF_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_SHT_DESC_LM_ADDR} {'X7'} {REG_SHT_DESC_LM_ADDR}")
        tran.writeAction(f"add {REG_TMP_BUF_LM_ADDR} {'X7'} {REG_TMP_BUF_LM_ADDR}")

        cls._macro_hash_word(tran=tran, in_sht_desc_lm_addr_reg=REG_SHT_DESC_LM_ADDR, in_key_reg=OB_KEY, out_lane_desc_lm_off_reg=REG_TMP0, out_bucket_desc_lm_off_reg=REG_TMP1, out_dst_nwid_reg=REG_TMP2, fn_name=FN_NAME)

        # write to LM buf for calling
        tran.writeAction(f"lshift_or {REG_TMP1} {REG_TMP0} {32}")  # combine LANE_DESC_LM_OFFSET(0:31) | BUCKET_DESC_LM_OFFSET(32:63)
        tran.writeAction(f"move {REG_TMP0} {0}({REG_TMP_BUF_LM_ADDR}) 0 8")

        # copy key and values to LM buf for calling
        tran.writeAction(f"mov_imm2reg {REG_TMP0} {3}")
        tran.writeAction(f"addi {REG_TMP_BUF_LM_ADDR} {REG_TMP1} {cls.WORD_SIZE}")
        tran.writeAction(f"bcopy_ops {OB_KEY} {REG_TMP1} {REG_TMP0}")

        # call
        SHTLane.ext_graph_append_migrate_wcont(tran=tran, ret='X1', tmp_reg=REG_TMP0, arg_lm_addr_reg=REG_TMP_BUF_LM_ADDR, dst_nwid_reg=REG_TMP2)
        tran.writeAction("yield_terminate")

    @classmethod
    def ext_graph_append_migrate(cls, tran: Transition, ret: int, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_ext_graph_append_migrate.getLabel(), ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=4)

    @classmethod
    def ext_graph_append_migrate_wcont(cls, tran: Transition, ret: str, tmp_reg0: str, arg_lm_addr_reg: str, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_ext_graph_append_migrate.getLabel(), cont_reg=ret, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=4)

    @classmethod
    def _ext_graph_get_with_offset(cls, state: State) -> None:
        """
        X8 - SHT_DESC_LM_OFFSET
        X9 - KEY
        X10 - OFFSET
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._ext_graph_get_with_offset.__name__

        OB_SHT_DESC_LM_OFFSET = 'X8'
        OB_KEY = 'X9'
        OB_OFFSET = 'X10'

        REG_SHT_DESC_LM_ADDR = 'X16'
        REG_TMP0 = 'X17'
        REG_TMP1 = 'X18'
        REG_TMP2 = 'X19'

        tran = cls.tran_ext_graph_get_with_offset
        if tran is None:
            return
        cls.tran_label_ext_graph_get_with_offset = tran.getLabel()

        # calculate lm addr
        tran.writeAction(f"add {OB_SHT_DESC_LM_OFFSET} {'X7'} {REG_SHT_DESC_LM_ADDR}")

        # hash
        cls._macro_hash_word(tran=tran, in_sht_desc_lm_addr_reg=REG_SHT_DESC_LM_ADDR, in_key_reg=OB_KEY, out_lane_desc_lm_off_reg=REG_TMP0, out_bucket_desc_lm_off_reg=REG_TMP1, out_dst_nwid_reg=REG_TMP2, fn_name=FN_NAME)

        tran.writeAction(f"lshift_or {REG_TMP1} {REG_TMP0} {32}")  # combine LANE_DESC_LM_OFFSET(0:31) | BUCKET_DESC_LM_OFFSET(32:63)

        # call
        SHTLane.ext_graph_get_with_offset_wcont(tran=tran, cont_reg='X1', tmp_reg=REG_TMP1, desc_lm_offset_reg=REG_TMP0, key_reg=OB_KEY, offset_reg=OB_OFFSET, dst_nwid_reg=REG_TMP2)
        tran.writeAction("yield_terminate")

    @classmethod
    def ext_graph_get_with_offset(cls, tran: Transition, ret: int, tmp_reg0: str, tmp_reg1: str, desc_lm_offset_reg: str, key_reg: str, offset_reg: str, dst_nwid_reg: str = 'X0'):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_ext_graph_get_with_offset.getLabel(), ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=desc_lm_offset_reg, arg_reg1=key_reg, arg_reg2=offset_reg)

    @classmethod
    def ext_graph_get_with_offset_wcont(cls, tran: Transition, ret: str, tmp_reg: str, desc_lm_offset_reg: str, key_reg: str, offset_reg: str, dst_nwid_reg: str = 'X0'):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_ext_graph_get_with_offset.getLabel(), cont_reg=ret, tmp_reg=tmp_reg, arg_reg0=desc_lm_offset_reg, arg_reg1=key_reg, arg_reg2=offset_reg)

    @classmethod
    def _ext_graph_get_word_cnt(cls, state: State) -> None:
        """
        X8 - SHT_DESC_LM_OFFSET
        X9 - KEY
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._ext_graph_get_word_cnt.__name__

        OB_SHT_DESC_LM_OFFSET = 'X8'
        OB_KEY = 'X9'

        REG_SHT_DESC_LM_ADDR = 'X16'
        REG_TMP0 = 'X17'
        REG_TMP1 = 'X18'
        REG_TMP2 = 'X19'

        tran = cls.tran_ext_graph_get_word_cnt
        if tran is None:
            return
        cls.tran_label_ext_graph_get_word_cnt = tran.getLabel()

        # calculate lm addr
        tran.writeAction(f"add {OB_SHT_DESC_LM_OFFSET} {'X7'} {REG_SHT_DESC_LM_ADDR}")

        # hash
        cls._macro_hash_word(tran=tran, in_sht_desc_lm_addr_reg=REG_SHT_DESC_LM_ADDR, in_key_reg=OB_KEY, out_lane_desc_lm_off_reg=REG_TMP0, out_bucket_desc_lm_off_reg=REG_TMP1, out_dst_nwid_reg=REG_TMP2, fn_name=FN_NAME)

        tran.writeAction(f"lshift_or {REG_TMP1} {REG_TMP0} {32}")  # combine LANE_DESC_LM_OFFSET(0:31) | BUCKET_DESC_LM_OFFSET(32:63)

        # call
        SHTLane.ext_graph_get_word_cnt_wcont(tran=tran, cont_reg='X1', tmp_reg=REG_TMP1, desc_lm_offset_reg=REG_TMP0, key_reg=OB_KEY, dst_nwid_reg=REG_TMP2)
        tran.writeAction("yield_terminate")

    @classmethod
    def ext_graph_get_word_cnt(cls, tran: Transition, ret: int, tmp_reg0: str, tmp_reg1: str, desc_lm_offset_reg: str, key_reg: str, dst_nwid_reg: str = 'X0'):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_ext_graph_get_word_cnt.getLabel(), ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=desc_lm_offset_reg, arg_reg1=key_reg)

    @classmethod
    def ext_graph_get_word_cnt_wcont(cls, tran: Transition, ret: str, tmp_reg: str, desc_lm_offset_reg: str, key_reg: str, dst_nwid_reg: str = 'X0'):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_ext_graph_get_word_cnt.getLabel(), cont_reg=ret, tmp_reg=tmp_reg, arg_reg0=desc_lm_offset_reg, arg_reg1=key_reg)

    @classmethod
    def _get_with_mask(cls, state: State) -> None:
        """
        X8 - SHT_DESC_LM_OFFSET
        X9 - KEY
        X10 - MASK
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._get_with_mask.__name__

        OB_SHT_DESC_LM_OFFSET = 'X8'
        OB_KEY = 'X9'
        OB_MASK = 'X10'

        REG_SHT_DESC_LM_ADDR = 'X16'
        REG_TMP0 = 'X17'
        REG_TMP1 = 'X18'
        REG_TMP2 = 'X19'

        tran = cls.tran_get_with_mask
        if tran is None:
            return
        cls.tran_label_get_with_mask = tran.getLabel()

        # calculate lm addr
        tran.writeAction(f"add {OB_SHT_DESC_LM_OFFSET} {'X7'} {REG_SHT_DESC_LM_ADDR}")

        # hash
        cls._macro_hash_word(tran=tran, in_sht_desc_lm_addr_reg=REG_SHT_DESC_LM_ADDR, in_key_reg=OB_KEY, out_lane_desc_lm_off_reg=REG_TMP0, out_bucket_desc_lm_off_reg=REG_TMP1, out_dst_nwid_reg=REG_TMP2, fn_name=FN_NAME)

        tran.writeAction(f"lshift_or {REG_TMP1} {REG_TMP0} {32}")  # combine LANE_DESC_LM_OFFSET(0:31) | BUCKET_DESC_LM_OFFSET(32:63)

        # call
        SHTLane.get_with_mask_wcont(tran=tran, cont_reg='X1', tmp_reg=REG_TMP1, desc_lm_offset_reg=REG_TMP0, key_reg=OB_KEY, mask_reg=OB_MASK, dst_nwid_reg=REG_TMP2)
        tran.writeAction("yield_terminate")

    @classmethod
    def get_with_mask(cls, tran: Transition, ret: int, tmp_reg0: str, tmp_reg1: str, desc_lm_offset_reg: str, key_reg: str, mask_reg: str, dst_nwid_reg: str = 'X0'):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_get_with_mask.getLabel(), ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=desc_lm_offset_reg, arg_reg1=key_reg, arg_reg2=mask_reg)

    @classmethod
    def get_with_mask_wcont(cls, tran: Transition, ret: str, tmp_reg: str, desc_lm_offset_reg: str, key_reg: str, mask_reg: str, dst_nwid_reg: str = 'X0'):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_get_with_mask.getLabel(), cont_reg=ret, tmp_reg=tmp_reg, arg_reg0=desc_lm_offset_reg, arg_reg1=key_reg, arg_reg2=mask_reg)

    @classmethod
    def _update_with_mask(cls, state: State) -> None:
        """
        only support up to the first 8 value words

        X8  - SHT_DESC_LM_OFFSET(0:31) | TMP_BUF_LM_OFFSET(32:63)
        X9  - KEY
        X10 - MASK
        X11 ~ X15 - VALUES
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._update_with_mask.__name__

        OB_SHT_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET = "X8"
        OB_KEY = "X9"
        OB_MASK = "X10"
        OB_VAL = "X11"
        MAX_VAL_NUM_WORDS = 5

        REG_SHT_DESC_LM_ADDR = "X16"
        REG_TMP_BUF_LM_ADDR = "X17"
        REG_TMP0 = "X18"
        REG_TMP1 = "X19"
        REG_TMP2 = "X20"

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_update_with_mask
        if tran is None:
            return
        cls.tran_label_update_with_mask = tran.getLabel()

        """==================== TRAN - entry ===================="""
        # calculate lm addr
        tran.writeAction(f"lshift {OB_SHT_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET} {REG_SHT_DESC_LM_ADDR} {32}")
        tran.writeAction(f"rshift {REG_SHT_DESC_LM_ADDR} {REG_SHT_DESC_LM_ADDR} {32}")
        tran.writeAction(f"rshift {OB_SHT_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET} {REG_TMP_BUF_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_SHT_DESC_LM_ADDR} {'X7'} {REG_SHT_DESC_LM_ADDR}")
        tran.writeAction(f"add {REG_TMP_BUF_LM_ADDR} {'X7'} {REG_TMP_BUF_LM_ADDR}")

        # hash
        cls._macro_hash_word(tran=tran, in_sht_desc_lm_addr_reg=REG_SHT_DESC_LM_ADDR, in_key_reg=OB_KEY, out_lane_desc_lm_off_reg=REG_TMP0, out_bucket_desc_lm_off_reg=REG_TMP1, out_dst_nwid_reg=REG_TMP2, fn_name=FN_NAME)

        # write to LM buf for calling
        tran.writeAction(f"lshift_or {REG_TMP1} {REG_TMP0} {32}")  # combine LANE_DESC_LM_OFFSET(0:31) | BUCKET_DESC_LM_OFFSET(32:63)
        tran.writeAction(f"move {REG_TMP0} {0}({REG_TMP_BUF_LM_ADDR}) 0 8")

        # extract the number of value operands along with key
        tran.writeAction(f"rshift_and_imm {'X2'} {REG_TMP0} {20} {0b111}")
        tran.writeAction(f"addi {REG_TMP0} {REG_TMP0} {1}")  # add 1 for key
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: number of operands for key, mask & val = %d' {'X0'} {REG_TMP0}")

        # copy key and values to LM buf for calling
        tran.writeAction(f"addi {REG_TMP_BUF_LM_ADDR} {REG_TMP1} {cls.WORD_SIZE}")
        tran.writeAction(f"bcopy_ops {OB_KEY} {REG_TMP1} {REG_TMP0}")

        # calling with the proper number of operands
        # mininum 4 words: X8, X9, X10, X11
        for i in range(4, 8 + 1):
            tran.writeAction(f"beqi {REG_TMP0} {i - 1} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send{i}'}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: shouldn't reach here!' {'X0'}")
        for i in range(4, 8 + 1):
            tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send{i}'}: addi {REG_TMP1} {REG_TMP1} {0}")  # dummy
            SHTLane.update_with_mask_wcont(tran=tran, cont_reg='X1', tmp_reg0=REG_TMP1, arg_lm_addr_reg=REG_TMP_BUF_LM_ADDR, arg_lm_words=i, dst_nwid_reg=REG_TMP2)
            tran.writeAction("yield_terminate")

    @classmethod
    def update_with_mask(cls, tran: Transition, ret: int, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, num_val_words: int, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_update_with_mask.getLabel(), ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=(3 + num_val_words))

    @classmethod
    def update_with_mask_wcont(cls, tran: Transition, ret: str, tmp_reg0: str, arg_lm_addr_reg: str, num_val_words: int, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_update_with_mask.getLabel(), cont_reg=ret, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=(3 + num_val_words))
