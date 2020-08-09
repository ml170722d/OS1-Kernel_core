/*
 * ker_sem.h
 *
 *  Created on: Aug 6, 2020
 *      Author: OS1
 */

#ifndef KER_SEM_H_
#define KER_SEM_H_

#include "linkLst.h"

class Kernel;
class PCB;

class KernelSem {
public:

	/*
	 * thread safe
	 */
	KernelSem(unsigned int initVal);

	virtual ~KernelSem();

	int wait(int maxWait);

	int signal(int n = 0);

	int val();

private:

	friend class Kernel;
	friend void tick();

	/*
	 * not thread safe!!!
	 */
	void update();

	void blockNonTimed(PCB* p);

	void blockTmed(Time t, PCB* p);

	PCB* unblockNonTimed();

	PCB* unblockTimed();

	LinkedList<PCB*> not_timed;

	class TimeNode {
	public:

		TimeNode(Time t, PCB* p) :
			time(t), pcb(p) {
		}

		~TimeNode() {
			pcb = null;
		}

	private:

		friend class KernelSem;

		Time time;

		PCB* pcb;
	};

	LinkedList<TimeNode*> timed;

	int value;

};

#endif /* KER_SEM_H_ */
