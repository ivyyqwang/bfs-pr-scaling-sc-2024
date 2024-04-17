#include "simupdown.h"
#include "updown.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>

using namespace UpDown;
int main(int argc, char* argv[], char* envp[]){

    // read the args
    int num_lanes = atoi(argv[1]);
    int num_threads_per_lane = atoi(argv[2]);
    // int num_elems_per_thread = atoi(argv[3]);
    // updowns
    UpDown::ud_machine_t machine;
    machine.NumLanes = num_lanes;
    machine.NumUDs = 1;
    machine.NumStacks = 1;
    machine.NumNodes = 1;
    machine.LocalMemAddrMode = 1;


    char dir[100] = "efas/";
	strcat(dir,"fork_join");
	printf("%s\n", dir);
    UpDown::SimUDRuntime_t *rt = new UpDown::SimUDRuntime_t(machine,
        "fork_join",
        "fork_join", 
        "./", 
        UpDown::EmulatorLogLevel::NONE);
    // return 0;
    srand((unsigned)time(NULL));
    // first allocate space for the vars, it is one d array. each thread has a chunk of it
    word_t* data = reinterpret_cast<word_t*>(malloc(sizeof(word_t) * num_lanes * num_threads_per_lane));
    // prepare random data
    for(int i = 0; i < num_lanes * num_threads_per_lane; i++){
        data[i] = rand() % 1000;
    }
    word_t expected_val = 0;
    for(int i = 0; i < num_lanes * num_threads_per_lane; i++){
        word_t temp = data[i];
        word_t temp0 = temp;
        temp += 127;
        temp -= 64;
        temp *= 3;
        temp /= 3;
        temp0 = (word_t)temp;
        temp += temp;
        temp += temp;
        temp += temp;
        temp = temp - temp0;
        // printf("temp[%d]: %lu\n",i, temp);
        expected_val += temp;
    }
    printf("expected val: %lu\n", expected_val);
    // expected value
    // prepare the ops
    word_t offset = 8;
    UpDown::operands_t ops(4);
    ops.set_operand(0, (word_t) offset);
    ops.set_operand(1, (word_t) num_lanes);
    ops.set_operand(2, (word_t) num_threads_per_lane);
    ops.set_operand(3, (word_t) num_lanes * num_threads_per_lane);
    // write the values to their onw SPs
    for(int i = 0; i < num_lanes; i++){
        word_t vzero = 0;
        rt->t2ud_memcpy(&vzero, sizeof(UpDown::word_t), UpDown::networkid_t(i, 0), 0);
        for(int j = 0; j < num_threads_per_lane; j++){
            // prepare the event
            UpDown::networkid_t nwid(i, 0);
            // write the data
            rt->t2ud_memcpy(&data[i * num_threads_per_lane + j], sizeof(UpDown::word_t), nwid, offset + j * sizeof(UpDown::word_t));
            // printf("writing %lu to %lu\n", data[i * num_threads_per_lane + j], offset + j * sizeof(UpDown::word_t));
        }
    }

    // prepare the event
    UpDown::event_t evnt_ops = UpDown::event_t(0,UpDown::networkid_t(0),UpDown::CREATE_THREAD,&ops);
    rt->send_event(evnt_ops);
    rt->start_exec(UpDown::networkid_t(0));
    printf("Expecting results to be = %ld\n", expected_val);
    rt->test_wait_addr(UpDown::networkid_t(0), 0, expected_val);

}
