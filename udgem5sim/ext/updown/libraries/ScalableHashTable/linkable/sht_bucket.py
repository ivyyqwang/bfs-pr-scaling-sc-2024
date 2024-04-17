from linker.EFAProgram import efaProgram, EFAProgram
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

    DESC_SIZE = 5 * 8

    DESC_STURCT_OFF_LOCK = 0
    DESC_STURCT_OFF_DRAM_ALLOC_START_ADDR = 8
    DESC_STURCT_OFF_NUM_ALLOC_ENTRIES = 16
    DESC_STURCT_OFF_ENTRY_COUNT = 24
    DESC_STURCT_OFF_LM_BUF_ADDR = 32
    # DESC_STURCT_OFF_USED_ENTRY_COUNT = 40

    WORD_SIZE = 8

    # INVALID_MARKER = 0
    # EMPTY_KEY = 0
    KEY_SIZE = 8
    VAL_SIZE = 8
    ENTRY_SIZE = KEY_SIZE + VAL_SIZE

    LM_BUF_SIZE = 64

    NUM_CONCURRENT_SENDS = 25

    @classmethod
    def setup(cls, state: EFAProgram.State, debug=False) -> None:
        cls.DEBUG = debug
        cls.lock = sht_macros.MRSWLock(atomic=False, debug=debug)
        # cls.lock = sht_macros.MRSWLock(atomic=True, debug=debug)  # remove locks for experiemnt

        CLS_NAME = cls.__name__
        cls.tran_initialize = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-initialize-TR")
        cls.tran_update = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-update-TR")
        cls.tran_get = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-get-TR")
        # cls.tran_delete = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-delete-TR")
        cls.tran_get_next = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-get_next-TR")
        cls.tran_get_next_split = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-get_next_split-TR")

        # TODO: code injection
        cls._initialize(state)
        cls._update(state)
        cls._get(state)
        # cls._delete(state)
        cls._get_next(state)
        cls._get_next_split(state)

    @classmethod
    def _initialize(cls, state: EFAProgram.State):
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
        OB_LM_BUF_OFFSET = "X11"

        REG_DESC_LM_ADDR = "X16"
        REG_TMP0 = "X17"
        REG_TMP1 = "X18"

        tran = cls.tran_initialize
        if tran is None:
            return
        cls.tran_label_init = tran.getLabel()

        # TRAN - init entry
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] INIT: start' {'X0'}")
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
        tran.writeAction(f"add {OB_LM_BUF_OFFSET} {'X7'} {REG_TMP1}")
        tran.writeAction(f"move {REG_TMP1} {cls.DESC_STURCT_OFF_LM_BUF_ADDR}({REG_DESC_LM_ADDR}) 0 8")
        # entry count
        tran.writeAction(f"mov_imm2reg {REG_TMP1} {0}")
        tran.writeAction(f"move {REG_TMP1} {cls.DESC_STURCT_OFF_ENTRY_COUNT}({REG_DESC_LM_ADDR}) 0 8")
        # # used entries
        # tran.writeAction(f"move {REG_TMP1} {cls.DESC_STURCT_OFF_USED_ENTRY_COUNT}({REG_DESC_LM_ADDR}) 0 8")

        sht_macros.return_wreg(tran=tran, cont_reg='X1', tmp_reg=REG_TMP0, arg_reg0="X0", arg_reg1="X0")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] INIT: done' {'X0'}")
        tran.writeAction("yield_terminate")

    @classmethod
    def initialize(cls, tran: EFAProgram.Transition, ret: int, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = "") -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_label_init, ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=4, branch_label=branch_label)

    @classmethod
    def initialize_wcont(cls, tran: EFAProgram.Transition, ret: str, tmp_reg0: str, arg_lm_addr_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = "") -> None:
        sht_macros.call_wlm_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_label_init, cont_reg=ret, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=4, branch_label=branch_label)

    @classmethod
    def _update(cls, state: EFAProgram.State):
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

        tran = cls.tran_update
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
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] UPDATE: lock admitted, TID = %lu, key = %lu, val = %lu' {'X0'} {'TID'} {OB_KEY} {OB_VAL}")
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] UPDATE: DESC_LM_ADDR = 0x%lx' {'X0'} {REG_DESC_LM_ADDR}")

        # copy ob regs
        tran.writeAction(f"addi {OB_KEY} {REG_KEY} {0}")
        tran.writeAction(f"addi {OB_VAL} {REG_VAL} {0}")

        # save cont
        tran.writeAction(f"addi {'X1'} {REG_CONT} {0}")

        # search with specified MLP
        # setup counters
        # check only the allocated entries
        tran.writeAction(f"move {cls.DESC_STURCT_OFF_ENTRY_COUNT}({REG_DESC_LM_ADDR}) {REG_TMP1} 0 8")  # tmp1 => entry count
        tran.writeAction(f"mov_imm2reg {REG_CONCURRENCY} {0}")  # tmp4 => mlp counter
        # if used entries is zero, write directly
        tran.writeAction(f"bgti {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-setup_send_ld'}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] UPDATE: empty bucket, writing without search' {'X0'}")
        tran.writeAction(f"addi {REG_TMP1} {REG_TMP1} {1}")
        tran.writeAction(f"move {REG_TMP1} {cls.DESC_STURCT_OFF_ENTRY_COUNT}({REG_DESC_LM_ADDR}) 0 8")
        tran.writeAction(f"move {cls.DESC_STURCT_OFF_DRAM_ALLOC_START_ADDR}({REG_DESC_LM_ADDR}) {REG_ENTRY_WR_ADDR} 0 8")
        sht_macros.dram_write_reg_ret(tran=tran, addr_reg=REG_ENTRY_WR_ADDR, ret_tran_label=tran_key_st_ret.getLabel(), tmp_reg=REG_TMP4, arg_reg0=REG_KEY, arg_reg1=REG_VAL)
        tran.writeAction("yield")

        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-setup_send_ld'}: mov_imm2reg {REG_TMP2} {64 // cls.ENTRY_SIZE}")  # tmp2 => max entries per send
        tran.writeAction(f"move {cls.DESC_STURCT_OFF_DRAM_ALLOC_START_ADDR}({REG_DESC_LM_ADDR}) {REG_TMP3} 0 8")  # tmp3 => dram_alloc_start_addr
        tran.writeAction(f"mov_imm2reg {REG_DONE} {0}")

        # Send load entries
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_ld'}: blei {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_done'}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] UPDATE: loading, DRAM addr = 0x%x' {'X0'} {REG_TMP3}")
        sht_macros.dram_read_ret(tran=tran, addr_reg=REG_TMP3, ret_tran_label=tran_key_ld_ret.getLabel(), tmp_reg=REG_TMP4, arg_lm_words=8)
        tran.writeAction(f"addi {REG_CONCURRENCY} {REG_CONCURRENCY} {1}")  # mlp++
        # check number of valid entries in the send
        tran.writeAction(f"bgti {REG_TMP1} {64 // cls.ENTRY_SIZE} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}")
        # last send, retain last send addr & valid size
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] UPDATE: all loads sent' {'X0'}")
        tran.writeAction(f"addi {REG_TMP1} {REG_TMP2} {0}")  # tmp2 => last send valid entries
        tran.writeAction(f"mov_imm2reg {REG_TMP1} {0}")
        tran.writeAction("yield")
        # full cache line send
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}: subi {REG_TMP1} {REG_TMP1} {64 // cls.ENTRY_SIZE}")
        tran.writeAction(f"addi {REG_TMP3} {REG_TMP3} {64}")
        # check mlp
        tran.writeAction(f"bltiu {REG_CONCURRENCY} {cls.NUM_CONCURRENT_SENDS} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_ld'}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] UPDATE: send concurrency reached' {'X0'}")
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_done'}: yield")


        # TRAN - load key return
        OB_LD_RET_ADDR = "X3"

        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] UPDATE: load from 0x%x returns, mlp = %d, looking for key = %lu, val = %lu' {'X0'} {OB_LD_RET_ADDR} {REG_CONCURRENCY} {REG_KEY} {REG_VAL}")
        tran_key_ld_ret.writeAction(f"subi {REG_CONCURRENCY} {REG_CONCURRENCY} {1}")  # mlp--
        tran_key_ld_ret.writeAction(f"beqi {REG_DONE} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}")
        tran_key_ld_ret.writeAction(f"beqi {REG_DONE} {1} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}")
        tran_key_ld_ret.writeAction(f"bgti {REG_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] UPDATE: last in-flight load, terminating... TID = %d' {'X0'} {'TID'}")
        # cls.lock.write_end(tran_key_ld_ret, REG_LOCK_LM_ADDR, REG_TMP1)
        tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_TMP1} {1}")
        sht_macros.return_wreg(tran=tran_key_ld_ret, cont_reg=REG_CONT, tmp_reg=REG_TMP2, arg_reg0=REG_TMP1, arg_reg1=REG_ENTRY_WR_ADDR)
        tran_key_ld_ret.writeAction("yield_terminate")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}: yield")

        # Check return
        # check if return is matched with (last) send address
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}: bne {OB_LD_RET_ADDR} {REG_TMP3} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{3 * cls.ENTRY_SIZE}'}")
        # deal with return data, no more sends if found key
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] UPDATE: tail send load returns, num entries = %d' {'X0'} {REG_TMP2}")

        tran_key_ld_ret.writeAction(f"beqi {REG_TMP2} {4} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{3 * cls.ENTRY_SIZE}'}")
        tran_key_ld_ret.writeAction(f"beqi {REG_TMP2} {3} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{2 * cls.ENTRY_SIZE}'}")
        tran_key_ld_ret.writeAction(f"beqi {REG_TMP2} {2} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{1 * cls.ENTRY_SIZE}'}")
        tran_key_ld_ret.writeAction(f"beqi {REG_TMP2} {1} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{0 * cls.ENTRY_SIZE}'}")

        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{3 * cls.ENTRY_SIZE}'}: beq {'X14'} {REG_KEY} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{3 * cls.ENTRY_SIZE}_match'}")  # X14 X15
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{2 * cls.ENTRY_SIZE}'}: beq {'X12'} {REG_KEY} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{2 * cls.ENTRY_SIZE}_match'}")  # X12 X13
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{1 * cls.ENTRY_SIZE}'}: beq {'X10'} {REG_KEY} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{1 * cls.ENTRY_SIZE}_match'}")  # X10 X11
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{0 * cls.ENTRY_SIZE}'}: beq {'X8'} {REG_KEY} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{0 * cls.ENTRY_SIZE}_match'}")  # X8 X9

        # not matched
        # if mlp is 0, finished, need to write entry & terminate; else go to send
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_no_match'}: bgti {REG_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_ld'}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] UPDATE: no matched entry found, last send load return' {'X0'}")
        # check if there is space at the end of the allocation area
        tran_key_ld_ret.writeAction(f"move {cls.DESC_STURCT_OFF_NUM_ALLOC_ENTRIES}({REG_DESC_LM_ADDR}) {REG_TMP1} 0 8")  # tmp1 => num_alloc_entries
        tran_key_ld_ret.writeAction(f"move {cls.DESC_STURCT_OFF_ENTRY_COUNT}({REG_DESC_LM_ADDR}) {REG_TMP2} 0 8")  # tmp2 => entry count
        tran_key_ld_ret.writeAction(f"blt {REG_TMP2} {REG_TMP1} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-new_entry'}")
        # out of space!
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] UPDATE: bucket full, add FAILED!' {'X0'}")
        tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_TMP1} {0}")  # indicate failue
        sht_macros.return_wreg(tran=tran_key_ld_ret, cont_reg=REG_CONT, tmp_reg=REG_TMP3, arg_reg0=REG_TMP1, arg_reg1=REG_TMP2)
        # sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, 'X0', REG_TMP3)
        cls.lock.write_end(tran_key_ld_ret, REG_LOCK_LM_ADDR, REG_TMP1)
        tran_key_ld_ret.writeAction("yield_terminate")  # only if running out of space!
        # new entry
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-new_entry'}: move {cls.DESC_STURCT_OFF_DRAM_ALLOC_START_ADDR}({REG_DESC_LM_ADDR}) {REG_TMP3} 0 8")  # tmp3 => dram alloc start addr
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] UPDATE: storing in a new entry, key = %lu, val = %lu' {'X0'} {REG_KEY} {REG_VAL}")
        tran_key_ld_ret.writeAction(f"lshift {REG_TMP2} {REG_TMP1} {int(math.log2(cls.ENTRY_SIZE))}")
        tran_key_ld_ret.writeAction(f"add {REG_TMP3} {REG_TMP1} {REG_ENTRY_WR_ADDR}")
        tran_key_ld_ret.writeAction(f"addi {REG_TMP2} {REG_TMP2} {1}")  # entry count++
        tran_key_ld_ret.writeAction(f"move {REG_TMP2} {cls.DESC_STURCT_OFF_ENTRY_COUNT}({REG_DESC_LM_ADDR}) 0 8")
        tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_st'}")

        # matched
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{0 * cls.ENTRY_SIZE}_match'}: addi {OB_LD_RET_ADDR} {REG_ENTRY_WR_ADDR} {0 * cls.ENTRY_SIZE}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] UPDATE: found MATCHED entry at addr = 0x%x, key = %lu, val = %lu' {'X0'} {REG_ENTRY_WR_ADDR} {REG_KEY} {REG_VAL}")
        tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_st'}")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{1 * cls.ENTRY_SIZE}_match'}: addi {OB_LD_RET_ADDR} {REG_ENTRY_WR_ADDR} {1 * cls.ENTRY_SIZE}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] UPDATE: found MATCHED entry at addr = 0x%x, key = %lu, val = %lu' {'X0'} {REG_ENTRY_WR_ADDR} {REG_KEY} {REG_VAL}")
        tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_st'}")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{2 * cls.ENTRY_SIZE}_match'}: addi {OB_LD_RET_ADDR} {REG_ENTRY_WR_ADDR} {2 * cls.ENTRY_SIZE}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] UPDATE: found MATCHED entry at addr = 0x%x, key = %lu, val = %lu' {'X0'} {REG_ENTRY_WR_ADDR} {REG_KEY} {REG_VAL}")
        tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_st'}")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{3 * cls.ENTRY_SIZE}_match'}: addi {OB_LD_RET_ADDR} {REG_ENTRY_WR_ADDR} {3 * cls.ENTRY_SIZE}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] UPDATE: found MATCHED entry at addr = 0x%x, key = %lu, val = %lu' {'X0'} {REG_ENTRY_WR_ADDR} {REG_KEY} {REG_VAL}")
        tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_st'}")

        # Send store
        # mark done
        sht_macros.dram_write_reg_ret(tran=tran_key_ld_ret, addr_reg=REG_ENTRY_WR_ADDR, ret_tran_label=tran_key_st_ret.getLabel(), tmp_reg=REG_TMP4, arg_reg0=REG_KEY, arg_reg1=REG_VAL, branch_label=f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_st')
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] UPDATE: sending write to addr = 0x%x, key = %lu, val = %lu' {'X0'} {REG_ENTRY_WR_ADDR} {REG_KEY} {REG_VAL}")
        tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_DONE} {1}")  # mark done
        tran_key_ld_ret.writeAction("yield")

        # Send load
        # if tmp1 (num entries left) is 0, no more sends
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_ld'}: beqi {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_done'}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] UPDATE: sending more load from addr = 0x%x' {'X0'} {REG_TMP3}")
        sht_macros.dram_read_ret(tran=tran_key_ld_ret, addr_reg=REG_TMP3, ret_tran_label=tran_key_ld_ret.getLabel(), tmp_reg=REG_TMP4, arg_lm_words=8)
        tran_key_ld_ret.writeAction(f"addi {REG_CONCURRENCY} {REG_CONCURRENCY} {1}")  # mlp++
        # check number of valid entries in the send
        tran_key_ld_ret.writeAction(f"bgti {REG_TMP1} {64 // cls.ENTRY_SIZE} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}")
        # last send, retain last send addr & valid size
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] UPDATE: last send' {'X0'}")
        tran_key_ld_ret.writeAction(f"addi {REG_TMP1} {REG_TMP2} {0}")  # tmp2 => last send valid entries
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
            tran_key_st_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] UPDATE: write to 0x%x returns, terminating... TID = %d' {'X0'} {'X8'} {'TID'}")
        tran_key_st_ret.writeAction(f"mov_imm2reg {REG_TMP1} {1}")
        sht_macros.return_wreg(tran=tran_key_st_ret, cont_reg=REG_CONT, tmp_reg=REG_TMP2, arg_reg0=REG_TMP1, arg_reg1=REG_ENTRY_WR_ADDR)
        # sht_macros.return_wreg(tran_key_st_ret, REG_CONT, 'X0', REG_ENTRY_WR_ADDR)
        tran_key_st_ret.writeAction("yield_terminate")
        tran_key_st_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_st_ret-LB-not_done'}: mov_imm2reg {REG_DONE} {2}")
        if cls.DEBUG:
            tran_key_st_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] UPDATE: write to 0x%x returns, waiting all loads return...' {'X0'} {'X8'}")
        tran_key_st_ret.writeAction("yield")

    @classmethod
    def update(cls, tran: EFAProgram.Transition, ret: int, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, arg_lm_words: int, dst_nwid_reg: str = 'X0', branch_label: str = "") -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_label_update, ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=arg_lm_words, branch_label=branch_label)

    @classmethod
    def update_wcont(cls, tran: EFAProgram.Transition, ret: str, tmp_reg0: str, arg_lm_addr_reg: str, arg_lm_words: int, dst_nwid_reg: str = 'X0', branch_label: str = "") -> None:
        sht_macros.call_wlm_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_label_update, cont_reg=ret, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=arg_lm_words, branch_label=branch_label)

    @classmethod
    def _get(cls, state: EFAProgram.State):
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

        tran = cls.tran_get
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
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] GET: lock admitted' {'X0'}")

        # copy ob regs
        tran.writeAction(f"addi {OB_KEY} {REG_KEY} {0}")

        # save cont
        tran.writeAction(f"addi {'X1'} {REG_CONT} {0}")

        # search with specified MLP
        # setup counters
        # check only the allocated entries
        tran.writeAction(f"move {cls.DESC_STURCT_OFF_ENTRY_COUNT}({REG_DESC_LM_ADDR}) {REG_TMP1} 0 8")  # tmp1 => entry count
        tran.writeAction(f"mov_imm2reg {REG_CONCURRENCY} {0}")  # tmp4 => mlp counter
        # if used entries is zero, reply not found
        tran.writeAction(f"bgti {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-setup_send_ld'}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] GET: empty bucket, reply not found' {'X0'}")
        tran.writeAction(f"mov_imm2reg {REG_TMP1} {0}")
        sht_macros.return_wreg(tran=tran, cont_reg=REG_CONT, tmp_reg=REG_TMP2, arg_reg0=REG_TMP1, arg_reg1=REG_KEY)
        cls.lock.read_end(tran, REG_LOCK_LM_ADDR, REG_TMP1)
        tran.writeAction("yield_terminate")

        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-setup_send_ld'}: mov_imm2reg {REG_TMP2} {64 // cls.ENTRY_SIZE}")  # tmp2 => max entries per send
        tran.writeAction(f"move {cls.DESC_STURCT_OFF_DRAM_ALLOC_START_ADDR}({REG_DESC_LM_ADDR}) {REG_TMP3} 0 8")  # tmp3 => dram_alloc_start_addr
        tran.writeAction(f"mov_imm2reg {REG_DONE} {0}")

        # Send load entries
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_ld'}: blei {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_done'}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] GET: loading, DRAM addr = 0x%x' {'X0'} {REG_TMP3}")
        # tran.writeAction(f"send_dmlm_ld_wret {REG_TMP3} {tran_key_ld_ret.getLabel()} {8}")
        sht_macros.dram_read_ret(tran=tran, addr_reg=REG_TMP3, ret_tran_label=tran_key_ld_ret.getLabel(), tmp_reg=REG_TMP4, arg_lm_words=8)
        tran.writeAction(f"addi {REG_CONCURRENCY} {REG_CONCURRENCY} {1}")  # mlp++
        # check number of valid entries in the send
        tran.writeAction(f"bgti {REG_TMP1} {64 // cls.ENTRY_SIZE} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}")
        # last send, retain last send addr & valid size
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] GET: all loads sent' {'X0'}")
        tran.writeAction(f"addi {REG_TMP1} {REG_TMP2} {0}")  # tmp2 => last send valid entries
        tran.writeAction(f"mov_imm2reg {REG_TMP1} {0}")
        tran.writeAction("yield")
        # full cache line send
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}: subi {REG_TMP1} {REG_TMP1} {64 // cls.ENTRY_SIZE}")
        tran.writeAction(f"addi {REG_TMP3} {REG_TMP3} {64}")
        # check mlp
        tran.writeAction(f"bltiu {REG_CONCURRENCY} {cls.NUM_CONCURRENT_SENDS} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_ld'}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] GET: send concurrent reached' {'X0'}")
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_done'}: yield")


        # TRAN - load key return
        OB_LD_RET_ADDR = "X3"

        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] GET: load from 0x%x returns, mlp = %d' {'X0'} {OB_LD_RET_ADDR} {REG_CONCURRENCY}")
        tran_key_ld_ret.writeAction(f"subi {REG_CONCURRENCY} {REG_CONCURRENCY} {1}")  # mlp--

        tran_key_ld_ret.writeAction(f"beqi {REG_DONE} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}")
        tran_key_ld_ret.writeAction(f"bgti {REG_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] GET: last in-flight load, terminating...' {'X0'}")
        tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_TMP1} {1}")
        sht_macros.return_wreg(tran=tran_key_ld_ret, cont_reg=REG_CONT, tmp_reg=REG_TMP2, arg_reg0=REG_TMP1, arg_reg1=REG_VAL)
        # cls.lock.read_end(tran_key_ld_ret, REG_LOCK_LM_ADDR, REG_TMP1)  # no need, unlocked early
        tran_key_ld_ret.writeAction("yield_terminate")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}: yield")

        # Check return
        # check if return is matched with (last) send address
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}: bne {OB_LD_RET_ADDR} {REG_TMP3} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{3 * cls.ENTRY_SIZE}'}")
        # deal with return data, no more sends if found key
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] GET: tail send load returns, num entries = %d' {'X0'} {REG_TMP2}")

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
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] GET: no matched entry found, last send load return, replying' {'X0'}")
        tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_TMP1} {0}")
        sht_macros.return_wreg(tran=tran_key_ld_ret, cont_reg=REG_CONT, tmp_reg=REG_TMP2, arg_reg0=REG_TMP1, arg_reg1=REG_KEY)
        cls.lock.read_end(tran_key_ld_ret, REG_LOCK_LM_ADDR, REG_TMP1)
        tran_key_ld_ret.writeAction("yield_terminate")

        # matched
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{0 * cls.ENTRY_SIZE}_match'}: addi {'X9'} {REG_VAL} {0}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] GET: found MATCHED entry at block addr = 0x%x, key = %d, val = %d' {'X0'} {OB_LD_RET_ADDR} {REG_KEY} {REG_VAL}")
        tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-matched_reply'}")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{1 * cls.ENTRY_SIZE}_match'}: addi {'X11'} {REG_VAL} {0}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] GET: found MATCHED entry at block addr = 0x%x, key = %d, val = %d' {'X0'} {OB_LD_RET_ADDR} {REG_KEY} {REG_VAL}")
        tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-matched_reply'}")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{2 * cls.ENTRY_SIZE}_match'}: addi {'X13'} {REG_VAL} {0}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] GET: found MATCHED entry at block addr = 0x%x, key = %d, val = %d' {'X0'} {OB_LD_RET_ADDR} {REG_KEY} {REG_VAL}")
        tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-matched_reply'}")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{3 * cls.ENTRY_SIZE}_match'}: addi {'X15'} {REG_VAL} {0}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] GET: found MATCHED entry at block addr = 0x%x, key = %d, val = %d' {'X0'} {OB_LD_RET_ADDR} {REG_KEY} {REG_VAL}")
        tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-matched_reply'}")

        # Send matched reply
        # mark done
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-matched_reply'}: bgti {REG_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_wait_ret'}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] GET: matched, reply & terminating...' {'X0'} ")
        tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_TMP1} {1}")
        sht_macros.return_wreg(tran=tran_key_ld_ret, cont_reg=REG_CONT, tmp_reg=REG_TMP2, arg_reg0=REG_TMP1, arg_reg1=REG_VAL)
        cls.lock.read_end(tran_key_ld_ret, REG_LOCK_LM_ADDR, REG_TMP1)
        tran_key_ld_ret.writeAction("yield_terminate")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_wait_ret'}: mov_imm2reg {REG_DONE} {1}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] GET: matched but have to wait other loads return...' {'X0'} ")
        cls.lock.read_end(tran_key_ld_ret, REG_LOCK_LM_ADDR, REG_TMP1)
        tran_key_ld_ret.writeAction("yield")

        # Send load
        # if tmp1 (num entries left) is 0, no more sends
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_ld'}: beqi {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_done'}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] GET: sending more load from addr = 0x%x' {'X0'} {REG_TMP3}")
        # tran_key_ld_ret.writeAction(f"send_dmlm_ld_wret {REG_TMP3} {tran_key_ld_ret.getLabel()} {8}")
        sht_macros.dram_read_ret(tran=tran_key_ld_ret, addr_reg=REG_TMP3, ret_tran_label=tran_key_ld_ret.getLabel(), tmp_reg=REG_TMP4, arg_lm_words=8)
        tran_key_ld_ret.writeAction(f"addi {REG_CONCURRENCY} {REG_CONCURRENCY} {1}")  # mlp++
        # check number of valid entries in the send
        tran_key_ld_ret.writeAction(f"bgti {REG_TMP1} {64 // cls.ENTRY_SIZE} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}")
        # last send, retain last send addr & valid size
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] GET: last send' {'X0'}")
        tran_key_ld_ret.writeAction(f"addi {REG_TMP1} {REG_TMP2} {0}")  # tmp2 => last send valid entries
        tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_TMP1} {0}")
        tran_key_ld_ret.writeAction("yield")
        # full cache line send
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}: subi {REG_TMP1} {REG_TMP1} {64 // cls.ENTRY_SIZE}")
        tran_key_ld_ret.writeAction(f"addi {REG_TMP3} {REG_TMP3} {64}")
        # send done
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_done'}: yield")

    @classmethod
    def get(cls, tran: EFAProgram.Transition, ret: int, tmp_reg0: str, tmp_reg1: str, desc_lm_offset_reg: str, key_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_label_get, ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=desc_lm_offset_reg, arg_reg1=key_reg, branch_label=branch_label)

    @classmethod
    def get_wcont(cls, tran: EFAProgram.Transition, ret: str, tmp_reg: str, desc_lm_offset_reg: str, key_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_label_get, cont_reg=ret, tmp_reg=tmp_reg, arg_reg0=desc_lm_offset_reg, arg_reg1=key_reg, branch_label=branch_label)

    @classmethod
    def _delete(cls, state: EFAProgram.State):
        """
        """
        pass

    @classmethod
    def _get_next(cls, state: EFAProgram.State):
        """
        X8 - NWID[0:31] | BUCKET_DESC_LM_OFFSET[32:63]
        X9 - CUR_POSITION
        Returns:
            X8 - NWID[0:31] | BUCKET_DESC_LM_OFFSET[32:63]
            X9  - CUR_POSITION - set to -1 if reached end, set to -2 if passed end
            X10 - KEY - omit if passed end
            X11 - VAL - omit if passed end
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._get_next.__name__

        OB_NWID__BUCEKT_DESC_LM_OFFSET = "X8"
        OB_CUR_POSITION = "X9"

        REG_BUCKET_DESC_LM_ADDR = "X16"
        REG_TMP_BUF_LM_ADDR = "X17"
        REG_TMP0 = "X18"
        REG_TMP1 = "X19"
        REG_TMP2 = "X20"
        REG_TMP3 = "X21"
        REG_NWID__BUCEKT_DESC_LM_OFFSET = "X22"

        REG_CONT = "X31"

        tran = cls.tran_get_next
        if tran is None:
            return
        cls.tran_label_get_next = tran.getLabel()
        tran_entry_ld_ret = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-entry_ld_ret")

        tran.writeAction(f"rshift {OB_NWID__BUCEKT_DESC_LM_OFFSET} {REG_BUCKET_DESC_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_BUCKET_DESC_LM_ADDR} {'X7'} {REG_BUCKET_DESC_LM_ADDR}")
        tran.writeAction(f"addi {OB_CUR_POSITION} {REG_TMP0} {0}")  # REG_TMP0 => CUR_POSITION

        tran.writeAction(f"move {cls.DESC_STURCT_OFF_LM_BUF_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP_BUF_LM_ADDR} 0 8")  # REG_TMP_BUF_LM_ADDR => lm_buf_addr
        tran.writeAction(f"move {cls.DESC_STURCT_OFF_ENTRY_COUNT}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP1} 0 8")  # REG_TMP1 => num_entries
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME}: X8 = %lu, X9 = %lu, TMP_BUF_LM_ADDR = 0x%lx, num_entries = %lu' {'X0'} {OB_NWID__BUCEKT_DESC_LM_OFFSET} {OB_CUR_POSITION} {REG_TMP_BUF_LM_ADDR} {REG_TMP1}")
        tran.writeAction(f"bleu {REG_TMP1} {REG_TMP0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-passed_end'}")  # use unsigned comparison, the negative value is larger than the positive value
        tran.writeAction(f"move {cls.DESC_STURCT_OFF_DRAM_ALLOC_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP2} 0 8")  # REG_TMP2 => dram_alloc_start_addr
        tran.writeAction(f"lshift {REG_TMP0} {REG_TMP3} {int(math.log2(cls.ENTRY_SIZE))}")  # REG_TMP0 => entry_offset
        tran.writeAction(f"add {REG_TMP2} {REG_TMP3} {REG_TMP2}")  # REG_TMP2 => dram_addr
        sht_macros.dram_read_ret(tran=tran, addr_reg=REG_TMP2, ret_tran_label=tran_entry_ld_ret.getLabel(), tmp_reg=REG_TMP3, arg_lm_words=cls.ENTRY_SIZE // 8)
        tran.writeAction(f"addi {'X1'} {REG_CONT} {0}")  # save cont
        tran.writeAction(f"addi {OB_NWID__BUCEKT_DESC_LM_OFFSET} {REG_NWID__BUCEKT_DESC_LM_OFFSET} {0}")  # save X8, LM_BUF is lane shared, cannot use across activations
        tran.writeAction("yield")

        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-passed_end'}: mov_imm2reg {REG_TMP3} {-2}")
        sht_macros.return_wreg(tran=tran, cont_reg='X1', tmp_reg=REG_TMP0, arg_reg0=OB_NWID__BUCEKT_DESC_LM_OFFSET, arg_reg1=REG_TMP3)
        tran.writeAction("yield_terminate")

        tran_entry_ld_ret.writeAction(f"move {REG_NWID__BUCEKT_DESC_LM_OFFSET} {cls.WORD_SIZE * 0}({REG_TMP_BUF_LM_ADDR}) 0 8")
        tran_entry_ld_ret.writeAction(f"move {'X8'} {cls.WORD_SIZE * 2}({REG_TMP_BUF_LM_ADDR}) 0 8")
        tran_entry_ld_ret.writeAction(f"move {'X9'} {cls.WORD_SIZE * 3}({REG_TMP_BUF_LM_ADDR}) 0 8")
        tran_entry_ld_ret.writeAction(f"addi {REG_TMP0} {REG_TMP0} {1}")
        tran_entry_ld_ret.writeAction(f"move {REG_TMP0} {cls.WORD_SIZE * 1}({REG_TMP_BUF_LM_ADDR}) 0 8")

        tran_entry_ld_ret.writeAction(f"bge {REG_TMP0} {REG_TMP1} {f'{CLS_NAME}-{FN_NAME}-TR-entry_ld_ret-LB-reached_end'}")
        sht_macros.return_wlm(tran=tran_entry_ld_ret, cont_reg=REG_CONT, tmp_reg=REG_TMP2, arg_lm_addr_reg=REG_TMP_BUF_LM_ADDR, arg_lm_words=4)
        tran_entry_ld_ret.writeAction("yield_terminate")

        tran_entry_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-entry_ld_ret-LB-reached_end'}: mov_imm2reg {REG_TMP3} {-1}")
        tran_entry_ld_ret.writeAction(f"move {REG_TMP3} {cls.WORD_SIZE * 1}({REG_TMP_BUF_LM_ADDR}) 0 8")
        sht_macros.return_wlm(tran=tran_entry_ld_ret, cont_reg=REG_CONT, tmp_reg=REG_TMP2, arg_lm_addr_reg=REG_TMP_BUF_LM_ADDR, arg_lm_words=4)
        tran_entry_ld_ret.writeAction("yield_terminate")

    @classmethod
    def get_next(cls, tran: EFAProgram.Transition, ret: int, tmp_reg0: str, tmp_reg1: str, iter_word0_reg: str, iter_word1_reg: str, dst_nwid_reg: str = 'X0'):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_label_get_next, ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=iter_word0_reg, arg_reg1=iter_word1_reg)

    @classmethod
    def get_next_wcont(cls, tran: EFAProgram.Transition, ret: str, tmp_reg: str, iter_word0_reg: str, iter_word1_reg: str, dst_nwid_reg: str = 'X0'):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_label_get_next, cont_reg=ret, tmp_reg=tmp_reg, arg_reg0=iter_word0_reg, arg_reg1=iter_word1_reg)

    @classmethod
    def _get_next_split(cls, state: EFAProgram.State):
        """
        X8 - NWID[0:31] | BUCKET_DESC_LM_OFFSET[32:63]
        X9 - CUR_POSITION
        X10 - (KEY, VAL) CONTINUATION
        Returns (with default continuation):
            X8 - NWID[0:31] | BUCKET_DESC_LM_OFFSET[32:63]
            X9 - CUR_POSITION - set to -1 if reached end, set to -2 if passed end
        Returns (with (KEY, VAL) continuation): - omit if passed end
            X8 - KEY
            X9 - VAL
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._get_next_split.__name__

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_get_next_split
        if tran is None:
            return
        cls.tran_label_get_next_split = tran.getLabel()
        tran_entry_ld_ret = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-entry_ld_ret")

        """******************** THREAD - get_next_split ********************"""
        REG_BUCKET_DESC_LM_ADDR = "X16"
        REG_TMP0 = "X17"
        REG_TMP1 = "X18"
        REG_TMP2 = "X19"
        REG_TMP3 = "X20"

        REG_KEY_VAL_CONT = "X31"

        """==================== TRAN - ENTRY ===================="""
        OB_NWID__BUCEKT_DESC_LM_OFFSET = "X8"
        OB_CUR_POSITION = "X9"
        OB_KEY_VAL_CONT = "X10"

        tran.writeAction(f"sri {OB_NWID__BUCEKT_DESC_LM_OFFSET} {REG_BUCKET_DESC_LM_ADDR} {32}")
        tran.writeAction(f"add {REG_BUCKET_DESC_LM_ADDR} {'X7'} {REG_BUCKET_DESC_LM_ADDR}")
        tran.writeAction(f"addi {OB_CUR_POSITION} {REG_TMP0} {0}")  # REG_TMP0 => CUR_POSITION

        tran.writeAction(f"movlr {cls.DESC_STURCT_OFF_ENTRY_COUNT}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP1} 0 8")  # REG_TMP1 => num_entries
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %lu][{CLS_NAME}] {FN_NAME}: X8 = %lu, X9 = %lu, num_entries = %lu' {'X0'} {OB_NWID__BUCEKT_DESC_LM_OFFSET} {OB_CUR_POSITION} {REG_TMP1}")

        tran.writeAction(f"bleu {REG_TMP1} {REG_TMP0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-passed_end'}")  # use unsigned comparison, the negative value is larger than the positive value

        # -> not passed end
        tran.writeAction(f"movlr {cls.DESC_STURCT_OFF_DRAM_ALLOC_START_ADDR}({REG_BUCKET_DESC_LM_ADDR}) {REG_TMP2} 0 8")  # REG_TMP2 => dram_alloc_start_addr
        tran.writeAction(f"sli {REG_TMP0} {REG_TMP3} {int(math.log2(cls.ENTRY_SIZE))}")  # REG_TMP0 => entry_offset
        tran.writeAction(f"add {REG_TMP2} {REG_TMP3} {REG_TMP2}")  # REG_TMP2 => dram_addr
        sht_macros.dram_read_ret(tran=tran, addr_reg=REG_TMP2, ret_tran_label=tran_entry_ld_ret.getLabel(), tmp_reg=REG_TMP3, arg_lm_words=cls.ENTRY_SIZE // 8)
        tran.writeAction(f"addi {OB_KEY_VAL_CONT} {REG_KEY_VAL_CONT} {0}")  # save cont
        tran.writeAction(f"bne {REG_TMP1} {REG_TMP0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-not_reached_end'}")  # check if reached end
        tran.writeAction(f"movir {REG_TMP0} {-1}")
        sht_macros.return_wreg(tran=tran, cont_reg='X1', tmp_reg=REG_TMP3, arg_reg0=OB_NWID__BUCEKT_DESC_LM_OFFSET, arg_reg1=REG_TMP0)
        tran.writeAction("yield")
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-not_reached_end'}: addi {REG_TMP0} {REG_TMP0} {1}")
        sht_macros.return_wreg(tran=tran, cont_reg='X1', tmp_reg=REG_TMP3, arg_reg0=OB_NWID__BUCEKT_DESC_LM_OFFSET, arg_reg1=REG_TMP0)
        tran.writeAction("yield")

        # -> passed end
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-passed_end'}: movir {REG_TMP3} {-2}")
        sht_macros.return_wreg(tran=tran, cont_reg='X1', tmp_reg=REG_TMP2, arg_reg0=OB_NWID__BUCEKT_DESC_LM_OFFSET, arg_reg1=REG_TMP3)
        tran.writeAction("yieldt")

        """==================== TRAN - entry ld return ===================="""
        OB_KEY = "X8"
        OB_VAL = "X9"

        # TODO: may skip this sync and let dram load directly return to the continuation
        sht_macros.return_wreg(tran=tran_entry_ld_ret, cont_reg=REG_KEY_VAL_CONT, tmp_reg=REG_TMP3, arg_reg0=OB_KEY, arg_reg1=OB_VAL)
        tran_entry_ld_ret.writeAction("yieldt")

    @classmethod
    def get_next_split(cls, tran: EFAProgram.Transition, ret: int, tmp_reg0: str, tmp_reg1: str, iter_word0_reg: str, iter_word1_reg: str, key_val_cont_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_label_get_next_split, ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=iter_word0_reg, arg_reg1=iter_word1_reg, arg_reg2=key_val_cont_reg, branch_label=branch_label)

    @classmethod
    def get_next_split_wcont(cls, tran: EFAProgram.Transition, ret: str, tmp_reg: str, iter_word0_reg: str, iter_word1_reg: str, key_val_cont_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_label_get_next_split, cont_reg=ret, tmp_reg=tmp_reg, arg_reg0=iter_word0_reg, arg_reg1=iter_word1_reg, arg_reg2=key_val_cont_reg, branch_label=branch_label)
