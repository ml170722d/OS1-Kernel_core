/*
 * kIntLock.h
 *
 *  Created on: Aug 24, 2020
 *      Author: OS1
 */

#ifndef KERNEL_INTLOCK_H_
#define KERNEL_INTLOCK_H_

extern int kern_mutex_glb;
void kern_mutex_glb_wait();

#define kIntLock kern_mutex_glb_wait();
#define kIntUnlock kern_mutex_glb = 1;

#endif
