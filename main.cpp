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

void exitThread(){
	Kernel::running->state = PCB::TERMINATED;
	dispatch();
}

const int M = 20;

/*
void f(){
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
	cout<<"----------fin: "<<++fin<<endl;
	Kernel::Lock::CS_unlock();

	exitThread();
}
*/

const int N = 10;

void doSomething(){
	lock_I;

	//testiram sa 10 niti
	//p[0] = new PCB();
	//PCB::runnig = p[0];
	p = new PCB*[N];

	for (int br = 0; br < N; ++br) {
		p[br] = new PCB(1024,(br%2)?30:20, NULL);  //(br%2)?40:20 da bi se niti razlikovale po vremenu izvrsavanja
		Scheduler::put(p[br]);
	}



	unlock_I;

	for (int i = 0; i < M; ++i) {
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
	}

	cout<<"fin on main end = "<<PCB::fin<<endl;
	cout<<"Srecan kraj!"<<endl;
}

int main(){

	Kernel::init();

	doSomething();

	Kernel::restore();

	return 0;

}
