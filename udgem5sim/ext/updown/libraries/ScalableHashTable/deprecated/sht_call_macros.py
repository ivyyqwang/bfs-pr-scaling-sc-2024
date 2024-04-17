from EFA_v2 import EFA, State, Transition
from sht import SHT as SHTImpl
import sht_macros


class SHT:
    @classmethod
    def setup(cls, state: State, debug=False) -> None:
        SHTImpl.setup(state=state, debug=debug)

    @classmethod
    def initialize(cls, tran: Transition, ret: int, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=SHTImpl.tran_label_init, ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=8)

    @classmethod
    def initialize_wcont(cls, tran: Transition, ret: str, tmp_reg0: str, arg_lm_addr_reg: str, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=SHTImpl.tran_label_init, cont_reg=ret, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=8)

    @classmethod
    def finalize(cls, tran: Transition, ret: int, tmp_reg0: str, tmp_reg1: str, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=SHTImpl.tran_label_finalize, ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0='X0', arg_reg1='X0')

    @classmethod
    def finalize_wcont(cls, tran: Transition, ret: str, tmp_reg0: str, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=SHTImpl.tran_label_finalize, cont_reg=ret, tmp_reg=tmp_reg0, arg_reg0='X0', arg_reg1='X0')

    @classmethod
    def update(cls, tran: Transition, ret: int, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=SHTImpl.tran_label_update, ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=4)

    @classmethod
    def update_wcont(cls, tran: Transition, ret: str, tmp_reg0: str, arg_lm_addr_reg: str, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=SHTImpl.tran_label_update, cont_reg=ret, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=4)

    @classmethod
    def get(cls, tran: Transition, ret: int, tmp_reg0: str, tmp_reg1: str, desc_lm_offset_reg: str, key_reg: str, dst_nwid_reg: str = 'X0'):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=SHTImpl.tran_label_get, ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=desc_lm_offset_reg, arg_reg1=key_reg)

    @classmethod
    def get_wcont(cls, tran: Transition, ret: str, tmp_reg: str, desc_lm_offset_reg: str, key_reg: str, dst_nwid_reg: str = 'X0'):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label=SHTImpl.tran_label_get, cont_reg=ret, tmp_reg=tmp_reg, arg_reg0=desc_lm_offset_reg, arg_reg1=key_reg)
