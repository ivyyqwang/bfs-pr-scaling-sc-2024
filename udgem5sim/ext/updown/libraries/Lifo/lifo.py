from linker.EFAProgram import efaProgram

## Global constants

@efaProgram
def EFA_lifo(efa):
  efa.code_level = 'machine'
  state0 = efa.State("udweave_init") #Only one state code 
  efa.add_initId(state0.state_id)
  ## Static declarations
  ## Scoped Variable "counter" uses Register X16, scope (0)
  ## Scoped Variable "descriptor" uses Register X17, scope (0)
  ## Param "descriptorIn" uses Register X8, scope (0->1)
  ## Param "sendBuffer" uses Register X9, scope (0->1)
  ## Param "addressLM" uses Register X10, scope (0->1)
  ## Param "sizeLM" uses Register X11, scope (0->1)
  ## Param "addressDRAM" uses Register X12, scope (0->1)
  ## Param "sizeDRAN" uses Register X13, scope (0->1)
  ## Scoped Variable "spPtr" uses Register X18, scope (0->1)
  ## Param "descriptorIn" uses Register X8, scope (0->2)
  ## Scoped Variable "size" uses Register X18, scope (0->2)
  ## Param "descriptorIn" uses Register X8, scope (0->3)
  ## Param "descriptorIn" uses Register X8, scope (0->4)
  ## Param "value" uses Register X9, scope (0->4)
  ## Scoped Variable "addressLM" uses Register X18, scope (0->4)
  ## Scoped Variable "sizeLM" uses Register X19, scope (0->4)
  ## Scoped Variable "hasLM" uses Register X20, scope (0->4)
  ## Scoped Variable "pos_front" uses Register X21, scope (0->4)
  ## Scoped Variable "pos_end" uses Register X22, scope (0->4)
  ## Scoped Variable "sizeDRAM" uses Register X23, scope (0->4)
  ## Scoped Variable "evw" uses Register X24, scope (0->4)
  ## Scoped Variable "dramIndex" uses Register X25, scope (0->4->5)
  ## Scoped Variable "dramAddress" uses Register X26, scope (0->4->5)
  ## Param "descriptorIn" uses Register X8, scope (0->11)
  ## Scoped Variable "addressLM" uses Register X18, scope (0->11)
  ## Scoped Variable "sizeLM" uses Register X19, scope (0->11)
  ## Scoped Variable "hasLM" uses Register X20, scope (0->11)
  ## Scoped Variable "pos_front" uses Register X21, scope (0->11)
  ## Scoped Variable "pos_end" uses Register X22, scope (0->11)
  ## Scoped Variable "evw" uses Register X23, scope (0->11)
  ## Scoped Variable "spaceInLM" uses Register X25, scope (0->11)
  ## Scoped Variable "dramIndex" uses Register X26, scope (0->11)
  ## Scoped Variable "dramAddress" uses Register X27, scope (0->11->16)
  ## Param "val0" uses Register X8, scope (0->17)
  ## Param "val1" uses Register X9, scope (0->17)
  ## Param "val2" uses Register X10, scope (0->17)
  ## Param "val3" uses Register X11, scope (0->17)
  ## Param "val4" uses Register X12, scope (0->17)
  ## Param "val5" uses Register X13, scope (0->17)
  ## Param "val6" uses Register X14, scope (0->17)
  ## Param "val7" uses Register X15, scope (0->17)
  ## Scoped Variable "addressLM" uses Register X18, scope (0->17)
  ## Scoped Variable "sizeLM" uses Register X19, scope (0->17)
  ## Scoped Variable "pos_end" uses Register X20, scope (0->17)
  ## Scoped Variable "hasLM" uses Register X21, scope (0->17)
  
  ##########################################
  ###### Writing code for thread LIFO ######
  ##########################################
  # Writing code for event LIFO::initialize
  tran0 = efa.writeEvent('LIFO::initialize')
  tran0.writeAction(f"entry: add X7 X8 X18") 
  tran0.writeAction(f"movrl X9 0(X18) 0 8") 
  ## LM
  tran0.writeAction(f"add X7 X10 X20") 
  tran0.writeAction(f"movrl X20 8(X18) 0 8") 
  tran0.writeAction(f"movrl X11 16(X18) 0 8") 
  ## total size for the LM buffer in bytes, must be divisable by 64 (since we store/load 8 elements to DRAM at once)
  tran0.writeAction(f"movir X20 0") 
  tran0.writeAction(f"movrl X20 24(X18) 0 8") 
  ## pos_front
  tran0.writeAction(f"movir X20 0") 
  tran0.writeAction(f"movrl X20 32(X18) 0 8") 
  ## pos_end
  tran0.writeAction(f"movir X20 0") 
  tran0.writeAction(f"movrl X20 64(X18) 0 8") 
  ## size of occupied space in the LM in bytes
  tran0.writeAction(f"movir X20 0") 
  tran0.writeAction(f"movrl X20 80(X18) 0 8") 
  ## DRAM
  tran0.writeAction(f"movrl X12 40(X18) 0 8") 
  tran0.writeAction(f"movrl X13 48(X18) 0 8") 
  ## total size of the DRAM in bytes
  tran0.writeAction(f"movir X20 0") 
  tran0.writeAction(f"movrl X20 56(X18) 0 8") 
  ## index in the DRAM
  ## wait cont
  tran0.writeAction(f"movir X20 32767") 
  tran0.writeAction(f"sli X20 X20 16") 
  tran0.writeAction(f"ori X20 X20 65535") 
  tran0.writeAction(f"sli X20 X20 16") 
  tran0.writeAction(f"ori X20 X20 65535") 
  tran0.writeAction(f"sli X20 X20 16") 
  tran0.writeAction(f"ori X20 X20 65535") 
  tran0.writeAction(f"movrl X20 72(X18) 0 8") 
  tran0.writeAction(f"movir X19 0") 
  tran0.writeAction(f"movir X20 32767") 
  tran0.writeAction(f"sli X20 X20 16") 
  tran0.writeAction(f"ori X20 X20 65535") 
  tran0.writeAction(f"sli X20 X20 16") 
  tran0.writeAction(f"ori X20 X20 65535") 
  tran0.writeAction(f"sli X20 X20 16") 
  tran0.writeAction(f"ori X20 X20 65535") 
  tran0.writeAction(f"sendr_wcont X1 X20 X19 X19") 
  tran0.writeAction(f"yield_terminate") 
  
  # Writing code for event LIFO::getSize
  tran1 = efa.writeEvent('LIFO::getSize')
  tran1.writeAction(f"entry: add X7 X8 X17") 
  tran1.writeAction(f"movlr 80(X17) X18 0 8") 
  ## print ("size = %ld", size);
  tran1.writeAction(f"movir X19 32767") 
  tran1.writeAction(f"sli X19 X19 16") 
  tran1.writeAction(f"ori X19 X19 65535") 
  tran1.writeAction(f"sli X19 X19 16") 
  tran1.writeAction(f"ori X19 X19 65535") 
  tran1.writeAction(f"sli X19 X19 16") 
  tran1.writeAction(f"ori X19 X19 65535") 
  tran1.writeAction(f"sendr_wcont X1 X19 X18 X18") 
  tran1.writeAction(f"yield_terminate") 
  
  # Writing code for event LIFO::clear
  tran2 = efa.writeEvent('LIFO::clear')
  tran2.writeAction(f"entry: add X7 X8 X17") 
  tran2.writeAction(f"movir X19 0") 
  tran2.writeAction(f"movrl X19 24(X17) 0 8") 
  ## pos_front
  tran2.writeAction(f"movir X19 0") 
  tran2.writeAction(f"movrl X19 32(X17) 0 8") 
  ## pos_end
  tran2.writeAction(f"movir X19 0") 
  tran2.writeAction(f"movrl X19 56(X17) 0 8") 
  ## index in the DRAM
  tran2.writeAction(f"movir X18 0") 
  tran2.writeAction(f"movir X19 32767") 
  tran2.writeAction(f"sli X19 X19 16") 
  tran2.writeAction(f"ori X19 X19 65535") 
  tran2.writeAction(f"sli X19 X19 16") 
  tran2.writeAction(f"ori X19 X19 65535") 
  tran2.writeAction(f"sli X19 X19 16") 
  tran2.writeAction(f"ori X19 X19 65535") 
  tran2.writeAction(f"sendr_wcont X1 X19 X18 X18") 
  tran2.writeAction(f"yield_terminate") 
  
  # Writing code for event LIFO::push
  tran3 = efa.writeEvent('LIFO::push')
  tran3.writeAction(f"entry: add X7 X8 X17") 
  tran3.writeAction(f"movlr 80(X17) X19 0 8") 
  tran3.writeAction(f"addi X19 X20 1") 
  tran3.writeAction(f"movrl X20 80(X17) 0 8") 
  tran3.writeAction(f"movlr 8(X17) X18 0 8") 
  tran3.writeAction(f"movlr 16(X17) X19 0 8") 
  tran3.writeAction(f"movlr 64(X17) X20 0 8") 
  tran3.writeAction(f"movlr 24(X17) X21 0 8") 
  tran3.writeAction(f"movlr 32(X17) X22 0 8") 
  tran3.writeAction(f"movlr 48(X17) X23 0 8") 
  tran3.writeAction(f"evi X2 X24 LIFO::endThread 1") 
  tran3.writeAction(f"evi X24 X24 1 2") 
  tran3.writeAction(f"movir X16 1") 
  ## LIFO in the LM is full		
  tran3.writeAction(f"bneu X20 X19 __if_push_2_post") 
  tran3.writeAction(f"__if_push_0_true: movir X16 2") 
  tran3.writeAction(f"movlr 56(X17) X25 0 8") 
  tran3.writeAction(f"movlr 40(X17) X27 0 8") 
  tran3.writeAction(f"add X27 X25 X26") 
  tran3.writeAction(f"add X18 X22 X18") 
  tran3.writeAction(f"send_dmlm X26 X24 X18 8") 
  tran3.writeAction(f"addi X25 X25 64") 
  tran3.writeAction(f"bgtu X23 X25 __if_push_5_post") 
  tran3.writeAction(f"__if_push_3_true: print '[ERROR] DRAM is full.'") 
  tran3.writeAction(f"yield_terminate") 
  tran3.writeAction(f"__if_push_5_post: movrl X25 56(X17) 0 8") 
  tran3.writeAction(f"addi X22 X22 64") 
  tran3.writeAction(f"subi X20 X20 64") 
  tran3.writeAction(f"bgtu X19 X22 __if_push_8_post") 
  tran3.writeAction(f"__if_push_6_true: movir X22 0") 
  ## print("trying to store to DRAM, pos_end: %ld", pos_end);
  tran3.writeAction(f"__if_push_8_post: movrl X22 32(X17) 0 8") 
  tran3.writeAction(f"__if_push_2_post: movlr 8(X17) X25 0 8") 
  tran3.writeAction(f"add X25 X21 X18") 
  tran3.writeAction(f"movrl X9 0(X18) 0 8") 
  ## compute the next address offset
  tran3.writeAction(f"addi X21 X21 8") 
  tran3.writeAction(f"addi X20 X20 8") 
  tran3.writeAction(f"bgtu X19 X21 __if_push_11_post") 
  tran3.writeAction(f"__if_push_9_true: movir X21 0") 
  tran3.writeAction(f"__if_push_11_post: movrl X21 24(X17) 0 8") 
  tran3.writeAction(f"movrl X20 64(X17) 0 8") 
  tran3.writeAction(f"movir X25 0") 
  tran3.writeAction(f"movir X26 32767") 
  tran3.writeAction(f"sli X26 X26 16") 
  tran3.writeAction(f"ori X26 X26 65535") 
  tran3.writeAction(f"sli X26 X26 16") 
  tran3.writeAction(f"ori X26 X26 65535") 
  tran3.writeAction(f"sli X26 X26 16") 
  tran3.writeAction(f"ori X26 X26 65535") 
  tran3.writeAction(f"sendr_wcont X1 X26 X25 X25") 
  ## return to the caller
  tran3.writeAction(f"movir X25 0") 
  tran3.writeAction(f"movir X26 32767") 
  tran3.writeAction(f"sli X26 X26 16") 
  tran3.writeAction(f"ori X26 X26 65535") 
  tran3.writeAction(f"sli X26 X26 16") 
  tran3.writeAction(f"ori X26 X26 65535") 
  tran3.writeAction(f"sli X26 X26 16") 
  tran3.writeAction(f"ori X26 X26 65535") 
  tran3.writeAction(f"sendr_wcont X24 X26 X25 X25") 
  ## make sure this thread terminates (eventually after writing to DRAM)
  tran3.writeAction(f"yield") 
  
  # Writing code for event LIFO::endThread
  tran4 = efa.writeEvent('LIFO::endThread')
  tran4.writeAction(f"entry: subi X16 X16 1") 
  tran4.writeAction(f"bneiu X16 0 __if_endThread_2_post") 
  tran4.writeAction(f"__if_endThread_0_true: yield_terminate") 
  tran4.writeAction(f"__if_endThread_2_post: yield") 
  
  # Writing code for event LIFO::pop
  tran5 = efa.writeEvent('LIFO::pop')
  tran5.writeAction(f"entry: add X7 X8 X17") 
  tran5.writeAction(f"movlr 8(X17) X18 0 8") 
  tran5.writeAction(f"movlr 16(X17) X19 0 8") 
  tran5.writeAction(f"movlr 64(X17) X20 0 8") 
  tran5.writeAction(f"movlr 24(X17) X21 0 8") 
  tran5.writeAction(f"movlr 32(X17) X22 0 8") 
  tran5.writeAction(f"evi X2 X23 LIFO::endThread 1") 
  tran5.writeAction(f"evi X23 X23 1 2") 
  tran5.writeAction(f"movir X16 1") 
  ## if (NETID == 617)  {
  ## 	print("pop: pos_front: %ld, pos_end: %ld, hasLM: %ld, offset: %lu", pos_front, pos_end, sizeLM, addressLM - LMBASE);
  ## }
  tran5.writeAction(f"bneiu X21 0 __if_pop_1_false") 
  tran5.writeAction(f"__if_pop_0_true: subi X19 X21 8") 
  tran5.writeAction(f"jmp __if_pop_2_post") 
  tran5.writeAction(f"__if_pop_1_false: subi X21 X21 8") 
  tran5.writeAction(f"__if_pop_2_post: movlr 80(X17) X24 0 8") 
  tran5.writeAction(f"bneiu X24 0 __if_pop_5_post") 
  tran5.writeAction(f"__if_pop_3_true: print 'LIFO is empty.'") 
  tran5.writeAction(f"yield_terminate") 
  tran5.writeAction(f"__if_pop_5_post: bneiu X20 0 __if_pop_8_post") 
  ## TODO: need to figure this out
  tran5.writeAction(f"__if_pop_6_true: print 'LIFO is empty on LM.'") 
  tran5.writeAction(f"yield_terminate") 
  tran5.writeAction(f"__if_pop_8_post: movlr 80(X17) X25 0 8") 
  tran5.writeAction(f"subi X25 X26 1") 
  tran5.writeAction(f"movrl X26 80(X17) 0 8") 
  tran5.writeAction(f"subi X20 X20 8") 
  tran5.writeAction(f"movrl X21 24(X17) 0 8") 
  tran5.writeAction(f"movrl X20 64(X17) 0 8") 
  tran5.writeAction(f"add X18 X21 X18") 
  tran5.writeAction(f"movlr 0(X18) X24 0 8") 
  tran5.writeAction(f"movir X27 32767") 
  tran5.writeAction(f"sli X27 X27 16") 
  tran5.writeAction(f"ori X27 X27 65535") 
  tran5.writeAction(f"sli X27 X27 16") 
  tran5.writeAction(f"ori X27 X27 65535") 
  tran5.writeAction(f"sli X27 X27 16") 
  tran5.writeAction(f"ori X27 X27 65535") 
  tran5.writeAction(f"sendr_wcont X1 X27 X24 X24") 
  tran5.writeAction(f"movir X27 0") 
  tran5.writeAction(f"movir X28 32767") 
  tran5.writeAction(f"sli X28 X28 16") 
  tran5.writeAction(f"ori X28 X28 65535") 
  tran5.writeAction(f"sli X28 X28 16") 
  tran5.writeAction(f"ori X28 X28 65535") 
  tran5.writeAction(f"sli X28 X28 16") 
  tran5.writeAction(f"ori X28 X28 65535") 
  tran5.writeAction(f"sendr_wcont X23 X28 X27 X27") 
  ## if we can load 8 values into the LM from DRAM again
  tran5.writeAction(f"sub X19 X20 X25") 
  tran5.writeAction(f"movlr 56(X17) X26 0 8") 
  tran5.writeAction(f"clti X25 X27 64") 
  tran5.writeAction(f"xori X27 X27 1") 
  tran5.writeAction(f"clti X26 X28 64") 
  tran5.writeAction(f"xori X28 X28 1") 
  tran5.writeAction(f"and X27 X28 X29") 
  tran5.writeAction(f"beqiu X29 0 __if_pop_11_post") 
  tran5.writeAction(f"__if_pop_9_true: movir X16 2") 
  tran5.writeAction(f"subi X26 X26 64") 
  tran5.writeAction(f"movlr 40(X17) X28 0 8") 
  tran5.writeAction(f"add X28 X26 X27") 
  tran5.writeAction(f"evi X2 X23 LIFO::readDRAM 1") 
  tran5.writeAction(f"evi X23 X23 1 2") 
  tran5.writeAction(f"send_dmlm_ld X27 X23 8") 
  tran5.writeAction(f"movrl X26 56(X17) 0 8") 
  ## if(NETID == 617) {
  ## 	print("after pop: pos_front: %ld, pos_end: %ld, hasLM: %ld, offset: %lu", pos_front, pos_end, sizeLM, addressLM - LMBASE);
  ## }
  tran5.writeAction(f"__if_pop_11_post: yield") 
  
  # Writing code for event LIFO::readDRAM
  tran6 = efa.writeEvent('LIFO::readDRAM')
  tran6.writeAction(f"entry: movlr 8(X17) X18 0 8") 
  tran6.writeAction(f"movlr 16(X17) X19 0 8") 
  tran6.writeAction(f"movlr 32(X17) X20 0 8") 
  tran6.writeAction(f"movlr 64(X17) X21 0 8") 
  tran6.writeAction(f"bneiu X20 0 __if_readDRAM_1_false") 
  tran6.writeAction(f"__if_readDRAM_0_true: subi X19 X20 64") 
  tran6.writeAction(f"jmp __if_readDRAM_2_post") 
  tran6.writeAction(f"__if_readDRAM_1_false: subi X20 X20 64") 
  tran6.writeAction(f"__if_readDRAM_2_post: addi X21 X21 64") 
  tran6.writeAction(f"add X18 X20 X18") 
  ## if (NETID == 617) {
  ## 	print("returning from DRAM, addressLM = %lu", addressLM - LMBASE);
  ## }
  tran6.writeAction(f"bcpyoli X8 X18 8") 
  ## print ("storing %lu %d", addressLM, *addressLM);
  tran6.writeAction(f"movrl X20 32(X17) 0 8") 
  tran6.writeAction(f"movrl X21 64(X17) 0 8") 
  tran6.writeAction(f"subi X16 X16 1") 
  tran6.writeAction(f"bneiu X16 0 __if_readDRAM_5_post") 
  tran6.writeAction(f"__if_readDRAM_3_true: yield_terminate") 
  ## if(NETID == 617) {
  ## 	print("after readDRAM: pos_end: %ld, hasLM: %ld, offset: %lu", pos_end, sizeLM, addressLM - LMBASE);
  ## }
  tran6.writeAction(f"__if_readDRAM_5_post: yield") 
  