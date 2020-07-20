/*
 * kernsem.cpp
 *
 *  Created on: Jul 18, 2020
 *      Author: OS1
 */

#include "kernsem.h"
#include "linkLst.h"
#include "kernel.h"
#include "pcb.h"
#include "SCHEDULE.h"

KernelSem::KernelSem(int initVal): semVal(initVal) {
	lock_I;
	Kernel::all_sem.add(this);
	unlock_I;
}

KernelSem::~KernelSem() {
	Kernel::Lock::CS_lock();

	signal(-1U); //-1U = 65535 (U is for unsigned); it doesn't matter the value of semaphore it will have because it is being destroyed

	Kernel::all_sem.remove(this);

	Kernel::Lock::CS_unlock();
}

int KernelSem::val() const {
	return semVal;
}

int KernelSem::signal(int permits) {
	if (permits < 0){
		return permits;
	}else{
		if (permits == 0){
			permits = 1;
		}
	}

	semVal += permits;
	int freed = 0;
	Kernel::Lock::CS_lock();
	while (permits > 0){
		PCB* p = unblok();
		if (p == null) break;

		p->state = PCB::READY;
		p->wokenBySignal = true;
		Scheduler::put(p);
		permits--;
		freed++;
	}
	Kernel::Lock::CS_unlock();
	return freed;
}

int KernelSem::wait(Time waitTime) {
	Kernel::Lock::CS_lock();
	if (semVal-- > 0){
		Kernel::Lock::CS_unlock();
		return 1;
	}
	if (waitTime == 0){
		block();
	} else {
		WaitNode* e = new WaitNode(waitTime, (PCB*)Kernel::running);
		block(e);
	}
	Kernel::Lock::CS_unlock();

	dispatch();

	Kernel::Lock::CS_lock();
	if (!Kernel::running->wokenBySignal){
		Kernel::running->wokenBySignal = false;
		Kernel::Lock::CS_unlock();
		return 0;
	}
	Kernel::Lock::CS_unlock();
	return 1;
}

void KernelSem::block(WaitNode* e) {
	lock_I;
	Kernel::running->state = PCB::BLOCKED;
	if (e == null){
		unlimitedWait.add((PCB*)Kernel::running);
		unlock_I;
		return;
	}

	int i = 0;
	for (LinkedList<WaitNode*>::Iterator it = timedWait.begin(); it != timedWait.end(); ++it){
		if ((*it)->waitTime > e->waitTime){
			(*it)->waitTime -= e->waitTime;
			break;
		}
		i++;
		e->waitTime -= (*it)->waitTime;
	}
	timedWait.putOn(i, e);
	unlock_I;
}

PCB* KernelSem::unblok() {
	PCB* ret = null;
	lock_I;
	if (unlimitedWait.getSize() > 0){
		ret = *(unlimitedWait.begin());
		unlimitedWait.remove(ret);
	} else {
		if (timedWait.getSize() > 0) {
			WaitNode* e = *(timedWait.begin());
			timedWait.remove(e);
			ret = e->data;
		}
	}
	unlock_I;
	return ret;
}

void KernelSem::update(){
	lock_I;
	for (LinkedList<WaitNode*>::Iterator it = timedWait.begin(); it != timedWait.end(); ++it){
		//syncPrintf("sem update; time left: %d\n", (*it)->waitTime);
		(*it)->waitTime--;
		if ((*it)->waitTime > 0) break;


		//syncPrintf("putting in sch\n");
		PCB* p = (*it)->data;
		timedWait.remove(*it);
		p->state = PCB::READY;
		p->wokenBySignal = false;
		Scheduler::put(p);
	}
	unlock_I;
	//syncPrintf("fin updating sem\n");
}
