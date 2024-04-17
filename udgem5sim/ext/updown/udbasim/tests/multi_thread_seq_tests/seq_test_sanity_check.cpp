#include "simupdown.h"
#include "updown.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define NUM_THREADS 2
int main(int argc, char *argv[]){
	UpDown::ud_machine_t machine;
	machine.NumLanes = 64;
	machine.NumUDs = 1;
	machine.NumStacks = 1;
	machine.NumNodes = 1;
	machine.LocalMemAddrMode = 0;
	printf("Before creating runtime\n");

#ifdef GEM5_MODE
	UpDown::UDRuntime_t *rt = new UpDown::UDRuntime_t(machine);
#else
	char dir[100] = "efas/";
	strcat(dir, argv[1]);
	printf("%s\n", dir);
	UpDown::SimUDRuntime_t *rt = new UpDown::SimUDRuntime_t(machine,
		argv[1],
		"main", 
		"./", 
		UpDown::EmulatorLogLevel::FULL_TRACE);
#endif
	printf("After creating runtime\n");
    for(int i = 0; i < NUM_THREADS; i++){
        UpDown::networkid_t nwid(0, 0);
        UpDown::word_t ops_data[2];
        UpDown::operands_t ops(2, ops_data);
        srand((unsigned)time(NULL));
        unsigned long op0 = rand();
        unsigned long op1 = rand();

        ops.set_operand(0, op0);
        ops.set_operand(1, op1);
        printf("Thread %d: op0 = %lu, op1 = %lu\n", i, op0, op1);
        // UpDown::word_t data = 0;
        // rt->t2ud_memcpy(&data, 8, nwid,0);

        UpDown::event_t evnt_ops = UpDown::event_t(0,nwid,UpDown::CREATE_THREAD,&ops);
        rt->send_event(evnt_ops);
        rt->start_exec(nwid);
    }


	return 0;
}