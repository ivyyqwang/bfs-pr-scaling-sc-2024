
# Context-Aware UD SHMEM
import math
from math import log2
from Utils import EventMap, Register, AdvancedRegister, RegPrinter, pmap, appendTransActions

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
            log2nworkers = log2(nchunks/(2^b))/(2^k)
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
            (4, thrprint.printr("high32bits:", [thr.high32bits, thr.high16bits, thr.bitmask16])),
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
            (4, thrprint.printr("log2nworkers:", [thr.log2nworkers, thr.nchunks])),
            f"skip-high1bits: sri {thr.log2nworkers} {thr.log2nworkers} {self.k}",
            f"blei {thr.log2nworkers} {self.maxlog2nworkers} launch-ud",
            f"movir {thr.log2nworkers} {self.maxlog2nworkers}",
            (4, thrprint.printr("cap-log2nworkers:", [thr.log2nworkers])),
        ]
        thr.free([thr.high16bits, thr.high32bits, thr.prev, thr.t])
        return actions
        

class LocationEstimator:
    """_summary_
    Modes: 
        TIED: movers will be on the same node as the data: this is the original implementation
        AFFI_OVERRIDE: user given affinity override, movers will be sent to that node
        LOCAL_FIRST: movers will be on the same node as the caller if source or dst happen to be on the same node.
        EMPIRICAL: movers will be on the same node if most performant, otherwise other node but with mirroring mover allocation
    """
    def __init__(self, T=1) -> None:
        self.T = T
        pass
    
    def genEstimateActions(self, thr: AdvancedRegister, thrprint: RegPrinter,  obdst, obsrc, obstartnodeid='X11', impl='naive-empirical', enable3rdPartyMovers=False):
        
        return self._local_first(thr, thrprint, obdst, obsrc, obstartnodeid=obstartnodeid)
        if impl == 'naive-empirical':
            return self._naive_empirical(thr, thrprint)
        else: 
            return self._naive(thr, thrprint, obstartnodeid=obstartnodeid, obdst=obdst, obsrc=obsrc)
    
    def _naive(self, thr: AdvancedRegister, thrprint: RegPrinter, obstartnodeid, obdst, obsrc):
        """
        Use this when enable3rdPartyMovers==True
        """
        actions = [
                f"blei {thr.numops} 3 udshmem-skip-3rdparty", # if numops <= 3, skip
                f"beqi {thr.numops} 6 udshmem-skip-3rdparty", # if numops == 6, then startnodeid is not included, only when numops == 4 or 7 we have startnodeid included
                f"addi {obstartnodeid} {thr.tmp} 1",
                (2, thrprint.printr("init: given nodeid after+1", [('obstartnodeid', obstartnodeid), thr.tmp,])),
                f"beqi {thr.tmp} 0 udshmem-skip-3rdparty", # if startnodeid < -1, skip
                # f"beqi {obstartnodeid} 0 udshmem-init-caller", # if startnodeid < 0, then start from caller
                # now startnodeid > 0
                f"sli {thr.snodeid} {thr.tmp} 3", # tmp = snodeid << 3
                f"sub {thr.sstackid} {thr.tmp} {thr.tmp}", # tmp = sstackid - tmp
                f"sli {obstartnodeid} {thr.psstackid} 3", # psstackid = startnodeid << 3 = startnodeid * 8
                f"add {thr.tmp} {thr.psstackid} {thr.psstackid}", # psstackid = tmp + psstackid
                (2, thrprint.printr("init: start from given nodeid", [('obstartnodeid', obstartnodeid), thr.psstackid, thr.snodeid, thr.sstackid, thr.tmp,])),
            ]

        return actions
    
    
    def _local_first(self, thr: AdvancedRegister, thrprint: RegPrinter, obdst, obsrc, obstartnodeid='X11'):
        """
        obdst = 'X8'
        obsrc = 'X9'
        obstartnodeid = 'X11'
        oblog2numnodes = "X12"
        Else 3rdPartyMover is False
        Now according to new experiments, it seems that if src or dst is local, we should simply put them there
        init's nodeid = inodeid
        ssnodeid = source_start_nodeid 
        dsnodeid = dst_start_nodeid
        """
        
        actions = [
                # check if override obstartnodeid
                f"beqi {thr.numops} 3 udshmem-skip-override", # if numops == 3, startnodeid is not included skip
                f"beqi {thr.numops} 6 udshmem-skip-override", # if numops == 6, then startnodeid is not included, only when numops == 4 or 7 we have startnodeid included
                f"addi {obstartnodeid} {thr.tmp} 1",
                (2, thrprint.printr("[LocAware]init: Detects starnodeid override!", [('obstartnodeid', obstartnodeid), thr.tmp, thr.numops])),
                f"beqi {thr.tmp} 0 udshmem-skip-override", # if startnodeid + 1 == 0, skip, since we use default psstackid = sstackid/dstackid
                # now startnodeid > 0
                f"sli {thr.snodeid} {thr.tmp} 3", # tmp = snodeid << 3
                f"sub {thr.sstackid} {thr.tmp} {thr.tmp}", # tmp = sstackid - tmp
                f"sli {obstartnodeid} {thr.psstackid} 3", # psstackid = startnodeid << 3 = startnodeid * 8
                f"add {thr.tmp} {thr.psstackid} {thr.psstackid}", # psstackid = tmp + psstackid

                # TODO: Need Finner grained locality awareness, current granularity is node-level. can be stack-level
                # The issue of node-level granularity is if src is local node but start at later stack, it might not be optimal to put the mover on the same node
                # Then more information needed: location = f(blocksize, size, src, dst, mapbase)
                # this has good performance if large amount of src is local, in the senario where src starts at the last few stacks, this needs optimization
                f"udshmem-skip-override: beq {thr.current_nodeid} {thr.snodeid} udshmem-skip-3rdparty", # if src is local, skip since by default psstackid = sstackid
                # then src is not local, checking if dst is local
                # dnodeid = ((dst - mapbase)>>log2blocksize)& mask
                f"sri {thr.dstackid} {thr.dnodeid} 3", # dnodeid = dstackid >> 3
                f"bne {thr.current_nodeid} {thr.dnodeid} udshmem-skip-3rdparty", # if src, dst are not local, skip following src-first
                # else dest is local, src is not local, psstackid = dstackid
                f"mov_reg2reg {thr.dstackid} {thr.psstackid}",
                (2, thrprint.printr("[LocAware]init: src=REMOTE, dst=LOCAL, making it local, override with dstackid:", [thr.psstackid, thr.dstackid])),
        ]
        return actions

    def _naive_empirical(self, thr: AdvancedRegister, thrprint: RegPrinter):
        """
        Decide whether to put the workers close to the read data or not by only examinng nelems/nstacks
        given a threshold T, if nelems/nstacks < T, put the workers on the same node as the data
        Check src and dst's locality:
        src is local, dst is local: default loc-aware
        src is local, dst is remote: default loc-aware
        src is remote, dst is remote: default loc-aware
        src is remote, dst is local: our naive implementation
        
        checking dst, if remote, skip
        if src is local, skip
        if src is remote, naive implementation
        

        Args:
            thr (AdvancedRegister): thread register context object
            thrprint (RegPrinter): thread register printer object
            
            thr has regs:
            remaining regs (n=11): log2numuds, log2numlanes, gmapbase, mapbase, log2blocksize, tmp, sstackid, nstacks, snodeid, numops, psstackid

        Returns:
            list: list of actions in ordrer
            needs to calculate: psstackid
        """
        
        """Implemenmtation
        check numops:
        if numops <=3, flex -> we decide whether it is in a 3rd party mover mode
        if numops == 4, force 3rd party mover with startnodeid
        if numops == 6, flex -> we decide whether it is in a 3rd party mover mode
        if numops == 7, force 3rd party mover with startnodeid
        
        if obstartnodeid + 1 ==0, flex -> we decide whether it is in a 3rd party mover mode
        
        force-3rdparty:
        psstackid = startnodeid << 3
        
        flex:
        if dst is local, skip
        if src is local, skip
        if src is remote, naive implementation
        given nelems, nstacks, 
        t = nelems/nstacks
        if t < T, put the workers on the same node as the data
        else, skip
        """
        raise NotImplementedError("Not implemented yet")
        actions = [
            f"",   
        ]
        return actions
   
 

class CAUDShmem:
    implLocAwareFastSim = 'loc-aware-fast-sim'
    implLocAwareWithConfig = 'loc-aware-wconfig'
    implLocAwareInterleaving = 'loc-aware-interleaving'
    implLocAwareUnrealBaseline = 'loc-aware-unreal-baseline'
    implLocAwareEvLoop = 'loc-aware-ev-read-loop'
    MAP_BASE_LSHIFT = 31
    GMAP_BASE_LSHIFT = 33
    def __init__(self, efa, state=None, event_map_start=2, debug_level=1, perflog_level=1, term_flag_offset=0,
                 linker=False, impl=implLocAwareInterleaving, throttle=128, enable3rdPartyMovers=False, includeConfigs=False, enableFastSim=False, printActions=False,
                 work_estimator_exp_scaler=1, work_estimator_scaler=1, maxlog2nworkers=6,
                 override_config=False,
                 numnodes=2, blocksize=65536, privblocksize=65536, log2gmapbase=GMAP_BASE_LSHIFT, log2mapbase=MAP_BASE_LSHIFT) -> None:
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
        self.enable3rdPartyMovers = enable3rdPartyMovers
        self.includeConfigs = includeConfigs
        self.printActions = printActions
        self.enableFastSim = enableFastSim
        self.work_estimator_exp_scaler = work_estimator_exp_scaler
        self.work_estimator_scaler = work_estimator_scaler
        self.maxlog2nworkers = maxlog2nworkers
        # config if passed in
        self.override_config = override_config
        self.numnodes = numnodes
        self.blocksize = blocksize
        self.privblocksize = privblocksize
        self.log2gmapbase = log2gmapbase
        self.log2mapbase = log2mapbase
        
        self.linker = linker
        self.em = EventMap(event_map_start, linker=linker)
        
        self.term_flag_offset = term_flag_offset
        self.config_offset = self.term_flag_offset + (1 << 3) # bytes [0,7] = flag, word [1, 16] = config
        self.lane_send_buffer_offset = self.config_offset + (1 << 7) # word [1, 16] = config, word [17, 24] = send buffer
        self.lane_operands_offset = self.lane_send_buffer_offset + (1 << 6) # word 1-8 = lane buffer, word 9-inf = operands
        self.numops = 3
        if self.enable3rdPartyMovers:
            self.numops += 1
        if self.includeConfigs:
            self.numops += 3        
    
        self.printinfo()    
        self.default_chunks = [1,2,4,8]
        self.allowed_chunks = [1,2,4,8]
        self.chunks = [1,2,3,4,5,6,7,8]
        self.elem_size = 8
        self.word_size = 8

        
        self.em.add_event('udshmem_put')
        self.em.add_event('udshmem_get') # TODO: not implemented, basically the same as put

        if impl.startswith('loc-aware'):
            self.udshmem()
        else:
            raise NotImplementedError(f"{impl} not implemented!")
        
        if self.printActions:
            print(self.em)
       
       
    def printinfo(self):
        info = f"\nUDSHMEM-ASSEM-INFO[{self.impl}]: NumOps={self.numops}, IncludeConfigs={self.includeConfigs}, EnableFastSim={self.enableFastSim}, Throttle={self.throttle}, enable3rdPartyMovers={self.enable3rdPartyMovers}, override_config={self.override_config} \n"
        info += f"UDSHMEM-ASSEM-INFO[{self.impl}]: TERM_FLAG_OFFSET={self.term_flag_offset}, CONFIG_OFFSET={self.config_offset}, LANE_SENDBUFF_OFFSET={self.lane_send_buffer_offset}, LANE_OPRANDS_OFFSET={self.lane_operands_offset}\n"
        info += f"UDSHMEM-ASSEM-INFO[{self.impl}]: total_bytes_reserved={self.lane_operands_offset - self.term_flag_offset}, debug_level={self.debug_level}, perflog_level={self.perflog_level},\n"
        info += f"UDSHMEM-ASSEM-INFO[{self.impl}]: work_estimator_exp_scaler={self.work_estimator_exp_scaler}, work_estimator_scaler={self.work_estimator_scaler}, maxlog2nworkers={self.maxlog2nworkers}\n"
        if self.override_config:
            info += f"UDSHMEM-ASSEM-INFO[{self.impl}]: numnodes={self.numnodes}, blocksize={self.blocksize}, privblocksize={self.privblocksize}, log2gmapbase={self.log2gmapbase}, log2mapbase={self.log2mapbase}\n"
        print(info)
         

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
                print("User-defined perflog or print action not allowed, please use tuple (level, msg) instead of string")
                pass
            else:
                tran.writeAction(action)
        if self.printActions:
            print("-----------------------------------------------------------")

    
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
            # (0, f"print 'BEFORE'"),
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
        self.em.add_event('udshmem-handle-head-tail')
        for c in self.chunks:
            self.em.add_event(f'udshmem-worker-write-{c}')
        for c in self.chunks:   
            self.em.add_event(f'udshmem-worker-ack-{c}')
        
        # general-worker-read: stride
        self.em.add_event('udshmem-general-worker-read')
        self.em.add_event('udshmem-worker-read')
        
        # stride read/write
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
            (1, f"print 'Implementation version = {self.impl}, debug_level = {self.debug_level}, perflog_level = {self.perflog_level}, throttle = {self.throttle}, enable3rdPartyMovers = {self.enable3rdPartyMovers}, numops={self.numops}, override_config={self.override_config}'"),
            (1, f"print '[UDSHMEM][NWID=%ld]============================================CONTEXT-AWARE-UDSHMEM=========================================================' NWID"),
            (1, f"print '[UDSHMEM][NWID=%ld]CONTEXT-AWARE SHMEM STARTS! evw=%lu, contw=%lu' NWID X2 X1"),
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
        
        self.appendTranActions(tran, actions)
        #------------------------------------------------udshmem-put-end------------------------------------------------
        #------------------------------------------------udshmem-get------------------------------------------------
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.em['udshmem_get'])
        self.appendTranActions(tran, actions)
        ethr.freeall()
        #------------------------------------------------udshmem-get-end------------------------------------------------

        # endregion entry-events
        #=================================================ENTRY-EVENTS-END================================================
        
        #============================================UDSHMEM-WORK-DISTRIBUTOR==============================================
        #region udshmem-work-distributor
        #------------------------------------------------udshmem-init------------------------------------------------
        #region init
        # make sure config is ready in spm; otherwise there needs to be a process asking for config information
        
        
        ithr = AdvancedRegister()
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.em['udshmem-init'])
        # obs: obdst, obsrc, obnelems
        # given configs: 1-log2numnodes, 2-log2numstacks, 3-log2numuds, 4-log2numlanes, 5-gmapbase, 6-mapbase, 7-log2blocksize
        # config should be ready in the local memory
        # remember to use LocalMemAddrMode
        # read the configs
        
        #--------------------
        # implLocAwareFastSim:
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
        if self.enable3rdPartyMovers and (not self.includeConfigs):
            obstartnodeid = "X11"
        elif (not self.enable3rdPartyMovers) and self.includeConfigs:
            # if impl== loc-aware-wconfig
            oblog2numnodes = "X11"
            oblog2blocksize = "X12"
            oblog2privblocksize = "X13"
        elif self.enable3rdPartyMovers and self.includeConfigs:
            # include configs and enable3rdPartyMoverss
            obstartnodeid = "X11"
            oblog2numnodes = "X12"
            oblog2blocksize = "X13"
            oblog2privblocksize = "X14"
        elif (not self.enable3rdPartyMovers) and (not self.includeConfigs):
            #default udshmem does have other operands
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
        
        
        if self.enableFastSim:
            # fast sim mode
            if not self.override_config:
                actions = [
                    f"movir {ithr.log2numnodes} 1",
                    f"movir {ithr.log2numstacks} 3",
                    f"movir {ithr.log2numuds} 2",
                    f"movir {ithr.log2numlanes} 6",
                    f"movir {ithr.gmapbase} 1",
                    f"sli {ithr.gmapbase} {ithr.gmapbase} {self.GMAP_BASE_LSHIFT}",
                    f"movir {ithr.mapbase} 1",
                    f"sli {ithr.mapbase} {ithr.mapbase} {self.MAP_BASE_LSHIFT}",
                    f"movir {ithr.log2blocksize} 10",
                    f"movir {ithr.log2privblocksize} 10",
                ]
            else:
                actions = [
                    f"movir {ithr.log2numnodes} {int(log2(self.numnodes))}",
                    f"movir {ithr.log2numstacks} 3",
                    f"movir {ithr.log2numuds} 2",
                    f"movir {ithr.log2numlanes} 6",
                    f"movir {ithr.log2blocksize} {int(log2(self.blocksize))}",
                    f"movir {ithr.log2privblocksize} {int(log2(self.privblocksize))}",
                    f"movir {ithr.gmapbase} 1",
                    f"sli {ithr.gmapbase} {ithr.gmapbase} {self.log2gmapbase}",
                    f"movir {ithr.mapbase} 1",
                    f"sli {ithr.mapbase} {ithr.mapbase} {self.log2mapbase}",
                ]
        elif self.includeConfigs and (not self.override_config):
            # config is included in the passed-in operands
            # obdst, obsrc, obnelems, oblog2numnodes, oblog2blocksize, oblog2privblocksize
            actions = [
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
            
        elif self.override_config:
            # use the library's config
            actions = [
                f"movir {ithr.log2numnodes} {int(log2(self.numnodes))}",
                f"movir {ithr.log2numstacks} 3",
                f"movir {ithr.log2numuds} 2",
                f"movir {ithr.log2numlanes} 6",
                f"movir {ithr.log2blocksize} {int(log2(self.blocksize))}",
                f"movir {ithr.log2privblocksize} {int(log2(self.privblocksize))}",
                
                f"movir {ithr.gmapbase} 1",
                f"sli {ithr.gmapbase} {ithr.gmapbase} {self.log2gmapbase}",
                f"movir {ithr.mapbase} 1",
                f"sli {ithr.mapbase} {ithr.mapbase} {self.log2mapbase}",
            ]
        else:
            # reading from scratchpad
            actions = [
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
        ithr.free([ithr.lmptr, ithr.lmbase])
        # assume we have config
        actions += [
            (1, ithrprint.printr("Initial Args(0):", [('obdst', obdst),('obsrc', obsrc), ('nelems', obnelems), ithr.log2blocksize, ithr.log2privblocksize])),
            (1, ithrprint.printr("Initial Args(1):", [ithr.log2numnodes, ithr.log2numstacks, ithr.log2numuds, ithr.log2numlanes, ithr.mapbase, ithr.gmapbase])),
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
        ithr.dstackid = 'alloc'
        ithr.tmp2 = 'alloc'
        ithr.log2segsize = 'alloc'
        actions += [
            # sstackid = [(src - gmapbase) >> (log2nsegs)] & mask(maxnstacks)
            f"subi {ithr.log2blocksize} {ithr.log2segsize} 3",
            f"sub {obsrc} {ithr.gmapbase} {ithr.tmp}",
            f"sr {ithr.tmp} {ithr.log2segsize} {ithr.tmp}",
            f"and {ithr.tmp} {ithr.mask} {ithr.sstackid}",
            f"sub {obdst} {ithr.gmapbase} {ithr.tmp}",
            f"sr {ithr.tmp} {ithr.log2segsize} {ithr.tmp}",
            f"and {ithr.tmp} {ithr.mask} {ithr.dstackid}",
            (3, ithrprint.printr("starting-stackids:", [ithr.sstackid, ithr.dstackid, ithr.tmp]))
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
        # ithr.tmp1 = 'alloc'
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
            # f"movir {ithr.tmp1} 1",
            # f"sl {ithr.tmp1} {ithr.log2segsize} {ithr.tmp1}", # tmp1 = 1 << log2segsize
            # f"add {ithr.src_stack_end} {ithr.tmp1} {ithr.src_stack_end}", # src_stack_end = src_stack_end + (1<<log2segsize)
            f"movir {ithr.tmp} 1",
            f"sl {ithr.tmp} {ithr.log2segsize} {ithr.tmp}", # tmp1 = 1 << log2segsize
            f"add {ithr.src_stack_end} {ithr.tmp} {ithr.src_stack_end}", # src_stack_end = src_stack_end + (1<<log2segsize)
            (5, ithrprint.printr("init: src_stack_end", [ithr.src_stack_end, ithr.src_end, ithr.log2segsize, ithr.tmp])),
            f"sub {ithr.src_stack_end} {ithr.src_stack_start} {ithr.nstacks}", # tmp2 = src_stack_end - src_stack_start
            f"sr {ithr.nstacks} {ithr.log2segsize} {ithr.nstacks}",
            # make sure it has remainder or not     
            (5, ithrprint.printr("init: nblocks <= 1<<log2numnodes, nstacks", [ithr.nstacks, ithr.log2numnodes, ithr.src_stack_start, ithr.src_stack_end]))
            # >>> free maxnnodes
        ]
        # ithr.free([ithr.src_end, ithr.log2segsize, ithr.src_stack_start, ithr.src_stack_end, ithr.tmp1])
        ithr.free([ithr.src_end, ithr.log2segsize, ithr.src_stack_start, ithr.src_stack_end])
        
        actions += [
            f"jmp cont",
            f"maxnodes-lt-nblocks: movir {ithr.nblocks} 1", # nstacks = nblocks << log2numstacks
            f"add {ithr.log2numnodes} {ithr.log2numstacks} {ithr.tmp}",
            f"sl {ithr.nblocks} {ithr.tmp} {ithr.nstacks}",
            (2, ithrprint.printr("init: nstacks", [ithr.nstacks])),
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
        ithr.dnodeid = 'alloc'
        ithr.numops = 'alloc'
        ithr.psstackid = 'alloc' # physical start stack id, psstackid = (sstackid - snodeid*8) + startnodeid*8
        ithr.current_nodeid = 'alloc'
        actions +=[
            f"cont: mov_reg2reg {ithr.sstackid} {ithr.psstackid}",
            f"mov_reg2reg NWID {ithr.current_nodeid}",
            (3, ithrprint.printr("init: psstackid", [ithr.psstackid, ithr.sstackid])),
            f"sri {ithr.current_nodeid} {ithr.current_nodeid} 11", # current_nodeid = NWID >> 11
            f"sri {ithr.sstackid} {ithr.snodeid} 3", # snodeid = sstackid >> 3
            # now it is remote, we check the num of operands
            # numops = (X2 >> 20) & 0b111 + 2
            f"sri X2 {ithr.numops} 20", 
            f"andi {ithr.numops} {ithr.numops} {0b111}",
            f"addi {ithr.numops} {ithr.numops} 2",
            (3, ithrprint.printr("init: numops", [ithr.numops, ithr.tmp, ithr.snodeid])),
        ]
        # remaining regs (n=11): log2numuds, log2numlanes, gmapbase, mapbase, log2blocksize, tmp, sstackid, nstacks, snodeid, numops, psstackid
        # all the obs: obdst, obsrc, obnelems, (oblog2numnodes, oblog2blocksize, oblog2privblocksize)
        if self.enable3rdPartyMovers:
            actions += LocationEstimator().genEstimateActions(ithr, ithrprint, obdst, obsrc, obstartnodeid)
        else:
            actions += LocationEstimator().genEstimateActions(ithr, ithrprint, obdst, obsrc)
        ithr.free([ithr.numops, ithr.snodeid, ithr.dnodeid, ithr.current_nodeid])
        
        
        # [upgrade](11-5-2023)
        # compress log2blocksize and log2maxnstacks into one operand: first 32bits = log2blocksize, last 32bits = log2maxnstack
        ithr.log2blocksizelog2maxnstacks = 'alloc'
        ithr.nwid_mask = 'alloc'
        actions += [
            f"udshmem-skip-3rdparty: movir {ithr.log2blocksizelog2maxnstacks} 0",
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
        
        
        # Buffer Event Operands for stack-root at LM
        ithr.rstackid = 'alloc'
        ithr.lmbase = 'alloc'
        ithr.lmptr = 'alloc'
        actions += [
            (2, ithrprint.printr("init: writing operands into LM", [('obdst', obdst), ('obsrc', obsrc), ('obnelems', obnelems)])),
            (2, ithrprint.printr("init: writing operands(2)", [ithr.nstacks, ithr.log2blocksizelog2maxnstacks, ithr.gmapbase])),        
            f"addi X7 {ithr.lmbase} {self.lane_send_buffer_offset}",
            f"movir {ithr.lmptr} 0",
            # put the values in the LM
            f"movwrl {obdst} {ithr.lmbase}({ithr.lmptr},1,0)", #0 cannot be compressed
            f"movwrl {obsrc} {ithr.lmbase}({ithr.lmptr},1,0)", #1 cannot be compressed
            f"movwrl {obnelems} {ithr.lmbase}({ithr.lmptr},1,0)", #2 cannot be compressed
            f"movwrl {ithr.rstackid} {ithr.lmbase}({ithr.lmptr},1,0)", #3
            f"movwrl {ithr.nstacks} {ithr.lmbase}({ithr.lmptr},1,0)", #4
            f"movwrl {ithr.sstackid} {ithr.lmbase}({ithr.lmptr},1,0)", #5
            f"movwrl {ithr.log2blocksizelog2maxnstacks} {ithr.lmbase}({ithr.lmptr},1,0)", #6
            f"movwrl {ithr.gmapbase} {ithr.lmbase}({ithr.lmptr},1,0)", #7 cannot be compressed
        ]
        # >>> free gmapbase, log2blocksize, log2maxnstacks (log2blocksizelog2maxnstacks)
        ithr.free([ithr.gmapbase, ithr.log2blocksizelog2maxnstacks])
        

        # Update rstackid in LM, stack_base_nwid is the actual starting stack to put the movers
        ithr.stack_nwid_shift = 'alloc'
        ithr.stack_base_nwid = 'alloc'
        actions += [
            # send to all the stacks
            f"movir {ithr.lmptr} 3", # this points to rstakid
            f"add {ithr.log2numlanes} {ithr.log2numuds} {ithr.stack_nwid_shift}", # stack_nwid_shift = log2numlanes + log2numuds
            f"sl {ithr.psstackid} {ithr.stack_nwid_shift} {ithr.stack_base_nwid}", # stack_base_nwid = psstackid << stack_nwid_shift
            (2, ithrprint.printr("init: target stacks", [ithr.sstackid, ithr.stack_nwid_shift, ithr.stack_base_nwid, ithr.psstackid, ithr.log2numlanes, ithr.log2numuds])),
            # >>> free sstackid
        ]
        ithr.free(ithr.sstackid)
        
        
        # send to all the involved stacks
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
        # [upgrade](11-5-2023), ob changed according to init
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
            (3, sthrprint.printr("stack-root: src_stack_start:", [sthr.src_stack_start, ('obsrc', obsrc), sthr.log2seg])),
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
            # current stackid = sstackid + rstackid
            f"add {sthr.sstackid} {obrstackid} {sthr.stackid}",
            f"and {sthr.stackid} {sthr.mask} {sthr.stackid}",
            
            # estackid = [(src_end-8 - gmapbase) >> log2seg] & mask(maxnstacks)
            f"sub {sthr.src_end} {obgmapbase} {sthr.tmp}",
            f"sr {sthr.tmp} {sthr.log2seg} {sthr.tmp}",
            f"and {sthr.tmp} {sthr.mask} {sthr.estackid}",
            # sstackid = [(src - gmapbase) >> log2seg] & mask(maxnstacks)
            
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
            (3, sthrprint.printr("stack-root: stack_end:", [sthr.stack_end, sthr.stack_start, sthr.src_stack_end, ('obnstacks', obnstacks), ('obrstackid', obrstackid), sthr.tmp]))
            # >>> free src_stack_end
        ]
        sthr.free([sthr.src_stack_end, sthr.maxnstacks])
        # stack end and stack start seem to be correct
        
        sthr.nsegs = 'alloc'
        sthr.snelems = 'alloc'
        actions +=[
            # nsegs = (stack_end - stack_start) >> (log2seg + log2maxnstacks)
            f"sub {sthr.stack_end} {sthr.stack_start} {sthr.nsegs}",
            f"add {sthr.log2seg} {sthr.log2maxnstacks} {sthr.tmp}",
            f"sr {sthr.nsegs} {sthr.tmp} {sthr.nsegs}",
            f"addi {sthr.nsegs} {sthr.nsegs} 1", # always have at least one seg since this stack has data
            (3, sthrprint.printr("stack-root: nsegs:", [sthr.nsegs, sthr.stack_end, sthr.stack_start, sthr.log2seg, sthr.log2maxnstacks, sthr.tmp])),
            
            # snelems = nsegs << (log2seg - 3)
            f"subi {sthr.log2seg} {sthr.tmp} 3",
            f"sl {sthr.nsegs} {sthr.tmp} {sthr.snelems}",
            (3, sthrprint.printr("stack-root: SNELEMS(before -src_head, -src_tail):", [sthr.snelems])),
            
        ]
        # >>> free nsegs
        sthr.free(sthr.nsegs)
        
        
        sthr.expect = 'alloc'
        actions += [
            # stackid = nwid >> 8  # just assume we will always have 4 uds, 64 lanes, that is (2 + 6)
            # expect = 0
            f"movir {sthr.expect} 0",
            
            # sstackid = [(src - gmapbase) >> log2seg] & mask(maxnstacks)
            # estackid = [(src_end-8 - gmapbase) >> log2seg] & mask(maxnstacks)
            f"sub {sthr.src_end} {obgmapbase} {sthr.tmp}",
            f"sr {sthr.tmp} {sthr.log2seg} {sthr.tmp}",
            f"and {sthr.tmp} {sthr.mask} {sthr.estackid}",
            (3, sthrprint.printr("stack-root: stackid", [sthr.stackid])),
            (3, sthrprint.printr("stack-root: sstackid", [sthr.sstackid])),
            (3, sthrprint.printr("stack-root: estackid", [sthr.estackid])),
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
        sthr.free([sthr.stack_end, sthr.src_end, sthr.tailnelems])
        
        
        sthr.aligned_start = 'alloc'
        sthr.aligned_end = 'alloc'
        sthr.tmp2 = 'alloc'
        
        actions += [
            # now get the unaligned data
            f"udshmem-no-stack-tail: sri {sthr.start} {sthr.aligned_start} 6", # aligned_start = start >> 6 << 6 + (64 if start > aligned_start else 0)
            # (4, sthrprint.printr("stack-root: SNELEMS-beforeAlignemnt:", [sthr.snelems, sthr.start])),
            f"sli {sthr.aligned_start} {sthr.aligned_start} 6",
            (4, sthrprint.printr("stack-root: SNELEMS-beforeAlignemnt:", [sthr.snelems, sthr.start, sthr.aligned_start])),
            f"ble {sthr.start} {sthr.aligned_start} udshmem-start-aligned",
            # if not alighed, check if we are one 64B away from next segment
            # if so, we need to add a stripe to it
            # tmp = log2seg
            # if 1<<log2seg == aligned_start - stack_start + 64, we then need to add a stripe to it
            f"movir {sthr.tmp} 1",
            f"sl {sthr.tmp} {sthr.log2seg} {sthr.tmp}",
            f"sub {sthr.aligned_start} {sthr.stack_start} {sthr.tmp2}",
            f"addi {sthr.tmp2} {sthr.tmp2} 64",
            # if segsize==64, then we need to add a block to it
            f"bne {sthr.tmp} {sthr.tmp2} udshmem-log2seg-no-stripe",
            f"movir {sthr.tmp} 1",
            f"add {sthr.log2seg} {sthr.log2maxnstacks} {sthr.tmp2}",
            f"sl {sthr.tmp} {sthr.tmp2} {sthr.tmp}",
            f"add {sthr.aligned_start} {sthr.tmp} {sthr.aligned_start}",
            (4, sthrprint.printr("stack-root: AlignedStart if log2seg==6:", [sthr.aligned_start, sthr.start, sthr.log2seg, sthr.tmp, sthr.tmp2])),
            f"jmp udshmem-start-aligned",
            f"udshmem-log2seg-no-stripe: addi {sthr.aligned_start} {sthr.aligned_start} 64",
        ]
        sthr.free([sthr.log2seg, sthr.tmp2, sthr.stack_start, ])
        
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
            (2, sthrprint.printr("stack-root: SENDING HEADS", [sthr.start, sthr.nheads, sthr.diff])),
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
            (2, sthrprint.printr("stack-root: SENDING TAILS:", [sthr.aligned_end, sthr.ntails, sthr.diff])),
            # >>> free ntail, aligned_end, tnwid, evw
        ]
        # print(sthr,sthr.ntails, sthr.aligned_end, sthr.tnwid, sthr.evw)
        sthr.free([sthr.ntails, sthr.aligned_end, sthr.tnwid, sthr.evw])
        
        
        sthr.nchunks = 'alloc'

        actions += [
            # nchunks = snelems >> 3
            f"udshmem-no-tail: sri {sthr.snelems} {sthr.nchunks} 3",
            (3, sthrprint.printr("stack-root: snelems-final:", [sthr.snelems])),
        ]
        
        ''' 
        [STACK-ROOT]
        LAUDSHMEM worker num estimator
        work_estimator_exp_scaler: higher values means fewer workers: log2nworkers = log2nworkers >> work_estimator_exp_scaler
        work_estimator_scaler: higher values means fewer workers: nchunks = nchunks >> work_estimator_scaler
        log2nworkers = log2(nchunks>>work_estimator_scaler) >> work_estimator_exp_scaler
        '''
        # naive worker num estimater
        # log2nworkers = nchunks >> 2
        # if log2nworkers <= 6 goto launch-ud
        # log2nworkers = 6
        # launch-ud: nworkers = 1 << log2nworkers
        # when 1024B per stack, there will be 16 chunks, then shfit 2 we got log2nworkers=4, 16 workers
        # when 2048B per stack, there will be 32 chunks, then shfit 2 we got log2nworkers=8, 64 workers; thus increasing the time; 
        # work_estimator_exp_scaler: higher values means fewer workers: log2nworkers = log2nworkers >> work_estimator_exp_scaler
        #
        sthr.log2nworkers = 'alloc'
        # actions += WorkEstimator(0, 0).genEstimateActions(sthr, sthrprint)
        actions += WorkEstimator(self.work_estimator_exp_scaler, self.work_estimator_scaler, self.maxlog2nworkers).genEstimateActions(sthr, sthrprint)
        
        sthr.rudid = 'alloc'
        sthr.base_nwid = 'alloc'
        sthr.lmbase = 'alloc'
        sthr.lmptr = 'alloc'
        actions += [
            f"launch-ud: movir {sthr.rudid} 0",
            f"mov_reg2reg NWID {sthr.base_nwid}",
            (2, sthrprint.printr("stack-root: nchunks:", [sthr.nchunks, sthr.log2nworkers, sthr.rudid, sthr.base_nwid])),
            f"addi X7 {sthr.lmbase} {self.lane_send_buffer_offset}",
            (3, sthrprint.printr("stack-root: writing to ud-root:",[sthr.stackid, sthr.aligned_start, sthr.diff, sthr.nchunks, sthr.rudid, sthr.log2nworkers, sthr.log2blocksize, sthr.log2maxnstacks])),
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
        # obs: obaligned_start, obdiff, obnchunks (per stack), obrudid, oblog2nworkers, oblog2blocksize, oblog2maxnstacks
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
            f"evii {udthr.evw} {self.em['udshmem-general-worker-read']} 255 {0b0101}",
            f"launch-worker-loop: ble {udthr.widx_end} {udthr.widx} worker-loop-done",
            f"movwrl {udthr.widx} {udthr.lmbase}({udthr.lmptr},0,0)",
            # tnwid = base_nwid + widx % 64
            f"and {udthr.widx} {udthr.lanemask} {udthr.tnwid}",
            f"add {udthr.base_nwid} {udthr.tnwid} {udthr.tnwid}",
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
        
        # endregion udshmem-distributor
        #===============================================udshmem-work-distributor=========================================
        
        

        
        #==================================================udshmem-worker================================================
        #region udshmem-workers
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
        # wthr.stackid = 'alloc'
        actions = []
        if self.debug_level:
            actions +=[
                (4, wthrprint.perflogr(pmap['worker-starts'], "WORKER-START.", [])),
                (4, wthrprint.printr("general-worker-read:", [('obaligned_start', obaligned_start), ('obdiff', obdiff), ('obnchunks', obnchunks), ('obwidx', obwidx), ('oblog2nworkers', oblog2nworkers), ('oblog2blocksize', oblog2blocksize), ('oblog2maxnstacks', oblog2maxnstacks)])),
            ]
        
        actions += [
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
        # wthr.stripe = 'alloc'
        wthr.log2stripe = 'alloc'
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
            f"add {oblog2maxnstacks} {wthr.log2seg} {wthr.log2stripe}",
            f"subi {wthr.maxnstacks} {wthr.maxnstacks} 1",
            f"sl {wthr.maxnstacks} {wthr.log2seg} {wthr.dstripe}", # do not free dstripe
        
            # initoffset = obwidx << 6
            # new implementation
            f"sli {obwidx} {wthr.initoffset} 6",  
        ]
        # >>> free fdnchunks
        wthr.free([wthr.fdnchunks, wthr.maxnstacks, wthr.rmnchunks])
        
        wthr.aligned_start = 'alloc'
        wthr.aligned_base = 'alloc'
        wthr.head = 'alloc'
        actions += [
            # aligned_base = aligned_start >> log2seg << log2seg
            f"sr {obaligned_start} {wthr.log2seg} {wthr.aligned_base}",
            f"sl {wthr.aligned_base} {wthr.log2seg} {wthr.aligned_base}",
            (4, wthrprint.printr("general-worker-read, check-worker-write: aligned_base:", [ ('obwidx', obwidx), wthr.aligned_base, wthr.log2seg])),
            # head = aligned_start - aligned_base
            f"sub {obaligned_start} {wthr.aligned_base} {wthr.head}",
            # initoffset = head + initoffset
            f"add {wthr.head} {wthr.initoffset} {wthr.initoffset}",
            # >>> free aligned_start, aligned_base
        ]
        wthr.free([wthr.aligned_start, wthr.head])
        
        wthr.segmask = 'alloc' # do not free
        wthr.rminitoffset = 'alloc' 
        wthr.nsstripe = 'alloc'
        actions += [
            # nsstripe = initoffset >> log2seg , stack stripe
            f"sr {wthr.initoffset} {wthr.log2seg} {wthr.nsstripe}",
            (4, wthrprint.printr("general-worker-read: nsstripe:", [('obwidx', obwidx), wthr.nsstripe, wthr.initoffset, wthr.log2seg])),
            # segmask = (1 << log2seg) - 1
            f"movir {wthr.segmask} 1",
            f"sl {wthr.segmask} {wthr.log2seg} {wthr.segmask}",
            f"subi {wthr.segmask} {wthr.segmask} 1", # do not free segmask
            
            # rminitoffset = initoffset & segmask
            f"and {wthr.initoffset} {wthr.segmask} {wthr.rminitoffset}",
            # >>> free initoffset
           
        ]
        wthr.free(wthr.initoffset)
        
        # calculate stride
        # stride = 1 << (log2nworkers + 2(UD) + 6(64B))
        wthr.stride = 'alloc'
        actions += [
            f"movir {wthr.stride} 1",
            f"addi {oblog2nworkers} {wthr.tmp} 8",
            f"sl {wthr.stride} {wthr.tmp} {wthr.stride}",   
        ]
        wthr.free(wthr.tmp)
        
        wthr.ldptr = 'alloc'
        wthr.seghead = 'alloc'
        wthr.segsize = 'alloc'
        actions += [
            # ldptr = aligned_base + nsstripe * stripe + rminitoffset
            f"sl {wthr.nsstripe} {wthr.log2stripe} {wthr.ldptr}",
            f"add {wthr.aligned_base} {wthr.ldptr} {wthr.ldptr}",
            f"add {wthr.rminitoffset} {wthr.ldptr} {wthr.ldptr}",
            (4, wthrprint.printr("general-worker-read: rminitoffset:", [ ('obrudid', obrudid), wthr.rminitoffset, wthr.nsstripe, wthr.segmask])),
            # seghead = ldptr >> log2seg << log2seg
            f"sr {wthr.ldptr} {wthr.log2seg} {wthr.seghead}",
            f"sl {wthr.seghead} {wthr.log2seg} {wthr.seghead}",
            f"addi {wthr.segmask} {wthr.segsize} 1",
            # >>> free aligned_base, rmintoffset, nsstripe
            # allocate strptr
        ]
        wthr.free([wthr.aligned_base, wthr.rminitoffset, wthr.nsstripe])
        # print(wthr)
        # wthr.strptr = 'alloc' # do not free
        wthr.diff = 'alloc' # do not free
        wthr.maxout = 'alloc' # do not free
        wthr.nout = 'alloc' # do not free
        wthr.ld_nleft = 'alloc' # do not free
        wthr.st_nleft = 'alloc' # do not free
        wthr.evw = 'alloc'
        
        # if self.debug_level:
        #     wthr.pnelems = 'alloc'
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
            # (5, wthrprint.printr("GENERAL-WORKER-READ: Before sending read event", [wthr.ldptr, ('obdiff', obdiff),  wthr.ld_nleft, wthr.st_nleft, ('maxout', wthr.maxout)])),
            f"blei {wthr.ld_nleft} 0 udshmem-worker-terminate",
            f"addi {obdiff} {wthr.diff} 0",
            # send the event to itself, with current thread context and contw=X1
            (4, wthrprint.printr("general-worker-read: stride", [wthr.stride, wthr.ldptr, wthr.wnchunks, ('oblog2nworkers', oblog2nworkers)])),
        ]

        if self.impl == self.implLocAwareUnrealBaseline: # default use interleaving
            actions += [
                f"evi X2 {wthr.evw} {self.em['udshmem-worker-read']} {0b0001}",
            ]
        elif self.impl == self.implLocAwareEvLoop:
            actions += [
                f"evi X2 {wthr.evw} {self.em['udshmem-worker-ev-read-loop']} {0b0001}",
            ]
        else:
            actions += [
                f"evi X2 {wthr.evw} {self.em['udshmem-worker-interleaving-read-write']} {0b0001}",
            ]
            
            
        actions += [f"sendr_wcont {wthr.evw} X1 {wthr.ldptr} {wthr.maxout}"]
        # >>> free evw    
        wthr.free(wthr.evw)
        
        wthr.tmp = 'alloc'
        actions += [
            f"yield",
            f"udshmem-worker-terminate: sendr_reply X31 X30 {wthr.tmp}",
            (4, wthrprint.printr("general-worker-read: terminate", [wthr.ldptr, ('obdiff', obdiff),  wthr.ld_nleft, wthr.st_nleft, ('maxout', wthr.maxout)])),
            f"yieldt",
        ]
        wthr.free(wthr.tmp)
        self.appendTranActions(tran, actions)
        # endregion general-worker-read
        #-----------------------------------------------------general-worker-read-----------------------------------------------------
        
        
        """ Unrealistic Baseline
            Infinite event queue size, infinite DRAM queue size
        """
        #-----------------------------------------------------WORKER-READ-----------------------------------------------------
        # region worker-read
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.em['udshmem-worker-read'])
        wthr.nseg = 'alloc'
        wthr.tmp = 'alloc'
        
        actions = [   
            # split shi into two event
            (5, wthrprint.printr("WORKER-READ:", [wthr.ldptr, wthr.diff,  wthr.ld_nleft, wthr.st_nleft, ('maxout', wthr.maxout)])),
            f"read-loop: send_dmlm_ld_wret {wthr.ldptr} {self.em['udshmem-worker-write-8']} 8 {wthr.tmp}",
            # tmp = (ldptr + stride) - seghead
            f"add {wthr.ldptr} {wthr.stride} {wthr.tmp}",
            f"sub {wthr.tmp} {wthr.seghead} {wthr.tmp}",
            
            # nseg = tmp >> log2seg
            f"sr {wthr.tmp} {wthr.log2seg} {wthr.nseg}",
            
            # dstripe = nseg * stripe - seg; or dstripe = nseg <<log2stripe - seg
            f"sl {wthr.nseg} {wthr.log2stripe} {wthr.dstripe}",
            f"and {wthr.tmp} {wthr.segmask} {wthr.tmp}",
            
            # dstripe = dstripe + (ldptr + stride-seghead) & segmask
            f"add {wthr.dstripe} {wthr.tmp} {wthr.dstripe}",
            
            # ldptr = seghead + dstripe
            f"add {wthr.seghead} {wthr.dstripe} {wthr.ldptr}",
            f"sr {wthr.ldptr} {wthr.log2seg} {wthr.seghead}",
            f"sl {wthr.seghead} {wthr.log2seg} {wthr.seghead}",
            f"subi {wthr.ld_nleft} {wthr.ld_nleft} 8", # one chunk gone!, each chunk is 8*8B
            f"blei {wthr.ld_nleft} 0 udshmem-worker-done",
            f"jmp read-loop",
            f"udshmem-worker-done: yield",
        ]
        wthr.free([wthr.nseg, wthr.tmp])
        self.appendTranActions(tran, actions)
        # endregion worker-read
        #-----------------------------------------------------WORKER-READ-----------------------------------------------------
        
    
        """ 
        Genenral write/ack
        """
        #-----------------------------------------------------WORKER-WRITE-ACK-----------------------------------------------------
        # region worker-write-ack
        # need to allocate and free tmp registers otherwise it won't be enough
        def _ev_write(C=8):
            chunk_size = C if C <= 8 else 8
            addr_reg = 'X' + str((chunk_size + 8) if chunk_size < 8 else 3)
            tran = self.state.writeTransition("eventCarry", self.state, self.state, self.em[f'udshmem-worker-write-{C}'])
            wthr.tmp = 'alloc'
            wthr.strptr = 'alloc'
            actions = [
                (5, wthrprint.printr(f"worker-write-{C}: WRITE DRAM", [ wthr.ldptr, wthr.diff,  wthr.ld_nleft, wthr.st_nleft, ('addr_reg', addr_reg)]) ),
            ]
            if self.debug_level > 3:
                for i in range(C):
                    actions +=[
                        (5, wthrprint.printr(f"worker-write-{C}: WRITE DRAM", [(f'op{i}', f'X{8+i}')])),
                    ]
    
            # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ REAL WRITE~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            actions += [
                f"udshmem-write-cont: add {wthr.diff} {addr_reg} {wthr.strptr}",
                f"sendops_dmlm_wret {wthr.strptr} {self.em[f'udshmem-worker-ack-{C}']} X8 {chunk_size} {wthr.tmp}",
            ]
            # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ REAL WRITE~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            
            actions +=[
                f"blei {wthr.ld_nleft} 0 udshmem-no-more-read",
                # TODO: Needs throttling here
                f"udshmem-no-more-read: yield",
            ]
            wthr.free([wthr.tmp, wthr.strptr])
            self.appendTranActions(tran, actions)
            
        
        def _ev_ack(C=8):
            wthr.acnelems = 'alloc'
            
            tran = self.state.writeTransition("eventCarry", self.state, self.state, self.em[f'udshmem-worker-ack-{C}'])
            actions = [(5,wthrprint.printr(f"worker-ack-{C}: ACK", [ wthr.ldptr, wthr.diff, wthr.ld_nleft, wthr.st_nleft, ('maxout', wthr.maxout)])),]
            if self.perflog_level:
                actions += [
                    f"sli {wthr.wnchunks} {wthr.acnelems} 3",
                    f"bne {wthr.acnelems} {wthr.st_nleft} ack-cont",
                    (4, wthrprint.perflogr(pmap['worker-ack-starts'], "WORKER-ACK-STARTS.", [])),
                ]
            wthr.free(wthr.acnelems)
            actions += [  
                f"ack-cont: subi {wthr.st_nleft} {wthr.st_nleft} {C}",
                (4, wthrprint.printr(f"worker-ack-{C}: ACK", [ wthr.ld_nleft, wthr.st_nleft, wthr.nout, ('maxout', wthr.maxout)])),
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
                    (4, wthrprint.printr(f"worker-ack-{C}: RESUMING READ", [ wthr.ld_nleft, wthr.st_nleft, wthr.nout, ('maxout', wthr.maxout)])),
                    f"evi X2 {wthr.evw} {self.em['udshmem-worker-read-throttled']} {0b0001}",
                    f"sendr_wcont {wthr.evw} X1 {wthr.ldptr} {wthr.maxout}",
                ]
            wthr.tmp = 'alloc'
            actions += [
                f"udshmem-no-more-read: yield",
                f"udshmem-worker-ack-{C}-done: sendr3_reply {wthr.nout} X1 X2 {wthr.tmp}",
                (4, wthrprint.perflogr(pmap['worker-ends'], "WORKER-ACK-ENDS.", [])),
                (4, wthrprint.printr(f"worker-ack-{C}: send reply to",[('CCONT','X1'), ('CEVW', 'X2')])),
                (4, wthrprint.printr(f"worker-ack-{C}: DONE", [ wthr.ldptr, wthr.diff, wthr.ld_nleft, wthr.st_nleft, ('maxout', wthr.maxout)])) ,
                f"yieldt",
            ]
            wthr.free([wthr.tmp, wthr.evw])
            self.appendTranActions(tran, actions)
        # endregion worker-write-ack
        #-----------------------------------------------------WORKER-WRITE-ACK-----------------------------------------------------
      
        
        """ Interleaving READ-WRITE
            Fixed max queue size for each SHMEM call
            strided:
            event: udshmem-worker-interleaving-read-write
            event: udshmem-worker-interleaving-write
            event: udshmem-worker-ack-8 ^ above
        """
    
        #-----------------------------------------------------INTERLEAVING-READ-WRITE-------------------------------------------------------
        # region interleaving-read-write
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.em['udshmem-worker-interleaving-read-write'])
        wthr.nseg = 'alloc'
        wthr.tmp = 'alloc'
        actions = []    
        actions += [   
            # split this into two event
            # (3, wthrprint.printr("WORKER-READ-INTERLEAVING:", [ wthr.ldptr, wthr.diff,  wthr.ld_nleft, wthr.st_nleft, wthr.nout, ('maxout', wthr.maxout)])),
            f"read-loop: blei {wthr.ld_nleft} 0 udshmem-worker-done",
            f"ble {wthr.maxout} {wthr.nout} udshmem-worker-done",
            f"send_dmlm_ld_wret {wthr.ldptr} {self.em['udshmem-worker-interleaving-write']} 8 {wthr.tmp}", # not throttling write but ack will know
            (5, wthrprint.printr("WORKER-READ-INTERLEAVING:", [ wthr.ldptr, wthr.diff, wthr.ld_nleft, wthr.st_nleft])),
            
            # tmp = (ldptr + stride) - seghead
            f"add {wthr.ldptr} {wthr.stride} {wthr.tmp}",
            f"sub {wthr.tmp} {wthr.seghead} {wthr.tmp}",
            
            # nseg = tmp >> log2seg
            f"sr {wthr.tmp} {wthr.log2seg} {wthr.nseg}",
            
            # dstripe = nseg * stripe - seg; or dstripe = nseg <<log2stripe - seg
            f"sl {wthr.nseg} {wthr.log2stripe} {wthr.dstripe}",
            f"and {wthr.tmp} {wthr.segmask} {wthr.tmp}",
            
            # dstripe = dstripe + (ldptr + stride-seghead) & segmask
            f"add {wthr.dstripe} {wthr.tmp} {wthr.dstripe}",
            
            # ldptr = seghead + dstripe
            f"add {wthr.seghead} {wthr.dstripe} {wthr.ldptr}",
            f"sr {wthr.ldptr} {wthr.log2seg} {wthr.seghead}",
            f"sl {wthr.seghead} {wthr.log2seg} {wthr.seghead}",
            f"subi {wthr.ld_nleft} {wthr.ld_nleft} 8", # one chunk gone!, each chunk is 8*8B
            f"addi {wthr.nout} {wthr.nout} 1",
            (5, wthrprint.printr("WORKER-READ-INTERLEAVING-AFTER:", [ wthr.ldptr, wthr.diff, wthr.dstripe, wthr.seghead, wthr.stride, wthr.nseg])),
            (5, wthrprint.printr("WORKER-READ-INTERLEAVING-AFTER(2):", [ wthr.segmask, wthr.log2seg])),
            f"jmp read-loop",
            f"udshmem-worker-done: yield",
            f"udshmem-worker-wait: yield",
        ]
        wthr.free([wthr.nseg, wthr.tmp])
        self.appendTranActions(tran, actions)
        
        #-------------------------------------------interleaving-read-write-ack-------------------------------------------
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.em[f'udshmem-worker-interleaving-write'])
        addr_reg = 'X3'
        wthr.strptr = 'alloc'
        wthr.tmp = 'alloc'
        actions = [
            (4, wthrprint.printr(f"worker-interleaving-write: WRITE DRAM", [ wthr.diff, wthr.ld_nleft, wthr.st_nleft, ('addr_reg', addr_reg)]) ),
        ]
        if self.debug_level > 1:
            for i in range(8):
                actions +=[
                    # (4, wthrprint.printr(f"worker-write-{C}: WRITE DRAM", [ wthr.ldptr, wthr.diff,  wthr.ld_nleft, wthr.st_nleft, ('addr_reg', addr_reg)])),
                    (4, wthrprint.printr(f"worker-interleaving-write: WRITE DRAM", [(f'op{i}', f'X{8+i}')])),
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
        wthr.free(wthr.tmp)
        wthr.evw = 'alloc'
        actions +=[
            
            f"udshmem-worker-resume-read: blei {wthr.ld_nleft} 0 udshmem-no-more-read",
            f"evi X2 {wthr.evw} {self.em['udshmem-worker-interleaving-read-write']} {0b0001}", 
            f"sendr_wcont {wthr.evw} X1 {wthr.ldptr} {wthr.maxout}",
            f"udshmem-no-more-read: yield",
        ]
        wthr.free([wthr.evw, wthr.strptr])
        self.appendTranActions(tran, actions)
        #-------------------------------------------interleaving-read-write-ack-ends------------------------------------------

            
    
        # endregion interleaving-read-write
        #-----------------------------------------------------INTERLEAVING-READ-WRITE-ENDS-------------------------------------------------------
        
        """ Event Loop
        
        """
        
        #-----------------------------------------------------EV-READ-LOOP-----------------------------------------------------
        # region ev-read-loop
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.em['udshmem-worker-ev-read-loop'])
        wthr.nseg = 'alloc'
        wthr.tmp = 'alloc'
       
        actions =[   
            # split this into two event
            (3, wthrprint.printr("WORKER-EV-READ-LOOP:", [ wthr.ldptr, wthr.diff,  wthr.ld_nleft, wthr.st_nleft, wthr.nout, ('maxout', wthr.maxout)])),
            f"read-loop: blei {wthr.ld_nleft} 0 udshmem-read-done",
            f"ble {wthr.maxout} {wthr.nout} udshmem-read-wait",
            f"send_dmlm_ld_wret {wthr.ldptr} {self.em['udshmem-worker-write-8']} 8 {wthr.tmp}", # not throttling write but ack will know
            # tmp = (ldptr + stride) - seghead
            f"add {wthr.ldptr} {wthr.stride} {wthr.tmp}",
            f"sub {wthr.tmp} {wthr.seghead} {wthr.tmp}",
            
            # nseg = tmp >> log2seg
            f"sr {wthr.tmp} {wthr.log2seg} {wthr.nseg}",
            
            # dstripe = nseg * stripe - seg; or dstripe = nseg <<log2stripe - seg
            f"sl {wthr.nseg} {wthr.log2stripe} {wthr.dstripe}",
            f"and {wthr.tmp} {wthr.segmask} {wthr.tmp}",
            
            # dstripe = dstripe + (ldptr + stride-seghead) & segmask
            f"add {wthr.dstripe} {wthr.tmp} {wthr.dstripe}",
            
            # ldptr = seghead + dstripe
            f"add {wthr.seghead} {wthr.dstripe} {wthr.ldptr}",
            f"sr {wthr.ldptr} {wthr.log2seg} {wthr.seghead}",
            f"sl {wthr.seghead} {wthr.log2seg} {wthr.seghead}",
            f"subi {wthr.ld_nleft} {wthr.ld_nleft} 8", # one chunk gone!, each chunk is 8*8B
            # (5, wthrprint.printr("WORKER-EV-READ:", [ wthr.ld_nleft, wthr.st_nleft, wthr.pnelems, wthr.nout, ('maxout', wthr.maxout)])),
            f"addi {wthr.nout} {wthr.nout} 1",
            f"jmp read-loop",
            f"udshmem-read-done: yield",
            f"udshmem-read-wait: movir {wthr.nout} 0", 
            f"sendr_wcont X2 X1 {wthr.ldptr} {wthr.maxout}", # just sendmyself
            f"yield",
        ]

        wthr.free([wthr.nseg, wthr.tmp])
        self.appendTranActions(tran, actions)
        
        # endregion ev-read-loop
        #-----------------------------------------------------EV-READ-LOOP-END-----------------------------------------------------
    
    
        #-----------------------------------------------------udshmem-handle-head-tail-----------------------------------------------------
        # region handle-head-tail
        # this should have the same thread context as above
        tran = self.state.writeTransition("eventCarry", self.state, self.state, self.em[f'udshmem-handle-head-tail'])
        # obs: obsrc, obnelems, obdiff and this thread is executed only once
        wthr.tmp = 'alloc'
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
        wthr.free(wthr.tmp)
        self.appendTranActions(tran, actions)  
        
        # endregion handle-head-tail
        #-----------------------------------------------------udshmem-handle-head-tail-----------------------------------------------------
        
        
        
        for c in self.chunks:
            _ev_write(c)
            _ev_ack(c)

        #endregion
        #==================================================udshmem-worker================================================
        


        #==================================================deprecated================================================
        # region deprecated
        #-----------------------------------------------------WORKER-READ-THROTTLED-----------------------------------------------------
        # region worker-read-throttled
        def throttled():
            tran = self.state.writeTransition("eventCarry", self.state, self.state, self.em['udshmem-worker-read-throttled'])
            wthr.inc = 'alloc'
            wthr.tmp = 'alloc'
            
            actions = []
            # if self.perflog_level:
            #     actions += [
            #         f"sli {wthr.wnchunks} {wthr.pnelems} 3",
            #         f"bne {wthr.pnelems} {wthr.ld_nleft} read-loop",
            #         (6, wthrprint.perflogr(pmap['worker-read-starts'], "WORKER-READ-THROTTLED-START.", [])),
            #     ]
            
            
            actions += [   
                # split shi into two event
                (3, wthrprint.printr("WORKER-READ-THROTTLED:", [ wthr.ldptr, wthr.diff, wthr.ld_nleft, wthr.st_nleft, wthr.nout, ('maxout', wthr.maxout)])),
                # f"read-loop: send_dmlm_ld_wret {wthr.ldptr} {self.em['udshmem-worker-write-8-throttled']} 8 {wthr.tmp}",
                f"read-loop: blei {wthr.ld_nleft} 0 udshmem-worker-done",
                f"ble {wthr.maxout} {wthr.nout} udshmem-worker-wait",
                f"send_dmlm_ld_wret {wthr.ldptr} {self.em['udshmem-worker-write-8']} 8 {wthr.tmp}", # not throttling write but ack will know
                f"add {wthr.ldptr} {wthr.ldptr} {wthr.stride}",
                
                # inc = 0; if ldptr & segmask: inc=1 ; if inc==1 meaning their is remainder, inc-1 as mask would mask out all the stripes; 
                # if inc==0 meaning no remainder, inc-1 as mask would mask out nothing.
                f"and {wthr.ldptr} {wthr.segmask} {wthr.tmp}",
                f"movir {wthr.inc} 0",
                f"cgti {wthr.tmp} {wthr.inc} 0", # if tmp > 0, inc would be 1. has tmp meaning it has remainder, meaning we still has reach the turning point
                f"subi {wthr.inc} {wthr.inc} 1",
                f"and {wthr.dstripe} {wthr.inc} {wthr.inc}",
                f"add {wthr.ldptr} {wthr.inc} {wthr.ldptr}",
                f"subi {wthr.ld_nleft} {wthr.ld_nleft} 8", # one chunk gone!, each chunk is 8*8B
                # (6, wthrprint.printr("WORKER-READ-THROTTLED:", [ wthr.inc, wthr.dstripe, wthr.ldptr, wthr.ld_nleft, wthr.st_nleft,  ('maxout', wthr.maxout)])),
                # (5, wthrprint.printr("WORKER-READ-THROTTLED:", [ wthr.ld_nleft, wthr.st_nleft, wthr.pnelems, wthr.nout, ('maxout', wthr.maxout)])),
                f"addi {wthr.nout} {wthr.nout} 1",
                # f"blei {wthr.ld_nleft} 0 udshmem-worker-done",
                f"jmp read-loop",
            
            ]
            # if self.perflog_level:
            #     actions += [
            #         f"udshmem-worker-done: addi {wthr.pnelems} {wthr.pnelems} 0",
            #         (4, wthrprint.perflogr(pmap['worker-read-ends'],"WORKER-READ-THROTTLED-ENDS.", [])),
            #         f"yield",
            #     ]
            # else:
            actions += [
                    f"udshmem-worker-done: yield",
                ]
            actions +=[
                f"udshmem-worker-wait: yield",
            ]

            wthr.free([wthr.inc, wthr.tmp])
            self.appendTranActions(tran, actions)
        # endregion worker-read
        #-----------------------------------------------------WORKER-READ-THROTTLED-----------------------------------------------------
        
        #-----------------------------------------------------WORKER-WRITE-ACK-THROTTLED-----------------------------------------------------
        # region worker-write-ack-throttled
        # need to allocate and free tmp registers otherwise it won't be enough
        def _ev_write_throttled_old(C=8):
            chunk_size = C if C <= 8 else 8
            addr_reg = 'X' + str((chunk_size + 8) if chunk_size < 8 else 3)
            tran = self.state.writeTransition("eventCarry", self.state, self.state, self.em[f'udshmem-worker-write-{C}-throttled'])
            wthr.strptr = 'alloc'
            actions = [
                (5, wthrprint.printr(f"worker-write-{C}-throttled: WRITE DRAM", [ wthr.ldptr, wthr.diff,  wthr.ld_nleft, wthr.st_nleft, ('addr_reg', addr_reg)]) ),
            ]
            if self.debug_level > 3:
                for i in range(C):
                    actions +=[
                        # (4, wthrprint.printr(f"worker-write-{C}: WRITE DRAM", [ wthr.ldptr, wthr.diff,  wthr.ld_nleft, wthr.st_nleft, ('addr_reg', addr_reg)])),
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
        # if self.impl == 'loc-aware-throttled-old':
        #     _ev_write_throttled_old(8)
        # endregion deprecated
        #==================================================deprecated================================================
   
   
def static_call_udshmem_put(tran, cont_label=1, numops=3):
    static_call_udshmem(tran, cont_label, numops, 'udshmem_put')
    
    
def static_call_udshmem_get(tran, cont_label=1, numops=3):
    static_call_udshmem(tran, cont_label, numops, 'udshmem_get')


def static_call_udshmem(tran, cont_label=1, numops=3, op='udshmem_put'):
    uthr = AdvancedRegister()
    uthr.lmbase = 'alloc'
    uthr.lmptr = 'alloc'
    uthr.evw = 'alloc'
    uthr.tmp = 'alloc'
    uthr.tmp1 = 'alloc'
    uthr.nwid = 'alloc'
    uthr.contw = 'alloc'
    print(f"Wrapping static_call_udshmem: numops={numops}")
    actions = [
        # (0, f"print 'BEFORE'"),
        f"evii {uthr.evw} {op} 255 {0b0101}",
        # f"sendops_wret {uthr.evw} {cont_label} X8 {self.numops} {uthr.tmp} {uthr.tmp1}",
        
        # TODO: this gets NWID wrong in the evword and contw
        f"mov_reg2reg NWID {uthr.nwid}",
        f"ev {uthr.evw} {uthr.evw} {uthr.nwid} {uthr.nwid} {0b1000}",
        # f"print '[NWID=%ld]END evw=%lu, cevw=%ld' NWID {uthr.evw} X2",
        # f"mov_reg2reg X2 {uthr.contw}",
        f"evi X2 {uthr.contw} {cont_label} {0b0001}",
        f"ev {uthr.contw} {uthr.contw} {uthr.nwid} {uthr.nwid} {0b1000}",
        f"print 'statically call udshmem: evw=%lu, contw=%lu, nwid=%lu, EVW=%lu, CONT=%lu, numops={numops}' {uthr.evw} {uthr.contw} {uthr.nwid} X2 X1",
        f"sendops_wcont {uthr.evw} {uthr.contw} X8 {numops}",
        f"yield",
    ]
    appendTransActions(tran, actions)
    uthr.freeall() 

# CAUDShmem = LAUDShmem