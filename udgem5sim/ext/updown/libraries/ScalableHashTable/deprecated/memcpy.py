from EFA_v2 import EFA, State, Transition
import sht_macros


class Memcpy:
    CONCURRENT_SENDS = 25
    DEBUG = False

    WORD_SIZE = 8

    @classmethod
    def setup(cls, state: State, num_concurrent_sends: int = 25, debug: bool = False) -> None:
        cls.CONCURRENT_SENDS = num_concurrent_sends
        cls.DEBUG = debug

        CLS_NAME = cls.__name__
        cls.tran_memcpy = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-memcpy-TR")

        cls._memcpy(state)

    @classmethod
    def memcpy(cls, tran: Transition, ret_tran_label: int, tmp_reg0: str, tmp_reg1: str, src_dram_addr_reg: str, dst_dram_addr_reg: str, num_words_reg: str, dst_nwid_reg: str = 'X0'):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_label_memcpy, ret_tran_label=ret_tran_label, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=src_dram_addr_reg, arg_reg1=dst_dram_addr_reg, arg_reg2=num_words_reg)

    @classmethod
    def memcpy_wcont(cls, tran: Transition, cont_reg: str, tmp_reg: str, src_dram_addr_reg: str, dst_dram_addr_reg: str, num_words_reg: str, dst_nwid_reg: str = 'X0'):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_label_memcpy, cont_reg=cont_reg, tmp_reg=tmp_reg, arg_reg0=src_dram_addr_reg, arg_reg1=dst_dram_addr_reg, arg_reg2=num_words_reg)

    @classmethod
    def _memcpy(cls, state: State):
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
        tran_st_ret = state.writeTransition("eventCarry", state, state, f"{CLS_NAME}-{FN_NAME}-TR-st_ret_{i}")
        if tran is None:  # code already injected
            return

        """==================== TRAN - function entry ===================="""
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] SRC_DRAM_ADDR = 0x%x, DST_DRAM_ADDR = 0x%x, NUM_WORDS = %d' {'X0'} {OB_SRC_DRAM_ADDR} {OB_DST_DRAM_ADDR} {OB_NUM_WORDS}")

        # handle zero case
        tran.writeAction(f"bnei {OB_NUM_WORDS} {0} {f'{CLS_NAME}-{FN_NAME}-TR-LB-start'}")
        # tran.writeAction(f"sendr_reply {'X0'} {'X0'}")
        sht_macros.return_wreg(tran=tran, cont_reg=REG_CONT, arg_reg0="X0", arg_reg1="X0")
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
                tran.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] loading {i} words from dram addr = 0x%x' {'X0'} {REG_CUR_SRC_DRAM_ADDR}")
            # tran.writeAction(f"send_dmlm_ld_wret {REG_CUR_SRC_DRAM_ADDR} {tran_ld_ret[i - 1].getLabel()} {i}")
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
                tran_st_ret.writeAction(f"print '[DEBUG][NWID %d][{CLS_NAME}] loading {i} words from dram addr = 0x%x' {'X0'} {REG_CUR_SRC_DRAM_ADDR}")
            # tran_st_ret.writeAction(f"send_dmlm_ld_wret {REG_CUR_SRC_DRAM_ADDR} {tran_ld_ret[i - 1].getLabel()} {i}")
            sht_macros.dram_read_ret(tran=tran_st_ret, addr_reg=REG_CUR_SRC_DRAM_ADDR, ret_tran_label=tran_ld_ret[i - 1].getLabel(), tmp_reg=REG_TMP0, arg_lm_words=i)
            tran_st_ret.writeAction(f"addi {REG_CUR_SRC_DRAM_ADDR} {REG_CUR_SRC_DRAM_ADDR} {i * cls.WORD_SIZE}")
            tran_st_ret.writeAction(f"subi {REG_NUM_WORD_LEFT} {REG_NUM_WORD_LEFT} {i}")
            tran_st_ret.writeAction(f"addi {REG_CONCURRENCY_CNT} {REG_CONCURRENCY_CNT} {1}")
            tran_st_ret.writeAction(f"blti {REG_CONCURRENCY_CNT} {Memcpy.CONCURRENT_SENDS} {f'{CLS_NAME}-{FN_NAME}-TR-st_ret-LB-lt{i}'}")  # next until mlp met
            tran_st_ret.writeAction("yield")
        tran_st_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-st_ret-LB-lt0'}: bgti {REG_CONCURRENCY_CNT} {0} {f'{CLS_NAME}-{FN_NAME}-TR-st_ret-LB-wait'}")
        sht_macros.return_wreg(tran_st_ret, REG_CONT, "X0", "X0")
        tran_st_ret.writeAction("yield_terminate")
        tran_st_ret.writeAction(f"{f'{CLS_NAME}-{FN_NAME}-TR-st_ret-LB-wait'}: yield")
