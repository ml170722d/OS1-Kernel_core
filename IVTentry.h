/*
 * IVTentry.h
 *
 *  Created on: Aug 10, 2020
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_

#include "consts.h"

class KernEv;

class IVTentry {
public:
	IVTentry(IVTNo _entry, pInterrupt new_int);
	virtual ~IVTentry();

	void call_old();
	void signal_ev();

private:
	friend class KernEv;
	pInterrupt old_int;
	IVTNo entry;
	KernEv* myEv;

};

#endif /* IVTENTRY_H_ */
