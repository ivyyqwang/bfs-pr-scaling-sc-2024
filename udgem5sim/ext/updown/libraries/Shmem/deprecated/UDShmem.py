from math import log2
import time 
perflog_map = {
    'start': 0,
    'end-all': 1,
    'start-ud-master': 2,
    'distribute-workers': 3,
    'start-ud-worker': 4,
    'start-worker-rw': 5,
    'end-worker-rw': 6,
    'end-ud': 7,
    'ud-no-workers': 8,
    'end-worker-read': 9,
    'end-worker-write': 10,
    'start-worker-write': 11,
    'start-worker-ack': 12,
    'start-worker-read': 13,
}

pmap = {
    'all-start': 0,
    'all-end': 1,
    'head-tail-starts': 2,
    'worker-starts': 3,
    'worker-read-ends': 4,
    'worker-write-starts': 5,
    'worker-write-ends': 6,
    'worker-ack-starts': 7,
    'worker-ends': 8,
    'worker-read-starts': 9,
}

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
    def __str__(self) -> str:
        r = ""
        for k, v in self.event_map.items():
            r += f"{k} -> {v}\n"
        return r



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
    OPCODE_SHMEM_GET = 0
    OPCODE_SHMEM_IGET = 1
    # Notes:
    # In ISAv2.3 all the sizes are in words, before are in bytes
    def __init__(self, efa, state=None, event_map_start=0, debug=0, lm_base=2048, config_offset=16 << 3, flag_offset= 1 << 3, ele_size=1, largest_chunk=16, impl='basim', linker=False, perflog=False, test=False):
        # configs
        self.lm_base = lm_base
        self.flag_offset = flag_offset
        self.ele_size = ele_size    # legal values are 2^x
        self.config_offset = config_offset
        self.allowed_chunk_sizes = [1, 2, 4, 8]
        self.default_chunk_sizes = [1, 2, 4, 8]
        self.nconfigs = 7
        
        self.isUbenchWrite = False
        self.test = test
        if largest_chunk is not None:
            self.allowed_chunk_sizes = [2**i for i in range(int(log2(largest_chunk))+1)] # 16 ~ largest_chunk
        self.debug = debug
        print(largest_chunk)
        print(self.allowed_chunk_sizes)
        print("Perflog is ", perflog)
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
        self.perflog = perflog
        print(f"UDShmem Instance: Implementation: {self.impl}")
        if self.impl == "subench-write":
            self.isUbenchWrite = True
        self.__generate_efa()
        print(self.event_map)

    # inline function
    def call_udshmem_get(self, tran, reg_src, reg_dst, reg_nelem, reg0, reg1, reg2, reg3, reg4, cont_label=1, reg_target_nwid="NWID"):
        LM_BASE = reg0
        LM_PTR = reg1
        REG_EVENT_WORD = reg2
        REG_TARGET_NWID = reg_target_nwid
        REG_EVENT_WORD = reg2
        if self.impl.startswith("subench"):
            self.call_udshmem_ubench(tran, reg0, reg1, reg2, reg3, cont_label=cont_label, reg_target_nwid=reg_target_nwid)
            return 
        OP = reg3
        REG_TARGET_NWID = reg_target_nwid
        # self.__debug_log(tran, f"print '==================UDSHMEM BEGIN================='") # new line        
        self.__debug_log(tran, f"print 'USER: Calling Inline UDShmem_get  at NWID=%ld' NWID")
        # self.__perf_log(tran, f"perflog 1 {perflog_map['start']} 'UDSHMEM Begins!'")
        tran.writeAction(f'addi X7 {LM_BASE} {self.lm_base + self.config_offset + self.flag_offset}')
        tran.writeAction(f'mov_imm2reg {LM_PTR} 0')
        tran.writeAction(f"movwrl {reg_src} {LM_BASE}({LM_PTR},1,0)")
        tran.writeAction(f"movwrl {reg_dst} {LM_BASE}({LM_PTR},1,0)")
        tran.writeAction(f"movwrl {reg_nelem} {LM_BASE}({LM_PTR},1,0)")
        tran.writeAction(f"evii {REG_EVENT_WORD} {self.event_map['udshmem-shmem-get']} 255 {0b0101}")
        tran.writeAction(f"ev {REG_EVENT_WORD} {REG_EVENT_WORD} {REG_TARGET_NWID} {REG_TARGET_NWID} {0b1000}")
        if self.test:
            tran.writeAction(f"sendops_wret {REG_EVENT_WORD} {cont_label} X8 8 {reg3}") # now $len is in words
        else:
            tran.writeAction(f"send_wret {REG_EVENT_WORD} {cont_label} {LM_BASE} 3 {reg3} {reg4}") # now $len is in words
        tran.writeAction(f"yield")


    def call_udshmem_iget(self, tran, reg_src, reg_dst, reg_nelem, reg0, reg1, reg2, reg3, reg4, cont_label=1, reg_target_nwid="NWID"):
        LM_BASE = reg0
        LM_PTR = reg1
        REG_EVENT_WORD = reg2
        REG_TARGET_NWID = reg_target_nwid
        self.__debug_log(tran, f"print '==================UDSHMEM BEGIN================='") # new line        
        self.__debug_log(tran, f"print 'USER: Calling Inline UDShmem_get  at NWID=%ld' NWID")
        self.__perf_log(tran, f"perflog 1 {perflog_map['start']} 'UDSHMEM Begins!'")
        tran.writeAction(f'addi X7 {LM_BASE} {self.lm_base + self.config_offset + self.flag_offset}')
        tran.writeAction(f'mov_imm2reg {LM_PTR} 0')
        tran.writeAction(f"movwrl {reg_src} {LM_BASE}({LM_PTR},1,0)")
        tran.writeAction(f"movwrl {reg_dst} {LM_BASE}({LM_PTR},1,0)")
        tran.writeAction(f"movwrl {reg_nelem} {LM_BASE}({LM_PTR},1,0)")
        tran.writeAction(f"evii {REG_EVENT_WORD} {self.event_map['udshmem-shmem-iget']} 255 {0b0101}")
        tran.writeAction(f"ev {REG_EVENT_WORD} {REG_EVENT_WORD} {REG_TARGET_NWID} {REG_TARGET_NWID} {0b1000}")
        tran.writeAction(f"send_wret {REG_EVENT_WORD} {cont_label} {LM_BASE} 3 {reg3} {reg4}") # now $len is in words
        tran.writeAction(f"yield")
    
    # the user or runtime must provide the configs first prior to calling this function 
    def init_udshmem_configs_regs(self, tran, reg_nnodes, reg_nstacks, reg_nuds, reg_nlanes, reg_gmap_mem_base, reg_map_mem_base, reg_node_block_size, reg0, reg1):
        LM_BASE = reg0
        LM_PTR = reg1
        tran.writeAction(f'addi X7 {LM_BASE} {self.lm_base}')
        tran.writeAction(f"movwrl {reg_nnodes} {LM_BASE}({LM_PTR},1,0)")
        tran.writeAction(f"movwrl {reg_nstacks} {LM_BASE}({LM_PTR},1,0)")
        tran.writeAction(f"movwrl {reg_nuds} {LM_BASE}({LM_PTR},1,0)")
        tran.writeAction(f"movwrl {reg_nlanes} {LM_BASE}({LM_PTR},1,0)")
        tran.writeAction(f"movwrl {reg_gmap_mem_base} {LM_BASE}({LM_PTR},1,0)")
        tran.writeAction(f"movwrl {reg_map_mem_base} {LM_BASE}({LM_PTR},1,0)")
        tran.writeAction(f"movwrl {reg_node_block_size} {LM_BASE}({LM_PTR},1,0)")
        tran.writeAction(f"yield")
   
   
    def call_udshmem_ubench(self, tran, reg0, reg1, reg2, reg3, cont_label=1, reg_target_nwid="NWID"):
        LM_BASE = reg0
        EVW = reg1
        self.__debug_log(tran, f"print '[NWID=%ld]==================UDSHMEM SUBENCH BEGIN=================' NWID") # new line
        # this is thread 0, where the user calls
        if self.impl == 'subench-read':
            tran.writeAction(f"evii {EVW} {self.event_map['udshmem-subench-read']} 255 {0b0101}")
        elif self.impl == 'subench-write':
            tran.writeAction(f"evii {EVW} {self.event_map['udshmem-subench-write']} 255 {0b0101}")
        elif self.impl == 'subench-naive':
            tran.writeAction(f"evii {EVW} {self.event_map['udshmem-subench-naive']} 255 {0b0101}")
        elif self.impl == 'subench-message':
            tran.writeAction(f"evii {EVW} {self.event_map['udshmem-subench-message']} 255 {0b0101}")
        else:
            print('Unknown implementation type!')
            exit(1)
        tran.writeAction(f"ev {EVW} {EVW} {reg_target_nwid} {reg_target_nwid} {0b1000}")
        tran.writeAction(f"sendops_wret {EVW} {cont_label} X8 8 {reg2} {reg3}") # now $len is in words
        tran.writeAction(f"yield")


    def __init_udshmem_configs(self):
        LM_BASE = "X30"
        LM_PTR = "X31"
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.event_map['udshmem-init-configs'])
        tran.writeAction(f"addi X7 {LM_BASE} {self.lm_base}")
        for i in range(self.nconfigs):
            tran.writeAction(f"movwrl X{8+i} {LM_BASE}({LM_PTR},1,0)")
        tran.writeAction(f"yield")


    def __udshmem_get(self):
        LMBASE = "X31"
        LMPTR = "X30"
        SRC_OB = "X8"
        DST_OB = "X9"
        NELE_OB = "X10"
        OP = "X16"
        EVW = "X17"
        
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.event_map['udshmem-shmem-get'])
        self.__debug_log(tran, f"print '==================UDSHMEM BEGIN================='") # new line        
        self.__debug_log(tran, f"print 'USER: Calling Event UDShmem_get at NWID=%ld' NWID")
        self.__perf_log(tran, f"perflog 1 {perflog_map['start']} 'UDSHMEM Begins!'")
        tran.writeAction(f"movir {OP} {self.OPCODE_SHMEM_GET}")
        tran.writeAction(f'addi X7 {LMBASE} {self.lm_base + self.config_offset + self.flag_offset}')
        tran.writeAction(f'mov_imm2reg {LMPTR} 0')
        tran.writeAction(f"movwrl {SRC_OB} {LMBASE}({LMPTR},1,0)")
        tran.writeAction(f"movwrl {DST_OB} {LMBASE}({LMPTR},1,0)")
        tran.writeAction(f"movwrl {NELE_OB} {LMBASE}({LMPTR},1,0)")
        tran.writeAction(f"movwrl {OP} {LMBASE}({LMPTR},1,0)")
        if self.impl.startswith('basim'):
            tran.writeAction(f"evii {EVW} {self.event_map['udshmem-init']} 255 {0b0101}")
        else:
             tran.writeAction(f"evii {EVW} {self.event_map['udshmem-intelli-init']} 255 {0b0101}")
        tran.writeAction(f"ev {EVW} {EVW} NWID NWID {0b1000}")
        if self.test:
            tran.writeAction(f"sendops_wcont {EVW} X1 X8 8") # now $len is in words, the X1 contw is current cont word, this will directly send event back to user
        else:
            tran.writeAction(f"send_wcont {EVW} X1 {LMBASE} 4") # now $len is in words, the X1 contw is current cont word, this will directly send event back to user
        tran.writeAction(f"yield")
        

    def __udshmem_iget(self):
        LMBASE = "X31"
        LMPTR = "X30"
        SRC_OB = "X8"
        DST_OB = "X9"
        NELE_OB = "X10"
        OP = "X16"
        EVW = "X17"
        
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.event_map['udshmem-shmem-iget'])
        self.__debug_log(tran, f"print '==================UDSHMEM BEGIN================='") # new line        
        self.__debug_log(tran, f"print 'USER: Calling UDShmem_get at NWID=%ld' NWID")
        tran.writeAction(f"movir {OP} {self.OPCODE_SHMEM_IGET}")
        tran.writeAction(f'addi X7 {LMBASE} {self.lm_base + self.config_offset + self.flag_offset}')
        tran.writeAction(f'mov_imm2reg {LMPTR} 0')
        tran.writeAction(f"movwrl {SRC_OB} {LMBASE}({LMPTR},1,0)")
        tran.writeAction(f"movwrl {DST_OB} {LMBASE}({LMPTR},1,0)")
        tran.writeAction(f"movwrl {NELE_OB} {LMBASE}({LMPTR},1,0)")
        tran.writeAction(f"movwrl {OP} {LMBASE}({LMPTR},1,0)")
        tran.writeAction(f"evii {EVW} {self.event_map['udshmem-init']} 255 {0b0101}")
        tran.writeAction(f"ev {EVW} {EVW} NWID NWID {0b1000}")
        tran.writeAction(f"send_wcont {EVW} X1 {LMBASE} 4") # now $len is in words, the X1 contw is current cont word, this will directly send event back to user
        tran.writeAction(f"yield")
       

    def __debug_log(self, tran, msg, isEFA=False, block_id=None, level=0):
        
        if self.debug:
            if isEFA:
                tran.appendBlockAction(block_id, msg)
            elif self.debug >= level:
                tran.writeAction(msg)
    
    def __perf_log(self, tran, msg):
        if self.perflog:
            tran.writeAction(msg)
    
    def __generate_efa(self):
        if self.impl.startswith("subench"):
            self.__ev_subench()
            return
            
        # Register Work distribute events
        self.event_map.add_event('udshmem-shmem-get')
        
        # Register Shmem data movement loop events, varies due to user's configuration
        # for C in default_chunks:
        #     self.event_map.add_event(f"udshmem-ack-{C}")
 
        # if self.impl == 'basim' or self.impl == 'basim-intelli':
        #     for C in self.allowed_chunk_sizes:
        #         self.event_map.add_event(f"udshmem-load-store-loop-{C}")
        # elif self.impl == "ubench-write" or self.impl == "ubench-read":
        #     pass
        # else:
        #     print('Unknown implementation type!')
        #     exit(1)      
        # print(self.event_map)
        # generate state transitions (events)   
        self.event_map.add_event('udshmem-init')
        self.__udshmem_get() 
        # self.__udshmem_iget()
        
        if self.impl.startswith('basim'):
            self.__initial_udshmem()
        else:
            print('Unknown implementation type!')
            exit(1)

                                
    def __NEXT_CHUNK(self, C):
        if C == 1:
            return 1
        else:
            return C >> 1  
    
    # floor division macro
    def __floor_div(self, tranx, t, x, y):
        tranx.writeAction(f"div {x} {y} {t}")
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


    def __initial_udshmem(self):
        # init is above
        self.event_map.add_event('udshmem-notify-master-completed')
        self.event_map.add_event('udshmem-start-master-thread')
        self.event_map.add_event('udshmem-cont-master-thread')
        
        self.event_map.add_event('udshmem-notify-ud-complete')
        self.event_map.add_event('udshmem-start-ud-master-threads')
        self.event_map.add_event('udshmem-start-worker-thread')
        self.event_map.add_event('udshmem-notify-worker-complete') 
        for C in self.allowed_chunk_sizes:
            self.event_map.add_event(f"udshmem-load-store-loop-{C}")
        for C in self.default_chunk_sizes:
            self.event_map.add_event(f"udshmem-ack-{C}")
            
        for C in self.allowed_chunk_sizes:
                self.__initial_ev_load_store_loop(C, self.ele_size)
            # print(default_chunks)
        for C in self.default_chunk_sizes:
                self.__initial_ev_ack(C)
        
        self.__initial_udshmem_init()
        self.__initial_notify_ud_complete()
        self.__initial_notify_master_completed()
        self.__initial_start_master_thread()
        self.__initial_start_ud_master_thread()
        self.__initial_notify_worker_complete()
        self.__initial_start_worker_thread()
        
        
    def __initial_udshmem_init(self):
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
        OPCODE_OB = "X11"
        NUDS_OB = "X12"
        NLANES_OB = "X13"
        NWORKERS_OB = "X14"
        START_UDID_OB = "X15"
        
        # old implementation
        ELE_SIZE = "X16"
        MAX_OUTGOING_READ = "X16"
        OPCODE = "X16"
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
        

        
        # nworkers = 64 # 2048
        # nstacks = 1
        # nuds = 1 * nstacks
        # nlanes = nuds * 64
        # start_udid = 0
      
        LM_BASE = "X30"
        LM_PTR = "X31"
        
        
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.event_map['udshmem-init'])
        self.__debug_log(tran, f"print 'LIB-ROOT: Initial UDShmem init at NWID=%ld' NWID")
        if self.test:
            self.__debug_log(tran, level=2, msg=f"print 'Incoming OBs: src=%p, dst=%p, nele=%ld, nuds=%ld, nlanes=%ld, nworkers=%ld, start_udid=%ld' {SRC_OB} {DST_OB} {NELE_OB} {NUDS_OB} {NLANES_OB} {NWORKERS_OB} {START_UDID_OB}")
        tran.writeAction(f'addi X7 {LM_BASE} {self.lm_base + self.config_offset + self.flag_offset}')
        tran.writeAction(f'movir {LM_PTR} 0')
        # self.__debug_log(tran, f"print 'src_ob: %ld' {SRC_OB}")
        # self.__debug_log(tran, f"print 'dst_ob: %ld' {DST_OB}")
        # self.__debug_log(tran, f"print 'nele_ob: %ld' {NELE_OB}")
        # assign values to OBs
        tran.writeAction(f"mov_reg2reg {OPCODE_OB} {OPCODE}")
        tran.writeAction(f"mov_reg2reg {SRC_OB} {SRC}")
        tran.writeAction(f"mov_reg2reg {DST_OB} {DST}")
        tran.writeAction(f"mov_reg2reg {NELE_OB} {NELE}") 
        # assign values to them
        
        if self.test:
            tran.writeAction(f"addi {NUDS_OB} {NUDS} 0")
            tran.writeAction(f"addi {NLANES_OB} {NLANES} 0")
            tran.writeAction(f"addi {NWORKERS_OB} {NWORKERS} 0")
            tran.writeAction(f"addi {START_UDID_OB} {START_UDID} 0")
        else:
            tran.writeAction(f"movir {NWORKERS} {nworkers}")
            tran.writeAction(f"movir {NLANES} {nlanes}")
            tran.writeAction(f"movir {NUDS} {nuds}")
            tran.writeAction(f"movir {START_UDID} {start_udid}")
            
        # tran.writeAction(f"movir {START_UDID} {start_udid}")
        
        self.__debug_log(tran, f"print 'LIB-ROOT: src=%p, dst=%p, nele=%ld, nuds=%ld, nlanes=%ld, nworkers=%ld, start_udid=%ld' {SRC} {DST} {NELE} {NUDS} {NLANES} {NWORKERS} {START_UDID}")
        tran.writeAction(f"movir {START_NWID} {start_udid << 6}")
        for o in range(NUM_PARAMS):
            tran.writeAction(f"movwrl X{16+o} {LM_BASE}({LM_PTR},1,0)")

        tran.writeAction(f"evii {EVENT_WORD} {self.event_map['udshmem-start-master-thread']} 255 {0b0101}")
        tran.writeAction(f"ev {EVENT_WORD} {EVENT_WORD} {START_NWID} {START_NWID} {0b1000}")
        tran.writeAction(f"send_wret {EVENT_WORD} {self.event_map['udshmem-notify-master-completed']} {LM_BASE} 8 {TEMP0} {TEMP1}") # now $len is in words
        
        tran.writeAction(f"yield")
        
        self.trans.append(tran)
        
        
    def __initial_notify_master_completed(self):
        TEMP = "X28"
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.event_map['udshmem-notify-master-completed'])
        self.__debug_log(tran, f"print 'LIB-ROOT: Notify master completed at NWID=%ld' NWID")   
        # global termination routine (barrier)
        tran.writeAction(f"movir X29 1")
        tran.writeAction(f"movir X28 0")
        tran.writeAction(f"addi X7 X30 {self.lm_base + self.config_offset}")
        # tran.writeAction(f"move X29 0(X30) 0 8")
        tran.writeAction(f"movwrl X29 X30(X28,0,0)")
        self.__debug_log(tran, f"print 'LIB-ROOT: Master thread completed! Shmem terminated! Write Flag(1) to %ld' X30")
        self.__perf_log(tran, f"perflog 1 {perflog_map['end-all']} 'UDSHMEM Completed!'")
        self.__debug_log(tran, f"print '===================UDSHMEM ENDS================='") # new line
        # TODO: are there any values we want to send back?
        tran.writeAction(f"sendr_reply X31 X30 {TEMP}")
        tran.writeAction(f"yield_terminate")
        
        
    def __initial_start_master_thread(self):
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
        OPCODE = "X16"
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
        self.__debug_log(tran_smt, "print 'UDSHMEM-Master: Start master thread'")
        # self.__perf_log(tran_smt, f"perflog 1 0 'master thread start, NWID=%ld' NWID")

        # save a copy of the arguments to LM
        tran_smt.writeAction(f'addi X7 {LM_BASE} {self.lm_base + self.config_offset + self.flag_offset}')
        tran_smt.writeAction(f'mov_imm2reg {LM_PTR} 0')
        for o in range(NUM_PARAMS):
            tran_smt.writeAction(f"mov_reg2reg X{8+o} X{16+o}")
            tran_smt.writeAction(f"movwrl X{16+o} {LM_BASE}({LM_PTR},1,0)")
    
        
        # reset the LM_BASE and LM_PTR
        tran_smt.writeAction(f"mov_imm2reg {LM_PTR} 0")
        # start lane master threads
        tran_smt.writeAction(f"mov_reg2reg {START_UDID} {TARGET_UDID}")
        tran_smt.writeAction(f"add {START_UDID} {NUDS} {END_UDID}")
        tran_smt.writeAction(f"start-loop: ble {END_UDID} {TARGET_UDID} done") # if end_udid <= start_udid, terminate
        tran_smt.writeAction(f"lshift {TARGET_UDID} {TARGET_L0ID} 6") # target_udid = target_l0idx << 6 = target_l0idx * 64

        tran_smt.writeAction(f"evii {EVENT_WORD} {self.event_map['udshmem-start-ud-master-threads']} 255 {0b0101}")
        tran_smt.writeAction(f"ev {EVENT_WORD} {EVENT_WORD} {TARGET_L0ID} {TARGET_L0ID} {0b1000}")
        tran_smt.writeAction(f"send_wret {EVENT_WORD} {self.event_map['udshmem-notify-ud-complete']} {LM_BASE} 8 {TEMP0} {TEMP1}") # now $len is in words

        tran_smt.writeAction(f"addi {TARGET_UDID} {TARGET_UDID} 1")
        tran_smt.writeAction(f"jmp start-loop")
        tran_smt.writeAction(f"done: mov_imm2reg {COMPLETED_UDS} 0")
        tran_smt.writeAction(f"yield")

        self.trans.append(tran_smt)


    def __initial_notify_ud_complete(self):
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
        # self.__debug_log(tran_udc, f"print 'NUDS: %ld, COMPLETED_UDS: %ld' {NUDS} {COMPLETED_UDS}")
        tran_udc.writeAction(f"ble {NUDS} {COMPLETED_UDS} terminate")    # if nuds <= compeleted uds, terminate
        tran_udc.writeAction(f"yield")
        tran_udc.writeAction(f"terminate: sendr_reply {NUDS} {COMPLETED_UDS} {TEMP}") # isav2.3
        self.__debug_log(tran_udc, f"print 'UDSHMEM-Master: All UDs completed!'")
        tran_udc.writeAction(f"yield_terminate")
        self.trans.append(tran_udc)  

    
    def __initial_start_ud_master_thread(self):
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
        OPCODE = "X16"
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
        self.__debug_log(tran_lmt, f"print 'UDSHMEM-UD-Master: Start ud master thread at NWID=%ld' NWID")
        self.__perf_log(tran_lmt, f"perflog 1 1 'start ud master thread at NWID=%ld' NWID")
        tran_lmt.writeAction(f'addi X7 {LM_BASE} {self.lm_base + self.config_offset + self.flag_offset}')
        tran_lmt.writeAction(f"mov_imm2reg {LM_PTR} 0")
        # TODO: optimize fewer instructions without loading unused arguments
        for o in range(NUM_PARAMS):
            tran_lmt.writeAction(f"mov_reg2reg X{8+o} X{16+o}")
            tran_lmt.writeAction(f"movwrl X{16+o} {LM_BASE}({LM_PTR},1,0)")

        self.__debug_log(tran_lmt, f"print 'UDSHMEM-UD-Master: Incoming operands: opcode=%ld, src=%ld, dst=%ld, nele=%ld, nworkers=%ld, nlanes=%ld, nuds=%ld'{OPCODE} {SRC} {DST} {NELE} {NWORKERS} {NLANES} {NUDS}")
        UDID = "X16"
        L0ID = "X17"
        UD_LANES = "X18"
        R_UDID = "X19" # relative UDID

        # UDID = NWID >> 6, L0ID = NWID << 6
        tran_lmt.writeAction(f"rshift NWID {UDID} 6") # udid = nwid >> 6 = nwid // 64
        tran_lmt.writeAction(f"lshift {UDID} {L0ID} 6") # L0ID = udid << 6 = udid * 64
        # R_UDID = UDID - START_UDID
        tran_lmt.writeAction(f"sub {UDID} {START_UDID} {R_UDID}")
        # self.__debug_log(tran_lmt, f"print 'start UD master. UDID: %ld, L0ID: %ld, R_UDID: %ld' {UDID} {L0ID} {R_UDID}")

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
        tran_lmt.writeAction(f"mod {NLANES} {NUDS} {UD_LANES_RM}")
        # UD_LANES = (UDID < UD_LANES_RM ? 1 : 0) + UD_LANES_FD
        tran_lmt.writeAction(f"mov_imm2reg {UD_LANES} 0")
        self.__ternary(tran_lmt, t=UD_LANES, cond=f'bgt {UD_LANES_RM} {R_UDID}', ifTrue=1, ifFalse=0, endLabel='ud-lanes-cont')
        tran_lmt.writeAction(f"ud-lanes-cont: add {UD_LANES} {UD_LANES_FD} {UD_LANES}")
        
        # make sure UD_LANES <= 64; can be optimized 
        tran_lmt.writeAction(f"movir {TEMP0} 64")
        tran_lmt.writeAction(f"ble {UD_LANES} {TEMP0} skip-max-lane") # if ud_lanes <= 64, terminate

        tran_lmt.writeAction(f"mov_imm2reg {UD_LANES} 64")
        tran_lmt.writeAction(f"skip-max-lane: addi {UD_LANES} {UD_LANES} 0") # nop
        # recyle X23, X24, X25, X26

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
        tran_lmt.writeAction(f"mod {NWORKERS} {NUDS} {UD_WORKERS_RM}")
    
        # if UD_WORKERS_RM != 0 or UD_WORKERS_FD != 0: give proper workers
        # UD_WORKERS = UDID < NWORKERS ? 1 : 0

        # UD_WORKERS = (UDID < UD_WORKERS_RM ? 1 : 0) + UD_WORKERS_FD
        tran_lmt.writeAction(f"mov_imm2reg {UD_WORKERS} 0")
 
        self.__ternary(tran_lmt, t=UD_WORKERS, cond=f'bgt {UD_WORKERS_RM} {R_UDID}', ifTrue=1, ifFalse=0, endLabel='ud-workers-cont')
        # self.__debug_log(tran_lmt, f"print 'ud_workers: %ld, ud_workers_fd: %ld, ud_workers_rm: %ld, udid: %ld' {UD_WORKERS} {UD_WORKERS_FD} {UD_WORKERS_RM} {R_UDID}")
        tran_lmt.writeAction(f"ud-workers-cont: add {UD_WORKERS} {UD_WORKERS_FD} {UD_WORKERS}")
        tran_lmt.writeAction(f"blec {UD_WORKERS} 0 lmt_terminate") # if ud_workers <= 0, terminate
        # X25, X26 still useable, recycle X27, X28
        # WIDX_INIT = (NWORKERS // NUDS) * UDID + (UDID < NWORKERS % NUDS ? UDID : NWORKERS % NUDS)
        WIDX_INIT0 = "X27"
        WIDX_INIT1 = "X28"
        WIDX = WIDX_INIT
        # WIDX_INT0 = (NWORKERS // NUDS) * UDID      
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
        LMBASE, LMPTR = "X28", "X29"
        MAX_NWID = "X30"
        L_WORKERS = "X31"
        COUNTER = "X19"
        # force recycle X20, X21, X22
        EVENT_WORD = "X20"
        COMPLETED_WORKERS = "X21"
        LMBASE="X21"
        LMPTR="X23"
        RELATIVE_NWID = "X22"
        

        self.__floor_div(tran_lmt, L_WORKERS_FD, UD_WORKERS, UD_LANES)
        # L_WORKERS_RM = UD_WORKERS % UD_LANES
        tran_lmt.writeAction(f"mod {UD_WORKERS} {UD_LANES} {L_WORKERS_RM}")

        self.__debug_log(tran_lmt, f"print 'UDSHMEM-UD-Master: UDID: %ld, UD master distributing worker threads.' {UDID}")
        self.__perf_log(tran_lmt, f"perflog 1 2 'UDID: %ld, Ud master distributing worker threads.' {UDID}")
# 
        # tran_lmt.writeAction(f"addi X7 {LMBASE} {self.lm_base + self.config_offset + self.flag_offset + 1024}")
        # tran_lmt.writeAction(f"movir {LMPTR} 0")
        tran_lmt.writeAction(f"mov_reg2reg {L0ID} {T_NWID}") # T_NWID = L0ID
        tran_lmt.writeAction(f"iter-lanes: add {L0ID} {UD_LANES} {MAX_NWID}") # MAX_NWID = L0ID + UD_LANES
        tran_lmt.writeAction(f"ble {MAX_NWID} {T_NWID} iter-lanes-end") # if MAX_NWID <= T_NWID, goto iter-lanes-end
        tran_lmt.writeAction(f"mov_imm2reg {L_WORKERS} 0")  # L_WORKERS = 0
        tran_lmt.writeAction(f"sub {T_NWID} {L0ID} {RELATIVE_NWID}") # RELATIVE_NWID = T_NWID - L0ID
        self.__ternary(tran_lmt, t=L_WORKERS, cond=f'bgt {L_WORKERS_RM} {RELATIVE_NWID}', ifTrue=1, ifFalse=0, endLabel='l-workers-cont') # L_WORKERS = (T_NWID < L_WORKERS_RM ? 1 : 0)
   
        tran_lmt.writeAction(f"l-workers-cont: add {L_WORKERS} {L_WORKERS_FD} {L_WORKERS}") # L_WORKERS = L_WORKERS_FD + L_WORKERS
        tran_lmt.writeAction(f"mov_imm2reg {COUNTER} 0") # COUNTER = 0
        tran_lmt.writeAction(f"iter-lane-workers: ble {L_WORKERS} {COUNTER} iter-next-lane")

        # start worker
        tran_lmt.writeAction(f"evii {EVENT_WORD} {self.event_map['udshmem-start-worker-thread']} 255 {0b0101}")
        tran_lmt.writeAction(f"ev {EVENT_WORD} {EVENT_WORD} {T_NWID} {T_NWID} {0b1000}")
        # tran_lmt.writeAction(f"movwrl {WIDX} {LMBASE}({LMPTR},0,0)")
        tran_lmt.writeAction(f"sendr3_wret {EVENT_WORD} {self.event_map['udshmem-notify-worker-complete']} {WIDX} {UD_WORKERS} {UD_WORKERS} {TEMP0} {TEMP1}") 
        # tran_lmt.writeAction(f"sendr3_wret {EVENT_WORD} {self.event_map['udshmem-notify-worker-complete']} {LMBASE} 8 {TEMP0} {TEMP1}") # last one is bogus
        # self.__debug_log(tran_lmt, f"print 'L_WORKERS_FD: %ld, L_WORKERS_RM: %ld, T_NWID: %ld, MAX_NWID: %ld, L_WORKERS: %ld, COUNTER: %ld, UD_LANES: %ld, WIDX: %ld' {L_WORKERS_FD} {L_WORKERS_RM} {T_NWID} {MAX_NWID} {L_WORKERS} {COUNTER} {UD_LANES} {WIDX}")
        tran_lmt.writeAction(f"addi {WIDX} {WIDX} 1") # WIDX++
        tran_lmt.writeAction(f"addi {COUNTER} {COUNTER} 1") # COUNTER++
        tran_lmt.writeAction(f"jmp iter-lane-workers") # goto iter-lane-workers
        tran_lmt.writeAction(f"iter-next-lane: addi {T_NWID} {T_NWID} 1") # T_NWID++
        tran_lmt.writeAction(f"jmp iter-lanes") # goto iter-lanes
        tran_lmt.writeAction(f"iter-lanes-end: mov_imm2reg {COMPLETED_WORKERS} 0")
 
        tran_lmt.writeAction(f"yield")
        tran_lmt.writeAction(f"lmt_terminate: sendr_reply {UDID} {UD_WORKERS} {TEMP0}") # isav2.3      
        self.__debug_log(tran_lmt, f"print 'UDSHMEM-UD-Master: No UD workers for this UD, UDID:%ld, UD_WORKERS:%ld' {UDID} {UD_WORKERS}")
        self.__perf_log(tran_lmt, f"perflog 1 8 'No UD workers for this UD, UDID:%ld, UD_WORKERS:%ld' {UDID} {UD_WORKERS}")

        tran_lmt.writeAction(f"yield_terminate")
        self.trans.append(tran_lmt)
    
      
    def __initial_notify_worker_complete(self):
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
        tran_wc.writeAction(f"addi {COMPLETED_WORKERS} {COMPLETED_WORKERS} 1")
        tran_wc.writeAction(f"ble {UD_WORKERS} {COMPLETED_WORKERS} wc_terminate")    # nworkers >= compeleted workers
        tran_wc.writeAction(f"yield")
        tran_wc.writeAction(f"wc_terminate: sendr_reply {UDID} {UD_WORKERS} {TEMP0}") # isav2.3

        self.__debug_log(tran_wc, f"print 'UDSHMEM-UD-Master: All UD workers done, UDID:%ld, UD_WORKERS:%ld' {UDID} {UD_WORKERS}")
        self.__perf_log(tran_wc, f"perflog 1 6 'All UD workers done, UDID:%ld, UD_WORKERS:%ld' {UDID} {UD_WORKERS}")

        tran_wc.writeAction("yield_terminate")
        self.trans.append(tran_wc)       
       
       
    def __initial_start_worker_thread(self):
        '''

        '''
        # load from LM
        ELE_SIZE = "X16"
        OPCODE = "X16"
        BLOCKSIZE= "X17"
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
        self.__debug_log(tran0, level=2, msg= f"print 'WORKER: start worker thread at NWID=%ld' NWID")
        tran0.writeAction(f"addi X7 X31 {self.lm_base + self.config_offset + self.flag_offset}")
        tran0.writeAction("mov_imm2reg X30 0")
        for o in range(5):
            tran0.writeAction(f"movwlr X31(X30,1,0) X{16+o}")
        self.__debug_log(tran0, level=3, msg=f"print 'WORKER: Incoming operands: opcode=%ld, src=%ld, dst=%ld, nele=%ld, nworkers=%ld' {OPCODE} {SRC} {DST} {NELE} {NWORKERS}")
       
        tran0.writeAction(f"mov_reg2reg X8 {WIDX}")
        self.__perf_log(tran0, f"perflog 1 3 'start-worker-thread=%ld' {WIDX}")
        
       

        # W_NELE = NELE // NWORKERS
        self.__floor_div(tran0, W_NELE_FD, NELE, NWORKERS)

        # W_NELE_RM = NELE % NWORKERS
        tran0.writeAction(f"mod {NELE} {NWORKERS} {W_NELE_RM}")
        tran0.writeAction(f"mov_imm2reg {W_NELE} 0")
        self.__ternary(tran0, W_NELE, f'bgt {W_NELE_RM} {WIDX}', 1, 0, endLabel='t-cont')
        tran0.writeAction(f"t-cont: add {W_NELE} {W_NELE_FD} {W_NELE}")
        # LDPTR = SRC + W_NELE * WIDX + (WIDX < W_NELE_RM ? WIDX : W_NELE_RM)
        # INIT_OFFSETS = (WIDX < W_NELE_RM ? WIDX : W_NELE_RM)
        tran0.writeAction(f"mov_imm2reg {INIT_OFFSETS} 0")
        self.__ternary(tran0, INIT_OFFSETS, f"bgt {W_NELE_RM} {WIDX}", WIDX, W_NELE_RM, endLabel='ldptr0-cont')
        # INIT_OFFSETS += W_NELE * WIDX
        # TEMP = W_NELE_FD * WIDX     
        tran0.writeAction(f"ldptr0-cont: mul {W_NELE_FD} {WIDX} {TEMP}")
        # INIT_OFFSETS = INIT_OFFSETS + TEMP
        tran0.writeAction(f"add {INIT_OFFSETS} {TEMP} {INIT_OFFSETS}")
        # self.__debug_log(tran0, f"print 'WIDX: %ld, W_NELE: %ld, W_NELE_FD: %ld, W_NELE_RM: %ld, INIT_OFFSETS: %ld, TEMP: %ld' {WIDX} {W_NELE} {W_NELE_FD} {W_NELE_RM} {INIT_OFFSETS} {TEMP}")

        # NLEFT_LD = W_NELE
        tran0.writeAction(f"mov_reg2reg {W_NELE} {NLEFT_LD}")
        # NLEFT_ST = W_NELE
        tran0.writeAction(f"mov_reg2reg {W_NELE} {NLEFT_ST}")
        # prepare to start the loop
        W_NELE = "X22"
        LDPTR = "X23"
        STPTR = "X24"
        NLEFT_LD = "X25"
        NLEFT_STR = "X29"
        
        DST_SRC_DIFF = "X28"
        SRC_ALIGNED = "X29"
        NLEFT_LD_ALIGNED = "X30"
        LDPTR_END = "X30"
        EV_WORD = "X31"
        TEMP0, TEMP1 = "X30", "X31"
        OUTGOING_READ = "X17"
        # MAX_OUTGOING_READ = "X16" 
        
        tran0.writeAction(f"lshift {INIT_OFFSETS} {INIT_OFFSETS} {3 + self.ele_shift}")
        tran0.writeAction(f"add {SRC} {INIT_OFFSETS} {LDPTR}")
        tran0.writeAction(f"add {DST} {INIT_OFFSETS} {STPTR}")
        tran0.writeAction(f"mov_reg2reg {W_NELE} {NLEFT_STR}")
        tran0.writeAction(f"sub {DST} {SRC} {DST_SRC_DIFF}")
        
        self.__debug_log(tran0, level=2, msg= f"print 'WORKER[WIDX=%ld, NWID=%ld]: worker_nele(W_NELE): %ld, INIT_OFFSET=%ld, src=%ld, dst=%ld'{WIDX} NWID {W_NELE} {INIT_OFFSETS} {LDPTR} {STPTR}")
        
        if self.impl == 'basim' or self.impl == 'basim-unleashed' or self.impl == "basim-send-all":
            tran0.writeAction(f"mov_imm2reg {OUTGOING_READ} 0") 
            tran0.writeAction(f"lshift {W_NELE} {LDPTR_END} {3 + self.ele_shift}")
            tran0.writeAction(f"add {LDPTR} {LDPTR_END} {LDPTR_END}")
            tran0.writeAction(f"beqi {OPCODE} {self.OPCODE_SHMEM_IGET} udshmem-iget")
            self.__initial_load_first(tran0, max(self.allowed_chunk_sizes), self.ele_size, label="udshmem-get")
            self.__iget_load_first(tran0, max(self.allowed_chunk_sizes), self.ele_size, label="udshmem-iget")
            self.__initial_terminate(tran0)
        elif self.impl == 'basim-ubench-write':
            tran0.writeAction(f"blei {NLEFT_LD} 0 ubench-write-terminate")
            tran0.writeAction(f"jmp ubench-write-loop-8")
            self.__ubenchmarks(tran0, isRead=False)
            self.__initial_terminate(tran0, tlabel="ubench-write-terminate")
        elif self.impl == 'basim-ubench-read':
            tran0.writeAction(f"blei {NLEFT_LD} 0 ubench-read-terminate")
            tran0.writeAction(f"jmp ubench-read-loop-8")
            self.__ubenchmarks(tran0, isRead=True)
            self.__initial_terminate(tran0, tlabel="ubench-read-terminate")
        else:
            print(f"Error: unknown impl {self.impl}")
            exit(1)
    
    
    def __start_iget_worker_thread(self):
        '''

        '''
        # load from LM
        ELE_SIZE = "X16"
        OPCODE = "X16"
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

        tran0 = self.state.writeTransition("eventCarry", self.state, self.state, self.event_map['udshmem-start-iget-worker-thread'])
        
       
        # tran0.writeAction(f"mov_imm2reg X31 {self.lm_base + self.flag_offset}")
        # self.__debug_log(tran0, f"print 'start worker thread at NWID=%ld' NWID")
        tran0.writeAction(f"addi X7 X31 {self.lm_base + self.config_offset + self.flag_offset}")
        tran0.writeAction("mov_imm2reg X30 0")
        for o in range(5):
            tran0.writeAction(f"movwlr X31(X30,1,0) X{16+o}")
       
        tran0.writeAction(f"mov_reg2reg X8 {WIDX}")
        self.__perf_log(tran0, f"perflog 1 3 'start-worker-thread=%ld' {WIDX}")
        
       

        # W_NELE = NELE // NWORKERS
        self.__floor_div(tran0, W_NELE_FD, NELE, NWORKERS)

        # W_NELE_RM = NELE % NWORKERS
        tran0.writeAction(f"mod {NELE} {NWORKERS} {W_NELE_RM}")
        tran0.writeAction(f"mov_imm2reg {W_NELE} 0")
        self.__ternary(tran0, W_NELE, f'bgt {W_NELE_RM} {WIDX}', 1, 0, endLabel='t-cont')
        tran0.writeAction(f"t-cont: add {W_NELE} {W_NELE_FD} {W_NELE}")
        # LDPTR = SRC + W_NELE * WIDX + (WIDX < W_NELE_RM ? WIDX : W_NELE_RM)
        # INIT_OFFSETS = (WIDX < W_NELE_RM ? WIDX : W_NELE_RM)
        tran0.writeAction(f"mov_imm2reg {INIT_OFFSETS} 0")
        self.__ternary(tran0, INIT_OFFSETS, f"bgt {W_NELE_RM} {WIDX}", WIDX, W_NELE_RM, endLabel='ldptr0-cont')
        # INIT_OFFSETS += W_NELE * WIDX
        # TEMP = W_NELE_FD * WIDX     
        tran0.writeAction(f"ldptr0-cont: mul {W_NELE_FD} {WIDX} {TEMP}")
        # INIT_OFFSETS = INIT_OFFSETS + TEMP
        tran0.writeAction(f"add {INIT_OFFSETS} {TEMP} {INIT_OFFSETS}")
        # self.__debug_log(tran0, f"print 'WIDX: %ld, W_NELE: %ld, W_NELE_FD: %ld, W_NELE_RM: %ld, INIT_OFFSETS: %ld, TEMP: %ld' {WIDX} {W_NELE} {W_NELE_FD} {W_NELE_RM} {INIT_OFFSETS} {TEMP}")

        # NLEFT_LD = W_NELE
        tran0.writeAction(f"mov_reg2reg {W_NELE} {NLEFT_LD}")
        # NLEFT_ST = W_NELE
        tran0.writeAction(f"mov_reg2reg {W_NELE} {NLEFT_ST}")
        # prepare to start the loop
        W_NELE = "X22"
        LDPTR = "X23"
        STPTR = "X24"
        DST_SRC_DIFF = "X28"
        NLEFT_STR = "X29"
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
        if self.impl == 'basim': 
            # tran0.writeAction(f"mov_imm2reg {MAX_OUTGOING_READ} 32")
            tran0.writeAction(f"mov_imm2reg {OUTGOING_READ} 0") 
            tran0.writeAction(f"lshift {W_NELE} {LDPTR_END} {3 + self.ele_shift}")
            tran0.writeAction(f"add {LDPTR} {LDPTR_END} {LDPTR_END}")
            self.__load_first(tran0, max(self.allowed_chunk_sizes), self.ele_size)
        else:
            print(f"Error: unknown impl {self.impl}")
            exit(1)
        self.trans.append(tran0)
    
   
    def __initial_terminate(self, tran, tlabel="terminate"):
        WIDX = "X21"
        TEMP = "X30"
        
        # FIXIME: since assembler will ignore this, we need this bogus line to make sure the label can be reached
        tran.writeAction(f"{tlabel}: addi {WIDX} {WIDX} 0") 
        self.__perf_log(tran, f"perflog 1 5 'Worker Read/write ends, NWID=%ld, WIDX=%ld' NWID {WIDX}")
        tran.writeAction(f"sendr_reply NWID {WIDX} {TEMP}") #TODO: need to change according to spec
        tran.writeAction(f"yieldt")
    
    
    def __initial_load_first(self, tran, C, E, label="udshmem-get"):
        # C: chunk size; E: element size in word
        LDPTR = "X23"
        NLEFT_LD = "X25"
        BYTES_LEFT = "X27"
        WIDX = "X21"
        MAX_OUTGOING_READ = "X16"
        
        # self.__debug_log(tran, f"print 'basim: NWID=%ld, next_chunk_{C}_{E}' NWID")
        tran.writeAction(f"movir {MAX_OUTGOING_READ} 32")
        tran.writeAction(f"{label}: blec {NLEFT_LD} 0 terminate") # if no elems at the begining, terminate
        self.__initial_load_next(tran, C, E)
        tran.writeAction(f"yield")
        
            
    def __initial_load_next(self, tran, C, E):
        LDPTR = "X23"
        NLEFT_LD = "X25"
        WIDX = "X21"
        WORDS_LEFT = "X27"
        OUTGOING_READ = "X17"
        TEMP0, TEMP1 = "X30", "X31"
        tran.writeAction(f"next_chunk_{C}_{E}: blec {NLEFT_LD} 0 done")
        tran.writeAction(f"lshift {NLEFT_LD} {WORDS_LEFT} {self.ele_shift}")
        # self.__debug_log(tran, f"print 'WORDS_LEFT=%ld, C={C}, E={E}' {WORDS_LEFT}")
        tran.writeAction(f"blec {WORDS_LEFT} {C-1} next_chunk_{self.__NEXT_CHUNK(C)}_{E}")
        if self.impl == "basim-send-all":
            tran.writeAction(f"send_dmlm_ld_wret {LDPTR} {self.event_map[f'udshmem-load-store-loop-8']} 8 {TEMP0}")
            tran.writeAction(f"addi {LDPTR} {LDPTR} 64") # dram read/write still uses bytes
            
            tran.writeAction(f"subi {NLEFT_LD} {NLEFT_LD} {8}")
            # self.__debug_log(tran, level=3, msg=f"print 'next_event=udshmem-load-store-loop-{C}; NLEFT_LD=%ld; LDPTR=%ld' {NLEFT_LD} {LDPTR}")
            tran.writeAction(f"jmp next_chunk_{C}_{E}")
        else:
            if C <= 8:
                # self.__debug_log(tran, f"print 'next_event=udshmem-load-store-loop-{C}; NLEFT_LD=%ld; LDPTR=%ld' {NLEFT_LD} {LDPTR}")
                tran.writeAction(f"send_dmlm_ld_wret {LDPTR} {self.event_map[f'udshmem-load-store-loop-{C}']} {C} {TEMP0}")
                tran.writeAction(f"addi {LDPTR} {LDPTR} {C * 8}") # dram read/write still uses bytes
            else:
                for i in range(C // 8):
                    tran.writeAction(f"send_dmlm_ld_wret {LDPTR} {self.event_map[f'udshmem-load-store-loop-{C}']} 8 {TEMP0}")
                    tran.writeAction(f"addi {LDPTR} {LDPTR} 64") # dram read/write still uses bytes
            tran.writeAction(f"subi {NLEFT_LD} {NLEFT_LD} {C >> self.ele_shift}")
        if not (self.impl =='basim-unleashed' or self.impl == 'basim-send-all'):
            tran.writeAction(f"addi {OUTGOING_READ} {OUTGOING_READ} {C // 8 if C > 8 else 1}")
        # self.__debug_log(tran, f"print 'basim: NWID=%ld, outgoing_read=%ld' NWID {OUTGOING_READ}")
        tran.writeAction(f"yield")
        if C != 1:
            self.__initial_load_next(tran, self.__NEXT_CHUNK(C), E)
        else:
            tran.writeAction(f"done: yield")
    
    
    def __initial_ev_ack(self, C):
        WIDX = "X21"
        W_NELE = "X22"
        NLEFT_ST = "X26"
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.event_map[f'udshmem-ack-{C}'])
        tran.writeAction(f"subi {NLEFT_ST} {NLEFT_ST} {C >> self.ele_shift}")
        self.__debug_log(tran, level=4, msg= f"print 'ack: NWID=%ld, NLEFT_ST=%ld' NWID {NLEFT_ST}")
        tran.writeAction(f"blec {NLEFT_ST} 0 ack_terminate")
        tran.writeAction(f"yield")
        # label is in the termniate
        self.__initial_terminate(tran, "ack_terminate")
        
        
    def __initial_ev_load_store_loop(self, C, E):
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
        # self.__debug_log(tran, f"print 'read-returns {C} {E}'")
        # self.__debug_log(tran, level=3,msg=f"print 'read-returns %ld %ld %ld %ld %ld %ld %ld' X8 X9 X10 X11 X12 X13 X14")
        tran.writeAction(f"add {RETURN_ADDR_REG} {DST_SRC_DIFF} {STPTR}")
        self.__debug_log(tran=tran, level=3, msg=f"print 'load-store-loop-{C}: NWID=%ld, NLEFT_LD=%ld, NLEFT_ST=%ld, STPTR=%ld, DST_SRC_DIFF=%ld, RETURN_ADDR_REG=%ld' NWID {NLEFT_LD} {NLEFT_STR} {STPTR} {DST_SRC_DIFF} {RETURN_ADDR_REG}")
        # tran.writeAction(f"subi {NLEFT_STR} {NLEFT_STR} {chunk_size >> self.ele_shift}")
        if C > 8:
            tran.writeAction(f"sendops_dmlm_wret {STPTR} {self.event_map['udshmem-ack-8']} X8 8 {TEMP0}")
        else:
            tran.writeAction(f"sendops_dmlm_wret {STPTR} {self.event_map[f'udshmem-ack-{C}']} X8 {C} {TEMP0}")
        if not (self.impl == "basim-uleashed" or self.impl == "basim-send-all"):
            tran.writeAction(f"subi {OUTGOING_READ} {OUTGOING_READ} 1")
            tran.writeAction(f"bgt {OUTGOING_READ} {MAX_OUTGOING_READ} wait_next")
        tran.writeAction(f"blec {NLEFT_LD} 0 no_more_reads")
        self.__initial_load_next(tran, C, E)
        tran.writeAction(f"no_more_reads: yield")
        tran.writeAction(f"wait_next: yield")
    
    #================UDSHMEM_GET END===================
    #===============UDSHMEM_UBENCHMAKR BEGIN================
    
    def __ubenchmarks(self, tran, isRead):
        
        if isRead:
            for c in self.default_chunk_sizes:
                self.__ubench_read_loop(tran, c)
        else:
            for c in self.default_chunk_sizes:
                self.__ubench_write_loop(tran, c)
       
    def __ubench_read_loop(self, tran, C=8):
        W_NELE = "X22"
        LDPTR = "X23"
        NLEFT_LD = "X25"
        NLEFT_ST = "X26"
        BYTES_LEFT = "X27"
        WIDX = "X21"
        MAX_OUTGOING_READ = "X16"
        TEMP0, TEMP1 = "X30", "X31"
        self.__debug_log(tran, level=2,msg=f"print 'LIBSHMEM-UBENCH[NWID=%ld]: Executing Ubench-Read...' NWID")
        tran.writeAction(f"ubench-read-loop-{C}: blei {NLEFT_LD} 0 ubench-read-done-{C}")
        tran.writeAction(f"blti {NLEFT_LD} {C} ubench-read-loop-{self.__NEXT_CHUNK(C)}")
        if self.perflog:
            tran.writeAction(f"beq {W_NELE} {NLEFT_LD} ubench-read-first-{C}")
            tran.writeAction(f"jmp ubench-keep-reading-{C}")
            self.__perf_log(tran, f"ubench-read-first-{C}: perflog 1 {perflog_map['start-worker-read']} 'Worker Read starts, NWID=%ld, WIDX=%ld' NWID {WIDX}")
        tran.writeAction(f"ubench-keep-reading-{C}: send_dmlm_ld_wret {LDPTR} {self.event_map[f'udshmem-ack-{C}']} {C} {TEMP0}")
        tran.writeAction(f"addi {LDPTR} {LDPTR} {C * 8}") # dram read/write still uses bytes
        tran.writeAction(f"subi {NLEFT_LD} {NLEFT_LD} {C >> self.ele_shift}")
        tran.writeAction(f"jmp ubench-read-loop-{C}")
        if self.perflog:
            self.__perf_log(tran, f"ubench-read-done-{C}: perflog 1 {perflog_map['end-worker-read']} 'Worker Read ends, NWID=%ld, WIDX=%ld' NWID {WIDX}")
            tran.writeAction(f"yield")
        else:
            tran.writeAction(f"ubench-read-done-{C}: yield")
    
    def __ubench_write_loop(self, tran, C=8):
        W_NELE = "X22"
        LDPTR = "X23"
        STPTR = "X24"
        NLEFT_LD = "X25"
        NLEFT_STR = "X29"
        
        
        BYTES_LEFT = "X27"
        WIDX = "X21"
        MAX_OUTGOING_READ = "X16"
        
        TEMP0, TEMP1 = "X30", "X31"
        self.__debug_log(tran, level=4, msg=f"print 'WORKER[WIDX=%ld][NWID=%ld]:Ubench-Write, nelems=%ld, dst=%ld.' NWID {WIDX} {W_NELE} {STPTR}")
        # self.__debug_log(tran, f"print 'ubench-write-loop-{C}: NWID=%ld, NLEFT_LD=%ld' NWID {NLEFT_LD}")
        tran.writeAction(f"ubench-write-loop-{C}: blei {NLEFT_LD} 0 ubench-write-done-{C}")
        # self.__debug_log(tran, f"print 'checking-{C}: NWID=%ld, NLEFT_LD=%ld' NWID {NLEFT_LD}")
        tran.writeAction(f"blti {NLEFT_LD} {C} ubench-write-loop-{self.__NEXT_CHUNK(C)}")
        if self.perflog:
            tran.writeAction(f"beq {W_NELE} {NLEFT_LD} ubench-write-first-{C}")
            tran.writeAction(f"jmp ubench-keep-writing-{C}")
            tran.writeAction(f"ubench-write-first-{C}: perflog 1 {perflog_map['start-worker-write']} 'Worker Write starts, NWID=%ld, WIDX=%ld' NWID {WIDX}")
        tran.writeAction(f"ubench-keep-writing-{C}: send_dmlm_wret {STPTR} {self.event_map[f'udshmem-ack-{C}']} X7 {C} {TEMP0}")
        tran.writeAction(f"addi {STPTR} {STPTR} {C * 8}") # dram read/write still uses bytes
        # self.__debug_log(tran, f"print ' {C >> self.ele_shift} '")
        tran.writeAction(f"subi {NLEFT_LD} {NLEFT_LD} {C >> self.ele_shift}")
        tran.writeAction(f"jmp ubench-write-loop-{C}")
        if self.perflog:
            self.__perf_log(tran, f"ubench-write-done-{C}: perflog 1 {perflog_map['end-worker-write']} 'Worker Write ends, NWID=%ld, WIDX=%ld' NWID {WIDX}")
            tran.writeAction(f"yield")
        else:
            tran.writeAction(f"ubench-write-done-{C}: yield")
        
    
    #===============UDSHMEM_UBENCHMARK END==================
    #================UDSHMEM_SIMPLE_UBENCH BEGIN================

    
    def __ev_subench_fork_template(self, name, parent_reg, iter_reg, shift, next_name="fork-nuds"):
        SRC_OB = "X8"
        DST_OB = "X9"
        NELEMS = "X10"
        NODEID = "X11" 
        LOGNNODES = "X11"
        LOGNSTACKS = "X12" # nstacks per node
        
        LOGNUDS = "X13" # nuds per stack
        LOGNLANES = "X14"   # nlanes per ud
        LOGNWORKERS = "X15" # nworkers per lane
        # send information to all the nodes
        LMBASE = "X31"
        LMPTR = "X30"
        TEMP0, TEMP1 = "X29", "X28"
        
        
        NSTACKS = "X16"
        ndevice = "X16"
        TARGET_NWID = "X17"
        I = "X18"
        EVW="X19"
        current_device = "X20"
        ZERO="X21"
        offset = "X22"
        numworkers = "X23"
        EXPECTED_NREPLY = "X27"
        REPLY_COUNT = "X28"
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.event_map[f'udshmem-subench-{name}'])
        self.__debug_log(tran, level=4, msg=f"print 'UDSHMEM-UBENCH[NWID=%ld]: fork-{name}' NWID")
        self.__debug_log(tran, level=4, msg=f"print 'Incoming OBs[NWID=%ld]: SRC_OB=%p, DST_OB=%p, NELEMS=%ld, LOGNNODES=%lu, LOGNSTACKS=%lu, LOGNUDS=%ld, LOGNLANES=%ld, LOGNWORKERS=%ld' NWID {SRC_OB} {DST_OB} {NELEMS} {LOGNNODES} {LOGNSTACKS} {LOGNUDS} {LOGNLANES} {LOGNWORKERS}")
        tran.writeAction(f"movir {ZERO} 0")
        tran.writeAction(f"movir {LMPTR} 0")
        tran.writeAction(f"addi X7 {LMBASE} {self.lm_base + self.config_offset + self.flag_offset}")
        for i in range(8):
            tran.writeAction(f"movwrl X{8+i} {LMBASE}({LMPTR},1,0)")
        tran.writeAction(f"addi X7 {LMBASE} {self.lm_base + self.config_offset + self.flag_offset}")
        # for i in range(nstacks): target_nwid = (nodeid << lognstacks + i) << (6+2)
        tran.writeAction(f"movir {ndevice} 1")
        if iter_reg !=  LOGNWORKERS:
            tran.writeAction(f"sl {ndevice} {iter_reg} {ndevice}")
        tran.writeAction(f"movir {I} 0") 
        tran.writeAction(f"mov_reg2reg NWID {current_device}")
        # tran.writeAction(f"sri {current_device} {current_device} {shift}")
        self.__debug_log(tran, level=4, msg=f"print 'UDSHMEM-UBENCH[NWID=%ld]: fork-{name}: current_device=%ld shift={shift}' NWID {current_device}")
        tran.writeAction(f"{name}-loop: beq {I} {ndevice} {name}-done")
        tran.writeAction(f"sli {I} {offset} {shift}")
        tran.writeAction(f"add {current_device} {offset} {TARGET_NWID}")
        self.__debug_log(tran, level=4, msg=f"print 'UDSHMEM-UBENCH[NWID=%ld]: fork-{name}: ndevice=%ld target_nwid=%ld' NWID {ndevice} {TARGET_NWID}")
        # send event
        tran.writeAction(f"evii {EVW} {self.event_map[f'udshmem-subench-{next_name}']} 255 {0b0101}")
        if iter_reg ==  LOGNWORKERS:
            tran.writeAction(f"mov_reg2reg NWID {TARGET_NWID}")    
        tran.writeAction(f"ev {EVW} {EVW} {TARGET_NWID} {TARGET_NWID} {0b1000}")
        if iter_reg ==  LOGNWORKERS:
            tran.writeAction(f"sendr3_wret {EVW} {self.event_map['udshmem-subench-join']} {I} {I} {I} {TEMP0} {TEMP1}")
        else:
            tran.writeAction(f"sendops_wret {EVW} {self.event_map['udshmem-subench-join']} X8 8 {TEMP0} {TEMP1}")
        tran.writeAction(f"addi {I} {I} 1")
        tran.writeAction(f"jmp {name}-loop")
        
        tran.writeAction(f"{name}-done: addi {ndevice} {EXPECTED_NREPLY} 0")
        tran.writeAction(f"movir {REPLY_COUNT} 0")
        tran.writeAction(f"yield")
    
    
    def __ev_subench(self):
        self.event_map.add_event("udshmem-subench-read") # fork nnodes
        self.event_map.add_event("udshmem-subench-write") # fork nnodes
        self.event_map.add_event("udshmem-subench-naive") # fork nnodes
        self.event_map.add_event("udshmem-subench-join")
        self.event_map.add_event("udshmem-subench-join-final")
        self.event_map.add_event("udshmem-subench-fork-nnodes")
        self.event_map.add_event("udshmem-subench-fork-nstacks")
        self.event_map.add_event("udshmem-subench-fork-nuds")
        self.event_map.add_event("udshmem-subench-fork-nlanes")
        self.event_map.add_event("udshmem-subench-fork-nworkers")
        self.event_map.add_event("udshmem-subench-worker-start")
        self.event_map.add_event("udshmem-subench-worker-write")
        self.event_map.add_event("udshmem-subench-worker-ack")
        self.event_map.add_event("udshmem-subench-remote")
        self.event_map.add_event("udshmem-subench-message")
        
     
        
        if self.impl == "subench-write":
            tran = self.state.writeTransition("eventCarry", self.state, self.state, self.event_map['udshmem-subench-write'])
        elif self.impl == "subench-read":
            tran = self.state.writeTransition("eventCarry", self.state, self.state, self.event_map['udshmem-subench-read'])
        elif self.impl == "subench-naive":
            tran = self.state.writeTransition("eventCarry", self.state, self.state, self.event_map['udshmem-subench-naive'])
        elif self.impl == "subench-message":
            tran = self.state.writeTransition("eventCarry", self.state, self.state, self.event_map['udshmem-subench-message'])
        else:
            print(f"Error: unknown impl {self.impl}")
            exit(1)
        SRC_OB = "X8"
        DST_OB = "X9"
        NELEMS = "X10"
        LOGNNODES = "X11" 
        LOGNSTACKS = "X12" # nstacks per node
        LOGNUDS = "X13" # nuds per stack
        LOGNLANES = "X14"   # nlanes per ud
        LOGNWORKERS = "X15" # nworkers per lane
        
        EVW="X19"
        LMBASE = "X31"
        LMPTR = "X30"
        EXPECTED_NREPLY = "X27"
        REPLY_COUNT = "X28"
        
        TEMP0, TEMP1 = "X29", "X30"    
            
        self.__debug_log(tran, f"print '[NWID=%ld]===================UDSHMEM UBENCH STARTS=================' NWID") # new line
        self.__debug_log(tran, f"print 'UDSHMEM-UBENCH[NWID=%ld]: Executing Ubench: {self.impl}...' NWID")
        self.__debug_log(tran, level=4, msg= f"print 'START status: ccont=%lu cevw=%lu' X1 X2")
        self.__debug_log(tran, level=2, msg=f"print 'Arguments: src=%p, dst=%p, nelems=%ld, lognnodes=%lu, lognstacks=%lu, lognuds=%ld, lognlanes=%ld, lognworkers=%ld' {SRC_OB} {DST_OB} {NELEMS} {LOGNNODES} {LOGNSTACKS} {LOGNUDS} {LOGNLANES} {LOGNWORKERS}")

        
        ZERO = "X21"
        self.__perf_log(tran, f"perflog 1 {pmap['all-start']} 'UDSHMEM Started!'")
        tran.writeAction(f"addi X7 {LMBASE} {self.lm_base + self.config_offset + self.flag_offset}")
        tran.writeAction(f"movir {REPLY_COUNT} 0")
        tran.writeAction(f"movir {EXPECTED_NREPLY} 1")
        
        # tran.writeAction(f"mov_reg2reg {TEMP0}")
        tran.writeAction(f"sl {EXPECTED_NREPLY} {LOGNNODES} {EXPECTED_NREPLY}")
        
        tran.writeAction(f"evii {EVW} {self.event_map['udshmem-subench-fork-nnodes']} 255 {0b0101}")
        tran.writeAction(f"sendops_wret {EVW} {self.event_map['udshmem-subench-join-final']} X8 8 {TEMP0} {TEMP1}")
        tran.writeAction(f"yield")
        
        # fork nodes
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.event_map['udshmem-subench-join'])
        EXPECTED_NREPLY = "X27"
        REPLY_COUNT = "X28"
        tran.writeAction(f"addi {REPLY_COUNT} {REPLY_COUNT} 1")
        tran.writeAction(f"beq {REPLY_COUNT} {EXPECTED_NREPLY} udshmem-subench-join-done")
        self.__debug_log(tran, level=4, msg=f"print 'UDSHMEM-UBENCH[NWID=%ld]: Joining... REPLY_COUNT=%ld, EXPECTED_NREPLY=%ld' NWID {REPLY_COUNT} {EXPECTED_NREPLY}")
        tran.writeAction(f"yield")
        self.__terminate(tran, tlabel="udshmem-subench-join-done")
        
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.event_map['udshmem-subench-join-final'])
        self.__debug_log(tran, f"print 'UDSHMEM-SUBENCH: Notify master completed at NWID=%ld' NWID")   
        # global termination routine (barrier)
        tran.writeAction(f"movir X29 1")
        tran.writeAction(f"movir X28 0")
        tran.writeAction(f"addi X7 X30 {self.lm_base + self.config_offset}")
        # tran.writeAction(f"move X29 0(X30) 0 8")
        tran.writeAction(f"movwrl X29 X30(X28,0,0)")
        self.__debug_log(tran, f"print 'UDSHMEM-SUBENCH: Master thread completed! Shmem terminated! Write Flag(1) to %ld' X30")
        self.__perf_log(tran, f"perflog 1 {pmap['all-end']} 'UDSHMEM Completed!'")
        self.__debug_log(tran, f"print '[NWID=%ld]===================UDSHMEM UBENCH ENDS=================' NWID") # new line
        # TODO: are there any values we want to send back?
        self.__debug_log(tran, f"print 'reg status: ccont=%lu cevw=%lu' X1 X2")
        # tran.writeAction(f"sendr_reply X31 X30 {TEMP0}")
        tran.writeAction(f"yieldt")
        
        self.__ev_subench_fork_template("fork-nnodes", ZERO, LOGNNODES, 11, next_name="fork-nstacks")
        self.__ev_subench_fork_template("fork-nstacks", LOGNNODES, LOGNSTACKS, 8, next_name="fork-nuds")
        self.__ev_subench_fork_template("fork-nuds", LOGNSTACKS, LOGNUDS, 6, next_name="fork-nlanes")
        self.__ev_subench_fork_template("fork-nlanes", LOGNUDS, LOGNLANES, 0, next_name="fork-nworkers")
        self.__ev_subench_fork_template("fork-nworkers", LOGNLANES, LOGNWORKERS, 0, next_name="worker-start")
        
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.event_map['udshmem-subench-worker-start'])
        # OB0,1,2 worker id
        SRC = "X16"
        DST = "X17"
        NELEMS = "X18"
        LOGNNODES = "X19"
        LOGNSTACKS = "X20" # nstacks per node
        LOGNUDS = "X21" # nuds per stack
        LOGNLANES = "X22"   # nlanes per ud
        LOGNWORKERS = "X23" # nworkers per lane
        
        LDPTR = "X23"
        STPTR = "X24"
        NLEFT_LD = "X25"
        NLEFT_ST = "X26"
        EXPECTED_NREPLY = "X27"
        REPLY_COUNT = "X28"
        TEMP = "X29"
        
        LMBASE = "X31"
        LMPTR = "X30"
        
        tran.writeAction(f"addi X7 {LMBASE} {self.lm_base + self.config_offset + self.flag_offset}")
        tran.writeAction(f"movir {LMPTR} 3")
        for i in range(3, 8):
            tran.writeAction(f"movwlr {LMBASE}({LMPTR},1,0) X{16+i}")
        self.__debug_log(tran, level=3, msg=f"print 'UDSHMEM-UBENCH[NWID=%ld] Worker-start: NELEMS=%ld, LOGNNODES=%ld, LOGNSTACKS=%ld, LOGNUDS=%ld, LOGNLANES=%ld, LOGNWORKERS=%ld' NWID {NELEMS} {LOGNNODES} {LOGNSTACKS} {LOGNUDS} {LOGNLANES} {LOGNWORKERS}")
        # first calculate offset by nelems
        # X24-X31 free
        NODEID = "X24"
        STACKID = "X25"
        UDID = "X26"
        LANEID = "X27"
        
        NW_NODE = "X28"
        NW_STACK = "X29"
        NW_UD = "X30"
        NW_LANE = "X31"
        NWID = "X16"
        TEMP = "X17"
        TEMP1 = "X18"
        tran.writeAction(f"mov_reg2reg NWID {NWID}")
        # tran.writeAction(f"movir {NWID} 0")
        # nodeid = nwid >> 11
        tran.writeAction(f"sri {NWID} {NODEID} 11")
        tran.writeAction(f"movir {NODEID} 0")
        # stackid = nwid >> 8 
        tran.writeAction(f"srandii {NWID} {STACKID} 8 {0b111}") #1792
        tran.writeAction(f"srandii {NWID} {UDID} 6 {0b11}") #192
        # self.__debug_log(tran, f"print 'NWID=%ld UDID=%ld' {NWID} {UDID}")
        # tran.writeAction(f"sri {NWID} {UDID} 6")
        # self.__debug_log(tran, f"print 'NWID=%ld UDID=%ld' {NWID} {UDID}")
        # tran.writeAction(f"andi {UDID} {UDID} {0b11}")
        # self.__debug_log(tran, f"print 'NWID=%ld UDID=%ld' {NWID} {UDID}")
        
        tran.writeAction(f"andi {NWID} {LANEID} {0b111111}") #63
        
        self.__debug_log(tran, level=4, msg=f"print 'UDSHMEM-UBENCH[NWID=%ld] Worker-start: NWID=%ld, nodeid=%ld, stackid=%ld, udid=%ld, laneid=%ld' NWID {NWID} {NODEID} {STACKID} {UDID} {LANEID}")
        # calculate the offset
        # nnodes = nstacks * nuds * nlanes * nworkers * nelems
        tran.writeAction(f"movir {TEMP} 1")
        # TEMP = nworkersperlane * nelems
        tran.writeAction(f"sl {TEMP} {LOGNWORKERS} {NW_LANE}")
        # tran.writeACtion(f"mov_reg2reg {TEMP} {NW_LANE}") # simply 1 worker perlane
        self.__debug_log(tran, level=4, msg= f"print 'UDSHMEM-UBENCH[NWID=%ld] Worker-start: NWID=%ld, LOGNWORKERS=%ld, NW_LANE=%ld, NELEMS=%ld' NWID {NWID} {LOGNWORKERS} {NW_LANE} {NELEMS}")
        # NWORKERS(LANE) = nlanes * TEMP
        tran.writeAction(f"sl {NW_LANE} {LOGNLANES} {NW_UD}")
        self.__debug_log(tran, level=4, msg=f"print 'UDSHMEM-UBENCH[NWID=%ld] Worker-start: NWID=%ld, LOGNLANES=%ld, NW_UD=%ld, NW_LANE=%ld' NWID {NWID} {LOGNLANES} {NW_UD} {NW_LANE}")
        # NWORKERS(UD) = nworkers * NLANES
        tran.writeAction(f"sl {NW_UD} {LOGNUDS} {NW_STACK}")
        self.__debug_log(tran, level=4, msg=f"print 'UDSHMEM-UBENCH[NWID=%ld] Worker-start: NWID=%ld, LOGNUDS=%ld, NW_STACK=%ld, NW_UD=%ld' NWID {NWID} {LOGNUDS} {NW_STACK} {NW_UD}")
        # NWORKERS(STACK) = nuds * NUDS
        tran.writeAction(f"sl {NW_STACK} {LOGNSTACKS} {NW_NODE}")
        self.__debug_log(tran, level=4, msg=f"print 'UDSHMEM-UBENCH[NWID=%ld] Worker-start: NWID=%ld, LOGNSTACKS=%ld, NW_NODE=%ld, NW_STACK=%ld' NWID {NWID} {LOGNSTACKS} {NW_NODE} {NW_STACK}")
        # NWORKERS(NODE) = nstacks * NUDS
        # current worker id = nworkersperlane * nelems * laneid + nworkers * nlanes * nelems * udid + nworkers * nlanes * nuds * nelems * stackid + nworkers * nlanes * nuds * nstacks * nelems * nodeid
        tran.writeAction(f"mul {LANEID} {NW_LANE} {TEMP}")
        tran.writeAction(f"addi {TEMP} {TEMP1} 0")
        self.__debug_log(tran, level=4, msg=f"print ' LANEID=%ld, NW_LANE=%ld, TEMP=%ld, TEMP1=%ld' {LANEID} {NW_LANE} {TEMP} {TEMP1}")
        tran.writeAction(f"mul {UDID} {NW_UD} {TEMP}")
        tran.writeAction(f"add {TEMP} {TEMP1} {TEMP1}")
        self.__debug_log(tran, level=4, msg= f"print ' UDID=%ld, NW_UD=%ld, TEMP=%ld, TEMP1=%ld' {UDID} {NW_UD} {TEMP} {TEMP1}")
        tran.writeAction(f"mul {STACKID} {NW_STACK} {TEMP}")
        tran.writeAction(f"add {TEMP} {TEMP1} {TEMP1}")
        self.__debug_log(tran, level=4, msg= f"print ' STACKID=%ld, NW_STACK=%ld, TEMP=%ld, TEMP1=%ld' {STACKID} {NW_STACK} {TEMP} {TEMP1}")
        tran.writeAction(f"mul {NODEID} {NW_NODE} {TEMP}")
        tran.writeAction(f"add {TEMP} {TEMP1} {TEMP1}")
        tran.writeAction(f"add {TEMP1} X8 {TEMP1}")
        self.__debug_log(tran, level=4, msg= f"print ' NODEID=%ld, NW_NODE=%ld, TEMP=%ld, TEMP1=%ld, x8=%ld' {NODEID} {NW_NODE} {TEMP} {TEMP1} X8")
        

        # recycle X24-X31
        SRC = "X16"
        DST = "X17"
        NELEMS = "X18"
        WIDX = "X19"
        INIT_OFFSET = "X20"
        LDPTR = "X23"
        STPTR = "X24"
        NLEFT_LD = "X25"
        NLEFT_ST = "X26"
        DST_SRC_DIFF = "X28"
        TEMP0 = "X29"
        tran.writeAction(f"movir {WIDX} 0")
        tran.writeAction(f"addi {TEMP1} {WIDX} 0")
            
        tran.writeAction(f"addi X7 {LMBASE} {self.lm_base + self.config_offset + self.flag_offset}")
        tran.writeAction(f"movir {LMPTR} 0")
        # SRC, DST and NELEMS are back
        for i in range(3):
            tran.writeAction(f"movwlr {LMBASE}({LMPTR},1,0) X{16+i}") 
        tran.writeAction(f"sli {WIDX} {INIT_OFFSET} 3")
        tran.writeAction(f"mul {INIT_OFFSET} {NELEMS} {INIT_OFFSET}")
        tran.writeAction(f"add {SRC} {INIT_OFFSET} {LDPTR}")
        # TEMP1 is the offset in nelems
        tran.writeAction(f"add {DST} {INIT_OFFSET} {STPTR}")
        tran.writeAction(f"sub {DST} {SRC} {DST_SRC_DIFF}")
        tran.writeAction(f"addi {NELEMS} {NLEFT_LD} 0")
        tran.writeAction(f"addi {NELEMS} {NLEFT_ST} 0")
        if self.impl == "subench-read":
            self.__debug_log(tran, level=3, msg=f"print 'UDSHMEM-UBENCH[NWID=%ld]: Start reading: WIDX=%ld, SRC=%p, LDPTR=%p, DST=%p, STPTR=%p, NLEFT_LD=%ld, NLEFT_ST=%ld' NWID {WIDX} {SRC} {LDPTR} {DST} {STPTR} {NLEFT_LD} {NLEFT_ST}")
        elif self.impl == "subench-write":
            self.__debug_log(tran, level=3, msg=f"print 'UDSHMEM-UBENCH[NWID=%ld]: Start writing: WIDX=%ld, SRC=%p, LDPTR=%p, DST=%p, STPTR=%p, NLEFT_LD=%ld, NLEFT_ST=%ld' NWID {WIDX} {SRC} {LDPTR} {DST} {STPTR} {NLEFT_LD} {NLEFT_ST}")
        elif self.impl == "subench-naive":
            self.__debug_log(tran, level=3, msg=f"print 'UDSHMEM-UBENCH[NWID=%ld]: Start naive shmem: WIDX=%ld, SRC=%p, LDPTR=%p, DST=%p, STPTR=%p, NLEFT_LD=%ld, NLEFT_ST=%ld' NWID {WIDX} {SRC} {LDPTR} {DST} {STPTR} {NLEFT_LD} {NLEFT_ST}")
        
        tran.writeAction(f"addi X7 {LMBASE} {self.lm_base + self.config_offset + self.flag_offset}")
        # tran.writeAction(f"movir {LMPTR} 0")
        if self.impl == "subench-message":
            EVW = "X19"
            TNWID = "X20"
            tran.writeAction(f"evii {EVW} {self.event_map['udshmem-subench-remote']} 255 {0b0101}")
            tran.writeAction(f"mov_reg2reg NWID {TNWID}")
            tran.writeAction(f"addi {TNWID} {TNWID} 2048")
            tran.writeAction(f"ev {EVW} {EVW} {TNWID} {TNWID} {0b1000}")
        # self.__perf_log(tran, f"perflog 1 {perflog_map['start-worker-rw']} 'Worker starts, NWID=%ld, WIDX=%ld' NWID {WIDX}")
        self.__perf_log(tran, f"perflog 1 {pmap['worker-starts']} 'Worker starts, NWID=%ld, WIDX=%ld' NWID {WIDX}")
        tran.writeAction(f"subench-loop: blei {NLEFT_LD} 0 subench-done")
        if self.impl == "subench-read":
            tran.writeAction(f"send_dmlm_ld_wret {LDPTR} {self.event_map['udshmem-subench-worker-ack']} 8 {TEMP0}")
            tran.writeAction(f"addi {LDPTR} {LDPTR} 64")                
        elif self.impl == "subench-write":
            tran.writeAction(f"send_dmlm_wret {STPTR} {self.event_map['udshmem-subench-worker-ack']} {LMBASE} 8 {TEMP0}")
            tran.writeAction(f"addi {STPTR} {STPTR} 64")
        elif self.impl == "subench-naive":
            tran.writeAction(f"send_dmlm_ld_wret {LDPTR} {self.event_map['udshmem-subench-worker-write']} 8 {TEMP0}")
            tran.writeAction(f"addi {LDPTR} {LDPTR} 64")
        elif self.impl == "subench-message":
            tran.writeAction(f"send_wret {EVW} {self.event_map['udshmem-subench-worker-ack']} {LMBASE} 8 {TEMP0}")
        else:
            print(f"Error: unknown impl {self.impl}")
            exit(1)
        tran.writeAction(f"subi {NLEFT_LD} {NLEFT_LD} 8")
        tran.writeAction(f"jmp subench-loop")
        if self.perflog:
            if self.impl == "subench-read":
                self.__perf_log(tran, f"subench-done: perflog 1 {pmap['worker-read-ends']} 'Worker read ends, NWID=%ld, WIDX=%ld' NWID {WIDX}")
            else:
                self.__perf_log(tran, f"subench-done: perflog 1 {pmap['worker-write-ends']} 'Worker write ends, NWID=%ld, WIDX=%ld' NWID {WIDX}")
            tran.writeAction(f"yield")
        else:
            tran.writeAction(f"subench-done: yield")
        
        
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.event_map['udshmem-subench-remote'])
        self.__debug_log(tran, level=2, msg=f"print 'UDSHMEM-UBENCH[NWID=%ld]: Remote access' NWID")
        tran.writeAction(f"sendr_reply X31 X30 X29")
        tran.writeAction(f"yieldt")
        
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.event_map['udshmem-subench-worker-ack'])
        LDPTR = "X23"
        STPTR = "X24"
        NLEFT_LD = "X25"
        NLEFT_ST = "X26"
        tran.writeAction(f"bne {NLEFT_LD} {NELEMS} ack-cont")
        self.__perf_log(tran, f"perflog 1 {pmap['worker-ack-starts']} 'Worker ack starts, NWID=%ld, WIDX=%ld' NWID {WIDX}")
        tran.writeAction(f"ack-cont: subi {NLEFT_ST} {NLEFT_ST} 8")
        if self.impl == "subench-read":
            self.__debug_log(tran, level=5, msg=f"print 'UDSHMEM-UBENCH[NWID=%ld]: Worker ack: NLEFT_LD=%ld, NLEFT_ST=%ld' NWID {NLEFT_LD} {NLEFT_ST}")
            self.__debug_log(tran, level=5, msg=f"print 'UDSHMEM-UBENCH[NWID=%ld]: Worker ack: NLEFT_ST=%ld, data=%ld, data[0]=%ld, data[1]=%ld, data[2]=%ld, data[3]=%ld, data[4]=%ld, data[5]=%ld, data[6]=%ld, data[7]=%ld' NWID {NLEFT_ST} X3 X8 X9 X10 X11 X12 X13 X14 X15")
        tran.writeAction(f"blei {NLEFT_ST} {0} udshmem-subench-worker-ack-done")
        tran.writeAction(f"yield")
        self.__terminate(tran, tlabel="udshmem-subench-worker-ack-done")
        
        # the write op
        RETURN_ADDR_REG = "X3"
        DST_SRC_DIFF = "X28"
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.event_map['udshmem-subench-worker-write'])
        tran.writeAction(f"add {RETURN_ADDR_REG} {DST_SRC_DIFF} {STPTR}")
        tran.writeAction(f"sendops_dmlm_wret {STPTR} {self.event_map['udshmem-subench-worker-ack']} X8 8 {TEMP0}")
        tran.writeAction(f"yield")
    
    #================UDSHMEM_SIMPLE_UBENCH END==================#
    
    #====================INTELLEGENT IMPLEMENTATION====================
    
    # region INTELLIGENT IMPLEMENTATION
    def __intelligent_udshmem(self):   
        self.event_map.add_event('udshmem-shmem-get')
        self.event_map.add_event('udshmem-shmem-iget')
        
        self.event_map.add_event('udshmem-intelli-init')
        self.event_map.add_event('udshmem-init-configs')
        self.event_map.add_event('udshmem-config-info-request')
        self.event_map.add_event('udshmem-config-info-response')
        self.event_map.add_event('udshmem-notify-master-completed')
        self.event_map.add_event('udshmem-start-master-thread')
        self.event_map.add_event('udshmem-cont-master-thread')
        self.event_map.add_event('udshmem-notify-ud-complete')
        self.event_map.add_event('udshmem-start-ud-master-threads')
        self.event_map.add_event('udshmem-start-worker-thread')
        self.event_map.add_event('udshmem-notify-worker-complete') 
        
        self.__udshmem_intelligent_init()
        self.__init_udshmem_configs()
        self.__config_info_request()
        self.__notify_master_completed()
        self.__start_master_thread()
        self.__notify_ud_complete()
        self.__start_ud_master_thread()
        self.__start_worker_thread()
        self.__notify_worker_complete()
        # print(self.allowed_chunk_sizes)
        for C in self.allowed_chunk_sizes:
            self.__ev_load_store_loop(C, self.ele_size)
        # print(default_chunks)
        for C in self.default_chunk_sizes:
            self.__ev_ack(C)
     

    def __udshmem_intelligent_init(self):
        '''
        Now the Entry function for shmem library
        This function is triggered once by the TOP or the user program
        For generating EFA, call once
        
        Future version will support reading from spm and decide the number of devices
        OB_0: SRC
        OB_1: DST
        OB_3: NELE
        OB_4: OPCODE
        
        In SPM/LM: configurations are stored in the following order:
        lm_base + 0: NumNodes
        lm_base + 8: NumStacks
        lm_base + 16: NumUDs
        lm_base + 24: NumLanes
        lm_base + 32: GMapMemBase
        lm_base + 40: MapMemBase
        lm_base + 48: NodeBlockSize
        '''
        # nuds, nworkers, nlanes are hardcoded for now
        # given src, dest, nele, the ele_size is known
        NUM_PARAMS = 8
        SRC_OB = "X8"
        DST_OB = "X9"
        NELE_OB = "X10"
        OPCODE_OB = "X11"
        
        OPCODE = "X16"
        SRC = "X17"
        DST =  "X18"
        NELE = "X19"
        
        # to be calculated
        NWORKERS = "X20"
        NLANES = "X21"
        NUDS = "X22"
        START_UDID = "X23"
        
        START_NWID = "X25"
        EVENT_WORD = "X24"
        TEMP0 = "X26"
        TEMP1 = "X27" #28 29
        
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
        
        
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.event_map['udshmem-intelli-init'])
        
        # read the configs from LM
        self.__debug_log(tran, f"print 'LIB-ROOT: Intelligent UDShmem(imp={self.impl}) init at NWID=%ld' NWID")
        NUMNODES = "X16"
        NUMSTACKS = "X17"
        NUMUDS = "X18"
        NUMLANES = "X19"
        GMAP_MEM_BASE = "X24"
        MAP_MEM_BASE = "X25"
        NODE_BLOCK_SIZE = "X26"
        LM_BASE = "X30"
        LM_PTR = "X31"
        tran.writeAction(f'addi X7 {LM_BASE} {self.lm_base}')
        tran.writeAction(f'movir {LM_PTR} 0')
        tran.writeAction(f"movwlr {LM_BASE}({LM_PTR},1,0) {NUMNODES}")
        tran.writeAction(f"movwlr {LM_BASE}({LM_PTR},1,0) {NUMSTACKS}")
        tran.writeAction(f"movwlr {LM_BASE}({LM_PTR},1,0) {NUMUDS}")
        tran.writeAction(f"movwlr {LM_BASE}({LM_PTR},1,0) {NUMLANES}")
        tran.writeAction(f"movwlr {LM_BASE}({LM_PTR},1,0) {GMAP_MEM_BASE}")
        tran.writeAction(f"movwlr {LM_BASE}({LM_PTR},1,0) {MAP_MEM_BASE}")
        tran.writeAction(f"movwlr {LM_BASE}({LM_PTR},1,0) {NODE_BLOCK_SIZE}")
        
        # self.__debug_log(tran, f"print 'LIB-ROOT: Intelligent UDShmem(imp={self.impl}) init at nwid=%ld, numnodes=%ld' NWID {NUMNODES}")
        self.__debug_log(tran, f"print 'LIB-ROOT: System Configuration: numnodes=%ld, numstacks=%ld, numuds=%ld, nlanes=%ld.' {NUMNODES} {NUMSTACKS} {NUMUDS} {NUMLANES}")
        self.__debug_log(tran, f"print 'LIB-ROOT: System Configuration: gmap_mem_base=%ld, map_mem_base=%ld, node_block_size=%ld.' {GMAP_MEM_BASE} {MAP_MEM_BASE} {NODE_BLOCK_SIZE}")
        
        # calculate the number of workers, lanes, uds, and start_udid
        # X27 - X29 are free
        
        # Calculate MAX_NUM_LANES
        MAX_NUM_LANES = "X27"
        # TODO: can be optmized by using shift, not worried for now
        tran.writeAction(f"mul {NUMNODES} {NUMSTACKS} {MAX_NUM_LANES}")
        tran.writeAction(f"mul {MAX_NUM_LANES} {NUMUDS} {MAX_NUM_LANES}")
        tran.writeAction(f"mul {MAX_NUM_LANES} {NUMLANES} {MAX_NUM_LANES}")
        tran.writeAction(f"movwrl {MAX_NUM_LANES} {LM_BASE}({LM_PTR},1,0)")
        
        # Calculate the start_UDID
        # based on mode, decide the start_nwid
        # for mode 0, 1, 2, start_nwid = caller_nwid << 6 >> 6
        # for mode 3, start_nwid = either src or dst's node's udid0
        # nnodes = |(src - src_end)| // node_block_size
        # start_nodeid = (src - gmap_mem_base) // node_block_size
        # target_nwid[] = target_nwid[] % total_nwids        
        
        # decide wheter it is a get(global->local)/put(local->global)/memcpy(global->global)
        # check sr and dst
        # mode = 0: local->local
        # mode = 1: global->local
        # mode = 2: local->global
        # mode = 3: global->global
        MODE = "X28"
        tran.writeAction(f"movir {MODE} 0")
        tran.writeAction(f"blt {SRC_OB} {GMAP_MEM_BASE} udshmem-src-local")
        tran.writeAction(f"ori {MODE} {MODE} 1") # src is global
        tran.writeAction(f"udshmem-src-local: ori {MODE} {MODE} 0") # src is local
        tran.writeAction(f"blt {DST_OB} {GMAP_MEM_BASE} udshmem-dst-local")
        tran.writeAction(f"ori {MODE} {MODE} 2") # dst is global
        tran.writeAction(f"udshmem-dst-local: ori {MODE} {MODE} 0") # dst is local
        self.__debug_log(tran, f"print 'LiB_ROOT: MODE 0: local->local, 1: global->local, 2: local->global, 3: global->global'")
        self.__debug_log(tran, f"print 'LIB_ROOT: MODE=%ld, SRC=%ld, DST=%ld, MAP_MEM_BASE=%ld, GMAP_MEM_BASE=%ld' {MODE} {SRC_OB} {DST_OB} {MAP_MEM_BASE} {GMAP_MEM_BASE}")
        # Calculate START_NWID
        # if mode = 0, 1, 2; START_NWID = caller_nwid << 6 >> 6
        
        # test only
        # tran.writeAction(f"movir {MODE} 2")
        NNODES = "X29"
        TEMP = "X30"

        # Calculate active NNODES
        # if mode = 0, 1, 2; NNODES = 1
        # else, NNODES = |(src - src_end)| // node_block_size
        tran.writeAction(f"beqi {MODE} 3 udshmem-all-global")
        tran.writeAction(f"movir {NNODES} 1")
        # start_nwid = caller_nwid << 6 >> 6
        tran.writeAction(f"mov_reg2reg X0 {START_NWID}")
        # tran.writeAction(f"addi {START_NWID} {TEMP} 0")
        tran.writeAction(f"sri {START_NWID} {START_UDID} 6")
        tran.writeAction(f"sli {START_UDID} {START_NWID} 6")
        self.__debug_log(tran, f"print 'LIB_ROOT: START_NWID=%ld' {START_NWID}")
        # FIXME: check if the start_nwid is with range
        tran.writeAction(f"jmp udshmem-nnodes-cont")
        
        
        # START_NWID(ADDR_DIFF)
        tran.writeAction(f"udshmem-all-global: sub {SRC_OB} {GMAP_MEM_BASE} {START_NWID}") 
        # Rv: START_NWID(NODEID, it could be over NUMNODES)
        tran.writeAction(f"div {START_NWID} {NODE_BLOCK_SIZE} {START_NWID}")
        # Rv: START_NWID(NODEID)
        tran.writeAction(f"mod {START_NWID} {NUMNODES} {START_NWID}")
        tran.writeAction(f"sli {START_NWID} {START_NWID} 11") # 2^11 = 2048
        self.__debug_log(tran, f"print 'LIB_ROOT: GLOBAL->GLOBAL: START_NWID=%ld' {START_NWID}")
        # this is src-src_end, which is how many bytes are involved
        tran.writeAction(f"sli {NELE_OB} {TEMP} {self.ele_shift}")
        tran.writeAction(f"div {TEMP} {NODE_BLOCK_SIZE} {NNODES}")

        tran.writeAction(f"bgt {NNODES} {NUMNODES} udshmem-gt-numnodes") # if NNODES > NUMNODES, jump to udshmem-gt-numnodes
        
        tran.writeAction(f"bgti {NNODES} 0 udshmem-nnodes-cont") # if NNODES > 1, jump to udshmem-gt-1node
        tran.writeAction(f"movir {NNODES} 1") # when NNODES <=1
        tran.writeAction(f"jmp udshmem-nnodes-cont")
        
        tran.writeAction(f"udshmem-gt-numnodes: mod {NNODES} {NUMNODES} {NNODES}") # NNODES = NNODES % NUMNODES
        tran.writeAction(f"jmp udshmem-nnodes0")
        tran.writeAction(f"udshmem-nnodes1: movir {NNODES} 1")
        tran.writeAction(f"udshmem-nnodes0: blti {NNODES} 1 udshmem-nnodes1") # if NNODES < 1, NNODES = 1
        # now NNODES is either 1 or NUMNODES or NNODES % NUMNODES, we calculated other nums

        
        # Calculate NUDS
        # based on the start and end, we can have a finer-grained estimation of how many will be used
        # P1: will use full NUDS, NUDS = NUMSTACKS * NUMUDS
        # if mode = 0, 1, 2; use full NUDS
        # NUMUDS = X18 can be recycled
      
        
        # Calculate total involved NLANES
        # based on the start and end, we can have a finer-grained estimation of how many will be used
        # P1: will use full NLANES, NLANES = NUDS * NUMLANES
        # NUMLANES = X19 can be recycled
        
        
        # Calcuate NWORKERS 
        # for now, nworkers will be MAX_NUM_LANES
        
        
        # if mode = 0, 1, 2 
        # if mode = 3, NUMSTACK * NUMUDS * NUMLANES * nnodes
        NSTACKS = "X30" # temporary
        tran.writeAction(f"udshmem-nnodes-cont: mul {NUMSTACKS} {NNODES} {NSTACKS}")
        tran.writeAction(f"mul {NUMUDS} {NSTACKS} {NUDS}")
        tran.writeAction(f"mul {NUMLANES} {NUDS} {NLANES}")
        tran.writeAction(f"addi {NLANES} {NWORKERS} 0")
        
        #test only
        # tran.writeAction(f"movir {START_NWID} 1")
        # tran.writeAction(f"sli {START_NWID} {START_NWID} 11")
        # tran.writeAction(f"movir {START_UDID} 32")
        #test only
        # tran.writeAction(f"movir {START_NWID} 4")
        # tran.writeAction(f"sli {START_NWID} {START_NWID} 6")
        # tran.writeAction(f"movir {START_UDID} 4")
        self.__debug_log(tran, f"print 'LIB-ROOT: Intelligent UDShmem init: NNODES=%ld, NUDS=%ld, NLANES=%ld, NWORKERS=%ld, START_NWID=%ld' {NNODES} {NUDS} {NLANES} {NWORKERS} {START_NWID}")
       
        
        # move values from OB to registers
        tran.writeAction(f"mov_reg2reg {OPCODE_OB} {OPCODE}")
        tran.writeAction(f"mov_reg2reg {SRC_OB} {SRC}")
        tran.writeAction(f"mov_reg2reg {DST_OB} {DST}")
        tran.writeAction(f"mov_reg2reg {NELE_OB} {NELE}") 
        
        tran.writeAction(f'addi X7 {LM_BASE} {self.lm_base + self.config_offset + self.flag_offset}')
        tran.writeAction(f'movir {LM_PTR} 0')
        for o in range(NUM_PARAMS):
            tran.writeAction(f"movwrl X{16+o} {LM_BASE}({LM_PTR},1,0)")

        tran.writeAction(f"evii {EVENT_WORD} {self.event_map['udshmem-start-master-thread']} 255 {0b0101}")
        tran.writeAction(f"ev {EVENT_WORD} {EVENT_WORD} {START_NWID} {START_NWID} {0b1000}")
        tran.writeAction(f"send_wret {EVENT_WORD} {self.event_map['udshmem-notify-master-completed']} {LM_BASE} 8 {TEMP0} {TEMP1}") # now $len is in words
        
        tran.writeAction(f"yield")
        
        self.trans.append(tran)
          
        
    def __notify_master_completed(self):
        TEMP = "X28"
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.event_map['udshmem-notify-master-completed'])
        self.__debug_log(tran, f"print 'LIB-ROOT: Notify master completed at NWID=%ld' NWID")   
        # global termination routine (barrier)
        tran.writeAction(f"movir X29 1")
        tran.writeAction(f"movir X28 0")
        tran.writeAction(f"addi X7 X30 {self.lm_base + self.config_offset}")
        # tran.writeAction(f"move X29 0(X30) 0 8")
        tran.writeAction(f"movwrl X29 X30(X28,0,0)")
        self.__debug_log(tran, f"print 'LIB-ROOT: Master thread completed! Shmem terminated! Write Flag(1) to %ld' X30")
        self.__perf_log(tran, f"perflog 1 {perflog_map['end-all']} 'UDSHMEM Completed!'")
        self.__debug_log(tran, f"print '===================UDSHMEM ENDS================='") # new line
        # TODO: are there any values we want to send back?
        tran.writeAction(f"sendr_reply X31 X30 {TEMP}")
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
        OPCODE = "X16"
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


        tran_smt0 = self.state.writeTransition("eventCarry", self.state, self.state, self.event_map['udshmem-start-master-thread'])
        self.__debug_log(tran_smt0, f"print 'UDSHMEM-Master(NWID=%ld): Start master thread' NWID")
        # self.__perf_log(tran_smt, f"perflog 1 0 'master thread start, NWID=%ld' NWID")
        
        # first check if the configuration info is in place
        #X22 - X29 are free for now
        NUMNODES = "X22"
        EVW = "X23"
        
        # save a copy of the arguments to LM
        tran_smt0.writeAction(f'addi X7 {LM_BASE} {self.lm_base + self.config_offset + self.flag_offset}')
        tran_smt0.writeAction(f'mov_imm2reg {LM_PTR} 0')
        for o in range(NUM_PARAMS):
            tran_smt0.writeAction(f"mov_reg2reg X{8+o} X{16+o}")
            tran_smt0.writeAction(f"movwrl X{16+o} {LM_BASE}({LM_PTR},1,0)")
        
        # check if the config info is ready  
        tran_smt0.writeAction(f"addi X7 {LM_BASE} {self.lm_base}")
        tran_smt0.writeAction(f"movir {LM_PTR} 0")
        tran_smt0.writeAction(f"movir {NUMNODES} 0")
        tran_smt0.writeAction(f"movwlr {LM_BASE}({LM_PTR},1,0) {NUMNODES}")
        # if not 0, then it should be ready
        tran_smt0.writeAction(f"bnei {NUMNODES} 0 udshmem-config-info-ready")
        # else, send a request to the parent asking for its config info, it must be there, and also new thread
        self.__debug_log(tran_smt0, f"print 'UDSHMEM-Master(NWID=%ld): Requesting config info from parent' NWID")
        tran_smt0.writeAction(f"evi X1 {EVW} {self.event_map['udshmem-config-info-request']} {0b0001}")
        tran_smt0.writeAction(f"evi {EVW} {EVW} 255 {0b0100}")
        tran_smt0.writeAction(f"sendr_wret {EVW} {self.event_map['udshmem-config-info-response']} {TEMP0} {TEMP0} {TEMP0} {TEMP0}")
        tran_smt0.writeAction(f"yield")

        # simply redirect event to the udshmem-cont-master-thread
        # the ops are the ops for the master thread; CCONT(X1) is the caller's passed CONT
        tran_smt0.writeAction(f"udshmem-config-info-ready: evi X2 {EVW} {self.event_map['udshmem-cont-master-thread']} {0b0001}")
        self.__debug_log(tran_smt0, f"print 'UDSHMEM-Master(NWID=%ld): Config info ready, continue master thread.' NWID")
        tran_smt0.writeAction(f"sendops_wcont {EVW} X1 X8 {NUM_PARAMS}")
        tran_smt0.writeAction(f"yield")
        
        
        tran_smt1 = self.state.writeTransition("eventCarry", self.state, self.state, self.event_map['udshmem-config-info-response'])
        self.__debug_log(tran_smt1, f"print 'UDSHMEM-Master(NWID=%ld): Receive config info from parent' NWID")
        tran_smt1.writeAction(f"addi X7 {LM_BASE} {self.lm_base}")
        tran_smt1.writeAction(f"movir {LM_PTR} 0")
        for i in range(NUM_PARAMS):
            self.__debug_log(tran_smt1, level=2, msg=f"print 'UDSHMEM-Master(NWID=%ld): Writing configs to LM, x{i}=%ld to %ld(%ld)' NWID X{8+i} {LM_BASE} {LM_PTR}")
            tran_smt1.writeAction(f"movwrl X{8+i} {LM_BASE}({LM_PTR},1,0)")
        # resume the master thread
        tran_smt1.writeAction(f"evi X2 {EVW} {self.event_map['udshmem-cont-master-thread']} {0b0001}")
        tran_smt1.writeAction(f"sendops_wcont {EVW} X1 X8 {NUM_PARAMS}")
        tran_smt1.writeAction(f"yield")
       
        
        tran_smt = self.state.writeTransition("eventCarry", self.state, self.state, self.event_map['udshmem-cont-master-thread'])
        self.__debug_log(tran_smt, f"print 'UDSHMEM-Master[NWID=%ld]: Continue master thread' NWID")
        tran_smt.writeAction(f'addi X7 {LM_BASE} {self.lm_base + self.config_offset + self.flag_offset}')
        tran_smt.writeAction(f'mov_imm2reg {LM_PTR} 0')
        for o in range(NUM_PARAMS):
            tran_smt.writeAction(f"movwlr {LM_BASE}({LM_PTR},1,0) X{16+o}")
        # X16 - X23 are used
        # START_UDID = "X23", TARGET_UDID = "X24", TARGET_L0ID = "X25", EVENT_WORD = "X26", COMPLETED_UDS = "X27"
        # get the max number of uds
        MAX_NUDS = "X27"
        tran_smt.writeAction(f'addi X7 {LM_BASE} {self.lm_base}')
        tran_smt.writeAction(f'movir {LM_PTR} 7')
        tran_smt.writeAction(f"movwlr {LM_BASE}({LM_PTR},0,0) {MAX_NUDS}") # actually max lanes got read
        self.__debug_log(tran_smt, level=2, msg=f"print 'UDSHMEM-Master[NWID=%ld]: MAX_NLANES=%ld' NWID {MAX_NUDS}")
        tran_smt.writeAction(f"sri {MAX_NUDS} {MAX_NUDS} 6") # max_nuds = max_nuds >> 6
        self.__debug_log(tran_smt, level=2, msg=f"print 'UDSHMEM-Master[NWID=%ld]: MAX_NUDS=%ld' NWID {MAX_NUDS}")
        # reset the LM_BASE and LM_PTR
        tran_smt.writeAction(f"mov_imm2reg {LM_PTR} 0")
        tran_smt.writeAction(f"addi X7 {LM_BASE} {self.lm_base + self.config_offset + self.flag_offset}")
        # start lane master threads
        tran_smt.writeAction(f"mov_reg2reg {START_UDID} {TARGET_UDID}")
        tran_smt.writeAction(f"add {START_UDID} {NUDS} {END_UDID}")
        self.__debug_log(tran_smt, f"print 'UDSHMEM-Master[NWID=%ld]: START_UDID=%ld END_UDID=%ld' NWID {START_UDID} {END_UDID}")
        # free START_UDID
        TEMP_UDID = "X23"
        tran_smt.writeAction(f"start-loop: ble {END_UDID} {TARGET_UDID} done") # if end_udid <= start_udid, terminate
        self.__debug_log(tran_smt, f"print 'UDSHMEM-Master[NWID=%ld]: Sending start_ud_master_thread to TARGE_UDID=%ld' NWID {TARGET_UDID}")
        tran_smt.writeAction(f"mod {TARGET_UDID} {MAX_NUDS} {TEMP_UDID}") # target_udid = target_udid % max_nuds
        tran_smt.writeAction(f"lshift {TEMP_UDID} {TARGET_L0ID} 6")
        # tran_smt.writeAction(f"lshift {TARGET_UDID} {TARGET_L0ID} 6") # target_udid = target_l0idx << 6 = target_l0idx * 64
        
        tran_smt.writeAction(f"evii {EVENT_WORD} {self.event_map['udshmem-start-ud-master-threads']} 255 {0b0101}")
        tran_smt.writeAction(f"ev {EVENT_WORD} {EVENT_WORD} {TARGET_L0ID} {TARGET_L0ID} {0b1000}")
        self.__debug_log(tran_smt, level=2, msg=f"print 'UDSHMEM-Master[NWID=%ld]:Target_lane0_id=%ld, Target_udid=%ld, Temp_udid=%ld' NWID {TARGET_L0ID} {TARGET_UDID} {TEMP_UDID}")
        tran_smt.writeAction(f"send_wret {EVENT_WORD} {self.event_map['udshmem-notify-ud-complete']} {LM_BASE} 8 {TEMP0} {TEMP1}") # now $len is in words

        tran_smt.writeAction(f"addi {TARGET_UDID} {TARGET_UDID} 1")
        tran_smt.writeAction(f"jmp start-loop")
        tran_smt.writeAction(f"done: mov_imm2reg {COMPLETED_UDS} 0")
        tran_smt.writeAction(f"yield")

        # self.trans.append(tran_smt)
   
        
    def __config_info_request(self):
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.event_map['udshmem-config-info-request'])
        TEMP = "X29"
        EVW = "X30"
        LMPTR = "X31"
        # only a short-lived thread sending back the config info
        self.__debug_log(tran, f"print 'UDSHMEM-Master[NWID=%ld]:(new thread) Receive config info request.' NWID")
        tran.writeAction(f"addi X7 {LMPTR} {self.lm_base}")
        tran.writeAction(f"send_reply {LMPTR} 8 {TEMP}")
        tran.writeAction(f"yieldt")


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
        # self.__debug_log(tran_udc, f"print 'NUDS: %ld, COMPLETED_UDS: %ld' {NUDS} {COMPLETED_UDS}")
        tran_udc.writeAction(f"ble {NUDS} {COMPLETED_UDS} terminate")    # if nuds <= compeleted uds, terminate
        tran_udc.writeAction(f"yield")
        tran_udc.writeAction(f"terminate: sendr_reply {NUDS} {COMPLETED_UDS} {TEMP}") # isav2.3
        self.__debug_log(tran_udc, f"print 'UDSHMEM-Master: All UDs completed!'")
        tran_udc.writeAction(f"yield_terminate")
        # self.trans.append(tran_udc)  

    
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
        OPCODE = "X16"
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
        self.__debug_log(tran_lmt, f"print 'UDSHMEM-UD-Master[NWID=%ld]: Start ud master thread at NWID=%ld' NWID NWID")
        self.__perf_log(tran_lmt, f"perflog 1 1 'start ud master thread at NWID=%ld' NWID")
        tran_lmt.writeAction(f'addi X7 {LM_BASE} {self.lm_base + self.config_offset + self.flag_offset}')
        tran_lmt.writeAction(f"mov_imm2reg {LM_PTR} 0")
        # TODO: optimize fewer instructions without loading unused arguments
        for o in range(NUM_PARAMS):
            tran_lmt.writeAction(f"mov_reg2reg X{8+o} X{16+o}")
            tran_lmt.writeAction(f"movwrl X{16+o} {LM_BASE}({LM_PTR},1,0)")

        self.__debug_log(tran_lmt, f"print 'UDSHMEM-UD-Master: Incoming operands: opcode=%ld, src=%ld, dst=%ld, nele=%ld, nworkers=%ld, nlanes=%ld, nuds=%ld'{OPCODE} {SRC} {DST} {NELE} {NWORKERS} {NLANES} {NUDS}")
        UDID = "X16"
        L0ID = "X17"
        UD_LANES = "X18"
        R_UDID = "X19" # relative UDID

        # UDID = NWID >> 6, L0ID = NWID << 6
        tran_lmt.writeAction(f"rshift NWID {UDID} 6") # udid = nwid >> 6 = nwid // 64
        tran_lmt.writeAction(f"lshift {UDID} {L0ID} 6") # L0ID = udid << 6 = udid * 64
        # R_UDID = UDID - START_UDID
        tran_lmt.writeAction(f"sub {UDID} {START_UDID} {R_UDID}")
        self.__debug_log(tran_lmt, level=2, msg=f"print 'start UD master. UDID: %ld, L0ID: %ld, R_UDID: %ld' {UDID} {L0ID} {R_UDID}")
        # if R_UDID < 0, meaning circling back, R_UDID = R_UDID + NUDS
        tran_lmt.writeAction(f"blti {R_UDID} 0 udshmem-ud-master-neg-udid")
        tran_lmt.writeAction(f"jmp udshmem-ud-master-udid-ok")
        tran_lmt.writeAction(f"udshmem-ud-master-neg-udid: add {R_UDID} {NUDS} {R_UDID}")
        
        self.__debug_log(tran_lmt, level=2, msg=f"print 'After adjusting R_UDID. UDID: %ld, L0ID: %ld, R_UDID: %ld' {UDID} {L0ID} {R_UDID}")
        # recyclable registers below
        UD_LANES_FD = "X23"
        UD_LANES_RM = "X24"
        B1, B2 = "X25", "X26"
        TEMP0, TEMP1 = "X27", "X28"

        # tran_lmt.writeAction("print 'checkpoint 1'")
        # UD_LANES = NLANES // NUDS + (UDID < NLANES % NUDS)
        # UD_LANES_FD = NLANES // NUDS
        tran_lmt.writeAction(f"udshmem-ud-master-udid-ok: div {NLANES} {NUDS} {UD_LANES_FD}")
        # self.__floor_div(tran_lmt, UD_LANES_FD, NLANES, NUDS)
        # UD_LANES_RM = NLANES % NUDS
        tran_lmt.writeAction(f"mod {NLANES} {NUDS} {UD_LANES_RM}")
        # UD_LANES = (UDID < UD_LANES_RM ? 1 : 0) + UD_LANES_FD
        tran_lmt.writeAction(f"mov_imm2reg {UD_LANES} 0")
        self.__ternary(tran_lmt, t=UD_LANES, cond=f'bgt {UD_LANES_RM} {R_UDID}', ifTrue=1, ifFalse=0, endLabel='ud-lanes-cont')
        tran_lmt.writeAction(f"ud-lanes-cont: add {UD_LANES} {UD_LANES_FD} {UD_LANES}")
        
        # make sure UD_LANES <= 64; can be optimized 
        tran_lmt.writeAction(f"movir {TEMP0} 64")
        tran_lmt.writeAction(f"ble {UD_LANES} {TEMP0} skip-max-lane") # if ud_lanes <= 64, terminate

        tran_lmt.writeAction(f"mov_imm2reg {UD_LANES} 64")
        tran_lmt.writeAction(f"skip-max-lane: addi {UD_LANES} {UD_LANES} 0") # nop
        # recyle X23, X24, X25, X26

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
        tran_lmt.writeAction(f"mod {NWORKERS} {NUDS} {UD_WORKERS_RM}")
    
        # if UD_WORKERS_RM != 0 or UD_WORKERS_FD != 0: give proper workers
        # UD_WORKERS = UDID < NWORKERS ? 1 : 0

        # UD_WORKERS = (UDID < UD_WORKERS_RM ? 1 : 0) + UD_WORKERS_FD
        tran_lmt.writeAction(f"mov_imm2reg {UD_WORKERS} 0")
 
        self.__ternary(tran_lmt, t=UD_WORKERS, cond=f'bgt {UD_WORKERS_RM} {R_UDID}', ifTrue=1, ifFalse=0, endLabel='ud-workers-cont')
        # self.__debug_log(tran_lmt, f"print 'ud_workers: %ld, ud_workers_fd: %ld, ud_workers_rm: %ld, udid: %ld' {UD_WORKERS} {UD_WORKERS_FD} {UD_WORKERS_RM} {R_UDID}")
        tran_lmt.writeAction(f"ud-workers-cont: add {UD_WORKERS} {UD_WORKERS_FD} {UD_WORKERS}")
        tran_lmt.writeAction(f"blec {UD_WORKERS} 0 lmt_terminate") # if ud_workers <= 0, terminate
        # X25, X26 still useable, recycle X27, X28
        # WIDX_INIT = (NWORKERS // NUDS) * UDID + (UDID < NWORKERS % NUDS ? UDID : NWORKERS % NUDS)
        WIDX_INIT0 = "X27"
        WIDX_INIT1 = "X28"
        WIDX = WIDX_INIT
        # WIDX_INT0 = (NWORKERS // NUDS) * UDID      
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
        tran_lmt.writeAction(f"mod {UD_WORKERS} {UD_LANES} {L_WORKERS_RM}")

        self.__debug_log(tran_lmt, f"print 'UDSHMEM-UD-Master: UDID: %ld, UD master distributing worker threads.' {UDID}")
        self.__perf_log(tran_lmt, f"perflog 1 2 'UDID: %ld, Ud master distributing worker threads.' {UDID}")

        tran_lmt.writeAction(f"mov_reg2reg {L0ID} {T_NWID}") # T_NWID = L0ID
        tran_lmt.writeAction(f"iter-lanes: add {L0ID} {UD_LANES} {MAX_NWID}") # MAX_NWID = L0ID + UD_LANES
        tran_lmt.writeAction(f"ble {MAX_NWID} {T_NWID} iter-lanes-end") # if MAX_NWID <= T_NWID, goto iter-lanes-end
        tran_lmt.writeAction(f"mov_imm2reg {L_WORKERS} 0")  # L_WORKERS = 0
        tran_lmt.writeAction(f"sub {T_NWID} {L0ID} {RELATIVE_NWID}") # RELATIVE_NWID = T_NWID - L0ID
        self.__ternary(tran_lmt, t=L_WORKERS, cond=f'bgt {L_WORKERS_RM} {RELATIVE_NWID}', ifTrue=1, ifFalse=0, endLabel='l-workers-cont') # L_WORKERS = (T_NWID < L_WORKERS_RM ? 1 : 0)
   
        tran_lmt.writeAction(f"l-workers-cont: add {L_WORKERS} {L_WORKERS_FD} {L_WORKERS}") # L_WORKERS = L_WORKERS_FD + L_WORKERS
        tran_lmt.writeAction(f"mov_imm2reg {COUNTER} 0") # COUNTER = 0
        tran_lmt.writeAction(f"iter-lane-workers: ble {L_WORKERS} {COUNTER} iter-next-lane")

        # start worker
        tran_lmt.writeAction(f"evii {EVENT_WORD} {self.event_map['udshmem-start-worker-thread']} 255 {0b0101}")
        tran_lmt.writeAction(f"ev {EVENT_WORD} {EVENT_WORD} {T_NWID} {T_NWID} {0b1000}")
        tran_lmt.writeAction(f"sendr3_wret {EVENT_WORD} {self.event_map['udshmem-notify-worker-complete']} {WIDX} {UD_WORKERS} {UD_WORKERS} {TEMP0} {TEMP1}") # last one is bogus
        # self.__debug_log(tran_lmt, f"print 'L_WORKERS_FD: %ld, L_WORKERS_RM: %ld, T_NWID: %ld, MAX_NWID: %ld, L_WORKERS: %ld, COUNTER: %ld, UD_LANES: %ld, WIDX: %ld' {L_WORKERS_FD} {L_WORKERS_RM} {T_NWID} {MAX_NWID} {L_WORKERS} {COUNTER} {UD_LANES} {WIDX}")
        tran_lmt.writeAction(f"addi {WIDX} {WIDX} 1") # WIDX++
        tran_lmt.writeAction(f"addi {COUNTER} {COUNTER} 1") # COUNTER++
        tran_lmt.writeAction(f"jmp iter-lane-workers") # goto iter-lane-workers
        tran_lmt.writeAction(f"iter-next-lane: addi {T_NWID} {T_NWID} 1") # T_NWID++
        tran_lmt.writeAction(f"jmp iter-lanes") # goto iter-lanes
        tran_lmt.writeAction(f"iter-lanes-end: mov_imm2reg {COMPLETED_WORKERS} 0")
 
        tran_lmt.writeAction(f"yield")
        tran_lmt.writeAction(f"lmt_terminate: sendr_reply {UDID} {UD_WORKERS} {TEMP0}") # isav2.3      
        self.__debug_log(tran_lmt, f"print 'UDSHMEM-UD-Master: No UD workers for this UD, UDID:%ld, UD_WORKERS:%ld' {UDID} {UD_WORKERS}")
        self.__perf_log(tran_lmt, f"perflog 1 8 'No UD workers for this UD, UDID:%ld, UD_WORKERS:%ld' {UDID} {UD_WORKERS}")

        tran_lmt.writeAction(f"yield_terminate")
        # self.trans.append(tran_lmt)
    
      
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
        tran_wc.writeAction(f"addi {COMPLETED_WORKERS} {COMPLETED_WORKERS} 1")
        tran_wc.writeAction(f"ble {UD_WORKERS} {COMPLETED_WORKERS} wc_terminate")    # nworkers >= compeleted workers
        tran_wc.writeAction(f"yield")
        tran_wc.writeAction(f"wc_terminate: sendr_reply {UDID} {UD_WORKERS} {TEMP0}") # isav2.3

        self.__debug_log(tran_wc, f"print 'UDSHMEM-UD-Master: All UD workers done, UDID:%ld, UD_WORKERS:%ld' {UDID} {UD_WORKERS}")
        self.__perf_log(tran_wc, f"perflog 1 6 'All UD workers done, UDID:%ld, UD_WORKERS:%ld' {UDID} {UD_WORKERS}")

        tran_wc.writeAction("yield_terminate")
        # self.trans.append(tran_wc)       
       
       
    def __start_worker_thread(self):
        '''

        '''
        # load from LM
        ELE_SIZE = "X16"
        OPCODE = "X16"
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
        # self.__debug_log(tran0, f"print 'WORKER: start worker thread at NWID=%ld' NWID")
        tran0.writeAction(f"addi X7 X31 {self.lm_base + self.config_offset + self.flag_offset}")
        tran0.writeAction("mov_imm2reg X30 0")
        for o in range(5):
            tran0.writeAction(f"movwlr X31(X30,1,0) X{16+o}")
        self.__debug_log(tran0, level=3, msg= f"print 'WORKER[NWID=%ld]: Incoming operands: opcode=%ld, src=%ld, dst=%ld, nele=%ld, nworkers=%ld' NWID {OPCODE} {SRC} {DST} {NELE} {NWORKERS}")
       
        tran0.writeAction(f"mov_reg2reg X8 {WIDX}")
        self.__perf_log(tran0, f"perflog 1 3 'start-worker-thread=%ld' {WIDX}")
        
       

        # W_NELE = NELE // NWORKERS
        self.__floor_div(tran0, W_NELE_FD, NELE, NWORKERS)

        # W_NELE_RM = NELE % NWORKERS
        tran0.writeAction(f"mod {NELE} {NWORKERS} {W_NELE_RM}")
        tran0.writeAction(f"mov_imm2reg {W_NELE} 0")
        self.__ternary(tran0, W_NELE, f'bgt {W_NELE_RM} {WIDX}', 1, 0, endLabel='t-cont')
        tran0.writeAction(f"t-cont: add {W_NELE} {W_NELE_FD} {W_NELE}")
        # LDPTR = SRC + W_NELE * WIDX + (WIDX < W_NELE_RM ? WIDX : W_NELE_RM)
        # INIT_OFFSETS = (WIDX < W_NELE_RM ? WIDX : W_NELE_RM)
        tran0.writeAction(f"mov_imm2reg {INIT_OFFSETS} 0")
        self.__ternary(tran0, INIT_OFFSETS, f"bgt {W_NELE_RM} {WIDX}", WIDX, W_NELE_RM, endLabel='ldptr0-cont')
        # INIT_OFFSETS += W_NELE * WIDX
        # TEMP = W_NELE_FD * WIDX     
        tran0.writeAction(f"ldptr0-cont: mul {W_NELE_FD} {WIDX} {TEMP}")
        # INIT_OFFSETS = INIT_OFFSETS + TEMP
        tran0.writeAction(f"add {INIT_OFFSETS} {TEMP} {INIT_OFFSETS}")
        # self.__debug_log(tran0, level=2, msg=f"print 'NWID: %ld, WIDX: %ld, W_NELE: %ld, W_NELE_FD: %ld, W_NELE_RM: %ld, INIT_OFFSETS: %ld, TEMP: %ld' NWID {WIDX} {W_NELE} {W_NELE_FD} {W_NELE_RM} {INIT_OFFSETS} {TEMP}")

        # NLEFT_LD = W_NELE
        tran0.writeAction(f"mov_reg2reg {W_NELE} {NLEFT_LD}")
        # NLEFT_ST = W_NELE
        tran0.writeAction(f"mov_reg2reg {W_NELE} {NLEFT_ST}")
        # prepare to start the loop
        W_NELE = "X22"
        LDPTR = "X23"
        STPTR = "X24"
        NLEFT_LD = "X25"
        NLEFT_STR = "X29"
        
        DST_SRC_DIFF = "X28"
        SRC_ALIGNED = "X29"
        NLEFT_LD_ALIGNED = "X30"
        LDPTR_END = "X30"
        EV_WORD = "X31"
        TEMP0, TEMP1 = "X30", "X31"
        OUTGOING_READ = "X17"
        # MAX_OUTGOING_READ = "X16" 
        
        tran0.writeAction(f"lshift {INIT_OFFSETS} {INIT_OFFSETS} {3 + self.ele_shift}")
        
        tran0.writeAction(f"add {SRC} {INIT_OFFSETS} {LDPTR}")
        tran0.writeAction(f"add {DST} {INIT_OFFSETS} {STPTR}")
        tran0.writeAction(f"mov_reg2reg {W_NELE} {NLEFT_STR}")
        tran0.writeAction(f"sub {DST} {SRC} {DST_SRC_DIFF}")
        self.__debug_log(tran0, level=2, msg=f"print 'WORKER[NWID=%ld, WIDX=%ld]:  NWORKER=%ld, W_ELEM=%ld, SRC=%ld, DST=%ld, LDPTR=%ld, STPTR=%ld, INIT_OFFSETS=%ld' NWID {WIDX} {NWORKERS} {W_NELE} {SRC} {DST} {LDPTR} {STPTR} {INIT_OFFSETS}")
        # self.__debug_log(tran0, f"print 'WORKER: worker_nele(W_NELE): %ld, INIT_OFFSET=%ld' {W_NELE} {INIT_OFFSETS}")
        
        # based on the config, choose the right function
        # start from loading max chunk size
        if self.impl == 'basim' or self.impl == 'basim-intelli': 
            # tran0.writeAction(f"mov_imm2reg {MAX_OUTGOING_READ} 32")
            tran0.writeAction(f"mov_imm2reg {OUTGOING_READ} 0") 
            tran0.writeAction(f"lshift {W_NELE} {LDPTR_END} {3 + self.ele_shift}")
            tran0.writeAction(f"add {LDPTR} {LDPTR_END} {LDPTR_END}")
            tran0.writeAction(f"beqi {OPCODE} {self.OPCODE_SHMEM_IGET} udshmem-iget")
            self.__load_first(tran0, max(self.allowed_chunk_sizes), self.ele_size, label="udshmem-get")
            self.__iget_load_first(tran0, max(self.allowed_chunk_sizes), self.ele_size, label="udshmem-iget")
            self.__terminate(tran0)
        elif self.impl == 'ubench-write':
            tran0.writeAction(f"blei {NLEFT_LD} 0 ubench-write-terminate")
            self.__ubenchmarks(tran0, isRead=False)
            self.__terminate(tran0, tlabel="ubench-write-terminate")
        elif self.impl == 'ubench-read':
            tran0.writeAction(f"blei {NLEFT_LD} 0 ubench-read-terminate")
            self.__ubenchmarks(tran0, isRead=True)
            self.__terminate(tran0, tlabel="ubench-read-terminate")
        else:
            print(f"Error: unknown impl {self.impl}")
            exit(1)
        # self.trans.append(tran0)
    
    
    def __start_iget_worker_thread(self):
        '''

        '''
        # load from LM
        ELE_SIZE = "X16"
        OPCODE = "X16"
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

        tran0 = self.state.writeTransition("eventCarry", self.state, self.state, self.event_map['udshmem-start-iget-worker-thread'])
        
       
        # tran0.writeAction(f"mov_imm2reg X31 {self.lm_base + self.flag_offset}")
        # self.__debug_log(tran0, f"print 'start worker thread at NWID=%ld' NWID")
        tran0.writeAction(f"addi X7 X31 {self.lm_base + self.config_offset + self.flag_offset}")
        tran0.writeAction("mov_imm2reg X30 0")
        for o in range(5):
            tran0.writeAction(f"movwlr X31(X30,1,0) X{16+o}")
       
        tran0.writeAction(f"mov_reg2reg X8 {WIDX}")
        self.__perf_log(tran0, f"perflog 1 3 'start-worker-thread=%ld' {WIDX}")
        
       

        # W_NELE = NELE // NWORKERS
        self.__floor_div(tran0, W_NELE_FD, NELE, NWORKERS)

        # W_NELE_RM = NELE % NWORKERS
        tran0.writeAction(f"mod {NELE} {NWORKERS} {W_NELE_RM}")
        tran0.writeAction(f"mov_imm2reg {W_NELE} 0")
        self.__ternary(tran0, W_NELE, f'bgt {W_NELE_RM} {WIDX}', 1, 0, endLabel='t-cont')
        tran0.writeAction(f"t-cont: add {W_NELE} {W_NELE_FD} {W_NELE}")
        # LDPTR = SRC + W_NELE * WIDX + (WIDX < W_NELE_RM ? WIDX : W_NELE_RM)
        # INIT_OFFSETS = (WIDX < W_NELE_RM ? WIDX : W_NELE_RM)
        tran0.writeAction(f"mov_imm2reg {INIT_OFFSETS} 0")
        self.__ternary(tran0, INIT_OFFSETS, f"bgt {W_NELE_RM} {WIDX}", WIDX, W_NELE_RM, endLabel='ldptr0-cont')
        # INIT_OFFSETS += W_NELE * WIDX
        # TEMP = W_NELE_FD * WIDX     
        tran0.writeAction(f"ldptr0-cont: mul {W_NELE_FD} {WIDX} {TEMP}")
        # INIT_OFFSETS = INIT_OFFSETS + TEMP
        tran0.writeAction(f"add {INIT_OFFSETS} {TEMP} {INIT_OFFSETS}")
        # self.__debug_log(tran0, f"print 'WIDX: %ld, W_NELE: %ld, W_NELE_FD: %ld, W_NELE_RM: %ld, INIT_OFFSETS: %ld, TEMP: %ld' {WIDX} {W_NELE} {W_NELE_FD} {W_NELE_RM} {INIT_OFFSETS} {TEMP}")

        # NLEFT_LD = W_NELE
        tran0.writeAction(f"mov_reg2reg {W_NELE} {NLEFT_LD}")
        # NLEFT_ST = W_NELE
        tran0.writeAction(f"mov_reg2reg {W_NELE} {NLEFT_ST}")
        # prepare to start the loop
        W_NELE = "X22"
        LDPTR = "X23"
        STPTR = "X24"
        DST_SRC_DIFF = "X28"
        NLEFT_STR = "X29"
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
        if self.impl == 'basim': 
            # tran0.writeAction(f"mov_imm2reg {MAX_OUTGOING_READ} 32")
            tran0.writeAction(f"mov_imm2reg {OUTGOING_READ} 0") 
            tran0.writeAction(f"lshift {W_NELE} {LDPTR_END} {3 + self.ele_shift}")
            tran0.writeAction(f"add {LDPTR} {LDPTR_END} {LDPTR_END}")
            self.__load_first(tran0, max(self.allowed_chunk_sizes), self.ele_size)
        else:
            print(f"Error: unknown impl {self.impl}")
            exit(1)
        self.trans.append(tran0)
    

    def __terminate(self, tran, tlabel="terminate"):
        WIDX = "X21"
        TEMP = "X30"
        
        # FIXIME: since assembler will ignore this, we need this bogus line to make sure the label can be reached
        tran.writeAction(f"{tlabel}: addi {WIDX} {WIDX} 0") 
        # self.__perf_log(tran, f"perflog 1 5 'Worker Read/write ends, NWID=%ld, WIDX=%ld' NWID {WIDX}")
        self.__perf_log(tran, f"perflog 1 {pmap['worker-ends']} 'Worker ends, NWID=%ld, WIDX=%ld' NWID {WIDX}")
        tran.writeAction(f"sendr_reply NWID {WIDX} {TEMP}") #TODO: need to change according to spec
        tran.writeAction(f"yieldt")
    
    
    def __load_first(self, tran, C, E, label="udshmem-get"):
        # C: chunk size; E: element size in word
        LDPTR = "X23"
        NLEFT_LD = "X25"
        BYTES_LEFT = "X27"
        WIDX = "X21"
        MAX_OUTGOING_READ = "X16"
        
        # self.__debug_log(tran, f"print 'basim: NWID=%ld, next_chunk_{C}_{E}' NWID")
        tran.writeAction(f"movir {MAX_OUTGOING_READ} 32")
        tran.writeAction(f"{label}: blec {NLEFT_LD} 0 terminate") # if no elems at the begining, terminate
        self.__load_next(tran, C, E)
        tran.writeAction(f"yield")
        
            
    def __load_next(self, tran, C, E):
        LDPTR = "X23"
        NLEFT_LD = "X25"
        WIDX = "X21"
        WORDS_LEFT = "X27"
        OUTGOING_READ = "X17"
        TEMP0, TEMP1 = "X30", "X31"
        tran.writeAction(f"next_chunk_{C}_{E}: blec {NLEFT_LD} 0 done")
        tran.writeAction(f"lshift {NLEFT_LD} {WORDS_LEFT} {self.ele_shift}")
        # self.__debug_log(tran, f"print 'WORDS_LEFT=%ld, C={C}, E={E}' {WORDS_LEFT}")
        tran.writeAction(f"blec {WORDS_LEFT} {C-1} next_chunk_{self.__NEXT_CHUNK(C)}_{E}")
        if C <= 8:
            # self.__debug_log(tran, f"print 'next_event=udshmem-load-store-loop-{C}; NLEFT_LD=%ld; LDPTR=%ld' {NLEFT_LD} {LDPTR}")
            tran.writeAction(f"send_dmlm_ld_wret {LDPTR} {self.event_map[f'udshmem-load-store-loop-{C}']} {C} {TEMP0}")
            tran.writeAction(f"addi {LDPTR} {LDPTR} {C * 8}") # dram read/write still uses bytes
        else:
            for i in range(C // 8):
                tran.writeAction(f"send_dmlm_ld_wret {LDPTR} {self.event_map[f'udshmem-load-store-loop-{C}']} 8 {TEMP0}")
                tran.writeAction(f"addi {LDPTR} {LDPTR} 64") # dram read/write still uses bytes
        tran.writeAction(f"subi {NLEFT_LD} {NLEFT_LD} {C >> self.ele_shift}")
        tran.writeAction(f"addi {OUTGOING_READ} {OUTGOING_READ} {C // 8 if C > 8 else 1}")
        # self.__debug_log(tran, f"print 'basim: NWID=%ld, outgoing_read=%ld' NWID {OUTGOING_READ}")
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
        if self.perflog:
            tran.writeAction(f"beq {NLEFT_ST} {W_NELE} ack-first")
            self.__perf_log(tran, f"ack-first: perflog 1 {perflog_map['start-worker-ack']} 'Ack start[NWID=%ld], WIDX=%ld' NWID {WIDX}")
        tran.writeAction(f"subi {NLEFT_ST} {NLEFT_ST} {C >> self.ele_shift}")
        # self.__debug_log(tran, f"print 'ack: NWID=%ld, NLEFT_ST=%ld' NWID {NLEFT_ST}")
        tran.writeAction(f"blec {NLEFT_ST} 0 ack_terminate")
        tran.writeAction(f"yield")
        # label is in the termniate
        if self.perflog:
            tran.writeAction(f"ack_terminate: perflog 1 {perflog_map['end-worker-rw']} 'Ack end[NWID=%ld], WIDX=%ld' NWID {WIDX}")
            self.__terminate(tran, "ack_term")
        else:
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
        # self.__debug_log(tran, f"print 'read-returns {C} {E}'")
        tran.writeAction(f"add {RETURN_ADDR_REG} {DST_SRC_DIFF} {STPTR}")
        # tran.writeAction(f"subi {NLEFT_STR} {NLEFT_STR} {chunk_size >> self.ele_shift}")
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
    
    #================INTELLIGENT IMPLEMETATION END===================
       
        
    def __iget_load_first(self, tran, C, E, label="udshmem-iget"):
        # C: chunk size; E: element size in word
        LDPTR = "X23"
        NLEFT_LD = "X25"
        BYTES_LEFT = "X27"
        WIDX = "X21"
        
        # self.__debug_log(tran, f"print 'basim: NWID=%ld, next_chunk_{C}_{E}' NWID")
        tran.writeAction(f"{label}: blec {NLEFT_LD} 0 terminate")
        # self.__load_next(tran, C, E)
        self.__debug_log(tran, f"print 'udshmem-iget: NWID=%ld, next_chunk_{C}_{E}' NWID")
        tran.writeAction(f"yield")
        # self.__terminate(tran)
    
    
    def __iget_load_next(self, tran, C, E):
        pass
    

    #================UDSHMEM INTELLIGENT SHMEM BLOCK-BASED START=============#
    
    def __ev_intelli_shmem_node_block(self):
        """
        input:
        src, dst, nelems, lognnodes, lognstacks, lognuds, lognlanes, nodebsize
        These are supposed to be consistent the ones in the config
        """
        
        def nodeid(tran, addr_reg, base_reg, blocksize_reg, result_reg, temp0_reg,label=None):
            if label:
                tran.writeAction(f"{label}: sub {addr_reg} {base_reg} {temp0_reg}")
            else:
                tran.writeAction(f"sub {addr_reg} {base_reg} {temp0_reg}")
            tran.writeAction(f"div {temp0_reg} {blocksize_reg} {result_reg}")
            
        def abs(tran, x, y, label="post-abs"):
            label_neg_x = f"neg-x-{str(time.time() * 1000)}"
            tran.writeAction(f"blti {x} 0 {label_neg_x}")
            tran.writeAction(f"addi {x} {x} 0")
            tran.writeAction(f"jmp {label}")
            tran.writeAction(f"{label_neg_x}: neg {x} {x}")
            tran.writeAction(f"movir {y} 0")
            tran.writeAction(f"sub {y} {x} {y}")
        
        def totalBlocks(tran, nelems, nodebsize, result_reg, temp0_reg, temp1_reg, temp2_reg):
            # totalBlocks = nelems * 8 // nodebsize
            # remainder = nelems * 8 % nodebsize
            # if remainder > 0 and remainder < nelems * 8: totalBlocks += 1
            tran.writeAction(f"sli {nelems} {temp1_reg} 3") # temp1 = nelems * 8
            tran.writeAction(f"div {temp1_reg} {nodebsize} {result_reg}") # totalBlocks = temp1 // nodebsize
            tran.writeAction(f"subi {nodebsize} {temp0_reg} 1") # temp0 = nodebsize - 1
            tran.writeAction(f"and {temp0_reg} {temp1_reg} {temp2_reg}") # remainder = temp1 % (nodebsize - 1)
            tran.writeAction(f"bnei {temp2_reg} 0 check-if-one-more-block") # if remainder != 0 and remainder < nelems * 8: totalBlocks += 1
            tran.writeAction(f"check-if-one-more-block: ble {temp1_reg} {temp2_reg} no-more-block") # if nelems * 8 <= remainder: skip
            tran.writeAction(f"addi {result_reg} {result_reg} 1") # totalBlocks += 1
            tran.writeAction(f"no-more-block: addi {result_reg} {result_reg} 0")
   
            
        # Master thread redirect calculated infos to the startnode's ud0
        # 
        # nnodes = totalBlocks if totalBlocks < nnodes else maxnodes
        # startNodeId = ((src-base) // blocksize) % nnodes
        # blocksize = blocksize
        # nodeNBlocks = totalBlocks // nnodes
        # src_dst_diff = dst - src
        # stripe = blocksize * nnodes
        # then send the info to the startnode
        # for i in range(nnodes):
        # rnodeid = i
        # rnwid = rnodeid << 11
        # tnwid = (rnwid + startNode<<11) % (maxnnodes << 11)
        # send src, src_dst_diff, nelems, rnwid, nnodes ; calculated: lognuds, lognlanes, lognworkers
        
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.event_map['udshmem-nodeblock-intelli-init'])
        src_ob = "X8"
        dst_ob = "X9"
        nelems_ob = "X10"
        
        expected = "X16"
        count = "X17"
        NUMNODES = "X"
        NUMSTACKS = "X"
        NUMUDS = "X"
        NUMLANES = "X"
        GMAP_MEM_BASE = "X"
        MAP_MEM_BASE = "X"
        NODE_BLOCK_SIZE = "X"
        
        src = "X"
        dst = "X"
        nelems = "X"
        nnodes = "X"
        start_node_id = "X"
        
        src_dst_diff = "X"
        mode = "X"
        total_blocks = "X"
        lm_base = "X"
        lm_ptr = "X"
        tmp0 = "X"
        rnwid = "X"
        rnodeid = "X"
        tnwid = "X"
        lognuds = "X"
        lognlanes = "X"
        lognworkers = "X"
        evw = "X"
        # request the config
        self.__debug_log(tran, level=3, msg=f"print 'LIB-ROOT: System Configuration: numnodes=%ld, numstacks=%ld, numuds=%ld, nlanes=%ld.' {NUMNODES} {NUMSTACKS} {NUMUDS} {NUMLANES}")
        self.__debug_log(tran, level=3,  msg=f"print 'LIB-ROOT: System Configuration: gmap_mem_base=%ld, map_mem_base=%ld, node_block_size=%ld.' {GMAP_MEM_BASE} {MAP_MEM_BASE} {NODE_BLOCK_SIZE}")
        tran.writeAction(f"addi X7 {lm_base} {self.lm_base}")
        tran.writeAction(f"movir {lm_ptr} 0")
        tran.writeAction(f"movwlr {lm_base}({lm_ptr},1,0) {NUMNODES}")
        tran.writeAction(f"movwlr {lm_base}({lm_ptr},1,0) {NUMSTACKS}")
        tran.writeAction(f"movwlr {lm_base}({lm_ptr},1,0) {NUMUDS}")
        tran.writeAction(f"movwlr {lm_base}({lm_ptr},1,0) {NUMLANES}")
        tran.writeAction(f"movwlr {lm_base}({lm_ptr},1,0) {GMAP_MEM_BASE}")
        tran.writeAction(f"movwlr {lm_base}({lm_ptr},1,0) {MAP_MEM_BASE}")
        tran.writeAction(f"movwlr {lm_base}({lm_ptr},1,0) {NODE_BLOCK_SIZE}")
        tran.writeAction(f"beqi {NUMNODES} 0 udshmem-nodeblock-intelli-init-error")
        

        self.__debug_log(tran, level=4, msg=f"print 'LIB-ROOT: total_blocks=%ld' {total_blocks}")
        
        # calculate startNodeID
        tran.writeAction(f"movir {mode} 0")
        tran.writeAction(f"blt {src_ob} {GMAP_MEM_BASE} udshmem-src-local")
        tran.writeAction(f"ori {mode} {mode} 1") # src is global
        tran.writeAction(f"udshmem-src-local: ori {mode} {mode} 0") # src is local
        tran.writeAction(f"blt {dst_ob} {GMAP_MEM_BASE} udshmem-dst-local")
        tran.writeAction(f"ori {mode} {mode} 2") # dst is global
        
        tran.writeAction(f"beqi {mode} 3 udshmem-all-global")
        tran.writeAction(f"movir {nnodes} 1")
        tran.writeAction(f"mov_reg2reg X0 {start_node_id}") # start_node_id = nwid
        tran.writeAction(f"sri {start_node_id} {start_node_id} 11") # start_node_id = nwid >> 11
        self.__debug_log(tran, level=4, msg=f"print 'LIB-ROOT: local mode start_node_id=%ld' {start_node_id}")
        tran.writeAction(f"jmp udshmem-nnodes-cont")
        # udshmem-all-global: calculate nnodes and totalblocks
        tran.writeAction(f"udshmem-all-global: mov_reg2reg {NUMNODES} {nnodes}")
        totalBlocks(tran, nelems_ob, NODE_BLOCK_SIZE, total_blocks, "X", "X", "X")
        tran.writeAction(f"bgt {total_blocks} {nnodes} udshmem-totalblocks-gt-nnodes")
        tran.writeAction(f"mov_reg2reg {total_blocks} {nnodes}")
        nodeid(tran, src_ob, GMAP_MEM_BASE, NODE_BLOCK_SIZE, start_node_id, tmp0,"udshmem-totalblocks-gt-nnodes")
        tran.writeAction(f"udshmem-nnodes-cont: sub {dst_ob} {src_ob} {src_dst_diff}")
        # calculate lognuds, lognlanes, lognworkers
        
        # just hardcode the values
        tran.writeAction(f"movir {lognuds} 2")
        tran.writeAction(f"movir {lognlanes} 6")
        tran.writeAction(f"movir {lognworkers} 0")
        
        # send the event to the nodes
        tran.writeAction(f"movir {rnodeid} 0")
        tran.writeAction(f"evii {evw} {self.event_map['udshmem-nodeblock-intelli-node']} 255 {0b0101}")
        tran.writeAction(f"udshmem-nodes-loop: blt {rnodeid} {nnodes} udshmem-nodes-loop-done")
        tran.writeAction(f"sli {rnodeid} {rnwid} 11")
        tran.writeAction(f"add {rnodeid} {start_node_id} {tmp0}")
        tran.writeAction(f"mod {tmp0} {nnodes} {tnwid}")
        tran.writeAction(f"sli {tnwid} {tnwid} 11")
        tran.writeAction(f"ev {evw} {evw} {tnwid} {tnwid} {0b1000}")
        tran.writeAction(f"send_wret {evw} {self.event_map['udshmem-nodeblock-intelli-join']}")
        tran.writeAction(f"addi {rnodeid} {rnodeid} 1")
        tran.writeAction(f"jmp udshmem-nodes-loop")
        tran.writeAction(f"udshmem-nodes-loop-done: movir {expected} {nnodes}")
        tran.writeAction(f"movir {count} 0")
        tran.writeAction(f"yield")
        tran.writeAction(f"udshmem-nodeblock-intelli-init-error: print 'Error: numnodes=0!'")
        tran.writeAction(f"yieldt")
        
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.event_map['udshmem-nodeblock-intelli-join'])
        tran.writeAction(f"addi {count} {count} 1")
        tran.writeAction(f"ble {expected} {count} udshmem-nodeblock-intelli-join-done")
        tran.writeAction(f"yield")
        tran.writeAction(f"udshmem-nodeblock-intelli-join-done: sendr_reply X31 X30 X29")
        tran.writeAction(f"yieldt")
        

        # Node thread: distribute infos to all the stacks
        # get src, sr_dst_diff, nelems, rnwid, nnodes, nlogstacks, nloguds, nloglanes
        # for i in range(1 << lognstacks=8):
        # rstackid = i & mask; mask = (1 << lognstacks) - 1
        # rrnwid = rnwid + rstackid << 8
        # tnwid = (NWID + rrnwid) % (maxnnodes << 11)
        # send src, src_dst_diff, nelems, rrnwid, nnodes, lognuds, lognlanes, lognworkers
        
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.event_map['udshmem-nodeblock-intelli-node'])
        expected = "X16"
        count = "X17"
        NODEBSIZE = "X"
        src =  "X"
        src_dst_diff = "X"
        nelems = "X"
        nwid = "X"
        rnwid = "X"
        rrnwid = "X"
        rstackid = "X"
        tnwid = "X"
        nnodes = "X"
        lognuds = "X"
        lognlanes = "X"
        lognworkers = "X"
        NLOGSTACKS = "X"
        nstacks = "X"
        i = "X"
        evw = "X"
        tmp = "X"
        lmptr = "X"
        tmp0 = "X"
        tmp1 = "X"
     
        tran.writeAction(f"movir {NLOGSTACKS} 3")
        tran.writeAction(f"movir {nstacks} 1")
        tran.writeAction(f"sl {nstacks} {NLOGSTACKS} {nstacks}")
        tran.writeAction(f"movir {rstackid} 0")
        tran.writeAction(f"mov_reg2reg NWID {nwid}")
        tran.writeAction(f"evii {evw} {self.event_map['udshmem-nodeblock-intelli-stack']} 255 {0b0101}")
        tran.writeAction(f"udshmem-node-stack-loop: ble {nstacks} {rstackid} udshmem-node-stack-loop-done")
        tran.writeAction(f"sli {rstackid} {tmp} 8")
        tran.writeAction(f"add {tmp} {rnwid} {rrnwid}") # this rnwid will always be the ud0 of a node
        # move it to the correct LM and then send
        tran.writeAction(f"add {tmp} {nwid} {tnwid}") # so it will not exceed the 
        tran.writeAction(f"ev {evw} {evw} {tnwid} {tnwid} {0b1000}")
        tran.writeAction(f"send_wret {evw} {self.event_map['udshmem-nodeblock-intelli-join']} {lmptr} 8 {tmp0}")
        tran.writeAction(f"addi {rstackid} {rstackid} 1")
        tran.writeAction(f"jmp udshmem-node-stack-loop")
        tran.writeAction(f"udshmem-node-stack-loop-done: mov_reg2reg {nstacks} {expected}")
        tran.writeAction(f"movir {count} 0")
        tran.writeAction(f"yield")
            
        
        # Stack thread: distribute infos to all the uds
        # get src, src_dst_diff, nelems, rrnwid, nnodes, lognuds, lognlanes, lognworkers
        # totalBlocks = totalBlocks(src, src+nelems*8, BASE, NODEBSIZE, totalBlocks, temp0)
        # nrnodeid = rrnwid >> 11
        # nrstackid = rrnwid >> 8 & mask; mask = (1 << lognstacks) - 1
        # stack_src_start = src + nrnodeid*nodebsize + nrstackid*(nodebsize>>lognstacks)
        # stripe = NODEBSIZE * nnodes
        # for i in range(1 << lognuds):
        # rudid = i & mask; mask = (1 << lognuds) - 1
        # rrrnwid = rrnwid + rudid << 6
        # tnwid = nwid>>11<<11 + rrrnwid
        # send stack_src, dst_src_diff, nelems, rrrnwid, nnodes, lognuds, lognlanes, lognworkers, stripe (rlaneid, nworkerid, rblockid)
        
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.event_map['udshmem-nodeblock-intelli-stack'])
        src = "X"
        dst_src_diff = "X"
        nelems = "X"
        rrnwid = "X"
        nnodes = "X"
        lognuds = "X"
        lognlanes = "X"
        lognworkers = "X"
        
        expected = "X16"
        count = "X17"
        mask = "X"
        rrrnwid = "X"
        nrnodeid = "X"
        nrstackid = "X"
        nuds = "X"
        rudid = "X"
        nwid = "X"
        tmp = "X"
        tnwid = "X"
        evw = "X"
        tmp0 = "X"
        lmptr = "X"
        stack_src_start = "X"
        NLOGSTACKS = "X"
        tran.writeAction(f"sri {rrnwid} {nrnodeid} 11")
        tran.writeAction(f"srandii {rrnwid} {nrstackid} 8 {0b111}") # nstacks is fixed to 8, because we will move block by block
        tran.writeAction(f"movir {nuds} 1")
        tran.writeAction(f"sl {nuds} {lognuds} {nuds}")
        tran.writeAction(f"movir {rudid} 0")
        tran.writeAction(f"mov_reg2reg NWID {nwid}")
        tran.writeAction(f"evii {evw} {self.event_map['udshmem-nodeblock-intelli-ud']} 255 {0b0101}")
        tran.writeAction(f"udshmem-node-ud-loop: ble {nuds} {rudid} udshmem-node-ud-loop-done")
        tran.writeAction(f"sli {rudid} {tmp} 6")
        tran.writeAction(f"add {tmp} {rrnwid} {rrrnwid}")
        # move it to the correct LM and then send
        tran.writeAction(f"add {tmp} {nwid} {tnwid}")
        tran.writeAction(f"ev {evw} {evw} {tnwid} {tnwid} {0b1000}")
        tran.writeAction(f"send_wret {evw} {self.event_map['udshmem-nodeblock-intelli-join']} {lmptr} 8 {tmp0}")
        tran.writeAction(f"addi {rudid} {rudid} 1")
        tran.writeAction(f"jmp udshmem-node-ud-loop")
        tran.writeAction(f"udshmem-node-ud-loop-done: movir {expected} {nuds}")
        tran.writeAction(f"movir {count} 0")
        tran.writeAction(f"yield")


        # UD thread: start the worker threads
        # rudid = rrrnwid >> 6 & mask; mask = (1 << lognuds) - 1
        # ud_src_start = stack_src_start + rudid * (NODEBSIZE>>(lognuds+lognstacks))
        # for i in range(1 << lognlanes):
        # rlaneid = i & mask; mask = (1 << lognlanes) - 1
        # rrrrnwid = rrrnwid + rlaneid << 3
        # tnwid = nwid>>11<<11 + rrrrnwid
        # lwidx = 0
        # for i in range(1 << (lognworkers + lognlanes)):
        # 
        # lwidx = rlaneid << lognworkers + i
        # send ud_src_start, dst_src_diff, nelems, lwidx, nnodes, lognuds, lognlanes, lognworkers, stripe, rlaneid, nworkerid, rblockid
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.event_map['udshmem-nodeblock-intelli-ud'])
        stack_src_start = "X"
        dst_src_diff = "X"
        nelems = "X"
        rrrnwid = "X"
        nnodes = "X"
        lognuds = "X"
        lognlanes = "X"
        lognworkers = "X"
        
        rudid = "X"
        rlaneid = "X"
        mask = "X"
        tran.writeAction(f"sri {rrrnwid} {nrnodeid} 11")
        tran.writeAction(f"srandii {rrrnwid} {nrstackid} 8 {0b111}") # nstacks is fixed to 8, because we will move block by block
        tran.writeAction(f"sri {rrrnwid} {rudid} 6")
        tran.writeAction(f"movir {mask} 1")
        tran.writeAction(f"sl {mask} {lognuds} {mask}")
        tran.writeAction(f"subi {mask} {mask} 1")
        tran.writeAction(f"and {rudid} {mask} {rudid}")
        tran.writeAction(f"movir {mask} 1")
        
        
     
        # Worker thread:
        # wnelems = nelems >> ((lognworkers + lognstacks + lognuds + lognlanes) * nnodes)
        # wsrc = ud_src_start + lwidx * wnelems * 8
        expected = "X16"
        count = "X17"
        NODEBSIZE = "X"
        LOGNSTACKS = "X"
        wsrc =  "X"
        sddiff = "X"
        wnelems = "X"
        nnodes = ""
        stride = "X" # stride = BNODESIZE * nnodes
        stack_stripe = "X"
        stripe_mask = "X"
        nleft_ld = "X"
        nleft_st = "X"
        lwidx = "X"
        rldptr = "X"
        ldptr = "X"
        stptr = "X"
        words_left = "X"
        num_sent = "X"
        temp0 = "X"
        temp1 = "X"
        
        
        tran.writeAction(f"mul {NODEBSIZE} {nnodes} {stride}") # in bytes
        tran.writeAction(f"sr {NODEBSIZE} {LOGNSTACKS} {stack_stripe}") # in bytes
        tran.writeAction(f"subi {stack_stripe} {stripe_mask} 1")
        
        
        def load_first(tran, C, E, label="udshmem-intelli-read"):
            tran.writeAction(f"{label}: blei {nleft_ld} 0 udshmem-intelli-terminate")
            load_next(tran, C, E)
            tran.writeAction(f"yield")
            
        def load_next(tran, C, E):
            tran.writeAction(f"next_chunk_{C}_{E}: blei {nleft_ld} 0 done")
            tran.writeAction(f"sli {nleft_ld} {words_left} {self.ele_shift}")
            tran.writeActionf(f"blei {words_left} {C-1} next_chunk_{self.__NEXT_CHUNK(C)}_{E}")
            if C <=8:
                tran.writeAction(f"add {rldptr} {wsrc} {ldptr}")
                tran.writeAction(f"send_dmlm_ld_wret {ldptr} {self.event_map['udshmem-intelli-write-read']} {C} {temp0}")
                tran.writeAction(f"addi {rldptr} {rldptr} {C<<3}")
                # if rldptr > 0 and rldptr % stacksize == 0: rldptr = 0, wsrc += stride 
                tran.writeAction(f"andi {rldptr} {stack_stripe} {temp0}") # temp0 = rldptr % stack_stripe
                tran.writeAction(f"beqi {temp0} 0 check-addr-overflow_{C}_{E}")
                tran.writeAction(f"jmp cont-{C}_{E}")
                tran.writeAction(f"check-addr-overflow_{C}_{E}: bgti {rldptr} 0 next-stride_{C}_{E}")
                tran.writeAction(f"jmp cont-{C}_{E}")
                tran.writeAction(f"next-stride_{C}_{E}: add {wsrc} {wsrc} {stride}")
            else:
                for i in range(C // 8):
                    pass
            tran.writeAction(f"cont-{C}_{E}: subi {nleft_ld} {nleft_ld} {C>>self.ele_shift}")
            tran.writeAction(f"addi {num_sent} {num_sent} {C // 8 if C > 8 else 1}")
            if C!=1:
                load_next(tran, self.__NEXT_CHUNK(C), E)
            else:
                tran.writeAction(f"done: yield")
        
        def ev_write_read(C, E):
            chunk_size = C if C <= 8 else 8
            RETURN_ADDR_REG = 'X' + str((chunk_size + 8) if chunk_size < 8 else 3)
            tran = self.state.writeTransition("eventCarry", self.state, self.state, self.event_map[f'udshmem-intelli-write-read-{C}-{E}'])
            tran.writeAction(f"add {RETURN_ADDR_REG} {sddiff} {stptr}")
            tran.writeAction(f"sendops_dmlm_wret {stptr} {self.event_map[f'udshmem-intelli-ack-{chunk_size}']} X8 {chunk_size} {temp0}")
            tran.writeAction(f"bgti {num_sent} 32 wait")
            tran.writeAction(f"blei {nleft_ld} 0 no_more_reads")
            load_next(tran, C, E)
            tran.writeAction(f"no_more_reads: yield")
            tran.writeAction(f"wait_next: yield")
            
        def ev_ack(C):
            chunk_size = C if C <= 8 else 8
            tran = self.state.writeTransition("eventCarry", self.state, self.state, self.event_map[f'udshmem-intelli-ack-{C}'])
            tran.writeAction(f"subi {nleft_st} {nleft_st} {chunk_size >> self.ele_shift}")
            tran.writeAction(f"blei {nleft_st} 0 udshmem-intelli-ack-terminate")
            tran.writeAction(f"yield")
            
            if self.perflog:
                tran.writeAction(f"udshmem-intelli-ack-terminate: perflog 1 {perflog_map['end-worker-rw']} 'Worker ends, NWID=%ld, WIDX=%ld' NWID {lwidx}")
                __join(tran, "ack-term")
            else:
                __join(tran, tlabel="udshmem-intelli-ack-terminate")
                
        def __join(tran, tlabel="terminate"):
            tran.writeAction(f"{tlabel}: addi {lwidx} {lwidx} 0") 
            self.__perf_log(tran, f"perflog 1 5 'Worker Read/write ends, NWID=%ld, WIDX=%ld' NWID {lwidx}")
            tran.writeAction(f"sendr_reply NWID {lwidx} {lwidx}") #TODO: need to change according to spec
            tran.writeAction(f"yieldt")
            
    # endregion
            
                    
    
    #================UDSHMEM INTELLIGENT SHMEM BLOCK-BASED ENDS=============#
    
    def __impl_locality_aware_shmem(self):
        
        pass