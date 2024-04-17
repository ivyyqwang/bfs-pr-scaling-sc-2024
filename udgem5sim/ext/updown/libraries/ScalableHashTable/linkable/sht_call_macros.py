from linker.EFAProgram import efaProgram, EFAProgram
from sht import SHT as SHTImpl
import sht_macros


class SHT:
    @classmethod
    def setup(cls, state: EFAProgram.State, debug=False) -> None:
        SHTImpl.setup(state=state, debug=debug)

    @classmethod
    def initialize(cls, tran: EFAProgram.Transition, ret: int, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = "") -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHT_initialize_TR", ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=8, branch_label=branch_label)

    @classmethod
    def initialize_wcont(cls, tran: EFAProgram.Transition, ret: str, tmp_reg0: str, arg_lm_addr_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = "") -> None:
        sht_macros.call_wlm_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHT_initialize_TR", cont_reg=ret, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=8, branch_label=branch_label)

    @classmethod
    def finalize(cls, tran: EFAProgram.Transition, ret: int, tmp_reg0: str, tmp_reg1: str, dst_nwid_reg: str = 'X0', branch_label: str = "") -> None:
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHT_finalize_TR", ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0='X0', arg_reg1='X0', branch_label=branch_label)

    @classmethod
    def finalize_wcont(cls, tran: EFAProgram.Transition, ret: str, tmp_reg0: str, dst_nwid_reg: str = 'X0', branch_label: str = "") -> None:
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHT_finalize_TR", cont_reg=ret, tmp_reg=tmp_reg0, arg_reg0='X0', arg_reg1='X0', branch_label=branch_label)

    @classmethod
    def update(cls, tran: EFAProgram.Transition, ret: int, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = "") -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHT_update_TR", ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=4, branch_label=branch_label)

    @classmethod
    def update_wcont(cls, tran: EFAProgram.Transition, ret: str, tmp_reg0: str, arg_lm_addr_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = "") -> None:
        sht_macros.call_wlm_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHT_update_TR", cont_reg=ret, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=4, branch_label=branch_label)

    @classmethod
    def get(cls, tran: EFAProgram.Transition, ret: int, tmp_reg0: str, tmp_reg1: str, desc_lm_offset_reg: str, key_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHT_get_TR", ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=desc_lm_offset_reg, arg_reg1=key_reg, branch_label=branch_label)

    @classmethod
    def get_wcont(cls, tran: EFAProgram.Transition, ret: str, tmp_reg: str, desc_lm_offset_reg: str, key_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHT_get_TR", cont_reg=ret, tmp_reg=tmp_reg, arg_reg0=desc_lm_offset_reg, arg_reg1=key_reg, branch_label=branch_label)

    @classmethod
    def get_iterators(cls, tran: EFAProgram.Transition, ret: int, tmp_reg0: str, tmp_reg1: str, desc_lm_offset_reg: str, iter_dram_addr_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHT_get_iterators_TR", ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=desc_lm_offset_reg, arg_reg1=iter_dram_addr_reg, branch_label=branch_label)

    @classmethod
    def get_iterators_wcont(cls, tran: EFAProgram.Transition, ret: str, tmp_reg: str, desc_lm_offset_reg: str, iter_dram_addr_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHT_get_iterators_TR", cont_reg=ret, tmp_reg=tmp_reg, arg_reg0=desc_lm_offset_reg, arg_reg1=iter_dram_addr_reg, branch_label=branch_label)

    @classmethod
    def get_next(cls, tran: EFAProgram.Transition, ret: int, tmp_reg0: str, tmp_reg1: str, iter_word0_reg: str, iter_word1_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHT_get_next_TR", ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=iter_word0_reg, arg_reg1=iter_word1_reg, branch_label=branch_label)

    @classmethod
    def get_next_wcont(cls, tran: EFAProgram.Transition, ret: str, tmp_reg: str, iter_word0_reg: str, iter_word1_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHT_get_next_TR", cont_reg=ret, tmp_reg=tmp_reg, arg_reg0=iter_word0_reg, arg_reg1=iter_word1_reg, branch_label=branch_label)

    @classmethod
    def get_next_split(cls, tran: EFAProgram.Transition, ret: int, tmp_reg0: str, tmp_reg1: str, iter_word0_reg: str, iter_word1_reg: str, key_val_cont_reg, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHT_get_next_split_TR", ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=iter_word0_reg, arg_reg1=iter_word1_reg, arg_reg2=key_val_cont_reg, branch_label=branch_label)

    @classmethod
    def get_next_split_wcont(cls, tran: EFAProgram.Transition, ret: str, tmp_reg: str, iter_word0_reg: str, iter_word1_reg: str, key_val_cont_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHT_get_next_split_TR", cont_reg=ret, tmp_reg=tmp_reg, arg_reg0=iter_word0_reg, arg_reg1=iter_word1_reg, arg_reg2=key_val_cont_reg, branch_label=branch_label)
