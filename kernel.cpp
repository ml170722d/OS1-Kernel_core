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

#include "linkLst.h"

LinkedList<PCB*> Kernel::all_pcb;
PCB* Kernel::main_pcb = NULL;
volatile boolean Kernel::CS_req = false;
volatile int Kernel::csCnt = 20;//DEFAULT_TIME_SLICE;
volatile PCB* Kernel::running = NULL;



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
	if (!Kernel::CS_req) Kernel::csCnt--;
		if ((Kernel::csCnt <= 0) || (Kernel::CS_req)) {
			if(!Kernel::Lock::isLocked()){

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

				//cout<<"old running id: "<<Kernel::running->id<<endl;
				if((Kernel::running->state != PCB::TERMINATED) && (Kernel::running->state != PCB::BLOCKED)){
					//cout<<"put"<<endl;
					Scheduler::put((PCB*)Kernel::running);
				}
				Kernel::running = Scheduler::get();

				if(Kernel::running->timeSlice == 0){
					Scheduler::put((PCB*)Kernel::running);
					cout<<"quantum=0, id: "<<Kernel::running->id<<endl;
					Kernel::running=Scheduler::get();
				}

				//cout<<"new running id: "<<Kernel::running->id<<endl;

				tsp = Kernel::running->sp;
				tss = Kernel::running->ss;
				tbp = Kernel::running->bp;

				tid = Kernel::running->id;
				Kernel::csCnt = Kernel::running->timeSlice;


				asm {
					// restaurira sp
					mov sp, tsp
					mov ss, tss
					mov bp, tbp
				}
			}

			Kernel::running->sp = tsp;
			Kernel::running->ss=tss;
			Kernel::running->bp=tbp;

			// scheduler
			//Kernel::running = getNextPCBToExecute();

			//cout<<"old running id: "<<Kernel::running->id<<endl;
			if((Kernel::running->state != PCB::TERMINATED) && (Kernel::running->state != PCB::BLOCKED)){
				//cout<<"put"<<endl;
				Scheduler::put((PCB*)Kernel::running);
			}
			Kernel::running = Scheduler::get();

			if(Kernel::running->timeSlice == 0){
				Scheduler::put((PCB*)Kernel::running);
				cout<<"quantum=0, id: "<<Kernel::running->id<<endl;
				Kernel::running=Scheduler::get();
			}

			//cout<<"new running id: "<<Kernel::running->id<<endl;

			tsp = Kernel::running->sp;
			tss = Kernel::running->ss;
			tbp = Kernel::running->bp;

			tid = Kernel::running->id;
			Kernel::csCnt = Kernel::running->timeSlice;


			asm {
				// restaurira sp
				mov sp, tsp
				mov ss, tss
				mov bp, tbp
			}
		}else{
			Kernel::CS_req = true;
		}
	}
}

void Kernel::allocateResources() {
	lock_I;
	Kernel::main_pcb = new PCB();
	unlock_I;
}

void Kernel::freeResources() {
	lock_I;
	delete Kernel::main_pcb;
	unlock_I;
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

void Kernel::printAllPCB(){
	Kernel::Lock::CS_lock();
	Kernel::all_pcb.printList();
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
	//cout<<"lock -> owner: "<<owner<<", runnning: "<<(PCB*)Kernel::running<<endl;
	if (owner == null){
		owner = (PCB*) Kernel::running;
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
	//cout<<"unlock -> owner: "<<owner<<", runnning: "<<(PCB*)Kernel::running<<endl;
	if ((owner == null) || (owner != Kernel::running)){
		unlock_I;
		return;
	}

	lockCnt--;
	if (lockCnt == 0){
		lockCond = false;
		owner = null;
	}
	unlock_I;
}

boolean Kernel::Lock::isLocked(){
	lock_I;
	//cout<<"lockCont: "<<lockCond<<", lockCnt: "<<lockCnt<<", owner: "<<owner->id<<endl;
	unlock_I;
	return lockCond;
}


/*
 * TODO: should be moved to thread.cpp (asked in project)
 * defining dispatch
 * NOTE: dispatch can't be called from code inside context switch block (it has no effect otherwise)
 */
void dispatch(){
	Kernel::requestCS(); //makes sure it is not interrupted for itself
	lock_I;
	cout<<"disp: "<<PCB::getRunningId()<<endl;
	timer();
	unlock_I
}
