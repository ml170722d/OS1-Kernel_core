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

#include "linkLst.h"

extern int syncPrintf(const char *format, ...);
extern int userMain(int argc, char** argv);

int main(int argc, char** argv) {


	syncPrintf("Starting system\n");

	Kernel::init();

	userMain(argc, argv);

	Kernel::restore();

	syncPrintf("System shutting down");


	//tests_for_linkedList();

	return 0;

}
