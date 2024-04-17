#include "simupdown.h"
#include "updown.h"

int main(int argc, char *argv[]){
	UpDown::ud_machine_t machine;
	machine.NumLanes = 2;
	machine.NumUDs = 1;
	machine.NumStacks = 1;
	machine.NumNodes = 1;
	machine.LocalMemAddrMode = 0;

#ifdef GEM5_MODE
	UpDown::UDRuntime_t *rt = new UpDown::UDRuntime_t(machine);
#else
	char dir[100] = "efas/";
	strcat(dir, "atomic_lock");
	printf("%s\n", dir);
	UpDown::SimUDRuntime_t *rt = new UpDown::SimUDRuntime_t(machine,
		"atomic_lock",
		"atomic_lock", 
		"./",
		UpDown::EmulatorLogLevel::FULL_TRACE);
#endif
	UpDown::networkid_t nwid0 = UpDown::networkid_t(0,0);
	UpDown::networkid_t nwid1 = UpDown::networkid_t(1,0);

	UpDown::word_t ops_data[2];
	UpDown::operands_t ops(2, ops_data);
	ops.set_operand(0, rand());
	ops.set_operand(1, rand());
	UpDown::event_t evnt_ops0 = UpDown::event_t(0,nwid0,UpDown::CREATE_THREAD,&ops);
	UpDown::event_t evnt_ops1 = UpDown::event_t(0,nwid1,UpDown::CREATE_THREAD,&ops);
	rt->send_event(evnt_ops0);
	rt->send_event(evnt_ops1);

	
	UpDown::word_t data[] = {0,0,0};
	rt->t2ud_memcpy(&data,sizeof(UpDown::word_t)*3,nwid0,0);

	rt->start_exec(nwid1);
	rt->start_exec(nwid0);
	

    uint32_t expected_val = 1;
	if (!rt->test_addr(nwid1,0,expected_val)){
		printf("TEST FAILED\n");
		return 1;
	}
   
	printf("TEST PASSED\n");
	return 0;
}
