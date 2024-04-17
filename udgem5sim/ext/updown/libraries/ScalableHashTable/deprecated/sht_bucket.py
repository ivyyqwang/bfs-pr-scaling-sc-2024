from EFA_v2 import EFA, State, Transition
import sht_macros
import math


class SHTArrayBucket:
    """
    struct HashTableDesc {
        WORD lock;
        WORD dram_alloc_start_addr;
        WORD alloc_entries;
        WORD entry_count;
        WORD lm_buf_addr;
        WORD num_used_entries;
    }

    struct Entry {
        WORD key;
        WORD val;
    }
    """

    DESC_SIZE = 6 * 8

    DESC_STURCT_OFF_LOCK = 0
    DESC_STURCT_OFF_DRAM_ALLOC_START_ADDR = 8
    DESC_STURCT_OFF_NUM_ALLOC_ENTRIES = 16
    DESC_STURCT_OFF_ENTRY_COUNT = 24
    DESC_STURCT_OFF_LM_BUF_ADDR = 32
    DESC_STURCT_OFF_USED_ENTRY_COUNT = 40

    WORD_SIZE = 8

    INVALID_MARKER = 0
    EMPTY_KEY = 0
    KEY_SIZE = 8
    VAL_SIZE = 8
    ENTRY_SIZE = KEY_SIZE + VAL_SIZE

    LM_BUF_SIZE = 64

    NUM_CONCURRENT_SENDS = 25

    @classmethod
    def setup(cls, state: State, debug=False) -> None:
        cls.DEBUG = debug
        cls.lock = sht_macros.MRSWLock(atomic=False, debug=debug)
        # cls.lock = sht_macros.MRSWLock(atomic=True, debug=debug)  # remove locks for experiemnt

        # TODO: code injection
        cls._initialize(state)
        cls._update(state)
        cls._get(state)
        # cls._delete(state)

    @classmethod
    def _initialize(cls, state: State):
        """
        X8 - desc_lm_offset
        X9 - dram_alloc_start_addr
        X10 - num_entries
        X11 - lm_buf_addr
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._initialize.__name__

        OB_DESC_LM_OFFSET = "X8"
        OB_DRAM_ALLOC_START_ADDR = "X9"
        OB_ALLOC_ENTRIES = "X10"
        OB_LM_BUF_ADDR = "X11"

        REG_DESC_LM_ADDR = "X16"
        REG_TMP0 = "X17"
        REG_TMP1 = "X18"

        tran = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR")
        if tran is None:
            return
        cls.tran_label_init = tran.getLabel()

        # TRAN - init entry
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] INIT: start' {'X0'}")
        # calc desc lm addr
        tran.writeAction(f"add {OB_DESC_LM_OFFSET} {'X7'} {REG_DESC_LM_ADDR}")
        # init lock
        tran.writeAction(f"addi {REG_DESC_LM_ADDR} {REG_TMP0} {cls.DESC_STURCT_OFF_LOCK}")
        cls.lock.init(tran, REG_TMP0, REG_TMP1)
        # set descriptor
        # TODO: could be replaced by bcopy_ops
        # dram alloc start addr
        tran.writeAction(f"move {OB_DRAM_ALLOC_START_ADDR} {cls.DESC_STURCT_OFF_DRAM_ALLOC_START_ADDR}({REG_DESC_LM_ADDR}) 0 8")
        # alloc entries
        tran.writeAction(f"move {OB_ALLOC_ENTRIES} {cls.DESC_STURCT_OFF_NUM_ALLOC_ENTRIES}({REG_DESC_LM_ADDR}) 0 8")
        # lm buf addr
        tran.writeAction(f"move {OB_LM_BUF_ADDR} {cls.DESC_STURCT_OFF_LM_BUF_ADDR}({REG_DESC_LM_ADDR}) 0 8")
        # entry count
        tran.writeAction(f"mov_imm2reg {REG_TMP1} {0}")
        tran.writeAction(f"move {REG_TMP1} {cls.DESC_STURCT_OFF_ENTRY_COUNT}({REG_DESC_LM_ADDR}) 0 8")
        # used entries
        tran.writeAction(f"move {REG_TMP1} {cls.DESC_STURCT_OFF_USED_ENTRY_COUNT}({REG_DESC_LM_ADDR}) 0 8")

        sht_macros.return_wreg(tran, 'X1', "X0", "X0")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] INIT: done' {'X0'}")
        tran.writeAction("yield_terminate")

    @classmethod
    def initialize(cls, tran: Transition, ret: int, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_label_init, ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=4)

    @classmethod
    def initialize_wcont(cls, tran: Transition, ret: str, tmp_reg0: str, arg_lm_addr_reg: str, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_label_init, cont_reg=ret, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=4)

    @classmethod
    def _update(cls, state: State):
        """
        X8 - desc_lm_offset
        X9 - key
        X10 - Elem *e
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._update.__name__

        OB_DESC_LM_OFFSET = "X8"
        OB_KEY = "X9"
        OB_VAL = "X10"

        REG_LOCK_LM_ADDR = "X16"
        REG_TMP1 = "X17"
        REG_TMP2 = "X18"
        REG_TMP3 = "X19"
        REG_TMP4 = "X23"
        REG_CONCURRENCY = "X20"
        REG_ENTRY_WR_ADDR = "X21"
        REG_DONE = "X22"

        REG_DESC_LM_ADDR = "X28"
        REG_KEY = "X29"
        REG_VAL = "X30"

        REG_CONT = "X31"

        tran = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR")
        if tran is None:
            return
        cls.tran_label_update = tran.getLabel()
        tran_key_ld_ret = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-key_ld_ret")
        tran_key_st_ret = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-key_st_ret")

        # TRAN - function entry
        # calc desc lm addr
        tran.writeAction(f"add {OB_DESC_LM_OFFSET} {'X7'} {REG_DESC_LM_ADDR}")
        # get lock
        tran.writeAction(f"addi {REG_DESC_LM_ADDR} {REG_LOCK_LM_ADDR} {cls.DESC_STURCT_OFF_LOCK}")
        cls.lock.write_begin(tran, REG_LOCK_LM_ADDR, REG_TMP1, 3)
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: lock admitted, TID = %d' {'X0'} {'TID'}")
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: DESC_LM_ADDR = %d' {'X0'} {REG_DESC_LM_ADDR}")

        # copy ob regs
        tran.writeAction(f"mov_reg2reg {OB_KEY} {REG_KEY}")
        tran.writeAction(f"mov_reg2reg {OB_VAL} {REG_VAL}")

        # save cont
        tran.writeAction(f"mov_reg2reg {'X1'} {REG_CONT}")

        # search with specified MLP
        # setup counters
        # check only the allocated entries
        tran.writeAction(f"move {cls.DESC_STURCT_OFF_USED_ENTRY_COUNT}({REG_DESC_LM_ADDR}) {REG_TMP1} 0 8")  # tmp1 => num_used_entries
        tran.writeAction(f"mov_imm2reg {REG_CONCURRENCY} {0}")  # tmp4 => mlp counter
        # if used entries is zero, write directly
        tran.writeAction(f"bgti {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-setup_send_ld'}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: empty bucket, writing without search' {'X0'}")
        tran.writeAction(f"addi {REG_TMP1} {REG_TMP1} {1}")
        tran.writeAction(f"move {REG_TMP1} {cls.DESC_STURCT_OFF_ENTRY_COUNT}({REG_DESC_LM_ADDR}) 0 8")
        tran.writeAction(f"move {REG_TMP1} {cls.DESC_STURCT_OFF_USED_ENTRY_COUNT}({REG_DESC_LM_ADDR}) 0 8")
        tran.writeAction(f"move {cls.DESC_STURCT_OFF_DRAM_ALLOC_START_ADDR}({REG_DESC_LM_ADDR}) {REG_ENTRY_WR_ADDR} 0 8")
        # tran.writeAction(f"sendr_dmlm_wret {REG_ENTRY_WR_ADDR} {tran_key_st_ret.getLabel()} {REG_KEY} {REG_VAL}")
        sht_macros.dram_write_reg_ret(tran=tran, addr_reg=REG_ENTRY_WR_ADDR, ret_tran_label=tran_key_st_ret.getLabel(), tmp_reg=REG_TMP4, arg_reg0=REG_KEY, arg_reg1=REG_VAL)
        tran.writeAction("yield")

        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-setup_send_ld'}: mov_imm2reg {REG_TMP2} {64 // cls.ENTRY_SIZE}")  # tmp2 => max entries per send
        tran.writeAction(f"move {cls.DESC_STURCT_OFF_DRAM_ALLOC_START_ADDR}({REG_DESC_LM_ADDR}) {REG_TMP3} 0 8")  # tmp3 => dram_alloc_start_addr
        tran.writeAction(f"mov_imm2reg {REG_ENTRY_WR_ADDR} {cls.INVALID_MARKER}")
        tran.writeAction(f"mov_imm2reg {REG_DONE} {0}")

        # Send load entries
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_ld'}: blei {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_done'}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: loading, DRAM addr = 0x%x' {'X0'} {REG_TMP3}")
        # tran.writeAction(f"send_dmlm_ld_wret {REG_TMP3} {tran_key_ld_ret.getLabel()} {8}")
        sht_macros.dram_read_ret(tran=tran, addr_reg=REG_TMP3, ret_tran_label=tran_key_ld_ret.getLabel(), tmp_reg=REG_TMP4, arg_lm_words=8)
        tran.writeAction(f"addi {REG_CONCURRENCY} {REG_CONCURRENCY} {1}")  # mlp++
        # check number of valid entries in the send
        tran.writeAction(f"bgti {REG_TMP1} {64 // cls.ENTRY_SIZE} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}")
        # last send, retain last send addr & valid size
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: all loads sent' {'X0'}")
        tran.writeAction(f"mov_reg2reg {REG_TMP1} {REG_TMP2}")  # tmp2 => last send valid entries
        tran.writeAction(f"mov_imm2reg {REG_TMP1} {0}")
        tran.writeAction("yield")
        # full cache line send
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}: subi {REG_TMP1} {REG_TMP1} {64 // cls.ENTRY_SIZE}")
        tran.writeAction(f"addi {REG_TMP3} {REG_TMP3} {64}")
        # check mlp
        tran.writeAction(f"blti {REG_CONCURRENCY} {cls.NUM_CONCURRENT_SENDS} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_ld'}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: send concurrent reached' {'X0'}")
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_done'}: yield")


        # TRAN - load key return
        OB_LD_RET_ADDR = "X3"

        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: load from 0x%x returns, mlp = %d' {'X0'} {OB_LD_RET_ADDR} {REG_CONCURRENCY}")
        tran_key_ld_ret.writeAction(f"subi {REG_CONCURRENCY} {REG_CONCURRENCY} {1}")  # mlp--
        tran_key_ld_ret.writeAction(f"beqi {REG_DONE} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}")
        tran_key_ld_ret.writeAction(f"beqi {REG_DONE} {1} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}")
        tran_key_ld_ret.writeAction(f"bgti {REG_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: last in-flight load, terminating... TID = %d' {'X0'} {'TID'}")
        # cls.lock.write_end(tran_key_ld_ret, REG_LOCK_LM_ADDR, REG_TMP1)
        tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_TMP1} {1}")
        sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, REG_TMP1, REG_ENTRY_WR_ADDR)
        tran_key_ld_ret.writeAction("yield_terminate")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}: yield")

        # Check return
        # check if return is matched with (last) send address
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}: bne {OB_LD_RET_ADDR} {REG_TMP3} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{3 * cls.ENTRY_SIZE}'}")
        # deal with return data, no more sends if found key
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: tail send load returns, num entries = %d' {'X0'} {REG_TMP2}")

        tran_key_ld_ret.writeAction(f"beqi {REG_TMP2} {4} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{3 * cls.ENTRY_SIZE}'}")
        tran_key_ld_ret.writeAction(f"beqi {REG_TMP2} {3} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{2 * cls.ENTRY_SIZE}'}")
        tran_key_ld_ret.writeAction(f"beqi {REG_TMP2} {2} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{1 * cls.ENTRY_SIZE}'}")
        tran_key_ld_ret.writeAction(f"beqi {REG_TMP2} {1} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{0 * cls.ENTRY_SIZE}'}")

        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{3 * cls.ENTRY_SIZE}'}: beq {'X14'} {REG_KEY} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{3 * cls.ENTRY_SIZE}_match'}")  # X14 X15
        tran_key_ld_ret.writeAction(f"bnei {'X14'} {cls.EMPTY_KEY} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{2 * cls.ENTRY_SIZE}'}")
        tran_key_ld_ret.writeAction(f"addi {OB_LD_RET_ADDR} {REG_ENTRY_WR_ADDR} {3 * cls.ENTRY_SIZE}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: found empty entry at addr = 0x%x' {'X0'} {REG_ENTRY_WR_ADDR}")

        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{2 * cls.ENTRY_SIZE}'}: beq {'X12'} {REG_KEY} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{2 * cls.ENTRY_SIZE}_match'}")  # X12 X13
        tran_key_ld_ret.writeAction(f"bnei {'X12'} {cls.EMPTY_KEY} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{1 * cls.ENTRY_SIZE}'}")
        tran_key_ld_ret.writeAction(f"addi {OB_LD_RET_ADDR} {REG_ENTRY_WR_ADDR} {2 * cls.ENTRY_SIZE}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: found empty entry at addr = 0x%x' {'X0'} {REG_ENTRY_WR_ADDR}")

        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{1 * cls.ENTRY_SIZE}'}: beq {'X10'} {REG_KEY} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{1 * cls.ENTRY_SIZE}_match'}")  # X10 X11
        tran_key_ld_ret.writeAction(f"bnei {'X10'} {cls.EMPTY_KEY} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{0 * cls.ENTRY_SIZE}'}")
        tran_key_ld_ret.writeAction(f"addi {OB_LD_RET_ADDR} {REG_ENTRY_WR_ADDR} {1 * cls.ENTRY_SIZE}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: found empty entry at addr = 0x%x' {'X0'} {REG_ENTRY_WR_ADDR}")

        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{0 * cls.ENTRY_SIZE}'}: beq {'X8'} {REG_KEY} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{0 * cls.ENTRY_SIZE}_match'}")  # X8 X9
        tran_key_ld_ret.writeAction(f"bnei {'X8'} {cls.EMPTY_KEY} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_no_match'}")
        tran_key_ld_ret.writeAction(f"addi {OB_LD_RET_ADDR} {REG_ENTRY_WR_ADDR} {0 * cls.ENTRY_SIZE}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: found empty entry at addr = 0x%x' {'X0'} {REG_ENTRY_WR_ADDR}")

        # not matched
        # if mlp is 0, finished, need to write entry & terminate; else go to send
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_no_match'}: bgti {REG_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_ld'}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: no matched entry found, last send load return' {'X0'}")
        tran_key_ld_ret.writeAction(f"bnei {REG_ENTRY_WR_ADDR} {cls.INVALID_MARKER} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_st'}")
        # check if there is space at the end of the allocation area
        tran_key_ld_ret.writeAction(f"move {cls.DESC_STURCT_OFF_NUM_ALLOC_ENTRIES}({REG_DESC_LM_ADDR}) {REG_TMP1} 0 8")  # tmp1 => num_alloc_entries
        tran_key_ld_ret.writeAction(f"move {cls.DESC_STURCT_OFF_USED_ENTRY_COUNT}({REG_DESC_LM_ADDR}) {REG_TMP2} 0 8")  # tmp2 => num_used_entries
        tran_key_ld_ret.writeAction(f"blt {REG_TMP2} {REG_TMP1} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-new_entry'}")
        # out of space!
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: bucket full, add FAILED!' {'X0'}")
        tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_TMP1} {0}")  # indicate failue
        tran_key_ld_ret.writeAction(f"move {cls.DESC_STURCT_OFF_ENTRY_COUNT}({REG_DESC_LM_ADDR}) {REG_TMP3} 0 8")  # tmp3 => entry count
        sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, REG_TMP1, REG_TMP3)
        # sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, 'X0', REG_TMP3)
        cls.lock.write_end(tran_key_ld_ret, REG_LOCK_LM_ADDR, REG_TMP1)
        tran_key_ld_ret.writeAction("yield_terminate")  # only if running out of space!
        # new entry
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-new_entry'}: move {cls.DESC_STURCT_OFF_DRAM_ALLOC_START_ADDR}({REG_DESC_LM_ADDR}) {REG_TMP3} 0 8")  # tmp3 => dram alloc start addr
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: storing in a new entry' {'X0'}")
        tran_key_ld_ret.writeAction(f"lshift {REG_TMP2} {REG_TMP1} {int(math.log2(cls.ENTRY_SIZE))}")
        tran_key_ld_ret.writeAction(f"add {REG_TMP3} {REG_TMP1} {REG_ENTRY_WR_ADDR}")
        tran_key_ld_ret.writeAction(f"addi {REG_TMP2} {REG_TMP2} {1}")  # num_used_entries++
        tran_key_ld_ret.writeAction(f"move {REG_TMP2} {cls.DESC_STURCT_OFF_USED_ENTRY_COUNT}({REG_DESC_LM_ADDR}) 0 8")
        tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_st'}")

        # matched
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{0 * cls.ENTRY_SIZE}_match'}: addi {OB_LD_RET_ADDR} {REG_ENTRY_WR_ADDR} {0 * cls.ENTRY_SIZE}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: found MATCHED entry at addr = 0x%x' {'X0'} {REG_ENTRY_WR_ADDR}")
        tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_st'}")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{1 * cls.ENTRY_SIZE}_match'}: addi {OB_LD_RET_ADDR} {REG_ENTRY_WR_ADDR} {1 * cls.ENTRY_SIZE}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: found MATCHED entry at addr = 0x%x' {'X0'} {REG_ENTRY_WR_ADDR}")
        tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_st'}")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{2 * cls.ENTRY_SIZE}_match'}: addi {OB_LD_RET_ADDR} {REG_ENTRY_WR_ADDR} {2 * cls.ENTRY_SIZE}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: found MATCHED entry at addr = 0x%x' {'X0'} {REG_ENTRY_WR_ADDR}")
        tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_st'}")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{3 * cls.ENTRY_SIZE}_match'}: addi {OB_LD_RET_ADDR} {REG_ENTRY_WR_ADDR} {3 * cls.ENTRY_SIZE}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: found MATCHED entry at addr = 0x%x' {'X0'} {REG_ENTRY_WR_ADDR}")
        tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_st'}")

        # Send store
        # count up the entries
        # mark done
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_st'}: move {cls.DESC_STURCT_OFF_ENTRY_COUNT}({REG_DESC_LM_ADDR}) {REG_TMP1} 0 8")
        tran_key_ld_ret.writeAction(f"addi {REG_TMP1} {REG_TMP1} {1}")
        tran_key_ld_ret.writeAction(f"move {REG_TMP1} {cls.DESC_STURCT_OFF_ENTRY_COUNT}({REG_DESC_LM_ADDR}) 0 8")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: sending write to addr = 0x%x' {'X0'} {REG_ENTRY_WR_ADDR}")
        # tran_key_ld_ret.writeAction(f"sendr_dmlm_wret {REG_ENTRY_WR_ADDR} {tran_key_st_ret.getLabel()} {REG_KEY} {REG_VAL}")
        sht_macros.dram_write_reg_ret(tran=tran_key_ld_ret, addr_reg=REG_ENTRY_WR_ADDR, ret_tran_label=tran_key_st_ret.getLabel(), tmp_reg=REG_TMP4, arg_reg0=REG_KEY, arg_reg1=REG_VAL)
        tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_DONE} {1}")  # mark done
        tran_key_ld_ret.writeAction("yield")

        # Send load
        # if tmp1 (num entries left) is 0, no more sends
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_ld'}: beqi {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_done'}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: sending more load from addr = 0x%x' {'X0'} {REG_TMP3}")
        # tran_key_ld_ret.writeAction(f"send_dmlm_ld_wret {REG_TMP3} {tran_key_ld_ret.getLabel()} {8}")
        sht_macros.dram_read_ret(tran=tran_key_ld_ret, addr_reg=REG_TMP3, ret_tran_label=tran_key_ld_ret.getLabel(), tmp_reg=REG_TMP4, arg_lm_words=8)
        tran_key_ld_ret.writeAction(f"addi {REG_CONCURRENCY} {REG_CONCURRENCY} {1}")  # mlp++
        # check number of valid entries in the send
        tran_key_ld_ret.writeAction(f"bgti {REG_TMP1} {64 // cls.ENTRY_SIZE} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}")
        # last send, retain last send addr & valid size
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: last send' {'X0'}")
        tran_key_ld_ret.writeAction(f"mov_reg2reg {REG_TMP1} {REG_TMP2}")  # tmp2 => last send valid entries
        tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_TMP1} {0}")
        tran_key_ld_ret.writeAction("yield")
        # full cache line send
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}: subi {REG_TMP1} {REG_TMP1} {64 // cls.ENTRY_SIZE}")
        tran_key_ld_ret.writeAction(f"addi {REG_TMP3} {REG_TMP3} {64}")
        # send done
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_done'}: yield")


        # TRAN - store key val
        cls.lock.write_end(tran_key_st_ret, REG_LOCK_LM_ADDR, REG_TMP1)
        tran_key_st_ret.writeAction(f"bgti {REG_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_st_ret-LB-not_done'}")
        if cls.DEBUG:
            tran_key_st_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: write to 0x%x returns, terminating... TID = %d' {'X0'} {'X8'} {'TID'}")
        tran_key_st_ret.writeAction(f"mov_imm2reg {REG_TMP1} {1}")
        sht_macros.return_wreg(tran_key_st_ret, REG_CONT, REG_TMP1, REG_ENTRY_WR_ADDR)
        # sht_macros.return_wreg(tran_key_st_ret, REG_CONT, 'X0', REG_ENTRY_WR_ADDR)
        tran_key_st_ret.writeAction("yield_terminate")
        tran_key_st_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_st_ret-LB-not_done'}: mov_imm2reg {REG_DONE} {2}")
        if cls.DEBUG:
            tran_key_st_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: write to 0x%x returns, waiting all loads return...' {'X0'} {'X8'}")
        tran_key_st_ret.writeAction("yield")

    @classmethod
    def update(cls, tran: Transition, ret: int, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, arg_lm_words: int, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_label_update, ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=arg_lm_words)

    @classmethod
    def update_wcont(cls, tran: Transition, ret: str, tmp_reg0: str, arg_lm_addr_reg: str, arg_lm_words: int, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_label_update, cont_reg=ret, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=arg_lm_words)

    @classmethod
    def _get(cls, state: State):
        """
        X8 - desc_lm_addr
        X9 - key
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._get.__name__

        OB_DESC_LM_OFFSET = "X8"
        OB_KEY = "X9"

        REG_LOCK_LM_ADDR = "X16"
        REG_TMP1 = "X17"
        REG_TMP2 = "X18"
        REG_TMP3 = "X19"
        REG_TMP4 = "X22"
        REG_CONCURRENCY = "X20"
        REG_DONE = "X21"

        REG_DESC_LM_ADDR = "X28"
        REG_KEY = "X29"
        REG_VAL = "X30"

        REG_CONT = "X31"

        tran = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR")
        if tran is None:
            return
        cls.tran_label_get = tran.getLabel()
        tran_key_ld_ret = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-key_ld_ret")

        # TRAN - function entry
        # calc desc lm addr
        tran.writeAction(f"add {OB_DESC_LM_OFFSET} {'X7'} {REG_DESC_LM_ADDR}")
        # get lock
        tran.writeAction(f"addi {REG_DESC_LM_ADDR} {REG_LOCK_LM_ADDR} {cls.DESC_STURCT_OFF_LOCK}")
        cls.lock.read_begin(tran, REG_LOCK_LM_ADDR, REG_TMP1, 2)
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] GET: lock admitted' {'X0'}")

        # copy ob regs
        tran.writeAction(f"mov_reg2reg {OB_KEY} {REG_KEY}")

        # save cont
        tran.writeAction(f"mov_reg2reg {'X1'} {REG_CONT}")

        # search with specified MLP
        # setup counters
        # check only the allocated entries
        tran.writeAction(f"move {cls.DESC_STURCT_OFF_USED_ENTRY_COUNT}({REG_DESC_LM_ADDR}) {REG_TMP1} 0 8")  # tmp1 => num_used_entries
        tran.writeAction(f"mov_imm2reg {REG_CONCURRENCY} {0}")  # tmp4 => mlp counter
        # if used entries is zero, reply not found
        tran.writeAction(f"bgti {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-setup_send_ld'}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] GET: empty bucket, reply not found' {'X0'}")
        tran.writeAction(f"mov_imm2reg {REG_TMP1} {0}")
        sht_macros.return_wreg(tran, REG_CONT, REG_TMP1, REG_KEY)
        cls.lock.read_end(tran, REG_LOCK_LM_ADDR, REG_TMP1)
        tran.writeAction("yield_terminate")

        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-setup_send_ld'}: mov_imm2reg {REG_TMP2} {64 // cls.ENTRY_SIZE}")  # tmp2 => max entries per send
        tran.writeAction(f"move {cls.DESC_STURCT_OFF_DRAM_ALLOC_START_ADDR}({REG_DESC_LM_ADDR}) {REG_TMP3} 0 8")  # tmp3 => dram_alloc_start_addr
        tran.writeAction(f"mov_imm2reg {REG_DONE} {0}")

        # Send load entries
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_ld'}: blei {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_done'}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] GET: loading, DRAM addr = 0x%x' {'X0'} {REG_TMP3}")
        # tran.writeAction(f"send_dmlm_ld_wret {REG_TMP3} {tran_key_ld_ret.getLabel()} {8}")
        sht_macros.dram_read_ret(tran=tran, addr_reg=REG_TMP3, ret_tran_label=tran_key_ld_ret.getLabel(), tmp_reg=REG_TMP4, arg_lm_words=8)
        tran.writeAction(f"addi {REG_CONCURRENCY} {REG_CONCURRENCY} {1}")  # mlp++
        # check number of valid entries in the send
        tran.writeAction(f"bgti {REG_TMP1} {64 // cls.ENTRY_SIZE} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}")
        # last send, retain last send addr & valid size
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] GET: all loads sent' {'X0'}")
        tran.writeAction(f"mov_reg2reg {REG_TMP1} {REG_TMP2}")  # tmp2 => last send valid entries
        tran.writeAction(f"mov_imm2reg {REG_TMP1} {0}")
        tran.writeAction("yield")
        # full cache line send
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}: subi {REG_TMP1} {REG_TMP1} {64 // cls.ENTRY_SIZE}")
        tran.writeAction(f"addi {REG_TMP3} {REG_TMP3} {64}")
        # check mlp
        tran.writeAction(f"blti {REG_CONCURRENCY} {cls.NUM_CONCURRENT_SENDS} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_ld'}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] GET: send concurrent reached' {'X0'}")
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_done'}: yield")


        # TRAN - load key return
        OB_LD_RET_ADDR = "X3"

        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] GET: load from 0x%x returns, mlp = %d' {'X0'} {OB_LD_RET_ADDR} {REG_CONCURRENCY}")
        tran_key_ld_ret.writeAction(f"subi {REG_CONCURRENCY} {REG_CONCURRENCY} {1}")  # mlp--

        tran_key_ld_ret.writeAction(f"beqi {REG_DONE} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}")
        tran_key_ld_ret.writeAction(f"bgti {REG_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] GET: last in-flight load, terminating...' {'X0'}")
        tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_TMP1} {1}")
        sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, REG_TMP1, REG_VAL)
        # cls.lock.read_end(tran_key_ld_ret, REG_LOCK_LM_ADDR, REG_TMP1)  # no need, unlocked early
        tran_key_ld_ret.writeAction("yield_terminate")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}: yield")

        # Check return
        # check if return is matched with (last) send address
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}: bne {OB_LD_RET_ADDR} {REG_TMP3} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{3 * cls.ENTRY_SIZE}'}")
        # deal with return data, no more sends if found key
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] GET: tail send load returns, num entries = %d' {'X0'} {REG_TMP2}")

        tran_key_ld_ret.writeAction(f"beqi {REG_TMP2} {4} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{3 * cls.ENTRY_SIZE}'}")
        tran_key_ld_ret.writeAction(f"beqi {REG_TMP2} {3} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{2 * cls.ENTRY_SIZE}'}")
        tran_key_ld_ret.writeAction(f"beqi {REG_TMP2} {2} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{1 * cls.ENTRY_SIZE}'}")
        tran_key_ld_ret.writeAction(f"beqi {REG_TMP2} {1} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{0 * cls.ENTRY_SIZE}'}")

        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{3 * cls.ENTRY_SIZE}'}: beq {'X14'} {REG_KEY} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{3 * cls.ENTRY_SIZE}_match'}")  # X14 X15
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{2 * cls.ENTRY_SIZE}'}: beq {'X12'} {REG_KEY} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{2 * cls.ENTRY_SIZE}_match'}")  # X12 X13
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{1 * cls.ENTRY_SIZE}'}: beq {'X10'} {REG_KEY} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{1 * cls.ENTRY_SIZE}_match'}")  # X10 X11
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{0 * cls.ENTRY_SIZE}'}: beq {'X8'} {REG_KEY} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{0 * cls.ENTRY_SIZE}_match'}")  # X8 X9

        # not matched
        # if mlp is 0, reply not found; else go to send
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_no_match'}: bgti {REG_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_ld'}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] GET: no matched entry found, last send load return, replying' {'X0'}")
        tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_TMP1} {0}")
        sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, REG_TMP1, REG_KEY)
        cls.lock.read_end(tran_key_ld_ret, REG_LOCK_LM_ADDR, REG_TMP1)
        tran_key_ld_ret.writeAction("yield_terminate")

        # matched
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{0 * cls.ENTRY_SIZE}_match'}: mov_reg2reg {'X9'} {REG_VAL}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] GET: found MATCHED entry at block addr = 0x%x, key = %d, val = %d' {'X0'} {OB_LD_RET_ADDR} {REG_KEY} {REG_VAL}")
        tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-matched_reply'}")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{1 * cls.ENTRY_SIZE}_match'}: mov_reg2reg {'X11'} {REG_VAL}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] GET: found MATCHED entry at block addr = 0x%x, key = %d, val = %d' {'X0'} {OB_LD_RET_ADDR} {REG_KEY} {REG_VAL}")
        tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-matched_reply'}")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{2 * cls.ENTRY_SIZE}_match'}: mov_reg2reg {'X13'} {REG_VAL}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] GET: found MATCHED entry at block addr = 0x%x, key = %d, val = %d' {'X0'} {OB_LD_RET_ADDR} {REG_KEY} {REG_VAL}")
        tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-matched_reply'}")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{3 * cls.ENTRY_SIZE}_match'}: mov_reg2reg {'X15'} {REG_VAL}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] GET: found MATCHED entry at block addr = 0x%x, key = %d, val = %d' {'X0'} {OB_LD_RET_ADDR} {REG_KEY} {REG_VAL}")
        tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-matched_reply'}")

        # Send matched reply
        # mark done
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-matched_reply'}: bgti {REG_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_wait_ret'}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] GET: matched, reply & terminating...' {'X0'} ")
        tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_TMP1} {1}")
        sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, REG_TMP1, REG_VAL)
        cls.lock.read_end(tran_key_ld_ret, REG_LOCK_LM_ADDR, REG_TMP1)
        tran_key_ld_ret.writeAction("yield_terminate")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_wait_ret'}: mov_imm2reg {REG_DONE} {1}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] GET: matched but have to wait other loads return...' {'X0'} ")
        cls.lock.read_end(tran_key_ld_ret, REG_LOCK_LM_ADDR, REG_TMP1)
        tran_key_ld_ret.writeAction("yield")

        # Send load
        # if tmp1 (num entries left) is 0, no more sends
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_ld'}: beqi {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_done'}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] GET: sending more load from addr = 0x%x' {'X0'} {REG_TMP3}")
        # tran_key_ld_ret.writeAction(f"send_dmlm_ld_wret {REG_TMP3} {tran_key_ld_ret.getLabel()} {8}")
        sht_macros.dram_read_ret(tran=tran_key_ld_ret, addr_reg=REG_TMP3, ret_tran_label=tran_key_ld_ret.getLabel(), tmp_reg=REG_TMP4, arg_lm_words=8)
        tran_key_ld_ret.writeAction(f"addi {REG_CONCURRENCY} {REG_CONCURRENCY} {1}")  # mlp++
        # check number of valid entries in the send
        tran_key_ld_ret.writeAction(f"bgti {REG_TMP1} {64 // cls.ENTRY_SIZE} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}")
        # last send, retain last send addr & valid size
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] GET: last send' {'X0'}")
        tran_key_ld_ret.writeAction(f"mov_reg2reg {REG_TMP1} {REG_TMP2}")  # tmp2 => last send valid entries
        tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_TMP1} {0}")
        tran_key_ld_ret.writeAction("yield")
        # full cache line send
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}: subi {REG_TMP1} {REG_TMP1} {64 // cls.ENTRY_SIZE}")
        tran_key_ld_ret.writeAction(f"addi {REG_TMP3} {REG_TMP3} {64}")
        # send done
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_done'}: yield")

    @classmethod
    def get(cls, tran: Transition, ret: int, tmp_reg0: str, tmp_reg1: str, desc_lm_offset_reg: str, key_reg: str, dst_nwid_reg: str = 'X0'):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_label_get, ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=desc_lm_offset_reg, arg_reg1=key_reg)

    @classmethod
    def get_wcont(cls, tran: Transition, ret: str, tmp_reg: str, desc_lm_offset_reg: str, key_reg: str, dst_nwid_reg: str = 'X0'):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_label_get, cont_reg=ret, tmp_reg=tmp_reg, arg_reg0=desc_lm_offset_reg, arg_reg1=key_reg)

    @classmethod
    def _delete(cls, state: State):
        """
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
