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

PCB** p;

const int N = 10;

void waitForSomeTime(int n){
	Kernel::Lock::CS_lock();
	cout<<"start of nested lock"<<endl;
	int i, j, k;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			for (k = 0; k < n; k++){

			}
	cout<<"end of nested lock"<<endl;
	Kernel::Lock::CS_unlock();
}

void doSomething(){
	Kernel::Lock::CS_lock();

	p = new PCB*[N];

	int i;

	for (i = 0; i < N; ++i) {
		p[i] = new PCB(1024,(i%2)?20:50, NULL);  //(br%2)?40:20 da bi se niti razlikovale po vremenu izvrsavanja
		p[i]->start();
	}

	Kernel::Lock::CS_unlock();

	dispatch();

	Kernel::Lock::CS_lock();
	cout<<"start wait main"<<endl;
	waitForSomeTime(1000);
	cout<<"end wait main"<<endl;
	Kernel::Lock::CS_unlock();
	//dispatch();

	Kernel::Lock::CS_lock();
	for (i = 0; i < N; i++){
		cout << p[i]<<" ";
	}
	cout<<endl;
	Kernel::all_pcb.printList();
	Kernel::Lock::CS_unlock();

	for (i = N - 1; i >= 0; i--){
		delete p[i];
		p[i] = null;
	}
	cout<<"all pcb terminated"<<endl;
	delete p;

	Kernel::Lock::CS_lock();
	for (i = 0; i < N; i++){
		cout << p[i]<<" ";
	}
	cout<<endl;
	Kernel::all_pcb.printList();
	Kernel::Lock::CS_unlock();

	cout<<"fin on main end = "<<PCB::fin<<endl;
	cout<<"Srecan kraj!"<<endl;
}

int main(){

	Kernel::init();

	doSomething();

	Kernel::restore();

	return 0;

}
