/*
 * consts.h
 *
 *  Created on: Jul 11, 2020
 *      Author: OS1
 */

#ifndef CONSTS_H_
#define CONSTS_H_

/*
 * always import these .h files with consts.h
 */
#include <iostream.h>
#include <dos.h>

/*
 * definition of custom types
 */
typedef void interrupt (*pInterrupt)(...);
typedef unsigned int Time;
typedef unsigned long int StackSize;
typedef int _ID;
typedef unsigned short int boolean;
typedef short int  ptr;

/*
 * definition of constanst
 */
const StackSize DEFAULT_STACK_SIZE = 4096;
const Time DEFAULT_TIME_SLICE = 2;
const boolean true = 1;
const boolean false = 0;
const ptr null = 0;

/*
 * definition of macros
 */
#define lock_I asm cli
#define unlock_I asm sti
#define NULL 0

#endif /* CONSTS_H_ */
