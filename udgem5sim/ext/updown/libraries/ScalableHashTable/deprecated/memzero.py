from EFA_v2 import EFA, State, Transition
import sht_macros


class Memzero:
    CONCURRENT_SENDS = 25
    DEBUG = False

    @classmethod
    def setup(cls, state: State, num_concurrent_sends: int = 25, debug: bool = False) -> None:
        cls.CONCURRENT_SENDS = num_concurrent_sends
        cls.DEBUG = debug
        cls._memzero(state)

    @classmethod
    def memzero(cls, tran: Transition, ret, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, dst_nwid_reg: str = 'X0') -> None:
        if type(ret) is int:
            sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_label_memzero, ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_len=24)
        elif type(ret) is str:
            sht_macros.call_wlm_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=cls.tran_label_memzero, cont_reg=ret, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_len=24)

    @classmethod
    def _memzero(cls, state: State):
        """
        X8 - dram_addr
        X9 - num bytes
        X10 - lm_buf_addr
        """
        OB_DRAM_ADDR = "X8"
        OB_NUM_BYTES = "X9"
        OB_LM_BUF_ADDR = "X10"

        REG_DRAM_ADDR = "X16"
        REG_BYTE_LEFT = "X17"
        REG_LM_BUF_ADDR = "X18"
        REG_CONT = "X19"
        REG_TMP0 = "X20"
        REG_TMP1 = "X21"
        REG_TMP2 = "X22"

        # function entry
        tran = state.writeTransition("eventCarry", state, state, f"{cls.__name__}-memzero-TR")
        if tran is None:
            return
        cls.tran_label_memzero = tran.getLabel()
        tran_wr_ret = state.writeTransition("eventCarry", state, state, f"{cls.__name__}-memzero-TR-wr_ret")
        if tran is None:  # code already injected
            return

        # handle zero case
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{cls.__name__}] DRAM_ADDR = 0x%x, NUM_BYTES = %d, LM_BUF_ADDR = 0x%x' {'X0'} {OB_DRAM_ADDR} {OB_NUM_BYTES} {OB_LM_BUF_ADDR}")
        tran.writeAction(f"bnec {OB_NUM_BYTES} {0} {f'{cls.__name__}-memzero-TR-LB-start'}")
        tran.writeAction(f"send4_reply {'X0'} {'X0'}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{cls.__name__}] zero bytes to be filled, returning' {'X0'}")
        tran.writeAction("yield_terminate")

        tran.writeAction(f"{f'{cls.__name__}-memzero-TR-LB-start'}: mov_reg2reg {'X1'} {REG_CONT}")
        tran.writeAction(f"mov_reg2reg {OB_DRAM_ADDR} {REG_DRAM_ADDR}")
        tran.writeAction(f"mov_reg2reg {OB_NUM_BYTES} {REG_BYTE_LEFT}")
        tran.writeAction(f"mov_reg2reg {OB_LM_BUF_ADDR} {REG_LM_BUF_ADDR}")

        # init lm buffer to zero
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{cls.__name__}] filling LM buffer with 64 bytes of 0' {'X0'}")
        tran.writeAction(f"mov_imm2reg {REG_TMP0} {0}")
        tran.writeAction(f"addi {OB_LM_BUF_ADDR} {REG_TMP1} {64}")
        tran.writeAction(f"{f'{cls.__name__}-memzero-TR-buf_fill'}: move {REG_TMP0} {0}({REG_LM_BUF_ADDR}) 1 8")  # auto increment
        tran.writeAction(f"blt {REG_LM_BUF_ADDR} {REG_TMP1} {f'{cls.__name__}-memzero-TR-buf_fill'}")
        tran.writeAction(f"mov_reg2reg {OB_LM_BUF_ADDR} {REG_LM_BUF_ADDR}")  # restore the lm buf addr

        # lanuch dram writes
        # TODO: optimize with memory aligned sends
        tran.writeAction(f"mov_imm2reg {REG_TMP1} {0}")
        tran.writeAction(f"{f'{cls.__name__}-memzero-TR-LB-next'}: bltc {REG_BYTE_LEFT} {64} {f'{cls.__name__}-memzero-TR-LB-lt64'}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{cls.__name__}] launching write to addr = 0x%x' {'X0'} {REG_DRAM_ADDR}")
        tran.writeAction(f"send_dmlm_wret {REG_DRAM_ADDR} {tran_wr_ret.getLabel()} {REG_LM_BUF_ADDR} {64} {REG_TMP2}")
        tran.writeAction(f"addi {REG_DRAM_ADDR} {REG_DRAM_ADDR} {64}")
        tran.writeAction(f"subi {REG_BYTE_LEFT} {REG_BYTE_LEFT} {64}")
        tran.writeAction(f"addi {REG_TMP1} {REG_TMP1} {1}")
        tran.writeAction(f"bltc {REG_TMP1} {Memzero.CONCURRENT_SENDS} {f'{cls.__name__}-memzero-TR-LB-next'}")  # next until mlp met
        tran.writeAction("yield")
        tran.writeAction(f"{f'{cls.__name__}-memzero-TR-LB-lt64'}: bltc {REG_BYTE_LEFT} {32} {f'{cls.__name__}-memzero-TR-LB-lt32'}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{cls.__name__}] launching write to addr = 0x%x' {'X0'} {REG_DRAM_ADDR}")
        tran.writeAction(f"send_dmlm_wret {REG_DRAM_ADDR} {tran_wr_ret.getLabel()} {REG_LM_BUF_ADDR} {32} {REG_TMP2}")
        tran.writeAction(f"addi {REG_DRAM_ADDR} {REG_DRAM_ADDR} {32}")
        tran.writeAction(f"subi {REG_BYTE_LEFT} {REG_BYTE_LEFT} {32}")
        tran.writeAction(f"addi {REG_TMP1} {REG_TMP1} {1}")
        tran.writeAction(f"bltc {REG_TMP1} {Memzero.CONCURRENT_SENDS} {f'{cls.__name__}-memzero-TR-LB-next'}")  # next until mlp met
        tran.writeAction("yield")
        tran.writeAction(f"{f'{cls.__name__}-memzero-TR-LB-lt32'}: bltc {REG_BYTE_LEFT} {16} {f'{cls.__name__}-memzero-TR-LB-lt16'}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{cls.__name__}] launching write to addr = 0x%x' {'X0'} {REG_DRAM_ADDR}")
        tran.writeAction(f"send_dmlm_wret {REG_DRAM_ADDR} {tran_wr_ret.getLabel()} {REG_LM_BUF_ADDR} {16} {REG_TMP2}")
        tran.writeAction(f"addi {REG_DRAM_ADDR} {REG_DRAM_ADDR} {16}")
        tran.writeAction(f"subi {REG_BYTE_LEFT} {REG_BYTE_LEFT} {16}")
        tran.writeAction(f"addi {REG_TMP1} {REG_TMP1} {1}")
        tran.writeAction(f"bltc {REG_TMP1} {Memzero.CONCURRENT_SENDS} {f'{cls.__name__}-memzero-TR-LB-next'}")  # next until mlp met
        tran.writeAction("yield")
        tran.writeAction(f"{f'{cls.__name__}-memzero-TR-LB-lt16'}: bltc {REG_BYTE_LEFT} {8} {f'{cls.__name__}-memzero-TR-LB-lt8'}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{cls.__name__}] launching write to addr = 0x%x' {'X0'} {REG_DRAM_ADDR}")
        tran.writeAction(f"send_dmlm_wret {REG_DRAM_ADDR} {tran_wr_ret.getLabel()} {REG_LM_BUF_ADDR} {8} {REG_TMP2}")
        tran.writeAction(f"addi {REG_DRAM_ADDR} {REG_DRAM_ADDR} {8}")
        tran.writeAction(f"subi {REG_BYTE_LEFT} {REG_BYTE_LEFT} {8}")
        tran.writeAction(f"addi {REG_TMP1} {REG_TMP1} {1}")
        tran.writeAction(f"bltc {REG_TMP1} {Memzero.CONCURRENT_SENDS} {f'{cls.__name__}-memzero-TR-LB-next'}")  # next until mlp met
        tran.writeAction("yield")
        tran.writeAction(f"{f'{cls.__name__}-memzero-TR-LB-lt8'}: bltc {REG_BYTE_LEFT} {4} {f'{cls.__name__}-memzero-TR-LB-lt4'}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{cls.__name__}] launching write to addr = 0x%x' {'X0'} {REG_DRAM_ADDR}")
        tran.writeAction(f"send_dmlm_wret {REG_DRAM_ADDR} {tran_wr_ret.getLabel()} {REG_LM_BUF_ADDR} {4} {REG_TMP2}")
        tran.writeAction(f"addi {REG_DRAM_ADDR} {REG_DRAM_ADDR} {4}")
        tran.writeAction(f"subi {REG_BYTE_LEFT} {REG_BYTE_LEFT} {4}")
        tran.writeAction(f"addi {REG_TMP1} {REG_TMP1} {1}")
        tran.writeAction(f"bltc {REG_TMP1} {Memzero.CONCURRENT_SENDS} {f'{cls.__name__}-memzero-TR-LB-next'}")  # next until mlp met
        tran.writeAction("yield")
        tran.writeAction(f"{f'{cls.__name__}-memzero-TR-LB-lt4'}: bltc {REG_BYTE_LEFT} {2} {f'{cls.__name__}-memzero-TR-LB-lt2'}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{cls.__name__}] launching write to addr = 0x%x' {'X0'} {REG_DRAM_ADDR}")
        tran.writeAction(f"send_dmlm_wret {REG_DRAM_ADDR} {tran_wr_ret.getLabel()} {REG_LM_BUF_ADDR} {2} {REG_TMP2}")
        tran.writeAction(f"addi {REG_DRAM_ADDR} {REG_DRAM_ADDR} {2}")
        tran.writeAction(f"subi {REG_BYTE_LEFT} {REG_BYTE_LEFT} {2}")
        tran.writeAction(f"addi {REG_TMP1} {REG_TMP1} {1}")
        tran.writeAction(f"bltc {REG_TMP1} {Memzero.CONCURRENT_SENDS} {f'{cls.__name__}-memzero-TR-LB-next'}")  # next until mlp met
        tran.writeAction("yield")
        tran.writeAction(f"{f'{cls.__name__}-memzero-TR-LB-lt2'}: bltc {REG_BYTE_LEFT} {1} {f'{cls.__name__}-memzero-TR-LB-lt1'}")
        if cls.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][{cls.__name__}] launching write to addr = 0x%x' {'X0'} {REG_DRAM_ADDR}")
        tran.writeAction(f"send_dmlm_wret {REG_DRAM_ADDR} {tran_wr_ret.getLabel()} {REG_LM_BUF_ADDR} {1} {REG_TMP2}")
        tran.writeAction(f"addi {REG_DRAM_ADDR} {REG_DRAM_ADDR} {1}")
        tran.writeAction(f"subi {REG_BYTE_LEFT} {REG_BYTE_LEFT} {1}")
        tran.writeAction(f"addi {REG_TMP1} {REG_TMP1} {1}")
        tran.writeAction(f"bltc {REG_TMP1} {Memzero.CONCURRENT_SENDS} {f'{cls.__name__}-memzero-TR-LB-next'}")  # next until mlp met
        tran.writeAction(f"{f'{cls.__name__}-memzero-TR-LB-lt1'}: yield")

        # TRAN - write return
        if cls.DEBUG:
            tran_wr_ret.writeAction(f"print '[DEBUG][NWID %d][{cls.__name__}] write return from addr = 0x%x' {'X0'} {'X8'}")
        tran_wr_ret.writeAction(f"subi {REG_TMP1} {REG_TMP1} {1}")  # dec outstanding requests
        # lanuch dram writes
        tran_wr_ret.writeAction(f"bltc {REG_BYTE_LEFT} {64} {f'{cls.__name__}-memzero-TR-wr_ret-LB-lt64'}")
        tran_wr_ret.writeAction(f"send_dmlm_wret {REG_DRAM_ADDR} {tran_wr_ret.getLabel()} {REG_LM_BUF_ADDR} {64} {REG_TMP2}")
        tran_wr_ret.writeAction(f"addi {REG_DRAM_ADDR} {REG_DRAM_ADDR} {64}")
        tran_wr_ret.writeAction(f"subi {REG_BYTE_LEFT} {REG_BYTE_LEFT} {64}")
        tran_wr_ret.writeAction(f"addi {REG_TMP1} {REG_TMP1} {1}")  # inc outstanding requests
        tran_wr_ret.writeAction("yield")
        tran_wr_ret.writeAction(f"{f'{cls.__name__}-memzero-TR-wr_ret-LB-lt64'}: bltc {REG_BYTE_LEFT} {32} {f'{cls.__name__}-memzero-TR-wr_ret-LB-lt32'}")
        tran_wr_ret.writeAction(f"send_dmlm_wret {REG_DRAM_ADDR} {tran_wr_ret.getLabel()} {REG_LM_BUF_ADDR} {32} {REG_TMP2}")
        tran_wr_ret.writeAction(f"addi {REG_DRAM_ADDR} {REG_DRAM_ADDR} {32}")
        tran_wr_ret.writeAction(f"subi {REG_BYTE_LEFT} {REG_BYTE_LEFT} {32}")
        tran_wr_ret.writeAction(f"addi {REG_TMP1} {REG_TMP1} {1}")  # inc outstanding requests
        tran_wr_ret.writeAction("yield")
        tran_wr_ret.writeAction(f"{f'{cls.__name__}-memzero-TR-wr_ret-LB-lt32'}: bltc {REG_BYTE_LEFT} {16} {f'{cls.__name__}-memzero-TR-wr_ret-LB-lt16'}")
        tran_wr_ret.writeAction(f"send_dmlm_wret {REG_DRAM_ADDR} {tran_wr_ret.getLabel()} {REG_LM_BUF_ADDR} {16} {REG_TMP2}")
        tran_wr_ret.writeAction(f"addi {REG_DRAM_ADDR} {REG_DRAM_ADDR} {16}")
        tran_wr_ret.writeAction(f"subi {REG_BYTE_LEFT} {REG_BYTE_LEFT} {16}")
        tran_wr_ret.writeAction(f"addi {REG_TMP1} {REG_TMP1} {1}")  # inc outstanding requests
        tran_wr_ret.writeAction("yield")
        tran_wr_ret.writeAction(f"{f'{cls.__name__}-memzero-TR-wr_ret-LB-lt16'}: bltc {REG_BYTE_LEFT} {8} {f'{cls.__name__}-memzero-TR-wr_ret-LB-lt8'}")
        tran_wr_ret.writeAction(f"send_dmlm_wret {REG_DRAM_ADDR} {tran_wr_ret.getLabel()} {REG_LM_BUF_ADDR} {8} {REG_TMP2}")
        tran_wr_ret.writeAction(f"addi {REG_DRAM_ADDR} {REG_DRAM_ADDR} {8}")
        tran_wr_ret.writeAction(f"subi {REG_BYTE_LEFT} {REG_BYTE_LEFT} {8}")
        tran_wr_ret.writeAction(f"addi {REG_TMP1} {REG_TMP1} {1}")  # inc outstanding requests
        tran_wr_ret.writeAction("yield")
        tran_wr_ret.writeAction(f"{f'{cls.__name__}-memzero-TR-wr_ret-LB-lt8'}: bltc {REG_BYTE_LEFT} {4} {f'{cls.__name__}-memzero-TR-wr_ret-LB-lt4'}")
        tran_wr_ret.writeAction(f"send_dmlm_wret {REG_DRAM_ADDR} {tran_wr_ret.getLabel()} {REG_LM_BUF_ADDR} {4} {REG_TMP2}")
        tran_wr_ret.writeAction(f"addi {REG_DRAM_ADDR} {REG_DRAM_ADDR} {4}")
        tran_wr_ret.writeAction(f"subi {REG_BYTE_LEFT} {REG_BYTE_LEFT} {4}")
        tran_wr_ret.writeAction(f"addi {REG_TMP1} {REG_TMP1} {1}")  # inc outstanding requests
        tran_wr_ret.writeAction("yield")
        tran_wr_ret.writeAction(f"{f'{cls.__name__}-memzero-TR-wr_ret-LB-lt4'}: bltc {REG_BYTE_LEFT} {2} {f'{cls.__name__}-memzero-TR-wr_ret-LB-lt2'}")
        tran_wr_ret.writeAction(f"send_dmlm_wret {REG_DRAM_ADDR} {tran_wr_ret.getLabel()} {REG_LM_BUF_ADDR} {2} {REG_TMP2}")
        tran_wr_ret.writeAction(f"addi {REG_DRAM_ADDR} {REG_DRAM_ADDR} {2}")
        tran_wr_ret.writeAction(f"subi {REG_BYTE_LEFT} {REG_BYTE_LEFT} {2}")
        tran_wr_ret.writeAction(f"addi {REG_TMP1} {REG_TMP1} {1}")  # inc outstanding requests
        tran_wr_ret.writeAction("yield")
        tran_wr_ret.writeAction(f"{f'{cls.__name__}-memzero-TR-wr_ret-LB-lt2'}: bltc {REG_BYTE_LEFT} {1} {f'{cls.__name__}-memzero-TR-wr_ret-LB-lt1'}")
        tran_wr_ret.writeAction(f"send_dmlm_wret {REG_DRAM_ADDR} {tran_wr_ret.getLabel()} {REG_LM_BUF_ADDR} {1} {REG_TMP2}")
        tran_wr_ret.writeAction(f"addi {REG_DRAM_ADDR} {REG_DRAM_ADDR} {1}")
        tran_wr_ret.writeAction(f"subi {REG_BYTE_LEFT} {REG_BYTE_LEFT} {1}")
        tran_wr_ret.writeAction(f"addi {REG_TMP1} {REG_TMP1} {1}")  # inc outstanding requests
        tran_wr_ret.writeAction("yield")
        tran_wr_ret.writeAction(f"{f'{cls.__name__}-memzero-TR-wr_ret-LB-lt1'}: beqc {REG_TMP1} {0} {f'{cls.__name__}-memzero-TR-wr_ret-LB-done'}")  # barrier
        tran_wr_ret.writeAction("yield")
        tran_wr_ret.writeAction(f"{f'{cls.__name__}-memzero-TR-wr_ret-LB-done'}: mov_reg2reg {REG_TMP1} {REG_TMP1}")  # TODO: dummy instruction
        sht_macros.return_wreg(tran_wr_ret, REG_CONT, REG_TMP0, "X0", "X0")
        if cls.DEBUG:
            tran_wr_ret.writeAction(f"print '[DEBUG][NWID %d][{cls.__name__}] all writes done' {'X0'}")
        tran_wr_ret.writeAction("yield_terminate")
