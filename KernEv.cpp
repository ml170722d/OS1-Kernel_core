/*
 * KernEv.cpp
 *
 *  Created on: Aug 10, 2020
 *      Author: OS1
 */

#include "KernEv.h"
#include "consts.h"
#include "kernel.h"
#include "pcb.h"
#include  "SCHEDULE.h"
#include "IVTentry.h"

KernEv::KernEv(IVTNo _itNo):ivtNo(_itNo) {
	lock_I;

	Kernel::ivtEntrys[ivtNo]->myEv = this;
	owner = (PCB*)Kernel::running;

	unlock_I;
}

KernEv::~KernEv() {
	lock_I;

	if (owner->state == PCB::BLOCKED){
		owner->state = PCB::READY;
	}

	Kernel::ivtEntrys[ivtNo]->myEv = NULL;

	cout<<"del ev"<<endl;

	unlock_I;
}

void KernEv::signal(){
	lock_I;
	if (owner->state == PCB::BLOCKED){
		owner->state = PCB::READY;
		Scheduler::put(owner);
	}
	unlock_I;
}

void KernEv::wait(){
	lock_I;

	if (owner == Kernel::running){
		owner->state = PCB::BLOCKED;
		unlock_I;
		dispatch();
	}else{
		unlock_I;
	}
}
