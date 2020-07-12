/*
 * pcb.h
 *
 *  Created on: Jul 11, 2020
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_

#include "consts.h"

class Thread;

class PCB{

public:
	enum State { READY, RUNNING, BLOCKED, TERMINATED, NEW };

	PCB();
	PCB(StackSize stackSize, Time timeSlice, Thread* myThread);


protected:

	friend void interrupt timer(...);
	friend void dispatch();
	friend void exitThread();

	//tmp friend
	friend void doSomething();

private:

	unsigned bp;
	unsigned sp;
	unsigned ss;
	State state;
	unsigned* stack;
	StackSize size;
	Time timeSlice;
	int id;

	static int ID;

	static void wrapper();

	//tmp variable
	static volatile int fin;

};

#endif /* PCB_H_ */
