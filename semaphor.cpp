/*
 * semaphor.cpp
 *
 *  Created on: Aug 6, 2020
 *      Author: OS1
 */

#include "semaphor.h"
#include "ker_sem.h"

Semaphor::Semaphor(int init) :
		myImpl(new KernelSem(init)) {
}

Semaphor::~Semaphor() {
	delete myImpl;
}

int Semaphor::signal(int n) {
	return myImpl->signal(n);
}

int Semaphor::wait(Time maxWait) {
	return myImpl->wait(maxWait);
}

int Semaphor::val() {
	return myImpl->val();
}
