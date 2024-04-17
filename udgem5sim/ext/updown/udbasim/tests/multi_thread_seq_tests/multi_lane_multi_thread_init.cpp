#include "simupdown.h"
#include "updown.h"

int main(int argc, char *argv[]){
    if (argc < 3){
        printf("multi_lane_multi_thread_init_fastsim [NUM_LANES > 1] [NUM_THREADS > 1]\n");
        return 1;
    }

    int num_lanes = atoi(argv[1]);
    int num_threads = atoi(argv[2]);

    if (num_threads < 1 || num_lanes < 1){
        printf("multi_lane_multi_thread_init_fastsim [NUM_LANES > 1] [NUM_THREADS > 1]\n");
    }

	UpDown::ud_machine_t machine;
	machine.NumLanes = num_lanes;
	machine.NumUDs = 1;
	machine.NumStacks = 1;
	machine.NumNodes = 1;
	machine.LocalMemAddrMode = 1;

#ifdef GEM5_MODE
	UpDown::UDRuntime_t *rt = new UpDown::UDRuntime_t(machine);
#else
	char dir[100] = "efas/";
	strcat(dir, "single_lane_multi_thread_init");
	printf("%s\n", dir);
	UpDown::SimUDRuntime_t *rt = new UpDown::SimUDRuntime_t(machine,
		"single_lane_multi_thread_init",
		"single_lane_multi_thread_init", 
		"./",
		UpDown::EmulatorLogLevel::FULL_TRACE);
#endif
	UpDown::word_t ops_data[2];
	UpDown::operands_t ops(2, ops_data);
	ops.set_operand(0, num_threads);
	ops.set_operand(1, rand());

	UpDown::networkid_t *nwid = new UpDown::networkid_t[num_lanes];
	UpDown::word_t *data = new UpDown::word_t[num_lanes];
    for(int i = 0; i < num_lanes; i++){
        nwid[i] = UpDown::networkid_t(i, 0);
	    data[i] = 0;
		rt->t2ud_memcpy(&data[i],sizeof(UpDown::word_t),nwid[i],0);

        UpDown::event_t evnt_ops = UpDown::event_t(0,nwid[i],UpDown::CREATE_THREAD,&ops);
	    rt->send_event(evnt_ops);
        printf("starting execution of lane %d",i);
	    rt->start_exec(nwid[i]);
    }

    uint32_t expected_val = 1;
	for (int i = 0; i < num_lanes; i++){
		printf("lane %d data %lu",nwid[i].get_LaneId(),data[i]);
		if (!rt->test_addr(nwid[i],0,expected_val)){
			printf("TEST FAILED\n");
			return 1;
		}
	}
   
	printf("TEST PASSED\n");
	return 0;
}
