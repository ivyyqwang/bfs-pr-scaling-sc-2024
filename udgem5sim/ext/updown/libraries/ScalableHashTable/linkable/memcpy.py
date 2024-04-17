from linker.EFAProgram import efaProgram, EFAProgram
import sht_macros


@efaProgram
def MemcpyModule(efa):
    efa.code_level = 'machine'

    state0 = efa.State()
    efa.add_initId(state0.state_id)

    Memcpy.setup(state0, num_concurrent_sends=25, debug=False)

    return efa


class Memcpy:
    CONCURRENT_SENDS = 25
    DEBUG = False

    WORD_SIZE = 8

    @classmethod
    def setup(cls, state: EFAProgram.State, num_concurrent_sends: int = 25, debug: bool = False) -> None:
        cls.CONCURRENT_SENDS = num_concurrent_sends
        cls.DEBUG = debug

        CLS_NAME = cls.__name__
        cls.tran_memcpy = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-memcpy-TR")
        cls.tran_memcpy_dram2lm = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-memcpy_dram2lm-TR")

        cls._memcpy(state)
        cls._memcpy_dram2lm(state)

    @classmethod
    def memcpy(cls, tran: EFAProgram.Transition, ret_tran_label: int, tmp_reg0: str, tmp_reg1: str, src_dram_addr_reg: str, dst_dram_addr_reg: str, num_words_reg: str, dst_nwid_reg: str = 'X0'):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="Memcpy_memcpy_TR", ret_tran_label=ret_tran_label, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=src_dram_addr_reg, arg_reg1=dst_dram_addr_reg, arg_reg2=num_words_reg)

    @classmethod
    def memcpy_wcont(cls, tran: EFAProgram.Transition, cont_reg: str, tmp_reg: str, src_dram_addr_reg: str, dst_dram_addr_reg: str, num_words_reg: str, dst_nwid_reg: str = 'X0'):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="Memcpy_memcpy_TR", cont_reg=cont_reg, tmp_reg=tmp_reg, arg_reg0=src_dram_addr_reg, arg_reg1=dst_dram_addr_reg, arg_reg2=num_words_reg)

    @classmethod
    def _memcpy(cls, state: EFAProgram.State):
        """
        X8  - SRC_DRAM_ADDR
        X9  - DST_DRAM_ADDR
        X10 - NUM_WORDS
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._memcpy.__name__

        OB_SRC_DRAM_ADDR = "X8"
        OB_DST_DRAM_ADDR = "X9"
        OB_NUM_WORDS = "X10"

        REG_START_SRC_DRAM_ADDR = "X16"
        REG_START_DST_DRAM_ADDR = "X17"
        REG_CUR_SRC_DRAM_ADDR = "X18"
        REG_NUM_WORD_LEFT = "X19"
        REG_CONCURRENCY_CNT = "X20"
        REG_TMP0 = "X21"
        REG_TMP1 = "X22"
        REG_CONT = "X31"

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_memcpy
        if tran is None:
            return
        cls.tran_label_memcpy = tran.getLabel()
        tran_ld_ret = []
        for i in range(1, 9):
            tran_ld_ret.append(state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-ld_ret_{i}"))
        tran_st_ret = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-st_ret")

        """==================== TRAN - function entry ===================="""
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] SRC_DRAM_ADDR = %p, DST_DRAM_ADDR = %p, NUM_WORDS = %lu' {'X0'} {OB_SRC_DRAM_ADDR} {OB_DST_DRAM_ADDR} {OB_NUM_WORDS}")

        # handle zero case
        tran.writeAction(f"bnei {OB_NUM_WORDS} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-start'}")
        sht_macros.return_wreg(tran=tran, cont_reg='X1', tmp_reg=REG_TMP0, arg_reg0="X0", arg_reg1="X0")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] zero bytes to be copied, returning' {'X0'}")
        tran.writeAction("yield_terminate")

        # save operands
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-start'}: addi {'X1'} {REG_CONT} {0}")
        tran.writeAction(f"addi {OB_SRC_DRAM_ADDR} {REG_START_SRC_DRAM_ADDR} {0}")
        tran.writeAction(f"addi {OB_DST_DRAM_ADDR} {REG_START_DST_DRAM_ADDR} {0}")
        tran.writeAction(f"addi {OB_NUM_WORDS} {REG_NUM_WORD_LEFT} {0}")

        """----- dram loads -----"""
        tran.writeAction(f"addi {REG_START_SRC_DRAM_ADDR} {REG_CUR_SRC_DRAM_ADDR} {0}")
        tran.writeAction(f"mov_imm2reg {REG_CONCURRENCY_CNT} {0}")
        for i in range(8, 0, -1):
            tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-lt{i}'}: blti {REG_NUM_WORD_LEFT} {i} {f'{CLS_NAME}-{FN_NAME}-TR-LB-lt{i - 1}'}")
            if cls.DEBUG:
                tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] loading {i} words from dram addr = %p' {'X0'} {REG_CUR_SRC_DRAM_ADDR}")
            sht_macros.dram_read_ret(tran=tran, addr_reg=REG_CUR_SRC_DRAM_ADDR, ret_tran_label=tran_ld_ret[i - 1].getLabel(), tmp_reg=REG_TMP0, arg_lm_words=i)
            tran.writeAction(f"addi {REG_CUR_SRC_DRAM_ADDR} {REG_CUR_SRC_DRAM_ADDR} {i * cls.WORD_SIZE}")
            tran.writeAction(f"subi {REG_NUM_WORD_LEFT} {REG_NUM_WORD_LEFT} {i}")
            tran.writeAction(f"addi {REG_CONCURRENCY_CNT} {REG_CONCURRENCY_CNT} {1}")
            tran.writeAction(f"blti {REG_CONCURRENCY_CNT} {Memcpy.CONCURRENT_SENDS} {f'{CLS_NAME}-{FN_NAME}-TR-LB-lt{i}'}")  # next until mlp met
            tran.writeAction("yield")
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-lt0'}: yield")

        """==================== TRANs - dram load return ===================="""
        """----- dram stores -----"""
        for i in range(1, 9):
            tran_ld_ret[i - 1].writeAction(f"sub X{(8 + i) if i < 8 else 3} {REG_START_SRC_DRAM_ADDR} {REG_TMP0}")
            tran_ld_ret[i - 1].writeAction(f"add {REG_START_DST_DRAM_ADDR} {REG_TMP0} {REG_TMP0}")
            tran_ld_ret[i - 1].writeAction(f"sendops_dmlm_wret {REG_TMP0} {tran_st_ret.getLabel()} {'X8'} {i} {REG_TMP1}")
            tran_ld_ret[i - 1].writeAction("yield")

        """==================== TRAN - dram store return ===================="""
        tran_st_ret.writeAction(f"subi {REG_CONCURRENCY_CNT} {REG_CONCURRENCY_CNT} {1}")  # dec outstanding requests
        """----- more dram loads -----"""
        for i in range(8, 0, -1):
            tran_st_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-st_ret-LB-lt{i}'}: blti {REG_NUM_WORD_LEFT} {i} {f'{CLS_NAME}-{FN_NAME}-TR-st_ret-LB-lt{i - 1}'}")
            if cls.DEBUG:
                tran_st_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] loading {i} words from dram addr = %p' {'X0'} {REG_CUR_SRC_DRAM_ADDR}")
            sht_macros.dram_read_ret(tran=tran_st_ret, addr_reg=REG_CUR_SRC_DRAM_ADDR, ret_tran_label=tran_ld_ret[i - 1].getLabel(), tmp_reg=REG_TMP0, arg_lm_words=i)
            tran_st_ret.writeAction(f"addi {REG_CUR_SRC_DRAM_ADDR} {REG_CUR_SRC_DRAM_ADDR} {i * cls.WORD_SIZE}")
            tran_st_ret.writeAction(f"subi {REG_NUM_WORD_LEFT} {REG_NUM_WORD_LEFT} {i}")
            tran_st_ret.writeAction(f"addi {REG_CONCURRENCY_CNT} {REG_CONCURRENCY_CNT} {1}")
            tran_st_ret.writeAction(f"blti {REG_CONCURRENCY_CNT} {Memcpy.CONCURRENT_SENDS} {f'{CLS_NAME}-{FN_NAME}-TR-st_ret-LB-lt{i}'}")  # next until mlp met
            tran_st_ret.writeAction("yield")
        tran_st_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-st_ret-LB-lt0'}: bgti {REG_CONCURRENCY_CNT} {0} {f'{CLS_NAME}-{FN_NAME}-TR-st_ret-LB-wait'}")
        sht_macros.return_wreg(tran=tran_st_ret, cont_reg=REG_CONT, tmp_reg=REG_TMP0, arg_reg0="X0", arg_reg1="X0")
        tran_st_ret.writeAction("yield_terminate")
        tran_st_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-st_ret-LB-wait'}: yield")

    @classmethod
    def memcpy_dram2lm(cls, tran: EFAProgram.Transition, ret_tran_label: int, tmp_reg0: str, tmp_reg1: str, src_dram_addr_reg: str, dst_lm_offset_reg: str, num_words_reg: str, dst_nwid_reg: str = 'X0'):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="Memcpy_memcpy_dram2lm_TR", ret_tran_label=ret_tran_label, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=src_dram_addr_reg, arg_reg1=dst_lm_offset_reg, arg_reg2=num_words_reg)

    @classmethod
    def memcpy_dram2lm_wcont(cls, tran: EFAProgram.Transition, cont_reg: str, tmp_reg: str, src_dram_addr_reg: str, dst_lm_offset_reg: str, num_words_reg: str, dst_nwid_reg: str = 'X0'):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="Memcpy_memcpy_dram2lm_TR", cont_reg=cont_reg, tmp_reg=tmp_reg, arg_reg0=src_dram_addr_reg, arg_reg1=dst_lm_offset_reg, arg_reg2=num_words_reg)

    @classmethod
    def _memcpy_dram2lm(cls, state: EFAProgram.State):
        """
        X8  - SRC_DRAM_ADDR
        X9  - DST_LM_OFFSET
        X10 - NUM_WORDS
        """
        CLS_NAME = cls.__name__
        FN_NAME = cls._memcpy_dram2lm.__name__

        OB_SRC_DRAM_ADDR = "X8"
        OB_DST_LM_OFFSET = "X9"
        OB_NUM_WORDS = "X10"

        REG_START_SRC_DRAM_ADDR = "X16"
        REG_START_DST_LM_ADDR = "X17"
        REG_CUR_SRC_DRAM_ADDR = "X18"
        REG_NUM_WORD_LEFT = "X19"
        REG_CONCURRENCY_CNT = "X20"
        REG_TMP0 = "X21"
        REG_CONT = "X31"

        """==================== TRANSITION DEFINITIONS ===================="""
        tran = cls.tran_memcpy_dram2lm
        if tran is None:
            return
        cls.tran_label_memcpy_dram2lm = tran.getLabel()
        tran_ld_ret = []
        for i in range(1, 9):
            tran_ld_ret.append(state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-ld_ret_{i}"))

        """==================== TRAN - function entry ===================="""
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] SRC_DRAM_ADDR = %p, DST_LM_OFFSET = %p, NUM_WORDS = %lu' {'X0'} {OB_SRC_DRAM_ADDR} {OB_DST_LM_OFFSET} {OB_NUM_WORDS}")

        # handle zero case
        tran.writeAction(f"bnei {OB_NUM_WORDS} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-start'}")
        sht_macros.return_wreg(tran=tran, cont_reg='X1', tmp_reg=REG_TMP0, arg_reg0="X0", arg_reg1="X0")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] zero bytes to be copied, returning' {'X0'}")
        tran.writeAction("yield_terminate")

        # save operands
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-start'}: addi {'X1'} {REG_CONT} {0}")
        tran.writeAction(f"addi {OB_SRC_DRAM_ADDR} {REG_START_SRC_DRAM_ADDR} {0}")
        tran.writeAction(f"add {OB_DST_LM_OFFSET} {'X7'} {REG_START_DST_LM_ADDR} {0}")
        tran.writeAction(f"addi {OB_NUM_WORDS} {REG_NUM_WORD_LEFT} {0}")

        """----- dram loads -----"""
        tran.writeAction(f"addi {REG_START_SRC_DRAM_ADDR} {REG_CUR_SRC_DRAM_ADDR} {0}")
        tran.writeAction(f"mov_imm2reg {REG_CONCURRENCY_CNT} {0}")
        for i in range(8, 0, -1):
            tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-lt{i}'}: blti {REG_NUM_WORD_LEFT} {i} {f'{CLS_NAME}-{FN_NAME}-TR-LB-lt{i - 1}'}")
            if cls.DEBUG:
                tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] loading {i} words from dram addr = %p' {'X0'} {REG_CUR_SRC_DRAM_ADDR}")
            sht_macros.dram_read_ret(tran=tran, addr_reg=REG_CUR_SRC_DRAM_ADDR, ret_tran_label=tran_ld_ret[i - 1].getLabel(), tmp_reg=REG_TMP0, arg_lm_words=i)
            tran.writeAction(f"addi {REG_CUR_SRC_DRAM_ADDR} {REG_CUR_SRC_DRAM_ADDR} {i * cls.WORD_SIZE}")
            tran.writeAction(f"subi {REG_NUM_WORD_LEFT} {REG_NUM_WORD_LEFT} {i}")
            tran.writeAction(f"addi {REG_CONCURRENCY_CNT} {REG_CONCURRENCY_CNT} {1}")
            tran.writeAction(f"blti {REG_CONCURRENCY_CNT} {Memcpy.CONCURRENT_SENDS} {f'{CLS_NAME}-{FN_NAME}-TR-LB-lt{i}'}")  # next until mlp met
            tran.writeAction("yield")
        tran.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-LB-lt0'}: yield")

        """==================== TRANs - dram load return ===================="""
        """----- dram stores -----"""
        for i in range(1, 9):
            tran_ld_ret[i - 1].writeAction(f"subi {REG_CONCURRENCY_CNT} {REG_CONCURRENCY_CNT} {1}")  # dec outstanding requests

            # copy data from operand buffer to LM
            tran_ld_ret[i - 1].writeAction(f"sub X{(8 + i) if i < 8 else 3} {REG_START_SRC_DRAM_ADDR} {REG_TMP0}")
            tran_ld_ret[i - 1].writeAction(f"add {REG_START_DST_LM_ADDR} {REG_TMP0} {REG_TMP0}")
            if cls.DEBUG:
                tran_ld_ret[i - 1].writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] storing loaded {i} words from DRAM addr = %p to LM addr = %p' {'X0'} X{(8 + i) if i < 8 else 3} {REG_TMP0}")
            tran_ld_ret[i - 1].writeAction(f"bcpyoli {'X8'} {REG_TMP0} {i}")

            """----- more dram loads -----"""
            for j in range(8, 0, -1):
                tran_ld_ret[i - 1].writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-ld_ret{i}-LB-lt{j}'}: blti {REG_NUM_WORD_LEFT} {j} {f'{CLS_NAME}-{FN_NAME}-TR-ld_ret{i}-LB-lt{j - 1}'}")
                if cls.DEBUG:
                    tran_ld_ret[i - 1].writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] loading {j} words from dram addr = %p' {'X0'} {REG_CUR_SRC_DRAM_ADDR}")
                sht_macros.dram_read_ret(tran=tran_ld_ret[i - 1], addr_reg=REG_CUR_SRC_DRAM_ADDR, ret_tran_label=tran_ld_ret[j - 1].getLabel(), tmp_reg=REG_TMP0, arg_lm_words=j)
                tran_ld_ret[i - 1].writeAction(f"addi {REG_CUR_SRC_DRAM_ADDR} {REG_CUR_SRC_DRAM_ADDR} {j * cls.WORD_SIZE}")
                tran_ld_ret[i - 1].writeAction(f"subi {REG_NUM_WORD_LEFT} {REG_NUM_WORD_LEFT} {j}")
                tran_ld_ret[i - 1].writeAction(f"addi {REG_CONCURRENCY_CNT} {REG_CONCURRENCY_CNT} {1}")
                tran_ld_ret[i - 1].writeAction(f"blti {REG_CONCURRENCY_CNT} {Memcpy.CONCURRENT_SENDS} {f'{CLS_NAME}-{FN_NAME}-TR-ld_ret{i}-LB-lt{j}'}")  # next until mlp met
                tran_ld_ret[i - 1].writeAction("yield")
            tran_ld_ret[i - 1].writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-ld_ret{i}-LB-lt0'}: bgti {REG_CONCURRENCY_CNT} {0} {f'{CLS_NAME}-{FN_NAME}-TR-ld_ret{i}-LB-wait'}")
            sht_macros.return_wreg(tran=tran_ld_ret[i - 1], cont_reg=REG_CONT, tmp_reg=REG_TMP0, arg_reg0="X0", arg_reg1="X0")
            tran_ld_ret[i - 1].writeAction("yield_terminate")
            tran_ld_ret[i - 1].writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-ld_ret{i}-LB-wait'}: yield")
