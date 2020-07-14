/*
 * main.cpp
 *
 *  Created on: Jul 11, 2020
 *      Author: OS1
 */

#include "SCHEDULE.H"
#include "pcb.h"
#include "linkLst.h"
#include "kernel.h"

#include "consts.h"

const int N = 10;

void doSomething1() {
	Kernel::Lock::CS_lock();
	PCB* p[N];

	int i;

	for (i = 0; i < N; ++i) {
		p[i] = new PCB(1024, (i % 2) ? 10 : 100, NULL);
		p[i]->start();
	}
	Kernel::Lock::CS_unlock();

/////////////////////////////////////////////////////////////

	Kernel::Lock::CS_lock();
	for (i = 0; i < N; i++) {
		cout << p[i] << " ";
	}
	cout << endl;
	Kernel::printAllPCB();
	Kernel::Lock::CS_unlock();

/////////////////////////////////////////////////////////////

	for (i = 0; i < N; i++) {
		delete p[i];
		p[i] = NULL;
	}
	Kernel::Lock::CS_lock();
	cout << "all pcb terminated" << endl;
	Kernel::Lock::CS_unlock();

/////////////////////////////////////////////////////////////

	Kernel::Lock::CS_lock();
	for (i = 0; i < N; i++) {
		cout << p[i] << " ";
	}
	cout << endl;
	Kernel::printAllPCB();
	Kernel::Lock::CS_unlock();

/////////////////////////////////////////////////////////////

	Kernel::Lock::CS_lock();
	cout << "fin on main end = " << PCB::fin << endl;
	cout << "Happy end for doSomethig1()!" << endl;
	Kernel::Lock::CS_unlock();
}

void doSomething2() {

	Kernel::Lock::CS_lock();
	cout << "fin on main end = " << PCB::fin << endl;
	cout << "Happy end for doSomethig2()!" << endl;
	Kernel::Lock::CS_unlock();
}

int main() {

	Kernel::init();

	doSomething1();

	doSomething2();

	Kernel::restore();

	return 0;

}
