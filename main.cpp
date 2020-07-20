/*
 * main.cpp
 *
 *  Created on: Jul 11, 2020
 *      Author: OS1
 */

#include "SCHEDULE.H"
#include "thread.h"
#include "kernel.h"

#include "consts.h"

extern int syncPrintf(const char *format, ...);
extern int userMain(int argc, char** argv);

void doSomething3(){
	userMain(0, NULL);
}

int main(int argc, char** argv) {

	syncPrintf("Starting system\n");

	Kernel::init();

	int val = userMain(argc, argv);

	//syncPrintf("userMain return value: %d\n", val);

	Kernel::restore();

	syncPrintf("System shutting down");
	return 0;

}
