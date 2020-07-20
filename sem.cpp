/*
 * sem.cpp
 *
 *  Created on: Jul 20, 2020
 *      Author: OS1
 */

#include "sem.h"
#include "consts.h"
#include "kernsem.h"

Semaphore::Semaphore(int init): myImpl(new KernelSem(init)) {
}

Semaphore::~Semaphore() {
	delete myImpl;
}

int Semaphore::signal(int permits){
	return myImpl->signal();
}

int Semaphore::wait(Time waitTime){
	//syncPrintf("wait\n");
	return myImpl->wait(waitTime);
}

int Semaphore::val() const {
	return myImpl->val();
}
