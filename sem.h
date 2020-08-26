/*
 * sem.h
 *
 *  Created on: Jul 20, 2020
 *      Author: OS1
 */

#ifndef SEM_H_
#define SEM_H_

#include "consts.h"

class KernelSem;

class Semaphore {
public:
	Semaphore(int init = 1);
	virtual ~Semaphore();

	virtual int wait(Time maxTimeToWait);
	virtual int signal(int n = 0);

	int val() const;

private:

	KernelSem* myImpl;

};

#endif /* SEM_H_ */
