from EFA_v2 import EFA, State, Transition
import math


NWID_MASK = 0x7FFFFFF  # lower 27 bits


def hash(tran: Transition, seed_reg: str, key_reg: str, num_entries_reg: str) -> None:
    """
    key_reg overwritten as the masked val
    num_entrires has to be 2^N for now
    """
    tran.writeAction(f"subi {num_entries_reg} {num_entries_reg} {1}")
    tran.writeAction(f"hash {seed_reg} {key_reg}")
    tran.writeAction(f"andr {key_reg} {num_entries_reg} {key_reg}")


def call_wreg(tran: Transition, dst_nwid_reg: str, callee_tran_label: int, ret_tran_label: int, tmp_reg0: str, tmp_reg1: str, arg_reg0: str, arg_reg1: str, arg_reg2: str = "", branch_label: str = "") -> None:
    # tran.writeAction(f"{'' if branch_label == '' else branch_label + ': '}evi {tmp_reg0} {'X2'} 255 {0b100}")  # setup a new thread
    tran.writeAction(f"{'' if branch_label == '' else branch_label + ': '}evii {tmp_reg0} 255 255 {0b100}")  # setup a new thread
    tran.writeAction(f"evlb {tmp_reg0} {callee_tran_label}")  # update callee event
    tran.writeAction(f"ev {tmp_reg0} {tmp_reg0} {dst_nwid_reg} {dst_nwid_reg} 8")  # update destination nwid
    tran.writeAction(f"addi {'X2'} {tmp_reg1} {0}")
    tran.writeAction(f"evlb {tmp_reg1} {ret_tran_label}")  # update return event
    if arg_reg2 == "":
        tran.writeAction(f"sendr {tmp_reg0} {tmp_reg1} {arg_reg0} {arg_reg1}")  # generate call
    else:
        tran.writeAction(f"sendr3 {tmp_reg0} {tmp_reg1} {arg_reg0} {arg_reg1} {arg_reg2}")  # generate call


def call_wlm(tran: Transition, dst_nwid_reg: str, callee_tran_label: int, ret_tran_label: int, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, arg_lm_words: int, branch_label: str = "") -> None:
    # tran.writeAction(f"{'' if branch_label == '' else branch_label + ': '}evi {tmp_reg0} {'X2'} 255 {0b100}")  # setup a new thread
    tran.writeAction(f"{'' if branch_label == '' else branch_label + ': '}evii {tmp_reg0} 255 255 {0b100}")  # setup a new thread
    tran.writeAction(f"evlb {tmp_reg0} {callee_tran_label}")  # update callee event
    tran.writeAction(f"ev {tmp_reg0} {tmp_reg0} {dst_nwid_reg} {dst_nwid_reg} 8")  # update destination nwid
    tran.writeAction(f"addi {'X2'} {tmp_reg1} {0}")
    tran.writeAction(f"evlb {tmp_reg1} {ret_tran_label}")  # update return event
    tran.writeAction(f"send {tmp_reg0} {tmp_reg1} {arg_lm_addr_reg} {arg_lm_words} 0")  # generate call


def call_wreg_cont(tran: Transition, dst_nwid_reg: str, callee_tran_label: int, cont_reg: str, tmp_reg: str, arg_reg0: str, arg_reg1: str, arg_reg2: str = "", branch_label: str = "") -> None:
    # tran.writeAction(f"{'' if branch_label == '' else branch_label + ': '}evi {tmp_reg} {'X2'} 255 {0b100}")  # setup a new thread
    tran.writeAction(f"{'' if branch_label == '' else branch_label + ': '}evii {tmp_reg} 255 255 {0b100}")  # setup a new thread
    tran.writeAction(f"evlb {tmp_reg} {callee_tran_label}")  # update callee event
    tran.writeAction(f"ev {tmp_reg} {tmp_reg} {dst_nwid_reg} {dst_nwid_reg} 8")  # update destination nwid
    if arg_reg2 == "":
        tran.writeAction(f"sendr {tmp_reg} {cont_reg} {arg_reg0} {arg_reg1}")  # generate call
    else:
        tran.writeAction(f"sendr3 {tmp_reg} {cont_reg} {arg_reg0} {arg_reg1} {arg_reg2}")  # generate call


def call_wlm_cont(tran: Transition, dst_nwid_reg: str, callee_tran_label: int, cont_reg: str, tmp_reg: str, arg_lm_addr_reg: str, arg_lm_words: int, branch_label: str = "") -> None:
    # tran.writeAction(f"{'' if branch_label == '' else branch_label + ': '}evi {tmp_reg} {'X2'} 255 {0b100}")  # setup a new thread
    tran.writeAction(f"{'' if branch_label == '' else branch_label + ': '}evii {tmp_reg} 255 255 {0b100}")  # setup a new thread
    tran.writeAction(f"evlb {tmp_reg} {callee_tran_label}")  # update callee event
    tran.writeAction(f"ev {tmp_reg} {tmp_reg} {dst_nwid_reg} {dst_nwid_reg} 8")  # update destination nwid
    tran.writeAction(f"send {tmp_reg} {cont_reg} {arg_lm_addr_reg} {arg_lm_words} 0")  # generate call


def return_wreg(tran: Transition, cont_reg: str, arg_reg0: str, arg_reg1: str, arg_reg2: str = "", branch_label: str = "") -> None:
    if arg_reg2 == "":
        tran.writeAction(f"{'' if branch_label == '' else branch_label + ': '}sendr {cont_reg} {cont_reg} {arg_reg0} {arg_reg1} ")  # WARN: the continuation is invalid
    else:
        tran.writeAction(f"{'' if branch_label == '' else branch_label + ': '}sendr3 {cont_reg} {cont_reg} {arg_reg0} {arg_reg1} {arg_reg2}")  # WARN: the continuation is invalid


def return_wlm(tran: Transition, cont_reg: str, arg_lm_addr_reg: str, arg_lm_words: int, branch_label: str = "") -> None:
    tran.writeAction(f"send {cont_reg} {cont_reg} {arg_lm_addr_reg} {arg_lm_words} 0")  # WARN: the continuation is invalid


def dram_write_reg_ret(tran: Transition, addr_reg: str, ret_tran_label: int, tmp_reg: str, arg_reg0: str, arg_reg1: str = "", branch_label: str = "") -> None:
    tran.writeAction(f"{'' if branch_label == '' else branch_label + ': '}addi {'X2'} {tmp_reg} {0}")
    tran.writeAction(f"evlb {tmp_reg} {ret_tran_label}")  # update return event
    if arg_reg1 == "":
        tran.writeAction(f"sendmr {addr_reg} {tmp_reg} {arg_reg0}")
    else:
        tran.writeAction(f"sendmr2 {addr_reg} {tmp_reg} {arg_reg0} {arg_reg1}")


def dram_write_reg_cont(tran: Transition, addr_reg: str, cont_reg: str, tmp_reg: str, arg_reg0: str, arg_reg1: str = "", branch_label: str = "") -> None:
    if arg_reg1 == "":
        tran.writeAction(f"{'' if branch_label == '' else branch_label + ': '}sendmr {addr_reg} {cont_reg} {arg_reg0}")
    else:
        tran.writeAction(f"{'' if branch_label == '' else branch_label + ': '}sendmr2 {addr_reg} {cont_reg} {arg_reg0} {arg_reg1}")


def dram_write_lm_ret(tran: Transition, addr_reg: str, ret_tran_label: int, tmp_reg: str, arg_lm_addr_reg: str, arg_lm_words: int, branch_label: str = "") -> None:
    tran.writeAction(f"{'' if branch_label == '' else branch_label + ': '}addi {'X2'} {tmp_reg} {0}")
    tran.writeAction(f"evlb {tmp_reg} {ret_tran_label}")  # update return event
    tran.writeAction(f"sendm {addr_reg} {tmp_reg} {arg_lm_addr_reg} {arg_lm_words} {0b01}")


def dram_write_lm_cont(tran: Transition, addr_reg: str, cont_reg: str, arg_lm_addr_reg: str, arg_lm_words: int, branch_label: str = "") -> None:
    tran.writeAction(f"{'' if branch_label == '' else branch_label + ': '}sendm {addr_reg} {cont_reg} {arg_lm_addr_reg} {arg_lm_words} {0b01}")


def dram_read_ret(tran: Transition, addr_reg: str, ret_tran_label: int, tmp_reg: str, arg_lm_words: int, branch_label: str = "") -> None:
    tran.writeAction(f"{'' if branch_label == '' else branch_label + ': '}addi {'X2'} {tmp_reg} {0}")
    tran.writeAction(f"evlb {tmp_reg} {ret_tran_label}")  # update return event
    tran.writeAction(f"sendm {addr_reg} {tmp_reg} {tmp_reg} {arg_lm_words} {0b00}")  # WARN: invalid field for Xptr


def dram_read_cont(tran: Transition, addr_reg: str, cont_reg: str, arg_lm_words: int, branch_label: str = "") -> None:
    tran.writeAction(f"{'' if branch_label == '' else branch_label + ': '}sendm {addr_reg} {cont_reg} {cont_reg} {arg_lm_words} {0b00}")  # WARN: invalid field for Xptr


# def hashcall_wreg(tran: Transition, key_reg: str, start_nwid_reg: str, num_lanes_reg: str, seed_reg: str, callee_tran_label: int, ret_tran_label: int, tmp_reg0: str, arg_reg0: str, arg_reg1: str, arg_reg2: str = "") -> None:
#     """
#     Hash the specified key to the specified UpDown lane range, create a new thread on the hash mapped network ID, and trigger the specified transition.
#     2 arguments can be specified via registers.
#     Args:
#         tran: current transition
#         key_reg: register with the key for hashing
#         start_nwid_reg: register with starting NWID for mapping to the UpDown lane range
#         num_lanes: constant number of UpDown lanes to be mapped onto
#         seed: seed number for hashing
#         callee_tran_label: transistion label to be triggered in the newly created thread
#         ret_tran_label: continuation label for the triggered transition
#         tmp_reg0: free temp register 0
#         tmp_reg1: free temp register 1
#         arg_reg0: arugument 0 passing to the triggered transition
#         arg_reg1: arugument 1 passing to the triggered transition
#     """
#     tran.writeAction(f"mov_reg2reg {key_reg} {tmp_reg0}")
#     tran.writeAction(f"subi {num_lanes_reg} {num_lanes_reg} {1}")
#     tran.writeAction(f"hash {seed_reg} {tmp_reg0}")
#     tran.writeAction(f"andr {tmp_reg0} {tmp_reg0} {num_lanes_reg}")
#     tran.writeAction(f"add {tmp_reg0} {start_nwid_reg} {tmp_reg0}")
#     call_wreg(tran=tran, dst_nwid_reg=tmp_reg0, callee_tran_label=callee_tran_label, ret_tran_label=ret_tran_label, tmp_reg=num_lanes_reg, arg_reg0=arg_reg0, arg_reg1=arg_reg1, arg_reg2=arg_reg2)


# def hashcall_wlm(tran: Transition, key_reg: str, start_nwid_reg: str, num_lanes_reg: str, seed_reg: str, callee_tran_label: int, ret_tran_label: int, tmp_reg0: str, arg_lm_addr_reg: str, arg_lm_len: int) -> None:
#     """
#     Hash the specified key to the specified UpDown lane range, create a new thread on the hash mapped network ID, and trigger the specified transition.
#     Up to 8 arguments can be specified via LM address.
#     Args:
#         tran: current transition
#         key_reg: register with the key for hashing
#         start_nwid_reg: register with starting NWID for mapping to the UpDown lane range
#         num_lanes: constant number of UpDown lanes to be mapped onto
#         seed: seed number for hashing
#         callee_tran_label: transistion label to be triggered in the newly created thread
#         ret_tran_label: continuation label for the triggered transition
#         tmp_reg0: free temp register 0
#         tmp_reg1: free temp register 1
#         arg_lm_addr_reg: LM address which stores the arguments to be sent
#         arg_lm_len: number of byte to be send as arugments from the LM
#     """
#     tran.writeAction(f"mov_reg2reg {key_reg} {tmp_reg0}")
#     tran.writeAction(f"subi {num_lanes_reg} {num_lanes_reg} {1}")
#     tran.writeAction(f"hash {seed_reg} {tmp_reg0}")
#     tran.writeAction(f"andr {tmp_reg0} {tmp_reg0} {num_lanes_reg}")
#     tran.writeAction(f"add {tmp_reg0} {start_nwid_reg} {tmp_reg0}")
#     call_wlm(tran=tran, dst_nwid_reg=tmp_reg0, callee_tran_label=callee_tran_label, ret_tran_label=ret_tran_label, tmp_reg=num_lanes_reg, arg_lm_addr_reg=arg_lm_addr_reg, arg_lm_len=arg_lm_len)


# def return_wreg(tran: Transition, saved_cont_reg: str, arg_reg0: str, arg_reg1: str, arg_reg2: str = "") -> None:
#     tran.writeAction(f"sendr_wcont {saved_cont_reg} {saved_cont_reg} {arg_reg0} {arg_reg1} {arg_reg2}")  # WARN: the continuation is invalid


# def return_wlm(tran: Transition, saved_cont_reg: str, arg_lm_addr_reg: str, arg_lm_words: int) -> None:
#     tran.writeAction(f"send_wcont {saved_cont_reg} {saved_cont_reg} {arg_lm_addr_reg} {arg_lm_words}")  # WARN: the continuation is invalid


class SpinLock:
    """
    Spin Lock
    TODO: implement atomic version (required for sharing among lanes in a single UpDown)
    """
    ID_CNT = 0

    def __init__(self, atomic: bool = False) -> None:
        """
        Creation
        Parameters:
            lock_lm_addr: LM address for storing the lock, occupies 1 byte
        """
        self.LOCK_SIZE = 1
        self.ATOMIC = atomic
        self.ID = SpinLock.ID_CNT
        SpinLock.ID_CNT += 1

    def init(self, tran: Transition, lock_lm_addr_reg: str, tmp_reg: str) -> None:
        """
        """
        tran.writeAction(f"mov_imm2reg {tmp_reg} {0}")
        tran.writeAction(f"move {tmp_reg} {0}({lock_lm_addr_reg}) 0 {self.LOCK_SIZE}")

    def acquire(self, tran: Transition, lock_lm_addr_reg: str, tmp_reg: str, num_ops: int) -> None:
        """
        """
        if not self.ATOMIC:
            tran.writeAction(f"move {0}({lock_lm_addr_reg}) {tmp_reg} 0 {self.LOCK_SIZE}")
            tran.writeAction(f"beqc {tmp_reg} {0} {f'LB-spin_lock-{self.ID}-acquired'}")
            tran.writeAction(f"sendops_wcont {'X2'} {'X1'} {'X8'} {num_ops}")  # send to self with current continuation and all operands
            tran.writeAction("yield")
            tran.writeAction(f"{f'LB-spin_lock-{self.ID}-acquired'}: addi {tmp_reg} {tmp_reg} 1")  # increment lock
            tran.writeAction(f"move {tmp_reg} {0}({lock_lm_addr_reg}) 0 {self.LOCK_SIZE}")

    def release(self, tran: Transition, lock_lm_addr_reg: str, tmp_reg: str) -> None:
        """
        should not be called when not holding a lock
        """
        if not self.ATOMIC:
            tran.writeAction(f"move {0}({lock_lm_addr_reg}) {tmp_reg} 0 {self.LOCK_SIZE}")
            tran.writeAction(f"subi {tmp_reg} {tmp_reg} 1")  # decrement lock
            tran.writeAction(f"move {tmp_reg} {0}({lock_lm_addr_reg}) 0 {self.LOCK_SIZE}")


# class SpinLock_fixaddr:
#     """
#     Spin Lock
#     TODO: implement atomic version (required for sharing among lanes in a single UpDown)
#     """
#     ID_CNT = 0

#     def __init__(self, lock_lm_addr: int, atomic: bool = False) -> None:
#         """
#         Creation
#         Parameters:
#             lock_lm_addr: LM address for storing the lock, occupies 1 byte
#         """
#         self.LOCK_LM_ADDR = lock_lm_addr
#         self.LOCK_SIZE = 1
#         self.ATOMIC = atomic
#         self.ID = SpinLock_fixaddr.ID_CNT
#         SpinLock_fixaddr.ID_CNT += 1

#     def init(self, tran: Transition, tmp_reg: str) -> None:
#         """
#         """
#         tran.writeAction(f"mov_imm2reg {tmp_reg} {0}")
#         tran.writeAction(f"move {tmp_reg} {self.LOCK_LM_ADDR}(X7) 0 {self.LOCK_SIZE}")

#     def acquire(self, tran: Transition, tmp_reg: str, num_ops: int) -> None:
#         """
#         """
#         if not self.ATOMIC:
#             tran.writeAction(f"move {self.LOCK_LM_ADDR}(X7) {tmp_reg} 0 {self.LOCK_SIZE}")
#             tran.writeAction(f"beqc {tmp_reg} {0} {f'LB-spin_lock-{self.ID}-acquired'}")
#             tran.writeAction(f"sendops_wcont {'X2'} {'X1'} {'X8'} {num_ops - 2}")  # send to self with current continuation and all operands
#             tran.writeAction("yield")
#             tran.writeAction(f"{f'LB-spin_lock-{self.ID}-acquired'}: addi {tmp_reg} {tmp_reg} 1")  # increment lock
#             tran.writeAction(f"move {tmp_reg} {self.LOCK_LM_ADDR}(X7) 0 {self.LOCK_SIZE}")

#     def release(self, tran: Transition, tmp_reg: str) -> None:
#         """
#         should not be called when not holding a lock
#         """
#         if not self.ATOMIC:
#             tran.writeAction(f"move {self.LOCK_LM_ADDR}(X7) {tmp_reg} 0 {self.LOCK_SIZE}")
#             tran.writeAction(f"subi {tmp_reg} {tmp_reg} 1")  # decrement lock
#             tran.writeAction(f"move {tmp_reg} {self.LOCK_LM_ADDR}(X7) 0 {self.LOCK_SIZE}")


class MRSWLock:
    """
    Multi-reader Single-writer Lock
    TODO: implement atomic version (required for sharing among lanes in a single UpDown)
    """
    ID_CNT = 0

    def __init__(self, atomic: bool = False, debug=False) -> None:
        """
        Creation
        struct MRSWLock {
            U8 reader_lock;
            U8 writer_lock;
            U16 reader_count;
        }
        Parameters:
            lock_lm_addr: LM address for storing the lock, occupies 4 bytes.
        """
        self.READER_COUNTER_SIZE = 2
        self.LOCK_SIZE = 1
        self.ATOMIC = atomic
        self.DEBUG = debug
        self.ID = MRSWLock.ID_CNT
        MRSWLock.ID_CNT += 1
        self.CALL_CNT = 0

    def init(self, tran: Transition, lock_lm_addr_reg: str, tmp_reg: str) -> None:
        """
        """
        tran.writeAction(f"mov_imm2reg {tmp_reg} {0}")
        # TODO: change to a single 4 byte move
        tran.writeAction(f"move {tmp_reg} {0}({lock_lm_addr_reg}) 0 {self.LOCK_SIZE}")
        tran.writeAction(f"move {tmp_reg} {self.LOCK_SIZE}({lock_lm_addr_reg}) 0 {self.LOCK_SIZE}")
        tran.writeAction(f"move {tmp_reg} {self.LOCK_SIZE * 2}({lock_lm_addr_reg}) 0 {self.READER_COUNTER_SIZE}")
        if self.DEBUG:
            tran.writeAction(f"print '[DEBUG][NWID %d][MRSWLock {self.ID}] INIT' {'X0'}")
        self.CALL_CNT += 1

    def read_begin(self, tran: Transition, lock_lm_addr_reg: str, tmp_reg: str, num_ops: int) -> None:
        """
        """
        MACRO_NAME = "read_begin"
        if not self.ATOMIC:
            # acquire reader lock
            tran.writeAction(f"move {0}({lock_lm_addr_reg}) {tmp_reg} 0 {self.LOCK_SIZE}")  # get reader lock
            tran.writeAction(f"beqc {tmp_reg} {0} {f'LB-mrsw_lock-{self.ID}-{MACRO_NAME}-{self.CALL_CNT}-reader_acquired'}")
            if self.DEBUG:
                tran.writeAction(f"print '[DEBUG][NWID %d][MRSWLock {self.ID}] READ_BEGIN: reader lock busy, delay current event' {'X0'}")
            tran.writeAction(f"sendops_wcont {'X2'} {'X1'} {'X8'} {num_ops}")  # delay current event, send to self with current continuation and all operands
            tran.writeAction("yield")
            tran.writeAction(f"{f'LB-mrsw_lock-{self.ID}-{MACRO_NAME}-{self.CALL_CNT}-reader_acquired'}: addi {tmp_reg} {tmp_reg} 1")  # increment reader lock
            tran.writeAction(f"move {tmp_reg} {0}({lock_lm_addr_reg}) 0 {self.LOCK_SIZE}")
            # if reader counter is 0, check writer lock
            tran.writeAction(f"move {self.LOCK_SIZE * 2}({lock_lm_addr_reg}) {tmp_reg} 0 {self.READER_COUNTER_SIZE}")  # get reader counter
            if self.DEBUG:
                tran.writeAction(f"print '[DEBUG][NWID %d][MRSWLock {self.ID}] READ_BEGIN: reader lock acquired, reader counter = %d' {'X0'} {tmp_reg}")
            tran.writeAction(f"bgtc {tmp_reg} {0} {f'LB-mrsw_lock-{self.ID}-{MACRO_NAME}-{self.CALL_CNT}-inc_release_reader'}")
            if self.DEBUG:
                tran.writeAction(f"print '[DEBUG][NWID %d][MRSWLock {self.ID}] READ_BEGIN: first active reader, checking writer lock...' {'X0'}")
            tran.writeAction(f"move {self.LOCK_SIZE}({lock_lm_addr_reg}) {tmp_reg} 0 {self.LOCK_SIZE}")  # get writer lock
            tran.writeAction(f"bgtc {tmp_reg} {0} {f'LB-mrsw_lock-{self.ID}-{MACRO_NAME}-{self.CALL_CNT}-release_reader_spin'}")  # writer is locked, spin
            # acquire writer lock
            tran.writeAction(f"addi {tmp_reg} {tmp_reg} 1")  # increment lock
            tran.writeAction(f"move {tmp_reg} {self.LOCK_SIZE}({lock_lm_addr_reg}) 0 {self.LOCK_SIZE}")
            if self.DEBUG:
                tran.writeAction(f"print '[DEBUG][NWID %d][MRSWLock {self.ID}] READ_BEGIN: writer lock free, writer lock acquired' {'X0'}")
            tran.writeAction(f"jmp {f'LB-mrsw_lock-{self.ID}-{MACRO_NAME}-{self.CALL_CNT}-inc_release_reader'}")
            # release reader lock & spin
            tran.writeAction(f"{f'LB-mrsw_lock-{self.ID}-{MACRO_NAME}-{self.CALL_CNT}-release_reader_spin'}: move {0}({lock_lm_addr_reg}) {tmp_reg} 0 {self.LOCK_SIZE}")
            if self.DEBUG:
                tran.writeAction(f"print '[DEBUG][NWID %d][MRSWLock {self.ID}] READ_BEGIN: writer lock busy, free reader lock & delay current event' {'X0'}")
            tran.writeAction(f"subi {tmp_reg} {tmp_reg} 1")  # decrement lock
            tran.writeAction(f"move {tmp_reg} {0}({lock_lm_addr_reg}) 0 {self.LOCK_SIZE}")
            tran.writeAction(f"sendops_wcont {'X2'} {'X1'} {'X8'} {num_ops}")  # send to self with current continuation and all operands
            tran.writeAction("yield")
            # increment reader counter & release reader lock
            # increment reader counter
            tran.writeAction(f"{f'LB-mrsw_lock-{self.ID}-{MACRO_NAME}-{self.CALL_CNT}-inc_release_reader'}: move {self.LOCK_SIZE * 2}({lock_lm_addr_reg}) {tmp_reg} 0 {self.READER_COUNTER_SIZE}")
            if self.DEBUG:
                tran.writeAction(f"print '[DEBUG][NWID %d][MRSWLock {self.ID}] READ_BEGIN: read permitted, increase reader counter & release reader lock' {'X0'}")
            tran.writeAction(f"addi {tmp_reg} {tmp_reg} 1")
            tran.writeAction(f"move {tmp_reg} {self.LOCK_SIZE * 2}({lock_lm_addr_reg}) 0 {self.READER_COUNTER_SIZE}")
            # release reader lock
            tran.writeAction(f"move {0}({lock_lm_addr_reg}) {tmp_reg} 0 {self.LOCK_SIZE}")
            tran.writeAction(f"subi {tmp_reg} {tmp_reg} 1")  # decrement lock
            tran.writeAction(f"move {tmp_reg} {0}({lock_lm_addr_reg}) 0 {self.LOCK_SIZE}")
        self.CALL_CNT += 1

    def read_begin_var(self, tran: Transition, lock_lm_addr_reg: str, tmp_reg: str) -> None:
        """
        """
        MACRO_NAME = "read_begin"
        if not self.ATOMIC:
            # acquire reader lock
            tran.writeAction(f"move {0}({lock_lm_addr_reg}) {tmp_reg} 0 {self.LOCK_SIZE}")  # get reader lock
            tran.writeAction(f"beqc {tmp_reg} {0} {f'LB-mrsw_lock-{self.ID}-{MACRO_NAME}-{self.CALL_CNT}-reader_acquired'}")
            # get number of operands
            tran.writeAction(f"rshift_and_imm {'X2'} {tmp_reg} {20} {0b111}")
            for i in range(0, 8):
                tran.writeAction(f"beqi {tmp_reg} {i} {f'LB-mrsw_lock-{self.ID}-{MACRO_NAME}-{self.CALL_CNT}-reader_wait_{i + 2}'}")
            if self.DEBUG:
                tran.writeAction(f"print '[DEBUG][NWID %d][MRSWLock {self.ID}] READER_BEGIN: SHOULDN'T REACH HERE!!!!' {'X0'}")

            tran.writeAction(f"{f'LB-mrsw_lock-{self.ID}-{MACRO_NAME}-{self.CALL_CNT}-reader_acquired'}: addi {tmp_reg} {tmp_reg} 1")  # increment reader lock
            tran.writeAction(f"move {tmp_reg} {0}({lock_lm_addr_reg}) 0 {self.LOCK_SIZE}")
            # if reader counter is 0, check writer lock
            tran.writeAction(f"move {self.LOCK_SIZE * 2}({lock_lm_addr_reg}) {tmp_reg} 0 {self.READER_COUNTER_SIZE}")  # get reader counter
            if self.DEBUG:
                tran.writeAction(f"print '[DEBUG][NWID %d][MRSWLock {self.ID}] READ_BEGIN: reader lock acquired, reader counter = %d' {'X0'} {tmp_reg}")
            tran.writeAction(f"bgtc {tmp_reg} {0} {f'LB-mrsw_lock-{self.ID}-{MACRO_NAME}-{self.CALL_CNT}-inc_release_reader'}")
            if self.DEBUG:
                tran.writeAction(f"print '[DEBUG][NWID %d][MRSWLock {self.ID}] READ_BEGIN: first active reader, checking writer lock...' {'X0'}")
            tran.writeAction(f"move {self.LOCK_SIZE}({lock_lm_addr_reg}) {tmp_reg} 0 {self.LOCK_SIZE}")  # get writer lock
            tran.writeAction(f"bgtc {tmp_reg} {0} {f'LB-mrsw_lock-{self.ID}-{MACRO_NAME}-{self.CALL_CNT}-release_reader_spin'}")  # writer is locked, spin
            # acquire writer lock
            tran.writeAction(f"addi {tmp_reg} {tmp_reg} 1")  # increment lock
            tran.writeAction(f"move {tmp_reg} {self.LOCK_SIZE}({lock_lm_addr_reg}) 0 {self.LOCK_SIZE}")
            if self.DEBUG:
                tran.writeAction(f"print '[DEBUG][NWID %d][MRSWLock {self.ID}] READ_BEGIN: writer lock free, writer lock acquired' {'X0'}")
            tran.writeAction(f"jmp {f'LB-mrsw_lock-{self.ID}-{MACRO_NAME}-{self.CALL_CNT}-inc_release_reader'}")
            # release reader lock & spin
            tran.writeAction(f"{f'LB-mrsw_lock-{self.ID}-{MACRO_NAME}-{self.CALL_CNT}-release_reader_spin'}: move {0}({lock_lm_addr_reg}) {tmp_reg} 0 {self.LOCK_SIZE}")
            if self.DEBUG:
                tran.writeAction(f"print '[DEBUG][NWID %d][MRSWLock {self.ID}] READ_BEGIN: writer lock busy, free reader lock & delay current event' {'X0'}")
            tran.writeAction(f"subi {tmp_reg} {tmp_reg} 1")  # decrement lock
            tran.writeAction(f"move {tmp_reg} {0}({lock_lm_addr_reg}) 0 {self.LOCK_SIZE}")
            # get number of operands
            tran.writeAction(f"rshift_and_imm {'X2'} {tmp_reg} {20} {0b111}")
            for i in range(0, 8):
                tran.writeAction(f"beqi {tmp_reg} {i} {f'LB-mrsw_lock-{self.ID}-{MACRO_NAME}-{self.CALL_CNT}-reader_wait_{i + 2}'}")
            if self.DEBUG:
                tran.writeAction(f"print '[DEBUG][NWID %d][MRSWLock {self.ID}] READER_BEGIN: SHOULDN'T REACH HERE!!!!' {'X0'}")

            # increment reader counter & release reader lock
            # increment reader counter
            tran.writeAction(f"{f'LB-mrsw_lock-{self.ID}-{MACRO_NAME}-{self.CALL_CNT}-inc_release_reader'}: move {self.LOCK_SIZE * 2}({lock_lm_addr_reg}) {tmp_reg} 0 {self.READER_COUNTER_SIZE}")
            if self.DEBUG:
                tran.writeAction(f"print '[DEBUG][NWID %d][MRSWLock {self.ID}] READ_BEGIN: read permitted, increase reader counter & release reader lock' {'X0'}")
            tran.writeAction(f"addi {tmp_reg} {tmp_reg} 1")
            tran.writeAction(f"move {tmp_reg} {self.LOCK_SIZE * 2}({lock_lm_addr_reg}) 0 {self.READER_COUNTER_SIZE}")
            # release reader lock
            tran.writeAction(f"move {0}({lock_lm_addr_reg}) {tmp_reg} 0 {self.LOCK_SIZE}")
            tran.writeAction(f"subi {tmp_reg} {tmp_reg} 1")  # decrement lock
            tran.writeAction(f"move {tmp_reg} {0}({lock_lm_addr_reg}) 0 {self.LOCK_SIZE}")

            for i in range(0, 8):
                tran.writeAction(f"{f'LB-mrsw_lock-{self.ID}-{MACRO_NAME}-{self.CALL_CNT}-reader_wait_{i + 2}'}: sendops_wcont {'X2'} {'X1'} {'X8'} {i + 2}")  # send to self with current continuation and all operands
                if self.DEBUG:
                    tran.writeAction(f"print '[DEBUG][NWID %d][MRSWLock {self.ID}] READER_BEGIN: reader lock busy, delay current event ({i + 2} operands)' {'X0'}")
                tran.writeAction("yield")
        self.CALL_CNT += 1

    def read_end(self, tran: Transition, lock_lm_addr_reg: str, tmp_reg: str) -> None:
        """
        """
        MACRO_NAME = "read_end"
        if not self.ATOMIC:
            # acquire reader lock
            tran.writeAction(f"{f'LB-mrsw_lock-{self.ID}-{MACRO_NAME}-{self.CALL_CNT}-reader_spinwait'}: move {0}({lock_lm_addr_reg}) {tmp_reg} 0 {self.LOCK_SIZE}")  # get reader lock
            tran.writeAction(f"beqc {tmp_reg} {0} {f'LB-mrsw_lock-{self.ID}-{MACRO_NAME}-{self.CALL_CNT}-reader_acquired'}")
            if self.DEBUG:
                tran.writeAction(f"print '[DEBUG][NWID %d][MRSWLock {self.ID}] READ_END: reader lock busy, loop spin wait (to be freed from another lane)' {'X0'}")
            tran.writeAction(f"jmp {f'LB-mrsw_lock-{self.ID}-{MACRO_NAME}-{self.CALL_CNT}-reader_spinwait'}")  # loop spin wait
            tran.writeAction(f"{f'LB-mrsw_lock-{self.ID}-{MACRO_NAME}-{self.CALL_CNT}-reader_acquired'}: addi {tmp_reg} {tmp_reg} 1")  # increment lock
            tran.writeAction(f"move {tmp_reg} {0}({lock_lm_addr_reg}) 0 {self.LOCK_SIZE}")
            # if reader counter is 1, check writer lock
            tran.writeAction(f"move {self.LOCK_SIZE * 2}({lock_lm_addr_reg}) {tmp_reg} 0 {self.READER_COUNTER_SIZE}")  # get writer lock
            if self.DEBUG:
                tran.writeAction(f"print '[DEBUG][NWID %d][MRSWLock {self.ID}] READ_END: reader lock acquired, reader counter = %d' {'X0'} {tmp_reg}")
            tran.writeAction(f"bgtc {tmp_reg} {1} {f'LB-mrsw_lock-{self.ID}-{MACRO_NAME}-{self.CALL_CNT}-dec_release_reader'}")
            if self.DEBUG:
                tran.writeAction(f"print '[DEBUG][NWID %d][MRSWLock {self.ID}] READ_END: last active reader, releasing writer lock' {'X0'}")
            tran.writeAction(f"move {self.LOCK_SIZE}({lock_lm_addr_reg}) {tmp_reg} 0 {self.LOCK_SIZE}")
            tran.writeAction(f"beqc {tmp_reg} {0} {f'LB-mrsw_lock-{self.ID}-{MACRO_NAME}-{self.CALL_CNT}-dec_release_reader'}")  # writer not locked??
            # release writer lock
            tran.writeAction(f"subi {tmp_reg} {tmp_reg} 1")  # decrement lock
            tran.writeAction(f"move {tmp_reg} {self.LOCK_SIZE}({lock_lm_addr_reg}) 0 {self.LOCK_SIZE}")
            # increment reader counter & release reader lock
            # decrement reader counter
            tran.writeAction(f"{f'LB-mrsw_lock-{self.ID}-{MACRO_NAME}-{self.CALL_CNT}-dec_release_reader'}: move {self.LOCK_SIZE * 2}({lock_lm_addr_reg}) {tmp_reg} 0 {self.READER_COUNTER_SIZE}")
            if self.DEBUG:
                tran.writeAction(f"print '[DEBUG][NWID %d][MRSWLock {self.ID}] READ_END: read finished, decrement reader counter & release reader lock' {'X0'}")
            tran.writeAction(f"subi {tmp_reg} {tmp_reg} 1")
            tran.writeAction(f"move {tmp_reg} {self.LOCK_SIZE * 2}({lock_lm_addr_reg}) 0 {self.READER_COUNTER_SIZE}")
            # release reader lock
            tran.writeAction(f"move {0}({lock_lm_addr_reg}) {tmp_reg} 0 {self.LOCK_SIZE}")
            tran.writeAction(f"subi {tmp_reg} {tmp_reg} 1")  # decrement lock
            tran.writeAction(f"move {tmp_reg} {0}({lock_lm_addr_reg}) 0 {self.LOCK_SIZE}")
        self.CALL_CNT += 1

    def write_begin(self, tran: Transition, lock_lm_addr_reg: str, tmp_reg: str, num_ops: int) -> None:
        """
        """
        MACRO_NAME = "write_begin"
        if not self.ATOMIC:
            tran.writeAction(f"move {self.LOCK_SIZE}({lock_lm_addr_reg}) {tmp_reg} 0 {self.LOCK_SIZE}")
            tran.writeAction(f"beqc {tmp_reg} {0} {f'LB-mrsw_lock-{self.ID}-{MACRO_NAME}-{self.CALL_CNT}-acquired'}")
            if self.DEBUG:
                tran.writeAction(f"print '[DEBUG][NWID %d][MRSWLock {self.ID}] WRITE_BEGIN: writer lock busy, delay current event' {'X0'}")
            tran.writeAction(f"sendops_wcont {'X2'} {'X1'} {'X8'} {num_ops}")  # send to self with current continuation and all operands
            tran.writeAction("yield")
            tran.writeAction(f"{f'LB-mrsw_lock-{self.ID}-{MACRO_NAME}-{self.CALL_CNT}-acquired'}: addi {tmp_reg} {tmp_reg} 1")  # increment lock
            tran.writeAction(f"move {tmp_reg} {self.LOCK_SIZE}({lock_lm_addr_reg}) 0 {self.LOCK_SIZE}")
            if self.DEBUG:
                tran.writeAction(f"print '[DEBUG][NWID %d][MRSWLock {self.ID}] WRITE_BEGIN: writer lock free, acquire writer lock' {'X0'}")
        self.CALL_CNT += 1

    def write_begin_var(self, tran: Transition, lock_lm_addr_reg: str, tmp_reg: str) -> None:
        """
        """
        MACRO_NAME = "write_begin"
        if not self.ATOMIC:
            tran.writeAction(f"move {self.LOCK_SIZE}({lock_lm_addr_reg}) {tmp_reg} 0 {self.LOCK_SIZE}")
            tran.writeAction(f"beqc {tmp_reg} {0} {f'LB-mrsw_lock-{self.ID}-{MACRO_NAME}-{self.CALL_CNT}-acquired'}")
            # get number of operands
            tran.writeAction(f"rshift_and_imm {'X2'} {tmp_reg} {20} {0b111}")
            for i in range(0, 8):
                tran.writeAction(f"beqi {tmp_reg} {i} {f'LB-mrsw_lock-{self.ID}-{MACRO_NAME}-{self.CALL_CNT}-writer_wait_{i + 2}'}")
            if self.DEBUG:
                tran.writeAction(f"print '[DEBUG][NWID %d][MRSWLock {self.ID}] WRITE_BEGIN: SHOULDN'T REACH HERE!!!!' {'X0'}")
            for i in range(0, 8):
                tran.writeAction(f"{f'LB-mrsw_lock-{self.ID}-{MACRO_NAME}-{self.CALL_CNT}-writer_wait_{i + 2}'}: sendops_wcont {'X2'} {'X1'} {'X8'} {i + 2}")  # send to self with current continuation and all operands
                if self.DEBUG:
                    tran.writeAction(f"print '[DEBUG][NWID %d][MRSWLock {self.ID}] WRITE_BEGIN: writer lock busy, delay current event ({i + 2} operands)' {'X0'}")
                tran.writeAction("yield")
            tran.writeAction(f"{f'LB-mrsw_lock-{self.ID}-{MACRO_NAME}-{self.CALL_CNT}-acquired'}: addi {tmp_reg} {tmp_reg} 1")  # increment lock
            tran.writeAction(f"move {tmp_reg} {self.LOCK_SIZE}({lock_lm_addr_reg}) 0 {self.LOCK_SIZE}")
            if self.DEBUG:
                tran.writeAction(f"print '[DEBUG][NWID %d][MRSWLock {self.ID}] WRITE_BEGIN: writer lock free, acquire writer lock' {'X0'}")
        self.CALL_CNT += 1

    def write_end(self, tran: Transition, lock_lm_addr_reg: str, tmp_reg: str) -> None:
        """
        """
        if not self.ATOMIC:
            tran.writeAction(f"move {self.LOCK_SIZE}({lock_lm_addr_reg}) {tmp_reg} 0 {self.LOCK_SIZE}")
            tran.writeAction(f"subi {tmp_reg} {tmp_reg} 1")  # decrement lock
            tran.writeAction(f"move {tmp_reg} {self.LOCK_SIZE}({lock_lm_addr_reg}) 0 {self.LOCK_SIZE}")
            if self.DEBUG:
                tran.writeAction(f"print '[DEBUG][NWID %d][MRSWLock {self.ID}] WRITE_END: writer lock freed' {'X0'}")
        self.CALL_CNT += 1


# class MRSWLock_fixaddr:
#     """
#     Multi-reader Single-writer Lock
#     TODO: implement atomic version (required for sharing among lanes in a single UpDown)
#     """
#     ID_CNT = 0

#     def __init__(self, lock_lm_addr: int, atomic: bool = False) -> None:
#         """
#         Creation
#         Parameters:
#             lock_lm_addr: LM address for storing the lock, occupies 4 bytes.
#         """
#         self.READER_LOCK_LM_ADDR = lock_lm_addr  # 1 byte
#         self.WRITER_LOCK_LM_ADDR = lock_lm_addr + 1  # 1 byte
#         self.READER_COUNTER_LM_ADDR = lock_lm_addr + 2  # 2 bytes
#         self.READER_COUNTER_SIZE = 2
#         self.LOCK_SIZE = 1
#         self.ATOMIC = atomic
#         self.ID = MRSWLock_fixaddr.ID_CNT
#         MRSWLock_fixaddr.ID_CNT += 1

#     def init(self, tran: Transition, tmp_reg: str) -> None:
#         """
#         """
#         tran.writeAction(f"mov_imm2reg {tmp_reg} {0}")
#         tran.writeAction(f"move {tmp_reg} {self.READER_COUNTER_LM_ADDR}(X7) 0 {self.READER_COUNTER_SIZE}")
#         tran.writeAction(f"move {tmp_reg} {self.READER_LOCK_LM_ADDR}(X7) 0 {self.LOCK_SIZE}")
#         tran.writeAction(f"move {tmp_reg} {self.WRITER_LOCK_LM_ADDR}(X7) 0 {self.LOCK_SIZE}")

#     def read_begin(self, tran: Transition, tmp_reg: str, num_ops: int) -> None:
#         """
#         """
#         MACRO_NAME = "read_begin"
#         if not self.ATOMIC:
#             # acquire reader lock
#             tran.writeAction(f"move {self.READER_LOCK_LM_ADDR}(X7) {tmp_reg} 0 {self.LOCK_SIZE}")
#             tran.writeAction(f"beqc {tmp_reg} {0} {f'LB-mrsw_lock-{self.ID}-{MACRO_NAME}-reader_acquired'}")
#             tran.writeAction(f"sendops_wcont {'X2'} {'X1'} {'X8'} {num_ops - 2}")  # send to self with current continuation and all operands
#             tran.writeAction("yield")
#             tran.writeAction(f"{f'LB-mrsw_lock-{self.ID}-{MACRO_NAME}-reader_acquired'}: addi {tmp_reg} {tmp_reg} 1")  # increment lock
#             tran.writeAction(f"move {tmp_reg} {self.READER_LOCK_LM_ADDR}(X7) 0 {self.LOCK_SIZE}")
#             # if reader counter is 0, check writer lock
#             tran.writeAction(f"move {self.READER_COUNTER_LM_ADDR}(X7) {tmp_reg} 0 {self.READER_COUNTER_SIZE}")
#             tran.writeAction(f"bgtc {tmp_reg} {0} {f'LB-mrsw_lock-{self.ID}-{MACRO_NAME}-inc_release_reader'}")
#             tran.writeAction(f"move {self.WRITER_LOCK_LM_ADDR}(X7) {tmp_reg} 0 {self.LOCK_SIZE}")
#             tran.writeAction(f"bgtc {tmp_reg} {0} {f'LB-mrsw_lock-{self.ID}-{MACRO_NAME}-release_reader_spin'}")  # writer is locked, spin
#             # acquire writer lock
#             tran.writeAction(f"addi {tmp_reg} {tmp_reg} 1")  # increment lock
#             tran.writeAction(f"move {tmp_reg} {self.WRITER_LOCK_LM_ADDR}(X7) 0 {self.LOCK_SIZE}")
#             tran.writeAction(f"jmp {f'LB-mrsw_lock-{self.ID}-{MACRO_NAME}-inc_release_reader'}")
#             # release reader lock & spin
#             tran.writeAction(f"{f'LB-mrsw_lock-{self.ID}-{MACRO_NAME}-release_reader_spin'}: move {self.READER_LOCK_LM_ADDR}(X7) {tmp_reg} 0 {self.LOCK_SIZE}")
#             tran.writeAction(f"subi {tmp_reg} {tmp_reg} 1")  # decrement lock
#             tran.writeAction(f"move {tmp_reg} {self.READER_LOCK_LM_ADDR}(X7) 0 {self.LOCK_SIZE}")
#             tran.writeAction(f"sendops_wcont {'X2'} {'X1'} {'X8'} {num_ops - 2}")  # send to self with current continuation and all operands
#             tran.writeAction("yield")
#             # increment reader counter & release reader lock
#             # increment reader counter
#             tran.writeAction(f"{f'LB-mrsw_lock-{self.ID}-{MACRO_NAME}-inc_release_reader'}: move {self.READER_COUNTER_LM_ADDR}(X7) {tmp_reg} 0 {self.READER_COUNTER_SIZE}")
#             tran.writeAction(f"addi {tmp_reg} {tmp_reg} 1")
#             tran.writeAction(f"move {tmp_reg} {self.READER_COUNTER_LM_ADDR}(X7) 0 {self.READER_COUNTER_SIZE}")
#             # release reader lock
#             tran.writeAction(f"move {self.READER_LOCK_LM_ADDR}(X7) {tmp_reg} 0 {self.LOCK_SIZE}")
#             tran.writeAction(f"subi {tmp_reg} {tmp_reg} 1")  # decrement lock
#             tran.writeAction(f"move {tmp_reg} {self.READER_LOCK_LM_ADDR}(X7) 0 {self.LOCK_SIZE}")

#     def read_end(self, tran: Transition, tmp_reg: str) -> None:
#         """
#         """
#         MACRO_NAME = "read_end"
#         if not self.ATOMIC:
#             # acquire reader lock
#             tran.writeAction(f"{f'LB-mrsw_lock-{self.ID}-{MACRO_NAME}-reader_spinwait'}: move {self.READER_LOCK_LM_ADDR}(X7) {tmp_reg} 0 {self.LOCK_SIZE}")
#             tran.writeAction(f"beqc {tmp_reg} {0} {f'LB-mrsw_lock-{self.ID}-{MACRO_NAME}-reader_acquired'}")
#             tran.writeAction(f"jmp {f'LB-mrsw_lock-{self.ID}-{MACRO_NAME}-reader_spinwait'}")  # loop spin wait
#             tran.writeAction(f"{f'LB-mrsw_lock-{self.ID}-{MACRO_NAME}-reader_acquired'}: addi {tmp_reg} {tmp_reg} 1")  # increment lock
#             tran.writeAction(f"move {tmp_reg} {self.READER_LOCK_LM_ADDR}(X7) 0 {self.LOCK_SIZE}")
#             # if reader counter is 1, check writer lock
#             tran.writeAction(f"move {self.READER_COUNTER_LM_ADDR}(X7) {tmp_reg} 0 {self.READER_COUNTER_SIZE}")
#             tran.writeAction(f"bgtc {tmp_reg} {1} {f'LB-mrsw_lock-{self.ID}-{MACRO_NAME}-dec_release_reader'}")
#             tran.writeAction(f"move {self.WRITER_LOCK_LM_ADDR}(X7) {tmp_reg} 0 {self.LOCK_SIZE}")
#             tran.writeAction(f"beqc {tmp_reg} {0} {f'LB-mrsw_lock-{self.ID}-{MACRO_NAME}-dec_release_reader'}")  # writer not locked??
#             # release writer lock
#             tran.writeAction(f"subi {tmp_reg} {tmp_reg} 1")  # decrement lock
#             tran.writeAction(f"move {tmp_reg} {self.WRITER_LOCK_LM_ADDR}(X7) 0 {self.LOCK_SIZE}")
#             # increment reader counter & release reader lock
#             # decrement reader counter
#             tran.writeAction(f"{f'LB-mrsw_lock-{self.ID}-{MACRO_NAME}-dec_release_reader'}: move {self.READER_COUNTER_LM_ADDR}(X7) {tmp_reg} 0 {self.READER_COUNTER_SIZE}")
#             tran.writeAction(f"subi {tmp_reg} {tmp_reg} 1")
#             tran.writeAction(f"move {tmp_reg} {self.READER_COUNTER_LM_ADDR}(X7) 0 {self.READER_COUNTER_SIZE}")
#             # release reader lock
#             tran.writeAction(f"move {self.READER_LOCK_LM_ADDR}(X7) {tmp_reg} 0 {self.LOCK_SIZE}")
#             tran.writeAction(f"subi {tmp_reg} {tmp_reg} 1")  # decrement lock
#             tran.writeAction(f"move {tmp_reg} {self.READER_LOCK_LM_ADDR}(X7) 0 {self.LOCK_SIZE}")

#     def write_begin(self, tran: Transition, tmp_reg: str, num_ops: int) -> None:
#         """
#         """
#         MACRO_NAME = "write_begin"
#         if not self.ATOMIC:
#             tran.writeAction(f"move {self.WRITER_LOCK_LM_ADDR}(X7) {tmp_reg} 0 {self.LOCK_SIZE}")
#             tran.writeAction(f"beqc {tmp_reg} {0} {f'LB-mrsw_lock-{self.ID}-{MACRO_NAME}-acquired'}")
#             tran.writeAction(f"sendops_wcont {'X2'} {'X1'} {'X8'} {num_ops - 2}")  # send to self with current continuation and all operands
#             tran.writeAction("yield")
#             tran.writeAction(f"{f'LB-mrsw_lock-{self.ID}-{MACRO_NAME}-acquired'}: addi {tmp_reg} {tmp_reg} 1")  # increment lock
#             tran.writeAction(f"move {tmp_reg} {self.LOCK_LM_ADDR}(X7) 0 {self.LOCK_SIZE}")

#     def write_end(self, tran: Transition, tmp_reg: str) -> None:
#         """
#         """
#         if not self.ATOMIC:
#             tran.writeAction(f"move {self.WRITER_LOCK_LM_ADDR}(X7) {tmp_reg} 0 {self.LOCK_SIZE}")
#             tran.writeAction(f"subi {tmp_reg} {tmp_reg} 1")  # decrement lock
#             tran.writeAction(f"move {tmp_reg} {self.LOCK_LM_ADDR}(X7) 0 {self.LOCK_SIZE}")
