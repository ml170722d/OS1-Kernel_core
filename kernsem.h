/*
 * kernsem.h
 *
 *  Created on: Jul 18, 2020
 *      Author: OS1
 */

#ifndef KERNSEM_H_
#define KERNSEM_H_

#include "linkLst.h"
#include "consts.h"

class PCB;

class KernelSem {
private:

	struct WaitNode {
		WaitNode(Time wt, PCB* d) :
				waitTime(wt), data(d) {
		}
		Time waitTime;
		PCB* data;
	};

public:

	/*
	 * standard methods of semaphores
	 */
	KernelSem(int permits);
	virtual ~KernelSem();
	int signal(int permits = 0);
	int wait(Time waitTime);
	int val() const;

protected:

	/*
	 * logic for blocking and unblocking processes
	 */
	void block(WaitNode* e = null);
	PCB* unblok();

	friend class Kernel;

private:

	/*
	 * update waiting queue
	 */
	void update();

	/*
	 * waiting queue
	 */
	LinkedList<WaitNode*> timedWait;
	LinkedList<PCB*> unlimitedWait;

	/*
	 * value of semaphore
	 */
	int semVal;
};

#endif /* KERNSEM_H_ */
