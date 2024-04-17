from math import log2
import time 

class DynamicEventMap:
    def __init__(self, start=0, linker=False) -> None:
        self.event_map = {}
        self.last = start
        self.linker = linker
       
    def add_event(self, key):
        self.event_map[key] = self.last
        # print(f"event {key} is mapped to {self.last}")
        self.last += 1

    def __sizeof__(self) -> int:
        return self.last
    
    def __getitem__(self, key):
        # print(key)
        if self.linker:
            return key
        else:
            return self.event_map[key]




class DynamicBlockActionMap:
    def __init__(self, start=0) -> None:
        self.block_map = {}
        self.last = start
       
    def add_ld_first_ba(self, C, ele_size):
        self.block_map[f'first-{C}-{ele_size}'] = 'block_'+str(self.last)
        self.last += 1
        return self.block_map[f'first-{C}-{ele_size}']

    def add_block(self, key):
        self.block_map[key] = 'block_'+str(self.last)
        self.last += 1
        return self.block_map[key]
    
    def get_block_id(self, key):
        return self.block_map[key]

    def add_ld_next_ba(self, C, ele_size):
        self.block_map[f'next-{C}-{ele_size}'] = 'block_'+str(self.last)
        self.last += 1
        return self.block_map[f'next-{C}-{ele_size}']
    
    def add_event_ld_next(self, C, ele_size):
        self.block_map[f'event-next-{C}-{ele_size}'] = 'block_'+str(self.last)
        self.last += 1
        return self.block_map[f'event-next-{C}-{ele_size}']
    
    def get_event_ld_next(self, C, ele_size):
        return self.block_map[f'event-next-{C}-{ele_size}']
    
    def get_ld_next_block_id(self, C, ele_size):    
        return self.block_map[f'next-{C}-{ele_size}']
    
    def get_ld_first_block_id(self, C, ele_size):
        return self.block_map[f'first-{C}-{ele_size}'] 

    def __sizeof__(self) -> int:
        return self.last


class UDShmem:
    # Notes:
    # In ISAv2.3 all the sizes are in words, before are in bytes
    def __init__(self, efa, state=None, event_map_start=0, debug=False, lm_base=2048, config_offset=16 << 3, flag_offset= 1 << 3, ele_size=1, largest_chunk=16, impl='fastest', linker=False, enable_perflog=False):
        # configs
        self.lm_base = lm_base
        self.flag_offset = flag_offset
        self.ele_size = ele_size    # legal values are 2^x
        self.config_offset = config_offset
        # isav2.1 - begin
        # self.allowed_chunk_sizes = [8, 16, 32, 64]
        # isav2.1 - end
        
        # isav2.3 - begin
        self.allowed_chunk_sizes = [1, 2, 4, 8]
        # isav2.3 - end
        if largest_chunk is not None:
            # isav2.1 - begin
            # self.allowed_chunk_sizes += [2**i for i in range(7, int(log2(largest_chunk))+1)] # 128 ~ largest_chunk
            # isav2.1 - end
            # isav2.3 - begin
            self.allowed_chunk_sizes += [2**i for i in range(4, int(log2(largest_chunk))+1)] # 16 ~ largest_chunk
            # isav2.3 - end
        self.debug = debug
        # configs used for estimating work
        self.impl = impl  # ['slow-safe', 'fast', 'fastest-unsafe']
        self.lseg = None
        self.gseg = None
        self.avl_nuds = None # avaliable uds, store the information of how many uds are avalibale each stack
        self.lseg_range = None
        self.gseg_range = None

        self.efa = efa
        self.state = state
        
        self.event_map = DynamicEventMap(event_map_start, linker=linker)
        self.block_action_map = DynamicBlockActionMap()
        
        # generate chunk size map
    
        self.ele_shift = int(log2(self.ele_size))
        self.trans = []  # maintain a list of transactions in case of GC (unlikely)

        self.debug = debug
        self.perflog = enable_perflog
        self.__generate_efa()

    # inline function
    def call_udshmem_get(self, tran, reg_src, reg_dst, reg_nelem, reg0, reg1, reg2, reg3, reg4, cont_label=1, reg_target_nwid="NWID"):
        LM_BASE = reg0
        LM_PTR = reg1
        REG_EVENT_WORD = reg2
        REG_TARGET_NWID = reg_target_nwid
        
        # tran.writeAction(f'mov_imm2reg {LM_BASE} {self.lm_base + self.flag_offset}')
        tran.writeAction(f'addi X7 {LM_BASE} {self.lm_base + self.config_offset + self.flag_offset}')
        tran.writeAction(f'mov_imm2reg {LM_PTR} 0')
        tran.writeAction(f"movwrl {reg_src} {LM_BASE}({LM_PTR},1,0)")
        tran.writeAction(f"movwrl {reg_dst} {LM_BASE}({LM_PTR},1,0)")
        tran.writeAction(f"movwrl {reg_nelem} {LM_BASE}({LM_PTR},1,0)")
        # tran.writeAction(f"move_word {reg_src} {LM_BASE}({LM_PTR},1,3)")
        # tran.writeAction(f"move_word {reg_dst} {LM_BASE}({LM_PTR},1,3)")
        # tran.writeAction(f"move_word {reg_nelem} {LM_BASE}({LM_PTR},1,3)")
        # isav2.1 - begin
        # tran.writeAction(f"ev_update_2 {REG_EVENT_WORD} {self.event_map['udshmem-init']} 255 5")
        # tran.writeAction(f"send_wret {REG_EVENT_WORD} {REG_TARGET_NWID} {cont_label} {LM_BASE} {3 * 8}")
        # isav2.1 - end
        # tran.writeAction(f'mov_imm2reg {LM_PTR} 0')
        # tran.writeAction(f"movwlr {LM_BASE}({LM_PTR},1,1) {reg3}")
        # self.__debug_log(tran, f"print 'lm_base=%ld, lm_ptr=%ld, temp=%d'{LM_BASE} {LM_PTR} {reg3}")
        # tran.writeAction(f"movwlr {LM_BASE}({LM_PTR},1,1) {reg3}")
        # self.__debug_log(tran, f"print 'lm_base=%ld, lm_ptr=%ld, temp=%d'{LM_BASE} {LM_PTR} {reg3}")
        # tran.writeAction(f"movwlr {LM_BASE}({LM_PTR},1,1) {reg3}")
        # self.__debug_log(tran, f"print 'lm_base=%ld, lm_ptr=%ld, temp=%d'{LM_BASE} {LM_PTR} {reg3}")
        # isav2.3 - begin
        tran.writeAction(f"evii {REG_EVENT_WORD} {self.event_map['udshmem-init']} 255 {0b0101}")
        tran.writeAction(f"ev {REG_EVENT_WORD} {REG_EVENT_WORD} {REG_TARGET_NWID} {REG_TARGET_NWID} {0b1000}")
        tran.writeAction(f"send_wret {REG_EVENT_WORD} {cont_label} {LM_BASE} 3 {reg3} {reg4}") # now $len is in words
        # isav2.3 - end
        tran.writeAction(f"yield")

    def call_udshmem_iget(self, tran, reg_src, reg_dst, reg_nelem, reg0, reg1, reg2, reg3, reg4, cont_label=1, reg_target_nwid="NWID"):
        LM_BASE = reg0
        LM_PTR = reg1
        REG_EVENT_WORD = reg2
        REG_TARGET_NWID = reg_target_nwid
        
        # tran.writeAction(f'mov_imm2reg {LM_BASE} {self.lm_base + self.flag_offset}')
        tran.writeAction(f'addi X7 {LM_BASE} {self.lm_base + self.config_offset + self.flag_offset}')
        tran.writeAction(f'mov_imm2reg {LM_PTR} 0')
        tran.writeAction(f"movwrl {reg_src} {LM_BASE}({LM_PTR},1,0)")
        tran.writeAction(f"movwrl {reg_dst} {LM_BASE}({LM_PTR},1,0)")
        tran.writeAction(f"movwrl {reg_nelem} {LM_BASE}({LM_PTR},1,0)")
        # tran.writeAction(f"move_word {reg_src} {LM_BASE}({LM_PTR},1,3)")
        # tran.writeAction(f"move_word {reg_dst} {LM_BASE}({LM_PTR},1,3)")
        # tran.writeAction(f"move_word {reg_nelem} {LM_BASE}({LM_PTR},1,3)")
        # isav2.1 - begin
        # tran.writeAction(f"ev_update_2 {REG_EVENT_WORD} {self.event_map['udshmem-init']} 255 5")
        # tran.writeAction(f"send_wret {REG_EVENT_WORD} {REG_TARGET_NWID} {cont_label} {LM_BASE} {3 * 8}")
        # isav2.1 - end
        # tran.writeAction(f'mov_imm2reg {LM_PTR} 0')
        # tran.writeAction(f"movwlr {LM_BASE}({LM_PTR},1,1) {reg3}")
        # self.__debug_log(tran, f"print 'lm_base=%ld, lm_ptr=%ld, temp=%d'{LM_BASE} {LM_PTR} {reg3}")
        # tran.writeAction(f"movwlr {LM_BASE}({LM_PTR},1,1) {reg3}")
        # self.__debug_log(tran, f"print 'lm_base=%ld, lm_ptr=%ld, temp=%d'{LM_BASE} {LM_PTR} {reg3}")
        # tran.writeAction(f"movwlr {LM_BASE}({LM_PTR},1,1) {reg3}")
        # self.__debug_log(tran, f"print 'lm_base=%ld, lm_ptr=%ld, temp=%d'{LM_BASE} {LM_PTR} {reg3}")
        # isav2.3 - begin
        tran.writeAction(f"evii {REG_EVENT_WORD} {self.event_map['udshmem-init']} 255 {0b0101}")
        tran.writeAction(f"ev {REG_EVENT_WORD} {REG_EVENT_WORD} {REG_TARGET_NWID} {REG_TARGET_NWID} {0b1000}")
        tran.writeAction(f"send_wret {REG_EVENT_WORD} {cont_label} {LM_BASE} 3 {reg3} {reg4}") # now $len is in words
        # isav2.3 - end
        tran.writeAction(f"yield")

    def udshmem_get():
        pass

    def udshmem_iget():
        pass


    def __debug_log(self, tran, msg, isEFA=False, block_id=None):
        
        if self.debug:
            if isEFA:
                tran.appendBlockAction(block_id, msg)
            else:
                tran.writeAction(msg)
    
    def __perf_log(self, tran, msg):
        if self.perflog:
            tran.writeAction(msg)
    
    def __generate_efa(self):
        # isav2.1 - begin
        # default_chunks = [8, 16, 32, 64]
        # isav2.1 - end
        # isav2.3 - begin
        default_chunks = [1, 2, 4, 8]
        # isav2.3 - end
        
                
        # Register Work distribute events
        self.event_map.add_event('udshmem-init')
        self.event_map.add_event('udshmem-notify-master-completed')
        self.event_map.add_event('udshmem-start-master-thread')
        self.event_map.add_event('udshmem-notify-ud-complete')
        self.event_map.add_event('udshmem-start-ud-master-threads')
        self.event_map.add_event('udshmem-start-worker-thread')
        self.event_map.add_event('udshmem-notify-worker-complete')
        # Shared block action
        self.block_action_map.add_block('terminate')      
        # Register Shmem data movement loop events, varies due to user's configuration
        for C in default_chunks:
            self.event_map.add_event(f"udshmem-ack-{C}")
 
        
        if self.impl == 'slow':       
            for C in self.allowed_chunk_sizes:  
                self.event_map.add_event(f'udshmem-load-store-loop-slow-{C}')
                self.block_action_map.add_ld_first_ba(C, self.ele_size)
                self.block_action_map.add_ld_next_ba(C, self.ele_size)
                     
        elif self.impl == 'fast':
            for C in self.allowed_chunk_sizes:
                self.event_map.add_event(f'udshmem-load-loop-fast-{C}')
                self.block_action_map.add_event_ld_next(C, self.ele_size)
            
            for C in default_chunks:
                self.event_map.add_event(f'udshmem-store-{C}')
                        
                
        elif self.impl == 'fastest':
            print(self.allowed_chunk_sizes)
            for C in self.allowed_chunk_sizes:
                self.event_map.add_event(f'udshmem-load-store-loop-fastest-{C}')
                self.block_action_map.add_ld_first_ba(C, self.ele_size)
                self.block_action_map.add_ld_next_ba(C, self.ele_size)  
        
        elif self.impl == 'test':
            for C in self.allowed_chunk_sizes:
                self.event_map.add_event(f'udshmem-load-store-loop-fastest-{C}')
                self.block_action_map.add_ld_first_ba(C, self.ele_size)
                self.block_action_map.add_ld_next_ba(C, self.ele_size)  
        
        elif self.impl == 'basim':
            for C in self.allowed_chunk_sizes:
                self.event_map.add_event(f"udshmem-load-store-loop-{C}")
            pass
        else:
            print('Unknown implementation type!')
            exit(1)      
        
        
        # generate block actions
        if not (self.impl == 'basim'):
            self.__ba_terminate(self.block_action_map.get_block_id('terminate'))
        # generate state transitions (events)
        self.__udshmem_init()
        self.__notify_master_completed()
        self.__start_master_thread()
        self.__notify_ud_complete()
        self.__start_ud_master_thread()
        self.__start_worker_thread()
        self.__notify_worker_complete()
        
        if self.impl == 'slow':
            for C in self.allowed_chunk_sizes:
                lf = self.block_action_map.get_ld_first_block_id(C, self.ele_size)
                ln = self.block_action_map.get_ld_next_block_id(C, self.ele_size)
                self.__ba_load_first_slow(lf, C, self.ele_size)
                self.__ba_load_next_slow(ln, C, self.ele_size)
                self.__load_store_loop_slow(C)
                
            for C in default_chunks:
                self.__ack_slow(C)
        else:
            if self.impl == 'fast':
                for C in self.allowed_chunk_sizes:
                    lne = self.block_action_map.get_event_ld_next(C, self.ele_size)
                    self.__ba_load_next_fast(lne, C, self.ele_size)
                    self.__load_loop_fast(C, self.ele_size)
                    
                for C in default_chunks:
                    self.__store_fast(C)
                    self.__ack_fast(C)
                    
            elif self.impl == 'fastest':
                for C in self.allowed_chunk_sizes:
                    lf = self.block_action_map.get_ld_first_block_id(C, self.ele_size)
                    ln = self.block_action_map.get_ld_next_block_id(C, self.ele_size)
                    self.__ba_load_first_fastest(lf, C, self.ele_size)
                    self.__ba_load_next_fastest(ln, C, self.ele_size)
                    self.__load_store_loop_fastest(C, self.ele_size)
                    
                for C in default_chunks:
                    self.__ack_fastest(C)
                    
            elif self.impl == 'test':
                for C in self.allowed_chunk_sizes:
                    lf = self.block_action_map.get_ld_first_block_id(C, self.ele_size)
                    ln = self.block_action_map.get_ld_next_block_id(C, self.ele_size)
                    self.__ba_load_first_test(lf, C, self.ele_size)
                    self.__ba_load_next_test(ln, C, self.ele_size)
                    self.__load_store_loop_test(C, self.ele_size)
                for C in default_chunks:
                    self.__ack_test(C)
            elif self.impl == 'basim':
                print(self.allowed_chunk_sizes)
                for C in self.allowed_chunk_sizes:
                    self.__ev_load_store_loop(C, self.ele_size)
                    pass
                print(default_chunks)
                for C in default_chunks:
                    self.__ev_ack(C)
                print(self.event_map)
                
      
                    
    def __NEXT_CHUNK(self, C):
        if C == 1:
            return 1
        else:
            return C >> 1
        # isv2.1 - begin
        # if C == 8:
        #     return 8
        # else:
        #     return C >> 1
        # isv2.1 - end
        
        
    # mod macro
    # t = x % y
    def __mod(self, tranx, t, x, y, b1, b2):
        skip_label = 'skip_residual' + str(time.time()*1000)
        # b1 = x // y
        tranx.writeAction(f"fdiv {x} {y} {b1} 1")
        tranx.writeAction(f"fcnvt_f2i {b1} {b1} 1")
        # b2 = x
        tranx.writeAction(f"mov_reg2reg {x} {b2}")
        # if x <= y, skip
        tranx.writeAction(f"bgt {y} {x} {skip_label}")
        tranx.writeAction(f"fmul {b1} {y} {b1} 1")
        tranx.writeAction(f"fcnvt_f2i {b1} {b1} 1")
        tranx.writeAction(f"sub {x} {b1} {b2}")
        tranx.writeAction(f"{skip_label}: mov_reg2reg {b2} {t}")
    
    
    # floor division macro
    def __floor_div(self, tranx, t, x, y):
        tranx.writeAction(f"div {x} {y} {t} 1")
        # tranx.writeAction(f"fcnvt_f2i {t} {t} 1")


    # ternary operator macro
    def __ternary(self, tranx, t, cond, ifTrue, ifFalse, endLabel):
        trueCond = 'trueCond' + str(time.time()*1000)
        tranx.writeAction(f"{cond} {trueCond}")
        if 'X' in str(ifFalse):
            tranx.writeAction(f"mov_reg2reg {ifFalse} {t}")
        else:
            tranx.writeAction(f"mov_imm2reg {t} {ifFalse}")
        tranx.writeAction(f"jmp {endLabel}")
        if 'X' in str(ifTrue):
            tranx.writeAction(f"{trueCond}: mov_reg2reg {ifTrue} {t}")
        else:
            tranx.writeAction(f"{trueCond}: mov_imm2reg {t} {ifTrue}")


    def __udshmem_init(self):
        '''
        Now the Entry function for shmem library
        This function is triggered once by the TOP or the user program
        For generating EFA, call once
        
        Future version will support reading from spm and decide the number of devices
        OB_0: SRC
        OB_1: DST
        OB_3: NELE
        '''
        # nuds, nworkers, nlanes are hardcoded for now
        # given src, dest, nele, the ele_size is known
        NUM_PARAMS = 8
        SRC_OB = "X8"
        DST_OB = "X9"
        NELE_OB = "X10"
        
        # old implementation
        ELE_SIZE = "X16"
        MAX_OUTGOING_READ = "X16"
        
        SRC = "X17"
        DST =  "X18"
        NELE = "X19"
        NWORKERS = "X20"
        NLANES = "X21"
        NUDS = "X22"

        START_UDID = "X23"
        EVENT_WORD = "X24"
        START_NWID = "X25"
        
        TEMP0 = "X26"
        TEMP1 = "X27"
        
        # hardcoded values
        ele_size = 8
        nworkers = 2048 # 2048
        nstacks = 8
        nuds = 4 * nstacks
        nlanes = nuds * 64
        start_udid = 0
        
        nworkers = 64 # 2048
        nstacks = 1
        nuds = 1 * nstacks
        nlanes = nuds * 64
        start_udid = 0
        
        LM_BASE = "X30"
        LM_PTR = "X31"
        
        
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.event_map['udshmem-init'])
        self.__debug_log(tran, f"print 'udshmem init at NWID=%d' NWID")
        
        # tran.writeAction(f'mov_imm2reg {LM_BASE} {self.lm_base + self.flag_offset}')
        tran.writeAction(f'addi X7 {LM_BASE} {self.lm_base + self.config_offset + self.flag_offset}')
        tran.writeAction(f'mov_imm2reg {LM_PTR} 0')
        self.__debug_log(tran, f"print 'src_ob: %d' {SRC_OB}")
        self.__debug_log(tran, f"print 'dst_ob: %d' {DST_OB}")
        self.__debug_log(tran, f"print 'nele_ob: %d' {NELE_OB}")
        # assign values to OBs
        tran.writeAction(f"mov_reg2reg {SRC_OB} {SRC}")
        tran.writeAction(f"mov_reg2reg {DST_OB} {DST}")
        tran.writeAction(f"mov_reg2reg {NELE_OB} {NELE}")
        # assign values to them
        # tran.writeAction(f"mov_imm2reg {ELE_SIZE} {ele_size}")
        tran.writeAction(f"mov_imm2reg {NWORKERS} {nworkers}")
        tran.writeAction(f"mov_imm2reg {NLANES} {nlanes}")
        tran.writeAction(f"mov_imm2reg {NUDS} {nuds}")
        tran.writeAction(f"mov_imm2reg {START_UDID} {start_udid}")
        tran.writeAction(f"mov_imm2reg {START_NWID} {start_udid << 6}")
        for o in range(NUM_PARAMS):
            # tran.writeAction(f"move_word X{16+o} {LM_BASE}({LM_PTR},1,3)")
            tran.writeAction(f"movwrl X{16+o} {LM_BASE}({LM_PTR},1,0)")
            # self.__debug_log(tran, f"print 'X{8+o}: %d' X{8+o}")
            # self.__debug_log(tran, f"print 'X{16+o}: %d' X{16+o}")
        
        # tran.writeAction(f"ev_update_2 {EVENT_WORD} {self.event_map['udshmem-start-master-thread']} 255 5")
        # tran.writeAction(f"send_wret {EVENT_WORD} {START_NWID} {self.event_map['udshmem-notify-master-completed']} {LM_BASE} {8 * NUM_PARAMS}")
        
        # isav2.3
        tran.writeAction(f"evii {EVENT_WORD} {self.event_map['udshmem-start-master-thread']} 255 {0b0101}")
        tran.writeAction(f"ev {EVENT_WORD} {EVENT_WORD} {START_NWID} {START_NWID} {0b1000}")
        tran.writeAction(f"send_wret {EVENT_WORD} {self.event_map['udshmem-notify-master-completed']} {LM_BASE} 8 {TEMP0} {TEMP1}") # now $len is in words
        
        tran.writeAction(f"yield")
        
        self.trans.append(tran)
        
        
    def __notify_master_completed(self):
        TEMP = "X28"
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.event_map['udshmem-notify-master-completed'])
        self.__debug_log(tran, f"print 'notify master completed at NWID=%d' NWID")   
        # global termination routine (barrier)
        tran.writeAction(f"mov_imm2reg X29 1")
        
        # tran.writeAction(f"mov_imm2reg X30 {self.lm_base}")
        tran.writeAction(f"addi X7 X30 {self.lm_base + self.config_offset}")
        
        tran.writeAction(f"move X29 0(X30) 0 8")
        self.__debug_log(tran, f"print 'Master thread completed! Shmem terminated!'")
        # TODO: are there any values we want to send back?
        tran.writeAction(f"sendr3_reply X31 X30 X29 {TEMP}")
        tran.writeAction(f"yield_terminate")
        
        

    def __start_master_thread(self):
        '''
        Entry function for shmem library
        This function is triggered once by the TOP, the master thread will then start each ud's master threads
        For generating EFA, call once
        OB_0: ELE_SIZE
        OB_1: SRC
        OB_2: DST
        OB_3: NELE
        OB_4: NWORKERS
        OB_5: NLANES
        OB_6: NUDS
        OB_7: EV_LABEL
        '''
        # constants
        NUM_PARAMS = 8
        # registers
        ELE_SIZE = "X16"
        SRC = "X17"
        DST =  "X18"
        NELE = "X19"
        NWORKERS = "X20"
        NLANES = "X21"
        NUDS = "X22"
        START_UDID = "X23"

        TARGET_UDID = "X24"
        TARGET_L0ID = "X25"
        EVENT_WORD = "X26"
        COMPLETED_UDS = "X27"

        END_UDID = "X28"
        
        TEMP0 = "X29"
        TEMP1 = "X16"

        LM_BASE = "X31"
        LM_PTR = "X30"


        tran_smt = self.state.writeTransition("eventCarry", self.state, self.state, self.event_map['udshmem-start-master-thread'])
        self.__debug_log(tran_smt, "print 'start master thread'")
        # tran_smt.writeAction("print 'start master thread'")
        # tran_smt.writeAction(f"perflog 1 0 'master thread start, NWID=%d' NWID")
        self.__perf_log(tran_smt, f"perflog 1 0 'master thread start, NWID=%d' NWID")

        # save a copy of the arguments to LM
        # tran_smt.writeAction(f'mov_imm2reg {LM_BASE} {self.lm_base + self.flag_offset}')
        tran_smt.writeAction(f'addi X7 {LM_BASE} {self.lm_base + self.config_offset + self.flag_offset}')
        
        tran_smt.writeAction(f'mov_imm2reg {LM_PTR} 0')
        for o in range(NUM_PARAMS):
            # tran_smt.writeAction(f"print '%d' X{8+o}")
            tran_smt.writeAction(f"mov_reg2reg X{8+o} X{16+o}")
            # tran_smt.writeAction(f"move_word X{16+o} {LM_BASE}({LM_PTR},1,3)")
            tran_smt.writeAction(f"movwrl X{16+o} {LM_BASE}({LM_PTR},1,0)")
            # self.__debug_log(tran_smt, f"print 'X{8+o}: %d' X{8+o}")
        
        # reset the LM_BASE and LM_PTR
        tran_smt.writeAction(f"mov_imm2reg {LM_PTR} 0")
        # start lane master threads
        tran_smt.writeAction(f"mov_reg2reg {START_UDID} {TARGET_UDID}")
        tran_smt.writeAction(f"add {START_UDID} {NUDS} {END_UDID}")
        tran_smt.writeAction(f"start-loop: ble {END_UDID} {TARGET_UDID} done") # if end_udid <= start_udid, terminate
        tran_smt.writeAction(f"lshift {TARGET_UDID} {TARGET_L0ID} 6") # target_udid = target_l0idx << 6 = target_l0idx * 64
        
        # isav2.1 - begin
        # tran_smt.writeAction(f"ev_update_2 {EVENT_WORD} {self.event_map['udshmem-start-ud-master-threads']} 255 5")
        # tran_smt.writeAction(f"send_wret {EVENT_WORD} {TARGET_L0ID} {self.event_map['udshmem-notify-ud-complete']} {LM_BASE} {8 * NUM_PARAMS}")
        # isav2.1 - end
        
        # isav2.3 - begin
        tran_smt.writeAction(f"evii {EVENT_WORD} {self.event_map['udshmem-start-ud-master-threads']} 255 {0b0101}")
        tran_smt.writeAction(f"ev {EVENT_WORD} {EVENT_WORD} {TARGET_L0ID} {TARGET_L0ID} {0b1000}")
        tran_smt.writeAction(f"send_wret {EVENT_WORD} {self.event_map['udshmem-notify-ud-complete']} {LM_BASE} 8 {TEMP0} {TEMP1}") # now $len is in words
        # isav2.3 - end
        tran_smt.writeAction(f"addi {TARGET_UDID} {TARGET_UDID} 1")
        tran_smt.writeAction(f"jmp start-loop")
        tran_smt.writeAction(f"done: mov_imm2reg {COMPLETED_UDS} 0")
        tran_smt.writeAction(f"yield")

        self.trans.append(tran_smt)


    def __notify_ud_complete(self):
        '''
        This function is triggered at Master thread when a ud is completed
        master_thread ----> start_ud_master_thread--> notify_ud_complete (completed_ud++) -> if nuds <= completed_ud, yield_terminate
                       |--> start_ud_master_thread---^        
        For generating EFA, call once
        '''
        SENDER_UDID = 'X8'
        NUDS = 'X22'
        # inherited from start_master_thread
        COMPLETED_UDS = 'X27'
        TEMP = "X29"
        tran_udc = self.state.writeTransition("eventCarry", self.state, self.state, self.event_map['udshmem-notify-ud-complete'])
        tran_udc.writeAction(f"addi {COMPLETED_UDS} {COMPLETED_UDS} 1")   # completed uds++
        self.__debug_log(tran_udc, f"print 'NUDS: %d, COMPLETED_UDS: %d' {NUDS} {COMPLETED_UDS}")
        tran_udc.writeAction(f"ble {NUDS} {COMPLETED_UDS} terminate")    # if nuds <= compeleted uds, terminate
        tran_udc.writeAction(f"yield")

        # tran_udc.writeAction(f"terminate: send4_reply {NUDS} {COMPLETED_UDS}")
        tran_udc.writeAction(f"terminate: sendr3_reply {NUDS} {COMPLETED_UDS} {NUDS} {TEMP}") # isav2.3
        # tran_udc.writeAction(f"terminate: addi {TEMP} {TEMP} 0")
        # tran_udc.writeAction(f"sendr_reply {NUDS} {COMPLETED_UDS} {NUDS} {TEMP}") # isav2.3
        self.__debug_log(tran_udc, f"print 'All UDs completed!'")
        tran_udc.writeAction(f"yield_terminate")
        self.trans.append(tran_udc)  

    
    def __start_ud_master_thread(self):
        '''
        This function is triggered by the master thread, it will start worker threads for each lanes in current ud
        For generating EFA, call once
        OB_0: ELE_SIZE
        OB_1: SRC
        OB_2: DST
        OB_3: NELE
        OB_4: NWORKERS
        OB_5: NLANES
        OB_6: NUDS
        '''
        # constants
        NUM_PARAMS = 8
        # from OBs
        ELE_SIZE = "X16"
        SRC = "X17"
        DST =  "X18"
        NELE = "X19"
        NWORKERS = "X20"
        NLANES = "X21"
        NUDS = "X22"
        START_UDID = "X23"

        LM_BASE = "X31"
        LM_PTR = "X30"

        tran_lmt = self.state.writeTransition("eventCarry", self.state, self.state, self.event_map['udshmem-start-ud-master-threads'])
        self.__debug_log(tran_lmt, f"print '2start ud master thread at NWID=%d' NWID")
        # tran_lmt.writeAction(f"perflog 1 1 'start ud master thread at NWID=%d' NWID")
        self.__perf_log(tran_lmt, f"perflog 1 1 'start ud master thread at NWID=%d' NWID")
        # tran_lmt.writeAction(f"mov_imm2reg {LM_BASE} {self.lm_base + self.flag_offset}")
        tran_lmt.writeAction(f'addi X7 {LM_BASE} {self.lm_base + self.config_offset + self.flag_offset}')
        tran_lmt.writeAction(f"mov_imm2reg {LM_PTR} 0")
        # TODO: optimize fewer instructions without loading unused arguments
        for o in range(NUM_PARAMS):
            # tran_lmt.writeAction(f"print 'load ob{o} %d' X{8+o}")
            tran_lmt.writeAction(f"mov_reg2reg X{8+o} X{16+o}")
            # tran_lmt.writeAction(f"move_word X{16+o} {LM_BASE}({LM_PTR},1,3)")
            tran_lmt.writeAction(f"movwrl X{16+o} {LM_BASE}({LM_PTR},1,0)")
            # self.__debug_log(tran_lmt, f"print 'load ob{o} %d' X{16+o}")
        # recycle registers X16-X19
        
        UDID = "X16"
        L0ID = "X17"
        UD_LANES = "X18"
        R_UDID = "X19" # relative UDID

        # UDID = NWID >> 6, L0ID = NWID << 6
        tran_lmt.writeAction(f"rshift NWID {UDID} 6") # udid = nwid >> 6 = nwid // 64
        tran_lmt.writeAction(f"lshift {UDID} {L0ID} 6") # L0ID = udid << 6 = udid * 64
        # R_UDID = UDID - START_UDID
        tran_lmt.writeAction(f"sub {UDID} {START_UDID} {R_UDID}")
        self.__debug_log(tran_lmt, f"print 'start UD master. UDID: %d, L0ID: %d, R_UDID: %d' {UDID} {L0ID} {R_UDID}")

        # recyclable registers below
        UD_LANES_FD = "X23"
        UD_LANES_RM = "X24"
        B1, B2 = "X25", "X26"
        TEMP0, TEMP1 = "X27", "X28"

        # tran_lmt.writeAction("print 'checkpoint 1'")
        # UD_LANES = NLANES // NUDS + (UDID < NLANES % NUDS)
        # UD_LANES_FD = NLANES // NUDS
        self.__floor_div(tran_lmt, UD_LANES_FD, NLANES, NUDS)
        # UD_LANES_RM = NLANES % NUDS
        # isv2.1 - begin
        # self.__mod(tran_lmt, UD_LANES_RM, NLANES, NUDS, B1, B2) # and this is not correct when x==y
        # isv2.1 - end
        tran_lmt.writeAction(f"mod {NLANES} {NUDS} {UD_LANES_RM}")
        # UD_LANES = (UDID < UD_LANES_RM ? 1 : 0) + UD_LANES_FD
        tran_lmt.writeAction(f"mov_imm2reg {UD_LANES} 0")
        # === old version ===
        # ternary(tran_lmt, t=UD_LANES, cond=f'bgt {UD_LANES_RM} {UDID}', ifTrue=1, ifFalse=0, endLabel='ud-lanes-cont')
        # === new version ===
        self.__ternary(tran_lmt, t=UD_LANES, cond=f'bgt {UD_LANES_RM} {R_UDID}', ifTrue=1, ifFalse=0, endLabel='ud-lanes-cont')
        # === end ===
        tran_lmt.writeAction(f"ud-lanes-cont: add {UD_LANES} {UD_LANES_FD} {UD_LANES}")
        
        # tran_lmt.writeAction("print 'checkpoint 2'")
        # make sure UD_LANES <= 64; can be optimized 
        tran_lmt.writeAction(f"movir {TEMP0} 64")
        tran_lmt.writeAction(f"ble {UD_LANES} {TEMP0} skip-max-lane") # if ud_lanes <= 64, terminate

        # tran_lmt.writeAction(f"print 'checkpoint 2.5'")

        # tran_lmt.writeAction(f"print 'Exeed max of 64 lane!, reset to UD_LANES = %d to 64.' {UD_LANES}")
        tran_lmt.writeAction(f"mov_imm2reg {UD_LANES} 64")
        tran_lmt.writeAction(f"skip-max-lane: addi {UD_LANES} {UD_LANES} 0") # nop
        # recyle X23, X24, X25, X26

        # tran_lmt.writeAction("print 'checkpoint 3'")
        UD_WORKERS = "X23" # pined register, will be used in notify-worker-complete
        WIDX_INIT = "X24"
        UD_WORKERS_FD = "X25"
        UD_WORKERS_RM = "X26"
        # recyclable registers below
        B1, B2 = "X27", "X28"
        TEMP = "X29"
        # UD_WORKERS = NWORKERS // NUDS + (UDID < NWORKERS % NUDS)
        # UD_WORKERS_FD = NWORKERS // NUDS
        self.__floor_div(tran_lmt, UD_WORKERS_FD, NWORKERS, NUDS)
        # UD_WORKERS_RM = NWORKERS % NUDS
        # isa v2.1 - begin
        # self.__mod(tran_lmt, UD_WORKERS_RM, NWORKERS, NUDS, B1, B2)
        # isa v2.1 - end
        
        # isa v2.3 - begin
        tran_lmt.writeAction(f"mod {NWORKERS} {NUDS} {UD_WORKERS_RM}")
        # isa v2.3 - end
        
        # if UD_WORKERS_RM != 0 or UD_WORKERS_FD != 0: give proper workers
        # UD_WORKERS = UDID < NWORKERS ? 1 : 0

        # UD_WORKERS = (UDID < UD_WORKERS_RM ? 1 : 0) + UD_WORKERS_FD
        tran_lmt.writeAction(f"mov_imm2reg {UD_WORKERS} 0")
 
        self.__ternary(tran_lmt, t=UD_WORKERS, cond=f'bgt {UD_WORKERS_RM} {R_UDID}', ifTrue=1, ifFalse=0, endLabel='ud-workers-cont')
        self.__debug_log(tran_lmt, f"print 'ud_workers: %d, ud_workers_fd: %d, ud_workers_rm: %d, udid: %d' {UD_WORKERS} {UD_WORKERS_FD} {UD_WORKERS_RM} {R_UDID}")
        # === end ===
        tran_lmt.writeAction(f"ud-workers-cont: add {UD_WORKERS} {UD_WORKERS_FD} {UD_WORKERS}")
        tran_lmt.writeAction(f"blec {UD_WORKERS} 0 lmt_terminate") # if ud_workers <= 0, terminate
        # X25, X26 still useable, recycle X27, X28
        # WIDX_INIT = (NWORKERS // NUDS) * UDID + (UDID < NWORKERS % NUDS ? UDID : NWORKERS % NUDS)
        WIDX_INIT0 = "X27"
        WIDX_INIT1 = "X28"
        WIDX = WIDX_INIT
        # WIDX_INT0 = (NWORKERS // NUDS) * UDID
        # tran_lmt.writeAction(f"fmul {UD_WORKERS_FD} {R_UDID} {WIDX_INIT0} 1")
        # tran_lmt.writeAction(f"fcnvt_f2i {WIDX_INIT0} {WIDX_INIT0} 1")        
        tran_lmt.writeAction(f"mul {UD_WORKERS_FD} {R_UDID} {WIDX_INIT0}")

        # WIDX_INIT1 = (UDID < NWORKERS % NUDS ? UDID : NWORKERS % NUDS)
        tran_lmt.writeAction(f"mov_imm2reg {WIDX_INIT1} 0")
        self.__ternary(tran_lmt, t=WIDX_INIT1, cond=f'bgt {UD_WORKERS_RM} {R_UDID}', ifTrue=R_UDID, ifFalse=UD_WORKERS_RM, endLabel='widx-init-cont')
        tran_lmt.writeAction(f"widx-init-cont: add {WIDX_INIT0} {WIDX_INIT1} {WIDX_INIT}")
        # recycle X25, X26, X27, X28
        # UD_LANES, UD_WORKERS, WIDX_INIT(WIDX), UDID, L0ID = X18, X23, X24, X16, X17
        # NWORKERS, NUDS, NLANES = X20, X21, X22, others are usable
        # usable registers: X19, X25, X26, X27, X28, X29, X30, X31

        # L_WORKERS_FD = UD_WORKERS // UD_LANES
        L_WORKERS_FD = "X25"
        L_WORKERS_RM = "X26"
        T_NWID = "X27"
        B1, B2 = "X28", "X29"
        TEMP0, TEMP1 = "X28", "X29"
        MAX_NWID = "X30"
        L_WORKERS = "X31"
        COUNTER = "X19"
        # force recycle X20, X21, X22
        EVENT_WORD = "X20"
        COMPLETED_WORKERS = "X21"
        RELATIVE_NWID = "X22"

        self.__floor_div(tran_lmt, L_WORKERS_FD, UD_WORKERS, UD_LANES)
        # L_WORKERS_RM = UD_WORKERS % UD_LANES
        # isa v2.1 - begin
        # self.__mod(tran_lmt, L_WORKERS_RM, UD_WORKERS, UD_LANES, B1, B2)
        # isa v2.1 - end
        # isa v2.3 - begin
        tran_lmt.writeAction(f"mod {UD_WORKERS} {UD_LANES} {L_WORKERS_RM}")
        # isa v2.3 - end

        self.__debug_log(tran_lmt, f"print 'UDID: %d, UD master distributing worker threads.' {UDID}")
        # tran_lmt.writeAction(f"perflog 1 2 'UDID: %d, Ud master distributing worker threads.' {UDID}")
        self.__perf_log(tran_lmt, f"perflog 1 2 'UDID: %d, Ud master distributing worker threads.' {UDID}")

        tran_lmt.writeAction(f"mov_reg2reg {L0ID} {T_NWID}") # T_NWID = L0ID
        tran_lmt.writeAction(f"iter-lanes: add {L0ID} {UD_LANES} {MAX_NWID}") # MAX_NWID = L0ID + UD_LANES
        # tran_lmt.writeAction(f"print 'L_WORKERS_FD: %d, L_WORKERS_RM: %d, T_NWID: %d, MAX_NWID: %d, L_WORKERS: %d, COUNTER: %d, EVENT_WORD: %d, COMPLETED_WORKERS: %d' {L_WORKERS_FD} {L_WORKERS_RM} {T_NWID} {MAX_NWID} {L_WORKERS} {COUNTER} {EVENT_WORD} {COMPLETED_WORKERS}")
        # tran_lmt.writeAction(f"print 'UD_WORKERS: %d, UD_LANES: %d' {UD_WORKERS} {UD_LANES}")
        tran_lmt.writeAction(f"ble {MAX_NWID} {T_NWID} iter-lanes-end") # if MAX_NWID <= T_NWID, goto iter-lanes-end
        tran_lmt.writeAction(f"mov_imm2reg {L_WORKERS} 0")  # L_WORKERS = 0
        tran_lmt.writeAction(f"sub {T_NWID} {L0ID} {RELATIVE_NWID}") # RELATIVE_NWID = T_NWID - L0ID
        self.__ternary(tran_lmt, t=L_WORKERS, cond=f'bgt {L_WORKERS_RM} {RELATIVE_NWID}', ifTrue=1, ifFalse=0, endLabel='l-workers-cont') # L_WORKERS = (T_NWID < L_WORKERS_RM ? 1 : 0)
        # tran_lmt.writeAction(f"print 'L_WORKERS_FD: %d, L_WORKERS_RM: %d, T_NWID: %d, MAX_NWID: %d, L_WORKERS: %d, COUNTER: %d, UD_LANES: %d, WIDX: %d' {L_WORKERS_FD} {L_WORKERS_RM} {T_NWID} {MAX_NWID} {L_WORKERS} {COUNTER} {UD_LANES} {WIDX}")
        
        tran_lmt.writeAction(f"l-workers-cont: add {L_WORKERS} {L_WORKERS_FD} {L_WORKERS}") # L_WORKERS = L_WORKERS_FD + L_WORKERS
        tran_lmt.writeAction(f"mov_imm2reg {COUNTER} 0") # COUNTER = 0
        # tran_lmt.writeAction(f"print 'UDID: %d, L_WORKERS: %d, L_WORKERS_FD: %d, L_WORKERS_RM: %d' {UDID} {L_WORKERS} {L_WORKERS_FD} {L_WORKERS_RM}")
        tran_lmt.writeAction(f"iter-lane-workers: ble {L_WORKERS} {COUNTER} iter-next-lane")

        # start worker
        # tran_lmt.writeAction(f"print 'L_WORKERS_FD: %d, L_WORKERS_RM: %d, T_NWID: %d, MAX_NWID: %d, L_WORKERS: %d, COUNTER: %d, UD_LANES: %d, WIDX: %d' {L_WORKERS_FD} {L_WORKERS_RM} {T_NWID} {MAX_NWID} {L_WORKERS} {COUNTER} {UD_LANES} {WIDX}")
        # isa v2.1 - begin
        # tran_lmt.writeAction(f"ev_update_2 {EVENT_WORD} {self.event_map['udshmem-start-worker-thread']} 255 5")
        # tran_lmt.writeAction(f"send4_wret {EVENT_WORD} {T_NWID} {self.event_map['udshmem-notify-worker-complete']} {WIDX} {UD_WORKERS}")
        # isa v2.1 - end
        # isa v2.3 - begin
        tran_lmt.writeAction(f"evii {EVENT_WORD} {self.event_map['udshmem-start-worker-thread']} 255 {0b0101}")
        tran_lmt.writeAction(f"ev {EVENT_WORD} {EVENT_WORD} {T_NWID} {T_NWID} {0b1000}")
        tran_lmt.writeAction(f"sendr3_wret {EVENT_WORD} {self.event_map['udshmem-notify-worker-complete']} {WIDX} {UD_WORKERS} {UD_WORKERS} {TEMP0} {TEMP1}") # last one is bogus
        # self.__debug_log(tran_lmt, f"print 'L_WORKERS_FD: %d, L_WORKERS_RM: %d, T_NWID: %d, MAX_NWID: %d, L_WORKERS: %d, COUNTER: %d, UD_LANES: %d, WIDX: %d' {L_WORKERS_FD} {L_WORKERS_RM} {T_NWID} {MAX_NWID} {L_WORKERS} {COUNTER} {UD_LANES} {WIDX}")
        tran_lmt.writeAction(f"addi {WIDX} {WIDX} 1") # WIDX++
        tran_lmt.writeAction(f"addi {COUNTER} {COUNTER} 1") # COUNTER++
        tran_lmt.writeAction(f"jmp iter-lane-workers") # goto iter-lane-workers
        tran_lmt.writeAction(f"iter-next-lane: addi {T_NWID} {T_NWID} 1") # T_NWID++
        tran_lmt.writeAction(f"jmp iter-lanes") # goto iter-lanes
        tran_lmt.writeAction(f"iter-lanes-end: mov_imm2reg {COMPLETED_WORKERS} 0")
        # tran_lmt.writeAction(f"print 'UDID: %d, distribute yield.' {UDID}")
        tran_lmt.writeAction(f"yield")
        # tran_lmt.writeAction(f"terminate: send4_reply {UDID} {UD_WORKERS}")
        tran_lmt.writeAction(f"lmt_terminate: sendr3_reply {UDID} {UD_WORKERS} {UDID} {TEMP0}") # isav2.3
        # tran_lmt.writeAction(f"lmt_terminate: addi {TEMP1} {TEMP1} 0")
        # tran_lmt.writeAction(f"sendr_reply {UDID} {UD_WORKERS} {UDID} {TEMP0}") # isav2.3
        self.__debug_log(tran_lmt, f"print 'No UD workers for this UD, UDID:%d, UD_WORKERS:%d' {UDID} {UD_WORKERS}")
        # tran_lmt.writeAction(f"perflog 1 8 'No UD workers for this UD, UDID:%d, UD_WORKERS:%d' {UDID} {UD_WORKERS}")
        self.__perf_log(tran_lmt, f"perflog 1 8 'No UD workers for this UD, UDID:%d, UD_WORKERS:%d' {UDID} {UD_WORKERS}")

        tran_lmt.writeAction(f"yield_terminate")
        self.trans.append(tran_lmt)
    
      
    def __notify_worker_complete(self):
        '''
        runnning at ud_master_thread
        This function is triggered at Lane's master thread when a worker at its lane is completed
        When all workers are completed, it notifies the master thread from UD0 (send_reply)
        ud_master_thread ----> start_worker_thread--> notify_worker_complete (completed_workers++)
                            |--> start_worker_thread---^
        For generating EFA, call once
        '''
        # inherit registers from start_worker_thread
        UDID = 'X16'
        COMPLETED_WORKERS = 'X21'
        UD_WORKERS = "X23"
        TEMP0, TEMP1 = "X28", "X29"

        tran_wc = self.state.writeTransition("eventCarry", self.state, self.state, self.event_map['udshmem-notify-worker-complete'])
        # one worker just finished, completed_workers++
        # tran_wc.writeAction(f"print 'UDID: %d UD_WORKERS: %d, COMPLETED_WORKERS: %d' {UDID} {UD_WORKERS} {COMPLETED_WORKERS}")
        tran_wc.writeAction(f"addi {COMPLETED_WORKERS} {COMPLETED_WORKERS} 1")
        tran_wc.writeAction(f"ble {UD_WORKERS} {COMPLETED_WORKERS} wc_terminate")    # nworkers >= compeleted workers
        tran_wc.writeAction(f"yield")
        # tran_wc.writeAction(f"terminate: send4_reply {UDID} {UD_WORKERS}") # all the workers in this UD are terminated, notify the master thread

        tran_wc.writeAction(f"wc_terminate: sendr3_reply {UDID} {UD_WORKERS} {UD_WORKERS} {TEMP0}") # isav2.3
        # tran_wc.writeAction(f"wc_terminate: addi {TEMP1} {TEMP1} 0")
        # tran_wc.writeAction(f"sendr_reply {UDID} {UD_WORKERS} {UD_WORKERS} {TEMP0}") # isav2.3
        
        self.__debug_log(tran_wc, f"print 'All UD workers done, UDID:%d, UD_WORKERS:%d' {UDID} {UD_WORKERS}")
        # tran_wc.writeAction(f"perflog 1 6 'All UD workers done, UDID:%d, UD_WORKERS:%d' {UDID} {UD_WORKERS}")
        self.__perf_log(tran_wc, f"perflog 1 6 'All UD workers done, UDID:%d, UD_WORKERS:%d' {UDID} {UD_WORKERS}")

        tran_wc.writeAction("yield_terminate")
        self.trans.append(tran_wc)       
       
       
    def __start_worker_thread(self):
        '''

        '''
        # load from LM
        ELE_SIZE = "X16"
        SRC = "X17"
        DST =  "X18"
        NELE = "X19"
        NWORKERS = "X20"
        # OBs
        WIDX = "X21" # X8, worker index
        # REGs
        W_NELE = "X22"
        LDPTR = "X23"
        STPTR = "X24"
        NLEFT_LD = "X25"
        NLEFT_ST = "X26"
        W_NELE_FD = "X27"
        W_NELE_RM = "X28"
        B1, B2 = "X29", "X30"
        INIT_OFFSETS = "X31"
        TEMP = "X30"

        tran0 = self.state.writeTransition("eventCarry", self.state, self.state, self.event_map['udshmem-start-worker-thread'])
        
       
        # tran0.writeAction(f"mov_imm2reg X31 {self.lm_base + self.flag_offset}")
        # self.__debug_log(tran0, f"print 'start worker thread at NWID=%d' NWID")
        tran0.writeAction(f"addi X7 X31 {self.lm_base + self.config_offset + self.flag_offset}")
        tran0.writeAction("mov_imm2reg X30 0")
        for o in range(5):
            # tran0.writeAction(f"move_word X31(X30,1,3) X{16+o}")
            tran0.writeAction(f"movwlr X31(X30,1,0) X{16+o}")
       
        tran0.writeAction(f"mov_reg2reg X8 {WIDX}")
        # tran0.writeAction(f"perflog 1 3 'start-worker-thread=%d' {WIDX}")
        self.__perf_log(tran0, f"perflog 1 3 'start-worker-thread=%d' {WIDX}")
        
       

        # W_NELE = NELE // NWORKERS
        self.__floor_div(tran0, W_NELE_FD, NELE, NWORKERS)

        # W_NELE_RM = NELE % NWORKERS
        # isa v2.1 - begin
        # self.__mod(tran0, W_NELE_RM, NELE, NWORKERS, B1, B2)
        # isa v2.1 - end
        # isa v2.3 - begin
        tran0.writeAction(f"mod {NELE} {NWORKERS} {W_NELE_RM}")
        # isa v2.3 - end
        tran0.writeAction(f"mov_imm2reg {W_NELE} 0")
        self.__ternary(tran0, W_NELE, f'bgt {W_NELE_RM} {WIDX}', 1, 0, endLabel='t-cont')
        tran0.writeAction(f"t-cont: add {W_NELE} {W_NELE_FD} {W_NELE}")
        # LDPTR = SRC + W_NELE * WIDX + (WIDX < W_NELE_RM ? WIDX : W_NELE_RM)
        # INIT_OFFSETS = (WIDX < W_NELE_RM ? WIDX : W_NELE_RM)
        tran0.writeAction(f"mov_imm2reg {INIT_OFFSETS} 0")
        self.__ternary(tran0, INIT_OFFSETS, f"bgt {W_NELE_RM} {WIDX}", WIDX, W_NELE_RM, endLabel='ldptr0-cont')
        # INIT_OFFSETS += W_NELE * WIDX
        # TEMP = W_NELE_FD * WIDX
        # tran0.writeAction(f"ldptr0-cont: fmul {W_NELE_FD} {WIDX} {TEMP} 1")
        # self.__debug_log(tran0, f"print 'WIDX: %ld, W_NELE_FD=%ld, TEMP=%ld'{WIDX} {W_NELE_FD} {TEMP}")
        # tran0.writeAction(f"fcnvt_f2i {TEMP} {TEMP} 1")        
        tran0.writeAction(f"ldptr0-cont: mul {W_NELE_FD} {WIDX} {TEMP}")
        # INIT_OFFSETS = INIT_OFFSETS + TEMP
        # tran0.writeAction(f"print 'INIT_OFFSETS: %d, TEMP: %d' {INIT_OFFSETS} {TEMP}")
        tran0.writeAction(f"add {INIT_OFFSETS} {TEMP} {INIT_OFFSETS}")
        self.__debug_log(tran0, f"print 'WIDX: %d, W_NELE: %d, W_NELE_FD: %d, W_NELE_RM: %d, INIT_OFFSETS: %d, TEMP: %d' {WIDX} {W_NELE} {W_NELE_FD} {W_NELE_RM} {INIT_OFFSETS} {TEMP}")

        # NLEFT_LD = W_NELE
        tran0.writeAction(f"mov_reg2reg {W_NELE} {NLEFT_LD}")
        # NLEFT_ST = W_NELE
        tran0.writeAction(f"mov_reg2reg {W_NELE} {NLEFT_ST}")
        
        # tran0.writeAction(f"print 'Lane %d starts, widx=%d, nworker=%d, w_nele=%d, init_offsets=%d' NWID {WIDX} {NWORKERS} {W_NELE} {INIT_OFFSETS}")
        # prepare to start the loop
        W_NELE = "X22"
        LDPTR = "X23"
        STPTR = "X24"
        DST_SRC_DIFF = "X28"
        SRC_ALIGNED = "X29"
        NLEFT_STR = "X29"
        NLEFT_LD_ALIGNED = "X30"
        LDPTR_END = "X30"
        EV_WORD = "X31"
        TEMP0, TEMP1 = "X30", "X31"
        OUTGOING_READ = "X17"
        MAX_OUTGOING_READ = "X16" 
        
        tran0.writeAction(f"lshift {INIT_OFFSETS} {INIT_OFFSETS} {3 + self.ele_shift}")
        tran0.writeAction(f"add {SRC} {INIT_OFFSETS} {LDPTR}")
        tran0.writeAction(f"add {DST} {INIT_OFFSETS} {STPTR}")
        tran0.writeAction(f"mov_reg2reg {W_NELE} {NLEFT_STR}")
        tran0.writeAction(f"sub {DST} {SRC} {DST_SRC_DIFF}")
        # based on the config, choose the right function
        # start from loading max chunk size
        if self.impl == 'slow':
            tran0.writeAction(f"tranCarry_goto {self.block_action_map.get_ld_first_block_id(max(self.allowed_chunk_sizes), self.ele_size)}")
        elif self.impl == 'fast':
            # fast and fastest-unsafe mode
            tran0.writeAction(f"lshift {W_NELE} {LDPTR_END} {self.ele_shift}")
            tran0.writeAction(f"add {LDPTR} {LDPTR_END} {LDPTR_END}")
            tran0.writeAction(f"tranCarry_goto {self.block_action_map.get_event_ld_next(max(self.allowed_chunk_sizes), self.ele_size)}")
        elif self.impl == 'fastest':
            tran0.writeAction(f"mov_imm2reg {MAX_OUTGOING_READ} 32")
            tran0.writeAction(f"mov_imm2reg {OUTGOING_READ} 0") 
            tran0.writeAction(f"lshift {W_NELE} {LDPTR_END} {3 + self.ele_shift}")
            tran0.writeAction(f"add {LDPTR} {LDPTR_END} {LDPTR_END}")
            self.__load_first(tran0, max(self.allowed_chunk_sizes), self.ele_size)
            tran0.writeAction(f"tranCarry_goto {self.block_action_map.get_ld_first_block_id(max(self.allowed_chunk_sizes), self.ele_size)}")
        elif self.impl == 'test':
            tran0.writeAction(f"lshift {W_NELE} {LDPTR_END} {self.ele_shift}")
            tran0.writeAction(f"add {LDPTR} {LDPTR_END} {LDPTR_END}")
            tran0.writeAction(f"tranCarry_goto {self.block_action_map.get_ld_first_block_id(max(self.allowed_chunk_sizes), self.ele_size)}")
        elif self.impl == 'basim':    
            tran0.writeAction(f"mov_imm2reg {MAX_OUTGOING_READ} 32")
            tran0.writeAction(f"mov_imm2reg {OUTGOING_READ} 0") 
            tran0.writeAction(f"lshift {W_NELE} {LDPTR_END} {3 + self.ele_shift}")
            tran0.writeAction(f"add {LDPTR} {LDPTR_END} {LDPTR_END}")
            self.__load_first(tran0, max(self.allowed_chunk_sizes), self.ele_size)
        else:
            print(f"Error: unknown impl {self.impl}")
            exit(1)
        self.trans.append(tran0)
    
    # blockAction cannot be defined by the user program  
    def __terminate(self, tran, tlabel="terminate"):
        WIDX = "X21"
        TEMP = "X30"
        
        # FIXIME: since assembler will ignore this, we need this bogus line to make sure the label can be reached
        tran.writeAction(f"{tlabel}: addi {WIDX} {WIDX} 0") 
        # tran.writeAction(f"perflog 1 5 'Worker Read/write ends, NWID=%d, WIDX=%d' NWID {WIDX}")
        self.__perf_log(tran, f"perflog 1 5 'Worker Read/write ends, NWID=%d, WIDX=%d' NWID {WIDX}")
        tran.writeAction(f"sendr3_reply NWID {WIDX} {WIDX} {TEMP}") #TODO: need to change according to spec
        tran.writeAction(f"yieldt")
    
    def __load_first(self, tran, C, E):
        # C: chunk size; E: element size in word
        LDPTR = "X23"
        NLEFT_LD = "X25"
        BYTES_LEFT = "X27"
        WIDX = "X21"
        
        self.__debug_log(tran, f"print 'nasim: NWID=%d, next_chunk_{C}_{E}' NWID")
        tran.writeAction(f"blec {NLEFT_LD} 0 terminate")
        self.__load_next(tran, C, E)
        tran.writeAction(f"yield")
        self.__terminate(tran)
        
    def __load_next(self, tran, C, E):
        LDPTR = "X23"
        NLEFT_LD = "X25"
        WIDX = "X21"
        WORDS_LEFT = "X27"
        OUTGOING_READ = "X17"
        TEMP0, TEMP1 = "X30", "X31"
        # self.__debug_log(tran, f"print 'basim: NWID=%d, reading from %d, rnleft=%d' NWID {LDPTR} {NLEFT_LD}")
        # self.__debug_log(tran, f"print 'basim: NWID=%d, C={C}, E={E}' NWID")
        tran.writeAction(f"next_chunk_{C}_{E}: blec {NLEFT_LD} 0 done")
        tran.writeAction(f"lshift {NLEFT_LD} {WORDS_LEFT} {self.ele_shift}")
        self.__debug_log(tran, f"print 'WORDS_LEFT=%d, C={C}, E={E}' {WORDS_LEFT}")
        tran.writeAction(f"blec {WORDS_LEFT} {C-1} next_chunk_{self.__NEXT_CHUNK(C)}_{E}")
        if C <= 8:
            # self.__debug_log(tran, f"print 'NWID=%d, reading from %d, rnleft=%d' NWID {LDPTR} {NLEFT_LD}")
            # self.__debug_log(tran, f"print 'basim: NWID=%d, ' NWID {} {NLEFT_LD}")
            self.__debug_log(tran, f"print 'next_event=udshmem-load-store-loop-{C}; NLEFT_LD=%d; LDPTR=%ld' {NLEFT_LD} {LDPTR}")
            tran.writeAction(f"send_dmlm_ld_wret {LDPTR} {self.event_map[f'udshmem-load-store-loop-{C}']} {C} {TEMP0}")
            tran.writeAction(f"addi {LDPTR} {LDPTR} {C * 8}") # dram read/write still uses bytes
        else:
            for i in range(C // 8):
                tran.writeAction(f"send_dmlm_ld_wret {LDPTR} {self.event_map[f'udshmem-load-store-loop-{C}']} 8 {TEMP0}")
                tran.writeAction(f"addi {LDPTR} {LDPTR} 64") # dram read/write still uses bytes
        tran.writeAction(f"subi {NLEFT_LD} {NLEFT_LD} {C >> self.ele_shift}")
        tran.writeAction(f"addi {OUTGOING_READ} {OUTGOING_READ} {C // 8 if C > 8 else 1}")
        self.__debug_log(tran, f"print 'basim: NWID=%d, outgoing_read=%d' NWID {OUTGOING_READ}")
        tran.writeAction(f"yield")
        if C != 1:
            self.__load_next(tran, self.__NEXT_CHUNK(C), E)
        else:
            tran.writeAction(f"done: yield")
        
    
    def __ev_ack(self, C):
        WIDX = "X21"
        W_NELE = "X22"
        NLEFT_ST = "X26"
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.event_map[f'udshmem-ack-{C}'])
        # tran.writeAction(f"blec {W_NELE} {NLEFT_ST}")
        tran.writeAction(f"subi {NLEFT_ST} {NLEFT_ST} {C >> self.ele_shift}")
        tran.writeAction(f"blec {NLEFT_ST} 0 ack_terminate")
        tran.writeAction(f"yield")
        # label is in the termniate
        self.__terminate(tran, "ack_terminate")
        
        
    def __ev_load_store_loop(self, C, E):
        WIDX = "X21"
        W_NELE = "X22"
        
        STPTR = "X24"
        NLEFT_LD = "X25"
        DST_SRC_DIFF = "X28"
        NLEFT_STR = "X29"
        
        OUTGOING_READ = "X17"
        MAX_OUTGOING_READ = "X16"
        TEMP0, TEMP1 = "X30", "X31"
        
        
        chunk_size = C if C <= 8 else 8
        RETURN_ADDR_REG = 'X' + str((chunk_size + 8) if chunk_size < 8 else 3)
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.event_map[f'udshmem-load-store-loop-{C}'])
        # debug log if we want
        self.__debug_log(tran, f"print 'read-returns {C} {E}'")
        tran.writeAction(f"add {RETURN_ADDR_REG} {DST_SRC_DIFF} {STPTR}")
        tran.writeAction(f"subi {NLEFT_STR} {NLEFT_STR} {chunk_size >> self.ele_shift}")
        if C > 8:
            tran.writeAction(f"sendops_dmlm_wret {STPTR} {self.event_map['udshmem-ack-8']} X8 8 {TEMP0}")
        else:
            tran.writeAction(f"sendops_dmlm_wret {STPTR} {self.event_map[f'udshmem-ack-{C}']} X8 {C} {TEMP0}")
        tran.writeAction(f"subi {OUTGOING_READ} {OUTGOING_READ} 1")
        tran.writeAction(f"bgt {OUTGOING_READ} {MAX_OUTGOING_READ} wait_next")
        tran.writeAction(f"blec {NLEFT_LD} 0 no_more_reads")
        self.__load_next(tran, C, E)
        tran.writeAction(f"no_more_reads: yield")
        tran.writeAction(f"wait_next: yield")
        
    
    # slow-safe, fast, fastest-unsafe
    def __ba_terminate(self, block_id):
        WIDX = "X21"
        # efa.appendBlockAction(block_id, f"print 'terminate at widx=%d' {WIDX}")
        # TODO: add perflog
        self.efa.appendBlockAction(block_id, f"perflog 1 5 'Worker Read/write ends, NWID=%d, WIDX=%d' NWID {WIDX}")
        self.efa.appendBlockAction(block_id, f"send4_reply NWID {WIDX}")
        self.efa.appendBlockAction(block_id, "yield_terminate")

    
    # safe-slow mode
    def __ba_load_first_slow(self, block_id, C, ele_size):
        WIDX = "X21"
        LDPTR = "X23"
        NLEFT_LD = "X25"
        BYTES_LEFT = "X27"
        BATCH_COUNTER = "X30"
        
        self.efa.appendBlockAction(block_id, f"mov_imm2reg {BATCH_COUNTER} 0")
        self.efa.appendBlockAction(block_id, f"blec {NLEFT_LD} 0 terminate") # if NLEFT_LD <= 0, terminate
        self.efa.appendBlockAction(block_id, f"lshift {NLEFT_LD} {BYTES_LEFT} {self.ele_size}")    # BYTES_LEFT = NLEFT_LD << SHIFT_MAP[ele_size]
        self.efa.appendBlockAction(block_id, f"blec {BYTES_LEFT} 7 ld_subword")  # if BYTES_LEFT <= 7, go to ld_subword
        self.efa.appendBlockAction(block_id, f"tranCarry_goto {self.block_action_map.get_ld_next_block_id(C, ele_size)}")
        self.efa.appendBlockAction(block_id, f"ld_subword: send_dmlm_ld_wret {LDPTR} {self.event_map[f'udshmem-load-store-loop-slow-{C}']} 8")
        self.efa.appendBlockAction(block_id, "yield")
        self.efa.appendBlockAction(block_id, f"terminate: tranCarry_goto {self.block_action_map.get_block_id('terminate')}") 
        
        
    def __ba_load_next_slow(self, block_id, C, ele_size):
        LDPTR = "X23"
        NLEFT_LD = "X25"
        WIDX = "X21"
        BYTES_LEFT = "X27"

        self.efa.appendBlockAction(block_id, f"blec {NLEFT_LD} 0 done")  # if NLEFT_LD <= 0, terminate
        self.efa.appendBlockAction(block_id, f"lshift {NLEFT_LD} {BYTES_LEFT} {self.ele_shift}")    # BYTES_LEFT = NLEFT_LD << SHIFT_MAP[ele_size]
        self.efa.appendBlockAction(block_id, f"blec {BYTES_LEFT} {C-1} next_chunk_{C}_{ele_size}")   # if BYTES_LEFT > C-1, go to ld_next_{C}_{ele_size}
        # efa.appendBlockAction(block_id, f"print 'NWID=%d, reading from %d, rnleft=%d' NWID {LDPTR} {NLEFT_LD} ")
        if C <= 64:
            # load small chunk
            self.efa.appendBlockAction(block_id, f"send_dmlm_ld_wret {LDPTR} {self.event_map[f'load-store-loop-slow-{C}']} {C}")
            self.efa.appendBlockAction(block_id, f"addi {LDPTR} {LDPTR} {C}") 
        else:
            #load large chunk
            # TODO: if C >> 64, we need to write a loop to load multiple 64-byte chunks
            for i in range(C // 64):
                self.efa.appendBlockAction(block_id, f"send_dmlm_ld_wret {LDPTR} {self.event_map[f'load-store-loop-slow-{C}']} 64")
                self.efa.appendBlockAction(block_id, f"addi {LDPTR} {LDPTR} 64") 
        self.efa.appendBlockAction(block_id, f"subi {NLEFT_LD} {NLEFT_LD} {C >> self.ele_shift}")
        self.efa.appendBlockAction(block_id, "yield")
        self.efa.appendBlockAction(block_id, f"next_chunk_{C}_{ele_size}: tranCarry_goto {self.block_action_map.get_ld_first_block_id(self.__NEXT_CHUNK(C), ele_size)}")
        # efa.appendBlockAction(block_id, "yield")
        self.efa.appendBlockAction(block_id, f"done: perflog 1 9 'Worker Read ends, NWID=%d, WIDX=%d, WORKER_NELE=%d' NWID {WIDX} {NLEFT_LD}")
        # efa.appendBlockAction(block_id, f"print 'Worker Read ends, NWID=%d, WIDX=%d, WORKER_NELE=%d' NWID {WIDX} {NLEFT_LD}")
        self.efa.appendBlockAction(block_id, f"yield")
        # efa.appendBlockAction(block_id, f"done: yield")
    
    
    def __ack_slow(self, C):
        NLEFT_ST = "X26"
        tranx = self.state.writeTransition("eventCarry", self.state, self.state, self.event_map[f'ack-{C}'])
        
        tranx.writeAction(f"subi {NLEFT_ST} {NLEFT_ST} {C >> self.ele_shift}")        # nleft_st -= S>>3
        tranx.writeAction(f"blec {NLEFT_ST} 0 terminate")
        tranx.writeAction("yield")
        tranx.writeAction(f"terminate: tranCarry_goto {self.block_action_map.get_block_id('terminate')}")

        self.trans.append(tranx)
    

    def __load_store_loop_slow(self, C):
        SRC = "X17"
        DST = "X18"

        WIDX = "X21"
        W_NELE = "X22"
        LDPTR = "X23"
        STPTR = "X24"
        NLEFT_LD = "X25"
        NLEFT_ST = "X26"
        BYTES_LEFT = "X27"
        DST_SRC_DIFF = "X28"
        BATCH_COUNTER = "X30"
        NLEFT_STR = "X29"
        chunk_size = C if C <= 64 else 64
       
        RETURN_ADDR_REG = 'X' + str((chunk_size // 8 + 8) if chunk_size // 8 < 8 else 3)


        tranx = self.state.writeTransition("eventCarry", self.state, self.state, self.event_map[f'load-store-loop-slow-{C}'])
        tranx.writeAction(f"ble {W_NELE} {NLEFT_STR} write_first")
        tranx.writeAction(f"jmp after_write_first")
        tranx.writeAction(f"write_first: perflog 1 11 'Write first, NWID=%d, WIDX=%d' NWID {WIDX}")
        tranx.writeAction(f"after_write_first: add {RETURN_ADDR_REG} {DST_SRC_DIFF} {STPTR}")   # stptr = dst + (rtr_addr - src) # the relative offset
        tranx.writeAction(f"subi {NLEFT_STR} {NLEFT_STR} {chunk_size >> self.ele_shift}")        # nleft_st -= S>>3
        if C > 64:
            tranx.writeAction(f"sendops_dmlm_wret {STPTR} {self.event_map[f'ack-64']} X8 8")
            tranx.writeAction(f"addi {BATCH_COUNTER} {BATCH_COUNTER} 1")
            tranx.writeAction(f"blec {BATCH_COUNTER} {C // 64 - 1} wait_next")  # if counter <= C//64 -1, go to wait_next. when counter == C//64, meaning next load
        else:
            tranx.writeAction(f"sendops_dmlm_wret {STPTR} {self.event_map[f'ack-{C}']} X8 {C//8}")
        tranx.writeAction(f"blec {NLEFT_STR} 0 write_done")
        tranx.writeAction(f"mov_imm2reg {BATCH_COUNTER} 0")
        tranx.writeAction(f"tranCarry_goto {self.block_action_map.get_ld_next_block_id(C, self.ele_size)}")
        tranx.writeAction("wait_next: yield")
        tranx.writeAction(f"write_done: perflog 1 10 'Write finished, NWID=%d, WIDX=%d' NWID {WIDX}")
        tranx.writeAction(f"yield")
        self.trans.append(tranx)


        
    # fastest-unsafe mode
    def __ba_load_first_fastest(self, block_id, C, ele_size):
        LDPTR = "X23"
        NLEFT_LD = "X25"
        BYTES_LEFT = "X27"
        WORDS_LEFT = "X27"
        WIDX = "X21"  
        # self.__debug_log(self.efa, f"print 'NWID=%d, reading from %d, rnleft=%d, C={C}' NWID {LDPTR} {NLEFT_LD}", isEFA=True, block_id=block_id)
        self.efa.appendBlockAction(block_id, f"blec {NLEFT_LD} 0 terminate") # if NLEFT_LD <= 0, terminate
        # self.efa.appendBlockAction(block_id, f"lshift {NLEFT_LD} {BYTES_LEFT} {self.ele_shift}")    # BYTES_LEFT = NLEFT_LD << SHIFT_MAP[ele_size]
        # self.efa.appendBlockAction(block_id, f"blec {BYTES_LEFT} 7 ld_subword")  # if BYTES_LEFT <= 7, go to ld_subword
        # self.efa.appendBlockAction(block_id, f"lshift {NLEFT_LD} {WORDS_LEFT} {self.ele_shift}")    # WORDS_LEFT = NLEFT_LD << SHIFT_MAP[ele_size]
        # self.efa.appendBlockAction(block_id, f"blec {WORDS_LEFT} 7 ld_subword")  # if BYTES_LEFT <= 7, go to ld_subword
       
        self.efa.appendBlockAction(block_id, f"tranCarry_goto {self.block_action_map.get_ld_next_block_id(C, ele_size)}")
        # isav2.1 - begin
        # self.efa.appendBlockAction(block_id, f"ld_subword: send_dmlm_ld_wret {LDPTR} {self.event_map[f'udshmem-load-store-loop-fastest-8']} 8")
        # isav2.1 - end
        # isav2.3 - begin
        # self.efa.appendBlockAction(block_id, f"ld_subword: send_dmlm_ld_wret {LDPTR} {self.event_map[f'udshmem-load-store-loop-fastest-1']} 1")
        self.efa.appendBlockAction(block_id, "yield")
        self.efa.appendBlockAction(block_id, f"terminate: tranCarry_goto {self.block_action_map.get_block_id('terminate')}")


    def __ba_load_next_fastest(self, block_id, C, ele_size):
        LDPTR = "X23"
        NLEFT_LD = "X25"
        WIDX = "X21"
        BYTES_LEFT = "X27"
        WORDS_LEFT = "X27"
        OUTGOING_READ = "X17"

        self.efa.appendBlockAction(block_id, f"blec {NLEFT_LD} 0 done")  # if NLEFT_LD <= 0, terminate
        # self.efa.appendBlockAction(block_id, f"lshift {NLEFT_LD} {BYTES_LEFT} {self.ele_shift}")    # BYTES_LEFT = NLEFT_LD << SHIFT_MAP[ele_size]
        # self.efa.appendBlockAction(block_id, f"blec {BYTES_LEFT} {C-1} next_chunk_{C}_{ele_size}")   # if BYTES_LEFT > C-1, go to ld_next_{C}_{ele_size}
        self.efa.appendBlockAction(block_id, f"lshift {NLEFT_LD} {WORDS_LEFT} {self.ele_shift}")    # BYTES_LEFT = NLEFT_LD << SHIFT_MAP[ele_size]
        self.efa.appendBlockAction(block_id, f"blec {WORDS_LEFT} {C-1} next_chunk_{C}_{ele_size}")   # if BYTES_LEFT > C-1, go to ld_next_{C}_{ele_size}
        if C <= 8:
            self.__debug_log(self.efa, f"print 'NWID=%d, reading from %d, rnleft=%d, C={C}' NWID {LDPTR} {NLEFT_LD}", isEFA=True, block_id=block_id)
            self.efa.appendBlockAction(block_id, f"send_dmlm_ld_wret {LDPTR} {self.event_map[f'udshmem-load-store-loop-fastest-{C}']} {C}")
            # self.efa.appendBlockAction(block_id, f"addi {LDPTR} {LDPTR} {C}")
            self.efa.appendBlockAction(block_id, f"addi {LDPTR} {LDPTR} {C*8}") 
        else:
            # for i in range(C // 64):
            for i in range(C // 8):
                self.efa.appendBlockAction(block_id, f"send_dmlm_ld_wret {LDPTR} {self.event_map[f'udshmem-load-store-loop-fastest-{C}']} 8")
                self.efa.appendBlockAction(block_id, f"addi {LDPTR} {LDPTR} 64")
        # self.efa.appendBlockAction(block_id, f"subi {NLEFT_LD} {NLEFT_LD} {C >> self.ele_shift}")
        self.efa.appendBlockAction(block_id, f"subi {NLEFT_LD} {NLEFT_LD} {C >> self.ele_shift}")
        # add static throttling
        # self.efa.appendBlockAction(block_id, f"addi {OUTGOING_READ} {OUTGOING_READ} {C // 64 if C > 64 else 1}")
        self.efa.appendBlockAction(block_id, f"addi {OUTGOING_READ} {OUTGOING_READ} {C // 8 if C > 8 else 1}")      
        self.efa.appendBlockAction(block_id, "yield")
        self.efa.appendBlockAction(block_id, f"next_chunk_{C}_{ele_size}: tranCarry_goto {self.block_action_map.get_ld_first_block_id(self.__NEXT_CHUNK(C), ele_size)}")
        self.efa.appendBlockAction(block_id, f"done: perflog 1 9 'Worker Read ends, NWID=%d, WIDX=%d, WORKER_NELE=%d' NWID {WIDX} {NLEFT_LD}")
        self.__debug_log(self.efa, f"print 'Worker Read ends, NWID=%d, WIDX=%d, WORKER_NELE=%d' NWID {WIDX} {NLEFT_LD}", isEFA=True, block_id=block_id)
        self.efa.appendBlockAction(block_id, f"yield")
        
    
    def __ack_fastest(self, C):
        WIDX = "X21"
        W_NELE = "X22"
        NLEFT_ST = "X26" 
        
        tranx = self.state.writeTransition("eventCarry", self.state, self.state, self.event_map[f'udshmem-ack-{C}'])
        tranx.writeAction(f"blec {W_NELE} {NLEFT_ST} ack_first")
        tranx.writeAction(f"jmp after_ack_first")
        tranx.writeAction(f"ack_first: perflog 1 12 'Ack first, NWID=%d, WIDX=%d' NWID {WIDX}")
        tranx.writeAction(f"after_ack_first: subi {NLEFT_ST} {NLEFT_ST} {C >> self.ele_shift}")        # nleft_st -= S>>3
        tranx.writeAction(f"blec {NLEFT_ST} 0 terminate")
        tranx.writeAction("yield")
        tranx.writeAction(f"terminate: tranCarry_goto {self.block_action_map.get_block_id('terminate')}")

        self.trans.append(tranx)
        
   
   
    def __load_store_loop_fastest(self, C, E):
        SRC = "X17"
        DST = "X18"

        WIDX = "X21"
        W_NELE = "X22"
        LDPTR = "X23"
        STPTR = "X24"
        NLEFT_LD = "X25"
        NLEFT_ST = "X26"
        BYTES_LEFT = "X27"
        DST_SRC_DIFF = "X28"
        BATCH_COUNTER = "X29"
        NLEFT_STR = "X29"
        TMP_STPTR = "X30"
        
        OUTGOING_READ = "X17"
        MAX_OUTGOING_READ = "X16"
        
        # isav2.1 - begin
        # chunk_size = C if C <= 64 else 64
        # RETURN_ADDR_REG = 'X' + str((chunk_size // 8 + 8) if chunk_size // 8 < 8 else 3)
        # isav2.1 - end
        
        chunk_size = C if C <=8 else 8
        RETURN_ADDR_REG = 'X' + str((chunk_size + 8) if chunk_size < 8 else 3)
        

        tranx = self.state.writeTransition("eventCarry", self.state, self.state, self.event_map[f'udshmem-load-store-loop-fastest-{C}'])
        self.__debug_log(tranx, f"print 'NWID=%d, read return from %ld, rnleft=%d, C={C}' NWID {RETURN_ADDR_REG} {NLEFT_LD}")
        tranx.writeAction(f"ble {W_NELE} {NLEFT_STR} write_first")
        tranx.writeAction(f"jmp after_write_first")
        tranx.writeAction(f"write_first: perflog 1 11 'Write first, NWID=%d, WIDX=%d' NWID {WIDX}")
        tranx.writeAction(f"after_write_first: add {RETURN_ADDR_REG} {DST_SRC_DIFF} {STPTR}")   # stptr = dst + (rtr_addr - src) # the relative offset
        tranx.writeAction(f"subi {NLEFT_STR} {NLEFT_STR} {chunk_size >> self.ele_shift}")        # nleft_st -= S>>3
        
        # if C > 64:
            # tranx.writeAction(f"sendops_dmlm_wret {STPTR} {self.event_map[f'udshmem-ack-64']} X8 8")
        # else:
            # tranx.writeAction(f"sendops_dmlm_wret {STPTR} {self.event_map[f'udshmem-ack-{C}']} X8 {C//8}")
        # self.__debug_log(tranx, f"print 'write: NWID = %ld, WIDX = %ld, return_addr=%lx, stptr=%lx, nleft_st=%ld' NWID {WIDX} {RETURN_ADDR_REG} {STPTR} {NLEFT_STR}")
        if C > 8:
            tranx.writeAction(f"sendops_dmlm_wret {STPTR} {self.event_map[f'udshmem-ack-8']} X8 8")
        else:
            tranx.writeAction(f"sendops_dmlm_wret {STPTR} {self.event_map[f'udshmem-ack-{C}']} X8 {C}")
        tranx.writeAction(f"subi {OUTGOING_READ} {OUTGOING_READ} 1")
        tranx.writeAction(f"bgt {OUTGOING_READ} {MAX_OUTGOING_READ} wait_next")
        tranx.writeAction(f"blec {NLEFT_STR} 0 write_done")
        tranx.writeAction(f"blec {NLEFT_LD} 0 no_more_reads")        
        tranx.writeAction(f"tranCarry_goto {self.block_action_map.get_ld_next_block_id(C, self.ele_size)}")
        tranx.writeAction(f"write_done: perflog 1 10 'Write finished, NWID=%d, WIDX=%d' NWID {WIDX}")
        tranx.writeAction(f"no_more_reads: yield")
        tranx.writeAction(f"wait_next: yield")
        self.trans.append(tranx)
    
    
    # fast mode
    def __ba_load_next_fast(self, block_id, C, E):
        WIDX = "X21"
        EV_WORD = "X31"
    
        self.efa.appendBlockAction(block_id, f"ev_update_1 X2 {EV_WORD} {self.event_map[f'load-loop-fast-{C}']} 1")  # if NLEFT_LD <= 0, terminate
        self.efa.appendBlockAction(block_id, f"send4_wcont {EV_WORD} NWID X1 X16 X17") # X16 X17 are just placeholders
        self.efa.appendBlockAction(block_id, f"yield")
     


    def __load_loop_fast(self, C, E):
        WIDX = "X21"
        LDPTR = "X23"
        LDPTR_END = "X30"
        BYTES_LEFT = "X27"
        tranx = self.state.writeTransition("eventCarry", self.state, self.state, self.event_map[f'load-loop-fast-{C}'])
        tranx.writeAction(f"ble {LDPTR_END} {LDPTR} read_done")  # if nleft_ld <= 0, terminate
        tranx.writeAction(f"sub {LDPTR_END} {LDPTR} {BYTES_LEFT}")
        tranx.writeAction(f"blec {BYTES_LEFT} {C-1} next-chunk-{C}-{E}")  # if BYTES_LEFT <= 7, go to ld_subword
        if C > 64:
            for i in range(C // 64):
                tranx.writeAction(f"send_dmlm_ld_wret {LDPTR} {self.event_map[f'store-64']} 64")
                tranx.writeAction(f"addi {LDPTR} {LDPTR} 64")
        else:
            tranx.writeAction(f"send_dmlm_ld_wret {LDPTR} {self.event_map[f'store-{C}']} {C}")
            tranx.writeAction(f"addi {LDPTR} {LDPTR} {C}")
            
        tranx.writeAction(f"tranCarry_goto {self.block_action_map.get_event_ld_next(C, E)}")
        tranx.writeAction(f"yield")
        tranx.writeAction(f"next-chunk-{C}-{E}: tranCarry_goto {self.block_action_map.get_event_ld_next(self.__NEXT_CHUNK(C), E)}")
        tranx.writeAction(f"read_done: perflog 1 9 'Reads finished, NWID=%d, WIDX=%d' NWID {WIDX}") # test-only
        tranx.writeAction(f"yield")
        self.trans.append(tranx)
        
   
    def __store_fast(self, C):
        WIDX = "X21"
        W_NELE = "X22"
        STRPTR = "X24"
        NLEFT_ST = "X26"
        DST_SRC_DIFF = "X28"
        NLEFT_STR = "X29"
        
        chunk_size = C if C <= 64 else 64
       
        RETURN_ADDR_REG = 'X' + str((chunk_size // 8 + 8) if chunk_size // 8 < 8 else 3)
        tranx = self.state.writeTransition("eventCarry", self.state, self.state, self.event_map[f'store-{C}'])
        tranx.writeAction(f"blec {W_NELE} {NLEFT_STR} write_first")
        tranx.writeAction(f"jmp after_write_first")
        tranx.writeAction(f"write_first: perflog 1 11 'Write first, NWID=%d, WIDX=%d' NWID {WIDX}")
        tranx.writeAction(f"after_write_first: add {RETURN_ADDR_REG} {DST_SRC_DIFF} {STRPTR}")   # stptr = dst + (rtr_addr - src) # the relative offset
        tranx.writeAction(f"sendops_dmlm_wret {STRPTR} {self.event_map[f'ack-{C}']} X8 {C // 8}")
        
        tranx.writeAction(f"subi {NLEFT_STR} {NLEFT_STR} {C >> self.ele_shift}")        # nleft_st -= S>>3
        tranx.writeAction(f"blec {NLEFT_STR} 0 write_done")
        tranx.writeAction("yield")
        tranx.writeAction(f"write_done: perflog 1 10 'Write finished, NWID=%d, WIDX=%d' NWID {WIDX}")
        tranx.writeAction(f"yield")
        
        self.trans.append(tranx)
        

    
    def __ack_fast(self, C):
        W_NELE = "X22"
        NLEFT_ST = "X26"
        
        WIDX = "X21"
        TMP_STPTR = "X30"
        tranx = self.state.writeTransition("eventCarry", self.state, self.state, self.event_map[f'ack-{C}'])
        tranx.writeAction(f"blec {W_NELE} {NLEFT_ST} ack_first")
        tranx.writeAction(f"jmp after_ack_first")
        tranx.writeAction(f"ack_first: perflog 1 12 'Ack first, NWID=%d, WIDX=%d' NWID {WIDX}")
        tranx.writeAction(f"after_ack_first: subi {NLEFT_ST} {NLEFT_ST} {C >> self.ele_shift}")        # nleft_st -= S>>3
        tranx.writeAction(f"blec {NLEFT_ST} 0 terminate")
        tranx.writeAction("yield")
        tranx.writeAction(f"terminate: tranCarry_goto {self.block_action_map.get_block_id('terminate')}")
        self.trans.append(tranx)      
        

        
    # test mode
    def __ba_load_first_test(self, block_id, C, ele_size):
        LDPTR = "X23"
        NLEFT_LD = "X25"
        BYTES_LEFT = "X27"
        WIDX = "X21"  
        self.efa.appendBlockAction(block_id, f"blec {NLEFT_LD} 0 terminate") # if NLEFT_LD <= 0, terminate
        self.efa.appendBlockAction(block_id, f"lshift {NLEFT_LD} {BYTES_LEFT} {self.ele_shift}")    # BYTES_LEFT = NLEFT_LD << SHIFT_MAP[ele_size]
        self.efa.appendBlockAction(block_id, f"blec {BYTES_LEFT} 7 ld_subword")  # if BYTES_LEFT <= 7, go to ld_subword
        self.efa.appendBlockAction(block_id, f"tranCarry_goto {self.block_action_map.get_ld_next_block_id(C, ele_size)}")
        self.efa.appendBlockAction(block_id, f"ld_subword: send_dmlm_ld_wret {LDPTR} {self.event_map[f'load-store-loop-fastest-8']} 8")
        self.efa.appendBlockAction(block_id, "yield")
        self.efa.appendBlockAction(block_id, f"terminate: tranCarry_goto {self.block_action_map.get_block_id('terminate')}")


    def __ba_load_next_test(self, block_id, C, ele_size):
        LDPTR = "X23"
        NLEFT_LD = "X25"
        WIDX = "X21"
        BYTES_LEFT = "X27"

        self.efa.appendBlockAction(block_id, f"blec {NLEFT_LD} 0 done")  # if NLEFT_LD <= 0, terminate
        self.efa.appendBlockAction(block_id, f"lshift {NLEFT_LD} {BYTES_LEFT} {self.ele_shift}")    # BYTES_LEFT = NLEFT_LD << SHIFT_MAP[ele_size]
        self.efa.appendBlockAction(block_id, f"blec {BYTES_LEFT} {C-1} next_chunk_{C}_{ele_size}")   # if BYTES_LEFT > C-1, go to ld_next_{C}_{ele_size}
        if C <= 64:
            self.efa.appendBlockAction(block_id, f"send_dmlm_ld_wret {LDPTR} {self.event_map[f'load-store-loop-fastest-{C}']} {C}")
            self.efa.appendBlockAction(block_id, f"addi {LDPTR} {LDPTR} {C}") 
        else:
            for i in range(C // 64):
                # the difference for test is it will always send 64 bytes
                self.efa.appendBlockAction(block_id, f"send_dmlm_ld_wret {LDPTR} {self.event_map[f'load-store-loop-fastest-{C}']} 64")
                self.efa.appendBlockAction(block_id, f"addi {LDPTR} {LDPTR} 64") 
        self.efa.appendBlockAction(block_id, f"subi {NLEFT_LD} {NLEFT_LD} {C >> self.ele_shift}")
        self.efa.appendBlockAction(block_id, "yield")
        self.efa.appendBlockAction(block_id, f"next_chunk_{C}_{ele_size}: tranCarry_goto {self.block_action_map.get_ld_first_block_id(self.__NEXT_CHUNK(C), ele_size)}")
        self.efa.appendBlockAction(block_id, f"done: perflog 1 9 'Worker Read ends, NWID=%d, WIDX=%d, WORKER_NELE=%d' NWID {WIDX} {NLEFT_LD}")
        self.efa.appendBlockAction(block_id, f"yield")
        
    
    def __ack_test(self, C):
        WIDX = "X21"
        W_NELE = "X22"
        NLEFT_ST = "X26" 
        
        tranx = self.state.writeTransition("eventCarry", self.state, self.state, self.event_map[f'ack-{C}'])
        tranx.writeAction(f"blec {W_NELE} {NLEFT_ST} ack_first")
        tranx.writeAction(f"jmp after_ack_first")
        tranx.writeAction(f"ack_first: perflog 1 12 'Ack first, NWID=%d, WIDX=%d' NWID {WIDX}")
        tranx.writeAction(f"after_ack_first: subi {NLEFT_ST} {NLEFT_ST} {C >> self.ele_shift}")        # nleft_st -= S>>3
        tranx.writeAction(f"blec {NLEFT_ST} 0 terminate")
        tranx.writeAction("yield")
        tranx.writeAction(f"terminate: tranCarry_goto {self.block_action_map.get_block_id('terminate')}")

        self.trans.append(tranx)
        
   
   
    def __load_store_loop_test(self, C, E):
        SRC = "X17"
        DST = "X18"

        WIDX = "X21"
        W_NELE = "X22"
        LDPTR = "X23"
        STPTR = "X24"
        NLEFT_LD = "X25"
        NLEFT_ST = "X26"
        BYTES_LEFT = "X27"
        DST_SRC_DIFF = "X28"
        BATCH_COUNTER = "X29"
        NLEFT_STR = "X29"
        TMP_STPTR = "X30"
        chunk_size = C if C <= 64 else 64
       
        RETURN_ADDR_REG = 'X' + str((chunk_size // 8 + 8) if chunk_size // 8 < 8 else 3)


        tranx = self.state.writeTransition("eventCarry", self.state, self.state, self.event_map[f'load-store-loop-fastest-{C}'])
        tranx.writeAction(f"ble {W_NELE} {NLEFT_STR} write_first")
        tranx.writeAction(f"jmp after_write_first")
        tranx.writeAction(f"write_first: perflog 1 11 'Write first, NWID=%d, WIDX=%d' NWID {WIDX}")
        tranx.writeAction(f"after_write_first: add {RETURN_ADDR_REG} {DST_SRC_DIFF} {STPTR}")   # stptr = dst + (rtr_addr - src) # the relative offset
        tranx.writeAction(f"subi {NLEFT_STR} {NLEFT_STR} {chunk_size >> self.ele_shift}")        # nleft_st -= S>>3
        if C > 64:
            tranx.writeAction(f"sendops_dmlm_wret {STPTR} {self.event_map[f'ack-64']} X8 8")
        else:
            tranx.writeAction(f"sendops_dmlm_wret {STPTR} {self.event_map[f'ack-{C}']} X8 {C//8}")
        tranx.writeAction(f"blec {NLEFT_STR} 0 write_done")
        tranx.writeAction(f"tranCarry_goto {self.block_action_map.get_ld_next_block_id(C, self.ele_size)}")
        tranx.writeAction(f"write_done: perflog 1 10 'Write finished, NWID=%d, WIDX=%d' NWID {WIDX}")
        tranx.writeAction(f"yield")
        self.trans.append(tranx)
    
