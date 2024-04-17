
# Locality-Aware UD SHMEM
import math
from Utils import EventMap, Register, AdvancedRegister, RegPrinter, pmap

class WorkEstimator:
    def __init__(self, k, b, maxlog2nworkers=6) -> None:
        self.k = k # coeff
        self.b = b # bias
        self.maxlog2nworkers = maxlog2nworkers
    
    def genEstimateActions(self, thr: AdvancedRegister, thrprint: RegPrinter, impl='linear'):
        if impl == 'linear':
            return self._linear(thr, thrprint)
        else: 
            return self._naive(thr, thrprint)
    
    def _naive(self, thr: AdvancedRegister, thrprint: RegPrinter):
       
        print(thr)
        actions =[
            f"sri {thr.nchunks} {thr.log2nworkers} 2",
            f"blei {thr.log2nworkers} 6 launch-ud",
            f"movir {thr.log2nworkers} 6",  
        ]
        return actions
    
    def _linear(self, thr: AdvancedRegister, thrprint: RegPrinter):
        '''
        Estimator, linear, naive implementation:
            log2nworkers = K * (log2nchunk - B)
            log2nworkers = K * log2(nchunks>>b)
            log2nworkers = log2(nchunks>>b) >> k
            # why only rightshift? because it the nchunks/nworkers would be huge, since each lanes capacity is huge
            log2nchunks = findmaxbits(nchunk)
        andi len($len)=16, 5 regs available
        log2nworkers = 0
        bitmask16 = 0xffff
        high16bits = bitmask << 16
        high32bits = (high16bits + bitmask16) << 32
        //free bitmask16
        prev = nchunks
        tmp = prev
        
        skiphigh64bit: tmp = high32bits & prev
        beqi tmp 0 skip-high32bits
        prev = prev >> 32
        log2nworker += 32
        skip-high32bits: tmp = high16bits & prev
        beqi tmp 0 skip-high16bits
        prev = prev >> 16
        log2nworker += 16
        skip-high16bits: tmp = prev & 0xff00
        beqi tmp 0 skip-high8bits
        prev = prev >> 8
        log2nworker += 8
        skip-high8bits: tmp = prev & 0xf0 # 1111 0000
        beqi tmp 0 skip-high4bits
        prev = prev >> 4
        log2nworker += 4
        skip-high4bits: tmp = prev & 0xc # 1100
        beqi tmp 0 skip-high2bits
        prev = prev >> 2
        log2nworker += 2
        skip-high2bits: tmp = prev & 0x2  # 10
        beqi tmp 0 skip-high1bits
        prev = prev >> 1
        log2nworker += 1
        
        '''
        thr.bitmask16 = 'alloc'
        thr.high16bits = 'alloc'
        thr.high32bits = 'alloc'
        thr.prev = 'alloc'
        thr.t = 'alloc'
        
        actions = [
            f"movir {thr.log2nworkers} 0",
            f"movir {thr.bitmask16} {0xffff}",
            f"sli {thr.bitmask16} {thr.high16bits} 16", # 0xffff0000
            f"add {thr.bitmask16} {thr.high16bits} {thr.high32bits}", # 0xffffffff = 0xffff0000 + 0xffff
            f"sli {thr.high32bits} {thr.high32bits} 32", # 0xffffffff00000000
            (2, thrprint.printr("high32bits:", [thr.high32bits, thr.high16bits, thr.bitmask16])),
        ]
        thr.free([thr.bitmask16])
        actions += [
            f"sri {thr.nchunks} {thr.prev} {self.b}",  # nchunks >> b, so that the highbits we get is smaller, since the range is only 1-6
            f"and {thr.high32bits} {thr.prev} {thr.t}",
            f"beqi {thr.t} 0 skip-high32bits",
            f"sri {thr.prev} {thr.prev} 32",
            f"addi {thr.log2nworkers} {thr.log2nworkers} 32",
            f"skip-high32bits: and {thr.high16bits} {thr.prev} {thr.t}",
            f"beqi {thr.t} 0 skip-high16bits",
            f"sri {thr.prev} {thr.prev} 16",
            f"addi {thr.log2nworkers} {thr.log2nworkers} 16",
            f"skip-high16bits: andi {thr.prev} {thr.t} {0xff00}",
            f"beqi {thr.t} 0 skip-high8bits",
            f"sri {thr.prev} {thr.prev} 8",
            f"addi {thr.log2nworkers} {thr.log2nworkers} 8",
            f"skip-high8bits: andi {thr.prev} {thr.t} {0xf0}",
            f"beqi {thr.t} 0 skip-high4bits",
            f"sri {thr.prev} {thr.prev} 4",
            f"addi {thr.log2nworkers} {thr.log2nworkers} 4",
            f"skip-high4bits: andi {thr.prev} {thr.t} {0xc}",
            f"beqi {thr.t} 0 skip-high2bits",
            f"sri {thr.prev} {thr.prev} 2",
            f"addi {thr.log2nworkers} {thr.log2nworkers} 2",
            f"skip-high2bits: andi {thr.prev} {thr.t} {0x2}",
            f"beqi {thr.t} 0 skip-high1bits",
            f"sri {thr.prev} {thr.prev} 1",
            f"addi {thr.log2nworkers} {thr.log2nworkers} 1",
            (2, thrprint.printr("log2nworkers:", [thr.log2nworkers, thr.nchunks])),
            f"skip-high1bits: sri {thr.log2nworkers} {thr.log2nworkers} {self.k}",
            f"blei {thr.log2nworkers} {self.maxlog2nworkers} launch-ud",
            f"movir {thr.log2nworkers} {self.maxlog2nworkers}",
            (2, thrprint.printr("cap-log2nworkers:", [thr.log2nworkers])),
        ]
        thr.free([thr.high16bits, thr.high32bits, thr.prev, thr.t])
        return actions
        

class LocationEstimator:
    """_summary_
    Modes: 
        TIED: movers will be on the same node as the data: this is the original implementation
        AFFI_OVERRIDE: user given affinity override, movers will be sent to that node
        EMPIRICAL: movers will be on the same node if most performant, otherwise other node but with mirroring mover allocation
    """
    def __init__(self) -> None:
        pass
    
    def genEstimateActions(self, thr: AdvancedRegister, thrprint: RegPrinter, impl='empirical'):
        if impl == 'empirical':
            return self._empirical(thr, thrprint)
        else: 
            return self._naive(thr, thrprint)
    
    def _naive(self, thr: AdvancedRegister, thrprint: RegPrinter):
        actions = [
            
        ]
        return actions

    def _empirical(self, thr: AdvancedRegister, thrprint: RegPrinter):
        """
        Decide whether to put the workers close to the data or not by examing the following:
        log2blocksize, nelems, src
        
        location = f(log2blocksize, nelems, src)
        case 0: log2blocksize > nelems
                case 0.0: src is on the same node as the data
                    by default, the workers are on the same node as the data
                case 0.1: src is on the different node as the data
                    by default, the workers are on the same node as the data
                    but if nelems too small (threshold), check the destination, if destination is current node, 
                
        case 1: log2blocksize <= nelems

        Args:
            thr (AdvancedRegister): thread register context object
            thrprint (RegPrinter): thread register printer object

        Returns:
            list: list of actions in ordrer
        """
        actions = [
            f"",   
        ]
        return actions
    

class LAUDShmem:
    implLocAware = 'loc-aware'
    implLocAwareTest = 'loc-aware-test'
    implLocAwareEvLoop = 'loc-aware-ev-read-loop'
    implLocAwareWithConfig = 'loc-aware-wconfig'
    implLocAwareInterleaving = 'loc-aware-interleaving'
    MAP_BASE_LSHIFT = 31
    GMAP_BASE_LSHIFT = 33
    def __init__(self, efa, state=None, event_map_start=2, debug_level=1, perflog_level=1, term_flag_offset=0,
                 linker=False, impl=implLocAwareInterleaving, throttle=128, is3rdPartyMover=False, includeConfigs=False, printActions=False,
                 work_estimator_exp_scaler=0, work_estimator_scaler=0) -> None:
        self.debug_level = debug_level
        self.perflog_level = perflog_level
        self.impl = impl
        self.efa = efa
        if state is None:
            self.state = efa.State("UDSHMEMS0")
            efa.add_initId(self.state.state_id)
        else:
            self.state = state
        self.throttle = throttle
        self.is3rdPartyMover = is3rdPartyMover
        self.includeConfigs = includeConfigs
        self.printActions = printActions
        self.work_estimator_exp_scaler = work_estimator_exp_scaler
        self.work_estimator_scaler = work_estimator_scaler
        
        self.em = EventMap(event_map_start, linker=linker)
        self.reg = Register()
        
        self.term_flag_offset = term_flag_offset
        self.config_offset = self.term_flag_offset + (1 << 3) # bytes [0,7] = flag, word [1, 16] = config
        self.lane_send_buffer_offset = self.config_offset + (1 << 7) # word [1, 16] = config, word [17, 24] = send buffer
        self.lane_operands_offset = self.lane_send_buffer_offset + (1 << 6) # word 1-8 = lane buffer, word 9-inf = operands
        self.numops = 3
        if self.is3rdPartyMover:
            self.numops += 1
        if self.includeConfigs:
            self.numops += 3        
        
        info = f"\nUDSHMEM-ASSEM-INFO[{self.impl}]: term_flag_offset={self.term_flag_offset}, config_offset={self.config_offset}, lane_send_buffer_offset={self.lane_send_buffer_offset}, lane_operands_offset={self.lane_operands_offset}\n"
        info += f"UDSHMEM-ASSEM-INFO[{self.impl}]: debug_level={self.debug_level}, perflog_level={self.perflog_level}, is3rdPartyMover={self.is3rdPartyMover}, total_bytes_reserved={self.lane_operands_offset - self.term_flag_offset}\n"
        info += f"UDSHMEM-ASSEM-INFO[{self.impl}]: numops={self.numops}, printAction={self.printActions}, linker={linker}, throttle={self.throttle}, includeConfigs={self.includeConfigs}\n"
        print(info)
        
        self.default_chunks = [1,2,4,8]
        self.allowed_chunks = [1,2,4,8]
        self.chunks = [1,2,3,4,5,6,7,8]
        self.elem_size = 8
        self.word_size = 8

        # self.numops = 6 if self.impl == self.implLocAwareWithConfig else 3
        # self.numops = 4 if is3rdPartyMover else self.numops
        
        self.em.add_event('udshmem_put')
        self.em.add_event('udshmem_get') # TODO: not implemented, basically the same as put
        if impl == 'naive':
            self.udshmem_naive_shmem()
        elif impl.startswith('loc-aware'):
            self.udshmem()
        if self.printActions:
            print(self.em)
        
    
                                    
    def __NEXT_CHUNK(self, C):
        if C == 1:
            return 1
        else:
            return C >> 1  
        

    def debug(self, tran, msg, level=1):
        if level <= self.debug_level:
            if self.printActions:
                print("PRINT:", msg)
            tran.writeAction(msg)
    
    
    def perflog(self, tran, level, msg):
        if level <= self.perflog_level:
            tran.writeAction(msg)    
        
        
    def appendTranActions(self, tran, actions):
        for action in actions:
            if self.printActions:
                print(action)
            if isinstance(action, tuple):
                level = action[0]
                msg = action[1]
                
                if msg.startswith("print"):
                    self.debug(tran, level=level,msg=msg)
                elif msg.startswith("perflog"):
                    self.perflog(tran, level=level,msg=msg)
            elif action.startswith("print") or action.startswith("perflog"):
                pass
            else:
                tran.writeAction(action)
        if self.printActions:
            print("-----------------------------------------------------------")

         
            
    def call_udshmem_put(self, tran, cont_label=1):
        lmbase = self.reg.alloc('lmbase')
        lmoffset = self.reg.alloc('lmoffset')
        evw = self.reg.alloc('evw')
        temp0 = self.reg.alloc('temp0')
        temp1 = self.reg.alloc('temp1')
        actions = [
            f"addi X7 {lmbase} {self.lane_send_buffer_offset}",
            f"movir {lmoffset} 0",
            f"evii {evw} {self.em['udshmem-naive-shmem-put']} 255 {0b0101}",
            (0, f"print '[nwid=%lu] Push shmem_put event, cevw=%lu, ccont=%lu, evw=%lu, label=%lu' NWID X2 X1 {evw} {self.em['udshmem-done']}"),
            f"sendops_wret {evw} {cont_label} X8 4 {temp0} {temp1}",
        ]
        self.appendTranActions(tran, actions)
        self.reg.freeall()      
    
    
    def call_udshmem(self, tran, cont_label=1):
        uthr = AdvancedRegister()
        uthr.lmbase = 'alloc'
        uthr.lmptr = 'alloc'
        uthr.evw = 'alloc'
        uthr.tmp = 'alloc'
        uthr.tmp1 = 'alloc'
        uthr.nwid = 'alloc'
        uthr.contw = 'alloc'
      
        actions = [
            (0, f"print 'BEFORE'"),
            f"evii {uthr.evw} {self.em['udshmem_put']} 255 {0b0101}",
            # f"sendops_wret {uthr.evw} {cont_label} X8 {self.numops} {uthr.tmp} {uthr.tmp1}",
            
            # TODO: this gets NWID wrong in the evword and contw
            f"mov_reg2reg NWID {uthr.nwid}",
            f"ev {uthr.evw} {uthr.evw} {uthr.nwid} {uthr.nwid} {0b1000}",
            (0, f"print '[NWID=%ld]END evw=%lu, cevw=%ld' NWID {uthr.evw} X2"),
            # f"mov_reg2reg X2 {uthr.contw}",
            f"evi X2 {uthr.contw} {cont_label} {0b0001}",
            f"ev {uthr.contw} {uthr.contw} {uthr.nwid} {uthr.nwid} {0b1000}",
            (0, f"print 'call args: evw=%lu, contw=%lu, nwid=%lu, EVW=%lu, CONT=%lu' {uthr.evw} {uthr.contw} {uthr.nwid} X2 X1"),
            f"sendops_wcont {uthr.evw} {uthr.contw} X8 {self.numops}",
            f"yield",
        ]
        self.appendTranActions(tran, actions)
        uthr.freeall()
            
    
    def udshmem(self):
        
         
        self.em.add_event('udshmem-init')
        self.em.add_event('udshmem-done')
        self.em.add_event('udshmem-stack-root')
        self.em.add_event('udshmem-ud-notify-stack-root')
        self.em.add_event('udshmem-ud-root')
        self.em.add_event('udshmem-worker-notify-ud-root')
        self.em.add_event('udshmem-general-worker-read')
        self.em.add_event('udshmem-worker-read')
        self.em.add_event('udshmem-handle-head-tail')
        for c in self.chunks:
            self.em.add_event(f'udshmem-worker-write-{c}')
        for c in self.chunks:   
            self.em.add_event(f'udshmem-worker-ack-{c}')
        
        # doesn't matter if we have more in the map
        self.em.add_event('udshmem-worker-read-throttled')
        self.em.add_event(f'udshmem-worker-write-8-throttled')
        
        self.em.add_event('udshmem-worker-interleaving-read-write')
        self.em.add_event('udshmem-worker-interleaving-write')
        self.em.add_event('udshmem-worker-ev-read-loop')


        
        
        #===================================================ENTRY-EVENTS=================================================
        # region entry-events
        #------------------------------------------------udshmem-put-with-config---------------------------------------------
        ethr = AdvancedRegister()

        #------------------------------------------------udshmem-put------------------------------------------------
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.em['udshmem_put'])
        # obdst, obsrc, obnelems
        # if self.impl == self.implLocAwareWithConfig: oblog2numnodes, oblog2blocksize, oblog2privblocksize
        ethr.evw = 'alloc'
        ethr.tmp0 = 'alloc'
        ethr.tmp1 = 'alloc'
        ethr.tmp2 = 'alloc'
        ethr.nwid = 'alloc'
        actions = [
            (1, f"print 'Implementation version = {self.impl}, debug_level = {self.debug_level}, perflog_level = {self.perflog_level}, throttle = {self.throttle}, is3rdPartyMover = {self.is3rdPartyMover}, numops={self.numops}'"),
            (1, f"print '[UDSHMEM][NWID=%ld]============================================LOC-AWARE-UDSHMEM=========================================================' NWID"),
            (1, f"print '[UDSHMEM][NWID=%ld]LOC-AWARE SHMEM STARTS! evw=%lu, contw=%lu' NWID X2 X1"),
            (1, f"perflog 1 {pmap['all-start']}'LOC-AWARE SHMEM STARTS!'"),
            # set the term_flag to 0
            f"movir X31 0",
            f"movir X29 0",
            f"addi X7 X30 {self.term_flag_offset}",
            f"movwrl X29 X30(X31,1,0)",
            f"evii {ethr.evw} {self.em['udshmem-init']} 255 {0b0101}",
            f"sendops_wcont {ethr.evw} X1 X8 {self.numops}",
            f"yieldt",
        ]

        #------------------------------------------------udshmem-put-end------------------------------------------------
        ethr.freeall()
        self.appendTranActions(tran, actions)
        # endregion entry-events
        #=================================================ENTRY-EVENTS-END================================================
        
        #============================================UDSHMEM-WORK-DISTRIBUTOR==============================================
        #region udshmem-work-distributor
        #------------------------------------------------udshmem-init------------------------------------------------
        #region init
        # make sure config is ready in spm; otherwise there needs to be a process asking for config information
        
        
        ithr = AdvancedRegister()
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.em['udshmem-init'])
        actions = []
        # obs: obdst, obsrc, obnelems
        # given configs: 1-log2numnodes, 2-log2numstacks, 3-log2numuds, 4-log2numlanes, 5-gmapbase, 6-mapbase, 7-log2blocksize
        # config should be ready in the local memory
        # remember to use LocalMemAddrMode
        # read the configs
        
        #--------------------
        # implLocAwareTest:
        # numobs = 3
        # obs: obdst, obsrc, obnelems
        # default config: GBlocksize = 1KB, PBlockisze=1KB, numnodes=1, gmapbase=obsrc, mapbase=obdst
        #--------------------
        # implLocAwareWithConfig:
        # numobs = 6
        # obs: obdst, obsrc, obnelems, oblog2numnodes, oblog2blocksize, oblog2privblocksize
        # default config: gmapbase=GMapBase, mapbase=MapBase
        #---------------------
        # implLocAware:
        # numobs = 3
        # obs: obdst, obsrc, obnelems
        # config is in the local memory starting from self.config_offset, has to be written prior to this event
        #---------------------
        # 3rdPartyMover==True:
        # numobs = 4
        # obs: obdst, obsrc, obnelems, obstartnodeid
        # config is the same as implLocAware
        #---------------------
        obdst = "X8"
        obsrc = "X9"
        obnelems = "X10"

        # test obs, mover starting nodeid
        if self.is3rdPartyMover and (not self.includeConfigs):
            obstartnodeid = "X11"
        elif (not self.is3rdPartyMover) and self.includeConfigs:
            # if impl== loc-aware-wconfig
            oblog2numnodes = "X11"
            oblog2blocksize = "X12"
            oblog2privblocksize = "X13"
        elif self.is3rdPartyMover and self.includeConfigs:
            # include configs and is3rdpartymovers
            obstartnodeid = "X11"
            oblog2numnodes = "X12"
            oblog2blocksize = "X13"
            oblog2privblocksize = "X14"
        elif (not self.is3rdPartyMover) and (not self.includeConfigs):
            pass
        
        ithr.lmbase = 'alloc'
        ithr.lmptr = 'alloc'
        ithr.log2numnodes = 'alloc'
        ithr.log2numstacks = 'alloc'
        ithr.log2numuds = 'alloc'
        ithr.log2numlanes = 'alloc'
        ithr.gmapbase = 'alloc'
        ithr.mapbase = 'alloc'
        ithr.log2blocksize = 'alloc'
        ithr.log2privblocksize = 'alloc'
        
        ithrprint = RegPrinter(ithr)
        
        
        if self.impl == self.implLocAwareTest:
            actions += [
                f"movir {ithr.log2numnodes} 1",
                f"movir {ithr.log2numstacks} 3",
                f"movir {ithr.log2numuds} 2",
                f"movir2 {ithr.log2numlanes} 6",
                f"mov_reg2reg {obsrc} {ithr.gmapbase}",
                f"mov_reg2reg {obdst} {ithr.mapbase}",
                f"movir {ithr.log2blocksize} 10",
                f"movir {ithr.log2privblocksize} 10",
            ]
        
        # elif self.impl == self.implLocAwareWithConfig:
        elif self.includeConfigs:
            actions += [
                f"mov_reg2reg {oblog2numnodes} {ithr.log2numnodes}",
                # const
                f"movir {ithr.log2numstacks} 3",
                f"movir {ithr.log2numuds} 2",
                f"movir {ithr.log2numlanes} 6",
                # same as config in updown_config.h
                f"movir {ithr.gmapbase} 1",
                f"sli {ithr.gmapbase} {ithr.gmapbase} {self.GMAP_BASE_LSHIFT}",
                f"movir {ithr.mapbase} 1",
                f"sli {ithr.mapbase} {ithr.mapbase} {self.MAP_BASE_LSHIFT}",
                f"mov_reg2reg {oblog2blocksize} {ithr.log2blocksize}",
                f"mov_reg2reg {oblog2privblocksize} {ithr.log2privblocksize}", 
            ]
        else:
            actions += [
                f"addi X7 {ithr.lmbase} {self.config_offset}",
                (4, ithrprint.printr("lmbase:", [ithr.lmbase])),
                f"movir {ithr.lmptr} 0",
                f"movwlr {ithr.lmbase}({ithr.lmptr},1,0) {ithr.log2numnodes}",
                f"movwlr {ithr.lmbase}({ithr.lmptr},1,0) {ithr.log2numstacks}",
                f"movwlr {ithr.lmbase}({ithr.lmptr},1,0) {ithr.log2numuds}",
                f"movwlr {ithr.lmbase}({ithr.lmptr},1,0) {ithr.log2numlanes}",
                f"movwlr {ithr.lmbase}({ithr.lmptr},1,0) {ithr.mapbase}",
                f"movwlr {ithr.lmbase}({ithr.lmptr},1,0) {ithr.gmapbase}",
                f"movwlr {ithr.lmbase}({ithr.lmptr},1,0) {ithr.log2blocksize}",
                f"movwlr {ithr.lmbase}({ithr.lmptr},1,0) {ithr.log2privblocksize}",
                (1,ithrprint.printr("Configs read:", [ithr.log2numnodes, ithr.log2numstacks, ithr.log2numuds, ithr.log2numlanes, ithr.mapbase, ithr.gmapbase, ithr.log2blocksize, ithr.log2privblocksize]))
            ]
        # >>> free lmptr, lmbase
        # print(ithr)
        ithr.free([ithr.lmptr, ithr.lmbase])
        # print(ithr)
        # assume we have config
        actions += [
            (1, ithrprint.printr("Initial Args:", [('obdst', obdst),('obsrc', obsrc), ('nelems', obnelems), ithr.log2numnodes, ithr.log2blocksize, ithr.log2privblocksize, ])),
        ]
        actions += [
            # if src < gmapbase: it is local
            f"ble {ithr.gmapbase} {obsrc} udshmem-src-global",
            # now it is local
            f"mov_reg2reg {ithr.log2privblocksize} {ithr.log2blocksize}",
            f"mov_reg2reg {ithr.mapbase} {ithr.gmapbase}",
            f"movir {ithr.log2numnodes} 0",
            # >>> free mapbase, log2privblocksize
            (2,ithrprint.printr("Local:", [ithr.log2numnodes, ithr.log2numstacks, ithr.mapbase, ithr.gmapbase, ithr.log2blocksize, ithr.log2privblocksize]))
        ]
        ithr.free([ithr.mapbase, ithr.log2privblocksize])

        ithr.maxnstacks = 'alloc'
        ithr.mask = 'alloc'
        ithr.log2maxnstacks = 'alloc'
        # maxnstacks = 1 << (log2numnodes + log2numstacks)
        actions += [
            f"udshmem-src-global: movir {ithr.maxnstacks} 1",
            f"add {ithr.log2numnodes} {ithr.log2numstacks} {ithr.log2maxnstacks}",
            f"sl {ithr.maxnstacks} {ithr.log2maxnstacks} {ithr.maxnstacks}", # TODO: check if this is correct
            f"subi {ithr.maxnstacks} {ithr.mask} 1",
            (3, ithrprint.printr("maxnstacks:", [ithr.maxnstacks, ithr.log2maxnstacks, ithr.mask]))
        ]
        # >>> free maxnstacks
        ithr.free(ithr.maxnstacks)
        
        
        ithr.tmp = 'alloc'
        ithr.sstackid = 'alloc'
        ithr.tmp2 = 'alloc'
        ithr.log2segsize = 'alloc'
        actions += [
            # sstackid = [(src - gmapbase) >> (log2nsegs)] & mask(maxnstacks)
            f"subi {ithr.log2blocksize} {ithr.log2segsize} 3",
            f"sub {obsrc} {ithr.gmapbase} {ithr.tmp}",
            f"sr {ithr.tmp} {ithr.log2segsize} {ithr.tmp}",
            f"and {ithr.tmp} {ithr.mask} {ithr.sstackid}",
            (3, ithrprint.printr("sstackid:", [ithr.sstackid, ithr.tmp]))
        ]
        # >>> free mask
        ithr.free([ithr.mask, ithr.tmp2])
        
        ithr.src_end = 'alloc'
        ithr.src_block_start = 'alloc'
        ithr.src_block_end = 'alloc'
        ithr.tmp1 = 'alloc'
        actions += [
            # src_end = src + nelems<<3
            f"sli {obnelems} {ithr.tmp} 3",
            f"add {obsrc} {ithr.tmp} {ithr.src_end}",
            (5, ithrprint.printr("init: src_end:", [ithr.src_end,  ('obsrc', obsrc), ('obnelems', obnelems), ithr.tmp])),
            
            # src_block_start = src>>log2blocksize << log2blocksize
            f"sr {obsrc} {ithr.log2blocksize} {ithr.tmp}",
            f"sl {ithr.tmp} {ithr.log2blocksize} {ithr.src_block_start}",
            (5, ithrprint.printr("init: src_block_start", [ithr.src_block_start, ('obsrc', obsrc), ithr.log2blocksize, ithr.tmp])),
            
            # src_block_end = src_end >> log2blocksize << log2blocksize + (1<<log2blocksize)
            f"subi {ithr.src_end} {ithr.tmp} 1",
            f"sr {ithr.tmp} {ithr.log2blocksize} {ithr.tmp}",
            f"sl {ithr.tmp} {ithr.log2blocksize} {ithr.tmp}",
            f"movir {ithr.tmp1} 1",
            f"sl {ithr.tmp1} {ithr.log2blocksize} {ithr.tmp1}",
            f"add {ithr.tmp} {ithr.tmp1} {ithr.src_block_end}",
            (5, ithrprint.printr("init: src_block_end:", [ithr.src_block_end, ithr.src_end, ithr.src_block_start, ithr.tmp, ithr.tmp1]))
        ]
        # >>> free tmp1
        ithr.free([ithr.tmp1])
        
        
        ithr.nblocks = 'alloc'
        actions += [
            # nblocks = (src_block_end - src_block_start) >> log2blocksize
            f"sub {ithr.src_block_end} {ithr.src_block_start} {ithr.tmp}",
            f"sr {ithr.tmp} {ithr.log2blocksize} {ithr.nblocks}", # this for sure >= 1
            (3, ithrprint.printr("init: nblocks", [ithr.nblocks, ithr.tmp, ithr.src_block_end, ithr.src_block_start, ithr.log2blocksize]))
        ]
        # >>> free src_block_start, src_block_end
        ithr.free([ithr.src_block_start, ithr.src_block_end])
        
        ithr.maxnnodes = 'alloc'
        actions += [
            # maxnnodes = 1 << log2numnodes
            f"movir {ithr.maxnnodes} 1",
            f"sl {ithr.maxnnodes} {ithr.log2numnodes} {ithr.maxnnodes}",
            (3, ithrprint.printr("init: maxnnodes", [ithr.maxnnodes])),
            
            
            # when nblocks < maxnnodes, we need exact stack num
            # stacks = src_stack_end - src_stack_start
            # src_stack_start = src >> log2segsize << log2segsize
            # src_stack_end = src_end >> log2segsize << log2segsize + (1<<log2segsize)
            f"bgt {ithr.nblocks} {ithr.maxnnodes} maxnodes-lt-nblocks",
        ]
        ithr.free([ithr.maxnnodes])
        
        ithr.nstacks = 'alloc'
        # ithr.log2segsize = 'alloc'
        ithr.src_stack_start = 'alloc'
        ithr.src_stack_end = 'alloc'
        ithr.tmp1 = 'alloc'
        actions += [
            # bgt maxnnodes nblocks maxnodes-lt-nblocks
            # nstacks = maxnnodes << log2numstacks
            # jmp cont
            
            f"sr {obsrc} {ithr.log2segsize} {ithr.tmp}",
            f"sl {ithr.tmp} {ithr.log2segsize} {ithr.src_stack_start}",
            (5, ithrprint.printr("init: src_stack_start", [ithr.src_stack_start, ithr.log2segsize, ithr.tmp])),
            
            f"subi {ithr.src_end} {ithr.src_end} 1",
            f"sr {ithr.src_end} {ithr.log2segsize} {ithr.tmp}",
            f"sl {ithr.tmp} {ithr.log2segsize} {ithr.src_stack_end}", # src_stack_end = src_end >> log2segsize << log2segsize
            f"movir {ithr.tmp1} 1",
            f"sl {ithr.tmp1} {ithr.log2segsize} {ithr.tmp1}", # tmp1 = 1 << log2segsize
            f"add {ithr.src_stack_end} {ithr.tmp1} {ithr.src_stack_end}", # src_stack_end = src_stack_end + (1<<log2segsize)
            # f"subi {ithr.src_stack_end} {ithr.src_stack_end} 8", # src_stack_end = src_stack_end, stack_end cannot be to the next seg, has to do this
            (5, ithrprint.printr("init: src_stack_end", [ithr.src_stack_end, ithr.src_end, ithr.log2segsize, ithr.tmp, ithr.tmp1])),
            f"sub {ithr.src_stack_end} {ithr.src_stack_start} {ithr.nstacks}", # tmp2 = src_stack_end - src_stack_start
            # f"subi {ithr.nstacks} {ithr.nstacks} 1", # nstacks = nstacks - 1
            f"sr {ithr.nstacks} {ithr.log2segsize} {ithr.nstacks}",
            # make sure it has remainder or not     
            # f"sl {ithr.maxnnodes} {ithr.log2numstacks} {ithr.nstacks}",
            (5, ithrprint.printr("init: nblocks <= 1<<log2numnodes, nstacks", [ithr.nstacks, ithr.log2numnodes, ithr.src_stack_start, ithr.src_stack_end]))
            # >>> free maxnnodes
        ]
        ithr.free([ ithr.src_end, ithr.log2segsize, ithr.src_stack_start, ithr.src_stack_end, ithr.tmp1])
        
        actions += [
            f"jmp cont",
            f"maxnodes-lt-nblocks: movir {ithr.nblocks} 1", # nstacks = nblocks << log2numstacks
            f"add {ithr.log2numnodes} {ithr.log2numstacks} {ithr.tmp}",
            f"sl {ithr.nblocks} {ithr.tmp} {ithr.nstacks}",
            (2, ithrprint.printr("init: nstacks", [ithr.nstacks, ithr.nblocks])),
            # >>> free log2numstacks, nblocks
        ]
        ithr.free([ithr.log2numstacks, ithr.nblocks, ithr.log2numnodes])
        
        # upgrade: init now decide where to put the movers
        # if read is local, skip the mover
        # if read is remote, we consider the nelems and decide if we need to put the mover in remote
        # how can we decide? we need to run a parameter sweep reading the 4th OB indicating whether force local or default remote
        
        # impl:
        # 1. if read is local, skip
        # 2. if read is remote, check num of operands, if num <=3, skip
        # 3. if not skip, then mode = ob4, ob4 == 0: targetnwid = caller; ob4 == any, startfrom that nodeid; ob4<0, skip
        ithr.snodeid = 'alloc'
        ithr.numops = 'alloc'
        ithr.psstackid = 'alloc' # physical start stack id, psstackid = (sstackid - snodeid*8) + startnodeid*8
        
        actions +=[
            f"cont: mov_reg2reg {ithr.sstackid} {ithr.psstackid}",
            f"mov_reg2reg NWID {ithr.tmp}",
            (3, ithrprint.printr("init: psstackid", [ithr.psstackid, ithr.sstackid])),
            f"sri {ithr.tmp} {ithr.tmp} 11", # current_nodeid = NWID >> 11
            f"sri {ithr.sstackid} {ithr.snodeid} 3", # snodeid = sstackid >> 3
            (3, ithrprint.printr("init: current_nodeid", [ithr.snodeid, ithr.tmp, ithr.sstackid])),
            # f"beq {ithr.tmp} {ithr.snodeid} udshmem-skip-init", # if current_nodeid == snodeid, then it is local, skip
            # now it is remote, we check the num of operands
            # numops = (X2 >> 20) & 0b111 + 2
            f"sri X2 {ithr.numops} 20", 
            f"andi {ithr.numops} {ithr.numops} {0b111}",
            f"addi {ithr.numops} {ithr.numops} 2",
            (3, ithrprint.printr("init: numops", [ithr.numops, ithr.tmp, ithr.snodeid])),
        ]
        if self.is3rdPartyMover:
            actions += [
                f"blei {ithr.numops} 3 udshmem-skip-init", # if numops <= 3, skip
                f"beqi {ithr.numops} 6 udshmem-skip-init", # if numops == 6, then startnodeid is not included, only when numops == 4 or 7 we have startnodeid included
                f"addi {obstartnodeid} {ithr.tmp} 1",
                # f"blti {obstartnodeid} -1 udshmem-skip-init", # if startnodeid < -1, skip
                (2, ithrprint.printr("init: given nodeid after+1", [('obstartnodeid', obstartnodeid), ithr.tmp,])),
                f"beqi {ithr.tmp} 0 udshmem-skip-init", # if startnodeid < -1, skip
                f"beqi {obstartnodeid} 0 udshmem-init-caller", # if startnodeid < 0, then start from caller
                # now startnodeid > 0
                f"sli {ithr.snodeid} {ithr.tmp} 3", # tmp = snodeid << 3
                f"sub {ithr.sstackid} {ithr.tmp} {ithr.tmp}", # tmp = sstackid - tmp
                f"sli {obstartnodeid} {ithr.psstackid} 3", # psstackid = startnodeid << 3 = startnodeid * 8
                f"add {ithr.tmp} {ithr.psstackid} {ithr.psstackid}", # psstackid = tmp + psstackid
                (2, ithrprint.printr("init: start from given nodeid", [('obstartnodeid', obstartnodeid), ithr.psstackid, ithr.snodeid, ithr.sstackid, ithr.tmp,])),
                f"jmp udshmem-skip-init",
                # start from caller's stack
                f"udshmem-init-caller: mov_reg2reg NWID {ithr.tmp}",
                f"sri {ithr.tmp} {ithr.psstackid} 8", # psstackid = NWID >> 8
                (3, ithrprint.printr("init: MODE: start-from-caller", [ithr.psstackid, ithr.snodeid, ithr.sstackid])),
            ]
        ithr.free([ithr.numops, ithr.snodeid])
        
        
        # [upgrade](11-5-2023)
        # compress log2blocksize and log2maxnstacks into one operand: first 32bits = log2blocksize, last 32bits = log2maxnstack
        ithr.log2blocksizelog2maxnstacks = 'alloc'
        ithr.nwid_mask = 'alloc'
        actions += [
            f"udshmem-skip-init: movir {ithr.log2blocksizelog2maxnstacks} 0",
            f"sli {ithr.log2blocksize} {ithr.tmp} 32",
            f"or {ithr.tmp} {ithr.log2maxnstacks} {ithr.log2blocksizelog2maxnstacks}",
            (3, ithrprint.printr("init: log2blocksizelog2maxnstacks", [ithr.log2blocksizelog2maxnstacks, ithr.log2blocksize, ithr.log2maxnstacks, ithr.tmp])),
            
            # nwid_mask = (1 << (log2maxnstacks+log2numlanes+log2numuds)) - 1
            f"add {ithr.log2maxnstacks} {ithr.log2numlanes} {ithr.tmp}",
            f"add {ithr.tmp} {ithr.log2numuds} {ithr.tmp}",
            f"movir {ithr.nwid_mask} 1",
            f"sl {ithr.nwid_mask} {ithr.tmp} {ithr.nwid_mask}",
            f"subi {ithr.nwid_mask} {ithr.nwid_mask} 1",
            (3, ithrprint.printr("init: nwid_mask", [ithr.nwid_mask, ithr.log2maxnstacks, ithr.log2numlanes, ithr.log2numuds, ithr.tmp])),
        ]
        # >>> free log2blocksize, log2maxnstacks
        ithr.free([ithr.log2blocksize, ithr.log2maxnstacks])
        
        ithr.rstackid = 'alloc'
        ithr.lmbase = 'alloc'
        ithr.lmptr = 'alloc'
        actions += [
            f"addi X7 {ithr.lmbase} {self.lane_send_buffer_offset}",
            # (4, ithrprint.printr("init: lmbase", [ithr.lmbase])),
            (2, ithrprint.printr("init: writing operands into LM", [('obdst', obdst), ('obsrc', obsrc), ('obnelems', obnelems)])),
            (2, ithrprint.printr("init: writing operands(2)", [ithr.nstacks, ithr.log2blocksizelog2maxnstacks, ithr.gmapbase])),
            # (2, ithrprint.printr("init: initialize with", [('obnelems', obnelems), ithr.nstacks, ithr.log2blocksize, ithr.gmapbase, ithr.log2maxnstacks])),
            f"movir {ithr.lmptr} 0",
            # put the values in the LM
            f"movwrl {obdst} {ithr.lmbase}({ithr.lmptr},1,0)", # cannot be compressed
            f"movwrl {obsrc} {ithr.lmbase}({ithr.lmptr},1,0)", # cannot be compressed
            f"movwrl {obnelems} {ithr.lmbase}({ithr.lmptr},1,0)", # cannot be compressed
            f"movwrl {ithr.rstackid} {ithr.lmbase}({ithr.lmptr},1,0)",
            f"movwrl {ithr.nstacks} {ithr.lmbase}({ithr.lmptr},1,0)",
            f"movwrl {ithr.sstackid} {ithr.lmbase}({ithr.lmptr},1,0)",
            f"movwrl {ithr.log2blocksizelog2maxnstacks} {ithr.lmbase}({ithr.lmptr},1,0)",
            # f"movwrl {ithr.log2blocksize} {ithr.lmbase}({ithr.lmptr},1,0)",
            f"movwrl {ithr.gmapbase} {ithr.lmbase}({ithr.lmptr},1,0)", # cannot be compressed
            # f"movwrl {ithr.log2maxnstacks} {ithr.lmbase}({ithr.lmptr},1,0)",
            # (4, ithrprint.printr("init: rstackid", [ithr.nstacks, ithr.log2blocksize, ithr.gmapbase, ithr.log2maxnstacks]))
        ]
        # >>> free gmapbase, log2blocksize, log2maxnstacks
        # ithr.free([ithr.gmapbase, ithr.log2blocksize, ithr.log2maxnstacks])
        ithr.free([ithr.gmapbase, ithr.log2blocksizelog2maxnstacks])
        

        ithr.stack_nwid_shift = 'alloc'
        ithr.stack_base_nwid = 'alloc'
        
        actions += [
            # send to all the stacks
            f"movir {ithr.lmptr} 3", # this points to rstakid
            f"add {ithr.log2numlanes} {ithr.log2numuds} {ithr.stack_nwid_shift}", # stack_nwid_shift = log2numlanes + log2numuds
            # f"sl {ithr.sstackid} {ithr.stack_nwid_shift} {ithr.stack_base_nwid}", # stack_base_nwid = sstackid << stack_nwid_shift
            f"sl {ithr.psstackid} {ithr.stack_nwid_shift} {ithr.stack_base_nwid}", # stack_base_nwid = psstackid << stack_nwid_shift
            (2, ithrprint.printr("init: target stacks", [ithr.sstackid, ithr.stack_nwid_shift, ithr.stack_base_nwid, ithr.psstackid, ithr.log2numlanes, ithr.log2numuds])),
            # >>> free sstackid
        ]
        ithr.free(ithr.sstackid)
        
        ithr.expect = 'alloc'
        ithr.nreplys = 'alloc'
        ithr.tnwid = 'alloc'
        ithr.evw = 'alloc'
        actions += [
            # TODO: can be optimized using a fan-out tree
            f"movir {ithr.rstackid} 0",
            f"udshmem-send-stack-loop: ble {ithr.nstacks} {ithr.rstackid} udshmem-stack-loop-done",
                f"movwrl {ithr.rstackid} {ithr.lmbase}({ithr.lmptr},0,0)",
                f"sl {ithr.rstackid} {ithr.stack_nwid_shift} {ithr.tnwid}", 
                f"add {ithr.tnwid} {ithr.stack_base_nwid} {ithr.tnwid}", # tnwid = stack_base_nwid + rstackid << stack_nwid_shift
                f"and {ithr.tnwid} {ithr.nwid_mask} {ithr.tnwid}", # tnwid = tnwid & nwid_mask
                f"evii {ithr.evw} {self.em['udshmem-stack-root']} 255 {0b0101}",
                f"ev {ithr.evw} {ithr.evw} {ithr.tnwid} {ithr.tnwid} {0b1000}",
                (4, ithrprint.printr("init: sending to stack-root", [ithr.rstackid, ithr.nstacks, ithr.lmbase, ithr.lmptr, ithr.stack_base_nwid, ithr.tnwid])),
                f"send_wret {ithr.evw} {self.em['udshmem-done']} {ithr.lmbase} 8 {ithr.tmp}",
                f"addi {ithr.rstackid} {ithr.rstackid} 1",
            f"jmp udshmem-send-stack-loop",
            f"udshmem-stack-loop-done: movir {ithr.nreplys} 0",
            f"mov_reg2reg {ithr.nstacks} {ithr.expect}",
            (4, ithrprint.printr("init: expect", [ithr.nstacks, ithr.expect])),
            f"yield",
            # send to the starting stack      
        ]
        self.appendTranActions(tran, actions)
        
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.em['udshmem-done'])
        actions = [
            
            f"addi {ithr.nreplys} {ithr.nreplys} 1",
            (5, ithrprint.printr("init: nreplys", [ithr.nreplys, ithr.expect])),
            f"ble {ithr.expect} {ithr.nreplys} udshmem-term",
            f"yield",
            f"udshmem-term: sendr_reply X31 X30 {ithr.tmp}", # send back to caller who calls init
            (1,f"print '[UDSHMEM][NWID=%ld]============================================LOC-AWARE-UDSHMEM-ENDS=========================================================' NWID"),
            (1, f"perflog 1 {pmap['all-end']}'LOC-AWARE SHMEM ENDS!'"),
            f"movir X31 0",
            f"movir X29 1",
            f"addi X7 X30 {self.term_flag_offset}",
            f"movwrl X29 X30(X31,1,0)",
            f"yieldt",
        ]
        self.appendTranActions(tran, actions)
        
        # endregion init
        #------------------------------------------------udshmem-init------------------------------------------------------
        
        
        #------------------------------------------------udshmem-stack-root------------------------------------------------
        # region stack-root
        sthr = AdvancedRegister()
        sthrprint = RegPrinter(sthr)
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.em['udshmem-stack-root'])
        # obs: obdst, obsrc, obnelems, obrstackid, obnstacks, oblog2blocksize, obgmapbase, oblog2maxnstacks
        obdst = "X8"
        obsrc = "X9"
        obnelems = "X10"
        obrstackid = "X11"
        obnstacks = "X12"
        # oblog2blocksize = "X13"
        # obgmapbase = "X14"
        # oblog2maxnstacks = "X15"
        # [upgrade](11-5-2023), ob changed according to init
        # obpsstackid = "X13"
        obsstackid = "X13" # virtual start stack id
        oblog2blocksizelog2maxnstacks = "X14" # 2 operands is combined into one, first 32bits = log2blocksize, last 32bits = log2maxnstack
        obgmapbase = "X15"
        
        
        sthr.log2seg = 'alloc'
        sthr.maxnstacks = 'alloc'
        sthr.mask = 'alloc'
        sthr.log2blocksize = 'alloc'
        sthr.log2maxnstacks = 'alloc'
        actions = [
            # (4, sthrprint.printr("stack-root:", [('obsrc', obsrc), ('obnelems', obnelems), ('obrstackid', obrstackid), ('obnstacks', obnstacks), ('oblog2blocksize', oblog2blocksize), ('obgmapbase', obgmapbase), ('oblog2maxnstacks', oblog2maxnstacks)])),
            f"sri {oblog2blocksizelog2maxnstacks} {sthr.log2blocksize} 32", # log2blocksize = oblog2blocksizelog2maxntacks >> 32
            # log2maxnstacks = oblog2blocksizelog2maxnstacks << 32 >> 32
            f"sli {oblog2blocksizelog2maxnstacks} {sthr.log2maxnstacks} 32",
            f"sri {sthr.log2maxnstacks} {sthr.log2maxnstacks} 32", 
            (4, sthrprint.printr("stack-root:", [('obsrc', obsrc), ('obnelems', obnelems), ('obrstackid', obrstackid), ('obnstacks', obnstacks), sthr.log2maxnstacks, sthr.log2blocksize, ('obgmapbase', obgmapbase)])),
            
            # log2seg = log2blocksize - 3
            # f"subi {oblog2blocksize} {sthr.log2seg} 3", # just assume we will always have 8 stacks
            f"subi {sthr.log2blocksize} {sthr.log2seg} 3", # log2seg = log2blocksize - 3; segsize = blocksize/8(stacks)
            
            # maxnstacks = 1 << log2maxnstacks
            f"movir {sthr.maxnstacks} 1",
            f"sl {sthr.maxnstacks} {sthr.log2maxnstacks} {sthr.maxnstacks}",
            
            # mask = maxnstacks - 1
            f"subi {sthr.maxnstacks} {sthr.mask} 1",
            
            (5, sthrprint.printr("stack-root: maxnstacks:", [sthr.maxnstacks, sthr.mask]))
        ]
        
        
        
        sthr.src_stack_start = 'alloc'
        sthr.stack_start = 'alloc'
        actions += [
            # src_stack_start = src >> log2blocksize << log2blocksize
            f"sr {obsrc} {sthr.log2seg} {sthr.src_stack_start}",
            (3, sthrprint.printr("stack-root: obsrc >> log2seg = src_stack_start(tmp):", [sthr.src_stack_start, ('obsrc', obsrc), sthr.log2seg])),
            f"sl {sthr.src_stack_start} {sthr.log2seg} {sthr.src_stack_start}",
            (3, sthrprint.printr("stack-root: src_stack_start:", [sthr.src_stack_start])),
            # stack_start = src_stack_start + rstackid << log2seg
            f"sl {obrstackid} {sthr.log2seg} {sthr.stack_start}",
            (3, sthrprint.printr("stack-root: stack_start0:", [sthr.stack_start,sthr.src_stack_start, ('obrstackid', obrstackid) ])),
            f"add {sthr.src_stack_start} {sthr.stack_start} {sthr.stack_start}",
            (3, sthrprint.printr("stack-root: stack_start-1:", [sthr.stack_start,sthr.src_stack_start, ('obrstackid', obrstackid) ])),
            # >>> free src_stack_start
        ]
        sthr.free(sthr.src_stack_start)
        
        sthr.tmp = 'alloc'
        sthr.src_stack_end = 'alloc'
        sthr.src_end = 'alloc'
        sthr.stack_end = 'alloc'
        sthr.stackid = 'alloc'
        sthr.estackid = 'alloc'
        sthr.sstackid = 'alloc'
        actions += [
            # src_end = src + (nelems-1) << 3
            # src_stack_end = src_end >> log2seg << log2seg + (1<<log2seg)
            f"sli {obnelems} {sthr.tmp} 3",
            f"subi {sthr.tmp} {sthr.tmp} 1",
            f"mov_reg2reg {obsstackid} {sthr.sstackid}",
            
            f"add {obsrc} {sthr.tmp} {sthr.src_end}",
            f"sr {sthr.src_end} {sthr.log2seg} {sthr.src_stack_end}",
            f"sl {sthr.src_stack_end} {sthr.log2seg} {sthr.src_stack_end}",
            f"movir {sthr.tmp} 1",
            f"sl {sthr.tmp} {sthr.log2seg} {sthr.tmp}",
            f"add {sthr.src_stack_end} {sthr.tmp} {sthr.src_stack_end}",
            (3, sthrprint.printr("stack-root: src_stack_end:", [sthr.src_stack_end, sthr.src_end, ('obnelems', obnelems), sthr.log2seg, sthr.tmp])),
            
            # if estackid > stackid: tmp = estackid - stackid
            # else: tmp = estackid + maxnstacks - stackid
            # stack_end = src_stack_end - (estackid - stackid) << log2seg
            # f"mov_reg2reg NWID {sthr.stackid}",
            # f"sri {sthr.stackid} {sthr.stackid} 8",
            # current stackid = sstackid + rstackid
            f"add {sthr.sstackid} {obrstackid} {sthr.stackid}",
            f"and {sthr.stackid} {sthr.mask} {sthr.stackid}",
            
            # estackid = [(src_end-8 - gmapbase) >> log2seg] & mask(maxnstacks)
            f"sub {sthr.src_end} {obgmapbase} {sthr.tmp}",
            f"sr {sthr.tmp} {sthr.log2seg} {sthr.tmp}",
            f"and {sthr.tmp} {sthr.mask} {sthr.estackid}",
            # sstackid = [(src - gmapbase) >> log2seg] & mask(maxnstacks)
            # f"sub {obsrc} {obgmapbase} {sthr.tmp}",
            # f"sr {sthr.tmp} {sthr.log2seg} {sthr.tmp}",
            # f"and {sthr.tmp} {sthr.mask} {sthr.sstackid}",
            
            f"sub {obnstacks} {obrstackid} {sthr.tmp}",
            f"ble {sthr.stackid} {sthr.estackid} stackid-le-estackid",
            f"add {sthr.estackid} {sthr.maxnstacks} {sthr.tmp}",
            f"sub {sthr.tmp} {sthr.stackid} {sthr.tmp}",
            f"jmp estack-diff",
            f"stackid-le-estackid: sub {sthr.estackid} {sthr.stackid} {sthr.tmp}",
            (3, sthrprint.printr("stack-root: stackid-diff:", [ sthr.tmp, sthr.estackid, sthr.stackid, ('obnstacks', obnstacks), ('obrstackid', obrstackid)])),
            f"estack-diff: sl {sthr.tmp} {sthr.log2seg} {sthr.tmp}",
            f"sub {sthr.src_stack_end} {sthr.tmp} {sthr.stack_end}",
            (3, sthrprint.printr("stack-root: stackid-diff2", [sthr.tmp, sthr.estackid, sthr.stackid, ('obnstacks', obnstacks), ('obrstackid', obrstackid)])),
            (3, sthrprint.printr("stack-root: tmp = nstacks - rstackid", [sthr.tmp, ('obnstacks', obnstacks), ('obrstackid', obrstackid)])),
            # f"subi {sthr.tmp} {sthr.tmp} 1",
            # f"sl {sthr.tmp} {sthr.log2seg} {sthr.tmp}",
            # f"sub {sthr.src_stack_end} {sthr.tmp} {sthr.stack_end}",
            # f"subi {sthr.stack_end} {sthr.stack_end} 8",
            (3, sthrprint.printr("stack-root: stack_end:", [sthr.stack_end, sthr.stack_start, sthr.src_stack_end, ('obnstacks', obnstacks), ('obrstackid', obrstackid), sthr.tmp]))
            # >>> free src_stack_end
        ]
        sthr.free([sthr.src_stack_end, sthr.maxnstacks])
        # stack end and stack start seem to be correct
        
        sthr.nsegs = 'alloc'
        actions +=[
            # nsegs = (stack_end - stack_start) >> (log2seg + log2maxnstacks)
            f"sub {sthr.stack_end} {sthr.stack_start} {sthr.nsegs}",
            # f"add {sthr.log2seg} {oblog2maxnstacks} {sthr.tmp}",
            f"add {sthr.log2seg} {sthr.log2maxnstacks} {sthr.tmp}",
            f"sr {sthr.nsegs} {sthr.tmp} {sthr.nsegs}",
            f"addi {sthr.nsegs} {sthr.nsegs} 1", # always have at least one seg since this stack has data
            # (2, sthrprint.printr("stack-root: nsegs:", [sthr.nsegs, sthr.stack_end, sthr.stack_start, sthr.log2seg, ('oblog2maxnstacks', oblog2maxnstacks), sthr.tmp]))
            (3, sthrprint.printr("stack-root: nsegs:", [sthr.nsegs, sthr.stack_end, sthr.stack_start, sthr.log2seg, sthr.log2maxnstacks, sthr.tmp]))
            # >>> free stack_end
        ]
        # sthr.free(sthr.stack_end)
        
        
        sthr.snelems = 'alloc'
        actions += [
            # snelems = nsegs << (log2seg - 3)
            f"subi {sthr.log2seg} {sthr.tmp} 3",
            f"sl {sthr.nsegs} {sthr.tmp} {sthr.snelems}",
            (2, sthrprint.printr("stack-root: SNELEMS(before -src_head, -src_tail):", [sthr.snelems])),
            # >>> free nsegs
        ]
        sthr.free(sthr.nsegs)
        
        
        # sthr.stackid = 'alloc'
        sthr.expect = 'alloc'
        # sthr.sstackid = 'alloc'
        # sthr.estackid = 'alloc'
        actions += [
            # stackid = nwid >> 8  # just assume we will always have 4 uds, 64 lanes, that is (2 + 6)
            # f"mov_reg2reg NWID {sthr.stackid}",
            # f"sri {sthr.stackid} {sthr.stackid} 8",
            
            # expect = 0
            f"movir {sthr.expect} 0",
            
            # sstackid = [(src - gmapbase) >> log2seg] & mask(maxnstacks)
            # f"sub {obsrc} {obgmapbase} {sthr.tmp}",
            # f"sr {sthr.tmp} {sthr.log2seg} {sthr.tmp}",
            # f"and {sthr.tmp} {sthr.mask} {sthr.sstackid}",
            
            
            # estackid = [(src_end-8 - gmapbase) >> log2seg] & mask(maxnstacks)
            f"sub {sthr.src_end} {obgmapbase} {sthr.tmp}",
            f"sr {sthr.tmp} {sthr.log2seg} {sthr.tmp}",
            f"and {sthr.tmp} {sthr.mask} {sthr.estackid}",
            (3, sthrprint.printr("stack-root: stackid", [sthr.stackid])),
            (3, sthrprint.printr("stack-root: sstackid", [sthr.sstackid])),
            (3, sthrprint.printr("stack-root: estackid", [sthr.estackid])),
            # >>> free log2seg, mask
        ]
        sthr.free([sthr.mask])
        
        
        sthr.headnelemes = 'alloc'
        sthr.start = 'alloc'
        sthr.end = 'alloc'
        actions += [
            # if sstackid != stackid goto udshmem-no-stack-head
            f"mov_reg2reg {sthr.stack_start} {sthr.start}",
            f"mov_reg2reg {sthr.stack_end} {sthr.end}",
            f"bne {sthr.sstackid} {sthr.stackid} udshmem-no-stack-head",
            
            # headnelems = (src - stack_start) >> 3
            f"sub {obsrc} {sthr.stack_start} {sthr.headnelemes}",
            f"sri {sthr.headnelemes} {sthr.headnelemes} 3",
            f"mov_reg2reg {obsrc} {sthr.start}",
           
            f"sub {sthr.snelems} {sthr.headnelemes} {sthr.snelems}",
            # >>> free headnelems
            (3, sthrprint.printr("stack-root: headnelems(src - stack_start):", [sthr.headnelemes, sthr.start, sthr.snelems])),
        ]
        sthr.free(sthr.headnelemes)
        
        actions += [
            # if estackid != stackid goto udshmem-no-stack-tail
            f"udshmem-no-stack-head: bne {sthr.estackid} {sthr.stackid} udshmem-no-stack-tail",
            (5, sthrprint.printr('stack-root: estackid == stackid', [sthr.estackid, sthr.stackid])),
            # >>> free estackid, stackid
        ]
        sthr.free([sthr.estackid])
        
        sthr.tailnelems = 'alloc'
        actions += [
            # tailnelems = (stack_end - (src_end + 8)) >> 3
            # f"addi {sthr.src_end} {sthr.tmp} 8",
            f"addi {sthr.src_end} {sthr.tmp} 1",
            f"sub {sthr.stack_end} {sthr.tmp} {sthr.tailnelems}",
            (3, sthrprint.printr("stack-root: tailnelems(tailnbytes) = stack_end - src_end:", [sthr.tailnelems, sthr.stack_end, sthr.src_end])),
            f"sri {sthr.tailnelems} {sthr.tailnelems} 3",
            # src_end = src + (nelems-1) << 3
            f"mov_reg2reg {sthr.src_end} {sthr.end}",
            f"addi {sthr.end} {sthr.end} 8",
            
            f"sub {sthr.snelems} {sthr.tailnelems} {sthr.snelems}",
            (3, sthrprint.printr("stack-root: tailnelems(stack_end - src_end)", [sthr.tailnelems, sthr.stack_end, sthr.src_end, sthr.end, sthr.snelems])),
            # >>> free src_end, stack_start, tailnelems
        ]
        sthr.free([sthr.stack_end, sthr.src_end, sthr.stack_start, sthr.tailnelems])
        
        
        sthr.aligned_start = 'alloc'
        sthr.aligned_end = 'alloc'
        sthr.tmp2 = 'alloc'
        
        actions += [
            # now get the unaligned data
            f"udshmem-no-stack-tail: sri {sthr.start} {sthr.aligned_start} 6", # aligned_start = start >> 6 << 6 + (64 if start > aligned_start else 0)
            (4, sthrprint.printr("stack-root: SNELEMS-beforeAlignemnt:", [sthr.snelems])),
            f"sli {sthr.aligned_start} {sthr.aligned_start} 6",
            f"ble {sthr.start} {sthr.aligned_start} udshmem-start-aligned",
            # if segsize==64, then we need to add a block to it
            f"bnei {sthr.log2seg} 6 udshmem-log2seg-ne-6",
            f"movir {sthr.tmp} 1",
            f"add {sthr.log2seg} {sthr.log2maxnstacks} {sthr.tmp2}",
            f"sl {sthr.tmp} {sthr.tmp2} {sthr.tmp}",
            f"add {sthr.aligned_start} {sthr.tmp} {sthr.aligned_start}",
            # f"mov_reg2reg {sthr.aligned_start} {sthr.start}",
            # f"subi {sthr.aligned_start} {sthr.aligned_start} 64",
            (4, sthrprint.printr("stack-root: AlignedStart if log2seg==6:", [sthr.aligned_start, sthr.start, sthr.log2seg, sthr.tmp, sthr.tmp2])),
            f"jmp udshmem-start-aligned",
            f"udshmem-log2seg-ne-6: addi {sthr.aligned_start} {sthr.aligned_start} 64",
        ]
        sthr.free([sthr.log2seg, sthr.tmp2])
        
        sthr.nheads = 'alloc'
        sthr.ntails = 'alloc'
        # when log2seg==6, when start is from the block above, aligned_start is placed in the starting of the next block. aligned_start - start would be too large; given nheads cannot execeed 8
        # the mask should be 7
        sthr.nhead_mask = 'alloc' 
        actions += [
            # aligned_end = end >> 6 << 6, no need to +64 since the tail is already taken care of after
            f"udshmem-start-aligned: sri {sthr.end} {sthr.aligned_end} 6",
            (4, sthrprint.printr("stack-root: aligned_start:", [sthr.aligned_start, sthr.start])),
            f"sli {sthr.aligned_end} {sthr.aligned_end} 6",
            (3, sthrprint.printr("stack-root: aligned_end:", [sthr.aligned_end, sthr.end])),
            
            # nheads = (aligned_start - start) >> 3, ntail = (end - aligned_end) >> 3
            f"sub {sthr.aligned_start} {sthr.start} {sthr.nheads}",
            f"sri {sthr.nheads} {sthr.nheads} 3",
            f"movir {sthr.nhead_mask} 7",
            f"and {sthr.nheads} {sthr.nhead_mask} {sthr.nheads}",
            f"sub {sthr.end} {sthr.aligned_end} {sthr.ntails}",
            f"sri {sthr.ntails} {sthr.ntails} 3",
            (3, sthrprint.printr("stack-root: nheads=(aligned_start - start) >> 3", [sthr.nheads, sthr.aligned_start, sthr.start])),
            (3, sthrprint.printr("stack-root: ntail=(end - aligned_end) >> 3", [sthr.ntails, sthr.end, sthr.aligned_end])),
            # >>> free end
        ]
        sthr.free([sthr.end, sthr.nhead_mask])
        
        sthr.evw = 'alloc'
        sthr.tnwid = 'alloc'
        sthr.diff = 'alloc'
        actions += [
            f"sub {obdst} {obsrc} {sthr.diff}",
            (3, sthrprint.printr("stack-root: diff:", [sthr.diff, ('obdst', obdst), ('obsrc', obsrc)])),
            # if nheads==0 goto udshmem-no-head
            # snelems -= nhead
            f"beqi {sthr.nheads} 0 udshmem-no-head",
            f"sub {sthr.snelems} {sthr.nheads} {sthr.snelems}",
            (3, sthrprint.printr("stack-root: snelems(after - head):", [sthr.snelems, sthr.nheads])),
            f"addi {sthr.expect} {sthr.expect} 1",
            # send heads
            f"evii {sthr.evw} {self.em['udshmem-handle-head-tail']} 255 {0b0101}",
            f"mov_reg2reg NWID {sthr.tnwid}",
            f"addi {sthr.tnwid} {sthr.tnwid} 1",
            f"ev {sthr.evw} {sthr.evw} {sthr.tnwid} {sthr.tnwid} {0b1000}",
            (3, sthrprint.printr("stack-root: SENDING HEADS", [sthr.start, sthr.nheads, sthr.diff])),
            f"sendr3_wret {sthr.evw} {self.em['udshmem-ud-notify-stack-root']} {sthr.start} {sthr.nheads} {sthr.diff} {sthr.tmp}",
            # >>> free start, nheads, evw
        ]
        sthr.free([sthr.start, sthr.nheads])
        
        actions += [
            # if ntail==0 goto udshmem-no-tail
            f"udshmem-no-head: beqi {sthr.ntails} 0 udshmem-no-tail",
            (3, sthrprint.printr("stack-root: snelems(before -tail):", [sthr.snelems, sthr.ntails])),
            f"sub {sthr.snelems} {sthr.ntails} {sthr.snelems}",
            (3, sthrprint.printr("stack-root: snelems(after -tail):", [sthr.snelems, sthr.ntails])),
            f"addi {sthr.expect} {sthr.expect} 1",
            
            f"evii {sthr.evw} {self.em['udshmem-handle-head-tail']} 255 {0b0101}",
            f"mov_reg2reg NWID {sthr.tnwid}",
            f"addi {sthr.tnwid} {sthr.tnwid} 2",
            f"ev {sthr.evw} {sthr.evw} {sthr.tnwid} {sthr.tnwid} {0b1000}",
            f"sendr3_wret {sthr.evw} {self.em['udshmem-ud-notify-stack-root']} {sthr.aligned_end} {sthr.ntails} {sthr.diff} {sthr.tmp}",
            (3, sthrprint.printr("stack-root: SENDING TAILS:", [sthr.aligned_end, sthr.ntails, sthr.diff])),
            # >>> free ntail, aligned_end, tnwid, evw
        ]
        # print(sthr,sthr.ntails, sthr.aligned_end, sthr.tnwid, sthr.evw)
        sthr.free([sthr.ntails, sthr.aligned_end, sthr.tnwid, sthr.evw])
        
        
        sthr.nchunks = 'alloc'

        actions += [
            # nchunks = snelems >> 3
            f"udshmem-no-tail: sri {sthr.snelems} {sthr.nchunks} 3",
            (2, sthrprint.printr("stack-root: snelems-final:", [sthr.snelems])),
        ]
        
        ''' 
        LAUDSHMEM worker num estimator
        '''
        # naive worker num estimater
        # log2nworkers = nchunks >> 2
        # if log2nworkers <= 6 goto launch-ud
        # log2nworkers = 6
        # launch-ud: nworkers = 1 << log2nworkers
        # when 1024B per stack, there will be 16 chunks, then shfit 2 we got log2nworkers=4, 16 workers
        # when 2048B per stack, there will be 32 chunks, then shfit 2 we got log2nworkers=8, 64 workers; thus increasing the time; 
        sthr.log2nworkers = 'alloc'
        # actions += WorkEstimator(0, 0).genEstimateActions(sthr, sthrprint)
        actions += WorkEstimator(self.work_estimator_exp_scaler, self.work_estimator_scaler).genEstimateActions(sthr, sthrprint)
        
        sthr.rudid = 'alloc'
        sthr.base_nwid = 'alloc'
        sthr.lmbase = 'alloc'
        sthr.lmptr = 'alloc'
        actions += [
            f"launch-ud: movir {sthr.rudid} 0",
            f"mov_reg2reg NWID {sthr.base_nwid}",
            (2, sthrprint.printr("stack-root: nchunks:", [sthr.nchunks, sthr.log2nworkers, sthr.rudid, sthr.base_nwid])),
            f"addi X7 {sthr.lmbase} {self.lane_send_buffer_offset}",
            # (2, sthrprint.printr("stack-root: writing to ud-root:",[sthr.stackid, sthr.aligned_start, sthr.diff, sthr.nchunks, sthr.rudid, sthr.log2nworkers, ('oblog2blocksize', oblog2blocksize), ('oblog2maxnstacks', oblog2maxnstacks)])),
            (2, sthrprint.printr("stack-root: writing to ud-root:",[sthr.stackid, sthr.aligned_start, sthr.diff, sthr.nchunks, sthr.rudid, sthr.log2nworkers, sthr.log2blocksize, sthr.log2maxnstacks])),
            f"movir {sthr.lmptr} 0",
            f"movwrl {sthr.aligned_start} {sthr.lmbase}({sthr.lmptr},1,0)",
            f"movwrl {sthr.diff} {sthr.lmbase}({sthr.lmptr},1,0)",
            f"movwrl {sthr.nchunks} {sthr.lmbase}({sthr.lmptr},1,0)",
            f"movwrl {sthr.rudid} {sthr.lmbase}({sthr.lmptr},1,0)",
            f"movwrl {sthr.log2nworkers} {sthr.lmbase}({sthr.lmptr},1,0)",
            f"movwrl {sthr.log2blocksize} {sthr.lmbase}({sthr.lmptr},1,0)",
            f"movwrl {sthr.log2maxnstacks} {sthr.lmbase}({sthr.lmptr},1,0)",
            # >>> free log2nworkers
        ]
        # sthr.free(sthr.log2nworkers)
        sthr.free([sthr.log2nworkers, sthr.log2blocksize, sthr.log2maxnstacks])
  
        sthr.nreplys = 'alloc'
        sthr.tnwid = 'alloc'
        sthr.evw = 'alloc'
        actions += [
            f"movir {sthr.lmptr} 3",
            f"ud-loop: bgti {sthr.rudid} 3 ud-finishes-loop",
            # send(aligend_start, diff, nchunks, rudid, log2nworkers, log2blocksize, log2maxnstacks)
            # TODO: write data into LM buffer
            f"sli {sthr.rudid} {sthr.tnwid} 6",
            f"add {sthr.base_nwid} {sthr.tnwid} {sthr.tnwid}",
            f"evii {sthr.evw} {self.em['udshmem-ud-root']} 255 {0b0101}",
            f"ev {sthr.evw} {sthr.evw} {sthr.tnwid} {sthr.tnwid} {0b1000}",
            f"movwrl {sthr.rudid} {sthr.lmbase}({sthr.lmptr},0,0)",
            (5, sthrprint.printr("stack-root: sending to ud-root,", [sthr.rudid, sthr.tnwid, sthr.lmbase, sthr.lmptr])),
            f"send_wret {sthr.evw} {self.em['udshmem-ud-notify-stack-root']} {sthr.lmbase} 8 {sthr.tmp}",
            f"addi {sthr.rudid} {sthr.rudid} 1",
            f"jmp ud-loop",
            f"ud-finishes-loop: movir {sthr.nreplys} 0",
            f"addi {sthr.expect} {sthr.expect} 4",
            f"yield",
        ] 
        self.appendTranActions(tran, actions)
        
        
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.em['udshmem-ud-notify-stack-root'])
        # nreplys += 1
        actions = []
        if self.debug_level:
            actions +=[
                (3, sthrprint.printr("notify-stack-root: replys", [('obrudid', 'X8'), ('childccont', 'X9'), ('childevw', 'X10') ]))
            ]
        actions += [
            (3, sthrprint.printr("notify-stack-root: nreplys", [sthr.expect, sthr.nreplys])),
            f"addi {sthr.nreplys} {sthr.nreplys} 1",
            f"ble {sthr.expect} {sthr.nreplys} udshmem-ud-notify-stack-root-done",
            f"yield",
            f"udshmem-ud-notify-stack-root-done: sendr_reply X31 X30 {sthr.tmp}",
            (3, sthrprint.printr("notify-stack-root: nreplys", [sthr.expect, sthr.nreplys])),
            f"yieldt",
        ]
        self.appendTranActions(tran, actions)
        # endregion stack-root
        #------------------------------------------------udshmem-stack-root------------------------------------------------
        
        
        #------------------------------------------------udshmem-ud-root------------------------------------------------
        # region ud-root
        udthr = AdvancedRegister()
        udthrprint = RegPrinter(udthr)
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.em['udshmem-ud-root'])
        # obs: obaligned_start, obdiff, obnchunks, obrudid, oblog2nworkers, oblog2blocksize, oblog2maxnstacks
        # this simply distributes the workload to workers
        obaligned_start = "X8"
        obdiff = "X9"
        obnchunks = "X10"
        obrudid = "X11"
        oblog2nworkers = "X12"
        oblog2blocksize = "X13"
        oblog2maxnstacks = "X14"
        udthr.lmbase = 'alloc'
        udthr.lmptr = 'alloc'
        udthr.tmp = 'alloc'
        udthr.tmp1 = 'alloc'
        udthr.lanemask = 'alloc'
        udthr.base_nwid = 'alloc'
        udthr.nworkers = 'alloc'
        udthr.widx = 'alloc'
        udthr.widx_end = 'alloc'
        udthr.nreplys = 'alloc'
        udthr.expect = 'alloc'
        udthr.evw = 'alloc'
        udthr.tnwid = 'alloc'
        udthr.pstackid = 'alloc'
        udthr.rudid = 'alloc'
        actions = []
        if self.debug_level:
            actions += [
                f"sri NWID {udthr.pstackid} 8",
                f"addi {obrudid} {udthr.rudid} 0",
                (4, udthrprint.printr("ud-root: pstackid", [udthr.pstackid, ('obaligned_start', obaligned_start), ('obdiff', obdiff), ('obnchunks', obnchunks), ('obrudid', obrudid), ('oblog2nworkers', oblog2nworkers), ('oblog2blocksize', oblog2blocksize), ('oblog2maxnstacks', oblog2maxnstacks)])),    
            ]
        
        actions += [
            # nworkers = 1 << log2nworkers, nworkers per ud
            f"movir {udthr.nworkers} 1",
            f"sl {udthr.nworkers} {oblog2nworkers} {udthr.nworkers}",
            
            # widx = rudid << log2nworkers
            f"sl {obrudid} {oblog2nworkers} {udthr.widx}",
            # widx_end = widx + nworkers
            f"add {udthr.widx} {udthr.nworkers} {udthr.widx_end}",
            (4, udthrprint.printr("ud-root: widx, widx_end", [udthr.pstackid, udthr.widx, udthr.widx_end, udthr.nworkers, ('obrudid', obrudid), ('oblog2nworkers', oblog2nworkers)])),
            
            # write unchanged data to LM buffer
            f"addi X7 {udthr.lmbase} {self.lane_send_buffer_offset}",
            f"movir {udthr.lmptr} 0",
            f"movwrl {obaligned_start} {udthr.lmbase}({udthr.lmptr},1,0)",
            f"movwrl {obdiff} {udthr.lmbase}({udthr.lmptr},1,0)",
            f"movwrl {obnchunks} {udthr.lmbase}({udthr.lmptr},1,0)",
            f"movwrl {udthr.widx} {udthr.lmbase}({udthr.lmptr},1,0)",
            f"movwrl {oblog2nworkers} {udthr.lmbase}({udthr.lmptr},1,0)",
            f"movwrl {oblog2blocksize} {udthr.lmbase}({udthr.lmptr},1,0)",
            f"movwrl {oblog2maxnstacks} {udthr.lmbase}({udthr.lmptr},1,0)",
            # we will update lm[3] which is udthr.widx
            f"movir {udthr.lmptr} 3",
            f"movir {udthr.lanemask} 63",
            f"mov_reg2reg NWID {udthr.base_nwid}",
            (4, udthrprint.printr("ud-root:", [('obaligned_start', obaligned_start),('obdiff',obdiff),('obnchunks', obnchunks), ('obrudid', obrudid), ('oblog2nworkers', oblog2nworkers), ('oblog2blocksize', oblog2blocksize), ('oblog2maxnstacks', oblog2maxnstacks)])),
            f"launch-worker-loop: ble {udthr.widx_end} {udthr.widx} worker-loop-done",
            f"movwrl {udthr.widx} {udthr.lmbase}({udthr.lmptr},0,0)",
            # tnwid = base_nwid + widx % 64
            f"and {udthr.widx} {udthr.lanemask} {udthr.tnwid}",
            f"add {udthr.base_nwid} {udthr.tnwid} {udthr.tnwid}",
            f"evii {udthr.evw} {self.em['udshmem-general-worker-read']} 255 {0b0101}",
            f"ev {udthr.evw} {udthr.evw} {udthr.tnwid} {udthr.tnwid} {0b1000}",
            (5, udthrprint.printr("ud-root: sending to general-worker-read", [udthr.widx, udthr.widx_end, udthr.tnwid])),
            f"send_wret {udthr.evw} {self.em['udshmem-worker-notify-ud-root']} {udthr.lmbase} 8 {udthr.tmp}",
            f"addi {udthr.widx} {udthr.widx} 1",
            f"jmp launch-worker-loop",
            f"worker-loop-done: movir {udthr.nreplys} 0",
            f"mov_reg2reg {udthr.nworkers} {udthr.expect}",
            f"yield",
        ]
        self.appendTranActions(tran, actions)
        
        
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.em['udshmem-worker-notify-ud-root'])
        
        actions = [
            (3, udthrprint.printr("worker-notify-ud-root: worker replies", [udthr.expect, udthr.nreplys])),
            f"addi {udthr.nreplys} {udthr.nreplys} 1",
            f"ble {udthr.expect} {udthr.nreplys} udshmem-worker-notify-ud-root-done",
            f"yield",
            f"udshmem-worker-notify-ud-root-done: sendr3_reply {udthr.rudid} X1 X2 {udthr.tmp}",
            (3, udthrprint.printr("worker-notify-ud-root: SEND_REPLY", [('CCONT', 'X1'), ('EVW', 'X2')])),
            f"yieldt",
        ]
        self.appendTranActions(tran, actions)
        
        # endregion ud-root
        #------------------------------------------------udshmem-ud-root------------------------------------------------
        
    
        #===============================================udshmem-work-distributor=========================================
        # endregion udshmem-distributor
        
        
        
        #region udshmem-workers
        #==================================================udshmem-worker================================================
        
        #-----------------------------------------------udshmem-genral-worker-read----------------------------------------
        # region general-worker-read
        wthr = AdvancedRegister()
        wthrprint = RegPrinter(wthr)
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.em['udshmem-general-worker-read'])
        # obs: obaligned_start, obdiff, obnchunks, obwidx, oblog2nworkers, oblog2blocksize, oblog2maxnstacks
        obaligned_start = "X8"
        obdiff = "X9"
        obnchunks = "X10"
        obwidx = "X11"
        oblog2nworkers = "X12"
        oblog2blocksize = "X13"
        oblog2maxnstacks = "X14"
        
        wthr.nworkers = 'alloc'
        wthr.log2tnworkers = 'alloc'
        wthr.mask = 'alloc'
        wthr.stackid = 'alloc'
        actions = []
        if self.debug_level:
            actions +=[
                f"sri NWID {wthr.stackid} 8",
                (4, wthrprint.perflogr(pmap['worker-starts'], "WORKER-START.", [])),
                (4, wthrprint.printr("general-worker-read:", [wthr.stackid, ('obaligned_start', obaligned_start), ('obdiff', obdiff), ('obnchunks', obnchunks), ('obwidx', obwidx), ('oblog2nworkers', oblog2nworkers), ('oblog2blocksize', oblog2blocksize), ('oblog2maxnstacks', oblog2maxnstacks)])),
            ]
        
        actions += [
            # (4, wthrprint.printr("general-worker-read:", [('obaligned_start', obaligned_start), ('obdiff', obdiff), ('obnchunks', obnchunks), ('obwidx', obwidx), ('oblog2nworkers', oblog2nworkers), ('oblog2blocksize', oblog2blocksize), ('oblog2maxnstacks', oblog2maxnstacks)])),
            # nworkers = 1 << (log2nworkers + 2); now we assume we always use all 4uds
            f"movir {wthr.nworkers} 1",
            f"addi {oblog2nworkers} {wthr.log2tnworkers} 2",
            f"sl {wthr.nworkers} {wthr.log2tnworkers} {wthr.nworkers}",
            
            # mask = nworkers - 1
            f"subi {wthr.nworkers} {wthr.mask} 1",
            # >>> free nworkers
        ]
        wthr.free(wthr.nworkers)
        
        wthr.fdnchunks = 'alloc'
        actions += [
            # fdnchunks = nchunks >> log2tnworkers
            f"sr {obnchunks} {wthr.log2tnworkers} {wthr.fdnchunks}",
            # >>> free log2tnworkers
        ]
        wthr.free(wthr.log2tnworkers)
        
        wthr.rmnchunks = 'alloc'
        actions += [
            # rmnchunks = nchunks & mask
            f"and {obnchunks} {wthr.mask} {wthr.rmnchunks}",
            # >>> free mask
        ]
        wthr.free(wthr.mask)
        
        wthr.wnchunks = 'alloc'
        wthr.initoffset = 'alloc'
        wthr.tmp = 'alloc'
        wthr.stripe = 'alloc'
        wthr.log2seg = 'alloc'
        wthr.maxnstacks = 'alloc'
        wthr.dstripe = 'alloc'
        actions += [
            # wnchunks = fdnchunks + (widx < rmnchunks)
            f"cgt {wthr.rmnchunks} {obwidx} {wthr.tmp}",
            f"add {wthr.fdnchunks} {wthr.tmp} {wthr.wnchunks}",
           
            # stripe = maxnstacks << (log2blocksize-3) # assume always 8 stacks
            f"movir {wthr.maxnstacks} 1",
            f"sl {wthr.maxnstacks} {oblog2maxnstacks} {wthr.maxnstacks}",
            f"subi {oblog2blocksize} {wthr.log2seg} 3", # assume always 8 stacks
            f"sl {wthr.maxnstacks} {wthr.log2seg} {wthr.stripe}", # do not free stripe
            f"subi {wthr.maxnstacks} {wthr.maxnstacks} 1",
            f"sl {wthr.maxnstacks} {wthr.log2seg} {wthr.dstripe}", # do not free dstripe
            
            # initoffset = fdnchunks * widx + (widx if widx < rmnchunks else rmnchunks)
            # initoffset = initoffset << 3 
            f"mul {wthr.fdnchunks} {obwidx} {wthr.initoffset}", # chunk offset
            (4, wthrprint.printr("general-worker-read: wnchunks:", [wthr.stackid, ('obwidx', obwidx),  wthr.wnchunks, wthr.fdnchunks, wthr.initoffset, wthr.rmnchunks, ('obwidx', obwidx)])),
            
            # >>> free fdnchunks
        ]
        wthr.free([wthr.fdnchunks, wthr.maxnstacks])
        actions += [
            f"bgt {wthr.rmnchunks} {obwidx} udshmem-initoffset-pick-widx",
            f"mov_reg2reg {wthr.rmnchunks} {wthr.tmp}",
            f"jmp udshmem-cont-initoffset",
            f"udshmem-initoffset-pick-widx: mov_reg2reg {obwidx} {wthr.tmp}",
            f"udshmem-cont-initoffset: add {wthr.tmp} {wthr.initoffset} {wthr.initoffset}",
            f"sli {wthr.initoffset} {wthr.initoffset} 6", # 3 for chunk->8 words and 3 for 8 words->64 bytes
            # >>> free rmnchunks
        ]
        wthr.free(wthr.rmnchunks)
        
        wthr.aligned_start = 'alloc'
        wthr.aligned_base = 'alloc'
        wthr.head = 'alloc'
        actions += [
            # aligned_base = aligned_start >> log2seg << log2seg
            f"sr {obaligned_start} {wthr.log2seg} {wthr.aligned_base}",
            f"sl {wthr.aligned_base} {wthr.log2seg} {wthr.aligned_base}",
            (4, wthrprint.printr("general-worker-read, check-worker-write: aligned_base:", [wthr.stackid, ('obwidx', obwidx), wthr.aligned_base, wthr.log2seg])),
            # head = aligned_start - aligned_base
            f"sub {obaligned_start} {wthr.aligned_base} {wthr.head}",
            # initoffset = head + initoffset
            f"add {wthr.head} {wthr.initoffset} {wthr.initoffset}",
            # >>> free aligned_start, aligned_base
        ]
        wthr.free([wthr.aligned_start])
        
        wthr.segmask = 'alloc' # do not free
        wthr.rminitoffset = 'alloc' 
        wthr.nsstripe = 'alloc'
        actions += [
            # nsstripe = initoffset >> log2seg , stack stripe
            f"sr {wthr.initoffset} {wthr.log2seg} {wthr.nsstripe}",
            (4, wthrprint.printr("general-worker-read: nsstripe:", [wthr.stackid,  ('obwidx', obwidx), wthr.nsstripe, wthr.initoffset, wthr.log2seg])),
            # segmask = (1 << log2seg) - 1
            f"movir {wthr.segmask} 1",
            f"sl {wthr.segmask} {wthr.log2seg} {wthr.segmask}",
            f"subi {wthr.segmask} {wthr.segmask} 1", # do not free segmask
            
            # rminitoffset = initoffset & segmask
            f"and {wthr.initoffset} {wthr.segmask} {wthr.rminitoffset}",
            # f"sli {wthr.rminitoffset} {wthr.rminitoffset} 3",
            # >>> free initoffset
           
        ]
        wthr.free(wthr.initoffset)
        
        wthr.ldptr = 'alloc'
        actions += [
            # ldptr = aligned_base + nsstripe * stripe + rminitoffset
            f"mul {wthr.nsstripe} {wthr.stripe} {wthr.ldptr}",
            f"add {wthr.aligned_base} {wthr.ldptr} {wthr.ldptr}",
            f"add {wthr.rminitoffset} {wthr.ldptr} {wthr.ldptr}",
            (4, wthrprint.printr("general-worker-read: rminitoffset:", [wthr.stackid, ('obrudid', obrudid), wthr.rminitoffset, wthr.nsstripe, wthr.segmask])),
            # >>> free aligned_base, rmintoffset, nsstripe
            # allocate strptr
        ]
        wthr.free([wthr.aligned_base, wthr.rminitoffset, wthr.nsstripe, wthr.stripe])
        wthr.strptr = 'alloc' # do not free
        wthr.diff = 'alloc' # do not free
        wthr.maxout = 'alloc' # do not free
        wthr.nout = 'alloc' # do not free
        wthr.ld_nleft = 'alloc' # do not free
        wthr.st_nleft = 'alloc' # do not free
        wthr.evw = 'alloc'
        if self.debug_level:
            wthr.pnelems = 'alloc'
        actions += [
            # ld_nleft = wnchunks << 3
            # st_nleft = wnchunks << 3
            f"sli {wthr.wnchunks} {wthr.ld_nleft} 3",
            f"sli {wthr.wnchunks} {wthr.st_nleft} 3",
            # >>> free wnchunks, maybe not this time
            # maxout = 64
            # TODO: how can we adjust this?
            f"movir {wthr.maxout} {self.throttle}",
            f"movir {wthr.nout} 0",
            # if ld_nleft <= 0, goto terminate
            (5, wthrprint.printr("GENERAL-WORKER-READ: Before sending read event", [wthr.stackid, wthr.ldptr, ('obdiff', obdiff), wthr.strptr, wthr.ld_nleft, wthr.st_nleft, ('maxout', wthr.maxout)])),
            f"blei {wthr.ld_nleft} 0 udshmem-worker-terminate",
            f"addi {obdiff} {wthr.diff} 0",
            # send the event to itself, with current thread context and contw=X1
        ]
        
        if self.impl == 'loc-aware-throttled':
            actions += [
                f"evi X2 {wthr.evw} {self.em['udshmem-worker-read-throttled']} {0b0001}",
                ]
        elif self.impl == 'loc-aware-interleaving' or self.impl == self.implLocAwareWithConfig: # default use interleaving
            actions += [
                f"evi X2 {wthr.evw} {self.em['udshmem-worker-interleaving-read-write']} {0b0001}",
                ]
        elif self.impl == 'loc-aware-ev-read-loop':
            actions += [
                f"evi X2 {wthr.evw} {self.em['udshmem-worker-ev-read-loop']} {0b0001}",
                ]
        else:
            actions += [
                f"evi X2 {wthr.evw} {self.em['udshmem-worker-read']} {0b0001}",
            ]
            
        actions += [f"sendr_wcont {wthr.evw} X1 {wthr.ldptr} {wthr.maxout}"]
        # >>> free evw    
        wthr.free(wthr.evw)
        
        actions += [
            f"yield",
            f"udshmem-worker-terminate: sendr_reply X31 X30 {wthr.tmp}",
            (4, wthrprint.printr("general-worker-read: terminate", [wthr.stackid, wthr.ldptr, ('obdiff', obdiff), wthr.strptr, wthr.ld_nleft, wthr.st_nleft, ('maxout', wthr.maxout)])),
            f"yieldt",
        ]
        self.appendTranActions(tran, actions)
        # endregion general-worker-read
        #-----------------------------------------------------general-worker-read-----------------------------------------------------
        
        
        #-----------------------------------------------------WORKER-READ-----------------------------------------------------
        # region worker-read
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.em['udshmem-worker-read'])
        wthr.inc = 'alloc'
        
        actions = []
        if self.perflog_level:
            actions += [
                f"sli {wthr.wnchunks} {wthr.pnelems} 3",
                f"bne {wthr.pnelems} {wthr.ld_nleft} read-loop",
                (4, wthrprint.perflogr(pmap['worker-read-starts'], "WORKER-READ-START.", [])),
            ]
        
        
        actions += [   
            # split shi into two event
            (5, wthrprint.printr("WORKER-READ:", [wthr.stackid, wthr.ldptr, wthr.diff, wthr.strptr, wthr.ld_nleft, wthr.st_nleft, ('maxout', wthr.maxout)])),
            f"read-loop: send_dmlm_ld_wret {wthr.ldptr} {self.em['udshmem-worker-write-8']} 8 {wthr.tmp}",
            f"addi {wthr.ldptr} {wthr.ldptr} 64",
            
            # inc = 0; if ldptr & segmask: inc=1 ; if inc==1 meaning their is remainder, inc-1 as mask would mask out all the stripes; 
            # if inc==0 meaning no remainder, inc-1 as mask would mask out nothing.
            f"and {wthr.ldptr} {wthr.segmask} {wthr.tmp}",
            f"movir {wthr.inc} 0",
            f"cgti {wthr.tmp} {wthr.inc} 0", # if tmp > 0, inc would be 1. has tmp meaning it has remainder, meaning we still has reach the turning point
            f"subi {wthr.inc} {wthr.inc} 1",
            f"and {wthr.dstripe} {wthr.inc} {wthr.inc}",
            f"add {wthr.ldptr} {wthr.inc} {wthr.ldptr}",
            f"subi {wthr.ld_nleft} {wthr.ld_nleft} 8", # one chunk gone!, each chunk is 8*8B
            (5, wthrprint.printr("WORKER-READ:", [wthr.stackid, wthr.inc, wthr.dstripe, wthr.ldptr, wthr.ld_nleft, wthr.st_nleft, ('maxout', wthr.maxout)])),
            f"blei {wthr.ld_nleft} 0 udshmem-worker-done",
            f"jmp read-loop",
           
        ]
        if self.perflog_level:
            actions += [
                f"udshmem-worker-done: addi {wthr.pnelems} {wthr.pnelems} 0",
                (4, wthrprint.perflogr(pmap['worker-read-ends'],"WORKER-READ-ENDS.", [])),
                f"yield",
            ]
        else:
            actions += [
                 f"udshmem-worker-done: yield",
            ]

        wthr.free(wthr.inc)
        self.appendTranActions(tran, actions)
        # endregion worker-read
        #-----------------------------------------------------WORKER-READ-----------------------------------------------------
        
        
                
        #-----------------------------------------------------WORKER-READ-THROTTLED-----------------------------------------------------
        # region worker-read-throttled
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.em['udshmem-worker-read-throttled'])
        wthr.inc = 'alloc'
        
        actions = []
        if self.perflog_level:
            actions += [
                f"sli {wthr.wnchunks} {wthr.pnelems} 3",
                f"bne {wthr.pnelems} {wthr.ld_nleft} read-loop",
                (6, wthrprint.perflogr(pmap['worker-read-starts'], "WORKER-READ-THROTTLED-START.", [])),
            ]
        
        
        actions += [   
            # split shi into two event
            (3, wthrprint.printr("WORKER-READ-THROTTLED:", [wthr.stackid, wthr.ldptr, wthr.diff, wthr.strptr, wthr.ld_nleft, wthr.st_nleft, wthr.nout, ('maxout', wthr.maxout)])),
            # f"read-loop: send_dmlm_ld_wret {wthr.ldptr} {self.em['udshmem-worker-write-8-throttled']} 8 {wthr.tmp}",
            f"read-loop: blei {wthr.ld_nleft} 0 udshmem-worker-done",
            f"ble {wthr.maxout} {wthr.nout} udshmem-worker-wait",
            f"send_dmlm_ld_wret {wthr.ldptr} {self.em['udshmem-worker-write-8']} 8 {wthr.tmp}", # not throttling write but ack will know
            f"addi {wthr.ldptr} {wthr.ldptr} 64",
            
            # inc = 0; if ldptr & segmask: inc=1 ; if inc==1 meaning their is remainder, inc-1 as mask would mask out all the stripes; 
            # if inc==0 meaning no remainder, inc-1 as mask would mask out nothing.
            f"and {wthr.ldptr} {wthr.segmask} {wthr.tmp}",
            f"movir {wthr.inc} 0",
            f"cgti {wthr.tmp} {wthr.inc} 0", # if tmp > 0, inc would be 1. has tmp meaning it has remainder, meaning we still has reach the turning point
            f"subi {wthr.inc} {wthr.inc} 1",
            f"and {wthr.dstripe} {wthr.inc} {wthr.inc}",
            f"add {wthr.ldptr} {wthr.inc} {wthr.ldptr}",
            f"subi {wthr.ld_nleft} {wthr.ld_nleft} 8", # one chunk gone!, each chunk is 8*8B
            # (6, wthrprint.printr("WORKER-READ-THROTTLED:", [wthr.stackid, wthr.inc, wthr.dstripe, wthr.ldptr, wthr.ld_nleft, wthr.st_nleft,  ('maxout', wthr.maxout)])),
            (5, wthrprint.printr("WORKER-READ-THROTTLED:", [wthr.stackid, wthr.ld_nleft, wthr.st_nleft, wthr.pnelems, wthr.nout, ('maxout', wthr.maxout)])),
            f"addi {wthr.nout} {wthr.nout} 1",
            # f"blei {wthr.ld_nleft} 0 udshmem-worker-done",
            f"jmp read-loop",
           
        ]
        if self.perflog_level:
            actions += [
                f"udshmem-worker-done: addi {wthr.pnelems} {wthr.pnelems} 0",
                (4, wthrprint.perflogr(pmap['worker-read-ends'],"WORKER-READ-THROTTLED-ENDS.", [])),
                f"yield",
            ]
        else:
            actions += [
                 f"udshmem-worker-done: yield",
            ]
        actions +=[
            f"udshmem-worker-wait: yield",
        ]

        wthr.free(wthr.inc)
        self.appendTranActions(tran, actions)
        # endregion worker-read
        #-----------------------------------------------------WORKER-READ-THROTTLED-----------------------------------------------------
        
        
        #-----------------------------------------------------WORKER-WRITE-ACK-----------------------------------------------------
        # region worker-write-ack
        # need to allocate and free tmp registers otherwise it won't be enough
        def _ev_write(C=8):
            chunk_size = C if C <= 8 else 8
            addr_reg = 'X' + str((chunk_size + 8) if chunk_size < 8 else 3)
            tran = self.state.writeTransition("eventCarry", self.state, self.state, self.em[f'udshmem-worker-write-{C}'])
        
            actions = [
                (5, wthrprint.printr(f"worker-write-{C}: WRITE DRAM", [wthr.stackid, wthr.ldptr, wthr.diff, wthr.strptr, wthr.ld_nleft, wthr.st_nleft, ('addr_reg', addr_reg)]) ),
            ]
            if self.debug_level > 3:
                for i in range(C):
                    actions +=[
                        # (4, wthrprint.printr(f"worker-write-{C}: WRITE DRAM", [wthr.stackid, wthr.ldptr, wthr.diff, wthr.strptr, wthr.ld_nleft, wthr.st_nleft, ('addr_reg', addr_reg)])),
                        (5, wthrprint.printr(f"worker-write-{C}: WRITE DRAM", [(f'op{i}', f'X{8+i}')])),
                    ]
            if self.perflog_level:
                if self.impl != self.implLocAwareEvLoop:  
                    actions += [
                        f"bne {wthr.pnelems} {wthr.st_nleft} udshmem-write-cont",
                        (4, wthrprint.perflogr(pmap['worker-write-starts'], "WORKER-WRITE-START.", [])),
                    ]
                
            # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ REAL WRITE~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            actions += [
                f"udshmem-write-cont: add {wthr.diff} {addr_reg} {wthr.strptr}",
                f"sendops_dmlm_wret {wthr.strptr} {self.em[f'udshmem-worker-ack-{C}']} X8 {chunk_size} {wthr.tmp}",
            ]
            # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ REAL WRITE~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            if self.perflog_level:
                if self.impl != self.implLocAwareEvLoop:
                    actions +=[
                        f"subi {wthr.pnelems} {wthr.pnelems} {chunk_size}", 
                        f"bgti {wthr.pnelems} 0 udshmem-no-more-read",
                        (4, wthrprint.perflogr(pmap['worker-write-ends'], "WORKER-WRITE-ENDS.", []) ),
                    ]
            
            actions +=[
                f"blei {wthr.ld_nleft} 0 udshmem-no-more-read",
                # TODO: Needs throttling here
                f"udshmem-no-more-read: yield",
            ]
            self.appendTranActions(tran, actions)
            
        
        def _ev_ack(C=8):
            wthr.acnelems = 'alloc'
            
            tran = self.state.writeTransition("eventCarry", self.state, self.state, self.em[f'udshmem-worker-ack-{C}'])
            actions = [(5,wthrprint.printr(f"worker-ack-{C}: ACK", [wthr.stackid, wthr.ldptr, wthr.diff, wthr.strptr, wthr.ld_nleft, wthr.st_nleft, ('maxout', wthr.maxout)])),]
            if self.perflog_level:
                actions += [
                    f"sli {wthr.wnchunks} {wthr.acnelems} 3",
                    f"bne {wthr.acnelems} {wthr.st_nleft} ack-cont",
                    (4, wthrprint.perflogr(pmap['worker-ack-starts'], "WORKER-ACK-STARTS.", [])),
                ]
            wthr.free(wthr.acnelems)
            actions += [  
                f"ack-cont: subi {wthr.st_nleft} {wthr.st_nleft} {C}",
                (4, wthrprint.printr(f"worker-ack-{C}: ACK", [wthr.stackid, wthr.ld_nleft, wthr.st_nleft, wthr.nout, ('maxout', wthr.maxout)])),
            ]
            
            actions += [
                f"blei {wthr.st_nleft} 0 udshmem-worker-ack-{C}-done",
            ]
            wthr.evw = 'alloc'
            if self.impl == 'loc-aware-throttled' and C==8:
                actions +=[
                    f"subi {wthr.nout} {wthr.nout} 1",
                    f"bgt {wthr.maxout} {wthr.nout} udshmem-worker-wake",
                    f"yield",
                    f"udshmem-worker-wake: blei {wthr.ld_nleft} 0 udshmem-no-more-read",
                    (4, wthrprint.printr(f"worker-ack-{C}: RESUMING READ", [wthr.stackid, wthr.ld_nleft, wthr.st_nleft, wthr.nout, ('maxout', wthr.maxout)])),
                    f"evi X2 {wthr.evw} {self.em['udshmem-worker-read-throttled']} {0b0001}",
                    f"sendr_wcont {wthr.evw} X1 {wthr.ldptr} {wthr.maxout}",
                ]
            actions += [
                f"udshmem-no-more-read: yield",
                f"udshmem-worker-ack-{C}-done: sendr3_reply {wthr.stackid} X1 X2 {wthr.tmp}",
                (4, wthrprint.perflogr(pmap['worker-ends'], "WORKER-ACK-ENDS.", [])),
                (4, wthrprint.printr(f"worker-ack-{C}: send reply to",[('CCONT','X1'), ('CEVW', 'X2')])),
                (4, wthrprint.printr(f"worker-ack-{C}: DONE", [wthr.stackid, wthr.ldptr, wthr.diff, wthr.strptr, wthr.ld_nleft, wthr.st_nleft, ('maxout', wthr.maxout)])) ,
                f"yieldt",
            ]
            wthr.free(wthr.evw)
            self.appendTranActions(tran, actions)
        # endregion worker-write-ack
        #-----------------------------------------------------WORKER-WRITE-ACK-----------------------------------------------------
        
        
        #-----------------------------------------------------WORKER-WRITE-ACK-THROTTLED-----------------------------------------------------
        # region worker-write-ack-throttled
        # need to allocate and free tmp registers otherwise it won't be enough
        def _ev_write_throttled_old(C=8):
            chunk_size = C if C <= 8 else 8
            addr_reg = 'X' + str((chunk_size + 8) if chunk_size < 8 else 3)
            tran = self.state.writeTransition("eventCarry", self.state, self.state, self.em[f'udshmem-worker-write-{C}-throttled'])
        
            actions = [
                (5, wthrprint.printr(f"worker-write-{C}-throttled: WRITE DRAM", [wthr.stackid, wthr.ldptr, wthr.diff, wthr.strptr, wthr.ld_nleft, wthr.st_nleft, ('addr_reg', addr_reg)]) ),
            ]
            if self.debug_level > 3:
                for i in range(C):
                    actions +=[
                        # (4, wthrprint.printr(f"worker-write-{C}: WRITE DRAM", [wthr.stackid, wthr.ldptr, wthr.diff, wthr.strptr, wthr.ld_nleft, wthr.st_nleft, ('addr_reg', addr_reg)])),
                        (5, wthrprint.printr(f"worker-write-{C}-throttled: WRITE DRAM", [(f'op{i}', f'X{8+i}')])),
                    ]
            if self.perflog_level:
                actions += [
                    # f"bne {wthr.pnelems} {wthr.st_nleft} udshmem-write-cont",
                    # (4, wthrprint.perflogr(pmap['worker-write-starts'], "WORKER-WRITE-THROTTLED-START.", [])),
                ]
                
            # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ REAL WRITE~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            actions += [
                f"udshmem-write-cont: add {wthr.diff} {addr_reg} {wthr.strptr}",
                f"sendops_dmlm_wret {wthr.strptr} {self.em[f'udshmem-worker-ack-{C}']} X8 {chunk_size} {wthr.tmp}",
                f"subi {wthr.nout} {wthr.nout} 1",
                f"bgt {wthr.maxout} {wthr.nout} udshmem-worker-wake",
                f"yield",
            ]
            # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ REAL WRITE~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            if self.perflog_level:
                actions +=[
                    f"subi {wthr.pnelems} {wthr.pnelems} {chunk_size}", 
                    f"bgti {wthr.pnelems} 0 udshmem-no-more-read",
                    (4, wthrprint.perflogr(pmap['worker-write-ends'], "WORKER-WRITE-THROTTLED-ENDS.", []) ),
                ]
            wthr.evw = 'alloc'
            actions +=[
                
                f"udshmem-worker-wake: blei {wthr.ld_nleft} 0 udshmem-no-more-read",
                f"evi X2 {wthr.evw} {self.em['udshmem-worker-read-throttled']} {0b0001}", 
                f"sendr_wcont {wthr.evw} X1 {wthr.ldptr} {wthr.maxout}",
                # TODO: Needs throttling here
                f"udshmem-no-more-read: yield",
            ]
            wthr.free(wthr.evw)
            self.appendTranActions(tran, actions)
            
        # endregion worker-write-ack-throttled
        #-----------------------------------------------------WORKER-WRITE-ACK-THROTTLED-----------------------------------------------------
            
    
        #-----------------------------------------------------INTERLEAVING-READ-WRITE-------------------------------------------------------
        # region interleaving-read-write
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.em['udshmem-worker-interleaving-read-write'])
        wthr.inc = 'alloc'
        actions = []    
        actions += [   
            # split this into two event
            (3, wthrprint.printr("WORKER-READ-INTERLEAVING:", [wthr.stackid, wthr.ldptr, wthr.diff, wthr.strptr, wthr.ld_nleft, wthr.st_nleft, wthr.nout, ('maxout', wthr.maxout)])),
            # f"read-loop: send_dmlm_ld_wret {wthr.ldptr} {self.em['udshmem-worker-write-8-throttled']} 8 {wthr.tmp}",
            f"read-loop: blei {wthr.ld_nleft} 0 udshmem-worker-done",
            f"ble {wthr.maxout} {wthr.nout} udshmem-worker-done",
            f"send_dmlm_ld_wret {wthr.ldptr} {self.em['udshmem-worker-interleaving-write']} 8 {wthr.tmp}", # not throttling write but ack will know
            f"addi {wthr.ldptr} {wthr.ldptr} 64",
            
            # inc = 0; if ldptr & segmask: inc=1 ; if inc==1 meaning their is remainder, inc-1 as mask would mask out all the stripes; 
            # if inc==0 meaning no remainder, inc-1 as mask would mask out nothing.
            f"and {wthr.ldptr} {wthr.segmask} {wthr.tmp}",
            f"movir {wthr.inc} 0",
            f"cgti {wthr.tmp} {wthr.inc} 0", # if tmp > 0, inc would be 1. has tmp meaning it has remainder, meaning we still has reach the turning point
            f"subi {wthr.inc} {wthr.inc} 1",
            f"and {wthr.dstripe} {wthr.inc} {wthr.inc}",
            f"add {wthr.ldptr} {wthr.inc} {wthr.ldptr}",
            f"subi {wthr.ld_nleft} {wthr.ld_nleft} 8", # one chunk gone!, each chunk is 8*8B
            # (6, wthrprint.printr("WORKER-READ-THROTTLED:", [wthr.stackid, wthr.inc, wthr.dstripe, wthr.ldptr, wthr.ld_nleft, wthr.st_nleft,  ('maxout', wthr.maxout)])),
            (5, wthrprint.printr("WORKER-READ-INTERLEAVING:", [wthr.stackid, wthr.ld_nleft, wthr.st_nleft, wthr.pnelems, wthr.nout, ('maxout', wthr.maxout)])),
            f"addi {wthr.nout} {wthr.nout} 1",
            # f"blei {wthr.ld_nleft} 0 udshmem-worker-done",
            f"jmp read-loop",
            f"udshmem-worker-done: yield",
            f"udshmem-worker-wait: yield",
        ]
  
        wthr.free(wthr.inc)
        self.appendTranActions(tran, actions)
        
        #-------------------------------------------interleaving-read-write-ack-------------------------------------------
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.em[f'udshmem-worker-interleaving-write'])
        addr_reg = 'X3'
        actions = [
            (5, wthrprint.printr(f"worker-interleaving-write: WRITE DRAM", [wthr.stackid, wthr.ldptr, wthr.diff, wthr.strptr, wthr.ld_nleft, wthr.st_nleft, ('addr_reg', addr_reg)]) ),
        ]
        if self.debug_level > 3:
            for i in range(8):
                actions +=[
                    # (4, wthrprint.printr(f"worker-write-{C}: WRITE DRAM", [wthr.stackid, wthr.ldptr, wthr.diff, wthr.strptr, wthr.ld_nleft, wthr.st_nleft, ('addr_reg', addr_reg)])),
                    (5, wthrprint.printr(f"worker-interleaving-write: WRITE DRAM", [(f'op{i}', f'X{8+i}')])),
                ]

        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ REAL WRITE~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        actions += [
            f"udshmem-write-cont: add {wthr.diff} {addr_reg} {wthr.strptr}",
            f"sendops_dmlm_wret {wthr.strptr} {self.em[f'udshmem-worker-ack-8']} X8 8 {wthr.tmp}",
            f"subi {wthr.nout} {wthr.nout} 1",
            f"bgt {wthr.maxout} {wthr.nout} udshmem-worker-resume-read",
            f"yield",
        ]
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ REAL WRITE~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        wthr.evw = 'alloc'
        actions +=[
            
            f"udshmem-worker-resume-read: blei {wthr.ld_nleft} 0 udshmem-no-more-read",
            f"evi X2 {wthr.evw} {self.em['udshmem-worker-interleaving-read-write']} {0b0001}", 
            f"sendr_wcont {wthr.evw} X1 {wthr.ldptr} {wthr.maxout}",
            f"udshmem-no-more-read: yield",
        ]
        wthr.free(wthr.evw)
        self.appendTranActions(tran, actions)
        #-------------------------------------------interleaving-read-write-ack-ends------------------------------------------

            
    
        # endregion interleaving-read-write
        #-----------------------------------------------------INTERLEAVING-READ-WRITE-ENDS-------------------------------------------------------
        
        
        
        #-----------------------------------------------------EV-READ-LOOP-----------------------------------------------------
        # region ev-read-loop
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.em['udshmem-worker-ev-read-loop'])
        wthr.inc = 'alloc'
        
        actions = []
        actions += [   
            # split this into two event
            (3, wthrprint.printr("WORKER-EV-READ-LOOP:", [wthr.stackid, wthr.ldptr, wthr.diff, wthr.strptr, wthr.ld_nleft, wthr.st_nleft, wthr.nout, ('maxout', wthr.maxout)])),
            f"read-loop: blei {wthr.ld_nleft} 0 udshmem-read-done",
            f"ble {wthr.maxout} {wthr.nout} udshmem-read-wait",
            f"send_dmlm_ld_wret {wthr.ldptr} {self.em['udshmem-worker-write-8']} 8 {wthr.tmp}", # not throttling write but ack will know
            f"addi {wthr.ldptr} {wthr.ldptr} 64",
            
            # inc = 0; if ldptr & segmask: inc=1 ; if inc==1 meaning their is remainder, inc-1 as mask would mask out all the stripes; 
            # if inc==0 meaning no remainder, inc-1 as mask would mask out nothing.
            f"and {wthr.ldptr} {wthr.segmask} {wthr.tmp}",
            # f"movir {wthr.inc} 0",
            f"cgti {wthr.tmp} {wthr.inc} 0", # if tmp > 0, inc would be 1. has tmp meaning it has remainder, meaning we still has reach the turning point
            f"subi {wthr.inc} {wthr.inc} 1",
            f"and {wthr.dstripe} {wthr.inc} {wthr.inc}",
            f"add {wthr.ldptr} {wthr.inc} {wthr.ldptr}",
            f"subi {wthr.ld_nleft} {wthr.ld_nleft} 8", # one chunk gone!, each chunk is 8*8B
            (5, wthrprint.printr("WORKER-EV-READ:", [wthr.stackid, wthr.ld_nleft, wthr.st_nleft, wthr.pnelems, wthr.nout, ('maxout', wthr.maxout)])),
            f"addi {wthr.nout} {wthr.nout} 1",
            f"jmp read-loop",
           
        ]

        actions += [
            f"udshmem-read-done: yield",
        ]
        actions +=[
            f"udshmem-read-wait: movir {wthr.nout} 0", 
            f"sendr_wcont X2 X1 {wthr.ldptr} {wthr.maxout}", # just sendmyself
            f"yield",
        ]
        wthr.free(wthr.inc)
        self.appendTranActions(tran, actions)
        
        # endregion ev-read-loop
        #-----------------------------------------------------EV-READ-LOOP-END-----------------------------------------------------
    
    
        #-----------------------------------------------------udshmem-handle-head-tail-----------------------------------------------------
        # region handle-head-tail
        # this should have the same thread context as above
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.em[f'udshmem-handle-head-tail'])
        # obs: obsrc, obnelems, obdiff and this thread is executed only once
        obsrc = "X8"
        obnelems = "X9"
        obdiff = "X10"
        actions = [
            f"addi {obsrc} {wthr.ldptr} 0",
            f"addi {obnelems} {wthr.ld_nleft} 0",
            f"addi {obnelems} {wthr.st_nleft} 0",
            f"addi {obdiff} {wthr.diff} 0", 
            f"movir {wthr.maxout} 64",
            (4, wthrprint.printr("handle-head-tail", [('obsrc', obsrc), wthr.ldptr, wthr.ld_nleft, wthr.st_nleft, wthr.diff]))           
        ]
        
        chunks = [1,2,3,4,5,6,7]
        for c in chunks:
            actions +=[
                f"beqi {obnelems} {c} udshmem-head-tail-load-{c}",
            ]
        actions += [
            (5,wthrprint.printr("handle-head-tail: FATAL invalid chunk size!", [])),
            f"yield",
        ]
        for c in chunks:
            actions +=[
                f"udshmem-head-tail-load-{c}: send_dmlm_ld_wret {wthr.ldptr} {self.em[f'udshmem-worker-write-{c}']} {c} {wthr.tmp}",
                f"yield",
            ]
        self.appendTranActions(tran, actions)  
        # endregion handle-head-tail
        #-----------------------------------------------------udshmem-handle-head-tail-----------------------------------------------------
        
        for c in self.chunks:
            _ev_write(c)
            _ev_ack(c)

        if self.impl == 'loc-aware-throttled-old':
            _ev_write_throttled_old(8)
        
        #==================================================udshmem-worker================================================
        #endregion

    
    
    
    def udshmem_naive_shmem(self):
        self.em.add_event('udshmem-naive-shmem-put')
        self.em.add_event('udshmem-done')
        self.em.add_event('udshmem-naive-shmem-get')
        self.em.add_event('udshmem-node-root')
        self.em.add_event('udshmem-node-root-done')
        self.em.add_event('udshmem-stack-root')
        self.em.add_event('udshmem-ud-root')
        self.em.add_event('udshmem-worker')
        self.em.add_event('udshmem-stack-root-done')
        self.em.add_event('udshmem-ud-root-done')
        self.em.add_event('udshmem-init-remote-lm')
        for c in self.allowed_chunks:
            self.em.add_event(f'udshmem-worker-read-{c}')
            self.em.add_event(f'udshmem-worker-write-{c}')
            self.em.add_event(f'udshmem-worker-ack-{c}')
            
        NUMUDS = 1
        NUMSTACKS = 1
        NUMLANES = 1
        # work distributor
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.em['udshmem-naive-shmem-put'])
        # startudid = local
        # obs = dst, src, nelems, nodeid
        # start udshmem-node-root
        obdst = "X8"
        obsrc = "X9"
        obnelems = "X10"
        obnodeid = "X11"
        
        evw = self.reg.alloc('evw')
        temp0 = self.reg.alloc('temp0')
        temp1 = self.reg.alloc('temp1')
        actions = [
            (0, f"print '[nwid=%lu] Calling udshmem_put...' NWID"),
            (0, f"print '[nwid=%lu] Push shmem_put event, cevw=%lu, ccont=%lu, evw=%lu, label=%lu' NWID X2 X1 {evw} {self.em['udshmem-done']}"),
            (0, f"print '=================================UDSHMEM-START=================================='"),
            f"evii {evw} {self.em['udshmem-node-root']} 255 {0b0101}",
            f"sendops_wcont {evw} X1 X8 4 {temp0} {temp1}",
            f"yieldt",
        ]
        self.appendTranActions(tran, actions)
        self.reg.freeall()
        
        # send to udshmem-node-root
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.em['udshmem-done'])
        temp0 = self.reg.alloc('temp0')
        actions = [
            (0, f"print '[nwid=%lu]udshmem-done udshmem_put done. cevw=%lu, ccont=%lu' NWID X2 X1"),
            f"sendr_reply X31 X30 {temp0}",
            f"yieldt"
        ]
        self.appendTranActions(tran, actions)
        self.reg.freeall()
   
        # for i in range(numstacks):
        # rudid = i
        # send to stack-root with stack-root event
        #======================================================NODE-ROOT===================================================
        #------------------------------------------------udshmem-node-root------------------------------------------------  
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.em['udshmem-node-root']) # node->stack
        obdst = "X8"
        obsrc = "X9"
        obnelems = "X10"
        obnodeid = "X11"
        dst = self.reg.alloc('dst')
        src = self.reg.alloc('src')
        nelems = self.reg.alloc('nelems')
        nodeid = self.reg.alloc('nodeid')
        rsid = self.reg.alloc('rsid') # relative stack id
        maxstacks = self.reg.alloc('maxstacks')
        evw = self.reg.alloc('evw')
        tnwid = self.reg.alloc('tnwid')
        nodenwid0 = self.reg.alloc('nodenwid0')
        
        lmbase = self.reg.alloc('lmbase')
        lmoffset = self.reg.alloc('lmoffset')
        # not free
        expect_replys = self.reg.alloc('expect_replys')
        nreplys = self.reg.alloc('nreplys')
        temp0 = self.reg.alloc('temp0')
        # save data to local lm
        actions = [
            (0, f"print 'node-root[nwid=%lu]: node-root start. src=%lu, dst=%lu, nelems=%lu, nodeid=%lu' NWID {obsrc} {obdst} {obnelems} {obnodeid}"),
            f"addi X7 {lmbase} {self.lane_send_buffer_offset}",
            f"movir {lmoffset} 0",
            
            f"movwrl {obdst} {lmbase}({lmoffset},1,0)",
            f"movwrl {obsrc} {lmbase}({lmoffset},1,0)",
            f"movwrl {obnelems} {lmbase}({lmoffset},1,0)",
            f"movwrl {obnodeid} {lmbase}({lmoffset},1,0)",
            
            f"mov_reg2reg NWID {tnwid}",
            f"sri {tnwid} {nodenwid0} 11",
            f"sli {nodenwid0} {nodenwid0} 11",
            f"movir {rsid} 0",
            f"movir {maxstacks} {NUMSTACKS}",
            f"udshmem-send-node-root-loop: ble {maxstacks} {rsid} udshmem-send-node-root-done",
            f"sli {rsid} {tnwid} 8",
            f"add {tnwid} {nodenwid0} {tnwid}",
            f"evii {evw} {self.em['udshmem-stack-root']} 255 {0b0101}",
            f"ev {evw} {evw} {tnwid} {tnwid} {0b1000}",
            f"movwrl {rsid} {lmbase}({lmoffset},0,0)",
            # send dst, src, nelems, rstackid to tnwid
            f"send_wret {evw} {self.em['udshmem-node-root-done']} {lmbase} 5 {temp0}",
            f"addi {rsid} {rsid} 1",
            f"jmp udshmem-send-node-root-loop",
            f"udshmem-send-node-root-done: movir {expect_replys} {NUMSTACKS}",
            f"movir {nreplys} 0",
            f"yield",
        ]
        self.appendTranActions(tran, actions)
        tofree = ['rsid', 'maxstacks', 'evw', 'tnwid', 'nodenwid0', 'lmbase', 'lmoffset', 'temp0'] # 'expect_replys', 'nreplys' will still be used
        self.reg.freemany(tofree)

        #------------------------------------------------udshmem-node-root-done------------------------------------------------
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.em['udshmem-node-root-done']) # stack->ud
        temp = self.reg.alloc('temp')
        lmbase = self.reg.alloc('lmbase')
        lmoffset = self.reg.alloc('lmoffset')
        actions = [
            f"addi {nreplys} {nreplys} 1",
            f"ble {expect_replys} {nreplys} udshmem-node-root-done",
            f"yield",
            f"udshmem-node-root-done: movir {temp} 1",
            (3, f"print 'node-root-done[%lu]: sendreply, expect=%lu, nreplys=%lu, cevw=%lu, ccont=%lu' NWID {expect_replys} {nreplys} X2 X1"),
            f"movir {lmoffset} 0",
            f"addi X7 {lmbase} {self.term_flag_offset}",
            f"movwrl {temp} {lmbase}({lmoffset},1,0)",
            f"sendr_reply X31 X30 {temp}",
            (0, f"print '=================================UDSHMEM-END=================================='"),
            f"yieldt",
        ]
        self.appendTranActions(tran, actions)
        self.reg.freeall()
        #=================================================NODE-ROOT-END================================================
    
        #------------------------------------------------udshmem-stack-root------------------------------------------------
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.em['udshmem-stack-root']) # stack->ud
        obdst = "X8"
        obsrc = "X9"
        obnelems = "X10"
        obnodeid = "X11"
        obrsid = "X12"
        
        
        lmbase = self.reg.alloc('lmbase')
        lmoffset = self.reg.alloc('lmoffset')
        tnwid = self.reg.alloc('tnwid')
        rudid = self.reg.alloc('rudid')
        maxuds = self.reg.alloc('maxuds')
        evw = self.reg.alloc('evw')
        tnwid = self.reg.alloc('tnwid')
        stacknwid0 = self.reg.alloc('stacknwid0')
        
        lmbase = self.reg.alloc('lmbase')
        lmoffset = self.reg.alloc('lmoffset')
        # not free
        expect_replys = self.reg.alloc('expect_replys')
        nreplys = self.reg.alloc('nreplys')
        temp0 = self.reg.alloc('temp0')
        actions = [
            (0, f"print 'stack-root[rsid=%lu]: stack-root start at nwid=%lu.' {obrsid} NWID "),
            f"addi X7 {lmbase} {self.lane_send_buffer_offset}",
            f"movir {lmoffset} 0",
            
            f"movwrl {obdst} {lmbase}({lmoffset},1,0)",
            f"movwrl {obsrc} {lmbase}({lmoffset},1,0)",
            f"movwrl {obnelems} {lmbase}({lmoffset},1,0)",
            f"movwrl {obnodeid} {lmbase}({lmoffset},1,0)",
            f"movwrl {obrsid} {lmbase}({lmoffset},1,0)",
            
            f"mov_reg2reg NWID {stacknwid0}", # this nwid should be stacknwid0
            f"movir {rudid} 0",
            f"movir {maxuds} {NUMUDS}",
            f"udshmem-send-stack-root-loop: ble {maxuds} {rudid} udshmem-send-stack-root-done",
            f"sli {rudid} {tnwid} 6",
            f"add {tnwid} {stacknwid0} {tnwid}",
            f"evii {evw} {self.em['udshmem-ud-root']} 255 {0b0101}",
            f"ev {evw} {evw} {tnwid} {tnwid} {0b1000}",
            f"movwrl {rudid} {lmbase}({lmoffset},0,0)",
            # send dst, src, nelems, rstackid to tnwid
            f"send_wret {evw} {self.em['udshmem-stack-root-done']} {lmbase} 6 {temp0}",
            f"addi {rudid} {rudid} 1",
            f"jmp udshmem-send-stack-root-loop",
            f"udshmem-send-stack-root-done: movir {expect_replys} {NUMUDS}",
            f"movir {nreplys} 0",
            f"yield",
        ]
        self.appendTranActions(tran, actions)
        tofree = ['rudid', 'maxuds', 'evw', 'tnwid', 'stacknwid0', 'lmbase', 'lmoffset', 'temp0']
        self.reg.freemany(tofree)
        #------------------------------------------------udshmem-stack-root-done------------------------------------------------
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.em['udshmem-stack-root-done'])
        temp = self.reg.alloc('temp')
        actions = [
            f"addi {nreplys} {nreplys} 1",
            (3, f"print 'stack-root-done[nwid=%lu]: nreplys=%lu, expect=%lu' NWID {nreplys} {expect_replys}"),
            f"ble {expect_replys} {nreplys} udshmem-stack-root-done",
            f"yield",
            f"udshmem-stack-root-done: sendr_reply X31 X30 {temp}",
            (3, f"print 'stack-root-done[nwid=%lu]: Finishes, sendrepy' NWID"),
            f"yieldt"
        ]
        
        self.appendTranActions(tran, actions)
        self.reg.freeall()
        #=================================================STACK-ROOT-END================================================
        
        #------------------------------------------------udshmem-ud-root------------------------------------------------
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.em['udshmem-ud-root']) # ud->lanes->workers
        # obdst, obsrc, obnelems, obnodeid, obrsid, obrudid, 
        # MAXLANES, MAXUDS, MAXSTACKS
        obdst = "X8"
        obsrc = "X9"
        obnelems = "X10"
        obnodeid = "X11"
        obrsid = "X12"
        obrudid = "X13"

        lmbase = self.reg.alloc('lmbase')
        lmoffset = self.reg.alloc('lmoffset')
        tnwid = self.reg.alloc('tnwid')
        rlaneid = self.reg.alloc('rlaneid')
        udnwid0 = self.reg.alloc('udnwid0')
        maxlanes = self.reg.alloc('maxlanes')
        expect_replys = self.reg.alloc('expect_replys')
        nreplys = self.reg.alloc('nreplys')
        temp0 = self.reg.alloc('temp0')
        evw = self.reg.alloc('evw')
        
        actions = [
            (0, f"print 'ud-root[rsid=%lu][rudid=%lu]: ud-root start, at nwid=%lu.'{obrsid} {obrudid} NWID"),
            f"addi X7 {lmbase} {self.lane_send_buffer_offset}",
            f"movir {lmoffset} 0",
            f"movwrl {obdst} {lmbase}({lmoffset},1,0)",
            f"movwrl {obsrc} {lmbase}({lmoffset},1,0)",
            f"movwrl {obnelems} {lmbase}({lmoffset},1,0)",
            f"movwrl {obnodeid} {lmbase}({lmoffset},1,0)",
            f"movwrl {obrsid} {lmbase}({lmoffset},1,0)",
            f"movwrl {obrudid} {lmbase}({lmoffset},1,0)",
            f"mov_reg2reg NWID {udnwid0}",
            f"movir {rlaneid} 0",
            f"movir {maxlanes} {NUMLANES}",

            (4, f"print 'ud-root[rsid=%lu][rudid=%lu][rlaneid=%lu]: maxlanes=%lu' {obrsid} {obrudid} {rlaneid} {maxlanes}"),
            
        
            f"udshmem-send-ud-root-loop: ble {maxlanes} {rlaneid} udshmem-send-ud-root-done",
            f"add {udnwid0} {rlaneid} {tnwid}",
            f"movwrl {rlaneid} {lmbase}({lmoffset},0,0)",
            f"evii {evw} {self.em['udshmem-worker']} 255 {0b0101}",
            f"ev {evw} {evw} {tnwid} {tnwid} {0b1000}",
            f"send_wret {evw} {self.em['udshmem-ud-root-done']} {lmbase} 7 {temp0}",
            f"addi {rlaneid} {rlaneid} 1",
            (4, f"print 'ud-root[srid=%lu][rudid=%lu][rlaneid=%lu]: Sending... maxlanes=%lu send to worker at nwid=%lu, tnwid=%lu.' {obrsid} {obrudid} {rlaneid} {maxlanes} NWID {tnwid}"),
            f"jmp udshmem-send-ud-root-loop",
            f"udshmem-send-ud-root-done: movir {expect_replys} {NUMLANES}",
            f"movir {nreplys} 0",
            (3, f"print 'ud-root[srid=%lu][rudid=%lu]: nreplys=%lu, expect=%lu, nwid=%lu, cevw=%lu, ccont=%lu' {obrsid} {obrudid} {nreplys} {expect_replys} NWID X2 X1"),
            f"yield",
        ]
        self.appendTranActions(tran, actions)
        tofree = ['lmbase', 'lmoffset', 'tnwid', 'rlaneid', 'udnwid0', 'temp0', 'maxlanes', 'evw']
        self.reg.freemany(tofree)
        #------------------------------------------------udshmem-ud-root-done------------------------------------------------
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.em['udshmem-ud-root-done'])
        temp = self.reg.alloc('temp')
        actions = [
            
            f"addi {nreplys} {nreplys} 1",
            f"ble {expect_replys} {nreplys} udshmem-ud-root-done",
            f"yield",
            f"udshmem-ud-root-done: sendr_reply X31 X30 {temp}",
            (3, f"print 'ud-root-done[nwid=%lu]: nreplys=%lu, expect=%lu, cevw=%lu, ccont=%lu' NWID {nreplys} {expect_replys} X2 X1"),
            f"yieldt",
        ]
        self.appendTranActions(tran, actions)
        self.reg.freeall()
        #=================================================UD-ROOT-END================================================
        
        #=================================================UD-WORKER================================================
        #------------------------------------------------udshmem-worker------------------------------------------------
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.em['udshmem-worker'])
        obdst = "X8"
        obsrc = "X9"
        obnelems = "X10"
        obnodeid = "X11"
        obrsid = "X12"
        obrudid = "X13"
        obrlaneid = "X14"
        
        # first calculate widx = obrlaneid + obrudid * NUMLANES + obrsid * NUMLANES * NUMUDS + obnodeid * NUMLANES * NUMUDS * NUMSTACKS
        LGNUMLANES = int(math.log2(NUMLANES))
        LGNUMUDS = int(math.log2(NUMUDS))
        LGNUMSTACKS = int(math.log2(NUMSTACKS))
        # regs
        widx = self.reg.alloc('widx') # no one free 1
        src = self.reg.alloc('src') # no one free 2
        diff = self.reg.alloc('diff') # no one free 3
        dnodeid = self.reg.alloc('dnodeid') # no one free 4
        temp1 = self.reg.alloc('temp1')
        temp2 = self.reg.alloc('temp2')
        temp3 = self.reg.alloc('temp3')
        actions = [
            f"addi {obsrc} {src} 0",
            f"sub {obdst} {obsrc} {diff}",
            f"addi {obnodeid} {dnodeid} 0",
            f"movir {widx} 0",
            f"sli {obrudid} {temp1} {LGNUMLANES}",
            f"sli {obrsid} {temp2} {LGNUMLANES + LGNUMUDS}",
            # f"sli {obn} {temp3} {LGNUMLANES + LGNUMUDS + LGNUMSTACKS}",
            
            f"add {widx} {temp1} {widx}",
            f"add {widx} {temp2} {widx}",
            f"add {widx} {obrlaneid} {widx}",
            # f"add {widx} {temp3} {widx}",
            (4, f"print 'udshmem-worker[nwid=%lu]: widx=%lu, obrlaneid=%lu, baserudid=%lu, basersid=%lu' NWID {widx} {obrsid} {obrudid} {obrlaneid}"),
        ]
        tofree = ['temp1', 'temp2', 'temp3']
        self.reg.freemany(tofree)
        NUMWORKERS = 1 << (LGNUMLANES + LGNUMUDS + LGNUMSTACKS)
        LGNWORKERS= int(math.log2(NUMWORKERS))
        initoffset = self.reg.alloc('initoffset') #5
        ldptr = self.reg.alloc('ldptr') #6 non free 5
        wnelems = self.reg.alloc('wnelems') #7 non free 6
        fd_nelems = self.reg.alloc('fd_nelems') #9, default 2048
        rm_nelems = self.reg.alloc('rm_nelems') #8, default 2048
        nworkers = self.reg.alloc('nworkers') #10
        ld_nleft = self.reg.alloc('ld_nleft') #11 non free 7
        st_nleft = self.reg.alloc('st_nleft') #12 non free 8
        mask = self.reg.alloc('mask') #13
        nelems = self.reg.alloc('nelems') #14
        
        
        actions.extend([
            (4, f"print 'worker[widx=%lu]: prepare worker at nwid=%lu.' {widx} NWID "),
            # cal wnelems
            f"addi {obnelems} {nelems} 0",
            f"sri {obnelems} {fd_nelems} {LGNWORKERS}", # wnelems = nelems >> LGNWORKERS
            f"movir {nworkers} {NUMWORKERS}",
            f"subi {nworkers} {mask} 1",
            f"and {nelems} {mask} {rm_nelems}",
            f"blt {widx} {rm_nelems} widx-lt-rm_nelems",
            f"mov_reg2reg {fd_nelems} {wnelems}", # wnelems = fd_nelems
            f"mul {fd_nelems} {widx} {initoffset}", # initoffset = widx * fd_nelems + rm_nelems
            f"add {initoffset} {rm_nelems} {initoffset}",
            f"sli {initoffset} {initoffset} 3",
            f"jmp cont",
            f"widx-lt-rm_nelems: mul {fd_nelems} {widx} {initoffset}",
            f"add {initoffset} {widx} {initoffset}",
            f"sli {initoffset} {initoffset} 3",
            f"addi {fd_nelems} {wnelems} 1",
            f"cont: add {obsrc} {initoffset} {ldptr}",
            f"mov_reg2reg {wnelems} {ld_nleft}",  
            f"mov_reg2reg {wnelems} {st_nleft}", 
            (3, f"print 'worker[widx=%lu, nwid=%lu]: wnelems=%lu, initoffset=%lu, ldptr=%lu, ld_nleft=%lu, st_nleft=%lu, fd_nelems=%d, rm_nelems=%d, LGNWORKERS={LGNWORKERS}' {widx} NWID {wnelems} {initoffset} {ldptr} {ld_nleft} {st_nleft} {fd_nelems} {rm_nelems}"),
        ])
        # occupied: wnelems, ldptr, ld_nleft, src, diff, 
        # OB: obnodeid
        # free: temp1, temp2, temp3, initoffset, mask, nworkers, rm_nelems, fd_nelems
        tofree = ['initoffset', 'mask', 'nworkers', 'rm_nelems', 'fd_nelems', 'nelems']
        self.reg.freemany(tofree)
        # sync with remote node, send diff, evw
        NODENWIDMASK = 0b11111111111
        nwid = self.reg.alloc('nwid') #8
        tnwid = self.reg.alloc('tnwid') #9
        evw = self.reg.alloc('evw') #10
        temp0 = self.reg.alloc('temp0') #11
        temp1 = self.reg.alloc('temp1') #12
        actions.extend([
            f"mov_reg2reg NWID {nwid}",
            f"andi {nwid} {tnwid} {NODENWIDMASK}",
            f"sli {dnodeid} {temp0} 11",
            f"add {temp0} {tnwid} {tnwid}",
            (3, f"print 'worker[widx=%lu, nwid=%lu]: sync with remote node at nwid=%lu, tnwid=%lu, dnodeid=%lu, cevw=%lu' {widx} NWID {nwid} {tnwid} {dnodeid} X2"),
            f"evii {evw} {self.em['udshmem-init-remote-lm']} 255 {0b0101}",
            f"ev {evw} {evw} {tnwid} {tnwid} {0b1000}",
            f"sendr3_wret {evw} {self.em[f'udshmem-worker-read-{max(self.allowed_chunks)}']} {obdst} {diff} X2 {temp0} {temp1}",
            f"yield",
        ])
        tofree = ['nwid', 'tnwid', 'evw', 'temp0', 'temp1']
        self.reg.freemany(tofree)
        self.appendTranActions(tran, actions)
        # worker thread
        #-------------------------------------------------udshmem-worker-start------------------------------------------------
        maxout = self.reg.alloc('maxout') #8
        outgoing = self.reg.alloc('outgoing') #9
        temp0 = self.reg.alloc('temp0') #9

        
        def _ev_read(mself, C=8):
            
            def _load_first(actions, label=f"udshmem-load-first", C=8):
                actions.extend([
                    f"movir {maxout} 32",
                    f"{label}: blec {ld_nleft} 0 terminate",
                ])
                _load_next(actions, C)
                return actions
                
                
            def _load_next(actions, C=8):
                evw = mself.reg.alloc('evw')
                tnwid = mself.reg.alloc('tnwid')
                nwid = mself.reg.alloc('nwid')
                contw = mself.reg.alloc('contw')
                actions.extend([
                    f"blec {ld_nleft} 0 done",
                    f"blec {ld_nleft} {C-1} next_chunk_{mself.__NEXT_CHUNK(C)}", 
                    f"mov_reg2reg NWID {nwid}",
                    f"andi {nwid} {tnwid} {NODENWIDMASK}",
                    f"sli {dnodeid} {temp0} 11",
                    f"add {temp0} {tnwid} {tnwid}",
                    f"evii {evw} {mself.em[f'udshmem-worker-write-{C}']} 255 {0b0101}",
                    (3, f"print 'worker[widx=%lu, nwid=%lu]: Readreturn will be on tnwid=%lu, dnodeid=%lu' {widx} NWID {tnwid} {dnodeid}"),
                    f"ev {evw} {evw} {tnwid} {tnwid} {0b1000}",       
                ])
                if C <= 8:
                    actions.extend([
                        (3, f"print 'worker-read[nwid=%lu, widx=%lu]loading from ldptr=%lu' NWID {widx} {ldptr} "),
                        f"send_dmlm_ld {ldptr} {evw} {C} {temp0}",
                        # f"sendm {ldptr} {evw} X7 {C} {0b00}",
                        f"addi {ldptr} {ldptr} {C * 8}",
                    ])
                else:
                    for i in range(C // 8):
                        actions.extend([
                            f"send_dmlm_ld {ldptr} {evw} 8 {temp0}",
                            f"addi {ldptr} {ldptr} 64",
                        ])
                actions.extend([
                    f"subi {ld_nleft} {ld_nleft} {C}",
                    f"addi {outgoing} {outgoing} {C//8 if C > 8 else 1}",
                    f"yield",
                ])
                if C!=1:
                    actions.extend([
                        f"next_chunk_{mself.__NEXT_CHUNK(C)}: evi X2 {evw} {mself.em[f'udshmem-worker-read-{mself.__NEXT_CHUNK(C)}']} {0b0001}",
                        f"mov_reg2reg X1 {contw}",
                        f"sendr_wcont {evw} {contw} X30 X31", # current contword
                        f"yield",
                    ])
                else:
                    actions.extend([
                        f"next_chunk_{C}: yield",
                    ])
                
                tofree = ['evw', 'tnwid', 'nwid', 'contw']
                mself.reg.freemany(tofree)
           
                actions.extend([
                    f"done: yield",
                ])
                return actions
            

            tran = mself.state.writeTransition("eventCarry", mself.state, mself.state, mself.em[f'udshmem-worker-read-{C}'])
            # thread context: widx, src, diff, dnodeid, ldptr, ld_nleft, st_nleft, wnelems, outgoing

            actions = [
                (3, f"print 'worker[widx=%lu, nwid=%lu]: Worker read({C}) start with welems=%lu, ld_nleft=%lu, st_nleft=%lu, cevw=%lu' {widx} NWID {wnelems} {ld_nleft} {st_nleft} X2"),
            ]
            actions = _load_first(actions,label=f"udshmem-load-first-{C}", C=C)
            actions.extend([
                f"terminate: sendr_reply X31 X30 {temp0}",
                (4, f"print 'worker[widx=%lu, nwid=%lu]: Worker read({C}) done with welems=%lu, ld_nleft=%lu, st_nleft=%lu' {widx} NWID {wnelems} {ld_nleft} {st_nleft}"),
                f"yieldt",
            ])
            mself.appendTranActions(tran, actions)

            

        #-------------------------------------------------udshmem-worker-write------------------------------------------------
       
        def _ev_write(mself, C=8):
            # dst = self.reg.alloc('dst')
            diff = mself.reg.alloc('addr-diff')
            lmbase = mself.reg.alloc('lmbase')
            lmoffset = mself.reg.alloc('lmoffset')
            stptr = mself.reg.alloc('stptr')
            evw = mself.reg.alloc('evw')
            
            tran = mself.state.writeTransition("eventCarry", mself.state, mself.state, mself.em[f'udshmem-worker-write-{C}'])
            actions = []
            chunk_size = C if C <= 8 else 8
            return_addr_reg = 'X' + str((chunk_size + 8) if chunk_size < 8 else 3)
            # assume we will use diff anyways
            actions.extend([
                # (3, f"print 'READ_RETURNS[nwid=%lu]: Worker read_returns. addr=%lu, val0=%lu, val1=%lu, val2=%lu' NWID X3 X8 X9 X10"),
                f"addi X7 {lmbase} {mself.lane_operands_offset}",
                f"movir {lmoffset} 1",
                f"movwlr {lmbase}({lmoffset},1,0) {diff}",
                f"movwlr {lmbase}({lmoffset},1,0) {evw}",
                f"add {return_addr_reg} {diff} {stptr}",
                (3, f"print 'WRITE[nwid=%lu]: Read from spm: evw=%lu, diff=%ld, return_addr=%lu, stptr=%lu' NWID {evw} {diff} {return_addr_reg} {stptr}"),
                f"evi {evw} {evw} {mself.em[f'udshmem-worker-ack-{C}']} {0b0001}",
                (3, f"print 'WRITE[nwid=%lu]: Worker write({C}) diff=%ld, return_addr=%lu, stptr=%lu, evw=%lu' NWID {diff} {return_addr_reg} {stptr} {evw}"),
                f"sendmops {stptr} {evw} X8 {C} {0b0}",
                f"yield"])

            tofree = ['addr-diff', 'lmbase', 'lmoffset', 'stptr', 'evw']
            mself.reg.freemany(tofree)
            mself.appendTranActions(tran, actions)
  
    
        def _ev_ack(mself, C=8):
            evw = mself.reg.alloc('evw')
            temp0 = mself.reg.alloc('temp0')
            tran = mself.state.writeTransition("eventCarry", mself.state, mself.state, mself.em[f'udshmem-worker-ack-{C}'])
            maxchunksize = C if C <= 8 else 8
            print(self.reg)
            actions = [
                (3, f"print 'ACK[nwid=%lu]: Worker ack({C}) start with st_nleft=%lu, outgoing=%lu cevw=%lu' NWID {st_nleft} {outgoing} X2"),
                f"subi {st_nleft} {st_nleft} {maxchunksize}",
                f"blec {st_nleft} 0 ack_terminate",
                f"blec {ld_nleft} 0 ack_terminate",
                f"subi {outgoing} {outgoing} {C//8 if C > 8 else 1}",
                f"ble {outgoing} {maxout} read_next",
                f"yield",
                f"read_next: evi X2 {evw} {mself.em[f'udshmem-worker-read-{C}']} {0b0001}",
                (3, f"print 'ACK[nwid=%lu]: ({C})Reading next, done with st_nleft=%lu, outgoing=%lu' NWID {st_nleft} {outgoing}"),
                f"sendr_wcont {evw} X1 X30 X31",
                f"yield",
                f"ack_terminate: sendr_reply X31 X30 {temp0}",
                (3, f"print 'ACK[nwid=%lu]: Worker ack({C}) done with st_nleft=%lu, outgoing=%lu' NWID {st_nleft} {outgoing}"),
                f"yieldt",
            ]
            tofree = ['evw', 'temp0']
            mself.reg.freemany(tofree)
            mself.appendTranActions(tran, actions)
        
          
        for c in self.allowed_chunks:
            _ev_read(self, c) 
            _ev_write(self, c)
            _ev_ack(self, c)
        #-------------------------------------------------udshmem-init-remote-lm------------------------------------------------
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.em['udshmem-init-remote-lm'])
        obdst = "X8"
        obdiff = "X9"
        obevw = "X10"
        
        lmbase = self.reg.alloc('lmbase')
        lmoffset = self.reg.alloc('lmoffset')
        temp = self.reg.alloc('temp')
        
        actions = [
           
            f"addi X7 {lmbase} {self.lane_operands_offset}",
            f"movir {lmoffset} 0",
            f"movwrl {obdst} {lmbase}({lmoffset},1,0)",
            f"movwrl {obdiff} {lmbase}({lmoffset},1,0)",
            f"movwrl {obevw} {lmbase}({lmoffset},1,0)",
            (3, f"print 'init-remote-lm[nwid=%lu]: init-remote-lm, lmbase=%lu, lmoffset=%lu, obdst=%lu, obdiff=%ld, obevw=%lu.' NWID {lmbase} {lmoffset} {obdst} {obdiff} {obevw}"),
            f"sendr_reply X31 X30 {temp}",
        ]
        tofree = ['lmbase', 'lmoffset', 'temp']
        self.reg.freemany(tofree)
        self.appendTranActions(tran, actions)


