/*
 * main.cpp
 *
 *  Created on: Jul 11, 2020
 *      Author: OS1
 */

//  v2_zad4.cpp
//  prevodjenje iz komandne linije: bcc -mh -Ic:\bc31\include -Lc:\bc31\lib v2_zad4.cpp

//////////////////////////
//dodata PCB.H i ostale izmene da bi radilo
//////////////////////////

//pretpostavljeni memorijski model: huge
#include "SCHEDULE.H"
#include "pcb.h"
#include "linkLst.h"
#include "kernel.h"

#include "consts.h"

PCB** p;

const int N = 10;

void doSomething(){
	lock_I;

	p = new PCB*[N];

	int i;

	for (i = 0; i < N; ++i) {
		p[i] = new PCB(1024,(i%2)?30:20, NULL);  //(br%2)?40:20 da bi se niti razlikovale po vremenu izvrsavanja
		p[i]->start();
	}



	unlock_I;

	/*for (i = 0; i < M; ++i) {
		lock_I;
		cout<<"main "<<i<<endl;
		unlock_I;

		for (int j = 0; j< 10000; ++j)
			for (int k = 0; k < 30000; ++k);

		if (i%10 == 0){
			Kernel::Lock::CS_lock();
			cout<<"----------------------"<<endl;
			cout<<"i = "<<i<<endl;
			cout<<"----------------------"<<endl;
			//tests_for_linkedList();
			cout<<"----------------------"<<endl;
			Kernel::Lock::CS_unlock();
		}
	}*/

	Kernel::Lock::CS_lock();
	for (i = 0; i < N; i++){
		cout << p[i]<<" ";
	}
	cout<<endl;
	Kernel::all_pcb.printList();
	Kernel::Lock::CS_unlock();

	for (i = 0; i < N; i++){
		delete p[i];
	}
	cout<<"all pcb terminated"<<endl;
	delete p;

	cout<<"fin on main end = "<<PCB::fin<<endl;
	cout<<"Srecan kraj!"<<endl;
}

int main(){

	Kernel::init();

	doSomething();

	Kernel::restore();

	return 0;

}
