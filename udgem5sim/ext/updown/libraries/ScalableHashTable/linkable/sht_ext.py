from linker.EFAProgram import efaProgram, EFAProgram
import sht_macros
from memcpy import Memcpy
from sht_ext_call_macros import SHTExt as SHTExtCall
import math


@efaProgram
def SHTExtModule(efa):
    efa.code_level = 'machine'

    state0 = efa.State()
    efa.add_initId(state0.state_id)

    SHTExt.setup(state0, debug=False)

    return efa


class SHTExt:
    """
    struct SHT_DESC {
        WORD NUM_ALLOC_LANES(0:31) | START_NWID(32:63);
        WORD LANE_DESC_LM_OFFSET(0:31) | BUCKETS_PER_LANE(32:63);
        WORD ENTRIES_PER_BUCKET(0:31) | VAL_NUM_WORDS(32:63);
        WORD DRAM_ALLOC_ADDR;
    }
    """

    @classmethod
    def setup(cls, state: EFAProgram.State, enable_ext=True, big_endian=False, debug=False) -> None:
        cls.ENABLE_EXT = enable_ext
        cls.LANES_PER_UD = 64
        cls.LANES_MASK = cls.LANES_PER_UD - 1

        cls.KEY_SIZE = 8
        cls.WORD_SIZE = 8

        cls.SHT_DESC_SIZE = 4 * cls.WORD_SIZE
        if not big_endian:
            # LITTLE ENDIAN
            cls.SHT_DESC_STURCT_OFF_NUM_ALLOC_LANES = 0  # 4 bytes
            cls.SHT_DESC_STURCT_OFF_START_NWID = cls.SHT_DESC_STURCT_OFF_NUM_ALLOC_LANES + 4  # 4 bytes
            cls.SHT_DESC_STURCT_OFF_LANE_DESC_LM_OFFSET = cls.SHT_DESC_STURCT_OFF_START_NWID + 4  # 4 bytes
            cls.SHT_DESC_STURCT_OFF_BUCKETS_PER_LANE = cls.SHT_DESC_STURCT_OFF_LANE_DESC_LM_OFFSET + 4  # 4 bytes
            cls.SHT_DESC_STURCT_OFF_ENTRIES_PER_BUCKET = cls.SHT_DESC_STURCT_OFF_BUCKETS_PER_LANE + 4  # 4 bytes
            cls.SHT_DESC_STURCT_OFF_VAL_NUM_WORDS = cls.SHT_DESC_STURCT_OFF_ENTRIES_PER_BUCKET + 4  # 4 bytes
            cls.SHT_DESC_STURCT_OFF_DRAM_ALLOC_ADDR = cls.SHT_DESC_STURCT_OFF_VAL_NUM_WORDS + 4  # 8 bytes
        else:
            # BIG ENDIAN
            cls.SHT_DESC_STURCT_OFF_START_NWID = 0  # 4 bytes
            cls.SHT_DESC_STURCT_OFF_NUM_ALLOC_LANES = cls.SHT_DESC_STURCT_OFF_START_NWID + 4  # 4 bytes
            cls.SHT_DESC_STURCT_OFF_BUCKETS_PER_LANE = cls.SHT_DESC_STURCT_OFF_NUM_ALLOC_LANES + 4  # 4 bytes
            cls.SHT_DESC_STURCT_OFF_LANE_DESC_LM_OFFSET = cls.SHT_DESC_STURCT_OFF_BUCKETS_PER_LANE + 4  # 4 bytes
            cls.SHT_DESC_STURCT_OFF_VAL_NUM_WORDS = cls.SHT_DESC_STURCT_OFF_LANE_DESC_LM_OFFSET + 4  # 4 bytes
            cls.SHT_DESC_STURCT_OFF_ENTRIES_PER_BUCKET = cls.SHT_DESC_STURCT_OFF_VAL_NUM_WORDS + 4  # 4 bytes
            cls.SHT_DESC_STURCT_OFF_DRAM_ALLOC_ADDR = cls.SHT_DESC_STURCT_OFF_ENTRIES_PER_BUCKET + 4  # 8 bytes

        cls.DEBUG = debug

        CLS_NAME = cls.__name__
        cls.tran_initialize = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-initialize-TR")
        cls.tran_finalize = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-finalize-TR")
        cls.tran_update = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-update-TR")
        cls.tran_update_with_mask = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-update_with_mask-TR")
        cls.tran_update_with_offset = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-update_with_offset-TR")
        cls.tran_get = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-get-TR")
        cls.tran_get_with_mask = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-get_with_mask-TR")
        cls.tran_get_with_offset = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-get_with_offset-TR")
        cls.tran_get_with_random = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-get_with_random-TR")
        # cls.tran_delete = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-delete-TR")
        cls.tran_get_iterators = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-get_iterators-TR")
        cls.tran_get_next = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-get_next-TR")
        cls.tran_get_next_split = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-get_next_split-TR")
        if cls.ENABLE_EXT:
            cls.tran_ext_graph_append = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-ext_graph_append-TR")
            cls.tran_ext_graph_append_migrate = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-ext_graph_append_migrate-TR")
            cls.tran_ext_graph_get_next = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-ext_graph_get_next-TR")
            cls.tran_ext_graph_get_addr = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-ext_graph_get_addr-TR")

        # TODO: code injection
        SHTLane.setup(state, enable_ext=enable_ext, big_endian=big_endian, debug=debug)
        SHTExtBroadcast.setup(state, fanout=16, debug=debug)
        cls._initialize(state)
        cls._finalize(state)
        cls._update(state)
        cls._update_with_mask(state)
        cls._update_with_offset(state)
        cls._get(state)
        cls._get_with_mask(state)
        cls._get_with_offset(state)
        cls._get_with_random(state)
        cls._get_iterators(state)
        cls._get_next(state)
        cls._get_next_split(state)
        # cls._delete(state)
        if cls.ENABLE_EXT:
            cls._ext_graph_append_migrate(state)
            cls._ext_graph_append(state)
            cls._ext_graph_get_next(state)
            cls._ext_graph_get_addr(state)

    @classmethod
    def _macro_calc_dst(cls, tran: EFAProgram.Transition, IN_sht_desc_lm_addr_reg: str, IN_key_reg: str, OUT_lane_desc_lm_off_reg: str, OUT_bucket_desc_lm_off_reg: str, OUT_dst_nwid_reg: str, fn_name: str, no_hash=False) -> None:
        CLS_NAME = cls.__name__
        FN_NAME = fn_name

        REG_KEY = IN_key_reg
        REG_SHT_DESC_LM_ADDR = IN_sht_desc_lm_addr_reg
        REG_TMP0 = OUT_lane_desc_lm_off_reg
        REG_TMP1 = OUT_bucket_desc_lm_off_reg
        REG_TMP2 = OUT_dst_nwid_reg

        if not no_hash:
            # hash the destination lane id
            if cls.DEBUG:
                tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: key = %lu' {'X0'} {REG_KEY}")
            tran.writeAction(f"mov_imm2reg {REG_TMP0} {0}")  # REG_TMP0 -> seed
            tran.writeAction(f"hash {REG_KEY} {REG_TMP0}")  # REG_TMP0 -> hash
            if cls.DEBUG:
                tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: hash = %lu' {'X0'} {REG_TMP0}")
        else:
            tran.writeAction(f"addi {REG_KEY} {REG_TMP0} {0}")
            if cls.DEBUG:
                tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: random input = %lu' {'X0'} {REG_TMP0}")

        # calc dest lane
        tran.writeAction(f"move {cls.SHT_DESC_STURCT_OFF_NUM_ALLOC_LANES}({REG_SHT_DESC_LM_ADDR}) {REG_TMP1} 0 4")  # REG_TMP1 -> num lane
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: num lane = %lu' {'X0'} {REG_TMP1}")
        tran.writeAction(f"subi {REG_TMP1} {REG_TMP1} {1}")  # REG_TMP1 -> lane mask (WARNING: assume num lane is power of 2)
        tran.writeAction(f"andr {REG_TMP0} {REG_TMP1} {REG_TMP1}")  # REG_TMP1 -> nwid offset
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: nwid offset = %lu' {'X0'} {REG_TMP1}")
        tran.writeAction(f"move {cls.SHT_DESC_STURCT_OFF_START_NWID}({REG_SHT_DESC_LM_ADDR}) {REG_TMP2} 0 4")  # REG_TMP2 -> start nwid
        tran.writeAction(f"add {REG_TMP2} {REG_TMP1} {REG_TMP2}")  # REG_TMP2 -> [dest nwid]
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: dst nwid = %lu' {'X0'} {REG_TMP2}")

        # calculate the address of the bucket descriptor on the destination lane
        tran.writeAction(f"move {cls.SHT_DESC_STURCT_OFF_BUCKETS_PER_LANE}({REG_SHT_DESC_LM_ADDR}) {REG_TMP1} 0 4")  # REG_TMP1 -> number of bucket per lane
        tran.writeAction(f"subi {REG_TMP1} {REG_TMP1} {1}")  # REG_TMP1 -> lane bucket off mask
        tran.writeAction(f"rshift {REG_TMP0} {REG_TMP0} {32}")  # low 32b hash for nwid, upper 32b for bucket
        tran.writeAction(f"andr {REG_TMP0} {REG_TMP1} {REG_TMP1}")  # REG_TMP1 -> lane bucket offset
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: lane bucket off = %lu' {'X0'} {REG_TMP1}")
        tran.writeAction(f"muli {REG_TMP1} {REG_TMP1} {SHTLane.BUCKET_DESC_SIZE}")
        tran.writeAction(f"move {cls.SHT_DESC_STURCT_OFF_LANE_DESC_LM_OFFSET}({REG_SHT_DESC_LM_ADDR}) {REG_TMP0} 0 4")  # REG_TMP0 -> [lane desc lm offset base]
        tran.writeAction(f"add {REG_TMP0} {REG_TMP1} {REG_TMP1}")  # REG_TMP1 -> bucket desc lm addr
        tran.writeAction(f"addi {REG_TMP1} {REG_TMP1} {SHTLane.LANE_DESC_SIZE}")  # REG_TMP1 -> [bucket desc lm addr]
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: LANE_DESC_LM_OFFSET = 0x%lx, BUCKET_DESC_LM_OFFSET = 0x%lx' {'X0'} {REG_TMP0} {REG_TMP1}")

    @classmethod
    def _initialize(cls, state: EFAProgram.State):
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

        Return:
        X8 - SHT_DESC_SIZE
        X9 - SHT_LANE_DESC_SIZE
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
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: entry' {'X0'}")

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
        if cls.ENABLE_EXT:
            # get number of operands
            tran.writeAction(f"rshift {'X2'} {REG_TMP2} {20}")
            tran.writeAction(f"andi {REG_TMP2} {REG_TMP2} {0b111}")
            # copy send buffer
            tran.writeAction(f"mov_imm2reg {REG_TMP0} {cls.SHT_DESC_SIZE // cls.WORD_SIZE + 3}")
            tran.writeAction(f"bgti {REG_TMP2} {cls.SHT_DESC_SIZE // cls.WORD_SIZE + 1 - 2} {f'{CLS_NAME}-{FN_NAME}-TR-LB-cpy_with_ext'}")
            tran.writeAction(f"mov_imm2reg {REG_TMP0} {cls.SHT_DESC_SIZE // cls.WORD_SIZE}")
            tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-cpy_with_ext'}: bcopy_ops {OB_NUM_ALLOC_LANES__START_NWID} {REG_TMP_BUF_LM_ADDR} {REG_TMP0}")
        else:
            # copy send buffer
            tran.writeAction(f"mov_imm2reg {REG_TMP0} {cls.SHT_DESC_SIZE // cls.WORD_SIZE}")
            tran.writeAction(f"bcopy_ops {OB_NUM_ALLOC_LANES__START_NWID} {REG_TMP_BUF_LM_ADDR} {REG_TMP0}")
        # calculate lane dram alloc size
        tran.writeAction(f"move {cls.SHT_DESC_STURCT_OFF_BUCKETS_PER_LANE}({REG_SHT_DESC_LM_ADDR}) {REG_LANE_DRAM_SIZE} 0 4")
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
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: num_alloc_lanes = %lu, start_nwid = %lu, start_dram_addr = %lu' {'X0'} {REG_TMP1} {REG_CUR_NWID} {REG_CUR_DRAM_ADDR}")
        # send loop
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: sending init to dst nwid = %lu' {'X0'} {REG_CUR_NWID}")
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_loop_next'}: add {REG_CUR_DRAM_ADDR} {REG_LANE_DRAM_SIZE} {REG_CUR_DRAM_ADDR}")
        if cls.ENABLE_EXT:
            tran.writeAction(f"bgti {REG_TMP2} {cls.SHT_DESC_SIZE // cls.WORD_SIZE + 1 - 2} {f'{CLS_NAME}-{FN_NAME}-TR-LB-call_with_ext'}")
            SHTLane.initialize_without_ext(tran=tran, ret=tran_lane_init_ret.getLabel(), tmp_reg0=REG_TMP2, tmp_reg1=REG_TMP3, arg_lm_addr_reg=REG_TMP_BUF_LM_ADDR, dst_nwid_reg=REG_CUR_NWID)
            tran.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-LB-call_out'}")
            SHTLane.initialize(tran=tran, ret=tran_lane_init_ret.getLabel(), tmp_reg0=REG_TMP2, tmp_reg1=REG_TMP3, arg_lm_addr_reg=REG_TMP_BUF_LM_ADDR, dst_nwid_reg=REG_CUR_NWID, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-LB-call_with_ext')
        else:
            SHTLane.initialize_without_ext(tran=tran, ret=tran_lane_init_ret.getLabel(), tmp_reg0=REG_TMP2, tmp_reg1=REG_TMP3, arg_lm_addr_reg=REG_TMP_BUF_LM_ADDR, dst_nwid_reg=REG_CUR_NWID)
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-call_out'}: addi {REG_CUR_NWID} {REG_CUR_NWID} {1}")
        tran.writeAction(f"move {REG_CUR_DRAM_ADDR} {cls.WORD_SIZE * 3}({REG_TMP_BUF_LM_ADDR}) 0 8")
        tran.writeAction(f"blt {REG_CUR_NWID} {REG_TMP0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_loop_next'}")
        tran.writeAction("yield")

        """==================== TRAN - init return ===================="""
        tran_lane_init_ret.writeAction(f"subi {REG_TMP1} {REG_TMP1} {1}")
        if cls.DEBUG:
            tran_lane_init_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: bucket on NWID %lu initialized.' {'X0'} {'X8'}")
        tran_lane_init_ret.writeAction(f"bgti {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-lane_init_ret-LB-yield'}")
        if cls.DEBUG:
            tran_lane_init_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: done, terminating' {'X0'}")
        tran_lane_init_ret.writeAction(f"mov_imm2reg {REG_TMP0} {cls.SHT_DESC_SIZE}")
        sht_macros.return_wreg(tran=tran_lane_init_ret, cont_reg=REG_CONT, tmp_reg=REG_TMP1, arg_reg0=REG_TMP0, arg_reg1='X9')  # return format: (SHT_DESC_SIZE, SHT_PER_LANE_DESC_SIZE)
        tran_lane_init_ret.writeAction("yield_terminate")
        tran_lane_init_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-lane_init_ret-LB-yield'}: yield")

    @classmethod
    def _finalize(cls, state: EFAProgram.State) -> None:
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
        sht_macros.return_wreg(tran=tran, cont_reg='X1', tmp_reg=REG_TMP0, arg_reg0='X0', arg_reg1='X0')
        tran.writeAction("yield_terminate")

    @classmethod
    def _update(cls, state: EFAProgram.State) -> None:
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
        cls._macro_calc_dst(tran=tran, IN_sht_desc_lm_addr_reg=REG_SHT_DESC_LM_ADDR, IN_key_reg=OB_KEY, OUT_lane_desc_lm_off_reg=REG_TMP0, OUT_bucket_desc_lm_off_reg=REG_TMP1, OUT_dst_nwid_reg=REG_TMP2, fn_name=FN_NAME)

        # write to LM buf for calling
        tran.writeAction(f"lshift_or {REG_TMP1} {REG_TMP0} {32}")  # combine LANE_DESC_LM_OFFSET(0:31) | BUCKET_DESC_LM_OFFSET(32:63)
        tran.writeAction(f"move {REG_TMP0} {0}({REG_TMP_BUF_LM_ADDR}) 0 8")

        # extract the number of value operands along with key
        tran.writeAction(f"rshift {'X2'} {REG_TMP0} {20}")
        tran.writeAction(f"andi {REG_TMP0} {REG_TMP0} {0b111}")
        tran.writeAction(f"addi {REG_TMP0} {REG_TMP0} {1}")  # add 1 for key
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: number of operands for key & val = %lu' {'X0'} {REG_TMP0}")

        # copy key and values to LM buf for calling
        tran.writeAction(f"addi {REG_TMP_BUF_LM_ADDR} {REG_TMP1} {cls.WORD_SIZE}")
        tran.writeAction(f"bcopy_ops {OB_KEY} {REG_TMP1} {REG_TMP0}")

        # calling with the proper number of operands
        # mininum 3 words: X8, X9, X10
        for i in range(3, 8 + 1):
            tran.writeAction(f"beqi {REG_TMP0} {i - 1} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send{i}'}")
        tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: shouldn't reach here!' {'X0'}")
        for i in range(3, 8 + 1):
            SHTLane.update_wcont(tran=tran, ret='X1', tmp_reg0=REG_TMP1, arg_lm_addr_reg=REG_TMP_BUF_LM_ADDR, arg_lm_words=i, dst_nwid_reg=REG_TMP2, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-LB-send{i}')
            tran.writeAction("yield_terminate")

    @classmethod
    def _get(cls, state: EFAProgram.State) -> None:
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
        cls._macro_calc_dst(tran=tran, IN_sht_desc_lm_addr_reg=REG_SHT_DESC_LM_ADDR, IN_key_reg=OB_KEY, OUT_lane_desc_lm_off_reg=REG_TMP0, OUT_bucket_desc_lm_off_reg=REG_TMP1, OUT_dst_nwid_reg=REG_TMP2, fn_name=FN_NAME)

        tran.writeAction(f"lshift_or {REG_TMP1} {REG_TMP0} {32}")  # combine LANE_DESC_LM_OFFSET(0:31) | BUCKET_DESC_LM_OFFSET(32:63)

        # call
        SHTLane.get_wcont(tran=tran, ret='X1', tmp_reg=REG_TMP1, desc_lm_offset_reg=REG_TMP0, key_reg=OB_KEY, dst_nwid_reg=REG_TMP2)
        tran.writeAction("yield_terminate")

    @classmethod
    def macro_ext_graph_append(cls, tran: EFAProgram.Transition, IN_sht_desc_lm_addr_reg: str, IN_tmp_buf_lm_addr_reg: str, IN_key_reg: str, IN_num_val_words_reg: str, IN_cont_reg: str, tmp_reg0: str, tmp_reg1: str, tmp_reg2: str, finish_branch_label: str, cls_name: str, fn_name: str) -> None:
        """
        Assmue the LM Temp Buffer prepopulated with the following format:
        WORD0 - not populated
        WORD1 - not populated
        WORD2~7 - values
        """
        CLS_NAME = cls_name
        FN_NAME = fn_name
        REG_SHT_DESC_LM_ADDR = IN_sht_desc_lm_addr_reg
        REG_TMP_BUF_LM_ADDR = IN_tmp_buf_lm_addr_reg
        REG_KEY = IN_key_reg
        REG_NUM_VAL_WORDS = IN_num_val_words_reg
        REG_TMP0 = tmp_reg0
        REG_TMP1 = tmp_reg1
        REG_TMP2 = tmp_reg2

        # hash
        cls._macro_calc_dst(tran=tran, IN_sht_desc_lm_addr_reg=REG_SHT_DESC_LM_ADDR, IN_key_reg=REG_KEY, OUT_lane_desc_lm_off_reg=REG_TMP0, OUT_bucket_desc_lm_off_reg=REG_TMP1, OUT_dst_nwid_reg=REG_TMP2, fn_name=FN_NAME)

        # write to LM buf for calling
        tran.writeAction(f"lshift_or {REG_TMP1} {REG_TMP0} {32}")  # combine LANE_DESC_LM_OFFSET(0:31) | BUCKET_DESC_LM_OFFSET(32:63)
        tran.writeAction(f"move {REG_TMP0} {0}({REG_TMP_BUF_LM_ADDR}) 0 8")
        tran.writeAction(f"move {REG_KEY} {cls.WORD_SIZE}({REG_TMP_BUF_LM_ADDR}) 0 8")

        # calling with the proper number of operands
        # mininum 3 words: X8, X9, X10
        for i in range(3, 8 + 1):
            tran.writeAction(f"beqi {REG_NUM_VAL_WORDS} {i - 2} {f'{CLS_NAME}-{FN_NAME}-TR-{tran.getLabel()}-LB-send{i}'}")
        tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: shouldn't reach here!' {'X0'}")
        for i in range(3, 8 + 1):
            SHTLane.ext_graph_append_wcont(tran=tran, ret=IN_cont_reg, tmp_reg0=REG_TMP1, arg_lm_addr_reg=REG_TMP_BUF_LM_ADDR, arg_lm_words=i, dst_nwid_reg=REG_TMP2, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-{tran.getLabel()}-LB-send{i}')
            tran.writeAction(f"jmp {finish_branch_label}")

    @classmethod
    def _ext_graph_append(cls, state: EFAProgram.State) -> None:
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
        cls._macro_calc_dst(tran=tran, IN_sht_desc_lm_addr_reg=REG_SHT_DESC_LM_ADDR, IN_key_reg=OB_KEY, OUT_lane_desc_lm_off_reg=REG_TMP0, OUT_bucket_desc_lm_off_reg=REG_TMP1, OUT_dst_nwid_reg=REG_TMP2, fn_name=FN_NAME)

        # write to LM buf for calling
        tran.writeAction(f"lshift_or {REG_TMP1} {REG_TMP0} {32}")  # combine LANE_DESC_LM_OFFSET(0:31) | BUCKET_DESC_LM_OFFSET(32:63)
        tran.writeAction(f"move {REG_TMP0} {0}({REG_TMP_BUF_LM_ADDR}) 0 8")

        # extract the number of value operands along with key
        tran.writeAction(f"rshift {'X2'} {REG_TMP0} {20}")
        tran.writeAction(f"andi {REG_TMP0} {REG_TMP0} {0b111}")
        tran.writeAction(f"addi {REG_TMP0} {REG_TMP0} {1}")  # add 1 for key
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: number of operands for key & val = %lu' {'X0'} {REG_TMP0}")

        # copy key and values to LM buf for calling
        tran.writeAction(f"addi {REG_TMP_BUF_LM_ADDR} {REG_TMP1} {cls.WORD_SIZE}")
        tran.writeAction(f"bcopy_ops {OB_KEY} {REG_TMP1} {REG_TMP0}")

        # calling with the proper number of operands
        # mininum 3 words: X8, X9, X10
        for i in range(3, 8 + 1):
            tran.writeAction(f"beqi {REG_TMP0} {i - 1} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send{i}'}")
        tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: shouldn't reach here!' {'X0'}")
        for i in range(3, 8 + 1):
            SHTLane.ext_graph_append_wcont(tran=tran, ret='X1', tmp_reg0=REG_TMP1, arg_lm_addr_reg=REG_TMP_BUF_LM_ADDR, arg_lm_words=i, dst_nwid_reg=REG_TMP2, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-LB-send{i}')
            tran.writeAction("yield_terminate")

    @classmethod
    def macro_ext_graph_append_migrate(cls, tran: EFAProgram.Transition, IN_sht_desc_lm_addr_reg: str, IN_tmp_buf_lm_addr_reg: str, IN_key_reg: str, IN_cont_reg: str, tmp_reg0: str, tmp_reg1: str, tmp_reg2: str, cls_name: str, fn_name: str) -> None:
        """
        Assmue the LM Temp Buffer prepopulated with the following format:
        WORD0 - not populated
        WORD1 - not populated
        WORD2 - src_val_addr
        WORD3 - copy_num_words
        """
        CLS_NAME = cls_name
        FN_NAME = fn_name
        REG_SHT_DESC_LM_ADDR = IN_sht_desc_lm_addr_reg
        REG_TMP_BUF_LM_ADDR = IN_tmp_buf_lm_addr_reg
        REG_KEY = IN_key_reg
        REG_TMP0 = tmp_reg0
        REG_TMP1 = tmp_reg1
        REG_TMP2 = tmp_reg2

        # hash
        cls._macro_calc_dst(tran=tran, IN_sht_desc_lm_addr_reg=REG_SHT_DESC_LM_ADDR, IN_key_reg=REG_KEY, OUT_lane_desc_lm_off_reg=REG_TMP0, OUT_bucket_desc_lm_off_reg=REG_TMP1, OUT_dst_nwid_reg=REG_TMP2, fn_name=FN_NAME)

        # write to LM buf for calling
        tran.writeAction(f"lshift_or {REG_TMP1} {REG_TMP0} {32}")  # combine LANE_DESC_LM_OFFSET(0:31) | BUCKET_DESC_LM_OFFSET(32:63)
        tran.writeAction(f"move {REG_TMP0} {cls.WORD_SIZE * 0}({REG_TMP_BUF_LM_ADDR}) 0 8")
        tran.writeAction(f"move {REG_KEY} {cls.WORD_SIZE * 1}({REG_TMP_BUF_LM_ADDR}) 0 8")

        # call
        SHTLane.ext_graph_append_migrate_wcont(tran=tran, ret=IN_cont_reg, tmp_reg=REG_TMP0, arg_lm_addr_reg=REG_TMP_BUF_LM_ADDR, dst_nwid_reg=REG_TMP2)

    @classmethod
    def _ext_graph_append_migrate(cls, state: EFAProgram.State) -> None:
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

        cls._macro_calc_dst(tran=tran, IN_sht_desc_lm_addr_reg=REG_SHT_DESC_LM_ADDR, IN_key_reg=OB_KEY, OUT_lane_desc_lm_off_reg=REG_TMP0, OUT_bucket_desc_lm_off_reg=REG_TMP1, OUT_dst_nwid_reg=REG_TMP2, fn_name=FN_NAME)

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
    def macro_ext_graph_get_with_offset(cls, tran: EFAProgram.Transition, IN_sht_desc_lm_addr_reg: str, IN_key_reg: str, IN_offset_reg: str, IN_cont_reg: str, tmp_reg0: str, tmp_reg1: str, tmp_reg2: str, cls_name: str, fn_name: str) -> None:
        """
        """
        CLS_NAME = cls_name
        FN_NAME = fn_name
        REG_SHT_DESC_LM_ADDR = IN_sht_desc_lm_addr_reg
        REG_KEY = IN_key_reg
        REG_OFFSET = IN_offset_reg
        REG_TMP0 = tmp_reg0
        REG_TMP1 = tmp_reg1
        REG_TMP2 = tmp_reg2

        # hash
        cls._macro_calc_dst(tran=tran, IN_sht_desc_lm_addr_reg=REG_SHT_DESC_LM_ADDR, IN_key_reg=REG_KEY, OUT_lane_desc_lm_off_reg=REG_TMP0, OUT_bucket_desc_lm_off_reg=REG_TMP1, OUT_dst_nwid_reg=REG_TMP2, fn_name=FN_NAME)

        tran.writeAction(f"lshift_or {REG_TMP1} {REG_TMP0} {32}")  # combine LANE_DESC_LM_OFFSET(0:31) | BUCKET_DESC_LM_OFFSET(32:63)

        # call
        SHTLane.ext_graph_get_next_wcont(tran=tran, cont_reg=IN_cont_reg, tmp_reg=REG_TMP1, desc_lm_offset_reg=REG_TMP0, key_reg=REG_KEY, offset_reg=REG_OFFSET, dst_nwid_reg=REG_TMP2)

    @classmethod
    def _ext_graph_get_next(cls, state: EFAProgram.State) -> None:
        """
        X8 - SHT_DESC_LM_OFFSET
        X9 - KEY
        X10 - OFFSET
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._ext_graph_get_next.__name__

        OB_SHT_DESC_LM_OFFSET = 'X8'
        OB_KEY = 'X9'
        OB_OFFSET = 'X10'

        REG_SHT_DESC_LM_ADDR = 'X16'
        REG_TMP0 = 'X17'
        REG_TMP1 = 'X18'
        REG_TMP2 = 'X19'

        tran = cls.tran_ext_graph_get_next
        if tran is None:
            return
        cls.tran_label_ext_graph_get_next = tran.getLabel()

        # calculate lm addr
        tran.writeAction(f"add {OB_SHT_DESC_LM_OFFSET} {'X7'} {REG_SHT_DESC_LM_ADDR}")

        # hash
        cls._macro_calc_dst(tran=tran, IN_sht_desc_lm_addr_reg=REG_SHT_DESC_LM_ADDR, IN_key_reg=OB_KEY, OUT_lane_desc_lm_off_reg=REG_TMP0, OUT_bucket_desc_lm_off_reg=REG_TMP1, OUT_dst_nwid_reg=REG_TMP2, fn_name=FN_NAME)

        tran.writeAction(f"lshift_or {REG_TMP1} {REG_TMP0} {32}")  # combine LANE_DESC_LM_OFFSET(0:31) | BUCKET_DESC_LM_OFFSET(32:63)

        # call
        SHTLane.ext_graph_get_next_wcont(tran=tran, cont_reg='X1', tmp_reg=REG_TMP1, desc_lm_offset_reg=REG_TMP0, key_reg=OB_KEY, offset_reg=OB_OFFSET, dst_nwid_reg=REG_TMP2)
        tran.writeAction("yield_terminate")

    @classmethod
    def macro_ext_graph_get_addr(cls, tran: EFAProgram.Transition, IN_sht_desc_lm_addr_reg: str, IN_key_reg: str, IN_cont_reg: str, tmp_reg0: str, tmp_reg1: str, tmp_reg2: str, cls_name: str, fn_name: str) -> None:
        """
        """
        CLS_NAME = cls_name
        FN_NAME = fn_name
        REG_SHT_DESC_LM_ADDR = IN_sht_desc_lm_addr_reg
        REG_KEY = IN_key_reg
        REG_TMP0 = tmp_reg0
        REG_TMP1 = tmp_reg1
        REG_TMP2 = tmp_reg2

        # hash
        cls._macro_calc_dst(tran=tran, IN_sht_desc_lm_addr_reg=REG_SHT_DESC_LM_ADDR, IN_key_reg=REG_KEY, OUT_lane_desc_lm_off_reg=REG_TMP0, OUT_bucket_desc_lm_off_reg=REG_TMP1, OUT_dst_nwid_reg=REG_TMP2, fn_name=FN_NAME)

        tran.writeAction(f"lshift_or {REG_TMP1} {REG_TMP0} {32}")  # combine LANE_DESC_LM_OFFSET(0:31) | BUCKET_DESC_LM_OFFSET(32:63)

        # call
        SHTLane.ext_graph_get_addr_wcont(tran=tran, cont_reg=IN_cont_reg, tmp_reg=REG_TMP1, desc_lm_offset_reg=REG_TMP0, key_reg=REG_KEY, dst_nwid_reg=REG_TMP2)

    @classmethod
    def _ext_graph_get_addr(cls, state: EFAProgram.State) -> None:
        """
        X8 - SHT_DESC_LM_OFFSET
        X9 - KEY
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._ext_graph_get_addr.__name__

        OB_SHT_DESC_LM_OFFSET = 'X8'
        OB_KEY = 'X9'

        REG_SHT_DESC_LM_ADDR = 'X16'
        REG_TMP0 = 'X17'
        REG_TMP1 = 'X18'
        REG_TMP2 = 'X19'

        tran = cls.tran_ext_graph_get_addr
        if tran is None:
            return
        cls.tran_label_ext_graph_get_addr = tran.getLabel()

        # calculate lm addr
        tran.writeAction(f"add {OB_SHT_DESC_LM_OFFSET} {'X7'} {REG_SHT_DESC_LM_ADDR}")

        # hash
        cls._macro_calc_dst(tran=tran, IN_sht_desc_lm_addr_reg=REG_SHT_DESC_LM_ADDR, IN_key_reg=OB_KEY, OUT_lane_desc_lm_off_reg=REG_TMP0, OUT_bucket_desc_lm_off_reg=REG_TMP1, OUT_dst_nwid_reg=REG_TMP2, fn_name=FN_NAME)

        tran.writeAction(f"lshift_or {REG_TMP1} {REG_TMP0} {32}")  # combine LANE_DESC_LM_OFFSET(0:31) | BUCKET_DESC_LM_OFFSET(32:63)

        # call
        SHTLane.ext_graph_get_addr_wcont(tran=tran, cont_reg='X1', tmp_reg=REG_TMP1, desc_lm_offset_reg=REG_TMP0, key_reg=OB_KEY, dst_nwid_reg=REG_TMP2)
        tran.writeAction("yield_terminate")

    @classmethod
    def _get_with_offset(cls, state: EFAProgram.State) -> None:
        """
        X8 - SHT_DESC_LM_OFFSET
        X9 - KEY
        X10 - OFFSET
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._get_with_offset.__name__

        OB_SHT_DESC_LM_OFFSET = 'X8'
        OB_KEY = 'X9'
        OB_OFFSET = 'X10'

        REG_SHT_DESC_LM_ADDR = 'X16'
        REG_TMP0 = 'X17'
        REG_TMP1 = 'X18'
        REG_TMP2 = 'X19'

        tran = cls.tran_get_with_offset
        if tran is None:
            return
        cls.tran_label_get_with_offset = tran.getLabel()

        # calculate lm addr
        tran.writeAction(f"add {OB_SHT_DESC_LM_OFFSET} {'X7'} {REG_SHT_DESC_LM_ADDR}")

        # hash
        cls._macro_calc_dst(tran=tran, IN_sht_desc_lm_addr_reg=REG_SHT_DESC_LM_ADDR, IN_key_reg=OB_KEY, OUT_lane_desc_lm_off_reg=REG_TMP0, OUT_bucket_desc_lm_off_reg=REG_TMP1, OUT_dst_nwid_reg=REG_TMP2, fn_name=FN_NAME)

        tran.writeAction(f"lshift_or {REG_TMP1} {REG_TMP0} {32}")  # combine LANE_DESC_LM_OFFSET(0:31) | BUCKET_DESC_LM_OFFSET(32:63)

        # call
        SHTLane.get_with_offset_wcont(tran=tran, cont_reg='X1', tmp_reg=REG_TMP1, desc_lm_offset_reg=REG_TMP0, key_reg=OB_KEY, offset_reg=OB_OFFSET, dst_nwid_reg=REG_TMP2)
        tran.writeAction("yield_terminate")

    @classmethod
    def _update_with_offset(cls, state: EFAProgram.State) -> None:
        """
        X8  - SHT_DESC_LM_OFFSET(0:31) | TMP_BUF_LM_OFFSET(32:63)
        X9  - KEY
        X10 - OFFSET
        X11 ~ X15 - VALUES
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._update_with_offset.__name__

        OB_SHT_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET = "X8"
        OB_KEY = "X9"
        OB_OFFSET = "X10"
        OB_VAL = "X11"
        MAX_VAL_NUM_WORDS = 5

        REG_SHT_DESC_LM_ADDR = "X16"
        REG_TMP_BUF_LM_ADDR = "X17"
        REG_TMP0 = "X18"
        REG_TMP1 = "X19"
        REG_TMP2 = "X20"

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_update_with_offset
        if tran is None:
            return
        cls.tran_label_update_with_offset = tran.getLabel()

        """==================== TRAN - entry ===================="""
        # calculate lm addr
        tran.writeAction(f"lshift {OB_SHT_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET} {REG_SHT_DESC_LM_ADDR} {32}")
        tran.writeAction(f"rshift {REG_SHT_DESC_LM_ADDR} {REG_SHT_DESC_LM_ADDR} {32}")
        tran.writeAction(f"rshift {OB_SHT_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET} {REG_TMP_BUF_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_SHT_DESC_LM_ADDR} {'X7'} {REG_SHT_DESC_LM_ADDR}")
        tran.writeAction(f"add {REG_TMP_BUF_LM_ADDR} {'X7'} {REG_TMP_BUF_LM_ADDR}")

        # hash
        cls._macro_calc_dst(tran=tran, IN_sht_desc_lm_addr_reg=REG_SHT_DESC_LM_ADDR, IN_key_reg=OB_KEY, OUT_lane_desc_lm_off_reg=REG_TMP0, OUT_bucket_desc_lm_off_reg=REG_TMP1, OUT_dst_nwid_reg=REG_TMP2, fn_name=FN_NAME)

        # write to LM buf for calling
        tran.writeAction(f"lshift_or {REG_TMP1} {REG_TMP0} {32}")  # combine LANE_DESC_LM_OFFSET(0:31) | BUCKET_DESC_LM_OFFSET(32:63)
        tran.writeAction(f"move {REG_TMP0} {0}({REG_TMP_BUF_LM_ADDR}) 0 8")

        # extract the number of value operands along with key
        tran.writeAction(f"rshift {'X2'} {REG_TMP0} {20}")
        tran.writeAction(f"andi {REG_TMP0} {REG_TMP0} {0b111}")
        tran.writeAction(f"addi {REG_TMP0} {REG_TMP0} {1}")  # add 1 for key
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: number of operands for key, mask & val = %lu' {'X0'} {REG_TMP0}")

        # copy key and values to LM buf for calling
        tran.writeAction(f"addi {REG_TMP_BUF_LM_ADDR} {REG_TMP1} {cls.WORD_SIZE}")
        tran.writeAction(f"bcopy_ops {OB_KEY} {REG_TMP1} {REG_TMP0}")

        # calling with the proper number of operands
        # mininum 4 words: X8, X9, X10, X11
        for i in range(4, 8 + 1):
            tran.writeAction(f"beqi {REG_TMP0} {i - 1} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send{i}'}")
        tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: shouldn't reach here!' {'X0'}")
        for i in range(4, 8 + 1):
            SHTLane.update_with_offset_wcont(tran=tran, cont_reg='X1', tmp_reg0=REG_TMP1, arg_lm_addr_reg=REG_TMP_BUF_LM_ADDR, arg_lm_words=i, dst_nwid_reg=REG_TMP2, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-LB-send{i}')
            tran.writeAction("yield_terminate")


    @classmethod
    def _get_with_mask(cls, state: EFAProgram.State) -> None:
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
        cls._macro_calc_dst(tran=tran, IN_sht_desc_lm_addr_reg=REG_SHT_DESC_LM_ADDR, IN_key_reg=OB_KEY, OUT_lane_desc_lm_off_reg=REG_TMP0, OUT_bucket_desc_lm_off_reg=REG_TMP1, OUT_dst_nwid_reg=REG_TMP2, fn_name=FN_NAME)

        tran.writeAction(f"lshift_or {REG_TMP1} {REG_TMP0} {32}")  # combine LANE_DESC_LM_OFFSET(0:31) | BUCKET_DESC_LM_OFFSET(32:63)

        # call
        SHTLane.get_with_mask_64_wcont(tran=tran, cont_reg='X1', tmp_reg=REG_TMP1, desc_lm_offset_reg=REG_TMP0, key_reg=OB_KEY, mask_reg=OB_MASK, dst_nwid_reg=REG_TMP2)
        tran.writeAction("yield_terminate")

    @classmethod
    def _update_with_mask(cls, state: EFAProgram.State) -> None:
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
        cls._macro_calc_dst(tran=tran, IN_sht_desc_lm_addr_reg=REG_SHT_DESC_LM_ADDR, IN_key_reg=OB_KEY, OUT_lane_desc_lm_off_reg=REG_TMP0, OUT_bucket_desc_lm_off_reg=REG_TMP1, OUT_dst_nwid_reg=REG_TMP2, fn_name=FN_NAME)

        # write to LM buf for calling
        tran.writeAction(f"lshift_or {REG_TMP1} {REG_TMP0} {32}")  # combine LANE_DESC_LM_OFFSET(0:31) | BUCKET_DESC_LM_OFFSET(32:63)
        tran.writeAction(f"move {REG_TMP0} {0}({REG_TMP_BUF_LM_ADDR}) 0 8")

        # extract the number of value operands along with key
        tran.writeAction(f"rshift {'X2'} {REG_TMP0} {20}")
        tran.writeAction(f"andi {REG_TMP0} {REG_TMP0} {0b111}")
        tran.writeAction(f"addi {REG_TMP0} {REG_TMP0} {1}")  # add 1 for key
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: number of operands for key, mask & val = %lu' {'X0'} {REG_TMP0}")

        # copy key and values to LM buf for calling
        tran.writeAction(f"addi {REG_TMP_BUF_LM_ADDR} {REG_TMP1} {cls.WORD_SIZE}")
        tran.writeAction(f"bcopy_ops {OB_KEY} {REG_TMP1} {REG_TMP0}")

        # calling with the proper number of operands
        # mininum 4 words: X8, X9, X10, X11
        for i in range(4, 8 + 1):
            tran.writeAction(f"beqi {REG_TMP0} {i - 1} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send{i}'}")
        tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: shouldn't reach here!' {'X0'}")
        for i in range(4, 8 + 1):
            SHTLane.update_with_mask_64_wcont(tran=tran, cont_reg='X1', tmp_reg0=REG_TMP1, arg_lm_addr_reg=REG_TMP_BUF_LM_ADDR, arg_lm_words=i, dst_nwid_reg=REG_TMP2, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-LB-send{i}')
            tran.writeAction("yield_terminate")

    @classmethod
    def _get_iterators(cls, state: EFAProgram.State) -> None:
        """
         X8 - SHT_DESC_LM_OFFSET
         X9 - ITER_DRAM_ADDR
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._get_iterators.__name__

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_get_iterators
        if tran is None:
            return
        cls.tran_label_get_iterators = tran.getLabel()

        """******************** THREAD - get_iterators ********************"""
        REG_SHT_DESC_LM_ADDR = 'X16'
        REG_START_NWID = 'X17'
        REG_END_NWID = 'X18'
        REG_LANE_DESC_LM_OFFSET = 'X19'

        """==================== TRAN - ENTRY ===================="""
        OB_SHT_DESC_LM_OFFSET = 'X8'
        OB_ITER_DRAM_ADDR = 'X9'

        tran.writeAction(f"add {OB_SHT_DESC_LM_OFFSET} {'X7'} {REG_SHT_DESC_LM_ADDR}")
        tran.writeAction(f"move {cls.SHT_DESC_STURCT_OFF_START_NWID}({REG_SHT_DESC_LM_ADDR}) {REG_START_NWID} 0 4")  # start nwid
        tran.writeAction(f"move {cls.SHT_DESC_STURCT_OFF_NUM_ALLOC_LANES}({REG_SHT_DESC_LM_ADDR}) {REG_END_NWID} 0 4")  # num lane
        tran.writeAction(f"add {REG_START_NWID} {REG_END_NWID} {REG_END_NWID}")
        tran.writeAction(f"subi {REG_END_NWID} {REG_END_NWID} {1}")
        tran.writeAction(f"move {cls.SHT_DESC_STURCT_OFF_LANE_DESC_LM_OFFSET}({REG_SHT_DESC_LM_ADDR}) {REG_LANE_DESC_LM_OFFSET} 0 4")  # lane desc lm offset

        tran.writeAction(f"sli {REG_END_NWID} {REG_END_NWID} {32}")
        SHTExtBroadcast.get_iterators_broadcast_wcont(tran=tran, ret='X1', tmp_reg=REG_SHT_DESC_LM_ADDR, iters_start_dram_addr_reg=OB_ITER_DRAM_ADDR, lane_desc_lm_offset_reg=REG_LANE_DESC_LM_OFFSET, val2__end_nwid_reg=REG_END_NWID, dst_nwid_reg=REG_START_NWID)

        tran.writeAction("yieldt")

    @classmethod
    def _get_with_random(cls, state: EFAProgram.State) -> None:
        """
        X8 - SHT_DESC_LM_OFFSET
        X9 - RAND_NUM
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._get_with_random.__name__

        OB_SHT_DESC_LM_OFFSET = 'X8'
        OB_RAND_NUM = 'X9'

        REG_SHT_DESC_LM_ADDR = 'X16'
        REG_TMP0 = 'X17'
        REG_TMP1 = 'X18'
        REG_TMP2 = 'X19'

        tran = cls.tran_get_with_random
        if tran is None:
            return
        cls.tran_label_get_with_random = tran.getLabel()

        # calculate lm addr
        tran.writeAction(f"add {OB_SHT_DESC_LM_OFFSET} {'X7'} {REG_SHT_DESC_LM_ADDR}")

        # hash
        cls._macro_calc_dst(tran=tran, IN_sht_desc_lm_addr_reg=REG_SHT_DESC_LM_ADDR, IN_key_reg=OB_RAND_NUM, OUT_lane_desc_lm_off_reg=REG_TMP0, OUT_bucket_desc_lm_off_reg=REG_TMP1, OUT_dst_nwid_reg=REG_TMP2, fn_name=FN_NAME, no_hash=True)

        tran.writeAction(f"lshift_or {REG_TMP1} {REG_TMP0} {32}")  # combine LANE_DESC_LM_OFFSET(0:31) | BUCKET_DESC_LM_OFFSET(32:63)

        # call
        SHTLane.get_with_random_wcont(tran=tran, ret='X1', tmp_reg=REG_TMP1, desc_lm_offset_reg=REG_TMP0, rand_reg=OB_RAND_NUM, dst_nwid_reg=REG_TMP2)
        tran.writeAction("yieldt")

    @classmethod
    def _get_next(cls, state: EFAProgram.State) -> None:
        """
        X8 - LANE_DESC_LM_OFFSET[0:31] | BUCKET_DESC_LM_OFFSET[32:63]
        X9 - NWID[0:31] | CUR_POSITION[32:63]
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._get_next.__name__

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_get_next
        if tran is None:
            return
        cls.tran_label_get_next = tran.getLabel()

        """******************** THREAD - get_iterators ********************"""
        REG_DST_NWID = 'X16'
        REG_TMP0 = 'X17'

        """==================== TRAN - ENTRY ===================="""
        OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET = "X8"
        OB_NWID__CUR_POSITION = "X9"

        tran.writeAction(f"sli {OB_NWID__CUR_POSITION} {REG_DST_NWID} {32}")
        tran.writeAction(f"sri {REG_DST_NWID} {REG_DST_NWID} {32}")
        SHTLane.get_next_wcont(tran=tran, ret='X1', tmp_reg=REG_TMP0, iter_word0_reg=OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET, iter_word1_reg=OB_NWID__CUR_POSITION, dst_nwid_reg=REG_DST_NWID)
        tran.writeAction("yieldt")

    @classmethod
    def _get_next_split(cls, state: EFAProgram.State) -> None:
        """
        X8  - LANE_DESC_LM_OFFSET[0:31] | BUCKET_DESC_LM_OFFSET[32:63]
        X9  - NWID[0:31] | CUR_POSITION[32:63]
        X10 - (KEY, ADDR) CONTINUATION
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._get_next_split.__name__

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_get_next_split
        if tran is None:
            return
        cls.tran_label_get_next_split = tran.getLabel()

        """******************** THREAD - get_iterators ********************"""
        REG_DST_NWID = 'X16'
        REG_TMP0 = 'X17'

        """==================== TRAN - ENTRY ===================="""
        OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET = "X8"
        OB_NWID__CUR_POSITION = "X9"
        OB_KEY_ADDR_CONT = "X10"

        tran.writeAction(f"sli {OB_NWID__CUR_POSITION} {REG_DST_NWID} {32}")
        tran.writeAction(f"sri {REG_DST_NWID} {REG_DST_NWID} {32}")
        SHTLane.get_next_split_wcont(tran=tran, ret='X1', tmp_reg=REG_TMP0, iter_word0_reg=OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET, iter_word1_reg=OB_NWID__CUR_POSITION, key_addr_cont_reg=OB_KEY_ADDR_CONT, dst_nwid_reg=REG_DST_NWID)
        tran.writeAction("yieldt")


class SHTLane:
    """
    struct SHTLaneDesc {
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
    // -------- EXTENSION --------
    // for next SHT
        WORD NUM_ALLOC_LANES(0:31) | START_NWID(32:63);
        WORD LANE_DESC_LM_OFFSET(0:31) | BUCKETS_PER_LANE(32:63);
        WORD ENTRIES_PER_BUCKET(0:31) | VAL_NUM_WORDS(32:63);
    }
    """

    @classmethod
    def setup(cls, state: EFAProgram.State, enable_ext=True, big_endian=False, debug=False) -> None:
        cls.ENABLE_EXT = enable_ext
        cls.WORD_SIZE = 8
        cls.KEY_SIZE = 8
        cls.LM_BUF_SIZE = 64

        cls.LANE_DESC_SIZE = 3 * cls.WORD_SIZE
        if not big_endian:
            # LITTLE ENDIAN
            cls.LANE_DESC_STURCT_OFF_NUM_ALLOC_LANES = 0  # 4 bytes
            cls.LANE_DESC_STURCT_OFF_START_NWID = 4  # 4 bytes
            cls.LANE_DESC_STURCT_OFF_LANE_DESC_LM_OFFSET = 8  # 4 bytes
            cls.LANE_DESC_STURCT_OFF_BUCKETS_PER_LANE = 12  # 4 bytes
            cls.LANE_DESC_STURCT_OFF_ENTRIES_PER_BUCKET = 16  # 4 bytes
            cls.LANE_DESC_STURCT_OFF_VAL_NUM_WORDS = 20  # 4 bytes
        else:
            # BIG ENDIAN
            cls.LANE_DESC_STURCT_OFF_START_NWID = 0  # 4 bytes
            cls.LANE_DESC_STURCT_OFF_NUM_ALLOC_LANES = 4  # 4 bytes
            cls.LANE_DESC_STURCT_OFF_BUCKETS_PER_LANE = 8  # 4 bytes
            cls.LANE_DESC_STURCT_OFF_LANE_DESC_LM_OFFSET = 12  # 4 bytes
            cls.LANE_DESC_STURCT_OFF_VAL_NUM_WORDS = 16  # 4 bytes
            cls.LANE_DESC_STURCT_OFF_ENTRIES_PER_BUCKET = 20  # 4 bytes

        cls.BUCKET_DESC_SIZE = 11 * cls.WORD_SIZE
        cls.BUCKET_DESC_STURCT_OFF_LOCK = 0  # 4 bytes
        cls.BUCKET_DESC_STURCT_OFF_ENTRY_COUNT = 4  # 4 bytes
        cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR = 8  # 8 bytes
        cls.BUCKET_DESC_STURCT_OFF_DRAM_VAL_START_ADDR = 16  # 8 bytes
        cls.BUCKET_DESC_STURCT_OFF_LM_BUF = 24  # 64 bytes

        cls.EXT_LANE_DESC_SIZE = 3 * cls.WORD_SIZE
        if not big_endian:
            # LITTLE ENDIAN
            cls.EXT_LANE_DESC_STURCT_OFF_NUM_ALLOC_LANES = cls.LANE_DESC_SIZE + 0  # 4 bytes
            cls.EXT_LANE_DESC_STURCT_OFF_START_NWID = cls.LANE_DESC_SIZE + 4  # 4 bytes
            cls.EXT_LANE_DESC_STURCT_OFF_LANE_DESC_LM_OFFSET = cls.LANE_DESC_SIZE + 8  # 4 bytes
            cls.EXT_LANE_DESC_STURCT_OFF_BUCKETS_PER_LANE = cls.LANE_DESC_SIZE + 12  # 4 bytes
            cls.EXT_LANE_DESC_STURCT_OFF_ENTRIES_PER_BUCKET = cls.LANE_DESC_SIZE + 16  # 4 bytes
            cls.EXT_LANE_DESC_STURCT_OFF_VAL_NUM_WORDS = cls.LANE_DESC_SIZE + 20  # 4 bytes
        else:
            # BIG ENDIAN
            cls.EXT_LANE_DESC_STURCT_OFF_START_NWID = cls.LANE_DESC_SIZE + 0  # 4 bytes
            cls.EXT_LANE_DESC_STURCT_OFF_NUM_ALLOC_LANES = cls.LANE_DESC_SIZE + 4  # 4 bytes
            cls.EXT_LANE_DESC_STURCT_OFF_BUCKETS_PER_LANE = cls.LANE_DESC_SIZE + 8  # 4 bytes
            cls.EXT_LANE_DESC_STURCT_OFF_LANE_DESC_LM_OFFSET = cls.LANE_DESC_SIZE + 12  # 4 bytes
            cls.EXT_LANE_DESC_STURCT_OFF_VAL_NUM_WORDS = cls.LANE_DESC_SIZE + 16  # 4 bytes
            cls.EXT_LANE_DESC_STURCT_OFF_ENTRIES_PER_BUCKET = cls.LANE_DESC_SIZE + 20  # 4 bytes

        cls.DEBUG = debug
        cls.lock = sht_macros.MRSWLock(atomic=False, debug=debug)

        CLS_NAME = cls.__name__
        cls.tran_initialize = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-initialize-TR")
        cls.tran_update = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-update-TR")
        cls.tran_update_with_mask_8 = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-update_with_mask_8-TR")
        cls.tran_update_with_mask_64 = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-update_with_mask_64-TR")
        cls.tran_update_with_offset = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-update_with_offset-TR")
        cls.tran_get = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-get-TR")
        cls.tran_get_with_mask_8 = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-get_with_mask_8-TR")
        cls.tran_get_with_mask_64 = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-get_with_mask_64-TR")
        cls.tran_get_with_offset = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-get_with_offset-TR")
        cls.tran_get_with_random = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-get_with_random-TR")
        # cls.tran_delete = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-delete-TR")
        cls.tran_get_iterators = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-get_iterators-TR")
        cls.tran_get_next = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-get_next-TR")
        cls.tran_get_next_split = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-get_next_split-TR")
        if cls.ENABLE_EXT:
            cls.tran_ext_graph_append = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-ext_graph_append-TR")
            cls.tran_ext_graph_append_migrate = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-ext_graph_append_migrate-TR")
            cls.tran_ext_graph_get_next = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-ext_graph_get_next-TR")
            cls.tran_ext_graph_get_addr = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-ext_graph_get_word_cnt-TR")

        # TODO: code injection
        # Memcpy.setup(state, debug=debug)
        cls._initialize(state)
        cls._update(state)
        cls._update_with_mask_8(state)
        cls._update_with_mask_64(state)
        cls._update_with_offset(state)
        cls._get(state)
        cls._get_with_mask_8(state)
        cls._get_with_mask_64(state)
        cls._get_with_offset(state)
        cls._get_with_random(state)
        # cls._delete(state)
        cls._get_iterators(state)
        cls._get_next(state)
        cls._get_next_split(state)
        if cls.ENABLE_EXT:
            cls._ext_graph_append(state)
            cls._ext_graph_append_migrate(state)
            cls._ext_graph_get_next(state)
            cls._ext_graph_get_addr(state)

    @classmethod
    def _initialize(cls, state: EFAProgram.State):
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
        REG_TMP2 = "X22"
        REG_TMP3 = "X23"
        REG_DESC_TOTAL_SIZE = "X24"

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_initialize
        if tran is None:
            return
        cls.tran_label_initialize = tran.getLabel()

        """==================== TRAN - entry ===================="""
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] INIT: start, lane dram start addr = 0x%lx' {'X0'} {OB_LANE_DRAM_START_ADDR}")

        tran.writeAction(f"lshift {OB_LANE_DESC_LM_OFFSET__BUCKETS_PER_LANE} {REG_CUR_LM_ADDR} {32}")
        tran.writeAction(f"rshift {REG_CUR_LM_ADDR} {REG_CUR_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_CUR_LM_ADDR} {'X7'} {REG_CUR_LM_ADDR}")

        # ---- copy operands ----
        tran.writeAction(f"move {OB_NUM_ALLOC_LANES__START_NWID} {0}({REG_CUR_LM_ADDR}) 0 8")
        tran.writeAction(f"move {OB_LANE_DESC_LM_OFFSET__BUCKETS_PER_LANE} {cls.WORD_SIZE}({REG_CUR_LM_ADDR}) 0 8")
        tran.writeAction(f"move {OB_ENTRIES_PER_BUCKET__VAL_NUM_WORDS} {cls.WORD_SIZE * 2}({REG_CUR_LM_ADDR}) 0 8")

        # ----- check if used ext -----
        if cls.ENABLE_EXT:
            # get number of operands
            tran.writeAction(f"rshift {'X2'} {REG_TMP2} {20}")
            tran.writeAction(f"andi {REG_TMP2} {REG_TMP2} {0b111}")
            tran.writeAction(f"mov_imm2reg {REG_DESC_TOTAL_SIZE} {cls.LANE_DESC_SIZE + cls.EXT_LANE_DESC_SIZE}")
            tran.writeAction(f"bgti {REG_TMP2} {2} {f'{CLS_NAME}-{FN_NAME}-TR-LB-start_init'}")
            tran.writeAction(f"mov_imm2reg {REG_DESC_TOTAL_SIZE} {cls.LANE_DESC_SIZE}")  # no ext
        else:
            tran.writeAction(f"mov_imm2reg {REG_DESC_TOTAL_SIZE} {cls.LANE_DESC_SIZE}")

        # ----- init lane desc -----
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-start_init'}: mov_imm2reg {REG_TMP0} {cls.LANE_DESC_SIZE}")
        tran.writeAction(f"add {REG_CUR_LM_ADDR} {REG_TMP0} {REG_CUR_LM_ADDR}")
        tran.writeAction(f"addi {OB_LANE_DRAM_START_ADDR} {REG_CUR_KEY_DRAM_ADDR} {0}")

        tran.writeAction(f"lshift {OB_ENTRIES_PER_BUCKET__VAL_NUM_WORDS} {REG_TMP0} {32}")
        tran.writeAction(f"rshift {REG_TMP0} {REG_TMP0} {32}")  # REG_TMP0 => ENTRIES_PER_BUCKET
        tran.writeAction(f"lshift {REG_TMP0} {REG_CUR_VAL_DRAM_ADDR} {int(math.log2(cls.WORD_SIZE))}")
        tran.writeAction(f"add {REG_CUR_VAL_DRAM_ADDR} {REG_CUR_KEY_DRAM_ADDR} {REG_CUR_VAL_DRAM_ADDR}")

        tran.writeAction(f"rshift {OB_ENTRIES_PER_BUCKET__VAL_NUM_WORDS} {REG_TMP1} {32}")  # REG_TMP1 => VAL_NUM_WORDS
        tran.writeAction(f"addi {REG_TMP1} {REG_TMP1} {1}")  # REG_TMP1 => KEY_NUM_WORD + VAL_NUM_WORDS
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

        if cls.ENABLE_EXT:
            tran.writeAction(f"blei {REG_TMP2} {2} {f'{CLS_NAME}-{FN_NAME}-TR-LB-done_init'}")
            # ---- copy ext operands ----
            if cls.DEBUG:
                tran.writeAction(f"sub {REG_CUR_LM_ADDR} {'X7'} {REG_TMP0}")
                tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: ext sht desc lm offset = 0x%lx' {'X0'} {REG_TMP0}")
            tran.writeAction(f"move {OB_EXT__NUM_ALLOC_LANES__START_NWID} {cls.WORD_SIZE * 0}({REG_CUR_LM_ADDR}) 0 8")
            tran.writeAction(f"move {OB_EXT__LANE_DESC_LM_OFFSET__BUCKETS_PER_LANE} {cls.WORD_SIZE * 1}({REG_CUR_LM_ADDR}) 0 8")
            tran.writeAction(f"move {OB_EXT__ENTRIES_PER_BUCKET__VAL_NUM_WORDS} {cls.WORD_SIZE * 2}({REG_CUR_LM_ADDR}) 0 8")

        # ----- return -----
        sht_macros.return_wreg(tran=tran, cont_reg='X1', tmp_reg=REG_TMP0, arg_reg0="X0", arg_reg1=REG_DESC_TOTAL_SIZE, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-LB-done_init')  # return format: (NWID, DESC_TOTAL_SIZE)
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] INIT: done' {'X0'}")
        tran.writeAction("yield_terminate")

    @classmethod
    def initialize(cls, tran: EFAProgram.Transition, ret: int, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, dst_nwid_reg: str = 'X0', branch_label="") -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_initialize.getLabel(), ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=7, branch_label=branch_label)

    @classmethod
    def initialize_wcont(cls, tran: EFAProgram.Transition, ret: str, tmp_reg0: str, arg_lm_addr_reg: str, dst_nwid_reg: str = 'X0', branch_label="") -> None:
        sht_macros.call_wlm_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_initialize.getLabel(), cont_reg=ret, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=7, branch_label=branch_label)

    @classmethod
    def initialize_without_ext(cls, tran: EFAProgram.Transition, ret: int, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, dst_nwid_reg: str = 'X0', branch_label="") -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_initialize.getLabel(), ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=4, branch_label=branch_label)

    @classmethod
    def initialize_without_ext_wcont(cls, tran: EFAProgram.Transition, ret: str, tmp_reg0: str, arg_lm_addr_reg: str, dst_nwid_reg: str = 'X0', branch_label="") -> None:
        sht_macros.call_wlm_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_initialize.getLabel(), cont_reg=ret, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=4, branch_label=branch_label)

    @classmethod
    def _update(cls, state: EFAProgram.State):
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
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: lock admitted, TID = %lu' {'X0'} {'TID'}")

        # calc desc lm addr
        tran.writeAction(f"lshift {OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET} {REG_LANE_DESC_LM_ADDR} {32}")
        tran.writeAction(f"rshift {REG_LANE_DESC_LM_ADDR} {REG_LANE_DESC_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_LANE_DESC_LM_ADDR} {'X7'} {REG_LANE_DESC_LM_ADDR}")

        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: REG_LANE_DESC_LM_ADDR = 0x%lx, REG_BUCKET_DESC_LM_ADDR = 0x%lx' {'X0'} {REG_LANE_DESC_LM_ADDR} {REG_BUCKET_DESC_LM_ADDR}")

        # copy ob regs
        tran.writeAction(f"addi {OB_KEY} {REG_KEY} {0}")
        # save cont
        tran.writeAction(f"addi {'X1'} {REG_CONT} {0}")

        # load desc
        tran.writeAction(f"addi {REG_BUCKET_DESC_LM_ADDR} {REG_BUCKET_BUF_LM_ADDR} {cls.BUCKET_DESC_STURCT_OFF_LM_BUF}")

        # extract num_elem_op
        # since there is an offset of 2 in the encoding, the desc & key counts are skipped
        tran.writeAction(f"rshift {'X2'} {REG_NUM_VAL_OP} {20}")
        tran.writeAction(f"andi {REG_NUM_VAL_OP} {REG_NUM_VAL_OP} {0b111}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: number of val operands = %lu' {'X0'} {REG_NUM_VAL_OP}")
        # copy val to buffer
        tran.writeAction(f"bcopy_ops {OB_VAL} {REG_BUCKET_BUF_LM_ADDR} {REG_NUM_VAL_OP}")

        tran.writeAction(f"move {cls.BUCKET_DESC_STURCT_OFF_ENTRY_COUNT}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP1} 0 4")  # tmp1 => entry_count

        """----- Empty Bucket -----"""
        # ----- if entry count is zero, write directly -----
        tran.writeAction(f"bgti {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-setup_send_ld'}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: empty bucket, writing without search' {'X0'}")
        # update entry count
        tran.writeAction(f"addi {REG_TMP1} {REG_TMP1} {1}")
        tran.writeAction(f"move {REG_TMP1} {cls.BUCKET_DESC_STURCT_OFF_ENTRY_COUNT}({REG_BUCKET_DESC_LM_ADDR}) 0 4")

        tran.writeAction(f"mov_imm2reg {REG_LD_CONCURRENCY} {0}")
        tran.writeAction(f"mov_imm2reg {REG_ST_CONCURRENCY} {2}")
        tran.writeAction(f"move {cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_KEY_WR_ADDR} 0 8")
        tran.writeAction(f"move {cls.BUCKET_DESC_STURCT_OFF_DRAM_VAL_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_VAL_WR_ADDR} 0 8")
        sht_macros.dram_write_reg_ret(tran=tran, addr_reg=REG_KEY_WR_ADDR, ret_tran_label=tran_key_st_ret.getLabel(), tmp_reg=REG_TMP2, arg_reg0=REG_KEY)
        # calling with the proper number of operands
        for i in range(1, MAX_VAL_NUM_WORDS + 1):
            tran.writeAction(f"beqi {REG_NUM_VAL_OP} {i} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_val_{i}'}")
        tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: shouldn't reach here!' {'X0'}")
        for i in range(1, MAX_VAL_NUM_WORDS + 1):
            sht_macros.dram_write_lm_ret(tran=tran, addr_reg=REG_VAL_WR_ADDR, ret_tran_label=tran_key_st_ret.getLabel(), tmp_reg=REG_TMP2, arg_lm_addr_reg=REG_BUCKET_BUF_LM_ADDR, arg_lm_words=i, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-LB-send_val_{i}')
            if cls.DEBUG:
                tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: writing {i} words value' {'X0'}")
            tran.writeAction("yield")

        """----- Filled Bucket -----"""
        # ----- already have entires, send load entries -----
        # init
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-setup_send_ld'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_LAST_LOAD_ADDR} 0 8")  # tmp3 => key load start address
        tran.writeAction(f"mov_imm2reg {REG_LD_CONCURRENCY} {0}")
        tran.writeAction(f"mov_imm2reg {REG_ST_CONCURRENCY} {-1}")

        tran.writeAction(f"blei {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_done'}")  # tmp1 => entry_count
        sht_macros.dram_read_ret(tran=tran, addr_reg=REG_LAST_LOAD_ADDR, ret_tran_label=tran_key_ld_ret.getLabel(), tmp_reg=REG_TMP2, arg_lm_words=8, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-LB-send_ld')
        tran.writeAction(f"addi {REG_LD_CONCURRENCY} {REG_LD_CONCURRENCY} {1}")  # concurrency++
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: loading, DRAM addr = 0x%lx' {'X0'} {REG_LAST_LOAD_ADDR}")
        # check if number of valid entries in the send is greater than 8
        tran.writeAction(f"bgti {REG_TMP1} {64 // cls.KEY_SIZE} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}")
        # last send, retain last send addr & valid size
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: all loads sent' {'X0'}")
        tran.writeAction(f"addi {REG_TMP1} {REG_LAST_LOAD_EFFECTIVE_WORDS} {0}")  # record last load effective size
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
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: load from 0x%lx returns, mlp = %lu' {'X0'} {OB_LD_RET_ADDR} {REG_LD_CONCURRENCY}")
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
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: last in-flight load & store finished, terminating... TID = %lu' {'X0'} {'TID'}")
        # unlocked already, no need to unlock
        # return format: (key, val_addr)
        sht_macros.return_wreg(tran=tran_key_ld_ret, cont_reg=REG_CONT, tmp_reg=REG_TMP0, arg_reg0=REG_KEY, arg_reg1=REG_VAL_WR_ADDR)
        tran_key_ld_ret.writeAction("yield_terminate")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}: yield")

        """----- Check returned keys -----"""
        # check if return is matched with (last) send address
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}: bne {OB_LD_RET_ADDR} {REG_LAST_LOAD_ADDR} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{7 * cls.KEY_SIZE}'}")  # tmp3 => last send addr
        # if it is the last send, branch to check only the valid entries
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: tail send load returns, num entries = %lu' {'X0'} {REG_LAST_LOAD_EFFECTIVE_WORDS}")  # tmp2 => last send num valid entries
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
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: no matched entry found' {'X0'}")
        # check if there is space at the end of the allocation area
        tran_key_ld_ret.writeAction(f"move {cls.LANE_DESC_STURCT_OFF_ENTRIES_PER_BUCKET}({REG_LANE_DESC_LM_ADDR}) {REG_TMP1} 0 4")  # REG_TMP1 => num_alloc_entries
        tran_key_ld_ret.writeAction(f"move {cls.BUCKET_DESC_STURCT_OFF_ENTRY_COUNT}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP2} 0 4")  # REG_TMP2 => entry count
        tran_key_ld_ret.writeAction(f"blt {REG_TMP2} {REG_TMP1} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-new_entry'}")
        # -> out of space!
        tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: bucket full, add FAILED!' {'X0'}")
        # if cls.DEBUG:
        #     tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: bucket full, add FAILED!' {'X0'}")
        # return format: (key, val_addr)
        tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_TMP1} {0}")  # indicate failue with addr == 0
        sht_macros.return_wreg(tran=tran_key_ld_ret, cont_reg=REG_CONT, tmp_reg=REG_TMP0, arg_reg0=REG_KEY, arg_reg1=REG_TMP1)
        # sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, 'X0', REG_TMP3)  # for debug
        cls.lock.write_end(tran_key_ld_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        tran_key_ld_ret.writeAction("yield_terminate")  # only if running out of space!
        # -> new entry
        # calculate the address of the key
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-new_entry'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_KEY_WR_ADDR} 0 8")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: storing in a new entry' {'X0'}")
        tran_key_ld_ret.writeAction(f"lshift {REG_TMP2} {REG_TMP1} {int(math.log2(cls.KEY_SIZE))}")
        tran_key_ld_ret.writeAction(f"add {REG_KEY_WR_ADDR} {REG_TMP1} {REG_KEY_WR_ADDR}")
        # store key
        sht_macros.dram_write_reg_ret(tran=tran_key_ld_ret, addr_reg=REG_KEY_WR_ADDR, ret_tran_label=tran_key_st_ret.getLabel(), tmp_reg=REG_TMP0, arg_reg0=REG_KEY)
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: sending key write to addr = 0x%lx' {'X0'} {REG_KEY_WR_ADDR}")
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
        tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: shouldn't reach here!' {'X0'}")
        for i in range(1, MAX_VAL_NUM_WORDS + 1):
            sht_macros.dram_write_lm_ret(tran=tran_key_ld_ret, addr_reg=REG_VAL_WR_ADDR, ret_tran_label=tran_key_st_ret.getLabel(), tmp_reg=REG_TMP0, arg_lm_addr_reg=REG_BUCKET_BUF_LM_ADDR, arg_lm_words=i, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-nomatch_send_val_{i}')
            if cls.DEBUG:
                tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: writing {i} words value' {'X0'}")
            tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-nomatch_send_val_done'}")
        # count up the entries
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-nomatch_send_val_done'}: addi {REG_TMP2} {REG_TMP2} {1}")
        tran_key_ld_ret.writeAction(f"move {REG_TMP2} {cls.BUCKET_DESC_STURCT_OFF_ENTRY_COUNT}({REG_BUCKET_DESC_LM_ADDR}) 0 4")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: sending value write to addr = 0x%lx' {'X0'} {REG_VAL_WR_ADDR}")
        tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_ST_CONCURRENCY} {2}")  # mark value written & all loads done
        # -> wait for in-flight load to come back
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait_ld'}: yield")

        """-> matched"""
        for i in range(0, 8):
            # calculate the entry index from key address
            tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{i * cls.KEY_SIZE}_match'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP1} 0 8")
            if cls.DEBUG:
                tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: matched at word offset {i}' {'X0'}")
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
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: sending write to addr = 0x%lx' {'X0'} {REG_VAL_WR_ADDR}")
        # calling with the proper number of operands
        for i in range(1, MAX_VAL_NUM_WORDS + 1):
            tran_key_ld_ret.writeAction(f"beqi {REG_NUM_VAL_OP} {i} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_{i}'}")
        tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: shouldn't reach here!' {'X0'}")
        for i in range(1, MAX_VAL_NUM_WORDS + 1):
            # tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_{i}'}: send_dmlm_wret {REG_VAL_WR_ADDR} {tran_key_st_ret.getLabel()} {REG_BUCKET_BUF_LM_ADDR} {i}")
            sht_macros.dram_write_lm_ret(tran=tran_key_ld_ret, addr_reg=REG_VAL_WR_ADDR, ret_tran_label=tran_key_st_ret.getLabel(), tmp_reg=REG_TMP0, arg_lm_addr_reg=REG_BUCKET_BUF_LM_ADDR, arg_lm_words=i, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_{i}')
            if cls.DEBUG:
                tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: writing {i} words value' {'X0'}")
            tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_done'}")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_done'}: mov_imm2reg {REG_ST_CONCURRENCY} {1}")  # mark value written
        tran_key_ld_ret.writeAction("yield")

        """==================== TRAN - store key val return ===================="""
        tran_key_st_ret.writeAction(f"subi {REG_ST_CONCURRENCY} {REG_ST_CONCURRENCY} {1}")
        tran_key_st_ret.writeAction(f"bgti {REG_ST_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_st_ret-LB-wait'}")
        tran_key_st_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_st_ret-LB-ld_wait'}")
        if cls.DEBUG:
            tran_key_st_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: write to 0x%lx returns & no load waiting, terminating... TID = %lu' {'X0'} {'X8'} {'TID'}")
        cls.lock.write_end(tran_key_st_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        # return format: (key, val_addr)
        sht_macros.return_wreg(tran=tran_key_st_ret, cont_reg=REG_CONT, tmp_reg=REG_TMP0, arg_reg0=REG_KEY, arg_reg1=REG_VAL_WR_ADDR)
        # sht_macros.return_wreg(tran_key_st_ret, REG_CONT, 'X0', REG_VAL_WR_ADDR)  # debug
        tran_key_st_ret.writeAction("yield_terminate")
        tran_key_st_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_st_ret-LB-ld_wait'}: addi {REG_TMP1} {REG_TMP1} {0}")  # dummy instruction
        cls.lock.write_end(tran_key_st_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        if cls.DEBUG:
            tran_key_st_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: write to 0x%lx returns & all stores done, waiting loads return...' {'X0'} {'X8'}")
        tran_key_st_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_st_ret-LB-wait'}: yield")

    @classmethod
    def update(cls, tran: EFAProgram.Transition, ret: int, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, arg_lm_words: int, dst_nwid_reg: str = 'X0', branch_label: str = "") -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_update.getLabel(), ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=arg_lm_words, branch_label=branch_label)

    @classmethod
    def update_wcont(cls, tran: EFAProgram.Transition, ret: str, tmp_reg0: str, arg_lm_addr_reg: str, arg_lm_words: int, dst_nwid_reg: str = 'X0', branch_label: str = "") -> None:
        sht_macros.call_wlm_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_update.getLabel(), cont_reg=ret, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=arg_lm_words, branch_label=branch_label)

    @classmethod
    def _get(cls, state: EFAProgram.State):
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
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: lock admitted, TID = %lu' {'X0'} {'TID'}")

        # calc desc lm addr
        tran.writeAction(f"lshift {OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET} {REG_LANE_DESC_LM_ADDR} {32}")
        tran.writeAction(f"rshift {REG_LANE_DESC_LM_ADDR} {REG_LANE_DESC_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_LANE_DESC_LM_ADDR} {'X7'} {REG_LANE_DESC_LM_ADDR}")

        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: REG_LANE_DESC_LM_ADDR = 0x%lx, REG_BUCKET_DESC_LM_ADDR = 0x%lx' {'X0'} {REG_LANE_DESC_LM_ADDR} {REG_BUCKET_DESC_LM_ADDR}")

        # copy ob regs
        tran.writeAction(f"addi {OB_KEY} {REG_KEY} {0}")
        # save cont
        tran.writeAction(f"addi {'X1'} {REG_CONT} {0}")

        # load desc
        tran.writeAction(f"addi {REG_BUCKET_DESC_LM_ADDR} {REG_BUCKET_BUF_LM_ADDR} {cls.BUCKET_DESC_STURCT_OFF_LM_BUF}")
        tran.writeAction(f"move {cls.LANE_DESC_STURCT_OFF_VAL_NUM_WORDS}({REG_LANE_DESC_LM_ADDR}) {REG_NUM_VAL_WORDS} 0 4")

        tran.writeAction(f"move {cls.BUCKET_DESC_STURCT_OFF_ENTRY_COUNT}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP1} 0 4")  # tmp1 => entry_count

        """----- Empty Bucket -----"""
        # ----- if entry count is zero, return not found -----
        tran.writeAction(f"bgti {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-setup_send_ld'}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: empty bucket, return without search' {'X0'}")
        # return format: (key, 0)
        # tran.writeAction(f"mov_imm2reg {REG_TMP1} {0}")  # indicate failue
        sht_macros.return_wreg(tran=tran, cont_reg=REG_CONT, tmp_reg=REG_TMP2, arg_reg0=REG_KEY, arg_reg1=REG_TMP1)
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
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: loading, DRAM addr = 0x%lx' {'X0'} {REG_LAST_LOAD_ADDR}")
        # check if number of valid entries in the send is greater than 8
        tran.writeAction(f"bgti {REG_TMP1} {64 // cls.KEY_SIZE} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}")
        # last send, retain last send addr & valid size
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: all loads sent' {'X0'}")
        tran.writeAction(f"addi {REG_TMP1} {REG_LAST_LOAD_EFFECTIVE_WORDS} {0}")  # record last load effective size
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
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: load from 0x%lx returns, mlp = %lu' {'X0'} {OB_LD_RET_ADDR} {REG_LD_CONCURRENCY}")
        tran_key_ld_ret.writeAction(f"subi {REG_LD_CONCURRENCY} {REG_LD_CONCURRENCY} {1}")
        # wait the load value return processed before terminating
        tran_key_ld_ret.writeAction(f"beqi {REG_MATCH_STATUS} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}")
        tran_key_ld_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}")
        tran_key_ld_ret.writeAction(f"beqi {REG_MATCH_STATUS} {1} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: last in-flight load key & value returned already, terminating... TID = %lu' {'X0'} {'TID'}")
        # unlocked already, no need to unlock
        tran_key_ld_ret.writeAction("yield_terminate")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}: yield")

        """----- Check returned keys -----"""
        # check if return is matched with (last) send address
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}: bne {OB_LD_RET_ADDR} {REG_LAST_LOAD_ADDR} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{7 * cls.KEY_SIZE}'}")  # tmp3 => last send addr
        # if it is the last send, branch to check only the valid entries
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: tail send load returns, num entries = %lu' {'X0'} {REG_LAST_LOAD_EFFECTIVE_WORDS}")  # tmp2 => last send num valid entries
        for i in range(8, 0, -1):
            tran_key_ld_ret.writeAction(f"beqi {REG_LAST_LOAD_EFFECTIVE_WORDS} {i} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}'}")
        # match return data
        for i in range(8, 0, -1):
            tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}'}: beq {f'X{i + 8 - 1}'} {REG_KEY} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}_match'}")

        """-> not matched (fall through)"""
        tran_key_ld_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait_ld'}")
        # from here, all in-flight loads are done & no match found
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: no matched entry found' {'X0'}")
        # return format: (key, 0)
        tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_TMP1} {0}")  # indicate failue
        sht_macros.return_wreg(tran=tran_key_ld_ret, cont_reg=REG_CONT, tmp_reg=REG_TMP2, arg_reg0=REG_KEY, arg_reg1=REG_TMP1)
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
                tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: matched at word offset {i}' {'X0'}")
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
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: sending load to addr = 0x%lx' {'X0'} {REG_VAL_RD_ADDR}")

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
                tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: loading {i} words value' {'X0'}")
            tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_done'}")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_done'}: mov_imm2reg {REG_MATCH_STATUS} {1}")  # mark key found
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: key found and value load issued' {'X0'}")
        tran_key_ld_ret.writeAction("yield")

        """==================== TRAN - load val return ===================="""
        if cls.DEBUG:
            tran_val_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: value load returns' {'X0'}")
        tran_val_ld_ret.writeAction(f"mov_imm2reg {REG_MATCH_STATUS} {2}")  # mark value returned
        cls.lock.read_end(tran_val_ld_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)

        # return format (key, addr, val0~5)
        tran_val_ld_ret.writeAction(f"move {REG_KEY} 0({REG_BUCKET_BUF_LM_ADDR}) 0 8")  # key
        tran_val_ld_ret.writeAction(f"move {REG_VAL_RD_ADDR} 8({REG_BUCKET_BUF_LM_ADDR}) 0 8")  # value address
        tran_val_ld_ret.writeAction(f"addi {REG_BUCKET_BUF_LM_ADDR} {REG_TMP1} {cls.WORD_SIZE * 2}")
        tran_val_ld_ret.writeAction(f"bcopy_ops {'X8'} {REG_TMP1} {REG_TMP2}")

        for i in range(1, 7):
            tran_val_ld_ret.writeAction(f"beqi {REG_NUM_VAL_WORDS} {i} {f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-ret_val_{i}'}")
        tran_val_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-ret_val_6'}")  # for value words > 6, load the first 6 words
        for i in range(1, 7):
            sht_macros.return_wlm(tran=tran_val_ld_ret, cont_reg=REG_CONT, tmp_reg=REG_TMP1, arg_lm_addr_reg=REG_BUCKET_BUF_LM_ADDR, arg_lm_words=(i + 2), branch_label=f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-ret_val_{i}')
            tran_val_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-ret_val_done'}")

        tran_val_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-ret_val_done'}: bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-wait_after_ld_val'}")
        tran_val_ld_ret.writeAction("yield_terminate")
        tran_val_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-wait_after_ld_val'}: yield")

    @classmethod
    def _get_fast(cls, state: EFAProgram.State):
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
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: lock admitted, TID = %lu' {'X0'} {'TID'}")
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: REG_BUCKET_DESC_LM_ADDR = 0x%lx' {'X0'} {REG_BUCKET_DESC_LM_ADDR}")

        # copy ob regs
        tran.writeAction(f"addi {OB_KEY} {REG_KEY} {0}")
        # save cont
        tran.writeAction(f"addi {'X1'} {REG_CONT} {0}")

        # load desc
        # tran.writeAction(f"move {cls.BUCKET_DESC_STURCT_OFF_LM_BUF_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_BUF_LM_ADDR} 0 8")
        tran.writeAction(f"move {cls.LANE_DESC_STURCT_OFF_VAL_NUM_WORDS}({REG_LANE_DESC_LM_ADDR}) {REG_NUM_VAL_WORDS} 0 4")

        tran.writeAction(f"move {cls.BUCKET_DESC_STURCT_OFF_ENTRY_COUNT}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP1} 0 4")  # tmp1 => entry_count

        """----- Empty Bucket -----"""
        # ----- if entry count is zero, return not found -----
        tran.writeAction(f"bgti {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-setup_send_ld'}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: empty bucket, return without search' {'X0'}")
        # return format: (key, 0)
        # tran.writeAction(f"mov_imm2reg {REG_TMP1} {0}")  # indicate failue
        sht_macros.return_wreg(tran=tran, cont_reg=REG_CONT, tmp_reg=REG_TMP2, arg_reg0=REG_KEY, arg_reg1=REG_TMP1)
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
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: loading, DRAM addr = 0x%lx' {'X0'} {REG_LAST_LOAD_ADDR}")
        # check if number of valid entries in the send is greater than 8
        tran.writeAction(f"bgti {REG_TMP1} {64 // cls.KEY_SIZE} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}")
        # last send, retain last send addr & valid size
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: all loads sent' {'X0'}")
        tran.writeAction(f"addi {REG_TMP1} {REG_LAST_LOAD_EFFECTIVE_WORDS} {0}")  # record last load effective size
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
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: load from 0x%lx returns, mlp = %lu' {'X0'} {OB_LD_RET_ADDR} {REG_LD_CONCURRENCY}")
        tran_key_ld_ret.writeAction(f"subi {REG_LD_CONCURRENCY} {REG_LD_CONCURRENCY} {1}")
        tran_key_ld_ret.writeAction(f"beqi {REG_MATCH_STATUS} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}")
        tran_key_ld_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: last in-flight load key & key found already, terminating... TID = %lu' {'X0'} {'TID'}")
        # unlocked already, no need to unlock
        tran_key_ld_ret.writeAction("yield_terminate")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}: yield")

        """----- Check returned keys -----"""
        # check if return is matched with (last) send address
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}: bne {OB_LD_RET_ADDR} {REG_LAST_LOAD_ADDR} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{7 * cls.KEY_SIZE}'}")  # tmp3 => last send addr
        # if it is the last send, branch to check only the valid entries
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: tail send load returns, num entries = %lu' {'X0'} {REG_LAST_LOAD_EFFECTIVE_WORDS}")  # tmp2 => last send num valid entries
        for i in range(8, 0, -1):
            tran_key_ld_ret.writeAction(f"beqi {REG_LAST_LOAD_EFFECTIVE_WORDS} {i} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}'}")
        # match return data
        for i in range(8, 0, -1):
            tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}'}: beq {f'X{i + 8 - 1}'} {REG_KEY} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}_match'}")

        """-> not matched (fall through)"""
        tran_key_ld_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait_ld'}")
        # from here, all in-flight loads are done & no match found
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: no matched entry found' {'X0'}")
        # return format: (key, 0)
        tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_TMP1} {0}")  # indicate failue
        sht_macros.return_wreg(tran=tran_key_ld_ret, cont_reg=REG_CONT, tmp_reg=REG_TMP2, arg_reg0=REG_KEY, arg_reg1=REG_TMP1)
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
                tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: matched at word offset {i}' {'X0'}")
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
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: sending load to addr = 0x%lx' {'X0'} {REG_VAL_RD_ADDR}")

        # calling with the proper number of operands
        for i in range(1, 9):
            tran_key_ld_ret.writeAction(f"beqi {REG_NUM_VAL_WORDS} {i} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_{i}'}")
        tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_8'}")  # for value words > 8, load the first 8 words
        for i in range(1, 9):
            # tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_{i}'}: send_dmlm_ld {REG_VAL_RD_ADDR} {REG_CONT} {i}")  # directly return to caller
            sht_macros.dram_read_cont(tran=tran_key_ld_ret, addr_reg=REG_VAL_RD_ADDR, cont_reg=REG_CONT, tmp_reg=REG_TMP2, arg_lm_words=i, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_{i}')
            if cls.DEBUG:
                tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: loading {i} words value' {'X0'}")
            tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_done'}")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_done'}: bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait_after_ld_val'}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: key found, bucket terminating' {'X0'}")
        cls.lock.read_end(tran_key_ld_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        tran_key_ld_ret.writeAction("yield_terminate")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait_after_ld_val'}: mov_imm2reg {REG_MATCH_STATUS} {1}")  # mark key found
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: key found, wait for rest of key loads' {'X0'}")
        cls.lock.read_end(tran_key_ld_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        tran_key_ld_ret.writeAction("yield")

    @classmethod
    def get(cls, tran: EFAProgram.Transition, ret: int, tmp_reg0: str, tmp_reg1: str, desc_lm_offset_reg: str, key_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_get.getLabel(), ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=desc_lm_offset_reg, arg_reg1=key_reg, branch_label=branch_label)

    @classmethod
    def get_wcont(cls, tran: EFAProgram.Transition, ret: str, tmp_reg: str, desc_lm_offset_reg: str, key_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_get.getLabel(), cont_reg=ret, tmp_reg=tmp_reg, arg_reg0=desc_lm_offset_reg, arg_reg1=key_reg, branch_label=branch_label)

    @classmethod
    def _delete(cls, state: EFAProgram.State):
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
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: lock admitted, TID = %lu' {'X0'} {'TID'}")

        # calc desc lm addr
        tran.writeAction(f"lshift {OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET} {REG_LANE_DESC_LM_ADDR} {32}")
        tran.writeAction(f"rshift {REG_LANE_DESC_LM_ADDR} {REG_LANE_DESC_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_LANE_DESC_LM_ADDR} {'X7'} {REG_LANE_DESC_LM_ADDR}")

        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: REG_LANE_DESC_LM_ADDR = 0x%lx, REG_BUCKET_DESC_LM_ADDR = 0x%lx' {'X0'} {REG_LANE_DESC_LM_ADDR} {REG_BUCKET_DESC_LM_ADDR}")

        # copy ob regs
        tran.writeAction(f"addi {OB_KEY} {REG_KEY} {0}")
        # save cont
        tran.writeAction(f"addi {'X1'} {REG_CONT} {0}")

        # load desc
        tran.writeAction(f"addi {REG_BUCKET_DESC_LM_ADDR} {REG_BUCKET_BUF_LM_ADDR} {cls.BUCKET_DESC_STURCT_OFF_LM_BUF}")
        tran.writeAction(f"move {cls.LANE_DESC_STURCT_OFF_VAL_NUM_WORDS}({REG_LANE_DESC_LM_ADDR}) {REG_NUM_VAL_WORDS} 0 4")

        tran.writeAction(f"move {cls.BUCKET_DESC_STURCT_OFF_ENTRY_COUNT}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP1} 0 4")  # tmp1 => entry_count

        """----- Empty Bucket -----"""
        # ----- if entry count is zero, return not found -----
        tran.writeAction(f"bgti {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-setup_send_ld'}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: empty bucket, return without search' {'X0'}")
        # return format: (key, 0)
        # tran.writeAction(f"mov_imm2reg {REG_TMP1} {0}")  # indicate failue
        sht_macros.return_wreg(tran=tran, cont_reg=REG_CONT, tmp_reg=REG_TMP2, arg_reg0=REG_KEY, arg_reg1=REG_TMP1)
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
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: loading, DRAM addr = 0x%lx' {'X0'} {REG_LAST_LOAD_ADDR}")
        # check if number of valid entries in the send is greater than 8
        tran.writeAction(f"bgti {REG_TMP1} {64 // cls.KEY_SIZE} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}")
        # last send, retain last send addr & valid size
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: all loads sent' {'X0'}")
        tran.writeAction(f"addi {REG_TMP1} {REG_LAST_LOAD_EFFECTIVE_WORDS} {0}")  # record last load effective size
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
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: load from 0x%lx returns, mlp = %lu' {'X0'} {OB_LD_RET_ADDR} {REG_LD_CONCURRENCY}")
        tran_key_ld_ret.writeAction(f"subi {REG_LD_CONCURRENCY} {REG_LD_CONCURRENCY} {1}")
        # wait the load value return processed before terminating
        tran_key_ld_ret.writeAction(f"beqi {REG_MATCH_STATUS} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}")
        tran_key_ld_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}")
        tran_key_ld_ret.writeAction(f"beqi {REG_MATCH_STATUS} {1} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: last in-flight load key & value returned already, terminating... TID = %lu' {'X0'} {'TID'}")
        # unlocked already, no need to unlock
        tran_key_ld_ret.writeAction("yield_terminate")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}: yield")

        """----- Check returned keys -----"""
        # check if return is matched with (last) send address
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}: bne {OB_LD_RET_ADDR} {REG_LAST_LOAD_ADDR} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{7 * cls.KEY_SIZE}'}")  # tmp3 => last send addr
        # if it is the last send, branch to check only the valid entries
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: tail send load returns, num entries = %lu' {'X0'} {REG_LAST_LOAD_EFFECTIVE_WORDS}")  # tmp2 => last send num valid entries
        for i in range(8, 0, -1):
            tran_key_ld_ret.writeAction(f"beqi {REG_LAST_LOAD_EFFECTIVE_WORDS} {i} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}'}")
        # match return data
        for i in range(8, 0, -1):
            tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}'}: beq {f'X{i + 8 - 1}'} {REG_KEY} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}_match'}")

        """-> not matched (fall through)"""
        tran_key_ld_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait_ld'}")
        # from here, all in-flight loads are done & no match found
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: no matched entry found' {'X0'}")
        # return format: (key, 0)
        tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_TMP1} {0}")  # indicate failue
        sht_macros.return_wreg(tran=tran_key_ld_ret, cont_reg=REG_CONT, tmp_reg=REG_TMP2, arg_reg0=REG_KEY, arg_reg1=REG_TMP1)
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
                tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: matched at word offset {i}' {'X0'}")
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
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: sending load to addr = 0x%lx' {'X0'} {REG_VAL_RD_ADDR}")

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
                tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: loading {i} words value' {'X0'}")
            tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_done'}")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_done'}: mov_imm2reg {REG_MATCH_STATUS} {1}")  # mark key found
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: key found and value load issued' {'X0'}")
        tran_key_ld_ret.writeAction("yield")

        """==================== TRAN - load val return ===================="""
        if cls.DEBUG:
            tran_val_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: value load returns' {'X0'}")
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
            sht_macros.return_wlm(tran=tran_val_ld_ret, cont_reg=REG_CONT, tmp_reg=REG_TMP1, arg_lm_addr_reg=REG_BUCKET_BUF_LM_ADDR, arg_lm_words=(i + 3), branch_label=f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-ret_val_{i}')
            tran_val_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-ret_val_done'}")

        tran_val_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-ret_val_done'}: bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-wait_after_ld_val'}")
        tran_val_ld_ret.writeAction("yield_terminate")
        tran_val_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-wait_after_ld_val'}: yield")

    @classmethod
    def delete(cls, tran: EFAProgram.Transition):
        """
        TODO
        """
        pass

    @classmethod
    def _ext_graph_append(cls, state: EFAProgram.State):
        """
        Extension for Graph Abstraction Neighbor List Store
        - It uses the first word in the value to store the number of filled words in the value
        - It triggers specified plugin function (entry migration in this particular case) when the number of filled words reaches the limit

        X8 - LANE_DESC_LM_OFFSET(0:31) | BUCKET_DESC_LM_OFFSET(32:63)
        X9 - KEY
        X10 ~ X15 - Elem e

        Returns:
        X8 - KEY
        X9 - NB_LIST_DRAM_ADDR (first word is the number of words in the list)
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._ext_graph_append.__name__

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
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: lock admitted, TID = %lu' {'X0'} {'TID'}")

        # calc desc lm addr
        tran.writeAction(f"lshift {OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET} {REG_LANE_DESC_LM_ADDR} {32}")
        tran.writeAction(f"rshift {REG_LANE_DESC_LM_ADDR} {REG_LANE_DESC_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_LANE_DESC_LM_ADDR} {'X7'} {REG_LANE_DESC_LM_ADDR}")

        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: REG_LANE_DESC_LM_ADDR = 0x%lx, REG_BUCKET_DESC_LM_ADDR = 0x%lx' {'X0'} {REG_LANE_DESC_LM_ADDR} {REG_BUCKET_DESC_LM_ADDR}")

        # copy ob regs
        tran.writeAction(f"addi {OB_KEY} {REG_KEY} {0}")
        # save cont
        tran.writeAction(f"addi {'X1'} {REG_CONT} {0}")

        # load desc
        tran.writeAction(f"addi {REG_BUCKET_DESC_LM_ADDR} {REG_BUCKET_BUF_LM_ADDR} {cls.BUCKET_DESC_STURCT_OFF_LM_BUF}")
        # LM Buffer Layout (8 words) - |?|?|?...|
        #                                 ^REG_BUCKET_BUF_LM_ADDR
        tran.writeAction(f"addi {REG_BUCKET_BUF_LM_ADDR} {REG_BUCKET_BUF_LM_ADDR} {cls.WORD_SIZE}")  # WARNING: reserve the first word for call redirection

        # extract num_elem_op
        # since there is an offset of 2 in the encoding, the desc & key counts are skipped
        tran.writeAction(f"rshift {'X2'} {REG_NUM_VAL_OP} {20}")
        tran.writeAction(f"andi {REG_NUM_VAL_OP} {REG_NUM_VAL_OP} {0b111}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: number of val operands = %lu' {'X0'} {REG_NUM_VAL_OP}")

        # copy val to buffer, using the number of val operands
        # LM Buffer Layout (8 words) - |?|?|VALs...|
        #                                 ^REG_BUCKET_BUF_LM_ADDR
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
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: empty bucket, writing without search' {'X0'}")
        # filling word counter
        # LM Buffer Layout (8 words) - |?|WC|VALs...|
        #                                 ^REG_BUCKET_BUF_LM_ADDR
        tran.writeAction(f"move {REG_NUM_VAL_OP} {0}({REG_BUCKET_BUF_LM_ADDR}) 0 8")  # set word counter for the value to 0 in the buffer
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: writing word counter = %lu' {'X0'} {REG_NUM_VAL_OP}")
        # update entry count
        tran.writeAction(f"addi {REG_TMP1} {REG_TMP1} {1}")
        tran.writeAction(f"move {REG_TMP1} {cls.BUCKET_DESC_STURCT_OFF_ENTRY_COUNT}({REG_BUCKET_DESC_LM_ADDR}) 0 4")
        # prep
        tran.writeAction(f"mov_imm2reg {REG_LD_CONCURRENCY} {0}")
        tran.writeAction(f"mov_imm2reg {REG_ST_CONCURRENCY} {2}")
        tran.writeAction(f"move {cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_KEY_WR_ADDR} 0 8")
        tran.writeAction(f"move {cls.BUCKET_DESC_STURCT_OFF_DRAM_VAL_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_VAL_WR_ADDR} 0 8")
        # write key
        sht_macros.dram_write_reg_ret(tran=tran, addr_reg=REG_KEY_WR_ADDR, ret_tran_label=tran_key_val_st_ret.getLabel(), tmp_reg=REG_TMP2, arg_reg0=REG_KEY)

        # calling with the proper number of operands
        for i in range(1, MAX_VAL_NUM_WORDS + 1):
            tran.writeAction(f"beqi {REG_NUM_VAL_OP} {i} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_val_{i}'}")
        tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: shouldn't reach here!' {'X0'}")
        for i in range(1, MAX_VAL_NUM_WORDS + 1):
            sht_macros.dram_write_lm_ret(tran=tran, addr_reg=REG_VAL_WR_ADDR, ret_tran_label=tran_key_val_st_ret.getLabel(), tmp_reg=REG_TMP2, arg_lm_addr_reg=REG_BUCKET_BUF_LM_ADDR, arg_lm_words=(i + 1), branch_label=f'{CLS_NAME}-{FN_NAME}-TR-LB-send_val_{i}')
            if cls.DEBUG:
                tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: writing {i} words value' {'X0'}")
            tran.writeAction("yield")

        # ----- input size larger than value size, mark redirected and redirect call -----
        # LM Buffer Layout (8 words) - |?|?|VALs...|
        #                               ^REG_BUCKET_BUF_LM_ADDR
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-oob_redirect'}: subi {REG_BUCKET_BUF_LM_ADDR} {REG_BUCKET_BUF_LM_ADDR} {cls.WORD_SIZE}")  # WARNING: release the reserved word
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: input size greater than allocated, redirecting call...' {'X0'}")
        tran.writeAction(f"move {cls.LANE_DESC_STURCT_OFF_BUCKETS_PER_LANE}({REG_LANE_DESC_LM_ADDR}) {REG_TMP3} 0 4")
        tran.writeAction(f"muli {REG_TMP3} {REG_TMP3} {cls.BUCKET_DESC_SIZE}")  # REG_TMP3 => size of all lane desc
        tran.writeAction(f"addi {REG_TMP3} {REG_TMP3} {cls.LANE_DESC_SIZE}")
        tran.writeAction(f"sub {REG_LANE_DESC_LM_ADDR} {'X7'} {REG_TMP2}")
        tran.writeAction(f"add {REG_TMP2} {REG_TMP3} {REG_TMP2}")  # REG_TMP2 => ext sht desc lm offset
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: ext sht desc lm offset = 0x%lx' {'X0'} {REG_TMP2}")
        tran.writeAction(f"sub {REG_BUCKET_BUF_LM_ADDR} {'X7'} {REG_TMP3}")  # REG_TMP3 => tmp buf lm offset
        tran.writeAction(f"lshift_or {REG_TMP3} {REG_TMP2} {32}")  # REG_TMP2 => SHT_DESC_LM_OFFSET(0:31) | TMP_BUF_LM_OFFSET(32:63)
        # LM Buffer Layout (8 words) - |SHT_DESC_LM_OFFSET(0:31) & TMP_BUF_LM_OFFSET(32:63)|KEY|VALs...|
        #                               ^REG_BUCKET_BUF_LM_ADDR
        tran.writeAction(f"move {REG_TMP2} {0}({REG_BUCKET_BUF_LM_ADDR}) 0 8")  # SHT_DESC_LM_OFFSET(0:31) | TMP_BUF_LM_OFFSET(32:63)
        tran.writeAction(f"move {REG_KEY} {cls.WORD_SIZE}({REG_BUCKET_BUF_LM_ADDR}) 0 8")  # KEY
        # call append with appropriate number of operands
        for i in range(1, MAX_VAL_NUM_WORDS + 1):
            tran.writeAction(f"beqi {REG_NUM_VAL_OP} {i} {f'{CLS_NAME}-{FN_NAME}-TR-LB-ret_val_{i}'}")
        tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: shouldn't reach here!' {'X0'}")
        for i in range(1, MAX_VAL_NUM_WORDS + 1):
            SHTExtCall.ext_graph_append_wcont(tran=tran, ret=REG_CONT, tmp_reg0=REG_TMP0, arg_lm_addr_reg=REG_BUCKET_BUF_LM_ADDR, num_val_words=i, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-LB-ret_val_{i}')
            tran.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-LB-mark_migrated'}")
        """-> mark the existing entry as migrated"""
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-mark_migrated'}: mov_imm2reg {REG_TMP0} {-1}")  # use -1 as marker of migrated
        # update entry count
        tran.writeAction(f"mov_imm2reg {REG_TMP1} {1}")
        tran.writeAction(f"move {REG_TMP1} {cls.BUCKET_DESC_STURCT_OFF_ENTRY_COUNT}({REG_BUCKET_DESC_LM_ADDR}) 0 4")
        # prep
        tran.writeAction(f"move {cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_KEY_WR_ADDR} 0 8")
        tran.writeAction(f"move {cls.BUCKET_DESC_STURCT_OFF_DRAM_VAL_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_VAL_WR_ADDR} 0 8")
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
        tran.writeAction(f"mov_imm2reg {REG_ST_CONCURRENCY} {-2}")
        tran.writeAction(f"move {REG_NUM_VAL_OP} {0}({REG_BUCKET_BUF_LM_ADDR}) 0 8")  # set word counter for the value to 0 in the buffer
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: writing word counter = %lu to LM addr = 0x%lx' {'X0'} {REG_NUM_VAL_OP} {REG_BUCKET_BUF_LM_ADDR}")

        tran.writeAction(f"blei {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_done'}")  # tmp1 => entry_count
        sht_macros.dram_read_ret(tran=tran, addr_reg=REG_LAST_LOAD_ADDR, ret_tran_label=tran_key_ld_ret.getLabel(), tmp_reg=REG_TMP2, arg_lm_words=8, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-LB-send_ld')
        tran.writeAction(f"addi {REG_LD_CONCURRENCY} {REG_LD_CONCURRENCY} {1}")  # concurrency++
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: loading, DRAM addr = 0x%lx' {'X0'} {REG_LAST_LOAD_ADDR}")
        # check if number of valid entries in the send is greater than 8
        tran.writeAction(f"bgti {REG_TMP1} {64 // cls.KEY_SIZE} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}")
        # last send, retain last send addr & valid size
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: all loads sent' {'X0'}")
        tran.writeAction(f"addi {REG_TMP1} {REG_LAST_LOAD_EFFECTIVE_WORDS} {0}")  # record last load effective size
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
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: load from 0x%lx returns, mlp = %lu' {'X0'} {OB_LD_RET_ADDR} {REG_LD_CONCURRENCY}")
        tran_key_ld_ret.writeAction(f"subi {REG_LD_CONCURRENCY} {REG_LD_CONCURRENCY} {1}")
        # POSSIBLE CONDITIONS -
        # LD_CONCURRENCY > 0: [wait for more loads]
        #   ST_CONCURRENCY == -3: [call redirected] wait
        #   ST_CONCURRENCY == -2: [not matched] to match
        #   ST_CONCURRENCY == -1: [matched] wait
        #   ST_CONCURRENCY ==  0: [all store done] wait
        #   ST_CONCURRENCY >   0: [store in progress] wait
        # LD_CONCURRENCY == 0: [last load returned]
        #   ST_CONCURRENCY == -3: [call redirected] terminate without reply
        #   ST_CONCURRENCY == -2: [not matched] to match
        #   ST_CONCURRENCY == -1: [matched] wait
        #   ST_CONCURRENCY ==  0: [all store done] terminate with reply
        #   ST_CONCURRENCY >   0: [matched] wait
        tran_key_ld_ret.writeAction(f"beqi {REG_ST_CONCURRENCY} {-2} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}")
        tran_key_ld_ret.writeAction(f"beqi {REG_ST_CONCURRENCY} {-1} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}")
        tran_key_ld_ret.writeAction(f"bgti {REG_ST_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}")
        tran_key_ld_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}")
        tran_key_ld_ret.writeAction(f"beqi {REG_ST_CONCURRENCY} {-3} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-term_no_reply'}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: last in-flight load & store finished, terminating... TID = %lu' {'X0'} {'TID'}")
        # unlocked already, no need to unlock
        # return format: (key, val_addr)
        sht_macros.return_wreg(tran=tran_key_ld_ret, cont_reg=REG_CONT, tmp_reg=REG_TMP0, arg_reg0=REG_KEY, arg_reg1=REG_VAL_WR_ADDR)
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-term_no_reply'}: yield_terminate")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}: yield")

        """----- Check returned keys -----"""
        # check if return is matched with (last) send address
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}: bne {OB_LD_RET_ADDR} {REG_LAST_LOAD_ADDR} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{7 * cls.KEY_SIZE}'}")  # tmp3 => last send addr
        # if it is the last send, branch to check only the valid entries
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: tail send load returns, num entries = %lu' {'X0'} {REG_LAST_LOAD_EFFECTIVE_WORDS}")  # tmp2 => last send num valid entries
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
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: no matched entry found' {'X0'}")
        # check if there is space at the end of the allocation area
        tran_key_ld_ret.writeAction(f"move {cls.LANE_DESC_STURCT_OFF_ENTRIES_PER_BUCKET}({REG_LANE_DESC_LM_ADDR}) {REG_TMP1} 0 4")  # REG_TMP1 => num_alloc_entries
        tran_key_ld_ret.writeAction(f"move {cls.BUCKET_DESC_STURCT_OFF_ENTRY_COUNT}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP2} 0 4")  # REG_TMP2 => entry count
        tran_key_ld_ret.writeAction(f"blt {REG_TMP2} {REG_TMP1} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-new_entry'}")
        """--> out of space!"""
        tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: bucket full, add FAILED!' {'X0'}")
        # if cls.DEBUG:
        #     tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: bucket full, add FAILED!' {'X0'}")
        # return format: (key, val_addr)
        tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_TMP1} {0}")  # indicate failue
        sht_macros.return_wreg(tran=tran_key_ld_ret, cont_reg=REG_CONT, tmp_reg=REG_TMP0, arg_reg0=REG_KEY, arg_reg1=REG_TMP1)
        # sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, 'X0', REG_TMP3)  # for debug
        cls.lock.write_end(tran_key_ld_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        tran_key_ld_ret.writeAction("yield_terminate")  # only if running out of space!
        """-> new entry"""
        # calculate the address of the key
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-new_entry'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_KEY_WR_ADDR} 0 8")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: storing in a new entry' {'X0'}")
        tran_key_ld_ret.writeAction(f"lshift {REG_TMP2} {REG_TMP1} {int(math.log2(cls.KEY_SIZE))}")
        tran_key_ld_ret.writeAction(f"add {REG_KEY_WR_ADDR} {REG_TMP1} {REG_KEY_WR_ADDR}")
        # store key
        sht_macros.dram_write_reg_ret(tran=tran_key_ld_ret, addr_reg=REG_KEY_WR_ADDR, ret_tran_label=tran_key_val_st_ret.getLabel(), tmp_reg=REG_TMP0, arg_reg0=REG_KEY)
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: sending key write to addr = 0x%lx' {'X0'} {REG_KEY_WR_ADDR}")
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
        tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: shouldn't reach here!' {'X0'}")
        for i in range(1, MAX_VAL_NUM_WORDS + 1):
            # LM Buffer Layout (8 words) - |?|REG_NUM_VAL_OP|VALs...|
            #                                 ^REG_BUCKET_BUF_LM_ADDR
            sht_macros.dram_write_lm_ret(tran=tran_key_ld_ret, addr_reg=REG_VAL_WR_ADDR, ret_tran_label=tran_key_val_st_ret.getLabel(), tmp_reg=REG_TMP0, arg_lm_addr_reg=REG_BUCKET_BUF_LM_ADDR, arg_lm_words=(i + 1), branch_label=f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-nomatch_send_val_{i}')
            if cls.DEBUG:
                tran_key_ld_ret.writeAction(f"movlr {0}({REG_BUCKET_BUF_LM_ADDR}) {REG_TMP0} 0 8")
                tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: writing {i} words value, word counter = %lu, LM addr = 0x%lx' {'X0'} {REG_TMP0} {REG_BUCKET_BUF_LM_ADDR}")
            tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-nomatch_send_val_done'}")
        # count up the entries
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-nomatch_send_val_done'}: addi {REG_TMP2} {REG_TMP2} {1}")
        tran_key_ld_ret.writeAction(f"move {REG_TMP2} {cls.BUCKET_DESC_STURCT_OFF_ENTRY_COUNT}({REG_BUCKET_DESC_LM_ADDR}) 0 4")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: sending value write to addr = 0x%lx' {'X0'} {REG_VAL_WR_ADDR}")
        tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_ST_CONCURRENCY} {2}")  # mark value written & all loads done
        # wait in-flight load to come back
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait_ld'}: yield")

        """-> matched"""
        for i in range(0, 8):
            # calculate the value index from key address
            tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{i * cls.KEY_SIZE}_match'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP1} 0 8")
            if cls.DEBUG:
                tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: matched at word offset {i}' {'X0'}")
            tran_key_ld_ret.writeAction(f"sub {OB_LD_RET_ADDR} {REG_TMP1} {REG_TMP1}")
            tran_key_ld_ret.writeAction(f"rshift {REG_TMP1} {REG_TMP1} {int(math.log2(cls.KEY_SIZE))}")
            tran_key_ld_ret.writeAction(f"addi {REG_TMP1} {REG_TMP1} {i}")  # REG_TMP1 => value index
            tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_ST_CONCURRENCY} {-1}")  # mark matched but not storing yet
            tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_load_word_cnt'}")

        # load word counter (first word of value)
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_load_word_cnt'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_VAL_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_VAL_WR_ADDR} 0 8")
        tran_key_ld_ret.writeAction(f"move {cls.LANE_DESC_STURCT_OFF_VAL_NUM_WORDS}({REG_LANE_DESC_LM_ADDR}) {REG_TMP2} 0 4")  # REG_TMP2 => value num words
        tran_key_ld_ret.writeAction(f"mul {REG_TMP2} {REG_TMP1} {REG_TMP1}")
        tran_key_ld_ret.writeAction(f"lshift {REG_TMP1} {REG_TMP1} {int(math.log2(cls.WORD_SIZE))}")
        tran_key_ld_ret.writeAction(f"add {REG_VAL_WR_ADDR} {REG_TMP1} {REG_VAL_WR_ADDR}")
        sht_macros.dram_read_ret(tran=tran_key_ld_ret, addr_reg=REG_VAL_WR_ADDR, ret_tran_label=tran_word_cnt_ld_ret.getLabel(), tmp_reg=REG_TMP0, arg_lm_words=1)
        tran_key_ld_ret.writeAction("yield")

        """==================== TRAN - load word counter return ===================="""
        # check if the entry is migrated
        if cls.DEBUG:
            tran_word_cnt_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: word counter = %lu' {'X0'} {'X8'}")
        tran_word_cnt_ld_ret.writeAction(f"beqi {'X8'} {-1} {f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-redirect'}")
        tran_word_cnt_ld_ret.writeAction(f"add {'X8'} {REG_NUM_VAL_OP} {REG_TMP1}")  # calc updated word counter
        tran_word_cnt_ld_ret.writeAction(f"bge {REG_TMP1} {REG_TMP2} {f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-migrate'}")  # check if the word counter reached (value num words - 1)

        """----- Values fit in existing entry, append -----"""
        """-> Send store updated word counter"""
        sht_macros.dram_write_reg_ret(tran=tran_word_cnt_ld_ret, addr_reg=REG_VAL_WR_ADDR, ret_tran_label=tran_key_val_st_ret.getLabel(), tmp_reg=REG_TMP0, arg_reg0=REG_TMP1)
        """-> Send store value"""
        # calculate the address of the append value
        tran_word_cnt_ld_ret.writeAction(f"lshift_add_imm {'X8'} {REG_TMP1} {int(math.log2(cls.WORD_SIZE))} {cls.WORD_SIZE}")  # skip the word counter
        tran_word_cnt_ld_ret.writeAction(f"add {REG_VAL_WR_ADDR} {REG_TMP1} {REG_TMP1}")
        # skip the word counter position for writing value
        tran_word_cnt_ld_ret.writeAction(f"addi {REG_BUCKET_BUF_LM_ADDR} {REG_TMP3} {cls.WORD_SIZE}")
        # append the value to the end of the value list
        if cls.DEBUG:
            tran_word_cnt_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: sending write to addr = 0x%lx' {'X0'} {REG_TMP1}")
        # calling with the proper number of operands
        for i in range(1, MAX_VAL_NUM_WORDS + 1):
            tran_word_cnt_ld_ret.writeAction(f"beqi {REG_NUM_VAL_OP} {i} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_{i}'}")
        tran_word_cnt_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: shouldn't reach here!' {'X0'}")
        for i in range(1, MAX_VAL_NUM_WORDS + 1):
            sht_macros.dram_write_lm_ret(tran=tran_word_cnt_ld_ret, addr_reg=REG_TMP1, ret_tran_label=tran_key_val_st_ret.getLabel(), tmp_reg=REG_TMP0, arg_lm_addr_reg=REG_TMP3, arg_lm_words=i, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_{i}')
            if cls.DEBUG:
                tran_word_cnt_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: writing {i} words value' {'X0'}")
            tran_word_cnt_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_done'}")
        tran_word_cnt_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_done'}: mov_imm2reg {REG_ST_CONCURRENCY} {2}")  # mark word counter & value written
        tran_word_cnt_ld_ret.writeAction("yield")

        """----- Values do not fit in existing entry, migrate -----"""
        # call for migration if exceeded value size
        """-> call migration function"""
        tran_word_cnt_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-migrate'}: subi {REG_BUCKET_BUF_LM_ADDR} {REG_BUCKET_BUF_LM_ADDR} {cls.WORD_SIZE}")  # WARNING: release the reserved word
        if cls.DEBUG:
            tran_word_cnt_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: migrating entry...' {'X0'}")
        # save the third and fourth word of the buffer
        tran_word_cnt_ld_ret.writeAction(f"move {cls.WORD_SIZE * 2}({REG_BUCKET_BUF_LM_ADDR}) {REG_TMP0} 0 8")  # REG_TMP0 => third word
        tran_word_cnt_ld_ret.writeAction(f"move {cls.WORD_SIZE * 3}({REG_BUCKET_BUF_LM_ADDR}) {REG_TMP1} 0 8")  # REG_TMP1 => fourth word

        # prepare migrate arguments
        tran_word_cnt_ld_ret.writeAction(f"move {cls.LANE_DESC_STURCT_OFF_BUCKETS_PER_LANE}({REG_LANE_DESC_LM_ADDR}) {REG_TMP3} 0 4")
        tran_word_cnt_ld_ret.writeAction(f"muli {REG_TMP3} {REG_TMP3} {cls.BUCKET_DESC_SIZE}")  # REG_TMP3 => size of all lane desc
        tran_word_cnt_ld_ret.writeAction(f"addi {REG_TMP3} {REG_TMP3} {cls.LANE_DESC_SIZE}")
        tran_word_cnt_ld_ret.writeAction(f"add {REG_LANE_DESC_LM_ADDR} {REG_TMP3} {REG_TMP3}")  # REG_TMP3 => ext sht desc lm addr
        # check if there is no next SHT registered, if so, reply error
        tran_word_cnt_ld_ret.writeAction(f"move {0}({REG_TMP3}) {REG_TMP2} 0 8")
        tran_word_cnt_ld_ret.writeAction(f"beqi {REG_TMP2} {0} {f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-mirgrate_not_registered'}")
        tran_word_cnt_ld_ret.writeAction(f"move {REG_VAL_WR_ADDR} {cls.WORD_SIZE * 2}({REG_BUCKET_BUF_LM_ADDR}) 0 8")  # SRC_VAL_ADDR
        tran_word_cnt_ld_ret.writeAction(f"addi {'X8'} {REG_TMP2} {1}")
        tran_word_cnt_ld_ret.writeAction(f"move {REG_TMP2} {cls.WORD_SIZE * 3}({REG_BUCKET_BUF_LM_ADDR}) 0 8")  # COPY_NUM_WORDS (X8 + 1)
        # WARNING: content of REG_KEY_WR_ADDR, REG_LAST_LOAD_ADDR, REG_LAST_LOAD_EFFECTIVE_WORDS overwritten!!!
        tran_word_cnt_ld_ret.writeAction(f"addi {'X2'} {REG_KEY_WR_ADDR} {0}")
        tran_word_cnt_ld_ret.writeAction(f"evlb {REG_KEY_WR_ADDR} {tran_migration_ret.getLabel()}")  # update return event
        SHTExt.macro_ext_graph_append_migrate(tran=tran_word_cnt_ld_ret,
                                              IN_sht_desc_lm_addr_reg=REG_TMP3, IN_tmp_buf_lm_addr_reg=REG_BUCKET_BUF_LM_ADDR,
                                              IN_key_reg=REG_KEY, IN_cont_reg=REG_KEY_WR_ADDR,
                                              tmp_reg0=REG_TMP2, tmp_reg1=REG_LAST_LOAD_ADDR, tmp_reg2=REG_LAST_LOAD_EFFECTIVE_WORDS,
                                              cls_name=CLS_NAME, fn_name=FN_NAME)
        tran_word_cnt_ld_ret.writeAction("yield")

        """----- Entry migrated, redirect call -----"""
        tran_word_cnt_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-redirect'}: subi {REG_BUCKET_BUF_LM_ADDR} {REG_BUCKET_BUF_LM_ADDR} {cls.WORD_SIZE}")  # WARNING: release the reserved word
        cls.lock.write_end(tran_word_cnt_ld_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        if cls.DEBUG:
            tran_word_cnt_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: entry already migrated, redirecting call...' {'X0'}")
        # prepare redirect arguments
        tran_word_cnt_ld_ret.writeAction(f"move {cls.LANE_DESC_STURCT_OFF_BUCKETS_PER_LANE}({REG_LANE_DESC_LM_ADDR}) {REG_TMP3} 0 4")
        tran_word_cnt_ld_ret.writeAction(f"muli {REG_TMP3} {REG_TMP3} {cls.BUCKET_DESC_SIZE}")  # REG_TMP3 => size of all bucket desc
        tran_word_cnt_ld_ret.writeAction(f"addi {REG_TMP3} {REG_TMP3} {cls.LANE_DESC_SIZE}")
        tran_word_cnt_ld_ret.writeAction(f"add {REG_LANE_DESC_LM_ADDR} {REG_TMP3} {REG_TMP3}")  # REG_TMP3 => ext sht desc lm addr
        SHTExt.macro_ext_graph_append(tran=tran_word_cnt_ld_ret,
                                       IN_sht_desc_lm_addr_reg=REG_TMP3, IN_tmp_buf_lm_addr_reg=REG_BUCKET_BUF_LM_ADDR,
                                       IN_key_reg=REG_KEY, IN_num_val_words_reg=REG_NUM_VAL_OP, IN_cont_reg=REG_CONT,
                                       tmp_reg0=REG_TMP0, tmp_reg1=REG_TMP1, tmp_reg2=REG_TMP2,
                                       finish_branch_label=f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-redirect_sent',
                                       cls_name=CLS_NAME, fn_name=FN_NAME)
        tran_word_cnt_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-redirect_sent'}: bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-wait_key_ld'}")
        tran_word_cnt_ld_ret.writeAction("yield_terminate")
        tran_word_cnt_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-wait_key_ld'}: mov_imm2reg {REG_ST_CONCURRENCY} {-3}")
        tran_word_cnt_ld_ret.writeAction("yield")

        """----- Migration Failure -----"""
        tran_word_cnt_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-mirgrate_not_registered'}: print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: migration failed, no next SHT registered!' {'X0'}")
        cls.lock.write_end(tran_word_cnt_ld_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        tran_word_cnt_ld_ret.writeAction(f"mov_imm2reg {REG_VAL_WR_ADDR} {0}")
        sht_macros.return_wreg(tran=tran_word_cnt_ld_ret, cont_reg=REG_CONT, tmp_reg=REG_TMP0, arg_reg0=REG_KEY, arg_reg1=REG_VAL_WR_ADDR)
        tran_word_cnt_ld_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-wait_key_ld'}")
        tran_word_cnt_ld_ret.writeAction("yield_terminate")

        """==================== TRAN - migrate return ===================="""
        # FIXME: check failure case
        """-> redirect append call to next sht"""
        if cls.DEBUG:
            tran_migration_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: migration complete, redirecting call...' {'X0'}")
        # restore the third and fourth word of the buffer
        tran_migration_ret.writeAction(f"move {REG_TMP0} {cls.WORD_SIZE * 2}({REG_BUCKET_BUF_LM_ADDR}) 0 8")
        tran_migration_ret.writeAction(f"move {REG_TMP1} {cls.WORD_SIZE * 3}({REG_BUCKET_BUF_LM_ADDR}) 0 8")

        SHTExt.macro_ext_graph_append(tran=tran_migration_ret,
                                       IN_sht_desc_lm_addr_reg=REG_TMP3, IN_tmp_buf_lm_addr_reg=REG_BUCKET_BUF_LM_ADDR,  # REG_TMP3 => ext sht desc lm addr, WARNING: have to guarantee REG_TMP3 is not overwritten between transitions
                                       IN_key_reg=REG_KEY, IN_num_val_words_reg=REG_NUM_VAL_OP, IN_cont_reg=REG_CONT,
                                       tmp_reg0=REG_TMP0, tmp_reg1=REG_TMP1, tmp_reg2=REG_TMP2,
                                       finish_branch_label=f'{CLS_NAME}-{FN_NAME}-TR-migration_ret-LB-mark_migrated',
                                       cls_name=CLS_NAME, fn_name=FN_NAME)

        """-> mark the existing entry as migrated"""
        tran_migration_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-migration_ret-LB-mark_migrated'}: mov_imm2reg {REG_TMP0} {-1}")  # use -1 as marker of migrated
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
            tran_key_val_st_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: write to 0x%lx returns & no load waiting, terminating... TID = %lu' {'X0'} {'X8'} {'TID'}")
        cls.lock.write_end(tran_key_val_st_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        # return format: (key, val_start_addr)
        sht_macros.return_wreg(tran=tran_key_val_st_ret, cont_reg=REG_CONT, tmp_reg=REG_TMP0, arg_reg0=REG_KEY, arg_reg1=REG_VAL_WR_ADDR)
        # sht_macros.return_wreg(tran_key_st_ret, REG_CONT, 'X0', REG_VAL_WR_ADDR)  # debug
        tran_key_val_st_ret.writeAction("yield_terminate")

        tran_key_val_st_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_val_st_ret-LB-ld_wait'}: addi {REG_TMP1} {REG_TMP1} {0}")  # FIXME: dummy instruction
        cls.lock.write_end(tran_key_val_st_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        if cls.DEBUG:
            tran_key_val_st_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: write to 0x%lx returns & all stores done, waiting loads return...' {'X0'} {'X8'}")
        tran_key_val_st_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_val_st_ret-LB-wait'}: yield")

        tran_key_val_st_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_val_st_ret-LB-ld_silent_term'}: addi {REG_TMP1} {REG_TMP1} {0}")  # FIXME: dummy instruction
        cls.lock.write_end(tran_key_val_st_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        if cls.DEBUG:
            tran_key_val_st_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: call migrated, terminating sliently... TID = %lu' {'X0'} {'TID'}")
        tran_key_val_st_ret.writeAction("yield_terminate")

    @classmethod
    def ext_graph_append(cls, tran: EFAProgram.Transition, ret: int, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, arg_lm_words: int, dst_nwid_reg: str = 'X0', branch_label: str = '') -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_ext_graph_append.getLabel(), ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=arg_lm_words, branch_label=branch_label)

    @classmethod
    def ext_graph_append_wcont(cls, tran: EFAProgram.Transition, ret: str, tmp_reg0: str, arg_lm_addr_reg: str, arg_lm_words: int, dst_nwid_reg: str = 'X0', branch_label: str = '') -> None:
        sht_macros.call_wlm_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_ext_graph_append.getLabel(), cont_reg=ret, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=arg_lm_words, branch_label=branch_label)

    @classmethod
    def _ext_graph_append_migrate(cls, state: EFAProgram.State):
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
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: lock admitted, TID = %lu' {'X0'} {'TID'}")

        # calc desc lm addr
        tran.writeAction(f"lshift {OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET} {REG_LANE_DESC_LM_ADDR} {32}")
        tran.writeAction(f"rshift {REG_LANE_DESC_LM_ADDR} {REG_LANE_DESC_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_LANE_DESC_LM_ADDR} {'X7'} {REG_LANE_DESC_LM_ADDR}")

        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: REG_LANE_DESC_LM_ADDR = 0x%lx, REG_BUCKET_DESC_LM_ADDR = 0x%lx' {'X0'} {REG_LANE_DESC_LM_ADDR} {REG_BUCKET_DESC_LM_ADDR}")

        # save cont
        tran.writeAction(f"addi {'X1'} {REG_CONT} {0}")
        tran.writeAction(f"addi {OB_KEY} {REG_KEY} {0}")

        # check if there is space at the end of the allocation area
        tran.writeAction(f"move {cls.LANE_DESC_STURCT_OFF_ENTRIES_PER_BUCKET}({REG_LANE_DESC_LM_ADDR}) {REG_TMP0} 0 4")  # REG_TMP0 => num_alloc_entries
        tran.writeAction(f"move {cls.BUCKET_DESC_STURCT_OFF_ENTRY_COUNT}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP1} 0 4")  # REG_TMP1 => entry count
        tran.writeAction(f"blt {REG_TMP1} {REG_TMP0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-new_entry'}")
        """--> out of space!"""
        tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: bucket full, add FAILED!' {'X0'}")
        # if cls.DEBUG:
        #     tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: bucket full, add FAILED!' {'X0'}")
        # return format: (key, val_addr)
        tran.writeAction(f"mov_imm2reg {REG_TMP0} {0}")  # indicate failue
        sht_macros.return_wreg(tran=tran, cont_reg=REG_CONT, tmp_reg=REG_TMP1, arg_reg0=REG_KEY, arg_reg1=REG_TMP0)
        # sht_macros.return_wreg(tran, REG_CONT, 'X0', REG_TMP3)  # for debug
        cls.lock.write_end(tran, REG_BUCKET_DESC_LM_ADDR, REG_TMP0)
        tran.writeAction("yield_terminate")  # only if running out of space!
        """-> new entry"""
        # calculate the address of the key
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-new_entry'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_KEY_WR_ADDR} 0 8")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: storing in a new entry' {'X0'}")
        tran.writeAction(f"lshift {REG_TMP1} {REG_TMP0} {int(math.log2(cls.KEY_SIZE))}")
        tran.writeAction(f"add {REG_KEY_WR_ADDR} {REG_TMP0} {REG_KEY_WR_ADDR}")
        # store key
        # tran.writeAction(f"sendr_dmlm_wret {REG_KEY_WR_ADDR} {tran_key_val_st_ret.getLabel()} {REG_KEY}")  # writing only one word
        sht_macros.dram_write_reg_ret(tran=tran, addr_reg=REG_KEY_WR_ADDR, ret_tran_label=tran_key_val_st_ret.getLabel(), tmp_reg=REG_TMP2, arg_reg0=REG_KEY)
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: sending key write to addr = 0x%lx' {'X0'} {REG_KEY_WR_ADDR}")
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
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: copying value to to dram addr = 0x%lx' {'X0'} {REG_VAL_WR_ADDR}")
        tran.writeAction(f"mov_imm2reg {REG_TMP0} {2}")  # concurrency
        tran.writeAction("yield")

        """==================== TRAN - store key val return ===================="""
        tran_key_val_st_ret.writeAction(f"subi {REG_TMP0} {REG_TMP0} {1}")
        tran_key_val_st_ret.writeAction(f"bgti {REG_TMP0} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_val_st_ret-LB-wait'}")
        # return format: (key, val_addr)
        sht_macros.return_wreg(tran=tran_key_val_st_ret, cont_reg=REG_CONT, tmp_reg=REG_TMP0, arg_reg0=REG_KEY, arg_reg1=REG_VAL_WR_ADDR)
        cls.lock.write_end(tran_key_val_st_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP0)
        tran_key_val_st_ret.writeAction("yield_terminate")
        tran_key_val_st_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_val_st_ret-LB-wait'}: yield")

    @classmethod
    def ext_graph_append_migrate(cls, tran: EFAProgram.Transition, ret: int, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = "") -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_ext_graph_append_migrate.getLabel(), ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=4, branch_label=branch_label)

    @classmethod
    def ext_graph_append_migrate_wcont(cls, tran: EFAProgram.Transition, ret: str, tmp_reg: str, arg_lm_addr_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = "") -> None:
        sht_macros.call_wlm_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_ext_graph_append_migrate.getLabel(), cont_reg=ret, tmp_reg=tmp_reg, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=4, branch_label=branch_label)

    @classmethod
    def _ext_graph_get_next(cls, state: EFAProgram.State):
        """
        Extended to support offset + call redirection

        X8  - LANE_DESC_LM_OFFSET(0:31) | BUCKET_DESC_LM_OFFSET(32:63)
        X9  - KEY
        X10 - OFFSET (in words, ignore the counter word)

        Return format:
            KEY - input KEY
            OFFSET - updated OFFSET, 0 if KEY not found, -1 if reached the end, -2 if passed the end
            (optional) ELEM0
            (optional) ELEM1
            (optional) ELEM2
            (optional) ELEM3
            (optional) ELEM4
            (optional) ELEM5
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._ext_graph_get_next.__name__

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
        tran = cls.tran_ext_graph_get_next
        if tran is None:
            return
        cls.tran_label_ext_graph_get_next = tran.getLabel()
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
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: lock admitted, TID = %lu' {'X0'} {'TID'}")

        # calc desc lm addr
        tran.writeAction(f"lshift {OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET} {REG_LANE_DESC_LM_ADDR} {32}")
        tran.writeAction(f"rshift {REG_LANE_DESC_LM_ADDR} {REG_LANE_DESC_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_LANE_DESC_LM_ADDR} {'X7'} {REG_LANE_DESC_LM_ADDR}")

        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: REG_LANE_DESC_LM_ADDR = 0x%lx, REG_BUCKET_DESC_LM_ADDR = 0x%lx' {'X0'} {REG_LANE_DESC_LM_ADDR} {REG_BUCKET_DESC_LM_ADDR}")

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
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: empty bucket, return without search' {'X0'}")
        # return format: (key, 0) - entry not found
        # tran.writeAction(f"mov_imm2reg {REG_TMP1} {0}")  # indicate failue
        sht_macros.return_wreg(tran=tran, cont_reg=REG_CONT, tmp_reg=REG_TMP2, arg_reg0=REG_KEY, arg_reg1=REG_TMP1)
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
        sht_macros.dram_read_ret(tran=tran, addr_reg=REG_LAST_LOAD_ADDR, ret_tran_label=tran_key_ld_ret.getLabel(), tmp_reg=REG_TMP2, arg_lm_words=8, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-LB-send_ld')
        tran.writeAction(f"addi {REG_LD_CONCURRENCY} {REG_LD_CONCURRENCY} {1}")  # concurrency++
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: loading, DRAM addr = 0x%lx' {'X0'} {REG_LAST_LOAD_ADDR}")
        # check if number of valid entries in the send is greater than 8
        tran.writeAction(f"bgti {REG_TMP1} {64 // cls.KEY_SIZE} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}")
        # last send, retain last send addr & valid size
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: all loads sent' {'X0'}")
        tran.writeAction(f"addi {REG_TMP1} {REG_LAST_LOAD_EFFECTIVE_WORDS} {0}")  # record last load effective size
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
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: load from 0x%lx returns, mlp = %lu' {'X0'} {OB_LD_RET_ADDR} {REG_LD_CONCURRENCY}")
        tran_key_ld_ret.writeAction(f"subi {REG_LD_CONCURRENCY} {REG_LD_CONCURRENCY} {1}")
        # wait the load value return processed before terminating
        tran_key_ld_ret.writeAction(f"beqi {REG_MATCH_STATUS} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}")
        tran_key_ld_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}")
        tran_key_ld_ret.writeAction(f"beqi {REG_MATCH_STATUS} {1} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: last in-flight load key & value returned already, terminating... TID = %lu' {'X0'} {'TID'}")
        # unlocked already, no need to unlock
        tran_key_ld_ret.writeAction("yield_terminate")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}: yield")

        """----- Check returned keys -----"""
        # check if return is matched with (last) send address
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}: bne {OB_LD_RET_ADDR} {REG_LAST_LOAD_ADDR} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{7 * cls.KEY_SIZE}'}")  # tmp3 => last send addr
        # if it is the last send, branch to check only the valid entries
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: tail send load returns, num entries = %lu' {'X0'} {REG_LAST_LOAD_EFFECTIVE_WORDS}")  # tmp2 => last send num valid entries
        for i in range(8, 0, -1):
            tran_key_ld_ret.writeAction(f"beqi {REG_LAST_LOAD_EFFECTIVE_WORDS} {i} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}'}")
        # match return data
        for i in range(8, 0, -1):
            tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}'}: beq {f'X{i + 8 - 1}'} {REG_KEY} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}_match'}")

        """-> not matched (fall through)"""
        tran_key_ld_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait_ld'}")
        # from here, all in-flight loads are done & no match found
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: no matched entry found' {'X0'}")
        # return format: (key, 0) - entry not found
        tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_TMP1} {0}")  # indicate failue
        sht_macros.return_wreg(tran=tran_key_ld_ret, cont_reg=REG_CONT, tmp_reg=REG_TMP2, arg_reg0=REG_KEY, arg_reg1=REG_TMP1)
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
                tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: matched at word offset {i}' {'X0'}")
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
        sht_macros.dram_read_ret(tran=tran_key_ld_ret, addr_reg=REG_VAL_RD_ADDR, ret_tran_label=tran_word_cnt_ld_ret.getLabel(), tmp_reg=REG_TMP3, arg_lm_words=1)
        tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_MATCH_STATUS} {1}")  # mark key found
        tran_key_ld_ret.writeAction("yield")

        """==================== TRAN - load word counter return ===================="""
        # FIXME: check if there is no next SHT registered, if so, reply error
        if cls.DEBUG:
            tran_word_cnt_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: word counter = %lu' {'X0'} {'X8'}")
        # check if the entry is migrated
        tran_word_cnt_ld_ret.writeAction(f"beqi {'X8'} {-1} {f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-redirect'}")
        # bundary check
        tran_word_cnt_ld_ret.writeAction(f"bge {REG_OFFSET} {'X8'} {f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-out_of_bound'}")
        # handle less equal than 8 words case
        tran_word_cnt_ld_ret.writeAction(f"sub {'X8'} {REG_OFFSET} {REG_NUM_VAL_WORDS}")  # WARNING: REG_NUM_VAL_WORDS represents the number of valid words adjusted for the offset

        """----- Send load value -----"""
        tran_word_cnt_ld_ret.writeAction(f"lshift_add_imm {REG_OFFSET} {REG_TMP1} {int(math.log2(cls.WORD_SIZE))} {cls.WORD_SIZE}")  # skip the word counter
        tran_word_cnt_ld_ret.writeAction(f"add {REG_VAL_RD_ADDR} {REG_TMP1} {REG_TMP1}")

        if cls.DEBUG:
            tran_word_cnt_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: sending load to addr = 0x%lx' {'X0'} {REG_TMP1}")

        # calling with the proper number of operands
        for i in range(1, 6 + 1):
            tran_word_cnt_ld_ret.writeAction(f"beqi {REG_NUM_VAL_WORDS} {i} {f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-match_send_val_{i}'}")
        tran_word_cnt_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-match_send_val_6'}")  # for value words > 6, load the first 6 words
        for i in range(1, 6 + 1):
            sht_macros.dram_read_ret(tran=tran_word_cnt_ld_ret, addr_reg=REG_TMP1, ret_tran_label=tran_val_ld_ret.getLabel(), tmp_reg=REG_TMP2, arg_lm_words=i, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-match_send_val_{i}')
            if cls.DEBUG:
                tran_word_cnt_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: loading {i} words value' {'X0'}")
            tran_word_cnt_ld_ret.writeAction(f"mov_imm2reg {REG_TMP2} {i}")  # words to be copied
            if i < 6:
                tran_word_cnt_ld_ret.writeAction(f"movir {REG_OFFSET} {-1}")  # mark the offset as the last
            else:
                tran_word_cnt_ld_ret.writeAction(f"addi {REG_OFFSET} {REG_OFFSET} {6}")  # set the next offset
                tran_word_cnt_ld_ret.writeAction(f"bgti {REG_NUM_VAL_WORDS} {6} {f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-has_next_{i}'}")
                tran_word_cnt_ld_ret.writeAction(f"movir {REG_OFFSET} {-1}")  # mark the offset as the last
            tran_word_cnt_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-has_next_{i}'}: jmp {f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-match_send_val_done'}")
        tran_word_cnt_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-match_send_val_done'}: mov_imm2reg {REG_MATCH_STATUS} {1}")  # mark key found
        if cls.DEBUG:
            tran_word_cnt_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: key found and value load issued' {'X0'}")
        tran_word_cnt_ld_ret.writeAction("yield")

        """----- Entry migrated, redirect call -----"""
        # prepare redirect arguments
        tran_word_cnt_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-redirect'}: sub {REG_LANE_DESC_LM_ADDR} {'X7'} {REG_TMP2}")
        if cls.DEBUG:
            tran_word_cnt_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: entry already migrated, redirecting call...' {'X0'}")
        tran_word_cnt_ld_ret.writeAction(f"move {cls.LANE_DESC_STURCT_OFF_BUCKETS_PER_LANE}({REG_LANE_DESC_LM_ADDR}) {REG_TMP3} 0 4")
        tran_word_cnt_ld_ret.writeAction(f"muli {REG_TMP3} {REG_TMP3} {cls.BUCKET_DESC_SIZE}")  # REG_TMP3 => size of all lane desc
        tran_word_cnt_ld_ret.writeAction(f"addi {REG_TMP3} {REG_TMP3} {cls.LANE_DESC_SIZE}")
        tran_word_cnt_ld_ret.writeAction(f"add {REG_TMP2} {REG_TMP3} {REG_TMP2}")  # REG_TMP2 => ext sht desc lm offset

        SHTExtCall.ext_graph_get_next_wcont(tran=tran_word_cnt_ld_ret, ret=REG_CONT, tmp_reg=REG_TMP3, desc_lm_offset_reg=REG_TMP2, key_reg=REG_KEY, offset_reg=REG_OFFSET)  # redirect call

        tran_word_cnt_ld_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-wait_key_ld'}")
        cls.lock.read_end(tran_word_cnt_ld_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        tran_word_cnt_ld_ret.writeAction("yield_terminate")
        tran_word_cnt_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-wait_key_ld'}: mov_imm2reg {REG_MATCH_STATUS} {2}")  # mark redirect / oob
        tran_word_cnt_ld_ret.writeAction("yield")

        """----- Out of bound -----"""
        tran_word_cnt_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-out_of_bound'}: mov_imm2reg {REG_TMP1} {-2}")
        if cls.DEBUG:
            tran_word_cnt_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: offset out of bound, return with failure.' {'X0'}")
        # return format: (key, -2) - offset out of bound
        sht_macros.return_wreg(tran=tran_word_cnt_ld_ret, cont_reg=REG_CONT, tmp_reg=REG_TMP2, arg_reg0=REG_KEY, arg_reg1=REG_TMP1)
        cls.lock.read_end(tran_word_cnt_ld_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        tran_word_cnt_ld_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-wait_key_ld'}")  # jump back
        tran_word_cnt_ld_ret.writeAction("yield_terminate")

        """==================== TRAN - load val return ===================="""
        if cls.DEBUG:
            tran_val_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: value load returns' {'X0'}")
        tran_val_ld_ret.writeAction(f"mov_imm2reg {REG_MATCH_STATUS} {2}")  # mark value returned
        cls.lock.read_end(tran_val_ld_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)

        # return format (key, next_offset, val0~5)
        tran_val_ld_ret.writeAction(f"move {REG_KEY} {0}({REG_BUCKET_BUF_LM_ADDR}) 0 8")  # key
        tran_val_ld_ret.writeAction(f"move {REG_OFFSET} {cls.WORD_SIZE * 1}({REG_BUCKET_BUF_LM_ADDR}) 0 8")  # next offset
        tran_val_ld_ret.writeAction(f"addi {REG_BUCKET_BUF_LM_ADDR} {REG_TMP1} {cls.WORD_SIZE * 2}")
        tran_val_ld_ret.writeAction(f"bcopy_ops {'X8'} {REG_TMP1} {REG_TMP2}")

        for i in range(1, 7):
            tran_val_ld_ret.writeAction(f"beqi {REG_NUM_VAL_WORDS} {i} {f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-ret_val_{i}'}")
        tran_val_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-ret_val_6'}")  # for value words > 6, load the first 6 words
        for i in range(1, 7):
            sht_macros.return_wlm(tran=tran_val_ld_ret, cont_reg=REG_CONT, tmp_reg=REG_TMP1, arg_lm_addr_reg=REG_BUCKET_BUF_LM_ADDR, arg_lm_words=(i + 2), branch_label=f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-ret_val_{i}')
            tran_val_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-ret_val_done'}")

        tran_val_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-ret_val_done'}: bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-wait_after_ld_val'}")
        tran_val_ld_ret.writeAction("yield_terminate")
        tran_val_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-wait_after_ld_val'}: yield")

    @classmethod
    def ext_graph_get_next(cls, tran: EFAProgram.Transition, ret_label: int, tmp_reg0: str, tmp_reg1: str, desc_lm_offset_reg: str, key_reg: str, offset_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_ext_graph_get_next.getLabel(), ret_tran_label=ret_label, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=desc_lm_offset_reg, arg_reg1=key_reg, arg_reg2=offset_reg, branch_label=branch_label)

    @classmethod
    def ext_graph_get_next_wcont(cls, tran: EFAProgram.Transition, cont_reg: str, tmp_reg: str, desc_lm_offset_reg: str, key_reg: str, offset_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_ext_graph_get_next.getLabel(), cont_reg=cont_reg, tmp_reg=tmp_reg, arg_reg0=desc_lm_offset_reg, arg_reg1=key_reg, arg_reg2=offset_reg, branch_label=branch_label)

    @classmethod
    def _ext_graph_get_addr(cls, state: EFAProgram.State):
        """
        Extended to get addr + word counter + call redirection

        X8  - LANE_DESC_LM_OFFSET(0:31) | BUCKET_DESC_LM_OFFSET(32:63)
        X9  - KEY
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._ext_graph_get_addr.__name__

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
        tran = cls.tran_ext_graph_get_addr
        if tran is None:
            return
        cls.tran_label_ext_graph_get_addr = tran.getLabel()
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
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: lock admitted, TID = %lu' {'X0'} {'TID'}")

        # calc desc lm addr
        tran.writeAction(f"lshift {OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET} {REG_LANE_DESC_LM_ADDR} {32}")
        tran.writeAction(f"rshift {REG_LANE_DESC_LM_ADDR} {REG_LANE_DESC_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_LANE_DESC_LM_ADDR} {'X7'} {REG_LANE_DESC_LM_ADDR}")

        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: REG_LANE_DESC_LM_ADDR = 0x%lx, REG_BUCKET_DESC_LM_ADDR = 0x%lx' {'X0'} {REG_LANE_DESC_LM_ADDR} {REG_BUCKET_DESC_LM_ADDR}")

        # copy ob regs
        tran.writeAction(f"addi {OB_KEY} {REG_KEY} {0}")
        # save cont
        tran.writeAction(f"addi {'X1'} {REG_CONT} {0}")

        # load desc
        tran.writeAction(f"addi {REG_BUCKET_DESC_LM_ADDR} {REG_BUCKET_BUF_LM_ADDR} {cls.BUCKET_DESC_STURCT_OFF_LM_BUF}")
        tran.writeAction(f"move {cls.BUCKET_DESC_STURCT_OFF_ENTRY_COUNT}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP1} 0 4")  # REG_TMP1 => entry_count

        """----- Empty Bucket -----"""
        # ----- if entry count is zero, return not found -----
        tran.writeAction(f"bgti {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-setup_send_ld'}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: empty bucket, return without search' {'X0'}")
        # return format: (key, 0)
        # tran.writeAction(f"mov_imm2reg {REG_TMP1} {0}")  # indicate failue
        sht_macros.return_wreg(tran=tran, cont_reg=REG_CONT, tmp_reg=REG_TMP2, arg_reg0=REG_KEY, arg_reg1=REG_TMP1)
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
        sht_macros.dram_read_ret(tran=tran, addr_reg=REG_LAST_LOAD_ADDR, ret_tran_label=tran_key_ld_ret.getLabel(), tmp_reg=REG_TMP2, arg_lm_words=8, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-LB-send_ld')
        tran.writeAction(f"addi {REG_LD_CONCURRENCY} {REG_LD_CONCURRENCY} {1}")  # concurrency++
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: loading, DRAM addr = 0x%lx' {'X0'} {REG_LAST_LOAD_ADDR}")
        # check if number of valid entries in the send is greater than 8
        tran.writeAction(f"bgti {REG_TMP1} {64 // cls.KEY_SIZE} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}")
        # last send, retain last send addr & valid size
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: all loads sent' {'X0'}")
        tran.writeAction(f"addi {REG_TMP1} {REG_LAST_LOAD_EFFECTIVE_WORDS} {0}")  # record last load effective size
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
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: load from 0x%lx returns, mlp = %lu' {'X0'} {OB_LD_RET_ADDR} {REG_LD_CONCURRENCY}")
        tran_key_ld_ret.writeAction(f"subi {REG_LD_CONCURRENCY} {REG_LD_CONCURRENCY} {1}")
        # wait the load value return processed before terminating
        tran_key_ld_ret.writeAction(f"beqi {REG_MATCH_STATUS} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}")
        tran_key_ld_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}")
        tran_key_ld_ret.writeAction(f"beqi {REG_MATCH_STATUS} {1} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: last in-flight load key & value returned already, terminating... TID = %lu' {'X0'} {'TID'}")
        # unlocked already, no need to unlock
        tran_key_ld_ret.writeAction("yield_terminate")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}: yield")

        """----- Check returned keys -----"""
        # check if return is matched with (last) send address
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}: bne {OB_LD_RET_ADDR} {REG_LAST_LOAD_ADDR} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{7 * cls.KEY_SIZE}'}")  # tmp3 => last send addr
        # if it is the last send, branch to check only the valid entries
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: tail send load returns, num entries = %lu' {'X0'} {REG_LAST_LOAD_EFFECTIVE_WORDS}")  # tmp2 => last send num valid entries
        for i in range(8, 0, -1):
            tran_key_ld_ret.writeAction(f"beqi {REG_LAST_LOAD_EFFECTIVE_WORDS} {i} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}'}")
        # match return data
        for i in range(8, 0, -1):
            tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}'}: beq {f'X{i + 8 - 1}'} {REG_KEY} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}_match'}")

        """-> not matched (fall through)"""
        tran_key_ld_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait_ld'}")
        # from here, all in-flight loads are done & no match found
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: no matched entry found' {'X0'}")
        # return format: (key, 0)
        tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_TMP1} {0}")  # indicate failue
        sht_macros.return_wreg(tran=tran_key_ld_ret, cont_reg=REG_CONT, tmp_reg=REG_TMP2, arg_reg0=REG_KEY, arg_reg1=REG_TMP1)
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
                tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: matched at word offset {i}' {'X0'}")
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
        sht_macros.dram_read_ret(tran=tran_key_ld_ret, addr_reg=REG_VAL_RD_ADDR, ret_tran_label=tran_word_cnt_ld_ret.getLabel(), tmp_reg=REG_TMP3, arg_lm_words=1)
        tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_MATCH_STATUS} {1}")  # mark key found
        tran_key_ld_ret.writeAction("yield")

        """==================== TRAN - load word counter return ===================="""
        # FIXME: check if there is no next SHT registered, if so, reply error
        # check if the entry is migrated
        tran_word_cnt_ld_ret.writeAction(f"beqi {'X8'} {-1} {f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-redirect'}")

        """----- reply word counter -----"""
        # return format: (key, val_start_addr, word_cnt)
        tran_word_cnt_ld_ret.writeAction(f"addi {REG_VAL_RD_ADDR} {REG_TMP1} {cls.WORD_SIZE}")  # REG_TMP1 => write addr skip the word counter
        sht_macros.return_wreg(tran=tran_word_cnt_ld_ret, cont_reg=REG_CONT, tmp_reg=REG_TMP2, arg_reg0=REG_KEY, arg_reg1=REG_TMP1, arg_reg2='X8')
        cls.lock.read_end(tran_word_cnt_ld_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        tran_word_cnt_ld_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-wait_key_ld'}")
        tran_word_cnt_ld_ret.writeAction("yield_terminate")

        """----- Entry migrated, redirect call -----"""
        # prepare redirect arguments
        tran_word_cnt_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-redirect'}: sub {REG_LANE_DESC_LM_ADDR} {'X7'} {REG_TMP2}")
        tran_word_cnt_ld_ret.writeAction(f"move {cls.LANE_DESC_STURCT_OFF_BUCKETS_PER_LANE}({REG_LANE_DESC_LM_ADDR}) {REG_TMP3} 0 4")
        tran_word_cnt_ld_ret.writeAction(f"muli {REG_TMP3} {REG_TMP3} {cls.BUCKET_DESC_SIZE}")  # REG_TMP3 => size of all lane desc
        tran_word_cnt_ld_ret.writeAction(f"addi {REG_TMP3} {REG_TMP3} {cls.LANE_DESC_SIZE}")
        tran_word_cnt_ld_ret.writeAction(f"add {REG_TMP2} {REG_TMP3} {REG_TMP2}")  # REG_TMP2 => ext sht desc lm offset

        SHTExtCall.ext_graph_get_addr_wcont(tran=tran_word_cnt_ld_ret, ret=REG_CONT, tmp_reg=REG_TMP3, desc_lm_offset_reg=REG_TMP2, key_reg=REG_KEY)  # redirect call
        cls.lock.read_end(tran_word_cnt_ld_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP3)

        tran_word_cnt_ld_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-wait_key_ld'}")
        tran_word_cnt_ld_ret.writeAction("yield_terminate")
        tran_word_cnt_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-word_cnt_ld_ret-LB-wait_key_ld'}: mov_imm2reg {REG_MATCH_STATUS} {2}")  # mark redirect
        tran_word_cnt_ld_ret.writeAction("yield")

    @classmethod
    def ext_graph_get_addr(cls, tran: EFAProgram.Transition, ret_label: int, tmp_reg0: str, tmp_reg1: str, desc_lm_offset_reg: str, key_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_ext_graph_get_addr.getLabel(), ret_tran_label=ret_label, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=desc_lm_offset_reg, arg_reg1=key_reg, branch_label=branch_label)

    @classmethod
    def ext_graph_get_addr_wcont(cls, tran: EFAProgram.Transition, cont_reg: str, tmp_reg: str, desc_lm_offset_reg: str, key_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_ext_graph_get_addr.getLabel(), cont_reg=cont_reg, tmp_reg=tmp_reg, arg_reg0=desc_lm_offset_reg, arg_reg1=key_reg, branch_label=branch_label)

    @classmethod
    def _get_with_offset(cls, state: EFAProgram.State):
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
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: lock admitted, TID = %lu' {'X0'} {'TID'}")

        # calc desc lm addr
        tran.writeAction(f"lshift {OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET} {REG_LANE_DESC_LM_ADDR} {32}")
        tran.writeAction(f"rshift {REG_LANE_DESC_LM_ADDR} {REG_LANE_DESC_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_LANE_DESC_LM_ADDR} {'X7'} {REG_LANE_DESC_LM_ADDR}")

        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: REG_LANE_DESC_LM_ADDR = 0x%lx, REG_BUCKET_DESC_LM_ADDR = 0x%lx' {'X0'} {REG_LANE_DESC_LM_ADDR} {REG_BUCKET_DESC_LM_ADDR}")

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
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: empty bucket, return without search' {'X0'}")
        # return format: (key, -1)
        tran.writeAction(f"mov_imm2reg {REG_TMP1} {-1}")  # indicate failue
        sht_macros.return_wreg(tran=tran, cont_reg=REG_CONT, tmp_reg=REG_TMP2, arg_reg0=REG_KEY, arg_reg1=REG_TMP1)
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
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: loading, DRAM addr = 0x%lx' {'X0'} {REG_LAST_LOAD_ADDR}")
        # check if number of valid entries in the send is greater than 8
        tran.writeAction(f"bgti {REG_TMP1} {64 // cls.KEY_SIZE} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}")
        # last send, retain last send addr & valid size
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: all loads sent' {'X0'}")
        tran.writeAction(f"addi {REG_TMP1} {REG_LAST_LOAD_EFFECTIVE_WORDS} {0}")  # record last load effective size
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
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: load from 0x%lx returns, mlp = %lu' {'X0'} {OB_LD_RET_ADDR} {REG_LD_CONCURRENCY}")
        tran_key_ld_ret.writeAction(f"subi {REG_LD_CONCURRENCY} {REG_LD_CONCURRENCY} {1}")
        # wait the load value return processed before terminating
        tran_key_ld_ret.writeAction(f"beqi {REG_MATCH_STATUS} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}")
        tran_key_ld_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}")
        tran_key_ld_ret.writeAction(f"beqi {REG_MATCH_STATUS} {1} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: last in-flight load key & value returned already, terminating... TID = %lu' {'X0'} {'TID'}")
        # unlocked already, no need to unlock
        tran_key_ld_ret.writeAction("yield_terminate")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}: yield")

        """----- Check returned keys -----"""
        # check if return is matched with (last) send address
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}: bne {OB_LD_RET_ADDR} {REG_LAST_LOAD_ADDR} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{7 * cls.KEY_SIZE}'}")  # tmp3 => last send addr
        # if it is the last send, branch to check only the valid entries
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: tail send load returns, num entries = %lu' {'X0'} {REG_LAST_LOAD_EFFECTIVE_WORDS}")  # tmp2 => last send num valid entries
        for i in range(8, 0, -1):
            tran_key_ld_ret.writeAction(f"beqi {REG_LAST_LOAD_EFFECTIVE_WORDS} {i} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}'}")
        # match return data
        for i in range(8, 0, -1):
            tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}'}: beq {f'X{i + 8 - 1}'} {REG_KEY} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}_match'}")

        """-> not matched (fall through)"""
        tran_key_ld_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait_ld'}")
        # from here, all in-flight loads are done & no match found
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: no matched entry found' {'X0'}")
        # return format: (key, -1)
        tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_TMP1} {-1}")  # indicate failue
        sht_macros.return_wreg(tran=tran_key_ld_ret, cont_reg=REG_CONT, tmp_reg=REG_TMP2, arg_reg0=REG_KEY, arg_reg1=REG_TMP1)
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
                tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: matched at word offset {i}' {'X0'}")
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
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: sending load to addr = 0x%lx' {'X0'} {REG_VAL_RD_ADDR}")

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
                tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: loading {i} words value' {'X0'}")
            tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_done'}")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_done'}: mov_imm2reg {REG_MATCH_STATUS} {1}")  # mark key found
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: key found and value load issued' {'X0'}")
        tran_key_ld_ret.writeAction("yield")

        """==================== TRAN - load val return ===================="""
        if cls.DEBUG:
            tran_val_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: value load returns' {'X0'}")
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
            sht_macros.return_wlm(tran=tran_val_ld_ret, cont_reg=REG_CONT, tmp_reg=REG_TMP1, arg_lm_addr_reg=REG_BUCKET_BUF_LM_ADDR, arg_lm_words=(i + 2), branch_label=f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-ret_val_{i}')
            tran_val_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-ret_val_done'}")

        tran_val_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-ret_val_done'}: bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-wait_after_ld_val'}")
        tran_val_ld_ret.writeAction("yield_terminate")
        tran_val_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-wait_after_ld_val'}: yield")

    @classmethod
    def get_with_offset(cls, tran: EFAProgram.Transition, ret_label: int, tmp_reg0: str, tmp_reg1: str, desc_lm_offset_reg: str, key_reg: str, offset_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_get_with_offset.getLabel(), ret_tran_label=ret_label, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=desc_lm_offset_reg, arg_reg1=key_reg, arg_reg2=offset_reg, branch_label=branch_label)

    @classmethod
    def get_with_offset_wcont(cls, tran: EFAProgram.Transition, cont_reg: str, tmp_reg: str, desc_lm_offset_reg: str, key_reg: str, offset_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_get_with_offset.getLabel(), cont_reg=cont_reg, tmp_reg=tmp_reg, arg_reg0=desc_lm_offset_reg, arg_reg1=key_reg, arg_reg2=offset_reg, branch_label=branch_label)

    @classmethod
    def _update_with_offset(cls, state: EFAProgram.State):
        """
        X8  - LANE_DESC_LM_OFFSET(0:31) | BUCKET_DESC_LM_OFFSET(32:63)
        X9  - KEY
        X10 - OFFSET
        X11 ~ X15 - VAL
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._update_with_offset.__name__

        OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET = "X8"
        OB_KEY = "X9"
        OB_OFFSET = "X10"
        OB_VAL = "X11"
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
        REG_OFFSET = "X19"

        REG_CONT = "X31"

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_update_with_offset
        if tran is None:
            return
        cls.tran_label_update_with_offset = tran.getLabel()
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
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: lock admitted, TID = %lu' {'X0'} {'TID'}")

        # calc desc lm addr
        tran.writeAction(f"lshift {OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET} {REG_LANE_DESC_LM_ADDR} {32}")
        tran.writeAction(f"rshift {REG_LANE_DESC_LM_ADDR} {REG_LANE_DESC_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_LANE_DESC_LM_ADDR} {'X7'} {REG_LANE_DESC_LM_ADDR}")

        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: REG_LANE_DESC_LM_ADDR = 0x%lx, REG_BUCKET_DESC_LM_ADDR = 0x%lx' {'X0'} {REG_LANE_DESC_LM_ADDR} {REG_BUCKET_DESC_LM_ADDR}")

        # copy ob regs
        tran.writeAction(f"addi {OB_KEY} {REG_KEY} {0}")
        # save offset
        tran.writeAction(f"addi {OB_OFFSET} {REG_OFFSET} {0}")
        # save cont
        tran.writeAction(f"addi {'X1'} {REG_CONT} {0}")

        # load desc
        tran.writeAction(f"addi {REG_BUCKET_DESC_LM_ADDR} {REG_BUCKET_BUF_LM_ADDR} {cls.BUCKET_DESC_STURCT_OFF_LM_BUF}")

        # extract num_elem_op
        # since there is an offset of 2 in the encoding, the desc & key counts are skipped
        tran.writeAction(f"rshift {'X2'} {REG_NUM_VAL_OP} {20}")
        tran.writeAction(f"andi {REG_NUM_VAL_OP} {REG_NUM_VAL_OP} {0b111}")
        tran.writeAction(f"subi {REG_NUM_VAL_OP} {REG_NUM_VAL_OP} {1}")  # skip the offset
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: number of val operands = %lu' {'X0'} {REG_NUM_VAL_OP}")
        # copy val to buffer
        tran.writeAction(f"bcopy_ops {OB_VAL} {REG_BUCKET_BUF_LM_ADDR} {REG_NUM_VAL_OP}")

        tran.writeAction(f"move {cls.BUCKET_DESC_STURCT_OFF_ENTRY_COUNT}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP1} 0 4")  # tmp1 => entry_count

        """----- Empty Bucket -----"""
        # ----- if entry count is zero, write directly -----
        tran.writeAction(f"bgti {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-setup_send_ld'}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: empty bucket, writing without search' {'X0'}")
        # update entry count
        tran.writeAction(f"addi {REG_TMP1} {REG_TMP1} {1}")
        tran.writeAction(f"move {REG_TMP1} {cls.BUCKET_DESC_STURCT_OFF_ENTRY_COUNT}({REG_BUCKET_DESC_LM_ADDR}) 0 4")

        tran.writeAction(f"mov_imm2reg {REG_LD_CONCURRENCY} {0}")
        tran.writeAction(f"mov_imm2reg {REG_ST_CONCURRENCY} {2}")
        tran.writeAction(f"move {cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_KEY_WR_ADDR} 0 8")
        sht_macros.dram_write_reg_ret(tran=tran, addr_reg=REG_KEY_WR_ADDR, ret_tran_label=tran_key_st_ret.getLabel(), tmp_reg=REG_TMP2, arg_reg0=REG_KEY)
        tran.writeAction(f"move {cls.BUCKET_DESC_STURCT_OFF_DRAM_VAL_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_VAL_WR_ADDR} 0 8")
        tran.writeAction(f"sli {REG_OFFSET} {REG_TMP2} {int(math.log2(cls.WORD_SIZE))}")  # adjust offset
        tran.writeAction(f"add {REG_KEY_WR_ADDR} {REG_OFFSET} {REG_VAL_WR_ADDR}")
        # calling with the proper number of operands
        for i in range(1, MAX_VAL_NUM_WORDS + 1):
            tran.writeAction(f"beqi {REG_NUM_VAL_OP} {i} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_val_{i}'}")
        tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: shouldn't reach here!' {'X0'}")
        for i in range(1, MAX_VAL_NUM_WORDS + 1):
            sht_macros.dram_write_lm_ret(tran=tran, addr_reg=REG_VAL_WR_ADDR, ret_tran_label=tran_key_st_ret.getLabel(), tmp_reg=REG_TMP2, arg_lm_addr_reg=REG_BUCKET_BUF_LM_ADDR, arg_lm_words=i, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-LB-send_val_{i}')
            if cls.DEBUG:
                tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: writing {i} words value' {'X0'}")
            tran.writeAction("yield")

        """----- Filled Bucket -----"""
        # ----- already have entires, send load entries -----
        # init
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-setup_send_ld'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_LAST_LOAD_ADDR} 0 8")  # tmp3 => key load start address
        tran.writeAction(f"mov_imm2reg {REG_LD_CONCURRENCY} {0}")
        tran.writeAction(f"mov_imm2reg {REG_ST_CONCURRENCY} {-1}")

        tran.writeAction(f"blei {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_done'}")  # tmp1 => entry_count
        sht_macros.dram_read_ret(tran=tran, addr_reg=REG_LAST_LOAD_ADDR, ret_tran_label=tran_key_ld_ret.getLabel(), tmp_reg=REG_TMP2, arg_lm_words=8, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-LB-send_ld')
        tran.writeAction(f"addi {REG_LD_CONCURRENCY} {REG_LD_CONCURRENCY} {1}")  # concurrency++
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: loading, DRAM addr = 0x%lx' {'X0'} {REG_LAST_LOAD_ADDR}")
        # check if number of valid entries in the send is greater than 8
        tran.writeAction(f"bgti {REG_TMP1} {64 // cls.KEY_SIZE} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}")
        # last send, retain last send addr & valid size
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: all loads sent' {'X0'}")
        tran.writeAction(f"addi {REG_TMP1} {REG_LAST_LOAD_EFFECTIVE_WORDS} {0}")  # record last load effective size
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
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: load from 0x%lx returns, mlp = %lu' {'X0'} {OB_LD_RET_ADDR} {REG_LD_CONCURRENCY}")
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
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: last in-flight load & store finished, terminating... TID = %lu' {'X0'} {'TID'}")
        # unlocked already, no need to unlock
        # return format: (key, offset)
        sht_macros.return_wreg(tran=tran_key_ld_ret, cont_reg=REG_CONT, tmp_reg=REG_TMP0, arg_reg0=REG_KEY, arg_reg1=REG_OFFSET)
        tran_key_ld_ret.writeAction("yield_terminate")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}: yield")

        """----- Check returned keys -----"""
        # check if return is matched with (last) send address
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}: bne {OB_LD_RET_ADDR} {REG_LAST_LOAD_ADDR} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{7 * cls.KEY_SIZE}'}")  # tmp3 => last send addr
        # if it is the last send, branch to check only the valid entries
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: tail send load returns, num entries = %lu' {'X0'} {REG_LAST_LOAD_EFFECTIVE_WORDS}")  # tmp2 => last send num valid entries
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
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: no matched entry found' {'X0'}")
        # check if there is space at the end of the allocation area
        tran_key_ld_ret.writeAction(f"move {cls.LANE_DESC_STURCT_OFF_ENTRIES_PER_BUCKET}({REG_LANE_DESC_LM_ADDR}) {REG_TMP1} 0 4")  # REG_TMP1 => num_alloc_entries
        tran_key_ld_ret.writeAction(f"move {cls.BUCKET_DESC_STURCT_OFF_ENTRY_COUNT}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP2} 0 4")  # REG_TMP2 => entry count
        tran_key_ld_ret.writeAction(f"blt {REG_TMP2} {REG_TMP1} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-new_entry'}")
        # -> out of space!
        tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: bucket full, add FAILED!' {'X0'}")
        # if cls.DEBUG:
        #     tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: bucket full, add FAILED!' {'X0'}")
        # return format: (key, offset)
        tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_TMP1} {-1}")  # indicate failue with offset == -1
        sht_macros.return_wreg(tran=tran_key_ld_ret, cont_reg=REG_CONT, tmp_reg=REG_TMP0, arg_reg0=REG_KEY, arg_reg1=REG_TMP1)
        # sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, 'X0', REG_TMP3)  # for debug
        cls.lock.write_end(tran_key_ld_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        tran_key_ld_ret.writeAction("yield_terminate")  # only if running out of space!
        # -> new entry
        # calculate the address of the key
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-new_entry'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_KEY_WR_ADDR} 0 8")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: storing in a new entry' {'X0'}")
        tran_key_ld_ret.writeAction(f"lshift {REG_TMP2} {REG_TMP1} {int(math.log2(cls.KEY_SIZE))}")
        tran_key_ld_ret.writeAction(f"add {REG_KEY_WR_ADDR} {REG_TMP1} {REG_KEY_WR_ADDR}")
        # store key
        sht_macros.dram_write_reg_ret(tran=tran_key_ld_ret, addr_reg=REG_KEY_WR_ADDR, ret_tran_label=tran_key_st_ret.getLabel(), tmp_reg=REG_TMP0, arg_reg0=REG_KEY)
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: sending key write to addr = 0x%lx' {'X0'} {REG_KEY_WR_ADDR}")
        # calculate the address of the value
        tran_key_ld_ret.writeAction(f"move {cls.BUCKET_DESC_STURCT_OFF_DRAM_VAL_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_VAL_WR_ADDR} 0 8")
        tran_key_ld_ret.writeAction(f"move {cls.LANE_DESC_STURCT_OFF_VAL_NUM_WORDS}({REG_LANE_DESC_LM_ADDR}) {REG_TMP1} 0 4")
        tran_key_ld_ret.writeAction(f"mul {REG_TMP2} {REG_TMP1} {REG_TMP1}")
        tran_key_ld_ret.writeAction(f"add {REG_TMP1} {REG_OFFSET} {REG_TMP1}")
        tran_key_ld_ret.writeAction(f"lshift {REG_TMP1} {REG_TMP1} {int(math.log2(cls.WORD_SIZE))}")
        tran_key_ld_ret.writeAction(f"add {REG_VAL_WR_ADDR} {REG_TMP1} {REG_VAL_WR_ADDR}")
        # store value
        # calling with the proper number of operands
        for i in range(1, MAX_VAL_NUM_WORDS + 1):
            tran_key_ld_ret.writeAction(f"beqi {REG_NUM_VAL_OP} {i} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-nomatch_send_val_{i}'}")
        tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: shouldn't reach here!' {'X0'}")
        for i in range(1, MAX_VAL_NUM_WORDS + 1):
            sht_macros.dram_write_lm_ret(tran=tran_key_ld_ret, addr_reg=REG_VAL_WR_ADDR, ret_tran_label=tran_key_st_ret.getLabel(), tmp_reg=REG_TMP0, arg_lm_addr_reg=REG_BUCKET_BUF_LM_ADDR, arg_lm_words=i, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-nomatch_send_val_{i}')
            if cls.DEBUG:
                tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: writing {i} words value' {'X0'}")
            tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-nomatch_send_val_done'}")
        # count up the entries
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-nomatch_send_val_done'}: addi {REG_TMP2} {REG_TMP2} {1}")
        tran_key_ld_ret.writeAction(f"move {REG_TMP2} {cls.BUCKET_DESC_STURCT_OFF_ENTRY_COUNT}({REG_BUCKET_DESC_LM_ADDR}) 0 4")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: sending value write to addr = 0x%lx' {'X0'} {REG_VAL_WR_ADDR}")
        tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_ST_CONCURRENCY} {2}")  # mark value written & all loads done
        # -> wait for in-flight load to come back
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait_ld'}: yield")

        """-> matched"""
        for i in range(0, 8):
            # calculate the entry index from key address
            tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{i * cls.KEY_SIZE}_match'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP1} 0 8")
            if cls.DEBUG:
                tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: matched at word offset {i}' {'X0'}")
            tran_key_ld_ret.writeAction(f"sub {OB_LD_RET_ADDR} {REG_TMP1} {REG_TMP1}")
            tran_key_ld_ret.writeAction(f"rshift {REG_TMP1} {REG_TMP1} {int(math.log2(cls.KEY_SIZE))}")
            tran_key_ld_ret.writeAction(f"addi {REG_TMP1} {REG_TMP1} {i}")  # REG_TMP1 => entry index
            tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_st'}")

        """----- Send store value -----"""
        # calculate value address
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_st'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_VAL_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_VAL_WR_ADDR} 0 8")
        tran_key_ld_ret.writeAction(f"move {cls.LANE_DESC_STURCT_OFF_VAL_NUM_WORDS}({REG_LANE_DESC_LM_ADDR}) {REG_TMP2} 0 4")
        tran_key_ld_ret.writeAction(f"mul {REG_TMP2} {REG_TMP1} {REG_TMP1}")
        tran_key_ld_ret.writeAction(f"add {REG_TMP1} {REG_OFFSET} {REG_TMP1}")
        tran_key_ld_ret.writeAction(f"lshift {REG_TMP1} {REG_TMP1} {int(math.log2(cls.WORD_SIZE))}")
        tran_key_ld_ret.writeAction(f"add {REG_VAL_WR_ADDR} {REG_TMP1} {REG_VAL_WR_ADDR}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: sending write to addr = 0x%lx' {'X0'} {REG_VAL_WR_ADDR}")
        # calling with the proper number of operands
        for i in range(1, MAX_VAL_NUM_WORDS + 1):
            tran_key_ld_ret.writeAction(f"beqi {REG_NUM_VAL_OP} {i} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_{i}'}")
        tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: shouldn't reach here!' {'X0'}")
        for i in range(1, MAX_VAL_NUM_WORDS + 1):
            sht_macros.dram_write_lm_ret(tran=tran_key_ld_ret, addr_reg=REG_VAL_WR_ADDR, ret_tran_label=tran_key_st_ret.getLabel(), tmp_reg=REG_TMP0, arg_lm_addr_reg=REG_BUCKET_BUF_LM_ADDR, arg_lm_words=i, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_{i}')
            if cls.DEBUG:
                tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: writing {i} words value' {'X0'}")
            tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_done'}")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_done'}: mov_imm2reg {REG_ST_CONCURRENCY} {1}")  # mark value written
        tran_key_ld_ret.writeAction("yield")

        """==================== TRAN - store key val return ===================="""
        tran_key_st_ret.writeAction(f"subi {REG_ST_CONCURRENCY} {REG_ST_CONCURRENCY} {1}")
        tran_key_st_ret.writeAction(f"bgti {REG_ST_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_st_ret-LB-wait'}")
        tran_key_st_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_st_ret-LB-ld_wait'}")
        if cls.DEBUG:
            tran_key_st_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: write to 0x%lx returns & no load waiting, terminating... TID = %lu' {'X0'} {'X8'} {'TID'}")
        # return format: (key, offset)
        sht_macros.return_wreg(tran=tran_key_st_ret, cont_reg=REG_CONT, tmp_reg=REG_TMP0, arg_reg0=REG_KEY, arg_reg1=REG_OFFSET)
        # sht_macros.return_wreg(tran_key_st_ret, REG_CONT, 'X0', REG_VAL_WR_ADDR)  # debug
        cls.lock.write_end(tran_key_st_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        tran_key_st_ret.writeAction("yield_terminate")
        tran_key_st_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_st_ret-LB-ld_wait'}: addi {REG_TMP1} {REG_TMP1} {0}")  # dummy instruction
        cls.lock.write_end(tran_key_st_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        if cls.DEBUG:
            tran_key_st_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: write to 0x%lx returns & all stores done, waiting loads return...' {'X0'} {'X8'}")
        tran_key_st_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_st_ret-LB-wait'}: yield")

    @classmethod
    def update_with_offset(cls, tran: EFAProgram.Transition, ret: int, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, arg_lm_words: int, dst_nwid_reg: str = 'X0', branch_label: str = "") -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_update_with_offset.getLabel(), ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=arg_lm_words, branch_label=branch_label)

    @classmethod
    def update_with_offset_wcont(cls, tran: EFAProgram.Transition, cont_reg: str, tmp_reg0: str, arg_lm_addr_reg: str, arg_lm_words: int, dst_nwid_reg: str = 'X0', branch_label: str = "") -> None:
        sht_macros.call_wlm_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_update_with_offset.getLabel(), cont_reg=cont_reg, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=arg_lm_words, branch_label=branch_label)

    @classmethod
    def _get_with_mask_8(cls, state: EFAProgram.State):
        """
        Extended to support mask

        X8  - LANE_DESC_LM_OFFSET(0:31) | BUCKET_DESC_LM_OFFSET(32:63)
        X9  - KEY
        X10 - MASK
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._get_with_mask_8.__name__

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
        tran = cls.tran_get_with_mask_8
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
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: lock admitted, TID = %lu' {'X0'} {'TID'}")

        # calc desc lm addr
        tran.writeAction(f"lshift {OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET} {REG_LANE_DESC_LM_ADDR} {32}")
        tran.writeAction(f"rshift {REG_LANE_DESC_LM_ADDR} {REG_LANE_DESC_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_LANE_DESC_LM_ADDR} {'X7'} {REG_LANE_DESC_LM_ADDR}")

        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: REG_LANE_DESC_LM_ADDR = 0x%lx, REG_BUCKET_DESC_LM_ADDR = 0x%lx' {'X0'} {REG_LANE_DESC_LM_ADDR} {REG_BUCKET_DESC_LM_ADDR}")

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
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: empty bucket, return without search' {'X0'}")
        # return format: (key, 0)
        # tran.writeAction(f"mov_imm2reg {REG_TMP1} {0}")  # indicate failue
        sht_macros.return_wreg(tran=tran, cont_reg=REG_CONT, tmp_reg=REG_TMP2, arg_reg0=REG_KEY, arg_reg1=REG_TMP1)
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
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: loading, DRAM addr = 0x%lx' {'X0'} {REG_LAST_LOAD_ADDR}")
        # check if number of valid entries in the send is greater than 8
        tran.writeAction(f"bgti {REG_TMP1} {64 // cls.KEY_SIZE} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}")
        # last send, retain last send addr & valid size
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: all loads sent' {'X0'}")
        tran.writeAction(f"addi {REG_TMP1} {REG_LAST_LOAD_EFFECTIVE_WORDS} {0}")  # record last load effective size
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
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: load from 0x%lx returns, mlp = %lu' {'X0'} {OB_LD_RET_ADDR} {REG_LD_CONCURRENCY}")
        tran_key_ld_ret.writeAction(f"subi {REG_LD_CONCURRENCY} {REG_LD_CONCURRENCY} {1}")
        # wait the load value return processed before terminating
        tran_key_ld_ret.writeAction(f"beqi {REG_MATCH_STATUS} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}")
        tran_key_ld_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}")
        tran_key_ld_ret.writeAction(f"beqi {REG_MATCH_STATUS} {1} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: last in-flight load key & value returned already, terminating... TID = %lu' {'X0'} {'TID'}")
        # unlocked already, no need to unlock
        tran_key_ld_ret.writeAction("yield_terminate")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}: yield")

        """----- Check returned keys -----"""
        # check if return is matched with (last) send address
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}: bne {OB_LD_RET_ADDR} {REG_LAST_LOAD_ADDR} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{7 * cls.KEY_SIZE}'}")  # tmp3 => last send addr
        # if it is the last send, branch to check only the valid entries
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: tail send load returns, num entries = %lu' {'X0'} {REG_LAST_LOAD_EFFECTIVE_WORDS}")  # tmp2 => last send num valid entries
        for i in range(8, 0, -1):
            tran_key_ld_ret.writeAction(f"beqi {REG_LAST_LOAD_EFFECTIVE_WORDS} {i} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}'}")
        # match return data
        for i in range(8, 0, -1):
            tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}'}: beq {f'X{i + 8 - 1}'} {REG_KEY} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}_match'}")

        """-> not matched (fall through)"""
        tran_key_ld_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait_ld'}")
        # from here, all in-flight loads are done & no match found
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: no matched entry found' {'X0'}")
        # return format: (key, 0)
        tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_TMP1} {0}")  # indicate failue
        sht_macros.return_wreg(tran=tran_key_ld_ret, cont_reg=REG_CONT, tmp_reg=REG_TMP2, arg_reg0=REG_KEY, arg_reg1=REG_TMP1)
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
                tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: matched at word offset {i}' {'X0'}")
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
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: sending load to addr = 0x%lx' {'X0'} {REG_VAL_RD_ADDR}")

        # calling with the proper number of operands
        for i in range(1, 9):
            tran_key_ld_ret.writeAction(f"beqi {REG_NUM_VAL_WORDS} {i} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_{i}'}")
        tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_8'}")  # for value words > 8, load the first 8 words
        for i in range(1, 9):
            # tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_{i}'}: send_dmlm_ld_wret {REG_VAL_RD_ADDR} {tran_val_ld_ret.getLabel()} {i}")
            sht_macros.dram_read_ret(tran=tran_key_ld_ret, addr_reg=REG_VAL_RD_ADDR, ret_tran_label=tran_val_ld_ret.getLabel(), tmp_reg=REG_TMP2, arg_lm_words=i, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_{i}')
            tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_TMP2} {i}")  # words to be copied
            if cls.DEBUG:
                tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: loading {i} words value' {'X0'}")
            tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_done'}")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_done'}: mov_imm2reg {REG_MATCH_STATUS} {1}")  # mark key found
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: key found and value load issued' {'X0'}")
        tran_key_ld_ret.writeAction("yield")

        """==================== TRAN - load val return ===================="""
        if cls.DEBUG:
            tran_val_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: value load returns' {'X0'}")
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
            sht_macros.return_wlm(tran=tran_val_ld_ret, cont_reg=REG_CONT, tmp_reg=REG_TMP1, arg_lm_addr_reg=REG_BUCKET_BUF_LM_ADDR, arg_lm_words=(i + 2), branch_label=f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-ret_val_{i}')
            tran_val_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-ret_val_done'}")

        tran_val_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-ret_val_done'}: bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-wait_after_ld_val'}")
        tran_val_ld_ret.writeAction("yield_terminate")
        tran_val_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-wait_after_ld_val'}: yield")

    @classmethod
    def get_with_mask_8(cls, tran: EFAProgram.Transition, ret_label: int, tmp_reg0: str, tmp_reg1: str, desc_lm_offset_reg: str, key_reg: str, mask_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_get_with_mask_8.getLabel(), ret_tran_label=ret_label, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=desc_lm_offset_reg, arg_reg1=key_reg, arg_reg2=mask_reg, branch_label=branch_label)

    @classmethod
    def get_with_mask_8_wcont(cls, tran: EFAProgram.Transition, cont_reg: str, tmp_reg: str, desc_lm_offset_reg: str, key_reg: str, mask_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_get_with_mask_8.getLabel(), cont_reg=cont_reg, tmp_reg=tmp_reg, arg_reg0=desc_lm_offset_reg, arg_reg1=key_reg, arg_reg2=mask_reg, branch_label=branch_label)

    @classmethod
    def _get_with_mask_64(cls, state: EFAProgram.State):
        """
        Extended to support mask

        X8  - LANE_DESC_LM_OFFSET(0:31) | BUCKET_DESC_LM_OFFSET(32:63)
        X9  - KEY
        X10 - MASK
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._get_with_mask_64.__name__

        OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET = "X8"
        OB_KEY = "X9"
        OB_MASK = "X10"

        REG_TMP0 = "X16"  # last reusable
        REG_TMP1 = "X17"
        REG_TMP2 = "X18"  # reusable
        REG_TMP3 = "X19"  # reusable
        REG_TMP4 = "X20"  # reusable

        REG_LD_KEY_CONCURRENCY = "X21"  # keep to handle key ld returns
        REG_LD_VAL_CONCURRENCY = "X22"  # needed
        REG_VAL_LD_ADDR = "X23"  # reuseable, can be reloaded from REG_BUCKET_DESC_LM_ADDR if needed

        REG_LAST_LOAD_EFFECTIVE_WORDS = "X24"  # reusable
        REG_LAST_LOAD_ADDR = "X25"  # reusable

        REG_LANE_DESC_LM_ADDR = "X26"  # may not be useful after entry found
        REG_BUCKET_DESC_LM_ADDR = "X27"  # keep to unlock
        REG_BUCKET_BUF_LM_ADDR = "X28"  # can be recalcuated from REG_BUCKET_DESC_LM_ADDR

        REG_KEY = "X29"  # keep for return
        REG_MASK = "X30"  # keep for return

        REG_CONT = "X31"  # keep for return

        REG_RET_TMP_LM_ADDR = [REG_LAST_LOAD_ADDR, REG_LAST_LOAD_EFFECTIVE_WORDS, REG_VAL_LD_ADDR, REG_TMP2, REG_TMP3, REG_TMP4]  # REG_TMP0 is used for the the cur tmp lm write addr

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_get_with_mask_64
        if tran is None:
            return
        cls.tran_label_get_with_mask = tran.getLabel()
        tran_key_ld_ret = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-key_ld_ret")
        tran_val_ld_ret = []
        for i in range(6):
            tran_val_ld_ret.append([])
            for j in range(6 - i):
                tran_val_ld_ret[i].append(state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-val_ld_ret_{i}_{j}"))

        """==================== TRAN - function entry ===================="""
        """----- Prep -----"""
        # calc desc lm addr
        tran.writeAction(f"rshift {OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET} {REG_BUCKET_DESC_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_BUCKET_DESC_LM_ADDR} {'X7'} {REG_BUCKET_DESC_LM_ADDR}")
        # get lock
        cls.lock.read_begin(tran, REG_BUCKET_DESC_LM_ADDR, REG_TMP1, 3)
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: lock admitted, TID = %lu' {'X0'} {'TID'}")

        # calc desc lm addr
        tran.writeAction(f"lshift {OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET} {REG_LANE_DESC_LM_ADDR} {32}")
        tran.writeAction(f"rshift {REG_LANE_DESC_LM_ADDR} {REG_LANE_DESC_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_LANE_DESC_LM_ADDR} {'X7'} {REG_LANE_DESC_LM_ADDR}")

        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: REG_LANE_DESC_LM_ADDR = 0x%lx, REG_BUCKET_DESC_LM_ADDR = 0x%lx' {'X0'} {REG_LANE_DESC_LM_ADDR} {REG_BUCKET_DESC_LM_ADDR}")
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: KEY = %lu, MASK = %lu' {'X0'} {OB_KEY} {OB_MASK}")

        # copy ob regs
        tran.writeAction(f"addi {OB_KEY} {REG_KEY} {0}")
        tran.writeAction(f"addi {OB_MASK} {REG_MASK} {0}")
        # save cont
        tran.writeAction(f"addi {'X1'} {REG_CONT} {0}")

        # load desc
        tran.writeAction(f"addi {REG_BUCKET_DESC_LM_ADDR} {REG_BUCKET_BUF_LM_ADDR} {cls.BUCKET_DESC_STURCT_OFF_LM_BUF}")
        # tran.writeAction(f"move {cls.LANE_DESC_STURCT_OFF_VAL_NUM_WORDS}({REG_LANE_DESC_LM_ADDR}) {REG_NUM_VAL_WORDS} 0 4")

        tran.writeAction(f"move {cls.BUCKET_DESC_STURCT_OFF_ENTRY_COUNT}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP1} 0 4")  # tmp1 => entry_count

        """----- Empty Bucket -----"""
        # ----- if entry count is zero, return not found -----
        tran.writeAction(f"bgti {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-setup_send_ld'}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: empty bucket, return without search' {'X0'}")
        # return format: (key, 0)
        # tran.writeAction(f"mov_imm2reg {REG_TMP1} {0}")  # indicate failue
        sht_macros.return_wreg(tran=tran, cont_reg=REG_CONT, tmp_reg=REG_TMP0, arg_reg0=REG_KEY, arg_reg1=REG_TMP1)
        # sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, 'X0', REG_TMP3)  # for debug
        cls.lock.read_end(tran, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        tran.writeAction("yield_terminate")  # only if running out of space!

        """----- Filled Bucket -----"""
        # ----- already have entires, send load entries -----
        # init
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-setup_send_ld'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_LAST_LOAD_ADDR} 0 8")  # tmp3 => key load start address
        tran.writeAction(f"mov_imm2reg {REG_LD_KEY_CONCURRENCY} {0}")
        tran.writeAction(f"mov_imm2reg {REG_LD_VAL_CONCURRENCY} {-1}")

        tran.writeAction(f"blei {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_done'}")  # tmp1 => entry_count
        sht_macros.dram_read_ret(tran=tran, addr_reg=REG_LAST_LOAD_ADDR, ret_tran_label=tran_key_ld_ret.getLabel(), tmp_reg=REG_TMP2, arg_lm_words=8, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-LB-send_ld')
        tran.writeAction(f"addi {REG_LD_KEY_CONCURRENCY} {REG_LD_KEY_CONCURRENCY} {1}")  # concurrency++
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: loading, DRAM addr = 0x%lx' {'X0'} {REG_LAST_LOAD_ADDR}")
        # check if number of valid entries in the send is greater than 8
        tran.writeAction(f"bgti {REG_TMP1} {64 // cls.KEY_SIZE} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}")
        # last send, retain last send addr & valid size
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: all loads sent' {'X0'}")
        tran.writeAction(f"addi {REG_TMP1} {REG_LAST_LOAD_EFFECTIVE_WORDS} {0}")  # record last load effective size
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
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: load from 0x%lx returns, mlp = %lu' {'X0'} {OB_LD_RET_ADDR} {REG_LD_KEY_CONCURRENCY}")
        tran_key_ld_ret.writeAction(f"subi {REG_LD_KEY_CONCURRENCY} {REG_LD_KEY_CONCURRENCY} {1}")
        # wait the load value return processed before terminating
        # possible states:
        #   REG_LD_KEY_CONCURRENCY == 0: last key loads returned
        #     REG_LD_VAL_CONCURRENCY <  0: key not matched, to match key
        #     REG_LD_VAL_CONCURRENCY == 0: key matched, all val loads returned, terminate
        #     REG_LD_VAL_CONCURRENCY >  0: key matched, wait for val loads
        #   REG_LD_KEY_CONCURRENCY > 0: more key loads
        #     REG_LD_VAL_CONCURRENCY <  0: key not matched, to match key
        #     REG_LD_VAL_CONCURRENCY == 0: key matched, all val loads returned, wait for key loads
        #     REG_LD_VAL_CONCURRENCY >  0: key matched, wait for key loads & val loads
        tran_key_ld_ret.writeAction(f"blti {REG_LD_VAL_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}")
        tran_key_ld_ret.writeAction(f"bgti {REG_LD_VAL_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}")
        tran_key_ld_ret.writeAction(f"bgti {REG_LD_KEY_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: last in-flight load key & value returned already, terminating... TID = %lu' {'X0'} {'TID'}")
        # unlocked already, no need to unlock
        tran_key_ld_ret.writeAction("yield_terminate")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}: yield")

        """----- Check returned keys -----"""
        # check if return is matched with (last) send address
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}: bne {OB_LD_RET_ADDR} {REG_LAST_LOAD_ADDR} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{7 * cls.KEY_SIZE}'}")  # tmp3 => last send addr
        # if it is the last send, branch to check only the valid entries
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: tail send load returns, num entries = %lu' {'X0'} {REG_LAST_LOAD_EFFECTIVE_WORDS}")  # tmp2 => last send num valid entries
        for i in range(8, 0, -1):
            tran_key_ld_ret.writeAction(f"beqi {REG_LAST_LOAD_EFFECTIVE_WORDS} {i} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}'}")
        # match return data
        for i in range(8, 0, -1):
            tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}'}: beq {f'X{i + 8 - 1}'} {REG_KEY} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}_match'}")

        """-> not matched (fall through)"""
        tran_key_ld_ret.writeAction(f"bgti {REG_LD_KEY_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait_ld'}")
        # from here, all in-flight loads are done & no match found
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: no matched entry found' {'X0'}")
        # return format: (key, 0)
        tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_TMP1} {0}")  # indicate failue
        sht_macros.return_wreg(tran=tran_key_ld_ret, cont_reg=REG_CONT, tmp_reg=REG_TMP0, arg_reg0=REG_KEY, arg_reg1=REG_TMP1)
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
                tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: matched at word offset {i}' {'X0'}")
            tran_key_ld_ret.writeAction(f"sub {OB_LD_RET_ADDR} {REG_TMP1} {REG_TMP1}")
            tran_key_ld_ret.writeAction(f"rshift {REG_TMP1} {REG_TMP1} {int(math.log2(cls.KEY_SIZE))}")
            tran_key_ld_ret.writeAction(f"addi {REG_TMP1} {REG_TMP1} {i}")  # REG_TMP1 => entry index
            tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_ld'}")

        """----- Send load value -----"""
        # calculate value address
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_ld'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_VAL_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_VAL_LD_ADDR} 0 8")
        tran_key_ld_ret.writeAction(f"move {cls.LANE_DESC_STURCT_OFF_VAL_NUM_WORDS}({REG_LANE_DESC_LM_ADDR}) {REG_TMP2} 0 4")
        tran_key_ld_ret.writeAction(f"mul {REG_TMP2} {REG_TMP1} {REG_TMP1}")
        tran_key_ld_ret.writeAction(f"lshift {REG_TMP1} {REG_TMP1} {int(math.log2(cls.WORD_SIZE))}")
        tran_key_ld_ret.writeAction(f"add {REG_VAL_LD_ADDR} {REG_TMP1} {REG_VAL_LD_ADDR}")  # REG_VAL_LD_ADDR => next value ld address

        # Useable registers:
        # REG_TMP0 = "X16"  # last reusable
        # REG_TMP1 = "X17"
        # REG_LANE_DESC_LM_ADDR = "X26"  # may not be useful after entry found
        # REG_BUCKET_BUF_LM_ADDR = "X28"  # can be recalcuated from REG_BUCKET_DESC_LM_ADDR
        # REG_LD_VAL_CONCURRENCY = "X22"  # needed
        # REG_VAL_LD_ADDR = "X23"  # reuseable, can be reloaded from REG_BUCKET_DESC_LM_ADDR if needed
        # ALL THE RESERVED REGISTERS ARE USEABLE BEFORE YIELD!

        # return format (key, mask, selected val0~5)
        tran_key_ld_ret.writeAction(f"addi {REG_MASK} {REG_TMP2} {0}")  # REG_TMP2 -> cur mask, can be reused after this
        tran_key_ld_ret.writeAction(f"movir {REG_LD_VAL_CONCURRENCY} {0}")  # reset ld val concurrency
        tran_key_ld_ret.writeAction(f"movir {REG_TMP0} {0}")  # reset for accumulating number of set bits
        tran_key_ld_ret.writeAction(f"movir {REG_LANE_DESC_LM_ADDR} {0}")  # WARNING: reuse REG_LANE_DESC_LM_ADDR => current num consecutive 1s

        for i in range(6):  # 6 is the max number of value words that can be returned
            # find next part of contiguous 1s
            tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-next_bit_{i}'}: andi {REG_TMP2} {REG_TMP1} {0b1}")
            tran_key_ld_ret.writeAction(f"add {REG_LANE_DESC_LM_ADDR} {REG_TMP1} {REG_LANE_DESC_LM_ADDR}")
            tran_key_ld_ret.writeAction(f"sri {REG_TMP2} {REG_TMP2} {1}")
            tran_key_ld_ret.writeAction(f"addi {REG_VAL_LD_ADDR} {REG_VAL_LD_ADDR} {cls.WORD_SIZE}")
            tran_key_ld_ret.writeAction(f"beqi {REG_TMP1} {1} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-next_bit_{i}'}")
            tran_key_ld_ret.writeAction(f"beqi {REG_LANE_DESC_LM_ADDR} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-next_bit_{i}'}")

            tran_key_ld_ret.writeAction(f"add {REG_LANE_DESC_LM_ADDR} {REG_TMP0} {REG_TMP0}")  # accumulate number of set bits
            tran_key_ld_ret.writeAction(f"sli {REG_LANE_DESC_LM_ADDR} {REG_TMP1} {int(math.log2(cls.WORD_SIZE))}")
            # dial back the ld address with number of 1s counted
            tran_key_ld_ret.writeAction(f"sub {REG_VAL_LD_ADDR} {REG_TMP1} {REG_TMP3}")  # REG_TMP3 => current value ld address
            tran_key_ld_ret.writeAction(f"subi {REG_TMP3} {REG_TMP3} {cls.WORD_SIZE}")  # we are going over by 1 word, so subtract 1 word

            # loading with the proper number of operands
            for j in range(6 - i):
                tran_key_ld_ret.writeAction(f"beqi {REG_LANE_DESC_LM_ADDR} {j + 1} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_val_{i}_{j}'}")
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: shouldn't reach here!' {'X0'}")
            # if cls.DEBUG:
            #     tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: shouldn't reach here!' {'X0'}")
            for j in range(6 - i):
                sht_macros.dram_read_ret(tran=tran_key_ld_ret, addr_reg=REG_TMP3, ret_tran_label=tran_val_ld_ret[i][j].getLabel(), tmp_reg=REG_TMP1, arg_lm_words=(j + 1), branch_label=f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_val_{i}_{j}')
                if cls.DEBUG:
                    tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: loading {j + 1} words value from 0x%lx' {'X0'} {REG_TMP3}")
                tran_key_ld_ret.writeAction(f"addi {REG_LD_VAL_CONCURRENCY} {REG_LD_VAL_CONCURRENCY} {1}")  # increment load val concurrency
                tran_key_ld_ret.writeAction(f"movir {REG_LANE_DESC_LM_ADDR} {0}")  # reset num consecutive 1s
                tran_key_ld_ret.writeAction(f"beqi {REG_TMP2} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-ld_val_done'}")  # if cur mask is zero, break
                if i + j + 1 < 6:
                    tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-next_bit_{i + j + 1}'}")
                else:
                    tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: ERROR! more than 6 bits are set in the mask!' {'X0'}")
                    tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-ld_val_done'}")

        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-ld_val_done'}: yield")

        """==================== TRAN - load val return ===================="""
        OB_LD_VAL = ["X8", "X9", "X10", "X11", "X12", "X13"]
        for i in range(6):  # 6 is the max number of value words that can be returned
            for j in range(6 - i):
                if cls.DEBUG:
                    tran_val_ld_ret[i][j].writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: value load {i} with {j + 1} words returns' {'X0'}")
                tran_val_ld_ret[i][j].writeAction(f"subi {REG_LD_VAL_CONCURRENCY} {REG_LD_VAL_CONCURRENCY} {1}")
                for k in range(0, j + 1):
                    tran_val_ld_ret[i][j].writeAction(f"addi {OB_LD_VAL[k]} {REG_RET_TMP_LM_ADDR[i + k]} {0}")
                    if cls.DEBUG:
                        tran_val_ld_ret[i][j].writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: load to offset {i} #{k} word = %lu' {'X0'} {OB_LD_VAL[k]}")
                # if not all value words returned, wait for the rest
                tran_val_ld_ret[i][j].writeAction(f"bgti {REG_LD_VAL_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret_{i}_{j}-LB-wait'}")

                cls.lock.read_end(tran_val_ld_ret[i][j], REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
                # return format: (key, mask, selected val0~5)
                for k in range(0, 6):
                    tran_val_ld_ret[i][j].writeAction(f"beqi {REG_TMP0} {k + 1} {f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret_{i}_{j}-LB-match_send_val_{k + 1 + 2}'}")
                tran_val_ld_ret[i][j].writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: shouldn't reach here!' {'X0'}")
                for k in range(0, 1):
                    sht_macros.return_wreg(tran=tran_val_ld_ret[i][j], cont_reg=REG_CONT, tmp_reg=REG_TMP1, arg_reg0=REG_KEY, arg_reg1=REG_MASK, arg_reg2=OB_LD_VAL[k], branch_label=f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret_{i}_{j}-LB-match_send_val_{k + 1 + 2}')  # return
                    if cls.DEBUG:
                        tran_val_ld_ret[i][j].writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: return with {k + 1} attrs.' {'X0'}")
                    tran_val_ld_ret[i][j].writeAction(f"bgti {REG_LD_KEY_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret_{i}_{j}-LB-wait'}")
                    tran_val_ld_ret[i][j].writeAction("yieldt")
                for k in range(1, 6):
                    # copy reg to buffer
                    tran_val_ld_ret[i][j].writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret_{i}_{j}-LB-match_send_val_{k + 1 + 2}'}: movrl {REG_KEY} {0 * cls.WORD_SIZE}({REG_BUCKET_BUF_LM_ADDR}) 0 8")
                    tran_val_ld_ret[i][j].writeAction(f"movrl {REG_MASK} {1 * cls.WORD_SIZE}({REG_BUCKET_BUF_LM_ADDR}) 0 8")
                    for m in range(0, k + 1):
                        tran_val_ld_ret[i][j].writeAction(f"movrl {REG_RET_TMP_LM_ADDR[m]} {(2 + m) * cls.WORD_SIZE}({REG_BUCKET_BUF_LM_ADDR}) 0 8")
                    sht_macros.return_wlm(tran=tran_val_ld_ret[i][j], cont_reg=REG_CONT, tmp_reg=REG_TMP1, arg_lm_addr_reg=REG_BUCKET_BUF_LM_ADDR, arg_lm_words=(k + 1 + 2))  # return
                    if cls.DEBUG:
                        tran_val_ld_ret[i][j].writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: return with {k + 1} attrs.' {'X0'}")
                    tran_val_ld_ret[i][j].writeAction(f"bgti {REG_LD_KEY_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret_{i}_{j}-LB-wait'}")
                    tran_val_ld_ret[i][j].writeAction("yieldt")

                tran_val_ld_ret[i][j].writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret_{i}_{j}-LB-wait'}: yield")

    @classmethod
    def get_with_mask_64(cls, tran: EFAProgram.Transition, ret_label: int, tmp_reg0: str, tmp_reg1: str, desc_lm_offset_reg: str, key_reg: str, mask_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_get_with_mask_64.getLabel(), ret_tran_label=ret_label, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=desc_lm_offset_reg, arg_reg1=key_reg, arg_reg2=mask_reg, branch_label=branch_label)

    @classmethod
    def get_with_mask_64_wcont(cls, tran: EFAProgram.Transition, cont_reg: str, tmp_reg: str, desc_lm_offset_reg: str, key_reg: str, mask_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_get_with_mask_64.getLabel(), cont_reg=cont_reg, tmp_reg=tmp_reg, arg_reg0=desc_lm_offset_reg, arg_reg1=key_reg, arg_reg2=mask_reg, branch_label=branch_label)

    @classmethod
    def _update_with_mask_8(cls, state: EFAProgram.State):
        """
        Extended to support mask

        X8  - LANE_DESC_LM_OFFSET(0:31) | BUCKET_DESC_LM_OFFSET(32:63)
        X9  - KEY
        X10 - MASK
        X11 ~ X15 - Elem e
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._update_with_mask_8.__name__

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
        tran = cls.tran_update_with_mask_8
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
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: lock admitted, TID = %lu' {'X0'} {'TID'}")

        # calc desc lm addr
        tran.writeAction(f"lshift {OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET} {REG_LANE_DESC_LM_ADDR} {32}")
        tran.writeAction(f"rshift {REG_LANE_DESC_LM_ADDR} {REG_LANE_DESC_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_LANE_DESC_LM_ADDR} {'X7'} {REG_LANE_DESC_LM_ADDR}")

        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: REG_LANE_DESC_LM_ADDR = 0x%lx, REG_BUCKET_DESC_LM_ADDR = 0x%lx' {'X0'} {REG_LANE_DESC_LM_ADDR} {REG_BUCKET_DESC_LM_ADDR}")

        # copy ob regs
        tran.writeAction(f"addi {OB_KEY} {REG_KEY} {0}")
        tran.writeAction(f"addi {OB_MASK} {REG_MASK} {0}")
        # save cont
        tran.writeAction(f"addi {'X1'} {REG_CONT} {0}")

        # load desc
        tran.writeAction(f"addi {REG_BUCKET_DESC_LM_ADDR} {REG_BUCKET_BUF_LM_ADDR} {cls.BUCKET_DESC_STURCT_OFF_LM_BUF}")

        # # extract num_elem_op
        # # since there is an offset of 2 in the encoding, the desc & key counts are skipped
        # tran.writeAction(f"rshift {'X2'} {REG_NUM_VAL_OP} {20}")
        # tran.writeAction(f"andi {REG_NUM_VAL_OP} {REG_NUM_VAL_OP} {0b111}")
        # tran.writeAction(f"subi {REG_NUM_VAL_OP} {REG_NUM_VAL_OP} {1}")
        # if cls.DEBUG:
        #     tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: number of val operands = %lu' {'X0'} {REG_NUM_VAL_OP}")
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
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: empty bucket, writing without search' {'X0'}")
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
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: sending key write to addr = 0x%lx' {'X0'} {REG_KEY_WR_ADDR}")
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: sending value write to addr = 0x%lx' {'X0'} {REG_VAL_WR_ADDR}")
        # calling with the proper number of operands
        for i in range(1, 8 + 1):
            tran.writeAction(f"beqi {REG_NUM_VAL_OP} {i} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_val_{i}'}")
        tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: shouldn't reach here!' {'X0'}")
        for i in range(1, 8 + 1):
            # tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_val_{i}'}: send_dmlm_wret {REG_VAL_WR_ADDR} {tran_key_st_ret.getLabel()} {REG_BUCKET_BUF_LM_ADDR} {i}")
            sht_macros.dram_write_lm_ret(tran=tran, addr_reg=REG_VAL_WR_ADDR, ret_tran_label=tran_key_st_ret.getLabel(), tmp_reg=REG_TMP2, arg_lm_addr_reg=REG_BUCKET_BUF_LM_ADDR, arg_lm_words=i, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-LB-send_val_{i}')
            if cls.DEBUG:
                tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: writing {i} words value' {'X0'}")
            tran.writeAction("yield")

        """----- Filled Bucket -----"""
        # ----- already have entires, send load entries -----
        # init
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-setup_send_ld'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_LAST_LOAD_ADDR} 0 8")  # tmp3 => key load start address
        tran.writeAction(f"mov_imm2reg {REG_LD_CONCURRENCY} {0}")
        tran.writeAction(f"mov_imm2reg {REG_ST_CONCURRENCY} {-2}")

        tran.writeAction(f"blei {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_done'}")  # tmp1 => entry_count
        # tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_ld'}: send_dmlm_ld_wret {REG_LAST_LOAD_ADDR} {tran_key_ld_ret.getLabel()} {8}")
        sht_macros.dram_read_ret(tran=tran, addr_reg=REG_LAST_LOAD_ADDR, ret_tran_label=tran_key_ld_ret.getLabel(), tmp_reg=REG_TMP2, arg_lm_words=8, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-LB-send_ld')
        tran.writeAction(f"addi {REG_LD_CONCURRENCY} {REG_LD_CONCURRENCY} {1}")  # concurrency++
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: loading, DRAM addr = 0x%lx' {'X0'} {REG_LAST_LOAD_ADDR}")
        # check if number of valid entries in the send is greater than 8
        tran.writeAction(f"bgti {REG_TMP1} {64 // cls.KEY_SIZE} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}")
        # last send, retain last send addr & valid size
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: all loads sent' {'X0'}")
        tran.writeAction(f"addi {REG_TMP1} {REG_LAST_LOAD_EFFECTIVE_WORDS} {0}")  # record last load effective size
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
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: load from 0x%lx returns, mlp = %lu' {'X0'} {OB_LD_RET_ADDR} {REG_LD_CONCURRENCY}")
        tran_key_ld_ret.writeAction(f"subi {REG_LD_CONCURRENCY} {REG_LD_CONCURRENCY} {1}")
        # possible situations:
        # ld concurrency >= 0
        # st concurrency == -2, no store yet, not matched, to match
        # st concurrency == -1, no store yet, matched, wait
        # st concurrency == 0, store done, if ld concurrency == 0, terminate
        # st concurrency == 1, store not done, wait
        # st concurrency == 2 (impossible, as it is only set when the last load is processed)
        tran_key_ld_ret.writeAction(f"beqi {REG_ST_CONCURRENCY} {-2} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}")
        tran_key_ld_ret.writeAction(f"bnei {REG_ST_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}")
        tran_key_ld_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: last in-flight load & store finished, terminating... TID = %lu' {'X0'} {'TID'}")
        # unlocked already, no need to unlock
        # return format: (key, mask)
        sht_macros.return_wreg(tran=tran_key_ld_ret, cont_reg=REG_CONT, tmp_reg=REG_TMP1, arg_reg0=REG_KEY, arg_reg1=REG_VAL_WR_ADDR)
        tran_key_ld_ret.writeAction("yield_terminate")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}: yield")

        """----- Check returned keys -----"""
        # check if return is matched with (last) send address
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}: bne {OB_LD_RET_ADDR} {REG_LAST_LOAD_ADDR} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{7 * cls.KEY_SIZE}'}")  # tmp3 => last send addr
        # if it is the last send, branch to check only the valid entries
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: tail send load returns, num entries = %lu' {'X0'} {REG_LAST_LOAD_EFFECTIVE_WORDS}")  # tmp2 => last send num valid entries
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
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: no matched entry found' {'X0'}")
        # check if there is space at the end of the allocation area
        tran_key_ld_ret.writeAction(f"move {cls.LANE_DESC_STURCT_OFF_ENTRIES_PER_BUCKET}({REG_LANE_DESC_LM_ADDR}) {REG_TMP1} 0 4")  # REG_TMP1 => num_alloc_entries
        tran_key_ld_ret.writeAction(f"move {cls.BUCKET_DESC_STURCT_OFF_ENTRY_COUNT}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP2} 0 4")  # REG_TMP2 => entry count
        tran_key_ld_ret.writeAction(f"blt {REG_TMP2} {REG_TMP1} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-new_entry'}")
        # -> out of space!
        tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: bucket full, add FAILED!' {'X0'}")
        # if cls.DEBUG:
        #     tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: bucket full, add FAILED!' {'X0'}")
        # return format: (key, mask)
        tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_TMP1} {0}")  # indicate failue with addr == 0
        sht_macros.return_wreg(tran=tran_key_ld_ret, cont_reg=REG_CONT, tmp_reg=REG_TMP2, arg_reg0=REG_KEY, arg_reg1=REG_TMP1)
        # sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, 'X0', REG_TMP3)  # for debug
        cls.lock.write_end(tran_key_ld_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        tran_key_ld_ret.writeAction("yield_terminate")  # only if running out of space!
        # -> new entry
        # calculate the address of the key
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-new_entry'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_KEY_WR_ADDR} 0 8")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: storing in a new entry' {'X0'}")
        tran_key_ld_ret.writeAction(f"lshift {REG_TMP2} {REG_TMP1} {int(math.log2(cls.KEY_SIZE))}")
        tran_key_ld_ret.writeAction(f"add {REG_KEY_WR_ADDR} {REG_TMP1} {REG_KEY_WR_ADDR}")
        # store key
        # tran_key_ld_ret.writeAction(f"sendr_dmlm_wret {REG_KEY_WR_ADDR} {tran_key_st_ret.getLabel()} {REG_KEY}")  # writing only one word
        sht_macros.dram_write_reg_ret(tran=tran_key_ld_ret, addr_reg=REG_KEY_WR_ADDR, ret_tran_label=tran_key_st_ret.getLabel(), tmp_reg=REG_TMP3, arg_reg0=REG_KEY)
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: sending key write to addr = 0x%lx' {'X0'} {REG_KEY_WR_ADDR}")
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
        tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: shouldn't reach here!' {'X0'}")
        for i in range(1, 8 + 1):
            # tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-nomatch_send_val_{i}'}: send_dmlm_wret {REG_VAL_WR_ADDR} {tran_key_st_ret.getLabel()} {REG_BUCKET_BUF_LM_ADDR} {i}")
            sht_macros.dram_write_lm_ret(tran=tran_key_ld_ret, addr_reg=REG_VAL_WR_ADDR, ret_tran_label=tran_key_st_ret.getLabel(), tmp_reg=REG_TMP3, arg_lm_addr_reg=REG_BUCKET_BUF_LM_ADDR, arg_lm_words=i, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-nomatch_send_val_{i}')
            if cls.DEBUG:
                tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: writing {i} words value' {'X0'}")
            tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-nomatch_send_val_done'}")
        # count up the entries
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-nomatch_send_val_done'}: addi {REG_TMP2} {REG_TMP2} {1}")
        tran_key_ld_ret.writeAction(f"move {REG_TMP2} {cls.BUCKET_DESC_STURCT_OFF_ENTRY_COUNT}({REG_BUCKET_DESC_LM_ADDR}) 0 4")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: sending value write to addr = 0x%lx' {'X0'} {REG_VAL_WR_ADDR}")
        tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_ST_CONCURRENCY} {2}")  # mark value written & all loads done
        # -> wait for in-flight load to come back
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait_ld'}: yield")

        """-> matched"""
        for i in range(0, 8):
            # calculate the entry index from key address
            tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{i * cls.KEY_SIZE}_match'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP1} 0 8")
            if cls.DEBUG:
                tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: matched at word offset {i}' {'X0'}")
            tran_key_ld_ret.writeAction(f"sub {OB_LD_RET_ADDR} {REG_TMP1} {REG_TMP1}")
            tran_key_ld_ret.writeAction(f"rshift {REG_TMP1} {REG_TMP1} {int(math.log2(cls.KEY_SIZE))}")
            tran_key_ld_ret.writeAction(f"addi {REG_TMP1} {REG_TMP1} {i}")  # REG_TMP1 => entry index
            tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_ST_CONCURRENCY} {-1}")  # mark matched but not storing yet
            tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_val_ld'}")

        """----- Send load value -----"""
        # calculate value address
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_val_ld'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_VAL_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_VAL_WR_ADDR} 0 8")
        tran_key_ld_ret.writeAction(f"move {cls.LANE_DESC_STURCT_OFF_VAL_NUM_WORDS}({REG_LANE_DESC_LM_ADDR}) {REG_TMP2} 0 4")
        tran_key_ld_ret.writeAction(f"mul {REG_TMP2} {REG_TMP1} {REG_TMP1}")
        tran_key_ld_ret.writeAction(f"lshift {REG_TMP1} {REG_TMP1} {int(math.log2(cls.WORD_SIZE))}")
        tran_key_ld_ret.writeAction(f"add {REG_VAL_WR_ADDR} {REG_TMP1} {REG_VAL_WR_ADDR}")

        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: sending load to addr = 0x%lx' {'X0'} {REG_VAL_WR_ADDR}")

        # calling with the proper number of operands
        for i in range(1, 9):
            tran_key_ld_ret.writeAction(f"beqi {REG_NUM_VAL_OP} {i} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_{i}'}")
        tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_8'}")  # for value words > 8, load the first 8 words
        for i in range(1, 9):
            # tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_{i}'}: send_dmlm_ld_wret {REG_VAL_WR_ADDR} {tran_val_ld_ret.getLabel()} {i}")
            sht_macros.dram_read_ret(tran=tran_key_ld_ret, addr_reg=REG_VAL_WR_ADDR, ret_tran_label=tran_val_ld_ret.getLabel(), tmp_reg=REG_TMP3, arg_lm_words=i, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_{i}')
            if cls.DEBUG:
                tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: loading {i} words value' {'X0'}")
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
            tran_val_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: sending write to addr = 0x%lx' {'X0'} {REG_VAL_WR_ADDR}")
        # calling with the proper number of operands
        for i in range(1, 9):
            tran_val_ld_ret.writeAction(f"beqi {REG_NUM_VAL_OP} {i} {f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-match_send_val_{i}'}")
        tran_val_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: shouldn't reach here!' {'X0'}")
        for i in range(1, 9):
            # tran_val_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-match_send_val_{i}'}: send_dmlm_wret {REG_VAL_WR_ADDR} {tran_key_st_ret.getLabel()} {REG_BUCKET_BUF_LM_ADDR} {i}")
            sht_macros.dram_write_lm_ret(tran=tran_val_ld_ret, addr_reg=REG_VAL_WR_ADDR, ret_tran_label=tran_key_st_ret.getLabel(), tmp_reg=REG_TMP1, arg_lm_addr_reg=REG_BUCKET_BUF_LM_ADDR, arg_lm_words=i, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-match_send_val_{i}')
            if cls.DEBUG:
                tran_val_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: writing {i} words value' {'X0'}")
            tran_val_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-match_send_val_done'}")
        tran_val_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-match_send_val_done'}: mov_imm2reg {REG_ST_CONCURRENCY} {1}")  # mark value written
        tran_val_ld_ret.writeAction("yield")

        """==================== TRAN - store key val return ===================="""
        tran_key_st_ret.writeAction(f"subi {REG_ST_CONCURRENCY} {REG_ST_CONCURRENCY} {1}")
        tran_key_st_ret.writeAction(f"bgti {REG_ST_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_st_ret-LB-wait'}")
        tran_key_st_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_st_ret-LB-ld_wait'}")
        if cls.DEBUG:
            tran_key_st_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: write to 0x%lx returns & no load waiting, terminating... TID = %lu' {'X0'} {'X8'} {'TID'}")
        cls.lock.write_end(tran_key_st_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        # return format: (key, mask)
        sht_macros.return_wreg(tran=tran_key_st_ret, cont_reg=REG_CONT, tmp_reg=REG_TMP1, arg_reg0=REG_KEY, arg_reg1=REG_MASK)
        # sht_macros.return_wreg(tran_key_st_ret, REG_CONT, 'X0', REG_VAL_WR_ADDR)  # debug
        tran_key_st_ret.writeAction("yield_terminate")
        tran_key_st_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_st_ret-LB-ld_wait'}: addi {REG_TMP1} {REG_TMP1} {0}")  # FIXME: dummy
        cls.lock.write_end(tran_key_st_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        if cls.DEBUG:
            tran_key_st_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: write to 0x%lx returns & all stores done, waiting loads return...' {'X0'} {'X8'}")
        tran_key_st_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_st_ret-LB-wait'}: yield")

    @classmethod
    def update_with_mask_8(cls, tran: EFAProgram.Transition, ret_label: int, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, arg_lm_words: int, dst_nwid_reg: str = 'X0', branch_label: str = "") -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_update_with_mask_8.getLabel(), ret_tran_label=ret_label, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=arg_lm_words, branch_label=branch_label)

    @classmethod
    def update_with_mask_8_wcont(cls, tran: EFAProgram.Transition, cont_reg: str, tmp_reg0: str, arg_lm_addr_reg: str, arg_lm_words: int, dst_nwid_reg: str = 'X0', branch_label: str = "") -> None:
        sht_macros.call_wlm_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_update_with_mask_8.getLabel(), cont_reg=cont_reg, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=arg_lm_words, branch_label=branch_label)

    @classmethod
    def _update_with_mask_64(cls, state: EFAProgram.State):
        """
        Extended to support mask

        X8  - LANE_DESC_LM_OFFSET(0:31) | BUCKET_DESC_LM_OFFSET(32:63)
        X9  - KEY
        X10 - MASK
        X11 ~ X15 - Elem e
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._update_with_mask_64.__name__

        MAX_VAL_NUM_WORDS = 5

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_update_with_mask_64
        if tran is None:
            return
        cls.tran_label_update_with_mask = tran.getLabel()
        tran_key_ld_ret = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-key_ld_ret")
        tran_key_st_ret = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-key_st_ret")

        """******************** THREAD - update with mask 64 ********************"""
        REG_TMP0 = "X16"
        REG_TMP1 = "X17"
        REG_TMP2 = "X18"
        REG_TMP3 = "X19"

        REG_LD_CONCURRENCY = "X20"
        REG_ST_CONCURRENCY = "X21"
        REG_KEY_WR_ADDR = "X22"
        REG_VAL_WR_ADDR = "X23"

        REG_LAST_LOAD_EFFECTIVE_WORDS = "X24"
        REG_LAST_LOAD_ADDR = "X25"

        REG_LANE_DESC_LM_ADDR = "X26"
        REG_BUCKET_DESC_LM_ADDR = "X27"
        REG_BUCKET_BUF_LM_ADDR = "X28"
        REG_KEY = "X29"
        REG_MASK = "X30"

        REG_CONT = "X31"

        """==================== TRAN - function entry ===================="""
        OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET = "X8"
        OB_KEY = "X9"
        OB_MASK = "X10"
        OB_VAL = "X11"

        """----- Prep -----"""
        # calc desc lm addr
        tran.writeAction(f"rshift {OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET} {REG_BUCKET_DESC_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_BUCKET_DESC_LM_ADDR} {'X7'} {REG_BUCKET_DESC_LM_ADDR}")

        # get lock
        cls.lock.write_begin_var(tran, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: lock admitted, TID = %lu' {'X0'} {'TID'}")

        # calc desc lm addr
        tran.writeAction(f"lshift {OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET} {REG_LANE_DESC_LM_ADDR} {32}")
        tran.writeAction(f"rshift {REG_LANE_DESC_LM_ADDR} {REG_LANE_DESC_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_LANE_DESC_LM_ADDR} {'X7'} {REG_LANE_DESC_LM_ADDR}")

        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: REG_LANE_DESC_LM_ADDR = 0x%lx, REG_BUCKET_DESC_LM_ADDR = 0x%lx' {'X0'} {REG_LANE_DESC_LM_ADDR} {REG_BUCKET_DESC_LM_ADDR}")

        # copy ob regs
        tran.writeAction(f"addi {OB_KEY} {REG_KEY} {0}")
        tran.writeAction(f"addi {OB_MASK} {REG_MASK} {0}")
        # save cont
        tran.writeAction(f"addi {'X1'} {REG_CONT} {0}")

        # load desc
        tran.writeAction(f"addi {REG_BUCKET_DESC_LM_ADDR} {REG_BUCKET_BUF_LM_ADDR} {cls.BUCKET_DESC_STURCT_OFF_LM_BUF}")

        # extract num_elem_op
        # since there is an offset of 2 in the encoding, the desc & key counts are skipped
        tran.writeAction(f"rshift {'X2'} {REG_TMP0} {20}")
        tran.writeAction(f"andi {REG_TMP0} {REG_TMP0} {0b111}")
        tran.writeAction(f"subi {REG_TMP0} {REG_TMP0} {1}")  # subtract 1 to get the number of value operands
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: number of val operands = %lu' {'X0'} {REG_TMP0}")
            for i in range(5):
                tran.writeAction(f"beqi {REG_TMP0} {i + 1} {f'{CLS_NAME}-{FN_NAME}-TR-LB-dbg_num_val_op_{i}'}")
            for i in range(5):
                tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-dbg_num_val_op_{i}'}: print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: KEY = %lu, MASK = 0x%lx, {', '.join(f'X{i} = %lu' for i in range(11, 11 + i + 1))}' {'X0'} {OB_KEY} {OB_MASK} {' '.join(f'X{i}' for i in range(11, 11 + i + 1))}")
                tran.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-LB-dbg_num_val_op_done'}")
        # copy val to buffer
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-dbg_num_val_op_done'}: bcpyol {OB_VAL} {REG_BUCKET_BUF_LM_ADDR} {REG_TMP0}")

        tran.writeAction(f"move {cls.BUCKET_DESC_STURCT_OFF_ENTRY_COUNT}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP1} 0 4")  # tmp1 => entry_count

        """----- Empty Bucket -----"""
        # ----- if entry count is zero, write directly -----
        tran.writeAction(f"bgti {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-setup_send_ld'}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: empty bucket, writing without search' {'X0'}")
        # update entry count
        tran.writeAction(f"addi {REG_TMP1} {REG_TMP1} {1}")
        tran.writeAction(f"move {REG_TMP1} {cls.BUCKET_DESC_STURCT_OFF_ENTRY_COUNT}({REG_BUCKET_DESC_LM_ADDR}) 0 4")

        tran.writeAction(f"mov_imm2reg {REG_LD_CONCURRENCY} {0}")
        tran.writeAction(f"mov_imm2reg {REG_ST_CONCURRENCY} {1}")
        tran.writeAction(f"move {cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_KEY_WR_ADDR} 0 8")
        tran.writeAction(f"move {cls.BUCKET_DESC_STURCT_OFF_DRAM_VAL_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_VAL_WR_ADDR} 0 8")
        sht_macros.dram_write_reg_ret(tran=tran, addr_reg=REG_KEY_WR_ADDR, ret_tran_label=tran_key_st_ret.getLabel(), tmp_reg=REG_TMP2, arg_reg0=REG_KEY)
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: sending key write to addr = 0x%lx' {'X0'} {REG_KEY_WR_ADDR}")
        # store value
        # Do multiple sends based on the mask
        tran.writeAction(f"addi {REG_MASK} {REG_TMP1} {0}")  # REG_TMP1 => current mask
        tran.writeAction(f"addi {REG_BUCKET_BUF_LM_ADDR} {REG_TMP2} {0}")  # REG_TMP2 => current LM buffer address
        tran.writeAction(f"movir {REG_TMP3} {0}")  # REG_TMP3 => current num consecutive 1s
        tran.writeAction(f"addi {REG_VAL_WR_ADDR} {REG_LAST_LOAD_EFFECTIVE_WORDS} {0}")  # WARNING: repurposing REG_LAST_LOAD_EFFECTIVE_WORDS => val dram write addr

        # loop
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-next_bit'}: andi {REG_TMP1} {REG_TMP0} {0b1}")
        tran.writeAction(f"add {REG_TMP3} {REG_TMP0} {REG_TMP3}")
        tran.writeAction(f"sri {REG_TMP1} {REG_TMP1} {1}")
        tran.writeAction(f"addi {REG_LAST_LOAD_EFFECTIVE_WORDS} {REG_LAST_LOAD_EFFECTIVE_WORDS} {cls.WORD_SIZE}")
        tran.writeAction(f"beqi {REG_TMP0} {1} {f'{CLS_NAME}-{FN_NAME}-TR-LB-next_bit'}")
        tran.writeAction(f"beqi {REG_TMP3} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-next_bit'}")

        # dial back the st address with number of 1s counted
        tran.writeAction(f"sli {REG_TMP3} {REG_TMP0} {int(math.log2(cls.WORD_SIZE))}")
        tran.writeAction(f"sub {REG_LAST_LOAD_EFFECTIVE_WORDS} {REG_TMP0} {REG_LAST_LOAD_ADDR}")  # WARNING: repurposing REG_LAST_LOAD_ADDR => current val dram write addr
        tran.writeAction(f"subi {REG_LAST_LOAD_ADDR} {REG_LAST_LOAD_ADDR} {cls.WORD_SIZE}")  # we are going over by 1 word, so subtract 1 word

        # storing with the proper number of operands
        for i in range(1, MAX_VAL_NUM_WORDS + 1):
            tran.writeAction(f"beqi {REG_TMP3} {i} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_val_{i}'}")
        tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: shouldn't reach here!' {'X0'}")
        # if cls.DEBUG:
        #     tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: shouldn't reach here!' {'X0'}")
        for i in range(1, MAX_VAL_NUM_WORDS + 1):
            sht_macros.dram_write_lm_ret(tran=tran, addr_reg=REG_LAST_LOAD_ADDR, ret_tran_label=tran_key_st_ret.getLabel(), tmp_reg=REG_TMP3, arg_lm_addr_reg=REG_TMP2, arg_lm_words=i, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-LB-send_val_{i}')
            if cls.DEBUG:
                tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: writing {i} words value to 0x%lx' {'X0'} {REG_LAST_LOAD_ADDR}")
            tran.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-LB-cur_val_sent'}")
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-cur_val_sent'}: addi {REG_ST_CONCURRENCY} {REG_ST_CONCURRENCY} {1}")  # increment store concurrency
        tran.writeAction(f"movir {REG_TMP3} {0}")  # reset num consecutive 1s
        tran.writeAction(f"add {REG_TMP2} {REG_TMP0} {REG_TMP2}")  # increment lm buf addr
        tran.writeAction(f"bnei {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-next_bit'}")  # if mask is not zero, continue
        tran.writeAction("yield")

        """----- Filled Bucket -----"""
        # ----- already have entires, send load entries -----
        # init
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-setup_send_ld'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_LAST_LOAD_ADDR} 0 8")  # tmp3 => key load start address
        tran.writeAction(f"mov_imm2reg {REG_LD_CONCURRENCY} {0}")
        tran.writeAction(f"mov_imm2reg {REG_ST_CONCURRENCY} {-2}")

        tran.writeAction(f"blei {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_done'}")  # tmp1 => entry_count
        sht_macros.dram_read_ret(tran=tran, addr_reg=REG_LAST_LOAD_ADDR, ret_tran_label=tran_key_ld_ret.getLabel(), tmp_reg=REG_TMP2, arg_lm_words=8, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-LB-send_ld')
        tran.writeAction(f"addi {REG_LD_CONCURRENCY} {REG_LD_CONCURRENCY} {1}")  # concurrency++
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: loading, DRAM addr = 0x%lx' {'X0'} {REG_LAST_LOAD_ADDR}")
        # check if number of valid entries in the send is greater than 8
        tran.writeAction(f"bgti {REG_TMP1} {64 // cls.KEY_SIZE} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}")
        # last send, retain last send addr & valid size
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: all loads sent' {'X0'}")
        tran.writeAction(f"addi {REG_TMP1} {REG_LAST_LOAD_EFFECTIVE_WORDS} {0}")  # record last load effective size
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
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: load from 0x%lx returns, mlp = %lu' {'X0'} {OB_LD_RET_ADDR} {REG_LD_CONCURRENCY}")
        tran_key_ld_ret.writeAction(f"subi {REG_LD_CONCURRENCY} {REG_LD_CONCURRENCY} {1}")
        # possible situations:
        # ld concurrency >= 0
        # st concurrency == -2, no store yet, not matched, to match
        # st concurrency == -1, no store yet, matched, wait
        # st concurrency == 0, store done, if ld concurrency == 0, terminate
        # st concurrency == 1, store not done, wait
        # st concurrency == 2 (impossible, as it is only set when the last load is processed)
        tran_key_ld_ret.writeAction(f"beqi {REG_ST_CONCURRENCY} {-2} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}")
        tran_key_ld_ret.writeAction(f"bnei {REG_ST_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}")
        tran_key_ld_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: last in-flight load & store finished, terminating... TID = %lu' {'X0'} {'TID'}")
        # unlocked already, no need to unlock
        # return format: (key, mask)
        sht_macros.return_wreg(tran=tran_key_ld_ret, cont_reg=REG_CONT, tmp_reg=REG_TMP0, arg_reg0=REG_KEY, arg_reg1=REG_VAL_WR_ADDR)
        tran_key_ld_ret.writeAction("yield_terminate")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}: yield")

        """----- Check returned keys -----"""
        # check if return is matched with (last) send address
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}: bne {OB_LD_RET_ADDR} {REG_LAST_LOAD_ADDR} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{7 * cls.KEY_SIZE}'}")  # tmp3 => last send addr
        # if it is the last send, branch to check only the valid entries
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: tail send load returns, num entries = %lu' {'X0'} {REG_LAST_LOAD_EFFECTIVE_WORDS}")  # tmp2 => last send num valid entries
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
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: no matched entry found' {'X0'}")
        # check if there is space at the end of the allocation area
        tran_key_ld_ret.writeAction(f"move {cls.LANE_DESC_STURCT_OFF_ENTRIES_PER_BUCKET}({REG_LANE_DESC_LM_ADDR}) {REG_TMP1} 0 4")  # REG_TMP1 => num_alloc_entries
        tran_key_ld_ret.writeAction(f"move {cls.BUCKET_DESC_STURCT_OFF_ENTRY_COUNT}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP2} 0 4")  # REG_TMP2 => entry count
        tran_key_ld_ret.writeAction(f"blt {REG_TMP2} {REG_TMP1} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-new_entry'}")
        # -> out of space!
        tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: bucket full, add FAILED!' {'X0'}")
        # if cls.DEBUG:
        #     tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: bucket full, add FAILED!' {'X0'}")
        # return format: (key, mask)
        tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_TMP1} {0}")  # indicate failue with addr == 0
        sht_macros.return_wreg(tran=tran_key_ld_ret, cont_reg=REG_CONT, tmp_reg=REG_TMP0, arg_reg0=REG_KEY, arg_reg1=REG_TMP1)
        # sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, 'X0', REG_TMP3)  # for debug
        cls.lock.write_end(tran_key_ld_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        tran_key_ld_ret.writeAction("yield_terminate")  # only if running out of space!
        # -> new entry
        # calculate the address of the key
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-new_entry'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_KEY_WR_ADDR} 0 8")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: storing in a new entry' {'X0'}")
        tran_key_ld_ret.writeAction(f"lshift {REG_TMP2} {REG_TMP1} {int(math.log2(cls.KEY_SIZE))}")
        tran_key_ld_ret.writeAction(f"add {REG_KEY_WR_ADDR} {REG_TMP1} {REG_KEY_WR_ADDR}")
        # store key
        sht_macros.dram_write_reg_ret(tran=tran_key_ld_ret, addr_reg=REG_KEY_WR_ADDR, ret_tran_label=tran_key_st_ret.getLabel(), tmp_reg=REG_TMP3, arg_reg0=REG_KEY)
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: sending key write to addr = 0x%lx' {'X0'} {REG_KEY_WR_ADDR}")
        # calculate the address of the value
        tran_key_ld_ret.writeAction(f"move {cls.BUCKET_DESC_STURCT_OFF_DRAM_VAL_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_VAL_WR_ADDR} 0 8")
        tran_key_ld_ret.writeAction(f"move {cls.LANE_DESC_STURCT_OFF_VAL_NUM_WORDS}({REG_LANE_DESC_LM_ADDR}) {REG_TMP1} 0 4")
        tran_key_ld_ret.writeAction(f"mul {REG_TMP2} {REG_TMP1} {REG_TMP1}")
        tran_key_ld_ret.writeAction(f"lshift {REG_TMP1} {REG_TMP1} {int(math.log2(cls.WORD_SIZE))}")
        tran_key_ld_ret.writeAction(f"add {REG_VAL_WR_ADDR} {REG_TMP1} {REG_VAL_WR_ADDR}")
        # count up the entries
        tran_key_ld_ret.writeAction(f"addi {REG_TMP2} {REG_TMP2} {1}")
        tran_key_ld_ret.writeAction(f"move {REG_TMP2} {cls.BUCKET_DESC_STURCT_OFF_ENTRY_COUNT}({REG_BUCKET_DESC_LM_ADDR}) 0 4")
        tran_key_ld_ret.writeAction(f"movir {REG_ST_CONCURRENCY} {1}")  # init store concurrency, 1 for the key write
        tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_val_st'}")

        """-> matched"""
        for i in range(0, 8):
            # calculate the entry index from key address
            tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{i * cls.KEY_SIZE}_match'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP1} 0 8")
            if cls.DEBUG:
                tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: matched at word offset {i}' {'X0'}")
            tran_key_ld_ret.writeAction(f"sub {OB_LD_RET_ADDR} {REG_TMP1} {REG_TMP1}")
            tran_key_ld_ret.writeAction(f"rshift {REG_TMP1} {REG_TMP1} {int(math.log2(cls.KEY_SIZE))}")
            tran_key_ld_ret.writeAction(f"addi {REG_TMP1} {REG_TMP1} {i}")  # REG_TMP1 => entry index
            tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_ST_CONCURRENCY} {-1}")  # mark matched but not storing yet
            tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_val_ld'}")

        # calculate value address
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_val_ld'}: move {cls.BUCKET_DESC_STURCT_OFF_DRAM_VAL_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_VAL_WR_ADDR} 0 8")
        tran_key_ld_ret.writeAction(f"move {cls.LANE_DESC_STURCT_OFF_VAL_NUM_WORDS}({REG_LANE_DESC_LM_ADDR}) {REG_TMP2} 0 4")
        tran_key_ld_ret.writeAction(f"mul {REG_TMP2} {REG_TMP1} {REG_TMP1}")
        tran_key_ld_ret.writeAction(f"lshift {REG_TMP1} {REG_TMP1} {int(math.log2(cls.WORD_SIZE))}")
        tran_key_ld_ret.writeAction(f"add {REG_VAL_WR_ADDR} {REG_TMP1} {REG_VAL_WR_ADDR}")
        tran_key_ld_ret.writeAction(f"movir {REG_ST_CONCURRENCY} {0}")  # init store concurrency

        """----- Send store value (shared among new entry and matched) -----"""
        # store value
        # Do multiple sends based on the mask
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_val_st'}: addi {REG_MASK} {REG_TMP1} {0}")  # REG_TMP1 => current mask
        tran_key_ld_ret.writeAction(f"addi {REG_BUCKET_BUF_LM_ADDR} {REG_TMP2} {0}")  # REG_TMP2 => current LM buffer address
        tran_key_ld_ret.writeAction(f"movir {REG_TMP3} {0}")  # REG_TMP3 => current num consecutive 1s
        tran_key_ld_ret.writeAction(f"addi {REG_VAL_WR_ADDR} {REG_LAST_LOAD_EFFECTIVE_WORDS} {0}")  # WARNING: repurposing REG_LAST_LOAD_EFFECTIVE_WORDS => val dram write byte
        # loop
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-next_bit'}: andi {REG_TMP1} {REG_TMP0} {0b1}")
        tran_key_ld_ret.writeAction(f"add {REG_TMP3} {REG_TMP0} {REG_TMP3}")
        tran_key_ld_ret.writeAction(f"sri {REG_TMP1} {REG_TMP1} {1}")
        tran_key_ld_ret.writeAction(f"addi {REG_LAST_LOAD_EFFECTIVE_WORDS} {REG_LAST_LOAD_EFFECTIVE_WORDS} {cls.WORD_SIZE}")
        tran_key_ld_ret.writeAction(f"beqi {REG_TMP0} {1} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-next_bit'}")
        tran_key_ld_ret.writeAction(f"beqi {REG_TMP3} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-next_bit'}")

        # dial back the st address with number of 1s counted
        tran_key_ld_ret.writeAction(f"sli {REG_TMP3} {REG_TMP0} {int(math.log2(cls.WORD_SIZE))}")
        tran_key_ld_ret.writeAction(f"sub {REG_LAST_LOAD_EFFECTIVE_WORDS} {REG_TMP0} {REG_LAST_LOAD_ADDR}")  # WARNING: repurposing REG_LAST_LOAD_ADDR => current val dram write addr
        tran_key_ld_ret.writeAction(f"subi {REG_LAST_LOAD_ADDR} {REG_LAST_LOAD_ADDR} {cls.WORD_SIZE}")  # we are going over by 1 word, so subtract 1 word

        # storing with the proper number of operands
        for i in range(1, MAX_VAL_NUM_WORDS + 1):
            tran_key_ld_ret.writeAction(f"beqi {REG_TMP3} {i} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_val_{i}'}")
        tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: shouldn't reach here!' {'X0'}")
        # if cls.DEBUG:
        #     tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: shouldn't reach here!' {'X0'}")
        for i in range(1, MAX_VAL_NUM_WORDS + 1):
            sht_macros.dram_write_lm_ret(tran=tran_key_ld_ret, addr_reg=REG_LAST_LOAD_ADDR, ret_tran_label=tran_key_st_ret.getLabel(), tmp_reg=REG_TMP3, arg_lm_addr_reg=REG_TMP2, arg_lm_words=i, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_val_{i}')
            if cls.DEBUG:
                tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: writing {i} words value to 0x%lx' {'X0'} {REG_LAST_LOAD_ADDR}")
            tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-cur_val_sent'}")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-cur_val_sent'}: addi {REG_ST_CONCURRENCY} {REG_ST_CONCURRENCY} {1}")  # increment store concurrency
        # increment lm buf addr
        tran_key_ld_ret.writeAction(f"movir {REG_TMP3} {0}")  # reset num consecutive 1s
        tran_key_ld_ret.writeAction(f"add {REG_TMP2} {REG_TMP0} {REG_TMP2}")
        tran_key_ld_ret.writeAction(f"bnei {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-next_bit'}")  # if mask is not zero, continue
        # -> wait for in-flight load to come back
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait_ld'}: yield")

        """==================== TRAN - store key val return ===================="""
        tran_key_st_ret.writeAction(f"subi {REG_ST_CONCURRENCY} {REG_ST_CONCURRENCY} {1}")
        tran_key_st_ret.writeAction(f"bgti {REG_ST_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_st_ret-LB-wait'}")
        tran_key_st_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_st_ret-LB-ld_wait'}")
        if cls.DEBUG:
            tran_key_st_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: write to 0x%lx returns & no load waiting, terminating... TID = %lu' {'X0'} {'X8'} {'TID'}")
        cls.lock.write_end(tran_key_st_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        # return format: (key, mask)
        sht_macros.return_wreg(tran=tran_key_st_ret, cont_reg=REG_CONT, tmp_reg=REG_TMP0, arg_reg0=REG_KEY, arg_reg1=REG_MASK)
        # sht_macros.return_wreg(tran_key_st_ret, REG_CONT, 'X0', REG_VAL_WR_ADDR)  # debug
        tran_key_st_ret.writeAction("yield_terminate")
        tran_key_st_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_st_ret-LB-ld_wait'}: addi {REG_TMP1} {REG_TMP1} {0}")  # FIXME: dummy
        cls.lock.write_end(tran_key_st_ret, REG_BUCKET_DESC_LM_ADDR, REG_TMP1)
        if cls.DEBUG:
            tran_key_st_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: write to 0x%lx returns & all stores done, waiting loads return...' {'X0'} {'X8'}")
        tran_key_st_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_st_ret-LB-wait'}: yield")

    @classmethod
    def update_with_mask_64(cls, tran: EFAProgram.Transition, ret_label: int, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, arg_lm_words: int, dst_nwid_reg: str = 'X0', branch_label: str = "") -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_update_with_mask_64.getLabel(), ret_tran_label=ret_label, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=arg_lm_words, branch_label=branch_label)

    @classmethod
    def update_with_mask_64_wcont(cls, tran: EFAProgram.Transition, cont_reg: str, tmp_reg0: str, arg_lm_addr_reg: str, arg_lm_words: int, dst_nwid_reg: str = 'X0', branch_label: str = "") -> None:
        sht_macros.call_wlm_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_update_with_mask_64.getLabel(), cont_reg=cont_reg, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=arg_lm_words, branch_label=branch_label)

    @classmethod
    def _get_with_random(cls, state: EFAProgram.State):
        """
        X8 - LANE_DESC_LM_OFFSET(0:31) | BUCKET_DESC_LM_OFFSET(32:63)
        X9 - RAND_NUM (64 bit)

        Returns:
            X8  - KEY (-1 if empty bucket)
            X9  - RAND_NUM
            X10 - VAL0 (optional)
            X11 - VAL1 (optional)
            X12 - VAL2 (optional)
            X13 - VAL3 (optional)
            X14 - VAL4 (optional)
            X15 - VAL5 (optional)
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._get_with_random.__name__

        MAX_RETURN_VAL_NUM_WORDS = 6

        OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET = "X8"
        OB_RAND_NUM = "X9"

        REG_LANE_DESC_LM_ADDR = "X16"
        REG_BUCKET_DESC_LM_ADDR = "X17"
        REG_BUCKET_BUF_LM_ADDR = "X18"

        REG_LD_CONCURRENCY = "X19"
        REG_NUM_VAL_WORDS = "X20"  # number of value operations

        REG_TMP0 = "X21"
        REG_TMP1 = "X22"
        REG_TMP2 = "X23"

        REG_KEY = "X24"
        REG_RAND_NUM = "X25"
        REG_VAL = [REG_NUM_VAL_WORDS, REG_TMP1, REG_TMP2, "X26", "X27", "X28"]

        REG_CONT = "X31"

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_get_with_random
        if tran is None:
            return
        cls.tran_label_get_with_random = tran.getLabel()
        tran_key_ld_ret = []
        tran_val_ld_ret = []
        for i in range(MAX_RETURN_VAL_NUM_WORDS):
            tran_key_ld_ret.append(state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-key_ld_ret_{i}"))
            tran_val_ld_ret.append(state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-val_ld_ret_{i}"))

        """==================== TRAN - function entry ===================="""
        """----- Prep -----"""
        # calc desc lm addr
        tran.writeAction(f"sri {OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET} {REG_BUCKET_DESC_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_BUCKET_DESC_LM_ADDR} {'X7'} {REG_BUCKET_DESC_LM_ADDR}")
        # get lock
        cls.lock.read_begin(tran, REG_BUCKET_DESC_LM_ADDR, REG_TMP0, 2)
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: lock admitted, TID = %lu' {'X0'} {'TID'}")

        # calc desc lm addr
        tran.writeAction(f"sli {OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET} {REG_LANE_DESC_LM_ADDR} {32}")
        tran.writeAction(f"sri {REG_LANE_DESC_LM_ADDR} {REG_LANE_DESC_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_LANE_DESC_LM_ADDR} {'X7'} {REG_LANE_DESC_LM_ADDR}")

        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: REG_LANE_DESC_LM_ADDR = 0x%lx, REG_BUCKET_DESC_LM_ADDR = 0x%lx' {'X0'} {REG_LANE_DESC_LM_ADDR} {REG_BUCKET_DESC_LM_ADDR}")

        # load desc
        tran.writeAction(f"addi {REG_BUCKET_DESC_LM_ADDR} {REG_BUCKET_BUF_LM_ADDR} {cls.BUCKET_DESC_STURCT_OFF_LM_BUF}")
        tran.writeAction(f"movlr {cls.LANE_DESC_STURCT_OFF_VAL_NUM_WORDS}({REG_LANE_DESC_LM_ADDR}) {REG_NUM_VAL_WORDS} 0 4")

        tran.writeAction(f"movlr {cls.BUCKET_DESC_STURCT_OFF_ENTRY_COUNT}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP0} 0 4")  # tmp0 => entry_count

        """----- Empty Bucket -----"""
        # ----- if entry count is zero, return not found -----
        tran.writeAction(f"bgti {REG_TMP0} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-non_empty_bucket'}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: empty bucket, return without search' {'X0'}")
        # return format: (-1, rand_num)
        tran.writeAction(f"movir {REG_TMP0} {-1}")  # indicate failue
        sht_macros.return_wreg(tran=tran, cont_reg='X1', tmp_reg=REG_TMP1, arg_reg0=REG_TMP0, arg_reg1=OB_RAND_NUM)
        cls.lock.read_end(tran, REG_BUCKET_DESC_LM_ADDR, REG_TMP0)
        tran.writeAction("yieldt")  # only if running out of space!

        """----- Filled Bucket -----"""
        # copy ob regs
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-non_empty_bucket'}: addi {OB_RAND_NUM} {REG_RAND_NUM} {0}")
        # save cont
        tran.writeAction(f"addi {'X1'} {REG_CONT} {0}")

        # use the upper 32 bits of the random number to select the entry
        tran.writeAction(f"sri {OB_RAND_NUM} {REG_TMP1} {32}")
        tran.writeAction(f"mod {REG_TMP1} {REG_TMP0} {REG_TMP1}")  # REG_TMP1 => entry index
        tran.writeAction(f"sli {REG_TMP1} {REG_TMP2} {int(math.log2(cls.KEY_SIZE))}")  # REG_TMP2 => key offset
        tran.writeAction(f"movlr {cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP0} 0 8")
        tran.writeAction(f"add {REG_TMP0} {REG_TMP2} {REG_TMP0}")  # REG_TMP0 => key dram addr
        for i in range(MAX_RETURN_VAL_NUM_WORDS):
            tran.writeAction(f"beqi {REG_NUM_VAL_WORDS} {i + 1} {f'{CLS_NAME}-{FN_NAME}-TR-LB-key_match_{i}'}")
        tran.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-LB-key_match_{MAX_RETURN_VAL_NUM_WORDS - 1}'}")
        for i in range(MAX_RETURN_VAL_NUM_WORDS):
            sht_macros.dram_read_ret(tran=tran, addr_reg=REG_TMP0, ret_tran_label=tran_key_ld_ret[i].getLabel(), tmp_reg=REG_TMP2, arg_lm_words=cls.KEY_SIZE // 8, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-LB-key_match_{i}')
            tran.writeAction(f"movlr {cls.BUCKET_DESC_STURCT_OFF_DRAM_VAL_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP0} 0 8")
            tran.writeAction(f"mul {REG_TMP1} {REG_NUM_VAL_WORDS} {REG_TMP2}")
            tran.writeAction(f"sli {REG_TMP2} {REG_TMP2} {int(math.log2(cls.WORD_SIZE))}")
            tran.writeAction(f"add {REG_TMP0} {REG_TMP2} {REG_TMP0}")  # REG_TMP0 => val dram addr
            sht_macros.dram_read_ret(tran=tran, addr_reg=REG_TMP0, ret_tran_label=tran_val_ld_ret[i].getLabel(), tmp_reg=REG_TMP2, arg_lm_words=(i + 1))
            tran.writeAction(f"movir {REG_LD_CONCURRENCY} {2}")
            tran.writeAction("yield")

        """==================== TRAN - load key return ===================="""
        for i in range(MAX_RETURN_VAL_NUM_WORDS):
            if cls.DEBUG:
                tran_key_ld_ret[i].writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: key received = ' {'X0'} {'X8'}")
            tran_key_ld_ret[i].writeAction(f"subi {REG_LD_CONCURRENCY} {REG_LD_CONCURRENCY} {1}")
            tran_key_ld_ret[i].writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret_{i}-LB-wait'}")

            if cls.DEBUG:
                tran_key_ld_ret[i].writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: key received, returning...' {'X0'}")
            tran_key_ld_ret[i].writeAction(f"movrl {'X8'} {0 * cls.WORD_SIZE}({REG_BUCKET_BUF_LM_ADDR}) 0 8")
            tran_key_ld_ret[i].writeAction(f"movrl {REG_RAND_NUM} {1 * cls.WORD_SIZE}({REG_BUCKET_BUF_LM_ADDR}) 0 8")
            for j in range(0, i + 1):
                tran_key_ld_ret[i].writeAction(f"movrl {REG_VAL[j]} {(2 + j) * cls.WORD_SIZE}({REG_BUCKET_BUF_LM_ADDR}) 0 8")
            # return format: (key, rand_num, val0~5)
            sht_macros.return_wlm(tran=tran_key_ld_ret[i], cont_reg=REG_CONT, tmp_reg=REG_TMP0, arg_lm_addr_reg=REG_BUCKET_BUF_LM_ADDR, arg_lm_words=(i + 2 + 1))
            cls.lock.read_end(tran_key_ld_ret[i], REG_BUCKET_DESC_LM_ADDR, REG_TMP0)
            tran_key_ld_ret[i].writeAction("yieldt")

            tran_key_ld_ret[i].writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret_{i}-LB-wait'}: addi {'X8'} {REG_KEY} {0}")
            tran_key_ld_ret[i].writeAction("yield")

        """==================== TRAN - load val return ===================="""
        for i in range(MAX_RETURN_VAL_NUM_WORDS):
            if cls.DEBUG:
                tran_val_ld_ret[i].writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: val received, {', '.join(f'X{j} = %lu' for j in range(8, i + j + 1))}' {'X0'} {' '.join(f'X{j}' for j in range(8, i + j + 1))}")
            tran_val_ld_ret[i].writeAction(f"subi {REG_LD_CONCURRENCY} {REG_LD_CONCURRENCY} {1}")
            tran_val_ld_ret[i].writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret_{i}-LB-wait'}")

            if cls.DEBUG:
                tran_val_ld_ret[i].writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: val received, returning...' {'X0'}")
            tran_val_ld_ret[i].writeAction(f"movrl {REG_KEY} {0 * cls.WORD_SIZE}({REG_BUCKET_BUF_LM_ADDR}) 0 8")
            tran_val_ld_ret[i].writeAction(f"movrl {REG_RAND_NUM} {1 * cls.WORD_SIZE}({REG_BUCKET_BUF_LM_ADDR}) 0 8")
            tran_val_ld_ret[i].writeAction(f"addi {REG_BUCKET_BUF_LM_ADDR} {REG_TMP0} {2 * cls.WORD_SIZE}")
            tran_val_ld_ret[i].writeAction(f"bcpyoli {'X8'} {REG_TMP0} {i + 1}")
            # return format: (key, rand_num, val0~5)
            sht_macros.return_wlm(tran=tran_val_ld_ret[i], cont_reg=REG_CONT, tmp_reg=REG_TMP0, arg_lm_addr_reg=REG_BUCKET_BUF_LM_ADDR, arg_lm_words=(i + 2 + 1))
            cls.lock.read_end(tran_val_ld_ret[i], REG_BUCKET_DESC_LM_ADDR, REG_TMP0)
            tran_val_ld_ret[i].writeAction("yieldt")

            tran_val_ld_ret[i].writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret_{i}-LB-wait'}: addi {'X8'} {REG_VAL[0]} {0}")
            for j in range(1, i + 1):
                tran_val_ld_ret[i].writeAction(f"addi {f'X{8 + j}'} {REG_VAL[j]} {0}")
            tran_val_ld_ret[i].writeAction("yield")

    @classmethod
    def get_with_random(cls, tran: EFAProgram.Transition, ret: int, tmp_reg0: str, tmp_reg1: str, desc_lm_offset_reg: str, rand_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_get_with_random.getLabel(), ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=desc_lm_offset_reg, arg_reg1=rand_reg, branch_label=branch_label)

    @classmethod
    def get_with_random_wcont(cls, tran: EFAProgram.Transition, ret: str, tmp_reg: str, desc_lm_offset_reg: str, rand_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_get_with_random.getLabel(), cont_reg=ret, tmp_reg=tmp_reg, arg_reg0=desc_lm_offset_reg, arg_reg1=rand_reg, branch_label=branch_label)

    @classmethod
    def _get_next(cls, state: EFAProgram.State):
        """
        X8 - LANE_DESC_LM_OFFSET[0:31] | BUCKET_DESC_LM_OFFSET[32:63]
        X9 - NWID[0:31] | CUR_POSITION[32:63]
        Returns:
            X8 - LANE_DESC_LM_OFFSET[0:31] | BUCKET_DESC_LM_OFFSET[32:63]
            X9 - NWID[0:31] | CUR_POSITION[32:63] - CUR_POSITION[0:31] set to -1 if reached end, set to -2 if passed end
            X10 - KEY - omit if passed end
            X11 - ADDR - omit if passed end
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._get_next.__name__

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_get_next
        if tran is None:
            return
        cls.tran_label_get_next = tran.getLabel()
        tran_key_ld_ret = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-key_ld_ret")

        """******************** THREAD - get_next ********************"""
        REG_BUCKET_DESC_LM_ADDR = "X16"
        REG_LANE_DESC_LM_ADDR = "X17"
        REG_CUR_POSITION = "X18"
        REG_BUCKET_BUF_LM_ADDR = "X19"
        REG_TMP0 = "X20"
        REG_TMP1 = "X21"
        REG_TMP2 = "X22"
        REG_TMP3 = "X23"

        REG_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET = "X30"
        REG_CONT = "X31"

        """==================== TRAN - ENTRY ===================="""
        OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET = "X8"
        OB_NWID__CUR_POSITION = "X9"

        # calc desc lm addr
        tran.writeAction(f"sri {OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET} {REG_BUCKET_DESC_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_BUCKET_DESC_LM_ADDR} {'X7'} {REG_BUCKET_DESC_LM_ADDR}")
        tran.writeAction(f"sli {OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET} {REG_LANE_DESC_LM_ADDR} {32}")
        tran.writeAction(f"sri {REG_LANE_DESC_LM_ADDR} {REG_LANE_DESC_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_LANE_DESC_LM_ADDR} {'X7'} {REG_LANE_DESC_LM_ADDR}")

        # get cur position
        tran.writeAction(f"sri {OB_NWID__CUR_POSITION} {REG_CUR_POSITION} {32}")

        tran.writeAction(f"addi {REG_BUCKET_DESC_LM_ADDR} {REG_BUCKET_BUF_LM_ADDR} {cls.BUCKET_DESC_STURCT_OFF_LM_BUF}")
        tran.writeAction(f"movlr {cls.BUCKET_DESC_STURCT_OFF_ENTRY_COUNT}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP0} 0 4")  # REG_TMP0 => entry count
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: REG_LANE_DESC_LM_ADDR = 0x%lx, REG_BUCKET_DESC_LM_ADDR = 0x%lx' {'X0'} {REG_LANE_DESC_LM_ADDR} {REG_BUCKET_DESC_LM_ADDR}")
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: X8 = %lu, X9 = %lu, cur_position = %lu, entry_count = %lu' {'X0'} {OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET} {OB_NWID__CUR_POSITION} {REG_CUR_POSITION} {REG_TMP0}")
        tran.writeAction(f"bleu {REG_TMP0} {REG_CUR_POSITION} {f'{CLS_NAME}-{FN_NAME}-TR-LB-passed_end'}")  # use unsigned comparison, the negative value is larger than the positive value

        # -> not passed end
        tran.writeAction(f"movlr {cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP1} 0 8")  # REG_TMP1 => key_dram_start_addr
        tran.writeAction(f"sli {REG_CUR_POSITION} {REG_TMP2} {int(math.log2(cls.KEY_SIZE))}")  # REG_TMP2 => key_offset
        tran.writeAction(f"add {REG_TMP1} {REG_TMP2} {REG_TMP2}")  # REG_TMP2 => key_dram_addr
        sht_macros.dram_read_ret(tran=tran, addr_reg=REG_TMP2, ret_tran_label=tran_key_ld_ret.getLabel(), tmp_reg=REG_TMP3, arg_lm_words=cls.KEY_SIZE // 8)
        tran.writeAction(f"addi {'X1'} {REG_CONT} {0}")  # save cont
        tran.writeAction(f"addi {OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET} {REG_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET} {0}")  # save X8, LM_BUF is lane shared, cannot use across activations
        tran.writeAction("yield")

        # -> passed end
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-passed_end'}: movir {REG_TMP3} {-2}")
        tran.writeAction(f"sli {REG_TMP3} {REG_TMP3} {32}")
        tran.writeAction(f"or {REG_TMP3} {'X0'} {REG_TMP3}")
        sht_macros.return_wreg(tran=tran, cont_reg='X1', tmp_reg=REG_TMP0, arg_reg0=OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET, arg_reg1=REG_TMP3)
        tran.writeAction("yieldt")

        """==================== TRAN - key load return ===================="""
        OB_KEY = "X8"

        tran_key_ld_ret.writeAction(f"movrl {REG_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET} {cls.WORD_SIZE * 0}({REG_BUCKET_BUF_LM_ADDR}) 0 8")
        tran_key_ld_ret.writeAction(f"movrl {OB_KEY} {cls.WORD_SIZE * 2}({REG_BUCKET_BUF_LM_ADDR}) 0 8")
        tran_key_ld_ret.writeAction(f"movlr {cls.BUCKET_DESC_STURCT_OFF_DRAM_VAL_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP1} 0 8")  # REG_TMP1 => val_dram_start_addr
        tran_key_ld_ret.writeAction(f"movlr {cls.LANE_DESC_STURCT_OFF_VAL_NUM_WORDS}({REG_LANE_DESC_LM_ADDR}) {REG_TMP2} 0 4")  # REG_TMP2 => value num words
        tran_key_ld_ret.writeAction(f"mul {REG_CUR_POSITION} {REG_TMP2} {REG_TMP3}")
        tran_key_ld_ret.writeAction(f"sli {REG_TMP3} {REG_TMP3} {int(math.log2(cls.WORD_SIZE))}")
        tran_key_ld_ret.writeAction(f"add {REG_TMP1} {REG_TMP3} {REG_TMP3}")  # REG_TMP3 => val_dram_addr
        tran_key_ld_ret.writeAction(f"movrl {REG_TMP3} {cls.WORD_SIZE * 3}({REG_BUCKET_BUF_LM_ADDR}) 0 8")
        tran_key_ld_ret.writeAction(f"addi {REG_CUR_POSITION} {REG_CUR_POSITION} {1}")
        tran_key_ld_ret.writeAction(f"bge {REG_CUR_POSITION} {REG_TMP0} {f'{CLS_NAME}-{FN_NAME}-TR-entry_ld_ret-LB-reached_end'}")

        # -> not reached end
        tran_key_ld_ret.writeAction(f"sli {REG_CUR_POSITION} {REG_TMP3} {32}")
        tran_key_ld_ret.writeAction(f"or {REG_TMP3} {'X0'} {REG_TMP3}")
        tran_key_ld_ret.writeAction(f"movrl {REG_TMP3} {cls.WORD_SIZE * 1}({REG_BUCKET_BUF_LM_ADDR}) 0 8")
        sht_macros.return_wlm(tran=tran_key_ld_ret, cont_reg=REG_CONT, tmp_reg=REG_TMP0, arg_lm_addr_reg=REG_BUCKET_BUF_LM_ADDR, arg_lm_words=4)
        tran_key_ld_ret.writeAction("yieldt")

        # -> reached end
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-entry_ld_ret-LB-reached_end'}: movir {REG_TMP3} {-1}")
        tran_key_ld_ret.writeAction(f"sli {REG_TMP3} {REG_TMP3} {32}")
        tran_key_ld_ret.writeAction(f"or {REG_TMP3} {'X0'} {REG_TMP3}")
        tran_key_ld_ret.writeAction(f"movrl {REG_TMP3} {cls.WORD_SIZE * 1}({REG_BUCKET_BUF_LM_ADDR}) 0 8")
        sht_macros.return_wlm(tran=tran_key_ld_ret, cont_reg=REG_CONT, tmp_reg=REG_TMP0, arg_lm_addr_reg=REG_BUCKET_BUF_LM_ADDR, arg_lm_words=4)
        tran_key_ld_ret.writeAction("yieldt")

    @classmethod
    def get_next(cls, tran: EFAProgram.Transition, ret: int, tmp_reg0: str, tmp_reg1: str, iter_word0_reg: str, iter_word1_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_label_get_next, ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=iter_word0_reg, arg_reg1=iter_word1_reg, branch_label=branch_label)

    @classmethod
    def get_next_wcont(cls, tran: EFAProgram.Transition, ret: str, tmp_reg: str, iter_word0_reg: str, iter_word1_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_label_get_next, cont_reg=ret, tmp_reg=tmp_reg, arg_reg0=iter_word0_reg, arg_reg1=iter_word1_reg, branch_label=branch_label)

    @classmethod
    def _get_next_split(cls, state: EFAProgram.State):
        """
        X8  - LANE_DESC_LM_OFFSET[0:31] | BUCKET_DESC_LM_OFFSET[32:63]
        X9  - NWID[0:31] | CUR_POSITION[32:63]
        X10 - (KEY, ADDR) CONTINUATION
        Returns (with default continuation):
            X8  - LANE_DESC_LM_OFFSET[0:31] | BUCKET_DESC_LM_OFFSET[32:63]
            X9  - NWID[0:31] | CUR_POSITION[32:63] - CUR_POSITION[0:31] set to -1 if reached end, set to -2 if passed end
        Returns (with (KEY, ADDR) continuation): - omit if passed end
            X8 - KEY
            X9 - ADDR
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._get_next_split.__name__

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_get_next_split
        if tran is None:
            return
        cls.tran_label_get_next_split = tran.getLabel()
        tran_key_ld_ret = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-key_ld_ret")

        """******************** THREAD - get_next ********************"""
        REG_BUCKET_DESC_LM_ADDR = "X16"
        REG_LANE_DESC_LM_ADDR = "X17"
        REG_CUR_POSITION = "X18"
        REG_BUCKET_BUF_LM_ADDR = "X19"
        REG_TMP0 = "X20"
        REG_TMP1 = "X21"
        REG_TMP2 = "X22"
        REG_TMP3 = "X23"

        REG_KEY_ADDR_CONT = "X31"

        """==================== TRAN - ENTRY ===================="""
        OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET = "X8"
        OB_NWID__CUR_POSITION = "X9"
        OB_KEY_ADDR_CONT = "X10"

        # calc desc lm addr
        tran.writeAction(f"sri {OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET} {REG_BUCKET_DESC_LM_ADDR} {32}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: BUCKET_DESC_LM_OFFSET = 0x%lx' {'X0'} {REG_BUCKET_DESC_LM_ADDR}")
        tran.writeAction(f"add {REG_BUCKET_DESC_LM_ADDR} {'X7'} {REG_BUCKET_DESC_LM_ADDR}")
        tran.writeAction(f"sli {OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET} {REG_LANE_DESC_LM_ADDR} {32}")
        tran.writeAction(f"sri {REG_LANE_DESC_LM_ADDR} {REG_LANE_DESC_LM_ADDR} {32}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: LANE_DESC_LM_OFFSET = 0x%lx' {'X0'} {REG_LANE_DESC_LM_ADDR}")
        tran.writeAction(f"add {REG_LANE_DESC_LM_ADDR} {'X7'} {REG_LANE_DESC_LM_ADDR}")

        # get cur position
        tran.writeAction(f"sri {OB_NWID__CUR_POSITION} {REG_CUR_POSITION} {32}")

        tran.writeAction(f"addi {REG_BUCKET_DESC_LM_ADDR} {REG_BUCKET_BUF_LM_ADDR} {cls.BUCKET_DESC_STURCT_OFF_LM_BUF}")
        tran.writeAction(f"movlr {cls.BUCKET_DESC_STURCT_OFF_ENTRY_COUNT}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP0} 0 4")  # REG_TMP0 => entry count
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: REG_LANE_DESC_LM_ADDR = 0x%lx, REG_BUCKET_DESC_LM_ADDR = 0x%lx' {'X0'} {REG_LANE_DESC_LM_ADDR} {REG_BUCKET_DESC_LM_ADDR}")
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: X8 = %lu, X9 = %lu, cur_position = %lu, entry_count = %lu' {'X0'} {OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET} {OB_NWID__CUR_POSITION} {REG_CUR_POSITION} {REG_TMP0}")
        tran.writeAction(f"bleu {REG_TMP0} {REG_CUR_POSITION} {f'{CLS_NAME}-{FN_NAME}-TR-LB-passed_end'}")  # use unsigned comparison, the negative value is larger than the positive value

        # -> not passed end
        # reply the new iterator
        tran.writeAction(f"addi {REG_CUR_POSITION} {REG_TMP1} {1}")
        tran.writeAction(f"bne {REG_TMP1} {REG_TMP0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-not_reached_end'}")  # check if reached end
        tran.writeAction(f"movir {REG_TMP1} {-1}")
        tran.writeAction(f"sli {REG_TMP1} {REG_TMP1} {32}")
        tran.writeAction(f"or {REG_TMP1} {'X0'} {REG_TMP1}")
        tran.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-LB-reply_next_iter'}")
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-not_reached_end'}: sli {REG_TMP1} {REG_TMP1} {32}")
        tran.writeAction(f"or {REG_TMP1} {'X0'} {REG_TMP1}")
        sht_macros.return_wreg(tran=tran, cont_reg='X1', tmp_reg=REG_TMP0, arg_reg0=OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET, arg_reg1=REG_TMP1, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-LB-reply_next_iter')
        # load key
        tran.writeAction(f"movlr {cls.BUCKET_DESC_STURCT_OFF_DRAM_KEY_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP1} 0 8")  # REG_TMP1 => key_dram_start_addr
        tran.writeAction(f"sli {REG_CUR_POSITION} {REG_TMP2} {int(math.log2(cls.KEY_SIZE))}")  # REG_TMP2 => key_offset
        tran.writeAction(f"add {REG_TMP1} {REG_TMP2} {REG_TMP2}")  # REG_TMP2 => key_dram_addr
        sht_macros.dram_read_ret(tran=tran, addr_reg=REG_TMP2, ret_tran_label=tran_key_ld_ret.getLabel(), tmp_reg=REG_TMP3, arg_lm_words=cls.KEY_SIZE // 8)
        tran.writeAction(f"addi {OB_KEY_ADDR_CONT} {REG_KEY_ADDR_CONT} {0}")  # save cont
        tran.writeAction("yield")

        # -> passed end
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-passed_end'}: movir {REG_TMP1} {-2}")
        tran.writeAction(f"sli {REG_TMP1} {REG_TMP1} {32}")
        tran.writeAction(f"or {REG_TMP1} {'X0'} {REG_TMP1}")
        sht_macros.return_wreg(tran=tran, cont_reg='X1', tmp_reg=REG_TMP0, arg_reg0=OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET, arg_reg1=REG_TMP1)
        tran.writeAction("yieldt")

        """==================== TRAN - key load return ===================="""
        OB_KEY = "X8"
        OB_ADDR = "X9"

        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: KEY = %lu, DRAM_ADDR = 0x%lx' {'X0'} {OB_KEY} {OB_ADDR}")
        tran_key_ld_ret.writeAction(f"movlr {cls.BUCKET_DESC_STURCT_OFF_DRAM_VAL_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP1} 0 8")  # REG_TMP1 => val_dram_start_addr
        tran_key_ld_ret.writeAction(f"movlr {cls.LANE_DESC_STURCT_OFF_VAL_NUM_WORDS}({REG_LANE_DESC_LM_ADDR}) {REG_TMP2} 0 4")  # REG_TMP2 => value num words
        tran_key_ld_ret.writeAction(f"mul {REG_CUR_POSITION} {REG_TMP2} {REG_TMP3}")
        tran_key_ld_ret.writeAction(f"sli {REG_TMP3} {REG_TMP3} {int(math.log2(cls.WORD_SIZE))}")
        tran_key_ld_ret.writeAction(f"add {REG_TMP1} {REG_TMP3} {REG_TMP3}")  # REG_TMP3 => val_dram_addr
        sht_macros.return_wreg(tran=tran_key_ld_ret, cont_reg=REG_KEY_ADDR_CONT, tmp_reg=REG_TMP0, arg_reg0=OB_KEY, arg_reg1=REG_TMP3)
        tran_key_ld_ret.writeAction("yieldt")

    @classmethod
    def get_next_split(cls, tran: EFAProgram.Transition, ret: int, tmp_reg0: str, tmp_reg1: str, iter_word0_reg: str, iter_word1_reg: str, key_addr_cont_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_label_get_next_split, ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=iter_word0_reg, arg_reg1=iter_word1_reg, arg_reg2=key_addr_cont_reg, branch_label=branch_label)

    @classmethod
    def get_next_split_wcont(cls, tran: EFAProgram.Transition, ret: str, tmp_reg: str, iter_word0_reg: str, iter_word1_reg: str, key_addr_cont_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_label_get_next_split, cont_reg=ret, tmp_reg=tmp_reg, arg_reg0=iter_word0_reg, arg_reg1=iter_word1_reg, arg_reg2=key_addr_cont_reg, branch_label=branch_label)

    @classmethod
    def _get_iterators(cls, state: EFAProgram.State) -> None:
        """
         X8 - LANE_DESC_LM_OFFSET
         X9 - ITER_DRAM_ADDR
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._get_iterators.__name__

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_get_iterators
        if tran is None:
            return
        cls.tran_label_get_iterators = tran.getLabel()
        tran_iter_st_ret = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-iter_st_ret")

        """******************** THREAD - get_iterators ********************"""
        REG_LANE_DESC_LM_ADDR = "X16"

        REG_CUR_ITER_DRAM_ADDR = "X17"
        REG_CUR_BUCKET_DESC_LM_OFFSET = "X18"
        REG_BUCKET_DESC_END_LM_OFFSET = "X19"
        REG_ITER_WRITE_STRIDE = "X20"
        REG_CONCURRENCY = "X21"

        REG_TMP1 = "X29"
        REG_TMP0 = "X30"
        REG_CONT = "X31"

        """==================== TRAN - ENTRY ===================="""
        OB_LANE_DESC_LM_OFFSET = 'X8'
        OB_ITER_DRAM_ADDR = 'X9'

        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}, LANE_DESC_LM_OFFSET = 0x%lx, ITER_DRAM_ADDR = 0x%lx' {'X0'} {OB_LANE_DESC_LM_OFFSET} {OB_ITER_DRAM_ADDR}")

        tran.writeAction(f"addi {'X1'} {REG_CONT} {0}")
        tran.writeAction(f"add {OB_LANE_DESC_LM_OFFSET} {'X7'} {REG_LANE_DESC_LM_ADDR}")
        # calculate the addr of the first iterator
        tran.writeAction(f"movlr {cls.LANE_DESC_STURCT_OFF_START_NWID}({REG_LANE_DESC_LM_ADDR}) {REG_CUR_ITER_DRAM_ADDR} 0 4")
        tran.writeAction(f"sub {'X0'} {REG_CUR_ITER_DRAM_ADDR} {REG_CUR_ITER_DRAM_ADDR}")  # WARNING: X0 has to be masked when the policy bits are set
        tran.writeAction(f"sli {REG_CUR_ITER_DRAM_ADDR} {REG_CUR_ITER_DRAM_ADDR} {int(math.log2(cls.WORD_SIZE * 2))}")
        tran.writeAction(f"add {OB_ITER_DRAM_ADDR} {REG_CUR_ITER_DRAM_ADDR} {REG_CUR_ITER_DRAM_ADDR}")  # REG_TMP0 => current iter dram write addr

        tran.writeAction(f"addi {OB_LANE_DESC_LM_OFFSET} {REG_CUR_BUCKET_DESC_LM_OFFSET} {cls.LANE_DESC_SIZE}")
        tran.writeAction(f"movlr {cls.LANE_DESC_STURCT_OFF_BUCKETS_PER_LANE}({REG_LANE_DESC_LM_ADDR}) {REG_CONCURRENCY} 0 4")
        tran.writeAction(f"muli {REG_CONCURRENCY} {REG_BUCKET_DESC_END_LM_OFFSET} {cls.BUCKET_DESC_SIZE}")
        tran.writeAction(f"add {REG_BUCKET_DESC_END_LM_OFFSET} {REG_CUR_BUCKET_DESC_LM_OFFSET} {REG_BUCKET_DESC_END_LM_OFFSET}")

        tran.writeAction(f"movlr {cls.LANE_DESC_STURCT_OFF_NUM_ALLOC_LANES}({REG_LANE_DESC_LM_ADDR}) {REG_ITER_WRITE_STRIDE} 0 4")
        tran.writeAction(f"sli {REG_ITER_WRITE_STRIDE} {REG_ITER_WRITE_STRIDE} {int(math.log2(cls.WORD_SIZE * 2))}")

        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-next_bucket'}: sli {REG_CUR_BUCKET_DESC_LM_OFFSET} {REG_TMP0} {32}")
        tran.writeAction(f"or {REG_TMP0} {OB_LANE_DESC_LM_OFFSET} {REG_TMP0}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}, writing iter to 0x%lx word0 = 0x%lx, word1 = %lu' {'X0'} {REG_CUR_ITER_DRAM_ADDR} {REG_TMP0} {'X0'}")
        sht_macros.dram_write_reg_ret(tran=tran, addr_reg=REG_CUR_ITER_DRAM_ADDR, ret_tran_label=tran_iter_st_ret.getLabel(), tmp_reg=REG_TMP1, arg_reg0=REG_TMP0, arg_reg1='X0')
        tran.writeAction(f"addi {REG_CUR_BUCKET_DESC_LM_OFFSET} {REG_CUR_BUCKET_DESC_LM_OFFSET} {cls.BUCKET_DESC_SIZE}")
        tran.writeAction(f"add {REG_CUR_ITER_DRAM_ADDR} {REG_ITER_WRITE_STRIDE} {REG_CUR_ITER_DRAM_ADDR}")
        tran.writeAction(f"blt {REG_CUR_BUCKET_DESC_LM_OFFSET} {REG_BUCKET_DESC_END_LM_OFFSET} {f'{CLS_NAME}-{FN_NAME}-TR-LB-next_bucket'}")

        tran.writeAction("yield")

        """==================== TRAN - store return ===================="""
        tran_iter_st_ret.writeAction(f"subi {REG_CONCURRENCY} {REG_CONCURRENCY} {1}")
        tran_iter_st_ret.writeAction(f"bnei {REG_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-iter_st_ret-LB-yield'}")
        sht_macros.return_wreg(tran=tran_iter_st_ret, cont_reg=REG_CONT, tmp_reg=REG_TMP0, arg_reg0='X0', arg_reg1='X0')
        tran_iter_st_ret.writeAction("yieldt")
        tran_iter_st_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-iter_st_ret-LB-yield'}: yield")

    @classmethod
    def get_iterators(cls, tran: EFAProgram.Transition, ret: int, tmp_reg0: str, tmp_reg1: str, lane_desc_lm_offset_reg: str, iters_start_dram_addr_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_label_get_iterators, ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=lane_desc_lm_offset_reg, arg_reg1=iters_start_dram_addr_reg, branch_label=branch_label)

    @classmethod
    def get_iterators_wcont(cls, tran: EFAProgram.Transition, ret: str, tmp_reg: str, lane_desc_lm_offset_reg: str, iters_start_dram_addr_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_label_get_iterators, cont_reg=ret, tmp_reg=tmp_reg, arg_reg0=lane_desc_lm_offset_reg, arg_reg1=iters_start_dram_addr_reg, branch_label=branch_label)


class SHTExtBroadcast:
    @classmethod
    def setup(cls, state: EFAProgram.State, fanout: int = 16, debug: bool = False) -> None:
        cls.DEBUG = debug
        cls.FANOUT = fanout

        CLS_NAME = cls.__name__
        cls.tran_get_iterators_broadcast = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-get_iterators_broadcast-TR")

        cls._get_iterators_broadcast(state)

    @classmethod
    def _get_iterators_broadcast(cls, state: EFAProgram.state):
        """
        X8  - long VAL0 (iterators start dram addr)
        X9  - long VAL1 (lane_desc_lm_offset)
        X10 - long VAL2__END_NWID
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._get_iterators_broadcast.__name__

        OB_VAL0 = "X8"
        OB_VAL1 = "X9"
        OB_VAL2__END_NWID = "X10"

        REG_TMP0 = "X16"
        REG_TMP1 = "X17"
        REG_TMP2 = "X18"
        REG_TMP3 = "X19"
        REG_TMP4 = "X20"
        REG_TMP5 = "X21"
        REG_TMP6 = "X22"
        REG_TMP7 = "X23"
        REG_SEND_CNT = "X24"
        REG_CONT = "X31"

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_get_iterators_broadcast
        if tran is None:
            return
        cls.tran_label_get_iterators_broadcast = tran.getLabel()
        tran_sync = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-sync")

        """==================== TRAN - entry ===================="""
        tran.writeAction(f"sri {OB_VAL2__END_NWID} {REG_TMP0} {32}")  # REG_TMP0 = end_nwid

        # extract current NWID
        # WARNING: X0 has to be masked when the policy bits are set
        tran.writeAction(f"addi {'X0'} {REG_TMP1} {0}")  # REG_TMP1 = cur_nwid

        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] start broadcast, val0 = 0x%lx, val1 = %lu, cur_nwid = %lu, nwid_end = %lu' {'X0'} {OB_VAL0} {OB_VAL1} {REG_TMP1} {REG_TMP0}")

        tran.writeAction(f"addi {'X1'} {REG_CONT} {0}")
        tran.writeAction(f"movir {REG_SEND_CNT} {1}")  # REG_SEND_CNT = 1 for the user call
        tran.writeAction(f"beq {REG_TMP1} {REG_TMP0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_done'}")

        tran.writeAction(f"sli {OB_VAL2__END_NWID} {REG_TMP5} {32}")
        tran.writeAction(f"sri {REG_TMP5} {REG_TMP5} {32}")  # REG_TMP5 = nwid_offset

        tran.writeAction(f"sub {REG_TMP0} {REG_TMP1} {REG_TMP2}")
        tran.writeAction(f"modi {REG_TMP2} {REG_TMP3} {cls.FANOUT}")
        tran.writeAction(f"divi {REG_TMP2} {REG_TMP2} {cls.FANOUT}")  # REG_TMP2 = stride
        tran.writeAction(f"beqi {REG_TMP3} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-no_ceil'}")
        tran.writeAction(f"addi {REG_TMP2} {REG_TMP2} {1}")

        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-no_ceil'}: addi {REG_TMP1} {REG_TMP1} {1}")
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_next'}: bgt {REG_TMP1} {REG_TMP0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_done'}")

        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] stride = %lu' {'X0'} {REG_TMP2}")

        # update dst NWID
        tran.writeAction(f"addi {REG_TMP1} {REG_TMP3} {0}")  # REG_TMP3 = dst_nwid

        tran.writeAction(f"add {REG_TMP1} {REG_TMP2} {REG_TMP4}")
        tran.writeAction(f"subi {REG_TMP4} {REG_TMP4} {1}")
        tran.writeAction(f"ble {REG_TMP4} {REG_TMP0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-end_in_range'}")
        tran.writeAction(f"addi {REG_TMP0} {REG_TMP4} {0}")  # REG_TMP4 = new end_nid

        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-end_in_range'}: sli {REG_TMP4} {REG_TMP4} {32}")
        tran.writeAction(f"addi {REG_TMP5} {REG_TMP5} {1}")
        tran.writeAction(f"or {REG_TMP5} {REG_TMP4} {REG_TMP4}")  # REG_TMP4 = new nwid_offset__end_nwid

        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] sending to NWID = %lu' {'X0'} {REG_TMP3}")
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=REG_TMP3, callee_tran_label=cls.tran_get_iterators_broadcast.getLabel(), ret_tran_label=tran_sync.getLabel(), tmp_reg0=REG_TMP6, tmp_reg1=REG_TMP7, arg_reg0=OB_VAL0, arg_reg1=OB_VAL1, arg_reg2=REG_TMP4)

        tran.writeAction(f"addi {REG_SEND_CNT} {REG_SEND_CNT} {1}")
        tran.writeAction(f"add {REG_TMP1} {REG_TMP2} {REG_TMP1}")
        tran.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_next'}")

        # call
        SHTLane.get_iterators(tran=tran, ret=tran_sync.getLabel(), tmp_reg0=REG_TMP2, tmp_reg1=REG_TMP3, lane_desc_lm_offset_reg=OB_VAL1, iters_start_dram_addr_reg=OB_VAL0, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-LB-send_done')

        tran.writeAction("yield")

        """==================== TRAN - sync ===================="""
        if cls.DEBUG:
            tran_sync.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] returned from NWID %lu' {'X0'} {'X8'}")
        tran_sync.writeAction(f"subi {REG_SEND_CNT} {REG_SEND_CNT} {1}")
        tran_sync.writeAction(f"bgti {REG_SEND_CNT} {0} {f'{CLS_NAME}-{FN_NAME}-TR-sync-wait'}")
        sht_macros.return_wreg(tran=tran_sync, cont_reg=REG_CONT, tmp_reg=REG_TMP0, arg_reg0='X0', arg_reg1='X0')
        tran_sync.writeAction("yieldt")
        tran_sync.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-sync-wait'}: yield")

    @classmethod
    def get_iterators_broadcast(cls, tran: EFAProgram.Transition, ret: int, tmp_reg0: str, tmp_reg1: str, iters_start_dram_addr_reg: str, lane_desc_lm_offset_reg: str, val2__end_nwid_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_label_get_iterators_broadcast, ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=iters_start_dram_addr_reg, arg_reg1=lane_desc_lm_offset_reg, arg_reg2=val2__end_nwid_reg, branch_label=branch_label)

    @classmethod
    def get_iterators_broadcast_wcont(cls, tran: EFAProgram.Transition, ret: str, tmp_reg: str, iters_start_dram_addr_reg: str, lane_desc_lm_offset_reg: str, val2__end_nwid_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_label_get_iterators_broadcast, cont_reg=ret, tmp_reg=tmp_reg, arg_reg0=iters_start_dram_addr_reg, arg_reg1=lane_desc_lm_offset_reg, arg_reg2=val2__end_nwid_reg, branch_label=branch_label)
