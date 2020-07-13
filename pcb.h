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

#include "kernel.h"

class Thread;

class PCB{

public:
	/*
	 * different states of process
	 */
	enum State { READY, RUNNING, BLOCKED, TERMINATED, NEW };

	PCB();
	PCB(StackSize stackSize, Time timeSlice, Thread* myThread = NULL);
	virtual ~PCB();

	/*
	 * functions required to complete core of project
	 */
	void start();
	void waitToComplete();

	_ID getId();
	static _ID getRunningId();
	static Thread* getThreadById(_ID id);

	//tmp variable
	static volatile int fin;

protected:

	/*
	 * friend classes and functions
	 */
	friend void interrupt timer(...);

	//tmp friend
	friend void doSomething();
	friend class Kernel::Lock;

private:

	/*
	 * variables to store context
	 */
	unsigned bp;
	unsigned sp;
	unsigned ss;

	State state;
	_ID id;

	/*
	 * stack for this process
	 */
	unsigned* stack;
	StackSize size;

	/*
	 * processes time slice
	 */
	Time timeSlice;

	/*
	 * process wrapper class
	 */
	Thread* myThread;

	/*
	 * queue of blocked processes on this process
	 */
	LinkedList<PCB*> waitingQueue;

	/*
	 * no one needs to know about this except PCB class
	 */
	static _ID ID;
	static void wrapper();

};

#endif /* PCB_H_ */
