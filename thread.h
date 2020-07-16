/*
 * thread.h
 *
 *  Created on: Jul 14, 2020
 *      Author: OS1
 */

#ifndef THREAD_H_
#define THREAD_H_

#include "consts.h"

class PCB;

class Thread {
public:

	void start();
	void waitToComplete();
	virtual ~Thread();

	_ID getId();
	static _ID getRunningId();
	static Thread* getThreadById(_ID id);

protected:

	friend class PCB;
	Thread(StackSize ss = DEFAULT_STACK_SIZE, Time ts = DEFAULT_TIME_SLICE);
	virtual void run() {}

private:

	PCB* myPCB;

};

void dispatch();

#endif /* THREAD_H_ */
