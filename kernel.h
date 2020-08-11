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
#include "thread.h"

extern int kern_mutex_glb;
void kern_mutex_glb_wait();

#define kIntLock kern_mutex_glb_wait();
#define kIntUnlock kern_mutex_glb = 1;

#define NUMBER_OF_IVT_ENTRIES 256

class PCB;
class KernelSem;
class IVTentry;
class KernEv;

/*
 * new timer routine declaration
 */
void interrupt timer(...);

extern void tick();

class Kernel {
public:
	/*
	 * class that is meant to allow for nested
	 * context switch locking
	 */
	class Lock {
	public:
		static void CS_lock();
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
	static void printAllPCBandSEM();

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

	friend class PCB;
	friend class Lock;
	friend void interrupt timer(...);
	//friend class Thread;
	friend void tick();
	friend class IVTentry;

	friend class KernelSem;
	friend class KernEv;

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

	/*
	 * list of all created PCBs
	 */
	static LinkedList<KernelSem*> all_sem;

	/*
	 *
	 */
	static IVTentry *ivtEntrys[NUMBER_OF_IVT_ENTRIES];

	class Idle: public Thread {
	public:
		Idle();
		~Idle();
	protected:
		virtual void run();
		friend class Kernel;
	private:
		boolean is_active;
	};

	static Idle* idle_thread;

	static void update();

};

void dispatch();

#endif /* KERNEL_H_ */
