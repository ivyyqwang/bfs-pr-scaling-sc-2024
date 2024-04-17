from EFA_v2 import EFA, State, Transition
import sht_macros
from memzero import Memzero
import math


class HashTable:
    """
    struct HashTableDesc {
        WORD lock;
        WORD dram_alloc_start_addr;
        WORD entry_size;
        WORD alloc_entries;
        WORD entry_count;
        WORD lm_buf_addr;
    }

    start dram address
    dram allocation size
    struct Entry {
        WORD key;
        WORD val;
    }
    entry size
    """

    DESC_SIZE = 6 * 8

    DESC_STURCT_OFF_LOCK = 0
    DESC_STURCT_OFF_DRAM_ALLOC_START_ADDR = 8
    DESC_STURCT_OFF_ENTRY_SIZE = 16
    DESC_STURCT_OFF_NUM_ALLOC_ENTRIES = 24
    DESC_STURCT_OFF_ENTRY_COUNT = 32
    DESC_STURCT_OFF_LM_BUF_ADDR = 40

    WORD_SIZE = 8
    KEY_SIZE = 8

    LM_BUF_SIZE = 64

    @classmethod
    def setup(cls, state: State, debug=False) -> None:
        cls.DEBUG = debug
        cls.lock = sht_macros.MRSWLock(atomic=False, debug=debug)

        # TODO: code injection
        Memzero.setup(state, debug=debug)
        cls._initialize(state)
        cls._add(state)
        cls._get(state)
        cls._delete(state)

    @classmethod
    def _hash(cls, tran: Transition, seed_reg: str, key_reg: str, num_entries_reg: str) -> None:
        """
        MACRO
        key_reg overwritten as the masked val
        num_entrires has to be 2^N for now
        """
        tran.writeAction(f"subi {num_entries_reg} {num_entries_reg} {1}")
        tran.writeAction(f"hash {seed_reg} {key_reg}")
        tran.writeAction(f"andr {key_reg} {num_entries_reg} {key_reg}")

    @classmethod
    def _calc_entry_addr(cls, tran: Transition, desc_lm_addr_reg, key_reg, tmp_reg0, tmp_reg1, out_entry_addr_reg) -> None:
        # hash key
        tran.writeAction(f"move {cls.DESC_STURCT_OFF_NUM_ALLOC_ENTRIES}({desc_lm_addr_reg}) {out_entry_addr_reg} 0 8")  # out => alloc entries
        tran.writeAction(f"mov_reg2reg {key_reg} {tmp_reg0}")  # tmp0 => key
        tran.writeAction(f"mov_imm2reg {tmp_reg1} {0}")  # tmp1 => seed
        cls._hash(tran, tmp_reg1, tmp_reg0, out_entry_addr_reg)  # tmp0 => entry index
        # calculate addr
        tran.writeAction(f"move {cls.DESC_STURCT_OFF_DRAM_ALLOC_START_ADDR}({desc_lm_addr_reg}) {out_entry_addr_reg} 0 8")  # out => dram_alloc_start_addr
        tran.writeAction(f"move {cls.DESC_STURCT_OFF_ENTRY_SIZE}({desc_lm_addr_reg}) {tmp_reg1} 0 8")  # tmp1 => entry size
        tran.writeAction(f"mul {tmp_reg0} {tmp_reg1} {tmp_reg1}")  # tmp1 => addr offset
        tran.writeAction(f"add {out_entry_addr_reg} {tmp_reg1} {out_entry_addr_reg}")  # out => entry addr

    @classmethod
    def _initialize(cls, state: State):
        """
        X8 - desc_lm_addr
        X9 - dram_alloc_start_addr
        X10 - entry_size (includes word size key)
        X11 - num_entries
        X12 - lm_buf_addr
        """
        OB_DESC_LM_ADDR = "X8"
        OB_DRAM_ALLOC_START_ADDR = "X9"
        OB_ENTRY_SIZE = "X10"
        OB_ALLOC_ENTRIES = "X11"
        OB_LM_BUF_ADDR = "X12"

        REG_TMP0 = "X16"
        REG_TMP1 = "X17"
        REG_CONT = "X18"

        tran = state.writeTransition("eventCarry", state, state, "HT-init-TR")
        if tran is None:
            return
        cls.tran_label_init = tran.getLabel()
        tran_memzero_done = state.writeTransition("eventCarry", state, state, "HT-init-TR-memzero_done")

        # TRAN - init entry
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{cls.__name__}] INIT: start' {'X0'}")
        # save cont
        tran.writeAction(f"mov_reg2reg {'X1'} {REG_CONT}")
        # init lock
        tran.writeAction(f"addi {OB_DESC_LM_ADDR} {REG_TMP0} {cls.DESC_STURCT_OFF_LOCK}")
        cls.lock.init(tran, REG_TMP0, REG_TMP1)
        # set descriptor
        # TODO: could be replaced by bcopy_ops
        # dram alloc start addr
        tran.writeAction(f"move {OB_DRAM_ALLOC_START_ADDR} {cls.DESC_STURCT_OFF_DRAM_ALLOC_START_ADDR}({OB_DESC_LM_ADDR}) 0 8")
        # entry size
        tran.writeAction(f"move {OB_ENTRY_SIZE} {cls.DESC_STURCT_OFF_ENTRY_SIZE}({OB_DESC_LM_ADDR}) 0 8")
        # alloc entries
        tran.writeAction(f"move {OB_ALLOC_ENTRIES} {cls.DESC_STURCT_OFF_NUM_ALLOC_ENTRIES}({OB_DESC_LM_ADDR}) 0 8")
        # lm buf addr
        tran.writeAction(f"move {OB_LM_BUF_ADDR} {cls.DESC_STURCT_OFF_LM_BUF_ADDR}({OB_DESC_LM_ADDR}) 0 8")
        # entry count
        tran.writeAction(f"mov_imm2reg {REG_TMP1} {0}")
        tran.writeAction(f"move {REG_TMP1} {cls.DESC_STURCT_OFF_ENTRY_COUNT}({OB_DESC_LM_ADDR}) 0 8")

        # zero out memory
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{cls.__name__}] INIT: zeroing memory...' {'X0'}")
        tran.writeAction(f"mul {OB_ALLOC_ENTRIES} {OB_ENTRY_SIZE} {REG_TMP0}")
        tran.writeAction(f"mov_reg2reg {OB_LM_BUF_ADDR} {REG_TMP1}")
        tran.writeAction(f"move {OB_DRAM_ALLOC_START_ADDR} {0}({REG_TMP1}) 1 8")
        tran.writeAction(f"move {REG_TMP0} {0}({REG_TMP1}) 1 8")
        tran.writeAction(f"move {OB_LM_BUF_ADDR} {0}({REG_TMP1}) 1 8")
        Memzero.memzero(tran, tran_memzero_done.getLabel(), REG_TMP0, REG_TMP1, OB_LM_BUF_ADDR)
        tran.writeAction("yield")

        # TRAN - memzero done
        # return
        sht_macros.return_wreg(tran_memzero_done, REG_CONT, REG_TMP0, "X0", "X0")
        if cls.DEBUG:
            tran_memzero_done.writeAction(f"print '[DEBUG][NWID %d][{cls.__name__}] INIT: done' {'X0'}")
        tran_memzero_done.writeAction("yield_terminate")

    @classmethod
    def initialize(cls, tran: Transition, ret_tran_label: int, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_label_init, ret_tran_label=ret_tran_label, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_len=(5 * 8))

    @classmethod
    def _add(cls, state: State):
        """
        X8 - desc_lm_addr
        X9 - key
        X10 - Elem *e
        """
        OB_DESC_LM_ADDR = "X8"
        OB_KEY = "X9"
        OB_VAL = "X10"

        REG_LOCK_LM_ADDR = "X16"
        REG_TMP1 = "X17"
        REG_TMP2 = "X18"
        REG_TMP3 = "X19"
        REG_TMP4 = "X20"
        REG_TMP5 = "X24"

        REG_DESC_LM_ADDR = "X21"
        REG_BUF_LM_ADDR = "X22"
        REG_KEY = "X23"

        REG_CONT = "X31"

        tran = state.writeTransition("eventCarry", state, state, "HT-add-TR")
        if tran is None:
            return
        cls.tran_label_add = tran.getLabel()
        tran_key_ld_ret = state.writeTransition("eventCarry", state, state, "HT-add-TR-key_ld_ret")
        tran_key_st_ret = state.writeTransition("eventCarry", state, state, "HT-add-TR-key_st_ret")

        # TRAN - function entry
        # get lock
        tran.writeAction(f"addi {OB_DESC_LM_ADDR} {REG_LOCK_LM_ADDR} {cls.DESC_STURCT_OFF_LOCK}")
        cls.lock.write_begin(tran, REG_LOCK_LM_ADDR, REG_TMP1, 3)  # TODO: FIX: currently hard coding 3 words in ob, to use buffer and bcopy
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{cls.__name__}] ADD: lock admitted' {'X0'}")

        # copy ob regs
        tran.writeAction(f"mov_reg2reg {OB_KEY} {REG_KEY}")
        tran.writeAction(f"mov_reg2reg {OB_DESC_LM_ADDR} {REG_DESC_LM_ADDR}")
        # copy entry to lm buffer (key + val)
        tran.writeAction(f"move {cls.DESC_STURCT_OFF_LM_BUF_ADDR}({REG_DESC_LM_ADDR}) {REG_BUF_LM_ADDR} 0 8")
        tran.writeAction(f"move {cls.DESC_STURCT_OFF_ENTRY_SIZE}({REG_DESC_LM_ADDR}) {REG_TMP2} 0 8")  # tmp2 => entry size
        tran.writeAction(f"rshift {REG_TMP2} {REG_TMP1} {int(math.log2(cls.WORD_SIZE))}")
        tran.writeAction(f"bcopy_ops {OB_KEY} {REG_BUF_LM_ADDR} {REG_TMP1}")

        # save cont
        tran.writeAction(f"mov_reg2reg {'X1'} {REG_CONT}")

        # calc entry addr
        cls._calc_entry_addr(tran, OB_DESC_LM_ADDR, OB_KEY, REG_TMP1, REG_TMP4, REG_TMP3)  # tmp3 => entry addr, tmp1 => entry index

        # read key
        tran.writeAction(f"send_dmlm_ld_wret {REG_TMP3} {tran_key_ld_ret.getLabel()} {cls.KEY_SIZE} {REG_TMP5}")
        tran.writeAction(f"move {cls.DESC_STURCT_OFF_NUM_ALLOC_ENTRIES}({OB_DESC_LM_ADDR}) {REG_TMP4} 0 8")  # tmp4 => num alloc entries
        tran.writeAction("yield")

        # TRAN - load key return
        OB_LD_KEY = "X8"
        # check if the entry occupied, insert if not
        tran_key_ld_ret.writeAction(f"beqc {OB_LD_KEY} {0} {'HT-add-TR-key_ld_ret-LB-empty'}")
        # check if the entry is the same as the argument, overwrite if so
        tran_key_ld_ret.writeAction(f"beq {OB_LD_KEY} {REG_KEY} {'HT-add-TR-key_ld_ret-LB-empty'}")

        # linear probing
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{cls.__name__}] ADD: collision, linear probing...' {'X0'}")
        tran_key_ld_ret.writeAction(f"addi {REG_TMP1} {REG_TMP1} {1}")  # tmp1 (cur entry index) += 1
        tran_key_ld_ret.writeAction(f"beq {REG_TMP1} {REG_TMP4} {'HT-add-TR-key_ld_ret-LB-oob'}")  # out of bound
        tran_key_ld_ret.writeAction(f"add {REG_TMP3} {REG_TMP2} {REG_TMP3}")  # tmp3 (cur entry addr) += tmp2 (entry size)
        tran_key_ld_ret.writeAction(f"send_dmlm_ld_wret {REG_TMP3} {tran_key_ld_ret.getLabel()} {cls.KEY_SIZE} {REG_TMP5}")
        tran_key_ld_ret.writeAction("yield")

        # => out of bound, return failure
        tran_key_ld_ret.writeAction(f"{'HT-add-TR-key_ld_ret-LB-oob'}: mov_imm2reg {REG_TMP4} {0}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{cls.__name__}] ADD: linear probe out of bound!! ERROR' {'X0'}")
        # unlock
        cls.lock.write_end(tran_key_ld_ret, REG_LOCK_LM_ADDR, REG_TMP1)
        # return
        tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_TMP4} {1}")
        sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, REG_TMP1, REG_TMP4, REG_TMP4)
        tran_key_ld_ret.writeAction("yield_terminate")

        # => found empty spot, write to the location
        # switch cases for various word size entry
        tran_key_ld_ret.writeAction(f"{'HT-add-TR-key_ld_ret-LB-empty'}: bgtc {REG_TMP2} {cls.WORD_SIZE * 2} {'HT-add-TR-key_ld_ret-LB-write_gt16'}")
        tran_key_ld_ret.writeAction(f"send_dmlm_wret {REG_TMP3} {tran_key_st_ret.getLabel()} {REG_BUF_LM_ADDR} {'16'} {REG_TMP5}")
        tran_key_ld_ret.writeAction(f"jmp {'HT-add-TR-key_ld_ret-LB-inc_entry_count'}")
        tran_key_ld_ret.writeAction(f"{'HT-add-TR-key_ld_ret-LB-write_gt16'}: bgtc {REG_TMP2} {cls.WORD_SIZE * 3} {'HT-add-TR-key_ld_ret-LB-write_gt24'}")
        tran_key_ld_ret.writeAction(f"send_dmlm_wret {REG_TMP3} {tran_key_st_ret.getLabel()} {REG_BUF_LM_ADDR} {'24'} {REG_TMP5}")
        tran_key_ld_ret.writeAction(f"jmp {'HT-add-TR-key_ld_ret-LB-inc_entry_count'}")
        tran_key_ld_ret.writeAction(f"{'HT-add-TR-key_ld_ret-LB-write_gt24'}: bgtc {REG_TMP2} {cls.WORD_SIZE * 4} {'HT-add-TR-key_ld_ret-LB-write_gt32'}")
        tran_key_ld_ret.writeAction(f"send_dmlm_wret {REG_TMP3} {tran_key_st_ret.getLabel()} {REG_BUF_LM_ADDR} {'32'} {REG_TMP5}")
        tran_key_ld_ret.writeAction(f"jmp {'HT-add-TR-key_ld_ret-LB-inc_entry_count'}")
        tran_key_ld_ret.writeAction(f"{'HT-add-TR-key_ld_ret-LB-write_gt32'}: bgtc {REG_TMP2} {cls.WORD_SIZE * 5} {'HT-add-TR-key_ld_ret-LB-write_gt40'}")
        tran_key_ld_ret.writeAction(f"send_dmlm_wret {REG_TMP3} {tran_key_st_ret.getLabel()} {REG_BUF_LM_ADDR} {'40'} {REG_TMP5}")
        tran_key_ld_ret.writeAction(f"jmp {'HT-add-TR-key_ld_ret-LB-inc_entry_count'}")
        tran_key_ld_ret.writeAction(f"{'HT-add-TR-key_ld_ret-LB-write_gt40'}: bgtc {REG_TMP2} {cls.WORD_SIZE * 6} {'HT-add-TR-key_ld_ret-LB-write_gt48'}")
        tran_key_ld_ret.writeAction(f"send_dmlm_wret {REG_TMP3} {tran_key_st_ret.getLabel()} {REG_BUF_LM_ADDR} {'48'} {REG_TMP5}")
        tran_key_ld_ret.writeAction(f"jmp {'HT-add-TR-key_ld_ret-LB-inc_entry_count'}")
        tran_key_ld_ret.writeAction(f"{'HT-add-TR-key_ld_ret-LB-write_gt48'}: bgtc {REG_TMP2} {cls.WORD_SIZE * 7} {'HT-add-TR-key_ld_ret-LB-write_gt56'}")
        tran_key_ld_ret.writeAction(f"send_dmlm_wret {REG_TMP3} {tran_key_st_ret.getLabel()} {REG_BUF_LM_ADDR} {'56'} {REG_TMP5}")
        tran_key_ld_ret.writeAction(f"jmp {'HT-add-TR-key_ld_ret-LB-inc_entry_count'}")
        tran_key_ld_ret.writeAction(f"{'HT-add-TR-key_ld_ret-LB-write_gt56'}: send_dmlm_wret {REG_TMP3} {tran_key_st_ret.getLabel()} {REG_BUF_LM_ADDR} {'64'} {REG_TMP5}")

        # increment entry count
        tran_key_ld_ret.writeAction(f"{'HT-add-TR-key_ld_ret-LB-inc_entry_count'}: move {cls.DESC_STURCT_OFF_ENTRY_COUNT}({REG_DESC_LM_ADDR}) {REG_TMP4} 0 8")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{cls.__name__}] ADD: writing entry... DRAM_ADDR = 0x%x' {'X0'} {REG_TMP3}")
        tran_key_ld_ret.writeAction(f"addi {REG_TMP4} {REG_TMP4} {1}")
        tran_key_ld_ret.writeAction(f"move {REG_TMP4} {cls.DESC_STURCT_OFF_ENTRY_COUNT}({REG_DESC_LM_ADDR}) 0 8")
        tran_key_ld_ret.writeAction("yield")

        # TRAN - store key val
        # unlock
        cls.lock.write_end(tran_key_st_ret, REG_LOCK_LM_ADDR, REG_TMP1)
        # return success
        tran_key_st_ret.writeAction(f"mov_imm2reg {REG_TMP4} {1}")
        sht_macros.return_wreg(tran_key_st_ret, REG_CONT, REG_TMP1, REG_TMP4, REG_TMP4)
        if cls.DEBUG:
            tran_key_st_ret.writeAction(f"print '[DEBUG][NWID %d][{cls.__name__}] ADD: done' {'X0'}")
        tran_key_st_ret.writeAction("yield_terminate")

    @classmethod
    def add(cls, tran: Transition, ret_tran_label: int, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, arg_lm_len: int, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_label_add, ret_tran_label=ret_tran_label, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_len=arg_lm_len)

    @classmethod
    def _get(cls, state: State):
        """
        X8 - desc_lm_addr
        X9 - key
        """
        OB_DESC_LM_ADDR = "X8"
        OB_KEY = "X9"

        REG_LOCK_LM_ADDR = "X16"
        REG_TMP1 = "X17"
        REG_TMP2 = "X18"
        REG_TMP3 = "X19"
        REG_TMP4 = "X20"

        REG_DESC_LM_ADDR = "X21"
        REG_KEY = "X22"

        REG_CONT = "X23"

        tran = state.writeTransition("eventCarry", state, state, "HT-get-TR")
        if tran is None:
            return
        cls.tran_label_get = tran.getLabel()
        tran_key_ld_ret = state.writeTransition("eventCarry", state, state, "HT-get-TR-key_ld_ret")

        # TRAN - function entry
        # get lock
        tran.writeAction(f"addi {OB_DESC_LM_ADDR} {REG_LOCK_LM_ADDR} {cls.DESC_STURCT_OFF_LOCK}")
        cls.lock.read_begin(tran, REG_LOCK_LM_ADDR, REG_TMP1, 2)  # TODO: FIX: currently hard coding 3 words in ob, to use buffer and bcopy
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{cls.__name__}] GET: lock admitted' {'X0'}")

        # copy ob regs
        tran.writeAction(f"mov_reg2reg {OB_KEY} {REG_KEY}")
        tran.writeAction(f"mov_reg2reg {OB_DESC_LM_ADDR} {REG_DESC_LM_ADDR}")

        # save cont
        tran.writeAction(f"mov_reg2reg {'X1'} {REG_CONT}")

        # calc entry addr
        cls._calc_entry_addr(tran, OB_DESC_LM_ADDR, OB_KEY, REG_TMP1, REG_TMP2, REG_TMP3)  # tmp3 => entry addr, tmp1 => entry index

        # read key
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{cls.__name__}] GET: first read key, DRAM_ADDR = 0x%x' {'X0'} {REG_TMP3}")
        tran.writeAction(f"send_dmlm_ld_wret {REG_TMP3} {tran_key_ld_ret.getLabel()} {64} {REG_TMP5}")
        tran.writeAction(f"move {cls.DESC_STURCT_OFF_ENTRY_SIZE}({OB_DESC_LM_ADDR}) {REG_TMP2} 0 8")  # tmp2 => entry size
        tran.writeAction(f"move {cls.DESC_STURCT_OFF_NUM_ALLOC_ENTRIES}({OB_DESC_LM_ADDR}) {REG_TMP4} 0 8")  # tmp4 => num alloc entries
        tran.writeAction("yield")

        # TRAN - load key return
        # check if the entry match
        # linear probe if not, otherwise return value
        OB_LD_KEY = "X8"
        OB_LD_VAL = "X9"
        tran_key_ld_ret.writeAction(f"beq {OB_LD_KEY} {REG_KEY} {'HT-get-TR-key_ld_ret-LB-match'}")

        tran_key_ld_ret.writeAction(f"beqc {OB_LD_KEY} {0} {'HT-get-TR-key_ld_ret-LB-not_found'}")  # not found if the key is 0
        # linear probe
        tran_key_ld_ret.writeAction(f"addi {REG_TMP1} {REG_TMP1} {1}")  # tmp1 (cur entry index) += 1
        tran_key_ld_ret.writeAction(f"beq {REG_TMP1} {REG_TMP4} {'HT-get-TR-key_ld_ret-LB-not_found'}")  # out of bound
        tran_key_ld_ret.writeAction(f"add {REG_TMP3} {REG_TMP2} {REG_TMP3}")  # tmp3 (cur entry addr) += tmp2 (entry size)
        tran_key_ld_ret.writeAction(f"send_dmlm_ld_wret {REG_TMP3} {tran_key_ld_ret.getLabel()} {64} {REG_TMP5}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{cls.__name__}] GET: linear probing, DRAM_ADDR = 0x%x' {'X0'} {REG_TMP3}")
        tran_key_ld_ret.writeAction("yield")

        # => not found
        tran_key_ld_ret.writeAction(f"{'HT-get-TR-key_ld_ret-LB-not_found'}: mov_imm2reg {REG_TMP4} {-1}")  # indicate invalid return
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{cls.__name__}] GET: key not found' {'X0'}")
        # unlock
        cls.lock.read_end(tran_key_ld_ret, REG_LOCK_LM_ADDR, REG_TMP1)
        # return
        sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, REG_LOCK_LM_ADDR, REG_TMP4, REG_TMP4)
        tran_key_ld_ret.writeAction("yield_terminate")

        # => match
        tran_key_ld_ret.writeAction(f"{'HT-get-TR-key_ld_ret-LB-match'}: mov_imm2reg {REG_TMP4} {1}")  # indicate valid return
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{cls.__name__}] GET: key match' {'X0'}")
        # unlock
        cls.lock.read_end(tran_key_ld_ret, REG_LOCK_LM_ADDR, REG_TMP1)
        # return
        # switch on differnet sizes
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{cls.__name__}] GET: done, val (first word) = %d' {'X0'} {OB_LD_VAL}")
        tran_key_ld_ret.writeAction(f"subi {REG_TMP2} {REG_TMP2} {cls.KEY_SIZE}")  # get val size alone
        tran_key_ld_ret.writeAction(f"rshift {REG_CONT} {REG_TMP1} {32}")  # get nwid from continuation word (may be removed after the isa is revised)
        tran_key_ld_ret.writeAction(f"bgtc {REG_TMP2} {cls.WORD_SIZE} {'HT-get-TR-key_ld_ret-LB-val_gt8'}")
        tran_key_ld_ret.writeAction(f"sendops_wcont {REG_CONT} {REG_TMP1} {REG_TMP1} {OB_LD_VAL} {'8'}")
        tran_key_ld_ret.writeAction(f"yield_terminate")
        tran_key_ld_ret.writeAction(f"{'HT-get-TR-key_ld_ret-LB-val_gt8'}: bgtc {REG_TMP2} {cls.WORD_SIZE * 2} {'HT-get-TR-key_ld_ret-LB-val_gt16'}")
        tran_key_ld_ret.writeAction(f"sendops_wcont {REG_CONT} {REG_TMP1} {REG_TMP1} {OB_LD_VAL} {'16'}")
        tran_key_ld_ret.writeAction(f"yield_terminate")
        tran_key_ld_ret.writeAction(f"{'HT-get-TR-key_ld_ret-LB-val_gt16'}: bgtc {REG_TMP2} {cls.WORD_SIZE * 3} {'HT-get-TR-key_ld_ret-LB-val_gt24'}")
        tran_key_ld_ret.writeAction(f"sendops_wcont {REG_CONT} {REG_TMP1} {REG_TMP1} {OB_LD_VAL} {'24'}")
        tran_key_ld_ret.writeAction(f"yield_terminate")
        tran_key_ld_ret.writeAction(f"{'HT-get-TR-key_ld_ret-LB-val_gt24'}: bgtc {REG_TMP2} {cls.WORD_SIZE * 4} {'HT-get-TR-key_ld_ret-LB-val_gt32'}")
        tran_key_ld_ret.writeAction(f"sendops_wcont {REG_CONT} {REG_TMP1} {REG_TMP1} {OB_LD_VAL} {'32'}")
        tran_key_ld_ret.writeAction(f"yield_terminate")
        tran_key_ld_ret.writeAction(f"{'HT-get-TR-key_ld_ret-LB-val_gt32'}: bgtc {REG_TMP2} {cls.WORD_SIZE * 5} {'HT-get-TR-key_ld_ret-LB-val_gt40'}")
        tran_key_ld_ret.writeAction(f"sendops_wcont {REG_CONT} {REG_TMP1} {REG_TMP1} {OB_LD_VAL} {'40'}")
        tran_key_ld_ret.writeAction(f"yield_terminate")
        tran_key_ld_ret.writeAction(f"{'HT-get-TR-key_ld_ret-LB-val_gt40'}: bgtc {REG_TMP2} {cls.WORD_SIZE * 6} {'HT-get-TR-key_ld_ret-LB-val_gt48'}")
        tran_key_ld_ret.writeAction(f"sendops_wcont {REG_CONT} {REG_TMP1} {REG_TMP1} {OB_LD_VAL} {'48'}")
        tran_key_ld_ret.writeAction(f"yield_terminate")
        tran_key_ld_ret.writeAction(f"{'HT-get-TR-key_ld_ret-LB-val_gt48'}: bgtc {REG_TMP2} {cls.WORD_SIZE * 7} {'HT-get-TR-key_ld_ret-LB-val_gt56'}")
        tran_key_ld_ret.writeAction(f"sendops_wcont {REG_CONT} {REG_TMP1} {REG_TMP1} {OB_LD_VAL} {'56'}")
        tran_key_ld_ret.writeAction(f"yield_terminate")
        tran_key_ld_ret.writeAction(f"{'HT-get-TR-key_ld_ret-LB-val_gt56'}: sendops_wcont {REG_CONT} {REG_TMP1} {REG_TMP1} {OB_LD_VAL} {'64'}")
        tran_key_ld_ret.writeAction(f"yield_terminate")

    @classmethod
    def get(cls, tran: Transition, ret_tran_label: int, tmp_reg0: str, tmp_reg1: str, desc_lm_addr_reg: str, key_reg: str, dst_nwid_reg: str = 'X0'):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_label_get, ret_tran_label=ret_tran_label, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=desc_lm_addr_reg, arg_reg1=key_reg)

    @classmethod
    def _delete(cls, state: State):
        """
        TODO
        """
        pass

    @classmethod
    def delete(cls, tran: Transition):
        """
        TODO
        """
        pass

    @classmethod
    def _get_iter_key(cls):
        """
        TODO
        """
        pass

    @classmethod
    def get_iter_key(cls):
        """
        TODO
        """
        pass

    @classmethod
    def _get_iter_val(cls):
        """
        TODO
        """
        pass

    @classmethod
    def get_iter_val(cls):
        """
        TODO
        """
        pass

