/*
 * main.cpp
 *
 *  Created on: Jul 11, 2020
 *      Author: OS1
 */

#include <STDLIB.H>

#include "kernel.h"

extern int syncPrintf(const char *format, ...);
extern int userMain(int argc, char** argv);

/*
int counter = 0;

void* operator new(unsigned size) {
  void* ret = malloc(size);
  if(ret==0)
    exit(1);//Out of mem
  counter++;
  return ret;
}

void operator delete(void* loc) {
  if(loc != 0){
    counter--;
    free(loc);
  }
}
*/

int main(int argc, char** argv) {

	//cout<<endl<<endl<<counter<<endl<<endl;

	syncPrintf("Starting system\n");

	Kernel::init();

	userMain(argc, argv);

	Kernel::restore();

	syncPrintf("System shutting down\n");

	//cout<<endl<<endl<<counter<<endl<<endl;

	//Kernel::printAllPCBandSEM();

	return 0;
}
