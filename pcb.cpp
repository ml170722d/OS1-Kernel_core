/*
 * pcb.cpp
 *
 *  Created on: Jul 11, 2020
 *      Author: OS1
 */

#include "pcb.h"

volatile PCB* PCB::runnig=0;

int PCB::ID=0;

PCB::PCB(): state(PCB::NEW), quantum(2), id(ID++), stack(0), sp(0), ss(0), bp(0){
}

PCB::PCB(unsigned stackSize, int timeSlice, void (*body)()): state(PCB::NEW), quantum(timeSlice), id(ID++), sp(0), ss(0), bp(0){
		asm cli;

		stack = new unsigned [stackSize];
		stack[stackSize-1] = 0x200;

#ifndef BCC_BLOCK_IGNORE
		stack[stackSize-2] = FP_SEG(body);
		stack[stackSize-3] = FP_OFF(body);

		sp = FP_OFF(stack+1012);
		ss = FP_SEG(stack+1012);
		bp = FP_OFF(stack+1012);
#endif

		asm sti;
}
