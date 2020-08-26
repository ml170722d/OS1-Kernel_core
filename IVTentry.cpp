/*
 * IVTentry.cpp
 *
 *  Created on: Aug 10, 2020
 *      Author: OS1
 */

#include "IVTentry.h"
#include "consts.h"
#include "kernel.h"
#include "KernEv.h"

IVTentry::IVTentry(IVTNo _entry, pInterrupt new_int):entry(_entry), myEv(NULL) {
		lock_I;
#ifndef BCC_BLOCK_IGNORE

		old_int = getvect(entry);
		setvect(entry, new_int);

#endif
		Kernel::ivtEntrys[entry] = this;
		unlock_I;
}

IVTentry::~IVTentry() {
	lock_I;
	old_int();
#ifndef BCC_BLOCK_IGNORE
	setvect(entry, old_int);
#endif
	Kernel::ivtEntrys[entry] = NULL;
	unlock_I;
}

void IVTentry::call_old() {
	old_int();
}

void IVTentry::signal_ev() {
	if (myEv != NULL) {
		myEv->signal();
	}
}
