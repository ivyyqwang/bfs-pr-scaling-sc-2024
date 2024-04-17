from EFA_v2 import EFA, State, Transition
import sht_macros
import math
from sht_ext import SHTExt


class ParallelGraphAbstraction:
    """
    struct PGA_DESC {
        VERTEX_STORE_SHT_DESC
        EDGE_STORE_SHT_DESC
        NUM_NEIGHBOR_LIST_STORE_SHT
        NEIGHBOR_LIST_STORE_SHT_DESC * N
    }
    """

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

    PGA_DESC_OFF_VERTEX_STORE_SHT_DESC = 0  # 32 bytes
    PGA_DESC_OFF_EDGE_STORE_SHT_DESC = PGA_DESC_OFF_VERTEX_STORE_SHT_DESC + SHT_DESC_SIZE  # 32 bytes
    PGA_DESC_OFF_NUM_NEIGHBOR_LIST_STORE_SHT = PGA_DESC_OFF_EDGE_STORE_SHT_DESC + SHT_DESC_SIZE  # 8 bytes
    PGA_DESC_OFF_NEIGHBOR_LIST_STORE_SHT_DESC_0 = PGA_DESC_OFF_NUM_NEIGHBOR_LIST_STORE_SHT + 8  # 32 bytes

    @classmethod
    def setup(cls, state: State, debug: bool = False):
        cls.DEBUG = debug

        CLS_NAME = cls.__name__
        cls.tran_initialize_vertex_store = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-initialize_vertex_store-TR")
        cls.tran_initialize_edge_store = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-initialize_edge_store-TR")
        cls.tran_initialize_neighbor_list_store_append = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-initialize_neighbor_list_store_append-TR")
        cls.tran_update_vertex = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-update_vertex-TR")
        cls.tran_get_vertex = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-get_vertex-TR")
        cls.tran_update_edge = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-update_edge-TR")
        cls.tran_get_edge = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-get_edge-TR")
        cls.tran_append_neighbors = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-append_neighbors-TR")
        cls.tran_get_neighbors = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-get_neighbors-TR")

        # TODO: code injection
        SHTExt.setup(state, debug=debug)
        cls._initialize_vertex_store(state)
        cls._initialize_edge_store(state)
        cls._initialize_neighbor_list_store_append(state)
        cls._update_vertex(state)
        cls._get_vertex(state)
        cls._update_edge(state)
        cls._get_edge(state)
        cls._append_neighbors(state)
        cls._get_neighbors(state)

    @classmethod
    def _initialize_vertex_store(cls, state: State):
        """
        X8  - PGA_DESC_LM_OFFSET [0:31] | TMP_BUF_LM_OFFSET [32:63]
        X9  - NUM_ALLOC_LANES(0:31) | START_NWID(32:63);
        X10 - LANE_DESC_LM_OFFSET(0:31) | BUCKETS_PER_LANE(32:63);
        X11 - ENTRIES_PER_BUCKET(0:31) | VAL_NUM_WORDS(32:63);
        X12 - DRAM_ALLOC_ADDR;
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
    def initialize_vertex_store(cls, tran: Transition, ret_tran_label: int, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_initialize_vertex_store.getLabel(), ret_tran_label=ret_tran_label, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=5)

    @classmethod
    def initialize_vertex_store_wcont(cls, tran: Transition, cont_reg: str, tmp_reg0: str, arg_lm_addr_reg: str, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_initialize_vertex_store.getLabel(), cont_reg=cont_reg, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=5)

    @classmethod
    def _initialize_edge_store(cls, state: State):
        """
        X8  - PGA_DESC_LM_OFFSET [0:31] | TMP_BUF_LM_OFFSET [32:63]
        X9  - NUM_ALLOC_LANES(0:31) | START_NWID(32:63);
        X10 - LANE_DESC_LM_OFFSET(0:31) | BUCKETS_PER_LANE(32:63);
        X11 - ENTRIES_PER_BUCKET(0:31) | VAL_NUM_WORDS(32:63);
        X12 - DRAM_ALLOC_ADDR;
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
        # fill in first word in the extension part as zero
        tran.writeAction(f"mov_imm2reg {REG_TMP0} {0}")
        tran.writeAction(f"move {REG_TMP0} {cls.WORD_SIZE * 5}({REG_TMP_BUF_LM_ADDR}) 0 8")

        # call
        SHTExt.initialize_wcont(tran=tran, ret='X1', tmp_reg0=REG_TMP0, arg_lm_addr_reg=REG_TMP_BUF_LM_ADDR)
        tran.writeAction("yield_terminate")

    @classmethod
    def initialize_edge_store(cls, tran: Transition, ret_tran_label: int, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_initialize_edge_store.getLabel(), ret_tran_label=ret_tran_label, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=5)

    @classmethod
    def initialize_edge_store_wcont(cls, tran: Transition, cont_reg: str, tmp_reg0: str, arg_lm_addr_reg: str, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_initialize_edge_store.getLabel(), cont_reg=cont_reg, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=5)

    @classmethod
    def _initialize_neighbor_list_store_append(cls, state: State):
        """
        largest SHT needs to be created first, appending smaller SHTs to it
        smallest should have entry allocated for every vertex

        X8  - PGA_DESC_LM_OFFSET [0:31] | TMP_BUF_LM_OFFSET [32:63]
        X9  - NUM_ALLOC_LANES(0:31) | START_NWID(32:63);
        X10 - LANE_DESC_LM_OFFSET(0:31) | BUCKETS_PER_LANE(32:63);
        X11 - ENTRIES_PER_BUCKET(0:31) | VAL_NUM_WORDS(32:63);
        X12 - DRAM_ALLOC_ADDR;
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._initialize_neighbor_list_store_append.__name__

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
        tran = cls.tran_initialize_neighbor_list_store_append
        if tran is None:
            return
        cls.tran_label_initialize_neighbor_list_store_append = tran.getLabel()

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
    def initialize_neighbor_list_store_append(cls, tran: Transition, ret_tran_label: int, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_initialize_neighbor_list_store_append.getLabel(), ret_tran_label=ret_tran_label, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=5)

    @classmethod
    def initialize_neighbor_list_store_append_wcont(cls, tran: Transition, cont_reg: str, tmp_reg0: str, arg_lm_addr_reg: str, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_initialize_neighbor_list_store_append.getLabel(), cont_reg=cont_reg, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=5)

    @classmethod
    def _update_vertex(cls, state: State):
        """
        X8  - PGA_DESC_LM_OFFSET [0:31] | TMP_BUF_LM_OFFSET [32:63]
        X9  - VID
        X10 - MASK
        X11~X15 - VAL
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._update_vertex.__name__

        OB_PGA_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET = "X8"
        OB_VID = "X9"
        OB_MASK = "X10"
        OB_VAL = "X11"

        REG_PGA_DESC_LM_ADDR = "X16"
        REG_TMP_BUF_LM_ADDR = "X17"

        REG_CALL_CNT = "X18"
        REG_CUR_MASK = "X19"
        REG_CUR_KEY = "X20"
        REG_CUR_CALL_NUM_VAL = "X21"
        REG_CUR_TMP_LM_BUF_ADDR = "X22"

        REG_TMP0 = "X23"
        REG_TMP1 = "X24"
        REG_TMP2 = "X25"
        REG_TMP3 = "X26"

        REG_HASH_SEED = "X27"
        REG_VID = "X28"

        REG_CONT = "X31"

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_update_vertex
        if tran is None:
            return
        cls.tran_label_update_vertex = tran.getLabel()
        tran_update_ret = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-update_ret")

        """==================== TRAN - entry ===================="""
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: entry' {'X0'}")

        # calculate lm addr
        tran.writeAction(f"lshift {OB_PGA_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET} {REG_PGA_DESC_LM_ADDR} {32}")
        tran.writeAction(f"rshift {REG_PGA_DESC_LM_ADDR} {REG_PGA_DESC_LM_ADDR} {32}")
        tran.writeAction(f"rshift {OB_PGA_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET} {REG_TMP_BUF_LM_ADDR} {32}")
        tran.writeAction(f"addi {REG_PGA_DESC_LM_ADDR} {REG_TMP0} {cls.PGA_DESC_OFF_VERTEX_STORE_SHT_DESC}")  # calc the first operand for the call
        tran.writeAction(f"lshift_or {REG_TMP_BUF_LM_ADDR} {REG_TMP0} {32}")  # calc the first operand for the call
        tran.writeAction(f"add {REG_PGA_DESC_LM_ADDR} {'X7'} {REG_PGA_DESC_LM_ADDR}")
        tran.writeAction(f"add {REG_TMP_BUF_LM_ADDR} {'X7'} {REG_TMP_BUF_LM_ADDR}")
        tran.writeAction(f"move {REG_TMP0} {0}({REG_TMP_BUF_LM_ADDR}) 0 8")  # fill in the first operand for the call

        # save operands
        tran.writeAction(f"addi {'X1'} {REG_CONT} {0}")
        tran.writeAction(f"addi {OB_MASK} {REG_CUR_MASK} {0}")
        tran.writeAction(f"addi {OB_VID} {REG_VID} {0}")
        tran.writeAction(f"addi {OB_VID} {REG_CUR_KEY} {0}")

        # extract number of value operands
        tran.writeAction(f"rshift_and_imm {'X2'} {REG_TMP0} {20} {0b111}")
        tran.writeAction(f"subi {REG_TMP0} {REG_TMP0} {1}")  # subtract for the mask operand

        # spliting operands to multiple calls based on the mask
        tran.writeAction(f"mov_imm2reg {REG_HASH_SEED} {0}")  # set hash seed to 0
        tran.writeAction(f"mov_imm2reg {REG_CALL_CNT} {0}")
        tran.writeAction(f"mov_imm2reg {REG_CUR_CALL_NUM_VAL} {0}")  # reset cur call num val
        tran.writeAction(f"mov_imm2reg {REG_TMP1} {1}")  # reset bit to probe
        tran.writeAction(f"addi {REG_TMP_BUF_LM_ADDR} {REG_CUR_TMP_LM_BUF_ADDR} {cls.WORD_SIZE * 3}")  # reset tmp buf lm addr ptr to val operand addr
        tran.writeAction(f"andi {REG_CUR_MASK} {REG_TMP1} {0b1111_1111}")  # REG_TMP1 -> current call 8 bits mask
        tran.writeAction(f"move {REG_TMP1} {cls.WORD_SIZE * 2}({REG_TMP_BUF_LM_ADDR}) 0 8")  # fill in mask for the first call
        tran.writeAction(f"rshift {REG_CUR_MASK} {REG_CUR_MASK} {8}")  # shift mask for next
        # for each operand, check if the corresponding bit is set, if so, copy to buffer
        # TODO: optimization? popcount + copy? hard to code since need to keep track of which operand to copy, or first copy all operands to buffer
        for i in range(1, 6):  # 1~5 value operands
            tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-next_operand_{i}'}: blei {REG_TMP0} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-next_operand_6'}")  # done sending
            tran.writeAction(f"subi {REG_TMP0} {REG_TMP0} {1}")  # decrement number of value operands left

            tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-next_bit_{i}'}: andi {REG_TMP1} {REG_TMP2} {1}")  # probe if bit is set
            tran.writeAction(f"rshift {REG_TMP1} {REG_TMP1} {1}")  # shift bit to probe

            # check if bit is set
            tran.writeAction(f"bnei {REG_TMP2} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-bit_set_{i}'}")
            # => cur bit not set
            tran.writeAction(f"bnei {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-next_bit_{i}'}")  # cur bit not set & more bits left -> find next set bit
            tran.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-LB-bit_check_skip_{i}'}")  # cur bit not set & no bits left -> check send/skip
            # => cur bit set
            # copy operand
            tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-bit_set_{i}'}: move {f'X{i + 11 - 1}'} {0}({REG_CUR_TMP_LM_BUF_ADDR}) 1 8")
            tran.writeAction(f"addi {REG_CUR_CALL_NUM_VAL} {REG_CUR_CALL_NUM_VAL} {1}")
            tran.writeAction(f"bnei {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-next_operand_{i + 1}'}")  # cur bit set & more bits left -> to copy more operands
            tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-bit_check_skip_{i}'}: beqi {REG_CUR_CALL_NUM_VAL} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-skip_call_{i}'}")  # cur bit set & no bits left -> send/skip

            # calling with the proper number of operands
            # mininum 4 words: X8, X9, X10, X11
            for j in range(4, 8 + 1):
                tran.writeAction(f"beqi {REG_CUR_CALL_NUM_VAL} {j - 3} {f'{CLS_NAME}-{FN_NAME}-TR-LB-call_{i}_{j}'}")
            if cls.DEBUG:
                tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: shouldn't reach here!' {'X0'}")
            for j in range(4, 8 + 1):
                # fill in
                tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-call_{i}_{j}'}: move {REG_CUR_KEY} {cls.WORD_SIZE * 1}({REG_TMP_BUF_LM_ADDR}) 0 8")  # fill in VID
                if cls.DEBUG:
                    tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: calling SHTExt.update_with_mask with %d values' {'X0'} {REG_CUR_CALL_NUM_VAL}")
                SHTExt.update_with_mask(tran=tran, ret=tran_update_ret.getLabel(), tmp_reg0=REG_TMP2, tmp_reg1=REG_TMP3, arg_lm_addr_reg=REG_TMP_BUF_LM_ADDR, num_val_words=(j - 3))  # call
                tran.writeAction(f"addi {REG_CALL_CNT} {REG_CALL_CNT} {1}")  # increment call count
                tran.writeAction(f"beqi {REG_CUR_MASK} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-next_operand_6'}")  # check if REG_CUR_MASK is 0, if so, done with all calls
                tran.writeAction(f"mov_imm2reg {REG_CUR_CALL_NUM_VAL} {0}")  # reset cur call num val
                tran.writeAction(f"andi {REG_CUR_MASK} {REG_TMP1} {0b1111_1111}")  # REG_TMP1 -> current call 8 bits mask
                tran.writeAction(f"move {REG_TMP1} {cls.WORD_SIZE * 2}({REG_TMP_BUF_LM_ADDR}) 0 8")  # fill in mask for the first call
                tran.writeAction(f"rshift {REG_CUR_MASK} {REG_CUR_MASK} {8}")  # shift mask for next
                tran.writeAction(f"addi {REG_TMP_BUF_LM_ADDR} {REG_CUR_TMP_LM_BUF_ADDR} {cls.WORD_SIZE * 3}")  # reset tmp buf lm addr ptr to val operand addr
                tran.writeAction(f"hash {REG_HASH_SEED} {REG_CUR_KEY}")  # hash vid
                tran.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-LB-next_operand_{i + 1}'}")  # jmp

            # skipped call
            tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-skip_call_{i}'}: andi {REG_CUR_MASK} {REG_TMP1} {0b1111_1111}")  # REG_TMP1 -> current call 8 bits mask
            tran.writeAction(f"move {REG_TMP1} {cls.WORD_SIZE * 2}({REG_TMP_BUF_LM_ADDR}) 0 8")  # fill in mask for the first call
            tran.writeAction(f"rshift {REG_CUR_MASK} {REG_CUR_MASK} {8}")  # shift mask for next
            tran.writeAction(f"hash {REG_HASH_SEED} {REG_CUR_KEY}")  # hash vid
            tran.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-LB-next_operand_{i + 1}'}")  # jmp

        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-next_operand_6'}: mov_imm2reg {REG_TMP0} {0}")  # count for number of failed updates
        tran.writeAction("yield")

        """==================== TRAN - update ret ===================="""
        # call return (user needs to mitigate insertion failures)
        tran_update_ret.writeAction(f"bgti {'X9'} {0} {f'{CLS_NAME}-{FN_NAME}-TR-update_ret-LB-success'}")  # success
        tran_update_ret.writeAction(f"addi {REG_TMP0} {REG_TMP0} {1}")  # increment failed count
        tran_update_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-update_ret-LB-success'}: subi {REG_CALL_CNT} {REG_CALL_CNT} {1}")  # decrement call count
        tran_update_ret.writeAction(f"bgti {REG_CALL_CNT} {0} {f'{CLS_NAME}-{FN_NAME}-TR-update_ret-LB-wait'}")
        # return format: (vid, num_failed_updates)
        sht_macros.return_wreg(tran=tran_update_ret, cont_reg=REG_CONT, arg_reg0=REG_VID, arg_reg1=REG_TMP0)  # return
        tran_update_ret.writeAction("yield_terminate")
        tran_update_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-update_ret-LB-wait'}: yield")

    @classmethod
    def update_vertex(cls, tran: Transition, ret_tran_label: int, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, num_val_words: int, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_update_vertex.getLabel(), ret_tran_label=ret_tran_label, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=(3 + num_val_words))

    @classmethod
    def update_vertex_wcont(cls, tran: Transition, cont_reg: str, tmp_reg0: str, arg_lm_addr_reg: str, num_val_words: int, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_update_vertex.getLabel(), cont_reg=cont_reg, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=(3 + num_val_words))

    @classmethod
    def _get_vertex(cls, state: State):
        """
        X8  - PGA_DESC_LM_OFFSET [0:31] | TMP_BUF_LM_OFFSET [32:63]
        X9  - VID
        X10 - MASK
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._get_vertex.__name__

        OB_PGA_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET = "X8"
        OB_VID = "X9"
        OB_MASK = "X10"

        REG_LM_OFF_VERTEX_STORE_SHT_DESC = "X16"
        REG_CALL_CNT = "X17"
        REG_TMP0 = "X18"
        REG_TMP1 = "X19"
        REG_TMP2 = "X20"
        REG_TMP3 = "X21"

        # reserve 8 registers to store the return value address
        REG_RET_TMP_LM_ADDR = []
        for i in range(23, 31):
            REG_RET_TMP_LM_ADDR.append(f"X{i}")
        REG_CUR_RET_TMP_LM_ADDR = "X30"

        REG_CONT = "X31"

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_get_vertex
        if tran is None:
            return
        cls.tran_label_get_vertex = tran.getLabel()
        tran_get_ret = []
        for i in range(8):
            tran_get_ret.append(state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-get_ret_{i}"))

        """==================== TRAN - entry ===================="""
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: entry' {'X0'}")
        tran.writeAction(f"lshift {OB_PGA_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET} {REG_LM_OFF_VERTEX_STORE_SHT_DESC} {32}")
        tran.writeAction(f"rshift {REG_LM_OFF_VERTEX_STORE_SHT_DESC} {REG_LM_OFF_VERTEX_STORE_SHT_DESC} {32}")
        tran.writeAction(f"addi {REG_LM_OFF_VERTEX_STORE_SHT_DESC} {REG_LM_OFF_VERTEX_STORE_SHT_DESC} {cls.PGA_DESC_OFF_VERTEX_STORE_SHT_DESC}")
        tran.writeAction(f"rshift {OB_PGA_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET} {REG_CUR_RET_TMP_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_CUR_RET_TMP_LM_ADDR} {'X7'} {REG_CUR_RET_TMP_LM_ADDR}")

        tran.writeAction(f"addi {'X1'} {REG_CONT} {0}")

        tran.writeAction(f"move {OB_VID} {0}({REG_CUR_RET_TMP_LM_ADDR}) 1 8")  # fill in vid for return
        tran.writeAction(f"move {OB_MASK} {0}({REG_CUR_RET_TMP_LM_ADDR}) 1 8")  # fill in mask for return

        tran.writeAction(f"mov_imm2reg {REG_CALL_CNT} {0}")
        tran.writeAction(f"addi {OB_VID} {REG_TMP1} {0}")  # REG_TMP1 is the current key

        for i in range(8):  # 8 bits per call, 8 calls
            tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-next_call_{i}'}: rshift {OB_MASK} {REG_TMP0} {8 * i}")
            tran.writeAction(f"beqi {REG_TMP0} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-next_call_8'}")  # no more calls
            tran.writeAction(f"andi {REG_TMP0} {REG_TMP0} {0b1111_1111}")
            # TODO: if mask is 0, skip?
            SHTExt.get_with_mask(tran=tran, ret=tran_get_ret[i].getLabel(), tmp_reg0=REG_TMP2, tmp_reg1=REG_TMP3, desc_lm_offset_reg=REG_LM_OFF_VERTEX_STORE_SHT_DESC, key_reg=REG_TMP1, mask_reg=REG_TMP0)
            tran.writeAction(f"addi {REG_CALL_CNT} {REG_CALL_CNT} {1}")  # increment call count
            tran.writeAction(f"mov_imm2reg {REG_TMP2} {0}")
            tran.writeAction(f"hash {REG_TMP2} {REG_TMP1}")  # hash vid

            tran.writeAction(f"addi {REG_CUR_RET_TMP_LM_ADDR} {REG_RET_TMP_LM_ADDR[i]} {0}")  # set return lm write addr
            for j in range(8):  # popcount for 8 bits, finding out where the return value should be written in the return lm buffer
                tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-next_bit_{i}_{j}'}: rshift {REG_TMP0} {REG_TMP2} {j}")
                tran.writeAction(f"beqi {REG_TMP2} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-next_call_{i + 1}'}")  # no more set bits, next call
                tran.writeAction(f"andi {REG_TMP2} {REG_TMP2} {1}")
                tran.writeAction(f"beqi {REG_TMP2} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-next_bit_{i}_{j + 1}'}")
                tran.writeAction(f"addi {REG_CUR_RET_TMP_LM_ADDR} {REG_CUR_RET_TMP_LM_ADDR} {cls.WORD_SIZE}")  # increment return lm write addr

            tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-next_bit_{i}_{8}'}: jmp {f'{CLS_NAME}-{FN_NAME}-TR-LB-next_call_{i + 1}'}")  # FIXME: redundant

        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-next_call_8'}: subi {REG_RET_TMP_LM_ADDR[0]} {REG_TMP0} {cls.WORD_SIZE * 2}")  # REG_TMP0 -> tmp buf lm addr start
        tran.writeAction(f"mov_imm2reg {REG_TMP2} {0}")  # for accumulating number of values returned
        # user have to guarantee that there is at least one call
        tran.writeAction("yield")

        """==================== TRANs - get return ===================="""
        for i in range(8):  # for each parallel call
            # FIXME: check failure and return to indicate failure
            # call return format: (vid, mask, vals)
            tran_get_ret[i].writeAction(f"subi {REG_CALL_CNT} {REG_CALL_CNT} {1}")  # decrement call count
            # extract number of value operands
            tran_get_ret[i].writeAction(f"rshift_and_imm {'X2'} {REG_TMP1} {20} {0b111}")
            # accumulate number of values returned for appopriate return num operands
            tran_get_ret[i].writeAction(f"add {REG_TMP1} {REG_TMP2} {REG_TMP2}")
            # copy
            tran_get_ret[i].writeAction(f"bcopy_ops {'X10'} {REG_RET_TMP_LM_ADDR[i]} {REG_TMP1}")
            # if call is zero, return and terminate
            tran_get_ret[i].writeAction(f"bgti {REG_CALL_CNT} {0} {f'{CLS_NAME}-{FN_NAME}-TR-get_ret_{i}-LB-wait'}")

            # calling with the proper number of operands
            for j in range(3, 9):
                tran_get_ret[i].writeAction(f"beqi {REG_TMP2} {j - 2} {f'{CLS_NAME}-{FN_NAME}-TR-get_ret_{i}-LB-match_send_val_{j}'}")
            if cls.DEBUG:
                tran_get_ret[i].writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: shouldn't reach here!' {'X0'}")
            for j in range(3, 9):
                tran_get_ret[i].writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-get_ret_{i}-LB-match_send_val_{j}'}: addi {REG_TMP0} {REG_TMP0} {0}")  # FIXME: dummy
                sht_macros.return_wlm(tran=tran_get_ret[i], cont_reg=REG_CONT, arg_lm_addr_reg=REG_TMP0, arg_lm_words=j)  # return
                if cls.DEBUG:
                    tran_get_ret[i].writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: return with {j} attrs.' {'X0'}")
                tran_get_ret[i].writeAction("yield_terminate")

            tran_get_ret[i].writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-get_ret_{i}-LB-wait'}: yield")

    @classmethod
    def get_vertex(cls, tran: Transition, ret_tran_label: int, tmp_reg0: str, tmp_reg1: str, desc_lm_offset_reg: str, vid_reg: str, mask_reg: str, dst_nwid_reg: str = 'X0'):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_get_vertex.getLabel(), ret_tran_label=ret_tran_label, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=desc_lm_offset_reg, arg_reg1=vid_reg, arg_reg2=mask_reg)

    @classmethod
    def get_vertex_wcont(cls, tran: Transition, cont_reg: str, tmp_reg: str, desc_lm_offset_reg: str, vid_reg: str, mask_reg: str, dst_nwid_reg: str = 'X0'):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_get_vertex.getLabel(), cont_reg=cont_reg, tmp_reg=tmp_reg, arg_reg0=desc_lm_offset_reg, arg_reg1=vid_reg, arg_reg2=mask_reg)

    @classmethod
    def _update_edge(cls, state: State):
        """
        X8  - PGA_DESC_LM_OFFSET [0:31] | TMP_BUF_LM_OFFSET [32:63]
        X9  - SRC_VID
        X10 - DST_VID
        X11 - MASK
        X12~X15 - VAL
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._update_edge.__name__

        OB_PGA_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET = "X8"
        OB_SRC_VID = "X9"
        OB_DST_VID = "X10"
        OB_MASK = "X11"
        OB_VAL = "X12"

        REG_PGA_DESC_LM_ADDR = "X16"
        REG_TMP_BUF_LM_ADDR = "X17"

        REG_CALL_CNT = "X18"
        REG_CUR_MASK = "X19"
        REG_CUR_KEY = "X20"
        REG_CUR_CALL_NUM_VAL = "X21"
        REG_CUR_TMP_LM_BUF_ADDR = "X22"

        REG_TMP0 = "X23"
        REG_TMP1 = "X24"
        REG_TMP2 = "X25"
        REG_TMP3 = "X26"

        REG_HASH_SEED = "X27"
        REG_SRC_VID = "X28"
        REG_DST_VID = "X29"

        REG_CONT = "X31"

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_update_edge
        if tran is None:
            return
        cls.tran_label_update_edge = tran.getLabel()
        tran_update_ret = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-update_ret")

        """==================== TRAN - entry ===================="""
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: entry' {'X0'}")

        # calculate lm addr
        tran.writeAction(f"lshift {OB_PGA_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET} {REG_PGA_DESC_LM_ADDR} {32}")
        tran.writeAction(f"rshift {REG_PGA_DESC_LM_ADDR} {REG_PGA_DESC_LM_ADDR} {32}")
        tran.writeAction(f"rshift {OB_PGA_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET} {REG_TMP_BUF_LM_ADDR} {32}")
        tran.writeAction(f"addi {REG_PGA_DESC_LM_ADDR} {REG_TMP0} {cls.PGA_DESC_OFF_EDGE_STORE_SHT_DESC}")  # calc the first operand for the call
        tran.writeAction(f"lshift_or {REG_TMP_BUF_LM_ADDR} {REG_TMP0} {32}")  # calc the first operand for the call
        tran.writeAction(f"add {REG_PGA_DESC_LM_ADDR} {'X7'} {REG_PGA_DESC_LM_ADDR}")
        tran.writeAction(f"add {REG_TMP_BUF_LM_ADDR} {'X7'} {REG_TMP_BUF_LM_ADDR}")
        tran.writeAction(f"move {REG_TMP0} {0}({REG_TMP_BUF_LM_ADDR}) 0 8")  # fill in the first operand for the call

        # save operands
        tran.writeAction(f"addi {'X1'} {REG_CONT} {0}")
        tran.writeAction(f"addi {OB_MASK} {REG_CUR_MASK} {0}")
        tran.writeAction(f"addi {OB_SRC_VID} {REG_SRC_VID} {0}")
        tran.writeAction(f"addi {OB_DST_VID} {REG_DST_VID} {0}")

        # extract number of value operands
        tran.writeAction(f"rshift_and_imm {'X2'} {REG_TMP0} {20} {0b111}")
        tran.writeAction(f"subi {REG_TMP0} {REG_TMP0} {2}")  # subtract for the dst_vid & mask operand

        # hash src & dst vid to get the initial key
        tran.writeAction(f"mov_imm2reg {REG_CUR_KEY} {0}")
        tran.writeAction(f"hash {REG_SRC_VID} {REG_CUR_KEY}")
        tran.writeAction(f"hash {REG_DST_VID} {REG_CUR_KEY}")
        # spliting operands to multiple calls based on the mask
        tran.writeAction(f"mov_imm2reg {REG_HASH_SEED} {0}")  # set hash seed to 0
        tran.writeAction(f"mov_imm2reg {REG_CALL_CNT} {0}")
        tran.writeAction(f"mov_imm2reg {REG_CUR_CALL_NUM_VAL} {0}")  # reset cur call num val
        tran.writeAction(f"mov_imm2reg {REG_TMP1} {1}")  # reset bit to probe
        tran.writeAction(f"addi {REG_TMP_BUF_LM_ADDR} {REG_CUR_TMP_LM_BUF_ADDR} {cls.WORD_SIZE * 3}")  # reset tmp buf lm addr ptr to val operand addr

        tran.writeAction(f"andi {REG_CUR_MASK} {REG_TMP1} {0b1111_1111}")  # REG_TMP1 -> current call 8 bits mask
        tran.writeAction(f"move {REG_TMP1} {cls.WORD_SIZE * 2}({REG_TMP_BUF_LM_ADDR}) 0 8")  # fill in mask for the first call
        tran.writeAction(f"rshift {REG_CUR_MASK} {REG_CUR_MASK} {8}")  # shift mask for next
        for i in range(1, 5):  # 1~4 value operands
            tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-next_operand_{i}'}: blei {REG_TMP0} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-next_operand_5'}")  # done sending
            tran.writeAction(f"subi {REG_TMP0} {REG_TMP0} {1}")  # decrement number of value operands left

            tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-next_bit_{i}'}: andi {REG_TMP1} {REG_TMP2} {1}")  # probe if bit is set
            tran.writeAction(f"rshift {REG_TMP1} {REG_TMP1} {1}")  # shift bit to probe

            # check if bit is set
            tran.writeAction(f"bnei {REG_TMP2} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-bit_set_{i}'}")
            # => cur bit not set
            tran.writeAction(f"bnei {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-next_bit_{i}'}")  # cur bit not set & more bits left -> find next set bit
            tran.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-LB-bit_check_skip_{i}'}")  # cur bit not set & no bits left -> check send/skip
            # => cur bit set
            # copy operand
            tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-bit_set_{i}'}: move {f'X{i + 12 - 1}'} {0}({REG_CUR_TMP_LM_BUF_ADDR}) 1 8")
            tran.writeAction(f"addi {REG_CUR_CALL_NUM_VAL} {REG_CUR_CALL_NUM_VAL} {1}")
            tran.writeAction(f"bnei {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-next_operand_{i + 1}'}")  # cur bit set & more bits left -> to copy more operands
            tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-bit_check_skip_{i}'}: beqi {REG_CUR_CALL_NUM_VAL} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-skip_call_{i}'}")  # cur bit set & no bits left -> send/skip

            # calling with the proper number of operands
            # mininum 4 words: X8, X9, X10, X11
            for j in range(4, 8 + 1):
                tran.writeAction(f"beqi {REG_CUR_CALL_NUM_VAL} {j - 3} {f'{CLS_NAME}-{FN_NAME}-TR-LB-call_{i}_{j}'}")
            if cls.DEBUG:
                tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: shouldn't reach here!' {'X0'}")
            for j in range(4, 8 + 1):
                # fill in
                tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-call_{i}_{j}'}: move {REG_CUR_KEY} {cls.WORD_SIZE * 1}({REG_TMP_BUF_LM_ADDR}) 0 8")  # fill in key
                if cls.DEBUG:
                    tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: calling SHTExt.update_with_mask with %d values' {'X0'} {REG_CUR_CALL_NUM_VAL}")
                SHTExt.update_with_mask(tran=tran, ret=tran_update_ret.getLabel(), tmp_reg0=REG_TMP2, tmp_reg1=REG_TMP3, arg_lm_addr_reg=REG_TMP_BUF_LM_ADDR, num_val_words=(j - 3))  # call
                tran.writeAction(f"addi {REG_CALL_CNT} {REG_CALL_CNT} {1}")  # increment call count
                tran.writeAction(f"beqi {REG_CUR_MASK} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-next_operand_5'}")  # check if REG_CUR_MASK is 0, if so, done with all calls
                tran.writeAction(f"mov_imm2reg {REG_CUR_CALL_NUM_VAL} {0}")  # reset cur call num val
                tran.writeAction(f"andi {REG_CUR_MASK} {REG_TMP1} {0b1111_1111}")  # REG_TMP1 -> current call 8 bits mask
                tran.writeAction(f"move {REG_TMP1} {cls.WORD_SIZE * 2}({REG_TMP_BUF_LM_ADDR}) 0 8")  # fill in mask for the first call
                tran.writeAction(f"rshift {REG_CUR_MASK} {REG_CUR_MASK} {8}")  # shift mask for next
                tran.writeAction(f"addi {REG_TMP_BUF_LM_ADDR} {REG_CUR_TMP_LM_BUF_ADDR} {cls.WORD_SIZE * 3}")  # reset tmp buf lm addr ptr to val operand addr
                tran.writeAction(f"hash {REG_HASH_SEED} {REG_CUR_KEY}")  # hash vid
                tran.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-LB-next_operand_{i + 1}'}")  # jmp

            # skipped call
            tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-skip_call_{i}'}: andi {REG_CUR_MASK} {REG_TMP1} {0b1111_1111}")  # REG_TMP1 -> current call 8 bits mask
            tran.writeAction(f"move {REG_TMP1} {cls.WORD_SIZE * 2}({REG_TMP_BUF_LM_ADDR}) 0 8")  # fill in mask for the first call
            tran.writeAction(f"rshift {REG_CUR_MASK} {REG_CUR_MASK} {8}")  # shift mask for next
            tran.writeAction(f"hash {REG_HASH_SEED} {REG_CUR_KEY}")  # hash vid
            tran.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-LB-next_operand_{i + 1}'}")  # jmp

        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-next_operand_5'}: mov_imm2reg {REG_TMP0} {0}")  # count for number of failed updates
        tran.writeAction("yield")

        """==================== TRAN - update ret ===================="""
        # call return (user needs to mitigate insertion failures)
        tran_update_ret.writeAction(f"bgti {'X9'} {0} {f'{CLS_NAME}-{FN_NAME}-TR-update_ret-LB-success'}")  # success
        tran_update_ret.writeAction(f"addi {REG_TMP0} {REG_TMP0} {1}")  # increment failed count
        tran_update_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-update_ret-LB-success'}: subi {REG_CALL_CNT} {REG_CALL_CNT} {1}")  # decrement call count
        tran_update_ret.writeAction(f"bgti {REG_CALL_CNT} {0} {f'{CLS_NAME}-{FN_NAME}-TR-update_ret-LB-wait'}")
        # return format: (src_vid, dst_vid, num_failed_updates)
        sht_macros.return_wreg(tran=tran_update_ret, cont_reg=REG_CONT, arg_reg0=REG_SRC_VID, arg_reg1=REG_DST_VID, arg_reg2=REG_TMP0)  # return
        tran_update_ret.writeAction("yield_terminate")
        tran_update_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-update_ret-LB-wait'}: yield")

    @classmethod
    def update_edge(cls, tran: Transition, ret_tran_label: int, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, num_val_words: int, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_update_edge.getLabel(), ret_tran_label=ret_tran_label, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=(4 + num_val_words))

    @classmethod
    def update_edge_wcont(cls, tran: Transition, cont_reg: str, tmp_reg0: str, arg_lm_addr_reg: str, num_val_words: int, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_update_edge.getLabel(), cont_reg=cont_reg, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=(4 + num_val_words))

    @classmethod
    def _get_edge(cls, state: State):
        """
        X8  - PGA_DESC_LM_OFFSET [0:31] | TMP_BUF_LM_OFFSET [32:63]
        X9  - SRC_VID
        X10 - DST_VID
        X11 - MASK
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._get_edge.__name__

        OB_PGA_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET = "X8"
        SRC_VID = "X9"
        DST_VID = "X10"
        OB_MASK = "X11"

        REG_LM_OFF_EDGE_STORE_SHT_DESC = "X16"
        REG_CALL_CNT = "X17"
        REG_TMP0 = "X18"
        REG_TMP1 = "X19"
        REG_TMP2 = "X20"
        REG_TMP3 = "X21"

        REG_RET_TMP_LM_ADDR = []
        for i in range(23, 31):
            REG_RET_TMP_LM_ADDR.append(f"X{i}")
        REG_CUR_RET_TMP_LM_ADDR = "X30"

        REG_CONT = "X31"

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_get_edge
        if tran is None:
            return
        cls.tran_label_get_edge = tran.getLabel()
        tran_get_ret = []
        for i in range(8):
            tran_get_ret.append(state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-get_ret_{i}"))

        """==================== TRAN - entry ===================="""
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: entry' {'X0'}")
        tran.writeAction(f"lshift {OB_PGA_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET} {REG_LM_OFF_EDGE_STORE_SHT_DESC} {32}")
        tran.writeAction(f"rshift {REG_LM_OFF_EDGE_STORE_SHT_DESC} {REG_LM_OFF_EDGE_STORE_SHT_DESC} {32}")
        tran.writeAction(f"addi {REG_LM_OFF_EDGE_STORE_SHT_DESC} {REG_LM_OFF_EDGE_STORE_SHT_DESC} {cls.PGA_DESC_OFF_EDGE_STORE_SHT_DESC}")
        tran.writeAction(f"rshift {OB_PGA_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET} {REG_CUR_RET_TMP_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_CUR_RET_TMP_LM_ADDR} {'X7'} {REG_CUR_RET_TMP_LM_ADDR}")

        tran.writeAction(f"addi {'X1'} {REG_CONT} {0}")

        tran.writeAction(f"move {SRC_VID} {0}({REG_CUR_RET_TMP_LM_ADDR}) 1 8")  # fill in src_vid for return
        tran.writeAction(f"move {DST_VID} {0}({REG_CUR_RET_TMP_LM_ADDR}) 1 8")  # fill in dst_vid for return
        tran.writeAction(f"move {OB_MASK} {0}({REG_CUR_RET_TMP_LM_ADDR}) 1 8")  # fill in mask for return

        tran.writeAction(f"mov_imm2reg {REG_CALL_CNT} {0}")
        tran.writeAction(f"mov_imm2reg {REG_TMP1} {0}")  # REG_TMP1 is the current key
        tran.writeAction(f"hash {SRC_VID} {REG_TMP1}")  # hash src_vid
        tran.writeAction(f"hash {DST_VID} {REG_TMP1}")  # hash dst_vid

        for i in range(8):  # 8 bits per call, 8 calls
            tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-next_call_{i}'}: rshift {OB_MASK} {REG_TMP0} {8 * i}")
            tran.writeAction(f"beqi {REG_TMP0} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-next_call_8'}")  # no more calls
            tran.writeAction(f"andi {REG_TMP0} {REG_TMP0} {0b1111_1111}")
            SHTExt.get_with_mask(tran=tran, ret=tran_get_ret[i].getLabel(), tmp_reg0=REG_TMP2, tmp_reg1=REG_TMP3, desc_lm_offset_reg=REG_LM_OFF_EDGE_STORE_SHT_DESC, key_reg=REG_TMP1, mask_reg=REG_TMP0)
            tran.writeAction(f"addi {REG_CALL_CNT} {REG_CALL_CNT} {1}")  # increment call count
            tran.writeAction(f"mov_imm2reg {REG_TMP2} {0}")
            tran.writeAction(f"hash {REG_TMP2} {REG_TMP1}")  # hash vid

            tran.writeAction(f"addi {REG_CUR_RET_TMP_LM_ADDR} {REG_RET_TMP_LM_ADDR[i]} {0}")  # set return lm write addr
            for j in range(8):  # popcount for 8 bits, finding out where the return value should be written in the return lm buffer
                tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-next_bit_{i}_{j}'}: rshift {REG_TMP0} {REG_TMP2} {j}")
                tran.writeAction(f"beqi {REG_TMP2} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-next_call_{i + 1}'}")  # no more set bits, next call
                tran.writeAction(f"andi {REG_TMP2} {REG_TMP2} {1}")
                tran.writeAction(f"beqi {REG_TMP2} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-next_bit_{i}_{j + 1}'}")
                tran.writeAction(f"addi {REG_CUR_RET_TMP_LM_ADDR} {REG_CUR_RET_TMP_LM_ADDR} {cls.WORD_SIZE}")  # increment return lm write addr

            tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-next_bit_{i}_{8}'}: jmp {f'{CLS_NAME}-{FN_NAME}-TR-LB-next_call_{i + 1}'}")  # FIXME: redundant

        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-next_call_8'}: subi {REG_RET_TMP_LM_ADDR[0]} {REG_TMP0} {cls.WORD_SIZE * 3}")  # REG_TMP0 -> tmp buf lm addr start
        tran.writeAction(f"mov_imm2reg {REG_TMP2} {0}")  # for accumulating number of values returned
        # user have to guarantee that there is at least one call
        tran.writeAction("yield")

        """==================== TRANs - get return ===================="""
        for i in range(8):  # for each parallel call
            # FIXME: check failure and return to indicate failure
            # call return format: (src_vid, dst_vid, mask, vals)
            tran_get_ret[i].writeAction(f"subi {REG_CALL_CNT} {REG_CALL_CNT} {1}")  # decrement call count
            # extract number of value operands
            tran_get_ret[i].writeAction(f"rshift_and_imm {'X2'} {REG_TMP1} {20} {0b111}")
            # accumulate number of values returned for appopriate return num operands
            tran_get_ret[i].writeAction(f"add {REG_TMP1} {REG_TMP2} {REG_TMP2}")
            # copy
            tran_get_ret[i].writeAction(f"bcopy_ops {'X10'} {REG_RET_TMP_LM_ADDR[i]} {REG_TMP1}")
            # if call is zero, return and terminate
            tran_get_ret[i].writeAction(f"bgti {REG_CALL_CNT} {0} {f'{CLS_NAME}-{FN_NAME}-TR-get_ret_{i}-LB-wait'}")

            # calling with the proper number of operands
            for j in range(4, 9):
                tran_get_ret[i].writeAction(f"beqi {REG_TMP2} {j - 3} {f'{CLS_NAME}-{FN_NAME}-TR-get_ret_{i}-LB-match_send_val_{j}'}")
            if cls.DEBUG:
                tran_get_ret[i].writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: shouldn't reach here!' {'X0'}")
            for j in range(4, 9):
                tran_get_ret[i].writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-get_ret_{i}-LB-match_send_val_{j}'}: addi {REG_TMP0} {REG_TMP0} {0}")  # FIXME: dummy
                sht_macros.return_wlm(tran=tran_get_ret[i], cont_reg=REG_CONT, arg_lm_addr_reg=REG_TMP0, arg_lm_words=j)  # return
                if cls.DEBUG:
                    tran_get_ret[i].writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: return with {j} attrs.' {'X0'}")
                tran_get_ret[i].writeAction("yield_terminate")

            tran_get_ret[i].writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-get_ret_{i}-LB-wait'}: yield")

    @classmethod
    def get_edge(cls, tran: Transition, ret_tran_label: int, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_get_edge.getLabel(), ret_tran_label=ret_tran_label, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=4)

    @classmethod
    def get_edge_wcont(cls, tran: Transition, cont_reg: str, tmp_reg0: str, arg_lm_addr_reg: str, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_get_edge.getLabel(), cont_reg=cont_reg, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=4)

    @classmethod
    def _append_neighbors(cls, state: State):
        """
        X8 - PGA_DESC_LM_OFFSET [0:31] | TMP_BUF_LM_OFFSET [32:63]
        X9 - VID
        X10~X15 - NB_VID
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._append_neighbors.__name__

        OB_PGA_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET = "X8"
        OB_VID = "X9"
        OB_NB_VID = "X10"

        REG_PGA_DESC_LM_ADDR = "X16"
        REG_TMP_BUF_LM_ADDR = "X17"

        REG_TMP0 = "X18"
        REG_TMP1 = "X19"

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_append_neighbors
        if tran is None:
            return
        cls.tran_label_append_neighbors = tran.getLabel()

        """==================== TRAN - entry ===================="""
        # calculate lm addr
        tran.writeAction(f"lshift {OB_PGA_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET} {REG_PGA_DESC_LM_ADDR} {32}")
        tran.writeAction(f"rshift {REG_PGA_DESC_LM_ADDR} {REG_PGA_DESC_LM_ADDR} {32}")
        tran.writeAction(f"rshift {OB_PGA_DESC_LM_OFFSET__TMP_BUF_LM_OFFSET} {REG_TMP_BUF_LM_ADDR} {32}")

        tran.writeAction(f"addi {REG_PGA_DESC_LM_ADDR} {REG_TMP0} {cls.PGA_DESC_OFF_NEIGHBOR_LIST_STORE_SHT_DESC_0}")  # calc the first operand for the call, last sht is the smallest
        tran.writeAction(f"add {REG_PGA_DESC_LM_ADDR} {'X7'} {REG_PGA_DESC_LM_ADDR}")
        tran.writeAction(f"move {cls.PGA_DESC_OFF_NUM_NEIGHBOR_LIST_STORE_SHT}({REG_PGA_DESC_LM_ADDR}) {REG_TMP1} 0 8")
        tran.writeAction(f"subi {REG_TMP1} {REG_TMP1} {1}")
        tran.writeAction(f"muli {REG_TMP1} {REG_TMP1} {cls.SHT_DESC_SIZE}")  # TODO: if 4 words, then may use shift instead
        tran.writeAction(f"add {REG_TMP0} {REG_TMP1} {REG_TMP0}")

        tran.writeAction(f"lshift_or {REG_TMP_BUF_LM_ADDR} {REG_TMP0} {32}")  # calc the first operand for the call
        tran.writeAction(f"add {REG_TMP_BUF_LM_ADDR} {'X7'} {REG_TMP_BUF_LM_ADDR}")
        tran.writeAction(f"move {REG_TMP0} {0}({REG_TMP_BUF_LM_ADDR}) 0 8")  # fill in the first operand for the call

        # extract number of value operands
        tran.writeAction(f"rshift_and_imm {'X2'} {REG_TMP0} {20} {0b111}")
        tran.writeAction(f"addi {REG_TMP0} {REG_TMP0} {1}")  # add for the vid operand
        tran.writeAction(f"addi {REG_TMP_BUF_LM_ADDR} {REG_TMP1} {cls.WORD_SIZE}")
        tran.writeAction(f"bcopy_ops {OB_VID} {REG_TMP1} {REG_TMP0}")

        # calling with the proper number of operands
        for i in range(3, 9):
            tran.writeAction(f"beqi {REG_TMP0} {i - 1} {f'{CLS_NAME}-{FN_NAME}-TR-LB-match_send_val_{i}'}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: shouldn't reach here!' {'X0'}")
        for i in range(3, 9):
            tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-match_send_val_{i}'}: addi {REG_TMP0} {REG_TMP0} {0}")  # FIXME: dummy
            SHTExt.ext_graph_append_wcont(tran=tran, ret='X1', tmp_reg0=REG_TMP1, arg_lm_addr_reg=REG_TMP_BUF_LM_ADDR, num_val_words=(i - 2))  # call
            if cls.DEBUG:
                tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] {FN_NAME.upper()}: calling with {i} neighbor VIDs.' {'X0'}")
            tran.writeAction("yield_terminate")

    @classmethod
    def append_neighbors(cls, tran: Transition, ret_tran_label: int, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, num_val_words: int, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_append_neighbors.getLabel(), ret_tran_label=ret_tran_label, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=(2 + num_val_words))

    @classmethod
    def append_neighbors_wcont(cls, tran: Transition, cont_reg: str, tmp_reg0: str, arg_lm_addr_reg: str, num_val_words: int, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_append_neighbors.getLabel(), cont_reg=cont_reg, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=(2 + num_val_words))

    @classmethod
    def _get_neighbors(cls, state: State):
        """
        X8 - PGA_DESC_LM_OFFSET [0:31]
        X8 - VID
        X9 - OFFSET
        returns (VID, NUM_NB, NB_VID, NB_VID...)
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._get_neighbors.__name__

        OB_PGA_DESC_LM_OFFSET = "X8"
        OB_VID = "X9"
        OB_OFFSET = "X10"

        REG_TMP0 = "X16"
        REG_TMP1 = "X17"

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_get_neighbors
        if tran is None:
            return
        cls.tran_label_get_neighbors = tran.getLabel()

        """==================== TRAN - entry ===================="""
        tran.writeAction(f"addi {OB_PGA_DESC_LM_OFFSET} {REG_TMP0} {cls.PGA_DESC_OFF_NEIGHBOR_LIST_STORE_SHT_DESC_0}")  # calc the offset for the last, last sht is the smallest
        tran.writeAction(f"add {OB_PGA_DESC_LM_OFFSET} {'X7'} {REG_TMP1}")
        tran.writeAction(f"move {cls.PGA_DESC_OFF_NUM_NEIGHBOR_LIST_STORE_SHT}({REG_TMP1}) {REG_TMP1} 0 8")
        tran.writeAction(f"subi {REG_TMP1} {REG_TMP1} {1}")
        tran.writeAction(f"muli {REG_TMP1} {REG_TMP1} {cls.SHT_DESC_SIZE}")  # TODO: if 4 words, then may use shift instead
        tran.writeAction(f"add {REG_TMP0} {REG_TMP1} {REG_TMP0}")
        SHTExt.ext_graph_get_with_offset_wcont(tran=tran, ret='X1', tmp_reg=REG_TMP1, desc_lm_offset_reg=REG_TMP0, key_reg=OB_VID, offset_reg=OB_OFFSET)
        tran.writeAction("yield_terminate")

    @classmethod
    def get_neighbors(cls, tran: Transition, ret_tran_label: int, tmp_reg0: str, tmp_reg1: str, desc_lm_offset_reg: str, vid_reg: str, offset_reg: str, dst_nwid_reg: str = 'X0'):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_get_neighbors.getLabel(), ret_tran_label=ret_tran_label, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=desc_lm_offset_reg, arg_reg1=vid_reg, arg_reg2=offset_reg)

    @classmethod
    def get_neighbors_wcont(cls, tran: Transition, cont_reg: str, tmp_reg: str, desc_lm_offset_reg: str, vid_reg: str, offset_reg: str, dst_nwid_reg: str = 'X0'):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_get_neighbors.getLabel(), cont_reg=cont_reg, tmp_reg=tmp_reg, arg_reg0=desc_lm_offset_reg, arg_reg1=vid_reg, arg_reg2=offset_reg)

    # @classmethod
    # def _iter_vertices(cls, state: State):
    #     """
    #     iter
    #     sht nwid-bucket order
    #     returns vid
    #     """
    #     pass

    # @classmethod
    # def _do_iter_vertices(cls, state: State):
    #     """
    #     intf to udkvmsr
    #     """
    #     pass

    # @classmethod
    # def _iter_neighbors(cls, state: State):
    #     """
    #     iter (vid, offset)
    #     returns (vid, nb, nb, nb...)
    #     """
    #     pass

    # @classmethod
    # def _do_iter_neighbors(cls, state: State):
    #     """
    #     intf to udkvmsr
    #     """
    #     pass

    # @classmethod
    # def _iter_edges(cls, state: State):
    #     """
    #     iter
    #     retrurns (src_vid, dst_vid)
    #     """
    #     pass

    # @classmethod
    # def _do_iter_edges(cls, state: State):
    #     """
    #     intf to udkvmsr
    #     """
    #     pass
