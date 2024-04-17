# README for do_all on Parallel Graph Abstruaction(PGA)

## Intro
We provide one class for running `do_all` on PGA. It offers a simple interface for executing user-specified transactions on every vertex or edge within a PGA. We also provide a test case in `updown\apps\pga_tests\linkable\pga_do_all_test.py`. The parts that follow contain information on the class `pga_do_all` and test case.

## Initialization
```
def __init__(self, 
             efa,
             task_name: str,
             do_all_desc_lm_offset: int,
             udkvmsr_meta_data_offset: int,
             send_buffer_offset: int,

             key_size: int = 1, value_size: int = 8,
             debug_flag: bool = True):
```
To initialize an instance of `pga_do_all`, we need to provide:
* `efa`: the EFAProgram used in the kernel.
* `task_name`: a string to identify the task.
* `do_all_desc_lm_offset`: the location for `do_all`'s descriptor. 40B needed.
* `udkvmsr_meta_data_offset`: the location to store the internal udkvmsr descriptor.
* `send_buffer_offset`: the location to store operands during sending.
* `key_size`: key size of the PGA.
* `value_size`: value size of the PGA.
* `debug_flag`: whethor to print debug information.

An example is:
```
pga_do_all(efa, task, do_all_desc_lm_offset= 0, udkvmsr_meta_data_offset=128, send_buffer_offset=256)
```

## Call do_all
To call `do_all_vertex` or `do_all_edge`, we need to send request with label `f'{task}::do_all_vertex_init'` or `f'{task}::do_all_edge_init'` respectively. Five operands are needed.

* X8:  Pointer to the partition array (64-bit DRAM address), This is used by UDKvmsr to store the PGA iterators. The size of it should not be less than X10 * X11 * 2 words.
* X9:  PGA descriptor offset
* X10: Number of SHT buckets per lane
* X11: Number of lanes
* X12: Label of user defined do_all transation

The X10 * X11 should be equal to the number of buckets in PGA. Two examples are:
```
addr = 'X11'
bucket_per_lane = 'X12'
num_lanes = 'X13'
send_buffer = 'X16'
label = 'X17'
ev_word = 'X18'
tmp_reg = 'X19'
tran_entry_do_all_vertex0.writeAction(f"print '[NWID %lu] => PGA ENTRY do all vertex 0: addr = %lu, bucket_per_lane = %lu, num_lanes = %lu' {'X0'} {addr} {bucket_per_lane} {num_lanes}")
tran_entry_do_all_vertex0.writeAction(f"addi {'X7'} {send_buffer} {256}")
tran_entry_do_all_vertex0.writeAction(f"movrl {addr} 0({send_buffer}) 0 8")
tran_entry_do_all_vertex0.writeAction(f"movir {tmp_reg} {584}")
tran_entry_do_all_vertex0.writeAction(f"movrl {tmp_reg} 8({send_buffer}) 0 8")
tran_entry_do_all_vertex0.writeAction(f"movrl {bucket_per_lane} 16({send_buffer}) 0 8")
tran_entry_do_all_vertex0.writeAction(f"movrl {num_lanes} 24({send_buffer}) 0 8")
tran_entry_do_all_vertex0.writeAction(f"movir {label} {0}")
tran_entry_do_all_vertex0.writeAction(f"evlb {label} {tran_entry_do_all_vertex_per_vertex.getLabel()}")
tran_entry_do_all_vertex0.writeAction(f"movrl {label} 32({send_buffer}) 0 8")
tran_entry_do_all_vertex0.writeAction(f"addi {'X2'} {ev_word} 0")
tran_entry_do_all_vertex0.writeAction(f"evlb {ev_word} {f'{task}::do_all_vertex_init'}" )
tran_entry_do_all_vertex0.writeAction(f"send_wret {ev_word} {tran_ret_top.getLabel()} {send_buffer} 5 {tmp_reg}")
tran_entry_do_all_vertex0.writeAction("yield")
```
```
addr = 'X11'
bucket_per_lane = 'X12'
num_lanes = 'X13'
send_buffer = 'X16'
label = 'X17'
ev_word = 'X18'
tmp_reg = 'X19'
tran_entry_do_all_edge0.writeAction(f"print '[NWID %lu] => PGA ENTRY do all edge 0: addr = %lu, bucket_per_lane = %lu, num_lanes = %lu' {'X0'} {addr} {bucket_per_lane} {num_lanes}")
tran_entry_do_all_edge0.writeAction(f"addi {'X7'} {send_buffer} {256}")
tran_entry_do_all_edge0.writeAction(f"movrl {addr} 0({send_buffer}) 0 8")
tran_entry_do_all_edge0.writeAction(f"movir {tmp_reg} {584}")
tran_entry_do_all_edge0.writeAction(f"movrl {tmp_reg} 8({send_buffer}) 0 8")
tran_entry_do_all_edge0.writeAction(f"movrl {bucket_per_lane} 16({send_buffer}) 0 8")
tran_entry_do_all_edge0.writeAction(f"movrl {num_lanes} 24({send_buffer}) 0 8")
tran_entry_do_all_edge0.writeAction(f"movir {label} {0}")
tran_entry_do_all_edge0.writeAction(f"evlb {label} {tran_entry_do_all_edge_per_edge.getLabel()}")
tran_entry_do_all_edge0.writeAction(f"movrl {label} 32({send_buffer}) 0 8")
tran_entry_do_all_edge0.writeAction(f"addi {'X2'} {ev_word} 0")
tran_entry_do_all_edge0.writeAction(f"evlb {ev_word} {f'{task}::do_all_edge_init'}" )
tran_entry_do_all_edge0.writeAction(f"send_wret {ev_word} {tran_ret_top.getLabel()} {send_buffer} 5 {tmp_reg}")
tran_entry_do_all_edge0.writeAction("yield")
```

## User-defined Transaction
The label of the user-defined transaction are transfered to `do_all` during Calling. `X8` will store the key for vertex (VID) or edge (EID). The continuation is already set, so a `send_reply` or some code equavalents is required at the end of the transaction. Please use `yield` instead of `yield_terminate` after `send_reply`. An example is:
```
TMP_REG0 = 'X17'
tran_entry_do_all_edge_per_edge.writeAction(f"print '[#####][NWID %lu] => PGA ENTRY do all edge per edge: X8 = %lu' {'X0'} {'X8'} ")   
tran_entry_do_all_edge_per_edge.writeAction(f"sendr_reply {TMP_REG0} {TMP_REG0} {TMP_REG0}")
tran_entry_do_all_edge_per_edge.writeAction(f"yield")
```

## Run test case
We have a test case in `updown\apps\pga_tests\linkable\pga_do_all_test.py`. Here is how to run it.
```
cd updown
source setup_env.sh

cd apps/pga_tests/linkable
make pga_do_all_test_exe 

cd ../../../udbasim/assembler
python3 efa2bin.py --efa ../../apps/pga_tests/linkable/pga_do_all_test_exe.py --outpath ../../install/updown/apps/ --toplinker

cd ../..
cmake $UPDOWN_SOURCE_CODE -DUPDOWNRT_ENABLE_TESTS=ON -DUPDOWNRT_ENABLE_UBENCH=ON -DUPDOWNRT_ENABLE_LIBRARIES=ON -DCMAKE_INSTALL_PREFIX=$UPDOWN_INSTALL_DIR -DUPDOWNRT_ENABLE_APPS=ON -DUPDOWN_ENABLE_DEBUG=OFF -DUPDOWN_ENABLE_FASTSIM=ON -DUPDOWN_ENABLE_BASIM=ON -S . -B build ; cd build ; make install ; cd ..

cd install/updown/apps
./pga_do_all_test 1 1
```
The example output is:
```
[BASIM_PRINT] 0: [NWID 0] => PGA ENTRY init 0: X8 = 2233382994504, X9 = 1
[BASIM_PRINT] 500: [NWID 0] => PGA return to top: X8 = 32, X9 = 136
[BASIM_PRINT] 800: [NWID 0] => PGA ENTRY init 1: X8 = 2233382994504, X9 = 1
[BASIM_PRINT] 1300: [NWID 0] => PGA return to top: X8 = 32, X9 = 136
[BASIM_PRINT] 1600: [NWID 0] => PGA ENTRY update vertex 0: X8 = 2233382994504, X9 = 1
[BASIM_PRINT] 2400: [NWID 0] => PGA return to top: X8 = 1, X9 = 322
[BASIM_PRINT] 2700: [NWID 0] => PGA ENTRY get vertex 0: X8 = 584, X9 = 1
[BASIM_PRINT] 3500: [NWID 0] => PGA return to top: X8 = 1, X9 = 322, X10 = 1, X11 = 2, X12 = 3
[BASIM_PRINT] 3800: [NWID 0] => PGA ENTRY update vertex 1: X8 = 2233382994504, X9 = 2
[BASIM_PRINT] 4600: [NWID 0] => PGA return to top: X8 = 2, X9 = 386
[BASIM_PRINT] 4900: [NWID 0] => PGA ENTRY get vertex 1: X8 = 584, X9 = 2
[BASIM_PRINT] 5600: [NWID 0] => PGA return to top: X8 = 2, X9 = 450, X10 = 4, X11 = 0, X12 = 5, X13 = 6
[BASIM_PRINT] 5900: [NWID 0] => PGA ENTRY update edge 0: X8 = 2233382994504, X9 = 3
[BASIM_PRINT] 6700: [NWID 0] => PGA return to top: X8 = 3, X9 = 322
[BASIM_PRINT] 27000: [NWID 0] => PGA ENTRY do all vertex 0: addr = 140063924000272, bucket_per_lane = 1, num_lanes = 1
[BASIM_PRINT] 30900: [#####][NWID 0] => PGA ENTRY do all vertex per vertex: X8 = 1
[BASIM_PRINT] 31400: [#####][NWID 0] => PGA ENTRY do all vertex per vertex: X8 = 2
[BASIM_PRINT] 32300: [NWID 0] => PGA return to top: X8 = 1, X9 = 0
[BASIM_PRINT] 47000: [NWID 0] => PGA ENTRY do all edge 0: addr = 140063924000272, bucket_per_lane = 1, num_lanes = 1
[BASIM_PRINT] 50400: [#####][NWID 0] => PGA ENTRY do all edge per edge: X8 = 3
[BASIM_PRINT] 51300: [NWID 0] => PGA return to top: X8 = 1, X9 = 0
TOP DONE.
```

## do_all on SHT
This `do_all` can also be used in SHT, as long as we use `f'{task}::do_all_vertex_init'` and send the SHT descriptor in X9. Use the descriptor for SHT whenever pga_desc required. 