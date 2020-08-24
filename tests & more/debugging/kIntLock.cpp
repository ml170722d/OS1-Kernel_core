#include "kIntLock.h"
#include "kernel.h"

int kern_mutex_glb = 1;

void kern_mutex_glb_wait(){
 ksloop:asm{
	mov ax, 0
	xchg ax, kern_mutex_glb
}
 if(_AX ==0){
	dispatch();
	asm jmp ksloop;
 }
}
