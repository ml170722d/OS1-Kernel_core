/*
 * kernel.cpp
 *
 *  Created on: Jul 1, 2020
 *      Author: OS1
 */

#include "kernel.h"
#include "consts.h"
#include "pcb.h"
#include "SCHEDULE.h"
#include "ker_sem.h"
#include "IVTentry.h"

#include "linkLst.h"
#include "kernsem.h"

LinkedList<PCB*> Kernel::all_pcb;
LinkedList<KernelSem*> Kernel::all_sem;
PCB* Kernel::main_pcb = NULL;
volatile boolean Kernel::CS_req = false;
volatile int Kernel::csCnt = 1;//DEFAULT_TIME_SLICE;
volatile PCB* Kernel::running = NULL;
Kernel::Idle* Kernel::idle_thread = NULL;
IVTentry* Kernel::ivtEntrys[NUMBER_OF_IVT_ENTRIES] = { NULL };

/*
 * old timer routine declaration
 */
pInterrupt oldTimer;

/*
 * variables for temporarily saving system registers
 */
unsigned tsp, tss, tbp;
unsigned tid;

/*
 * new timer routine definition
 */
void interrupt timer(...) {
	//cout<<"*"<<endl;
	if (!Kernel::CS_req) {
		tick();
		Kernel::update();
		asm int 60h;

		Kernel::csCnt--;
	}

	//timeSlice == 0 -> neograniceno vreme izvrsavanja, menja se samo na blokirajuci poziv ili eksplicitni dispatch
		if ((Kernel::running->timeSlice != 0 && Kernel::csCnt <= 0) || (Kernel::CS_req)) {
			//if(!Kernel::Lock::isLocked()){

				//cout<<"context switch ------------"<<endl;
				Kernel::CS_req=0;
				asm {
					// cuva sp
					mov tsp, sp
					mov tss, ss
					mov tbp, bp
				}

				Kernel::running->sp = tsp;
				Kernel::running->ss=tss;
				Kernel::running->bp=tbp;

				// scheduler
				//Kernel::running = getNextPCBToExecute();

				//cout<<"idle prt: "<<Kernel::idle_thread<<endl;
				//cout<<"old running id: "<<Kernel::running->id<<", state: "<<Kernel::running->state<<endl;

				if((Kernel::running->state != PCB::TERMINATED) && (Kernel::running->state != PCB::BLOCKED) && (Kernel::running->id != Kernel::idle_thread->getId())){
					//cout<<"put"<<endl;
					Kernel::running->state = PCB::READY;
					Scheduler::put((PCB*)Kernel::running);
				}

				Kernel::running = Scheduler::get();


				//cout<<(PCB*)Kernel::running<<endl;
				if (Kernel::running == 0){
					//cout<<"running is now idle"<<endl;
					Kernel::running = Kernel::idle_thread->myPCB;
					//cout<<"I";
				}
				//cout<<(PCB*)Kernel::running<<endl;

				//cout<<"new running id: "<<Kernel::running->id<<endl;

				tsp = Kernel::running->sp;
				tss = Kernel::running->ss;
				tbp = Kernel::running->bp;

				//tid = Kernel::running->id;
				Kernel::csCnt = Kernel::running->timeSlice;
				Kernel::running->state = PCB::RUNNING;

				asm {
					mov ss, tss
					// restaurira sp
					mov sp, tsp
					mov bp, tbp
				}
			//}
			//else{
			//	Kernel::CS_req=1;
			//}
		}


}

void Kernel::allocateResources() {
	Kernel::main_pcb = new PCB();
	Kernel::idle_thread = new Idle();
}

void Kernel::freeResources() {
	delete Kernel::main_pcb;
	delete Kernel::idle_thread;
}

void Kernel::init() {
	Kernel::allocateResources();
	lock_I;
	Kernel::running = Kernel::main_pcb;
#ifndef BCC_BLOCK_IGNORE
	//cuvam staru prekidnu rutinu
	oldTimer=getvect(0x8);
	//na 08h stavljam novu
	setvect(0x8,timer);
	//staru premestam na 60h
	setvect(0x60,oldTimer);
#endif
	unlock_I;
}

void Kernel::restore() {
	lock_I;
#ifndef BCC_BLOCK_IGNORE
	setvect(0x8,oldTimer);
#endif
	unlock_I;
	Kernel::freeResources();
}


void Kernel::requestCS() {
	lock_I;
	Kernel::CS_req = true;
	unlock_I;
}

PCB* Kernel::getRunning(){
	return (PCB*)Kernel::running;
}

void Kernel::printAllPCBandSEM(){
	Kernel::Lock::CS_lock();
	for (LinkedList<PCB*>::Iterator it = all_pcb.begin(); it != all_pcb.end(); it++){
		cout<<(*it)->id<<endl;
	}
	cout<<endl;
	for (LinkedList<KernelSem*>::Iterator itt = all_sem.begin(); itt != all_sem.end(); itt++){
		cout<<(*itt)<<endl;
	}
	Kernel::Lock::CS_unlock();
}
/*
 * Kernel::Lock function definitions
 */
volatile boolean Kernel::Lock::lockCond = false;
volatile int Kernel::Lock::lockCnt = 0;
PCB* Kernel::Lock::owner = null;

void Kernel::Lock::CS_lock(){
	lock_I;
	if (owner == null){
		owner = (PCB*) Kernel::running;
		//syncPrintf("new owner id: %d\n", owner->getId());
	}
	if (owner != Kernel::running){
		unlock_I;
		return;
	}

	if (!lockCond){
		lockCond = true;
	}
	lockCnt++;
	unlock_I;
}

void Kernel::Lock::CS_unlock(){
	lock_I;
	if ((owner == null) || (owner != Kernel::running)){
		unlock_I;
		return;
	}

	lockCnt--;
	if (lockCnt == 0){
		lockCond = false;
		owner = null;
		//syncPrintf("owner == null\n");
	}
	unlock_I;
}

boolean Kernel::Lock::isLocked(){
	lock_I;
	//cout<<"lockCont: "<<lockCond<<", lockCnt: "<<lockCnt<<", owner id: "<<owner->getId()<<endl;
	unlock_I;
	return lockCond;
}


Kernel::Idle::Idle(): Thread(DEFAULT_STACK_SIZE, 1), is_active(true) {}

Kernel::Idle::~Idle(){
	is_active = false;
	//waitToComplete();
}

void Kernel::Idle::run(){
<<<<<<< HEAD
	while (is_active) {}
=======
	while (is_active) {
		//syncPrintf("*");
	}
>>>>>>> master
}


/*
 * defining dispatch
 */
void dispatch(){
	//syncPrintf("disp\n");
	Kernel::requestCS(); //makes sure it is not interrupted for itself
	lock_I;
	//cout<<"disp"<<endl;
	timer();
	unlock_I
}

void Kernel::update(){
	//cout << "update ";
	for (LinkedList<KernelSem*>::Iterator it = all_sem.begin(); it != all_sem.end(); it++){
		(*it)->update();
	}
}
