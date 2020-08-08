/*
 * semaphor.h
 *
 *  Created on: Aug 6, 2020
 *      Author: OS1
 */

#ifndef SEMAPHOR_H_
#define SEMAPHOR_H_

#include  "consts.h"

class KernelSem;

class Semaphor {
public:
	Semaphor(int init = 1);

	virtual ~Semaphor();

	virtual int wait(Time maxTimeToWait);

	virtual int signal(int n = 0);

	int val();

private:

	friend void tick();

	KernelSem* myImpl;

};

#endif /* SEMAPHOR_H_ */
