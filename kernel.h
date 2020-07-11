/*
 * kernel.h
 *
 *  Created on: Jul 1, 2020
 *      Author: OS1
 */

#ifndef KERNEL_H_
#define KERNEL_H_

#include "consts.h"
#include "linkLst.h"

class PCB;

/*
 * new timer routine declaration
 */
void interrupt timer(...);

class Kernel {
private:
	/*
	 * class that is meant to allow for nested
	 * context switch locking
	 */
	class Lock{
	public:
		static void CS_lock();
		static void CS_unlock();
		static boolean isLocked();
	private:
		static PCB* owner;
		static volatile int lockCnt;
		static volatile boolean lockCond; //false -> unlocked, true -> locked
	};
public:

	/*
	 * initialize system
	 */
	static void init();

	/*
	 * restore all resource changes by init
	 */
	static void restore();

	/*
	 * get running process
	 */
	static PCB* getRunning();

	/*
	 * context switch lock
	 */
	static volatile Lock CSLock;

	/*
	 * request for context switch
	 */
	static void requestCS();

protected:

	/*
	 * allocates resources for system
	 */
	static void allocateResources();

	/*
	 * frees resources occupied by system
	 */
	static void freeResources();

	friend class PCB;
	friend class Lock;
	friend void interrupt timer(...);

	//TODO: delete temp friend functions and classes
	friend void f();

private:

	/*
	 * variable for signaling context switch request
	 */
	static volatile boolean CS_req;

	/*
	 * context switch counter
	 */
	static volatile int csCnt;

	/*
	 * running process
	 */
	static volatile PCB* running;

	/*
	 * main process
	 */
	static PCB* main_pcb;

	/*
	 * list of all created PCBs
	 */
	static LinkedList<PCB*> all_pcb;

};

void dispatch();

#endif /* KERNEL_H_ */
