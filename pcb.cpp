/*
 * pcb.cpp
 *
 *  Created on: Jul 11, 2020
 *      Author: OS1
 */

#include "pcb.h"
#include "thread.h"
#include "consts.h"

#include "kernel.h"

#include "SCHEDULE.h"

int PCB::ID=0;

PCB::PCB(): state(PCB::NEW), timeSlice(DEFAULT_TIME_SLICE), id(ID++), size(0), stack(0), sp(0), ss(0), bp(0), myThread(NULL), wokenBySignal(false) {
	lock_I;

	Kernel::all_pcb.add(this);

	unlock_I;
}

PCB::PCB(StackSize stackSize, Time _timeSlice, Thread* _myThread): state(PCB::NEW), size(stackSize),
		timeSlice(_timeSlice), myThread(_myThread), id(ID++), sp(0), ss(0), bp(0), wokenBySignal(false) {
		lock_I;

		stack = new unsigned [stackSize];
		stack[stackSize-1] = 0x200;

#ifndef BCC_BLOCK_IGNORE
		stack[stackSize-2] = FP_SEG(PCB::wrapper);
		stack[stackSize-3] = FP_OFF(PCB::wrapper);

		sp = FP_OFF(stack + size - 12);
		ss = FP_SEG(stack + size - 12);
		bp = FP_OFF(stack + size - 12);
#endif

		Kernel::all_pcb.add(this);
		unlock_I;
}

PCB::~PCB(){
	this->waitToComplete();
	lock_I;
	delete stack;
	//cout<<"del pcb id: "<<this->id<<endl;
	Kernel::all_pcb.remove(this);
	unlock_I;
}

//volatile int PCB::fin = 0;
const int M = 20;

void PCB::wrapper(){

	//TODO: needs to call thread->run() to complete PCB class completely
	/*
	for (int i =0; i < M; ++i) {

		if(Kernel::CS_req)
			dispatch();
		for (int k = 0; k<10000; ++k)
			for (int j = 0; j <30000; ++j);
	}

	PCB::fin++;
	*/

	Kernel::running->myThread->run();

	Kernel::Lock::CS_lock();
	//cout<<"----------fin"<<" my id: "<<Kernel::running->id<<endl;
	Kernel::Lock::CS_unlock();

	lock_I;
	LinkedList<PCB*>::Iterator it;

	Kernel::running->state = PCB::TERMINATED;

	for (it = ((PCB*)Kernel::running)->waitingQueue.begin(); it != ((PCB*)Kernel::running)->waitingQueue.end(); ++it){
		(*it)->state = PCB::READY;
		Scheduler::put((PCB*)(*it));
	}
	unlock_I;
	//cout<<"i call disp"<<endl;
	dispatch();
}

void PCB::start(){
	lock_I;
	//cout<<"start id: "<<id<<endl;
	if (this->state == PCB::NEW){
		this->state = PCB::READY;
		Scheduler::put((PCB*)this);
	}
	unlock_I;
}

void PCB::waitToComplete(){
	lock_I;
	//cout<<PCB::getRunningId()<<" called waitToComplete on "<<id<<endl;

	if (this == Kernel::running){
		//cout<<PCB::getRunningId()<<" called waitToComplete on "<<id<<" -> can't wait on itself"<<endl;
		unlock_I;
		return;
	}

	if ((Kernel::running->id == Kernel::idle_thread->getId()) || (this->id == Kernel::idle_thread->getId())){
		//cout<<"can't wait on idle"<<endl;
		unlock_I;
		return;
	}

	if (this->state != PCB::TERMINATED){
		Kernel::running->state = PCB::BLOCKED;
		this->waitingQueue.add((PCB*)Kernel::running);
		//cout<<PCB::getRunningId()<<" now waiting on "<<id<<endl;
		unlock_I;
		dispatch();
		lock_I;
		//cout<<PCB::getRunningId()<<" finished waitToComplete on "<<id<<endl;
		unlock_I;
		return;
	}

	//cout<<PCB::getRunningId()<<" called waitToComplete on "<<id<<", but it is already terminated"<<endl;

	unlock_I;
}

_ID PCB::getId(){
	return this->id;
}

_ID PCB::getRunningId(){
	return Kernel::running->id;
}

Thread* PCB::getThreadById(_ID id){
	Kernel::Lock::CS_lock();
	for (LinkedList<PCB*>::Iterator it = Kernel::all_pcb.begin(); it != Kernel::all_pcb.end(); ++it){
		if ((*it)->id == id){
			Kernel::Lock::CS_unlock();
			return (*it)->myThread;
		}
	}
	Kernel::Lock::CS_unlock();
	return NULL;
}
