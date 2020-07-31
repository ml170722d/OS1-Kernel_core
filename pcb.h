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
	/*
	 * different states of process
	 */
	enum State { READY, RUNNING, BLOCKED, TERMINATED, NEW };

	PCB();
	PCB(StackSize stackSize, Time timeSlice, Thread* myThread = NULL);
	virtual ~PCB();

	/*
	 * functions needed for project
	 */
	void start();
	void waitToComplete();

	_ID getId();
	static _ID getRunningId();
	static Thread* getThreadById(_ID id);

	//tmp variable
	//static volatile int fin;

protected:

	friend void interrupt timer(...);
	friend void dispatch();
	friend class KernelSem;

private:

	/*
	 * variables to save context
	 */
	unsigned bp;
	unsigned sp;
	unsigned ss;


	State state;
	_ID id;
	Time timeSlice;

	/*
	 * stack of process
	 */
	Word* stack;
	StackSize size;

	/*
	 * wrapper of class PCB
	 */
	Thread* myThread;

	/*
	 * queue for all processes waiting on this process to finish
	 */
	LinkedList<PCB*> waitingQueue;

	/*
	 * no one need to know about this except PCB class
	 */
	static _ID ID;
	static void wrapper();

	/*
	 * flag for waking up
	 */
	boolean wokenBySignal;

};

#endif /* PCB_H_ */
