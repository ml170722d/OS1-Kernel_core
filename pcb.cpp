/*
 * pcb.cpp
 *
 *  Created on: Jul 11, 2020
 *      Author: OS1
 */

#include "pcb.h"
#include "consts.h"

#include "kernel.h"

volatile PCB* PCB::runnig=0;

int PCB::ID=0;

PCB::PCB(): state(PCB::NEW), quantum(DEFAILT_TIME_SLICE), id(ID++), stack(0), sp(0), ss(0), bp(0){
}

PCB::PCB(unsigned stackSize, int timeSlice, void (*body)()): state(PCB::NEW), quantum(timeSlice), id(ID++), sp(0), ss(0), bp(0){
		asm cli;

		stack = new unsigned [stackSize];
		stack[stackSize-1] = 0x200;

#ifndef BCC_BLOCK_IGNORE
		stack[stackSize-2] = FP_SEG(PCB::wrapper);
		stack[stackSize-3] = FP_OFF(PCB::wrapper);

		sp = FP_OFF(stack+1012);
		ss = FP_SEG(stack+1012);
		bp = FP_OFF(stack+1012);
#endif

		asm sti;
}

volatile int PCB::fin = 0;
const int M = 20;

void PCB::wrapper(){
	for (int i =0; i < M; ++i) {
		Kernel::Lock::CS_lock();
		//cout<<"funkcija_"<<tid<<" "<<i<<endl;
		Kernel::Lock::CS_unlock();
		if(Kernel::CS_req)
			dispatch();
		for (int k = 0; k<10000; ++k)
			for (int j = 0; j <30000; ++j);
	}

	Kernel::Lock::CS_lock();
	cout<<"----------fin: "<<++PCB::fin<<endl;
	Kernel::Lock::CS_unlock();

	exitThread();
}
