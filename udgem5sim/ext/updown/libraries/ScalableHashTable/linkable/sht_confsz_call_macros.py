from linker.EFAProgram import efaProgram, EFAProgram
import sht_macros


class SHT:
    @classmethod
    def initialize(cls, tran: EFAProgram.Transition, ret: int, tmp_reg0: str, arg_lm_addr_reg: str, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHTConfsz__initialize_TR", ret_tran_label=ret, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=7)

    @classmethod
    def initialize_wcont(cls, tran: EFAProgram.Transition, ret: str, tmp_reg0: str, arg_lm_addr_reg: str, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHTConfsz__initialize_TR", cont_reg=ret, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=7)

    @classmethod
    def finalize(cls, tran: EFAProgram.Transition, ret: int, tmp_reg0: str, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHTConfsz__finalize_TR", ret_tran_label=ret, tmp_reg=tmp_reg0, arg_reg0='X0', arg_reg1='X0')

    @classmethod
    def finalize_wcont(cls, tran: EFAProgram.Transition, ret: str, tmp_reg0: str, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHTConfsz__finalize_TR", cont_reg=ret, tmp_reg=tmp_reg0, arg_reg0='X0', arg_reg1='X0')

    @classmethod
    def update(cls, tran: EFAProgram.Transition, ret: int, tmp_reg0: str, arg_lm_addr_reg: str, val_num_words: int, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHTConfsz__update_TR", ret_tran_label=ret, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=(3 + val_num_words))

    @classmethod
    def update_wcont(cls, tran: EFAProgram.Transition, ret: str, tmp_reg0: str, arg_lm_addr_reg: str, val_num_words: int, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHTConfsz__update_TR", cont_reg=ret, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=(3 + val_num_words))

    @classmethod
    def get(cls, tran: EFAProgram.Transition, ret: int, tmp_reg: str, desc_lm_offset_reg: str, key_reg: str, dst_nwid_reg: str = 'X0'):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHTConfsz__get_TR", ret_tran_label=ret, tmp_reg=tmp_reg, arg_reg0=desc_lm_offset_reg, arg_reg1=key_reg)

    @classmethod
    def get_wcont(cls, tran: EFAProgram.Transition, ret: str, tmp_reg: str, desc_lm_offset_reg: str, key_reg: str, dst_nwid_reg: str = 'X0'):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHTConfsz__get_TR", cont_reg=ret, tmp_reg=tmp_reg, arg_reg0=desc_lm_offset_reg, arg_reg1=key_reg)
