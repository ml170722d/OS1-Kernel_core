/*
 * thread.cpp
 *
 *  Created on: Jul 14, 2020
 *      Author: OS1
 */

#include "thread.h"

#include "consts.h"
#include "pcb.h"

Thread::Thread(StackSize ss, Time ts): myPCB(new PCB(ss, ts, this)) {
}


Thread::~Thread() {
	waitToComplete();
	delete myPCB;
}

void Thread::waitToComplete(){
	myPCB->waitToComplete();
}

void Thread::start(){
	myPCB->start();
}

_ID Thread::getId(){
	return myPCB->getId();
}

_ID Thread::getRunningId(){
	return PCB::getRunningId();
}

Thread* Thread::getThreadById(_ID id){
	return PCB::getThreadById(id);
}

