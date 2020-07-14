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
public:
	/*
	 * class that is meant to allow for nested
	 * context switch locking
	 */
	class Lock{
	public:
		/*
		 * lock context switch
		 */
		static void CS_lock();

		/*
		 * unlock context switch
		 */
		static void CS_unlock();
		/*
		 * return false if lock is unlocked and context can be switched, otherwise true;
		 */
		static boolean isLocked();

	private:

		static PCB* owner;
		static volatile int lockCnt;
		static volatile boolean lockCond;
	};

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
	 * request for context switch
	 * it is thread safe
	 */
	static void requestCS();

	/*
	 * prints out list of all created pcbs;
	 * it is thread safe
	 */
	static void printAllPCB();

protected:

	/*
	 * allocates resources for system;
	 * it is thread safe
	 */
	static void allocateResources();

	/*
	 * frees resources occupied by system;
	 * it is thread safe
	 */
	static void freeResources();

	/*
	 * friend classes and functions
	 */
	friend class PCB;
	friend class Lock;
	friend void interrupt timer(...);

	//TODO: delete tmp friends
	friend void doSomething1();
	friend void doSomething2();

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

/*
 * synchronized context switch
 */
void dispatch();

#endif /* KERNEL_H_ */
