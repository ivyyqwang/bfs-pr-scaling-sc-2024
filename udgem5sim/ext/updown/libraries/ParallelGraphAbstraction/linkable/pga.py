from linker.EFAProgram import efaProgram, EFAProgram
import sht_macros
from sht_ext_call_macros import SHTExt
import math


@efaProgram
def ParallelGraphAbstractionModule(efa):
    efa.code_level = 'machine'

    state0 = efa.State()
    efa.add_initId(state0.state_id)

    ParallelGraphAbstraction.setup(state0, big_endian=False, debug=False)

    return efa


class ParallelGraphAbstraction:
    """
    struct PGA_DESC {
        VERTEX_STORE_SHT_DESC
        EDGE_STORE_SHT_DESC
        NUM_NEIGHBOR_LIST_STORE_SHT
        NEIGHBOR_LIST_STORE_SHT_DESC * N
    }
    """

    @classmethod
    def setup(cls, state: EFAProgram.State, big_endian=False, debug: bool = False):
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

        cls.PGA_DESC_OFF_VERTEX_STORE_SHT_DESC = 0  # 32 bytes
        cls.PGA_DESC_OFF_EDGE_STORE_SHT_DESC = cls.PGA_DESC_OFF_VERTEX_STORE_SHT_DESC + cls.SHT_DESC_SIZE  # 32 bytes
        cls.PGA_DESC_OFF_NUM_NEIGHBOR_LIST_STORE_SHT = cls.PGA_DESC_OFF_EDGE_STORE_SHT_DESC + cls.SHT_DESC_SIZE  # 8 bytes
        cls.PGA_DESC_OFF_NEIGHBOR_LIST_STORE_SHT_DESC_0 = cls.PGA_DESC_OFF_NUM_NEIGHBOR_LIST_STORE_SHT + 8  # 32 bytes

        cls.DEBUG = debug

        CLS_NAME = cls.__name__
        cls.tran_initialize_vertex_store = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-initialize_vertex_store-TR")
        cls.tran_initialize_edge_store = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-initialize_edge_store-TR")
        cls.tran_initialize_edge_list_store_append = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-initialize_edge_list_store_append-TR")
        cls.tran_update_vertex = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-update_vertex-TR")
        cls.tran_update_vertex_with_offset = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-update_vertex_with_offset-TR")
        cls.tran_update_edge = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-update_edge-TR")
        cls.tran_update_edge_with_offset = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-update_edge_with_offset-TR")
        cls.tran_get_vertex = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-get_vertex-TR")
        cls.tran_get_vertex_with_offset = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-get_vertex_with_offset-TR")
        cls.tran_get_vertex_with_random = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-get_vertex_with_random-TR")
        cls.tran_get_edge = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-get_edge-TR")
        cls.tran_get_edge_with_offset = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-get_edge_with_offset-TR")
        cls.tran_get_iters_vertex_store = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-get_iters_vertex_store-TR")
        cls.tran_get_iters_edge_store = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-get_iters_edge_store-TR")
        cls.tran_get_next_vertex_store_iter = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-get_next_vertex_store_iter-TR")
        cls.tran_get_next_edge_store_iter = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-get_next_edge_store_iter-TR")
        cls.tran_get_next_split_vertex_store_iter = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-get_next_split_vertex_store_iter-TR")
        cls.tran_get_next_split_edge_store_iter = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-get_next_split_edge_store_iter-TR")
        cls.tran_append_edge_list = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-append_edge_list-TR")
        cls.tran_get_edge_list_addr = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-get_edge_list_addr-TR")
        cls.tran_get_edge_list_next = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-get_edge_list_next-TR")

        # TODO: code injection
        cls._initialize_vertex_store(state)
        cls._initialize_edge_store(state)
        cls._initialize_edge_list_store_append(state)
        cls._update_vertex(state)
        cls._update_vertex_with_offset(state)
        cls._update_edge(state)
        cls._update_edge_with_offset(state)
        cls._get_vertex(state)
        cls._get_vertex_with_offset(state)
        cls._get_vertex_with_random(state)
        cls._get_edge(state)
        cls._get_edge_with_offset(state)
        cls._get_iters_vertex_store(state)
        cls._get_iters_edge_store(state)
        cls._get_next_vertex_store_iter(state)
        cls._get_next_edge_store_iter(state)
        cls._get_next_split_vertex_store_iter(state)
        cls._get_next_split_edge_store_iter(state)
        cls._append_edge_list(state)
        cls._get_edge_list_addr(state)
        cls._get_edge_list_next(state)

    @classmethod
    def _initialize_vertex_store(cls, state: EFAProgram.State):
        """
        X8  - PGA_DESC_LM_OFFSET [0:31] | TMP_BUF_LM_OFFSET [32:63]
        X9  - NUM_ALLOC_LANES(0:31) | START_NWID(32:63);
        X10 - LANE_DESC_LM_OFFSET(0:31) | BUCKETS_PER_LANE(32:63);
        X11 - ENTRIES_PER_BUCKET(0:31) | VAL_NUM_WORDS(32:63);
        X12 - DRAM_ALLOC_ADDR;

        Return:
        X8 - SHT_DESC_SIZE
        X9 - SHT_LANE_DESC_SIZE
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._initialize_vertex_store.__name__

        OB_PGA_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET = "X8"
        OB_NUM_ALLOC_LANES__START_NWID = "X9"
        OB_LANE_DESC_LM_OFFSET__BUCKETS_PER_LANE = "X10"
        OB_ENTRIES_PER_BUCKET__VAL_NUM_WORDS = "X11"
        OB_DRAM_ALLOC_ADDR = "X12"

        REG_PGA_DESC_LM_ADDR = "X16"
        REG_TMP_BUF_LM_ADDR = "X17"

        REG_TMP0 = "X21"

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_initialize_vertex_store
        if tran is None:
            return
        cls.tran_label_initialize_vertex_store = tran.getLabel()

        """==================== TRAN - entry ===================="""
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: entry' {'X0'}")

        # calculate lm addr
        tran.writeAction(f"lshift {OB_PGA_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET} {REG_PGA_DESC_LM_ADDR} {32}")
        tran.writeAction(f"rshift {REG_PGA_DESC_LM_ADDR} {REG_PGA_DESC_LM_ADDR} {32}")
        tran.writeAction(f"rshift {OB_PGA_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET} {REG_TMP_BUF_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_PGA_DESC_LM_ADDR} {'X7'} {REG_PGA_DESC_LM_ADDR}")
        tran.writeAction(f"add {REG_TMP_BUF_LM_ADDR} {'X7'} {REG_TMP_BUF_LM_ADDR}")

        # copy to buffer and send
        tran.writeAction(f"addi {OB_PGA_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET} {REG_TMP0} {cls.PGA_DESC_OFF_VERTEX_STORE_SHT_DESC}")
        tran.writeAction(f"move {REG_TMP0} {0}({REG_TMP_BUF_LM_ADDR}) 0 8")
        tran.writeAction(f"move {OB_NUM_ALLOC_LANES__START_NWID} {cls.WORD_SIZE * 1}({REG_TMP_BUF_LM_ADDR}) 0 8")
        tran.writeAction(f"move {OB_LANE_DESC_LM_OFFSET__BUCKETS_PER_LANE} {cls.WORD_SIZE * 2}({REG_TMP_BUF_LM_ADDR}) 0 8")
        tran.writeAction(f"move {OB_ENTRIES_PER_BUCKET__VAL_NUM_WORDS} {cls.WORD_SIZE * 3}({REG_TMP_BUF_LM_ADDR}) 0 8")
        tran.writeAction(f"move {OB_DRAM_ALLOC_ADDR} {cls.WORD_SIZE * 4}({REG_TMP_BUF_LM_ADDR}) 0 8")
        # fill in first word in the extension part as zero
        tran.writeAction(f"mov_imm2reg {REG_TMP0} {0}")
        tran.writeAction(f"move {REG_TMP0} {cls.WORD_SIZE * 5}({REG_TMP_BUF_LM_ADDR}) 0 8")

        # call
        SHTExt.initialize_wcont(tran=tran, ret='X1', tmp_reg0=REG_TMP0, arg_lm_addr_reg=REG_TMP_BUF_LM_ADDR)
        tran.writeAction("yield_terminate")

    @classmethod
    def _initialize_edge_store(cls, state: EFAProgram.State):
        """
        X8  - PGA_DESC_LM_OFFSET [0:31] | TMP_BUF_LM_OFFSET [32:63]
        X9  - NUM_ALLOC_LANES(0:31) | START_NWID(32:63);
        X10 - LANE_DESC_LM_OFFSET(0:31) | BUCKETS_PER_LANE(32:63);
        X11 - ENTRIES_PER_BUCKET(0:31) | VAL_NUM_WORDS(32:63);
        X12 - DRAM_ALLOC_ADDR;

        Return:
        X8 - SHT_DESC_SIZE
        X9 - SHT_LANE_DESC_SIZE
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._initialize_edge_store.__name__

        OB_PGA_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET = "X8"
        OB_NUM_ALLOC_LANES__START_NWID = "X9"
        OB_LANE_DESC_LM_OFFSET__BUCKETS_PER_LANE = "X10"
        OB_ENTRIES_PER_BUCKET__VAL_NUM_WORDS = "X11"
        OB_DRAM_ALLOC_ADDR = "X12"

        REG_PGA_DESC_LM_ADDR = "X16"
        REG_TMP_BUF_LM_ADDR = "X17"

        REG_TMP0 = "X21"

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_initialize_edge_store
        if tran is None:
            return
        cls.tran_label_initialize_edge_store = tran.getLabel()

        """==================== TRAN - entry ===================="""
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: entry' {'X0'}")

        # calculate lm addr
        tran.writeAction(f"lshift {OB_PGA_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET} {REG_PGA_DESC_LM_ADDR} {32}")
        tran.writeAction(f"rshift {REG_PGA_DESC_LM_ADDR} {REG_PGA_DESC_LM_ADDR} {32}")
        tran.writeAction(f"rshift {OB_PGA_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET} {REG_TMP_BUF_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_PGA_DESC_LM_ADDR} {'X7'} {REG_PGA_DESC_LM_ADDR}")
        tran.writeAction(f"add {REG_TMP_BUF_LM_ADDR} {'X7'} {REG_TMP_BUF_LM_ADDR}")

        # copy to buffer and send
        tran.writeAction(f"addi {OB_PGA_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET} {REG_TMP0} {cls.PGA_DESC_OFF_EDGE_STORE_SHT_DESC}")
        tran.writeAction(f"move {REG_TMP0} {0}({REG_TMP_BUF_LM_ADDR}) 0 8")
        tran.writeAction(f"move {OB_NUM_ALLOC_LANES__START_NWID} {cls.WORD_SIZE * 1}({REG_TMP_BUF_LM_ADDR}) 0 8")
        tran.writeAction(f"move {OB_LANE_DESC_LM_OFFSET__BUCKETS_PER_LANE} {cls.WORD_SIZE * 2}({REG_TMP_BUF_LM_ADDR}) 0 8")
        tran.writeAction(f"move {OB_ENTRIES_PER_BUCKET__VAL_NUM_WORDS} {cls.WORD_SIZE * 3}({REG_TMP_BUF_LM_ADDR}) 0 8")
        tran.writeAction(f"move {OB_DRAM_ALLOC_ADDR} {cls.WORD_SIZE * 4}({REG_TMP_BUF_LM_ADDR}) 0 8")
        tran.writeAction(f"mov_imm2reg {REG_TMP0} {0}")
        # reset num edge list store sht to 0
        tran.writeAction(f"move {REG_TMP0} {cls.PGA_DESC_OFF_NUM_NEIGHBOR_LIST_STORE_SHT}({REG_PGA_DESC_LM_ADDR}) 0 8")
        # fill in first word in the extension part as zero
        tran.writeAction(f"move {REG_TMP0} {cls.WORD_SIZE * 5}({REG_TMP_BUF_LM_ADDR}) 0 8")

        # call
        SHTExt.initialize_wcont(tran=tran, ret='X1', tmp_reg0=REG_TMP0, arg_lm_addr_reg=REG_TMP_BUF_LM_ADDR)

        tran.writeAction("yield_terminate")

    @classmethod
    def _initialize_edge_list_store_append(cls, state: EFAProgram.State):
        """
        largest SHT needs to be created first, appending smaller SHTs to it
        smallest should have entry allocated for every vertex

        X8  - PGA_DESC_LM_OFFSET [0:31] | TMP_BUF_LM_OFFSET [32:63]
        X9  - NUM_ALLOC_LANES(0:31) | START_NWID(32:63);
        X10 - LANE_DESC_LM_OFFSET(0:31) | BUCKETS_PER_LANE(32:63);
        X11 - ENTRIES_PER_BUCKET(0:31) | VAL_NUM_WORDS(32:63);
        X12 - DRAM_ALLOC_ADDR;

        Return:
        X8 - SHT_DESC_SIZE
        X9 - SHT_LANE_DESC_SIZE
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._initialize_edge_list_store_append.__name__

        OB_PGA_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET = "X8"
        OB_NUM_ALLOC_LANES__START_NWID = "X9"
        OB_LANE_DESC_LM_OFFSET__BUCKETS_PER_LANE = "X10"
        OB_ENTRIES_PER_BUCKET__VAL_NUM_WORDS = "X11"
        OB_DRAM_ALLOC_ADDR = "X12"

        REG_PGA_DESC_LM_ADDR = "X16"
        REG_TMP_BUF_LM_ADDR = "X17"

        REG_TMP0 = "X21"
        REG_TMP1 = "X22"
        REG_TMP2 = "X23"

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_initialize_edge_list_store_append
        if tran is None:
            return
        cls.tran_label_initialize_edge_list_store_append = tran.getLabel()

        """==================== TRAN - entry ===================="""
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: entry' {'X0'}")

        # calculate lm addr
        tran.writeAction(f"lshift {OB_PGA_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET} {REG_PGA_DESC_LM_ADDR} {32}")
        tran.writeAction(f"rshift {REG_PGA_DESC_LM_ADDR} {REG_PGA_DESC_LM_ADDR} {32}")
        tran.writeAction(f"rshift {OB_PGA_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET} {REG_TMP_BUF_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_PGA_DESC_LM_ADDR} {'X7'} {REG_PGA_DESC_LM_ADDR}")
        tran.writeAction(f"add {REG_TMP_BUF_LM_ADDR} {'X7'} {REG_TMP_BUF_LM_ADDR}")

        # copy to buffer and send
        # read number of neighbor list store sht
        tran.writeAction(f"move {cls.PGA_DESC_OFF_NUM_NEIGHBOR_LIST_STORE_SHT}({REG_PGA_DESC_LM_ADDR}) {REG_TMP0} 0 8")
        tran.writeAction(f"addi {REG_TMP0} {REG_TMP1} {1}")  # increment num sht
        tran.writeAction(f"move {REG_TMP1} {cls.PGA_DESC_OFF_NUM_NEIGHBOR_LIST_STORE_SHT}({REG_PGA_DESC_LM_ADDR}) 0 8")  # increment num sht
        tran.writeAction(f"muli {REG_TMP0} {REG_TMP1} {cls.SHT_DESC_SIZE}")
        tran.writeAction(f"addi {REG_TMP1} {REG_TMP1} {cls.PGA_DESC_OFF_NEIGHBOR_LIST_STORE_SHT_DESC_0}")

        tran.writeAction(f"beqi {REG_TMP0} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-no_bigger_sht'}")
        # copy bigger sht desc (less dram addr) to buffer
        tran.writeAction(f"subi {REG_TMP1} {REG_TMP2} {cls.SHT_DESC_SIZE}")
        tran.writeAction(f"add {REG_TMP2} {REG_PGA_DESC_LM_ADDR} {REG_TMP2}")
        # WARNING: depends on SHTExt descriptor definition
        tran.writeAction(f"move {cls.WORD_SIZE * 0}({REG_TMP2}) {REG_TMP0} 0 8")
        tran.writeAction(f"move {REG_TMP0} {cls.WORD_SIZE * 5}({REG_TMP_BUF_LM_ADDR}) 0 8")
        tran.writeAction(f"move {cls.WORD_SIZE * 1}({REG_TMP2}) {REG_TMP0} 0 8")
        tran.writeAction(f"move {REG_TMP0} {cls.WORD_SIZE * 6}({REG_TMP_BUF_LM_ADDR}) 0 8")
        tran.writeAction(f"move {cls.WORD_SIZE * 2}({REG_TMP2}) {REG_TMP0} 0 8")
        tran.writeAction(f"move {REG_TMP0} {cls.WORD_SIZE * 7}({REG_TMP_BUF_LM_ADDR}) 0 8")
        # copy new sht info to buffer
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-no_bigger_sht'}: add {OB_PGA_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET} {REG_TMP1} {REG_TMP2}")
        tran.writeAction(f"move {REG_TMP2} {0}({REG_TMP_BUF_LM_ADDR}) 0 8")
        tran.writeAction(f"move {OB_NUM_ALLOC_LANES__START_NWID} {cls.WORD_SIZE * 1}({REG_TMP_BUF_LM_ADDR}) 0 8")
        tran.writeAction(f"move {OB_LANE_DESC_LM_OFFSET__BUCKETS_PER_LANE} {cls.WORD_SIZE * 2}({REG_TMP_BUF_LM_ADDR}) 0 8")
        tran.writeAction(f"move {OB_ENTRIES_PER_BUCKET__VAL_NUM_WORDS} {cls.WORD_SIZE * 3}({REG_TMP_BUF_LM_ADDR}) 0 8")
        tran.writeAction(f"move {OB_DRAM_ALLOC_ADDR} {cls.WORD_SIZE * 4}({REG_TMP_BUF_LM_ADDR}) 0 8")

        # call
        SHTExt.initialize_wcont(tran=tran, ret='X1', tmp_reg0=REG_TMP2, arg_lm_addr_reg=REG_TMP_BUF_LM_ADDR)
        tran.writeAction("yield_terminate")

    @classmethod
    def _update_vertex(cls, state: EFAProgram.State):
        """
        X8  - PGA_DESC_LM_OFFSET [0:31] | TMP_BUF_LM_OFFSET [32:63]
        X9  - VID
        X10 - MASK
        X11~X15 - VAL words up to 5 words

        Return:
        X8  - VID
        X9  - MASK (== 0 if failed)
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._update_vertex.__name__

        OB_PGA_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET = "X8"
        OB_VID = "X9"
        OB_MASK = "X10"
        OB_VAL = "X11"

        REG_PGA_DESC_LM_ADDR = "X16"
        REG_TMP_BUF_LM_ADDR = "X17"

        REG_TMP0 = "X18"
        REG_TMP1 = "X19"

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_update_vertex
        if tran is None:
            return
        cls.tran_label_update_vertex = tran.getLabel()

        """==================== TRAN - entry ===================="""
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: entry' {'X0'}")

        # calculate lm addr
        tran.writeAction(f"sli {OB_PGA_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET} {REG_PGA_DESC_LM_ADDR} {32}")
        tran.writeAction(f"sri {REG_PGA_DESC_LM_ADDR} {REG_PGA_DESC_LM_ADDR} {32}")
        tran.writeAction(f"sri {OB_PGA_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET} {REG_TMP_BUF_LM_ADDR} {32}")
        tran.writeAction(f"addi {REG_PGA_DESC_LM_ADDR} {REG_TMP0} {cls.PGA_DESC_OFF_VERTEX_STORE_SHT_DESC}")  # calc the first operand for the call
        tran.writeAction(f"slori {REG_TMP_BUF_LM_ADDR} {REG_TMP0} {32}")  # calc the first operand for the call
        tran.writeAction(f"add {REG_PGA_DESC_LM_ADDR} {'X7'} {REG_PGA_DESC_LM_ADDR}")
        tran.writeAction(f"add {REG_TMP_BUF_LM_ADDR} {'X7'} {REG_TMP_BUF_LM_ADDR}")
        tran.writeAction(f"movrl {REG_TMP0} {0}({REG_TMP_BUF_LM_ADDR}) 0 8")  # fill in the first operand for the call

        # extract number of value operands + vid + mask
        tran.writeAction(f"sri {'X2'} {REG_TMP0} {20}")
        tran.writeAction(f"andi {REG_TMP0} {REG_TMP0} {0b111}")
        tran.writeAction(f"addi {REG_TMP0} {REG_TMP0} {1}")  # add for the vid operand
        # copy operands to buffer
        tran.writeAction(f"addi {REG_TMP_BUF_LM_ADDR} {REG_TMP1} {cls.WORD_SIZE}")
        tran.writeAction(f"bcpyol {OB_VID} {REG_TMP1} {REG_TMP0}")

        for i in range(4, 8 + 1):  # 1~5 value operands
            tran.writeAction(f"beqi {REG_TMP0} {i - 1} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send{i}'}")
        tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: shouldn't reach here!' {'X0'}")
        for i in range(4, 8 + 1):
            SHTExt.update_with_mask_wcont(tran=tran, ret='X1', tmp_reg0=REG_TMP0, arg_lm_addr_reg=REG_TMP_BUF_LM_ADDR, num_val_words=(i - 3), branch_label=f'{CLS_NAME}-{FN_NAME}-TR-LB-send{i}')  # call
            tran.writeAction("yieldt")

    @classmethod
    def _update_vertex_with_offset(cls, state: EFAProgram.State):
        """
        X8  - PGA_DESC_LM_OFFSET [0:31] | TMP_BUF_LM_OFFSET [32:63]
        X9  - VID
        X10 - OFFSET
        X11~X15 - VAL words up to 5 words

        Return:
        X8  - VID
        X9  - OFFSET (== -1 if failed)
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._update_vertex_with_offset.__name__

        OB_PGA_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET = "X8"
        OB_VID = "X9"
        OB_OFFSET = "X10"
        OB_VAL = "X11"

        REG_PGA_DESC_LM_ADDR = "X16"
        REG_TMP_BUF_LM_ADDR = "X17"

        REG_TMP0 = "X18"
        REG_TMP1 = "X19"

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_update_vertex_with_offset
        if tran is None:
            return
        cls.tran_label_update_vertex_with_offset = tran.getLabel()

        """==================== TRAN - entry ===================="""
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: entry' {'X0'}")

        # calculate lm addr
        tran.writeAction(f"sli {OB_PGA_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET} {REG_PGA_DESC_LM_ADDR} {32}")
        tran.writeAction(f"sri {REG_PGA_DESC_LM_ADDR} {REG_PGA_DESC_LM_ADDR} {32}")
        tran.writeAction(f"sri {OB_PGA_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET} {REG_TMP_BUF_LM_ADDR} {32}")
        tran.writeAction(f"addi {REG_PGA_DESC_LM_ADDR} {REG_TMP0} {cls.PGA_DESC_OFF_VERTEX_STORE_SHT_DESC}")  # calc the first operand for the call
        tran.writeAction(f"slori {REG_TMP_BUF_LM_ADDR} {REG_TMP0} {32}")  # calc the first operand for the call
        tran.writeAction(f"add {REG_PGA_DESC_LM_ADDR} {'X7'} {REG_PGA_DESC_LM_ADDR}")
        tran.writeAction(f"add {REG_TMP_BUF_LM_ADDR} {'X7'} {REG_TMP_BUF_LM_ADDR}")
        tran.writeAction(f"movrl {REG_TMP0} {0}({REG_TMP_BUF_LM_ADDR}) 0 8")  # fill in the first operand for the call

        # extract number of value operands + vid + offset
        tran.writeAction(f"sri {'X2'} {REG_TMP0} {20}")
        tran.writeAction(f"andi {REG_TMP0} {REG_TMP0} {0b111}")
        tran.writeAction(f"addi {REG_TMP0} {REG_TMP0} {1}")  # add for the vid operand
        # copy operands to buffer
        tran.writeAction(f"addi {REG_TMP_BUF_LM_ADDR} {REG_TMP1} {cls.WORD_SIZE}")
        tran.writeAction(f"bcpyol {OB_VID} {REG_TMP1} {REG_TMP0}")

        for i in range(4, 8 + 1):  # 1~5 value operands
            tran.writeAction(f"beqi {REG_TMP0} {i - 1} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send{i}'}")
        tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: shouldn't reach here!' {'X0'}")
        for i in range(4, 8 + 1):
            SHTExt.update_with_offset_wcont(tran=tran, ret='X1', tmp_reg0=REG_TMP0, arg_lm_addr_reg=REG_TMP_BUF_LM_ADDR, num_val_words=(i - 3), branch_label=f'{CLS_NAME}-{FN_NAME}-TR-LB-send{i}')  # call
            tran.writeAction("yieldt")

    @classmethod
    def _update_edge(cls, state: EFAProgram.State):
        """
        X8  - PGA_DESC_LM_OFFSET [0:31] | TMP_BUF_LM_OFFSET [32:63]
        X9  - EID (Edge ID)
        X10 - MASK
        X11~X15 - VAL words up to 5 words

        Return:
        X8  - EID
        X9  - MASK (== 0 if failed)
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._update_edge.__name__

        OB_PGA_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET = "X8"
        OB_EID = "X9"
        OB_MASK = "X10"
        OB_VAL = "X11"

        REG_PGA_DESC_LM_ADDR = "X16"
        REG_TMP_BUF_LM_ADDR = "X17"

        REG_TMP0 = "X18"
        REG_TMP1 = "X19"

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_update_edge
        if tran is None:
            return
        cls.tran_label_update_edge = tran.getLabel()

        """==================== TRAN - entry ===================="""
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: entry' {'X0'}")

        # calculate lm addr
        tran.writeAction(f"sli {OB_PGA_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET} {REG_PGA_DESC_LM_ADDR} {32}")
        tran.writeAction(f"sri {REG_PGA_DESC_LM_ADDR} {REG_PGA_DESC_LM_ADDR} {32}")
        tran.writeAction(f"sri {OB_PGA_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET} {REG_TMP_BUF_LM_ADDR} {32}")
        tran.writeAction(f"addi {REG_PGA_DESC_LM_ADDR} {REG_TMP0} {cls.PGA_DESC_OFF_EDGE_STORE_SHT_DESC}")  # calc the first operand for the call
        tran.writeAction(f"slori {REG_TMP_BUF_LM_ADDR} {REG_TMP0} {32}")  # calc the first operand for the call
        tran.writeAction(f"add {REG_PGA_DESC_LM_ADDR} {'X7'} {REG_PGA_DESC_LM_ADDR}")
        tran.writeAction(f"add {REG_TMP_BUF_LM_ADDR} {'X7'} {REG_TMP_BUF_LM_ADDR}")
        tran.writeAction(f"movrl {REG_TMP0} {0}({REG_TMP_BUF_LM_ADDR}) 0 8")  # fill in the first operand for the call

        # extract number of value operands + eid + mask
        tran.writeAction(f"sri {'X2'} {REG_TMP0} {20}")
        tran.writeAction(f"andi {REG_TMP0} {REG_TMP0} {0b111}")
        tran.writeAction(f"addi {REG_TMP0} {REG_TMP0} {1}")  # add for the eid operand
        # copy operands to buffer
        tran.writeAction(f"addi {REG_TMP_BUF_LM_ADDR} {REG_TMP1} {cls.WORD_SIZE}")
        tran.writeAction(f"bcpyol {OB_EID} {REG_TMP1} {REG_TMP0}")

        for i in range(4, 8 + 1):  # 1~5 value operands
            tran.writeAction(f"beqi {REG_TMP0} {i - 1} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send{i}'}")
        tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: shouldn't reach here!' {'X0'}")
        for i in range(4, 8 + 1):
            SHTExt.update_with_mask_wcont(tran=tran, ret='X1', tmp_reg0=REG_TMP0, arg_lm_addr_reg=REG_TMP_BUF_LM_ADDR, num_val_words=(i - 3), branch_label=f'{CLS_NAME}-{FN_NAME}-TR-LB-send{i}')  # call
            tran.writeAction("yieldt")

    @classmethod
    def _update_edge_with_offset(cls, state: EFAProgram.State):
        """
        X8  - PGA_DESC_LM_OFFSET [0:31] | TMP_BUF_LM_OFFSET [32:63]
        X9  - EID (Edge ID)
        X10 - OFFSET
        X11~X15 - VAL words up to 5 words

        Return:
        X8  - EID
        X9  - OFFSET (== -1 if failed)
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._update_edge_with_offset.__name__

        OB_PGA_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET = "X8"
        OB_EID = "X9"
        OB_OFFSET = "X10"
        OB_VAL = "X11"

        REG_PGA_DESC_LM_ADDR = "X16"
        REG_TMP_BUF_LM_ADDR = "X17"

        REG_TMP0 = "X18"
        REG_TMP1 = "X19"

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_update_edge_with_offset
        if tran is None:
            return
        cls.tran_label_update_edge_with_offset = tran.getLabel()

        """==================== TRAN - entry ===================="""
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: entry' {'X0'}")

        # calculate lm addr
        tran.writeAction(f"sli {OB_PGA_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET} {REG_PGA_DESC_LM_ADDR} {32}")
        tran.writeAction(f"sri {REG_PGA_DESC_LM_ADDR} {REG_PGA_DESC_LM_ADDR} {32}")
        tran.writeAction(f"sri {OB_PGA_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET} {REG_TMP_BUF_LM_ADDR} {32}")
        tran.writeAction(f"addi {REG_PGA_DESC_LM_ADDR} {REG_TMP0} {cls.PGA_DESC_OFF_EDGE_STORE_SHT_DESC}")  # calc the first operand for the call
        tran.writeAction(f"slori {REG_TMP_BUF_LM_ADDR} {REG_TMP0} {32}")  # calc the first operand for the call
        tran.writeAction(f"add {REG_PGA_DESC_LM_ADDR} {'X7'} {REG_PGA_DESC_LM_ADDR}")
        tran.writeAction(f"add {REG_TMP_BUF_LM_ADDR} {'X7'} {REG_TMP_BUF_LM_ADDR}")
        tran.writeAction(f"movrl {REG_TMP0} {0}({REG_TMP_BUF_LM_ADDR}) 0 8")  # fill in the first operand for the call

        # extract number of value operands + eid + offset
        tran.writeAction(f"sri {'X2'} {REG_TMP0} {20}")
        tran.writeAction(f"andi {REG_TMP0} {REG_TMP0} {0b111}")
        tran.writeAction(f"addi {REG_TMP0} {REG_TMP0} {1}")  # add for the eid operand
        # copy operands to buffer
        tran.writeAction(f"addi {REG_TMP_BUF_LM_ADDR} {REG_TMP1} {cls.WORD_SIZE}")
        tran.writeAction(f"bcpyol {OB_EID} {REG_TMP1} {REG_TMP0}")

        for i in range(4, 8 + 1):  # 1~5 value operands
            tran.writeAction(f"beqi {REG_TMP0} {i - 1} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send{i}'}")
        tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME.upper()}: shouldn't reach here!' {'X0'}")
        for i in range(4, 8 + 1):
            SHTExt.update_with_offset_wcont(tran=tran, ret='X1', tmp_reg0=REG_TMP0, arg_lm_addr_reg=REG_TMP_BUF_LM_ADDR, num_val_words=(i - 3), branch_label=f'{CLS_NAME}-{FN_NAME}-TR-LB-send{i}')  # call
            tran.writeAction("yieldt")

    @classmethod
    def _get_vertex(cls, state: EFAProgram.State):
        """
        X8  - PGA_DESC_LM_OFFSET
        X9  - VID
        X10 - MASK

        Return:
        X8  - VID
        X9  - MASK (== 0 if failed)
        X10~X15 - Value words up to 6 words (ignored if failed)
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._get_vertex.__name__

        OB_PGA_DESC_LM_OFFSET = "X8"
        OB_VID = "X9"
        OB_MASK = "X10"

        REG_TMP0 = "X18"
        REG_TMP1 = "X19"

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_get_vertex
        if tran is None:
            return
        cls.tran_label_get_vertex = tran.getLabel()

        """==================== TRAN - entry ===================="""
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: entry' {'X0'}")

        # calculate lm addr
        tran.writeAction(f"addi {OB_PGA_DESC_LM_OFFSET} {REG_TMP0} {cls.PGA_DESC_OFF_VERTEX_STORE_SHT_DESC}")  # calc the first operand for the call

        SHTExt.get_with_mask_wcont(tran=tran, ret='X1', tmp_reg=REG_TMP1, desc_lm_offset_reg=REG_TMP0, key_reg=OB_VID, mask_reg=OB_MASK)  # call
        tran.writeAction("yieldt")

    @classmethod
    def _get_vertex_with_random(cls, state: EFAProgram.State):
        """
        X8  - PGA_DESC_LM_OFFSET
        X9  - RAND_NUM

        Return:
        X8  - VID (== -1 if failed)
        X9  - RAND_NUM
        X10~X15 - Value words up to 6 words (ignored if failed)
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._get_vertex_with_random.__name__

        OB_PGA_DESC_LM_OFFSET = "X8"
        OB_RAND_NUM = "X9"

        REG_TMP0 = "X18"
        REG_TMP1 = "X19"

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_get_vertex_with_random
        if tran is None:
            return
        cls.tran_label_get_vertex_with_random = tran.getLabel()

        """==================== TRAN - entry ===================="""
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: entry' {'X0'}")

        # calculate lm addr
        tran.writeAction(f"addi {OB_PGA_DESC_LM_OFFSET} {REG_TMP0} {cls.PGA_DESC_OFF_VERTEX_STORE_SHT_DESC}")  # calc the first operand for the call

        SHTExt.get_with_random_wcont(tran=tran, ret='X1', tmp_reg=REG_TMP1, desc_lm_offset_reg=REG_TMP0, rand_reg=OB_RAND_NUM)  # call
        tran.writeAction("yieldt")

    @classmethod
    def _get_vertex_with_offset(cls, state: EFAProgram.State):
        """
        X8  - PGA_DESC_LM_OFFSET
        X9  - VID
        X10 - OFFSET

        Return:
        X8  - VID
        X9  - OFFSET (== -1 if failed)
        X10~X15 - Value words up to 6 words (ignored if failed)
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._get_vertex_with_offset.__name__

        OB_PGA_DESC_LM_OFFSET = "X8"
        OB_VID = "X9"
        OB_OFFSET = "X10"

        REG_TMP0 = "X18"
        REG_TMP1 = "X19"

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_get_vertex_with_offset
        if tran is None:
            return
        cls.tran_label_get_vertex_with_offset = tran.getLabel()

        """==================== TRAN - entry ===================="""
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: entry' {'X0'}")

        # calculate lm addr
        tran.writeAction(f"addi {OB_PGA_DESC_LM_OFFSET} {REG_TMP0} {cls.PGA_DESC_OFF_VERTEX_STORE_SHT_DESC}")  # calc the first operand for the call

        SHTExt.get_with_offset_wcont(tran=tran, ret='X1', tmp_reg=REG_TMP1, desc_lm_offset_reg=REG_TMP0, key_reg=OB_VID, offset_reg=OB_OFFSET)  # call
        tran.writeAction("yieldt")

    @classmethod
    def _get_edge(cls, state: EFAProgram.State):
        """
        X8  - PGA_DESC_LM_OFFSET
        X9  - EID (Edge ID)
        X10 - MASK

        Return:
        X8  - EID
        X9  - MASK
        X10~X15 - Value words up to 6 words
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._get_edge.__name__

        OB_PGA_DESC_LM_OFFSET = "X8"
        OB_EID = "X9"
        OB_MASK = "X10"

        REG_TMP0 = "X18"
        REG_TMP1 = "X19"

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_get_edge
        if tran is None:
            return
        cls.tran_label_get_edge = tran.getLabel()

        """==================== TRAN - entry ===================="""
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: entry' {'X0'}")

        # calculate lm addr
        tran.writeAction(f"addi {OB_PGA_DESC_LM_OFFSET} {REG_TMP0} {cls.PGA_DESC_OFF_EDGE_STORE_SHT_DESC}")  # calc the first operand for the call

        SHTExt.get_with_mask_wcont(tran=tran, ret='X1', tmp_reg=REG_TMP1, desc_lm_offset_reg=REG_TMP0, key_reg=OB_EID, mask_reg=OB_MASK)  # call
        tran.writeAction("yieldt")

    @classmethod
    def _get_edge_with_offset(cls, state: EFAProgram.State):
        """
        X8  - PGA_DESC_LM_OFFSET
        X9  - EID (Edge ID)
        X10 - OFFSET

        Return:
        X8  - EID
        X9  - OFFSET (== -1 if failed)
        X10~X15 - Value words up to 6 words (ignored if failed)
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._get_edge_with_offset.__name__

        OB_PGA_DESC_LM_OFFSET = "X8"
        OB_EID = "X9"
        OB_OFFSET = "X10"

        REG_TMP0 = "X18"
        REG_TMP1 = "X19"

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_get_edge_with_offset
        if tran is None:
            return
        cls.tran_label_get_edge_with_offset = tran.getLabel()

        """==================== TRAN - entry ===================="""
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: entry' {'X0'}")

        # calculate lm addr
        tran.writeAction(f"addi {OB_PGA_DESC_LM_OFFSET} {REG_TMP0} {cls.PGA_DESC_OFF_EDGE_STORE_SHT_DESC}")  # calc the first operand for the call

        SHTExt.get_with_offset_wcont(tran=tran, ret='X1', tmp_reg=REG_TMP1, desc_lm_offset_reg=REG_TMP0, key_reg=OB_EID, offset_reg=OB_OFFSET)  # call
        tran.writeAction("yieldt")

    @classmethod
    def _append_edge_list(cls, state: EFAProgram.State):
        """
        X8 - PGA_DESC_LM_OFFSET [0:31] | TMP_BUF_LM_OFFSET [32:63]
        X9 - VID
        X10~X11 - (NB_VID0, EID0)
        (optional) X12~X13 - (NB_VID1, EID1)
        (optional) X14~X15 - (NB_VID2, EID2)

        Return:
        X8 - KEY
        X9 - EDGE_LIST_DRAM_ADDR (first word is the number of words in the list) (== 0 if failed)
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._append_edge_list.__name__

        OB_PGA_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET = "X8"
        OB_VID = "X9"
        OB_NB_VID0 = "X10"
        OB_NB_EID0 = "X11"

        REG_PGA_DESC_LM_ADDR = "X16"
        REG_TMP_BUF_LM_ADDR = "X17"

        REG_TMP0 = "X18"
        REG_TMP1 = "X19"

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_append_edge_list
        if tran is None:
            return
        cls.tran_label_append_edge_list = tran.getLabel()

        """==================== TRAN - entry ===================="""
        # calculate lm addr
        tran.writeAction(f"sli {OB_PGA_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET} {REG_PGA_DESC_LM_ADDR} {32}")
        tran.writeAction(f"sri {REG_PGA_DESC_LM_ADDR} {REG_PGA_DESC_LM_ADDR} {32}")
        tran.writeAction(f"sri {OB_PGA_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET} {REG_TMP_BUF_LM_ADDR} {32}")

        tran.writeAction(f"addi {REG_PGA_DESC_LM_ADDR} {REG_TMP0} {cls.PGA_DESC_OFF_NEIGHBOR_LIST_STORE_SHT_DESC_0}")  # calc the first operand for the call, last sht is the smallest
        tran.writeAction(f"add {REG_PGA_DESC_LM_ADDR} {'X7'} {REG_PGA_DESC_LM_ADDR}")
        tran.writeAction(f"movlr {cls.PGA_DESC_OFF_NUM_NEIGHBOR_LIST_STORE_SHT}({REG_PGA_DESC_LM_ADDR}) {REG_TMP1} 0 8")
        tran.writeAction(f"subi {REG_TMP1} {REG_TMP1} {1}")
        # tran.writeAction(f"muli {REG_TMP1} {REG_TMP1} {cls.SHT_DESC_SIZE}")  # may use shift instead if SHT_DESC_SIZE is power of 2
        tran.writeAction(f"sli {REG_TMP1} {REG_TMP1} {int(math.log2(cls.SHT_DESC_SIZE))}")  # use shift instead as SHT_DESC_SIZE is power of 2
        tran.writeAction(f"add {REG_TMP0} {REG_TMP1} {REG_TMP0}")

        tran.writeAction(f"slori {REG_TMP_BUF_LM_ADDR} {REG_TMP0} {32}")  # calc the first operand for the call
        tran.writeAction(f"add {REG_TMP_BUF_LM_ADDR} {'X7'} {REG_TMP_BUF_LM_ADDR}")
        tran.writeAction(f"movrl {REG_TMP0} {0}({REG_TMP_BUF_LM_ADDR}) 0 8")  # fill in the first operand for the call

        # extract number of value operands
        tran.writeAction(f"sri {'X2'} {REG_TMP0} {20}")
        tran.writeAction(f"andi {REG_TMP0} {REG_TMP0} {0b111}")
        tran.writeAction(f"addi {REG_TMP0} {REG_TMP0} {1}")  # add for the vid operand
        tran.writeAction(f"addi {REG_TMP_BUF_LM_ADDR} {REG_TMP1} {cls.WORD_SIZE}")
        tran.writeAction(f"bcpyol {OB_VID} {REG_TMP1} {REG_TMP0}")

        # calling with the proper number of operands
        # at least 4 operands => changed to 3 to compatible with the old scheme
        for i in range(3, 9):
            tran.writeAction(f"beqi {REG_TMP0} {i - 1} {f'{CLS_NAME}-{FN_NAME}-TR-LB-match_send_val_{i}'}")
        tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: shouldn't reach here!' {'X0'}")
        for i in range(3, 9):
            tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-match_send_val_{i}'}: addi {REG_TMP0} {REG_TMP0} {0}")  # FIXME: dummy
            SHTExt.ext_graph_append_wcont(tran=tran, ret='X1', tmp_reg0=REG_TMP1, arg_lm_addr_reg=REG_TMP_BUF_LM_ADDR, num_val_words=(i - 2))  # call
            if cls.DEBUG:
                tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: calling with {i} neighbor VIDs.' {'X0'}")
            tran.writeAction("yieldt")

    @classmethod
    def _get_edge_list_next(cls, state: EFAProgram.State):
        """
        X8  - PGA_DESC_LM_OFFSET
        X9  - VID
        X10 - WORD_OFFSET
        Return:
            X8  - VID
            X9  - WORD_OFFSET [32:63] - == 0 if not found, == -1 if reached end, == -2 if passed end, otherwise word offset for the next call
            (optional) X10~X11 - (NB_VID0, EID0)
            (optional) X12~X13 - (NB_VID1, EID1)
            (optional) X14~X15 - (NB_VID2, EID2)
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._get_edge_list_next.__name__

        OB_PGA_DESC_LM_OFFSET = "X8"
        OB_VID = "X9"
        OB_WORD_OFFSET = "X10"

        REG_TMP0 = "X17"
        REG_TMP1 = "X18"

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_get_edge_list_next
        if tran is None:
            return
        cls.tran_label_get_edge_list_next = tran.getLabel()

        """==================== TRAN - entry ===================="""
        tran.writeAction(f"addi {OB_PGA_DESC_LM_OFFSET} {REG_TMP0} {cls.PGA_DESC_OFF_NEIGHBOR_LIST_STORE_SHT_DESC_0}")  # calc the offset for the last, last sht is the smallest
        tran.writeAction(f"add {OB_PGA_DESC_LM_OFFSET} {'X7'} {REG_TMP1}")
        tran.writeAction(f"move {cls.PGA_DESC_OFF_NUM_NEIGHBOR_LIST_STORE_SHT}({REG_TMP1}) {REG_TMP1} 0 8")
        tran.writeAction(f"subi {REG_TMP1} {REG_TMP1} {1}")
        # tran.writeAction(f"muli {REG_TMP1} {REG_TMP1} {cls.SHT_DESC_SIZE}")  # may use shift instead if SHT_DESC_SIZE is power of 2
        tran.writeAction(f"sli {REG_TMP1} {REG_TMP1} {int(math.log2(cls.SHT_DESC_SIZE))}")  # use shift instead as SHT_DESC_SIZE is power of 2
        tran.writeAction(f"add {REG_TMP0} {REG_TMP1} {REG_TMP0}")

        SHTExt.ext_graph_get_next_wcont(tran=tran, ret='X1', tmp_reg=REG_TMP1, desc_lm_offset_reg=REG_TMP0, key_reg=OB_VID, offset_reg=OB_WORD_OFFSET)
        tran.writeAction("yieldt")

    @classmethod
    def _get_edge_list_addr(cls, state: EFAProgram.State):
        """
        X8  - PGA_DESC_LM_OFFSET
        X9  - VID
        Return:
            X8  - VID
            X9  - Edge list start address
            X10 - Edge list length in number of words (2 words per edge)
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._get_edge_list_addr.__name__

        OB_PGA_DESC_LM_OFFSET = "X8"
        OB_VID = "X9"

        REG_TMP0 = "X16"
        REG_TMP1 = "X17"

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_get_edge_list_addr
        if tran is None:
            return
        cls.tran_label_get_edge_list_addr = tran.getLabel()

        """==================== TRAN - entry ===================="""
        tran.writeAction(f"addi {OB_PGA_DESC_LM_OFFSET} {REG_TMP0} {cls.PGA_DESC_OFF_NEIGHBOR_LIST_STORE_SHT_DESC_0}")  # calc the offset for the last, last sht is the smallest
        tran.writeAction(f"add {OB_PGA_DESC_LM_OFFSET} {'X7'} {REG_TMP1}")
        tran.writeAction(f"move {cls.PGA_DESC_OFF_NUM_NEIGHBOR_LIST_STORE_SHT}({REG_TMP1}) {REG_TMP1} 0 8")
        tran.writeAction(f"subi {REG_TMP1} {REG_TMP1} {1}")
        # tran.writeAction(f"muli {REG_TMP1} {REG_TMP1} {cls.SHT_DESC_SIZE}")  # may use shift instead if SHT_DESC_SIZE is power of 2
        tran.writeAction(f"sli {REG_TMP1} {REG_TMP1} {int(math.log2(cls.SHT_DESC_SIZE))}")  # use shift instead as SHT_DESC_SIZE is power of 2
        tran.writeAction(f"add {REG_TMP0} {REG_TMP1} {REG_TMP0}")
        SHTExt.ext_graph_get_addr_wcont(tran=tran, ret='X1', tmp_reg=REG_TMP1, desc_lm_offset_reg=REG_TMP0, key_reg=OB_VID)
        tran.writeAction("yield_terminate")

    @classmethod
    def _get_iters_vertex_store(cls, state: EFAProgram.State):
        """
        X8 - PGA_DESC_LM_OFFSET
        X9 - ITER_DRAM_ADDR
        Return:
            X8 - Excuting NWID
            X9 - Excuting NWID
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._get_iters_vertex_store.__name__

        OB_PGA_DESC_LM_OFFSET = "X8"
        OB_ITER_DRAM_ADDR = "X9"

        REG_TMP0 = "X16"
        REG_TMP1 = "X17"

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_get_iters_vertex_store
        if tran is None:
            return
        cls.tran_label_get_iters_vertex_store = tran.getLabel()

        """==================== TRAN - entry ===================="""
        tran.writeAction(f"addi {OB_PGA_DESC_LM_OFFSET} {REG_TMP0} {cls.PGA_DESC_OFF_VERTEX_STORE_SHT_DESC}")
        SHTExt.get_iterators_wcont(tran=tran, ret='X1', tmp_reg=REG_TMP1, desc_lm_offset_reg=REG_TMP0, iter_dram_addr_reg=OB_ITER_DRAM_ADDR)
        tran.writeAction("yieldt")

    @classmethod
    def _get_next_vertex_store_iter(cls, state: EFAProgram.State):
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
        FN_NAME = cls._get_next_vertex_store_iter.__name__

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_get_next_vertex_store_iter
        if tran is None:
            return
        cls.tran_label_get_next_vertex_store_iter = tran.getLabel()

        """******************** THREAD - get_iterators ********************"""
        REG_TMP0 = 'X16'

        """==================== TRAN - ENTRY ===================="""
        OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET = "X8"
        OB_NWID__CUR_POSITION = "X9"

        SHTExt.get_next_wcont(tran=tran, ret='X1', tmp_reg=REG_TMP0, iter_word0_reg=OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET, iter_word1_reg=OB_NWID__CUR_POSITION)
        tran.writeAction("yieldt")

    @classmethod
    def _get_next_split_vertex_store_iter(cls, state: EFAProgram.State):
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
        FN_NAME = cls._get_next_split_vertex_store_iter.__name__

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_get_next_split_vertex_store_iter
        if tran is None:
            return
        cls.tran_label_get_next_split_vertex_store_iter = tran.getLabel()

        """******************** THREAD - get_iterators ********************"""
        REG_TMP0 = 'X16'

        """==================== TRAN - ENTRY ===================="""
        OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET = "X8"
        OB_NWID__CUR_POSITION = "X9"
        OB_KEY_ADDR_CONT = "X10"

        SHTExt.get_next_split_wcont(tran=tran, ret='X1', tmp_reg=REG_TMP0, iter_word0_reg=OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET, iter_word1_reg=OB_NWID__CUR_POSITION, key_addr_cont_reg=OB_KEY_ADDR_CONT)
        tran.writeAction("yieldt")

    @classmethod
    def _get_iters_edge_store(cls, state: EFAProgram.State):
        """
        X8 - PGA_DESC_LM_OFFSET
        X9 - ITER_DRAM_ADDR
        Return:
            X8 - Excuting NWID
            X9 - Excuting NWID
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._get_iters_edge_store.__name__

        OB_PGA_DESC_LM_OFFSET = "X8"
        OB_ITER_DRAM_ADDR = "X9"

        REG_TMP0 = "X16"
        REG_TMP1 = "X17"

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_get_iters_edge_store
        if tran is None:
            return
        cls.tran_label_get_iters_edge_store = tran.getLabel()

        """==================== TRAN - entry ===================="""
        tran.writeAction(f"addi {OB_PGA_DESC_LM_OFFSET} {REG_TMP0} {cls.PGA_DESC_OFF_EDGE_STORE_SHT_DESC}")
        SHTExt.get_iterators_wcont(tran=tran, ret='X1', tmp_reg=REG_TMP1, desc_lm_offset_reg=REG_TMP0, iter_dram_addr_reg=OB_ITER_DRAM_ADDR)
        tran.writeAction("yieldt")

    @classmethod
    def _get_next_edge_store_iter(cls, state: EFAProgram.State):
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
        FN_NAME = cls._get_next_edge_store_iter.__name__

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_get_next_edge_store_iter
        if tran is None:
            return
        cls.tran_label_get_next_edge_store_iter = tran.getLabel()

        """******************** THREAD - get_iterators ********************"""
        REG_TMP0 = 'X16'

        """==================== TRAN - ENTRY ===================="""
        OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET = "X8"
        OB_NWID__CUR_POSITION = "X9"

        SHTExt.get_next_wcont(tran=tran, ret='X1', tmp_reg=REG_TMP0, iter_word0_reg=OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET, iter_word1_reg=OB_NWID__CUR_POSITION)
        tran.writeAction("yieldt")

    @classmethod
    def _get_next_split_edge_store_iter(cls, state: EFAProgram.State):
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
        FN_NAME = cls._get_next_split_edge_store_iter.__name__

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_get_next_split_edge_store_iter
        if tran is None:
            return
        cls.tran_label_get_next_split_edge_store_iter = tran.getLabel()

        """******************** THREAD - get_iterators ********************"""
        REG_TMP0 = 'X16'

        """==================== TRAN - ENTRY ===================="""
        OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET = "X8"
        OB_NWID__CUR_POSITION = "X9"
        OB_KEY_ADDR_CONT = "X10"

        SHTExt.get_next_split_wcont(tran=tran, ret='X1', tmp_reg=REG_TMP0, iter_word0_reg=OB_LANE_DESC_LM_OFFSET__BUCKET_DESC_LM_OFFSET, iter_word1_reg=OB_NWID__CUR_POSITION, key_addr_cont_reg=OB_KEY_ADDR_CONT)
        tran.writeAction("yieldt")
