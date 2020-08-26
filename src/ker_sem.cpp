/*
 * ker_sem.cpp
 *
 *  Created on: Aug 6, 2020
 *      Author: OS1
 */

#include "ker_sem.h"
#include "kernel.h"
#include "pcb.h"

#include "consts.h"
#include "SCHEDULE.h"

KernelSem::KernelSem(unsigned int init) : value(init), not_timed(), timed() {
	lock_I;

	Kernel::all_sem.push_back(this);

	unlock_I;
}

KernelSem::~KernelSem() {
	//TODO
	this->signal(val() * -1);

	lock_I;

	Kernel::all_sem.remove(this);

	unlock_I;
}

void KernelSem::blockNonTimed(PCB* p) {

	if (p->getId() == Kernel::idle_thread->getId()) return;

	p->state = PCB::BLOCKED;
	not_timed.push_back(p);
}

void KernelSem::blockTmed(Time t, PCB* p) {

	if (p->getId() == Kernel::idle_thread->getId()) return;

	p->state = PCB::BLOCKED;
	TimeNode* _new = new TimeNode(t, p);

	for (LinkedList<TimeNode*>::Iterator it = timed.begin(); it != timed.end(); it++) {
		if (_new->time >= (*it)->time) {
			_new->time -= (*it)->time;
		}
		else {
			(*it)->time -= _new->time;
			timed.insert_before(it, _new);
			return;
		}
	}

	timed.push_back(_new);

}

int KernelSem::wait(int maxWait) {
	lock_I;

	//cout<<"call wait : sem value = "<<value<<endl;

	if (value > 0) {
		value--;
		unlock_I;
		return 1; //success in taking semaphore
	}

	//cout<<"blocked"<<endl;
	value--;
	//semaphore taken; need to block running process on this semaphore and dispatch
	if (maxWait == 0) {
		blockNonTimed((PCB*)Kernel::running);//unlimited wait queue
	}
	else {
		blockTmed(maxWait, (PCB*)Kernel::running);//limited wait queue
	}

	//cout<<"call disp\n";

	unlock_I;

	dispatch();

	//TODO: add if for time woken up processes
	lock_I;

	if (Kernel::running->end_of_wait_time == true){
		Kernel::running->end_of_wait_time = false;
		unlock_I;
		return 0;
	}

	unlock_I;

	//syncPrintf("fin wait");

	return 1;//only non timed processes are tested now
}

PCB* KernelSem::unblockNonTimed() {
	//TODO
	LinkedList<PCB*>::Iterator it = not_timed.begin();


	if (it.isNull())
		return null;//not_timed queue was empty

	PCB* p = *it;

	not_timed.remove(*it);//remove and delete node from list, but not data in node (PCB*)

	p->state = PCB::READY;
	return p;
}

PCB* KernelSem::unblockTimed() {
	LinkedList<TimeNode*>::Iterator it = timed.begin();

	if (it.isNull())
		return null;//timed queue was empty

	TimeNode* tn = *it;//get list node data

	PCB* p = tn->pcb;//get PCB from time node
	timed.remove(*it);//remove and delete node from list, but not data in node (TimeNode*)

	it = timed.begin();//get new first node
	if (!it.isNull())
		(*it)->time += tn->time;//add wait time that was left on previous first node to new first node
	delete tn;//free memory of TimeNode

	p->state = PCB::READY;
	return p;
}

int KernelSem::signal(int n) {
	lock_I;

	//cout<<"call signal : sem value = "<<value<<endl;

	if (n < 0) {
		unlock_I;
		return n;
	}

	if (n == 0) {
		value++;
		if ((timed.isEmpty() == true) && (not_timed.isEmpty() == true)) {
			//cout<<endl<<"queues are empty"<<endl;
			unlock_I;
			return 0;
		}

		PCB* p = unblockNonTimed();
		if (p == null) {
			p = unblockTimed();
			if (p == null) {
				//double check for safety reasons
				//cout<<endl<<"queues are empty"<<endl;
				unlock_I;
				return 0;
			}
		}
		Scheduler::put(p);
		unlock_I;

		return 0;//by project definition
	}

	int ret = 0;

	while (n > 0) {
		if ((timed.isEmpty() == true) && (not_timed.isEmpty() == true)) {
			//cout<<endl<<"queues empty"<<endl;
			break;
		}

		unlock_I;
		this->signal(0);
		lock_I;

		ret++;
		n--;
	}

	value += n - ret;

	unlock_I;
	return ret;
}


void KernelSem::update() {
	//lock_I;

	//cout<<"updated sem\n";

	LinkedList<TimeNode*>::Iterator it = timed.begin();

	//timed.printList();

	if (!it.isNull()) {

		(*it)->time--;
		//cout<<"id: "<< (*it)->pcb->getId() <<" time = "<<(*it)->time<<endl;

		while ((*it)->time <= 0) {
			//cout<<"time to wake up " << (*it)->pcb->getId()<<endl;
			TimeNode* tn = *it;
			it++;
			PCB* p = tn->pcb;
			timed.remove(tn);
			delete tn;

			p->state = PCB::READY;
			Scheduler::put(p);

			//TODO: set flag for time awake
			p->end_of_wait_time = true;
			value++;

			if (it.isNull())
				break;
		}
	}

	//unlock_I;
}

int KernelSem::val() {
	return value;
}
