from linker.EFAProgram import efaProgram, EFAProgram
import sht_macros


class ParallelGraphAbstraction:
    @classmethod
    def setup(cls, state: EFAProgram.State, big_endian=False, debug: bool = False):
        from pga import ParallelGraphAbstraction as PGAImpl
        PGAImpl.setup(state=state, big_endian=big_endian, debug=debug)

    @classmethod
    def initialize_vertex_store(cls, tran: EFAProgram.Transition, ret_tran_label: int, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="ParallelGraphAbstraction_initialize_vertex_store_TR", ret_tran_label=ret_tran_label, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=5)

    @classmethod
    def initialize_vertex_store_wcont(cls, tran: EFAProgram.Transition, cont_reg: str, tmp_reg0: str, arg_lm_addr_reg: str, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="ParallelGraphAbstraction_initialize_vertex_store_TR", cont_reg=cont_reg, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=5)

    @classmethod
    def initialize_edge_store(cls, tran: EFAProgram.Transition, ret_tran_label: int, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="ParallelGraphAbstraction_initialize_edge_store_TR", ret_tran_label=ret_tran_label, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=5)

    @classmethod
    def initialize_edge_store_wcont(cls, tran: EFAProgram.Transition, cont_reg: str, tmp_reg0: str, arg_lm_addr_reg: str, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="ParallelGraphAbstraction_initialize_edge_store_TR", cont_reg=cont_reg, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=5)

    @classmethod
    def initialize_edge_list_store_append(cls, tran: EFAProgram.Transition, ret_tran_label: int, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="ParallelGraphAbstraction_initialize_edge_list_store_append_TR", ret_tran_label=ret_tran_label, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=5)

    @classmethod
    def initialize_edge_list_store_append_wcont(cls, tran: EFAProgram.Transition, cont_reg: str, tmp_reg0: str, arg_lm_addr_reg: str, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="ParallelGraphAbstraction_edge_neighbor_list_store_append_TR", cont_reg=cont_reg, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=5)

    @classmethod
    def update_vertex(cls, tran: EFAProgram.Transition, ret_tran_label: int, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, num_val_words: int, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="ParallelGraphAbstraction_update_vertex_TR", ret_tran_label=ret_tran_label, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=(3 + num_val_words))

    @classmethod
    def update_vertex_wcont(cls, tran: EFAProgram.Transition, cont_reg: str, tmp_reg0: str, arg_lm_addr_reg: str, num_val_words: int, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="ParallelGraphAbstraction_update_vertex_TR", cont_reg=cont_reg, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=(3 + num_val_words))

    @classmethod
    def update_vertex_with_offset(cls, tran: EFAProgram.Transition, ret_tran_label: int, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, num_val_words: int, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="ParallelGraphAbstraction_update_vertex_with_offset_TR", ret_tran_label=ret_tran_label, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=(3 + num_val_words))

    @classmethod
    def update_vertex_with_offset_wcont(cls, tran: EFAProgram.Transition, cont_reg: str, tmp_reg0: str, arg_lm_addr_reg: str, num_val_words: int, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="ParallelGraphAbstraction_update_vertex_with_offset_TR", cont_reg=cont_reg, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=(3 + num_val_words))

    @classmethod
    def get_vertex(cls, tran: EFAProgram.Transition, ret_tran_label: int, tmp_reg0: str, tmp_reg1: str, desc_lm_offset_reg: str, vid_reg: str, mask_reg: str, dst_nwid_reg: str = 'X0'):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="ParallelGraphAbstraction_get_vertex_TR", ret_tran_label=ret_tran_label, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=desc_lm_offset_reg, arg_reg1=vid_reg, arg_reg2=mask_reg)

    @classmethod
    def get_vertex_wcont(cls, tran: EFAProgram.Transition, cont_reg: str, tmp_reg: str, desc_lm_offset_reg: str, vid_reg: str, mask_reg: str, dst_nwid_reg: str = 'X0'):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="ParallelGraphAbstraction_get_vertex_TR", cont_reg=cont_reg, tmp_reg=tmp_reg, arg_reg0=desc_lm_offset_reg, arg_reg1=vid_reg, arg_reg2=mask_reg)

    @classmethod
    def get_vertex_with_random(cls, tran: EFAProgram.Transition, ret_tran_label: int, tmp_reg0: str, tmp_reg1: str, desc_lm_offset_reg: str, rand_reg: str, dst_nwid_reg: str = 'X0'):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="ParallelGraphAbstraction_get_vertex_with_random_TR", ret_tran_label=ret_tran_label, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=desc_lm_offset_reg, arg_reg1=rand_reg)

    @classmethod
    def get_vertex_with_random_wcont(cls, tran: EFAProgram.Transition, cont_reg: str, tmp_reg: str, desc_lm_offset_reg: str, rand_reg: str, dst_nwid_reg: str = 'X0'):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="ParallelGraphAbstraction_get_vertex_with_random_TR", cont_reg=cont_reg, tmp_reg=tmp_reg, arg_reg0=desc_lm_offset_reg, arg_reg1=rand_reg)

    @classmethod
    def get_vertex_with_offset(cls, tran: EFAProgram.Transition, ret_tran_label: int, tmp_reg0: str, tmp_reg1: str, desc_lm_offset_reg: str, vid_reg: str, offset_reg: str, dst_nwid_reg: str = 'X0'):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="ParallelGraphAbstraction_get_vertex_with_offset_TR", ret_tran_label=ret_tran_label, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=desc_lm_offset_reg, arg_reg1=vid_reg, arg_reg2=offset_reg)

    @classmethod
    def get_vertex_with_offset_wcont(cls, tran: EFAProgram.Transition, cont_reg: str, tmp_reg: str, desc_lm_offset_reg: str, vid_reg: str, offset_reg: str, dst_nwid_reg: str = 'X0'):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="ParallelGraphAbstraction_get_vertex_with_offset_TR", cont_reg=cont_reg, tmp_reg=tmp_reg, arg_reg0=desc_lm_offset_reg, arg_reg1=vid_reg, arg_reg2=offset_reg)

    @classmethod
    def update_edge(cls, tran: EFAProgram.Transition, ret_tran_label: int, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, num_val_words: int, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="ParallelGraphAbstraction_update_edge_TR", ret_tran_label=ret_tran_label, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=(3 + num_val_words))

    @classmethod
    def update_edge_wcont(cls, tran: EFAProgram.Transition, cont_reg: str, tmp_reg0: str, arg_lm_addr_reg: str, num_val_words: int, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="ParallelGraphAbstraction_update_edge_TR", cont_reg=cont_reg, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=(3 + num_val_words))

    @classmethod
    def update_edge_with_offset(cls, tran: EFAProgram.Transition, ret_tran_label: int, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, num_val_words: int, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="ParallelGraphAbstraction_update_edge_with_offset_TR", ret_tran_label=ret_tran_label, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=(3 + num_val_words))

    @classmethod
    def update_edge_with_offset_wcont(cls, tran: EFAProgram.Transition, cont_reg: str, tmp_reg0: str, arg_lm_addr_reg: str, num_val_words: int, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="ParallelGraphAbstraction_update_edge_with_offset_TR", cont_reg=cont_reg, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=(3 + num_val_words))

    @classmethod
    def get_edge(cls, tran: EFAProgram.Transition, ret_tran_label: int, tmp_reg0: str, tmp_reg1: str, desc_lm_offset_reg: str, eid_reg: str, mask_reg: str, dst_nwid_reg: str = 'X0'):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="ParallelGraphAbstraction_get_edge_TR", ret_tran_label=ret_tran_label, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=desc_lm_offset_reg, arg_reg1=eid_reg, arg_reg2=mask_reg)

    @classmethod
    def get_edge_wcont(cls, tran: EFAProgram.Transition, cont_reg: str, tmp_reg: str, desc_lm_offset_reg: str, eid_reg: str, mask_reg: str, dst_nwid_reg: str = 'X0'):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="ParallelGraphAbstraction_get_edge_TR", cont_reg=cont_reg, tmp_reg=tmp_reg, arg_reg0=desc_lm_offset_reg, arg_reg1=eid_reg, arg_reg2=mask_reg)

    @classmethod
    def get_edge_with_offset(cls, tran: EFAProgram.Transition, ret_tran_label: int, tmp_reg0: str, tmp_reg1: str, desc_lm_offset_reg: str, eid_reg: str, offset_reg: str, dst_nwid_reg: str = 'X0'):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="ParallelGraphAbstraction_get_edge_with_offset_TR", ret_tran_label=ret_tran_label, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=desc_lm_offset_reg, arg_reg1=eid_reg, arg_reg2=offset_reg)

    @classmethod
    def get_edge_with_offset_wcont(cls, tran: EFAProgram.Transition, cont_reg: str, tmp_reg: str, desc_lm_offset_reg: str, eid_reg: str, offset_reg: str, dst_nwid_reg: str = 'X0'):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="ParallelGraphAbstraction_get_edge_with_offset_TR", cont_reg=cont_reg, tmp_reg=tmp_reg, arg_reg0=desc_lm_offset_reg, arg_reg1=eid_reg, arg_reg2=offset_reg)

    @classmethod
    def append_edge_list(cls, tran: EFAProgram.Transition, ret_tran_label: int, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, num_val_words: int, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="ParallelGraphAbstraction_append_edge_list_TR", ret_tran_label=ret_tran_label, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=(2 + num_val_words))

    @classmethod
    def append_edge_list_wcont(cls, tran: EFAProgram.Transition, cont_reg: str, tmp_reg0: str, arg_lm_addr_reg: str, num_val_words: int, dst_nwid_reg: str = 'X0') -> None:
        sht_macros.call_wlm_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="ParallelGraphAbstraction_append_edge_list_TR", cont_reg=cont_reg, tmp_reg=tmp_reg0, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_words=(2 + num_val_words))

    @classmethod
    def get_edge_list_next(cls, tran: EFAProgram.Transition, ret_tran_label: int, tmp_reg0: str, tmp_reg1: str, desc_lm_offset_reg: str, vid_reg: str, offset_reg: str, dst_nwid_reg: str = 'X0'):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="ParallelGraphAbstraction_get_edge_list_next_TR", ret_tran_label=ret_tran_label, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=desc_lm_offset_reg, arg_reg1=vid_reg, arg_reg2=offset_reg)

    @classmethod
    def get_edge_list_next_wcont(cls, tran: EFAProgram.Transition, cont_reg: str, tmp_reg: str, desc_lm_offset_reg: str, vid_reg: str, offset_reg: str, dst_nwid_reg: str = 'X0'):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="ParallelGraphAbstraction_get_edge_list_next_TR", cont_reg=cont_reg, tmp_reg=tmp_reg, arg_reg0=desc_lm_offset_reg, arg_reg1=vid_reg, arg_reg2=offset_reg)

    @classmethod
    def get_edge_list_addr(cls, tran: EFAProgram.Transition, ret_tran_label: int, tmp_reg0: str, tmp_reg1: str, desc_lm_offset_reg: str, vid_reg: str, dst_nwid_reg: str = 'X0'):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="ParallelGraphAbstraction_get_edge_list_addr_TR", ret_tran_label=ret_tran_label, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=desc_lm_offset_reg, arg_reg1=vid_reg)

    @classmethod
    def get_edge_list_addr_wcont(cls, tran: EFAProgram.Transition, cont_reg: str, tmp_reg: str, desc_lm_offset_reg: str, vid_reg: str, dst_nwid_reg: str = 'X0'):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="ParallelGraphAbstraction_get_edge_list_addr_TR", cont_reg=cont_reg, tmp_reg=tmp_reg, arg_reg0=desc_lm_offset_reg, arg_reg1=vid_reg)

    @classmethod
    def get_iters_vertex_store(cls, tran: EFAProgram.Transition, ret: int, tmp_reg0: str, tmp_reg1: str, desc_lm_offset_reg: str, iter_dram_addr_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="ParallelGraphAbstraction_get_iters_vertex_store_TR", ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=desc_lm_offset_reg, arg_reg1=iter_dram_addr_reg, branch_label=branch_label)

    @classmethod
    def get_iters_vertex_store_wcont(cls, tran: EFAProgram.Transition, ret: str, tmp_reg: str, desc_lm_offset_reg: str, iter_dram_addr_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="ParallelGraphAbstraction_get_iters_vertex_store_TR", cont_reg=ret, tmp_reg=tmp_reg, arg_reg0=desc_lm_offset_reg, arg_reg1=iter_dram_addr_reg, branch_label=branch_label)

    @classmethod
    def get_iters_edge_store(cls, tran: EFAProgram.Transition, ret: int, tmp_reg0: str, tmp_reg1: str, desc_lm_offset_reg: str, iter_dram_addr_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="ParallelGraphAbstraction_get_iters_edge_store_TR", ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=desc_lm_offset_reg, arg_reg1=iter_dram_addr_reg, branch_label=branch_label)

    @classmethod
    def get_iters_edge_store_wcont(cls, tran: EFAProgram.Transition, ret: str, tmp_reg: str, desc_lm_offset_reg: str, iter_dram_addr_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="ParallelGraphAbstraction_get_iters_edge_store_TR", cont_reg=ret, tmp_reg=tmp_reg, arg_reg0=desc_lm_offset_reg, arg_reg1=iter_dram_addr_reg, branch_label=branch_label)

    @classmethod
    def get_next_vertex_store_iter(cls, tran: EFAProgram.Transition, ret: int, tmp_reg0: str, tmp_reg1: str, iter_word0_reg: str, iter_word1_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="ParallelGraphAbstraction_get_next_vertex_store_iter_TR", ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=iter_word0_reg, arg_reg1=iter_word1_reg, branch_label=branch_label)

    @classmethod
    def get_next_vertex_store_iter_wcont(cls, tran: EFAProgram.Transition, ret: str, tmp_reg: str, iter_word0_reg: str, iter_word1_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="ParallelGraphAbstraction_get_next_vertex_store_iter_TR", cont_reg=ret, tmp_reg=tmp_reg, arg_reg0=iter_word0_reg, arg_reg1=iter_word1_reg, branch_label=branch_label)

    @classmethod
    def get_next_edge_store_iter(cls, tran: EFAProgram.Transition, ret: int, tmp_reg0: str, tmp_reg1: str, iter_word0_reg: str, iter_word1_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="ParallelGraphAbstraction_get_next_edge_store_iter_TR", ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=iter_word0_reg, arg_reg1=iter_word1_reg, branch_label=branch_label)

    @classmethod
    def get_next_edge_store_iter_wcont(cls, tran: EFAProgram.Transition, ret: str, tmp_reg: str, iter_word0_reg: str, iter_word1_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="ParallelGraphAbstraction_get_next_edge_store_iter_TR", cont_reg=ret, tmp_reg=tmp_reg, arg_reg0=iter_word0_reg, arg_reg1=iter_word1_reg, branch_label=branch_label)

    @classmethod
    def get_next_split_vertex_store_iter(cls, tran: EFAProgram.Transition, ret: int, tmp_reg0: str, tmp_reg1: str, iter_word0_reg: str, iter_word1_reg: str, key_addr_cont_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="ParallelGraphAbstraction_get_next_split_vertex_store_iter_TR", ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=iter_word0_reg, arg_reg1=iter_word1_reg, arg_reg2=key_addr_cont_reg, branch_label=branch_label)

    @classmethod
    def get_next_split_vertex_store_iter_wcont(cls, tran: EFAProgram.Transition, ret: str, tmp_reg: str, iter_word0_reg: str, iter_word1_reg: str, key_addr_cont_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="ParallelGraphAbstraction_get_next_split_vertex_store_iter_TR", cont_reg=ret, tmp_reg=tmp_reg, arg_reg0=iter_word0_reg, arg_reg1=iter_word1_reg, arg_reg2=key_addr_cont_reg, branch_label=branch_label)

    @classmethod
    def get_next_split_edge_store_iter(cls, tran: EFAProgram.Transition, ret: int, tmp_reg0: str, tmp_reg1: str, iter_word0_reg: str, iter_word1_reg: str, key_addr_cont_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="ParallelGraphAbstraction_get_next_split_edge_store_iter_TR", ret_tran_label=ret, tmp_reg0=tmp_reg0, tmp_reg1=tmp_reg1, arg_reg0=iter_word0_reg, arg_reg1=iter_word1_reg, arg_reg2=key_addr_cont_reg, branch_label=branch_label)

    @classmethod
    def get_next_split_edge_store_iter_wcont(cls, tran: EFAProgram.Transition, ret: str, tmp_reg: str, iter_word0_reg: str, iter_word1_reg: str, key_addr_cont_reg: str, dst_nwid_reg: str = 'X0', branch_label: str = ""):
        sht_macros.call_wreg_cont(tran=tran, dst_nwid_reg=dst_nwid_reg, callee_tran_label="ParallelGraphAbstraction_get_next_split_edge_store_iter_TR", cont_reg=ret, tmp_reg=tmp_reg, arg_reg0=iter_word0_reg, arg_reg1=iter_word1_reg, arg_reg2=key_addr_cont_reg, branch_label=branch_label)
