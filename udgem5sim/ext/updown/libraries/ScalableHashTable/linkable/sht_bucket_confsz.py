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
        WORD value_words;
        WORD dram_value_start_addr;
    }
    """

    DESC_SIZE = 7 * 8

    DESC_STURCT_OFF_LOCK = 0
    DESC_STURCT_OFF_DRAM_ALLOC_START_ADDR = 8
    DESC_STURCT_OFF_NUM_ALLOC_ENTRIES = 16
    DESC_STURCT_OFF_ENTRY_COUNT = 24
    DESC_STURCT_OFF_LM_BUF_ADDR = 32
    DESC_STURCT_OFF_VALUE_WORDS = 40
    DESC_STURCT_OFF_DRAM_VALUE_START_ADDR = 48

    WORD_SIZE = 8
    KEY_SIZE = 8

    LM_BUF_SIZE = 64

    @classmethod
    def setup(cls, state: EFAProgram.State, debug=False) -> None:
        cls.DEBUG = debug
        cls.lock = sht_macros.MRSWLock(atomic=False, debug=debug)
        # cls.lock = sht_macros.MRSWLock(atomic=True, debug=debug)  # remove locks for experiemnt

        # TODO: code injection
        cls._initialize(state)
        cls._update(state)
        cls._get(state)
        # cls._delete(state)

    @classmethod
    def _initialize(cls, state: EFAProgram.State):
        """
        X8 - desc_lm_offset
        X9 - dram_alloc_start_addr
        X10 - num_entries
        X11 - value_size
        X12 - lm_buf_addr
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._initialize.__name__

        OB_DESC_LM_OFFSET = "X8"
        OB_DRAM_ALLOC_START_ADDR = "X9"
        OB_ALLOC_ENTRIES = "X10"
        OB_VAL_WORDS = "X11"
        OB_LM_BUF_OFFSET = "X12"

        REG_DESC_LM_ADDR = "X16"
        REG_TMP0 = "X17"
        REG_TMP1 = "X18"

        tran = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR")
        if tran is None:
            return
        cls.tran_label_init = tran.getLabel()

        # ===== TRAN - init entry =====
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] INIT: start' {'X0'}")
        # calc desc lm addr
        tran.writeAction(f"add {OB_DESC_LM_OFFSET} {'X7'} {REG_DESC_LM_ADDR}")
        # init lock
        tran.writeAction(f"addi {REG_DESC_LM_ADDR} {REG_TMP0} {cls.DESC_STURCT_OFF_LOCK}")
        cls.lock.init(tran, REG_TMP0, REG_TMP1)

        # ----- init descriptor -----
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
        # entry words
        tran.writeAction(f"move {OB_VAL_WORDS} {cls.DESC_STURCT_OFF_VALUE_WORDS}({REG_DESC_LM_ADDR}) 0 8")
        # dram value start addr
        tran.writeAction(f"lshift {OB_ALLOC_ENTRIES} {REG_TMP1} {int(math.log2(cls.WORD_SIZE))}")
        tran.writeAction(f"add {OB_DRAM_ALLOC_START_ADDR} {REG_TMP1} {REG_TMP1}")
        tran.writeAction(f"addi {REG_TMP1} {REG_TMP1} {64}")  # TODO: this is a hack to avoid overwriting the first value when storing last key
        tran.writeAction(f"move {REG_TMP1} {cls.DESC_STURCT_OFF_DRAM_VALUE_START_ADDR}({REG_DESC_LM_ADDR}) 0 8")

        # ----- return -----
        sht_macros.return_wreg(tran, 'X1', "X0", "X0")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] INIT: done' {'X0'}")
        tran.writeAction("yield_terminate")

    @classmethod
    def initialize(cls, tran: EFAProgram.Transition, ret: int, tmp_reg0: str, arg_lm_addr_reg: str, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_label_init, ret_tran_label=ret, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=5)

    @classmethod
    def initialize_wcont(cls, tran: EFAProgram.Transition, ret: str, tmp_reg0: str, arg_lm_addr_reg: str, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_label_init, cont_reg=ret, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=5)

    @classmethod
    def _update(cls, state: EFAProgram.State):
        """
        X8 - desc_lm_offset
        X9 - key
        X10 ~ X15 - Elem e
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
        REG_LD_CONCURRENCY = "X20"
        REG_KEY_WR_ADDR = "X21"
        REG_VAL_WR_ADDR = "X22"
        REG_ST_CONCURRENCY = "X23"
        REG_NUM_VAL_OP = "X24"  # number of value operations
        REG_LAST_LOAD_EFFECTIVE_WORDS = "X25"
        REG_LAST_LOAD_ADDR = "X26"

        REG_DESC_LM_ADDR = "X28"
        REG_BUF_LM_ADDR = "X29"
        REG_KEY = "X30"

        REG_CONT = "X31"

        tran = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR")
        if tran is None:
            return
        cls.tran_label_update = tran.getLabel()
        tran_key_ld_ret = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-key_ld_ret")
        tran_key_st_ret = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-key_st_ret")

        # ===== TRAN - function entry =====
        # calc desc lm addr
        tran.writeAction(f"add {OB_DESC_LM_OFFSET} {'X7'} {REG_DESC_LM_ADDR}")
        # get lock
        tran.writeAction(f"addi {REG_DESC_LM_ADDR} {REG_LOCK_LM_ADDR} {cls.DESC_STURCT_OFF_LOCK}")
        cls.lock.write_begin_var(tran, REG_LOCK_LM_ADDR, REG_TMP1)
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: lock admitted, TID = %d' {'X0'} {'TID'}")
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: DESC_LM_ADDR = 0x%x' {'X0'} {REG_DESC_LM_ADDR}")

        # copy ob regs
        tran.writeAction(f"mov_reg2reg {OB_KEY} {REG_KEY}")
        # save cont
        tran.writeAction(f"mov_reg2reg {'X1'} {REG_CONT}")

        # load desc
        tran.writeAction(f"move {cls.DESC_STURCT_OFF_LM_BUF_ADDR}({REG_DESC_LM_ADDR}) {REG_BUF_LM_ADDR} 0 8")

        # extract num_elem_op
        # since there is an offset of 2 in the encoding, the desc & key counts are skipped
        tran.writeAction(f"rshift_and_imm {'X2'} {REG_NUM_VAL_OP} {20} {0b111}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: number of val operands = %d' {'X0'} {REG_NUM_VAL_OP}")
        # copy val to buffer
        tran.writeAction(f"bcopy_ops {OB_VAL} {REG_BUF_LM_ADDR} {REG_NUM_VAL_OP}")

        tran.writeAction(f"move {cls.DESC_STURCT_OFF_ENTRY_COUNT}({REG_DESC_LM_ADDR}) {REG_TMP1} 0 8")  # tmp1 => entry_count

        # ----- if entry count is zero, write directly -----
        tran.writeAction(f"bgti {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-setup_send_ld'}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: empty bucket, writing without search' {'X0'}")
        # update entry count
        tran.writeAction(f"addi {REG_TMP1} {REG_TMP1} {1}")
        tran.writeAction(f"move {REG_TMP1} {cls.DESC_STURCT_OFF_ENTRY_COUNT}({REG_DESC_LM_ADDR}) 0 8")

        tran.writeAction(f"mov_imm2reg {REG_LD_CONCURRENCY} {0}")
        tran.writeAction(f"mov_imm2reg {REG_ST_CONCURRENCY} {2}")
        tran.writeAction(f"move {cls.DESC_STURCT_OFF_DRAM_ALLOC_START_ADDR}({REG_DESC_LM_ADDR}) {REG_KEY_WR_ADDR} 0 8")
        tran.writeAction(f"move {cls.DESC_STURCT_OFF_DRAM_VALUE_START_ADDR}({REG_DESC_LM_ADDR}) {REG_VAL_WR_ADDR} 0 8")
        tran.writeAction(f"sendr_dmlm_wret {REG_KEY_WR_ADDR} {tran_key_st_ret.getLabel()} {REG_KEY} {REG_KEY}")
        # calling with the proper number of operands
        for i in range(1, 6):
            tran.writeAction(f"beqi {REG_NUM_VAL_OP} {i} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_val_{i}'}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: shouldn't reach here!' {'X0'}")
        for i in range(1, 6):
            tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_val_{i}'}: send_dmlm_wret {REG_VAL_WR_ADDR} {tran_key_st_ret.getLabel()} {REG_BUF_LM_ADDR} {i}")
            if cls.DEBUG:
                tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: writing {i} words value' {'X0'}")
            tran.writeAction("yield")

        # ----- already have entires, send load entries -----
        # init
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-setup_send_ld'}: move {cls.DESC_STURCT_OFF_DRAM_ALLOC_START_ADDR}({REG_DESC_LM_ADDR}) {REG_LAST_LOAD_ADDR} 0 8")  # tmp3 => key load start address
        tran.writeAction(f"mov_imm2reg {REG_LD_CONCURRENCY} {0}")
        tran.writeAction(f"mov_imm2reg {REG_ST_CONCURRENCY} {-1}")

        tran.writeAction(f"blei {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_done'}")  # tmp1 => entry_count
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_ld'}: send_dmlm_ld_wret {REG_LAST_LOAD_ADDR} {tran_key_ld_ret.getLabel()} {8}")
        tran.writeAction(f"addi {REG_LD_CONCURRENCY} {REG_LD_CONCURRENCY} {1}")  # concurrency++
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: loading, DRAM addr = 0x%x' {'X0'} {REG_LAST_LOAD_ADDR}")
        # check if number of valid entries in the send is greater than 8
        tran.writeAction(f"bgti {REG_TMP1} {64 // cls.KEY_SIZE} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}")
        # last send, retain last send addr & valid size
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: all loads sent' {'X0'}")
        tran.writeAction(f"mov_reg2reg {REG_TMP1} {REG_LAST_LOAD_EFFECTIVE_WORDS}")  # record last load effective size
        tran.writeAction("yield")
        # full 8 word send
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}: subi {REG_TMP1} {REG_TMP1} {64 // cls.KEY_SIZE}")
        tran.writeAction(f"addi {REG_LAST_LOAD_ADDR} {REG_LAST_LOAD_ADDR} {64}")
        tran.writeAction(f"bgti {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_ld'}")
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_done'}: yield")

        # ===== TRAN - load key return =====
        OB_LD_RET_ADDR = "X3"

        # ----- synchronize all loads -----
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: load from 0x%x returns, mlp = %d' {'X0'} {OB_LD_RET_ADDR} {REG_LD_CONCURRENCY}")
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
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: last in-flight load & store finished, terminating... TID = %d' {'X0'} {'TID'}")
        # unlocked already, no need to unlock
        tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_TMP1} {1}")
        sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, REG_TMP1, REG_KEY, REG_VAL_WR_ADDR)
        tran_key_ld_ret.writeAction("yield_terminate")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}: yield")

        # ----- Check return -----
        # check if return is matched with (last) send address
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}: bne {OB_LD_RET_ADDR} {REG_LAST_LOAD_ADDR} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{7 * cls.KEY_SIZE}'}")  # tmp3 => last send addr
        # if it is the last send, branch to check only the valid entries
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: tail send load returns, num entries = %d' {'X0'} {REG_LAST_LOAD_EFFECTIVE_WORDS}")  # tmp2 => last send num valid entries
        for i in range(8, 0, -1):
            tran_key_ld_ret.writeAction(f"beqi {REG_LAST_LOAD_EFFECTIVE_WORDS} {i} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}'}")
        # match return data
        for i in range(8, 0, -1):
            tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}'}: beq {f'X{i + 8 - 1}'} {REG_KEY} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}_match'}")

        # => not matched (fall through)
        # if not the last send came back (check concurrency counter), yield wait
        # if mlp is 0, finished, need to write entry & terminate
        tran_key_ld_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait_ld'}")
        # from here, all in-flight loads are done & no match found
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: no matched entry found' {'X0'}")
        # check if there is space at the end of the allocation area
        tran_key_ld_ret.writeAction(f"move {cls.DESC_STURCT_OFF_NUM_ALLOC_ENTRIES}({REG_DESC_LM_ADDR}) {REG_TMP1} 0 8")  # REG_TMP1 => num_alloc_entries
        tran_key_ld_ret.writeAction(f"move {cls.DESC_STURCT_OFF_ENTRY_COUNT}({REG_DESC_LM_ADDR}) {REG_TMP2} 0 8")  # REG_TMP2 => entry count
        tran_key_ld_ret.writeAction(f"blt {REG_TMP2} {REG_TMP1} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-new_entry'}")
        # -> out of space!
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: bucket full, add FAILED!' {'X0'}")
        tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_TMP1} {0}")  # indicate failue
        sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, REG_TMP1, REG_KEY, REG_TMP2)
        # sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, 'X0', REG_TMP3)  # for debug
        cls.lock.write_end(tran_key_ld_ret, REG_LOCK_LM_ADDR, REG_TMP1)
        tran_key_ld_ret.writeAction("yield_terminate")  # only if running out of space!
        # -> new entry
        # calculate the address of the key
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-new_entry'}: move {cls.DESC_STURCT_OFF_DRAM_ALLOC_START_ADDR}({REG_DESC_LM_ADDR}) {REG_KEY_WR_ADDR} 0 8")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: storing in a new entry' {'X0'}")
        tran_key_ld_ret.writeAction(f"lshift {REG_TMP2} {REG_TMP1} {int(math.log2(cls.KEY_SIZE))}")
        tran_key_ld_ret.writeAction(f"add {REG_KEY_WR_ADDR} {REG_TMP1} {REG_KEY_WR_ADDR}")
        # store key
        tran_key_ld_ret.writeAction(f"sendr_dmlm_wret {REG_KEY_WR_ADDR} {tran_key_st_ret.getLabel()} {REG_KEY} {REG_KEY}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: sending key write to addr = 0x%x' {'X0'} {REG_VAL_WR_ADDR}")
        # calculate the address of the value
        tran_key_ld_ret.writeAction(f"move {cls.DESC_STURCT_OFF_DRAM_VALUE_START_ADDR}({REG_DESC_LM_ADDR}) {REG_VAL_WR_ADDR} 0 8")
        tran_key_ld_ret.writeAction(f"move {cls.DESC_STURCT_OFF_VALUE_WORDS}({REG_DESC_LM_ADDR}) {REG_TMP1} 0 8")
        tran_key_ld_ret.writeAction(f"mul {REG_TMP2} {REG_TMP1} {REG_TMP1}")
        tran_key_ld_ret.writeAction(f"lshift {REG_TMP1} {REG_TMP1} {int(math.log2(cls.WORD_SIZE))}")
        tran_key_ld_ret.writeAction(f"add {REG_VAL_WR_ADDR} {REG_TMP1} {REG_VAL_WR_ADDR}")
        # store value
        # calling with the proper number of operands
        for i in range(1, 6):
            tran_key_ld_ret.writeAction(f"beqi {REG_NUM_VAL_OP} {i} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-nomatch_send_val_{i}'}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: shouldn't reach here!' {'X0'}")
        for i in range(1, 6):
            tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-nomatch_send_val_{i}'}: send_dmlm_wret {REG_VAL_WR_ADDR} {tran_key_st_ret.getLabel()} {REG_BUF_LM_ADDR} {i}")
            if cls.DEBUG:
                tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: writing {i} words value' {'X0'}")
            tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-nomatch_send_val_done'}")
        # count up the entries
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-nomatch_send_val_done'}: addi {REG_TMP2} {REG_TMP2} {1}")
        tran_key_ld_ret.writeAction(f"move {REG_TMP2} {cls.DESC_STURCT_OFF_ENTRY_COUNT}({REG_DESC_LM_ADDR}) 0 8")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: sending value write to addr = 0x%x' {'X0'} {REG_VAL_WR_ADDR}")
        tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_ST_CONCURRENCY} {2}")  # mark value written & all loads done
        # -> wait for in-flight load to come back
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait_ld'}: yield")

        # => matched
        for i in range(0, 8):
            # calculate the entry index from key address
            tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{i * cls.KEY_SIZE}_match'}: move {cls.DESC_STURCT_OFF_DRAM_ALLOC_START_ADDR}({REG_DESC_LM_ADDR}) {REG_TMP1} 0 8")
            if cls.DEBUG:
                tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: matched at word offset {i}' {'X0'}")
            tran_key_ld_ret.writeAction(f"sub {OB_LD_RET_ADDR} {REG_TMP1} {REG_TMP1}")
            tran_key_ld_ret.writeAction(f"rshift {REG_TMP1} {REG_TMP1} {int(math.log2(cls.KEY_SIZE))}")
            tran_key_ld_ret.writeAction(f"addi {REG_TMP1} {REG_TMP1} {i}")  # REG_TMP1 => entry index
            tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_st'}")

        # ----- Send store value -----
        # calculate value address
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_st'}: move {cls.DESC_STURCT_OFF_DRAM_VALUE_START_ADDR}({REG_DESC_LM_ADDR}) {REG_VAL_WR_ADDR} 0 8")
        tran_key_ld_ret.writeAction(f"move {cls.DESC_STURCT_OFF_VALUE_WORDS}({REG_DESC_LM_ADDR}) {REG_TMP2} 0 8")
        tran_key_ld_ret.writeAction(f"mul {REG_TMP2} {REG_TMP1} {REG_TMP1}")
        tran_key_ld_ret.writeAction(f"lshift {REG_TMP1} {REG_TMP1} {int(math.log2(cls.WORD_SIZE))}")
        tran_key_ld_ret.writeAction(f"add {REG_VAL_WR_ADDR} {REG_TMP1} {REG_VAL_WR_ADDR}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: sending write to addr = 0x%x' {'X0'} {REG_VAL_WR_ADDR}")
        # calling with the proper number of operands
        for i in range(1, 6):
            tran_key_ld_ret.writeAction(f"beqi {REG_NUM_VAL_OP} {i} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_{i}'}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: shouldn't reach here!' {'X0'}")
        for i in range(1, 6):
            tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_{i}'}: send_dmlm_wret {REG_VAL_WR_ADDR} {tran_key_st_ret.getLabel()} {REG_BUF_LM_ADDR} {i}")
            if cls.DEBUG:
                tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: writing {i} words value' {'X0'}")
            tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_done'}")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_done'}: mov_imm2reg {REG_ST_CONCURRENCY} {1}")  # mark value written
        tran_key_ld_ret.writeAction("yield")

        # ===== TRAN - store key val =====
        tran_key_st_ret.writeAction(f"subi {REG_ST_CONCURRENCY} {REG_ST_CONCURRENCY} {1}")
        tran_key_st_ret.writeAction(f"bgti {REG_ST_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_st_ret-LB-wait'}")
        tran_key_st_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_st_ret-LB-ld_wait'}")
        if cls.DEBUG:
            tran_key_st_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: write to 0x%x returns & no load waiting, terminating... TID = %d' {'X0'} {'X8'} {'TID'}")
        cls.lock.write_end(tran_key_st_ret, REG_LOCK_LM_ADDR, REG_TMP1)
        tran_key_st_ret.writeAction(f"mov_imm2reg {REG_TMP1} {1}")
        sht_macros.return_wreg(tran_key_st_ret, REG_CONT, REG_TMP1, REG_KEY, REG_VAL_WR_ADDR)
        # sht_macros.return_wreg(tran_key_st_ret, REG_CONT, 'X0', REG_VAL_WR_ADDR)  # debug
        tran_key_st_ret.writeAction("yield_terminate")
        tran_key_st_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_st_ret-LB-ld_wait'}: addi {REG_TMP1} {REG_TMP1} {0}")  # dummy instruction
        cls.lock.write_end(tran_key_st_ret, REG_LOCK_LM_ADDR, REG_TMP1)
        if cls.DEBUG:
            tran_key_st_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] UPDATE: write to 0x%x returns & all stores done, waiting loads return...' {'X0'} {'X8'}")
        tran_key_st_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_st_ret-LB-wait'}: yield")

    @classmethod
    def update(cls, tran: EFAProgram.Transition, ret: int, tmp_reg0: str, arg_lm_addr_reg: str, arg_lm_words: int, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_label_update, ret_tran_label=ret, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=arg_lm_words)

    @classmethod
    def update_wcont(cls, tran: EFAProgram.Transition, ret: str, tmp_reg0: str, arg_lm_addr_reg: str, arg_lm_words: int, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_label_update, cont_reg=ret, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=arg_lm_words)

    @classmethod
    def _get(cls, state: EFAProgram.State):
        """
        X8 - desc_lm_offset
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
        REG_LD_CONCURRENCY = "X20"
        REG_VAL_RD_ADDR = "X22"
        REG_MATCH_STATUS = "X23"
        REG_NUM_VAL_WORDS = "X24"  # number of value operations
        REG_LAST_LOAD_EFFECTIVE_WORDS = "X25"
        REG_LAST_LOAD_ADDR = "X26"

        REG_DESC_LM_ADDR = "X28"
        REG_BUF_LM_ADDR = "X29"
        REG_KEY = "X30"

        REG_CONT = "X31"

        tran = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR")
        if tran is None:
            return
        cls.tran_label_get = tran.getLabel()
        tran_key_ld_ret = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-key_ld_ret")
        tran_val_ld_ret = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-val_ld_ret")

        # ===== TRAN - function entry =====
        # calc desc lm addr
        tran.writeAction(f"add {OB_DESC_LM_OFFSET} {'X7'} {REG_DESC_LM_ADDR}")
        # get lock
        tran.writeAction(f"addi {REG_DESC_LM_ADDR} {REG_LOCK_LM_ADDR} {cls.DESC_STURCT_OFF_LOCK}")
        cls.lock.read_begin(tran, REG_LOCK_LM_ADDR, REG_TMP1, 2)
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] GET: lock admitted, TID = %d' {'X0'} {'TID'}")
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] GET: DESC_LM_ADDR = 0x%x' {'X0'} {REG_DESC_LM_ADDR}")

        # copy ob regs
        tran.writeAction(f"mov_reg2reg {OB_KEY} {REG_KEY}")
        # save cont
        tran.writeAction(f"mov_reg2reg {'X1'} {REG_CONT}")

        # load desc
        tran.writeAction(f"move {cls.DESC_STURCT_OFF_LM_BUF_ADDR}({REG_DESC_LM_ADDR}) {REG_BUF_LM_ADDR} 0 8")
        tran.writeAction(f"move {cls.DESC_STURCT_OFF_VALUE_WORDS}({REG_DESC_LM_ADDR}) {REG_NUM_VAL_WORDS} 0 8")

        tran.writeAction(f"move {cls.DESC_STURCT_OFF_ENTRY_COUNT}({REG_DESC_LM_ADDR}) {REG_TMP1} 0 8")  # tmp1 => entry_count

        # ----- if entry count is zero, return not found -----
        tran.writeAction(f"bgti {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-setup_send_ld'}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] GET: empty bucket, return without search' {'X0'}")
        # tran.writeAction(f"mov_imm2reg {REG_TMP1} {0}")  # indicate failue
        sht_macros.return_wreg(tran, REG_CONT, REG_TMP1, REG_KEY)
        # sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, 'X0', REG_TMP3)  # for debug
        cls.lock.read_end(tran, REG_LOCK_LM_ADDR, REG_TMP1)
        tran.writeAction("yield_terminate")  # only if running out of space!

        # ----- already have entires, send load entries -----
        # init
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-setup_send_ld'}: move {cls.DESC_STURCT_OFF_DRAM_ALLOC_START_ADDR}({REG_DESC_LM_ADDR}) {REG_LAST_LOAD_ADDR} 0 8")  # tmp3 => key load start address
        tran.writeAction(f"mov_imm2reg {REG_LD_CONCURRENCY} {0}")
        tran.writeAction(f"mov_imm2reg {REG_MATCH_STATUS} {0}")

        tran.writeAction(f"blei {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_done'}")  # tmp1 => entry_count
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_ld'}: send_dmlm_ld_wret {REG_LAST_LOAD_ADDR} {tran_key_ld_ret.getLabel()} {8}")
        tran.writeAction(f"addi {REG_LD_CONCURRENCY} {REG_LD_CONCURRENCY} {1}")  # concurrency++
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] GET: loading, DRAM addr = 0x%x' {'X0'} {REG_LAST_LOAD_ADDR}")
        # check if number of valid entries in the send is greater than 8
        tran.writeAction(f"bgti {REG_TMP1} {64 // cls.KEY_SIZE} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}")
        # last send, retain last send addr & valid size
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] GET: all loads sent' {'X0'}")
        tran.writeAction(f"mov_reg2reg {REG_TMP1} {REG_LAST_LOAD_EFFECTIVE_WORDS}")  # record last load effective size
        tran.writeAction("yield")
        # full 8 word send
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}: subi {REG_TMP1} {REG_TMP1} {64 // cls.KEY_SIZE}")
        tran.writeAction(f"addi {REG_LAST_LOAD_ADDR} {REG_LAST_LOAD_ADDR} {64}")
        tran.writeAction(f"bgti {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_ld'}")
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_done'}: yield")

        # ===== TRAN - load key return =====
        OB_LD_RET_ADDR = "X3"

        # ----- synchronize all loads -----
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] GET: load from 0x%x returns, mlp = %d' {'X0'} {OB_LD_RET_ADDR} {REG_LD_CONCURRENCY}")
        tran_key_ld_ret.writeAction(f"subi {REG_LD_CONCURRENCY} {REG_LD_CONCURRENCY} {1}")
        # FIXME: need to wait the load value return processed before terminating
        tran_key_ld_ret.writeAction(f"beqi {REG_MATCH_STATUS} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}")
        tran_key_ld_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}")
        tran_key_ld_ret.writeAction(f"beqi {REG_MATCH_STATUS} {1} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] GET: last in-flight load key & value returned already, terminating... TID = %d' {'X0'} {'TID'}")
        # unlocked already, no need to unlock
        tran_key_ld_ret.writeAction("yield_terminate")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}: yield")

        # ----- Check return -----
        # check if return is matched with (last) send address
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}: bne {OB_LD_RET_ADDR} {REG_LAST_LOAD_ADDR} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{7 * cls.KEY_SIZE}'}")  # tmp3 => last send addr
        # if it is the last send, branch to check only the valid entries
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] GET: tail send load returns, num entries = %d' {'X0'} {REG_LAST_LOAD_EFFECTIVE_WORDS}")  # tmp2 => last send num valid entries
        for i in range(8, 0, -1):
            tran_key_ld_ret.writeAction(f"beqi {REG_LAST_LOAD_EFFECTIVE_WORDS} {i} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}'}")
        # match return data
        for i in range(8, 0, -1):
            tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}'}: beq {f'X{i + 8 - 1}'} {REG_KEY} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}_match'}")

        # => not matched (fall through)
        tran_key_ld_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait_ld'}")
        # from here, all in-flight loads are done & no match found
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] GET: no matched entry found' {'X0'}")
        tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_TMP1} {0}")  # indicate failue
        sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, REG_TMP1, REG_KEY)
        # sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, 'X0', REG_TMP3)  # for debug
        cls.lock.read_end(tran_key_ld_ret, REG_LOCK_LM_ADDR, REG_TMP1)
        tran_key_ld_ret.writeAction("yield_terminate")  # only if running out of space!

        # -> wait for in-flight load to come back
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait_ld'}: yield")

        # => matched
        for i in range(0, 8):
            # calculate the entry index from key address
            tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{i * cls.KEY_SIZE}_match'}: move {cls.DESC_STURCT_OFF_DRAM_ALLOC_START_ADDR}({REG_DESC_LM_ADDR}) {REG_TMP1} 0 8")
            if cls.DEBUG:
                tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] GET: matched at word offset {i}' {'X0'}")
            tran_key_ld_ret.writeAction(f"sub {OB_LD_RET_ADDR} {REG_TMP1} {REG_TMP1}")
            tran_key_ld_ret.writeAction(f"rshift {REG_TMP1} {REG_TMP1} {int(math.log2(cls.KEY_SIZE))}")
            tran_key_ld_ret.writeAction(f"addi {REG_TMP1} {REG_TMP1} {i}")  # REG_TMP1 => entry index
            tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_ld'}")

        # ----- Send load value -----
        # calculate value address
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_ld'}: move {cls.DESC_STURCT_OFF_DRAM_VALUE_START_ADDR}({REG_DESC_LM_ADDR}) {REG_VAL_RD_ADDR} 0 8")
        tran_key_ld_ret.writeAction(f"move {cls.DESC_STURCT_OFF_VALUE_WORDS}({REG_DESC_LM_ADDR}) {REG_TMP2} 0 8")
        tran_key_ld_ret.writeAction(f"mul {REG_TMP2} {REG_TMP1} {REG_TMP1}")
        tran_key_ld_ret.writeAction(f"lshift {REG_TMP1} {REG_TMP1} {int(math.log2(cls.WORD_SIZE))}")
        tran_key_ld_ret.writeAction(f"add {REG_VAL_RD_ADDR} {REG_TMP1} {REG_VAL_RD_ADDR}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] GET: sending load to addr = 0x%x' {'X0'} {REG_VAL_RD_ADDR}")

        # calling with the proper number of operands
        for i in range(1, 9):
            tran_key_ld_ret.writeAction(f"beqi {REG_NUM_VAL_WORDS} {i} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_{i}'}")
        tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_8'}")  # for value words > 8, load the first 8 words
        for i in range(1, 9):
            tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_{i}'}: send_dmlm_ld_wret {REG_VAL_RD_ADDR} {tran_val_ld_ret.getLabel()} {i}")
            if i <= 5:
                tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_TMP2} {i}")  # words to be copied
            else:
                tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_TMP2} {5}")  # words to be copied
            if cls.DEBUG:
                tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] GET: loading {i} words value' {'X0'}")
            tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_done'}")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_done'}: mov_imm2reg {REG_MATCH_STATUS} {1}")  # mark key found
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] GET: key found and value load issued' {'X0'}")
        tran_key_ld_ret.writeAction("yield")

        # ===== TRAN - load value return =====
        if cls.DEBUG:
            tran_val_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] GET: value load returns' {'X0'}")
        tran_val_ld_ret.writeAction(f"mov_imm2reg {REG_MATCH_STATUS} {2}")  # mark value returned
        cls.lock.read_end(tran_val_ld_ret, REG_LOCK_LM_ADDR, REG_TMP1)

        tran_val_ld_ret.writeAction(f"mov_imm2reg {REG_TMP1} {1}")  # indicate success
        tran_val_ld_ret.writeAction(f"move {REG_TMP1} 0({REG_BUF_LM_ADDR}) 0 8")  # status
        tran_val_ld_ret.writeAction(f"move {REG_KEY} 8({REG_BUF_LM_ADDR}) 0 8")  # key
        tran_val_ld_ret.writeAction(f"move {REG_VAL_RD_ADDR} 16({REG_BUF_LM_ADDR}) 0 8")  # value address
        tran_val_ld_ret.writeAction(f"addi {REG_BUF_LM_ADDR} {REG_TMP1} {cls.WORD_SIZE * 3}")
        tran_val_ld_ret.writeAction(f"bcopy_ops {'X8'} {REG_TMP1} {REG_TMP2}")

        for i in range(1, 6):
            tran_val_ld_ret.writeAction(f"beqi {REG_NUM_VAL_WORDS} {i} {f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-ret_val_{i}'}")
        tran_val_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-ret_val_5'}")  # for value words > 5, load the first 5 words
        for i in range(1, 6):
            tran_val_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-ret_val_{i}'}: addi {REG_TMP1} {REG_TMP1} {0}")  # FIXME: dummy
            sht_macros.return_wlm(tran_val_ld_ret, REG_CONT, REG_BUF_LM_ADDR, i + 3)
            tran_val_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-ret_val_done'}")

        tran_val_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-ret_val_done'}: bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-wait_after_ld_val'}")
        tran_val_ld_ret.writeAction("yield_terminate")
        tran_val_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-val_ld_ret-LB-wait_after_ld_val'}: yield")

    @classmethod
    def _get_fast(cls, state: EFAProgram.State):
        """
        X8 - desc_lm_offset
        X9 - key
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._get_fast.__name__

        OB_DESC_LM_OFFSET = "X8"
        OB_KEY = "X9"

        REG_LOCK_LM_ADDR = "X16"
        REG_TMP1 = "X17"
        REG_TMP2 = "X18"
        REG_TMP3 = "X19"
        REG_LD_CONCURRENCY = "X20"
        REG_VAL_RD_ADDR = "X22"
        REG_MATCH_STATUS = "X23"
        REG_NUM_VAL_WORDS = "X24"  # number of value operations
        REG_LAST_LOAD_EFFECTIVE_WORDS = "X25"
        REG_LAST_LOAD_ADDR = "X26"

        REG_DESC_LM_ADDR = "X28"
        # REG_BUF_LM_ADDR = "X29"
        REG_KEY = "X30"

        REG_CONT = "X31"

        tran = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR")
        if tran is None:
            return
        cls.tran_label_get = tran.getLabel()
        tran_key_ld_ret = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-key_ld_ret")

        # ===== TRAN - function entry =====
        # calc desc lm addr
        tran.writeAction(f"add {OB_DESC_LM_OFFSET} {'X7'} {REG_DESC_LM_ADDR}")
        # get lock
        tran.writeAction(f"addi {REG_DESC_LM_ADDR} {REG_LOCK_LM_ADDR} {cls.DESC_STURCT_OFF_LOCK}")
        cls.lock.read_begin(tran, REG_LOCK_LM_ADDR, REG_TMP1, 2)
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] GET: lock admitted, TID = %d' {'X0'} {'TID'}")
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] GET: DESC_LM_ADDR = 0x%x' {'X0'} {REG_DESC_LM_ADDR}")

        # copy ob regs
        tran.writeAction(f"mov_reg2reg {OB_KEY} {REG_KEY}")
        # save cont
        tran.writeAction(f"mov_reg2reg {'X1'} {REG_CONT}")

        # load desc
        # tran.writeAction(f"move {cls.DESC_STURCT_OFF_LM_BUF_ADDR}({REG_DESC_LM_ADDR}) {REG_BUF_LM_ADDR} 0 8")
        tran.writeAction(f"move {cls.DESC_STURCT_OFF_VALUE_WORDS}({REG_DESC_LM_ADDR}) {REG_NUM_VAL_WORDS} 0 8")

        tran.writeAction(f"move {cls.DESC_STURCT_OFF_ENTRY_COUNT}({REG_DESC_LM_ADDR}) {REG_TMP1} 0 8")  # tmp1 => entry_count

        # ----- if entry count is zero, return not found -----
        tran.writeAction(f"bgti {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-setup_send_ld'}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] GET: empty bucket, return without search' {'X0'}")
        # tran.writeAction(f"mov_imm2reg {REG_TMP1} {0}")  # indicate failue
        sht_macros.return_wreg(tran, REG_CONT, REG_TMP1, REG_KEY)
        # sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, 'X0', REG_TMP3)  # for debug
        cls.lock.read_end(tran, REG_LOCK_LM_ADDR, REG_TMP1)
        tran.writeAction("yield_terminate")  # only if running out of space!

        # ----- already have entires, send load entries -----
        # init
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-setup_send_ld'}: move {cls.DESC_STURCT_OFF_DRAM_ALLOC_START_ADDR}({REG_DESC_LM_ADDR}) {REG_LAST_LOAD_ADDR} 0 8")  # tmp3 => key load start address
        tran.writeAction(f"mov_imm2reg {REG_LD_CONCURRENCY} {0}")
        tran.writeAction(f"mov_imm2reg {REG_MATCH_STATUS} {0}")

        tran.writeAction(f"blei {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_done'}")  # tmp1 => entry_count
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_ld'}: send_dmlm_ld_wret {REG_LAST_LOAD_ADDR} {tran_key_ld_ret.getLabel()} {8}")
        tran.writeAction(f"addi {REG_LD_CONCURRENCY} {REG_LD_CONCURRENCY} {1}")  # concurrency++
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] GET: loading, DRAM addr = 0x%x' {'X0'} {REG_LAST_LOAD_ADDR}")
        # check if number of valid entries in the send is greater than 8
        tran.writeAction(f"bgti {REG_TMP1} {64 // cls.KEY_SIZE} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}")
        # last send, retain last send addr & valid size
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] GET: all loads sent' {'X0'}")
        tran.writeAction(f"mov_reg2reg {REG_TMP1} {REG_LAST_LOAD_EFFECTIVE_WORDS}")  # record last load effective size
        tran.writeAction("yield")
        # full 8 word send
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_full'}: subi {REG_TMP1} {REG_TMP1} {64 // cls.KEY_SIZE}")
        tran.writeAction(f"addi {REG_LAST_LOAD_ADDR} {REG_LAST_LOAD_ADDR} {64}")
        tran.writeAction(f"bgti {REG_TMP1} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-send_ld'}")
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-send_done'}: yield")

        # ===== TRAN - load key return =====
        OB_LD_RET_ADDR = "X3"

        # ----- synchronize all loads -----
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] GET: load from 0x%x returns, mlp = %d' {'X0'} {OB_LD_RET_ADDR} {REG_LD_CONCURRENCY}")
        tran_key_ld_ret.writeAction(f"subi {REG_LD_CONCURRENCY} {REG_LD_CONCURRENCY} {1}")
        tran_key_ld_ret.writeAction(f"beqi {REG_MATCH_STATUS} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}")
        tran_key_ld_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] GET: last in-flight load key & key found already, terminating... TID = %d' {'X0'} {'TID'}")
        # unlocked already, no need to unlock
        tran_key_ld_ret.writeAction("yield_terminate")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait'}: yield")

        # ----- Check return -----
        # check if return is matched with (last) send address
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-not_done'}: bne {OB_LD_RET_ADDR} {REG_LAST_LOAD_ADDR} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{7 * cls.KEY_SIZE}'}")  # tmp3 => last send addr
        # if it is the last send, branch to check only the valid entries
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] GET: tail send load returns, num entries = %d' {'X0'} {REG_LAST_LOAD_EFFECTIVE_WORDS}")  # tmp2 => last send num valid entries
        for i in range(8, 0, -1):
            tran_key_ld_ret.writeAction(f"beqi {REG_LAST_LOAD_EFFECTIVE_WORDS} {i} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}'}")
        # match return data
        for i in range(8, 0, -1):
            tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}'}: beq {f'X{i + 8 - 1}'} {REG_KEY} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{(i - 1) * cls.KEY_SIZE}_match'}")

        # => not matched (fall through)
        tran_key_ld_ret.writeAction(f"bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait_ld'}")
        # from here, all in-flight loads are done & no match found
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] GET: no matched entry found' {'X0'}")
        tran_key_ld_ret.writeAction(f"mov_imm2reg {REG_TMP1} {0}")  # indicate failue
        sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, REG_TMP1, REG_KEY)
        # sht_macros.return_wreg(tran_key_ld_ret, REG_CONT, 'X0', REG_TMP3)  # for debug
        cls.lock.read_end(tran_key_ld_ret, REG_LOCK_LM_ADDR, REG_TMP1)
        tran_key_ld_ret.writeAction("yield_terminate")  # only if running out of space!

        # -> wait for in-flight load to come back
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait_ld'}: yield")

        # => matched
        for i in range(0, 8):
            # calculate the entry index from key address
            tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-check_{i * cls.KEY_SIZE}_match'}: move {cls.DESC_STURCT_OFF_DRAM_ALLOC_START_ADDR}({REG_DESC_LM_ADDR}) {REG_TMP1} 0 8")
            if cls.DEBUG:
                tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] GET: matched at word offset {i}' {'X0'}")
            tran_key_ld_ret.writeAction(f"sub {OB_LD_RET_ADDR} {REG_TMP1} {REG_TMP1}")
            tran_key_ld_ret.writeAction(f"rshift {REG_TMP1} {REG_TMP1} {int(math.log2(cls.KEY_SIZE))}")
            tran_key_ld_ret.writeAction(f"addi {REG_TMP1} {REG_TMP1} {i}")  # REG_TMP1 => entry index
            tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_ld'}")

        # ----- Send load value -----
        # calculate value address
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-send_ld'}: move {cls.DESC_STURCT_OFF_DRAM_VALUE_START_ADDR}({REG_DESC_LM_ADDR}) {REG_VAL_RD_ADDR} 0 8")
        tran_key_ld_ret.writeAction(f"move {cls.DESC_STURCT_OFF_VALUE_WORDS}({REG_DESC_LM_ADDR}) {REG_TMP2} 0 8")
        tran_key_ld_ret.writeAction(f"mul {REG_TMP2} {REG_TMP1} {REG_TMP1}")
        tran_key_ld_ret.writeAction(f"lshift {REG_TMP1} {REG_TMP1} {int(math.log2(cls.WORD_SIZE))}")
        tran_key_ld_ret.writeAction(f"add {REG_VAL_RD_ADDR} {REG_TMP1} {REG_VAL_RD_ADDR}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] GET: sending load to addr = 0x%x' {'X0'} {REG_VAL_RD_ADDR}")

        # calling with the proper number of operands
        for i in range(1, 9):
            tran_key_ld_ret.writeAction(f"beqi {REG_NUM_VAL_WORDS} {i} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_{i}'}")
        tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_8'}")  # for value words > 8, load the first 8 words
        for i in range(1, 9):
            tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_{i}'}: send_dmlm_ld {REG_VAL_RD_ADDR} {REG_CONT} {i}")  # directly return to caller
            if cls.DEBUG:
                tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] GET: loading {i} words value' {'X0'}")
            tran_key_ld_ret.writeAction(f"jmp {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_done'}")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-match_send_val_done'}: bgti {REG_LD_CONCURRENCY} {0} {f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait_after_ld_val'}")
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] GET: key found, bucket terminating' {'X0'}")
        cls.lock.read_end(tran_key_ld_ret, REG_LOCK_LM_ADDR, REG_TMP1)
        tran_key_ld_ret.writeAction("yield_terminate")
        tran_key_ld_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-key_ld_ret-LB-wait_after_ld_val'}: mov_imm2reg {REG_MATCH_STATUS} {1}")  # mark key found
        if cls.DEBUG:
            tran_key_ld_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] GET: key found, wait for rest of key loads' {'X0'}")
        cls.lock.read_end(tran_key_ld_ret, REG_LOCK_LM_ADDR, REG_TMP1)
        tran_key_ld_ret.writeAction("yield")

    @classmethod
    def get(cls, tran: EFAProgram.Transition, ret: int, tmp_reg: str, desc_lm_offset_reg: str, key_reg: str, dst_nwid_reg: str = 'X0'):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_label_get, ret_tran_label=ret, tmp_reg=tmp_reg, arg_reg0=desc_lm_offset_reg, arg_reg1=key_reg)

    @classmethod
    def get_wcont(cls, tran: EFAProgram.Transition, ret: str, tmp_reg: str, desc_lm_offset_reg: str, key_reg: str, dst_nwid_reg: str = 'X0'):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_label_get, cont_reg=ret, tmp_reg=tmp_reg, arg_reg0=desc_lm_offset_reg, arg_reg1=key_reg)

    @classmethod
    def _delete(cls, state: EFAProgram.State):
        """
        """
        pass

    @classmethod
    def delete(cls, tran: EFAProgram.Transition):
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
