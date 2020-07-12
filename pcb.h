/*
 * pcb.h
 *
 *  Created on: Jul 11, 2020
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_

class PCB{

public:

	static volatile PCB* runnig;

	enum State { READY, RUNNING, BLOCKED, FINISHED, NEW };

	PCB();
	PCB(unsigned stackSize, int timeSlice, void (*body)());


private:

	friend void interrupt timer(...);
	friend void dispatch();
	friend void exitThread();

	//tmp friend
	friend void doSomething();

	unsigned bp;
	unsigned sp;
	unsigned ss;
	State state;
	unsigned* stack;
	int quantum;
	int id;

	static int ID;

	static void wrapper();

	static volatile int fin;

};

#endif /* PCB_H_ */
