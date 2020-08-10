/*
 * event.h
 *
 *  Created on: Aug 10, 2020
 *      Author: OS1
 */

#ifndef EVENT_H_
#define EVENT_H_

#include "consts.h"
#include "IVTentry.h"

class KernEv;

class Event {
public:
	Event(IVTNo ivtNo);
	virtual ~Event();

	void wait();

protected:
	friend class KernEv;

	void signal();

private:

	KernEv* myImpl;
};

#define PREPAREENTRY(num, flag)\
	void interrupt new_int##num(...);\
	IVTentry newEntry##num(num, new_int##num);\
	void interrupt new_int##num(...){\
		newEntry##num.signal_ev();\
		if (flag == 1) newEntry##num.call_old();\
	}


#endif /* EVENT_H_ */
