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
#include <iostream.h>
#include <dos.h>
#include "SCHEDULE.H"
#include "PCB.H"

#include "consts.h"

 //pok na prekidnu rutinu
pInterrupt oldTimer;

unsigned stara=0x8;
unsigned nova=0x60;

PCB** p;
//volatile PCB* running;
volatile int nextThread = 2;

// stara prekidna rutina
unsigned oldTimerOFF, oldTimerSEG;

// deklaracija nove prekidne rutine
void interrupt timer(...);

// postavlja novu prekidnu rutinu
void inic(){
#ifndef BCC_BLOCK_IGNORE
	asm cli;
	//cuvam staru prekidnu rutinu
	oldTimer=getvect(stara);
	//na 08h stavljam novu
	setvect(stara,timer);
	//staru premestam na 60h
	setvect(nova,oldTimer);
	asm sti;
#endif
}

// vraca staru prekidnu rutinu
void restore(){
#ifndef BCC_BLOCK_IGNORE
	asm cli;
	setvect(stara,oldTimer);
	asm sti;
#endif
}

//pomocne promenljive za prekid tajmera
unsigned tsp, tss, tbp;
unsigned tid;


class Lock{
public:
	static void lock();
	static void unlock();
	static boolean isLocked();
private:
	static PCB* owner;
	static volatile int lockCnt;
	static volatile boolean lockCond; //false -> unlocked, true -> losked
};

volatile boolean Lock::lockCond = false;
volatile int Lock::lockCnt = 0;
PCB* Lock::owner = null;

void Lock::lock(){
	lock_I;
	if (owner == null){
		owner = (PCB*) PCB::runnig;
	}
	if (owner != PCB::runnig){
		unlock_I;
		return;
	}

	if (!lockCond){
		lockCond = true;
	}
	lockCnt++;
	unlock_I;
}

void Lock::unlock(){
	lock_I;
	if ((owner == null) || (owner != PCB::runnig)){
		unlock_I;
		return;
	}

	lockCnt--;
	if (lockCnt == 0){
		lockCond = false;
	}
	unlock_I;
}

boolean Lock::isLocked(){
	return lockCond;
}

volatile boolean lockFlag = true;

volatile int csCnt = 20;
volatile boolean CS_req = false;

// nova prekidna rutina tajmera
void interrupt timer(...){
	int dummy=0;
	if (!CS_req) csCnt--;
	if (csCnt == 0 || CS_req) {
		if(!Lock::isLocked()){
			CS_req=0;
			asm {
				// cuva sp
				mov tsp, sp
				mov tss, ss
				mov tbp, bp
			}

			PCB::runnig->sp = tsp;
			PCB::runnig->ss=tss;
			PCB::runnig->bp=tbp;

			// scheduler
			//PCB::runnig = getNextPCBToExecute();

			cout<<"old running id: "<<PCB::runnig->id<<endl;
			if(PCB::runnig->state!=PCB::FINISHED) Scheduler::put((PCB*)PCB::runnig);
			PCB::runnig=Scheduler::get();

			if(PCB::runnig->quantum==0){
				Scheduler::put((PCB*)PCB::runnig);
				cout<<"quantum=0, id: "<<PCB::runnig->id<<endl;
				PCB::runnig=Scheduler::get();
			}

			cout<<"new running id: "<<PCB::runnig->id<<endl;

			tsp = PCB::runnig->sp;
			tss = PCB::runnig->ss;
			tbp = PCB::runnig->bp;

			tid = PCB::runnig->id;
			csCnt = PCB::runnig->quantum;


			asm {
				// restaurira sp
				mov sp, tsp
				mov ss, tss
				mov bp, tbp
			}
		}
		else{
			CS_req=1;
		}
	}

	// poziv stare prekidne rutine
	// koja se nalazila na 08h, a sad je na 60h;
	// poziva se samo kada nije zahtevana promena konteksta
	// tako da se stara rutina poziva
	// samo kada je stvarno doslo do prekida
	if(!CS_req) asm int 60h;

	//CS_req = 0;
}

// sinhrona promena konteksta
void dispatch(){
	lock_I
	CS_req = 1;
	timer();
	unlock_I
}

void exitThread(){
	PCB::runnig->state = PCB::FINISHED;
	dispatch();
}

const int M = 20;

void f(){
	for (int i =0; i < M; ++i) {
			Lock::lock();
			cout<<"funkcija_"<<tid<<" "<<i<<endl;
			Lock::unlock();
			if(CS_req)
				dispatch();
			for (int k = 0; k<10000; ++k)
				for (int j = 0; j <30000; ++j);
		}
		exitThread();
}


const int N = 10;

void doSomething(){
	lock_I;

	//testiram sa 10 niti
	p[0] = new PCB();
	PCB::runnig = p[0];
	p = new PCB*[N];

	for (int br = 1; br < N; ++br) {
		p[br] = new PCB(1024,(br%2)?15:10,f);  //(br%2)?40:20 da bi se niti razlikovale po vremenu izvrsavanja
		Scheduler::put(p[br]);
	}



	unlock_I;

	for (int i = 0; i < 15; ++i) {
		lock_I;
		cout<<"main "<<i<<endl;
		unlock_I;

		for (int j = 0; j< 10000; ++j)
			for (int k = 0; k < 30000; ++k);
	}
	cout<<"Srecan kraj!"<<endl;
}

int main(){

	inic();

	doSomething();

	restore();

	return 0;

}
