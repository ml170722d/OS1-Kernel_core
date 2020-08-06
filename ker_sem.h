/*
 * ker_sem.h
 *
 *  Created on: Aug 6, 2020
 *      Author: OS1
 */

#ifndef KER_SEM_H_
#define KER_SEM_H_

#include  "kernel.h"
#include "linkLst.h"

class PCB;

class KernelSem {
public:

	KernelSem(unsigned int initVal);

	virtual ~KernelSem();

	int wait(int maxWait);

	int signal(int n = 0);

	int val();

	void update();

private:

	void blockNonTimed(PCB* p);

	void blockTmed(Time t, PCB* p);

	PCB* unblockNonTimed();

	PCB* unblockTimed();

	LinkedList<PCB*> not_timed;

	class TimeNode{
	public:

		TimeNode(Time t, PCB* p);

		~TimeNode();

	private:

		friend class KernelSem;

		Time time;

		PCB* pcb;
	};

	LinkedList<TimeNode*> timed;

	unsigned int value;

};

#endif /* KER_SEM_H_ */
