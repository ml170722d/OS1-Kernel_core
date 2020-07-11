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
//volatile Kernel::Lock Kernel::CSLock;
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
	if (!Kernel::CS_req) Kernel::csCnt--;
		if ((Kernel::csCnt == 0) || (Kernel::CS_req)) {
			if(!Kernel::Lock::isLocked()){
				Kernel::CS_req=0;
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
				Kernel::csCnt = PCB::runnig->quantum;


				asm {
					// restaurira sp
					mov sp, tsp
					mov ss, tss
					mov bp, tbp
				}
			}
			else{
				Kernel::CS_req=1;
			}
		}

		// poziv stare prekidne rutine
		// koja se nalazila na 08h, a sad je na 60h;
		// poziva se samo kada nije zahtevana promena konteksta
		// tako da se stara rutina poziva
		// samo kada je stvarno doslo do prekida
		if(!Kernel::CS_req) asm int 60h;
}

void Kernel::allocateResources() {
	//TODO: implement
}

void Kernel::freeResources() {
	//TODO: implement
}

void Kernel::init() {
	lock_I;
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
}


void Kernel::requestCS() {
	lock_I;
	Kernel::CS_req = true;
	unlock_I;
}

PCB* Kernel::getRunning(){
	//TODO: implement correctly
	return null;
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

void Kernel::Lock::CS_unlock(){
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

boolean Kernel::Lock::isLocked(){
	return lockCond;
}


/*
 * defining dispatch
 */
void dispatch(){
	Kernel::requestCS(); //makes sure it is not interrupted for itself
	lock_I;
	timer();
	unlock_I
}
