/*
 * semaphor.cpp
 *
 *  Created on: Aug 6, 2020
 *      Author: OS1
 */

#include "semaphor.h"
#include "ker_sem.h"

Semaphore::Semaphore(int init) :
		myImpl(new KernelSem(init)) {
}

Semaphore::~Semaphore() {
	delete myImpl;
}

int Semaphore::signal(int n) {
	return myImpl->signal(n);
}

int Semaphore::wait(Time maxWait) {
	return myImpl->wait(maxWait);
}

int Semaphore::val() {
	return myImpl->val();
}
