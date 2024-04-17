from linker.EFAProgram import efaProgram, EFAProgram
import sht_macros


class SHTExt:
    @classmethod
    def setup(cls, state: EFAProgram.State, enable_ext=True, big_endian=False, debug=False) -> None:
        from sht_ext import SHTExt as SHTExtImpl
        SHTExtImpl.setup(state=state, enable_ext=enable_ext, big_endian=big_endian, debug=debug)

    @classmethod
    def macro_ext_graph_append(cls, tran: EFAProgram.Transition, IN_sht_desc_lm_addr_reg: str, IN_tmp_buf_lm_addr_reg: str, IN_key_reg: str, IN_num_val_words_reg: str, IN_cont_reg: str, tmp_reg0: str, tmp_reg1: str, tmp_reg2: str, finish_branch_label: str, cls_name: str, fn_name: str) -> None:
        from sht_ext import SHTExt as SHTExtImpl
        SHTExtImpl.macro_ext_graph_append(tran=tran, IN_sht_desc_lm_addr_reg=IN_sht_desc_lm_addr_reg, IN_tmp_buf_lm_addr_reg=IN_tmp_buf_lm_addr_reg, IN_key_reg=IN_key_reg, IN_num_val_words_reg=IN_num_val_words_reg, IN_cont_reg=IN_cont_reg, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, tmp_reg2=tmp_reg2, finish_branch_label=finish_branch_label, cls_name=cls_name, fn_name=fn_name)

    @classmethod
    def macro_ext_graph_append_migrate(cls, tran: EFAProgram.Transition, IN_sht_desc_lm_addr_reg: str, IN_tmp_buf_lm_addr_reg: str, IN_key_reg: str, IN_cont_reg: str, tmp_reg0: str, tmp_reg1: str, tmp_reg2: str, cls_name: str, fn_name: str) -> None:
        from sht_ext import SHTExt as SHTExtImpl
        SHTExtImpl.macro_ext_graph_append_migrate(tran=tran, IN_sht_desc_lm_addr_reg=IN_sht_desc_lm_addr_reg, IN_tmp_buf_lm_addr_reg=IN_tmp_buf_lm_addr_reg, IN_key_reg=IN_key_reg, IN_cont_reg=IN_cont_reg, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, tmp_reg2=tmp_reg2, cls_name=cls_name, fn_name=fn_name)

    @classmethod
    def macro_ext_graph_get_with_offset(cls, tran: EFAProgram.Transition, IN_sht_desc_lm_addr_reg: str, IN_key_reg: str, IN_offset_reg: str, IN_cont_reg: str, tmp_reg0: str, tmp_reg1: str, tmp_reg2: str, cls_name: str, fn_name: str) -> None:
        from sht_ext import SHTExt as SHTExtImpl
        SHTExtImpl.macro_ext_graph_get_with_offset(tran=tran, IN_sht_desc_lm_addr_reg=IN_sht_desc_lm_addr_reg, IN_key_reg=IN_key_reg, IN_offset_reg=IN_offset_reg, IN_cont_reg=IN_cont_reg, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, tmp_reg2=tmp_reg2, cls_name=cls_name, fn_name=fn_name)

    @classmethod
    def macro_ext_graph_get_word_cnt(cls, tran: EFAProgram.Transition, IN_sht_desc_lm_addr_reg: str, IN_key_reg: str, IN_cont_reg: str, tmp_reg0: str, tmp_reg1: str, tmp_reg2: str, cls_name: str, fn_name: str) -> None:
        from sht_ext import SHTExt as SHTExtImpl
        SHTExtImpl.macro_ext_graph_get_addr(tran=tran, IN_sht_desc_lm_addr_reg=IN_sht_desc_lm_addr_reg, IN_key_reg=IN_key_reg, IN_cont_reg=IN_cont_reg, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, tmp_reg2=tmp_reg2, cls_name=cls_name, fn_name=fn_name)

    @classmethod
    def initialize(cls, tran: EFAProgram.Transition, ret: int, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = "") -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHTExt_initialize_TR", ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=8, branch_label=branch_label)

    @classmethod
    def initialize_wcont(cls, tran: EFAProgram.Transition, ret: str, tmp_reg0: str, arg_lm_addr_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = "") -> None:
        sht_macros.call_wlm_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHTExt_initialize_TR", cont_reg=ret, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=8, branch_label=branch_label)

    @classmethod
    def initialize_without_ext(cls, tran: EFAProgram.Transition, ret: int, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = "") -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHTExt_initialize_TR", ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=5, branch_label=branch_label)

    @classmethod
    def initialize_witout_ext_wcont(cls, tran: EFAProgram.Transition, ret: str, tmp_reg0: str, arg_lm_addr_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = "") -> None:
        sht_macros.call_wlm_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHTExt_initialize_TR", cont_reg=ret, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=5, branch_label=branch_label)

    @classmethod
    def finalize(cls, tran: EFAProgram.Transition, ret: int, tmp_reg0: str, tmp_reg1: str, dst_nwid_reg: str = 'X0', branch_label: str = "") -> None:
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHTExt_finalize_TR", ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0='X0', arg_reg1='X0', branch_label=branch_label)

    @classmethod
    def finalize_wcont(cls, tran: EFAProgram.Transition, ret: str, tmp_reg0: str, dst_nwid_reg: str = 'X0', branch_label: str = "") -> None:
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHTExt_finalize_TR", cont_reg=ret, tmp_reg=tmp_reg0, arg_reg0='X0', arg_reg1='X0', branch_label=branch_label)

    @classmethod
    def update(cls, tran: EFAProgram.Transition, ret: int, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, num_val_words: int, dst_nwid_reg: str = 'X0', branch_label: str = "") -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHTExt_update_TR", ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=(2 + num_val_words), branch_label=branch_label)

    @classmethod
    def update_wcont(cls, tran: EFAProgram.Transition, ret: str, tmp_reg0: str, arg_lm_addr_reg: str, num_val_words: int, dst_nwid_reg: str = 'X0', branch_label: str = "") -> None:
        sht_macros.call_wlm_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHTExt_update_TR", cont_reg=ret, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=(2 + num_val_words), branch_label=branch_label)

    @classmethod
    def get(cls, tran: EFAProgram.Transition, ret: int, tmp_reg0: str, tmp_reg1: str, desc_lm_offset_reg: str, key_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHTExt_get_TR", ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=desc_lm_offset_reg, arg_reg1=key_reg, branch_label=branch_label)

    @classmethod
    def get_wcont(cls, tran: EFAProgram.Transition, ret: str, tmp_reg: str, desc_lm_offset_reg: str, key_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHTExt_get_TR", cont_reg=ret, tmp_reg=tmp_reg, arg_reg0=desc_lm_offset_reg, arg_reg1=key_reg, branch_label=branch_label)

    @classmethod
    def get_with_random(cls, tran: EFAProgram.Transition, ret: int, tmp_reg0: str, tmp_reg1: str, desc_lm_offset_reg: str, rand_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHTExt_get_with_random_TR", ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=desc_lm_offset_reg, arg_reg1=rand_reg, branch_label=branch_label)

    @classmethod
    def get_with_random_wcont(cls, tran: EFAProgram.Transition, ret: str, tmp_reg: str, desc_lm_offset_reg: str, rand_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHTExt_get_with_random_TR", cont_reg=ret, tmp_reg=tmp_reg, arg_reg0=desc_lm_offset_reg, arg_reg1=rand_reg, branch_label=branch_label)

    @classmethod
    def ext_graph_append(cls, tran: EFAProgram.Transition, ret: int, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, num_val_words: int, dst_nwid_reg: str = 'X0', branch_label: str = "") -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHTExt_ext_graph_append_TR", ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=(2 + num_val_words), branch_label=branch_label)

    @classmethod
    def ext_graph_append_wcont(cls, tran: EFAProgram.Transition, ret: str, tmp_reg0: str, arg_lm_addr_reg: str, num_val_words: int, dst_nwid_reg: str = 'X0', branch_label: str = "") -> None:
        sht_macros.call_wlm_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHTExt_ext_graph_append_TR", cont_reg=ret, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=(2 + num_val_words), branch_label=branch_label)

    @classmethod
    def ext_graph_get_next(cls, tran: EFAProgram.Transition, ret: int, tmp_reg0: str, tmp_reg1: str, desc_lm_offset_reg: str, key_reg: str, offset_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHTExt_ext_graph_get_next_TR", ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=desc_lm_offset_reg, arg_reg1=key_reg, arg_reg2=offset_reg, branch_label=branch_label)

    @classmethod
    def ext_graph_get_next_wcont(cls, tran: EFAProgram.Transition, ret: str, tmp_reg: str, desc_lm_offset_reg: str, key_reg: str, offset_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHTExt_ext_graph_get_next_TR", cont_reg=ret, tmp_reg=tmp_reg, arg_reg0=desc_lm_offset_reg, arg_reg1=key_reg, arg_reg2=offset_reg, branch_label=branch_label)

    @classmethod
    def ext_graph_get_addr(cls, tran: EFAProgram.Transition, ret: int, tmp_reg0: str, tmp_reg1: str, desc_lm_offset_reg: str, key_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHTExt_ext_graph_get_addr_TR", ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=desc_lm_offset_reg, arg_reg1=key_reg, branch_label=branch_label)

    @classmethod
    def ext_graph_get_addr_wcont(cls, tran: EFAProgram.Transition, ret: str, tmp_reg: str, desc_lm_offset_reg: str, key_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHTExt_ext_graph_get_addr_TR", cont_reg=ret, tmp_reg=tmp_reg, arg_reg0=desc_lm_offset_reg, arg_reg1=key_reg, branch_label=branch_label)

    @classmethod
    def get_with_mask(cls, tran: EFAProgram.Transition, ret: int, tmp_reg0: str, tmp_reg1: str, desc_lm_offset_reg: str, key_reg: str, mask_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHTExt_get_with_mask_TR", ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=desc_lm_offset_reg, arg_reg1=key_reg, arg_reg2=mask_reg, branch_label=branch_label)

    @classmethod
    def get_with_mask_wcont(cls, tran: EFAProgram.Transition, ret: str, tmp_reg: str, desc_lm_offset_reg: str, key_reg: str, mask_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHTExt_get_with_mask_TR", cont_reg=ret, tmp_reg=tmp_reg, arg_reg0=desc_lm_offset_reg, arg_reg1=key_reg, arg_reg2=mask_reg, branch_label=branch_label)

    @classmethod
    def update_with_mask(cls, tran: EFAProgram.Transition, ret: int, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, num_val_words: int, dst_nwid_reg: str = 'X0', branch_label: str = "") -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHTExt_update_with_mask_TR", ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=(3 + num_val_words), branch_label=branch_label)

    @classmethod
    def update_with_mask_wcont(cls, tran: EFAProgram.Transition, ret: str, tmp_reg0: str, arg_lm_addr_reg: str, num_val_words: int, dst_nwid_reg: str = 'X0', branch_label: str = "") -> None:
        sht_macros.call_wlm_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHTExt_update_with_mask_TR", cont_reg=ret, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=(3 + num_val_words), branch_label=branch_label)

    @classmethod
    def get_with_offset(cls, tran: EFAProgram.Transition, ret: int, tmp_reg0: str, tmp_reg1: str, desc_lm_offset_reg: str, key_reg: str, offset_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHTExt_get_with_offset_TR", ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=desc_lm_offset_reg, arg_reg1=key_reg, arg_reg2=offset_reg, branch_label=branch_label)

    @classmethod
    def get_with_offset_wcont(cls, tran: EFAProgram.Transition, ret: str, tmp_reg: str, desc_lm_offset_reg: str, key_reg: str, offset_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHTExt_get_with_offset_TR", cont_reg=ret, tmp_reg=tmp_reg, arg_reg0=desc_lm_offset_reg, arg_reg1=key_reg, arg_reg2=offset_reg, branch_label=branch_label)

    @classmethod
    def update_with_offset(cls, tran: EFAProgram.Transition, ret: int, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, num_val_words: int, dst_nwid_reg: str = 'X0', branch_label: str = "") -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHTExt_update_with_offset_TR", ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=(3 + num_val_words), branch_label=branch_label)

    @classmethod
    def update_with_offset_wcont(cls, tran: EFAProgram.Transition, ret: str, tmp_reg0: str, arg_lm_addr_reg: str, num_val_words: int, dst_nwid_reg: str = 'X0', branch_label: str = "") -> None:
        sht_macros.call_wlm_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHTExt_update_with_offset_TR", cont_reg=ret, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=(3 + num_val_words), branch_label=branch_label)

    @classmethod
    def ext_graph_append_migrate(cls, tran: EFAProgram.Transition, ret: int, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = "") -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHTExt_ext_graph_append_migrate_TR", ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=4, branch_label=branch_label)

    @classmethod
    def ext_graph_append_migrate_wcont(cls, tran: EFAProgram.Transition, ret: str, tmp_reg0: str, arg_lm_addr_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = "") -> None:
        sht_macros.call_wlm_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHTExt_ext_graph_append_migrate_TR", cont_reg=ret, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=4, branch_label=branch_label)

    @classmethod
    def get_iterators(cls, tran: EFAProgram.Transition, ret: int, tmp_reg0: str, tmp_reg1: str, desc_lm_offset_reg: str, iter_dram_addr_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHTExt_get_iterators_TR", ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=desc_lm_offset_reg, arg_reg1=iter_dram_addr_reg, branch_label=branch_label)

    @classmethod
    def get_iterators_wcont(cls, tran: EFAProgram.Transition, ret: str, tmp_reg: str, desc_lm_offset_reg: str, iter_dram_addr_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHTExt_get_iterators_TR", cont_reg=ret, tmp_reg=tmp_reg, arg_reg0=desc_lm_offset_reg, arg_reg1=iter_dram_addr_reg, branch_label=branch_label)

    @classmethod
    def get_next(cls, tran: EFAProgram.Transition, ret: int, tmp_reg0: str, tmp_reg1: str, iter_word0_reg: str, iter_word1_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHTExt_get_next_TR", ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=iter_word0_reg, arg_reg1=iter_word1_reg, branch_label=branch_label)

    @classmethod
    def get_next_wcont(cls, tran: EFAProgram.Transition, ret: str, tmp_reg: str, iter_word0_reg: str, iter_word1_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHTExt_get_next_TR", cont_reg=ret, tmp_reg=tmp_reg, arg_reg0=iter_word0_reg, arg_reg1=iter_word1_reg, branch_label=branch_label)

    @classmethod
    def get_next_split(cls, tran: EFAProgram.Transition, ret: int, tmp_reg0: str, tmp_reg1: str, iter_word0_reg: str, iter_word1_reg: str, key_addr_cont_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHTExt_get_next_split_TR", ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=iter_word0_reg, arg_reg1=iter_word1_reg, arg_reg2=key_addr_cont_reg, branch_label=branch_label)

    @classmethod
    def get_next_split_wcont(cls, tran: EFAProgram.Transition, ret: str, tmp_reg: str, iter_word0_reg: str, iter_word1_reg: str, key_addr_cont_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="SHTExt_get_next_split_TR", cont_reg=ret, tmp_reg=tmp_reg, arg_reg0=iter_word0_reg, arg_reg1=iter_word1_reg, arg_reg2=key_addr_cont_reg, branch_label=branch_label)
