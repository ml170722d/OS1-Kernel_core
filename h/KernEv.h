/*
 * KernEv.h
 *
 *  Created on: Aug 10, 2020
 *      Author: OS1
 */

#ifndef KERNEV_H_
#define KERNEV_H_

#include "consts.h"

class PCB;

class KernEv {
public:
	KernEv(IVTNo ivtNo);
	virtual ~KernEv();

	void wait();
	void signal();
private:
	IVTNo ivtNo;
	PCB* owner;
};

#endif /* KERNEV_H_ */
