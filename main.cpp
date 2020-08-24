/*
 * main.cpp
 *
 *  Created on: Jul 11, 2020
 *      Author: OS1
 */

#include "kernel.h"
#include "tests.h"

#ifdef MEMORY_LEAK_TEST
int counter = 0;

void* operator new(unsigned size) {
	void* ret = malloc(size);
	if (ret == 0)
		exit(1); //Out of mem
	counter++;
	return ret;
}

void operator delete(void* loc) {
	if (loc != 0) {
		counter--;
		free(loc);
	}
}
#endif

extern int syncPrintf(const char *format, ...);
extern int userMain(int argc, char** argv);

int main(int argc, char** argv) {

#ifdef MEMORY_LEAK_TEST
	syncPrintf("counter at the start: %d\n", counter);
#endif
	//syncPrintf("Starting system\n");

	Kernel::init();

	int val = userMain(argc, argv);

	Kernel::restore();

	//syncPrintf("System shutting down\n");

#ifdef MEMORY_LEAK_TEST
	syncPrintf("counter at the end: %d\n", counter);
#endif

	return val;
}
