/*
 * event.cpp
 *
 *  Created on: Aug 10, 2020
 *      Author: OS1
 */

#include "event.h"
#include "consts.h"
#include "KernEv.h"

Event::Event(IVTNo ivtNo):myImpl(new KernEv(ivtNo)) {
}

Event::~Event() {
	delete myImpl;
}

void Event::wait(){
	myImpl->wait();
}

void Event::signal(){
	myImpl->signal();
}
