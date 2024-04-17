# from EFA_v2 import EFA, State, Transition
from linker.EFAProgram import efaProgram
# import sht_macros
from sht import SHT

import random

def call_wreg(tran, dst_nwid_reg: str, callee_tran_label: int, ret_tran_label: int, tmp_reg0: str, tmp_reg1: str, arg_reg0: str, arg_reg1: str, arg_reg2: str = "") -> None:
    tran.writeAction(f"ev_update_2 {tmp_reg0} {callee_tran_label} 255 5")  # setup callee event in a new thread
    tran.writeAction(f"ev_update_reg_2 {tmp_reg0} {tmp_reg0} {dst_nwid_reg} {dst_nwid_reg} 8")  # update destination nwid
    if arg_reg2 == "":
        tran.writeAction(f"sendr_wret {tmp_reg0} {ret_tran_label} {arg_reg0} {arg_reg1} {tmp_reg1}")  # generate call
    else:
        tran.writeAction(f"sendr3_wret {tmp_reg0} {ret_tran_label} {arg_reg0} {arg_reg1} {arg_reg2} {tmp_reg1}")  # generate call


def call_wlm(tran, dst_nwid_reg: str, callee_tran_label: int, ret_tran_label: int, tmp_reg0: str, tmp_reg1: str, arg_lm_addr_reg: str, arg_lm_words: int) -> None:
    tran.writeAction(f"ev_update_2 {tmp_reg0} {callee_tran_label} 255 5")  # setup callee event in a new thread
    tran.writeAction(f"ev_update_reg_2 {tmp_reg0} {tmp_reg0} {dst_nwid_reg} {dst_nwid_reg} 8")  # update destination nwid
    tran.writeAction(f"send_wret {tmp_reg0} {ret_tran_label} {arg_lm_addr_reg} {arg_lm_words} {tmp_reg1}")  # generate call

def return_wreg(tran, saved_cont_reg: str, arg_reg0: str, arg_reg1: str) -> None:
    tran.writeAction(f"sendr_wcont {saved_cont_reg} {saved_cont_reg} {arg_reg0} {arg_reg1}")  # WARN: the continuation is invalid


@efaProgram
def SHTConcLiteTestEFA(efa):
    """
    Lite concurrency test code for SHT.
    TODO: change some gets to deletes
    Way to run this:
        1.  Make install
            make
        2.  Run in command line (num_lanes, num_buckets_per_lane), e.g.:
            ./sht_concurrency_test.exe 128 64
    Estimated output:
        1.  If SHT work, no "ERROR" should be found in the output
        2.  Should see:
            Gather1 DONE.
            Gather2 DONE.
            Gather3 DONE.
            Gather4 DONE.
            Gather5 DONE.
            Gather6 DONE.
            Gather7 DONE.
            Gather8 DONE.
            Gather9 DONE.
            Gather10 DONE.
            Gather11 DONE.
    What this test:
        1.  Initialize the SHT
        2.  Gather0:    Upon initialization finish, send SHT info to each lane
        3.              Each lane setup SHT, send back ack
        4.  Gather1:    Upon all ack receive, send update for different keys to each lane
        5.              Each lane send update request to SHT, wait for respond
        6.              Each lane receive update ack, check X8, send back ack
        7.  Gather2:    Upon all ack receive, send get for different keys to each lane
        8.              Each lane send get request to SHT, wait for respond
        9.              Each lane receive get ack, check X8, check value in X9, send back ack
        10. Gather3:    Upon all ack receive, send update/get for different keys to each lane
        11.             Each lane send update/get request to SHT, wait for respond
        12.             Each lane receive update/get ack, check X8, check value in X9, send back ack
        13. Gather4:    Upon all ack receive, send delete for different keys to each lane
        14.             Each lane send delete request to SHT, wait for respond
        15.             Each lane receive delete ack, check X8, send back ack
        16. Gather5:    Upon all ack receive, send update for different keys to each lane
        17.             Each lane send update request to SHT, wait for respond
        18.             Each lane receive update ack, check X8, send back ack
        19. Gather6:    Upon all ack receive, send update/get/delete for different keys to each lane
        20.             Each lane send update/get/delete request to SHT, wait for respond
        21.             Each lane receive update/get/delete ack, check X8, check value in X9, send back ack
        22. Gather7:    Upon all ack receive, send update for same key to each lane
        23.             Each lane send update request to SHT, wait for respond
        24.             Each lane receive update ack, check X8, send back ack
        25. Gather8:    Upon all ack receive, send get for same key to each lane
        26.             Each lane send get request to SHT, wait for respond
        27.             Each lane receive get ack, check X8, check value in X9, send back ack
        28. Gather9:    Upon all ack receive, send update/get for same keys to each lane
        29.             Each lane send update/get request to SHT, wait for respond
        30.             Each lane receive update/get ack, check X8, check value in X9, send back ack
        31. Gather10:   Upon all ack receive, send delete for same key to each lane
        32.             Each lane send delete request to SHT, wait for respond
        33.             Each lane receive delete ack, check X8, send back ack
        34. Gather11:   Upon all ack receive, yield_terminate
        #35.Test get_iter()
    """
    # efa = EFA([])
    efa.code_level = 'machine'

    state0 = efa.State()
    efa.add_initId(state0.state_id)
    efa.add_state(state0)

    NUM_GATHER = 12

    tran_entry_init     = state0.writeTransition("eventCarry", state0, state0, "entry_init")
    tran_gather         = []
    for i in range(NUM_GATHER):
        tran_gather.append(state0.writeTransition("eventCarry", state0, state0, "gather_"+str(i)))
    tran_desc_replicate = state0.writeTransition("eventCarry", state0, state0, "desc_replicate")
    tran_update_send    = state0.writeTransition("eventCarry", state0, state0, "update_send")
    tran_update_receive = state0.writeTransition("eventCarry", state0, state0, "update_receive")
    tran_get_send       = state0.writeTransition("eventCarry", state0, state0, "get_send")
    tran_get_receive    = state0.writeTransition("eventCarry", state0, state0, "get_receive")
    tran_delete_send    = state0.writeTransition("eventCarry", state0, state0, "delete_send")
    tran_delete_receive = state0.writeTransition("eventCarry", state0, state0, "delete_receive")

    NUM_UD = 20
    # Generate test cases
    NUM_INIT_UPDATE_TEST = 1 # should be positive
    test_data = [[random.randint(0, NUM_UD-1), random.randint(0, 255)], ]

    # Code injection
    SHT.setup(state0, debug=False)
    # SHT.setup(state0, debug=True)

    INIT_NUM_OPS = 8

    REG_SHT_DESC_LM_OFFSET  = 'X16'
    REG_LM_BUF_OFFSET       = 'X17'
    REG_LM_BUF_ADDR         = 'X18'
    REG_TMP0                = 'X19'
    REG_TMP1                = 'X20'
    REG_TMP2                = 'X21'
    REG_TMP3                = 'X28'
    REG_KEY                 = 'X22'
    REG_VALUE               = 'X23'
    REG_UD_COUNTER          = 'X24'
    REG_TMP_EVENT           = 'X25'
    REG_ERROR_FLAG          = 'X26'
    REG_TMP_CONT            = 'X27'

    # TRAN - ENTRY init
    ENTRY_OB_SHT_DESC_LM_OFFSET = 'X8'
    ENTRY_OB_SHT_LM_BUF_OFFSET  = 'X9'

    tran_entry_init.writeAction(f"print '[NWID %d] => ENTRY SHT init: X8 = %d, X9 = %d' {'X0'} {'X8'} {'X9'}")
    tran_entry_init.writeAction(f"perflog 1 0 'init started, nwid = %d' {'X0'}")
    tran_entry_init.writeAction(f"mov_reg2reg {ENTRY_OB_SHT_DESC_LM_OFFSET} {REG_SHT_DESC_LM_OFFSET}")  # save SHT descriptor LM addr
    tran_entry_init.writeAction(f"mov_imm2reg {REG_TMP0} {INIT_NUM_OPS}")  # REG_TMP0 = number of operands needed by SHT init call
    tran_entry_init.writeAction(f"mov_reg2reg {ENTRY_OB_SHT_LM_BUF_OFFSET} {REG_LM_BUF_OFFSET}")  # 64 Bytes LM send buffer address
    tran_entry_init.writeAction(f"add {REG_LM_BUF_OFFSET} {'X7'} {REG_LM_BUF_ADDR}")  # 64 Bytes LM send buffer address
    tran_entry_init.writeAction(f"bcopy_ops {'X8'} {REG_LM_BUF_ADDR} {REG_TMP0}")  # copy the operands to LM buffer for calling SHT init
    SHT.initialize(tran=tran_entry_init,
                   ret=tran_gather[0].getLabel(),
                   tmp_reg0=REG_TMP0,
                   tmp_reg1=REG_TMP2,
                   arg_lm_addr_reg=REG_LM_BUF_ADDR)  # call SHT init
    tran_entry_init.writeAction("yield")

    # TRAN - entry init return
    tran_gather[0].writeAction(f"print '[NWID %d] => SHT init return: X8 = %d, X9 = %d' {'X0'} {'X8'} {'X9'}")
    tran_gather[0].writeAction(f"print '[NWID %d] => ENTRY SHT desc replicate: X8 = %d, X9 = %d' {'X0'} {'X8'} {'X9'}")
    tran_gather[0].writeAction(f"mov_imm2reg {REG_UD_COUNTER} {1}")
    tran_gather[0].writeAction(f"add {REG_SHT_DESC_LM_OFFSET} {'X7'} {REG_TMP1}")
    tran_gather[0].writeAction(f"move {REG_SHT_DESC_LM_OFFSET} {40}({REG_TMP1}) 0 8")
    tran_gather[0].writeAction(f"{'TR_gather0_next'}: bgeiu {REG_UD_COUNTER} {NUM_UD} {'TR_gather0_done'}")
    tran_gather[0].writeAction(f"print '[NWID %d] sending SHT desc to nwid = %d' {'X0'} {REG_UD_COUNTER}")
    call_wlm(tran=tran_gather[0],
                        dst_nwid_reg=REG_UD_COUNTER,
                        callee_tran_label=tran_desc_replicate.getLabel(),
                        ret_tran_label=tran_gather[1].getLabel(),
                        tmp_reg0=REG_TMP0,
                        tmp_reg1=REG_TMP2,
                        arg_lm_addr_reg=REG_TMP1,
                        arg_lm_words=SHT.DESC_WORD_CNT + 1)
    tran_gather[0].writeAction(f"addi {REG_UD_COUNTER} {REG_UD_COUNTER} {1}")
    tran_gather[0].writeAction(f"jmp {'TR_gather0_next'}")
    tran_gather[0].writeAction(f"{'TR_gather0_done'}: mov_imm2reg {REG_UD_COUNTER} {0}")
    tran_gather[0].writeAction(f"print '[SRC NWID %03d] source sent all update0 pings out.' {'X0'}")
    tran_gather[0].writeAction(f"mov_imm2reg {REG_ERROR_FLAG} {0}")
    tran_gather[0].writeAction(f"mov_imm2reg {REG_UD_COUNTER} {1}")
    tran_gather[0].writeAction("yield")

    # TRAN - SHT desc replicate receive
    SHT_DESC_RECV_OB_SHT_DESC_LM_OFFSET = 'X13'
    tran_desc_replicate.writeAction(f"print '[NWID %d] => ENTRY SHT desc replicate recv: X13 = %d' {'X0'} {SHT_DESC_RECV_OB_SHT_DESC_LM_OFFSET}")
    tran_desc_replicate.writeAction(f"add {SHT_DESC_RECV_OB_SHT_DESC_LM_OFFSET} {'X7'} {REG_TMP0}")
    tran_desc_replicate.writeAction(f"mov_imm2reg {REG_TMP1} {SHT.DESC_WORD_CNT + 1}")
    tran_desc_replicate.writeAction(f"bcopy_ops {'X8'} {REG_TMP0} {REG_TMP1}")
    tran_desc_replicate.writeAction(f"mov_imm2reg {REG_TMP0} {1}")
    tran_desc_replicate.writeAction(f"sendr_reply {'X0'} {REG_TMP0} {REG_TMP3}")
    tran_desc_replicate.writeAction("yield_terminate")
    
    for i in range(1, NUM_GATHER-1):
        tran_gather[i].writeAction(f"addi {REG_UD_COUNTER} {REG_UD_COUNTER} {1}")
        tran_gather[i].writeAction(f"print '[SRC NWID %03d] <= [DST NWID %03d] source received back. Counter = %d' {'X0'} {'X8'} {REG_UD_COUNTER}")
        tran_gather[i].writeAction(f"beqi {'X9'} {0} {'TR_gather'+str(i)+'_error'}")
        tran_gather[i].writeAction(f"beqiu {REG_UD_COUNTER} {NUM_UD} {'TR_gather'+str(i)+'_all'}")
        tran_gather[i].writeAction("yield")
        # tran_gather[i].writeAction(f"{'TR_gather'+str(i)+'_error'}: addi X31 X31 0")
        # tran_gather[i].writeAction(f"{'X'}: print 'Y: Z'")
        tran_gather[i].writeAction(f"{'TR_gather'+str(i)+'_error'}: print '[NWID %d] => SHT gather{i} ERROR: got X8 = %d, X9 = %d' {'X0'} {'X8'} {'X9'}")
        tran_gather[i].writeAction(f"mov_imm2reg {REG_ERROR_FLAG} {1}")
        tran_gather[i].writeAction("yield")
        tran_gather[i].writeAction(f"{'TR_gather'+str(i)+'_all'}: beqi {REG_ERROR_FLAG} {0} {'TR_gather'+str(i)+'_no_error'}")
        tran_gather[i].writeAction(f"print '[NWID %d] => ERROR gather{i}' {'X0'}")
        tran_gather[i].writeAction(f"mov_imm2reg {REG_TMP0} {1}")
        tran_gather[i].writeAction(f"addi X7 X31 0")
        tran_gather[i].writeAction(f"move {REG_TMP0} {0}({'X31'}) 0 8")  # write 1 as termination flag
        tran_gather[i].writeAction(f"yield_terminate")
        tran_gather[i].writeAction(f"{'TR_gather'+str(i)+'_no_error'}: print 'Gather{i-1} DONE.'")
        tran_gather[i].writeAction(f"print '[NWID %d] => ENTRY SHT gather{i}: X8 = %d, X9 = %d' {'X0'} {'X8'} {'X9'}")
        tran_gather[i].writeAction(f"mov_imm2reg {REG_ERROR_FLAG} {0}")
        tran_gather[i].writeAction(f"mov_imm2reg {REG_UD_COUNTER} {0}")
        tran_gather[i].writeAction(f"mov_imm2reg {REG_TMP2} {0}")
        tran_gather[i].writeAction(f"{'TR_gather'+str(i)+'_next'}: bgeiu {REG_UD_COUNTER} {NUM_UD} {'TR_gather'+str(i)+'_done'}")
        tran_gather[i].writeAction(f"move {REG_SHT_DESC_LM_OFFSET} {0}({REG_LM_BUF_ADDR}) 0 8")  # SHT_DESC_LM_ADDR
        tran_gather[i].writeAction(f"move {REG_LM_BUF_OFFSET} {8}({REG_LM_BUF_ADDR}) 0 8")  # TMP_BUF_LM_ADDR
        match i:
            case 1:
                tran_gather[i].writeAction(f"ev_update_2 {REG_TMP_EVENT} {tran_update_send.getLabel()} 255 5")
                tran_gather[i].writeAction(f"move {REG_UD_COUNTER} {16}({REG_LM_BUF_ADDR}) 0 8")  # KEY
                tran_gather[i].writeAction(f"move {REG_UD_COUNTER} {24}({REG_LM_BUF_ADDR}) 0 8")  # VAL
            case 2:
                tran_gather[i].writeAction(f"ev_update_2 {REG_TMP_EVENT} {tran_get_send.getLabel()} 255 5")
                tran_gather[i].writeAction(f"move {REG_UD_COUNTER} {16}({REG_LM_BUF_ADDR}) 0 8")  # KEY
                tran_gather[i].writeAction(f"move {REG_UD_COUNTER} {24}({REG_LM_BUF_ADDR}) 0 8")  # VAL
            case 3:
                tran_gather[i].writeAction(f"beqi {REG_TMP2} {0} {'TR_gather'+str(i)+'_case3_0'}")
                tran_gather[i].writeAction(f"beqi {REG_TMP2} {1} {'TR_gather'+str(i)+'_case3_1'}")
                tran_gather[i].writeAction(f"{'TR_gather'+str(i)+'_case3_0'}: ev_update_2 {REG_TMP_EVENT} {tran_update_send.getLabel()} 255 5")
                tran_gather[i].writeAction(f"mov_imm2reg {REG_TMP2} {1}")
                tran_gather[i].writeAction(f"jmp {'TR_gather'+str(i)+'_case3_all'}")
                tran_gather[i].writeAction(f"{'TR_gather'+str(i)+'_case3_1'}: ev_update_2 {REG_TMP_EVENT} {tran_get_send.getLabel()} 255 5")
                tran_gather[i].writeAction(f"mov_imm2reg {REG_TMP2} {0}")
                tran_gather[i].writeAction(f"jmp {'TR_gather'+str(i)+'_case3_all'}")
                tran_gather[i].writeAction(f"{'TR_gather'+str(i)+'_case3_all'}: move {REG_UD_COUNTER} {16}({REG_LM_BUF_ADDR}) 0 8")  # KEY
                tran_gather[i].writeAction(f"move {REG_UD_COUNTER} {24}({REG_LM_BUF_ADDR}) 0 8")  # VAL
            case 4:
                tran_gather[i].writeAction(f"ev_update_2 {REG_TMP_EVENT} {tran_delete_send.getLabel()} 255 5")
                tran_gather[i].writeAction(f"move {REG_UD_COUNTER} {16}({REG_LM_BUF_ADDR}) 0 8")  # KEY
                tran_gather[i].writeAction(f"move {REG_UD_COUNTER} {24}({REG_LM_BUF_ADDR}) 0 8")  # VAL
            case 5:
                tran_gather[i].writeAction(f"ev_update_2 {REG_TMP_EVENT} {tran_update_send.getLabel()} 255 5")
                tran_gather[i].writeAction(f"move {REG_UD_COUNTER} {16}({REG_LM_BUF_ADDR}) 0 8")  # KEY
                tran_gather[i].writeAction(f"move {REG_UD_COUNTER} {24}({REG_LM_BUF_ADDR}) 0 8")  # VAL
            case 6:
                tran_gather[i].writeAction(f"beqi {REG_TMP2} {0} {'TR_gather'+str(i)+'_case6_0'}")
                tran_gather[i].writeAction(f"beqi {REG_TMP2} {1} {'TR_gather'+str(i)+'_case6_1'}")
                tran_gather[i].writeAction(f"beqi {REG_TMP2} {2} {'TR_gather'+str(i)+'_case6_2'}")
                tran_gather[i].writeAction(f"{'TR_gather'+str(i)+'_case6_0'}: ev_update_2 {REG_TMP_EVENT} {tran_update_send.getLabel()} 255 5")
                tran_gather[i].writeAction(f"mov_imm2reg {REG_TMP2} {1}")
                tran_gather[i].writeAction(f"jmp {'TR_gather'+str(i)+'_case6_all'}")
                tran_gather[i].writeAction(f"{'TR_gather'+str(i)+'_case6_1'}: ev_update_2 {REG_TMP_EVENT} {tran_get_send.getLabel()} 255 5")
                tran_gather[i].writeAction(f"mov_imm2reg {REG_TMP2} {2}")
                tran_gather[i].writeAction(f"jmp {'TR_gather'+str(i)+'_case6_all'}")
                tran_gather[i].writeAction(f"{'TR_gather'+str(i)+'_case6_2'}: ev_update_2 {REG_TMP_EVENT} {tran_delete_send.getLabel()} 255 5")
                tran_gather[i].writeAction(f"mov_imm2reg {REG_TMP2} {0}")
                tran_gather[i].writeAction(f"jmp {'TR_gather'+str(i)+'_case6_all'}")
                tran_gather[i].writeAction(f"{'TR_gather'+str(i)+'_case6_all'}: move {REG_UD_COUNTER} {16}({REG_LM_BUF_ADDR}) 0 8")  # KEY
                tran_gather[i].writeAction(f"move {REG_UD_COUNTER} {24}({REG_LM_BUF_ADDR}) 0 8")  # VAL
            case 7:
                tran_gather[i].writeAction(f"ev_update_2 {REG_TMP_EVENT} {tran_update_send.getLabel()} 255 5")
                tran_gather[i].writeAction(f"mov_imm2reg {REG_TMP0} {test_data[0][0]}")
                tran_gather[i].writeAction(f"move {REG_TMP0} {16}({REG_LM_BUF_ADDR}) 0 8")  # KEY
                tran_gather[i].writeAction(f"mov_imm2reg {REG_TMP0} {test_data[0][1]}")
                tran_gather[i].writeAction(f"move {REG_TMP0} {24}({REG_LM_BUF_ADDR}) 0 8")  # VAL
            case 8:
                tran_gather[i].writeAction(f"ev_update_2 {REG_TMP_EVENT} {tran_get_send.getLabel()} 255 5")
                tran_gather[i].writeAction(f"mov_imm2reg {REG_TMP0} {test_data[0][0]}")
                tran_gather[i].writeAction(f"move {REG_TMP0} {16}({REG_LM_BUF_ADDR}) 0 8")  # KEY
                tran_gather[i].writeAction(f"mov_imm2reg {REG_TMP0} {test_data[0][1]}")
                tran_gather[i].writeAction(f"move {REG_TMP0} {24}({REG_LM_BUF_ADDR}) 0 8")  # VAL
            case 9:
                tran_gather[i].writeAction(f"beqi {REG_TMP2} {0} {'TR_gather'+str(i)+'_case9_0'}")
                tran_gather[i].writeAction(f"beqi {REG_TMP2} {1} {'TR_gather'+str(i)+'_case9_1'}")
                tran_gather[i].writeAction(f"{'TR_gather'+str(i)+'_case9_0'}: ev_update_2 {REG_TMP_EVENT} {tran_update_send.getLabel()} 255 5")
                tran_gather[i].writeAction(f"mov_imm2reg {REG_TMP2} {1}")
                tran_gather[i].writeAction(f"jmp {'TR_gather'+str(i)+'_case9_all'}")
                tran_gather[i].writeAction(f"{'TR_gather'+str(i)+'_case9_1'}: ev_update_2 {REG_TMP_EVENT} {tran_get_send.getLabel()} 255 5")
                tran_gather[i].writeAction(f"mov_imm2reg {REG_TMP2} {0}")
                tran_gather[i].writeAction(f"jmp {'TR_gather'+str(i)+'_case9_all'}")
                tran_gather[i].writeAction(f"{'TR_gather'+str(i)+'_case9_all'}: mov_imm2reg {REG_TMP0} {test_data[0][0]}")
                tran_gather[i].writeAction(f"move {REG_TMP0} {16}({REG_LM_BUF_ADDR}) 0 8")  # KEY
                tran_gather[i].writeAction(f"mov_imm2reg {REG_TMP0} {test_data[0][1]}")
                tran_gather[i].writeAction(f"move {REG_TMP0} {24}({REG_LM_BUF_ADDR}) 0 8")  # VAL
            case 10:
                tran_gather[i].writeAction(f"ev_update_2 {REG_TMP_EVENT} {tran_delete_send.getLabel()} 255 5")
                tran_gather[i].writeAction(f"mov_imm2reg {REG_TMP0} {test_data[0][0]}")
                tran_gather[i].writeAction(f"move {REG_TMP0} {16}({REG_LM_BUF_ADDR}) 0 8")  # KEY
                tran_gather[i].writeAction(f"mov_imm2reg {REG_TMP0} {test_data[0][1]}")
                tran_gather[i].writeAction(f"move {REG_TMP0} {24}({REG_LM_BUF_ADDR}) 0 8")  # VAL
        tran_gather[i].writeAction(f"ev_update_reg_2 {REG_TMP_EVENT} {REG_TMP_EVENT} {REG_UD_COUNTER} {REG_UD_COUNTER} 8")
        tran_gather[i].writeAction(f"send_wret {REG_TMP_EVENT} {tran_gather[i+1].getLabel()} {REG_LM_BUF_ADDR} {4} {REG_TMP3}")
        tran_gather[i].writeAction(f"print '[SRC NWID %03d] => [DST NWID %03d] source pinging...' {'X0'} {REG_UD_COUNTER}")
        tran_gather[i].writeAction(f"addi {REG_UD_COUNTER} {REG_UD_COUNTER} {1}")
        tran_gather[i].writeAction(f"jmp {'TR_gather'+str(i)+'_next'}")
        tran_gather[i].writeAction(f"{'TR_gather'+str(i)+'_done'}: mov_imm2reg {REG_UD_COUNTER} {0}")
        tran_gather[i].writeAction(f"print '[SRC NWID %03d] source sent all update{i} pings out.' {'X0'}")
        tran_gather[i].writeAction("yield")
    
    tran_gather[NUM_GATHER-1].writeAction(f"addi {REG_UD_COUNTER} {REG_UD_COUNTER} {1}")
    tran_gather[NUM_GATHER-1].writeAction(f"print '[SRC NWID %03d] <= [DST NWID %03d] source received back.' {'X0'} {'X8'}")
    tran_gather[NUM_GATHER-1].writeAction(f"beqi {'X9'} {0} {'TR_gather'+str(NUM_GATHER-1)+'_error'}")
    tran_gather[NUM_GATHER-1].writeAction(f"beqiu {REG_UD_COUNTER} {NUM_UD} {'TR_gather'+str(NUM_GATHER-1)+'_all'}")
    tran_gather[NUM_GATHER-1].writeAction("yield")
    tran_gather[NUM_GATHER-1].writeAction(f"{'TR_gather'+str(NUM_GATHER-1)+'_error'}: print '[NWID %d] => SHT gather{i} ERROR: got X8 = %d, X9 = %d' {'X0'} {'X8'} {'X9'}")
    tran_gather[NUM_GATHER-1].writeAction(f"mov_imm2reg {REG_ERROR_FLAG} {1}")
    tran_gather[NUM_GATHER-1].writeAction("yield")
    tran_gather[NUM_GATHER-1].writeAction(f"{'TR_gather'+str(NUM_GATHER-1)+'_all'}: beqi {REG_ERROR_FLAG} {0} {'TR_gather'+str(NUM_GATHER-1)+'_no_error'}")
    tran_gather[NUM_GATHER-1].writeAction(f"print '[NWID %d] => ERROR gather{'+str(NUM_GATHER-1)+'}' {'X0'}")
    tran_gather[NUM_GATHER-1].writeAction(f"{'TR_gather'+str(NUM_GATHER-1)+'_no_error'}: print 'Gather{NUM_GATHER-2} DONE.'")
    tran_gather[NUM_GATHER-1].writeAction(f"mov_imm2reg {REG_TMP0} {1}")
    tran_gather[NUM_GATHER-1].writeAction(f"addi X7 X31 0")
    tran_gather[NUM_GATHER-1].writeAction(f"move {REG_TMP0} {0}({'X31'}) 0 8")  # write 1 as termination flag
    tran_gather[NUM_GATHER-1].writeAction(f"print 'Gather{NUM_GATHER-1} DONE.'")
    tran_gather[NUM_GATHER-1].writeAction(f"yield_terminate")

    SEND_REG_SHT_DESC_LM_OFFSET = 'X8'
    SEND_REG_LM_BUF_OFFSET      = 'X9'
    SEND_REG_KEY                = 'X10'
    SEND_REG_VALUE              = 'X11'
    
    # TRAN - Lane receive update
    tran_update_send.writeAction(f"print '[NWID %d] => ENTRY update received X8 = %d, X9 = %d, X10 = %d, X11 = %d' {'X0'} {'X8'} {'X9'} {'X10'} {'X11'}")
    tran_update_send.writeAction(f"mov_reg2reg {SEND_REG_SHT_DESC_LM_OFFSET} {REG_SHT_DESC_LM_OFFSET}")
    tran_update_send.writeAction(f"mov_reg2reg {SEND_REG_LM_BUF_OFFSET} {REG_LM_BUF_OFFSET}")
    tran_update_send.writeAction(f"mov_reg2reg {SEND_REG_KEY} {REG_KEY}")
    tran_update_send.writeAction(f"mov_reg2reg {SEND_REG_VALUE} {REG_VALUE}")
    tran_update_send.writeAction(f"add {REG_LM_BUF_OFFSET} {'X7'} {REG_LM_BUF_ADDR}")  # 64 Bytes LM send buffer address
    tran_update_send.writeAction(f"mov_reg2reg {'X1'} {REG_TMP_CONT}")
    tran_update_send.writeAction(f"move {REG_SHT_DESC_LM_OFFSET} {0}({REG_LM_BUF_ADDR}) 0 8")  # SHT_DESC_LM_ADDR
    tran_update_send.writeAction(f"move {REG_LM_BUF_OFFSET} {8}({REG_LM_BUF_ADDR}) 0 8")  # TMP_BUF_LM_ADDR
    tran_update_send.writeAction(f"move {REG_KEY} {16}({REG_LM_BUF_ADDR}) 0 8")  # KEY
    tran_update_send.writeAction(f"move {REG_VALUE} {24}({REG_LM_BUF_ADDR}) 0 8")  # VAL
    tran_update_send.writeAction(f"print '[NWID %d] => launching SHT update' {'X0'}")
    SHT.update(tran=tran_update_send,
            ret=tran_update_receive.getLabel(),
            tmp_reg0=REG_TMP1,
            tmp_reg1=REG_TMP2,
            arg_lm_addr_reg=REG_LM_BUF_ADDR)
    tran_update_send.writeAction("yield")

    tran_update_receive.writeAction(f"print '[NWID %d] => SHT update return: X8 = %d, X9 = %d' {'X0'} {'X8'} {'X9'}")
    tran_update_receive.writeAction(f"sendr_wcont {REG_TMP_CONT} {'X2'} {'X0'} {'X8'}")
    tran_update_receive.writeAction("yield_terminate")

    # TRAN - Lane receive get
    tran_get_send.writeAction(f"print '[NWID %d] => ENTRY get received X8 = %d, X9 = %d, X10 = %d, X11 = %d' {'X0'} {'X8'} {'X9'} {'X10'} {'X11'}")
    tran_get_send.writeAction(f"mov_reg2reg {SEND_REG_SHT_DESC_LM_OFFSET} {REG_SHT_DESC_LM_OFFSET}")
    tran_get_send.writeAction(f"mov_reg2reg {SEND_REG_LM_BUF_OFFSET} {REG_LM_BUF_OFFSET}")
    tran_get_send.writeAction(f"mov_reg2reg {SEND_REG_KEY} {REG_KEY}")
    tran_get_send.writeAction(f"mov_reg2reg {SEND_REG_VALUE} {REG_VALUE}")
    tran_get_send.writeAction(f"add {REG_LM_BUF_OFFSET} {'X7'} {REG_LM_BUF_ADDR}")  # 64 Bytes LM send buffer address
    tran_get_send.writeAction(f"mov_reg2reg {'X1'} {REG_TMP_CONT}")
    tran_get_send.writeAction(f"print '[NWID %d] => launching SHT get' {'X0'}")
    SHT.get(tran=tran_get_send,
            ret=tran_get_receive.getLabel(),
            tmp_reg0=REG_TMP1,
            tmp_reg1=REG_TMP2,
            desc_lm_offset_reg=REG_SHT_DESC_LM_OFFSET,
            key_reg=REG_KEY)
    tran_get_send.writeAction("yield")

    tran_get_receive.writeAction(f"print '[NWID %d] => SHT get return: X8 = %d, X9 = %d' {'X0'} {'X8'} {'X9'}")
    tran_get_receive.writeAction(f"bne {'X9'} {REG_VALUE} {'TR_get_wrong'}")
    tran_get_receive.writeAction(f"sendr_wcont {REG_TMP_CONT} {'X2'} {'X0'} {'X8'}")
    tran_get_receive.writeAction("yield")
    tran_get_receive.writeAction(f"{'TR_get_wrong'}: mov_imm2reg {REG_TMP0} {0}")
    tran_get_receive.writeAction(f"sendr_wcont {REG_TMP_CONT} {'X2'} {'X0'} {REG_TMP0}")
    tran_get_receive.writeAction("yield_terminate")
    
    # TRAN - Lan receive delete
    tran_delete_send.writeAction(f"print '[NWID %d] => ENTRY delete received X8 = %d, X9 = %d, X10 = %d, X11 = %d' {'X0'} {'X8'} {'X9'} {'X10'} {'X11'}")
    tran_delete_send.writeAction(f"mov_reg2reg {SEND_REG_SHT_DESC_LM_OFFSET} {REG_SHT_DESC_LM_OFFSET}")
    tran_delete_send.writeAction(f"mov_reg2reg {SEND_REG_LM_BUF_OFFSET} {REG_LM_BUF_OFFSET}")
    tran_delete_send.writeAction(f"mov_reg2reg {SEND_REG_KEY} {REG_KEY}")
    tran_delete_send.writeAction(f"mov_reg2reg {SEND_REG_VALUE} {REG_VALUE}")
    tran_delete_send.writeAction(f"add {REG_LM_BUF_OFFSET} {'X7'} {REG_LM_BUF_ADDR}")  # 64 Bytes LM send buffer address
    tran_delete_send.writeAction(f"mov_reg2reg {'X1'} {REG_TMP_CONT}")
    tran_delete_send.writeAction(f"print '[NWID %d] => launching SHT delete' {'X0'}")
    # TODO: Change to delete
    SHT.get(tran=tran_delete_send,
            ret=tran_delete_receive.getLabel(),
            tmp_reg0=REG_TMP1,
            tmp_reg1=REG_TMP2,
            desc_lm_offset_reg=REG_SHT_DESC_LM_OFFSET,
            key_reg=REG_KEY)
    tran_delete_send.writeAction("yield")

    tran_delete_receive.writeAction(f"print '[NWID %d] => SHT delete return: X8 = %d, X9 = %d' {'X0'} {'X8'} {'X9'}")
    tran_delete_receive.writeAction(f"sendr_wcont {REG_TMP_CONT} {'X2'} {'X0'} {'X8'}")
    tran_delete_receive.writeAction("yield_terminate")

    return efa

