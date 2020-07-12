/*
 * pcb.cpp
 *
 *  Created on: Jul 11, 2020
 *      Author: OS1
 */

#include "pcb.h"
#include "consts.h"

#include "kernel.h"

#include "SCHEDULE.h"

int PCB::ID=0;

PCB::PCB(): state(PCB::NEW), timeSlice(DEFAILT_TIME_SLICE), id(ID++), size(0), stack(0), sp(0), ss(0), bp(0), myThread(NULL) {
	lock_I;

	Kernel::all_pcb.add(this);

	unlock_I;
}

PCB::PCB(StackSize stackSize, Time _timeSlice, Thread* _myThread): state(PCB::NEW), size(stackSize),
		timeSlice(_timeSlice), myThread(_myThread), id(ID++), sp(0), ss(0), bp(0) {
		asm cli;

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
		asm sti;
}

PCB::~PCB(){
	this->waitToComplete();
	lock_I;
	delete stack;
	//cout<<"del pcb id: "<<this->id<<endl;
	unlock_I;
}

volatile int PCB::fin = 0;
const int M = 20;

void PCB::wrapper(){
	for (int i =0; i < M; ++i) {
		Kernel::Lock::CS_lock();
		//cout<<"funkcija_"<<Kernel::running->id<<" "<<i<<endl;
		Kernel::Lock::CS_unlock();
		if(Kernel::CS_req)
			dispatch();
		for (int k = 0; k<10000; ++k)
			for (int j = 0; j <30000; ++j);
	}

	PCB::fin++;

	Kernel::Lock::CS_lock();
	cout<<"----------fin: "<<PCB::fin<<", my id: "<<Kernel::running->id<<endl;
	Kernel::Lock::CS_unlock();

	//TODO: more improvements needed
	lock_I;
	LinkedList<PCB*>::Iterator it(NULL);

	Kernel::running->state = PCB::TERMINATED;

	//((PCB*)Kernel::running)->waitingQueue.printList();

	for (it = ((PCB*)Kernel::running)->waitingQueue.begin(); it != ((PCB*)Kernel::running)->waitingQueue.end(); ++it){
		(*it)->state = PCB::READY;
		Scheduler::put((PCB*)(*it));
	}
	unlock_I;
	//cout<<"i call disp"<<endl;
	dispatch();
}

void PCB::start(){
	//TODO: implement
	lock_I;
	//cout<<"start id: "<<id<<endl;
	if (this->state == PCB::NEW){
		this->state = PCB::READY;
		Scheduler::put((PCB*)this);
	}
	unlock_I;
}

void PCB::waitToComplete(){
	//TODO: implement
	lock_I;
	//cout<<"waitToComplete on "<<id<<endl;

	if (this == Kernel::running){
		unlock_I;
		return;
	}

	if (this->state != PCB::TERMINATED){
		Kernel::running->state = PCB::BLOCKED;
		this->waitingQueue.add((PCB*)Kernel::running);
		unlock_I;
		dispatch();
		return;
	}

	unlock_I;
}

_ID PCB::getId(){
	return this->id;
}

_ID PCB::getRunningId(){
	return Kernel::running->id;
}

Thread* PCB::getThreadById(_ID id){
	//TODO: implement
	return NULL;
}
