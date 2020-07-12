/*
 * pcb.h
 *
 *  Created on: Jul 11, 2020
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_

#include "consts.h"
#include "linkLst.h"

class Thread;

class PCB{

public:
	enum State { READY, RUNNING, BLOCKED, TERMINATED, NEW };

	PCB();
	PCB(StackSize stackSize, Time timeSlice, Thread* myThread = NULL);
	virtual ~PCB();

	void start();
	void waitToComplete();

	_ID getId();
	static _ID getRunningId();
	static Thread* getThreadById(_ID id);


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
	_ID id;

	unsigned* stack;
	StackSize size;
	Time timeSlice;

	Thread* myThread;
	LinkedList<PCB*> waitingQueue;

	static _ID ID;

	static void wrapper();

	//tmp variable
	static volatile int fin;

};

#endif /* PCB_H_ */
