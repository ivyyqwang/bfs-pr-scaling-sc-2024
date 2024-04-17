from EFA_v2 import EFA, State, Transition
import sht_macros
from hashtable import HashTable

class SHT:
    """
    struct SHT_DESC {
        WORD START_NWID;
        WORD NUM_ALLOC_LANES;
        WORD BUCKET_DESC_LM_ADDR;
        WORD DRAM_ALLOC_ADDR;
        WORD ENTRY_SIZE;
        WORD ENTRIES_PER_BUCKET;
    }
    """

    DESC_SIZE = 6 * 8

    DESC_STURCT_OFF_START_NWID = 0
    DESC_STURCT_OFF_NUM_ALLOC_LANES = 8
    DESC_STURCT_OFF_BUCKET_DESC_LM_ADDR = 16
    DESC_STURCT_OFF_DRAM_ALLOC_ADDR = 24
    DESC_STURCT_OFF_ENTRY_SIZE = 32
    DESC_STURCT_OFF_ENTRIES_PER_BUCKET = 40

    LANES_PER_UD = 64
    LANES_MASK = LANES_PER_UD - 1

    WORD_SIZE = 8
    KEY_SIZE = 8

    @classmethod
    def setup(cls, state: State, debug=False) -> None:
        cls.DEBUG = debug

        # TODO: code injection
        HashTable.setup(state, debug=debug)
        cls._initialize(state)
        cls._finalize(state)
        # cls._add(state)
        # cls._get(state)
        # cls._delete(state)

    @classmethod
    def _initialize(cls, state: State):
        """
        X8  - SHT_DESC_LM_ADDR
        X9  - TMP_BUF_LM_ADDR
        X10 - START_NWID
        X11 - NUM_ALLOC_LANES
        X12 - BUCKET_DESC_LM_ADDR
        X13 - DRAM_ALLOC_ADDR
        X14 - ENTRY_SIZE (includes word size key)
        X15 - ENTRIES_PER_BUCKET
        """
        OB_SHT_DESC_LM_ADDR           = 'X8'
        OB_TMP_BUF_LM_ADDR            = 'X9'

        OB_START_NWID                 = 'X10'
        OB_NUM_ALLOC_LANES            = 'X11'
        OB_BUCKET_DESC_LM_ADDR        = 'X12'
        OB_DRAM_ALLOC_ADDR            = 'X13'
        OB_ENTRY_SIZE                 = 'X14'
        OB_ENTRIES_PER_BUCKET         = 'X15'

        NUM_OPS = 8

        REG_TMP0 = "X16"
        REG_TMP1 = "X17"
        REG_TMP2 = "X18"
        REG_TMP3 = "X19"
        REG_TMP4 = "X20"
        REG_TMP5 = "X21"
        REG_TMP6 = "X22"
        REG_TMP7 = "X23"
        REG_TMP8 = "X24"

        REG_CONT = "X31"

        tran = state.writeTransition("eventCarry", state, state, "SHT-init-TR")
        if tran is None:
            return
        tran_lane_init_ret = state.writeTransition("eventCarry", state, state, "SHT-init-TR-lane_init_ret")
        cls.tran_label_init = tran.getLabel()

        # TRAN - entry
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][SHT] INIT' {'X0'}")
        # Save continuation
        tran.writeAction(f"mov_reg2reg {'X1'} {REG_CONT}")

        # Copy OB and set descriptor
        tran.writeAction(f"mov_imm2reg {REG_TMP0} {NUM_OPS - 2}")
        tran.writeAction(f"bcopy_ops {OB_START_NWID} {OB_SHT_DESC_LM_ADDR} {REG_TMP0}")

        # Initalize allocated lanes
        # TODO: use UDKVMSR?
        # tmp0 -> current nwid
        tran.writeAction(f"mov_reg2reg {OB_START_NWID} {REG_TMP0}")
        # tmp1 -> end nwid
        tran.writeAction(f"add {OB_START_NWID} {OB_NUM_ALLOC_LANES} {REG_TMP1}")
        # tmp2 -> current bucket desc lm addr
        tran.writeAction(f"mov_reg2reg {OB_BUCKET_DESC_LM_ADDR} {REG_TMP2}")
        tran.writeAction(f"andi {REG_TMP0} {REG_TMP4} {cls.LANES_MASK}")
        tran.writeAction(f"muli {REG_TMP4} {REG_TMP7} {HashTable.DESC_SIZE}")
        tran.writeAction(f"add {REG_TMP2} {REG_TMP7} {REG_TMP2}")
        # tmp3 -> tmp buffer start lm addr
        tran.writeAction(f"mov_imm2reg {REG_TMP3} {cls.LANES_PER_UD}")
        tran.writeAction(f"muli {REG_TMP3} {REG_TMP3} {HashTable.DESC_SIZE}")
        tran.writeAction(f"add {REG_TMP3} {REG_TMP2} {REG_TMP3}")
        # tmp4 -> current tmp buffer lm addr
        tran.writeAction(f"muli {REG_TMP4} {REG_TMP4} {HashTable.LM_BUF_SIZE}")
        tran.writeAction(f"add {REG_TMP3} {REG_TMP4} {REG_TMP4}")
        # tmp5 -> dram alloc size per bucket
        tran.writeAction(f"mul {OB_ENTRY_SIZE} {OB_ENTRIES_PER_BUCKET} {REG_TMP5}")
        # tmp6 -> dram addr for current bucket
        tran.writeAction(f"mov_reg2reg {OB_DRAM_ALLOC_ADDR} {REG_TMP6}")

        # Prepare call args
        tran.writeAction(f"{'SHT-init-TR-LB-lane_init_next'}: mov_reg2reg {OB_TMP_BUF_LM_ADDR} {REG_TMP7}")
        tran.writeAction(f"move {REG_TMP2} {0}({REG_TMP7}) 1 8")  # desc_lm_addr
        tran.writeAction(f"move {REG_TMP6} {0}({REG_TMP7}) 1 8")  # dram_alloc_start_addr
        tran.writeAction(f"move {OB_ENTRY_SIZE} {0}({REG_TMP7}) 1 8")  # entry size
        tran.writeAction(f"move {OB_ENTRIES_PER_BUCKET} {0}({REG_TMP7}) 1 8")  # num_entries
        tran.writeAction(f"move {REG_TMP4} {0}({REG_TMP7}) 1 8")  # lm_buf_addr
        # Call
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][SHT] INIT: dst nwid = %d' {'X0'} {REG_TMP0}")
        HashTable.initialize(tran, tran_lane_init_ret.getLabel(), REG_TMP7, REG_TMP8, OB_TMP_BUF_LM_ADDR, dst_nwid_reg=REG_TMP0)
        # Prepare for the next call
        tran.writeAction(f"addi {REG_TMP0} {REG_TMP0} {1}")
        tran.writeAction(f"add {REG_TMP6} {REG_TMP5} {REG_TMP6}")
        # check if it is in the next updown, if masked output is 0, reset lm addr
        tran.writeAction(f"andi {REG_TMP0} {REG_TMP7} {cls.LANES_MASK}")
        tran.writeAction(f"bnec {REG_TMP7} {0} {'SHT-init-TR-LB-lane_init_not_new_ud'}")
        # reset counters
        tran.writeAction(f"mov_reg2reg {OB_BUCKET_DESC_LM_ADDR} {REG_TMP2}")
        tran.writeAction(f"mov_reg2reg {REG_TMP3} {REG_TMP4}")
        tran.writeAction(f"jmp {'SHT-init-TR-LB-lane_init_next_loop_check'}")
        # increment counters
        tran.writeAction(f"{'SHT-init-TR-LB-lane_init_not_new_ud'}: addi {REG_TMP2} {REG_TMP2} {HashTable.DESC_SIZE}")
        tran.writeAction(f"addi {REG_TMP4} {REG_TMP4} {HashTable.LM_BUF_SIZE}")
        tran.writeAction(f"{'SHT-init-TR-LB-lane_init_next_loop_check'}: blt {REG_TMP0} {REG_TMP1} {'SHT-init-TR-LB-lane_init_next'}")
        # init barrier counter
        tran.writeAction(f"mov_reg2reg {OB_NUM_ALLOC_LANES} {REG_TMP7}")
        tran.writeAction("yield")

        # TRAN - return barrier
        tran_lane_init_ret.writeAction(f"subi {REG_TMP7} {REG_TMP7} {1}")
        tran_lane_init_ret.writeAction(f"bnec {REG_TMP7} {0} {'SHT-init-TR-lane_init_ret-LB-yield'}")
        sht_macros.return_wreg(tran_lane_init_ret, REG_CONT, REG_TMP7, 'X0', 'X0')
        tran_lane_init_ret.writeAction("yield_terminate")
        tran_lane_init_ret.writeAction(f"{'SHT-init-TR-lane_init_ret-LB-yield'}: yield")

    @classmethod
    def initialize(cls, tran: Transition, ret_tran_label: int, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_label_init, ret_tran_label=ret_tran_label, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_len=(8 * 8))

    @classmethod
    def _finalize(cls, state: State) -> None:
        """
        """
        tran = state.writeTransition("eventCarry", state, state, "SHT-init-TR")
        if tran is None:
            return
        REG_TMP0 = 'X16'
        sht_macros.return_wreg(tran, 'X1', REG_TMP0, 'X0', 'X0')
        tran.writeAction("yield_terminate")

    @classmethod
    def finalize(cls, tran: Transition, ret_tran_label: int, tmp_reg0: str, tmp_reg1: str, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_label_init, ret_tran_label=ret_tran_label, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0='X0', arg_reg1='X0')

    @classmethod
    def add(cls, tran: Transition, ret_tran_label: int, tmp_reg0: str, tmp_reg1: str, tmp_reg2: str, arg_lm_addr_reg: str, arg_lm_len: int) -> None:
        """
        Macro
        """
        # hash the destination lane id
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][SHT] ADD' {'X0'}")
        tran.writeAction(f"move {cls.WORD_SIZE}({arg_lm_addr_reg}) {tmp_reg0} 0 8")  # tmp0 -> key
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][SHT] ADD: key = %d' {'X0'} {tmp_reg0}")
        tran.writeAction(f"mov_imm2reg {tmp_reg1} {0}")  # tmp1 -> seed
        tran.writeAction(f"hash {tmp_reg0} {tmp_reg1}")  # tmp1 -> hash
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][SHT] ADD: hash = %d' {'X0'} {tmp_reg1}")
        # calc dest lane
        tran.writeAction(f"move {0}({arg_lm_addr_reg}) {tmp_reg0} 0 8")  # tmp0 ->  sht lm desc addr
        tran.writeAction(f"move {cls.DESC_STURCT_OFF_NUM_ALLOC_LANES}({tmp_reg0}) {tmp_reg2} 0 8")  # tmp2 -> num lane
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][SHT] ADD: num lane = %d' {'X0'} {tmp_reg2}")
        tran.writeAction(f"subi {tmp_reg2} {tmp_reg2} {1}")  # tmp2 -> lane mask
        tran.writeAction(f"andr {tmp_reg1} {tmp_reg2} {tmp_reg1}")  # tmp1 -> lane offset
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][SHT] ADD: lane offset = %d' {'X0'} {tmp_reg1}")
        tran.writeAction(f"move {cls.DESC_STURCT_OFF_START_NWID}({tmp_reg0}) {tmp_reg2} 0 8")  # tmp2 -> load start nwid
        tran.writeAction(f"add {tmp_reg2} {tmp_reg1} {tmp_reg1}")  # tmp1 -> dest nwid
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][SHT] ADD: dst nwid = %d' {'X0'} {tmp_reg1}")
        tran.writeAction(f"move {cls.DESC_STURCT_OFF_BUCKET_DESC_LM_ADDR}({tmp_reg0}) {tmp_reg2} 0 8")  # tmp2 -> bucket desc lm addr base
        tran.writeAction(f"andi {tmp_reg1} {tmp_reg0} {cls.LANES_MASK}")  # tmp0 -> lane offset in ud
        tran.writeAction(f"muli {tmp_reg0} {tmp_reg0} {HashTable.DESC_SIZE}")
        tran.writeAction(f"add {tmp_reg0} {tmp_reg2} {tmp_reg0}")  # tmp0 -> bucket desc lm addr
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][SHT] ADD: bucket desc lm addr = %d' {'X0'} {tmp_reg0}")
        tran.writeAction(f"move {tmp_reg0} {0}({arg_lm_addr_reg}) 0 8")
        # TODO: should we be able to use send size stored previously?
        HashTable.add(tran, ret_tran_label, tmp_reg0, tmp_reg2, arg_lm_addr_reg, arg_lm_len, tmp_reg1)

    @classmethod
    def get(cls, tran: Transition, ret_tran_label: int, tmp_reg0: str, tmp_reg1: str, tmp_reg2: str, tmp_reg3: str, desc_lm_addr_reg: str, key_reg: str):
        """
        Macro
        """
        # hash the destination lane id
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][SHT] GET: key = %d' {'X0'} {key_reg}")
        tran.writeAction(f"mov_imm2reg {tmp_reg0} {0}")  # tmp0 -> seed
        tran.writeAction(f"hash {key_reg} {tmp_reg0}")  # tmp0 -> hash
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][SHT] GET: hash = %d' {'X0'} {tmp_reg0}")
        tran.writeAction(f"move {cls.DESC_STURCT_OFF_NUM_ALLOC_LANES}({desc_lm_addr_reg}) {tmp_reg1} 0 8")  # tmp1 -> num lane
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][SHT] GET: num lane = %d' {'X0'} {tmp_reg1}")
        tran.writeAction(f"subi {tmp_reg1} {tmp_reg1} {1}")  # tmp1 -> lane mask
        tran.writeAction(f"andr {tmp_reg0} {tmp_reg1} {tmp_reg0}")  # tmp0 -> lane offset
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][SHT] GET: lane offset = %d' {'X0'} {tmp_reg0}")
        tran.writeAction(f"move {cls.DESC_STURCT_OFF_START_NWID}({desc_lm_addr_reg}) {tmp_reg1} 0 8")  # tmp1 -> load start nwid
        tran.writeAction(f"add {tmp_reg1} {tmp_reg0} {tmp_reg0}")  # tmp0 -> dest nwid
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][SHT] GET: dst nwid = %d' {'X0'} {tmp_reg0}")
        tran.writeAction(f"andi {tmp_reg0} {tmp_reg1} {cls.LANES_MASK}")  # tmp1 -> lane offset in ud
        tran.writeAction(f"muli {tmp_reg1} {tmp_reg1} {HashTable.DESC_SIZE}")
        tran.writeAction(f"move {cls.DESC_STURCT_OFF_BUCKET_DESC_LM_ADDR}({desc_lm_addr_reg}) {tmp_reg2} 0 8")  # tmp2 -> bucket desc lm addr base
        tran.writeAction(f"add {tmp_reg1} {tmp_reg2} {tmp_reg1}")  # tmp1 -> bucket desc lm addr
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][SHT] GET: bucket desc lm addr = %d' {'X0'} {tmp_reg1}")
        HashTable.get(tran, ret_tran_label, tmp_reg2, tmp_reg3, tmp_reg1, key_reg, tmp_reg0)

